
#include <ntoskrnl.h>
#include "Ke_internal.h"

/* Guarded mutexes ************************************************************/

VOID
KeInitializeGate(PKGATE Gate)
{
    KeInitializeEvent((PKEVENT)Gate, SynchronizationEvent, FALSE);
}

VOID
KeSignalGate(PKGATE Gate)
{
    KeSetEvent((PKEVENT)Gate, 0, FALSE);
}

/* The measning of the Count member:
 * 1: The mutex is available
 * 0: The mutex is owned by a thread, no waiters
 * -1, -2, ...: The mutex is oned by a thread and -Count threads are waiting
 */

VOID
FORCEINLINE
KiAcquireFastOrGuardedMutexUnsafe(
    _Inout_ PKGUARDED_MUTEX Mutex,
    _In_ KWAIT_REASON WaitReason)
{
    NTSTATUS Status;
    LONG Count;

    /* Decrement the count value */
    Count = InterlockedDecrement(&Mutex->Count);

    /* Check if we own the lock */
    if (Count != 0)
    {
        /* Boost the owner thread */

        /* Do a wait on the gate (or synchronisation event) */
        Status = KeWaitForSingleObject(&Mutex->Gate,
                                       WrGuardedMutex,
                                       KernelMode,
                                       FALSE,
                                       NULL);

        /* The mutex must not be available */
        ASSERT(Mutex->Count < 1);
    }

    /* Set this thread as the new owner */
    ASSERT(Mutex->Owner == NULL);
    Mutex->Owner = KeGetCurrentThread();
}

VOID
FORCEINLINE
KiReleaseFastOrGuardedMutexUnsafe(
    __inout PKGUARDED_MUTEX Mutex)
{
    ULONG Count;

    ASSERT(Mutex->Owner == KeGetCurrentThread());
    ASSERT(Mutex->Count < 1);

    /* Increment the count value */
    Count = InterlockedIncrement(&Mutex->Count);

    /* Check if there are waiters */
    if (Count < 1)
    {
        /* There are waiters, signal the gate, pass ownership to the next waiter */
        KeSignalGate(&Mutex->Gate);
    }
}

VOID
NTAPI
KeInitializeGuardedMutex(
    __out PKGUARDED_MUTEX Mutex)
{
    /* Initialize the synchronisation gate (in unsignaled state) */
    KeInitializeGate(&Mutex->Gate);

    /* Initialize the other members */
    Mutex->Count = 1;
    Mutex->Owner = NULL;
    Mutex->Contention = 0;
    Mutex->CombinedApcDisable = 0;
}

BOOLEAN
NTAPI
KeTryToAcquireGuardedMutex(
    __inout PKGUARDED_MUTEX Mutex)
{
    /* Enter a guarded region */
    KeEnterGuardedRegion();


    __debugbreak();

    Mutex->Owner = KeGetCurrentThread();
    return TRUE;

}

VOID
NTAPI
KeAcquireGuardedMutexUnsafe(
    __inout PKGUARDED_MUTEX Mutex)
{
    KiAcquireFastOrGuardedMutexUnsafe(Mutex, WrGuardedMutex);
}

VOID
NTAPI
KeReleaseGuardedMutexUnsafe(
    __inout PKGUARDED_MUTEX Mutex)
{
    KiReleaseFastOrGuardedMutexUnsafe(Mutex);
}

VOID
NTAPI
KeAcquireGuardedMutex(
    __inout PKGUARDED_MUTEX Mutex)
{
    /* Enter a guarded region */
    KeEnterGuardedRegion();

    /* Acquire the mutex */
    KiAcquireFastOrGuardedMutexUnsafe(Mutex, WrGuardedMutex);
}

VOID
NTAPI
KeReleaseGuardedMutex(
    __inout PKGUARDED_MUTEX Mutex)
{
    /* Release the mutex */
    KiReleaseFastOrGuardedMutexUnsafe(Mutex);

    /* Leave the guarded region */
    KeLeaveGuardedRegion ();
}


/* Fast Mutex *****************************************************************/

BOOLEAN
FASTCALL
KeTryToAcquireFastMutex(
    __inout PFAST_MUTEX Mutex)
{
    __debugbreak();
    if (KeTryToAcquireGuardedMutex((PKGUARDED_MUTEX)Mutex))
    {
        /* Raise IRQL to APC_LEVEL */
        Mutex->OldIrql = KfRaiseIrql(APC_LEVEL);

        return TRUE;
    }

    return FALSE;
}

VOID
NTAPI
KeAcquireFastMutexUnsafe(
    __inout PFAST_MUTEX Mutex)
{
    /* Acquire the mutex (identical to guarded mutex) */
    KiAcquireFastOrGuardedMutexUnsafe((PKGUARDED_MUTEX)Mutex, WrFastMutex);
}

VOID
NTAPI
KeReleaseFastMutexUnsafe(
    __inout PFAST_MUTEX Mutex)
{
    /* Release the mutex (identical to guarded mutex) */
    KiReleaseFastOrGuardedMutexUnsafe((PKGUARDED_MUTEX)Mutex);
}

VOID
NTAPI
KeAcquireFastMutex(
    __inout PFAST_MUTEX Mutex)
{
    /* Raise IRQL to APC_LEVEL */
    Mutex->OldIrql = KfRaiseIrql(APC_LEVEL);

    /* Acquire the mutex (identical to guarded mutex) */
    KiAcquireFastOrGuardedMutexUnsafe((PKGUARDED_MUTEX)Mutex, WrFastMutex);
}

VOID
NTAPI
KeReleaseFastMutex(
    __inout PFAST_MUTEX Mutex)
{
    /* Release the mutex (identical to guarded mutex) */
    KiReleaseFastOrGuardedMutexUnsafe((PKGUARDED_MUTEX)Mutex);

    /* Restore previous IRQL */
    KeLowerIrql((KIRQL)Mutex->OldIrql);
}

VOID
FASTCALL
KeEnterCriticalRegionAndAcquireFastMutexUnsafe(
    PFAST_MUTEX Mutex)
{
    /* Enter a critical region */
    KeEnterCriticalRegion();

    /* Acquire the mutex (identical to guarded mutex) */
    KiAcquireFastOrGuardedMutexUnsafe((PKGUARDED_MUTEX)Mutex, WrFastMutex);
}

VOID
FASTCALL
KeReleaseFastMutexUnsafeAndLeaveCriticalRegion(
    PFAST_MUTEX Mutex)
{
    /* Release the mutex (identical to guarded mutex) */
    KiReleaseFastOrGuardedMutexUnsafe((PKGUARDED_MUTEX)Mutex);

    /* Leave the critical region */
    KeLeaveCriticalRegion ();
}

