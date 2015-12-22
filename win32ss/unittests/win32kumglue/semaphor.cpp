#include <win32k.h>

extern "C" {

HSEMAPHORE
APIENTRY
EngCreateSemaphore(
    VOID)
{
    __debugbreak();
    return NULL;
}

_Requires_lock_not_held_(*hsem)
_Acquires_exclusive_lock_(*hsem)
_Acquires_lock_(_Global_critical_region_)
VOID
APIENTRY
EngAcquireSemaphore(
    _Inout_ HSEMAPHORE hsem)
{
    __debugbreak();
}

_Requires_lock_held_(*hsem)
_Releases_lock_(*hsem)
_Releases_lock_(_Global_critical_region_)
VOID
APIENTRY
EngReleaseSemaphore(
    _Inout_ HSEMAPHORE hsem)
{
    __debugbreak();
}

_Acquires_lock_(_Global_critical_region_)
_Requires_lock_not_held_(*hsem)
_Acquires_shared_lock_(*hsem)
VOID
NTAPI
EngAcquireSemaphoreShared(
     _Inout_ HSEMAPHORE hsem)
{
    __debugbreak();
}

_Requires_lock_not_held_(*hsem)
VOID
APIENTRY
EngDeleteSemaphore(
    _Inout_ __drv_freesMem(Mem) HSEMAPHORE hsem)
{
    __debugbreak();
}

BOOL
APIENTRY
EngIsSemaphoreOwned(
    _In_ HSEMAPHORE hsem)
{
    __debugbreak();
    return TRUE;
}

BOOL
APIENTRY
EngIsSemaphoreOwnedByCurrentThread(
    _In_ HSEMAPHORE hsem)
{
    __debugbreak();
    return TRUE;
}

BOOL
APIENTRY
EngInitializeSafeSemaphore(
    _Out_ ENGSAFESEMAPHORE *Semaphore)
{
    __debugbreak();
    return TRUE;
}

VOID
APIENTRY
EngDeleteSafeSemaphore(
    _Inout_ _Post_invalid_ ENGSAFESEMAPHORE *pssem)
{
    __debugbreak();
}

} // extern "C"
