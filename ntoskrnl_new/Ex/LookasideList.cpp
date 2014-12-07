
#include "Exp.hpp"

typedef struct _PAGED_LOOKASIDE_LIST *PPAGED_LOOKASIDE_LIST;
typedef struct _NPAGED_LOOKASIDE_LIST *PNPAGED_LOOKASIDE_LIST;
typedef struct _LOOKASIDE_LIST_EX *PLOOKASIDE_LIST_EX;

_IRQL_requires_same_
_Function_class_(ALLOCATE_FUNCTION)
typedef
PVOID
(NTAPI *PALLOCATE_FUNCTION) (
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag);

_IRQL_requires_same_
_Function_class_(ALLOCATE_FUNCTION_EX)
typedef
PVOID
(NTAPI *PALLOCATE_FUNCTION_EX) (
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag,
    _Inout_ PLOOKASIDE_LIST_EX Lookaside);

_IRQL_requires_same_
_Function_class_(FREE_FUNCTION)
typedef
VOID
(NTAPI *PFREE_FUNCTION) (
    _In_ PVOID Buffer);

_IRQL_requires_same_
_Function_class_(FREE_FUNCTION_EX)
typedef
VOID
(NTAPI *PFREE_FUNCTION_EX) (
    _In_ PVOID Buffer,
    _Inout_ PLOOKASIDE_LIST_EX Lookaside);

extern "C" {

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExInitializeNPagedLookasideList (
    _Out_ PNPAGED_LOOKASIDE_LIST Lookaside,
    _In_opt_ PALLOCATE_FUNCTION Allocate,
    _In_opt_ PFREE_FUNCTION Free,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag,
    _In_ USHORT Depth)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExInitializePagedLookasideList (
    _Out_ PPAGED_LOOKASIDE_LIST Lookaside,
    _In_opt_ PALLOCATE_FUNCTION Allocate,
    _In_opt_ PFREE_FUNCTION Free,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag,
    _In_ USHORT Depth)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
ExInitializeLookasideListEx (
    _Out_ PLOOKASIDE_LIST_EX Lookaside,
    _In_opt_ PALLOCATE_FUNCTION_EX Allocate,
    _In_opt_ PFREE_FUNCTION_EX Free,
    _In_ POOL_TYPE PoolType,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag,
    _In_ USHORT Depth)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExDeleteNPagedLookasideList (
    _Inout_ PNPAGED_LOOKASIDE_LIST Lookaside)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExDeletePagedLookasideList (
    _Inout_ PPAGED_LOOKASIDE_LIST Lookaside)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExDeleteLookasideListEx (
    _Inout_ PLOOKASIDE_LIST_EX Lookaside)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExFlushLookasideListEx (
    _Inout_ PLOOKASIDE_LIST_EX Lookaside)
{
    __debugbreak();
}

}; // extern "C"


