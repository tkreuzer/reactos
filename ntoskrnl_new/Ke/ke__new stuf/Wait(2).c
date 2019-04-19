

#include <ntifs.h>

typedef enum _KOBJECTS  // 26 elements, 0x4 bytes
{
    EventNotificationObject    = 0 /*0x0*/,
    EventSynchronizationObject = 1 /*0x1*/,
    MutantObject               = 2 /*0x2*/,
    ProcessObject              = 3 /*0x3*/,
    QueueObject                = 4 /*0x4*/,
    SemaphoreObject            = 5 /*0x5*/,
    ThreadObject               = 6 /*0x6*/,
    GateObject                 = 7 /*0x7*/,
    TimerNotificationObject    = 8 /*0x8*/,
    TimerSynchronizationObject = 9 /*0x9*/,
    Spare2Object               = 10 /*0xA*/,
    Spare3Object               = 11 /*0xB*/,
    Spare4Object               = 12 /*0xC*/,
    Spare5Object               = 13 /*0xD*/,
    Spare6Object               = 14 /*0xE*/,
    Spare7Object               = 15 /*0xF*/,
    Spare8Object               = 16 /*0x10*/,
    ProfileCallbackObject      = 17 /*0x11*/,
    ApcObject                  = 18 /*0x12*/,
    DpcObject                  = 19 /*0x13*/,
    DeviceQueueObject          = 20 /*0x14*/,
    EventPairObject            = 21 /*0x15*/,
    InterruptObject            = 22 /*0x16*/,
    ProfileObject              = 23 /*0x17*/,
    ThreadedDpcObject          = 24 /*0x18*/,
    MaximumKernelObject        = 25 /*0x19*/
} KOBJECTS, *PKOBJECTS;


struct _KTHREAD
{
    KWAIT_BLOCK WaitBlock[4];
    KWAIT_BLOCK *WaitBlockList;
    ULONG State;
    KTIMER Timer;
    LONG_PTR WaitState;
    BOOLEAN WaitNext;
    KIRQL WaitIrql;
};

#define Waiting 1
#define Running 2
#define TIMER_WAIT_BLOCK THREAD_WAIT_OBJECTS
#define WaitBlockActive 1

#define KeBugCheck(...)
#define KiWaitThread(...) 0
#define KiIsTimerExpired(...) 0
#define KeSetTimer(...)
#define KeInitializeTimer(...)

/******************************************************************************/

#define DH_LOCK_MASK 0x80
#define DH_LOCK_BIT 7

VOID
FORCEINLINE
KiLockDispatcherObject(
    __inout DISPATCHER_HEADER *DispatcherHeader)
{
    do
    {
        while (DispatcherHeader->Lock & DH_LOCK_MASK) YieldProcessor();

    } while (InterlockedBitTestAndSet(&DispatcherHeader->Lock, DH_LOCK_BIT));
}

VOID
FORCEINLINE
KiUnlockDispatcherObject(
    __inout DISPATCHER_HEADER *DispatcherHeader)
{
    InterlockedAnd(&DispatcherHeader->Lock, ~DH_LOCK_MASK);
}

BOOLEAN
FORCEINLINE
IsSynchronisationObject(
    __inout DISPATCHER_HEADER *DispatcherHeader)
{
    UCHAR Type = DispatcherHeader->Type & ~DH_LOCK_MASK;
    return ((Type & 7) == EventSynchronizationObject) ||
           (Type == SemaphoreObject) ||
           (Type ==  MutantObject);
}

VOID
FORCEINLINE
KiAcquireDispatcherObject(
    __inout DISPATCHER_HEADER *DispatcherHeader)
{
    if (IsSynchronisationObject(DispatcherHeader))
    {
        DispatcherHeader->SignalState--;
    }
}

VOID
KiSortWaitBlockObjects(
    __out PKWAIT_BLOCK WaitBlockArray,
    __in PVOID Object[])
{
}
#if 0
NTSTATUS
FORCEINLINE
KiWaitForAllObjects(
    __in ULONG Count,
    __inout PKWAIT_BLOCK WaitBlockArray)
{
    ULONG Index, StartIndex;
    PKWAIT_BLOCK WaitBlock;
    DISPATCHER_HEADER *DispatcherHeader;
    NTSTATUS Status;

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
                    Status = KiWaitThread();

                    if (Status == STATUS_TIMEOUT)
                    {
                        return Status;
                    }

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

                    KiAcquireDispatcherObject(DispatcherHeader);

                    /* Unlock the dispatcher object */
                    KiUnlockDispatcherObject(DispatcherHeader);
                }

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

#if 0
NTSTATUS
NTAPI
KiWaitThread(
    __in PKTIMER Timer)
{
    PKTHREAD CurrentThread;

    if (Timer)
    {
        /* We have a timer, check if it's expired already */
        if (KiIsTimerExpired(Timer))
        {
            CurrentThread->State = Running;

            /* Return timeout! */
            return STATUS_TIMEOUT;
        }

        /* Insert the timer into the timer table */
        KiInsertTimer(Timer);
    }
}
#endif

