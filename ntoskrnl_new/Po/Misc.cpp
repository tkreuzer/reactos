
#include "Po.hpp"

extern "C" {

//@ stub PoGetProcessorIdleAccounting

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
POWER_STATE
NTAPI
PoSetPowerState (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ POWER_STATE_TYPE Type,
    _In_ POWER_STATE State)
{
    POWER_STATE powerState = {PowerSystemUnspecified};
    __debugbreak();
    return powerState;
}

// ntosp.h
BOOLEAN
NTAPI
PoCpuIdledSinceLastCallImprecise(
    _In_ ULONG ProcessorNumber,
    _Inout_ PULONGLONG IdleTimeReturned)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PoDisableSleepStates (
    _In_ PO_SLEEP_DISABLE_REASON Reason,
    _In_ ULONG SleepMask,
    _Outptr_ PVOID *Token)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
BOOLEAN
NTAPI
PoEnergyEstimationEnabled (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PoLatencySensitivityHint (
    _In_ PO_LATENCY_HINT_TYPE HintType)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
PoQueryWatchdogTime (
    _In_ PDEVICE_OBJECT Pdo,
    _Out_ PULONG SecondsRemaining)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PoReenableSleepStates (
    _In_ PVOID Token)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
PoSetHiberRange (
    _In_opt_ PVOID MemoryMap,
    _In_ ULONG Flags,
    _In_ PVOID Address,
    _In_ ULONG_PTR Length,
    _In_ ULONG Tag)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoSetUserPresent (
    _In_ POWER_MONITOR_REQUEST_REASON RequestReason)
{
    __debugbreak();
}


} // extern "C"
