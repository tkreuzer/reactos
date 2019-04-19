
#include <ntoskrnl.h>
#include "Ke_internal.h"

/*
 * Interrupts / s: ~ 30 - 40 (2Ghz -> every 50-67 Million cycles)
 * Interrupttime: ~ 0.1 - 0.2 %
 * Cycles per interrupt: 2GHz -> 25,000 - 67,000
 * Clock cycles used by the atomic instruction: ~100 (?)
 * Chance of an interrupt during that time: ~ 1 : 200,000

*/

#ifdef _M_AMD64
#define KiIsWaitBlockPointer(Ptr) (((LONG64)(Ptr)) < 0)
#else
#define KiIsWaitBlockPointer(Ptr) ((Ptr) >= MmSystemRangeStart)
#endif

typedef struct _KSNAPLOCK_WAIT_BLOCK *PKSNAPLOCK_WAIT_BLOCK;
typedef struct _KSNAPLOCK_WAIT_BLOCK
{
    PKTHREAD Thread;
    volatile PKSNAPLOCK_WAIT_BLOCK Next;
    volatile PKSNAPLOCK_WAIT_BLOCK Previous;
    volatile PKSNAPLOCK_WAIT_BLOCK First;
    volatile PKSNAPLOCK_WAIT_BLOCK FirstCopy;
    volatile ULONG_PTR Done;
} KSNAPLOCK_WAIT_BLOCK;

typedef struct _KSNAPLOCK
{
    union
    {
        PVOID Ptr;
        struct _KSNAPLOCK_WAIT_BLOCK *WaitBlock;
        ULONG_PTR Long;
        struct
        {
            ULONG_PTR Lock : 1;
            ULONG_PTR ShareCount : 29;
        };
    };
} KSNAPLOCK, *PKSNAPLOCK;

VOID
NTAPI
KeAcquireSnapLockExclusive (
    _In_ PKSNAPLOCK SnapLock )
{
    PKTHREAD CurrentThread;
    volatile KSNAPLOCK_WAIT_BLOCK WaitBlock, *FirstWaitBlock, *LastWaitBlock;
    KIRQL OldIrql;
    KSNAPLOCK LockValue;

    /* Read the lock value */
    LockValue = *SnapLock;

    /* Check if the lock is free */
    if (LockValue.Long == 0)
    {
        /* Try to atomically acquire the lock */
        LockValue.Ptr = InterlockedCompareExchangePointer(&SnapLock->Ptr,
                                                          (PVOID)(ULONG_PTR)1,
                                                          (PVOID)0);
        /* Check for success */
        if (LockValue.Long == 0)
        {
            return;
        }
    }

    /* Lock is busy, we probably need to do a wait, raise to DISPATCH_LEVEL */
    OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

    /* Put this thread into waiting state */
    CurrentThread = KeGetCurrentThread();
    CurrentThread->State = Waiting;

    /* Setup the wait block */
    WaitBlock.Thread = CurrentThread;
    WaitBlock.Next = NULL;
    WaitBlock.First = NULL;
    WaitBlock.FirstCopy = NULL;
    WaitBlock.Previous = &WaitBlock;
    WaitBlock.Done = FALSE;

    /* Since we need to modify the wait block of the previous waiter, that
       one will have to spin until we're done before continuing execution
       after releasing the lock. This is to prevent a race condition,
       removing the wait block from the stack before it is being written to.
       To avoid being interrupted by an interrupt, causing needless spinning
       for the releasing thread, we inhibit all interrupts for a short time. */
    _disable();

    /* Atomically exchange the lock value with a pointer to our wait block */
    LockValue.Ptr = InterlockedExchangePointer(&SnapLock->Ptr, &WaitBlock);

    /* Check if the previous value was a wait block pointer */
    if (KiIsWaitBlockPointer(LockValue.Ptr))
    {
        /* Link the previous wait block */
        WaitBlock.Previous = LockValue.WaitBlock;
        LockValue.WaitBlock->Next = &WaitBlock;

        /* Get the pointer to the first wait block */
        FirstWaitBlock = LockValue.WaitBlock->First;

        /* If it is not set, use the copy of the first wait block pointer */
        if (!FirstWaitBlock)
            WaitBlock.FirstCopy = LockValue.WaitBlock->FirstCopy;

        /* Store the first wait block as our copy */
        WaitBlock.FirstCopy = FirstWaitBlock;

        /* Mark the previous wait block that we don't access it anymore */
        LockValue.WaitBlock->Done = TRUE;
    }
    else
    {
        /* This is the first wait block */
        WaitBlock.First = &WaitBlock;
    }

    _enable();

    /* Check if we got a pointer to the first block already */
    if (!WaitBlock.First)
    {
        /* Loop wait blocks until we get one that knows the first one */
        LastWaitBlock = WaitBlock.Previous;
        while (!LastWaitBlock->First)
        {
            /* Go one back in the queue */
            LastWaitBlock = LastWaitBlock->Previous;
        }

        /* Copy the pointer to the first wait block */
        WaitBlock.First = LastWaitBlock->First;
    }

    /* Check if the lock was still owned when we enqueued */
    if (LockValue.Long != 0)
    {
        /* The lock was still owned, wait to be released */
        KiWaitThread(NULL);
        ASSERT(CurrentThread->State == Running);

        /* Read the current lock value */
        LockValue = *SnapLock;
    }
    else
    {
        /* Otherwise we own the lock now and don't need to wait */
        CurrentThread->State = Running;

        /* This is the new expected value */
        LockValue.Ptr = &WaitBlock;
    }

    /* Check if we are still the last in the queue */
    if (LockValue.Ptr == &WaitBlock)
    {
        /* There are no more waiters, change the lock value back to 1 */
        LockValue.Ptr = InterlockedCompareExchangePointer(&SnapLock->Ptr,
                                                          (PVOID)(ULONG_PTR)1,
                                                          &WaitBlock);
        /* Check if that succeeded */
        if (LockValue.Ptr == &WaitBlock)
        {
            KeLowerIrql(OldIrql);
            return;
        }
    }

    /* This must be a pointer to a wait block now */
    ASSERT(KiIsWaitBlockPointer(LockValue.Ptr));

    /* Finally, we need to make sure that the last waiter's wait block points
     * to the correct first waiter, which is now the next after this one.
     * This value will propagate to the following waiters and we will use it
     * when releasing the lock to wake the next waiter. */

    /* Get pointer to the last wait block */
    LastWaitBlock = LockValue.WaitBlock;
    do
    {
        /* Save the next wait block as the first one */
        LastWaitBlock->First = WaitBlock.Next;

        /* Get the next wait block. If it is set, another thread has started
           the enqueuing procedure and might have read the old pointer to the
           first wait block, so we need to repeat. */
        LastWaitBlock = LastWaitBlock->Next;
    } while (LastWaitBlock);

    /* The Next field of the last wait block is NULL, so there is either no
       more wait block enqueued or it has not yet updated it's First member */

    KeLowerIrql(OldIrql);

    /* Another thread has enqueued behind us, that thread accesses our
       wait block, so we need to wait, until that is finished */
    while (!WaitBlock.Done) YieldProcessor();
}

