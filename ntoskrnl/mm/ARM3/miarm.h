/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         BSD - See COPYING.ARM in the top level directory
 * FILE:            ntoskrnl/mm/ARM3/miarm.h
 * PURPOSE:         ARM Memory Manager Header
 * PROGRAMMERS:     ReactOS Portable Systems Group
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Make the code cleaner with some definitions for size multiples */
#define _1KB (1024u)
#define _1MB (1024 * _1KB)
#define _1GB (1024 * _1MB)

/* Everyone loves 64K */
#define _64K (64 * _1KB)

/* Size of a page table */
#define PT_SIZE  (PTE_PER_PAGE * sizeof(MMPTE))

/* Size of a page directory */
#define PD_SIZE  (PDE_PER_PAGE * sizeof(MMPDE))

/* Size of all page directories for a process */
#define SYSTEM_PD_SIZE (PPE_PER_PAGE * PD_SIZE)
#ifdef _M_IX86
C_ASSERT(SYSTEM_PD_SIZE == PAGE_SIZE);
#endif

#define PAGED_POOL_MASK                     1
#define MUST_SUCCEED_POOL_MASK              2
#define CACHE_ALIGNED_POOL_MASK             4
#define QUOTA_POOL_MASK                     8
#define SESSION_POOL_MASK                   32
#define VERIFIER_POOL_MASK                  64


//
// FIXFIX: These should go in ex.h after the pool merge
//
#ifdef _WIN64
#define POOL_BLOCK_SIZE 16
#else
#define POOL_BLOCK_SIZE  8
#endif
#define POOL_LISTS_PER_PAGE (PAGE_SIZE / POOL_BLOCK_SIZE)
#define BASE_POOL_TYPE_MASK 1
#define POOL_MAX_ALLOC (PAGE_SIZE - (sizeof(POOL_HEADER) + POOL_BLOCK_SIZE))

//
// Pool debugging/analysis/tracing flags
//
#define POOL_FLAG_CHECK_TIMERS 0x1
#define POOL_FLAG_CHECK_WORKERS 0x2
#define POOL_FLAG_CHECK_RESOURCES 0x4
#define POOL_FLAG_VERIFIER 0x8
#define POOL_FLAG_CHECK_DEADLOCK 0x10
#define POOL_FLAG_SPECIAL_POOL 0x20
#define POOL_FLAG_DBGPRINT_ON_FAILURE 0x40
#define POOL_FLAG_CRASH_ON_FAILURE 0x80

//
// BAD_POOL_HEADER codes during pool bugcheck
//
#define POOL_CORRUPTED_LIST 3
#define POOL_SIZE_OR_INDEX_MISMATCH 5
#define POOL_ENTRIES_NOT_ALIGNED_PREVIOUS 6
#define POOL_HEADER_NOT_ALIGNED 7
#define POOL_HEADER_IS_ZERO 8
#define POOL_ENTRIES_NOT_ALIGNED_NEXT 9
#define POOL_ENTRY_NOT_FOUND 10

//
// BAD_POOL_CALLER codes during pool bugcheck
//
#define POOL_ENTRY_CORRUPTED 1
#define POOL_ENTRY_ALREADY_FREE 6
#define POOL_ENTRY_NOT_ALLOCATED 7
#define POOL_ALLOC_IRQL_INVALID 8
#define POOL_FREE_IRQL_INVALID 9
#define POOL_BILLED_PROCESS_INVALID 13
#define POOL_HEADER_SIZE_INVALID 32

typedef struct _POOL_DESCRIPTOR
{
    POOL_TYPE PoolType;
    ULONG PoolIndex;
    ULONG RunningAllocs;
    ULONG RunningDeAllocs;
    ULONG TotalPages;
    ULONG TotalBigPages;
    ULONG Threshold;
    PVOID LockAddress;
    PVOID PendingFrees;
    LONG PendingFreeDepth;
    SIZE_T TotalBytes;
    SIZE_T Spare0;
    LIST_ENTRY ListHeads[POOL_LISTS_PER_PAGE];
} POOL_DESCRIPTOR, *PPOOL_DESCRIPTOR;

typedef struct _POOL_HEADER
{
    union
    {
        struct
        {
#ifdef _WIN64
            USHORT PreviousSize:8;
            USHORT PoolIndex:8;
            USHORT BlockSize:8;
            USHORT PoolType:8;
#else
            USHORT PreviousSize:9;
            USHORT PoolIndex:7;
            USHORT BlockSize:9;
            USHORT PoolType:7;
#endif
        };
        ULONG Ulong1;
    };
#ifdef _WIN64
    ULONG PoolTag;
#endif
    union
    {
#ifdef _WIN64
        PEPROCESS ProcessBilled;
#else
        ULONG PoolTag;
#endif
        struct
        {
            USHORT AllocatorBackTraceIndex;
            USHORT PoolTagHash;
        };
    };
} POOL_HEADER, *PPOOL_HEADER;

C_ASSERT(sizeof(POOL_HEADER) == POOL_BLOCK_SIZE);
C_ASSERT(POOL_BLOCK_SIZE == sizeof(LIST_ENTRY));

typedef struct _POOL_TRACKER_TABLE
{
    ULONG Key;
    LONG NonPagedAllocs;
    LONG NonPagedFrees;
    SIZE_T NonPagedBytes;
    LONG PagedAllocs;
    LONG PagedFrees;
    SIZE_T PagedBytes;
} POOL_TRACKER_TABLE, *PPOOL_TRACKER_TABLE;

