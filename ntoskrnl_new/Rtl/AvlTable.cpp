
#include "AvlTable.hpp"

extern "C" {

VOID
NTAPI
RtlInitializeGenericTableAvl (
    _Out_ PRTL_AVL_TABLE Table,
    _In_ PRTL_AVL_COMPARE_ROUTINE CompareRoutine,
    _In_ PRTL_AVL_ALLOCATE_ROUTINE AllocateRoutine,
    _In_ PRTL_AVL_FREE_ROUTINE FreeRoutine,
    _In_opt_ PVOID TableContext)
{
    __debugbreak();
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlIsGenericTableEmptyAvl (
    _In_ PRTL_AVL_TABLE Table)
{
    __debugbreak();
    return FALSE;
}

ULONG
NTAPI
RtlNumberGenericTableElementsAvl (
    _In_ PRTL_AVL_TABLE Table)
{
    __debugbreak();
    return 0;
}

PVOID
NTAPI
RtlInsertElementGenericTableAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ CLONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement)
{
    __debugbreak();
    return NULL;
}

PVOID
NTAPI
RtlInsertElementGenericTableFullAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ CLONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement,
    _In_ PVOID NodeOrParent,
    _In_ TABLE_SEARCH_RESULT SearchResult)
{
    __debugbreak();
    return NULL;
}

BOOLEAN
NTAPI
RtlDeleteElementGenericTableAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlDeleteElementGenericTableAvlEx (
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID NodeOrParent)
{
    __debugbreak();
}

_Must_inspect_result_
PVOID
NTAPI
RtlGetElementGenericTableAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_ ULONG I)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PVOID
NTAPI
RtlLookupElementGenericTableAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer)
{
    __debugbreak();
    return NULL;
}

PVOID
NTAPI
RtlLookupElementGenericTableFullAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID *NodeOrParent,
    _Out_ TABLE_SEARCH_RESULT *SearchResult)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PVOID
NTAPI
RtlLookupFirstMatchingElementGenericTableAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID *RestartKey)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PVOID
NTAPI
RtlEnumerateGenericTableAvl (
    _In_ PRTL_AVL_TABLE Table,
    _In_ BOOLEAN Restart)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PVOID
NTAPI
RtlEnumerateGenericTableWithoutSplayingAvl (
    _In_ PRTL_AVL_TABLE Table,
    _Inout_ PVOID *RestartKey)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PVOID
NTAPI
RtlEnumerateGenericTableLikeADirectory (
    _In_ PRTL_AVL_TABLE Table,
    _In_opt_ PRTL_AVL_MATCH_FUNCTION MatchFunction,
    _In_opt_ PVOID MatchData,
    _In_ ULONG NextFlag,
    _Inout_ PVOID *RestartKey,
    _Inout_ PULONG DeleteCount,
    _In_ PVOID Buffer)
{
    __debugbreak();
    return NULL;
}

// undocumented
NTSTATUS
NTAPI
RtlAvlInsertNodeEx (
    PVOID P1,
    PVOID P2,
    PVOID P3,
    PVOID P4)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
RtlAvlRemoveNode (
    PVOID P1,
    PVOID P2)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//@ stub RtlAvlRemoveNode

} // extern "C"
