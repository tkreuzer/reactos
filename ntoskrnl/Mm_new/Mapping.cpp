

#include "Mapping.hpp"
#include "PfnDatabase.hpp"
#include "CommitCharge.hpp"
#include "AddressSpace.hpp"
#include _ARCH_RELATIVE_(PageTables.hpp)
#include _ARCH_RELATIVE_(MachineDependent.hpp)

/// HACK HACK HACK HACK
VOID
KeFlushMultipleTb (
    _In_ PVOID* AddressArray,
    _In_ ULONG AddressCount)
{
    while (AddressCount--)
    {
        __invlpg(AddressArray[AddressCount]);
    }
}

VOID
KeFlushRangeTb (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR NumberOfPages)
{
    while (NumberOfPages--)
    {
        __invlpg(BaseAddress);
        BaseAddress = AddToPointer(BaseAddress, PAGE_SIZE);
    }
}

VOID
KeFlushProcessTb ()
{
    __writecr3(__readcr3());
}


namespace Mm {

extern ULONG_PTR LowestSystemVpn;
PFN_NUMBER GlobalZeroPfn;

PVOID
ReserveKernelMemory (
    SIZE_T Size);

VOID
ReleaseKernelMemory (
    _In_ PVOID BaseAddress);

ULONG
ConvertProtect (
    _In_ ULONG Win32Protect)
{
    ULONG Protect;

    if (Win32Protect & PAGE_IS_WRITECOPY)
        Protect = MM_WRITECOPY;
    else if (Win32Protect & PAGE_IS_WRITABLE)
        Protect = MM_READWRITE;
    else if (Win32Protect & PAGE_IS_READABLE)
        Protect = MM_READONLY;

    if (Win32Protect & PAGE_IS_EXECUTABLE)
        Protect |= MM_EXECUTE;

    if (Win32Protect & PAGE_WRITECOMBINE)
        Protect |= MM_WRITECOMBINE;
    else if (Win32Protect & PAGE_NOCACHE)
        Protect |= MM_UNCACHED;

    return Protect;
}

ULONG
ConvertProtectAndCaching (
    _In_ ULONG Win32Protect,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    /* Set caching type */
    Win32Protect &= ~(PAGE_NOCACHE | PAGE_WRITECOMBINE);
    if ((CachingType == MmNonCached) || (CachingType == MmNonCachedUnordered))
        Win32Protect |= PAGE_NOCACHE;
    else if (CachingType == MmWriteCombined)
        Win32Protect |= PAGE_WRITECOMBINE;

    return ConvertProtect(Win32Protect);
}

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

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
AllocatePagesForMapping (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _Out_ PPFN_LIST PageList,
    _Out_opt_ PPFN_LIST LargePageList,
    _In_ BOOLEAN ChargeForPages,
    _In_ ULONG Protect,
    _Out_ PULONG_PTR PagesCharged)
{
    ULONG_PTR MaxPageTables, NumberOfPages, CommitCharge, PageAllocation;
    NTSTATUS Status;

    NT_ASSERT(EndingVpn >= StartingVpn);

    /* Check if we allocate for a large page mapping */
    if (Protect & MM_LARGEPAGE)
    {
        NT_ASSERT(LargePageList != NULL);
        NT_ASSERT(Protect & MM_NONPAGED);
        // assert alignment
        UNIMPLEMENTED;
    }

    /* Calculate the maximum number of page tables and pages */
    MaxPageTables = CalculateMaximumNumberOfPageTables(StartingVpn, EndingVpn);
    NumberOfPages = EndingVpn - StartingVpn + 1;

    /* Calculate for how many pages we charge */
    CommitCharge = MaxPageTables;
    if (ChargeForPages)
    {
        CommitCharge += NumberOfPages;
    }

    /* Charge the system commit */
    Status = ChargeSystemCommit(CommitCharge);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Calculate how many pages we need to allocate */
    PageAllocation = MaxPageTables;
    if (Protect & MM_MAPPED)
    {
        PageAllocation += NumberOfPages;
    }

    /* Allocate the pages */
    Status = g_PfnDatabase.AllocateMultiplePages(PageList, PageAllocation, TRUE);
    if (!NT_SUCCESS(Status))
    {
        UnchargeSystemCommit(CommitCharge);
        return Status;
    }

    *PagesCharged = CommitCharge;
    return STATUS_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
#include "Mapping_old.cpp"



ULONG_PTR
ReserveMappingPtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _In_ PPFN_LIST PageList,
    _In_ ULONG Protect)
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
    PFN_NUMBER PfnOfPd, PfnOfPt;
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
                UNIMPLEMENTED;
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
                    /// FIXME: handle paged out page tables
                    NT_ASSERT(CurrentPde->IsValid());

