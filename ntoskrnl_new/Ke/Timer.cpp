
#include "Timer.hpp"

extern "C" {

typedef struct _KTIMER *PKTIMER;

// @ stub KeCancelTimer2
// @ stub KeInitializeTimer2
// @ stub KeSetTimer2
// ; ??? @ extern -arch=??? KiEnableTimerWatchdog

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
KeInitializeTimer (
    _Out_ PKTIMER Timer)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
KeInitializeTimerEx (
    _Out_ PKTIMER Timer,
    _In_ TIMER_TYPE Type)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeReadStateTimer (
    _In_ PKTIMER Timer)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeSetTimer (
    _Inout_ PKTIMER Timer,
    _In_ LARGE_INTEGER DueTime,
    _In_opt_ PKDPC Dpc)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeSetTimerEx (
    _Inout_ PKTIMER Timer,
    _In_ LARGE_INTEGER DueTime,
    _In_ LONG Period,
    _In_opt_ PKDPC Dpc)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeSetCoalescableTimer (
    _Inout_ PKTIMER Timer,
    _In_ LARGE_INTEGER DueTime,
    _In_ ULONG Period,
    _In_ ULONG TolerableDelay,
    _In_opt_ PKDPC Dpc)
{
    __debugbreak();
    return FALSE;
}

/// FIXME: should be in wdm.h
typedef struct _EXT_SET_PARAMETERS_V0 {
    ULONG Version;
    ULONG Reserved;
    LONGLONG NoWakeTolerance;
} EXT_SET_PARAMETERS, *PEXT_SET_PARAMETERS;
typedef EXT_SET_PARAMETERS KT2_SET_PARAMETERS, *PKT2_SET_PARAMETERS;

FORCEINLINE
VOID
KeInitializeTimer2SetParameters (
    _Out_ PKT2_SET_PARAMETERS Parameters)
{
    RtlZeroMemory(Parameters, sizeof(*Parameters));
    NT_ASSERT(Parameters->Version == 0);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeCancelTimer (
    _Inout_ PKTIMER)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"
