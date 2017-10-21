
#include "Exp.hpp"
#include "Resource.hpp"
#include "Ps/Ps.hpp"

/*
        State
    #   Act/Excl ActiveEntries
    ---------------------------------
    0 -  0 / 0   0
    1 -  0 / 0   1  #0 => Acquire 1
    2 -  1 / 1   1  #1 -> Acquire Exclusive
    3 -  1 / 0   1  #1 -> Acquire Shared
    4 -  1 / 0   x  #3,#4 -> Acquire multiple shared
   (5 -  0 / 0   1  #3 -> release shared (mixed state))
    6 -  0 / 0   x  #4 -> release shared (mixed state)

    0 -> 1
    1 -> 2
    2 -> 1
    1 -> 0
    1 -> 3
    3 -> 4
    3 -> 1
    4 -> 3
    4 -> 6
    1 -> 0
    6 -> 3
    6 -> 4

*/

namespace Ex {

RESOURCE::RESOURCE (
    VOID) :
        _SharedWaiters()
{
    RtlZeroMemory(this, sizeof(*this));
    InitializeListHead(&_SystemResourcesList);
    _OwnerTable = NULL;
    _State.Long = 0;
    _ExclusiveWaitGate = NULL;
    _OwnerEntry.OwnerThread = NULL;
    _OwnerEntry.TableSize = 0;
    _ActiveEntries = 0;
    _ContentionCount = 0;
    _NumberOfSharedWaiters = 0;
    _NumberOfExclusiveWaiters = 0;
    _Address = NULL;
    _SpinLock = 0;
}

RESOURCE::~RESOURCE (
    VOID)
{
    NT_ASSERT(_State.ActiveCount == 0);
    NT_ASSERT(_State.Exclusive == 0);
    NT_ASSERT(_OwnerEntry.OwnerThread == 0);
    NT_ASSERT(_ActiveEntries == 0);
    NT_ASSERT(_ContentionCount == 0);
    NT_ASSERT(_NumberOfSharedWaiters == 0);
    NT_ASSERT(_NumberOfExclusiveWaiters == 0);

    if (_ExclusiveWaitGate != NULL)
    {
        delete _ExclusiveWaitGate;
    }

    if (_OwnerTable != NULL)
    {
        //delete _OwnerTable;
    }
}

VOID
RESOURCE::AllocateWaitGate (
    VOID)
{
    Ke::PGATE WaitGate;

    WaitGate = new Ke::GATE(FALSE);
    if (WaitGate == NULL)
    {
        /// FIXME
        NT_ASSERT(FALSE);
    }

    if (InterlockedExchangePointer((PVOID*)&_ExclusiveWaitGate, WaitGate) != NULL)
    {
        ExFreePoolWithTag(WaitGate, 'aGeR');
    }
}

BOOLEAN
RESOURCE::WaitExclusive (
    VOID)
{
    if (_ExclusiveWaitGate == NULL)
    {
        AllocateWaitGate();
        NT_ASSERT(_ExclusiveWaitGate != NULL);
    }

    /* Increment waiter count */
    InterlockedIncrementUL(&_NumberOfExclusiveWaiters);

    /* Check the state again */
    if (_ActiveEntries == 0)
    {
        /* The resource was already released, return FALSE to indicate that */
        InterlockedDecrementUL(&_NumberOfExclusiveWaiters);
        return FALSE;
    }

    _ExclusiveWaitGate->Wait();

    /* Decrement waiter count */
    InterlockedIncrementUL(&_NumberOfExclusiveWaiters);

    return TRUE;
}


BOOLEAN
RESOURCE::AcquireExclusive (
    _In_ ULONG Flags)
{
    RESOURCE_STATE State;
    ULONG ActiveEntries;

    /* Check if we already own the resource exclusively */
    if (IsAcquiredExclusiveLite())
    {
        /* Bump up our owner count and we are done */
        NT_ASSERT(_OwnerEntry.OwnerCount > 0);
        _OwnerEntry.OwnerCount++;
        return TRUE;
    }

    /// \todo FIXME: use ReadNoFence
    ActiveEntries = _ActiveEntries;

    for (;;)
    {
        /* Check if the resource is free */
        if (ActiveEntries == 0)
        {
            /* Try to acquire it exclusively */
            ActiveEntries = InterlockedCompareExchangeAcquire(&_ActiveEntries, 1, 0);
            if (ActiveEntries != 0)
            {
                continue;
            }

            State.Long = _State.Long;
            NT_ASSERT(State.ActiveCount == 0);
            NT_ASSERT(State.Exclusive == 0);
            State.ActiveCount = 1;
            State.Exclusive = 1;
            _State.Long = State.Long;

            NT_ASSERT(_OwnerEntry.OwnerThread == NULL);
            _OwnerEntry.OwnerThread = (ULONG_PTR)KeGetCurrentThread();

            /* Set owner count */
            NT_ASSERT(_OwnerEntry.OwnerCount == 0);
            _OwnerEntry.OwnerCount = 1;

            return TRUE;
        }

        /* Bail out, if waiting was not requested */
        if (!FlagOn(Flags, FLAG_WAIT))
        {
            return FALSE;
        }

        /* Wait for release */
        if (WaitExclusive() == FALSE)
        {
            continue;
        }

        /* Check if we returned with an exclusive lock */ /// FIXME: race condition!
        if (_State.Exclusive == 1)
        {
            NT_ASSERT(_OwnerEntry.OwnerCount == 0);
            NT_ASSERT(_ActiveEntries >= 1);

            /* Set OwnerCount to 1 */
            _OwnerEntry.OwnerCount = 1;
            return TRUE;
        }

        continue;
    }
}

BOOLEAN
RESOURCE::CanAcquireShared (
    _In_ ULONG Flags)
{
    /* Check if the resource is free */
    if (_ActiveEntries == 0)
    {
        return TRUE;
    }

    /* Check if the resource is owned exclusively */
    if ((_State.Exclusive != 0) || (_State.ActiveCount == 0))
    {
        /* Need to wait */
        return FALSE;
    }

    /* Check if there are exclusive waiters */
    if ((_NumberOfExclusiveWaiters > 0) &&
        !FlagOn(Flags, FLAG_STARVE_EXCLUSIVE))
    {
        /* Need to wait */
        return FALSE;
    }

    /// \todo FIXME: need to handle FLAG_WAIT_FOR_EXCLUSIVE

    return TRUE;
}

VOID
RESOURCE::WaitShared (
    _In_ ULONG Flags)
{

    _SharedWaiters.Enqueue();

    /* Increment waiter count */
    InterlockedIncrementUL(&_NumberOfSharedWaiters);

    /* Check again if we can acquire the resource shared */
    if (!CanAcquireShared(Flags))
    {
        /* We can't, so wait as expected */
        _SharedWaiters.Wait();
    }
    else
    {
        /* We can, so things changed. We need to release the whole waiter queue */
        _SharedWaiters.WakeAll();
    }

    InterlockedDecrementUL(&_NumberOfSharedWaiters);

    return FALSE;
}

BOOLEAN
RESOURCE::AcquireShared (
    _In_ ULONG Flags)
{
    RESOURCE_STATE State;
    ULONG ActiveEntries;

    /* Check if we already own the resource exclusively */
    if (IsAcquiredExclusiveLite())
    {
        /* Bump up our owner count and we are done */
        NT_ASSERT(_OwnerEntry.OwnerCount > 0);
        _OwnerEntry.OwnerCount++;
        return TRUE;
    }

    for (;;)
    {
        /* Quick check if we can acquire the resource shared */
        if (!CanAcquireShared(Flags))
        {
            /* Bail out, if we shall not wait */
            if (!FlagOn(Flags, FLAG_WAIT))
            {
                return FALSE;
            }

            WaitShared(Flags);
            continue;
        }

        /* Increment active count */
        ActiveEntries = InterlockedIncrementAcquire(&_ActiveEntries);
        NT_ASSERT(ActiveEntries > 0);

        /* Re-read the state */
        State.Long = _State.Long;

        /* Check if this is the first acquire */
        if (ActiveEntries == 1)
        {
            /* */
            NT_ASSERT(State.ActiveCount == 0);
            NT_ASSERT(State.Exclusive == 0);

            _OwnerEntry.OwnerCount = 1;
            _OwnerEntry.OwnerThread = (ULONG_PTR)KeGetCurrentThread();

            /* Convert to a shared lock */
            State.ActiveCount = 1;
            _State.Long = State.Long;

            /* Check for shared waiters that sneaked in */
            if (_NumberOfSharedWaiters > 0)
            {
                /* Let them join in */
                _SharedWaiters.WakeAll();
            }

            return TRUE;
        }

        /* Check again if the resource is owned exclusively */
        if ((State.Exclusive != 0) || (State.ActiveCount == 0))
        {
            /* Need to release the additional reference and try again */
            InterlockedDecrement(&_ActiveEntries);
            continue;
        }

        break;
    }

    return TRUE;
}

VOID
RESOURCE::Release (
    VOID)
{
    RESOURCE_STATE State;
    LONG ActiveEntries, OldActiveEntries;

    NT_ASSERT(_ActiveEntries > 0);

    /// \todo FIXME: use ReadNoFence
    State.Long = _State.Long;

    /* Check if the resource is held exclusively */
    if (State.Exclusive != 0)
    {
        /* We must own the resource */
        NT_ASSERT(_OwnerEntry.OwnerThread == (ULONG_PTR)KeGetCurrentThread());

        /* Decrement the recursive acquire count */
        NT_ASSERT(_OwnerEntry.OwnerCount > 0);
        _OwnerEntry.OwnerCount--;
        if (_OwnerEntry.OwnerCount != 0)
        {
            return;
        }

        /* Reset owner */
        _OwnerEntry.OwnerThread = NULL;

        /* Check if there are only exclusive waiters */
        if ((_NumberOfExclusiveWaiters > 0) &&
            (_NumberOfSharedWaiters == 0))
        {
            /* Signal the next exclusive waiter and hand him the resource */
            _ExclusiveWaitGate->Signal();
            return;
        }

        State.ActiveCount = 0;
        State.Exclusive = 0;
        _State.Long = State.Long;

        /* Finally release the lock itself. We need to use an atomic decrement,
           since other threads can have incremented this value */
        InterlockedDecrement(&_ActiveEntries);

        /* Check if there are shared waiters */
        if (_NumberOfSharedWaiters > 0)
        {
            _SharedWaiters.WakeAll();
        }

        return;
    }

    /* The resource is acquired shared and we hold a reference,
       so no other thread can fully release it */
    NT_ASSERT(_State.ActiveCount == 1);

    /* Get the number of active entries */
    ActiveEntries = _ActiveEntries;
    NT_ASSERT(ActiveEntries > 0);

    for (;;)
    {
        if (ActiveEntries == 1)
        {
            /* Set ActiveCount to 0. We will either enter the 1st exclusive
               state or a mixed state. This might put waiters into a wait state! */
            _State.ActiveCount = 0;

            /* Reset owner count */
            _OwnerEntry.OwnerThread = NULL;

            ActiveEntries = InterlockedCompareExchangeAcquire(&_ActiveEntries, 0, 1);
            if (ActiveEntries != 1)
            {
                /* There are more shared owners, reset the ActiveCount to 1 */
                _State.ActiveCount = 1;
                _OwnerEntry.OwnerThread = (ULONG_PTR)KeGetCurrentThread();
                continue;
            }

            break;
        }
        else
        {
            OldActiveEntries = ActiveEntries;
            ActiveEntries = InterlockedCompareExchangeAcquire(&_ActiveEntries,
                                                              ActiveEntries - 1,
                                                              ActiveEntries);
            if (ActiveEntries != OldActiveEntries)
            {
                continue;
            }

            break;
        }
    }

    /* Check if there are exclusive waiters */
    if (_NumberOfExclusiveWaiters > 0)
    {
        /* Signal the next exclusive waiter */
        _ExclusiveWaitGate->Signal();
    }
}

}; // namespace Ex

