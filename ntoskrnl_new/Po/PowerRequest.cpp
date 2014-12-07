
#include "Po.hpp"

extern "C" {

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PoCreatePowerRequest (
    _Outptr_ PVOID *PowerRequest,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ PCOUNTED_REASON_CONTEXT Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PoDeletePowerRequest (
    _Inout_ PVOID PowerRequest)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
PoClearPowerRequest (
    _Inout_ PVOID PowerRequest,
    _In_ POWER_REQUEST_TYPE Type)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
PoSetPowerRequest (
    _Inout_ PVOID PowerRequest,
    _In_ POWER_REQUEST_TYPE Type)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
