
#include "HashTable.hpp"

extern "C" {

_Must_inspect_result_
_Success_(return != 0)
BOOLEAN
NTAPI
RtlCreateHashTable (
    _Inout_ _When_(NULL == *HashTable, _At_(*HashTable, __drv_allocatesMem(Mem)))
        PRTL_DYNAMIC_HASH_TABLE *HashTable,
    _In_ ULONG Shift,
    _Reserved_ ULONG Flags)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_Success_(return != 0)
BOOLEAN
NTAPI
RtlCreateHashTableEx (
    _Inout_ _When_(NULL == *HashTable, _At_(*HashTable, __drv_allocatesMem(Mem)))
        PRTL_DYNAMIC_HASH_TABLE *HashTable,
    _In_ ULONG InitialSize,
    _In_ ULONG Shift,
    _Reserved_ ULONG Flags)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlDeleteHashTable (
    _In_ _When_((HashTable->Flags & RTL_HASH_ALLOCATED_HEADER), __drv_freesMem(Mem) _Post_invalid_)
        PRTL_DYNAMIC_HASH_TABLE HashTable)
{
    __debugbreak();
}

BOOLEAN
NTAPI
RtlInsertEntryHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ __drv_aliasesMem PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
    _In_ ULONG_PTR Signature,
    _Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
RtlRemoveEntryHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
    _Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
RtlExpandHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
RtlContractHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlGetNextEntryHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlLookupEntryHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ ULONG_PTR Signature,
    _Out_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context)
{
    __debugbreak();
    return NULL;
}

BOOLEAN
NTAPI
RtlInitEnumerationHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlEnumerateEntryHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
RtlEndEnumerationHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
}

BOOLEAN
NTAPI
RtlInitWeakEnumerationHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlWeaklyEnumerateEntryHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
RtlEndWeakEnumerationHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
}

#if 0 // not exported
BOOLEAN
NTAPI
RtlInitStrongEnumerationHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlStronglyEnumerateEntryHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
RtlEndStrongEnumerationHashTable (
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
    __debugbreak();
}
#endif // 0

} // extern "C"
