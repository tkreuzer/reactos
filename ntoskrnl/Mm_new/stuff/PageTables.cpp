

VOID
ScanPageTables (
    _In_ PFN_NUMBER PageFrameNumber)
{
    ULONG i,j,k,l;
    PPXE Pxe;
    PPPE Ppe;
    PPDE Pde;
    PPTE Pte;

    for (Pxe = AddressToPxe(0), i = 0; i < PXE_PER_PAGE; i++, Pxe++)
    {
        if (!Pxe->IsValid()) continue;

        if (Pxe->GetPageFrameNumber() == PageFrameNumber) __debugbreak();

        for (Ppe = PxeToPpe(Pxe), j = 0; j < PPE_PER_PAGE; j++, Ppe++)
        {
            if (!Ppe->IsValid()) continue;

            if (Ppe->GetPageFrameNumber() == PageFrameNumber) __debugbreak();

            for (Pde = PpeToPde(Ppe), k = 0; k < PDE_PER_PAGE; k++, Pde++)
            {
                if (!Pde->IsValid()) continue;

                if (Pde->IsLargePage())
                {
                    for (ULONG m = 0; m < 512; m++)
                    {
                        if ((Pde->GetPageFrameNumber() <= PageFrameNumber) &&
                            ((Pde->GetPageFrameNumber() + 512) > PageFrameNumber)) __debugbreak();
                    }
                }
                else
                {
                    if (Pde->GetPageFrameNumber() == PageFrameNumber) __debugbreak();

                    for (Pte = PdeToPte(Pde), l = 0; l < PTE_PER_PAGE; l++, Pte++)
                    {
                        if (!Pte->IsValid()) continue;

                        if (Pte->GetPageFrameNumber() == PageFrameNumber) __debugbreak();
                    }
                }
            }
        }
    }
}


