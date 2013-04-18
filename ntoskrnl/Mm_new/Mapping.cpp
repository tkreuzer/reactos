

#include "ntosbase.h"

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
NTAPI
MiMapPhysicalMemory (
    _In_ PFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ ULONG Protect,
    _In_ MEMORY_CACHING_TYPE CacheType)
{
#if 0
    PFN_NUMBER PageFrameNumber;
    PVOID BaseAddress;

    BaseAddress = MmAllocateMappingAddress(NumberOfPages * PAGE_SIZE, TAG_MM);
    if (BaseAddress == NULL)
    {
        return NULL;
    }

    PtePointer = MiAddressToPte(BaseAddress);
    PageFrameNumber = BasePageFrameNumber;

    Pte.InitValidKernelPte(Protect, CacheType);
    while (NumberOfPages--)
    {
        MiWriteValidPte(PtePointer, &Pte);

        ++PtePointer;
        ++PageFrameNumber;
    }
#endif
    UNIMPLEMENTED;
    return NULL;
}

extern "C" {

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_When_ (return != NULL, _Out_writes_bytes_opt_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateMappingAddress (
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag)
{
    // allocate a VAD
    // reserve PTEs (allocate page tables, map MM_NOACCESS software PTEs)
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeMappingAddress (
    _In_ PVOID BaseAddress,
    _In_ ULONG Tag)
{
    // find the vad by it's address
    // make sure all pages are freed (assert or bugcheck)
    // remove the vad from the VadTable
    // free the vad
    UNIMPLEMENTED;
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
    PFN_NUMBER BasePageFrameNumber;

    BasePageFrameNumber = PhysicalAddress.QuadPart >> PAGE_SHIFT;
    return MiMapPhysicalMemory(BasePageFrameNumber,
                               (PFN_COUNT)BYTES_TO_PAGES(NumberOfBytes),
                               PAGE_READWRITE,
                               CacheType);
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
#if 0
    if (AccessMode == KernelMode)
    {
        MappingAddress = MmAllocateMappingAddress

        Address = MmMapLockedPagesWithReservedMapping(MappingAddress,
                                                      TAG_MM,
                                                      MemoryDescriptorList,
                                                      CacheType);
    }
#endif
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
    _Inout_ PMDLX MemoryDescriptorList)
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


VOID
NTAPI
MmMapMemoryDumpMdl (
    IN PMDL Mdl)
{
    UNIMPLEMENTED;
}

}; // extern "C"
