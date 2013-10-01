/*!

    \file CommitCharge.cpp

    \brief Implements the commit charge/limit related functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "CommitCharge.hpp"
#include "MmData.hpp"

extern "C" {

SIZE_T MmTotalCommittedPages;
SIZE_T MmTotalCommitLimit;
SIZE_T MmtotalCommitLimitMaximum; /// \todo Fix typo
SIZE_T MmPeakCommitment;

};

/*! \fn InitializeSystemCommitLimit
 *
 *  \brief Initialize the system commit limit.
 */
VOID
INIT_FUNCTION
InitializeSystemCommitLimit (
    VOID)
{
    /* Initialize the limit based on physical memory */
    MmTotalCommitLimit = MmNumberOfPhysicalPages;
    MmTotalCommittedPages = MmNumberOfPhysicalPages - MmAvailablePages;
}

/*! \fn ChargeSystemCommit
 *
 *  \brief Increases the number of globally committed pages by the specified
 *      amount, unless it would exceed the system commit limit.
 *
 *  \param [in] NumberOfPages - Number of pages to add to the currently
 *      committed pages.
 *
 *  \return STATUS_SUCCESS on success, STATUS_COMMITMENT_LIMIT if the system
 *      commit limit would be exceeded.
 *
 *  \remarks This function must be called before actually allocating or
 *      committing (writing demand zero PTEs) any pages to make sure that
 *      there will always be sufficient memory to resolve any page faults.
 */
NTSTATUS
ChargeSystemCommit (
    _In_ ULONG_PTR NumberOfPages)
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

/*! \fn UnchargeSystemCommit
 *
 *  \brief Decreases the number of globally committed pages by the specified
 *      amount.
 *
 *  \param [in] NumberOfPages - Number of pages to subtract from the currently
 *      committed pages.
 *
 *  \remarks Calling this function must not decrease the number of committed
 *      pages below 0. It can only be used after a previous call to
 *      ChargeSystemCommit.
 */
VOID
UnchargeSystemCommit (
    _In_ ULONG_PTR NumberOfPages)
{
    NT_ASSERT(MmTotalCommittedPages > NumberOfPages);
    InterlockedExchangeAddSizeT(&MmTotalCommittedPages, -(LONG_PTR)NumberOfPages);
}


