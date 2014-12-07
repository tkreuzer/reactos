
#include "Rtl.hpp"
#include "SplayTree.hpp"

extern "C" {

// ntifs.h
typedef struct _UNICODE_PREFIX_TABLE_ENTRY
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    struct _UNICODE_PREFIX_TABLE_ENTRY *NextPrefixTree;
    struct _UNICODE_PREFIX_TABLE_ENTRY *CaseMatch;
    RTL_SPLAY_LINKS Links;
    PUNICODE_STRING Prefix;
} UNICODE_PREFIX_TABLE_ENTRY, *PUNICODE_PREFIX_TABLE_ENTRY;

typedef struct _UNICODE_PREFIX_TABLE
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    PUNICODE_PREFIX_TABLE_ENTRY NextPrefixTree;
    PUNICODE_PREFIX_TABLE_ENTRY LastNextEntry;
} UNICODE_PREFIX_TABLE, *PUNICODE_PREFIX_TABLE;

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
RtlInitializeUnicodePrefix (
    _Out_ PUNICODE_PREFIX_TABLE PrefixTable)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
NTAPI
RtlInsertUnicodePrefix (
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ __drv_aliasesMem PUNICODE_STRING Prefix,
    _Out_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
RtlRemoveUnicodePrefix (
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
PUNICODE_PREFIX_TABLE_ENTRY
NTAPI
RtlFindUnicodePrefix (
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ PCUNICODE_STRING FullName,
    _In_ ULONG CaseInsensitiveIndex)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
PUNICODE_PREFIX_TABLE_ENTRY
NTAPI
RtlNextUnicodePrefix (
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ BOOLEAN Restart)
{
    __debugbreak();
    return NULL;
}

} // extern "C"
