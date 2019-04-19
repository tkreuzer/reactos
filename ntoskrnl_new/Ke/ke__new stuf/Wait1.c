
#include <ntoskrnl.h>
#include "Ke_internal.h"

/* Private types **************************************************************/

typedef enum _KWAIT_BLOCK_STATE
{
    WaitBlockBypassStart    = 0,
    WaitBlockBypassComplete = 1,
    WaitBlockActive         = 2,
    WaitBlockInactive       = 3,
    WaitBlockAllStates      = 4
} KWAIT_BLOCK_STATE, *PKWAIT_BLOCK_STATE;

#define TIMER_WAIT_BLOCK THREAD_WAIT_OBJECTS


/* Private functions **********************************************************/

/*!
 *  \remarks This function is used if no wait block is present that is already
 *      enqueued in the object's wait list. If an enqueued wait block is given,
 *      KiLockDispatcherObjectBreakOnSignal() is used, which spins on the
 *      wait block to reduce contention.
 */
VOID
FORCEINLINE
KiLockDispatcherObject(
  __inout PDISPATCHER_HEADER DispatcherHeader)
{
    SPINLOCK_ACQUIRE(Dispatcher);
    do
    {
        while (DispatcherHeader->Lock & DH_LOCK_MASK) YieldProcessor();

    } while (InterlockedBitTestAndSet(&DispatcherHeader->Lock, DH_LOCK_BIT));
}

VOID
FORCEINLINE
KiUnlockDispatcherObject(
  __inout PDISPATCHER_HEADER DispatcherHeader)
{
    SPINLOCK_RELEASE(Dispatcher);
    DispatcherHeader->Lock = DispatcherHeader->Lock & ~DH_LOCK_MASK;
    KeMemoryBarrierWithoutFence();
}

BOOLEAN
FORCEINLINE
KiLockDispatcherObjectIfWaitBlockActive(
    __inout PDISPATCHER_HEADER DispatcherHeader,
    __in PKWAIT_BLOCK WaitBlock)
{
    /* Debugging, do it here, because we might unlock again later */
    SPINLOCK_ACQUIRE(Dispatcher);

    do
    {
        while (DispatcherHeader->Lock & DH_LOCK_MASK)
        {
            if (WaitBlock->BlockState != WaitBlockActive)
            {
                SPINLOCK_RELEASE(Dispatcher);
                return FALSE;
            }

            YieldProcessor();
        }

    } while (InterlockedBitTestAndSet(&DispatcherHeader->Lock, DH_LOCK_BIT));

    /* Check again, to be sure */
    if (WaitBlock->BlockState != WaitBlockActive)
    {
        KiUnlockDispatcherObject(DispatcherHeader);
        return FALSE;
    }

    return TRUE;
}

BOOLEAN
FORCEINLINE
IsSynchronisationObject(
    __inout DISPATCHER_HEADER *DispatcherHeader)
{
    UCHAR Type = DispatcherHeader->Type & ~DH_LOCK_MASK;
    return ((Type == SemaphoreObject) || (Type ==  MutantObject) ||
            ((Type & 7) == EventSynchronizationObject));
}

VOID
FORCEINLINE
KiAcquireDispatcherObjectLocked(
    __inout DISPATCHER_HEADER *DispatcherHeader)
{
    if (IsSynchronisationObject(DispatcherHeader))
    {
        DispatcherHeader->SignalState--;
    }
}

BOOLEAN
FORCEINLINE
TryAcquireDispatcherObject(
    PDISPATCHER_HEADER DispatcherHeader)
{
    LONG SignalState, NewState;

    /* First check the current state of the object */
    if (DispatcherHeader->SignalState <= 0) return FALSE;

    /* Nothing more to do for non-synchronization objects */
    if (!IsSynchronisationObject(DispatcherHeader)) return TRUE;

    /* Get the current signal state */
    SignalState = DispatcherHeader->SignalState;

    // FIXME: for semaphores we need this, but for others we can use
    // InterlockedBitTestAndReset without a loop

    do
    {
        /* Fail, if the object is not signaled */
        if (SignalState <= 0) return FALSE;

        /* Try to set new, decreased state */
        NewState = SignalState - 1;
        SignalState = InterlockedCompareExchange(&DispatcherHeader->SignalState,
                                                 NewState,
                                                 SignalState);
    }
    while (SignalState != NewState + 1);

    return TRUE;
}

