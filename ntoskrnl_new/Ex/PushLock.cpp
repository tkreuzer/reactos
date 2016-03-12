
#include "PushLock.hpp"

namespace Ex {

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
PUSH_LOCK::AcquireExclusive (
    VOID)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
bool
PUSH_LOCK::TryAcquireExclusive (
    VOID)
{
    __debugbreak();
    return false;
}

extern "C" {

/* Normal push lock */
#undef ExInitializePushLock
VOID
NTAPI
ExInitializePushLock (
    _Out_ PEX_PUSH_LOCK PushLock)
{
    new((PVOID)PushLock) PUSH_LOCK;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExfAcquirePushLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    reinterpret_cast<PPUSH_LOCK>(PushLock)->AcquireExclusive();
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExAcquirePushLockExclusiveEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
BOOLEAN
FASTCALL
ExTryAcquirePushLockExclusiveEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    return reinterpret_cast<PPUSH_LOCK>(PushLock)->TryAcquireExclusive();
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExfAcquirePushLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExAcquirePushLockSharedEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
BOOLEAN
FASTCALL
ExfTryAcquirePushLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return==1, _Acquires_lock_(*_Curr_))
    PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
BOOLEAN
FASTCALL
ExTryAcquirePushLockSharedEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExfReleasePushLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExReleasePushLockExclusiveEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExfReleasePushLockShared (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExReleasePushLockSharedEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExfReleasePushLock (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExReleasePushLockEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

VOID
FASTCALL
ExBlockPushLock (
    PVOID Ptr1,
    PVOID Ptr2)
{
    __debugbreak();
}

VOID
FASTCALL
ExfUnblockPushLock (
    _Inout_ PEX_PUSH_LOCK PushLock,
    _Inout_opt_ PVOID WaitBlock)
{
    __debugbreak();
}

VOID
FASTCALL
ExUnblockPushLockEx (
    _Inout_ PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

VOID
FASTCALL
ExWaitForUnblockPushLock (
    PVOID Ptr1,
    PVOID Ptr2)
{
    __debugbreak();
}


NTSTATUS
FASTCALL
ExBlockOnAddressPushLock (
    _Inout_ PEX_PUSH_LOCK PushLock,
    _In_reads_bytes_(AddressSize) volatile VOID *Address,
    _In_reads_bytes_(AddressSize) PVOID CompareAddress,
    _In_ SIZE_T AddressSize,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
FASTCALL
ExUnblockOnAddressPushLockEx (
    _Inout_ PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

VOID
FASTCALL
ExTimedWaitForUnblockPushLock (
    PVOID Ptr1,
    PVOID Ptr2,
    PVOID Ptr3)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FASTCALL
ExfTryToWakePushLock (
    _Inout_ PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
BOOLEAN
FASTCALL
ExTryConvertPushLockSharedToExclusiveEx (
    _Inout_ _Requires_lock_held_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
    return FALSE;
}


/* cache aware pushlocks */
#define EX_CACHE_LINE_SIZE 128
#define EX_PUSH_LOCK_FANNED_COUNT (PAGE_SIZE/EX_CACHE_LINE_SIZE)

typedef struct _EX_PUSH_LOCK_CACHE_AWARE_LEGACY
{
    PEX_PUSH_LOCK Locks[EX_PUSH_LOCK_FANNED_COUNT];
} EX_PUSH_LOCK_CACHE_AWARE_LEGACY, *PEX_PUSH_LOCK_CACHE_AWARE_LEGACY;

typedef struct _EX_PUSH_LOCK_CACHE_AWARE_PADDED
{
    EX_PUSH_LOCK Lock;
    union
    {
        UCHAR Pad[EX_CACHE_LINE_SIZE - sizeof (EX_PUSH_LOCK)];
        struct
        {
            BOOLEAN Single;
            PVOID ParentLock;
        };
    };
} EX_PUSH_LOCK_CACHE_AWARE_PADDED, *PEX_PUSH_LOCK_CACHE_AWARE_PADDED;


_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PEX_PUSH_LOCK_CACHE_AWARE_LEGACY
NTAPI
ExAllocateCacheAwarePushLock (
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExFreeCacheAwarePushLock (
    _Inout_ PEX_PUSH_LOCK_CACHE_AWARE_LEGACY PushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExAcquireCacheAwarePushLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
ExAcquireCacheAwarePushLockExclusiveEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
FASTCALL
ExTryAcquireCacheAwarePushLockExclusiveEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
     _Inout_ PEX_PUSH_LOCK_CACHE_AWARE_LEGACY AutoExpandPushLock,
     _In_ ULONG Flags)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
PEX_PUSH_LOCK
FASTCALL
ExAcquireCacheAwarePushLockSharedEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
FASTCALL
ExTryAcquireCacheAwarePushLockSharedEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK_CACHE_AWARE_LEGACY AutoExpandPushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExReleaseCacheAwarePushLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
ExReleaseCacheAwarePushLockExclusiveEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExReleaseCacheAwarePushLockSharedEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}


/* auto expand pushlocks */
typedef struct _EX_PUSH_LOCK_AUTO_EXPAND_STATE
{
    union
    {
        struct
        {
            ULONG Expanded      : 1;
            ULONG Transitioning : 1;
            ULONG Pageable      : 1;
        };
        volatile ULONG Value;
    };
} EX_PUSH_LOCK_AUTO_EXPAND_STATE, *PEX_PUSH_LOCK_AUTO_EXPAND_STATE;

typedef struct _EX_PUSH_LOCK_AUTO_EXPAND
{
    EX_PUSH_LOCK LocalLock;
    EX_PUSH_LOCK_AUTO_EXPAND_STATE State;
    ULONG Stats;
} EX_PUSH_LOCK_AUTO_EXPAND, *PEX_PUSH_LOCK_AUTO_EXPAND;

_IRQL_requires_max_(APC_LEVEL)
SIZE_T
NTAPI
ExSizeOfAutoExpandPushLock (
    _In_ ULONG Flags)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PEX_PUSH_LOCK_AUTO_EXPAND
NTAPI
ExAllocateAutoExpandPushLock (
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExInitializeAutoExpandPushLock (
    _Out_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExCleanupAutoExpandPushLock (
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExFreeAutoExpandPushLock (
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND PushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
ExAcquireAutoExpandPushLockExclusive (
    _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
FASTCALL
ExTryAcquireAutoExpandPushLockExclusive (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
PVOID
FASTCALL
ExAcquireAutoExpandPushLockShared (
    _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
FASTCALL
ExTryAcquireAutoExpandPushLockShared (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
ExReleaseAutoExpandPushLockExclusive (
    _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExReleaseAutoExpandPushLockShared (
    _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    _Inout_ PVOID PushLock,
    _In_ ULONG Flags)
{
    __debugbreak();
}


}; // extern "C"
}; // namespace Ex
