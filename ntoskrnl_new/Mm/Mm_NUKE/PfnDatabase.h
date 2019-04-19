

enum _PFN_STATE
{
    InvalidPfn,
    FreePfn,
    ActivePfn,
    PageTablePfn,
};

typedef union _MIPFNENTRY
{
    struct
    {
        ULONG_PTR Type : 3;
        ULONG_PTR Unused : 51;
        ULONG_PTR RefCount : 10;
    };
    struct
    {
        ULONG_PTR Type : 3;
        ULONG_PTR Dirty : 1;
        ULONG_PTR Next : 36;
        ULONG_PTR Unused : 14;
        ULONG_PTR RefCount : 10;
    } Free;
    struct
    {
        ULONG_PTR Type : 3;
        ULONG_PTR Dirty : 1;
        ULONG_PTR Owner : 1; /* 0 = system, 1 = process */
        ULONG_PTR BackingStorage : 1; // 0 = PageFile, 1 = Section
        ULONG_PTR Unused : 48;
        ULONG_PTR ShareCount : 10;
    } Active;
    struct
    {
        ULONG Type : 3;
        ULONG_PTR Unused : 41;
        ULONG_PTR ValidEntries : 10;
        ULONG_PTR UsedEntries : 10;
    } PageTable;
} MIPFNENTRY, *PMIPFNENTRY;

extern PMIPFNENTRY MmPfnDatabase;

VOID
INITAPI
MiBuildPfnDatabase(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock);

PFN_NUMBER
NTAPI
MiAllocatePage(BOOLEAN NeedZero);

ULONG
FORCEINLINE
MiIncrementUsedPteCount(
    _In_ PFN_NUMBER PageFrameNumber)
{
    return (ULONG)++MmPfnDatabase[PageFrameNumber].PageTable.UsedEntries;
}

ULONG
FORCEINLINE
MiIncrementValidPteCount(
    _In_ PFN_NUMBER PageFrameNumber)
{
    return (ULONG)++MmPfnDatabase[PageFrameNumber].PageTable.ValidEntries;
}
