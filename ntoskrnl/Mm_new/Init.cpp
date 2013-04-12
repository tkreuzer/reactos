

#include "ntosbase.h"
#include "AddressSpace.hpp"
#include "PfnDatabase.hpp"
#include "SectionObject.hpp"
#include "VadTable.hpp"
#include "amd64/PageTables.hpp"
#include <arc/arc.h>

extern "C" PFN_NUMBER MmLowestPhysicalPage;
extern "C" PFN_NUMBER MmHighestPhysicalPage;
extern "C" PFN_NUMBER MmAvailablePages;
extern "C" PFN_NUMBER MmNumberOfPhysicalPages;

PFN_NUMBER MmBadPagesDetected;

namespace Mm {

ULONG RandomNumberSeed;

PFN_NUMBER EarlyAllocPageBase;
PFN_NUMBER EarlyAllocPageCount;
PFN_NUMBER EarlyAllocLargePageBase;

/// \todo HACK!!!
PADDRESS_SPACE g_KernelAddressSpace;
VAD_TABLE g_KernelVadTable;

ULONG NumberOfPhysicalMemoryRuns;
ULONG NumberOfMemoryDescriptors;
PMEMORY_ALLOCATION_DESCRIPTOR LargestFreeDescriptor;

/// \todo FIXME: duplicated in PfnDatabase.cpp
inline
BOOLEAN
IsFreeMemory (
    TYPE_OF_MEMORY MemoryType)
{
    return ((MemoryType == LoaderFree) ||
            (MemoryType == LoaderLoadedProgram) ||
            (MemoryType == LoaderFirmwareTemporary) ||
            (MemoryType == LoaderOsloaderStack));
}

/*! \name EarlyAllocPage
 *
 *  \brief Allocates a single page of physical memory, before the PFN
 *      database is initialized.
 *
 *  \remarks This function can only used after EarlyAllocPageCount and
 *      EarlyAllocPageBase are set and can not be used after the PFN database
 *      was created.
 */
PFN_NUMBER
INIT_FUNCTION
EarlyAllocPage (
    VOID)
{
    /* Sanity check, that there is a page available */
    if (EarlyAllocPageCount < 1)
    {
        KeBugCheck(INSTALL_MORE_MEMORY);
    }

    /* Decrement number of pages and return next page */
    MmAvailablePages--;
    EarlyAllocPageCount--;
    return EarlyAllocPageBase++;
}

/*! \name EarlyAllocLargePage
 *
 *  \brief Allocates a single large page of physical memory, before the PFN
 *      database is initialized.
 *
 *  \remarks This function can only used after EarlyAllocPageCount and
 *      EarlyAllocPageBase are set and can not be used after the PFN database
 *      was created.
 */
PFN_NUMBER
INIT_FUNCTION
EarlyAllocLargePage (
    VOID)
{
    /* Sanity check, that there is a page available */
    if (EarlyAllocPageCount < LARGE_PAGE_SIZE / PAGE_SIZE)
    {
        KeBugCheck(INSTALL_MORE_MEMORY);
    }

    /* Decrement number of pages and return next page */
    MmAvailablePages -= LARGE_PAGE_SIZE / PAGE_SIZE;
    EarlyAllocPageCount -= LARGE_PAGE_SIZE / PAGE_SIZE;
    EarlyAllocLargePageBase -= LARGE_PAGE_SIZE / PAGE_SIZE;
    return EarlyAllocLargePageBase;
}

VOID
INIT_FUNCTION
EarlyMapPages (
    PVOID StartAddress,
    PVOID EndAddress)
{
#if MI_PAGING_LEVELS >= 4
    for (PPXE PxePointer = AddressToPxe(StartAddress);
         PxePointer <= AddressToPxe(EndAddress);
         PxePointer++)
    {
        if (!PxePointer->IsValid())
        {
            //PxePointer->WriteValidKernelPxe(EarlyAllocPage());
            *PxePointer = PXE::CreateValidKernelPxe(EarlyAllocPage());
            RtlFillMemoryUlonglong(PteToAddress(PxePointer), PAGE_SIZE, 0);
        }
    }
#endif
#if MI_PAGING_LEVELS >= 3
    for (PPPE PpePointer = AddressToPpe(StartAddress);
         PpePointer <= AddressToPpe(EndAddress);
         PpePointer++)
    {
        if (!PpePointer->IsValid())
        {
            *PpePointer = PPE::CreateValidKernelPpe(EarlyAllocPage());
            RtlFillMemoryUlonglong(PteToAddress(PpePointer), PAGE_SIZE, 0);
        }
    }
#endif
    for (PPDE PdePointer = AddressToPde(StartAddress);
         PdePointer <= AddressToPde(EndAddress);
         PdePointer++)
    {
        if (!PdePointer->IsValid())
        {
#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
            *PdePointer = PDE::CreateValidLargePageKernelPde(EarlyAllocLargePage());
            RtlFillMemoryUlonglong(PteToAddress(PdePointer), LARGE_PAGE_SIZE, 0);
#else
            *PdePointer = PDE::CreateValidKernelPde(EarlyAllocPage());
            RtlFillMemoryUlonglong(PteToAddress(PdePointer), PAGE_SIZE, 0);
#endif
        }
    }

#ifndef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
    for (PPTE PtePointer = AddressToPte(StartAddress);
         PtePointer <= AddressToPte(EndAddress);
         PtePointer++)
    {
        if (!PtePointer->IsValid())
        {
            *PtePointer = PTE::CreateValidKernelPte(EarlyAllocPage());
            RtlZeroMemory(PteToAddress(PtePointer), PAGE_SIZE);
        }
    }
#endif
}

/*! \name ScanMemoryDescriptors
 *
 * \brief Collects information from the loader blocks's memory descriptors
 *
 * \param [in] LoaderBlock
 *       Pointer to the loader block.
 *
 * \remarks This function sets up MmLowestPhysicalPage, MmHighestPhysicalPage,
 *      MmNumberOfPhysicalPages, MmBadPagesDetected, MmAvailablePages,
 *      NumberOfPhysicalMemoryRuns, NumberOfMemoryDescriptors and
 *      LargestFreeDescriptor
 */
static
VOID
INIT_FUNCTION
ScanMemoryDescriptors (
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PLIST_ENTRY ListEntry;
    PMEMORY_ALLOCATION_DESCRIPTOR Descriptor;
    PFN_NUMBER LastPage, FreePages;

    /* Set LastPage so that the first descriptor will count as a new run */
    LastPage = -2;
    FreePages = 0;

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
        NumberOfMemoryDescriptors++;

        /* Skip invisible memory */
        //if (MiIsMemoryTypeInvisible(Descriptor->MemoryType)) continue;

        /* Check if this is a new run */
        if (Descriptor->BasePage != LastPage + 1)
        {
            NumberOfPhysicalMemoryRuns++;
        }

        /* Get the last page and update lowest and highest page */
        LastPage = Descriptor->BasePage + Descriptor->PageCount - 1;
        MmHighestPhysicalPage = max(MmHighestPhysicalPage, LastPage);
        MmLowestPhysicalPage = min(MmLowestPhysicalPage, Descriptor->BasePage);

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
        if (IsFreeMemory(Descriptor->MemoryType))
        {
            /* Count it to free pages */
            MmAvailablePages += (ULONG)Descriptor->PageCount;

            /* Check if this is the largest memory descriptor */
            if (Descriptor->PageCount > FreePages)
            {
                /* Remember it */
                LargestFreeDescriptor = Descriptor;
                FreePages = Descriptor->PageCount;
            }
        }
    }

