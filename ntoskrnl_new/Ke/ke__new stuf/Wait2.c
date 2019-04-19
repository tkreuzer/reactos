
#include <ntoskrnl.h>
#include "Ke_internal.h"
#include "Wait.h"

/*

since there is no way for the signalling thread to know, whether the waiting
thread has even begun it's wait on the object, the object cannot be freed,
before the waiting thread has returned from the wait.

TODO: Try to spin on the WaitBlock instead of on the dispatcher header, to
reduce contention. To notify the waiting thread, a release would require to
loop the object's wait list, until a waiter spinning on it is found and then
release the waitblock, passing the lock to the spinning one or signalling the
spinning thread that the object was signalled and thus the wait should be
aborted. The spinning thread will receive exactly either of these.

-> set WaitBlockBypassStart and spin until it changes
-> set WaitBlockBypassComplete to signal that the lock is passed on
-> set WaitBlockInactive to signal that the wait is to be aborted
-> block state is not changed by any thread not holding the lock on the object

This mechanism will prefer waiters that are already enqueued over waiters that
want to enqueue. This is good, since the former has already completed it's
wait and can continue. Also threads that had the wait block enqueued earlier
are preferred over those that enqueued it later. This is not a problem, since
the former will remove it's entry anyway.

TODO:
If the thread is in a usermode wait the kernel stack is swappable, so we need
to enqueue the waiting thread into the PRCs waitListHead


NEW:
- loop all -> lock object, entweder enqueue oder interlocked dec, unlock

- on signal and reset, lock object, loop all waiters, atomic increment/decremt
  of the waitcount. reset = InterlockedIncrement, bugcheck when too large
  set = interlockedDecrement?
  if waitcount -> 0, lock thread,


- use 2 locks on the dispatcher header: 1 list lock, that is acquired when
  changing or enumerating the list (shared would be good, but possibly not
  doable) and one lock for designalling, which is necessary when

- Thread 0 waits for object A and B (A is signaled)
- Thread 1 signals object B
    - Thread 1 acquries list lock on object B
    - Thread 1 decrements waitcount of Thread 0 to 0

- Thread 2 waits for object A and B
    - Thread 2 acquires double lock on object A
    - Thread 2 blocks on object B (list lock)

    - Thread 1 acquires signal lock for all of Thread 0's objects (in sorted order)
    - Thread 1 blocks on object A (double lock)
        => wakes thread 0 for self check
    - Thread 1 unlocks all of threaf 0's objects and continues with next waiter


- Thread 2 signals object B
    - Thread 2 acquires list lock on object B
    - Thread 2 decrements waitcount of Thread 3 to 0
    - Thread 2 acquires signal lock on all of Thread 3's objects

- seperate version for WaitAny and WaitAll, the former used inlined for
    WaitForSingleObject

*/

#define IsSynchronisationObject() 1


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
    do
    {
        while (DispatcherHeader->Lock & DH_LOCK_MASK) YieldProcessor();

    } while (InterlockedBitTestAndSet(&DispatcherHeader->Lock, DH_LOCK_BIT));
}

VOID
FORCEINLINE
KiLockDispatcherObjectWithWaitBlock(
  __inout PDISPATCHER_HEADER DispatcherHeader,
  __inout PKWAIT_BLOCK WaitBlock)
{

    ASSERT(WaitBlock->BlockState == WaitBlockActive);

    WaitBlock->BlockState = WaitBlockBypassStart;
    KeMemoryBarrierWithoutFence();

    if (!(DispatcherHeader->Lock & DH_LOCK_MASK))
    {
        if (!InterlockedBitTestAndSet(&DispatcherHeader->Lock, DH_LOCK_BIT))
        {
            WaitBlock->BlockState = WaitBlockActive;
            return;
        }
    }

    while (WaitBlock->BlockState == WaitBlockBypassStart) YieldProcessor();

}


VOID
FORCEINLINE
KiUnlockDispatcherObject(
  __inout PDISPATCHER_HEADER DispatcherHeader)
{
    PLIST_ENTRY ListEntry;
    PKWAIT_BLOCK WaitBlock;

    /* Loop the wait list */
    for (ListEntry = &DispatcherHeader->WaitListHead;
         ListEntry != &DispatcherHeader->WaitListHead;
         ListEntry = ListEntry->Flink)
    {
        /* Get a pointer to the wait block */
        WaitBlock = CONTAINING_RECORD(ListEntry, KWAIT_BLOCK, WaitListEntry);

        /* Check if this wait block is being spinned on */
        if (WaitBlock->BlockState == WaitBlockBypassStart)
        {
            /* Signal the spinning thread, that it now owns the lock */
            WaitBlock->BlockState = WaitBlockBypassComplete;

            /* Done. */
            return;
        }
    }

    /* No waiting thread was found, do a normal unlock */
    KeMemoryBarrierWithoutFence();
    DispatcherHeader->Lock &= ~DH_LOCK_MASK;
}

