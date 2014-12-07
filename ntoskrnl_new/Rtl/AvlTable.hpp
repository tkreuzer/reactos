
#pragma once

#include "GenericTable.hpp" // for RTL_GENERIC_COMPARE_RESULTS

struct _RTL_AVL_TABLE;

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_COMPARE_ROUTINE)
RTL_GENERIC_COMPARE_RESULTS
NTAPI
RTL_AVL_COMPARE_ROUTINE (
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ PVOID FirstStruct,
    _In_ PVOID SecondStruct);
typedef RTL_AVL_COMPARE_ROUTINE *PRTL_AVL_COMPARE_ROUTINE;

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_ALLOCATE_ROUTINE)
__drv_allocatesMem(Mem)
PVOID
NTAPI
RTL_AVL_ALLOCATE_ROUTINE (
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ CLONG ByteSize);
typedef RTL_AVL_ALLOCATE_ROUTINE *PRTL_AVL_ALLOCATE_ROUTINE;

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_FREE_ROUTINE)
VOID
NTAPI
RTL_AVL_FREE_ROUTINE (
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ __drv_freesMem(Mem) _Post_invalid_ PVOID Buffer);
typedef RTL_AVL_FREE_ROUTINE *PRTL_AVL_FREE_ROUTINE;

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_MATCH_FUNCTION)
NTSTATUS
NTAPI
RTL_AVL_MATCH_FUNCTION (
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ PVOID UserData,
    _In_ PVOID MatchData);
typedef RTL_AVL_MATCH_FUNCTION *PRTL_AVL_MATCH_FUNCTION;

typedef struct _RTL_BALANCED_LINKS
{
    struct _RTL_BALANCED_LINKS *Parent;
    struct _RTL_BALANCED_LINKS *LeftChild;
    struct _RTL_BALANCED_LINKS *RightChild;
    CHAR Balance;
    UCHAR Reserved[3];
} RTL_BALANCED_LINKS, *PRTL_BALANCED_LINKS;

typedef struct _RTL_AVL_TABLE
{
    RTL_BALANCED_LINKS BalancedRoot;
    PVOID OrderedPointer;
    ULONG WhichOrderedElement;
    ULONG NumberGenericTableElements;
    ULONG DepthOfTree;
    PRTL_BALANCED_LINKS RestartKey;
    ULONG DeleteCount;
    PRTL_AVL_COMPARE_ROUTINE CompareRoutine;
    PRTL_AVL_ALLOCATE_ROUTINE AllocateRoutine;
    PRTL_AVL_FREE_ROUTINE FreeRoutine;
    PVOID TableContext;
} RTL_AVL_TABLE, *PRTL_AVL_TABLE;
