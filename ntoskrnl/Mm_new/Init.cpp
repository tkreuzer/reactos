

#include "ntosbase.h"
#include "AddressSpace.hpp"
#include "PfnDatabase.hpp"
#include "SectionObject.hpp"
#include "VadTable.hpp"
#include "KernelVad.hpp"
#include "CommitCharge.hpp"
#include "amd64/PageTables.hpp"
#include "amd64/MachineDependent.hpp"
#include <arc/arc.h>
#include <limits.h>

// This is to shut up linker warnings about .CRT sections
#pragma comment(linker, "/merge:.CRT=.rdata")

extern "C" PFN_NUMBER MmLowestPhysicalPage;
extern "C" PFN_NUMBER MmHighestPhysicalPage;
extern "C" PFN_NUMBER MmAvailablePages;
extern "C" PFN_NUMBER MmNumberOfPhysicalPages;

PFN_NUMBER MmBadPagesDetected;

namespace Mm {

VOID
InitializePoolSupport (
    VOID);

VOID
InitializeMachineDependent (
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock);

ULONG RandomNumberSeed;
ULONG_PTR LowestSystemVpn;

PFN_NUMBER EarlyAllocPageBase;
PFN_NUMBER EarlyAllocPageCount;
PFN_NUMBER EarlyAllocLargePageBase;

KERNEL_VAD PageTableVad;
KERNEL_VAD HyperSpaceVad;
KERNEL_VAD LoaderMappingsVad;
KERNEL_VAD HalVaVad;

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
    _In_ PVOID StartAddress,
    _In_ PVOID EndAddress,
    _In_ ULONG Protect)
{
#if MI_PAGING_LEVELS >= 4
    for (PPXE PxePointer = AddressToPxe(StartAddress);
         PxePointer <= AddressToPxe(EndAddress);
         PxePointer++)
    {
        if (!PxePointer->IsValid())
        {
            NT_ASSERT(PxePointer->IsEmpty());
            PxePointer->MakeValidPxe(EarlyAllocPage(), Protect);
            RtlFillMemoryUlonglong(PxeToPpe(PxePointer), PAGE_SIZE, 0);
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
            NT_ASSERT(PpePointer->IsEmpty());
            PpePointer->MakeValidPpe(EarlyAllocPage(), Protect);
            RtlFillMemoryUlonglong(PpeToPde(PpePointer), PAGE_SIZE, 0);
        }
    }
#endif
    for (PPDE PdePointer = AddressToPde(StartAddress);
         PdePointer <= AddressToPde(EndAddress);
         PdePointer++)
    {
        if (!PdePointer->IsValid())
        {
            NT_ASSERT(PdePointer->IsEmpty());
            if (Protect & MM_LARGEPAGE)
            {
                PdePointer->MakeValidLargePagePde(EarlyAllocLargePage(), Protect);
                RtlFillMemoryUlonglong(LargePagePdeToAddress(PdePointer), LARGE_PAGE_SIZE, 0);
            }
            else
            {
                PdePointer->MakeValidPde(EarlyAllocPage(), Protect);
                RtlFillMemoryUlonglong(PdeToPte(PdePointer), PAGE_SIZE, 0);
            }
        }
    }

    if ((Protect & MM_MAPPED) && !(Protect & MM_LARGEPAGE))
    {
        for (PPTE PtePointer = AddressToPte(StartAddress);
             PtePointer <= AddressToPte(EndAddress);
             PtePointer++)
        {
            if (!PtePointer->IsValid())
            {
                PtePointer->MakeValidPte(EarlyAllocPage(), Protect);
                RtlZeroMemory(PteToAddress(PtePointer), PAGE_SIZE);
            }
        }
    }
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

    /* Initialize the physical page range */
    MmLowestPhysicalPage = SIZE_MAX;
    MmHighestPhysicalPage = 0;

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
    NTSTATUS Status;
    ULONG_PTR NumberOfPages;

    /* Initialize a random number seed from the interrupt time and TSC */
    RandomNumberSeed = static_cast<ULONG>(KeQueryInterruptTime() << 8);
    RandomNumberSeed ^= static_cast<ULONG>(__rdtsc());

    /* Set lowest system VPN */
    LowestSystemVpn = AddressToVpn(MmSystemRangeStart);

    /* Set and initialize the kernel address space */
    g_SystemProcessAddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
    g_SystemProcessAddressSpace->Initialize();

    /* Initialize the global kernel VAD table, so that we can reserve
       virtual memory. Required for the PFN database. */
    g_KernelVadTable.Initialize(TRUE);

    /* Reserve the address space for the page tables */
    PageTableVad.Initialize();
    NumberOfPages = AddressToVpn(PTE_TOP) - AddressToVpn(PTE_BASE) + 1;
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&PageTableVad,
                                                   AddressToVpn(PTE_BASE),
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Reserve the address space for hyper space (same size as page tables) */
    HyperSpaceVad.Initialize();
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&HyperSpaceVad,
                                                   AddressToVpn(PTE_TOP) + 1,
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Reserve the address space for the loader mappings */
    LoaderMappingsVad.Initialize();
    NumberOfPages = LoaderBlock->Extension->LoaderPagesSpanned;
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&LoaderMappingsVad,
                                                   AddressToVpn(KSEG0_BASE),
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Reserve the address space for HAL */
    HalVaVad.Initialize();
    NumberOfPages = AddressToVpn(MM_HAL_VA_END) - AddressToVpn(MM_HAL_VA_START);
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&HalVaVad,
                                                   AddressToVpn(MM_HAL_VA_START),
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Gather some basic information from the loader block's memory descriptors */
    ScanMemoryDescriptors(LoaderBlock);

    /* Initialize machine dependent parts */
    InitializeMachineDependent(LoaderBlock);

    /* Initialize the PFN database */
    g_PfnDatabase.Initialize(LoaderBlock);

    /* Allocate the global zero page */
    GlobalZeroPfn = g_PfnDatabase.AllocatePage(TRUE);

    /* Initialize the system commit limit */
    InitializeSystemCommitLimit();

    /* Initialize the pools */
    InitializePoolSupport();

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
    return TRUE;
}

BOOLEAN
NTAPI
INIT_FUNCTION
MmArmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    g_MemoryManager.Inititalize(LoaderBlock);

    return TRUE;
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