                    /* Go to the next PDE */
                    CurrentPde++;
                } while (CurrentPde < MarginPde);

                /* Increment entry count in the page directory and count pages */
                g_PfnDatabase.ModifyEntryCount(PfnOfPd, NumberOfNewPdes);
                ActualCharge += NumberOfNewPdes;
            }

            /* Continue with PDE at the next PPE boundary */
            CurrentPde = MarginPde;
            CurrentPte = PdeToPte(CurrentPde);

#if (MI_PAGING_LEVELS >= 3)
            /* Go to the next PPE */
            CurrentPpe++;
        } while (CurrentPpe < MarginPpe);

        /* Increment entry count in the parent directory and count pages */
        g_PfnDatabase.ModifyEntryCount(PfnOfPdpt, NumberOfNewPpes);
        ActualCharge += NumberOfNewPpes;
#endif /* MI_PAGING_LEVELS >= 3 */

#if (MI_PAGING_LEVELS >= 4)
        /* Go to the next PXE */
        CurrentPxe++;
    } while (CurrentPxe < EndPxe);

    /* Increment entry count in the parent page table */
    g_PfnDatabase.ModifyEntryCount(PfnOfPml4, NumberOfNewPxes);
#endif /* MI_PAGING_LEVELS >= 4 */

    return ActualCharge;
}

NTSTATUS
MapVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    UNIMPLEMENTED;
    return 0;
}

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

    /* For now only kernel mode addresses! */ /// might need usermode as well
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

    /* Start with the first PFN */
    PageFrameNumber = BasePageFrameNumber;

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

    /* Release the kernel working set lock */
    g_KernelAddressSpace.ReleaseWorkingSetLock();

    /* Return the pages, we did not use */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);
    UnchargeSystemCommit(PagesCharged - PagesUsed);

    return STATUS_SUCCESS;
}

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

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
MapPrototypePtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PPTE Prototypes)
{
    ULONG_PTR EndingVpn, PagesCharged, PagesUsed;
    PADDRESS_SPACE AddressSpace;
    PFN_NUMBER PfnOfPt;
    ULONG NumberOfNewPtes;
    PFN_LIST PageList;
    //PTE TemplatePte;
    PPTE CurrentPte;
    PPDE CurrentPde;
    NTSTATUS Status;

    NT_ASSERT((Protect & (MM_LARGEPAGE)) == 0);
    NT_ASSERT((Protect & MM_PROTECTION_MASK) != MM_NOACCESS);

    if (Protect == -1) __debugbreak(); /// not yet handled

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
    PagesUsed = ReserveMappingPtes(StartingVpn, EndingVpn, &PageList, Protect);

    /* Prepare a template PTE */
    //TemplatePte.MakePrototypePte(Prototypes, Protect);

    /* Loop all reserved PTEs */
    CurrentPte = VpnToPte(StartingVpn);
    CurrentPde = VpnToPde(StartingVpn);
    NumberOfNewPtes = 0;
    do
    {
        /* Make sure the PTE is empty */
        NT_ASSERT(CurrentPte->IsEmpty());
        //TemplatePte.SetPageFrameNumber(*PfnArray);
        CurrentPte->MakePrototypePte(Prototypes, Protect);
        NumberOfNewPtes++;

        /* Next PTE and next prototype */
        CurrentPte++;
        Prototypes++;
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

    /* Release the working set lock */
    AddressSpace->ReleaseWorkingSetLock();

    /* Return the pages, we did not use */
    g_PfnDatabase.ReleaseMultiplePages(&PageList);
    UnchargeSystemCommit(PagesCharged - PagesUsed);

    return STATUS_SUCCESS;
}


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

            *(ULONG64*)CurrentPte = 0; /// FIXME
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
                /// FIXME: unmap the üage table
                __debugbreak();
            }

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


