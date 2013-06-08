

/*

Concurrency between interlocked page removal and contiguous page allocation:
- Contiguous allocator
    - Lock global contiguous memory spinlock
    - trigger an IPI for all CPUs
        - All CPUs wait, except this one
        - This CPU performs the allocation (non-interlocked)
        -


*/

/// \todo Use RTL_BITMAP_EX

#include "PfnDatabase.hpp"
#include "VadTable.hpp"
#include "KernelVad.hpp"
#include _ARCH_RELATIVE_(PageTables.hpp)
#include _ARCH_RELATIVE_(MachineDependent.hpp)
#include <arc/arc.h>
#include <limits.h>
#include <ndk/ketypes.h>
#include <ndk/pstypes.h>


extern "C" PFN_NUMBER MmLowestPhysicalPage;
extern "C" PFN_NUMBER MmHighestPhysicalPage;
extern "C" PFN_NUMBER MmNumberOfPhysicalPages;
extern "C" PFN_NUMBER MmAvailablePages;
extern "C" PVOID MmPfnDatabase;
extern "C" UCHAR KeNumberNodes;

PFN_NUMBER MmBadPagesDetected;

namespace Mm {

PFN_DATABASE g_PfnDatabase;
ULONG PFN_DATABASE::m_CacheColorBits;
ULONG PFN_DATABASE::m_CacheColorMask;
PPFN_LIST PFN_DATABASE::m_FreeLists;
PPFN_LIST PFN_DATABASE::m_ZeroedLists;
PPHYSICAL_MEMORY_DESCRIPTOR PFN_DATABASE::m_PhysicalMemoryDescriptor;
PRTL_BITMAP_EX PFN_DATABASE::m_PhysicalMemoryBitmap;
PFN_ENTRY* PFN_DATABASE::m_PfnArray;
PULONG_PTR PFN_DATABASE::m_PhysicalBitmapBuffer;
static KERNEL_VAD g_PfnDatabaseVad;
static KERNEL_VAD g_MappingPtesVad;
static KEVENT PagesAvailableEvent;
#define NUMBER_OF_MAPPING_PTES 128
PPTE ZeroingPtes;
PPTE DebugPte;
ULONG NodeShift;
ULONG NodeMask;

SIZE_T MmSizeOfPfnDatabase;

PFN_NUMBER EarlyAllocPageBase;
PFN_NUMBER EarlyAllocPageCount;
#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
PFN_NUMBER EarlyAllocLargePageBase;
#endif // MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
ULONG NumberOfPhysicalMemoryRuns;
ULONG NumberOfMemoryDescriptors;
PMEMORY_ALLOCATION_DESCRIPTOR LargestFreeDescriptor;


static const PFN_CACHE_ATTRIBUTE CachingTypeToCacheAttribute[] =
{
    PfnNonCached, PfnCached, PfnWriteCombined, PfnCached, PfnNonCached, PfnCached
};


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

#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
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
#endif // MI_USE_LARGE_PAGES_FOR_PFN_DATABASE

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
            RtlFillMemoryUlongPtr(PxeToPpe(PxePointer), PAGE_SIZE, 0);
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
            RtlFillMemoryUlongPtr(PpeToPde(PpePointer), PAGE_SIZE, 0);
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
#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
            if (Protect & MM_LARGEPAGE)
            {
                PdePointer->MakeValidLargePagePde(EarlyAllocLargePage(), Protect);
                RtlFillMemoryUlongPtr(LargePagePdeToAddress(PdePointer), LARGE_PAGE_SIZE, 0);
            }
            else
#endif // MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
            {
                PdePointer->MakeValidPde(EarlyAllocPage(), Protect);
                RtlFillMemoryUlongPtr(PdeToPte(PdePointer), PAGE_SIZE, 0);
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
            Descriptor->MemoryType, (ULONG)Descriptor->BasePage, (ULONG)Descriptor->PageCount);

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

static
VOID
INIT_FUNCTION
CalculatePageColors (
    VOID)
{
    ULONG PageColors, CacheSize, CacheAssociativity;

    /* Get the cache size */
    CacheSize = KeGetPcr()->SecondLevelCacheSize;
    if (CacheSize != 0)
    {
        /* Calculate the number of pages per way */
        CacheAssociativity = KeGetPcr()->SecondLevelCacheAssociativity;
        PageColors = (CacheSize / CacheAssociativity) / PAGE_SIZE;

        /* Check if this is a power of 2 */
        if (PageColors & (PageColors - 1))
        {
            __debugbreak();
            PageColors = 64;
        }
    }
    else
    {
        PageColors = 64;
    }

    KeGetCurrentPrcb()->SecondaryColorMask = (PageColors - 1);

    /* Make sure the number of nodes is a power of 2 */
    NT_ASSERT((KeNumberNodes != 0) && (KeNumberNodes & (KeNumberNodes - 1)) == 0);

    /* Get the node shift and calculate the node mask */
    NT_VERIFY(BitScanReverse(&NodeShift, PageColors));
    NodeMask = (KeNumberNodes - 1) << NodeShift;
}

inline
ULONG
GetNextPageColor (
    _In_ ULONG PageColor)
{
    ULONG CacheColorMask = KeGetCurrentPrcb()->SecondaryColorMask;

    /* Return the next cache color */
    return ((PageColor + 1) & CacheColorMask) | (PageColor & NodeMask);
}

inline
ULONG
GetNextPageColorCycleNodes (
    _Inout_ ULONG PageColor,
    _In_ ULONG OriginalColor)
{
    ULONG CacheColorMask = KeGetCurrentPrcb()->SecondaryColorMask;
    ULONG NextColor;

    /* First get the next cache color */
    NextColor = (PageColor + 1) & CacheColorMask;

    /* Check if this matches the original cache color */
    if (NextColor == (OriginalColor & CacheColorMask))
    {
        /* Increment node color */
        PageColor += (CacheColorMask + 1);
    }

    /* Combine to full color */
    NextColor |= (PageColor & NodeMask);

    return NextColor;
}


VOID
INIT_FUNCTION
PFN_DATABASE::InitializePfnEntries (
    _In_ PFN_NUMBER BasePage,
    _In_ PFN_NUMBER PageCount,
    _In_ ULONG MemoryType) /// FIXME: better use PFN_STATE?
{
    PFN_ENTRY* PfnEntry;
    ULONG Color;

    /* Get the first PFN entry of this range. */
    PfnEntry = &m_PfnArray[BasePage];

    /* Check if the memory is free */
    if (IsFreeMemory((TYPE_OF_MEMORY)MemoryType))
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++, BasePage++)
        {
            /* Mark it as a free entry */
            PfnEntry->State = PfnFree;
            PfnEntry->ReferenceCount = 0;
            PfnEntry->Dirty = TRUE;

            /* Insert the page into the dirty list */
            Color = BasePage & KeGetCurrentPrcb()->SecondaryColorMask;
            PfnEntry->Flink = m_FreeLists[Color].m_ListHead;
            m_FreeLists[Color].m_ListHead = BasePage;
        }
    }
    else if (MemoryType == LoaderXIPRom)
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++, BasePage++)
        {
            /* Mark it as ROM */
            PfnEntry->State = PfnRom;
            PfnEntry->Dirty = TRUE;
        }
    }
    else if (MemoryType == LoaderBad)
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++, BasePage++)
        {
            /* Mark it as bad */
            PfnEntry->State = PfnBad;
            PfnEntry->Dirty = TRUE;
        }
    }
    else if (MemoryType == LoaderLargePageFiller)
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++)
        {
            /// \todo Maybe we need to use a special type
            /* Mark it as contiguous memory (large page) */
            PfnEntry->State = PfnContiguous;
            PfnEntry->Dirty = TRUE;
        }
    }
    else
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++)
        {
            /* Mark it as a reserved PFN */
            PfnEntry->State = PfnKernelReserved;
            PfnEntry->Dirty = TRUE;
        }
    }
}

