
#include <ntoskrnl.h>
#include "Mm_internal.h"

ULONG MiNumberDescriptors;
ULONG MiNumberOfFreePages;
PMEMORY_ALLOCATION_DESCRIPTOR MiLargestDescriptor;
PFN_NUMBER MiEarlyAllocBasePage;
PFN_NUMBER MiEarlyAllocPageCount;


/*! \name MiScanMemoryDescriptors
 *
 * \brief Collects information from the loader blocks's memory descriptor
 *
 * \param [in] LoaderBlock
 *       Pointer to the loader block.
 *
 * \remarks This function sets up MmLowestPhysicalPage, MmHighestPhysicalPage,
 *      MmNumberOfPhysicalPages, MmBadPagesDetected, MiNumberDescriptors,
 *      MiEarlyAllocBasePage and MiEarlyAllocPageCount
 */
VOID
INITAPI
MiScanMemoryDescriptors(IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PLIST_ENTRY ListEntry;
    PMEMORY_ALLOCATION_DESCRIPTOR Descriptor;
    PFN_NUMBER PageFrameNumber, FreePages = 0;

    /* Loop the memory descriptors */
    for (ListEntry = LoaderBlock->MemoryDescriptorListHead.Flink;
         ListEntry != &LoaderBlock->MemoryDescriptorListHead;
         ListEntry = ListEntry->Flink)
    {
        /* Get the descriptor */
        Descriptor = CONTAINING_RECORD(ListEntry,
                                       MEMORY_ALLOCATION_DESCRIPTOR,
                                       ListEntry);
        TRACE("MD Type: %lx Base: %lx Count: %lx\n",
            Descriptor->MemoryType, Descriptor->BasePage, Descriptor->PageCount);

        /* Count this descriptor */
        MiNumberDescriptors++;

        /* Skip invisible memory */
        if (MiIsMemoryTypeInvisible(Descriptor->MemoryType)) continue;

        /* Check if this is bad memory */
        if (Descriptor->MemoryType == LoaderBad)
        {
            /* Count this to the number of bad pages */
            MmBadPagesDetected += (PFN_COUNT)Descriptor->PageCount;
        }
        else
        {
            /* Count this in the total of pages */
            MmNumberOfPhysicalPages += (PFN_COUNT)Descriptor->PageCount;
        }

        /* Check if the memory is free */
        if (MiIsMemoryTypeFree(Descriptor->MemoryType))
        {
            /* Count it to free pages */
            MiNumberOfFreePages += (ULONG)Descriptor->PageCount;

            /* Check if this is the largest memory descriptor */
            if (Descriptor->PageCount > FreePages)
            {
                /* Remember it */
                MiLargestDescriptor = Descriptor;
                FreePages = Descriptor->PageCount;
            }
        }

        /* Check if this is the lowest page so far */
        if (Descriptor->BasePage < MmLowestPhysicalPage)
        {
            /* Update the lowest page */
            MmLowestPhysicalPage = Descriptor->BasePage;
        }

        /* Check if this is the highest page so far */
        PageFrameNumber = Descriptor->BasePage + Descriptor->PageCount - 1;
        if (PageFrameNumber > MmHighestPhysicalPage)
        {
            /* Update the highest page */
            MmHighestPhysicalPage = PageFrameNumber;
        }
    }

    /* Set base page and last page for early page allocations */
    MiEarlyAllocBasePage = MiLargestDescriptor->BasePage;
    MiEarlyAllocPageCount = MiLargestDescriptor->PageCount;
}


/*! \name MiEarlyAllocPage
 *
 *  \brief Allocates a single page of pyhsical memory, before the pfn
 *      database is initialized.
 *
 *  \remarks This function can only used after MiScanMemoryDescriptors and can
 *      not be used after the pfn database is created.
 */
PFN_NUMBER
INITAPI
MiEarlyAllocPage(VOID)
{
    /* Sanity check, that there is a page available */
    if (MiEarlyAllocPageCount < 1)
    {
        KeBugCheck(0);//INSTALL_MORE_MEMORY);
    }

    /* Decrement number of pages and return next page */
    MiEarlyAllocPageCount--;
    return MiEarlyAllocBasePage++;
}

