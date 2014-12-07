
#include "SpinLock.hpp"

extern "C" {

VOID
NTAPI
KeInitializeSpinLock (
    _Out_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
}

_Must_inspect_result_
BOOLEAN
FASTCALL
KeTestSpinLock (
    _In_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_min_(DISPATCH_LEVEL)
_Post_satisfies_(return == 1 || return == 0)
BOOLEAN
FASTCALL
KeTryToAcquireSpinLockAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_lock_(*_Curr_))
        PKSPIN_LOCK SpinLock)
{
    __debugbreak();
    return FALSE;
}

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
KeAcquireSpinLockAtDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
}

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
KeReleaseSpinLockFromDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
}

#ifdef _M_IX86
_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
FASTCALL
KefAcquireSpinLockAtDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
}

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
FASTCALL
KefReleaseSpinLockFromDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
}
#endif // _M_IX86

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
FASTCALL
KeAcquireSpinLockRaiseToDpc (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
    return 0;
}

#ifdef _M_IX86
_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
NTAPI
Ke386AcquireSpinLock (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
    return 0;
}
#endif

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_raises_(SYNCH_LEVEL)
_IRQL_saves_
KIRQL
FASTCALL
KeAcquireSpinLockRaiseToSynch (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
    return 0;
}

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_(DISPATCH_LEVEL)
VOID
FASTCALL
KeReleaseSpinLock (
    _Inout_ PKSPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL NewIrql)
{
    __debugbreak();
}

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
KIRQL
FASTCALL
KeAcquireSpinLockForDpc (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    __debugbreak();
    return 0;
}

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_(DISPATCH_LEVEL)
VOID
FASTCALL
KeReleaseSpinLockForDpc (
    _Inout_ PKSPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql)
{
    __debugbreak();
}

}; // extern "C"