VOID
INIT_FUNCTION
PFN_DATABASE::InitializePageTablePfn (
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ PFN_NUMBER ParendDirectoryPfn,
    _In_ PVOID MappedAddress,
    _In_ ULONG PageTableLevel)
{
    PPFN_ENTRY PfnEntry;

    /* Everything that is mapped at the moment should be in the database */
    if (PageFrameNumber > MmHighestPhysicalPage)
    {
        return;
    }

    /* Get the PFN entry for this page */
    PfnEntry = &m_PfnArray[PageFrameNumber];

    /* This must not be free memory! */
    NT_ASSERT(PfnEntry->State != PfnFree);

    /* Is this a page table? */
    if (PageTableLevel > 0)
    {
        /// \todo Check if we can set this based on loader block descriptors
        PfnEntry->State = PfnPageTable;
        PfnEntry->PageTable.UsedPteCount = 0;
        PfnEntry->PageTable.ValidPteCount = 0;
    }

    /* Setup the PFN entry */
    PfnEntry->CacheAttribute = PfnCached;

    PfnEntry->PteAddress = AddressToPte(MappedAddress);

    /* Check if this is a child page table */
    if (PageTableLevel < MI_PAGING_LEVELS)
    {
        /* Increment the count of used and valid entries in the parent directory */
        PfnEntry = &m_PfnArray[ParendDirectoryPfn];
        NT_ASSERT(PfnEntry->State == PfnPageTable);
        PfnEntry->PageTable.UsedPteCount++;
        PfnEntry->PageTable.ValidPteCount++;
    }
}


