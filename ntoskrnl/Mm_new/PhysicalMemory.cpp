
#include "ntosbase.h"

extern "C" {

_IRQL_requires_max_ (PASSIVE_LEVEL)
PPHYSICAL_MEMORY_RANGE
NTAPI
MmGetPhysicalMemoryRanges (
    VOID)
{
    UNIMPLEMENTED;
    return NULL;
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
_Out_writes_bytes_opt_(NumberOfBytes)
PVOID
NTAPI
MmAllocateNonCachedMemory (
  _In_ SIZE_T NumberOfBytes)
{
    UNIMPLEMENTED;
    return NULL;
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

}; // extern "C"