typedef struct _POOL_TRACKER_BIG_PAGES
{
    PVOID Va;
    ULONG Key;
    ULONG NumberOfPages;
    PVOID QuotaObject;
} POOL_TRACKER_BIG_PAGES, *PPOOL_TRACKER_BIG_PAGES;

extern ULONG ExpNumberOfPagedPools;
extern POOL_DESCRIPTOR NonPagedPoolDescriptor;
extern PPOOL_DESCRIPTOR ExpPagedPoolDescriptor[16 + 1];
extern PPOOL_TRACKER_TABLE PoolTrackTable;

//
// END FIXFIX
//


#if (_MI_PAGING_LEVELS == 2)
FORCEINLINE
BOOLEAN
MiSynchronizeSystemPde(PMMPDE PointerPde)
{
    MMPDE SystemPde;
    ULONG Index;

    /* Get the Index from the PDE */
    Index = ((ULONG_PTR)PointerPde & (SYSTEM_PD_SIZE - 1)) / sizeof(MMPTE);

    /* Copy the PDE from the double-mapped system page directory */
    SystemPde = MmSystemPagePtes[Index];
    *PointerPde = SystemPde;

    /* Make sure we re-read the PDE and PTE */
    KeMemoryBarrierWithoutFence();

    /* Return, if we had success */
    return SystemPde.u.Hard.Valid != 0;
}
#endif

#if _MI_PAGING_LEVELS == 2
FORCEINLINE
USHORT
MiIncrementPageTableReferences(IN PVOID Address)
{
    PUSHORT RefCount;

    RefCount = &MmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)];

    *RefCount += 1;
    ASSERT(*RefCount <= PTE_PER_PAGE);
    return *RefCount;
}

FORCEINLINE
USHORT
MiDecrementPageTableReferences(IN PVOID Address)
{
    PUSHORT RefCount;

    RefCount = &MmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)];

    *RefCount -= 1;
    ASSERT(*RefCount < PTE_PER_PAGE);
    return *RefCount;
}
#else
FORCEINLINE
USHORT
MiIncrementPageTableReferences(IN PVOID Address)
{
    PMMPDE PointerPde = MiAddressToPde(Address);
    PMMPFN Pfn;

    /* We should not tinker with this one. */
    ASSERT(PointerPde != (PMMPDE)PXE_SELFMAP);
    DPRINT("Incrementing %p from %p\n", Address, _ReturnAddress());

    /* Make sure we're locked */
    ASSERT(PsGetCurrentThread()->OwnsProcessWorkingSetExclusive);

    /* If we're bumping refcount, then it must be valid! */
    ASSERT(PointerPde->u.Hard.Valid == 1);

    /* This lies on the PFN */
    Pfn = MiGetPfnEntry(PFN_FROM_PDE(PointerPde));
    Pfn->OriginalPte.u.Soft.UsedPageTableEntries++;

    ASSERT(Pfn->OriginalPte.u.Soft.UsedPageTableEntries <= PTE_PER_PAGE);

    return Pfn->OriginalPte.u.Soft.UsedPageTableEntries;
}

FORCEINLINE
USHORT
MiDecrementPageTableReferences(IN PVOID Address)
{
    PMMPDE PointerPde = MiAddressToPde(Address);
    PMMPFN Pfn;

    /* We should not tinker with this one. */
    ASSERT(PointerPde != (PMMPDE)PXE_SELFMAP);

    DPRINT("Decrementing %p from %p\n", PointerPde, _ReturnAddress());

    /* Make sure we're locked */
    ASSERT(PsGetCurrentThread()->OwnsProcessWorkingSetExclusive);

    /* If we're decreasing refcount, then it must be valid! */
    ASSERT(PointerPde->u.Hard.Valid == 1);

    /* This lies on the PFN */
    Pfn = MiGetPfnEntry(PFN_FROM_PDE(PointerPde));

    ASSERT(Pfn->OriginalPte.u.Soft.UsedPageTableEntries != 0);
    Pfn->OriginalPte.u.Soft.UsedPageTableEntries--;

    ASSERT(Pfn->OriginalPte.u.Soft.UsedPageTableEntries < PTE_PER_PAGE);

    return Pfn->OriginalPte.u.Soft.UsedPageTableEntries;
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif

FORCEINLINE
VOID
MiDeletePde(
    _In_ PMMPDE PointerPde,
    _In_ PEPROCESS CurrentProcess)
{
    /* Only for user-mode ones */
    ASSERT(MiIsUserPde(PointerPde));

    /* Kill this one as a PTE */
    MiDeletePte((PMMPTE)PointerPde, MiPdeToPte(PointerPde), CurrentProcess, NULL);
#if _MI_PAGING_LEVELS >= 3
    /* Cascade down */
    if (MiDecrementPageTableReferences(MiPdeToPte(PointerPde)) == 0)
    {
        MiDeletePte(MiPdeToPpe(PointerPde), PointerPde, CurrentProcess, NULL);
#if _MI_PAGING_LEVELS == 4
        if (MiDecrementPageTableReferences(PointerPde) == 0)
        {
            MiDeletePte(MiPdeToPxe(PointerPde), MiPdeToPpe(PointerPde), CurrentProcess, NULL);
        }
#endif
    }
#endif
}

/* EOF */