NTSTATUS
NTAPI
KiWaitThread(
    __in PKTIMER TimeoutTimer)
{
    PKTHREAD NextThread, CurrentThread = KeGetCurrentThread();
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);
    ASSERT(CurrentThread->State == Waiting);

    /* Check for expired timer */
    if (TimeoutTimer && (TimeoutTimer->Header.SignalState > 0))
    {
        return STATUS_TIMEOUT;
    }

    NextThread = KiGetNextReadyThread();

    KiSwapThread(NextThread);

    return (NTSTATUS)CurrentThread->WaitStatus;
}

/*!
 * \remarks The sorting algorithm is a variant of selectsort, a very simple
 *      algorithm, similar to bubblesort. Fo the expectedly low number of
 *      elements, the overhead of morecomplex algorithms is not justified
 *      by possible better runtime.
 */
VOID
FORCEINLINE
KiSortWaitBlockObjects(
    __out PKWAIT_BLOCK WaitBlockArray,
    __in PVOID Object[],
    __in ULONG Count)
{
    PKWAIT_BLOCK WaitBlock;
    USHORT i, j;
    ULONG_PTR Value, Margin = MAXULONG_PTR;

    /* Loop all wait blocks */
    for (i = 0; i < Count; i++)
    {
        /* Initialize the wait block */
        WaitBlock = &WaitBlockArray[i];
        WaitBlock->WaitType = WaitAny;
        WaitBlock->Object = NULL;
        WaitBlock->Thread = KeGetCurrentThread();
        WaitBlock->BlockState = WaitBlockInactive;

        /* Loop all objects to find the next */
        for (j = 0; j < Count; j++)
        {
            /* Use the object pointer as sort value */
            Value = (ULONG_PTR)Object[j];

            /* Check if the value is in the range that is not yet assigned */
            if (Value < Margin)
            {
                /* Check if it's the higest value of the current iteration */
                if (Value > (ULONG_PTR)WaitBlock->Object)
                {
                    /* Assign the pointer and save the object index */
                    WaitBlock->Object = (PVOID)Value;
                    WaitBlock->WaitKey = j;
                }
            }
        }

        /* Set the margin to the highest value we found */
        Margin = (ULONG_PTR)WaitBlock->Object;
    }
}

PKTIMER
FORCEINLINE
KiHandleTimeout(
    __in PLARGE_INTEGER Timeout)
{
    PKTHREAD CurrentThread = KeGetCurrentThread();
    PKTIMER Timer;
    PKWAIT_BLOCK WaitBlock;

    if (Timeout)
    {
        /* Use the thread's own timer and initialize it */
        Timer = &CurrentThread->Timer;
        KeInitializeTimer(Timer);

        if (Timeout->QuadPart == 0)
        {
            /* Emulate a timer that is already expired */
            Timer->Header.SignalState = 1;
        }
        else
        {
            /* Get the internal timer wait block and initialize it */
            WaitBlock = &CurrentThread->WaitBlock[TIMER_WAIT_BLOCK];
            WaitBlock->WaitType = WaitAny;
            WaitBlock->Object = Timer;
            WaitBlock->WaitKey = STATUS_TIMEOUT;
            WaitBlock->Thread = CurrentThread;

            /* Insert the wait block into the timer's wait list */
            InsertTailList(&Timer->Header.WaitListHead,
                           &WaitBlock->WaitListEntry);

            KeSetTimer(Timer, *Timeout, NULL);
        }
    }
    else
    {
        Timer = NULL;
    }

    return Timer;
}


