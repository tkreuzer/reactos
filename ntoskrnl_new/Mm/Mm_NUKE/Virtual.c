

#include <ntoskrnl.h>
#include "Mm_internal.h"

/*
 *                      32bit       64bit
 * -----------------------------------------------
 * size of HyperSpace   4 MB        512 GB
 * sizeof(VPNENTRY)     4           8
 * Num VPNs in UM       0x30000     0x80000000
 * size of UM VPN list  768 KB      16 GB
 * Bits for VPN number  18          32
 * Num VPNs in KM       0x20000     0x98000000 (from page tables)
 *                                  0x100000000 (from FFFFF00000000000)
 *
 * max num VADs         12288       0x8000000
 * sizeof(MIVAD)        ~32         ~64
 * max size VADs        384 KB      8 GB
 * Bits for VAD index   14          27
 *
 * needs extra region of VPEs for page tables and hyper space!
 */


/*

PTEs for user mode
------------------
FFFFF68000000000    PTE for 0
FFFFF683FFFFFFF8    PTE for 000007FFFFFFFFFF

PTEs for PTs
-------------
FFFFF6FB40000000    PDE for 0 == PTE for FFFFF68000000000
FFFFF6FB41FFFFF8    PDE for 000007FFFFFFFFFF

FFFFF6FB7DA00000    PPE for 0 == PTE for FFFFF6FB40000000
FFFFF6FB7DBED000    PXE for 0 == PTE for FFFFF6FB7DA00000

FFFFF70000000000    Hyperspace start


*/

NTSTATUS
NTAPI
MiCreateVirtualMapping(
    _In_ PVOID Address,
    _In_ ULONG PageCount,
    _In_ ULONG Protection)
{
    return 0;
}


ULONG_PTR MmHighestUserVpn;

NTSTATUS
NTAPI
MiCommitNonPagedMemory(
    _Inout_ PMIVAD Vad,
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount)
{
    MXPTE PteValue, *PtePointer;

    /* Commit higher page table levels, so we can access PTEs */
    PtePointer = MxReservePtes(StartingVpn, PageCount);

    /* Create a valid kernel PTE */
    PteValue = MxValidKernelPte;

    /* Loop all pages */
    while (PageCount--)
    {
        /* Allocate a physical page, no zeroing, FIXME: no waiting? */
        PteValue.Active.PageFrameNumber = MiAllocatePage(FALSE);

        /* Write the PTE and continue with next PTE */
        *PtePointer = PteValue;
        PtePointer++;
    }

    return 0;
}

#if 0
NTSTATUS
NTAPI
MiCommitVirtualMemory(
    _Inout_ PMIVAD Vad,
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount)
{
    MXPTE PteValue, *PtePointer;
    BOOLEAN Owner;

    /* Map higher page table levels, so we can access PTEs */
    PtePointer = MxReservePtes(StartingVpn, PageCount);

    Owner = (StartingVpn <= MmHighestUserVpn);

    /* Create a demand PTE */
    PteValue = MxCreateDemandPte(Vad->Type, Protection, Vad->Owner);

    /* Loop all PTEs */
    while (PageCount--)
    {
        /* Write the demand PTE and continue with next PTE */
        *PtePointer = PteValue;
        PtePointer++;
    }

    return 0;
}
#endif



//MIVADTYPE MiVirtualMemoryVadType;
//MIVADTYPE MiNonPagedMemoryVadType;
//MIVADTYPE MiPagedMemoryVadType;

enum
{
    VadCommit,
    VadDecommit,
};

VOID
NTAPI
MiModifyVad(
    _Inout_ PMIVAD Vad,
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount,
    _In_ ULONG Action)
{
    ASSERT(StartingVpn + PageCount > StartingVpn);
    ASSERT(StartingVpn >= Vad->StartingVpn);
    ASSERT(StartingVpn + PageCount - 1 <= Vad->EndingVpn);
#if 0
    //VadType = Vad->Type;


    // lock the Vad

    Status = VadType->ModifyRoutine[Action](Vad, ...);

    // unlock the Vad

    if (VpnState == VadCommit)
    {
        // create a demand zero pte

        while (PageCount--)
        {
            /* Write the PTE and continue with next PTE */
            *PtePointer = PteValue;
            PtePointer++;
        }
    }
    else
    {
        __debugbreak();
    }

#endif
}


