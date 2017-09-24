

#include "../Mapping.hpp"
#include "../PfnDatabase.hpp"
#include "../CommitCharge.hpp"
#include "../AddressSpace.hpp"
#include <eal.h>

#define DPRINT(...)

namespace Mm {

static const
USHORT ProtectToWin32Protect[32] =
{
    PAGE_NOACCESS, // MM_INVALID
    PAGE_READONLY, // MM_READONLY
    PAGE_EXECUTE_READ, // MM_EXECUTE
    PAGE_EXECUTE_READ, // MM_EXECUTE_READ
    PAGE_READWRITE, // MM_READWRITE
    PAGE_WRITECOPY, // MM_WRITECOPY
    PAGE_EXECUTE_READWRITE, // MM_EXECUTE_READWRITE
    PAGE_EXECUTE_WRITECOPY, // MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_UNCACHED | MM_INVALID
    PAGE_NOCACHE | PAGE_READONLY, // MM_UNCACHED | MM_READONLY
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE_READ
    PAGE_NOCACHE | PAGE_READWRITE, // MM_UNCACHED | MM_READWRITE
    PAGE_NOCACHE | PAGE_WRITECOPY, // MM_UNCACHED | MM_WRITECOPY
    PAGE_NOCACHE | PAGE_EXECUTE_READWRITE, // MM_UNCACHED | MM_EXECUTE_READWRITE
    PAGE_NOCACHE | PAGE_EXECUTE_WRITECOPY, // MM_UNCACHED | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_GUARDPAGE | MM_INVALID
    PAGE_GUARD | PAGE_READONLY, // MM_GUARDPAGE | MM_READONLY
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE_READ
    PAGE_GUARD | PAGE_READWRITE, // MM_GUARDPAGE | MM_READWRITE
    PAGE_GUARD | PAGE_WRITECOPY, // MM_GUARDPAGE | MM_WRITECOPY
    PAGE_GUARD | PAGE_EXECUTE_READWRITE, // MM_GUARDPAGE | MM_EXECUTE_READWRITE
    PAGE_GUARD | PAGE_EXECUTE_WRITECOPY, // MM_GUARDPAGE | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_WRITECOMBINE | MM_INVALID
    PAGE_WRITECOMBINE | PAGE_READONLY, // MM_WRITECOMBINE | MM_READONLY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE_READ
    PAGE_WRITECOMBINE | PAGE_READWRITE, // MM_WRITECOMBINE | MM_READWRITE
    PAGE_WRITECOMBINE | PAGE_WRITECOPY, // MM_WRITECOMBINE | MM_WRITECOPY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READWRITE, // MM_WRITECOMBINE | MM_EXECUTE_READWRITE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_WRITECOPY, // MM_WRITECOMBINE | MM_EXECUTE_WRITECOPY
};

ULONG __attribute__((section(".local"))) PageCommitBitmapBuffer[0x4000];
RTL_BITMAP PageCommitBitmap = {0x80000, PageCommitBitmapBuffer};

extern ULONG_PTR LowestSystemVpn;
extern "C" ULONG NumberOfProcesses;
extern "C" PVOID MmPagedPoolStart;
extern "C" PVOID MmPagedPoolEnd;

PFN_NUMBER GlobalZeroPfn;
ULONG MappingRecordTimeStamp = 0;
ULONG NumberOfMappingRecords = 0;
KSPIN_LOCK MappingRecordListLock;
LIST_ENTRY MappingRecordListHead;
ULONG PagedPoolFileDescriptor;
ULONG PagedPoolSectionSize;

PVOID
ReserveKernelMemory (
    SIZE_T Size);

VOID
ReleaseKernelMemory (
    _In_ PVOID BaseAddress);

ULONG
ConvertProtect (
    _In_ ULONG Win32Protect)
{
    ULONG Protect = MM_INVALID;

    if (Win32Protect & PAGE_IS_WRITECOPY)
        Protect = MM_WRITECOPY;
    else if (Win32Protect & PAGE_IS_WRITABLE)
        Protect = MM_READWRITE;
    else if (Win32Protect & PAGE_IS_READABLE)
        Protect = MM_READONLY;

    if (Win32Protect & PAGE_IS_EXECUTABLE)
        Protect |= MM_EXECUTE;

    if (Win32Protect & PAGE_WRITECOMBINE)
        Protect |= MM_WRITECOMBINE;
    else if (Win32Protect & PAGE_NOCACHE)
        Protect |= MM_UNCACHED;

    return Protect;
}

ULONG
ConvertProtectAndCaching (
    _In_ ULONG Win32Protect,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    /* Set caching type */
    Win32Protect &= ~(PAGE_NOCACHE | PAGE_WRITECOMBINE);
    if ((CachingType == MmNonCached) || (CachingType == MmNonCachedUnordered))
        Win32Protect |= PAGE_NOCACHE;
    else if (CachingType == MmWriteCombined)
        Win32Protect |= PAGE_WRITECOMBINE;

    return ConvertProtect(Win32Protect);
}

ULONG
ConvertProtectToWin32 (
    _In_ ULONG Protect)
{
    /* Convert it to the win32 format */
    return ProtectToWin32Protect[Protect & MM_PROTECTION_MASK];
}

typedef struct _MAPPING_RECORD
{
    LIST_ENTRY ListEntry;
    ULONG ProcessCount;
    ULONG TimeStamp;
    ULONG_PTR StartingVpn;
    ULONG_PTR NumberOfPages;
    ULONG Protect;
    UINT32 FileDescriptor;
    UINT32 SectionOffset;
} MAPPING_RECORD, *PMAPPING_RECORD;

VOID
CommitPagesInBitmap (
    ULONG StartingVpn,
    ULONG NumberOfPages)
{
    ASSERT(StartingVpn < 0x80000);
    ASSERT(0x80000 - StartingVpn > NumberOfPages);
    RtlSetBits(&PageCommitBitmap, StartingVpn, NumberOfPages);
}

VOID
DecommitPagesInBitmap (
    ULONG StartingVpn,
    ULONG NumberOfPages)
{
    ASSERT(StartingVpn < 0x80000);
    ASSERT(0x80000 - StartingVpn > NumberOfPages);
    RtlClearBits(&PageCommitBitmap, StartingVpn, NumberOfPages);
}

VOID
InitializeMappingSupport (
    VOID)
{

    InitializeListHead(&MappingRecordListHead);
    KeInitializeSpinLock(&MappingRecordListLock);

    /* Create a shared memory object for paged pool */
    PagedPoolFileDescriptor = EalCreateSharedMemoryObject();
    if (PagedPoolFileDescriptor == 0)
    {
        __debugbreak();
    }

}

VOID
DeleteMappingRecord (
    PMAPPING_RECORD MappingRecord)
{
    /* Check if this was a private mapping */
    if (MappingRecord->FileDescriptor & 0x80000000)
    {
        /* We don't need this file descriptor anymore */
        EalClose(MappingRecord->FileDescriptor & ~0x80000000);
    }

    /* Delete the record */
    ExFreePoolWithTag(MappingRecord, 'RMmM');
}

VOID
NTAPI
RegisterMappingRecord (
    ULONG_PTR StartingVpn,
    ULONG_PTR NumberOfPages,
    ULONG Protect,
    UINT32 FileDescriptor,
    UINT32 SectionOffset)
{
    PMAPPING_RECORD MappingRecord;
    KIRQL OldIrql;

    /* Allocate a mapping record */
    MappingRecord = (PMAPPING_RECORD)ExAllocatePoolWithTag(NonPagedPool, sizeof(*MappingRecord), 'RMmM');
    if (MappingRecord == NULL)
    {
        /// FIXME, should switch processes or something
        __debugbreak();
    }

    /* Set parameters */
    MappingRecord->StartingVpn = StartingVpn;
    MappingRecord->NumberOfPages = NumberOfPages;
    MappingRecord->Protect = Protect;
    MappingRecord->FileDescriptor = FileDescriptor;
    MappingRecord->SectionOffset = SectionOffset;

    /* Lock the list */
    OldIrql = KfAcquireSpinLock(&MappingRecordListLock);

    /* Set current number of processes and next time stamp */
    MappingRecord->ProcessCount = NumberOfProcesses - 1;
    MappingRecord->TimeStamp = ++MappingRecordTimeStamp;

    /* Insert the entry at the tail */
    InsertTailList(&MappingRecordListHead, &MappingRecord->ListEntry);
    NumberOfMappingRecords++;

    DPRINT("RegisterMappingRecord(Vpn %x, Cnt %x, Prt %x, FD 0x%x, Off %x), TS %x\n",
        StartingVpn, NumberOfPages, Protect, FileDescriptor, SectionOffset, MappingRecordTimeStamp);

    /* Release the lock */
    KeReleaseSpinLock(&MappingRecordListLock, OldIrql);

    /* Update the process mapping time stamp */
    PsGetCurrentProcess()->Spare0[0] = (PVOID)MappingRecordTimeStamp;
}

VOID
NTAPI
ProcessSingleMappingRecord (
    PMAPPING_RECORD MappingRecord)
{
    NTSTATUS Status;

    DPRINT("ProcessSingleMappingRecord: %p - %p, FD 0x%x\n",
             VpnToAddress(MappingRecord->StartingVpn),
             VpnToAddress(MappingRecord->StartingVpn + MappingRecord->NumberOfPages),
             MappingRecord->FileDescriptor);

    /* Map the part of the shared memory object */
    Status = EalMapSharedMemoryObject(MappingRecord->FileDescriptor & ~0x80000000,
                                      VpnToAddress(MappingRecord->StartingVpn),
                                      MappingRecord->NumberOfPages * PAGE_SIZE,
                                      MappingRecord->SectionOffset,
                                      MappingRecord->Protect);
    if (!NT_SUCCESS(Status))
    {
        __debugbreak();
    }
}

extern "C"
VOID
NTAPI
ProcessMappingRecords (
    VOID)
{
    PMAPPING_RECORD MappingRecord;
    KIRQL OldIrql;
    ULONG ProcessCount, ProcessTimeStamp;
    PEPROCESS CurrentProcess;
    PLIST_ENTRY ListEntry;
//__debugbreak();
    /* Get the current process */
    CurrentProcess = PsGetCurrentProcess();

    /* Lock the list */
    OldIrql = KfAcquireSpinLock(&MappingRecordListLock);

    /* Get the last mapping time stamp from the process */
    ProcessTimeStamp = (ULONG)CurrentProcess->Spare0[0];

    /* Get the list head and start looping */
    ListEntry = MappingRecordListHead.Flink;
    while (ListEntry != &MappingRecordListHead)
    {
        /* Get the mapping record and check if it's new */
        MappingRecord = CONTAINING_RECORD(ListEntry, MAPPING_RECORD, ListEntry);
        if (MappingRecord->TimeStamp > ProcessTimeStamp)
        {
            /* We will now process the record, so decrement it's process count */
            ProcessCount = --MappingRecord->ProcessCount;

            /* Process this record */
            ProcessSingleMappingRecord(MappingRecord);

            /* Check if the record is completed */
            if (ProcessCount == 0)
            {
                /* Get the next entry */
                ListEntry = ListEntry->Flink;

                /* Remove the entry from the list */
                RemoveEntryList(&MappingRecord->ListEntry);
                NumberOfMappingRecords--;

                DeleteMappingRecord(MappingRecord);

                continue;
            }
        }

        /* Get the next entry */
        ListEntry = ListEntry->Flink;
    }

    /* Update the process time stamp */
    CurrentProcess->Spare0[0] = (PVOID)MappingRecordTimeStamp;

    /* Release the lock */
    KeReleaseSpinLock(&MappingRecordListLock, OldIrql);


}

_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
ReserveSystemMappingRange (
    _In_ ULONG_PTR NumberOfPages)
{
    PVOID BaseAddress;

    /* Reserve kernel address space */
    BaseAddress = ReserveKernelVaSpace(NumberOfPages);
    if (BaseAddress == NULL)
    {
        ERR("Could not reserve kernel address space.\n");
        return NULL;
    }

    /* Return the base address of the mapping range */
    return BaseAddress;
}

VOID
ReleaseSystemMappingRange (
    _In_ PVOID BaseAddress)
{
    ReleaseKernelVaSpace(BaseAddress);
}

VOID
UnmapSystemMappingRange (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR NumberOfPages)
{
    EalUnmapVirtualMemory(BaseAddress, NumberOfPages * PAGE_SIZE);
}

NTSTATUS
MapVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    NTSTATUS Status;
    PVOID BaseAddress;
    ULONG SectionOffset;
    UINT32 FileDescriptor;

