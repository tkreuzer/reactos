/*
 * COPYRIGHT:   See COPYING in the top level directory
 * PROJECT:     ReactOS TCP/IP protocol driver
 * FILE:        tcpip/lock.c
 * PURPOSE:     Locking and unlocking
 * PROGRAMMERS: Art Yerkes
 * REVISIONS:
 */

#include "precomp.h"

DBG_SPINLOCK_ENTRY DbgSpinLockTable[DBG_TABLE_SIZE];
ULONG64 DbgSpinLockAcquireCount;
ULONG64 DbgSpinLockSpinCount;

void
DbgLockObject(PKSPIN_LOCK SpinLock)
{
    ULONG i;
    DbgSpinLockAcquireCount++;
    if (*SpinLock != 0) __debugbreak();

    for (i = 0; i < DBG_TABLE_SIZE; i++)
    {
        if (DbgSpinLockTable[i].SpinLock == NULL)
        {
            DbgSpinLockTable[i].SpinLock = SpinLock;
            DbgSpinLockTable[i].LockThread = PsGetCurrentThread();
            RtlCaptureStackBackTrace(1, 5, DbgSpinLockTable[i].LockCaller, NULL);
            return;
        }
    }
    __debugbreak();
}

void
DbgUnlockObject(PKSPIN_LOCK SpinLock)
{
    ULONG i;
    for (i = 0; i < DBG_TABLE_SIZE; i++)
    {
        if (DbgSpinLockTable[i].SpinLock == SpinLock)
        {
            RtlZeroMemory(&DbgSpinLockTable[i], sizeof(DbgSpinLockTable[i]));
            return;
        }
    }
    __debugbreak();
}

KIRQL TcpipGetCurrentIrql() { return KeGetCurrentIrql(); }

VOID TcpipInitializeSpinLock( PKSPIN_LOCK SpinLock ) {
    KeInitializeSpinLock( SpinLock );
}

VOID TcpipAcquireSpinLock( PKSPIN_LOCK SpinLock, PKIRQL Irql ) {
    KeAcquireSpinLock( SpinLock, Irql );
}

VOID TcpipAcquireSpinLockAtDpcLevel( PKSPIN_LOCK SpinLock ) {
    KeAcquireSpinLockAtDpcLevel( SpinLock );
}

VOID TcpipReleaseSpinLock( PKSPIN_LOCK SpinLock, KIRQL Irql ) {
    KeReleaseSpinLock( SpinLock, Irql );
}

VOID TcpipReleaseSpinLockFromDpcLevel( PKSPIN_LOCK SpinLock ) {
    KeReleaseSpinLockFromDpcLevel( SpinLock );
}

VOID TcpipInterlockedInsertTailList( PLIST_ENTRY ListHead,
				     PLIST_ENTRY Item,
				     PKSPIN_LOCK Lock ) {
    ExInterlockedInsertTailList( ListHead, Item, Lock );
}

VOID TcpipAcquireFastMutex( PFAST_MUTEX Mutex ) {
    ExAcquireFastMutex( Mutex );
}

VOID TcpipReleaseFastMutex( PFAST_MUTEX Mutex ) {
    ExReleaseFastMutex( Mutex );
}
