/*!

    \file CommitCharge.hpp

    \brief Header for CommitCharge.cpp

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"

extern "C" SIZE_T MmTotalCommitLimit;
extern "C" SIZE_T MmTotalCommitLimitMaximum;
extern "C" SIZE_T MmTotalCommittedPages;
extern "C" SIZE_T MmPeakCommitment;


VOID
InitializeSystemCommitLimit (
    VOID);

NTSTATUS
ChargeSystemCommit (
    ULONG_PTR NumberOfPages);

VOID
UnchargeSystemCommit (
    ULONG_PTR NumberOfPages);

