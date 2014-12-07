
#include "Exp.hpp"

extern "C" {

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
ExInitializeResourceLite (
    _Out_ PERESOURCE Resource)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
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
BOOLEAN
NTAPI
ExTryToAcquireResourceExclusiveLite (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_exclusive_lock_(*_Curr_))
        PERESOURCE Resource)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
BOOLEAN
NTAPI
ExAcquireResourceExclusiveLite (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_exclusive_lock_(*_Curr_))
        PERESOURCE Resource,
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
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG
NTAPI
ExGetExclusiveWaiterCount (
    _In_ PERESOURCE Resource)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
BOOLEAN
NTAPI
ExAcquireResourceSharedLite (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_shared_lock_(*_Curr_))
        PERESOURCE Resource,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG
NTAPI
ExIsResourceAcquiredSharedLite (
    _In_ PERESOURCE Resource)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG
NTAPI
ExGetSharedWaiterCount (
    _In_ PERESOURCE Resource)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
BOOLEAN
NTAPI
ExAcquireSharedWaitForExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_lock_(*_Curr_))
        PERESOURCE Resource,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
BOOLEAN
NTAPI
ExAcquireSharedStarveExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_shared_lock_(*_Curr_))
        PERESOURCE Resource,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExConvertExclusiveToSharedLite (
    _Inout_ _Requires_lock_held_(*_Curr_) PERESOURCE Resource)
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
PVOID
NTAPI
ExEnterCriticalRegionAndAcquireResourceExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_exclusive_lock_(*_Curr_)
        PERESOURCE Resource)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
PVOID
NTAPI
ExEnterCriticalRegionAndAcquireResourceShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_shared_lock_(*_Curr_)
    PERESOURCE Resource)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
PVOID
NTAPI
ExEnterCriticalRegionAndAcquireSharedWaitForExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PERESOURCE Resource)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Releases_lock_(_Global_critical_region_)
VOID
FASTCALL
ExReleaseResourceAndLeaveCriticalRegion(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PERESOURCE Resource)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Acquires_lock_(_Global_priority_region_)
PVOID
NTAPI
ExEnterPriorityRegionAndAcquireResourceExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_exclusive_lock_(*_Curr_)
        PERESOURCE Resource)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Acquires_lock_(_Global_priority_region_)
PVOID
NTAPI
ExEnterPriorityRegionAndAcquireResourceShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_shared_lock_(*_Curr_)
        PERESOURCE Resource)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Releases_lock_(_Global_critical_region_)
_Releases_lock_(_Global_priority_region_)
VOID
FASTCALL
ExReleaseResourceAndLeavePriorityRegion(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PERESOURCE Resource)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
NTAPI
ExReleaseResourceForThreadLite(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
        PERESOURCE Resource,
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

