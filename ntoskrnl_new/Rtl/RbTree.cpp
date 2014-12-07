
#include "Rtl.hpp"

extern "C" {

typedef struct _RTL_BALANCED_LINKS
{
    struct _RTL_BALANCED_LINKS *Parent;
    struct _RTL_BALANCED_LINKS *LeftChild;
    struct _RTL_BALANCED_LINKS *RightChild;
    CHAR Balance;
    UCHAR Reserved[3];
} RTL_BALANCED_LINKS, *PRTL_BALANCED_LINKS;

typedef struct _RTL_RB_TREE
{
    struct _RTL_BALANCED_NODE* Root;
    struct _RTL_BALANCED_NODE* Min;
} RTL_RB_TREE, *PRTL_RB_TREE;

// http://filelog.net/func/RtlRbInsertNodeEx
VOID
NTAPI
RtlRbInsertNodeEx (
    PRTL_RB_TREE Tree,
    PRTL_BALANCED_NODE Parent,
    BOOLEAN Right,
    PRTL_BALANCED_NODE Node)
{
    __debugbreak();
}

// http://filelog.net/func/RtlRbRemoveNode
VOID
NTAPI
RtlRbRemoveNode (
    PRTL_RB_TREE Tree,
    PRTL_BALANCED_NODE Node)
{
    __debugbreak();
}

} // extern "C"
