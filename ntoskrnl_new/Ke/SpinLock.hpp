
#pragma once

#include "Kep.hpp"


extern "C" {

#ifdef _M_IX86
#define KeAcquireSpinLockRaiseToDpc KfAcquireSpinLock
#define KeReleaseSpinLock KfReleaseSpinLock
#endif // _M_IX86

VOID
NTAPI
KeInitializeSpinLock (
    _Out_ PKSPIN_LOCK SpinLock);

_Must_inspect_result_
BOOLEAN
FASTCALL
KeTestSpinLock (
    _In_ PKSPIN_LOCK SpinLock);

_Must_inspect_result_
_IRQL_requires_min_(DISPATCH_LEVEL)
_Post_satisfies_(return == 1 || return == 0)
BOOLEAN
FASTCALL
KeTryToAcquireSpinLockAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_lock_(*_Curr_))
        PKSPIN_LOCK SpinLock);

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
KeAcquireSpinLockAtDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock);

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
KeReleaseSpinLockFromDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock);

#ifdef _M_IX86
_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
FASTCALL
KefAcquireSpinLockAtDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock);

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
FASTCALL
KefReleaseSpinLockFromDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock);
#endif // _M_IX86

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
FASTCALL
KeAcquireSpinLockRaiseToDpc (
    _Inout_ PKSPIN_LOCK SpinLock);

#ifdef _M_IX86
_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
NTAPI
KeAcquireSpinLock (
    _Inout_ PKSPIN_LOCK SpinLock);
#endif

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_raises_(SYNCH_LEVEL)
_IRQL_saves_
KIRQL
FASTCALL
KeAcquireSpinLockRaiseToSynch (
    _Inout_ PKSPIN_LOCK SpinLock);

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_(DISPATCH_LEVEL)
VOID
FASTCALL
KeReleaseSpinLock (
    _Inout_ PKSPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL NewIrql);

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
KIRQL
FASTCALL
KeAcquireSpinLockForDpc (
    _Inout_ PKSPIN_LOCK SpinLock);

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_(DISPATCH_LEVEL)
VOID
FASTCALL
KeReleaseSpinLockForDpc (
    _Inout_ PKSPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql);

_Requires_lock_not_held_(*Interrupt->ActualLock)
_Acquires_lock_(*Interrupt->ActualLock)
_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
_IRQL_raises_(HIGH_LEVEL)
KIRQL
NTAPI
KeAcquireInterruptSpinLock (
    _Inout_ PKINTERRUPT Interrupt);

_Requires_lock_held_(*Interrupt->ActualLock)
_Releases_lock_(*Interrupt->ActualLock)
_IRQL_requires_(HIGH_LEVEL)
VOID
NTAPI
KeReleaseInterruptSpinLock (
    _Inout_ PKINTERRUPT Interrupt,
    _In_ _IRQL_restores_ KIRQL OldIrql);

}; // extern "C"