#if 0

PMMVPNENTRY MiUserVpnList



enum
{
    VadTypeNonPaged,
    VadTypeAllocation,
    VadTypeSection,
};


typedef union _MIVADLISTHEADER
{
    LONG Long;
    struct
    {
        USHORT First;
        USHORT Sequence;
    };
} MIVADLISTHEADER, *PMIVADLISTHEADER;

typedef struct _MIVADLIST
{
    MM_AVL_TABLE VadRoot;
    ULONG NumberOfPages;
    MIVADLISTHEADER FreeListHead;
    MIVAD PagetableVad;
    MIVAD HyperspaceVad;
    MIVAD VadEntries[];
} MIVADLIST, *PMIVADLIST;

typedef struct
{
    MIVADLIST;
    MIVAD VadEntriesBuffer[20];
} VADLIST2;

void
MiInitializeVirtualMapping()
{
    // first commit the range needed for the working set list entries

}

VOID
NTAPI
MiInitializeAddressSpace()
{
    PMIVADLIST VadList;
    PULONG NextLink;
    PMIVAD Vad;

    // map the page for the vadlist
    MiMapPxe(MxAddressToPxe(VadList), MiAllocateZeroedPage());
    MiMapPpe(MxAddressToPxe(VadList), MiAllocateZeroedPage());

    VadList->NumberOfPages = 1;
    VadList->FreeList.Long = 0;

    // link the free vad entries
    for (i = 0; i < VadList->MaxIndex; i++)
    {
        NextLink = VadList->VadEntries[i];
        *NextLink = i + 1;
    }

    // initialize the mapping
    //VadList->PagetableVad;

    VadList->HyperspaceVad.Node.StartingVpn = MX_HYPERSPACE_START >> PAGE_SHIFT;
    VadList->HyperspaceVad.Node.EndingVpn = MX_HYPERSPACE_END >> PAGE_SHIFT;

    MiInsertNode(&VadList->VadRoot, &VadList->HyperspaceVad.Node);


    // map the pages for the working set list entries for

}


static
PFN_NUMBER
MiInterlockedAllocVad(PMIPFNLISTHEADER VadList)
{
    MIVADLISTHEADER ListHead, NewListHead;
    PMIVAD Vad;

    /* Read the list head */
    ListHead = VadList->FreeListHead;

    do
    {
        /* Check if the list is empty */
        if (ListHead.First == 0)
        {
            /* Fail */
            return 0;
        }

        /* Get the VAD */
        Vad = &VadList->VadEntries[ListHead.First];

        /* Initialize a new list head */
        NewListHead.First = (USHORT)Vad->StartingVpn;
        NewListHead.Sequence = ListHead.Sequence + 1;

        /* Try to atomically exchange the list head */
        ListHead.Long = InterlockedCompareExchange(&VadList->FreeListHead.Long,
                                                   NewListHead.Long,
                                                   ListHead.Long);

    /* Repeat if this didn't succeed */
    } while (ListHead.Sequence != NewListHead.Sequence - 1);

    return ListHead.PageFrameNumber;
}


PMIVAD
NTAPI
MiAllocateVad(
    PVOID StartAddress,
    SIZE_T Size,

    )
{
    PMIVADLIST VadList;

    // try to atomically allocate a vad

    /* Check if that failed */
    if (!Vad)
    {
        // Lock VadList->SelfVad;

        // check if there are free entries now
            // commit next page in the hyperspace vad region
            // initialize the vad entries free links
        // remove first entry
        // set new free list head (atomically link the list):
            // head->free1->free2  =>  head->newfree1->newfree2->...->newfree_n->free1->free2
        // unlock hyperspace vad
    }



}


