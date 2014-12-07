
#include "Exp.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExInitializeRundownProtectionCacheAware(
    _Out_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    _In_ SIZE_T RunRefSize)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExInitializeRundownProtectionCacheAwareEx (
    _Out_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    _In_ ULONG Flags)
{
    __debugbreak();
}

VOID
FASTCALL
ExReInitializeRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExCleanupRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
SIZE_T
NTAPI
ExSizeOfRundownProtectionCacheAware (
    VOID)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PEX_RUNDOWN_REF_CACHE_AWARE
NTAPI
ExAllocateCacheAwareRundownProtection(
    __drv_strictTypeMatch(__drv_typeExpr) _In_ POOL_TYPE PoolType,
    _In_ ULONG PoolTag)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExFreeCacheAwareRundownProtection(
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware)
{
    __debugbreak();
}

_Must_inspect_result_
_Post_satisfies_(return==0 || return==1)
BOOLEAN
FASTCALL
ExAcquireRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_Post_satisfies_(return==0 || return==1)
BOOLEAN
FASTCALL
ExAcquireRundownProtectionCacheAwareEx (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    _In_ ULONG Count)
{
    __debugbreak();
    return 0;
}

VOID
FASTCALL
ExReleaseRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware)
{
    __debugbreak();
}

VOID
FASTCALL
ExReleaseRundownProtectionCacheAwareEx (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRef,
    _In_ ULONG Count)
{
    __debugbreak();
}

VOID
FASTCALL
ExRundownCompletedCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware)
{
    __debugbreak();
}

VOID
FASTCALL
ExWaitForRundownProtectionReleaseCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRef)
{
    __debugbreak();
}

}; // extern "C"
