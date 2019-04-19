
#include <ntoskrnl.h>
#include "Ke_internal.h"

KSPIN_LOCK KiQueuedSpinLocks[LockQueueMaximumLock];

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
    }
    while (InterlockedBitTestAndSet((PLONG)SpinLock, 0));
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


BOOLEAN
NTAPI
KeTestSpinLock(
    __in PKSPIN_LOCK SpinLock)
{
    /* Return FALSE if the spinlock is held */
    return !(*SpinLock & 1);
}

BOOLEAN
FASTCALL
KeTryToAcquireSpinLockAtDpcLevel(
    __inout PKSPIN_LOCK SpinLock)
{
    /* First test the spin lock */
    if (*SpinLock & 1) return FALSE;

    /* Now attempt to acquire it and return TRUE on success */
    return !InterlockedBitTestAndSet((PLONG)SpinLock, 0);
}

VOID
NTAPI
KeAcquireSpinLockAtDpcLevel(
    __inout PKSPIN_LOCK SpinLock)
{
    /* Use the inlined function */
    _KiAcquireSpinLock(SpinLock);
}

VOID
NTAPI
KeReleaseSpinLockFromDpcLevel(
    __inout  PKSPIN_LOCK SpinLock)
{
    /* Just use the inlined version */
    _KiReleaseSpinLock(SpinLock);
}

KIRQL
NTAPI
KeAcquireSpinLockRaiseToDpc(
    IN OUT PKSPIN_LOCK SpinLock)
{
    KIRQL OldIrql;

    /* Raise IRQL to dispatch level */
    OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

    /* Use the inlined function */
    _KiAcquireSpinLock(SpinLock);

    return OldIrql;
}

KIRQL
FASTCALL
KeAcquireSpinLockRaiseToSynch(
  IN OUT PKSPIN_LOCK SpinLock)
{
    KIRQL OldIrql;

    /* Raise IRQL to synch level */
    OldIrql = KfRaiseIrql(SYNCH_LEVEL);

    /* Use the inlined function */
    _KiAcquireSpinLock(SpinLock);

    return OldIrql;
}


VOID
NTAPI
KeReleaseSpinLock(
    IN PKSPIN_LOCK SpinLock,
    IN KIRQL NewIrql)
{
    /* Use the inlined version */
    _KiReleaseSpinLock(SpinLock);

    /* Restore IRQL */
    KeLowerIrql(NewIrql);
}

KIRQL
FASTCALL
KeAcquireSpinLockForDpc(
    IN PKSPIN_LOCK SpinLock)
{
    KIRQL OldIrql;

    /* Get the current IRQL */
    OldIrql = KeGetCurrentIrql();

    /* Check if this is a threaded DPC running at passive level */
    if (OldIrql < DISPATCH_LEVEL)
    {
        /* In this case we need to raise IRQL */
        KfRaiseIrql(DISPATCH_LEVEL);
    }

    /* Use the inlined function */
    _KiAcquireSpinLock(SpinLock);

    return OldIrql;
}

VOID
FASTCALL
KeReleaseSpinLockForDpc(
    __inout  PKSPIN_LOCK SpinLock,
    __in     KIRQL OldIrql)
{
    /* Use the inlined version */
    _KiReleaseSpinLock(SpinLock);

    /* Restore IRQL */
    KeLowerIrql(OldIrql);
}

#ifndef _M_AMD64
VOID
NTAPI
KeInitializeSpinLock_(
    __out PKSPIN_LOCK SpinLock)
{
    KeInitializeSpinLock(SpinLock);
}

VOID
FASTCALL
KefAcquireSpinLockAtDpcLevel(
    __inout  PKSPIN_LOCK SpinLock)
{
    /* Use the inlined function */
    _KiAcquireSpinLock(SpinLock);
}