VOID
INIT_FUNCTION
PFN_DATABASE::InitializePfnEntriesFromPageTables (
    VOID)
{
    PVOID Address = NULL;
    PFN_NUMBER PfnForPxe, PfnForPpe, PfnForPde, PfnForPte;
    PPDE PdePointer;
    PPTE PtePointer;
    ULONG k, l;
#if (MI_PAGING_LEVELS >= 3)
    PPPE PpePointer;
    ULONG j;
#endif
#if (MI_PAGING_LEVELS == 4)
    PPXE PxePointer;
    PFN_NUMBER PfnForPml4;
    ULONG i;
#endif

    /* Setup the top level page directory */
#if (MI_PAGING_LEVELS == 4)
    PtePointer = AddressToPte((PVOID)PXE_BASE);
    PfnForPml4 = PtePointer->GetPageFrameNumber();
    InitializePageTablePfn(PfnForPml4, 0, (PVOID)PXE_BASE, 4);
#elif (MI_PAGING_LEVELS == 3)
    PtePointer = MiAddressToPte(PPE_BASE);
    PfnForPxe = PtePointer->GetPageFrameNumber();
#else
    PtePointer = AddressToPte((PVOID)PDE_BASE);
    PfnForPxe = 0;
    PfnForPpe = PtePointer->GetPageFrameNumber();
#endif

#if (MI_PAGING_LEVELS == 4)
    /* Loop all PXEs in the PML4 */
    PxePointer = AddressToPxe(Address);
    for (i = 0; i < PXE_PER_PAGE; ++i, ++PxePointer)
    {
        /* Skip invalid PXEs */
        if (!PxePointer->IsValid())
        {
            NT_ASSERT(PxePointer->IsEmpty());
            continue;
        }

        /* Get starting VA for this PXE */
        Address = PxeToAddress(PxePointer);

        /* Skip page-table PXE */
        if (IsPageTableAddress(Address))
        {
            continue;
        }

        /* Get the PFN for the PXE */
        PfnForPxe = PxePointer->GetPageFrameNumber();
#endif
#if (MI_PAGING_LEVELS >= 3)
        /* Get the PPE for the current address */
        PpePointer = AddressToPpe(Address);

        /* Initialize the PFN entry for the PDPT */
        InitializePageTablePfn(PfnForPxe, PfnForPml4, PpePointer, 3);

        /* Loop all PPEs in this PDPT */
        for (j = 0; j < PPE_PER_PAGE; ++j, ++PpePointer)
        {
            /* Skip invalid PPEs */
            if (!PpePointer->IsValid())
            {
                NT_ASSERT(PpePointer->IsEmpty());
                continue;
            }

            /* Get starting VA for this PPE */
            Address = PpeToAddress(PpePointer);

            /* Skip page-table PPEs */
            if (IsPageTableAddress(Address))
            {
                continue;
            }

            /* Get the PFN for the PPE */
            PfnForPpe = PpePointer->GetPageFrameNumber();
#endif
            /* Get the PDE for the current address */
            PdePointer = AddressToPde(Address);

            /* Initialize the PFN entry for the PD */
            InitializePageTablePfn(PfnForPpe, PfnForPxe, PdePointer, 2);

            /* Loop all PDEs in this PD */
            for (k = 0; k < PDE_PER_PAGE; ++k, ++PdePointer)
            {
                /* Skip invalid PDEs */
                if (!PdePointer->IsValid())
                {
                    NT_ASSERT(PdePointer->IsEmpty());
                    continue;
                }

                /* Get starting VA for this PDE and the first PTE */
                Address = PdeToAddress(PdePointer);
                PtePointer = AddressToPte(Address);

                /* Skip page-table PDEs */
                if (IsPageTableAddress(Address))
                {
                    continue;
                }

                /* Get the PFN for the PT or the large page */
                PfnForPde = PdePointer->GetPageFrameNumber();

                /* Check if this is a large page PDE */
                if (PdePointer->IsLargePage())
                {
                    for (l = 0; l < PTE_PER_PAGE; l++)
                    {
                        m_PfnArray[PfnForPde + l].CacheAttribute = PfnCached;
                        m_PfnArray[PfnForPde + l].PteAddress = PdePointer;
                    }

                    ModifyEntryCount(PfnForPpe, 1);
                    continue;
                }

                /* Initialize the PFN entry for the PT */
                InitializePageTablePfn(PfnForPde, PfnForPpe, PtePointer, 1);

                /* Loop all PTEs in this PT */
                for (l = 0; l < PTE_PER_PAGE; ++l, ++PtePointer)
                {
                    /* Skip invalid PTEs */
                    if (!PtePointer->IsValid())
                    {
                        NT_ASSERT(PtePointer->IsEmpty());
                        continue;
                    }

                    /* Get starting VA for this PTE */
                    Address = PteToAddress(PtePointer);

                    /* Skip page-table PTEs */
                    if (IsPageTableAddress(Address))
                    {
                        continue;
                    }

                    /* Handle the PFN */
                    PfnForPte = PtePointer->GetPageFrameNumber();
                    InitializePageTablePfn(PfnForPte, PfnForPde, Address, 0);
                }
            }
#if (MI_PAGING_LEVELS >= 3)
        }
#endif
#if (MI_PAGING_LEVELS == 4)
    }
#endif
}

