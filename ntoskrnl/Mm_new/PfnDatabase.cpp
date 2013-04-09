

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
#include "VadObject.hpp"
#include "amd64/MmConstants.hpp"
#include <arc/arc.h>
#include <ndk/ketypes.h>


extern "C" PFN_NUMBER MmLowestPhysicalPage;
extern "C" PFN_NUMBER MmHighestPhysicalPage;
ULONG KeNumberNodes;
ULONG KeNodeShift;

namespace Mm {

ULONG PFN_DATABASE::m_CacheColorBits;
ULONG PFN_DATABASE::m_CacheColorMask;
PPFN_LIST PFN_DATABASE::m_FreeLists;
PPFN_LIST PFN_DATABASE::m_ZeroedLists;
PPHYSICAL_MEMORY_DESCRIPTOR PFN_DATABASE::m_PhysicalMemoryDescriptor;
PRTL_BITMAP PFN_DATABASE::m_PhysicalMemoryBitmap;
PFN_ENTRY* PFN_DATABASE::m_PfnArray;
PULONG PFN_DATABASE::m_PhysicalBitmapBuffer;
KSPIN_LOCK PFN_DATABASE::m_ContiguousMemoryLock;

extern PFN_NUMBER EarlyAllocPageBase;
extern PFN_NUMBER EarlyAllocPageCount;
extern PFN_NUMBER EarlyAllocLargePageBase;
//static KERNEL_VAD g_PfnDatabaseVad;

extern PMEMORY_ALLOCATION_DESCRIPTOR LargestFreeDescriptor;
extern ULONG NumberOfPhysicalMemoryRuns;

static const PFN_CACHE_ATTRIBUTE CachingTypeToCacheAttribute[] =
{
    PfnNonCached, PfnCached, PfnWriteCombined, PfnCached, PfnNonCached, PfnCached
};

VOID
EarlyMapPages (
    PVOID StartAddress,
    PVOID EndAddress);

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
    NT_ASSERT((KeNumberNodes & (KeNumberNodes - 1)) == 0);

    /* Get the node shift and calculate the node mask */
    NT_VERIFY(BitScanReverse(&KeNodeShift, PageColors));
    KeNodeMask = (KeNumberNodes - 1) << KeNodeShift;
}

static
ULONG
GetNextPageColor (
    _In_ ULONG PageColor,
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
    NextColor |= (PageColor & KeNodeMask);

    if (NextColor == OriginalColor)
    {
        return 0;
    }

    return NextColor;
}


VOID
INIT_FUNCTION
PFN_DATABASE::InitializePfnEntries (
    _In_ PFN_NUMBER BasePage,
    _In_ PFN_NUMBER PageCount,
    _In_ TYPE_OF_MEMORY MemoryType)
{
    PFN_ENTRY* PfnEntry;
    ULONG Color;

    /* Get the first PFN entry of this range. */
    PfnEntry = &m_PfnArray[BasePage];

    /* Check if the memory is free */
    if (IsFreeMemory(MemoryType))
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++, BasePage++)
        {
            /* Mark it as a free entry */
            PfnEntry->State = PfnFree;

            /* Insert the page into the dirty list */
            Color = BasePage & KeGetCurrentPrcb()->SecondaryColorMask;
            PfnEntry->Free.Next = m_FreeLists[Color].m_ListHead;
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
        }
    }
    else if (MemoryType == LoaderBad)
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++, BasePage++)
        {
            /* Mark it as bad */
            PfnEntry->State = PfnBad;
        }
    }
    else
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++)
        {
            /* Mark it as a reserved PFN */
            PfnEntry->State = PfnKernelReserved;
        }
    }


}

VOID
INIT_FUNCTION
InitializePfnEntriesFromPageTables (
    VOID)
{
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
    PULONG Buffer, BufferEnd;
    ULONG_PTR StaringVpn, EndingVpn;

    /* Initialize the page color mask */
    CalculatePageColors();
    NumberPageColors = KeGetCurrentPrcb()->SecondaryColorMask + 1;

    /* Calculate location of the page lists and physical memory descriptor */
    m_PfnArray = (PFN_ENTRY*)PFN_DATABASE_ADDRESS;
    m_FreeLists = reinterpret_cast<PPFN_LIST>(&m_PfnArray[MmHighestPhysicalPage + 1]);
    m_ZeroedLists = &m_FreeLists[NumberPageColors];
    m_PhysicalMemoryDescriptor = reinterpret_cast<PPHYSICAL_MEMORY_DESCRIPTOR>(
            &m_ZeroedLists[NumberPageColors]);
    m_PhysicalMemoryBitmap = reinterpret_cast<PRTL_BITMAP>(
            &m_PhysicalMemoryDescriptor->Run[NumberOfPhysicalMemoryRuns]);
    m_PhysicalBitmapBuffer = reinterpret_cast<PULONG>(
            m_PhysicalMemoryBitmap + 1);

    /* Map page lists, physical memory descriptor and physical memory bitmaps */
    EarlyMapPages(m_FreeLists, m_PhysicalBitmapBuffer);

    /* Initialize the physical memory descriptor */
    m_PhysicalMemoryDescriptor->NumberOfRuns = NumberOfPhysicalMemoryRuns;
    m_PhysicalMemoryDescriptor->NumberOfPages = 0;
    m_PhysicalMemoryDescriptor->Run[0].BasePage = MmLowestPhysicalPage;
    m_PhysicalMemoryDescriptor->Run[0].PageCount = 0;

    /* Initialize the PFN bitmap with the maximum range */
    RtlInitializeBitMap(m_PhysicalMemoryBitmap,
                        m_PhysicalBitmapBuffer,
                        static_cast<ULONG>(MmHighestPhysicalPage));

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
                      (PUCHAR)(&m_PfnArray[BasePage + PageCount]) - 1);

        /* Add this descriptor to the database */
        InitializePfnEntries(BasePage, PageCount, Descriptor->MemoryType);

        /* Calculate the range of the PFN bitmap buffer for this run */
        Buffer = &m_PhysicalBitmapBuffer[BasePage / 32];
        BufferEnd = &m_PhysicalBitmapBuffer[(NextPage - 1 + 31) / 32];

        /* Map the pages for the bitmap buffer */
        EarlyMapPages(Buffer, reinterpret_cast<PCHAR>(BufferEnd) - 1);

        /* Check if this is free memory */
        if (IsFreeMemory(Descriptor->MemoryType))
        {
            /* Set the bits for this run */
            RtlSetBits(m_PhysicalMemoryBitmap,
                       static_cast<ULONG>(BasePage),
                       static_cast<ULONG>(PageCount));
        }

    }

    /* Make sure we counted correctly */
    NT_ASSERT(i == NumberOfPhysicalMemoryRuns - 1);

