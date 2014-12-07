
#include "Rtl.hpp"
#include "SplayTree.hpp"

extern "C" {

typedef struct _PREFIX_TABLE_ENTRY {
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    struct _PREFIX_TABLE_ENTRY *NextPrefixTree;
    RTL_SPLAY_LINKS Links;
    PSTRING Prefix;
} PREFIX_TABLE_ENTRY;
typedef PREFIX_TABLE_ENTRY *PPREFIX_TABLE_ENTRY;

typedef struct _PREFIX_TABLE {
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    PPREFIX_TABLE_ENTRY NextPrefixTree;
} PREFIX_TABLE;
typedef PREFIX_TABLE *PPREFIX_TABLE;

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PfxInitialize (
    _Out_ PPREFIX_TABLE PrefixTable)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
NTAPI
PfxInsertPrefix (
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ __drv_aliasesMem PSTRING Prefix,
    _Out_ PPREFIX_TABLE_ENTRY PrefixTableEntry)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PfxRemovePrefix (
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PPREFIX_TABLE_ENTRY PrefixTableEntry)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
PPREFIX_TABLE_ENTRY
NTAPI
PfxFindPrefix (
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PSTRING FullName)
{
    __debugbreak();
    return NULL;
}

} // extern "C"