    BaseAddress = VpnToAddress(StartingVpn);

    DPRINT("MapVirtualMemory %p - %p (process 0x%x)\n",
             BaseAddress, VpnToAddress(StartingVpn + NumberOfPages), PsGetCurrentProcessId());

    /* Check for usermode mappings */
    if (BaseAddress <= MmHighestUserAddress)
    {
        /* just map the memory */
        Status = EalMapVirtualMemory(BaseAddress,
                                     NumberOfPages * PAGE_SIZE,
                                     Protect);
        if (NT_SUCCESS(Status))
        {
            /* Mark the pages as committed */
            CommitPagesInBitmap(StartingVpn, NumberOfPages);
        }

        return Status;
    }

    /* Check if we even need to register anything */
    if (NumberOfProcesses == 1)
    {
        /* We only have one process, so no need to process anything */
        return EalMapVirtualMemory(BaseAddress,
                                   NumberOfPages * PAGE_SIZE,
                                   Protect);
    }
//__debugbreak();
    /* Check if this is paged pool */
    if ((BaseAddress >= MmPagedPoolStart) && (BaseAddress <= MmPagedPoolEnd))
    {
        /* Calculate offset into paged pool */
        SectionOffset = (ULONG)BaseAddress - (ULONG)MmPagedPoolStart;

        if (PagedPoolSectionSize < (SectionOffset + NumberOfPages * PAGE_SIZE))
        {
            PagedPoolSectionSize = SectionOffset + NumberOfPages * PAGE_SIZE;
            Status = EalSetSectionSize(PagedPoolFileDescriptor, PagedPoolSectionSize);
        }

        /* Map the part of the paged pool shared memory object */
        Status = EalMapSharedMemoryObject(PagedPoolFileDescriptor,
                                          BaseAddress,
                                          NumberOfPages * PAGE_SIZE,
                                          SectionOffset,
                                          Protect);
        if (NT_SUCCESS(Status))
        {
            RegisterMappingRecord(StartingVpn,
                                  NumberOfPages,
                                  Protect,
                                  PagedPoolFileDescriptor,
                                  SectionOffset);
        }
    }
    else
    {
        /* Create a shared memory object */
        FileDescriptor = EalCreateSharedMemoryObject();
        if (FileDescriptor == 0)
        {
            __debugbreak();
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        Status = EalSetSectionSize(FileDescriptor, NumberOfPages * PAGE_SIZE);
        if (!NT_SUCCESS(Status))
        {
            __debugbreak();
            return Status;
        }

        /* Map the part of the paged pool shared memory object */
        Status = EalMapSharedMemoryObject(FileDescriptor,
                                          BaseAddress,
                                          NumberOfPages * PAGE_SIZE,
                                          0,
                                          Protect);
        if (NT_SUCCESS(Status))
        {
            RegisterMappingRecord(StartingVpn,
                                  NumberOfPages,
                                  Protect,
                                  FileDescriptor | 0x80000000,
                                  0);
        }
    }

    return Status;
}

NTSTATUS
MapNonPagedMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    return MapVirtualMemory(StartingVpn, NumberOfPages, Protect);
}