NTSTATUS
FORCEINLINE
KiWaitForAnyObject(
    __in ULONG Count,
    __in PVOID Object[],
    __inout PKWAIT_BLOCK WaitBlockArray,
    __in PLARGE_INTEGER Timeout)
{
    DISPATCHER_HEADER *DispatcherHeader;
    PKWAIT_BLOCK WaitBlock;
    PKTHREAD CurrentThread;
    PKTIMER TimeoutTimer;
    NTSTATUS Status;
    USHORT Index;

    /* Get the current thread */
    CurrentThread = KeGetCurrentThread();

    /* Loop all objects in given order */
    for (Index = 0; Index < Count; Index++)
    {
        /* Try to atomically acquire this object */
        if (TryAcquireDispatcherObject(Object[Index]))
        {
            /* Check if IRQL was raised already */
            if (CurrentThread->WaitNext)
            {
                KeLowerIrql(CurrentThread->WaitIrql);
            }

            /* Return the object's key */
            return Index;
        }
    }

    /* If the timeout value is 0, the operation timed out now */
    if (Timeout && Timeout->QuadPart == 0) return STATUS_TIMEOUT;

    /* Setup the timeout timer */
    TimeoutTimer = KiHandleTimeout(Timeout);

    /* Initialize the wait blocks */
    for (Index = 0; Index < Count; Index++)
    {
        WaitBlock = &WaitBlockArray[Index];
        WaitBlock->WaitType = WaitAny;
        WaitBlock->Object = NULL;
        WaitBlock->WaitKey = Index;
        WaitBlock->Thread = CurrentThread;
        WaitBlock->BlockState = WaitBlockInactive;
    }

    /* Check if we need to raise IRQL */
    if (!CurrentThread->WaitNext)
    {
        /* Raise IRQL and save the old value */
        CurrentThread->WaitIrql = KfRaiseIrql(DISPATCH_LEVEL);
    }

    while (TRUE)
    {
        /* Not successful yet */
        Status = STATUS_UNSUCCESSFUL;

        /* Put the thread into waiting state */
        CurrentThread->State = Waiting;

        /* Loop all objects in given order again */
        for (Index = 0; Index < Count; Index++)
        {
            /* Get the wait block and check if it's active (enqueued into the
               dispatcher header). If it is, we can skip the next steps and
               continue with the next wait block */
            WaitBlock = &WaitBlockArray[Index];
            if (WaitBlock->BlockState == WaitBlockActive) continue;

            /* Lock the dispatcher object */
            DispatcherHeader = Object[Index];
            KiLockDispatcherObject(DispatcherHeader);

            /* Check, if the object is signaled now */
            if (DispatcherHeader->SignalState > 0)
            {
                /* Acquire the object, if applicable */
                KiAcquireDispatcherObjectLocked(DispatcherHeader);

                /* Unlock the object */
                KiUnlockDispatcherObject(DispatcherHeader);

                /* Set STATUS_WAIT_X and break out of the loop */
                Status = Index;
                break;
            }

            /* Check if the wait block is still not active */
            if (WaitBlock->BlockState != WaitBlockActive)
            {
                /* Insert the wait block into the object's wait list */
                InsertTailList(&DispatcherHeader->WaitListHead,
                               &WaitBlock->WaitListEntry);

                /* Activate the wait block */
                WaitBlock->Object = DispatcherHeader;
                WaitBlock->BlockState = WaitBlockActive;

                /* Special case mutant */
                if (DispatcherHeader->Type == MutantObject)
                {
                    PKMUTANT Mutant = (PKMUTANT)DispatcherHeader;

                    /* Boost owner priority to current thread's priority */
                    KiBoostPriorityThread(Mutant->OwnerThread,
                                          CurrentThread->BasePriority);
                }
            }

            /* Unlock the dispatcher object and continue */
            KiUnlockDispatcherObject(DispatcherHeader);
        }

        /* Check if we had success already */
        if (NT_SUCCESS(Status)) break;

        /* Wait for the objects */
        Status = KiWaitThread(TimeoutTimer);

        if (Status == STATUS_TIMEOUT) break;

        // FIXME: check for alerted thread

        /* At this point we must have a STATUS_WAIT_X */
        ASSERT((ULONG)Status < Count);
        DispatcherHeader = Object[Status];

        /* Try to atomically acquire this object */
        if (TryAcquireDispatcherObject(DispatcherHeader)) break;

        /* If we got here, we were woken up by a signaled synchronization
           object and a concurrent thread, which was doing a WaitAll was
           woken before this thread and managed to acquire the object first.
           So we need to repeat the whole process */
    }

    /* Loop all objects in given order again */
    for (Index = 0; Index < Count; Index++)
    {
        /* Get the wait block and dispatcher header */
        WaitBlock = &WaitBlockArray[Index];
        DispatcherHeader = WaitBlock->Object;

        /* If the object pointer is not set, the wait block is unused and
           the previous loop ended before this object. */
        if (!DispatcherHeader) break;

        /* Lock the dispatcher object, bail out on inactive wait block */
        if (KiLockDispatcherObjectIfWaitBlockActive(DispatcherHeader, WaitBlock))
        {
            /* Remove the entry */
            RemoveEntryList(&WaitBlock->WaitListEntry);

            /* Unlock the dispatcher object */
            KiUnlockDispatcherObject(DispatcherHeader);
        }
    }

    /* Lower IRQL back to previous value */
    KeLowerIrql(CurrentThread->WaitIrql);

    /* Cancel the timeout timer, if any */
    if (TimeoutTimer) KeCancelTimer(TimeoutTimer);

    return Status;
}


