/*!

    \file Mapping.cpp

    \brief Implements architecture independent mapping functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "Mapping.hpp"
#include "PfnDatabase.hpp"
#include "CommitCharge.hpp"
#include "AddressSpace.hpp"
#include "VadObject.hpp"
#include "Utilities.hpp"
#include _ARCH_RELATIVE_(PageTables.hpp)
#include _ARCH_RELATIVE_(MachineDependent.hpp)

namespace Mm {

extern ULONG_PTR LowestSystemVpn;
PFN_NUMBER GlobalZeroPfn;

PVOID
ReserveKernelMemory (
    SIZE_T Size);

VOID
ReleaseKernelMemory (
    _In_ PVOID BaseAddress);


/*! \fn CalculateMaximumNumberOfPageTables
 *
 *  \brief Calculates the maximum number of physical pages for page tables that
 *      a mapping of a given VPN range might need.
 *
 *  \param [in] StartingVpn - The starting VPN of the range.
 *
 *  \param [in] EndingVpn - The (inclusive) ending VPN of the range.
 *
 *  \return The maximum number of physical pages for page tables.
 */
ULONG_PTR
CalculateMaximumNumberOfPageTables (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn)
{
    ULONG_PTR PageCount;

    PageCount = 0;
#if MI_PAGING_LEVELS >= 4
    PageCount += VpnToPxe(EndingVpn) - VpnToPxe(StartingVpn) + 1;
#endif
#if MI_PAGING_LEVELS >= 3
    PageCount += VpnToPpe(EndingVpn) - VpnToPpe(StartingVpn) + 1;
#endif
    PageCount += VpnToPde(EndingVpn) - VpnToPde(StartingVpn) + 1;

    return PageCount;
}

/*! \fn AllocatePagesForMapping
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] EndingVpn -
 *
 *  \param [out] PageList -
 *
 *  \param [out] LargePageList -
 *
 *  \param [in] ChargeForPages -
 *
 *  \param [in] Protect -
 *
 *  \param [out] PagesCharged -
 *
 *  \return ...
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
AllocatePagesForMapping (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _Out_ PPFN_LIST PageList,
    _When_(Protect & MM_LARGEPAGE, _Out_) PPFN_LIST LargePageList,
    _In_ BOOLEAN ChargeForPages,
    _In_ ULONG Protect,
    _Out_ PULONG_PTR PagesCharged)
{
    ULONG_PTR MaxPageTables, NumberOfPages, CommitCharge, PageAllocation;
    NTSTATUS Status;

    NT_ASSERT(EndingVpn >= StartingVpn);
    NT_ASSERT(ChargeForPages || !(Protect & MM_MAPPED));

    /* Calculate the maximum number of page tables and pages */
    MaxPageTables = CalculateMaximumNumberOfPageTables(StartingVpn, EndingVpn);
    NumberOfPages = EndingVpn - StartingVpn + 1;

    /* Check if we allocate for a large page mapping */
    if (Protect & MM_LARGEPAGE)
    {
        NT_ASSERT(LargePageList != NULL);
        NT_ASSERT(Protect & MM_NONPAGED);
        NT_ASSERT(Protect & MM_MAPPED);

        // assert alignment?

        /* Fix up page count for page tables (don't allocate pages for PTs) */
        MaxPageTables -= VpnToPde(EndingVpn) - VpnToPde(StartingVpn) + 1;
    }

    /* Calculate for how many pages we charge */
    CommitCharge = MaxPageTables + (ChargeForPages ? NumberOfPages : 0);

    /* Charge the system commit */
    Status = ChargeSystemCommit(CommitCharge);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Calculate how many pages we need to allocate */
    PageAllocation = MaxPageTables;
    if ((Protect & (MM_MAPPED|MM_LARGEPAGE)) == MM_MAPPED)
    {
        /* Add the mapped pages for the allocation as well */
        PageAllocation += NumberOfPages;
    }

    /* Allocate the pages */
    Status = g_PfnDatabase.AllocateMultiplePages(PageList, PageAllocation, TRUE);
    if (!NT_SUCCESS(Status))
    {
        UnchargeSystemCommit(CommitCharge);
        return Status;
    }

    /* Check if we allocate for a large page mapping */
    if (Protect & MM_LARGEPAGE)
    {
        /* Allocate large pages */
        Status = g_PfnDatabase.AllocateLargePages(LargePageList,
                                                  NumberOfPages / (LARGE_PAGE_SIZE / PAGE_SIZE),
                                                  FALSE);
        if (!NT_SUCCESS(Status))
        {
            g_PfnDatabase.ReleaseMultiplePages(PageList);
            UnchargeSystemCommit(CommitCharge);
            return Status;
        }
    }

    *PagesCharged = CommitCharge;
    return STATUS_SUCCESS;
}

/*! \fn AllocatePageTables
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] EndingVpn -
 *
 *  \param [in] PageList -
 *
 *  \param [in] Protect -
 *
 *  \return The number of physical pages that have been used to map page tables.
 */