VOID
INIT_FUNCTION
PFN_DATABASE::Initialize (
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    ULONG NumberPageColors, i;
    PFN_NUMBER BasePage, PageCount, NextPage;
    PLIST_ENTRY ListEntry;
    PMEMORY_ALLOCATION_DESCRIPTOR Descriptor;
    PULONG_PTR Buffer, BufferEnd = NULL;
    ULONG_PTR StartingVpn, EndingVpn;
    ULONG Protect = MM_READWRITE | MM_GLOBAL | MM_LARGEPAGE | MM_MAPPED;
    PVOID MappingBase;

    /* Initialize the page color mask */
    CalculatePageColors();
    NumberPageColors = KeGetCurrentPrcb()->SecondaryColorMask + 1;

    /* Reserve the whole area of mapping PTEs and HAL VA space */
    MappingBase = (PVOID)(MM_HAL_VA_START - (NUMBER_OF_MAPPING_PTES * PAGE_SIZE));
    EarlyMapPages(MappingBase, (PVOID)MM_HAL_VA_END, MM_INVALID);

    /* Reserve the virtual address range for mapping PTEs */
    StartingVpn = AddressToVpn(MappingBase);
    EndingVpn = AddressToVpn((PUCHAR)MM_HAL_VA_START - 1);
    g_MappingPtesVad.Initialize();
    g_KernelVadTable.InsertVadObjectAtVpn(&g_MappingPtesVad,
                                          StartingVpn,
                                          EndingVpn - StartingVpn + 1);

    /* Get the debug PTE and zeroing PTEs (one per CPU) */
    DebugPte = AddressToPte(MappingBase);
    ZeroingPtes = DebugPte + 1;

    /* Calculate location of the page lists and physical memory descriptor */
    m_PfnArray = (PFN_ENTRY*)PFN_DATABASE_ADDRESS;
    m_FreeLists = reinterpret_cast<PPFN_LIST>(&m_PfnArray[MmHighestPhysicalPage + 1]);
    m_ZeroedLists = &m_FreeLists[NumberPageColors];
    m_PhysicalMemoryDescriptor = reinterpret_cast<PPHYSICAL_MEMORY_DESCRIPTOR>(
            &m_ZeroedLists[NumberPageColors]);
    m_PhysicalMemoryBitmap = reinterpret_cast<PRTL_BITMAP_EX>(
            &m_PhysicalMemoryDescriptor->Run[NumberOfPhysicalMemoryRuns]);
    m_PhysicalBitmapBuffer = reinterpret_cast<PULONG_PTR>(
            m_PhysicalMemoryBitmap + 1);

    /* Map page lists, physical memory descriptor and physical memory bitmaps */
    EarlyMapPages(m_FreeLists, m_PhysicalBitmapBuffer, Protect);

    /* Initialize the free lists */
    for (i = 0; i < NumberPageColors; i++)
    {
        m_FreeLists[i].Initialize();
        m_ZeroedLists[i].Initialize();
    }

    /* Initialize the physical memory descriptor */
    m_PhysicalMemoryDescriptor->NumberOfRuns = NumberOfPhysicalMemoryRuns;
    m_PhysicalMemoryDescriptor->NumberOfPages = 0;
    m_PhysicalMemoryDescriptor->Run[0].BasePage = MmLowestPhysicalPage;
    m_PhysicalMemoryDescriptor->Run[0].PageCount = 0;

    /* Initialize the PFN bitmap with the maximum range */
    RtlInitializeBitMapEx(m_PhysicalMemoryBitmap,
                          m_PhysicalBitmapBuffer,
                          MmHighestPhysicalPage);

    /* Initialize NextPage, so we skip the first descriptor(s)
       when looking for new physical memory runs */
    NextPage = MmLowestPhysicalPage;
    i = 0;

    /* The second loop to map the database and fill in the data */
    for (ListEntry = LoaderBlock->MemoryDescriptorListHead.Flink;
         ListEntry != &LoaderBlock->MemoryDescriptorListHead;
         ListEntry = ListEntry->Flink)
    {
        /* Get the descriptor */
        Descriptor = CONTAINING_RECORD(ListEntry,
                                       MEMORY_ALLOCATION_DESCRIPTOR,
                                       ListEntry);

        /* Check if this is a new run */
        if (Descriptor->BasePage != NextPage)
        {
            /* Start next run */
            i++;

            /* Set base page for the new run and update the buffer */
            m_PhysicalMemoryDescriptor->Run[i].BasePage = Descriptor->BasePage;
            m_PhysicalMemoryDescriptor->Run[i].PageCount = 0;
            Buffer = BufferEnd;
        }

        /* Get the range for this descriptor */
        BasePage = Descriptor->BasePage;
        PageCount = Descriptor->PageCount;
        NextPage = BasePage + PageCount;

        /* Add this descriptor's pages to the current run */
        m_PhysicalMemoryDescriptor->Run[i].PageCount += PageCount;

        /* Map the pages for the database */
        EarlyMapPages(&m_PfnArray[BasePage],
                      (PUCHAR)(&m_PfnArray[BasePage + PageCount]) - 1,
                      Protect);

        /* Add this descriptor to the database */
        InitializePfnEntries(BasePage, PageCount, Descriptor->MemoryType);

        /* Calculate the range of the PFN bitmap buffer for this run */
        Buffer = &m_PhysicalBitmapBuffer[BasePage / 32];
        BufferEnd = &m_PhysicalBitmapBuffer[(NextPage - 1 + 31) / 32];

        /* Map the pages for the bitmap buffer */
        EarlyMapPages(Buffer, reinterpret_cast<PCHAR>(BufferEnd) - 1, Protect);

        /* Check if this is free memory */
        if (IsFreeMemory(Descriptor->MemoryType))
        {
            /* Set the bits for this run */
            RtlSetBitsEx(m_PhysicalMemoryBitmap, BasePage, PageCount);
        }

    }

    /* Make sure we counted correctly */
    NT_ASSERT(i == NumberOfPhysicalMemoryRuns - 1);

    /* Early allocations are not allowed any longer */
    EarlyAllocPageCount = 0;

    /* Reinitialize the PFN entries for the early allocations */
    InitializePfnEntries(LargestFreeDescriptor->BasePage,
                         EarlyAllocPageBase - LargestFreeDescriptor->BasePage,
                         LoaderMemoryData);

    /* Clear the free bits */
    RtlClearBitsEx(m_PhysicalMemoryBitmap,
                   LargestFreeDescriptor->BasePage,
                   EarlyAllocPageBase - LargestFreeDescriptor->BasePage);

#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
    /* Calculate the "next" page (exclusive) for large page allocations */
    NextPage = (LargestFreeDescriptor->BasePage +
                LargestFreeDescriptor->PageCount) & LARGE_PAGE_MASK;

    /* Reinitialize the PFN entries for the large page allocations */
    InitializePfnEntries(EarlyAllocLargePageBase,
                         NextPage - EarlyAllocLargePageBase,
                         LoaderLargePageFiller);

    /* Clear the free bits */
    RtlClearBitsEx(m_PhysicalMemoryBitmap,
                   EarlyAllocLargePageBase,
                   NextPage - EarlyAllocLargePageBase);
#endif

    /* Now parse the page tables */
    InitializePfnEntriesFromPageTables();

    /* Calculate the starting and ending VPN of the database */
    StartingVpn = AddressToVpn(m_PfnArray);
    EndingVpn = AddressToVpn(AddToPointer(BufferEnd, -1));

    /* Reserve the virtual address range for the PFN database */
    g_PfnDatabaseVad.Initialize();
    g_KernelVadTable.InsertVadObjectAtVpn(&g_PfnDatabaseVad,
                                          StartingVpn,
                                          EndingVpn - StartingVpn + 1);

    /* Set global variables */
    MmPfnDatabase = m_PfnArray;
    MmSizeOfPfnDatabase = (EndingVpn + 1 - StartingVpn) * PAGE_SIZE;

    /* Initialize the event for waiting on free pages */
    KeInitializeEvent(&PagesAvailableEvent, NotificationEvent, TRUE);
}


