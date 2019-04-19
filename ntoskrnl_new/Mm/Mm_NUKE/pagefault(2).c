


typedef struct _MI_X86_FAULT_REASON
{
    ULONG PageNotPresent : 1;
    ULONG WriteAccess : 1;
    ULONG PreviousMode : 1;
    ULONG InvalidPte : 1;
    ULONG InstructionFetch : 1;
} MI_X86_FAULT_REASON;

VOID
NTAPI
MiPageFaultHandler(
    PKTRAP_FRAME TrapFrame)
{
    MI_FAULT_REASON Reason;

    /* Get the reason for this fault */
    Reason = MxGetPageFaultReason(TrapFrame);

#if (_MI_PAGING_LEVELS == 2)
    /* Check for an invalid system PDE */
    if (!PointerPde->u.Hard.Valid && (Address > MmSystemRangeStart))
    {
        /* Check for an unsychronized system space PDE */
        MiSynchronizeSystemPdes();
    }
#endif

    /* Check (again) for an invalid PDE */
    if (!PointerPde->u.Hard.Valid)
    {
        /* This can be only a paged out page table */
        Status = MiResolvePageFileFault(PointerPte);

        /* Bail out if that failed */
        if (!NT_SUCCESS(Status)) return Status;
    }

    /* Check if the PTE is invalid */
    if (!PointerPte->u.Hard.Valid)
    {

    }



}