static
ULONG_PTR
ReserveMappingPtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _In_ PPFN_LIST PageList,
    _In_ ULONG Protect)
{
    ULONG_PTR PagesUsed;
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
    PPTE CurrentPte = VpnToPte(StartingVpn);
    PPTE EndPte = VpnToPte(EndingVpn) + 1;
    PPTE MarginPte;

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
    PagesUsed = 0;

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
                //UNIMPLEMENTED;
            }
            else
            {
                ULONG NumberOfNewPdes = 0;
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

                    /* Calculate the number of used PTEs */
                    ULONG NumberOfNewPtes = (ULONG)(MarginPte - CurrentPte);

                    /* Increment entry count in the parent page table */
                    g_PfnDatabase.ModifyUsedCount(PfnOfPt, NumberOfNewPtes);

                    /* Update the PTE pointer */
                    CurrentPte = MarginPte;

                    /* Go to the next PDE */
                    CurrentPde++;
                } while (CurrentPde < MarginPde);

                /* Increment entry count in the page directory and count pages */
                g_PfnDatabase.ModifyEntryCount(PfnOfPd, NumberOfNewPdes);
                PagesUsed += NumberOfNewPdes;
            }

            /* Continue with PDE at the next PPE boundary */
            CurrentPde = MarginPde;

#if (MI_PAGING_LEVELS >= 3)
            /* Go to the next PPE */
            CurrentPpe++;
        } while (CurrentPpe < MarginPpe);

        /* Increment entry count in the parent directory and count pages */
        g_PfnDatabase.ModifyEntryCount(PfnOfPdpt, NumberOfNewPpes);
        PagesUsed += NumberOfNewPpes;
#endif /* MI_PAGING_LEVELS >= 3 */

#if (MI_PAGING_LEVELS >= 4)
        /* Go to the next PXE */
        CurrentPxe++;
    } while (CurrentPxe < EndPxe);

    /* Increment entry count in the parent page table */
    g_PfnDatabase.ModifyEntryCount(PfnOfPml4, NumberOfNewPxes);
    PagesUsed += NumberOfNewPxes;
#endif /* MI_PAGING_LEVELS >= 4 */

    return PagesUsed;
}

/*! \fn PrepareSystemMappingRange
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] EndingVpn -
 *
 *  \param [in] Protect -
 *
 *  \return The number of physical pages that have been used to map page tables.
 *
 *  \remarks
 *      - System PTEs are PTEs managed by the system only, usermode function
 *        must not map/unmap them.
 *      - System PTEs can be located in the user mode address range, but only
 *        in a special system reserved VAD, that cannot be decommitted or
 *        released from user mode.
 *      - When reserving a range of System PTEs, the address range must be
 *        exclusively owned by the calling thread and all PTEs must be empty.
 *      - Since all mapped page tables have a valid-count > 0, they can not be
 *        paged out
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
PrepareSystemMappingRange (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    ULONG_PTR EndingVpn, PagesCharged, PagesUsed, PageCount;
    PPDE CurrentPde, LastPde;
    PFN_LIST PageList;
    NTSTATUS Status;

    /* Allocate pages for the page tables */
    EndingVpn = StartingVpn + NumberOfPages - 1;
    Status = AllocatePagesForMapping(StartingVpn,
                                     EndingVpn,
                                     &PageList,
                                     NULL,
                                     FALSE,
                                     Protect,
                                     &PagesCharged);
    if (!NT_SUCCESS(Status))
    {
        ERR("Could not allocate pages for mapping: %x\n", Status);
        return Status;
    }

    /* Lock the kernel address space */
    /// \todo use systemlock queued spinlock?
    // g_AddressSpaces[SystemMappingSpace].AcquireWorkingsetLock();

    /* Allocate the page tables for the mapping */
    PagesUsed = AllocatePageTables(StartingVpn, EndingVpn, &PageList, Protect);

    /* Calculate the PDE range */
    CurrentPde = VpnToPde(StartingVpn);
    LastPde = VpnToPde(EndingVpn);

    /* Check if all PTEs are in the same PT */
    if (CurrentPde == LastPde)
    {
        /* Simply add all pages to the count of valid PTEs */
        g_PfnDatabase.ModifyEntryCount(CurrentPde->GetPageFrameNumber(), NumberOfPages);
    }
    else
    {
        /* Increment number of active PTEs in the first PT */
        PageCount = PdeToPte(CurrentPde + 1) - VpnToPte(StartingVpn);
        g_PfnDatabase.ModifyEntryCount(CurrentPde->GetPageFrameNumber(), PageCount);

        /* Loop all fully used PDEs */
        while (++CurrentPde < LastPde)
        {
            /* Increment the number by the number of PTEs per PT */
            g_PfnDatabase.ModifyEntryCount(CurrentPde->GetPageFrameNumber(), PTE_PER_PAGE);
        }

        /* Finally update the count for the last PT */
        PageCount = VpnToPte(EndingVpn + 1) - PdeToPte(CurrentPde);;
        g_PfnDatabase.ModifyEntryCount(CurrentPde->GetPageFrameNumber(), PageCount);
    }

    /* Unlock the kernel address space */
    /// \todo use systemlock queued spinlock?

    /* Return the pages, we did not use */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);
    UnchargeSystemCommit(PagesCharged - PagesUsed);

    return STATUS_SUCCESS;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
ReserveSystemMappingRange (
    _In_ ULONG_PTR NumberOfPages)
{
    PVOID BaseAddress;
    NTSTATUS Status;

    /* Reserve kernel address space */
    BaseAddress = ReserveKernelVaSpace(NumberOfPages);
    if (BaseAddress == NULL)
    {
        ERR("Could not reserve kernel address space.\n");
        return NULL;
    }

    /* Prepare the mapping PTEs */
    Status = PrepareSystemMappingRange(AddressToVpn(BaseAddress),
                                       NumberOfPages,
                                       MM_EXECUTE_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        ERR("Could not prepare mapping range: %x\n", Status);
        ReleaseKernelVaSpace(BaseAddress);
        return NULL;
    }

    /* Return the base address of the mapping range */
    return BaseAddress;
}

