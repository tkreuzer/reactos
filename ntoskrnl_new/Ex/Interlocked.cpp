
#include "Interlocked.hpp"
#include <Ke/SpinLock.hpp>
#include <Ke/Irql.hpp>

extern "C" {

LARGE_INTEGER
NTAPI
ExInterlockedAddLargeInteger (
    _Inout_ PLARGE_INTEGER Addend,
    _In_ LARGE_INTEGER Increment,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    LARGE_INTEGER Result;

    /* No lock used */
    UNREFERENCED_PARAMETER(Lock);

    /* Do a 64 bit atomic exchange */
    Result.QuadPart = InterlockedExchangeAdd64(&Addend->QuadPart,
                                               Increment.QuadPart);

    return Result;
}

ULONG
FASTCALL
ExInterlockedAddUlong (
    _Inout_ PULONG Addend,
    _In_ ULONG Increment,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    /* No lock used */
    UNREFERENCED_PARAMETER(Lock);

    /* Use an atomic operation */
    return InterlockedExchangeAdd((PLONG)(Addend), Increment);
}

/// \todo FIXME: move these to Ke
_Acquires_lock_(*SpinLock)
KIRQL
FASTCALL
KeAcquireSpinLockAtAnyIrqlLevel(
    _Inout_ PKSPIN_LOCK SpinLock)
{
    KIRQL OldIrql;

    /* This function needs to run at any IRQL, so get the current IRQL and
       if we are at DISPATCH_LEVEL, raise to DISPATCH_LEVEL */
    OldIrql = KeGetCurrentIrql();
    if (OldIrql < DISPATCH_LEVEL)
    {
        KeRaiseIrqlToDpcLevel();
    }

    /* Acquire the spinlock */
    KeAcquireSpinLockAtDpcLevel(SpinLock);

    return OldIrql;
}

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
FASTCALL
KeReleaseSpinLockFromAnyIrqlLevel (
    _Inout_ PKSPIN_LOCK SpinLock,
    _In_ KIRQL OldIrql)
{
    /* Release the spinlock */
    KeReleaseSpinLockFromDpcLevel(SpinLock);

    /* Lower back to old IRQL, if required */
    if (OldIrql < DISPATCH_LEVEL)
    {
        KeLowerIrql(OldIrql);
    }
}

PLIST_ENTRY
FASTCALL
ExInterlockedInsertHeadList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    KIRQL OldIrql;
    PLIST_ENTRY OldHead;

    /* Acquire the spinlock */
    OldIrql = KeAcquireSpinLockAtAnyIrqlLevel(Lock);

    /* Get the first entry on the list */
    OldHead = ListHead->Flink;

    /* Insert the new entry */
    InsertHeadList(ListHead, ListEntry);

    /* Release the spinlock */
    KeReleaseSpinLockFromAnyIrqlLevel(Lock, OldIrql);

    /* Return the old head */
    return OldHead;
}

PLIST_ENTRY
FASTCALL
ExInterlockedInsertTailList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    KIRQL OldIrql;
    PLIST_ENTRY OldTail;

    /* Acquire the spinlock */
    OldIrql = KeAcquireSpinLockAtAnyIrqlLevel(Lock);

    /* Get the last entry on the list */
    OldTail = ListHead->Blink;

    /* Insert the new entry */
    InsertTailList(ListHead, ListEntry);

    /* Release the spinlock */
    KeReleaseSpinLockFromAnyIrqlLevel(Lock, OldIrql);

    /* Return the old tail */
    return OldTail;
}

PLIST_ENTRY
FASTCALL
ExInterlockedRemoveHeadList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    KIRQL OldIrql;
    PLIST_ENTRY ListEntry;

    /* Acquire the spinlock */
    OldIrql = KeAcquireSpinLockAtAnyIrqlLevel(Lock);

    /* Insert the new entry */
    ListEntry = RemoveHeadList(ListHead);

    /* Release the spinlock */
    KeReleaseSpinLockFromAnyIrqlLevel(Lock, OldIrql);

    /* Return the old tail */
    return ListEntry;
}

