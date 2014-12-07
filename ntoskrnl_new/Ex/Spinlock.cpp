
#include "Exp.hpp"

#include <Ke/Ke.hpp>
#include <Ke/Irql.hpp>

/*!
    \todo
        - Set Waiting bit
        - Update performance counters
        - Add Hypervisor enlightenments
*/

namespace Ex {

typedef union _EX_SPIN_LOCK
{
    volatile LONG_PTR Long;
    volatile PVOID Ptr;
    struct
    {
        ULONG_PTR Shared : sizeof(ULONG_PTR) * 8 - 2;
        ULONG_PTR Waiting : 1;
        ULONG_PTR Exclusive : 1;
    };
} EX_SPIN_LOCK, *PEX_SPIN_LOCK;

extern "C" {

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExAcquireSpinLockExclusiveAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    __debugbreak();
}

_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
NTAPI
ExAcquireSpinLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExAcquireSpinLockSharedAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    __debugbreak();
}

_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
KIRQL
NTAPI
ExAcquireSpinLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockExclusiveFromDpcLevel (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    __debugbreak();
}

_IRQL_requires_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql)
{
    __debugbreak();
}

_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockSharedFromDpcLevel (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock)
{
    __debugbreak();
}

_IRQL_requires_(DISPATCH_LEVEL)
VOID
NTAPI
ExReleaseSpinLockShared (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PEX_SPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_(DISPATCH_LEVEL)
_Post_satisfies_(return == 0 || return == 1)
LOGICAL
NTAPI
ExTryConvertSharedSpinLockExclusive (
    _Inout_ PEX_SPIN_LOCK SpinLock)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"
}; // namespace Ex


