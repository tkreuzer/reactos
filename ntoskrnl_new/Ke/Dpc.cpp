
#include "Dpc.hpp"

extern "C" {

//@ stub KiEntropyQueueDpc
//@ stdcall -stub -arch=i386 KiDispatchInterrupt()
#if 0 // FIXME where to put? From "NUKE"
VOID KiDpcInterruptHandler(VOID)
{
}

VOID KiRetireDpcList(VOID)
{
}
#endif

// wdm.h / ntosp.h
VOID
NTAPI
KeInitializeDpc (
    _Out_ __drv_aliasesMem PRKDPC Dpc,
    _In_ PKDEFERRED_ROUTINE DeferredRoutine,
    _In_opt_ __drv_aliasesMem PVOID DeferredContext)
{
    __debugbreak();
}

// wdm.h / ntosp.h
VOID
NTAPI
KeInitializeThreadedDpc (
    _Out_ PRKDPC Dpc,
    _In_ PKDEFERRED_ROUTINE DeferredRoutine,
    _In_opt_ PVOID DeferredContext)
{
    __debugbreak();
}

// wdm.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeFlushQueuedDpcs (
    VOID)
{
    __debugbreak();
}

// wdm.h / ntosp.h
BOOLEAN
NTAPI
KeInsertQueueDpc (
    _Inout_ PRKDPC Dpc,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ __drv_aliasesMem PVOID SystemArgument2)
{
    __debugbreak();
    return FALSE;
}


// wdm.h / ntosp.h
_IRQL_requires_max_(HIGH_LEVEL)
BOOLEAN
NTAPI
KeRemoveQueueDpc (
    _Inout_ PRKDPC Dpc)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(HIGH_LEVEL)
BOOLEAN
NTAPI
KeRemoveQueueDpcEx (
    _Inout_ PRKDPC Dpc,
    _In_ BOOLEAN WaitIfActive)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_same_
VOID
NTAPI
KeGenericCallDpc (
    _In_ PKDEFERRED_ROUTINE Routine,
    _In_opt_ PVOID Context)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_same_
LOGICAL
NTAPI
KeIsExecutingDpc (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
KeQueryDpcWatchdogInformation (
    _Out_ PKDPC_WATCHDOG_INFORMATION WatchdogInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h / ntosp.h
VOID
NTAPI
KeSetImportanceDpc (
    _Inout_ PRKDPC Dpc,
    _In_ KDPC_IMPORTANCE Importance)
{
    __debugbreak();
}

// wdm.h / ntosp.h
VOID
NTAPI
KeSetTargetProcessorDpc (
    _Inout_ PRKDPC Dpc,
    _In_ CCHAR Number)
{
    __debugbreak();
}

// wdm.h / ntosp.h
_Must_inspect_result_
NTSTATUS
NTAPI
KeSetTargetProcessorDpcEx (
    _Inout_ PKDPC Dpc,
    _In_ PPROCESSOR_NUMBER ProcNumber)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
VOID
NTAPI
KeSignalCallDpcDone (
    _In_ PVOID SystemArgument1)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
LOGICAL
NTAPI
KeSignalCallDpcSynchronize (
    _In_ PVOID SystemArgument2)
{
    __debugbreak();
    return FALSE;
}


}; // extern "C"
