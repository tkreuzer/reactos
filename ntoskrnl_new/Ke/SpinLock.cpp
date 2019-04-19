
#include "SpinLock.hpp"
#include "Irql.hpp"

#include <Cpp/bitcount.hpp>

namespace Ke {

VOID
FASTCALL
SpinAndAcquireExclusiveOnly (
    volatile ULONG_PTR *Lock,
    ULONG ExclusiveBit)
{
    do
    {
        do
        {
            YieldProcessor();
        } while ((ReadULongPtrAcquire(Lock) & ((ULONG_PTR)1 << ExclusiveBit)) != 0);
    } while (InterlockedBitTestAndSetSizeTAcquire(Lock, ExclusiveBit) != 0);
}

VOID
FASTCALL
SpinAndAcquireExclusiveEx (
    volatile ULONG_PTR *Lock,
    ULONG ExclusiveBit)
{
    SpinAndAcquireExclusiveOnly(Lock, ExclusiveBit);

    while (ReadULongPtrAcquire(Lock) != ((ULONG_PTR)1 << ExclusiveBit))
    {
        YieldProcessor();
    }

}

bool Test()
{
    struct FOO
    {
        LIST_ENTRY ListLink;
    };

    struct BAR
    {
        LINKED_LIST<FOO> FooList;
    } a;

    return a.FooList.IsEmpty();
}
}; // namespace Ke

extern "C" {

using namespace Ke;

VOID
NTAPI
KeInitializeSpinLock (
    _Out_ PKSPIN_LOCK SpinLock)
{
    new (SpinLock) SPIN_LOCK;
}

_Must_inspect_result_
BOOLEAN
FASTCALL
KeTestSpinLock (
    _In_ PKSPIN_LOCK SpinLock)
{
    return SpinLock->Test();
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
    return SpinLock->TryToAcquireExclusive();
}

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
KeAcquireSpinLockAtDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    SpinLock->AcquireExclusive();
}

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
KeReleaseSpinLockFromDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    SpinLock->ReleaseSetZero();
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
    SpinLock->AcquireExclusive();
}

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
FASTCALL
KefReleaseSpinLockFromDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock)
{
    SpinLock->ReleaseSetZero();
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
    KIRQL OldIrql;

    /* Raise IRQL to dispatch level */
    OldIrql = KeRaiseIrqlToDpcLevel();

    /* Use the inlined function */
    SpinLock->AcquireExclusive();

    return OldIrql;
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
    KIRQL OldIrql;

    OldIrql = KeRaiseIrqlToDpcLevel();
    SpinLock->AcquireExclusive();
    return OldIrql;
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
    KIRQL OldIrql;

    /* Raise IRQL to synch level */
    OldIrql = KfRaiseIrql(SYNCH_LEVEL);

    /* Use the inlined function */
    SpinLock->AcquireExclusive();

    return OldIrql;
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
    /* Use the inlined version */
    SpinLock->ReleaseSetZero();

    /* Restore IRQL */
    KeLowerIrql(NewIrql);
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
    KIRQL OldIrql;

    /* Get the current IRQL */
    OldIrql = KeGetCurrentIrql();

    /* Check if this is a threaded DPC running at passive level */
    if (OldIrql < DISPATCH_LEVEL)
    {
        /* In this case we need to raise IRQL */
        KfRaiseIrql(DISPATCH_LEVEL);
    }

    SpinLock->AcquireExclusive();

    return OldIrql;
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
    SpinLock->ReleaseSetZero();

    /* Restore IRQL */
    KeLowerIrql(OldIrql);
}

}; // extern "C"
