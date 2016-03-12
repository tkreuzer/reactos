
#include "Exp.hpp"

#include <Ke/Ke.hpp>
#include <Ke/Irql.hpp>

/*!
    \todo
        - Set Waiting bit
        - Update performance counters
        - Add Hypervisor enlightenments
*/

namespace Ex {

typedef union _EX_SPIN_LOCK
{
    volatile LONG_PTR Long;
    volatile PVOID Ptr;
    struct
    {
        ULONG_PTR Shared : sizeof(ULONG_PTR) * 8 - 2;
        ULONG_PTR Waiting : 1;
        ULONG_PTR Exclusive : 1;
    };
} EX_SPIN_LOCK, *PEX_SPIN_LOCK;

#define ReadPointerNoFence(Address) (*(void* volatile *)(Address))
#define WritePointerNoFence(Address, Value) (*(void* volatile *)(Address) = (Value))

#define EXCLUSIVE_BIT (sizeof(PVOID) * 8 - 1)

inline
VOID
ExpWaitForSpinLockExclusive (
    _In_ _Requires_lock_not_held_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    /* Lock is held exclusively, spin until it's free */
    while (SpinLock->Exclusive != 0)
    {
        YieldProcessor();
        KeMemoryBarrierWithoutFence();
    }
}

extern "C" {

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExAcquireSpinLockExclusiveAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    /* Try to set the exclusive lock bit */
    while (InterlockedBitTestAndSetLongPtrAcquire(&SpinLock->Long,
                                                  EXCLUSIVE_BIT) != 0)
    {
        /* Lock is held exclusively, spin until it's free */
        ExpWaitForSpinLockExclusive(SpinLock);
    }

    /* Now we need to wait for shared owners */
    while (SpinLock->Shared != 0)
    {
        YieldProcessor();
        KeMemoryBarrierWithoutFence();
    }

    NT_ASSERT(SpinLock->Exclusive == 1);
    NT_ASSERT(SpinLock->Shared == 0);
}

_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
NTAPI
ExAcquireSpinLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    KIRQL OldIrql;

    /* Raise IRQL to DISPATCH_LEVEL */
    OldIrql = KeRaiseIrqlToDpcLevel();

    /* Call the function for high IRQL */
    ExAcquireSpinLockExclusiveAtDpcLevel(SpinLock);

    /* return the old IRQL */
    return OldIrql;
}

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExAcquireSpinLockSharedAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    EX_SPIN_LOCK Value, Compare;

    Value.Ptr = ReadPointerNoFence(SpinLock);

    do
    {
        /* Check if the lock is held exclusively */
        if (Value.Exclusive != 0)
        {
            /* Lock is held exclusively, spin until it's free */
            ExpWaitForSpinLockExclusive(SpinLock);

            /* Reread the pointer value */
            Value.Ptr = ReadPointerNoFence(SpinLock);
        }

        /* Save the current value for comparison */
        Compare = Value;

        /* Increment the shared count */
        Value.Shared++;

        /* Atomically exchange with the new value */
        Value.Ptr = InterlockedCompareExchangePointerAcquire(&SpinLock->Ptr,
                                                             Value.Ptr,
                                                             Compare.Ptr);
        /* Repeat until the exchange succeeded */
    } while (Value.Ptr == Compare.Ptr);

    NT_ASSERT(SpinLock->Exclusive == 0);
    NT_ASSERT(SpinLock->Shared > 0);
}

_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
NTAPI
ExAcquireSpinLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    KIRQL OldIrql;

    /* Raise IRQL to DISPATCH_LEVEL */
    OldIrql = KeRaiseIrqlToDpcLevel();

    /* Call the function for high IRQL */
    ExAcquireSpinLockSharedAtDpcLevel(SpinLock);

    /* return the old IRQL */
    return OldIrql;
}

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockExclusiveFromDpcLevel (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    NT_ASSERT(SpinLock->Exclusive == 1);

    WritePointerNoFence(&SpinLock->Ptr, 0);
}

_IRQL_requires_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql)
{
    ExReleaseSpinLockExclusiveFromDpcLevel(SpinLock);

    KeLowerIrql(OldIrql);
}

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockSharedFromDpcLevel (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    InterlockedDecrementSizeT(&SpinLock->Long);
}

_IRQL_requires_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockShared (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql)
{
    ExReleaseSpinLockSharedFromDpcLevel(SpinLock);

    KeLowerIrql(OldIrql);
}

_Must_inspect_result_
_IRQL_requires_(DISPATCH_LEVEL)
_Post_satisfies_(return == 0 || return == 1)
LOGICAL
NTAPI
ExTryConvertSharedSpinLockExclusive (
    _Inout_ PEX_SPIN_LOCK SpinLock)
{
    /* Try to set the exclusive lock bit */
    if (InterlockedBitTestAndSetLongPtrAcquire(&SpinLock->Long,
                                               EXCLUSIVE_BIT) != 0)
    {
        /* There is an exclusive waiter, cannot convert to exclusive  */
        return FALSE;
    }

    /* Now we need to wait for other shared owners */
    while (SpinLock->Shared != 1)
    {
        YieldProcessor();
        KeMemoryBarrierWithoutFence();
    }

    //InterlockedDecrementSizeT(&SpinLock->Long);
    WritePointerNoFence(&SpinLock->Ptr, (PVOID)EXCLUSIVE_BIT);

    return TRUE;
}

}; // extern "C"
}; // namespace Ex


