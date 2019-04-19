
#include <ntoskrnl.h>
#include "Mm_internal.h"

/* Private types **************************************************************/

typedef union _MIPFNLISTHEADER
{
    LONGLONG Long;
    struct
    {
        ULONGLONG PageFrameNumber : 36;
        ULONGLONG Sequence : 28;
    };
} MIPFNLISTHEADER, *PMIPFNLISTHEADER;

typedef union _MIPFNLISTS
{
    struct
    {
        MIPFNLISTHEADER Dirty;
        MIPFNLISTHEADER Zeroed;
    };
    MIPFNLISTHEADER Lists[2];
} MIPFNLISTS, *PMIPFNLISTS;


/* Globals ********************************************************************/

PMIPFNENTRY MmPfnDatabase = (PMIPFNENTRY)MX_PFN_DATABASE;
static SIZE_T MiPfnDatabaseSize;
static ULONG MiNumberPageColors;
static ULONG MiPageColorMask;
static PMIPFNLISTS MiFreeListsByColor;


static
VOID
INITAPI
MiInitializePfnEntries(
    PFN_NUMBER BasePage,
    PFN_NUMBER PageCount,
    TYPE_OF_MEMORY MemoryType)
{
    PMIPFNENTRY PfnEntry;
    PMIPFNLISTHEADER ListHead;
    ULONG Color;
    ASSERT(!MiIsMemoryTypeInvisible(MemoryType));

    /* Get the first pfn of this descriptor. */
    PfnEntry = &MmPfnDatabase[BasePage];

    /* Check if the memory is free */
    if (MiIsMemoryTypeFree(MemoryType))
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++, BasePage++)
        {
            /* Add it to the free list */
            PfnEntry->Type = FreePfn;

            /* Insert the page into the dirty list */
            Color = BasePage & KxGetCurrentPrcb()->SecondaryColorMask;
            ListHead = &MiFreeListsByColor[Color].Dirty;
            PfnEntry->Free.Next = ListHead->PageFrameNumber;
            ListHead->PageFrameNumber = BasePage;
        }
    }
    else if (MemoryType == LoaderXIPRom)
    {
        // FIXME: later
        ASSERT(FALSE);
    }
    else if (MemoryType == LoaderBad)
    {
        // FIXME: later
        ASSERT(FALSE);
    }
    else
    {
        /* Loop all pages */
        for ( ; PageCount-- > 0; PfnEntry++)
        {
            /* Page is active for now assume it's not a page table */
            PfnEntry->Type = ActivePfn;
        }
    }

}

static
VOID
MiCalculatePageColors(VOID)
{
    ULONG PageColors, CacheSize, CacheAssociativity;

    /* Get the cache size */
    CacheSize = KeGetPcr()->SecondLevelCacheSize;
    if (CacheSize)
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

    KxGetCurrentPrcb()->SecondaryColorMask = (PageColors - 1);
}

VOID
INITAPI
MiBuildPfnDatabase(IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PLIST_ENTRY ListEntry;
    PMEMORY_ALLOCATION_DESCRIPTOR Descriptor;
    PFN_NUMBER BasePage, PageCount;
    PUCHAR PfnDataBaseEnd;
    SIZE_T SizeOfPageLists;
    ULONG NumberPageColors;

    /* Calculate number of page colors and mask */
    MiCalculatePageColors();

    /* Calculate the size of the pfn database entries */
    MiPfnDatabaseSize = MmHighestPhysicalPage * sizeof(MIPFNENTRY);

    /* Calculate Number of page colors and the size of the page lists */
    NumberPageColors = KeGetCurrentPrcb()->SecondaryColorMask + 1;
    SizeOfPageLists = sizeof(MIPFNLISTS) * NumberPageColors;

    /* Get address of page lists, which start after the PFN database */
    MiFreeListsByColor = (PVOID)&MmPfnDatabase[MmHighestPhysicalPage + 1];

    /* Calculate the end of the whole database */
    PfnDataBaseEnd = (PUCHAR)MiFreeListsByColor + SizeOfPageLists - 1;

    /* Map the PDEs and PPEs for the pfn database (ignore holes) */
#if (MI_PAGING_LEVELS >= 3)
    MiEarlyMapPPEs(MmPfnDatabase, PfnDataBaseEnd);
#endif
    MiEarlyMapPDEs(MmPfnDatabase, PfnDataBaseEnd);

    /* First map the page lists */
    MiEarlyMapPTEs(MiFreeListsByColor, PfnDataBaseEnd);

    /* Loop the memory descriptors */
    for (ListEntry = LoaderBlock->MemoryDescriptorListHead.Flink;
         ListEntry != &LoaderBlock->MemoryDescriptorListHead;
         ListEntry = ListEntry->Flink)
    {
        /* Get the descriptor */
        Descriptor = CONTAINING_RECORD(ListEntry,
                                       MEMORY_ALLOCATION_DESCRIPTOR,
                                       ListEntry);

        /* Skip invisible memory */
        if (MiIsMemoryTypeInvisible(Descriptor->MemoryType)) continue;

        /* Get the range for this descriptor */
        BasePage = Descriptor->BasePage;
        PageCount = Descriptor->PageCount;

        /* Map the pages for the database */
        MiEarlyMapPTEs(&MmPfnDatabase[BasePage],
                       (PUCHAR)(&MmPfnDatabase[BasePage + PageCount]) - 1);

        /* If this was the free descriptor, skip the next step */
        if (Descriptor == MiLargestDescriptor) continue;

        /* Add this descriptor to the database */
        MiInitializePfnEntries(BasePage, PageCount, Descriptor->MemoryType);
    }

    /* At this point the whole pfn database is mapped. We are about to add the
       pages from the descriptor to the database, that was used for early
       allocations. So from now on we cannot use it for allocations anymore. */

    /* Add the memory we used */
    BasePage = MiLargestDescriptor->BasePage;
    PageCount = MiLargestDescriptor->PageCount - MiEarlyAllocPageCount;
    MiInitializePfnEntries(BasePage, PageCount, LoaderMemoryData);

    /* Add the remaining free pages */
    BasePage = MiEarlyAllocBasePage;
    PageCount = MiEarlyAllocPageCount;
    MiInitializePfnEntries(BasePage, PageCount, LoaderFree);
}


