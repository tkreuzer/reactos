
/* Possible enhancements:
 * Implement a shared version. shared locked is only a counter, atomically
 * incremented, if the highest bit is not set. First exclusive locker
 * now enqueues and sets lock pointer value to it's PRCB with an interlocked
 * compare exchange, using the share count, which is copied to the PRCB lock
 * queue before. Next shared locker must enqueue as usual. Leaving shared
 * lockers will decrement the count in the first waiter's PRCB, where the
 * waiter spins on. KeAcquireMSpinLockExclusive()
 * - Currently the spinlock needs to have a unique pointer, so allocating it
 * dynamically is not allowed. This can be overcome by using a hazard pointer
 * in each PRCB, which needs to be checked when the spinlock is initialized.
 * - Instead of using the PRCB, a global array could be used, which has
 * one element per CPU, which should be the size of a cache line.

 * - When a shared waiter is enqueued as the first waiter, then the lock is
 *   currently owned by an exclusive waiter. The share count of the spinlock
 *   is 0, the value is incremented by 1 before stored in the ShareCount field
 *   of the queue entry, to make sure all shared entries always contain 1, when
 *   being enqueued.
 * - When an exclusive waiter is enqueued as the first waiter, then the lock
 *   can be either owned exclusively or shared. In the shared case the value
 *   stored in the ShareCount field of the queue entry is the lock's current
 *   share count incremented by 1, which is used by the shared release routine
 *   to count down to 1, where all current shared users have released the lock.
 *   In the exclusive case, it's 1 and the value is ignored when the exclusive
 *   lock is being released.
 * - All queue entries that are enqueued after the first entry contain either 1
 *   to identify a shared locker, or 0 to identify an exclusive locker. These
 *   values are used, when a shared queue entry is released and subsequently
 *   releases the following shared entries.

 * Lock | Owner    | Queue
 *-------------------------------------
 *  0   | -        |
 *  1   | T0x      | -
 *  2   | T0s      | -
 *  4   | T0s/T1s  | -
 * &E1x | T0x      | E1x.ShareCount = 1
 * &E1x | T0s..Tns | E1x.ShareCount = n+2
 * &E1s | T0x      | E1s.ShareCount = 1
 * &E1x | T0x      | E1x.ShareCount = 1, E2x.ShareCount = 0

 */


/// \todo when acquiring a lock, preemption is disabled, but interrupts are
///       still allowed. When an interrupt occurs, the CPU should be dequeued
///       to not block the spin lock while serving the interrupt.

#include <ntoskrnl.h>
#include "Ke_internal.h"

typedef struct _KSPINLOCK_QENTRY
{
    ULONG_PTR Value;
    LONG ShareCount;
} KSPINLOCK_QENTRY, *PKSPINLOCK_QENTRY;


#if defined(_WIN64)
#define InterlockedCompareExchangeSizeT InterlockedCompareExchange64
#define InterlockedBitTestAndSetSizeT InterlockedBitTestAndSet64
#else
#define InterlockedCompareExchangeSizeT InterlockedCompareExchange
#define InterlockedBitTestAndSetSizeT InterlockedBitTestAndSet
#endif

BOOLEAN
FORCEINLINE
KiEnqueueQSpinLockWaitList(
    PKSPIN_LOCK SpinLock,
    KSPIN_LOCK SpinLockValue,
    PKSPINLOCK_QENTRY ThisEntry)
{
    PKSPINLOCK_QENTRY EntryPointer;
    ULONG_PTR EntryValue;
    KSPIN_LOCK OldLockValue;

    /* Set the CPUs SpinLockQueue to identify the spinLock */
    ThisEntry->Value = (ULONG_PTR)SpinLock|3;

    /* Check if the wait list is empty */
    if (SpinLockValue < 0x1000)
    {
        /* Save the previous share count incremented by 1.
         * This is a trick to make sure, all shared entries contain 1 */
        ThisEntry->ShareCount = (LONG)(SpinLockValue >> 1) + 1;

        /* There are no waiters, try to set this CPU as the first waiter */
        OldLockValue = InterlockedCompareExchangeSizeT(SpinLock,
                                                       (ULONG_PTR)ThisEntry|1,
                                                       SpinLockValue);

        /* Check if this succeeded */
        if (OldLockValue == SpinLockValue)
        {
            /* Success */
            return TRUE;
        }

        /* Retry acquiring */
        return FALSE;
    }

    /* Start at the head */
    EntryPointer = (PKSPINLOCK_QENTRY)(SpinLockValue & ~1);
    EntryValue = EntryPointer->Value;

    /* Try to find the last waiter */
    while (TRUE)
    {
        /* Check if this waiter is not blocked anymore */
        if (!(EntryValue & 1))
        {
            /* Spin on this entry, until it is released completely */
            while ((EntryPointer->Value & ~3) == (ULONG_PTR)SpinLock)
                YieldProcessor();

            /* We cannot enqueue here anymore */
            return FALSE;
        }

        /* Check if this is a tail entry */
        if (EntryValue & 2)
        {
            /* Check if the waiter is waiting for this lock */
            if (EntryValue != ((ULONG_PTR)SpinLock|3))
            {
                /* It's not, return failure */
                return FALSE;
            }

            /* Try to atomically enqueue as the next waiter */
            EntryValue = InterlockedCompareExchangeSizeT(&EntryPointer->Value,
                                                         (ULONG_PTR)ThisEntry|1,
                                                         EntryValue);

            /* Check for success */
            if (EntryValue == ((ULONG_PTR)SpinLock|3))
            {
                return TRUE;
            }
        }
        else
        {
            /* Go to the next waiter and continue searching */
            EntryPointer = (PKSPINLOCK_QENTRY)(EntryValue & ~1);
            EntryValue = EntryPointer->Value;
        }
    }
}


