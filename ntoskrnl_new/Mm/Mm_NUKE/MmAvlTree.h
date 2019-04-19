
typedef struct _MM_AVL_NODE
{
    union
    {
        LONG_PTR Balance : 2;
        struct _MM_AVL_NODE* Parent;
    } u1;
    struct _MM_AVL_NODE* LeftChild;
    struct _MM_AVL_NODE* RightChild;
} MM_AVL_NODE, *PMM_AVL_NODE;

typedef struct _MM_AVL_TABLE
{
    MM_AVL_NODE BalancedRoot;
    struct
    {
        ULONG_PTR DepthOfTree : 5;
        ULONG_PTR Unused : 3;
        ULONG_PTR NumberGenericTableElements : 56;
    };
    PVOID NodeHint;
    PVOID NodeFreeHint;
} MM_AVL_TABLE, *PMM_AVL_TABLE;

typedef struct _MM_ADDRES_RANGE
{
    ULONG_PTR StartingVpn;
    ULONG_PTR EndingVpn;
} MM_ADDRES_RANGE, *PMM_ADDRES_RANGE;

TABLE_SEARCH_RESULT
NTAPI
MiAvlFindNodeOrParent(
    PMM_AVL_TABLE Table,
    ULONG_PTR StartVpn,
    PMM_AVL_NODE *NodeOrParent);

VOID
NTAPI
MiAvlInsertNode(
    PMM_AVL_TABLE Table,
    PMM_AVL_NODE Parent,
    PMM_AVL_NODE Node,
    TABLE_SEARCH_RESULT InsertAs);

VOID
NTAPI
MiAvlRemoveNode(
    PMM_AVL_TABLE Table,
    PMM_AVL_NODE Node);