NTSTATUS
ProtectVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _Out_ PULONG OutOldProtect)
{
    NTSTATUS Status;
    UINT32 OldProtect;
    SIZE_T Size;
    /// FIXME Should use some locking

    /* Check if all pages are comitted */
    if (!RtlAreBitsSet(&PageCommitBitmap, StartingVpn, NumberOfPages))
    {
        EalDumpMemoryMap();
        __debugbreak();
        return STATUS_NOT_COMMITTED;
    }
    
    EalQueryProtection(VpnToAddress(StartingVpn), &Size, &OldProtect);
    *OutOldProtect = OldProtect;

    Status = EalProtectVirtualMemory(VpnToAddress(StartingVpn),
                                     NumberOfPages * PAGE_SIZE,
                                     Protect);

    return Status;
}

VOID
CheckVirtualMapping (
    _In_ PVOID BaseAddress,
    _Out_ PSIZE_T OutRegionSize,
    _Out_ PULONG OutProtect)
{
    EalQueryProtection(BaseAddress, OutRegionSize, (UINT32*)OutProtect);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
MapPhysicalMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PFN_NUMBER BasePageFrameNumber)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
MapPfnArray (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PPFN_NUMBER PfnArray)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
MapPrototypePtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PVOID Prototypes)
{
    __debugbreak();
    return STATUS_SUCCESS;
}


