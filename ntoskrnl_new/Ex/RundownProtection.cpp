
#include "Exp.hpp"

extern "C" {

VOID
FASTCALL
ExInitializeRundownProtection (
    _Out_ PEX_RUNDOWN_REF RunRef)
{
    __debugbreak();
}

VOID
FASTCALL
ExReInitializeRundownProtection (
    _Inout_ PEX_RUNDOWN_REF RunRef)
{
    __debugbreak();
}

_Must_inspect_result_
_Post_satisfies_(return==0 || return==1)
BOOLEAN
FASTCALL
ExAcquireRundownProtection (
    _Inout_ PEX_RUNDOWN_REF RunRef)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_Post_satisfies_(return == 0 || return == 1)
BOOLEAN
FASTCALL
ExAcquireRundownProtectionEx (
    _Inout_ PEX_RUNDOWN_REF RunRef,
    _In_ ULONG Count)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FASTCALL
ExReleaseRundownProtection (
    _Inout_ PEX_RUNDOWN_REF RunRef)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FASTCALL
ExReleaseRundownProtectionEx (
    _Inout_ PEX_RUNDOWN_REF RunRef,
    _In_ ULONG Count)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
ExWaitForRundownProtectionRelease (
    _Inout_ PEX_RUNDOWN_REF RunRef)
{
    __debugbreak();
}

VOID
FASTCALL
ExRundownCompleted (
    _Out_ PEX_RUNDOWN_REF RunRef)
{
    __debugbreak();
}

}; // extern "C"