/* FUNCTIONS ******************************************************************/

VOID
ZeroPage (
    _In_ PFN_NUMBER PageFrameNumber)
{
    const ULONG Protect = MM_MAPPED | MM_GLOBAL | MM_EXECUTE_READWRITE;
    PPTE MappingPte;
    KIRQL OldIrql;

    /* Raise to DISPATCH_LEVEL to be sure we stay on this CPU */
    OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

    /* Get the PTE for zeroing */
    MappingPte = ZeroingPtes + KeGetCurrentPrcb()->Number;
    NT_ASSERT(MappingPte->IsValid() == FALSE);

    /* Map the PFN */
    MappingPte->MakeValidPte(PageFrameNumber, Protect);

    /* zero the page */
    RtlFillMemoryUlongPtr(PteToAddress(MappingPte), PAGE_SIZE, 0);

    /* Unmap the page */
    //MappingPte->Erase();
    *(ULONG64*)MappingPte = 0;
    __invlpg(PteToAddress(MappingPte));

    /* Restore IRQL */
    KeLowerIrql(OldIrql);
}

BOOLEAN
PFN_DATABASE::IsValidPageFrameNumber (
    _In_ PFN_NUMBER PageFrameNumber)
{
    PPFN_ENTRY PfnEntry;

    /* Get the PFN entry and check if is mapped */
    PfnEntry = &m_PfnArray[PageFrameNumber];
    if (!MmIsAddressValid(PfnEntry))
    {
        return FALSE;
    }

    /* Return, whether the PFN is valid */
    return (PfnEntry->State != PfnNotPresent);
}

PFN_CACHE_ATTRIBUTE
PFN_DATABASE::GetPfnCacheAttribute (
    _In_ PFN_NUMBER PageFrameNumber)
{
    return m_PfnArray[PageFrameNumber].CacheAttribute;
}

VOID
PFN_DATABASE::MakeActivePfn (
    _Inout_ PFN_NUMBER PageFrameNumber,
    _In_ PVOID PteAddress,
    _In_ ULONG Protect)
{
    PFN_ENTRY* PfnEntry = &m_PfnArray[PageFrameNumber];
    NT_ASSERT(PfnEntry->State == PfnFree);

    PfnEntry->State = PfnPrivate;
    PfnEntry->CacheAttribute = ProtectToCacheAttribute(Protect);
    PfnEntry->PteAddress = PteAddress;
}


VOID
PFN_DATABASE::MakeLargePagePfn (
    _Inout_ PFN_NUMBER PageFrameNumber,
    _In_ PVOID PteAddress,
    _In_ ULONG Protect)
{
    //UNIMPLEMENTED;
}

VOID
PFN_DATABASE::MakePageTablePfn (
    _Inout_ PFN_NUMBER PageFrameNumber,
    _In_ PVOID PteAddress,
    _In_ ULONG Protect)
{
    PFN_ENTRY* PfnEntry = &m_PfnArray[PageFrameNumber];
    NT_ASSERT(PfnEntry->State == PfnFree);

    PfnEntry->State = PfnPageTable;
    PfnEntry->CacheAttribute = ProtectToCacheAttribute(Protect);
    PfnEntry->PteAddress = PteAddress;
    PfnEntry->PageTable.UsedPteCount = 0;
    PfnEntry->PageTable.ValidPteCount = 0;
}

ULONG
PFN_DATABASE::ModifyEntryCount (
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ LONG Addend)
{
    PFN_ENTRY* PfnEntry = &m_PfnArray[PageFrameNumber];
    NT_ASSERT(PfnEntry->State == PfnPageTable);

    PfnEntry->PageTable.UsedPteCount += Addend;
    PfnEntry->PageTable.ValidPteCount += Addend;
    NT_ASSERT((PfnEntry->PageTable.UsedPteCount >= 0) &&
              (PfnEntry->PageTable.UsedPteCount <= PTE_PER_PAGE)); // HACK
    NT_ASSERT((PfnEntry->PageTable.ValidPteCount >= 0) &&
              (PfnEntry->PageTable.ValidPteCount <= PTE_PER_PAGE)); // HACK
    return PfnEntry->PageTable.UsedPteCount;
}

ULONG
PFN_DATABASE::ModifyUsedCount (
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ LONG Addend)
{
    PFN_ENTRY* PfnEntry = &m_PfnArray[PageFrameNumber];
    NT_ASSERT(PfnEntry->State == PfnPageTable);

    PfnEntry->PageTable.UsedPteCount += Addend;
    NT_ASSERT((PfnEntry->PageTable.UsedPteCount >= 0) &&
              (PfnEntry->PageTable.UsedPteCount <= PTE_PER_PAGE)); // HACK
    return PfnEntry->PageTable.UsedPteCount;
}

ULONG
PFN_DATABASE::ModifyValidCount (
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ LONG Addend)
{
    PFN_ENTRY* PfnEntry = &m_PfnArray[PageFrameNumber];
    NT_ASSERT(PfnEntry->State == PfnPageTable);

    PfnEntry->PageTable.ValidPteCount += Addend;
    NT_ASSERT((PfnEntry->PageTable.ValidPteCount >= 0) &&
              (PfnEntry->PageTable.ValidPteCount <= PTE_PER_PAGE)); // HACK
    return PfnEntry->PageTable.ValidPteCount;
}

