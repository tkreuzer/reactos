inline
ULONG_PTR
MapLargePagePdes (
    _In_ PPDE CurrentPde,
    _In_ PPDE MarginPde,
    _In_ ULONG Protect,
    _In_ PFN_NUMBER PfnOfPd,
    _Inout_ PFN_LIST* LargePageList)
{
    PFN_NUMBER PageFrameNumber;
    ULONG NumberOfNewPdes = 0;

    do
    {
        /* Check if the PDE is empty */
        if (CurrentPde->IsEmpty())
        {
            /* Map the large page */
            PageFrameNumber = LargePageList->RemovePage();
            g_PfnDatabase.MakeLargePagePfn(PageFrameNumber, CurrentPde, Protect);
            CurrentPde->MakeValidLargePagePde(PageFrameNumber, Protect);
            NumberOfNewPdes++;
        }
        else
        {
            NT_ASSERT(CurrentPde->IsLargePage());
        }

        /* Go to the next PDE */
        CurrentPde++;
    } while (CurrentPde < MarginPde);

    /* Increment entry count in the parent page table */
    g_PfnDatabase.IncrementEntryCount(PfnOfPd, NumberOfNewPdes);

    /* Return the number of pages we removed from the page list */
    return NumberOfNewPdes * (LARGE_PAGE_SIZE / PAGE_SIZE);
}

inline
ULONG_PTR
MapPdesAndPtes (
    _In_ PPDE CurrentPde,
    _In_ PPDE MarginPde,
    _In_ PPTE CurrentPte,
    _In_ PPTE EndPte,
    _In_ ULONG Protect,
    _In_ PFN_NUMBER PfnOfPd,
    _Inout_ PFN_LIST* PageList,
    _Inout_ PPFN_NUMBER* PfnArrayPointer,
    _Inout_ PPTE* PrototypePtePointer)
{
    PFN_NUMBER PfnOfPt;
    ULONG_PTR NumberOfPages = 0;
    ULONG NumberOfNewPdes = 0, NumberOfNewPtes;
    PPTE MarginPte;
    PTE TemplatePte;

    do
    {
        /* Check if the PDE is empty */
        if (CurrentPde->IsEmpty())
        {
            /* Map the PT */
            PfnOfPt = PageList->RemovePage();
            g_PfnDatabase.MakePageTablePfn(PfnOfPt, CurrentPde, Protect);
            CurrentPde->MakeValidPde(PfnOfPt, Protect);
            NumberOfNewPdes++;
        }
        else
        {
            /* Get the page frame number of the PT */
            PfnOfPt = CurrentPde->GetPageFrameNumber();
        }

        /* Calculate the margin for PTEs in this PT */
        MarginPte = MinPtr(PdeToPte(CurrentPde + 1), EndPte);

        /* Start counting new PTEs */
        NumberOfNewPtes = 0;

        /* Check if we have a PFN array */
        if (*PfnArrayPointer != NULL)
        {
            TemplatePte.MakeValidPte(0, Protect);
            do
            {
                NT_ASSERT(CurrentPte->IsEmpty());
                TemplatePte.SetPageFrameNumber(*(*PfnArrayPointer));
                CurrentPte->WriteValidPte(TemplatePte);
                NumberOfNewPtes++;
                CurrentPte++;
                (*PfnArrayPointer)++;
            }
            while (CurrentPte < MarginPte);
        }
        /* Check if we have a prototype PTE array */
        else if (*PrototypePtePointer != NULL)
        {
            do
            {
                if (CurrentPte->IsEmpty())
                {
                    CurrentPte->MakePrototypePte(*PrototypePtePointer, Protect);
                    NumberOfNewPtes++;
                }
                else
                {
                    /* Just update the protection */
                    CurrentPte->UpdateProtection(Protect);
                    NT_ASSERT(FALSE);
                    /// \todo we need to invalidate TLB entries when the page was valid!
                }
                CurrentPte++;
                (*PrototypePtePointer)++;
            }
            while (CurrentPte < MarginPte);
        }
        /* Check if the pages should be mapped */
        else if (Protect & MM_MAPPED)
        {
            TemplatePte.MakeValidPte(0, Protect);

            do
            {
                if (CurrentPte->IsEmpty())
                {
                    PFN_NUMBER PageFrameNumber = PageList->RemovePage();
                    NT_ASSERT(PageFrameNumber != 0);
                    TemplatePte.SetPageFrameNumber(PageFrameNumber);
                    CurrentPte->WriteValidPte(TemplatePte);
                    NumberOfNewPtes++;
                }
                else
                {
                    /* For now unsupported! */
                    NT_ASSERT(FALSE);
                }
                CurrentPte++;
            }
            while (CurrentPte < MarginPte);

            /* The new pages count for the commit charge */
            NumberOfPages += NumberOfNewPtes;
        }
        else
        {
            TemplatePte.MakeDemandZeroPte(Protect);

            do
            {
                /* Check if this PTE is empty */
                if (CurrentPte->IsEmpty())
                {
                    /* Write a new demand zero PTE */
                    CurrentPte->WriteSoftwarePte(TemplatePte);
                    NumberOfNewPtes++;
                }
                else
                {
                    /* Only update the protection */
                    CurrentPte->UpdateProtection(Protect);
                    NT_ASSERT(FALSE);
                    /// \todo we need to invalidate TLB entries when the page was valid!
                }
                CurrentPte++;
            }
            while (CurrentPte < MarginPte);

            /* The new pages count for the commit charge */
            NumberOfPages += NumberOfNewPtes;
        }

        /* Increment entry count in the parent page table */
        g_PfnDatabase.IncrementEntryCount(PfnOfPt, NumberOfNewPtes);

        /* Go to the next PDE */
        CurrentPde++;
    } while (CurrentPde < MarginPde);

    /* Increment entry count in the parent page table */
    g_PfnDatabase.IncrementEntryCount(PfnOfPd, NumberOfNewPdes);

    /* Return the number of pages we removed from the page list */
    return NumberOfNewPdes + NumberOfPages;
}