/// ****************************************************************************


extern "C" {

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
    BaseAddress = ReserveKernelMemory(NumberOfBytes);
    if (BaseAddress == NULL)
    {
        return NULL;
    }

    /* Map no-access PTEs */
    Status = CreateMapping(AddressToVpn(BaseAddress),
                           BYTES_TO_PAGES(NumberOfBytes),
                           MM_NOACCESS | MM_GLOBAL | MM_NONPAGED,
                           NULL,
                           NULL);
    if (!NT_SUCCESS(Status))
    {
        ReleaseKernelMemory(BaseAddress);
        return NULL;
    }

    return BaseAddress;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeMappingAddress (
    _In_ PVOID BaseAddress,
    _In_ ULONG Tag)
{
    __debugbreak();
    //DeleteReservedMapping(BaseAddress);
    ReleaseKernelMemory(BaseAddress);
}

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

    /* Reserve virtual memory range */
    NumberOfPages = (ULONG_PTR)BYTES_TO_PAGES(NumberOfBytes);
    BaseAddress = ReserveKernelMemory(NumberOfPages * PAGE_SIZE);
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
    ReleaseKernelMemory(ALIGN_DOWN_POINTER_BY(BaseAddress, PAGE_SIZE));
}

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

_Post_writable_byte_size_(MemoryDescriptorList->ByteCount)
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL) _Post_notnull_)
_At_(MemoryDescriptorList->MappedSystemVa, _Post_writable_byte_size_(MemoryDescriptorList->ByteCount))
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
    ASSERT(!(Mdl->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA));

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

_Post_writable_byte_size_(MemoryDescriptorList->ByteCount)
_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(MemoryDescriptorList->MappedSystemVa + MemoryDescriptorList->ByteOffset,
  _Post_writable_byte_size_(MemoryDescriptorList->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesWithReservedMapping (
    _In_ PVOID MappingAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDLX MemoryDescriptorList,
    _In_ __drv_strictTypeMatch(__drv_typeCond)
        MEMORY_CACHING_TYPE CacheType)
{
    // Find the VAD
    // Commit pages
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapReservedMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDLX Mdl)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapLockedPages (
    _In_ PVOID BaseAddress,
    _Inout_ PMDL Mdl)
{
    ULONG_PTR NumberOfPages;

    NumberOfPages = BYTES_TO_PAGES(Mdl->ByteCount);
    UnmapPages(AddressToVpn(BaseAddress), NumberOfPages, FALSE);

    Mdl->MdlFlags &= ~(MDL_PARTIAL_HAS_BEEN_MAPPED | MDL_MAPPED_TO_SYSTEM_VA);
}


VOID
NTAPI
MmMapMemoryDumpMdl (
    IN PMDL Mdl)
{
    UNIMPLEMENTED;
}

PHYSICAL_ADDRESS
NTAPI
MmGetPhysicalAddress(
    _In_ PVOID BaseAddress)
{
    PHYSICAL_ADDRESS PhysicalAddress;
    PPTE PtePointer;

    /* Get the PTE */
    PtePointer = AddressToPte(BaseAddress);

    /* Get the base physical address */
    PhysicalAddress.QuadPart = PtePointer->GetPageFrameNumber() * PAGE_SIZE;

    /* Add byte offset */
    PhysicalAddress.LowPart +=
        reinterpret_cast<ULONG_PTR>(BaseAddress) & (PAGE_SIZE - 1);

    return PhysicalAddress;
}

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

}; // extern "C"
}; // namespace Mm
