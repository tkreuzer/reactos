
#include <ntoskrnl.h>
#include "Ke_internal.h"

extern PKPROCESS KiGlobalSystemProcess;

UCHAR
FORCEINLINE
InterlockedExchangeThreadState(
    PKTHREAD Thread,
    UCHAR State)
{
    volatile LONG *Target;
    union
    {
        UCHAR State;
        LONG Long;
    } Value;

    Target = (PLONG)&Thread->State;

    Value.Long = *Target;
    Value.State = State;

    Value.Long = InterlockedExchange(Target, Value.Long);

    return Value.State;
}

UCHAR
FORCEINLINE
InterlockedCompareExchangeThreadState(
    PKTHREAD Thread,
    UCHAR NewState,
    UCHAR CompState)
{
    volatile LONG *Target;
    union
    {
        UCHAR State;
        LONG Long;
    } OldValue, NewValue;

    Target = (PLONG)&Thread->State;
    ASSERT(((ULONG_PTR)Target & 3) == 0);

    /* Read the current value */
    OldValue.Long = *Target;

    /* Bail out if it doesn't match the comparand */
    if (OldValue.State != CompState) return OldValue.State;

    /* Setup a new value */
    NewValue = OldValue;
    NewValue.State = NewState;

    /* Atomically exchange if the old value is still correct */
    OldValue.Long = InterlockedCompareExchange(Target,
                                               NewValue.Long,
                                               OldValue.Long);

    /* Return the pevious state */
    return OldValue.State;
}

ULONG
FORCEINLINE
KiSelectProcessor(PKTHREAD Thread)
{
    // FIXME: check ideal processor, affinity, waitprcb
    return 0;
}

VOID
NTAPI
KiReadyThread(
    PKTHREAD Thread,
    LONG_PTR WaitStatus)
{
    PKPRCB Prcb = KeGetCurrentPrcb();
    PLIST_ENTRY ListHead;
    UCHAR OldState;
    ULONG Processor;
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

    /* Atomically exchange the state with DeferredReady */
    OldState = InterlockedCompareExchangeThreadState(Thread, Waiting, DeferredReady);

    /* Check if we woke up the thread */
    if (OldState == Waiting)
    {
        /* Set the wait status */
        Thread->WaitStatus = WaitStatus;

        /* Select a processor to run this thread on */
        Processor = KiSelectProcessor(Thread);

        /* Check if the thread will be run on the current CPU */
        if (Processor == Prcb->Number)
        {
            /* Insert the thread into this CPUs ready list */
            ListHead = &Prcb->DispatcherReadyListHead[Thread->Priority];
            InsertTailList(ListHead, &Thread->WaitListEntry);
            Thread->State = Ready;

            if (Thread->Priority > Prcb->NextThread->Priority)
            {
                Prcb->NextThread = Thread;
            }
        }
        else
        {
            // FIXME: need to put it on a CPUs deferred ready list
            __debugbreak();
            //InterlockedPushEntrySList(&Thread->WaitPrcb->DeferrefReadyListHead,
            //                          &Thread->DeferrefReadyListEntry
            // target cpu will process this list on next clock tick
            // if priority is higher than current, issue an IPI
            // target cpu will flush the list and move all threads to its ready list
        }
    }
}


PKTHREAD
NTAPI
KiGetNextReadyThread()
{
    PKPRCB Prcb = KeGetCurrentPrcb();
    PLIST_ENTRY ListHead, ListEntry;
    PKTHREAD Thread = NULL;
    LONG Priority;
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

    /* Loop all priorities from high to low */
    Priority = HIGH_PRIORITY;
    do
    {
        ListHead = &Prcb->DispatcherReadyListHead[Priority];

        ListEntry = ListHead->Flink;

        if (ListEntry != ListHead)
        {
            Thread = CONTAINING_RECORD(ListEntry, KTHREAD, WaitListEntry);
            return Thread;
        }

        /* Next lower priority */
        Priority--;
    } while (Priority >= 0);

    /* Nothing found, return the idle thread. */
    return Prcb->IdleThread;
}

VOID
NTAPI
KiSwapThread(
    PKTHREAD NewThread)
{
    PKPRCB Prcb = KeGetCurrentPrcb();
    PKTHREAD OldThread = Prcb->CurrentThread;
    //XSAVE_AREA ExtendedFltState;
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);
    ASSERT(NewThread->State == Ready);

    /* Set the new thread in the PRCB */
    Prcb->CurrentThread = NewThread;

    /* Check if the new thread is from a different process */
    if ((NewThread->Process != OldThread->Process) &&
        (NewThread->Process != KiGlobalSystemProcess))
    {
        /* Attach to new process' address space */
        KxAttachProcessAddressSpace(NewThread->Process);
    }

    NewThread->State = Running;

    //KeQueryInterruptTime(
    // Update runtime

    /* Now switch to the new thread's stack */
    KxSwapContext(OldThread, NewThread);
}


VOID
NTAPI
KiBoostPriorityThread(
    PKTHREAD Thread,
    CHAR Priority)
{
    __debugbreak();
}


