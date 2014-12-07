
#include "Po.hpp"

extern "C" {

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PULONG
NTAPI
PoRegisterDeviceForIdleDetection (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG ConservationIdleTime,
    _In_ ULONG PerformanceIdleTime,
    _In_ DEVICE_POWER_STATE State)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
#define PoSetDeviceBusy(IdlePointer) \
    *IdlePointer = 0

// ntosp.h
VOID
NTAPI
PoSetDeviceBusyEx (
    _Inout_ PULONG IdlePointer)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
PoStartDeviceBusy (
    _Inout_ PULONG IdlePointer)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
PoEndDeviceBusy (
    _Inout_ PULONG IdlePointer)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoStartNextPowerIrp(
    _Inout_ PIRP Irp)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
PoRequestPowerIrp (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ UCHAR MinorFunction,
    _In_ POWER_STATE PowerState,
    _In_opt_ PREQUEST_POWER_COMPLETE CompletionFunction,
    _In_opt_ __drv_aliasesMem PVOID Context,
    _Outptr_opt_ PIRP *Irp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
PoCallDriver (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ __drv_aliasesMem PIRP Irp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
