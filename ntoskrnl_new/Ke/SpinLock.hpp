
#pragma once

#include "Kep.hpp"


VOID
FORCEINLINE
_KiAcquireSpinLock(
    IN PKSPIN_LOCK SpinLock)
{
    ASSERT((*SpinLock & ~1) != (KSPIN_LOCK)KeGetCurrentThread());

#ifdef CONFIG_SMP
    /* Try to acquire the lock */
    do
    {
        /* Spin while the lock is not free */
        while (*(volatile KSPIN_LOCK *)SpinLock & 1) YieldProcessor();
    } while (InterlockedBitTestAndSet((PLONG)SpinLock, 0));
#else
    /* Add an explicit memory barrier to prevent the compiler from reordering
    memory accesses across the borders of UP spinlocks */
    KeMemoryBarrierWithoutFence();
#endif

#ifdef DBG
    /* On debug builds put the KTHREAD into the spinlock */
    *SpinLock = (KSPIN_LOCK)KeGetCurrentThread() | 1;
#endif
}

VOID
FORCEINLINE
_KiReleaseSpinLock(
    IN PKSPIN_LOCK SpinLock)
{
    ASSERT((*SpinLock & ~1) == (KSPIN_LOCK)KeGetCurrentThread());

#ifdef CONFIG_SMP
#if defined(_M_IX86) || defined(_M_AMD64)
    /* x86/amd64 SMP memory ordering guarantees the following:

    a) Loads do not pass previous loads (loads are not re-ordered) and
    stores do not pass previous stores (stores are not re-ordered).

    A shared variable is initialized with 0 and the spinlock acquired by
    CPU0, containing 1. If CPU0 first writes 1 to the shared variable,
    and then writes 0 to the spinlock, and CPU1 first reads the spinlock
    then read the shared variable, then CPU1 cannot read a value of 0
    from the shared variable if it read 0 from the spinlock.

    b) Stores do not pass loads

    A shared variable is initialized with 0 and the spinlock acquired by
    CPU0, containing 1. If CPU0 first reads the shared variable, then
    writes 0 to the spinlock, CPU1 first reads the spinlock and then (if
    it read 0) writes 1 to the shared variable, then CPU0 cannot read 1
    from the shared variable. */
    *SpinLock = 0;
#else /* _M_IX86 || _M_AMD64 */
    /* Do it the hard (and slow) way */
    InterlockedExchangePointer((PVOID*)SpinLock, 0);
#endif /* _M_IX86 || _M_AMD64 */

#else /* CONFIG_SMP */
    /* Add an explicit memory barrier to prevent the compiler from reordering
    memory accesses across the borders of UP spinlocks. While the CPU is
    allowed to do speculative reads, even preceeding a mov cr8, * (which
    is not a serializing instruction), the results would be invalidated, if
    an interrupt happened between reading the memory and raising irql. */
    KeMemoryBarrierWithoutFence();
#ifdef DBG
    /* On debug builds we need to reset the value */
    *SpinLock = (KSPIN_LOCK)KeGetCurrentThread() | 1;
#endif /* DBG */
#endif /* CONFIG_SMP */
}

namespace Ke {

VOID
FASTCALL
SpinAndAcquireExclusiveOnly (
    volatile ULONG_PTR *Lock,
    ULONG ExclusiveBit);

template<unsigned _BIT>
class TSPIN_LOCK
{
protected:

    volatile ULONG_PTR _Value;

    _Requires_lock_not_held_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    VOID
    WaitForExclusive (
        VOID)
    {
        /* Lock is held exclusively, spin until it's free */
        while ((_Value & (1 << _BIT)) != 0)
        {
            YieldProcessor();
            KeMemoryBarrierWithoutFence();
        }
    }

    _Requires_lock_not_held_(*this)
    _Acquires_exclusive_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    VOID
    AcquireExclusiveInternal (
        VOID)
    {
        /* Try to set the exclusive lock bit */
        while (InterlockedBitTestAndSetSizeTAcquire(&_Value, _BIT) != 0)
        {
            /* Lock is held exclusively, spin until it's free */
            WaitForExclusive();
        }
    }

public:

    inline
    TSPIN_LOCK (
        VOID)
    {
        _Value = 0;
    }

    _Must_inspect_result_
    BOOLEAN
    FASTCALL
    Test (
        VOID)
    {
        return ((_Value & (1 << _BIT)) == 0);
    }