VOID
NTAPI
KeReleaseSnapLockExclusive(
    _In_ PKSNAPLOCK SnapLock)
{
    //PKTHREAD CurrentThread;
    PKSNAPLOCK_WAIT_BLOCK WaitBlock, FirstWaitBlock;
    KSNAPLOCK LockValue, NewValue, OldValue;

    /* Read the lock value */
    LockValue = *SnapLock;

    /* Check if the lock is owned exclusively without waiters */
    if (LockValue.Long == 1)
    {
        /* Try to atomically release the lock */
        LockValue.Ptr = InterlockedCompareExchangePointer(&SnapLock->Ptr,
                                                          (PVOID)0,
                                                          (PVOID)(ULONG_PTR)1);
        /* Check for success */
        if (LockValue.Long == 1)
        {
            return;
        }
    }
    else
    {
        /* If it's not a wait block pointer, it must be shared */
        while (!KiIsWaitBlockPointer(LockValue.Ptr))
        {
            NewValue = OldValue = LockValue;
            NewValue.ShareCount--;

            /* Try to atomically acquire the lock */
            LockValue.Ptr = InterlockedCompareExchangePointer(&SnapLock->Ptr,
                                                              NewValue.Ptr,
                                                              LockValue.Ptr);
            /* Check for success */
            if (LockValue.Long == OldValue.Long)
            {
                return;
            }
        }
    }

    /* We must have a wait block pointer now */
    ASSERT(KiIsWaitBlockPointer(LockValue.Ptr));

    /* Get pointer to the last wait block */
    WaitBlock = LockValue.WaitBlock;

    /* Loop wait blocks until we get one that knows the first one */
    while (TRUE)
    {
        /* Check if the wait block knows the first block */
        FirstWaitBlock = WaitBlock->First;
        if (FirstWaitBlock) break;

        /* Otherwise check the copied field */
        FirstWaitBlock = WaitBlock->FirstCopy;
        if (FirstWaitBlock) break;

        /* Go one back in the queue */
        WaitBlock = WaitBlock->Previous;
    }



    WaitBlock->Previous = WaitBlock;

}


