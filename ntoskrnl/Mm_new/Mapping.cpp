

#include "ntosbase.h"

extern "C" {

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

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeMappingAddress (
  _In_ PVOID BaseAddress,
  _In_ ULONG PoolTag)
{
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
    UNIMPLEMENTED;
    return NULL;
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

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmUnmapVideoDisplay (
  _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes)
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