__debugbreak();

    /* Reinitialize the PFN entries for the early allocations */
    InitializePfnEntries(LargestFreeDescriptor->BasePage,
                         EarlyAllocPageBase - LargestFreeDescriptor->BasePage,
                         LoaderMemoryData);

#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
    /* Calculate the "next" page (exclusive) for large page allocations */
    NextPage = (LargestFreeDescriptor->BasePage +
                LargestFreeDescriptor->PageCount) & LARGE_PAGE_MASK;

    /* Reinitialize the PFN entries for the large page allocations */
    InitializePfnEntries(EarlyAllocLargePageBase,
                         NextPage - EarlyAllocLargePageBase,
                         LoaderLargePageFiller);
#endif

    /* Early allocations are not allowed any longer */
    EarlyAllocPageCount = 0;

    /* Calculate the starting and ending VPN of the database */
    StaringVpn = reinterpret_cast<ULONG_PTR>(m_PfnArray) >> PAGE_SHIFT;
    EndingVpn = (reinterpret_cast<ULONG_PTR>(BufferEnd) - 1) >> PAGE_SHIFT;

    /* Reserve the virtual address range for the PFN database */
//    g_KernelVadTable.InsertVadObjectAtVpn(&g_PfnDatabaseVad,
//                                          StaringVpn,
//                                          EndingVpn - StaringVpn + 1);

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
    KLOCK_QUEUE_HANDLE LockHandle, *LockHandles;
    ULONG NumberPageColors, Index;
    PFN_NUMBER BasePage;

    /// \todo FIXME NUMA nodes!
    NumberPageColors = KeGetCurrentPrcb()->SecondaryColorMask + 1;

    LockHandles = static_cast<PKLOCK_QUEUE_HANDLE>(
                  ExAllocatePoolWithTag(NonPagedPool,
                                        2 * NumberPageColors * sizeof(*LockHandles),
                                        TAG_MM));
    if (LockHandles == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // acquire the global lock
    KeAcquireInStackQueuedSpinLock(&m_ContiguousMemoryLock, &LockHandle);

    // lock the lists (free and zeroed for all page colors)
    for (ULONG i = 0; i < NumberPageColors; i++)
    {
        m_FreeLists[i].AcquireSpinLock(&LockHandles[i * 2]);
        m_ZeroedLists[i].AcquireSpinLock(&LockHandles[i * 2 + 1]);
    }

    for (ULONG i = 0; i < m_PhysicalMemoryDescriptor->NumberOfRuns; i++)
    {
        ULONG HintIndex = 0;

        // find free bits in the physical memory bitmap for this run
        /// \todo FIXME: currently we do sparse mapping of the bitmap.
        /// We can either map it fully, possibly wasting some memory
        /// or we use multiple bitmaps (one per run) and have each
        /// point to a ULONG(64) aligned range in the buffer.
        Index = RtlFindSetBitsAndClear(m_PhysicalMemoryBitmap,
                                       NumberOfPages,
                                       HintIndex);
        if (Index != 0xFFFFFFFF)
        {
            BasePage = m_PhysicalMemoryDescriptor->Run[i].BasePage + Index;
            break;
        }
    }


    // unlock the lists
    for (ULONG i = 0; i < NumberPageColors; i++)
    {
        m_FreeLists[i].ReleaseSpinLock(&LockHandles[i * 2]);
        m_ZeroedLists[i].ReleaseSpinLock(&LockHandles[i * 2 + 1]);
    }

    KeReleaseInStackQueuedSpinLock(&LockHandle);

    return 0;
}

VOID
PFN_DATABASE::FreeContiguousPages (
    _In_ PFN_NUMBER BasePageFrameNumber)
{
    UNIMPLEMENTED;
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

}; // namespace Mm
