
#include "ntoskrnl.h"
#include "Mm_internal.h"


/* Types **********************************************************************/

typedef struct _VAD_POOL_HEADER
{
    LIST_ENTRY PageLink;
    LIST_ENTRY FreeLink;
    ULONG UsedVadEntries;

} VAD_POOL_HEADER, *PVAD_POOL_HEADER;

#define ALLOCATION_SIZE (PAGE_SIZE - sizeof(VAD_POOL_HEADER))
#define SLOTS_PER_PAGE (ALLOCATION_SIZE / sizeof(MMVAD))
#define BITMAP_SIZE ((SLOTS_PER_PAGE + 31) / 32)
#define ALIGN_VADS (PAGE_SIZE - sizeof(VAD_POOL_HEADER) - SLOTS_PER_PAGE * sizeof(MMVAD))

#if 0

typedef struct _VAD_POOL_PAGE
{
    VAD_POOL_HEADER;
    UCHAR align[ALIGN_VADS];
    MMVAD VadArray[SLOTS_PER_PAGE];
} VAD_POOL_PAGE, *PVAD_POOL_PAGE;
C_ASSERT(sizeof(VAD_POOL_PAGE) == PAGE_SIZE);

typedef struct _VAD_POOL
{
    VAD_POOL_HEADER Header;

    KGUARDED_MUTEX Lock; // For pool growth

    LIST_ENTRY PageList;
    LIST_ENTRY FreeList;
    LIST_ENTRY FreeVadList;
    PLIST_ENTRY InsertVadHead;

    ULONG MaximumPages;
    PVAD_POOL_PAGE LastPoolPage;

    struct _MIVPNENTRY *VpnList;

    MMVAD PoolVad;
    MMVAD VpnListVad;

} VAD_POOL, *PVAD_POOL;

#define SIZE_FOR_POOL (sizeof(VAD_POOL) - sizeof(VAD_POOL_HEADER))
#define SLOTS_FOR_POOL ((SIZE_FOR_POOL + sizeof(MMVAD) - 1) / sizeof(MMVAD))


/* Functions ******************************************************************/

NTSTATUS
NTAPI
MiCreateVadPoolAtAddress(
    _In_ PVOID Address,
    _In_ ULONG MaximumCount)
{
    PVAD_POOL Pool;
    ULONG MaximumPages;
    PVAD_POOL_PAGE PoolPage;
    PMMVAD Vad;
    NTSTATUS Status;

    // manually map the first page
    Status = MiCreateVirtualMapping(Address, 1, MM_PAGE_READ_WRITE);
    if (!NT_SUCCESS(Status))
    {
        /* Failed */
        return Status;
    }

    Pool = Address;

    // manually setup the VAD for the vad pool
    // set the first page as non paged (protected)

    InitializeListHead(&Pool->PageList);
    InitializeListHead(&Pool->FreeList);

    /* Insert the page for the pool into the page list */
    InsertHeadList(&Pool->PageList, &Pool->Header.PageLink);
    InsertHeadList(&Pool->FreeList, &Pool->Header.FreeLink);

    /* Get the Page for the pool */
    PoolPage = (PVAD_POOL_PAGE)Pool;

    /* Calculate the end of the pool */
    MaximumPages = (MaximumCount + SLOTS_FOR_POOL) / SLOTS_PER_PAGE;
    Pool->LastPoolPage = PoolPage + MaximumPages;

    /* This prevents the page from ever getting empty */
    PoolPage->UsedVadEntries = SLOTS_FOR_POOL;

    /* Loop all Vad entries after those used for the pool itself */
    for (Vad = &PoolPage->VadArray[SLOTS_FOR_POOL];
         Vad < &PoolPage->VadArray[SLOTS_PER_PAGE];
         Vad++)
    {
        /* Insert the VAD entry into the pool's free list */
        InsertTailList(&Pool->FreeVadList, (PLIST_ENTRY)Vad);
    }

    /* Point the head for inserting to the last entry */
    Pool->InsertVadHead = Pool->FreeVadList.Blink;

    return STATUS_SUCCESS;
}

VOID
FORCEINLINE
MiAcquireVadPoolLock(PVAD_POOL Pool)
{
    //
}

VOID
FORCEINLINE
MiReleaseVadPoolLock(PVAD_POOL Pool)
{
    //
}

