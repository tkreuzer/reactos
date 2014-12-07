
#include "Apc.hpp"

extern "C" {

_IRQL_requires_same_
VOID
NTAPI
KeInitializeApc (
    _Out_ PRKAPC Apc,
    _In_ PRKTHREAD Thread,
    _In_ KAPC_ENVIRONMENT Environment,
    _In_ PKKERNEL_ROUTINE KernelRoutine,
    _In_opt_ PKRUNDOWN_ROUTINE RundownRoutine,
    _In_opt_ PKNORMAL_ROUTINE NormalRoutine,
    _In_opt_ KPROCESSOR_MODE ProcessorMode,
    _In_opt_ PVOID NormalContext)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeAreAllApcsDisabled (
    VOID)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeAreApcsDisabled (
    VOID)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
BOOLEAN
NTAPI
KeInsertQueueApc (
    _Inout_ PRKAPC Apc,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2,
    _In_ KPRIORITY Increment)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KiCheckForKernelApcDelivery (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
KiDeliverApc (
    PVOID p1,
    PVOID p2,
    PVOID p3)
{
    __debugbreak();
}

// wdm.h
_Acquires_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
KeEnterCriticalRegion (
    VOID)
{
    __debugbreak();
}

// wdm.h
_Releases_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
KeLeaveCriticalRegion (
    VOID)
{
    __debugbreak();
}

// wdm.h
_Acquires_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeEnterGuardedRegion (
    VOID)
{
    __debugbreak();
}

// wdm.h
_Releases_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeLeaveGuardedRegion (
    VOID)
{
    __debugbreak();
}

}; // extern "C"
