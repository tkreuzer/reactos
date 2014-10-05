/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         BSD - See COPYING.ARM in the top level directory
 * FILE:            ntoskrnl/mm/ARM3/commitment.c
 * PURPOSE:         Page commitment limits
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES *******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

#define MODULE_INVOLVED_IN_ARM3
#include "../ARM3/miarm.h"
#include <ntintsafe.h>

/* GLOBALS ********************************************************************/

ULONG_PTR MmTotalCommitLimit;

/* Pages reserved for system use */
ULONG_PTR MmSystemCommitReserve = 0x500;

/* Systemwide total of committed pages */
ULONG_PTR MmTotalCommittedPages;

/* Maximum value seen for MmTotalCommittedPages */
ULONG_PTR MmPeakCommitment;

SIZE_T MmSharedCommit;
SIZE_T MmDriverCommit;
SIZE_T MmProcessCommit;
SIZE_T MmPagedPoolCommit;
SIZE_T MmtotalCommitLimitMaximum;

/*

Needs to be called whenever a range of virtual memory is being committed or
when physical pages are being used from anywhere, except the page fault handler
- MiAllocatePfn
- MiRemoveAnyPage
    - MiAllocatePfn
    - MiAllocatePoolPages
    - MmAllocateSpecialPool
    + MmCreateKernelStack
    + MmGrowKernelStackEx
    + MmCreateProcessAddressSpace
    MiSessionInitializeWorkingSetList
    MiSessionCreateInternal
    MiAllocatePagesForMdl
- MiRemoveZeroPage
    MiBuildPagedPool
    MiInitializeAndChargePfn
    MmCreateProcessAddressSpace
    MmAllocPage

    Whenever a physical page is allocated this is either done on behalf of the
    page fault handler, which must already have the pages being charged for or
    on behalf of other functions that allocate pages for previously uncharged
    virtual memory. To make sure all pages we allocate have been paid for,
    there is a debug mechanism, to keep track of page charges.

*/

#ifdef _WIN64
#define InterlockedCompareExchangeSizeT(a, b, c) \
    ((SIZE_T)InterlockedCompareExchange64((PLONG64)(a), b, c))
#else
#define InterlockedCompareExchangeSizeT(a, b, c) \
    ((SIZE_T)InterlockedCompareExchange((PLONG)(a), b, c))
#endif // _WIN64

ULONG_PTR
NTAPI
MiCalculatePageTableCharge(
    _In_ PVOID StartingVa,
    _In_ SIZE_T NumberOfBytes)
{
    ULONG_PTR CommitCharge = 0;
    PVOID EndingVa;

    EndingVa = (PUCHAR)StartingVa + NumberOfBytes - 1;
#if MI_PAGING_LEVELS >= 4
    CommitCharge += MiAddressToPxe(EndingVa) - MiAddressToPxe(StartingVa) + 1;
#endif
#if MI_PAGING_LEVELS >= 3
    CommitCharge += MiAddressToPpe(EndingVa) - MiAddressToPpe(StartingVa) + 1;
#endif
    CommitCharge += MiAddressToPde(EndingVa) - MiAddressToPde(StartingVa) + 1;

    return CommitCharge;
}

ULONG_PTR
NTAPI
MiCalculateMaxPageTableCharge(
    _In_ SIZE_T SizeInBytes)
{
    ULONG_PTR CommitCharge = 0;

#if MI_PAGING_LEVELS >= 4
    CommitCharge += MiAddressToPxe((PVOID)SizeInBytes) - MiAddressToPxe(0) + 2;
#endif
#if MI_PAGING_LEVELS >= 3
    CommitCharge += MiAddressToPpe((PVOID)SizeInBytes) - MiAddressToPpe(0) + 2;
#endif
    CommitCharge += MiAddressToPde((PVOID)SizeInBytes) - MiAddressToPde(0) + 2;

    return CommitCharge;
}

BOOLEAN
NTAPI
MiChargeCommitment(
    _In_ ULONG_PTR NumberOfPages)
{
    ULONG_PTR MaximumCommittedPages;
    ULONG_PTR TotalCommittedPages, Compare;
    NTSTATUS Status;

    ASSERT(MmTotalCommitLimit != 0);

    /* Calculate the maximum pages that we can commit */
    MaximumCommittedPages = MmTotalCommitLimit - MmSystemCommitReserve;

    /* Get the current commitment */
    TotalCommittedPages = MmTotalCommittedPages;

    /* Enter the exchange loop */
    do
    {
        /* Save the current value for comparison */
        Compare = TotalCommittedPages;

        /* Calculate new total page commitment */
        Status = RtlULongPtrAdd(TotalCommittedPages,
                                NumberOfPages,
                                &TotalCommittedPages);

        /* Check for overflow or if the new size is too large */
        if (!NT_SUCCESS(Status) ||
            (TotalCommittedPages > MaximumCommittedPages))
        {
            DPRINT1("MM: Page commitment of %lu pages exceeds limit of %lu\n",
                    NumberOfPages, MaximumCommittedPages);
            return FALSE;
        }

        /* Do the exchange */
        TotalCommittedPages = InterlockedCompareExchangeSizeT(&MmTotalCommittedPages,
                                                              TotalCommittedPages,
                                                              Compare);

        /* Repeat if exchange did not succeed */
    } while (TotalCommittedPages != Compare);

    /* Update peak commitment for statistics */
    MmPeakCommitment = max(MmPeakCommitment, TotalCommittedPages + NumberOfPages);

    /* Success! */
    return TRUE;
}


VOID
NTAPI
MiReturnCommitment(
    _In_ ULONG_PTR NumberOfPages)
{
    LONG_PTR NewLimit;

    ASSERT((LONG_PTR)NumberOfPages >= 0);
    NewLimit = InterlockedExchangeAddSizeT(&MmTotalCommittedPages,
                                           -(LONG_PTR)NumberOfPages);
    ASSERT(NewLimit >= 0);
}

