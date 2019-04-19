

typedef struct _MM_AVL_NODE
{
    union
    {
        INT64 Balance : 2;
        PMM_AVL_NODE Parent;
    } u1;
    PMM_AVL_NODE LeftChild;
    PMM_AVL_NODE RightChild;
} MM_AVL_NODE, *PMM_AVL_NODE;

typedef struct _MM_AVL_TABLE
{
    MM_AVL_NODE BalancedRoot;
    struct
    {
        ULONG64 DepthOfTree : 5;
        ULONG64 TableType : 3;
        ULONG64 NumberGenericTableElements : 56;
    };
    PVOID NodeHint;
    PVOID NodeFreeHint;
} MM_AVL_TABLE, *PMM_AVL_TABLE;

typedef struct _MI_VAD_SEQUENTIAL_INFO // 2 elements, 0x8 bytes (sizeof)
{
    UINT64       Length : 12;          // 0 BitPosition
    UINT64       Vpn : 52;             // 12 BitPosition
} MI_VAD_SEQUENTIAL_INFO, *PMI_VAD_SEQUENTIAL_INFO;

typedef struct _MI_VAD_EVENT_BLOCK
{
    struct _MI_VAD_EVENT_BLOCK* Next;
    ULONG WaitReason;
    union
    {
        KGATE Gate;
        MMADDRESS_LIST SecureInfo;
        RTL_BITMAP_EX BitMap;
        PMMINPAGE_SUPPORT InPageSupport;
        MI_PHYSMEM_BLOCK PhysicalMemory;
        PMI_LARGEPAGE_MEMORY_INFO LargePage;
    };
} MI_VAD_EVENT_BLOCK, *PMI_VAD_EVENT_BLOCK;

typedef struct _MMVAD_FLAGS            // 8 elements, 0x4 bytes (sizeof)
{
    ULONG VadType : 3;          // 0 BitPosition
    ULONG Protection : 5;       // 3 BitPosition
    ULONG PreferredNode : 6;    // 8 BitPosition
    ULONG NoChange : 1;         // 14 BitPosition
    ULONG PrivateMemory : 1;    // 15 BitPosition
    ULONG Teb : 1;              // 16 BitPosition
    ULONG Spare : 14;           // 17 BitPosition
    ULONG DeleteInProgress : 1; // 31 BitPosition
} MMVAD_FLAGS, *PMMVAD_FLAGS;

typedef struct _MMVAD_FLAGS1        // 2 elements, 0x4 bytes (sizeof)
{
    ULONG32      CommitCharge : 31; // 0 BitPosition
    ULONG32      MemCommit : 1;     // 31 BitPosition
} MMVAD_FLAGS1, *PMMVAD_FLAGS1;

typedef struct _MMVAD_FLAGS2      // 6 elements, 0x4 bytes (sizeof)
{
    ULONG FileOffset : 24; // 0 BitPosition
    ULONG Large : 1;       // 24 BitPosition
    ULONG TrimBehind : 1;  // 25 BitPosition
    ULONG Inherit : 1;     // 26 BitPosition
    ULONG CopyOnWrite : 1; // 27 BitPosition
    ULONG Spare : 4;       // 28 BitPosition
} MMVAD_FLAGS2, *PMMVAD_FLAGS2;

typedef struct _MMVAD_SHORT                // 8 elements, 0x40 bytes (sizeof)
{
    MM_AVL_NODE VadNode;           // 3 elements, 0x18 bytes (sizeof)
    ULONG StartingVpn;
    ULONG EndingVpn;
    EX_PUSH_LOCK PushLock;         // 7 elements, 0x8 bytes (sizeof)
    union                                  // 2 elements, 0x4 bytes (sizeof)
    {
        ULONG LongFlags;
        MMVAD_FLAGS VadFlags;      // 8 elements, 0x4 bytes (sizeof)
    } u;
    union                                  // 2 elements, 0x4 bytes (sizeof)
    {
        ULONG LongFlags1;
        MMVAD_FLAGS1 VadFlags1;    // 2 elements, 0x4 bytes (sizeof)
    } u1;
    struct _MI_VAD_EVENT_BLOCK* EventList;
    LONG ReferenceCount;
} MMVAD_SHORT, *PMMVAD_SHORT;

typedef struct _MMVAD                                // 9 elements, 0x80 bytes (sizeof)
{
    MMVAD_SHORT Core;                        // 8 elements, 0x40 bytes (sizeof)
    union                                            // 2 elements, 0x4 bytes (sizeof)
    {
        ULONG LongFlags2;
        MMVAD_FLAGS2 VadFlags2;              // 6 elements, 0x4 bytes (sizeof)
    } u2;
    union                                            // 2 elements, 0x8 bytes (sizeof)
    {
        struct _SUBSECTION* Subsection;
        struct _MSUBSECTION* MappedSubsection;
    };
    struct _MMPTE* FirstPrototypePte;
    struct _MMPTE* LastContiguousPte;
    struct _LIST_ENTRY ViewLinks;                    // 2 elements, 0x10 bytes (sizeof)
    struct _EPROCESS* VadsProcess;
    union                                            // 2 elements, 0x8 bytes (sizeof)
    {
        struct _MI_VAD_SEQUENTIAL_INFO SequentialVa; // 2 elements, 0x8 bytes (sizeof)
        struct _MMEXTEND_INFO* ExtendedInfo;
    } u4;
} MMVAD, *PMMVAD;