VOID
CleanupSystemMappingRange (
    _In_ PVOID BaseAddress)
{

}

VOID
ReleaseSystemMappingRange (
    _In_ PVOID BaseAddress)
{
    VAD_OBJECT* Vad;
    ULONG_PTR EndingVpn;

    Vad = g_KernelAddressSpace.ReferenceVadObjectByAddress(BaseAddress, FALSE);
    NT_ASSERT(Vad != NULL);

    EndingVpn = Vad->GetEndingVpn();

}

BOOLEAN
CheckReservedMapping (
    _In_ PVOID MappingAddress,
    _In_ ULONG Tag,
    _In_ ULONG_PTR NumberOfPages)
{
    /// Check if the tag is correct and the mapping is large enough
    UNIMPLEMENTED;
    return TRUE;
}

/*! \fn MapPhysicalMemory
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \param [in] BasePageFrameNumber -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
MapPhysicalMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PFN_NUMBER BasePageFrameNumber)
{
    ULONG_PTR EndingVpn, PagesCharged, PagesUsed;
    PFN_NUMBER PageFrameNumber, PfnOfPt;
    ULONG NumberOfNewPtes;
    PFN_LIST PageList;
    PTE TemplatePte;
    PPTE CurrentPte;
    PPDE CurrentPde;
    NTSTATUS Status;


    NT_ASSERT((Protect & (MM_LARGEPAGE)) == 0);
    NT_ASSERT((Protect & MM_PROTECTION_MASK) != MM_NOACCESS);

    /* Allocate pages for the page tables */
    EndingVpn = StartingVpn + NumberOfPages - 1;
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

    /* Reserve the PTEs for the mapping */
    PagesUsed = ReserveMappingPtes(StartingVpn, EndingVpn, &PageList, Protect);

    /* Loop all reserved PTEs */
    CurrentPte = VpnToPte(StartingVpn);
    CurrentPde = VpnToPde(StartingVpn);
    NumberOfNewPtes = 0;
    do
    {
        /* Make sure the PTE is empty */
        NT_ASSERT(CurrentPte->IsEmpty());
        TemplatePte.SetPageFrameNumber(PageFrameNumber);
        CurrentPte->WriteValidPte(TemplatePte);
        NumberOfNewPtes++;

        /* Next PTE and next PFN */
        CurrentPte++;
        PageFrameNumber++;
        NumberOfPages--;

        /* Update the PFN of the PT, if we reached the next PT or the end */
        if ((CurrentPte->IsPdeBoundary()) || (NumberOfPages == 0))
        {
            PfnOfPt = CurrentPde->GetPageFrameNumber();
            g_PfnDatabase.ModifyEntryCount(PfnOfPt, NumberOfNewPtes);
            NumberOfNewPtes = 0;
            CurrentPde++;
        }
    }
    while (NumberOfPages);

    AddressSpace->ReleaseLock()

    /* Return the pages, we did not use */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);
    NT_ASSERT(PagesUsed <= PagesCharged);
    UnchargeSystemCommit(PagesCharged - PagesUsed);

    return STATUS_SUCCESS;
}

/*! \fn MapPfnArray
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \param [in] PfnArray -
 *
 *  \return ...
 */
NTSTATUS
MapPfnArray (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PPFN_NUMBER PfnArray)
{
    ULONG_PTR EndingVpn, PagesCharged, PagesUsed;
    PFN_NUMBER PfnOfPt;
    ULONG NumberOfNewPtes;
    PFN_LIST PageList;
    PTE TemplatePte;
    PPTE CurrentPte;
    PPDE CurrentPde;
    NTSTATUS Status;

    /* For now only kernel mode addresses! */ /// we need usermode as well
    NT_ASSERT(VpnToAddress(StartingVpn) >= MmSystemRangeStart);

    NT_ASSERT((Protect & (MM_LARGEPAGE)) == 0);
    NT_ASSERT((Protect & MM_PROTECTION_MASK) != MM_NOACCESS);

    /* Allocate pages for the page tables */
    EndingVpn = StartingVpn + NumberOfPages - 1;
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

    /* Acquire the kernel working set lock */ /// see above
    g_KernelAddressSpace.AcquireWorkingSetLock();

    /* Reserve the PTEs for the mapping */
    PagesUsed = ReserveMappingPtes(StartingVpn, EndingVpn, &PageList, Protect);

    /* Prepare a template PTE */
    TemplatePte.MakeValidPte(0, Protect);

    /* Loop all reserved PTEs */
    CurrentPte = VpnToPte(StartingVpn);
    CurrentPde = VpnToPde(StartingVpn);
    NumberOfNewPtes = 0;
    do
    {
        /* Make sure the PTE is empty */
        NT_ASSERT(CurrentPte->IsEmpty());
        TemplatePte.SetPageFrameNumber(*PfnArray);
        CurrentPte->WriteValidPte(TemplatePte);
        NumberOfNewPtes++;

        /* Next PTE and next PFN array element */
        CurrentPte++;
        PfnArray++;
        NumberOfPages--;

        /* Update the PFN of the PT, if we reached the next PT or the end */
        if ((CurrentPte->IsPdeBoundary()) || (NumberOfPages == 0))
        {
            PfnOfPt = CurrentPde->GetPageFrameNumber();
            g_PfnDatabase.ModifyEntryCount(PfnOfPt, NumberOfNewPtes);
            NumberOfNewPtes = 0;
            CurrentPde++;
        }
    }
    while (NumberOfPages);

    /* Release the kernel working set lock */
    g_KernelAddressSpace.ReleaseWorkingSetLock();

    /* Return the pages, we did not use */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);
    UnchargeSystemCommit(PagesCharged - PagesUsed);

    return STATUS_SUCCESS;
}