PFN_NUMBER
PFN_DATABASE::AllocatePageLocked (
    _In_ ULONG DesiredPageColor,
    _Inout_ PBOOLEAN Zeroed)
{
    PFN_NUMBER PageFrameNumber;
    ULONG PageColor;
    PPFN_LIST List1, List2;

    /* Safe the original page color */
    PageColor = DesiredPageColor;

    /* Check if the caller wants a zeroed page */
    if (*Zeroed)
    {
        /* Yes, try zeroed list first, then dirty list */
        List1 = m_ZeroedLists;
        List2 = m_FreeLists;
    }
    else
    {
        /* No, try dirty list first, then zeroed list */
        List1 = m_FreeLists;
        List2 = m_ZeroedLists;
    }

    for (;;)
    {
        /* Remove a page from the preferred list */
        PageFrameNumber = List1[PageColor].RemovePage();
        if (PageFrameNumber == 0)
        {
            /* Remove a page from the alternative list */
            PageFrameNumber = List2[PageColor].RemovePage();
            if (PageFrameNumber != 0)
            {
                /* Signal the caller, that we didn't get the preferred type */
                *Zeroed = !*Zeroed;
            }
        }

        /* Did we get a page? */
        if (PageFrameNumber != 0)
        {
            /* Check if it was allocated by contiguous allocations */
            if (!RtlTestBitEx(m_PhysicalMemoryBitmap, PageFrameNumber))
            {
                /* Continue with this page color */
                continue;
            }

            /* This one must be free now. Clear the free bit */
            NT_ASSERT(m_PfnArray[PageFrameNumber].State == PfnFree);
            m_PfnArray[PageFrameNumber].ReferenceCount = 1;
            RtlClearBitEx(m_PhysicalMemoryBitmap, PageFrameNumber);
            MmAvailablePages--;
            return PageFrameNumber;
        }

        /* Try with the next page color */
        PageColor = GetNextPageColorCycleNodes(PageColor, DesiredPageColor);
        if (PageColor == DesiredPageColor)
            break;
    }

    return 0;
}

PFN_NUMBER
PFN_DATABASE::AllocatePage (
    _In_ BOOLEAN Zeroed)
{
    PFN_NUMBER PageFrameNumber;
    PEPROCESS Process;
    ULONG PageColor;
    BOOLEAN WasZeroed;
    KIRQL OldIrql;

    /* Get the current process and the next page color */
    Process = PsGetCurrentProcess();
    PageColor = Process->NextPageColor;
    Process->NextPageColor = static_cast<USHORT>(GetNextPageColor(PageColor));

    /* Acquire the PFN database lock */
    OldIrql = KeAcquireQueuedSpinLock(LockQueuePfnLock);

    /* Allocate a page from the appropriate list */
    WasZeroed = Zeroed;
    PageFrameNumber = AllocatePageLocked(PageColor, &WasZeroed);

    /* Release the PFN database lock */
    KeReleaseQueuedSpinLock(LockQueuePfnLock, OldIrql);

    /* Check if we have a page and we need to zero it */
    if ((PageFrameNumber != 0) && Zeroed && !WasZeroed)
    {
        /* Zero this page */
        ZeroPage(PageFrameNumber);
        m_PfnArray[PageFrameNumber].Dirty = FALSE;
    }

    /* Return the new page */
    return PageFrameNumber;
}

VOID
PFN_DATABASE::FreePageLocked (
    _Inout_ PFN_NUMBER PageFrameNumber)
{
    PPFN_ENTRY PfnEntry;
    ULONG Color;

    Color = PageFrameNumber & KeGetCurrentPrcb()->SecondaryColorMask;

    PfnEntry = &m_PfnArray[PageFrameNumber];
    NT_ASSERT(PfnEntry->ReferenceCount == 0);

    /* Mark it as a free entry */
    PfnEntry->State = PfnFree;

    /* Insert the page into the free list */ /// \todo check for Dirty flag
    PfnEntry->Flink = m_FreeLists[Color].m_ListHead;
    m_FreeLists[Color].m_ListHead = PageFrameNumber;

    /* Set the free bit */
    RtlSetBitEx(m_PhysicalMemoryBitmap, PageFrameNumber);

    MmAvailablePages++;
}

VOID
PFN_DATABASE::ReleasePage (
    _Inout_ PFN_NUMBER PageFrameNumber)
{
    KIRQL OldIrql;

    /* Acquire the PFN database lock */
    OldIrql = KeAcquireQueuedSpinLock(LockQueuePfnLock);

    /* Dereference the page */
    m_PfnArray[PageFrameNumber].ReferenceCount--;
    if (m_PfnArray[PageFrameNumber].ReferenceCount == 0)
    {
        /* Free the page */
        FreePageLocked(PageFrameNumber);
    }

    /* Release the PFN database lock */
    KeReleaseQueuedSpinLock(LockQueuePfnLock, OldIrql);
}