static
PVAD_POOL_PAGE
MiAllocateVadPoolPage(PVAD_POOL Pool)
{
    PVAD_POOL_PAGE PreviousPage, PoolPage;
    PMMVAD Vad;

    /* Check if the free list is empty */
    if (IsListEmpty(&Pool->FreeList))
    {
        return NULL;
    }

    /* Get the first entry of the free list */
    PreviousPage = CONTAINING_RECORD(Pool->FreeList.Flink,
                                     VAD_POOL_PAGE,
                                     FreeLink);

    /* Get the address of the next free pool page */
    PoolPage = PreviousPage + 1;

    /* Commit and map the page */
    MiModifyVad(&Pool->PoolVad, MiAddressToVpn(PoolPage), 1, VPNSTATE_Valid);

    /* Insert the page after the previous page */
    InsertHeadList(&PreviousPage->PageLink, &PoolPage->PageLink);

    /* Check if the following page is not in use */
    if (PoolPage->PageLink.Flink != &PoolPage[1].PageLink)
    {
        /* Check if there are any free pages left */
        if (PoolPage < Pool->LastPoolPage)
        {
            /* Insert the page in the free list after the previous page */
            InsertHeadList(&PreviousPage->FreeLink, &PoolPage->FreeLink);
        }
    }

    /* Remove the previous page from the free list */
    RemoveEntryList(&PreviousPage->FreeLink);

    /* Loop all Vad entries except the first one */
    for (Vad = &PoolPage->VadArray[1];
         Vad < &PoolPage->VadArray[SLOTS_PER_PAGE];
         Vad++)
    {
        /* Insert the VAD entry into the pool's free list */
        InsertTailList(&Pool->FreeVadList, (PLIST_ENTRY)Vad);
    }

    /* Set number of used slots */
    PoolPage->UsedVadEntries = 1;

    /* Return the page */
    return PoolPage;
}

static
VOID
MiFreeVadPoolPage(PVAD_POOL Pool, PVAD_POOL_PAGE PoolPage)
{
    // FIXME
    __debugbreak();
}

PMMVAD
NTAPI
MiAllocateVad(PVAD_POOL Pool)
{
    PMMVAD Vad;
    PVAD_POOL_PAGE PoolPage;

    /* Lock the pool */
    MiAcquireVadPoolLock(Pool);

    /* Get an entry from the free list */
    Vad = (PMMVAD)RemoveHeadList(&Pool->FreeVadList);
    if (Vad)
    {
        /* Get the pool page */
        PoolPage = ALIGN_DOWN_POINTER_BY(Vad, PAGE_SIZE);

        /* Increment the used count */
        PoolPage->UsedVadEntries++;
        ASSERT(PoolPage->UsedVadEntries <= SLOTS_PER_PAGE);

        /* Update the head */
        if (Pool->InsertVadHead == (PLIST_ENTRY)Vad)
            Pool->InsertVadHead = &Pool->FreeVadList;
    }
    else
    {
        /* Allocate a new pool page */
        PoolPage = MiAllocateVadPoolPage(Pool);
        if (PoolPage)
        {
            /* Use the first slot */
            Vad = &PoolPage->VadArray[0];
        }
    }

    /* Unlock the pool */
    MiReleaseVadPoolLock(Pool);

    return Vad;
}

VOID
NTAPI
MiFreeVad(PVAD_POOL Pool, PMMVAD Vad)
{
    PVAD_POOL_PAGE PoolPage;
    PLIST_ENTRY ListHead;

    /* Lock the pool */
    MiAcquireVadPoolLock(Pool);

    /* Get the pool page */
    PoolPage = ALIGN_DOWN_POINTER_BY(Vad, PAGE_SIZE);

    /* Decrement the used count */
    ASSERT(PoolPage->UsedVadEntries >= 0);
    PoolPage->UsedVadEntries--;

    /* Check if the pool page is empty now */
    if (PoolPage->UsedVadEntries == 0)
    {
        MiFreeVadPoolPage(Pool, PoolPage);
    }
    else
    {
        /* Check if this allocation is from the pool's page itself */
        if (PoolPage == (PVAD_POOL_PAGE)Pool)
        {
            /* Always insert these at the list head */
            ListHead = &Pool->FreeVadList;

            /* Update the head */
            if (Pool->InsertVadHead == &Pool->FreeVadList)
                Pool->InsertVadHead = (PLIST_ENTRY)Vad;
        }
        /* Check if the page is more than half full */
        else if (PoolPage->UsedVadEntries > SLOTS_PER_PAGE / 2)
        {
            /* Use the current head for entries from additional pages */
            ListHead = Pool->InsertVadHead;
        }
        else
        {
            /* Use the tail of the list */
            ListHead = Pool->FreeVadList.Blink;
        }

        /* Insert the VAD into the appropriate position of the free list */
        InsertHeadList(ListHead, (PLIST_ENTRY)Vad);
    }

    /* Unlock the pool */
    MiReleaseVadPoolLock(Pool);
}

#endif