/*! \fn MapNonPagedMemory
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \param [in] PfnList -
 */
NTSTATUS
MapNonPagedMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    PFN_NUMBER PageFrameNumber;
    PTE TemplatePte;
    PPTE CurrentPte;
    PFN_LIST PfnList;
    NTSTATUS Status;

    NT_ASSERT((Protect & (MM_LARGEPAGE)) == 0);
    NT_ASSERT((Protect & MM_PROTECTION_MASK) != MM_NOACCESS);

    /* Charge the system commit */
    Status = ChargeSystemCommit(NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Allocate pages */
    Status = g_PfnDatabase.AllocateMultiplePages(&PfnList, NumberOfPages, FALSE);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Prepare a template PTE */
    TemplatePte.MakeValidPte(0, Protect);

    /* Loop all reserved PTEs */
    CurrentPte = VpnToPte(StartingVpn);
    do
    {
        /* Make sure the PTE is empty */
        NT_ASSERT(CurrentPte->IsEmpty());

        /* Remove a page from the list */
        PageFrameNumber = PfnList.RemovePage();
        NT_ASSERT(PageFrameNumber != 0);

        /* Make it into a private PFN */
        //g_PfnDatabase.MakePrivatePfn(PageFrameNumber, Protect);

        /* Map the page */
        TemplatePte.SetPageFrameNumber(PageFrameNumber);
        CurrentPte->WriteValidPte(TemplatePte);

        /* Next PTE */
        CurrentPte++;
        NumberOfPages--;
    }
    while (NumberOfPages);

    return STATUS_SUCCESS;
}

/*! \fn MapVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
NTSTATUS
MapVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    PADDRESS_SPACE AddressSpace;
    ULONG_PTR EndingVpn, PagesCharged, PagesUsed;
    PFN_NUMBER PageFrameNumber, PfnOfPt;
    ULONG NumberOfNewPdes, NumberOfNewPtes;
    PFN_LIST PageList, LargePageList;
    PTE TemplatePte;
    PPTE CurrentPte;
    PPDE CurrentPde;
    NTSTATUS Status;

    NT_ASSERT((Protect & MM_PROTECTION_MASK) != MM_NOACCESS);

    /* Calculate the ending VPN */
    EndingVpn = StartingVpn + NumberOfPages - 1;

    /* Check for large page mapping */
    if ((Protect & MM_LARGEPAGE) != 0)
    {
        NT_ASSERT(Protect & MM_NONPAGED);
        /* Align VPNs and page count to large page boundaries */
        StartingVpn = ALIGN_DOWN_BY(StartingVpn, LARGE_PAGE_SIZE / PAGE_SIZE);
        EndingVpn = ALIGN_UP_BY(EndingVpn + 1, LARGE_PAGE_SIZE / PAGE_SIZE) - 1;
        NumberOfPages = EndingVpn - StartingVpn + 1;
    }

    /* Allocate pages for the page tables */
    Status = AllocatePagesForMapping(StartingVpn,
                                     EndingVpn,
                                     &PageList,
                                     &LargePageList,
                                     TRUE,
                                     Protect,
                                     &PagesCharged);
    if (!NT_SUCCESS(Status))
    {
        ERR("Could not allocate pages for mapping: %x\n", Status);
        return Status;
    }

    /* Acquire the working set lock */
    AddressSpace = GetAddressSpaceForAddress(VpnToAddress(StartingVpn));
    AddressSpace->AcquireWorkingSetLock();

    /* Allocate page tables for the mapping */
    ReserveMappingPtes()

    /* Check for large page mapping */
    if ((Protect & MM_LARGEPAGE) != 0)
    {
        /* Loop all reserved PDEs */
#if (MI_PAGING_LEVELS >= 4)
        PPPE CurrentPpe = VpnToPpe(StartingVpn);
#endif
        CurrentPde = VpnToPde(StartingVpn);
        NumberOfNewPdes = 0;
        do
        {
            /* Check if the PDE is empty */
            if (CurrentPde->IsEmpty())
            {
                /* Map the large page */
                PageFrameNumber = LargePageList.RemovePage();
                g_PfnDatabase.MakeLargePagePfn(PageFrameNumber, CurrentPde, Protect);
                CurrentPde->MakeValidLargePagePde(PageFrameNumber, Protect);
                NumberOfNewPdes++;
            }
            else
            {
                NT_ASSERT(CurrentPde->IsLargePage());
            }

            /* Next PDE */
            CurrentPde++;
            NumberOfPages -= LARGE_PAGE_SIZE / PAGE_SIZE;

            /* Update the PFN of the PD, if we reached the next PD or the end */
            if ((CurrentPde->GetTableIndex() == 0) || (NumberOfPages == 0))
            {
#if (MI_PAGING_LEVELS >= 4)
                PFN_NUMBER PfnOfPd = CurrentPpe->GetPageFrameNumber();
                g_PfnDatabase.ModifyEntryCount(PfnOfPd, NumberOfNewPdes);
                CurrentPpe++;
#endif
                PagesUsed += NumberOfNewPdes * (LARGE_PAGE_SIZE / PAGE_SIZE);
                NumberOfNewPdes = 0;
            }
        }
        while (NumberOfPages);

        /* Return the large pages, we did not use */
        g_PfnDatabase.ReleaseLargePages(&LargePageList);
    }
    else
    {
        /* Prepare a template PTE */
        TemplatePte.MakeValidPte(0, Protect);

        /* Loop all reserved PTEs */
        CurrentPte = VpnToPte(StartingVpn);
        CurrentPde = VpnToPde(StartingVpn);
        NumberOfNewPtes = 0;
        do
        {
            /* Check, if the PTE is empty */
            if (CurrentPte->IsEmpty())
            {
                TemplatePte.SetPageFrameNumber(PageList.RemovePage());
                CurrentPte->WriteValidPte(TemplatePte);
                NumberOfNewPtes++;
            }
            else
            {
                __debugbreak();
            }

            /* Next PTE */
            CurrentPte++;
            NumberOfPages--;

            /* Update the PFN of the PT, if we reached the next PT or the end */
            if ((CurrentPte->IsPdeBoundary()) || (NumberOfPages == 0))
            {
                PfnOfPt = CurrentPde->GetPageFrameNumber();
                g_PfnDatabase.ModifyEntryCount(PfnOfPt, NumberOfNewPtes);
                PagesUsed += NumberOfNewPtes;
                NumberOfNewPtes = 0;
                CurrentPde++;
            }
        }
        while (NumberOfPages);
    }

    /* Release the working set lock */
    AddressSpace->ReleaseWorkingSetLock();

    /* Return the pages, we did not use */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);
    UnchargeSystemCommit(PagesCharged - PagesUsed);

    return STATUS_SUCCESS;
}

