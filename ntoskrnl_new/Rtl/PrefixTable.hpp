
#pragma once

#include "String.hpp"

template<typename _TCHAR>
struct TPREFIX_TABLE_ENTRY
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    struct PREFIX_TABLE_ENTRY *NextPrefixTree;
    struct PREFIX_TABLE_ENTRY *CaseMatch;
    RTL_SPLAY_LINKS Links;
    TSTRING<_TCHAR> *Prefix;
};

template<typename _TCHAR>
class TPREFIX_TABLE
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    TPPREFIX_TABLE_ENTRY<_TCHAR> NextPrefixTree;
    TPPREFIX_TABLE_ENTRY<_TCHAR> LastNextEntry;

private:



public:

    _IRQL_requires_max_(PASSIVE_LEVEL)
    TPREFIX_TABLE (
        VOID
        );

    _IRQL_requires_max_(PASSIVE_LEVEL)
    BOOLEAN
    InsertPrefix (
        _In_ __drv_aliasesMem PSTRING Prefix,
        _Out_ PPREFIX_TABLE_ENTRY PrefixTableEntry
        );

    _IRQL_requires_max_(PASSIVE_LEVEL)
    VOID
    RemovePrefix (
        _In_ PPREFIX_TABLE_ENTRY PrefixTableEntry
        );

    _IRQL_requires_max_(PASSIVE_LEVEL)
    _Must_inspect_result_
    PPREFIX_TABLE_ENTRY
    FindPrefix (
        _In_ PSTRING FullName
        );

    _IRQL_requires_max_(PASSIVE_LEVEL)
    _Must_inspect_result_
    PUNICODE_PREFIX_TABLE_ENTRY
    NextPrefix (
        _In_ BOOLEAN Restart
        );

};

