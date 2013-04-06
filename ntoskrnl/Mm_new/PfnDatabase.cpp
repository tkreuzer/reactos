

/*

Concurrency between interlocked page removal and contiguous page allocation:
- Contiguous allocator
    - Lock global contiguous memory spinlock
    - trigger an IPI for all CPUs
        - All CPUs wait, except this one
        - This CPU performs the allocation (non-interlocked)
        -


*/

#include "PfnDatabase.hpp"
#include "VadTable.hpp"
#include "VadObject.hpp"
#include "amd64/PageTables.hpp"
#include "amd64/MmConstants.hpp"
#include <arc/arc.h>
#include <ndk/ketypes.h>

#define INIT_FUNCTION

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
PRTL_BITMAP PFN_DATABASE::m_PhysicalMemoryBitmaps;
PFN_ENTRY* PFN_DATABASE::m_PfnArray;
PULONG PFN_DATABASE::m_PhysicalBitmapBuffer;
KSPIN_LOCK PFN_DATABASE::m_ContiguousMemoryLock;

static PFN_NUMBER EarlyAllocBasePage;
static PFN_NUMBER EarlyAllocPageCount;
//static KERNEL_VAD g_PfnDatabaseVad;

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
 *      EarlyAllocBasePage are set and can not be used after the PFN database
 *      was created.
 */
static
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
    EarlyAllocPageCount--;
    return EarlyAllocBasePage++;
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
EarlyMapPTEs (
    PVOID StartAddress,
    PVOID EndAddress)
{
#if MI_PAGING_LEVELS >= 4
    for (PPXE PxePointer = AddressToPxe(StartAddress);
         PxePointer <= AddressToPxe(EndAddress);
         PxePointer++)
    {
        //PXE TempPxe;
        if (!PxePointer->IsValid())
        {
            //TempPxe.InitializeKernelPxe(EarlyAllocPage());
            //*PxePointer = TempPxe;
            *PxePointer = PXE::CreateValidKernelPxe(EarlyAllocPage());
            RtlZeroMemory(PteToAddress(PxePointer), PAGE_SIZE);
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
            RtlZeroMemory(PteToAddress(PpePointer), PAGE_SIZE);
        }
    }
#endif
    for (PPDE PdePointer = AddressToPde(StartAddress);
         PdePointer <= AddressToPde(EndAddress);
         PdePointer++)
    {
        if (!PdePointer->IsValid())
        {
            DbgPrint("Writing Pde @ %p\n", PdePointer);
            *PdePointer = PDE::CreateValidKernelPde(EarlyAllocPage());
            DbgPrint("Zeroing page table @ %p\n", PteToAddress(PdePointer));
            RtlZeroMemory(PteToAddress(PdePointer), PAGE_SIZE);
        }
    }

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
    ULONG NumberPageColors, NumberOfRuns, i;
    PFN_NUMBER BasePage, PageCount, LastPage, LargestPageCount;
    PLIST_ENTRY ListEntry;
    PMEMORY_ALLOCATION_DESCRIPTOR Descriptor, LargestFreeDescriptor;
    PULONG Buffer, BufferEnd;
    ULONG_PTR StaringVpn, EndingVpn;

    /* Initialize the page color mask */
    CalculatePageColors();
    NumberPageColors = KeGetCurrentPrcb()->SecondaryColorMask + 1;

    /* Start with 0 runs and set LastPage so that the first descriptor will
       count as a new run */
    NumberOfRuns = 0;
    LastPage = -2;
    LargestPageCount = 0;

    MmLowestPhysicalPage = -1; // ULONG_PTR_MAX;
    MmHighestPhysicalPage = 0;

    /* The first loop to gather the required data */
    for (ListEntry = LoaderBlock->MemoryDescriptorListHead.Flink;
         ListEntry != &LoaderBlock->MemoryDescriptorListHead;
         ListEntry = ListEntry->Flink)
    {
        /* Get the descriptor */
        Descriptor = CONTAINING_RECORD(ListEntry,
                                       MEMORY_ALLOCATION_DESCRIPTOR,
                                       ListEntry);

        /* Check if this is a new run */
        if (Descriptor->BasePage != LastPage + 1)
        {
            NumberOfRuns++;
        }

        /* Get the range for this descriptor */
        LastPage = Descriptor->BasePage + Descriptor->PageCount - 1;
        MmHighestPhysicalPage = max(MmHighestPhysicalPage, LastPage);
        MmLowestPhysicalPage = min(MmLowestPhysicalPage, Descriptor->BasePage);

        /* Check if this is free memory */
        if (IsFreeMemory(Descriptor->MemoryType))
        {
            /* Check if it's the larges free descriptor do far */
            if (Descriptor->PageCount > LargestPageCount)
            {
                /* Remember this descriptor for early allocations */
                LargestFreeDescriptor = Descriptor;
            }
        }
    }

    /* Save range of pages for early allocations */
    EarlyAllocBasePage = LargestFreeDescriptor->BasePage;
    EarlyAllocPageCount = LargestFreeDescriptor->PageCount;

    /* Calculate location of the page lists and physical memory descriptor */
    m_PfnArray = (PFN_ENTRY*)PFN_DATABASE_ADDRESS;
    m_FreeLists = reinterpret_cast<PPFN_LIST>(&m_PfnArray[MmHighestPhysicalPage + 1]);
    m_ZeroedLists = &m_FreeLists[NumberPageColors];
    m_PhysicalMemoryDescriptor = reinterpret_cast<PPHYSICAL_MEMORY_DESCRIPTOR>(
                                                    &m_ZeroedLists[NumberPageColors]);
    m_PhysicalMemoryBitmaps = reinterpret_cast<PRTL_BITMAP>(&m_PhysicalMemoryDescriptor->Run[NumberOfRuns]);
    m_PhysicalBitmapBuffer = reinterpret_cast<PULONG>(&m_PhysicalMemoryBitmaps[NumberOfRuns]);

    /* Map page lists, physical memory descriptor and physical memory bitmaps */
    EarlyMapPTEs(m_FreeLists, m_PhysicalBitmapBuffer);

    /* Initialize the physical memory descriptor */
    m_PhysicalMemoryDescriptor->NumberOfRuns = NumberOfRuns;
    m_PhysicalMemoryDescriptor->NumberOfPages = 0;
    m_PhysicalMemoryDescriptor->Run[0].BasePage = MmLowestPhysicalPage;

    /* This time initialize LastPage, so we skip the first descriptor(s)
       when looking for physical memory runs */
    LastPage = MmLowestPhysicalPage - 1;
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
        if (Descriptor->BasePage != LastPage + 1)
        {
            /* Calculate the page count for this run */
            m_PhysicalMemoryDescriptor->Run[i].PageCount =
                LastPage + 1 - m_PhysicalMemoryDescriptor->Run[i].BasePage;

            /* Start next run */
            i++;

            /* Set base page for the new run */
            m_PhysicalMemoryDescriptor->Run[i].BasePage = Descriptor->BasePage;
        }

        /* Get the range for this descriptor */
        BasePage = Descriptor->BasePage;
        PageCount = Descriptor->PageCount;
        LastPage = BasePage + PageCount - 1;

        /* Map the pages for the database */
        EarlyMapPTEs(&m_PfnArray[BasePage],
                       (PUCHAR)(&m_PfnArray[BasePage + PageCount]) - 1);

        /* Add this descriptor to the database */
        InitializePfnEntries(BasePage, PageCount, Descriptor->MemoryType);
    }

    /* Make sure we counted correctly */
    NT_ASSERT(i == NumberOfRuns - 1);

    /* Calculate the page count for the last run */
    m_PhysicalMemoryDescriptor->Run[i].PageCount =
        LastPage + 1 - m_PhysicalMemoryDescriptor->Run[i].BasePage;
