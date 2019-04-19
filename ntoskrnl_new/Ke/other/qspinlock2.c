
#define MAX_CACHE_LINE_SIZE 128

// this is 5
#define NUMBER_OF_LOCK_HANDLES ((MAX_CACHE_LINE_SIZE - sizeof(ULONG)) / sizeof(KLOCK_QUEUE_HANDLE))

typedef union _KI_CACHE_AWARE_LOCK_HANDLE_TABLE
{
    struct
    {
        KLOCK_QUEUE_HANDLE LockHandles[NUMBER_OF_LOCK_HANDLES];
        ULONG LockCount;
    };
    UCHAR Sizing[MAX_CACHE_LINE_SIZE];
} KI_CACHE_AWARE_LOCK_HANDLE_TABLE, *PKI_CACHE_AWARE_LOCK_HANDLE_TABLE;


PKI_CACHE_AWARE_LOCK_HANDLE_TABLE KiPerCpuLockHandles;

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
NTHALAPI
KIRQL
FASTCALL
KfAcquireSpinLockAtDpcLevel(
    _Inout_ PKSPIN_LOCK SpinLock)
{
    PKI_CACHE_AWARE_LOCK_HANDLE_TABLE LockHandleTable;
    ULONG ProcessorNumber;

    NT_ASSERT(KiPerCpuLockHandles != NULL);
    NT_ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

    ProcessorNumber = KeGetCurrentProcessorNumber();

    LockHandleTable = &KiPerCpuLockHandles[ProcessorNumber];

    if (LockHandleTable->LockCount >= NUMBER_OF_LOCK_HANDLES)
    {
        OldIrql = KfAcquireSpinLockAtDpcLevelOld(SpinLock);
    }
    else
    {
        LockHandle = LockHandleTable->LockHandles[LockHandleTable->LockCount];
        KeAcquireInStackQueuedSpinLockAtDpcLevel(SpinLock, LockHandle);
        LockHandle->OldIrql;
    }

    LockHandleTable->LockCount++;

    return OldIrql;
}