NTSTATUS
ReservePtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR PageCount,
    _In_ ULONG Protect,
    _Out_ PULONG_PTR OutUsedPages)
{
    PFN_LIST PageList;
    ULONG_PTR EndingVpn;
    ULONG_PTR NumberOfPages, MaximumPageTables;
    NTSTATUS Status;

    ASSERT(PageCount > 0);
    EndingVpn = StartingVpn + PageCount - 1;

    /* Calculate the maximum number of page table we need */
    MaximumPageTables = CalculateMaximumNumberOfPageTables(StartingVpn, EndingVpn);

    /* Preallocate pages for the new page tables */
    Status = g_PfnDatabase.AllocateMultiplePages(&PageList, MaximumPageTables);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Start counting the pages we use */
    NumberOfPages = 0;

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
    PFN_NUMBER PfnOfPd, PfnOfPt;
    PPDE CurrentPde = VpnToPde(StartingVpn);
    PPDE EndPde = VpnToPde(EndingVpn) + 1;
    PPDE MarginPde;

#if (MI_PAGING_LEVELS == 4)
    PfnOfPml4 = AddressToPte((PVOID)PXE_BASE)->GetPageFrameNumber();
#elif (MI_PAGING_LEVELS == 3)
    PfnOfPdpt = AddressToPte((PVOID)PPE_BASE)->GetPageFrameNumber();
    MarginPpe = EndPpe;
#else
    PfnOfPd = AddressToPte((PVOID)PDE_BASE)->GetPageFrameNumber();
    MarginPde = EndPde;
#endif

#if (MI_PAGING_LEVELS >= 4)
    ULONG NumberOfNewPxes = 0;
    do
    {
        /* Check if the PXE is empty */
        if (CurrentPxe->IsEmpty())
        {
            /* Map the PDPT */
            PfnOfPdpt = PageList.RemovePage();
            g_PfnDatabase.MakePageTablePfn(PfnOfPdpt, CurrentPxe, Protect);
            CurrentPxe->MakeValidPxe(PfnOfPdpt, Protect);
            NumberOfPages++;
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
                PfnOfPd = PageList.RemovePage();
                g_PfnDatabase.MakePageTablePfn(PfnOfPd, CurrentPpe, Protect);
                CurrentPpe->MakeValidPpe(PfnOfPd, Protect);
                NumberOfPages++;
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

            ULONG NumberOfNewPdes = 0;
            do
            {
                /* Check if the PDE is empty */
                if (CurrentPde->IsEmpty())
                {
                    /* Map the PT */
                    PfnOfPt = PageList.RemovePage();
                    g_PfnDatabase.MakePageTablePfn(PfnOfPt, CurrentPde, Protect);
                    CurrentPde->MakeValidPde(PfnOfPt, Protect);
                    NumberOfPages++;
                    NumberOfNewPdes++;
                }
                else
                {
                    /* Get the page frame number of the PT */
                    PfnOfPt = CurrentPde->GetPageFrameNumber();
                }

                /* Calculate the margin for PTEs in this PT */
                //MarginPte = MinPtr(PdeToPte(CurrentPde + 1), EndPte);


                /* Go to the next PDE */
                CurrentPde++;
            } while (CurrentPde < MarginPde);

            /* Increment entry count in the parent page table */
            g_PfnDatabase.IncrementEntryCount(PfnOfPd, NumberOfNewPdes);

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

    /* Return the pages, we did not consume */
    //g_PfnDatabase.ReleaseMultiplePages(&PageList);

    *OutUsedPages = NumberOfPages;

    return STATUS_SUCCESS;
}


PPTE
ReservePtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{

    if (StartingVpn >= LowestSystemVpn)
    {
        // lock kernel address space
    }
    else
    {
        // lock process address space
    }

#if MI_PAGING_LEVELS >= 4
    for (PPXE PxePointer = AddressToPxe(StartAddress);
         PxePointer <= AddressToPxe(EndAddress);
         PxePointer++)
    {
        if (PxePointer->IsEmpty())
        {
            PageFrameNumber = g_PfnDatabase.AllocatePage();
            NT_ASSERT(PageFrameNumber != 0); /// \todo FIXME

            g_PfnDatabase.MakePageTablePfn(PageFrameNumber);

            *PxePointer = PXE::CreateValidKernelPxe(PageFrameNumber);
        }
    }
#endif
#if MI_PAGING_LEVELS >= 3
    for (PPPE PpePointer = AddressToPpe(StartAddress);
         PpePointer <= AddressToPpe(EndAddress);
         PpePointer++)
    {
        if (PpePointer->IsEmpty())
        {
            PageFrameNumber = g_PfnDatabase.AllocatePage();
            NT_ASSERT(PageFrameNumber != 0); /// \todo FIXME

            g_PfnDatabase.MakePageTablePfn(PageFrameNumber);

            PpePointer->MakeValidPpe(PageFrameNumber, Protect);

            PxePointer = AddressToPxe(PpeToAddress(PpePointer));
            g_PfnDatabase.IncrementEntryCount(PxePointer->GetPageFrameNumber());
        }
    }
#endif
    for (PPDE PdePointer = AddressToPde(StartAddress);
         PdePointer <= AddressToPde(EndAddress);
         PdePointer++)
    {
        if (PdePointer->IsEmpty())
        {
#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
            *PdePointer = PDE::CreateValidLargePageKernelPde(EarlyAllocLargePage());
            RtlFillMemoryUlonglong(PdeToAddress(PdePointer), LARGE_PAGE_SIZE, 0);
#else
            *PdePointer = PDE::CreateValidKernelPde(EarlyAllocPage());
            RtlFillMemoryUlonglong(PteToAddress(PdePointer), PAGE_SIZE, 0);
#endif
        }
    }

    if (StartingVpn >= LowestSystemVpn)
    {
        // unlock kernel address space
    }
    else
    {
        // unlock process address space
    }

    return AddressToPte(StartAddress);
}

VOID
CreateMapping (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    PPTE FirstPte, LastPte, CurrentPte;
    PTE TemplatePte;
    PFN_NUMBER PageFrameNumber;
    NTSTATUS Status;

    NT_ASSERT((StartingVpn >= LowestSystemVpn) || (EndingVpn < LowestSystemVpn));
    NT_ASSERT((StartingVpn < LowestSystemVpn) || (Protect & MM_GLOBAL));

    Status = ChargeSystemCommit(CommitCharge);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /// \todo charge resident available / non-paged pages

    // reserve PTEs
    FirstPte = ReservePtes(StartingVpn, EndingVpn, &NewPageTables);
    LastPte = FirtstPte + NumberOfPages - 1;

    /* Check if mapping of pages is requested */
    if (Protect & MM_MAPPED)
    {
        // create a template PTE
        TemplatePte.InitializeValidPte(Protect);

        /* No mapping is requested, just write the demand PTEs */
        for (CurrentPte = FirstPte; CurrentPte <= LastPte; ++CurrentPte)
        {
            /* Check if the PTE is empty */
            if (CurrentPte->IsEmpty())
            {
                // Allocate physical page
                PageFrameNumber = g_PfnDatabase.AllocatePage();

                // Make it non-paged if Protect & MM_NONPAGED
                if (Protect & MM_NONPAGED)
                {
                    g_PfnDatabase.LockPfn(PageFrameNumber);
                }

                TemplatePte.SetPageFrameNumber(PageFrameNumber);

                // write the PTE
                CurrentPte->WritePte(TemplatePte);
            }
        }
    }
    else
    {
        // create a template PTE
        TemplatePte.InitializeSoftwarePte(Protect);

        /* No mapping is requested, just write the demand PTEs */
        for (CurrentPte = FirstPte; CurrentPte <= LastPte; ++CurrentPte)
        {
            /* Check if the PTE is empty */
            if (CurrentPte->IsEmpty())
            {
                // write demand zero PTE
                CurrentPte->WritePte(TemplatePte);
            }
        }
    }

}

VOID
CreateLargePageMapping (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages)
{



}

VOID
CreateMappingFromPfns (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ PPFN_NUMBER PfnArray,
    _In_ ULONG Protect)
{



}

