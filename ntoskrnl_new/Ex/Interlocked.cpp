
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

    __debugbreak();
    Result.QuadPart = 0;
    return Result;
}

ULONG
FASTCALL
ExInterlockedAddUlong (
    _Inout_ PULONG Addend,
    _In_ ULONG Increment,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return 0;
}

PLIST_ENTRY
FASTCALL
ExInterlockedInsertHeadList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return 0;
}


PLIST_ENTRY
FASTCALL
ExInterlockedInsertTailList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return 0;
}

PLIST_ENTRY
FASTCALL
ExInterlockedRemoveHeadList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return 0;
}

PSINGLE_LIST_ENTRY
FASTCALL
ExInterlockedPopEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return 0;
}

PSINGLE_LIST_ENTRY
FASTCALL
ExInterlockedPushEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PSINGLE_LIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
__drv_preferredFunction("lookaside lists instead", "Obsolete")
DECLSPEC_DEPRECATED_DDK
NTSTATUS
NTAPI
ExInterlockedExtendZone(
    _Inout_ PZONE_HEADER Zone,
    _Inout_ PVOID Segment,
    _In_ ULONG SegmentSize,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock)
{
    __debugbreak();
    return 0;
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
    __debugbreak();
    return ResultZero;
}

ULONG
FASTCALL
Exfi386InterlockedExchangeUlong (
    _Inout_ _Interlocked_operand_ ULONG volatile *Target,
    _In_ ULONG Value)
{
    __debugbreak();
    return 0;
}

INTERLOCKED_RESULT
FASTCALL
Exfi386InterlockedIncrementLong (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    __debugbreak();
    return ResultZero;
}

INTERLOCKED_RESULT
NTAPI
Exi386InterlockedDecrementLong (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    __debugbreak();
    return ResultZero;
}

ULONG
NTAPI
Exi386InterlockedExchangeUlong (
    _Inout_ _Interlocked_operand_ ULONG volatile *Target,
    _In_ ULONG Value)
{
    __debugbreak();
    return 0;
}

INTERLOCKED_RESULT
NTAPI
Exi386InterlockedIncrementLong (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    __debugbreak();
    return ResultZero;
}


#endif // _M_IX86

}; // extern "C"
