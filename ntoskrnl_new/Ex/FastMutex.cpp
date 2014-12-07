
#include "FastMutex.hpp"

extern "C" {

_Must_inspect_result_
_Success_(return!=FALSE)
_IRQL_raises_(APC_LEVEL)
_IRQL_saves_global_(OldIrql, FastMutex)
BOOLEAN
FASTCALL
ExTryToAcquireFastMutex (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PFAST_MUTEX FastMutex)
{
    __debugbreak();
    return FALSE;
}

_IRQL_raises_(APC_LEVEL)
_IRQL_saves_global_(OldIrql, FastMutex)
VOID
FASTCALL
ExAcquireFastMutex (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExAcquireFastMutexUnsafe (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
VOID
FASTCALL
ExEnterCriticalRegionAndAcquireFastMutexUnsafe (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

_IRQL_requires_(APC_LEVEL)
_IRQL_restores_global_(OldIrql, FastMutex)
VOID
FASTCALL
ExReleaseFastMutex (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExReleaseFastMutexUnsafe(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Releases_lock_(_Global_critical_region_)
VOID
FASTCALL
ExReleaseFastMutexUnsafeAndLeaveCriticalRegion(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

#ifdef _M_IX86

VOID
FASTCALL
ExiAcquireFastMutex (
    _Inout_ PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

VOID
FASTCALL
ExiReleaseFastMutex (
    _Inout_ PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

BOOLEAN
FASTCALL
ExiTryToAcquireFastMutex (
    _Inout_ PFAST_MUTEX FastMutex)
{
    __debugbreak();
    return FALSE;
}

#endif // _M_IX86

}; // extern "C"

