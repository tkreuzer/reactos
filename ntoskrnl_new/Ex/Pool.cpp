
#include "Exp.hpp"

// wdm.h
typedef _Enum_is_bitflag_ enum _EX_POOL_PRIORITY
{
    LowPoolPriority,
    LowPoolPrioritySpecialPoolOverrun = 8,
    LowPoolPrioritySpecialPoolUnderrun = 9,
    NormalPoolPriority = 16,
    NormalPoolPrioritySpecialPoolOverrun = 24,
    NormalPoolPrioritySpecialPoolUnderrun = 25,
    HighPoolPriority = 32,
    HighPoolPrioritySpecialPoolOverrun = 40,
    HighPoolPrioritySpecialPoolUnderrun = 41
} EX_POOL_PRIORITY;

extern "C" {

DECLSPEC_DEPRECATED_DDK                     // Use ExAllocatePoolWithTag
__drv_preferredFunction("ExAllocatePoolWithTag",
                        "No tag interferes with debugging.")
__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
PVOID
NTAPI
ExAllocatePool (
    __drv_strictTypeMatch(__drv_typeExpr) _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes)
{
    __debugbreak();
    return 0;
}

DECLSPEC_DEPRECATED_DDK                     // Use ExAllocatePoolWithQuotaTag
__drv_preferredFunction("ExAllocatePoolWithQuotaTag",
                        "No tag interferes with debugging.")
__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) != 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) == 0, _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
PVOID
NTAPI
ExAllocatePoolWithQuota (
    __drv_strictTypeMatch(__drv_typeExpr) _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes)
{
    __debugbreak();
    return 0;
}

__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
NTAPI
ExAllocatePoolWithTag (
    _In_ __drv_strictTypeMatch(__drv_typeExpr) POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag)
{
    __debugbreak();
    return 0;
}

__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) != 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) == 0, _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
PVOID
NTAPI
ExAllocatePoolWithQuotaTag (
    _In_ __drv_strictTypeMatch(__drv_typeExpr) POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag)
{
    __debugbreak();
    return 0;
}

__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
PVOID
NTAPI
ExAllocatePoolWithTagPriority (
    _In_ __drv_strictTypeMatch(__drv_typeCond) POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag,
    _In_ __drv_strictTypeMatch(__drv_typeExpr) EX_POOL_PRIORITY Priority)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExFreePool (
    _Pre_notnull_ __drv_freesMem(Mem) PVOID P)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExFreePoolWithTag (
    _Pre_notnull_ __drv_freesMem(Mem) PVOID P,
    _In_ ULONG Tag)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
SIZE_T
NTAPI
ExQueryPoolBlockSize (
    _In_ PVOID PoolBlock,
    _Out_ PBOOLEAN QuotaCharged)
{
    __debugbreak();
    return 0;
}

}; // extern "C"

