
#include <ntoskrnl.h>
#include "Mm_internal.h"

PVOID MmHighestUserAddress;
ULONG_PTR MmUserProbeAddress;
PVOID MmSystemRangeStart = (PVOID)MX_SYSTEM_RANGE_START;

ULONG_PTR MmLowestPhysicalPage;
ULONG_PTR MmHighestPhysicalPage;
ULONG_PTR MmNumberOfPhysicalPages;
ULONG_PTR MmBadPagesDetected;
ULONG_PTR MmAvailablePages;
ULONG_PTR MmResidentAvailablePages;

ULONG_PTR MmZeroedPageListHead;
ULONG_PTR MmFreePageListHead;
ULONG_PTR MmStandbyPageListHead;
ULONG_PTR MmModifiedPageListHead;
ULONG_PTR MmModifiedNoWritePageListHead;

ULONG_PTR MmNonPagedPoolStart;
ULONG_PTR MmNonPagedPoolEnd;
ULONG_PTR MmPagedPoolStart;
ULONG_PTR MmPagedPoolEnd;
ULONG_PTR MmSystemCacheStart;
ULONG_PTR MmSystemCacheEnd;
ULONG_PTR MmSystemCacheWs;
ULONG_PTR MmSystemPtesStart;
ULONG_PTR MmSystemPtesEnd;
ULONG_PTR MmSubsectionBase;
ULONG_PTR MmSessionBase;
ULONG_PTR MmSessionSize;

ULONG_PTR NonPagedPoolDescriptor;
ULONG_PTR MmMaximumNonPagedPoolInBytes;
ULONG_PTR MmNonPagedSystemStart;
ULONG_PTR MmPagedPoolInformation;
ULONG_PTR MmSizeOfPagedPoolInBytes;
ULONG_PTR MmAllocatedNonPagedPool;


ULONG_PTR MmTotalCommitLimit;
ULONG_PTR MmTotalCommittedPages;
ULONG_PTR MmSharedCommit;
ULONG_PTR MmDriverCommit;
ULONG_PTR MmProcessCommit;
ULONG_PTR MmPagedPoolCommit;
ULONG_PTR MmExtendedCommit;

ULONG_PTR MmLoadedUserImageList;
ULONG_PTR MmUnloadedDrivers;
ULONG_PTR MmLastUnloadedDriver;
ULONG_PTR MmTriageActionTaken;
ULONG_PTR MmSpecialPoolTag;
ULONG_PTR KernelVerifier;
ULONG_PTR MmVerifierData;
ULONG_PTR MmPeakCommitment;
ULONG_PTR MmTotalCommitLimitMaximum;
ULONG_PTR MmPhysicalMemoryBlock;
ULONG_PTR MmSystemParentTablePage;
ULONG_PTR MmVirtualTranslationBase;
ULONG_PTR MmZeroedPageSingleBitErrorsDetected;
ULONG_PTR MmNumberOfPagingFiles;