MxUnmapPxe(
    PMXPTE Pxe)
{
    ASSERT(Pxe->u.Hard.Valid);
    ASSERT(Pxe->u.Hard.PageFrameNumber != 0)
    ASSERT(MmPfnDataBase[Pxe->u.Hard.PageFrameNumber].PageTable.ValidCount == 0);

    *Pxe =
    __invlpg();
}


MiMapPxe(
    PMMPXE PointerPxe,
    PFN_NUMBER PageFrameNumber)
{

}


VOID
NTAPI
MiInitializeVirtualMapping(
    PMIVAD Vad,
    PVOID StartAddress,
    SIZE_T Size,
    ULONG Protection,


{
    PMIVAD PageTableVad = MiPageTableVad;

#if (MI_PAGING_LEVELS == 4)
    // map all PXEs
        // check if its already mapped
        // allocate a page
        // map the PXE
        // mark the allocation in the
#endif
#if (MI_PAGING_LEVELS >= 3)
    // map all PPEs
#endif



}

VOID
NTAPI
MiInsertNode(
    PMM_AVL_TABLE Table,
    PMMAVLNODE Parent,
    PMMAVLNODE Node)
{
}

NTSTATUS
NTAPI
MiInsertVad(
    PMIVADLIST VadList,
    PMIVAD Vad)
{
    TABLE_SEARCH_RESULT Result;
    NTSTATUS Status;

    /* Lock the VAD list */
    KeAcquireGuardedMutex(&VadList->Lock);

    /* Try to find the VAD parent */
    Result = MiAvlFindNodeOrParent(&VadList->VadRoot, Vpn, &Parent);

    /* Check if we found a parent and if the VAD fits into the tree */
    if (((Result == TableInsertAsLeft) && (Vad->EndingVpn < Parent->StartingVpn)) ||
        ((Result == TableInsertAsRight) && (Vad->StartingVpn > Parent->EndingVpn)))
    {
        /* The VAD fits, so insert it */
        MiAvlInsertNode(&VadList->VadRoot, Parent, &Vad->Node, Result);
        Status = STATUS_SUCCESS;
    }
    else
    {
        /* The VAD overlap with the parent */
        Status = STATUS_UNSUCCESSFUL;
    }

    /* Unlock the VAD list */
    KeReleaseGuardedMutex(&VadList->Lock);

    return Status;
}

// checkme: possible to commit over 2 adjacent reserves?
NTSTATUS
NTAPI
MmAllocateVirtualMemory(
    PVOID BaseAddress,
    SIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protection
    ...)
{
    PMIVADLIST VadList;
    PMIVAD Vad;

    // Verify flags (ASSERT)


    if (MiIsSessionSpaceAddress(BaseAddress)
        VadList = MiSessionVadList;
    if (MiIsGlobalSystemAddress(BaseAddress)
        VadList = MiSystemVadList;
    else
        VadList = MiProcessVadList;

    if (AllocationType & MEM_RESERVE)
    {
        Vad = MiAllocateVad(VadList);

        if (!Vad)
        {
            return STATUS_UNSUCCESSFUL;
        }

        /* Initialize the VAD */
        Vad->... = bla

        Status = MiInsertVad(VadList, Vad);
        if (!NT_SUCCESS(Status))
        {
            MiFreeVad(Vad);
            return Status;
        }
    }
    else
    {
        // Search for existing VAD
        Vad = MiFindVad(VadList, ...);

        if (!Vad)
        {
            return STATUS_UNSUCCESSFUL;
        }
    }

    if (AllocationType & MEM_COMMIT)
    {
        StartVpe = MiAddressToVpe(BaseAddress);


        // commit and map the hyper space pages required for the WS list entries
        MiCommitPages(HyperVad, StartVpe, PageCount * sizeof(MMVPNENTRY), MEM_MAPPED)

        // lock the vad
        // loop the requested pages
            // initialize the PTE (make it a demand zero PTE or demand anything (for kernel))

        // unlock the vad
    }


}



#endif