VOID
NTAPI
KeAcquireQSpinLock(KSPIN_LOCK *SpinLock)
{
    PKSPINLOCK_QENTRY ThisEntry;
    KSPIN_LOCK SpinLockValue;

    ThisEntry = (PKSPINLOCK_QENTRY)&KeGetCurrentPrcb()->SpinLockQueue;
    ASSERT(ThisEntry->Value = 0);

    /* Read the spin lock value */
    SpinLockValue = *SpinLock;

    while (TRUE)
    {
        /* Check if the lock is free */
        if (SpinLockValue == 0)
        {
            /* Try to atomically set the lock bit */
            if (InterlockedBitTestAndSetSizeT(SpinLock, 0) == 0)
            {
                /* Success, we're done! */
                return;
            }

            /* Someone was faster, start over */
            SpinLockValue = *SpinLock;
            continue;
        }

        /* Set share count to 0, to identify an exclusive waiter in the queue */
        ThisEntry->ShareCount = 0;

        /* There are waiters, try to enqueue at the end */
        if (KiEnqueueQSpinLockWaitList(SpinLock, SpinLockValue, ThisEntry))
        {
            /* Success */
            break;
        }

        /* We couldn't enqueue, so the wait list probably got empty.
           Restart the whole operation */
        SpinLockValue = *SpinLock;
    }

    /* Now spin until the lock is released */
    while (ThisEntry->Value & 1) YieldProcessor();

    /* Check if we need to update the Spinlock ourselves */
    if (ThisEntry->Value == 2)
    {
        /* The spinlock still points to our queue entry */
        ASSERT(*SpinLock == ((ULONG_PTR)ThisEntry|1));
        *SpinLock = 1;
        ThisEntry->Value = 0;
    }
}

VOID
FORCEINLINE
KiReleaseNextWaiter(
    PKSPIN_LOCK SpinLock,
    PKSPINLOCK_QENTRY FirstWaiter)
{
    ULONG_PTR EntryValue;

    /* Read the first waiter's queue entry */
    EntryValue = FirstWaiter->Value;
    ASSERT(EntryValue & 1);

    /* Check if this is the tail entry */
    if (EntryValue & 2)
    {
        ASSERT(EntryValue == ((ULONG_PTR)SpinLock|3));

#if 0 // TODO: check performance of these instructions
        /* In this case we need to use an atomic instruction, since concurrent
           CPUs might try to enqueue here */
        EntryValue = InterlockedAndSizeT(&FirstWaiter->Value, ~1);
#else
        /* No other waiters are there, try to reset the first waiter  */
        EntryValue = InterlockedCompareExchangeSizeT(&FirstWaiter->Value,
                                                     EntryValue & ~1,
                                                     EntryValue);
#endif
        /* Check for success */
        if (EntryValue & 2)
        {
            ASSERT(EntryValue == ((ULONG_PTR)SpinLock|3));

            /* We're done. The waiter will change the spinlock value */
            return;
        }
    }

    /* Write the next waiter as wait list head */
    *SpinLock = EntryValue;

    /* Release the first waiter */
    FirstWaiter->Value = (EntryValue & ~1);
}