NTSTATUS
FORCEINLINE
KiWaitForAllObjects(
    __in ULONG Count,
    __in PVOID Object[],
    __inout PKWAIT_BLOCK WaitBlockArray,
    __in PLARGE_INTEGER Timeout)
{
    PKTHREAD CurrentThread = KeGetCurrentThread();
    ULONG Index, StartIndex;
    PKWAIT_BLOCK WaitBlock;
    DISPATCHER_HEADER *DispatcherHeader;
    PKTIMER TimeoutTimer = NULL;
    NTSTATUS Status;

    /* Sort all objects to prevent dead locks, when locking them */
    KiSortWaitBlockObjects(WaitBlockArray, Object, Count);

    /* Setup the timeout timer */
    TimeoutTimer = KiHandleTimeout(Timeout);

    if (!CurrentThread->WaitNext)
    {
        CurrentThread->WaitIrql = KfRaiseIrql(DISPATCH_LEVEL);
    }

    while (TRUE)
    {
        /* Loop all wait blocks, starting with index 0 */
        Index = StartIndex = 0;
        do
        {
            /* Get the wait block and dispatcher header */
            WaitBlock = &WaitBlockArray[Index];
            DispatcherHeader = WaitBlock->Object;

            /* Check if the object is unsignaled */
            if (DispatcherHeader->SignalState <= 0)
            {
                /* Lock the dispatcher object */
                KiLockDispatcherObject(DispatcherHeader);

                /* Now that the object is locked, check the state again */
                if (DispatcherHeader->SignalState <= 0)
                {
                    /* Set waiting state before the object is enqueued */
                    KeGetCurrentThread()->State = Waiting;

                    /* Insert the wait block into the object's wait list */
                    InsertTailList(&DispatcherHeader->WaitListHead,
                                   &WaitBlock->WaitListEntry);

                    /* Unlock the dispatcher object */
                    KiUnlockDispatcherObject(DispatcherHeader);

                    /* Wait until the object gets signaled */
                    Status = KiWaitThread(TimeoutTimer);

                    if (Status == STATUS_TIMEOUT)
                    {
                        /* Lower IRQL back to previous value */
                        KeLowerIrql(CurrentThread->WaitIrql);

                        return Status;
                    }

                    // FIXME: handle alerted thread

                    /* Restart the looping at this point */
                    StartIndex = Index;
                }
                else
                {
                    /* Just unlock the dispatcher object */
                    KiUnlockDispatcherObject(DispatcherHeader);
                }
            }

            /* Go to next wait index */
            Index++;
            if (Index == Count) Index = 0;

        /* Continue, while we haven't checked all objects in a single run */
        } while (Index != StartIndex);

        /* Loop all wait blocks in sorted order again */
        Index = 0;
        while (TRUE)
        {
            /* Get the wait block and dispatcher header */
            WaitBlock = &WaitBlockArray[Index];
            DispatcherHeader = WaitBlock->Object;

            /* Lock the dispatcher object */
            KiLockDispatcherObject(DispatcherHeader);

            /* Bail out, if the object is not signaled anymore */
            if (DispatcherHeader->SignalState <= 0) break;

            Index++;

            /* Check if all objects are locked and signaled now */
            if (Index == Count)
            {
                /* Loop all objects a last time */
                while (Index--)
                {
                    /* Get the wait block and dispatcher header */
                    WaitBlock = &WaitBlockArray[Index];
                    DispatcherHeader = WaitBlock->Object;

                    /* Acquire the object */
                    KiAcquireDispatcherObjectLocked(DispatcherHeader);

                    /* Unlock the dispatcher object */
                    KiUnlockDispatcherObject(DispatcherHeader);
                }

                /* Lower IRQL back to previous value */
                KeLowerIrql(CurrentThread->WaitIrql);

                /* Cancel the timeout timer, if any */
                if (TimeoutTimer) KeCancelTimer(TimeoutTimer);

                /* Success */
                return STATUS_SUCCESS;
            }
        }

        /* An object was not signalled, unlock all objects */
        do
        {
            /* Unlock this dispatcher object */
            KiUnlockDispatcherObject(WaitBlockArray[Index].Object);
        }
        while (--Index);

        /* Repeat from the beginning */
    }
}