/*! \fn MapPrototypePtes
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \param [in] Prototypes -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
MapPrototypePtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PPTE Prototypes)
{
    PFN_NUMBER PfnOfPt;
    ULONG NumberOfNewPtes;
    PPTE CurrentPte;
    PPDE CurrentPde;
    NTSTATUS Status;

    /* Get the PFN of the page table */
    PfnOfPt = VpnToPde(StartingVpn)->GetPageFrameNumber();

    /* Get the starting PTE */
    CurrentPte = VpnToPte(StartingVpn);

    /* Allocate pages for the page tables */
    EndingVpn = StartingVpn + NumberOfPages - 1;
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

    /* Acquire the working set lock */
    AddressSpace = GetAddressSpaceForAddress(VpnToAddress(StartingVpn));
    AddressSpace->AcquireWorkingSetLock();

    /* Reserve the PTEs for the mapping */
    PagesUsed = AllocatePageTables(StartingVpn, EndingVpn, &PageList, Protect);

    /* Loop all reserved PTEs */
    CurrentPte = VpnToPte(StartingVpn);
    CurrentPde = VpnToPde(StartingVpn);
    NumberOfNewPtes = 0;
    do
    {
        /* Make sure the PTE is a no-access PTE and make it a prototype PTE */
        NT_ASSERT(CurrentPte->IsNoAccess());
        CurrentPte->MakePrototypePte(Prototypes, Protect);
        NumberOfNewPtes++;

        /* Next PTE and next prototype */
        CurrentPte++;
        Prototypes++;
        NumberOfPages--;

#if 0 // This only makes sense, when we move page table referencing completely out
// of the reserving function, but then we need to lock outside of both functions
        /* Update the PFN of the PT, if we reached the next PT or the end */
        if ((CurrentPte->IsPdeBoundary()) || (NumberOfPages == 0))
        {
            PfnOfPt = CurrentPde->GetPageFrameNumber();
            g_PfnDatabase.ModifyEntryCount(PfnOfPt, NumberOfNewPtes);
            NumberOfNewPtes = 0;
            CurrentPde++;
        }
#endif
    }
    while (NumberOfPages);

    /* Release the working set lock */
    AddressSpace->ReleaseWorkingSetLock();

    /* Return the pages, we did not use */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);
    UnchargeSystemCommit(PagesCharged - PagesUsed);

    return STATUS_SUCCESS;
}

/*! \fn UnmapPages
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] ReleasePages -
 */
