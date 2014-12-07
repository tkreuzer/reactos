
#include "PoFx.hpp"

extern "C" {

//@ stub PoFxRegisterCoreDevice
//@ stub PoFxRegisterPlugin
//@ stub PoFxRegisterPluginEx

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PoFxRegisterPrimaryDevice (
    _In_ PDEVICE_OBJECT Pdo,
    _In_ PPO_FX_PRIMARY_DEVICE Device,
    _Out_ POHANDLE *Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PoFxEnableDStateReporting (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PoFxRegisterDevice (
    _In_ PDEVICE_OBJECT Pdo,
    _In_ PPO_FX_DEVICE Device,
    _Out_ POHANDLE *Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PoFxStartDevicePowerManagement (
    _In_ POHANDLE Handle)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PoFxUnregisterDevice (
    _In_ POHANDLE Handle)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PoFxRegisterCrashdumpDevice (
    _In_ POHANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
PoFxPowerOnCrashdumpDevice(
    _In_ POHANDLE Handle,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxActivateComponent (
    _In_ POHANDLE Handle,
    _In_ ULONG Component,
    _In_ ULONG Flags)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxCompleteDevicePowerNotRequired (
    _In_ POHANDLE Handle)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxCompleteIdleCondition (
    _In_ POHANDLE Handle,
    _In_ ULONG Component)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxCompleteIdleState (
    _In_ POHANDLE Handle,
    _In_ ULONG Component)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxIdleComponent (
    _In_ POHANDLE Handle,
    _In_ ULONG Component,
    _In_ ULONG Flags)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxSetComponentLatency (
    _In_ POHANDLE Handle,
    _In_ ULONG Component,
    _In_ ULONGLONG Latency)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxSetComponentResidency (
    _In_ POHANDLE Handle,
    _In_ ULONG Component,
    _In_ ULONGLONG Residency)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxSetComponentWake (
    _In_ POHANDLE Handle,
    _In_ ULONG Component,
    _In_ BOOLEAN WakeHint)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxSetDeviceIdleTimeout (
    _In_ POHANDLE Handle,
    _In_ ULONGLONG IdleTimeout)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxReportDevicePoweredOn (
    _In_ POHANDLE Handle)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
PoFxPowerControl (
    _In_ POHANDLE Handle,
    _In_ LPCGUID PowerControlCode,
    _In_opt_ PVOID InBuffer,
    _In_ SIZE_T InBufferSize,
    _Out_opt_ PVOID OutBuffer,
    _In_ SIZE_T OutBufferSize,
    _Out_opt_ PSIZE_T BytesReturned)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxNotifySurprisePowerOn(
    _In_ PDEVICE_OBJECT Pdo)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PoFxRegisterComponentPerfStates (
    _In_ POHANDLE Handle,
    _In_ ULONG Component,
    _In_ ULONGLONG Flags,
    _In_ PPO_FX_COMPONENT_PERF_STATE_CALLBACK ComponentPerfStateCallback,
    _In_ PPO_FX_COMPONENT_PERF_INFO InputStateInfo,
    _Out_ PPO_FX_COMPONENT_PERF_INFO* OutputStateInfo)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxIssueComponentPerfStateChange (
    _In_ POHANDLE Handle,
    _In_ ULONG Flags,
    _In_ ULONG Component,
    _In_ PPO_FX_PERF_STATE_CHANGE PerfChange,
    _In_ PVOID Context)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoFxIssueComponentPerfStateChangeMultiple (
    _In_ POHANDLE Handle,
    _In_ ULONG Flags,
    _In_ ULONG Component,
    _In_ ULONG PerfChangesCount,
    _In_ PO_FX_PERF_STATE_CHANGE PerfChanges[],
    _In_ PVOID Context)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
PoFxQueryCurrentComponentPerfState (
    _In_ POHANDLE Handle,
    _In_ ULONG Flags,
    _In_ ULONG Component,
    _In_ ULONG SetIndex,
    _Out_ PULONGLONG CurrentPerf)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
PoFxProcessorNotification (
    _In_ POHANDLE Handle,
    _In_ ULONG Notification,
    _Inout_opt_ PVOID Data)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