PSINGLE_LIST_ENTRY
FASTCALL
ExInterlockedPopEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    KIRQL OldIrql;
    PSINGLE_LIST_ENTRY ListEntry;

    /* Acquire the spinlock */
    OldIrql = KeAcquireSpinLockAtAnyIrqlLevel(Lock);

    /* Pop the next entry from the list */
    ListEntry = PopEntryList(ListHead);

    /* Release the spinlock */
    KeReleaseSpinLockFromAnyIrqlLevel(Lock, OldIrql);

    /* Return the old tail */
    return ListEntry;
}

PSINGLE_LIST_ENTRY
FASTCALL
ExInterlockedPushEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PSINGLE_LIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    KIRQL OldIrql;
    PSINGLE_LIST_ENTRY OldHead;

    /* Acquire the spinlock */
    OldIrql = KeAcquireSpinLockAtAnyIrqlLevel(Lock);

    /* Get the last entry on the list */
    OldHead = ListHead->Next;

    /* Insert the new entry */
    PushEntryList(ListHead, ListEntry);

    /* Release the spinlock */
    KeReleaseSpinLockFromAnyIrqlLevel(Lock, OldIrql);

    /* Return the old tail */
    return OldHead;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
__drv_preferredFunction("lookaside lists instead", "Obsolete")
DECLSPEC_DEPRECATED_DDK
NTSTATUS
NTAPI
ExInterlockedExtendZone (
    _Inout_ PZONE_HEADER Zone,
    _Inout_ PVOID Segment,
    _In_ ULONG SegmentSize,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    KIRQL OldIrql;
    NTSTATUS Status;

    /* Acquire the spinlock */
    OldIrql = KeAcquireSpinLockAtAnyIrqlLevel(Lock);

    /* Get the last entry on the list */
    Status = ExExtendZone(Zone, Segment, SegmentSize);

    /* Release the spinlock */
    KeReleaseSpinLockFromAnyIrqlLevel(Lock, OldIrql);

    /* Return the old tail */
    return Status;
}

#ifdef _M_IX86
LONGLONG
FASTCALL
ExInterlockedCompareExchange64 (
    _Inout_ _Interlocked_operand_ LONGLONG volatile *Destination,
    _In_ PLONGLONG ExChange,
    _In_ PLONGLONG Comperand)
{
    return _InterlockedCompareExchange64(Destination, *ExChange, *Comperand);
}

typedef struct _SLIST_HEADER *PSLIST_HEADER;
typedef struct _SLIST_ENTRY *PSLIST_ENTRY;

PSLIST_ENTRY
FASTCALL
ExInterlockedPopEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return NULL;
}

PSLIST_ENTRY
FASTCALL
ExInterlockedPushEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return NULL;
}

INTERLOCKED_RESULT
FASTCALL
Exfi386InterlockedDecrementLong (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    LONG OldValue = InterlockedDecrement(Addend);
    return (OldValue > 0) ? ResultPositive :
           (OldValue < 0) ? ResultPositive :
            ResultZero;
}

ULONG
FASTCALL
Exfi386InterlockedExchangeUlong (
    _Inout_ _Interlocked_operand_ ULONG volatile *Target,
    _In_ ULONG Value)
{
    return InterlockedExchange((LONG volatile *)Target, Value);
}

INTERLOCKED_RESULT
FASTCALL
Exfi386InterlockedIncrementLong (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    LONG OldValue = InterlockedIncrement(Addend);
    return (OldValue > 0) ? ResultPositive :
           (OldValue < 0) ? ResultPositive :
            ResultZero;
}

INTERLOCKED_RESULT
NTAPI
Exi386InterlockedDecrementLong (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    LONG OldValue = InterlockedDecrement(Addend);
    return (OldValue > 0) ? ResultPositive :
           (OldValue < 0) ? ResultPositive :
            ResultZero;
}

ULONG
NTAPI
Exi386InterlockedExchangeUlong (
    _Inout_ _Interlocked_operand_ ULONG volatile *Target,
    _In_ ULONG Value)
{
    return InterlockedExchange((LONG volatile *)Target, Value);
}

INTERLOCKED_RESULT
NTAPI
Exi386InterlockedIncrementLong (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    LONG OldValue = InterlockedIncrement(Addend);
    return (OldValue > 0) ? ResultPositive :
           (OldValue < 0) ? ResultPositive :
            ResultZero;
}

#endif // _M_IX86

}; // extern "C"
