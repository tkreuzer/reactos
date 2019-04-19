

#include <ntoskrnl.h>
#include "Ke_internal.h"

#ifdef _M_AMD64
typedef union _KSPINLOCK_QUEUE_ENTRY
{
    /* Must be signed! */
    LONGLONG LongLong;
    struct
    {
        LONGLONG CpuNumber : 12;
        LONGLONG SpinLock : 52;
    };
} KSPINLOCK_QUEUE_ENTRY, *PKSPINLOCK_QUEUE_ENTRY;

#define MAKE_ENTRY(Entry, SpinLock, NextWaiter) \
    Entry->LongLong = (LONGLONG)SpinLock << 12; \
    Entry->CpuNumber = NextWaiter->Number;

#define GET_LOCK(Entry) ((PKSPIN_LOCK)(Entry->LongLong >> 12))
#define GET_NEXT_WAITER(Entry) KeProcessorBlock[Entry->CpuNumber]

/* aligned 64 bit reads and writes are atomic */
#define READ_ENTRY(Dest, Source) Dest->LongLong = *Source;
#define WRITE_ENTRY(Dest, Source) *Dest = Source->LongLong;

#elif defined(_M_IX86)
typedef union _KSPINLOCK_QUEUE_ENTRY
{
    LONGLONG LongLong;
    struct
    {
        PKPRCB NextWaiter;
        PKSPIN_LOCK SpinLock;
    };
} KSPINLOCK_QUEUE_ENTRY, *PKSPINLOCK_QUEUE_ENTRY;

#define MAKE_ENTRY(Entry, SpinLock, NextWaiter) \
    Entry->SpinLock = SpinLock; \
    Entry->NextWaiter = NextWaiter;

#define GET_LOCK(Entry) (Entry->SpinLock)
#define GET_NEXT_WAITER(Entry) (Entry->NextWaiter)

/* Read the NextWaiter before reading the SpinLock */
#define READ_ENTRY(Dest, Source) \
    Dest->NextWaiter = Source->NextWaiter; \
    Dest->SpinLock = Source->SpinLock;

/* Write the SpinLock before writing the NextWaiter */
#define WRITE_ENTRY(Dest, Source) \
    Dest->SpinLock = Source->SpinLock; \
    Dest->NextWaiter = Source->NextWaiter;


#else
#error not implemented
#endif

BOOLEAN
FORCEINLINE
KiEnqueueQSpinLockWaitList(PKPRCB WaitListHead)
{
    KSPINLOCK_QUEUE_ENTRY QueueEntry;
    PKPRCB CurrentWaiter;

    /* Start at the head */
    CurrentWaiter = WaitListHead;

    /* Try to find the last waiter */
    do
    {
        /* Read the waiters queue entry */
        READ_ENTRY(&QueueEntry, CurrentWaiter->SpinLockQueue);

        /* Get the lock pointer */
        CurrentLock = GET_LOCK(&QueueEntry);

        /* Check if the waiter is waiting for this lock */
        if (CurrentLock != SpinLock)
        {
            /* It's not, return failure */
            return FALSE;
        }

        /* Get the next waiter and check if there is any */
        NextWaiter = GET_NEXT_WAITER(&QueueEntry);
        if (NextWaiter != NULL)
        {
            /* Switch to the next waiter and continue searching */
            CurrentWaiter = NextWaiter;
            continue;
        }


        MAKE_ENTRY(NewEntry, SpinLock, CurrentPrcb);

        Previous = InterlockedCompareExchange64(&CurrentWaiter->SpinLockQueue,
                                                NewEntry.LongLong,
                                                QueueEntry.LongLong);

        /* Check for success */
        if (Previous == QueueEntry.LongLong)
        {
            /* Success, break out of both loops */
            return TRUE;
        }
    }
}


VOID
NTAPI
KeAcquireQSpinLock(KSPIN_LOCK *SpinLock)
{
    PKPRCB FirstWaiter, CurrentPrcb = KeGetCurrentPrcb();
    LOCK_QUEUE Current
    KSPIN_LOCK SpinLockValue;

    MAKE_ENTRY(&CurrentPrcb->SpinLockQueue, SpinLock, NULL);

    while (TRUE)
    {
        /* Read the spin lock value */
        SpinLockValue = *SpinLock;

        /* Check if the lock is free */
        if (SpinLockValue == 0)
        {
            /* Try to atomically set the busy bit */
            if (InterlockedBitTestAndSet(SpinLock, 1) == 0)
            {
                /* Success, we're done! */
                return;
            }

            /* Someone was faster, start over */
            continue;
        }

        /* Mask off the busy bit and check if we have waiters */
        FirstWaiter = (PKPRCB)(SpinLockValue & ~1);
        if (FirstWaiter == NULL)
        {
            /* There are no waiters, try to set this CPU as the first waiter */
            Previous = InterlockedCompareExchangePointer(SpinLock,
                                                         (PVOID)((ULONG_PTR)CurrentPrcb|1),
                                                         (PVOID)(ULONG_PTR)1);

            /* Check if this succeeded */
            if (Previous == (PVOID)1)
            {
                /* Break out of the loop */
                break;
            }

            /* Check if the lock is free now */
            if (Previous == NULL)
            {
                /* Retry acquiring */
                continue;
            }
        }

        /* There are waiters, try to enqueue at the end */
        if (KiEnqueueQSpinLockWaitList(FirstWaiter))
        {
            /* Success */
            break;
        }

        /* We couldn't enqueue, so the wait list probably got empty.
           Restart the whole operation */
    }

    /* Now spin until the lock is released */
    while (GET_LOCK(&QueueEntry)) YieldProcessor();
}


VOID
NTAPI
KeReleaseQSpinLock(PKSPIN_LOCK SpinLock)
{
    KSPIN_LOCK SpinLockValue;
    KSPINLOCK_QUEUE_ENTRY QueueEntry, NewEntry;
    PKPRCB FirstWaiter, NextWaiter;
    ULONG64 Previous;

    /* Read the spin lock value */
    SpinLockValue = *SpinLock;

    /* Check if we have waiters */
    if (SpinLockValue == 1)
    {
        /* There are no waiters, so try to unlock */
        SpinLockValue = (ULONG_PTR)InterlockedCompareExchangePointer(SpinLock,
                                                                     NULL),
                                                                     SpinLockValue);

        /* Check for success */
        if (SpinLockValue == 1)
        {
            /* Success, we're done! */
            return;
        }
    }

    /* Mask off the busy bit and get the first waiter */
    FirstWaiter = (PKPRCB)(SpinLockValue & ~1);

    READ_ENTRY(&QueueEntry, FirstWaiter->SpinLockQueue);

    /* Get the next waiter and check if there is any */
    NextWaiter = GET_NEXT_PRCB(&QueueEntry);
    if (NextWaiter == NULL)
    {
        /* Try to reset the first waiter, if no other waiters are there */
        Previous = InterlockedCompareExchange64(&FirstWaiter->SpinLockQueue,
                                                0,
                                                QueueEntry.LongLong);
        /* Check for success */
        if (Previous == QueueEntry.LongLong)
        {
            /* Set acquired state with no waiters */
            *SpinLock = 1;

            /* We're done */
            return;
        }
    }

    /* Write the next waiter as wait list head */
    *SpinLock = (ULONG_PTR)NextWaiter | 1;

    /* Release the first waiter */
    MAKE_ENTRY(NewEntry, NULL, NULL);
    WRITE_ENTRY(&FirstWaiterr->SpinLockQueue, NewEntry);
}