VOID
FASTCALL
KefReleaseSpinLockFromDpcLevel(
    IN OUT PKSPIN_LOCK SpinLock)
{
    /* Just use the inlined version */
    _KiReleaseSpinLock(SpinLock);
}

VOID
FASTCALL
KiAcquireSpinLock(
    IN PKSPIN_LOCK SpinLock)
{
    UNIMPLEMENTED;
    __debugbreak();
}

KIRQL
FASTCALL
KfAcquireSpinLock(
    PKSPIN_LOCK SpinLock)
{
    KIRQL OldIrql;

    /* Raise IRQL to dispatch level */
    OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

    /* Use the inlined function */
    _KiAcquireSpinLock(SpinLock);

    return OldIrql;
}

VOID
FASTCALL
KfReleaseSpinLock(
    IN PKSPIN_LOCK SpinLock,
    IN KIRQL NewIrql)
{
    /* Use the inlined version */
    _KiReleaseSpinLock(SpinLock);

    /* Restore IRQL */
    KeLowerIrql(NewIrql);
}

#endif


/* Queued Spin Locks **********************************************************/

#ifdef CONFIG_SMP
VOID
FASTCALL
KiAcquireQueuedSpinLock(
    IN OUT PKSPIN_LOCK SpinLock,
    IN OUT PKSPIN_LOCK_QUEUE LockQueue)
{
    PKSPIN_LOCK_QUEUE PreviousWaiter;

    LockQueue->Lock = SpinLock;
    LockQueue->Next = NULL;

    PreviousWaiter = InterlockedCompareExchangePointer((PVOID*)SpinLock,
                                                       (PVOID)LockQueue,
                                                       NULL);

#if 0
    if (PreviousWaiter)
    {
        /* Register with the previous waiter */
        PreviousWaiter->Next = LockQueue;

        /* Check if the previous waiter is already done */
        if (PreviousWaiter->Lock != SpinLock)

        while (LockQueue->Lock
    }
#endif

    UNIMPLEMENTED;
    __debugbreak();
}

VOID
FASTCALL
KiReleaseQueuedSpinLock(
    IN PKSPIN_LOCK_QUEUE LockQueue)
{
#if 0
    PKSPIN_LOCK_QUEUE NextWaiter;


    NextWaiter = InterlockedCompareExchangePointer((PVOID*)SpinLock,
                                                   (PVOID)LockQueue,
                                                   NULL);

    /* Check if there are waiters */
    if (NextWaiter != NULL)
    {
        /* There is a waiter in the queue, wait his for notification */
        while (LockHandle->LockQueue.Next == 0) YieldProcessor();

        /* Release the next waiters lock */
        LockHandle->LockQueue.Next->Lock = 0;
    }

#endif
}
#else

#define KiAcquireQueuedSpinLock(SpinLock, LockQueue)
#define KiReleaseQueuedSpinLock(LockQueue)

#endif

KIRQL
FASTCALL
KeAcquireQueuedSpinLock(
    IN KSPIN_LOCK_QUEUE_NUMBER LockNumber)
{
    KIRQL OldIrql;

    /* Raise IRQL to dispatch level */
    OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

    /* Call the internal function */
    KiAcquireQueuedSpinLock(&KiQueuedSpinLocks[LockNumber],
                            &KxGetCurrentPrcb()->LockQueue[LockNumber]);

    /* Return the old IRQL */
    return OldIrql;
}

KIRQL
FASTCALL
KeAcquireQueuedSpinLockRaiseToSynch(
    IN KSPIN_LOCK_QUEUE_NUMBER LockNumber)
{
    KIRQL OldIrql;

    /* Raise IRQL to aync level */
    OldIrql = KfRaiseIrql(SYNCH_LEVEL);

    /* Call the internal function */
    KiAcquireQueuedSpinLock(&KiQueuedSpinLocks[LockNumber],
                            &KxGetCurrentPrcb()->LockQueue[LockNumber]);

    /* Return the old IRQL */
    return OldIrql;
}

LOGICAL
FASTCALL
KeTryToAcquireQueuedSpinLock(
  IN KSPIN_LOCK_QUEUE_NUMBER Number,
  OUT PKIRQL OldIrql)
{
    UNIMPLEMENTED;
    __debugbreak();
    return 0;
}

KIRQL
FASTCALL
KeTryToAcquireQueuedSpinLockRaiseToSynch(
    IN KSPIN_LOCK_QUEUE_NUMBER LockNumber)
{
    UNIMPLEMENTED;
    __debugbreak();
    return 0;
}

VOID
FASTCALL
KeReleaseQueuedSpinLock(
    IN OUT KSPIN_LOCK_QUEUE_NUMBER LockNumber,
    IN KIRQL OldIrql)
{
    /* Call the internal function */
    KiReleaseQueuedSpinLock(&KxGetCurrentPrcb()->LockQueue[LockNumber]);

    /* Lower IRQL back to previous */
    KeLowerIrql(OldIrql);
}


/* In Stack Queued Spin Locks *************************************************/

VOID
FASTCALL
KeAcquireInStackQueuedSpinLock(
    IN PKSPIN_LOCK SpinLock,
    IN PKLOCK_QUEUE_HANDLE LockHandle)
{
    /* Raise IRQL to dispatch level */
    LockHandle->OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

    /* Call the internal function */
    KiAcquireQueuedSpinLock(SpinLock, &LockHandle->LockQueue);
}

VOID
FASTCALL
KeAcquireInStackQueuedSpinLockRaiseToSynch(
    IN PKSPIN_LOCK SpinLock,
    IN PKLOCK_QUEUE_HANDLE LockHandle)
{
    /* Raise IRQL to dispatch level */
    LockHandle->OldIrql = KfRaiseIrql(SYNCH_LEVEL);

    /* Call the internal function */
    KiAcquireQueuedSpinLock(SpinLock, &LockHandle->LockQueue);
}

VOID
FASTCALL
KeAcquireInStackQueuedSpinLockAtDpcLevel(
    __inout PKSPIN_LOCK SpinLock,
    __out PKLOCK_QUEUE_HANDLE LockHandle)
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
FASTCALL
KeReleaseInStackQueuedSpinLockFromDpcLevel(
    __out PKLOCK_QUEUE_HANDLE LockHandle)
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
FASTCALL
KeAcquireInStackQueuedSpinLockForDpc(
    __inout PKSPIN_LOCK SpinLock,
    __out PKLOCK_QUEUE_HANDLE LockHandle)
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
FASTCALL
KeReleaseInStackQueuedSpinLockForDpc(
    IN PKLOCK_QUEUE_HANDLE LockHandle)
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
FASTCALL
KeReleaseInStackQueuedSpinLockFromDpcLevel2(
    __in PKLOCK_QUEUE_HANDLE LockHandle)
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
FASTCALL
KeReleaseInStackQueuedSpinLock(
    IN PKLOCK_QUEUE_HANDLE LockHandle)
{
    /* Call the internal function and check for waiters */
    KiReleaseQueuedSpinLock(&LockHandle->LockQueue);

    /* Lower IRQL back to previous */
    KeLowerIrql(LockHandle->OldIrql);
}


KIRQL
NTAPI
KeAcquireInterruptSpinLock(
    IN OUT PKINTERRUPT Interrupt)
{
    KIRQL OldIrql;

    /* Raise IRQL to the synchronization IRQL */
    OldIrql = KfRaiseIrql(Interrupt->SynchronizeIrql);

    /* Use the inlined function */
    _KiAcquireSpinLock(Interrupt->ActualLock);

    return OldIrql;
}

VOID
NTAPI
KeReleaseInterruptSpinLock(
    __inout PKINTERRUPT Interrupt,
    __in KIRQL OldIrql)
{
    UNIMPLEMENTED;
    __debugbreak();
}








