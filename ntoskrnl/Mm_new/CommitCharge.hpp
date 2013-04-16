
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