extern "C" {

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
ExInitializeResourceLite (
    _Out_ PERESOURCE Resource)
{
    new ((PVOID)Resource) Ex::RESOURCE;
    return STATUS_SUCCESS;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
ExReinitializeResourceLite (
    _Inout_ PERESOURCE Resource)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
ExDeleteResourceLite (
    _Inout_ PERESOURCE Resource)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_When_(return!=0, _Acquires_exclusive_lock_(*Resource))
BOOLEAN
NTAPI
ExTryToAcquireResourceExclusiveLite (
    _Inout_ PERESOURCE Resource)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_When_(Wait!=0, _Acquires_exclusive_lock_(*Resource))
_When_(Wait!=0, _Post_satisfies_(return==1))
_When_(Wait==0, _Post_satisfies_(return==0 || return==1) _Must_inspect_result_)
_When_(return!=0, _Acquires_exclusive_lock_(*Resource))
BOOLEAN
NTAPI
ExAcquireResourceExclusiveLite (
  _Inout_ PERESOURCE Resource,
  _In_ _Literal_ BOOLEAN Wait)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
ExIsResourceAcquiredExclusiveLite (
    _In_ PERESOURCE Resource)
{
    return reinterpret_cast<Ex::PRESOURCE>(Resource)->IsAcquiredExclusiveLite();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG
NTAPI
ExGetExclusiveWaiterCount (
    _In_ PERESOURCE Resource)
{
    return reinterpret_cast<Ex::PRESOURCE>(Resource)->GetExclusiveWaiterCount();
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_When_(Wait!=0, _Post_satisfies_(return==1))
_When_(Wait==0, _Post_satisfies_(return==0 || return==1) _Must_inspect_result_)
_When_(return!=0, _Acquires_shared_lock_(*Resource))
BOOLEAN
NTAPI
ExAcquireResourceSharedLite (
    _Inout_ PERESOURCE Resource,
    _In_ BOOLEAN Wait)
{
    ULONG Flags;

    Flags = Wait ? Ex::RESOURCE::FLAG_WAIT : 0;
    return reinterpret_cast<Ex::PRESOURCE>(Resource)->AcquireShared(Flags);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG
NTAPI
ExIsResourceAcquiredSharedLite (
    _In_ PERESOURCE Resource)
{
    return reinterpret_cast<Ex::PRESOURCE>(Resource)->IsAcquiredSharedLite();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG
NTAPI
ExGetSharedWaiterCount (
    _In_ PERESOURCE Resource)
{
    return reinterpret_cast<Ex::PRESOURCE>(Resource)->GetSharedWaiterCount();
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_When_(Wait!=0, _Post_satisfies_(return==1))
_When_(Wait==0, _Post_satisfies_(return==0 || return==1) _Must_inspect_result_)
_When_(return!=0, _Acquires_lock_(*Resource))
BOOLEAN
NTAPI
ExAcquireSharedWaitForExclusive (
    _Inout_ PERESOURCE Resource,
    _In_ BOOLEAN Wait)
{
    ULONG Flags;

    Flags = Ex::RESOURCE::FLAG_WAIT_FOR_EXCLUSIVE;
    Flags |= Wait ? Ex::RESOURCE::FLAG_WAIT : 0;
    return reinterpret_cast<Ex::PRESOURCE>(Resource)->AcquireShared(Flags);
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
_When_(return!=0, _Acquires_shared_lock_(*Resource))
BOOLEAN
NTAPI
ExAcquireSharedStarveExclusive (
    _Inout_ PERESOURCE Resource,
    _In_ BOOLEAN Wait)
{
    ULONG Flags;

    Flags = Ex::RESOURCE::FLAG_STARVE_EXCLUSIVE;
    Flags |= Wait ? Ex::RESOURCE::FLAG_WAIT : 0;
    return reinterpret_cast<Ex::PRESOURCE>(Resource)->AcquireShared(Flags);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_exclusive_lock_held_(*Resource)
VOID
NTAPI
ExConvertExclusiveToSharedLite (
    _Inout_ PERESOURCE Resource)
{
    __debugbreak();
}

_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_held_(*Resource)
_Releases_lock_(*Resource)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FASTCALL
ExReleaseResourceLite (
    _Inout_ PERESOURCE Resource)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_Acquires_exclusive_lock_(*Resource)
PVOID
NTAPI
ExEnterCriticalRegionAndAcquireResourceExclusive (
    _Inout_ PERESOURCE Resource)
{
    /* Enter a critical region */
    KeEnterCriticalRegion();

    /* Call the "lite" function */
    ExAcquireResourceExclusiveLite(Resource, TRUE);

    return NULL;//KeGetCurrentThread()->Win32Thread;
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_Acquires_shared_lock_(*Resource)
PVOID
NTAPI
ExEnterCriticalRegionAndAcquireResourceShared (
    _Inout_ PERESOURCE Resource)
{
    /* Enter a critical region */
    KeEnterCriticalRegion();

    /* Call the "lite" function */
    ExAcquireResourceSharedLite(Resource, TRUE);

    return NULL;//KeGetCurrentThread()->Win32Thread;
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Requires_lock_not_held_(*Resource)
_Acquires_lock_(*Resource)
PVOID
NTAPI
ExEnterCriticalRegionAndAcquireSharedWaitForExclusive (
    _Inout_ PERESOURCE Resource)
{
    /* Enter a critical region */
    KeEnterCriticalRegion();

    /* Call the "lite" function */
    ExAcquireSharedWaitForExclusive(Resource, TRUE);

    return NULL;//KeGetCurrentThread()->Win32Thread;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Releases_lock_(_Global_critical_region_)
_Requires_lock_held_(*Resource)
_Releases_lock_(*Resource)
VOID
FASTCALL
ExReleaseResourceAndLeaveCriticalRegion (
    _Inout_ PERESOURCE Resource)
{
    ExReleaseResourceLite(Resource);

    KeLeaveCriticalRegion();
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Acquires_lock_(_Global_priority_region_)
_Requires_lock_not_held_(*Resource)
_Acquires_exclusive_lock_(*Resource)
PVOID
NTAPI
ExEnterPriorityRegionAndAcquireResourceExclusive (
    _Inout_ PERESOURCE Resource)
{
    /* Enter a priority region */
    PsEnterPriorityRegion();

    /* Call the "lite" function */
    ExAcquireResourceExclusiveLite(Resource, TRUE);

    return NULL;//KeGetCurrentThread()->Win32Thread;
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Acquires_lock_(_Global_priority_region_)
_Requires_lock_not_held_(*Resource)
_Acquires_shared_lock_(*Resource)
PVOID
NTAPI
ExEnterPriorityRegionAndAcquireResourceShared (
    _Inout_ PERESOURCE Resource)
{
    /* Enter a priority region */
    PsEnterPriorityRegion();

    /* Call the "lite" function */
    ExAcquireResourceSharedLite(Resource, TRUE);

    return NULL;//KeGetCurrentThread()->Win32Thread;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Releases_lock_(_Global_critical_region_)
_Releases_lock_(_Global_priority_region_)
_Requires_lock_held_(*Resource)
_Releases_lock_(*Resource)
VOID
FASTCALL
ExReleaseResourceAndLeavePriorityRegion(
    _Inout_ PERESOURCE Resource)
{
    ExReleaseResourceLite(Resource);

    PsLeavePriorityRegion();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_held_(*Resource)
_Releases_lock_(*Resource)
VOID
NTAPI
ExReleaseResourceForThreadLite(
    _Inout_ PERESOURCE Resource,
    _In_ ERESOURCE_THREAD ResourceThreadId)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExDisableResourceBoostLite (
    _In_ PERESOURCE Resource)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExSetResourceOwnerPointer (
    _Inout_ PERESOURCE Resource,
    _In_ PVOID OwnerPointer)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExSetResourceOwnerPointerEx (
    _Inout_ PERESOURCE Resource,
    _In_ PVOID OwnerPointer,
    _In_ ULONG Flags)
{
    __debugbreak();
}

}; // extern "C"

