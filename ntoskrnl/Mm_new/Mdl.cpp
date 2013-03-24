

#include "Mdl.hpp"

extern "C" {

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

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreePagesFromMdl (
  _Inout_ PMDLX MemoryDescriptorList)
{
    UNIMPLEMENTED;
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

}; // extern "C"