VOID
UnmapPages (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ BOOLEAN ReleasePages)
{
    __debugbreak();
}


/// ****************************************************************************


extern "C" {

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_When_ (return != NULL, _Out_writes_bytes_opt_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateMappingAddress (
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag) /// \todo handle Tag
{
    PVOID BaseAddress;
    NTSTATUS Status;

    /* Reserve virtual memory range */
    BaseAddress = ReserveKernelVaSpace(NumberOfBytes);
    if (BaseAddress == NULL)
    {
        return NULL;
    }

    /* Map no-access PTEs */
    Status = MapVirtualMemory(AddressToVpn(BaseAddress),
                              BYTES_TO_PAGES(NumberOfBytes),
                              MM_NOACCESS | MM_GLOBAL | MM_NONPAGED);
    if (!NT_SUCCESS(Status))
    {
        ReleaseKernelVaSpace(BaseAddress);
        return NULL;
    }

    return BaseAddress;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeMappingAddress (
    _In_ PVOID BaseAddress,
    _In_ ULONG Tag)
{
    __debugbreak();
    //DeleteReservedMapping(BaseAddress);
    ReleaseKernelVaSpace(BaseAddress);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Out_writes_bytes_opt_ (NumberOfBytes)
PVOID
NTAPI
MmMapIoSpace (
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    PFN_NUMBER BasePageFrameNumber;
    ULONG_PTR NumberOfPages;
    PVOID BaseAddress;
    ULONG Protect;

    /* Get the number of pages for the mapping */
    NumberOfBytes += PhysicalAddress.LowPart & (PAGE_SIZE - 1);
    NumberOfPages = BYTES_TO_PAGES(NumberOfBytes);

    /* Reserve virtual memory range */
    BaseAddress = ReserveSystemMappingRange(NumberOfPages);
    if (BaseAddress == NULL)
    {
        return NULL;
    }

    /* Convert protection */
    Protect = ConvertProtectAndCaching(PAGE_READWRITE, CachingType);

    /* Map the physical pages */
    BasePageFrameNumber = (PFN_NUMBER)(PhysicalAddress.QuadPart >> PAGE_SHIFT);
    MapPhysicalMemory(AddressToVpn(BaseAddress),
                      NumberOfPages,
                      Protect,
                      BasePageFrameNumber);

    /* Return the pointer to the real start address */
    return AddToPointer(BaseAddress, PhysicalAddress.LowPart & (PAGE_SIZE - 1));
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapIoSpace (
    _In_reads_bytes_ (NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes)
{
    ULONG_PTR NumberOfPages;

    /* Get the number of pages for the mapping */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseAddress, NumberOfBytes);

    /* Unmap the memory, ignore the PFNs */
    UnmapPages(AddressToVpn(BaseAddress), NumberOfPages, FALSE);

    /* Release the virtual memory */
    ReleaseKernelVaSpace(ALIGN_DOWN_POINTER_BY(BaseAddress, PAGE_SIZE));
}

_Must_inspect_result_
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL))
PVOID
NTAPI
MmMapLockedPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
        KPROCESSOR_MODE AccessMode)
{
    return MmMapLockedPagesSpecifyCache(MemoryDescriptorList,
                                        AccessMode,
                                        MmCached,
                                        NULL,
                                        FALSE,
                                        NormalPagePriority);
}

_Post_writable_byte_size_(Mdl->ByteCount)
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL) _Post_notnull_)
_At_(Mdl->MappedSystemVa, _Post_writable_byte_size_(Mdl->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesSpecifyCache (
    _Inout_ PMDLX Mdl,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
        KPROCESSOR_MODE AccessMode,
    _In_ __drv_strictTypeMatch(__drv_typeCond) MEMORY_CACHING_TYPE CacheType,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG BugCheckOnFailure,
    _In_ MM_PAGE_PRIORITY Priority)
{
    ULONG_PTR NumberOfPages;
    ULONG Protect;

    /* Make sure the MDL is not yet mapped */
    NT_ASSERT(!(Mdl->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA));

    /* Calculate the number of pages */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(Mdl->StartVa, Mdl->ByteCount);

    /* Check if we have enough free system address space */
    if (!CheckAvailableSystemVa(NumberOfPages, Priority))
    {
        /* Not enough resources */
        return NULL;
    }

    /* Convert the protection */
    Protect = ConvertProtectAndCaching(PAGE_EXECUTE_READWRITE, CacheType);

    /* Check for user mode mapping */
    if (AccessMode != KernelMode)
    {
        Protect |= MM_USER; /// | MM_LOCKED / MM_SYSTEM
        UNIMPLEMENTED_DBGBREAK;
        return NULL;
    }

    /* Reserve system PTEs for the mapping */
    BaseAddress = ReserveSystemMappingRange(NumberOfPages);
    if (BaseAddress == NULL)
    {
        ERR("Failed to reserve system PTEs\n");
        if (BugCheckOnFailure)
        {
            KeBugCheckEx(0, 0, 0, 0, 0);
        }

        return NULL;
    }

    /* Map the PFNs from the MDL */
    MapPfnArray(AddressToVpn(BaseAddress),
                NumberOfPages,
                Protect | MM_GLOBAL,
                MmGetMdlPfnArray(Mdl));

    /* Update the MDL */
    Mdl->MappedSystemVa = AddToPointer(BaseAddress, Mdl->ByteOffset);
    Mdl->MdlFlags |= MDL_MAPPED_TO_SYSTEM_VA;
    if (Mdl->MdlFlags & MDL_PARTIAL)
        Mdl->MdlFlags |= MDL_PARTIAL_HAS_BEEN_MAPPED;

    return Mdl->MappedSystemVa;
}

_Post_writable_byte_size_(MemoryDescriptorList->ByteCount)
_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(MemoryDescriptorList->MappedSystemVa + MemoryDescriptorList->ByteOffset,
  _Post_writable_byte_size_(MemoryDescriptorList->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesWithReservedMapping (
    _In_ PVOID MappingAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDLX MemoryDescriptorList,
    _In_ __drv_strictTypeMatch(__drv_typeCond)
        MEMORY_CACHING_TYPE CacheType)
{
    // Find the VAD
    // Commit pages
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapReservedMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDLX Mdl)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapLockedPages (
    _In_ PVOID BaseAddress,
    _Inout_ PMDL Mdl)
{
    ULONG_PTR NumberOfPages;

    NumberOfPages = BYTES_TO_PAGES(Mdl->ByteCount);
    UnmapPages(AddressToVpn(BaseAddress), NumberOfPages, FALSE);

    Mdl->MdlFlags &= ~(MDL_PARTIAL_HAS_BEEN_MAPPED | MDL_MAPPED_TO_SYSTEM_VA);
}


VOID
NTAPI
MmMapMemoryDumpMdl (
    IN PMDL Mdl)
{
    UNIMPLEMENTED;
}

PHYSICAL_ADDRESS
NTAPI
MmGetPhysicalAddress(
    _In_ PVOID BaseAddress)
{
    PHYSICAL_ADDRESS PhysicalAddress = {{0}};

    return PhysicalAddress;
}

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmSetAddressRangeModified (
    _In_reads_bytes_ (Length) PVOID Address,
    _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
MmIsAddressValid (
    _In_ PVOID VirtualAddress)
{
    /* Use SEH */
    _SEH2_TRY
    {
        /* Read a char value from the address */
        (void)*(volatile char*)VirtualAddress;
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
    _SEH2_END;

    return TRUE;
}

BOOLEAN
NTAPI
MmIsNonPagedSystemAddressValid (
  _In_ PVOID VirtualAddress)
{
    UNIMPLEMENTED;
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmMapUserAddressesToPage (
  _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes,
  _In_ PVOID PageAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
}; // namespace Mm
