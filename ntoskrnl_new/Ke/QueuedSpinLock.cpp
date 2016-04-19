
#include "Kep.hpp"
#include "SpinLock.hpp"

extern "C" {

typedef enum _KSPIN_LOCK_QUEUE_NUMBER
{
    LockQueueUnusedSpare0,
    LockQueueUnusedSpare1,
    LockQueueUnusedSpare2,
    LockQueueUnusedSpare3,
    LockQueueVacbLock,
    LockQueueMasterLock,
    LockQueueNonPagedPoolLock,
    LockQueueIoCancelLock,
    LockQueueWorkQueueLock,
    LockQueueIoVpbLock,
    LockQueueIoDatabaseLock,
    LockQueueIoCompletionLock,
    LockQueueNtfsStructLock,
    LockQueueAfdWorkQueueLock,
    LockQueueBcbLock,
    LockQueueUnusedSpare15,
    LockQueueUnusedSpare16,
    LockQueueMaximumLock = LockQueueUnusedSpare16 + 1
} KSPIN_LOCK_QUEUE_NUMBER, *PKSPIN_LOCK_QUEUE_NUMBER;

typedef struct _KLOCK_QUEUE_HANDLE *PKLOCK_QUEUE_HANDLE;

_Must_inspect_result_
_Post_satisfies_(return == 1 || return == 0)
LOGICAL
FASTCALL
KeTryToAcquireQueuedSpinLock (
    _In_ KSPIN_LOCK_QUEUE_NUMBER Number,
    _Out_ _At_(*OldIrql, _IRQL_saves_) PKIRQL OldIrql)
{
    __debugbreak();
    return FALSE;
}

_Requires_lock_not_held_(Number)
_Acquires_lock_(Number)
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
FASTCALL
KeAcquireQueuedSpinLock (
    _In_ KSPIN_LOCK_QUEUE_NUMBER Number)
{
    __debugbreak();
    return 0;
}

_Requires_lock_held_(Number)
_Releases_lock_(Number)
VOID
FASTCALL
KeReleaseQueuedSpinLock (
    _In_ KSPIN_LOCK_QUEUE_NUMBER Number,
    _In_ KIRQL OldIrql)
{
    __debugbreak();
}

_Requires_lock_not_held_(*LockHandle)
_Acquires_lock_(*LockHandle)
_Post_same_lock_(*SpinLock, *LockHandle)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
FASTCALL
KeAcquireInStackQueuedSpinLockAtDpcLevel (
    _Inout_ PKSPIN_LOCK SpinLock,
    _Out_ PKLOCK_QUEUE_HANDLE LockHandle)
{
    __debugbreak();
}

_Requires_lock_held_(*LockHandle)
_Releases_lock_(*LockHandle)
_IRQL_requires_(DISPATCH_LEVEL)
VOID
FASTCALL
KeReleaseInStackQueuedSpinLockFromDpcLevel (
    _In_ PKLOCK_QUEUE_HANDLE LockHandle)
{
    __debugbreak();
}

_Must_inspect_result_
_Post_satisfies_(return == 1 || return == 0)
LOGICAL
FASTCALL
KeTryToAcquireQueuedSpinLockRaiseToSynch (
    _In_ KSPIN_LOCK_QUEUE_NUMBER Number,
    _Out_ _At_(*OldIrql, _IRQL_saves_) PKIRQL OldIrql)
{
    __debugbreak();
    return FALSE;
}

_Requires_lock_not_held_(Number)
_Acquires_lock_(Number)
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
FASTCALL
KeAcquireQueuedSpinLockRaiseToSynch (
    _In_ KSPIN_LOCK_QUEUE_NUMBER Number)
{
    __debugbreak();
    return 0;
}

_Requires_lock_not_held_(*LockHandle)
_Acquires_lock_(*LockHandle)
_Post_same_lock_(*SpinLock, *LockHandle)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_global_(QueuedSpinLock,LockHandle)
_IRQL_raises_(DISPATCH_LEVEL)
VOID
FASTCALL
KeAcquireInStackQueuedSpinLock (
    _Inout_ PKSPIN_LOCK SpinLock,
    _Out_ PKLOCK_QUEUE_HANDLE LockHandle)
{
    __debugbreak();
}

_Requires_lock_held_(*LockHandle)
_Releases_lock_(*LockHandle)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_restores_global_(QueuedSpinLock,LockHandle)
VOID
FASTCALL
KeReleaseInStackQueuedSpinLock (
    _In_ PKLOCK_QUEUE_HANDLE LockHandle)
{
    __debugbreak();
}

_Requires_lock_not_held_(*LockHandle)
_Acquires_lock_(*LockHandle)
_Post_same_lock_(*SpinLock, *LockHandle)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_global_(QueuedSpinLock,LockHandle)
VOID
FASTCALL
KeAcquireInStackQueuedSpinLockForDpc (
    _Inout_ PKSPIN_LOCK SpinLock,
    _Out_ PKLOCK_QUEUE_HANDLE LockHandle)
{
    __debugbreak();
}

_Requires_lock_held_(*LockHandle)
_Releases_lock_(*LockHandle)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_restores_global_(QueuedSpinLock,LockHandle)
VOID
FASTCALL
KeReleaseInStackQueuedSpinLockForDpc (
    _In_ PKLOCK_QUEUE_HANDLE LockHandle)
{
    __debugbreak();
}

// coped prototype from KeAcquireInStackQueuedSpinLock
_Requires_lock_not_held_(*LockHandle)
_Acquires_lock_(*LockHandle)
_Post_same_lock_(*SpinLock, *LockHandle)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_global_(QueuedSpinLock,LockHandle)
VOID
FASTCALL
KeAcquireInStackQueuedSpinLockRaiseToSynch (
    _Inout_ PKSPIN_LOCK SpinLock,
    _Out_ PKLOCK_QUEUE_HANDLE LockHandle)
{
    __debugbreak();
}

}; // extern "C"