NTSTATUS
PFN_DATABASE::AllocateMultiplePages (
    _Out_ PFN_LIST* PageList,
    _In_ ULONG_PTR NumberOfPages,
    _In_ BOOLEAN Zeroed)
{
    PEPROCESS Process;
    PFN_NUMBER PageFrameNumber;
    ULONG_PTR PagesRemaining;
    ULONG PageColor;
    BOOLEAN WasZeroed;
    KIRQL OldIrql;

    /* Initialize the page list */
    PageList->Initialize();

    /* Check if there is anything to do */
    if (NumberOfPages == 0)
    {
        return STATUS_SUCCESS;
    }

    /* Get the current process and the next page color */
    Process = PsGetCurrentProcess();
    PageColor = Process->NextPageColor;

    /* Acquire the PFN database lock */
    OldIrql = KeAcquireQueuedSpinLock(LockQueuePfnLock);

    PagesRemaining = NumberOfPages;
    do
    {
        /* Allocate a page from the appropriate list */
        WasZeroed = Zeroed;
        PageFrameNumber = AllocatePageLocked(PageColor, &WasZeroed);

        /* Check for failure */
        if (PageFrameNumber == 0)
        {
            /* Release the PFN database lock */
            KeReleaseQueuedSpinLock(LockQueuePfnLock, OldIrql);

            /* Release everything we allocated so far */
            ReleaseMultiplePages(PageList);

            return STATUS_NO_MEMORY;
        }

        /* Add the page to the list */
        PageList->AddPage(PageFrameNumber);

        /* Get the next page color */
        PageColor = GetNextPageColor(PageColor);
    }
    while (--PagesRemaining);

    /* Adjust next page color */
    Process->NextPageColor = (USHORT)PageColor;

    /* Release the PFN database lock */
    KeReleaseQueuedSpinLock(LockQueuePfnLock, OldIrql);

    /* Check if zeroed pages were requested */
    if (Zeroed)
    {
        /* Loop all pages from the list */
        PageFrameNumber = PageList->m_ListHead;
        while (PageFrameNumber != 0)
        {
            /* Check if page is dirty */
            if (m_PfnArray[PageFrameNumber].Dirty)
            {
                /* Zero this page */
                ZeroPage(PageFrameNumber);
                m_PfnArray[PageFrameNumber].Dirty = FALSE;
            }

            /* Get next PFN */
            PageFrameNumber = m_PfnArray[PageFrameNumber].Flink;
        }
    }

    return STATUS_SUCCESS;
}


VOID
PFN_DATABASE::ReleaseMultiplePages (
    _Inout_ PFN_LIST* PageList)
{
    PFN_NUMBER PageFrameNumber;

    for (;;)
    {
        PageFrameNumber = PageList->RemovePage();
        if (PageFrameNumber == 0)
        {
            break;
        }

        ReleasePage(PageFrameNumber);
    }
}

NTSTATUS
PFN_DATABASE::AllocateLargePages (
    _Out_ PFN_LIST* LargePageList,
    _In_ ULONG_PTR NumberOfLargePages,
    _In_ BOOLEAN Zeroed)
{
    PFN_NUMBER LargePageNumber;
    NTSTATUS Status;
    NT_ASSERT(NumberOfLargePages > 0);

    /* Initialize the page list */
    LargePageList->Initialize();

    do
    {
        /* Allocate one large page */
        Status = AllocateContiguousPages(&LargePageNumber,
                                         LARGE_PAGE_SIZE / PAGE_SIZE,
                                         0,
                                         MmHighestPhysicalPage,
                                         LARGE_PAGE_SIZE / PAGE_SIZE,
                                         0);
        if (!NT_SUCCESS(Status))
        {
            ReleaseLargePages(LargePageList);
            return Status;
        }

        LargePageList->AddPage(LargePageNumber);
    }
    while (--NumberOfLargePages > 0);

    return STATUS_SUCCESS;
}

