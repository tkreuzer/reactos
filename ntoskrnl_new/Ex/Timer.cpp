
#include "Exp.hpp"

typedef struct _OBJECT_TYPE *POBJECT_TYPE;

extern "C" {

POBJECT_TYPE ExTimerObjectType;

/// FIXME: should be in wdm.h
typedef struct _EX_TIMER *PEX_TIMER;
_Function_class_(EXT_CALLBACK)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
VOID
EXT_CALLBACK (
    _In_ PEX_TIMER Timer,
    _In_opt_ PVOID Context
    );
typedef EXT_CALLBACK *PEXT_CALLBACK;
typedef struct _EXT_SET_PARAMETERS_V0 {
    ULONG Version;
    ULONG Reserved;
    LONGLONG NoWakeTolerance;
} EXT_SET_PARAMETERS, *PEXT_SET_PARAMETERS;
typedef EXT_SET_PARAMETERS KT2_SET_PARAMETERS, *PKT2_SET_PARAMETERS;
_Function_class_(EXT_DELETE_CALLBACK)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
VOID
EXT_DELETE_CALLBACK (
    _In_opt_ PVOID Context
    );
typedef EXT_DELETE_CALLBACK *PEXT_DELETE_CALLBACK;
typedef PVOID PEXT_CANCEL_PARAMETERS;
typedef struct _EXT_DELETE_PARAMETERS {
    ULONG Version;
    ULONG Reserved;
    PEXT_DELETE_CALLBACK DeleteCallback;
    PVOID DeleteContext;
} EXT_DELETE_PARAMETERS, *PEXT_DELETE_PARAMETERS;

/// FIXME: should be in wdm.h
FORCEINLINE
VOID
KeInitializeTimer2SetParameters (
    _Out_ PKT2_SET_PARAMETERS Parameters)
{
    RtlZeroMemory(Parameters, sizeof(*Parameters));
    NT_ASSERT(Parameters->Version == 0);
}

FORCEINLINE
VOID
ExInitializeSetTimerParameters (
    _Out_ PEXT_SET_PARAMETERS Parameters)
{
    KeInitializeTimer2SetParameters(Parameters);
}

FORCEINLINE
VOID
ExInitializeDeleteTimerParameters (
    _Out_ PEXT_DELETE_PARAMETERS Parameters)
{
    RtlZeroMemory(Parameters, sizeof(*Parameters));
    NT_ASSERT(Parameters->Version == 0);
}

PEX_TIMER
NTAPI
ExAllocateTimerInternal (
    _In_ PEXT_CALLBACK Callback,
    _In_opt_ PVOID CallbackContext,
    _When_(((_Curr_ & EX_TIMER_IDLE_RESILIENT) != 0),
            __drv_reportError("Use of EX_TIMER_IDLE_RESILIENT is"
                              " strictly restricted."))
    _In_ ULONG Attributes)
{
    __debugbreak();
    return NULL;
}

PEX_TIMER
NTAPI
ExAllocateTimer (
    _In_opt_ PEXT_CALLBACK Callback,
    _In_opt_ PVOID CallbackContext,
    _In_ ULONG Attributes)
{
    __debugbreak();
    return NULL;
}

BOOLEAN
NTAPI
ExSetTimer (
    _In_ PEX_TIMER Timer,
    _In_ LONGLONG DueTime,
    _In_ LONGLONG Period,
    _In_opt_ PEXT_SET_PARAMETERS Parameters)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
ExCancelTimer (
    _Inout_ PEX_TIMER Timer,
    _In_opt_ PEXT_CANCEL_PARAMETERS Parameters)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
ExDeleteTimer (
    _In_ PEX_TIMER Timer,
    _In_ BOOLEAN Cancel,
    _In_ BOOLEAN Wait,
    _In_opt_ PEXT_DELETE_PARAMETERS Parameters)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
ExQueryTimerResolution (
    _Out_ PULONG MaximumTime,
    _Out_ PULONG MinimumTime,
    _Out_ PULONG CurrentTime)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
ExSetTimerResolution (
    _In_ ULONG DesiredTime,
    _In_ BOOLEAN SetResolution)
{
    __debugbreak();
    return 0;
}

}; // extern "C"