NTSTATUS
FORCEINLINE
KiWaitForAnyObject(
    __in ULONG Count,
    __in PVOID Object[],
    __inout PKWAIT_BLOCK WaitBlockArray,
    __in PKTIMER Timer)
{
    DISPATCHER_HEADER *DispatcherHeader;
    PKWAIT_BLOCK WaitBlock;
    PKTHREAD CurrentThread;
    NTSTATUS Status;
    ULONG Index;

    /* Loop all objects in given order */
    for (Index = 0; Index < Count; Index++)
    {
        DispatcherHeader = Object[Index];

        /* Check if the object is signaled */
        if (DispatcherHeader->SignalState > 0)
        {
            /* Lock the dispatcher object */
            KiLockDispatcherObject(DispatcherHeader);

            /* Check, if the object is still signaled */
            if (DispatcherHeader->SignalState > 0)
            {
                /* Acquire the object, if applicable */
                KiAcquireDispatcherObject(DispatcherHeader);

                /* Unlock the object and return it's key */
                KiUnlockDispatcherObject(DispatcherHeader);
                return Index;
            }

            /* Unlock the dispatcher object and continue */
            KiUnlockDispatcherObject(DispatcherHeader);
        }
    }

    /* Quick check for expired timer */
    if (Timer && KiIsTimerExpired(Timer))
    {
        /* Return timeout! */
        return STATUS_TIMEOUT;
    }

    /* Get the current thread and set a wait state */
    CurrentThread = KeGetCurrentThread();
    CurrentThread->State = Waiting;

    /* Loop all objects in given order again */
    for (Index = 0; Index < Count; Index++)
    {
        DispatcherHeader = Object[Index];
        WaitBlock = &WaitBlockArray[Index];

        WaitBlock->WaitType = WaitAny;
        WaitBlock->Object = DispatcherHeader;
        WaitBlock->WaitKey = Index;
        WaitBlock->Thread = KeGetCurrentThread();

        /* Lock the dispatcher object */
        KiLockDispatcherObject(DispatcherHeader);

        /* Check, if the object is signaled now */
        if (DispatcherHeader->SignalState > 0)
        {
            /* Acquire the object, if applicable */
            KiAcquireDispatcherObject(DispatcherHeader);

            /* Unlock the object and return it's key */
            KiUnlockDispatcherObject(DispatcherHeader);
            return Index;
        }

        /* Insert the wait block into the wait list */
        InsertTailList(&DispatcherHeader->WaitListHead,
                       &WaitBlock->WaitListEntry);

        /* Unlock the dispatcher object and continue */
        KiUnlockDispatcherObject(DispatcherHeader);
    }

    Status = KiWaitThread();

    /* Loop all objects in given order again */
    for (Index = 0; Index < Count; Index++)
    {
        /* Get the wait block and dispatcher header */
        WaitBlock = &WaitBlockArray[Index];
        DispatcherHeader = WaitBlock->Object;

        if (DispatcherHeader)
        {
            /* Lock the dispatcher object */
            KiLockDispatcherObject(DispatcherHeader);

            if (WaitBlock->BlockState == WaitBlockActive)
            {
                RemoveEntryList(&WaitBlock->WaitListEntry);
            }

            /* Unlock the dispatcher object and continue */
            KiUnlockDispatcherObject(DispatcherHeader);
        }

    }

    return KeGetCurrentThread()->WaitState;
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
    PKTHREAD CurrentThread = KeGetCurrentThread();
    DISPATCHER_HEADER *DispatcherHeader;
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
    else if (Count > THREAD_WAIT_OBJECTS)
    {
        /* Bugcheck the system! */
        KeBugCheck(MAXIMUM_WAIT_OBJECTS_EXCEEDED);
    }

    /* Sort all objects to prevent dead locks, when locking them */
    KiSortWaitBlockObjects(WaitBlockArray, Object);

    /* Save pointer to the wait block array */
    CurrentThread->WaitBlockList = WaitBlockArray;

    if (!CurrentThread->WaitNext)
    {
        CurrentThread->WaitIrql = KfRaiseIrql(DISPATCH_LEVEL);
    }



    KeLowerIrql(CurrentThread->WaitIrql);

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
    PKTIMER Timer;

    // handle timeout
    Timer = KiHandleTimeout(Timeout);

    if (!Thread->WaitNext)
    {
        Thread->WaitIrql = KfRaiseIrql(DISPATCH_LEVEL);
    }


    Status = KiWaitForAnyObject(1, &Object, &Thread->WaitBlock[0], Timer);

    KeLowerIrql(Thread->WaitIrql);

    return 0;
}


