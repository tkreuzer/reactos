
#define VerifyPointer(PreviousMode, Pointer, Size, Alignment) STATUS_SUCCESS

    /* Make sure the pointer is valid */
    Status = VerifyPointer(PreviousMode, OutHandle, sizeof(HANDLE), 1);
    if (!NT_SUCCESS(Status)) return Status;

#if 0
MiPageOutVirtualMemory()
{
    // PFN was on transition list, not on any list now

    // try to lock the VAD, but don't wait
    // continue somewhere else if VAD is locked

    if (pte is dirty)
    {
        PfnEntry->Dirty = 1;
        PageFileIndex = WriteDirtyPfnToDisk(Pfn)
        if (PageFileIndex <= PfnEntry->PreviousPageFileIndex)
        {
            PfnEntry->Sequence++;
        }

        SoftPte = MxCreatePageFilePte(PageFileIndex, PfnEntry->Sequence);

    }
    else
    {
        PfnEntry->Dirty = 0;
        SoftPte = MxCreateDemandPte(1);
    }

    InterlockedExchangePte(PtePointer, SoftPte, TransPte);
    if (success)
    {
        MiDereferencePfn(PfnEntry)
    }
}
#endif

MXPTE
FORCEINLINE
MxMakeValidPte(
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ ULONG Protection,
    ...)
{
    ULONG64
    PteValue.Long = MxProtectToPteLong[Protection];
    PteValue.Active.Sequence = MmPfnDatabase[PageFrameNumber].Sequence
}



MxWriteValidPte(
{
    MmPfnDatabase[PageFrameNumber].Sequence
}

MXPTE
FORCEINLINE
MxCreateDemandPte(
    _In_ UCHAR Type,
    _In_ ULONG Protection,
    _In_ BOOLEAN Owner)
{
    MXPTE DemandPte;
    ASSERT((Type == PteDemandAny) || (Type == PteDemandZero));
    DemandPte.Long = MxProtectToPteLong[Protection];
    DemandPte.Demand.Type = Type;
    DemandPte.Demand.Global = !Owner;
    DemandPte.Demand.Owner = Owner;
    return DemandPte;
}

MXPTE
FORCEINLINE
MxCreateValidPte(ULONG Protection, BOOLEAN x)
{
    MXPTE PteValue = {0};
    return PteValue;
}

// This needs optimization regarding field sizes and layout
typedef union _MIVPNENTRY
{
    ULONG_PTR Long;
    ULONG_PTR State : 2; // possibly move to the end
    struct
    {
        ULONG_PTR ValidState : 2;
        ULONG_PTR Protection : 5;
        ULONG_PTR LargePage : 1;
        ULONG_PTR WriteWatch : 1;
        ULONG_PTR SecureCount : 5; // check if that is enough
        ULONG_PTR Locked : 1; // cannot be paged out
        ULONG_PTR unused : 13;
        ULONG_PTR NextVpn : 36;
    } Valid;

    struct
    {
        ULONG_PTR ValidState : 2;
        ULONG_PTR Global : 1;
        ULONG_PTR UsedTableEntries : 10;
        ULONG_PTR ValidTableEntries : 10;
        ULONG_PTR unused : 5;
        ULONG_PTR NextVpn : 36;
    } PageTable;

    struct
    {
        ULONG_PTR InvalidState : 2;
        ULONG_PTR aligneunused: 2;
        ULONG_PTR VadIndex : 27;
    } Invalid;

} MIVPNENTRY, *MIVPNENTRY;

typedef
NTSTATUS
(NTAPI *PMM_FAULT_CALLBACK)(
    PMXPTE NewPteValue,
    MXPTE PteValue);

NTSTATUS
NTAPI
MiResolveFaultDummy(
    PMXPTE NewPteValue,
    MXPTE PteValue)
{
    __debugbreak();
    KeBugCheck(0); // FIXME
    return STATUS_ACCESS_VIOLATION;
}

NTSTATUS
NTAPI
MiResolveDemandFault(
    _Out_ PMXPTE NewPte,
    _In_ MXPTE PteValue)
{
    MXPTE NewPteValue;
    ASSERT(PteValue.Hard.Valid == 0);
    ASSERT(PteValue.Soft.VadBased == 0);

    /* Allocate a page (zero or any) */
    PageFrameNumber = MiAllocatePage(!PteValue.Vad.Dirty, TRUE);
    ASSERT(PageFrameNumber);

    *NewPte = MxDemandPteToValidPte(PteValue, PageFrameNumber);

    return STATUS_PAGE_FAULT_DEMAND_ZERO;
}

NTSTATUS
NTAPI
MiResolvePrototypeFault(
    PMXPTE NewPteValue,
    MXPTE PteValue)
{
    return STATUS_ACCESS_VIOLATION;
}

PMM_FAULT_CALLBACK
MmFaultCallback[] =
{
    MiResolveFaultDummy,        /* PteInvalid */
    MiResolveDemandFault,       /* PteDemandAny */
    MiResolveDemandFault,       /* PteDemandZero */
    MiResolvePrototypeFault,    /* PtePrototype */
    MiResolveFaultDummy,        /* PtePageFile */
    MiResolveFaultDummy,        /* PteSection */
};
