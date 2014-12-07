
#include "GenericTable.hpp"

extern "C" {

VOID
NTAPI
RtlInitializeGenericTable (
    _Out_ PRTL_GENERIC_TABLE Table,
    _In_ PRTL_GENERIC_COMPARE_ROUTINE CompareRoutine,
    _In_ PRTL_GENERIC_ALLOCATE_ROUTINE AllocateRoutine,
    _In_ PRTL_GENERIC_FREE_ROUTINE FreeRoutine,
    _In_opt_ PVOID TableContext)
{
    __debugbreak();
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlIsGenericTableEmpty (
    _In_ PRTL_GENERIC_TABLE Table)
{
    __debugbreak();
    return FALSE;
}

ULONG
NTAPI
RtlNumberGenericTableElements (
    _In_ PRTL_GENERIC_TABLE Table)
{
    __debugbreak();
    return 0;
}

PVOID
NTAPI
RtlInsertElementGenericTable (
    _In_ PRTL_GENERIC_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ CLONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement)
{
    __debugbreak();
    return NULL;
}

PVOID
NTAPI
RtlInsertElementGenericTableFull (
    _In_ PRTL_GENERIC_TABLE Table,
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
RtlDeleteElementGenericTable (
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer)
{
    __debugbreak();
    return FALSE;
}

PVOID
NTAPI
RtlGetElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ ULONG I)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PVOID
NTAPI
RtlLookupElementGenericTable (
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer)
{
    __debugbreak();
    return NULL;
}

PVOID
NTAPI
RtlLookupElementGenericTableFull (
    _In_ PRTL_GENERIC_TABLE Table,
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
RtlEnumerateGenericTable (
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ BOOLEAN Restart)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_Must_inspect_result_
PVOID
NTAPI
RtlEnumerateGenericTableWithoutSplaying (
    _In_ PRTL_GENERIC_TABLE Table,
    _Inout_ PVOID *RestartKey)
{
    __debugbreak();
    return NULL;
}

} // extern "C"