VOID
INITAPI
MiEarlyMapPXEs(
    PVOID StartAddress,
    PVOID EndAddress)
{
    PMXPTE PointerPxe;
    MXPTE TemplatePxe = MxValidKernelPxe;

    /* Loop the PTEs */
    for (PointerPxe = MxAddressToPxe(StartAddress);
         PointerPxe <= MxAddressToPxe(EndAddress);
         PointerPxe++)
    {
        /* Skip it, if it is already mapped */
        if (PointerPxe->Hard.Valid) continue;

        /* Allocate a page and map it */
        TemplatePxe.Hard.PageFrameNumber = MiEarlyAllocPage();
        *PointerPxe = TemplatePxe;

        /* Zero out the page */
        RtlZeroMemory(MxPteToAddress(PointerPxe), PAGE_SIZE);
    }
}

VOID
INITAPI
MiEarlyMapPPEs(
    PVOID StartAddress,
    PVOID EndAddress)
{
    PMXPTE PointerPpe;
    MXPTE TemplatePpe = MxValidKernelPpe;

    /* Loop the PTEs */
    for (PointerPpe = MxAddressToPpe(StartAddress);
         PointerPpe <= MxAddressToPpe(EndAddress);
         PointerPpe++)
    {
        /* Skip it, if it is already mapped */
        if (PointerPpe->Hard.Valid) continue;

        /* Allocate a page and map it */
        TemplatePpe.Hard.PageFrameNumber = MiEarlyAllocPage();
        *PointerPpe = TemplatePpe;

        /* Zero out the page */
        RtlZeroMemory(MxPteToAddress(PointerPpe), PAGE_SIZE);
    }
}

VOID
INITAPI
MiEarlyMapPDEs(
    PVOID StartAddress,
    PVOID EndAddress)
{
    PMXPTE PointerPde;
    MXPTE TemplatePde = MxValidKernelPde;

    /* Loop the PTEs */
    for (PointerPde = MxAddressToPde(StartAddress);
         PointerPde <= MxAddressToPde(EndAddress);
         PointerPde++)
    {
        /* Skip it, if it is already mapped */
        if (PointerPde->Hard.Valid) continue;

        /* Allocate a page and map it */
        TemplatePde.Hard.PageFrameNumber = MiEarlyAllocPage();
        *PointerPde = TemplatePde;

        /* Zero out the page */
        RtlZeroMemory(MxPteToAddress(PointerPde), PAGE_SIZE);
    }
}

VOID
INITAPI
MiEarlyMapPTEs(
    PVOID StartAddress,
    PVOID EndAddress)
{
    PMXPTE PointerPte;
    MXPTE TemplatePte = MxValidKernelPte;

    /* Loop the PTEs */
    for (PointerPte = MxAddressToPte(StartAddress);
         PointerPte <= MxAddressToPte(EndAddress);
         PointerPte++)
    {
        /* Skip it, if it is already mapped */
        if (PointerPte->Hard.Valid) continue;

        /* Allocate a page and map it */
        TemplatePte.Hard.PageFrameNumber = MiEarlyAllocPage();
        *PointerPte = TemplatePte;

        /* Zero out the page */
        RtlZeroMemory(MxPteToAddress(PointerPte), PAGE_SIZE);
    }
}

VOID
INITAPI
MiInitializePageTables()
{
    PVOID PageDirectoryBase, PageDirectoryEnd;

    /* Get the user mode range of the top level page directory */
#if (MI_PAGING_LEVELS == 4)
    PageDirectoryBase = MxAddressToPxe(0);
    PageDirectoryEnd = MxAddressToPxe(MmHighestUserAddress);
#elif (MI_PAGING_LEVELS == 3)
    PageDirectoryBase = MxAddressToPpe(0);
    PageDirectoryEnd = MxAddressToPpe(MmHighestUserAddress);
#else
    PageDirectoryBase = MxAddressToPde(0);
    PageDirectoryEnd = MxAddressToPde(MmHighestUserAddress);
#endif

    /* Zero out the page directory */
    RtlZeroMemory(PageDirectoryBase,
                  (PCHAR)PageDirectoryEnd - (PCHAR)PageDirectoryBase);
    __writecr3(__readcr3());

#if (MI_PAGING_LEVELS == 4)
    MiEarlyMapPXEs(MmSystemRangeStart, MmSystemRangeEnd);
#elif (MI_PAGING_LEVELS == 3)
    MiEarlyMapPPEs(MmSystemRangeStart, MmSystemRangeEnd);
#else
    // FIXME: double mapped PDEs
    ASSERT(FALSE);
#endif

}


VOID
INITAPI
MmInitialize(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    /* Collect some information from the loader block */
    MiScanMemoryDescriptors(LoaderBlock);

    /* Do the architecture specific initialization */
    MxInitializeArchitectureSpecific(LoaderBlock);

    /* Setup the core page tables */
    MiInitializePageTables();

    /* Build the PFN database */
    MiBuildPfnDatabase(LoaderBlock);

}

