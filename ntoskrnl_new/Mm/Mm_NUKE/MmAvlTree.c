/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         BSD - See COPYING.ARM in the top level directory
 * FILE:            ntoskrnl/mm/MmAvlTree.c
 * PURPOSE:         ARM Memory Manager VAD Node Algorithms
 * PROGRAMMERS:     ReactOS Portable Systems Group
 */

/* INCLUDES ******************************************************************/

/*
 * This is the glue code for the Memory Manager version of AVL Trees that is used
 * to store the MM_AVL_TABLE for Virtual Address Descriptors (VAD) in the VadRoot
 * field in EPROCESS.
 *
 * In this version of the package, the balance and parent pointers are stored in
 * the same field as a union (since we know the parent will be at least 8-byte
 * aligned), saving some space, but requiring special logic to handle setting and
 * querying the parent and balance.
 *
 * The other difference is that the AVL package for Rtl has custom callbacks for
 * comparison purposes (which would access some internal, opaque, user data) while
 * the Mm package stores the user-data inline as StartingVpn and EndingVpn. So
 * when a compare is being made, RtlpAvlCompareRoutine is called, which will either
 * perform the Mm work, or call the user-specified callback in the Rtl case.
 */

#include <ntoskrnl.h>
#include "MmAvlTree.h"

#define PRTL_AVL_TABLE              PMM_AVL_TABLE
#define PRTL_BALANCED_LINKS         PMM_AVL_NODE
#define MI_ASSERT(x)                ASSERT(x)

RTL_GENERIC_COMPARE_RESULTS
FORCEINLINE
RtlpAvlCompareRoutine(IN PRTL_AVL_TABLE Table,
                      IN PVOID Buffer,
                      IN PVOID UserData)
{
    PMM_ADDRES_RANGE AddressRange = (PVOID)UserData;
    ULONG_PTR StartingVpn = (ULONG_PTR)Buffer;
    if (StartingVpn < AddressRange->StartingVpn)
    {
        return GenericLessThan;
    }
    else if (StartingVpn > AddressRange->EndingVpn)
    {
        return GenericGreaterThan;
    }
    else
    {
        return GenericEqual;
    }
}

VOID
FORCEINLINE
RtlSetParent(IN PRTL_BALANCED_LINKS Node,
             IN PRTL_BALANCED_LINKS Parent)
{
    Node->u1.Parent = (PRTL_BALANCED_LINKS)((ULONG_PTR)Parent | (Node->u1.Balance & 0x3));
}

VOID
FORCEINLINE
RtlSetBalance(IN PRTL_BALANCED_LINKS Node,
              IN SCHAR Balance)
{
    Node->u1.Balance = Balance;
}

SCHAR
FORCEINLINE
RtlBalance(IN PRTL_BALANCED_LINKS Node)
{
    return (SCHAR)Node->u1.Balance;
}

PRTL_BALANCED_LINKS
FORCEINLINE
RtlParentAvl(IN PRTL_BALANCED_LINKS Node)
{
    return (PRTL_BALANCED_LINKS)((ULONG_PTR)Node->u1.Parent & ~3);
}

PRTL_BALANCED_LINKS
FORCEINLINE
RtlRightChildAvl(IN PRTL_BALANCED_LINKS Node)
{
    return Node->RightChild;
}

PRTL_BALANCED_LINKS
FORCEINLINE
RtlLeftChildAvl(IN PRTL_BALANCED_LINKS Node)
{
    return Node->LeftChild;
}

BOOLEAN
FORCEINLINE
RtlIsLeftChildAvl(IN PRTL_BALANCED_LINKS Node)
{
   return (RtlLeftChildAvl(RtlParentAvl(Node)) == Node);
}

BOOLEAN
FORCEINLINE
RtlIsRightChildAvl(IN PRTL_BALANCED_LINKS Node)
{
   return (RtlRightChildAvl(RtlParentAvl(Node)) == Node);
}

VOID
FORCEINLINE
RtlInsertAsLeftChildAvl(IN PRTL_BALANCED_LINKS Parent,
                        IN PRTL_BALANCED_LINKS Node)
{
    Parent->LeftChild = Node;
    RtlSetParent(Node, Parent);
}

VOID
FORCEINLINE
RtlInsertAsRightChildAvl(IN PRTL_BALANCED_LINKS Parent,
                         IN PRTL_BALANCED_LINKS Node)
{
    Parent->RightChild = Node;
    RtlSetParent(Node, Parent);
}

/* Now include the core code from RTL */
#include "../../lib/rtl/avlsupp.c"

TABLE_SEARCH_RESULT
NTAPI
MiAvlFindNodeOrParent(
    PMM_AVL_TABLE Table,
    ULONG_PTR StartVpn,
    PMM_AVL_NODE *NodeOrParent)
{
    return RtlpFindAvlTableNodeOrParent(Table, (PVOID)StartVpn, NodeOrParent);
}

VOID
NTAPI
MiAvlInsertNode(
    PMM_AVL_TABLE Table,
    PMM_AVL_NODE Parent,
    PMM_AVL_NODE Node,
    TABLE_SEARCH_RESULT InsertAs)
{
    RtlpInsertAvlTreeNode(Table, Node, Parent, InsertAs);
}

VOID
NTAPI
MiAvlRemoveNode(
    PMM_AVL_TABLE Table,
    PMM_AVL_NODE Node)
{
    RtlpDeleteAvlTreeNode(Table, Node);
}


/* EOF */
