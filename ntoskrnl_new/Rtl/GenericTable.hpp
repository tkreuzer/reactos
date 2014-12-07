
#pragma once

#include "SplayTree.hpp"

typedef enum _TABLE_SEARCH_RESULT
{
    TableEmptyTree,
    TableFoundNode,
    TableInsertAsLeft,
    TableInsertAsRight
} TABLE_SEARCH_RESULT;

typedef enum _RTL_GENERIC_COMPARE_RESULTS
{
    GenericLessThan,
    GenericGreaterThan,
    GenericEqual
} RTL_GENERIC_COMPARE_RESULTS;

struct _RTL_GENERIC_TABLE;

typedef
_IRQL_requires_same_
_Function_class_(RTL_GENERIC_COMPARE_ROUTINE)
RTL_GENERIC_COMPARE_RESULTS
NTAPI
RTL_GENERIC_COMPARE_ROUTINE (
    _In_ struct _RTL_GENERIC_TABLE *Table,
    _In_ PVOID FirstStruct,
    _In_ PVOID SecondStruct);
typedef RTL_GENERIC_COMPARE_ROUTINE *PRTL_GENERIC_COMPARE_ROUTINE;

typedef
_IRQL_requires_same_
_Function_class_(RTL_GENERIC_ALLOCATE_ROUTINE)
__drv_allocatesMem(Mem)
PVOID
NTAPI
RTL_GENERIC_ALLOCATE_ROUTINE (
    _In_ struct _RTL_GENERIC_TABLE *Table,
    _In_ CLONG ByteSize);
typedef RTL_GENERIC_ALLOCATE_ROUTINE *PRTL_GENERIC_ALLOCATE_ROUTINE;

typedef
_IRQL_requires_same_
_Function_class_(RTL_GENERIC_FREE_ROUTINE)
VOID
NTAPI
RTL_GENERIC_FREE_ROUTINE (
    _In_ struct _RTL_GENERIC_TABLE *Table,
    _In_ __drv_freesMem(Mem) _Post_invalid_ PVOID Buffer);
typedef RTL_GENERIC_FREE_ROUTINE *PRTL_GENERIC_FREE_ROUTINE;

typedef struct _RTL_GENERIC_TABLE
{
    PRTL_SPLAY_LINKS TableRoot;
    LIST_ENTRY InsertOrderList;
    PLIST_ENTRY OrderedPointer;
    ULONG WhichOrderedElement;
    ULONG NumberGenericTableElements;
    PRTL_GENERIC_COMPARE_ROUTINE CompareRoutine;
    PRTL_GENERIC_ALLOCATE_ROUTINE AllocateRoutine;
    PRTL_GENERIC_FREE_ROUTINE FreeRoutine;
    PVOID TableContext;
} RTL_GENERIC_TABLE, *PRTL_GENERIC_TABLE;