    _Requires_lock_not_held_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    BOOLEAN
    TryToAcquireExclusive (
        VOID)
    {
        /* First test the spin lock */
        if (*SpinLock & 1) return FALSE;

        return (InterlockedBitTestAndSetSizeTAcquire(&_Value, _BIT) == 0);
    }

    _Requires_lock_not_held_(*this)
    _Acquires_exclusive_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    VOID
    AcquireExclusive (
        VOID)
    {
        /* Try acquiring inline */
        if (!TryToAcquireExclusive())
        {
            /* Use the long path */
            SpinAndAcquireExclusiveOnly(&_Value, _BIT);
        }
        NT_ASSERT((_Value & (1 << _BIT)) != 0);
    }

    _Requires_exclusive_lock_held_(*this)
    _Releases_exclusive_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    VOID
    ReleaseExclusive (
        VOID)
    {
        ULONG_PTR value = _Value;
        WriteULongPtrRelease(&_Value, value & ~(1 << _BIT));
    }

    _Requires_exclusive_lock_held_(*this)
    _Releases_exclusive_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    VOID
    ReleaseSetZero (
        VOID)
    {
        WriteULongPtrRelease(&_Value, 0);
    }

};

template<unsigned _BIT, SSIZE_T _INC>
class TSPIN_LOCK_EX : public TSPIN_LOCK<_BIT>
{
public:

    _Requires_lock_not_held_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    BOOLEAN
    TryToAcquireExclusive (
        VOID)
    {
        return (InterlockedCompareExchangeSizeTAcquire(&this->_Value,
                                                       1 << _BIT,
                                                       0) == 0);
    }

    _Requires_lock_not_held_(*this)
    _Acquires_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    VOID
    AcquireExclusive (
        VOID)
    {
        // Exclusive bit is for exclusive only!
        // a: try full acquire, fall back to wait
        // b: try set exclusive, spin on shared
        /* First acquire the exclusive bit */
        TSPIN_LOCK<_BIT>::AcquireExclusive();

        /* Now wait for shared owners */
        while (this->_Value != (1 << _BIT))
        {
            YieldProcessor();
        }

        NT_ASSERT(this->_Value == (1 << _BIT));
    }

    _Requires_lock_not_held_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    BOOLEAN
    TryToAcquireShared (
        VOID)
    {
        ULONG_PTR value, previous;

        value = ReadULongPtrAcquire(&this->_Value);
        if ((value & (1 << _BIT)) != 0)
        {
            return FALSE;
        }

        previous = InterlockedCompareExchangeSizeTAcquire(&this->_Value,
                                                          value + _INC,
                                                          value);
        return (previous == value);
    }

    _Requires_lock_not_held_(*this)
    _Acquires_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    VOID
    AcquireShared (
        VOID)
    {
        ULONG_PTR value, compare;

        value = ReadULongPtrAcquire(&this->_Value);
        do
        {
            /* Check if the lock is held exclusively */
            while ((value & (1 << _BIT)) != 0)
            {
                /* Lock is held exclusively, spin until it's free */
                this->WaitForExclusive();

                /* Reread the pointer value */
                value = ReadULongPtrAcquire(&this->_Value);
            }

            /* Save the current value for comparison */
            compare = value;

            /* Atomically exchange with the new value */
            value = InterlockedCompareExchangeSizeTAcquire(&this->_Value,
                                                           value + _INC,
                                                           compare);
            /* Repeat until the exchange succeeded */
        } while (value != compare);

        NT_ASSERT((this->_Value & (1 << _BIT)) == 0);
        NT_ASSERT(this->_Value != 0);
    }

    _Requires_exclusive_lock_held_(*this)
    _Releases_exclusive_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    inline
    VOID
    ReleaseExclusive (
        VOID)
    {
        InterlockedBitTestAndResetSizeTRelease(&this->_LongValue, _BIT);
    }

    _Requires_lock_held_(*this)
    _Releases_lock_(*this)
    _IRQL_requires_min_(DISPATCH_LEVEL)
    VOID
    ReleaseShared (
        VOID)
    {
        InterlockedExchangeAddSizeTRelease(&this->_LongValue, -_INC);
    }

};

struct _EX_SPIN_LOCK
{
    ULONG_PTR Shared : sizeof(ULONG_PTR) * 8 - 2;
    ULONG_PTR Waiting : 1;
    ULONG_PTR Exclusive : 1;
};

typedef class TSPIN_LOCK<0> SPIN_LOCK;
typedef class TSPIN_LOCK_EX<0, 2> SPIN_LOCK_EX;

}; // namespace Ke

typedef Ke::SPIN_LOCK KSPIN_LOCK, *PKSPIN_LOCK;

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