BOOLEAN
FORCEINLINE
KiTryAcquireObject(
  __inout PDISPATCHER_HEADER DispatcherHeader)
{
    LONG SignalState;

    SignalState = DispatcherHeader->SignalState;
    if (!IsSynchronisationObject(DispatcherHeader))
    {
        return (SignalState == 0);
    }
#ifdef CONFIG_SMP
    do
    {
        if (SignalState == 0) return FALSE;

        NewState = SignalState - 1;
        SignalState = InterlockedCompareExchange(&DispatcherHeader->SignalState,
                                              NewState,
                                              SignalState);

    } while (SignalState != NewState + 1);
#else
    DispatcherHeader->SignalState--;
#endif
    return TRUE;
}

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
    PKTHREAD CurrentThread;
    PDISPATCHER_HEADER DispatcherHeader;
    PKWAIT_BLOCK WaitBlock;
    ULONG i;

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
    else if (Count > MAX_WAIT_OBJECTS)
    {
        /* Bugcheck the system! */
        KeBugCheck(MAXIMUM_WAIT_OBJECTS_EXCEEDED);
    }

    /* Save pointer to the wait block array */
    Thread->WaitBlockList = WaitBlockArray;

    /* This is how many waits must be satisfied */
    WaitCount = (WaitType == WaitAll) ? Count : 1;
    Thread->WaitStatus = WaitCount;

    /* Before we enqueue any wait block, we need to initialize all of them,
       so that a cleanup operation doesn't work on bogus data */
    for (i = 0; i < Count; i++)
    {
        /* Initialize the wait block */
        WaitBlock = &WaitBlockArray[i];
        WaitBlock->WaitType = WaitType;
        WaitBlock->BlockState = WaitBlockInactive;
        WaitBlock->WaitKey = (Count - 1) - i;
        WaitBlock->Thread = CurrentThread;
        WaitBlock->Object = DispatcherHeader;
    }

    /* Check if IRQL is already raised */
    if (Thread->WaitNext)
    {
        /* The previous IRQL is stored in the thread */
        OldIrql = Thread->WaitIrql;
    }
    else
    {
        OldIrql = KeRaiseIrqlToDpcLevel();
    }

    Thread->State = Waiting;

    for (i = 0; i < Count; i++)
    {
        WaitBlock = &WaitBlockArray[i];
        DispatcherHeader = Object[i];

        /* Try a quick acquire without locking */
        if (!KiTryAcquireObject(DispatcherHeader))
        {
            /* Acquire an exclusive lock on the dispatcher object.
               This will prevent the object from becoming signaled */
            KiLockDispatcherObject(DispatcherHeader);

            /* Check again, if the object is still unsignaled */
            if (!KiTryAcquireObject(DispatcherHeader))
            {
                /* Check if this wait block is still valid */
                if (WaitBlock->Object == DispatcherHeader)  // doewsn't make sense!
                {
                    /* Enqueue the wait block and activate it */
                    InsertTailList(&DispatcherHeader->WaitListHead,
                                   &WaitBlock->WaitListEntry);
                    WaitBlock->BlockState = WaitBlockActive;

                    /* Unlock this object */
                    KiUnlockDispatcherObject(DispatcherHeader);

                    /* Continue with next object */
                    continue;
                }

                /* The wait was already satisfied by another thread */
                ASSERT(WaitBlock->Object == NULL);
            }

            /* Unlock this object */
            KiUnlockDispatcherObject(DispatcherHeader);
        }

        /* Check if all waits must be satisfied */
        if (WaitType == WaitAll)
        {
            /* This one is satisfied, decrement the count */
            WaitCount = KiDecrementThreadWaitCount(Thread);

            /* Check if we have waiters left */
            if (WaitCount != 0)
            {
                continue;
            }

            /* On WaitAll we return STATUS_SUCCESS */
            Thread->WaitStatus = STATUS_SUCCESS;
        }
        else
        {
            /* A wait was satisfied, set the key */
            // FIXME: another object might have been signalled earlier
            // and we need to decide whether this one was the first or not
            Thread->WaitStatus = WaitBlock->WaitKey;
        }

        /* At this point all waits are satisfied */
        Thread->State = Running;
        goto Cleanup;
    }


    KeSwapThread()

