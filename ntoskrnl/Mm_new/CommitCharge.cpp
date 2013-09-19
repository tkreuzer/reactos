

#include "CommitCharge.hpp"

extern "C" ULONG_PTR MmNumberOfPhysicalPages;
extern "C" ULONG_PTR MmAvailablePages;

extern "C" {

SIZE_T MmTotalCommittedPages;
SIZE_T MmTotalCommitLimit;
SIZE_T MmtotalCommitLimitMaximum; /// \todo Fix typo
SIZE_T MmPeakCommitment;

};

VOID
INIT_FUNCTION
InitializeSystemCommitLimit (
    VOID)
{
    /* Initialize the limit based on physical memory */
    MmTotalCommitLimit = MmNumberOfPhysicalPages;
    MmTotalCommittedPages = MmNumberOfPhysicalPages - MmAvailablePages;
}


NTSTATUS
ChargeSystemCommit (
    ULONG_PTR NumberOfPages)
{
    ULONG_PTR CurrentCommit, NewCommit, ExpectedOldCommit;

    /* Start with the current commit */
    CurrentCommit = MmTotalCommittedPages;

    do
    {
        /* Calculate the new commit charge */
        NewCommit = CurrentCommit + NumberOfPages;

        /* Check if that overflows or exceeds the limit */
        if ((NewCommit < CurrentCommit) ||
            (NewCommit > MmTotalCommitLimit))
        {
            return STATUS_COMMITMENT_LIMIT;
        }

        /* Try to exchange */
        ExpectedOldCommit = CurrentCommit;
        CurrentCommit = InterlockedCompareExchangeSizeT(&MmTotalCommittedPages,
                                                        NewCommit,
                                                        ExpectedOldCommit);
    }
    while (CurrentCommit != ExpectedOldCommit);

    /* Update the peak commitment */
    if (MmTotalCommittedPages > MmPeakCommitment)
        MmPeakCommitment = MmTotalCommittedPages;

    return STATUS_SUCCESS;
}

VOID
UnchargeSystemCommit (
    ULONG_PTR NumberOfPages)
{
    InterlockedExchangeAddSizeT(&MmTotalCommittedPages, -(LONG_PTR)NumberOfPages);
}