VOID
UnmapPages (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ BOOLEAN ReleasePages)
{
    PADDRESS_SPACE AddressSpace;
    PFN_NUMBER PfnOfPt, PageFrameNumber;
    //PFN_LIST PageList;
    LONG NumberOfDeletedPtes, NumberOfInvalidatedPtes;
    PVOID AddressArray[32];
    ULONG AddressCount;
    ULONG_PTR RemainingPages;
    PPTE CurrentPte;
    PPDE CurrentPde;

//__debugbreak();
    AddressCount = 0;

    /* Acquire the working set lock */
    AddressSpace = GetAddressSpaceForAddress(VpnToAddress(StartingVpn));
    AddressSpace->AcquireWorkingSetLock();

    /* Loop all PTEs */
    CurrentPte = VpnToPte(StartingVpn);
    CurrentPde = VpnToPde(StartingVpn);
    NumberOfDeletedPtes = 0;
    NumberOfInvalidatedPtes = 0;
    RemainingPages = NumberOfPages;
    do
    {
        /* Check if the PTE is not empty */
        if (!CurrentPte->IsEmpty())
        {
            /* Check if the PTE is valid */
            if (CurrentPte->IsValid())
            {
                /* Check if the caller wants to release the pages */
                if (ReleasePages)
                {
                    /* Get the page frame number */
                    PageFrameNumber = CurrentPte->GetPageFrameNumber();

                    UNIMPLEMENTED;
                    (void)PageFrameNumber;

                    /// since we own the WS lock, we can access the reference count
                    /// of the PFN without locking the PFN database!
                    /// For section PFNs, we must additionally own the SECTION lock!
                    /// Locked pages and IoSpace are not released
                }

                /* Check if we still have free slots in the address list */
                if (AddressCount < RTL_NUMBER_OF(AddressArray))
                {
                    /* Add this virtual address to the address list */
                    AddressArray[AddressCount] = PteToAddress(CurrentPte);
                    AddressCount++;
                }

                /* Increment number of invalidated PTEs in this PT */
                NumberOfInvalidatedPtes++;
            }

            CurrentPte->Erase();
            NumberOfDeletedPtes++;
        }

        /* Next PTE */
        CurrentPte++;
        RemainingPages--;

        /* Update the PFN of the PT, if we reached the next PT or the end */
        if ((CurrentPte->IsPdeBoundary()) || (RemainingPages == 0))
        {
            PfnOfPt = CurrentPde->GetPageFrameNumber();
            g_PfnDatabase.ModifyValidCount(PfnOfPt, -NumberOfInvalidatedPtes);
            if (g_PfnDatabase.ModifyUsedCount(PfnOfPt, -NumberOfDeletedPtes) == 0)
            {
                /// FIXME: unmap the page table
                __debugbreak();
            }

            NumberOfInvalidatedPtes = 0;
            NumberOfDeletedPtes = 0;
            CurrentPde++;
        }
    }
    while (RemainingPages);

    /* Check if we have invalidated more than 32 PTEs */
    if (AddressCount > RTL_NUMBER_OF(AddressArray))
    {
        /* Check if this is kernel or user mode */
        if (StartingVpn < AddressToVpn(MmSystemRangeStart))
        {
            /* User mode, flush the process TLB */
            KeFlushProcessTb();
        }
        else
        {
            /* Kernel mode, flush the whole range */
            KeFlushRangeTb(VpnToAddress(StartingVpn), NumberOfPages);
        }
    }
    /* Check if any pages were invalidated at all */
    else if (AddressCount > 0)
    {
        /* Flush the addresses that we collected */
        KeFlushMultipleTb(AddressArray, AddressCount);
    }

    /* Release the working set lock */
    AddressSpace->ReleaseWorkingSetLock();
}

/*! \fn ProtectVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \param [out] OutOldProtect -
 *
 *  \return ...
 */
NTSTATUS
ProtectVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _Out_ PULONG OutOldProtect)
{
    UNIMPLEMENTED;
    return STATUS_UNSUCCESSFUL;
}

/*! \fn CheckVirtualMapping
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [out] OutRegionSize -
 *
 *  \param [out] OutProtect -
 */
VOID
CheckVirtualMapping (
    _In_ PVOID BaseAddress,
    _Out_ PSIZE_T OutRegionSize,
    _Out_ PULONG OutProtect)
{
    UNIMPLEMENTED;
}

/// ****************************************************************************


extern "C" {

/*! \fn MmAllocateMappingAddress
 *
 *  \brief ...
 *
 *  \param [in] NumberOfBytes -
 *
 *  \param [in] Tag -
 *
 *  \return ...
 *
 *  \todo Handle Tag (could use one additional "PTE" to store it and one for size)
 */
_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_When_ (return != NULL, _Out_writes_bytes_opt_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateMappingAddress (
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag) /// \todo handle Tag
{
    PVOID BaseAddress;
    NTSTATUS Status;

    /* Reserve virtual memory range */
    BaseAddress = ReserveSystemMappingRange(BYTES_TO_PAGES(NumberOfBytes));
    if (BaseAddress == NULL)
    {
        return NULL;
    }

    /* Map no-access PTEs */
    Status = MapVirtualMemory(AddressToVpn(BaseAddress),
                              BYTES_TO_PAGES(NumberOfBytes),
                              MM_NOACCESS | MM_GLOBAL | MM_NONPAGED);
    if (!NT_SUCCESS(Status))
    {
        ReleaseKernelMemory(BaseAddress);
        return NULL;
    }

    return BaseAddress;
}

/*! \fn MmFreeMappingAddress
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] Tag -
 *
 *  \todo Handle Tag
 */
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeMappingAddress (
    _In_ PVOID BaseAddress,
    _In_ ULONG Tag)
{
    /* Check if the reserved mapping is ok */
    if (!CheckReservedMapping(BaseAddress, Tag, 1))
    {
        ERR("Invalid mapping address: %p\n", BaseAddress);
        NT_ASSERT(FALSE);
        KeBugCheck(0);
        return;
    }

    ReleaseSystemMappingRange(BaseAddress);
}

/*! \fn MmMapIoSpace
 *
 *  \brief ...
 *
 *  \param [in] PhysicalAddress -
 *
 *  \param [in] NumberOfBytes -
 *
 *  \param [in] CachingType -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Out_writes_bytes_opt_ (NumberOfBytes)
PVOID
NTAPI
MmMapIoSpace (
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    PFN_NUMBER BasePageFrameNumber;
    ULONG_PTR NumberOfPages;
    PVOID BaseAddress;
    ULONG Protect;
    NTSTATUS Status;

    /* Get the number of pages for the mapping */
    NumberOfBytes += PhysicalAddress.LowPart & (PAGE_SIZE - 1);
    NumberOfPages = BYTES_TO_PAGES(NumberOfBytes);

    /* Reserve virtual memory range */
    BaseAddress = ReserveSystemMappingRange(NumberOfPages);
    if (BaseAddress == NULL)
    {
        return NULL;
    }

    /* Convert protection */
    Protect = ConvertProtectAndCaching(PAGE_READWRITE, CachingType);

    /* Map the physical pages */
    BasePageFrameNumber = (PFN_NUMBER)(PhysicalAddress.QuadPart >> PAGE_SHIFT);
    Status = MapPhysicalMemory(AddressToVpn(BaseAddress),
                               NumberOfPages,
                               Protect,
                               BasePageFrameNumber);
    if (!NT_SUCCESS(Status))
    {
        ReleaseKernelMemory(BaseAddress);
        return NULL;
    }

    /* Return the pointer to the real start address */
    return AddToPointer(BaseAddress, PhysicalAddress.LowPart & (PAGE_SIZE - 1));
}

/*! \fn MmUnmapIoSpace
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] NumberOfBytes -
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapIoSpace (
    _In_reads_bytes_ (NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes)
{
    ULONG_PTR NumberOfPages;

    /* Get the number of pages for the mapping */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseAddress, NumberOfBytes);

    /* Unmap the memory, ignore the PFNs */
    UnmapPages(AddressToVpn(BaseAddress), NumberOfPages, FALSE);

    /* Release the virtual memory */
    ReleaseSystemMappingRange(ALIGN_DOWN_POINTER_BY(BaseAddress, PAGE_SIZE));
}

