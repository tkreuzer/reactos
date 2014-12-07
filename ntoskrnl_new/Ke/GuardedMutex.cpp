
#include "Kep.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
KeInitializeGuardedMutex (
    _Out_ PKGUARDED_MUTEX Mutex)
{
    __debugbreak();
}

_Must_inspect_result_
_Success_(return != FALSE)
_IRQL_requires_max_(APC_LEVEL)
_Post_satisfies_(return == 1 || return == 0)
BOOLEAN
FASTCALL
KeTryToAcquireGuardedMutex (
    _When_ (return, _Acquires_exclusive_lock_(*_Curr_)) _Acquires_lock_(_Global_critical_region_)
    _Inout_ PKGUARDED_MUTEX Mutex)
{
    __debugbreak();
    return FALSE;
}

_Requires_lock_not_held_(*FastMutex)
_Acquires_lock_(*FastMutex)
_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
KeAcquireGuardedMutexUnsafe (
    _Inout_ PKGUARDED_MUTEX FastMutex)
{
    __debugbreak();
}

_Requires_lock_held_(*FastMutex)
_Releases_lock_(*FastMutex)
_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
KeReleaseGuardedMutexUnsafe (
    _Inout_ PKGUARDED_MUTEX FastMutex)
{
    __debugbreak();
}

_Acquires_lock_(_Global_critical_region_)
_Requires_lock_not_held_(*Mutex)
_Acquires_lock_(*Mutex)
_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
KeAcquireGuardedMutex (
    _Inout_ PKGUARDED_MUTEX Mutex)
{
    __debugbreak();
}

_Releases_lock_(_Global_critical_region_)
_Requires_lock_held_(*Mutex)
_Releases_lock_(*Mutex)
_IRQL_requires_max_(APC_LEVEL)
VOID
FASTCALL
KeReleaseGuardedMutex (
    _Inout_ PKGUARDED_MUTEX Mutex)
{
    __debugbreak();
}


}; // extern "C"
