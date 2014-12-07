
#include "Mmp.hpp"

extern "C" {

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmIsVerifierEnabled (
    _Out_ PULONG VerifierFlags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

LOGICAL
NTAPI
MmIsDriverVerifying (
    _In_ struct _DRIVER_OBJECT *DriverObject)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_ (APC_LEVEL)
LOGICAL
NTAPI
MmIsDriverVerifyingByAddress (
    _In_ PVOID AddressWithinSection)
{
    __debugbreak();
    return FALSE;
}

LOGICAL
NTAPI
MmIsDriverSuspectForVerifier (
    _In_ struct _DRIVER_OBJECT *DriverObject)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmAddVerifierThunks (
    _In_reads_bytes_ (ThunkBufferSize) PVOID ThunkBuffer,
    _In_ ULONG ThunkBufferSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmAddVerifierSpecialThunks(
    _In_ ULONG_PTR EntryRoutine,
    _In_reads_bytes_(ThunkBufferSize) PVOID ThunkBuffer,
    _In_ ULONG ThunkBufferSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"