/*! \fn MmMapLockedPages
 *
 *  \brief ...
 *
 *  \param [inout] MemoryDescriptorList -
 *
 *  \param [in] AccessMode -
 *
 *  \return ...
 */
_Must_inspect_result_
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL))
PVOID
NTAPI
MmMapLockedPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
        KPROCESSOR_MODE AccessMode)
{
    return MmMapLockedPagesSpecifyCache(MemoryDescriptorList,
                                        AccessMode,
                                        MmCached,
                                        NULL,
                                        FALSE,
                                        NormalPagePriority);
}

/*! \fn MmMapLockedPagesSpecifyCache
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 *
 *  \param [in] AccessMode -
 *
 *  \param [in] CacheType -
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] BugCheckOnFailure -
 *
 *  \param [in] Priority -
 *
 *  \return ...
 */
_Post_writable_byte_size_(Mdl->ByteCount)
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL) _Post_notnull_)
_At_(Mdl->MappedSystemVa, _Post_writable_byte_size_(Mdl->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesSpecifyCache (
    _Inout_ PMDLX Mdl,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
        KPROCESSOR_MODE AccessMode,
    _In_ __drv_strictTypeMatch(__drv_typeCond) MEMORY_CACHING_TYPE CacheType,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG BugCheckOnFailure,
    _In_ MM_PAGE_PRIORITY Priority)
{
    PADDRESS_SPACE AddressSpace;
    ULONG_PTR NumberOfPages;
    ULONG Protect;
    NTSTATUS Status;

if (Mdl == (PVOID)0xfffffa80001f7e20ULL) __debugbreak();

    /* Make sure the MDL is not yet mapped */
    NT_ASSERT(!(Mdl->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA));

    Protect = ConvertProtectAndCaching(PAGE_EXECUTE_READWRITE, CacheType);

    if (AccessMode == KernelMode)
    {
        AddressSpace = &g_KernelAddressSpace;
        BaseAddress = NULL;
        Protect |= MM_GLOBAL;
    }
    else
    {
        AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
        BugCheckOnFailure = 0;
        Protect |= MM_USER;
    }

    /* Calculate the number of pages */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(Mdl->StartVa, Mdl->ByteCount);

    Status = AddressSpace->ReserveVirtualMemory(&BaseAddress, NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to reserve virtual memory\n");
        goto Failure;
    }

    Status = MapPfnArray(AddressToVpn(BaseAddress),
                         NumberOfPages,
                         Protect,
                         MmGetMdlPfnArray(Mdl));
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to map MDL PFN array\n");
        // AddressSpace->ReleaseVirtualMemory()
        UNIMPLEMENTED;
        goto Failure;
    }

    Mdl->MappedSystemVa = AddToPointer(BaseAddress, Mdl->ByteOffset);
    Mdl->MdlFlags |= MDL_MAPPED_TO_SYSTEM_VA;

    if (Mdl->MdlFlags & MDL_PARTIAL)
        Mdl->MdlFlags |= MDL_PARTIAL_HAS_BEEN_MAPPED;

    return Mdl->MappedSystemVa;

Failure:

    if (BugCheckOnFailure)
    {
        KeBugCheckEx(0, 0, 0, 0, 0);
    }

    return NULL;
}

/*! \fn MmMapLockedPagesWithReservedMapping
 *
 *  \brief ...
 *
 *  \param [in] MappingAddress -
 *
 *  \param [in] PoolTag -
 *
 *  \param [inout] Mdl -
 *
 *  \param [in] CacheType -
 *
 *  \return ...
 */
_Post_writable_byte_size_(Mdl->ByteCount)
_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(Mdl->MappedSystemVa + Mdl->ByteOffset,
  _Post_writable_byte_size_(Mdl->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesWithReservedMapping (
    _In_ PVOID MappingAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDLX Mdl,
    _In_ __drv_strictTypeMatch(__drv_typeCond)
        MEMORY_CACHING_TYPE CacheType)
{
    ULONG_PTR NumberOfPages;
    ULONG Protect;

    /* Make sure the MDL is not yet mapped */
    NT_ASSERT(!(Mdl->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA));

    /* Calculate the number of pages */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(Mdl->StartVa, Mdl->ByteCount);

    /* Check if the reserved mapping is ok */
    if (!CheckReservedMapping(MappingAddress, PoolTag, NumberOfPages))
    {
        ERR("Invalid mapping address: %p\n", MappingAddress);
        return NULL;
    }

    /* Convert the protection */
    Protect = ConvertProtectAndCaching(PAGE_EXECUTE_READWRITE, CacheType);

    /* Map the PFNs from the MDL */
    MapPfnArray(AddressToVpn(MappingAddress),
                NumberOfPages,
                Protect | MM_GLOBAL,
                MmGetMdlPfnArray(Mdl));

    /* Update the MDL (MappedSystemVa does not contain the byte offset!) */
    Mdl->MappedSystemVa = MappingAddress;
    Mdl->MdlFlags |= MDL_MAPPED_TO_SYSTEM_VA;
    if (Mdl->MdlFlags & MDL_PARTIAL)
        Mdl->MdlFlags |= MDL_PARTIAL_HAS_BEEN_MAPPED;

    return AddToPointer(MappingAddress, Mdl->ByteOffset);

}

/*! \fn MmUnmapReservedMapping
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] PoolTag -
 *
 *  \param [inout] Mdl -
 *
 *  \param [in] CacheType -
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapReservedMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDLX Mdl)
{
    ULONG_PTR NumberOfPages;

    /* Calculate the size in pages */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseAddress, Mdl->ByteCount);

    /* Check if the reserved mapping is ok */
    if (!CheckReservedMapping(BaseAddress, PoolTag, NumberOfPages))
    {
        ERR("Invalid mapping address: %p\n", BaseAddress);
        NT_ASSERT(FALSE);
        KeBugCheck(0);
        return;
    }

    UNIMPLEMENTED_DBGBREAK;
}

/*! \fn MmUnmapLockedPages
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [inout] Mdl -
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapLockedPages (
    _In_ PVOID BaseAddress,
    _Inout_ PMDL Mdl)
{
    ULONG_PTR NumberOfPages;

    /* Calculate the number of pages */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(Mdl->StartVa, Mdl->ByteCount);

    /* Unmap the pages */
    UnmapPages(AddressToVpn(BaseAddress), NumberOfPages, FALSE);

    Mdl->MdlFlags &= ~(MDL_PARTIAL_HAS_BEEN_MAPPED | MDL_MAPPED_TO_SYSTEM_VA);
}