inline
ULONG_PTR
PageMappingWorker (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _In_ ULONG Protect,
    _In_opt_ PPFN_NUMBER PfnArray,
    _In_opt_ PPTE Prototypes,
    _In_ PFN_LIST* PageList,
    _In_ PFN_LIST* LargePageList)
{
    ULONG_PTR ActualCharge;
#if (MI_PAGING_LEVELS >= 4)
    PFN_NUMBER PfnOfPml4;
    PPXE CurrentPxe = VpnToPxe(StartingVpn);
    PPXE EndPxe = VpnToPxe(EndingVpn) + 1;
#endif /* MI_PAGING_LEVELS >= 4 */
#if (MI_PAGING_LEVELS >= 3)
    PFN_NUMBER PfnOfPdpt;
    PPPE CurrentPpe = VpnToPpe(StartingVpn);
    PPPE EndPpe = VpnToPpe(EndingVpn) + 1;
    PPPE MarginPpe;
#endif /* MI_PAGING_LEVELS >= 3 */
    PFN_NUMBER PfnOfPd;
    PPDE CurrentPde = VpnToPde(StartingVpn);
    PPDE EndPde = VpnToPde(EndingVpn) + 1;
    PPDE MarginPde;
    PPTE CurrentPte = VpnToPte(StartingVpn);
    PPTE EndPte = VpnToPte(EndingVpn) + 1;

#if (MI_PAGING_LEVELS == 4)
    PfnOfPml4 = AddressToPte((PVOID)PXE_BASE)->GetPageFrameNumber();
#elif (MI_PAGING_LEVELS == 3)
    PfnOfPdpt = AddressToPte((PVOID)PPE_BASE)->GetPageFrameNumber();
    MarginPpe = EndPpe;
#else
    PfnOfPd = AddressToPte((PVOID)PDE_BASE)->GetPageFrameNumber();
    MarginPde = EndPde;
#endif

    /* Start counting the pages we use */
    ActualCharge = 0;

#if (MI_PAGING_LEVELS >= 4)
    ULONG NumberOfNewPxes = 0;
    do
    {
        /* Check if the PXE is empty */
        if (CurrentPxe->IsEmpty())
        {
            /* Map the PDPT */
            PfnOfPdpt = PageList->RemovePage();
            g_PfnDatabase.MakePageTablePfn(PfnOfPdpt, CurrentPxe, Protect);
            CurrentPxe->MakeValidPxe(PfnOfPdpt, Protect);
            ActualCharge++;
            NumberOfNewPxes++;
        }
        else
        {
            /* Get the page frame number of the PDPT */
            PfnOfPdpt = CurrentPxe->GetPageFrameNumber();
        }

        /* Calculate the margin for PPEs in this PDPT */
        MarginPpe = MinPtr(PxeToPpe(CurrentPxe + 1), EndPpe);
#endif /* MI_PAGING_LEVELS >= 4 */

#if (MI_PAGING_LEVELS >= 3)
        ULONG NumberOfNewPpes = 0;
        do
        {
            /* Check if the PPE is empty */
            if (CurrentPpe->IsEmpty())
            {
                /* Map the PD */
                PfnOfPd = PageList->RemovePage();
                g_PfnDatabase.MakePageTablePfn(PfnOfPd, CurrentPpe, Protect);
                CurrentPpe->MakeValidPpe(PfnOfPd, Protect);
                ActualCharge++;
                NumberOfNewPpes++;
            }
            else
            {
                /* Get the page frame number of the PD */
                PfnOfPd = CurrentPpe->GetPageFrameNumber();
            }

            /* Calculate the margin for PDEs in this PD */
            MarginPde = MinPtr(PpeToPde(CurrentPpe + 1), EndPde);
#endif /* MI_PAGING_LEVELS >= 3 */

            /* Check if large pages are requested */
            if (Protect & MM_LARGEPAGE)
            {
                /* Map the large pages in this PD */
                ActualCharge += MapLargePagePdes(CurrentPde,
                                                 MarginPde,
                                                 Protect,
                                                 PfnOfPd,
                                                 LargePageList);
            }
            else
            {
                /* Map the PTs and the PTEs in this PD */
                ActualCharge += MapPdesAndPtes(CurrentPde,
                                               MarginPde,
                                               CurrentPte,
                                               EndPte,
                                               Protect,
                                               PfnOfPd,
                                               PageList,
                                               &PfnArray,
                                               &Prototypes);
            }

            /* Continue with PDE at the next PPE boundary */
            CurrentPde = MarginPde;
            CurrentPte = PdeToPte(CurrentPde);

#if (MI_PAGING_LEVELS >= 3)
            /* Go to the next PPE */
            CurrentPpe++;
        } while (CurrentPpe < MarginPpe);

        /* Increment entry count in the parent page table */
        g_PfnDatabase.IncrementEntryCount(PfnOfPdpt, NumberOfNewPpes);
#endif /* MI_PAGING_LEVELS >= 3 */

#if (MI_PAGING_LEVELS >= 4)
        /* Go to the next PXE */
        CurrentPxe++;
    } while (CurrentPxe < EndPxe);

    /* Increment entry count in the parent page table */
    g_PfnDatabase.IncrementEntryCount(PfnOfPdpt, NumberOfNewPxes);
#endif /* MI_PAGING_LEVELS >= 4 */

    return ActualCharge;
}