    /* Set base page and last page for early page allocations */
    EarlyAllocPageBase = LargestFreeDescriptor->BasePage;
    EarlyAllocPageCount = LargestFreeDescriptor->PageCount;
#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
    /* Allocate large pages at the upper range of the descriptor */
    EarlyAllocLargePageBase = EarlyAllocPageBase + EarlyAllocPageCount;
    EarlyAllocLargePageBase &= LARGE_PAGE_MASK;
#endif
}


class MEMORY_MANAGER
{
public:

    static
    VOID
    Inititalize (
        _In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock);

};

MEMORY_MANAGER g_MemoryManager;

VOID
INIT_FUNCTION
MEMORY_MANAGER::Inititalize (
    _In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    /* Initialize a random number seed from the TSC */
    RandomNumberSeed = static_cast<ULONG>(KeQueryInterruptTime());
    RandomNumberSeed ^= static_cast<ULONG>(__rdtsc());

    /* Gather some basic information from the loader blocks memory descriptors */
    ScanMemoryDescriptors(LoaderBlock);

    /* Initialize the global kernel VAD table, so that we can reserve
       virtual memory. Required for the PFN database. */
    g_KernelVadTable.Initialize(TRUE);

    /* Initialize the PFN database */
    g_PfnDatabase.Initialize(LoaderBlock);

    /* Set and initialize the kernel address space */
    g_KernelAddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
    g_KernelAddressSpace->Initialize();

    /* Initialize the section object class */
    SECTION_OBJECT::InitializeClass();
}


extern "C" {

BOOLEAN
NTAPI
INIT_FUNCTION
MmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
INIT_FUNCTION
MmArmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    DbgPrint("MmArmInitSystem()\n");

    g_MemoryManager.Inititalize(LoaderBlock);

    return FALSE;
}

VOID
NTAPI
INIT_FUNCTION
MmFreeLoaderBlock (
    struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
    // Find the VAD (which is the static loader allocation VAD)
    // decommit the page (will release the PFN)
}


}; // extern "C"
}; // namespace Mm
