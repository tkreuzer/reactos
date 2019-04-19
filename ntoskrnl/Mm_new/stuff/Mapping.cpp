


NTSTATUS
ReservePageTables (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    PFN_LIST PageList;
    ULONG_PTR EndingVpn;
    ULONG_PTR PageAllocation, PagesUsed;
    NTSTATUS Status;

    ASSERT(NumberOfPages > 0);
    EndingVpn = StartingVpn + NumberOfPages - 1;

    /* Calculate the maximum number of page table we need */
    PageAllocation = CalculateMaximumNumberOfPageTables(StartingVpn, EndingVpn);

    /* Check if we have large pages */
    if (Protect & MM_LARGEPAGE)
    {
        NT_ASSERT((NumberOfPages & (LARGE_PAGE_SIZE / PAGE_SIZE - 1)) == 0);

        __debugbreak();
    }

    /* Charge the system commit */
    Status = ChargeSystemCommit(PageAllocation);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Preallocate pages */
    Status = g_PfnDatabase.AllocateMultiplePages(&PageList, PageAllocation, TRUE);
    if (!NT_SUCCESS(Status))
    {
        UnchargeSystemCommit(PageAllocation);
        return Status;
    }

    /* Check if we have kernel mode addresses */
    if (StartingVpn >= LowestSystemVpn)
    {
        // AddressSpace = g_KernelAddressSpace;
        Protect &= ~MM_USER;
    }
    else
    {
        NT_ASSERT(EndingVpn < LowestSystemVpn);

        // AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
        Protect |= MM_USER;
    }

    /* Lock the address space */
    // AddressSpace->AcquireLock();

    /* Call the worker function */
    PagesUsed = ReservePageTablesWorker(StartingVpn,
                                        EndingVpn,
                                        Protect,
                                        &PageList);

    /* Unlock the address space */
    // AddressSpace->ReleaseLock();

    /* Return the pages, we did not consume */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);

    /* Return the system commit charge, we did not use */
    NT_ASSERT(PagesUsed <= PageAllocation);
    UnchargeSystemCommit(PageAllocation - PagesUsed);

    return STATUS_SUCCESS;
}

/// ****************************************************************************



NTSTATUS
MapVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _In_ ULONG Protect
{
    PFN_LIST PageList, LargePageList;
    NTSTATUS Status;

    if (Protect & MM_LARGEPAGE)
    {
        NT_ASSERT(Protect & MM_NONPAGED);
        StartingVpn = ALIGN_DOWN_BY(StartingVpn, LARGE_PAGE_SIZE);
        EndingVpn = ALIGN_UP_BY(EndingVpn + 1, LARGE_PAGE_SIZE) - 1;
    }

    Status = AllocatePagesForMapping(StartingVpn,
                                     EndingVpn,
                                     &PageList,
                                     &LargePageList,
                                     TRUE,
                                     Protect);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    AddressSpace->AcquireLock()

    ReserveMappingPtes()

    loop Ptes
    {
        CurrentPte->WriteValidPte()
        CurrentPte++
        PageframeNumber++
    }

    AddressSpace->ReleaseLock()

    // return commit charge for pages that were already mapped

    return STATUS_SUCCESS;
}

NTSTATUS
MapPhysicalMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _In_ ULONG Protect,
    _In_ PFN_NUMBER BasePageFrameNumber)
{

    Status = AllocatePagesForMapping(StartingVpn,
                                     EndingVpn,
                                     &PageList,
                                     NULL,
                                     FALSE,
                                     Protect,
                                     &PagesCharged);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    AddressSpace->AcquireLock()

    PagesUsed = ReserveMappingPtes(StartingVpn, EndingVpn, &PageList, Protect);

    /* Loop all reserved PTEs */
    do
    {
        /* Make sure the PTE is empty */
        NT_ASSERT(CurrentPte->IsEmpty());
        TemplatePte.SetPageFrameNumber(PageFrameNumber);
        CurrentPte->WriteValidPte(TemplatePte);
        NumberOfNewPtes++;

        CurrentPte++;
        PageFrameNumber++;
        NumberOfPages--;

        /* Update the PFN of the PT, if we reached the next PT or the end */
        if ((CurrentPte->IsPdeBoundary()) || (NumberOfPages == 0))
        {
            PfnOfPt = PteToPde(CurrentPte - 1)->GetPageFrameNumber();
            g_PfnDatabase.IncrementEntryCount(PfnOfPt, NumberOfNewPtes);
            NumberOfNewPtes = 0;
        }
    }
    while (NumberOfPages);

    AddressSpace->ReleaseLock()

    /* Return the system commit charge, we did not use */
    NT_ASSERT(PagesUsed <= PagesCharged);
    UnchargeSystemCommit(PagesCharged - PagesUsed);


    return STATUS_SUCCESS;
}

NTSTATUS
ReservePageTables_ (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    return CreateMapping(StartingVpn,
                         NumberOfPages,
                         MM_NOACCESS | MM_GLOBAL,
                         NULL,
                         NULL);
}

VOID
MapPrototypePtes_ (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ PPTE Ptototypes,
    _In_ ULONG Protect)
{
    PFN_NUMBER PfnOfPt;
    PPTE CurrentPte;
    ULONG NumberOfNewPtes;

    /* Get the PFN of the page table */
    PfnOfPt = VpnToPde(StartingVpn)->GetPageFrameNumber();

    /* Get the starting PTE */
    CurrentPte = VpnToPte(StartingVpn);

    NumberOfNewPtes = 0;

    /* Lock the address space */
    // AddressSpace->AcquireLock();

    /* Now loop all reserved PTEs */
    do
    {
        /* Make sure the PTE is a no-access PTE and make it a prototype PTE */
        NT_ASSERT(CurrentPte->IsNoAccess());
        CurrentPte->MakePrototypePte(Ptototypes, 0);
        NumberOfNewPtes++;

        CurrentPte++;
        Ptototypes++;
        NumberOfPages--;
#if 0 // This only makes sense, when we move page table referencing completely out
// of the reserving function, but then we need to lock outside of both functions
        /* Update the PFN of the PT, if we reached the next PT or the end */
        if ((CurrentPte->IsPdeBoundary()) || (NumberOfPages == 0))
        {
            PfnOfPt = PdeToPte(CurrentPte)->GetPageFrameNumber();
            NumberOfNewPtes = 0;
        }
#endif
    }
    while (NumberOfPages);

    /* Unlock the address space */
    // AddressSpace->ReleaseLock();
}

