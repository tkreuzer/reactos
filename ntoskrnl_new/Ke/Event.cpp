
#include "Event.hpp"

FORCEINLINE
BOOLEAN
KiIsEventType(PRKEVENT Event)
{
    UCHAR Type = Event->Header.Type & ~DH_LOCK_MASK;
    return ((Type == EventNotificationObject) ||
        (Type == EventSynchronizationObject));
}

extern "C" {

// wdm.h / ntosp.h
VOID
NTAPI
KeInitializeEvent (
    _Out_ PRKEVENT Event,
    _In_ EVENT_TYPE Type,
    _In_ BOOLEAN State)
{
    Event->Header.Type = (Type == SynchronizationEvent) ?
        EventSynchronizationObject : EventNotificationObject;

    Event->Header.Size = sizeof(KEVENT) / sizeof(ULONG);
    Event->Header.SignalState = State;

    InitializeListHead(&Event->Header.WaitListHead);
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeReadStateEvent (
    _In_ PRKEVENT Event)
{
    ASSERT(KiIsEventType(Event));

    return Event->Header.SignalState;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
KeClearEvent (
    _Inout_ PRKEVENT Event)
{
    ASSERT(KiIsEventType(Event));

    Event->Header.SignalState = 0;
}

// ntddk.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KePulseEvent (
    _Inout_ PRKEVENT Event,
    _In_ KPRIORITY Increment,
    _In_ BOOLEAN Wait)
{

    // lock
    // set state
    // satisfy waits
    // reset state
    // unlock

    return 0;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeResetEvent (
    _Inout_ PRKEVENT Event)
{
    ASSERT(KiIsEventType(Event));

    return InterlockedExchange(&Event->Header.SignalState, 0);
}

// wdm.h / ntosp.h
LONG
NTAPI
KeSetEvent (
    _Inout_ PRKEVENT Event,
    _In_ KPRIORITY Increment,
    _In_ _Literal_ BOOLEAN Wait)
{
    UCHAR Type = Event->Header.Type & ~DH_LOCK_MASK;
    BOOLEAN WakeAll = (Type == EventNotificationObject);
    PKTHREAD Thread = KeGetCurrentThread();
    LONG OldState;
    KIRQL OldIrql;
    ASSERT(KiIsEventType(Event));

    /* If this is a notification object, we can try a fast path without lock */
    if (Type == EventNotificationObject)
    {
        /* If Wait was specified, we raise IRQL before reading the value,
        so that there will be no preemption between reading it and the
        following wait operation */
        if (Wait)
        {
            /* Raise IRQL and save old value in the thread */
            OldIrql = KfRaiseIrql(DISPATCH_LEVEL);
            Thread->WaitIrql = OldIrql;
        }

        /* Now read the signal state and check if its signalled */
        OldState = Event->Header.SignalState;
        if (OldState)
        {
            return OldState;
        }

        /* When Wait is TRUE, IRQL has already been raised above. */
        if (!Wait) OldIrql = KfRaiseIrql(DISPATCH_LEVEL);
    }
    else
    {
        /* Synchronisation events always need to raise and signal the event */
        OldIrql = KfRaiseIrql(DISPATCH_LEVEL);
    }

    KiSignalObject(&Event->Header, WakeAll, PriorityIncrement);

    if (Wait)
    {
        Thread->WaitIrql = OldIrql;
    }
    else
    {
        KeLowerIrql(OldIrql);
    }

    return OldState;
}

// prototype from reactos
LONG
NTAPI
KeSetEventBoostPriority (
    _Inout_ PRKEVENT Event,
    _Out_ PKTHREAD *WaitingThread)
{
    __debugbreak();
    return 0;
}

}; // extern "C"