LONG
NTAPI
KiSignalObject(
    PDISPATCHER_HEADER DispatcherHeader,
    BOOLEAN WakeAll,
    KPRIORITY PriorityIncrement)
{
    PKWAIT_BLOCK WaitBlock;
    PLIST_ENTRY ListEntry;
    KIRQL OldIrql;

    /* Raise irql to dispatch level */
    OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

    /* Lock the object */
    KiLockDispatcherObject(DispatcherHeader);

    while (TRUE)
    {
        /* Remove the head entry from the list */
        ListEntry = RemoveHeadList(&DispatcherHeader->WaitListHead);

        /* Bail out, if there are no more waiters */
        if (ListEntry == &DispatcherHeader->WaitListHead) break;

        /* Get pointer to the wait block */
        WaitBlock = CONTAINING_RECORD(ListEntry, KWAIT_BLOCK, WaitListEntry);

        /* Sanity check */
        ASSERT(WaitBlock->BlockState == WaitBlockActive);

        /* Set the wait blocks state to inactive. This way the thread
           can avoid locking the dispatcher object again to dequeue itself */
        WaitBlock->BlockState = WaitBlockInactive;

        /* Wake the thread */
        KiReadyThread(WaitBlock->Thread, WaitBlock->WaitKey);

        /* Check if we only need to wake one waiter */
        if (!WakeAll)
        {
            /* If this is a wait for multiple objects at once (WaitAll), then
               we don't know if the wait will be satisfied now, so we need to
               continue and wake more threads, otherwise if this is a WaitAny,
               we can be sure the wait is satisfied and we are done now. */
            if (WaitBlock->WaitType == WaitAny) break;
        }
    }

    /* Unlock the object */
    KiUnlockDispatcherObject(DispatcherHeader);

    // check if we now have a higher priority thread to run
    //NextThread = KiGetNextThread();
    //if (

    /* Restore old irql */
    KeLowerIrql(OldIrql);

    return 0;
}

#define MAXIMUM_WAIT_OBJECTS_EXCEEDED 0

NTSTATUS
NTAPI
KeWaitForMultipleObjects(
  __in       ULONG Count,
  __in       PVOID Object[],
  __in       WAIT_TYPE WaitType,
  __in       KWAIT_REASON WaitReason,
  __in       KPROCESSOR_MODE WaitMode,
  __in       BOOLEAN Alertable,
  __in_opt   PLARGE_INTEGER Timeout,
  __out_opt  PKWAIT_BLOCK WaitBlockArray)
{
    PKTHREAD CurrentThread = KeGetCurrentThread();
    NTSTATUS Status;

    /* Check if the caller provided a wait block array */
    if (WaitBlockArray == NULL)
    {
        /* Check if there are more objects than we have wait blocks */
        if (Count > THREAD_WAIT_OBJECTS)
        {
            /* Bugcheck the system! */
            KeBugCheck(MAXIMUM_WAIT_OBJECTS_EXCEEDED);
        }

        /* Use the thread's own wait block array */
        WaitBlockArray = CurrentThread->WaitBlock;
    }
    else if (Count > MAXIMUM_WAIT_OBJECTS)
    {
        /* Bugcheck the system! */
        KeBugCheck(MAXIMUM_WAIT_OBJECTS_EXCEEDED);
    }

    /* Save pointer to the wait block array */
    CurrentThread->WaitBlockList = WaitBlockArray;

    /* Save wait parameters */
    CurrentThread->WaitReason = WaitReason;
    CurrentThread->WaitMode = WaitMode;
    CurrentThread->Alertable = Alertable;

    if (WaitType == WaitAll)
    {
        Status = KiWaitForAllObjects(Count, Object, WaitBlockArray, Timeout);
    }
    else
    {
        Status = KiWaitForAnyObject(Count, Object, WaitBlockArray, Timeout);
    }

    /* Set running state again */
    CurrentThread->State = Running;

    CurrentThread->WaitNext = FALSE;

    return 0;
}

NTSTATUS
NTAPI
KeWaitForSingleObject(
    __in PVOID Object,
    __in KWAIT_REASON WaitReason,
    __in KPROCESSOR_MODE WaitMode,
    __in BOOLEAN Alertable,
    __in_opt PLARGE_INTEGER Timeout)
{
    PKTHREAD Thread = KeGetCurrentThread();
    NTSTATUS Status;

    /* Save wait parameters */
    Thread->WaitReason = WaitReason;
    Thread->WaitMode = WaitMode;
    Thread->Alertable = Alertable;

    Status = KiWaitForAnyObject(1, &Object, &Thread->WaitBlock[0], Timeout);

    /* Lower IRQL back to old value */
    KeLowerIrql(Thread->WaitIrql);

    Thread->WaitNext = FALSE;

    return 0;
}

NTSTATUS
NTAPI
KeDelayExecutionThread(
    IN KPROCESSOR_MODE WaitMode,
    IN BOOLEAN Alertable,
    IN PLARGE_INTEGER Interval)
{
    PKTHREAD Thread = KeGetCurrentThread();
    NTSTATUS Status;

    do
    {
        /* Wait for ourselves, use the Interval as timeout value */
        Status = KeWaitForSingleObject(Thread,
                                       WrKernel,
                                       WaitMode,
                                       Alertable,
                                       Interval);

    } while (Status != STATUS_TIMEOUT);

    return STATUS_SUCCESS;
}