static
PFN_NUMBER
MiAllocPage(PMIPFNLISTHEADER FreeList)
{
    MIPFNLISTHEADER ListHead, NewListHead;
    PMIPFNENTRY PfnEntry;

    /* Read the list head */
    ListHead = *FreeList;

    do
    {
        /* Check if the list is empty or locked */
        if (ListHead.PageFrameNumber == 0)
        {
            /* Fail */
            return 0;
        }

        /* Get the pfn entry for this page */
        PfnEntry = &MmPfnDatabase[ListHead.PageFrameNumber];

        /* Initialize a new list head */
        NewListHead.PageFrameNumber = PfnEntry->Free.Next;
        NewListHead.Sequence = ListHead.Sequence + 1;

        /* Try to atomically exchange the list head */
        ListHead.Long = InterlockedCompareExchange64(&FreeList->Long,
                                                     NewListHead.Long,
                                                     ListHead.Long);

    /* Repeat if this didn't succeed */
    } while (ListHead.Sequence != NewListHead.Sequence - 1);

    return ListHead.PageFrameNumber;
}

VOID
NTAPI
MiZeroPhysicalPage(PFN_NUMBER PageFrameNumber)
{
    PVOID Address;

    Address = MxGetEphemeralMapping(PageFrameNumber);

    MxZeroPage(Address);

    MxReleaseEphemeralMapping(Address);
}

PFN_NUMBER
NTAPI
MiAllocatePage(BOOLEAN NeedZero)
{
    PKPRCB Prcb = KxGetCurrentPrcb();
    ULONG OriginalColor, Color;
    PFN_NUMBER PageFrameNumber;
    UCHAR List1, List2;

    /* Get next page color (note: this is not safe regarding context switches,
       but for performance reasons we want to avoid an interlocked operation.
       Worst thing that can happen is a wrong page color once in a while. */
    OriginalColor = Color = (Prcb->PageColor++ & Prcb->SecondaryColorMask);

    List1 = NeedZero ? 1 : 0;
    List2 = NeedZero ? 0 : 1;

    while (TRUE)
    {
        /* Try to get a page with this color from the first list */
        PageFrameNumber = MiAllocPage(&MiFreeListsByColor[Color].Lists[List1]);
        if (PageFrameNumber != 0)
        {
            /* If a zeroed page was requested, we now got one. */
            NeedZero = FALSE;
            break;
        }

        /* Try second list for this color */
        PageFrameNumber = MiAllocPage(&MiFreeListsByColor[Color].Lists[List2]);
        if (PageFrameNumber != 0)
        {
            break;
        }

        /* Still nothing, try next color */
        Color++;
        Color &= Prcb->SecondaryColorMask;

        /* Check if we tried all colors */
        if (Color == OriginalColor)
        {
            /* Nothing free, we need to wait for the balancer */
            ASSERT(FALSE);
        }
    };

    /* Check if we (still) need to zero it out */
    if (NeedZero) MiZeroPhysicalPage(PageFrameNumber);

    return PageFrameNumber;
}