VOID
NTAPI
KeReleaseQSpinLock(PKSPIN_LOCK SpinLock)
{
    PKSPINLOCK_QENTRY FirstWaiter;
    KSPIN_LOCK SpinLockValue;

    /* Read the spin lock value */
    SpinLockValue = *SpinLock;

    /* Check if we have waiters */
    if (SpinLockValue == 1)
    {
        /* There are no waiters, so try to unlock */
        SpinLockValue = InterlockedCompareExchangeSizeT(SpinLock, 0, 1);

        /* Check for success */
        if (SpinLockValue == 1)
        {
            /* Success, we're done! */
            return;
        }
    }

    /* Get the first waiter */
    FirstWaiter = (PKSPINLOCK_QENTRY)(SpinLockValue & ~1);

    /* Release the first waiter */
    KiReleaseNextWaiter(SpinLock, FirstWaiter);
}


VOID
NTAPI
KeAcquireQSpinLockShared(KSPIN_LOCK *SpinLock)
{
    PKSPINLOCK_QENTRY ThisEntry, NextWaiter;
    KSPIN_LOCK SpinLockValue, OldLockValue;

    ThisEntry = (PKSPINLOCK_QENTRY)&KeGetCurrentPrcb()->SpinLockQueue;
    ASSERT(ThisEntry->Value = 0);

    /* Read the spin lock value */
    SpinLockValue = *SpinLock;

    while (TRUE)
    {
        /* Check if the lock is available */
        if (!(SpinLockValue & 1))
        {
            /* Try to atomically increment the share count */
            OldLockValue = InterlockedCompareExchangeSizeT(SpinLock,
                                                           SpinLockValue + 2,
                                                           SpinLockValue);

            if (OldLockValue == SpinLockValue)
            {
                /* Success, we're done! */
                return;
            }

            /* Someone was faster, start over */
            SpinLockValue = OldLockValue;
            continue;
        }

        /* Set share count to 1, to identify a shared waiter in the queue */
        ThisEntry->ShareCount = 1;

        /* There are waiters, try to enqueue at the end */
        if (KiEnqueueQSpinLockWaitList(SpinLock, SpinLockValue, ThisEntry))
        {
            /* Success */
            break;
        }

        /* We couldn't enqueue, so the wait list probably got empty.
           Restart the whole operation */
        SpinLockValue = *SpinLock;
    }

    /* Now spin until the lock is released */
    while (ThisEntry->Value & 1) YieldProcessor();

    /* Check if this was a tail entry */
    if (ThisEntry->Value & 2)
    {
        /* The spinlock must still point to our queue entry */
        ASSERT(*SpinLock == ((ULONG_PTR)ThisEntry|1));

        /* This is the last waiter in the queue.
           Store the accumulated share count in the spin lock */
        *SpinLock = ThisEntry->ShareCount << 1;
    }
    else
    {
        /* Get the next waiter */
        NextWaiter = (PKSPINLOCK_QENTRY)(ThisEntry->Value & ~1);

        /* Check if the next waiter is also a shared waiter */
        if (NextWaiter->ShareCount > 0)
        {
            /* Pass on the accumulated share count, increased by 1 */
            NextWaiter->ShareCount = ThisEntry->ShareCount + 1;

            /* Release the next waiter */
            NextWaiter->Value = (NextWaiter->Value & ~1);
        }
    }

    /* Clean up the queue entry */
    ThisEntry->Value = 0;
}


VOID
NTAPI
KeReleaseQSpinLockShared(PKSPIN_LOCK SpinLock)
{
    PKSPINLOCK_QENTRY FirstWaiter;
    KSPIN_LOCK SpinLockValue, OldLockValue;

    /* Read the spin lock value */
    SpinLockValue = *SpinLock;

    while (SpinLockValue < 0x1000)
    {
        /* There are no waiters, so try to unlock */
        OldLockValue = InterlockedCompareExchangeSizeT(SpinLock,
                                                       SpinLockValue - 2,
                                                       SpinLockValue);

        /* Check for success */
        if (OldLockValue == SpinLockValue)
        {
            /* Success, we're done! */
            return;
        }

        /* Someone was faster, start over */
        SpinLockValue = OldLockValue;
    }

    /* Get the first waiter */
    FirstWaiter = (PKSPINLOCK_QENTRY)(SpinLockValue & ~1);

    /* Decrement the share count.
       Note: the value is one above the actual sharing value. */
    if (InterlockedDecrement(&FirstWaiter->ShareCount) > 1)
    {
        /* There are more threads sharing this lock */
        return;
    }

    /* Release the first waiter */
    KiReleaseNextWaiter(SpinLock, FirstWaiter);
}