__debugbreak();
    /* Loop all physical memory runs */
    Buffer = m_PhysicalBitmapBuffer;
    for (i = 0; i < NumberOfRuns; i++)
    {
        /* Get the page count for this run (must not overflow an ULONG!) */
        PageCount = m_PhysicalMemoryDescriptor->Run[i].PageCount;
        NT_ASSERT(PageCount < MAXULONG);

        /* Calculate the end of the bitmap buffer (exclusive) */
        BufferEnd = &Buffer[(PageCount + 31) / 32];

        /* Map the pages for the bitmap buffer */
        EarlyMapPTEs(Buffer, reinterpret_cast<PCHAR>(BufferEnd) - 1);

        /* Initialize the bitmap and update the buffer */
        RtlInitializeBitMap(&m_PhysicalMemoryBitmaps[i],
                            Buffer,
                            static_cast<ULONG>(PageCount));
        RtlClearAllBits(&m_PhysicalMemoryBitmaps[i]);
        Buffer = BufferEnd;
    }

    /* Reinitialize the PFN entries for the early allocations */
    InitializePfnEntries(LargestFreeDescriptor->BasePage,
                         LargestFreeDescriptor->PageCount - EarlyAllocPageCount,
                         LoaderMemoryData);

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
        Index = RtlFindSetBitsAndClear(&m_PhysicalMemoryBitmaps[i],
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
PFN_DATABASE::SetMappedPages (
    _In_ PFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    // walk through the PFN entries
        // make sure caching type is ok (bugcheck otherwise)
        // set caching type, if not yet mapped
        // increment mapping count
    UNIMPLEMENTED;
}

}; // namespace Mm