VOID
PFN_DATABASE::ReleaseLargePages (
    _Inout_ PFN_LIST* PageList)
{
    PFN_NUMBER LargePagePfn;

    for (;;)
    {
        /* Remove the next page from the list */
        LargePagePfn = PageList->RemovePage();
        if (LargePagePfn == 0)
        {
            break;
        }

        /* Must be large page aligned */
        NT_ASSERT((LargePagePfn & ~LARGE_PAGE_MASK) == 0);

        /* Free the large page allocation */
        FreeContiguousPages(LargePagePfn);
    }
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
PFN_DATABASE::AllocateContiguousPages (
    _Out_ PPFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ PFN_NUMBER LowestAcceptablePfn,
    _In_ PFN_NUMBER HighestAcceptablePfn,
    _In_opt_ PFN_NUMBER BoundaryPageMultiple,
    _In_ NODE_REQUIREMENT PreferredNode)
{
    PFN_NUMBER PageNumber, BasePage, EndPage, PageCount;
    KIRQL OldIrql;
    RTL_BITMAP_EX Bitmap;
    PPHYSICAL_MEMORY_RUN Run;
    ULONG_PTR Index, HintIndex;
    PULONG_PTR Buffer;
    NTSTATUS Status;

    /* Fix up boundary page multiple */
    if (BoundaryPageMultiple == 0)
        BoundaryPageMultiple = 1;

    /* Acquire the PFN database lock */
    OldIrql = KeAcquireQueuedSpinLock(LockQueuePfnLock);

    /* Loop all physical memory runs */
    for (ULONG i = 0; i < m_PhysicalMemoryDescriptor->NumberOfRuns; i++)
    {
        /* Check if this memory run is suitable */
        Run = &m_PhysicalMemoryDescriptor->Run[i];
        if ((Run->BasePage < LowestAcceptablePfn) ||
            (Run->BasePage + NumberOfPages > HighestAcceptablePfn))
        {
            /* There are no suitable pages in this physical run */
            continue;
        }

        /* Calculate the base and end page page */
        BasePage = max(Run->BasePage, LowestAcceptablePfn);
        EndPage = min(Run->BasePage + Run->PageCount, HighestAcceptablePfn + 1);

        for (;;)
        {
            /* Align the base page and calculate the page count for the bitmap */
            BasePage = ALIGN_DOWN_BY(BasePage, sizeof(ULONG_PTR) * 8);
            PageCount = EndPage - BasePage;

            /* Initialize the bitmap */
            Buffer = &m_PhysicalBitmapBuffer[BasePage / (sizeof(ULONG_PTR) * 8)];
            RtlInitializeBitMapEx(&Bitmap, Buffer, PageCount);

            HintIndex = Run->BasePage & (sizeof(ULONG_PTR) * 8 - 1);

            /* Try to find bits */
            Index = RtlFindSetBitsEx(&Bitmap, NumberOfPages, HintIndex);
            if (Index == MAXULONG_PTR)
            {
                break;
            }

            /* Calculate the page number, aligned as required */
            PageNumber = ALIGN_UP_BY(BasePage + Index, BoundaryPageMultiple);

            /* Check range */
            if (((PageNumber + NumberOfPages) > EndPage) ||
                ((PageNumber + NumberOfPages) <= BasePage))
            {
                break;
            }

            /* Check if the aligned bits are set */
            Index = PageNumber - BasePage;
            if (RtlAreBitsSetEx(&Bitmap, Index, NumberOfPages))
            {
                /* Mark it as a contiguous allocation */
                m_PfnArray[PageNumber].State = PfnContiguous;
                m_PfnArray[PageNumber].ReferenceCount = 1;
                m_PfnArray[PageNumber].Contiguous.NumberOfPages = NumberOfPages;

                /* Clear the free bits */
                RtlClearBitsEx(&Bitmap, Index, NumberOfPages);
                Status = STATUS_SUCCESS;
                goto Done;
            }

            /* Update start index and try again */
            BasePage += NumberOfPages - 1;
        }
    }

    PageNumber = 0;
    Status = STATUS_NO_MEMORY;

Done:

    MmAvailablePages -= NumberOfPages;

    /* Release the PFN database lock */
    KeReleaseQueuedSpinLock(LockQueuePfnLock, OldIrql);

    *BasePageFrameNumber = PageNumber;
    return Status;
}

VOID
PFN_DATABASE::FreeContiguousPages (
    _In_ PFN_NUMBER BasePageFrameNumber)
{
    PPFN_ENTRY PfnEntry;
    ULONG NumberOfPages;
    KIRQL OldIrql;

    PfnEntry = &m_PfnArray[BasePageFrameNumber];
    NT_ASSERT(PfnEntry->State == PfnContiguous);
    NT_ASSERT(PfnEntry->ReferenceCount == 1);
    NumberOfPages = PfnEntry->Contiguous.NumberOfPages;

    /* Acquire the PFN database lock */
    OldIrql = KeAcquireQueuedSpinLock(LockQueuePfnLock);

    do
    {
        PfnEntry->ReferenceCount = 0;
        FreePageLocked(BasePageFrameNumber++);
    }
    while (--NumberOfPages > 0);

    /* Release the PFN database lock */
    KeReleaseQueuedSpinLock(LockQueuePfnLock, OldIrql);
}


VOID
PFN_DATABASE::LockPage (
    _In_ PFN_NUMBER PageFrameNumber)
{

}

VOID
PFN_DATABASE::UnlockPage (
    _In_ PFN_NUMBER PageFrameNumber)
{

}

VOID
PFN_DATABASE::SetPageMapping (
    _In_ PFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    PFN_ENTRY* PfnEntry;

    PfnEntry = &m_PfnArray[BasePageFrameNumber];
    while (NumberOfPages--)
    {
        NT_ASSERT(PfnEntry->State == PfnFree);
        NT_ASSERT(PfnEntry->CacheAttribute == PfnNotMapped);
        //PfnEntry->State = 0;
        PfnEntry->CacheAttribute = CachingTypeToCacheAttribute[CachingType];

        PfnEntry++;
    }

    // walk through the PFN entries
        // make sure caching type is ok (bugcheck otherwise)
        // set caching type, if not yet mapped
        // increment mapping count
    UNIMPLEMENTED;
}

VOID
PFN_LIST::Initialize (
    VOID)
{
    m_ListHead = 0;
    m_ListTail = 0;
}

PFN_NUMBER
PFN_LIST::RemovePage (
    VOID)
{
    PFN_NUMBER PageFrameNumber;
    PFN_ENTRY* PfnEntry;

    /* Get the list head */
    PageFrameNumber = m_ListHead;
    if (PageFrameNumber != 0)
    {
        /* Get the PFN entry */
        PfnEntry = &g_PfnDatabase.m_PfnArray[PageFrameNumber];
        NT_ASSERT((PfnEntry->State == PfnFree) || (PfnEntry->State == PfnContiguous));

        /* Set head to the next entry */
        m_ListHead = PfnEntry->Flink;
    }

    return PageFrameNumber;
}

VOID
PFN_LIST::AddPage (
    PFN_NUMBER PageFrameNumber)
{
    PFN_ENTRY* PfnEntry;

    /* Get the PFN entry of the new page */
    PfnEntry = &g_PfnDatabase.m_PfnArray[PageFrameNumber];
    PfnEntry->Flink = 0;

    /* Check if the list is empty */
    if (m_ListHead == 0)
    {
        NT_ASSERT(m_ListTail == 0);
        m_ListHead = m_ListTail = PageFrameNumber;
    }
    else
    {
        /* Get the PFN entry of the old list tail */
        NT_ASSERT(m_ListTail != 0);
        PfnEntry = &g_PfnDatabase.m_PfnArray[m_ListTail];
        NT_ASSERT(PfnEntry->Flink == 0);
        PfnEntry->Flink = PageFrameNumber;
        m_ListTail = PageFrameNumber;
    }
}

}; // namespace Mm
