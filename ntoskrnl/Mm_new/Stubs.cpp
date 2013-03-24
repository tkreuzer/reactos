
#include "ntosbase.h"

extern "C" {

#define UNIMPLEMENTED __debugbreak()

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmAddVerifierThunks (
  _In_reads_bytes_ (ThunkBufferSize) PVOID ThunkBuffer,
  _In_ ULONG ThunkBufferSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmAdvanceMdl (
  _Inout_ PMDLX Mdl,
  _In_ ULONG NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateContiguousMemory (
  _In_ SIZE_T NumberOfBytes,
  _In_ PHYSICAL_ADDRESS HighestAcceptableAddress)
{
    UNIMPLEMENTED;
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateContiguousMemorySpecifyCache (
  _In_ SIZE_T NumberOfBytes,
  _In_ PHYSICAL_ADDRESS LowestAcceptableAddress,
  _In_ PHYSICAL_ADDRESS HighestAcceptableAddress,
  _In_opt_ PHYSICAL_ADDRESS BoundaryAddressMultiple,
  _In_ MEMORY_CACHING_TYPE CacheType)
{
    UNIMPLEMENTED;
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_When_ (return != NULL, _Out_writes_bytes_opt_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateMappingAddress (
  _In_ SIZE_T NumberOfBytes,
  _In_ ULONG PoolTag)
{
    UNIMPLEMENTED;
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PMDL
NTAPI
MmAllocatePagesForMdl (
  _In_ PHYSICAL_ADDRESS LowAddress,
  _In_ PHYSICAL_ADDRESS HighAddress,
  _In_ PHYSICAL_ADDRESS SkipBytes,
  _In_ SIZE_T TotalBytes)
{
    UNIMPLEMENTED;
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_ (DISPATCH_LEVEL)
PMDL
NTAPI
MmAllocatePagesForMdlEx (
  _In_ PHYSICAL_ADDRESS LowAddress,
  _In_ PHYSICAL_ADDRESS HighAddress,
  _In_ PHYSICAL_ADDRESS SkipBytes,
  _In_ SIZE_T TotalBytes,
  _In_ MEMORY_CACHING_TYPE CacheType,
  _In_ ULONG Flags)
{
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmBuildMdlForNonPagedPool (
  _Inout_ PMDLX MemoryDescriptorList)
{
    UNIMPLEMENTED;
}


PMDL
NTAPI
MmCreateMdl(
  _Out_writes_bytes_opt_ (sizeof (MDL) + (sizeof (PFN_NUMBER) * ADDRESS_AND_SIZE_TO_SPAN_PAGES (Base, Length)))
    PMDL MemoryDescriptorList,
  _In_reads_bytes_opt_ (Length) PVOID Base,
  _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreeContiguousMemory (
  _In_ PVOID BaseAddress)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_ (DISPATCH_LEVEL)
VOID
NTAPI
MmFreeContiguousMemorySpecifyCache (
  _In_reads_bytes_ (NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes,
  _In_ MEMORY_CACHING_TYPE CacheType)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeMappingAddress (
  _In_ PVOID BaseAddress,
  _In_ ULONG PoolTag)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreePagesFromMdl (
  _Inout_ PMDLX MemoryDescriptorList)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
PVOID
NTAPI
MmGetSystemRoutineAddress (
  _In_ PUNICODE_STRING SystemRoutineName)
{
    UNIMPLEMENTED;
    return NULL;
}

LOGICAL
NTAPI
MmIsDriverVerifying (
  _In_ struct _DRIVER_OBJECT *DriverObject)
{
    UNIMPLEMENTED;
    return 0;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmIsVerifierEnabled (
  _Out_ PULONG VerifierFlags)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Out_writes_bytes_opt_ (NumberOfBytes)
PVOID
NTAPI
MmMapIoSpace (
  _In_ PHYSICAL_ADDRESS PhysicalAddress,
  _In_ SIZE_T NumberOfBytes,
  _In_ MEMORY_CACHING_TYPE CacheType)
{
    UNIMPLEMENTED;
    return NULL;
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
    UNIMPLEMENTED;
    return NULL;
}

_Post_writable_byte_size_(MemoryDescriptorList->ByteCount)
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL) _Post_notnull_)
_At_(MemoryDescriptorList->MappedSystemVa, _Post_writable_byte_size_(MemoryDescriptorList->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesSpecifyCache (
  _Inout_ PMDLX MemoryDescriptorList,
  _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
    KPROCESSOR_MODE AccessMode,
  _In_ __drv_strictTypeMatch(__drv_typeCond) MEMORY_CACHING_TYPE CacheType,
  _In_opt_ PVOID BaseAddress,
  _In_ ULONG BugCheckOnFailure,
  _In_ MM_PAGE_PRIORITY Priority)
{
    UNIMPLEMENTED;
    return NULL;
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
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
MmPageEntireDriver (
  _In_ PVOID AddressWithinSection)
{
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(MemoryDescriptorList->StartVa + MemoryDescriptorList->ByteOffset,
  _Field_size_bytes_opt_(MemoryDescriptorList->ByteCount))
VOID
NTAPI
MmProbeAndLockPages (
  _Inout_ PMDLX MemoryDescriptorList,
  _In_ KPROCESSOR_MODE AccessMode,
  _In_ LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
VOID
NTAPI
MmProbeAndLockProcessPages (
  _Inout_ PMDL MemoryDescriptorList,
  _In_ PEPROCESS Process,
  _In_ KPROCESSOR_MODE AccessMode,
  _In_ LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmProtectMdlSystemAddress (
  _In_ PMDLX MemoryDescriptorList,
  _In_ ULONG NewProtect)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

MM_SYSTEMSIZE MmSystemSize;

MM_SYSTEMSIZE
NTAPI
MmQuerySystemSize (
    VOID)
{
    UNIMPLEMENTED;
    return MmSystemSize;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmResetDriverPaging (
  _In_ PVOID AddressWithinSection)
{
    UNIMPLEMENTED;
}

SIZE_T
NTAPI
MmSizeOfMdl (
  _In_reads_bytes_opt_ (Length) PVOID Base,
  _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnlockPages (
  _Inout_ PMDLX MemoryDescriptorList)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapIoSpace (
  _In_reads_bytes_ (NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapLockedPages (
  _In_ PVOID BaseAddress,
  _Inout_ PMDL MemoryDescriptorList)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapReservedMapping (
  _In_ PVOID BaseAddress,
  _In_ ULONG PoolTag,
  _Inout_ PMDLX MemoryDescriptorList)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmAddPhysicalMemory (
  _In_ PPHYSICAL_ADDRESS StartAddress,
  _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Out_writes_bytes_opt_(NumberOfBytes)
PVOID
NTAPI
MmAllocateNonCachedMemory (
  _In_ SIZE_T NumberOfBytes)
{
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmCanFileBeTruncated (
  _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
  _In_opt_ PLARGE_INTEGER NewFileSize)
{
    UNIMPLEMENTED;
    return FALSE;
}

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmFlushImageSection (
  _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
  _In_ MMFLUSH_TYPE FlushType)
{
    UNIMPLEMENTED;
    return FALSE;
}

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmForceSectionClosed (
  _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
  _In_ BOOLEAN DelayClose)
{
    UNIMPLEMENTED;
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeNonCachedMemory (
  _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
PPHYSICAL_MEMORY_RANGE
NTAPI
MmGetPhysicalMemoryRanges (
    VOID)
{
    UNIMPLEMENTED;
    return NULL;
}

PVOID
NTAPI
MmGetVirtualForPhysical (
  _In_ PHYSICAL_ADDRESS PhysicalAddress)
{
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
MmIsAddressValid (
  _In_ PVOID VirtualAddress)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmIsNonPagedSystemAddressValid (
  _In_ PVOID VirtualAddress)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmIsRecursiveIoFault (
    VOID)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmIsThisAnNtAsSystem (
    VOID)
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

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Out_writes_bytes_opt_(NumberOfBytes)
PVOID
NTAPI
MmMapVideoDisplay (
  _In_ PHYSICAL_ADDRESS PhysicalAddress,
  _In_ SIZE_T NumberOfBytes,
  _In_ MEMORY_CACHING_TYPE CacheType)
{
    UNIMPLEMENTED;
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSessionSpace (
  _In_ PVOID Section,
  _Outptr_result_bytebuffer_(*ViewSize) PVOID *MappedBase,
  _Inout_ PSIZE_T ViewSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSystemSpace (
  _In_ PVOID Section,
  _Outptr_result_bytebuffer_(*ViewSize) PVOID *MappedBase,
  _Inout_ PSIZE_T ViewSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmPrefetchPages (
  _In_ ULONG NumberOfLists,
  _In_reads_ (NumberOfLists) PREAD_LIST *ReadLists)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmRemovePhysicalMemory (
  _In_ PPHYSICAL_ADDRESS StartAddress,
  _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
HANDLE
NTAPI
MmSecureVirtualMemory (
  __in_data_source(USER_MODE) _In_reads_bytes_ (Size) PVOID Address,
  _In_ __in_data_source(USER_MODE) SIZE_T Size,
  _In_ ULONG ProbeMode)
{
    UNIMPLEMENTED;
    return 0;
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

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmUnmapVideoDisplay (
  _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSessionSpace (
  _In_ PVOID MappedBase)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSystemSpace (
  _In_ PVOID MappedBase)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmUnsecureVirtualMemory (
  _In_ HANDLE SecureHandle)
{
    UNIMPLEMENTED;
}

_Must_inspect_result_
_At_(*BaseAddress, __drv_allocatesMem(Mem))
__kernel_entry
NTSTATUS
NTAPI
NtAllocateVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ _Outptr_result_buffer_(*RegionSize) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtFreeVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmMapViewOfSection (
    _In_ PVOID SectionObject,
    _In_ PEPROCESS Process,
    _Inout_ PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmUnmapViewOfSection (
    _In_ struct _EPROCESS* Process,
    _In_ PVOID BaseAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmAdjustWorkingSetSize (
    _In_ SIZE_T WorkingSetMinimumInBytes,
    _In_ SIZE_T WorkingSetMaximumInBytes,
    _In_ ULONG SystemCache,
    _In_ BOOLEAN IncreaseOkay)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
MmDisableModifiedWriteOfSection (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer)
{
    UNIMPLEMENTED;
    return FALSE;
}

NTSTATUS
NTAPI
MmGrowKernelStackEx (
    IN PVOID StackPointer,
    IN ULONG GrowSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmGrowKernelStack (
    IN PVOID StackPointer)
{
    return MmGrowKernelStackEx(StackPointer, KERNEL_LARGE_STACK_COMMIT);
}

PVOID
NTAPI
MmLockPageableDataSection (
    IN PVOID AddressWithinSection)
{
    //
    // We should just find the section and call MmLockPageableSectionByHandle
    //
    static BOOLEAN Warn; if (!Warn++) UNIMPLEMENTED;
    return AddressWithinSection;
}

VOID
NTAPI
MmLockPageableSectionByHandle (
    IN PVOID ImageSectionHandle)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
MmMapMemoryDumpMdl (
    IN PMDL Mdl)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmMarkPhysicalMemoryAsBad (
    IN PPHYSICAL_ADDRESS StartAddress,
    IN OUT PLARGE_INTEGER NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmMarkPhysicalMemoryAsGood (
    IN PPHYSICAL_ADDRESS StartAddress,
    IN OUT PLARGE_INTEGER NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmProbeAndLockSelectedPages (
    IN OUT PMDL MemoryDescriptorList,
    IN LARGE_INTEGER PageList[],
    IN KPROCESSOR_MODE AccessMode,
    IN LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmSetBankedSection (
    IN HANDLE ProcessHandle,
    IN PVOID VirtualAddress,
    IN ULONG BankLength,
    IN BOOLEAN ReadWriteBank,
    IN PVOID BankRoutine,
    IN PVOID Context)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


ULONG
NTAPI
MmTrimAllSystemPageableMemory (
    IN ULONG PurgeTransitionList)
{
    UNIMPLEMENTED;
    return 0;
}

VOID
NTAPI
MmUnlockPageableImageSection (
    IN PVOID ImageSectionHandle)
{
    UNIMPLEMENTED;
}

PHYSICAL_ADDRESS
NTAPI
MmGetPhysicalAddress(
    _In_ PVOID BaseAddress)
{
    PHYSICAL_ADDRESS PhysicalAddress = {0};
    UNIMPLEMENTED;
    return PhysicalAddress;
}

NTSTATUS
NTAPI
NtAllocateUserPhysicalPages (
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtAreMappedFilesTheSame (
    _In_ PVOID File1MappedAsAnImage,
    _In_ PVOID File2MappedAsFile)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtCreatePagingFile (
    _In_ PUNICODE_STRING FileName,
    _In_ PLARGE_INTEGER InitialSize,
    _In_ PLARGE_INTEGER MaxiumSize,
    _In_ ULONG Reserved)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtExtendSection (
    _In_ HANDLE SectionHandle,
    _In_ PLARGE_INTEGER NewMaximumSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtFlushVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtFreeUserPhysicalPages (
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtGetWriteWatch (
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _In_ PVOID *UserAddressArray,
    _Out_ PULONG_PTR EntriesInUserAddressArray,
    _Out_ PULONG Granularity)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtLockVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T NumberOfBytesToLock,
    _In_ ULONG MapType)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtMapUserPhysicalPages (
    _In_ PVOID VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtMapUserPhysicalPagesScatter (
    _In_ PVOID *VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtOpenSection (
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtProtectVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID *BaseAddress,
    _In_ SIZE_T *NumberOfBytesToProtect,
    _In_ ULONG NewAccessProtection,
    _Out_ PULONG OldAccessProtection)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtQuerySection (
    _In_ HANDLE SectionHandle,
    _In_ enum _SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_ PVOID SectionInformation,
    _In_ SIZE_T Length,
    _Out_ PSIZE_T ResultLength)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtQueryVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID Address,
    _In_ enum _MEMORY_INFORMATION_CLASS VirtualMemoryInformationClass,
    _Out_ PVOID VirtualMemoryInformation,
    _In_ SIZE_T Length,
    _Out_opt_ PSIZE_T ResultLength)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtReadVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _Out_ PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToRead,
    _Out_opt_ PSIZE_T NumberOfBytesRead)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtResetWriteWatch (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtUnlockVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T NumberOfBytesToUnlock,
    _In_ ULONG MapType)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtUnmapViewOfSection (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtWriteVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID  BaseAddress,
    _In_ PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToWrite,
    _Out_opt_ PSIZE_T NumberOfBytesWritten)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////

PVOID
NTAPI
MmCreateKernelStack (
    BOOLEAN GuiStack,
    UCHAR Node)
{
    UNIMPLEMENTED;
    return NULL;
}

VOID
NTAPI
MmDeleteKernelStack (
    PVOID Stack,
    BOOLEAN GuiStack)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmGetFileNameForSection (
    IN PVOID Section,
    OUT POBJECT_NAME_INFORMATION *ModuleName)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmGetFileNameForAddress (
    IN PVOID Address,
    OUT PUNICODE_STRING ModuleName)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmZeroPageThread(
     VOID)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmLoadSystemImage (
    IN PUNICODE_STRING FileName,
    IN PUNICODE_STRING NamePrefix OPTIONAL,
    IN PUNICODE_STRING LoadedName OPTIONAL,
    IN ULONG Flags,
    OUT PVOID *ModuleObject,
    OUT PVOID *ImageBaseAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmUnloadSystemImage (
    IN PVOID ImageHandle)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCreatePeb (
    _In_ PEPROCESS Process,
    _In_ struct _INITIAL_PEB* InitialPeb,
    _Out_ struct _PEB** BasePeb)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCreateTeb (
    _In_ PEPROCESS Process,
    _In_ PCLIENT_ID ClientId,
    _In_ struct _INITIAL_TEB* InitialTeb,
    _Out_ struct _TEB** BaseTeb)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmDeleteTeb (
    struct _EPROCESS *Process,
    struct _TEB* Teb)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmSessionCreate (
    OUT PULONG SessionId)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmSessionDelete (
    IN ULONG SessionId)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

ULONG
NTAPI
MmGetSessionId (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
    return 0;
}

ULONG
NTAPI
MmGetSessionLocaleId (
    VOID)
{
    UNIMPLEMENTED;
    return 0;
}

BOOLEAN
NTAPI
MmIsSessionAddress (
    IN PVOID Address)
{
    UNIMPLEMENTED;
    return 0;
}

BOOLEAN
NTAPI
MmIsFileObjectAPagingFile (
    PFILE_OBJECT FileObject)
{
    UNIMPLEMENTED;
    return 0;
}

NTSTATUS
NTAPI
MmCallDllInitialize (
    IN struct _LDR_DATA_TABLE_ENTRY* LdrEntry,
    IN PLIST_ENTRY ListHead)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmFreeDriverInitialization (
    IN struct _LDR_DATA_TABLE_ENTRY* LdrEntry)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MiResolveImageReferences (
    IN PVOID ImageBase,
    IN PUNICODE_STRING ImageFileDirectory,
    IN PUNICODE_STRING NamePrefix OPTIONAL,
    OUT PCHAR *MissingApi,
    OUT PWCHAR *MissingDriver,
    OUT struct _LOAD_IMPORTS** LoadImports)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
MmCreateProcessAddressSpace (
    IN ULONG MinWs,
    IN PEPROCESS Dest,
    IN PULONG_PTR DirectoryTableBase)
{
    UNIMPLEMENTED;
    return 0;
}

NTSTATUS
NTAPI
MmInitializeProcessAddressSpace (
    IN PEPROCESS Process,
    IN PEPROCESS Clone OPTIONAL,
    IN PVOID Section OPTIONAL,
    IN OUT PULONG Flags,
    IN POBJECT_NAME_INFORMATION *AuditName OPTIONAL)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmCleanProcessAddressSpace (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmDeleteProcessAddressSpace (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmInitializeHandBuiltProcess (
    IN PEPROCESS Process,
    IN PULONG_PTR DirectoryTableBase)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmInitializeHandBuiltProcess2 (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmSetMemoryPriorityProcess (
    IN PEPROCESS Process,
    IN UCHAR MemoryPriority)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCheckSystemImage (
    IN HANDLE ImageHandle,
    IN BOOLEAN PurgeSection)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmSetExecuteOptions (
    IN ULONG ExecuteOptions)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmGetExecuteOptions (
    IN PULONG ExecuteOptions)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmDbgCopyMemory (
    IN ULONG64 Address,
    IN PVOID Buffer,
    IN ULONG Size,
    IN ULONG Flags)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmDumpArmPfnDatabase(
    IN BOOLEAN StatusOnly)
{
    UNIMPLEMENTED;
}

#if 0
sysinfo.c.obj : error LNK2001: unresolved external symbol MiMemoryConsumers
kdapi.c.obj : error LNK2019: unresolved external symbol MmDumpArmPfnDatabase referenced in function KdSystemDebugControl


#endif

}; // extern "C"