NTSTATUS
CreateMapping (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_opt_ PPFN_NUMBER PfnArray,
    _In_opt_ PPTE Prototypes)
{
    PFN_LIST PageList, LargePageList;
    ULONG_PTR EndingVpn;
    ULONG_PTR PageAllocation, MaximumCharge, ActualCharge;
    NTSTATUS Status;

    ASSERT(NumberOfPages > 0);
    EndingVpn = StartingVpn + NumberOfPages - 1;

    /* Calculate the maximum number of page table we need */
    PageAllocation = CalculateMaximumNumberOfPageTables(StartingVpn, EndingVpn);
    MaximumCharge = PageAllocation + NumberOfPages;
    /// FIXME: we don't need to charge for NOACCESS and PFN array/proto PTEs

    /* Check if we have large pages */
    if (Protect & MM_LARGEPAGE)
    {
        NT_ASSERT((NumberOfPages & (LARGE_PAGE_SIZE / PAGE_SIZE - 1)) == 0);


    }

    /* Otherwise check if we need to allocate the actual pages */
    else if ((Protect & MM_MAPPED) && (PfnArray == NULL) && (Prototypes == NULL))
    {
        /* Add the number of pages as well */
        PageAllocation += NumberOfPages;
    }

    /* Charge the system commit */
    Status = ChargeSystemCommit(MaximumCharge);
    if (!NT_SUCCESS(Status))
    {
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

    /* Preallocate pages */
    Status = g_PfnDatabase.AllocateMultiplePages(&PageList, PageAllocation, TRUE);
    if (!NT_SUCCESS(Status))
    {
        UnchargeSystemCommit(MaximumCharge);
        return Status;
    }

    /* Check if we have large pages */
    if (Protect & MM_LARGEPAGE)
    {
        /* Initialize the large page list and allocate large pages */
        LargePageList.Initialize();
        Status = g_PfnDatabase.AllocateLargePages(&LargePageList,
                                                  NumberOfPages /
                                                    (LARGE_PAGE_SIZE / PAGE_SIZE),
                                                  FALSE);
        if (!NT_SUCCESS(Status))
        {
            UnchargeSystemCommit(MaximumCharge);
            return Status;
        }
    }

    /* Lock the address space */
    // AddressSpace->AcquireLock();

    /* Call the worker function */
    ActualCharge = PageMappingWorker(StartingVpn,
                                     EndingVpn,
                                     Protect,
                                     PfnArray,
                                     Prototypes,
                                     &PageList,
                                     &LargePageList);

    /* Unlock the address space */
    // AddressSpace->ReleaseLock();

    /* Return the pages, we did not consume */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);

    /* Return the system commit charge, we did not use */
    NT_ASSERT(ActualCharge <= MaximumCharge);
    UnchargeSystemCommit(MaximumCharge - ActualCharge);

    return STATUS_SUCCESS;
}

NTSTATUS
ReservePageTables (
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
MapPrototypePtes (
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