Cleanup:

    /* Last wait was satisfied, now release all remaining wait blocks */
    WaitBlock = Thread->WaitBlockList;
    do
    {
        /* Get the object from the wait block. If this is NULL, the wait
           block was already unlinked and we have nothing to do here */
        DispatcherHeader = WaitBlock->Object;
        if (DispatcherHeader)
        {
            /* Now try to lock the object, but break out, if it is
               signalled by another thread to prevent a deadlock */
            if (KiLockDispatcherObjectBreakOnSignal(DispatcherHeader))
            {

                if (WaitBlock->BlockState == WaitBlockActive)
                {
                    RemoveEntryList(&WaitBlock->WaitListEntry);
                }

                WaitBlock->Object = NULL;
                WaitBlock->BlockState = WaitBlockBypassStart;
                KiUnlockDispatcherObject(DispatcherHeader);
            }
        }
    } while ((WaitBlock++)->WaitKey > 0)

#ifdef DBG
    /* Make sure all wait blocks are released */
    for (i = 0; i < Count; i++)
    {
        ASSERT(WaitBlockArray[i].BlockState == WaitBlockInactive);
        ASSERT(WaitBlockArray[i].WaitListEntry.Flink == NULL);
        ASSERT(WaitBlockArray[i].WaitListEntry.Blink == NULL);
    }
#endif

}

KiRetireWaitBlockList(PKWAIT_BLOCK WaitBlockList)
{

}


VOID
FORCEINLINE
KiSignalThread(
    PKTHREAD Thread,
    LONG WaitKey,
    KPRIORITY PriorityIncrement)
{
    WaitCount = InterlockedDecrement(&Thread->WaitStatus); // ... or something
    if (WaitCount == 0)
    {
        /* All neccessary waits are satisfied, now set the wait result
           and make the thread ready */
        Thread->WaitStatus = WaitBlock->WaitKey;
        KiReadyThread(Thread, PriorityIncrement);
    }

}

LONG
NTAPI
KiSignalObject(
    PDISPATCHER_HEADER DispatcherHeader,
    BOOLEAN WakeAll,
    KPRIORITY PriorityIncrement)
{
    LIST_ENTRY ListEntry;
    PKWAIT_BLOCK WaitBlock;
    LONG OldState;
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

    /* Lock the object exclusively */
    KiLockDispatcherObject(DispatcherHeader);

    OldState = DispatcherHeader->SignalState;
    DispatcherHeader->SignalState = 1;

    do
    {
        /* Remove the top entry from the wait list */
        ListEntry = RemoveHeadList(&DispatcherHeader->WaitListHead);
        if (!ListEntry)
        {
            /* No more waiters, done. */
            break;
        }

        /* Get pointer to the wait block and make sure it's in a sane state */
        WaitBlock = CONTAINING_RECORD(ListEntry, KWAIT_BLOCK, WaitListEntry);
        ASSERT(WaitBlock->Object == DispatcherHeader);
        ASSERT(WaitBlock->BlockState == WaitBlockActive);

        // FIXME: check if thread is in a kernel APC

        /* Reset the wait block, so that it can be skipped from now on */
        WaitBlock->Object = NULL;
        WaitBlock->BlockState = WaitBlockInactive;

        /* Signal the waiting thread */
        KiSignalThread(WaitBlock->Thread, WaitBlock->WaitKey, PriorityIncrement);

        /* When the thread is in WaitAll mode, we continue */
    } while (WakeAll || (WaitBlock->WaitType == WaitAll))

    /* Unlock the object */
    KiUnlockDispatcherObject(DispatcherHeader);

    return OldState;
}

NTSTATUS
NTAOI
KeWaitForMutexObject(
    IN PRKMUTEX  Mutex,
    IN KWAIT_REASON  WaitReason,
    IN KPROCESSOR_MODE  WaitMode,
    IN BOOLEAN  Alertable,
    IN PLARGE_INTEGER  Timeout  OPTIONAL)
{
    __debugbreak();
}

NTSTATUS
NTAPI
KeDelayExecutionThread(
    IN KPROCESSOR_MODE WaitMode,
    IN BOOLEAN Alertable,
    IN PLARGE_INTEGER Interval)
{
    __debugbreak();
}




Thread A                    Thread B
---------------------------------------------------------
lock obj0
signal obj0

                            lock obj1
                            signal obj1

flush waitlist
    lock obj1 / break