/*! \fn MmMapMemoryDumpMdl
 *
 *  \brief ...
 *
 *  \param [in] Mdl -
 *
 *  \param [in] CacheType -
 */
VOID
NTAPI
MmMapMemoryDumpMdl (
    _In_ PMDL Mdl)
{
    UNIMPLEMENTED;
}

/*! \fn MmGetPhysicalAddress
 *
 *  \brief Returns the physical address corresponding to a given virtual address.
 *
 *  \param [in] BaseAddress - The virtual address of interest.
 *
 *  \return The physical address corresponding to a given virtual address.
 */
PHYSICAL_ADDRESS
NTAPI
MmGetPhysicalAddress (
    _In_ PVOID BaseAddress)
{
    PFN_NUMBER PageFrameNumber;
    PHYSICAL_ADDRESS PhysicalAddress;
    PPDE PdePointer;
    PPTE PtePointer;

    /* Check if the address is valid */
    if (!MmIsAddressValid(BaseAddress))
    {
        PhysicalAddress.QuadPart = 0;
        return PhysicalAddress;
    }

    /* Get the PDE and PTE */
    PdePointer = AddressToPde(BaseAddress);
    PtePointer = AddressToPte(BaseAddress);

    /* Check if this is a large page allocation */
    if (PdePointer->IsLargePage())
    {
        /* Get the base page frame number of the large page */
        PageFrameNumber = PdePointer->GetPageFrameNumber();

        /* Add the page offset for the given address */
        PageFrameNumber += PtePointer - PdeToPte(PdePointer);
    }
    else
    {
        /* Get the page frame number */
        PageFrameNumber = PtePointer->GetPageFrameNumber();
    }

    /* Calculate the physical address */
    PhysicalAddress.QuadPart =
        (static_cast<ULONG64>(PageFrameNumber) << PAGE_SHIFT) +
        (reinterpret_cast<ULONG_PTR>(BaseAddress) & (PAGE_SIZE - 1));

    return PhysicalAddress;
}

/*! \fn MmSetAddressRangeModified
 *
 *  \brief ...
 *
 *  \param [in] Address -
 *
 *  \param [in] Length -
 *
 *  \return ...
 */
_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmSetAddressRangeModified (
    _In_reads_bytes_ (Length) PVOID Address,
    _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*! \fn MmIsAddressValid
 *
 *  \brief ...
 *
 *  \param [in] VirtualAddress -
 *
 *  \return ...
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
MmIsAddressValid (
    _In_ PVOID VirtualAddress)
{
    /* Check all present page table levels */
    return (
#if MI_PAGING_LEVELS >= 4
        AddressToPxe(VirtualAddress)->IsValid() &&
#endif
#if MI_PAGING_LEVELS >= 3
        AddressToPpe(VirtualAddress)->IsValid() &&
#endif
        AddressToPde(VirtualAddress)->IsValid() &&
        (AddressToPde(VirtualAddress)->IsLargePage() ||
         AddressToPte(VirtualAddress)->IsValid()));
}

/*! \fn MmIsNonPagedSystemAddressValid
 *
 *  \brief ...
 *
 *  \param [in] VirtualAddress -
 *
 *  \return ...
 */
BOOLEAN
NTAPI
MmIsNonPagedSystemAddressValid (
  _In_ PVOID VirtualAddress)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*! \fn MmMapUserAddressesToPage
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] NumberOfBytes -
 *
 *  \param [in] PageAddress -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmMapUserAddressesToPage (
  _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes,
  _In_ PVOID PageAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
}; // namespace Mm
