/*!

    \file MmData.cpp

    \brief Global data

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include "MmData.hpp"
#include _ARCH_RELATIVE_(MachineDependent.hpp)

extern "C" {

BOOLEAN Mm64BitPhysicalAddress = TRUE;
PVOID MmSystemRangeStart = (PVOID)SYSTEM_RANGE_START;
ULONG_PTR MmUserProbeAddress = USER_PROBE_ADDRESS;
PVOID MmHighestUserAddress = (PVOID)HIGHEST_USER_ADDRESS;

/* For cmdata.c */
BOOLEAN MmLargeSystemCache;
BOOLEAN MmZeroPageFile;
BOOLEAN MmProtectFreedNonPagedPool;
BOOLEAN MmTrackLockedPages;
BOOLEAN MmTrackPtes;
BOOLEAN MmDynamicPfn;
BOOLEAN MmMirroring;
BOOLEAN MmMakeLowMemory;
BOOLEAN MmEnforceWriteProtection;
SIZE_T MmAllocationFragment;
ULONG MmConsumedPoolPercentage;
ULONG MmVerifyDriverBufferType;
ULONG MmVerifyDriverLevel;
WCHAR MmVerifyDriverBuffer[512];
ULONG MmVerifyDriverBufferLength;
SIZE_T MmSizeOfNonPagedPoolInBytes;
SIZE_T MmMaximumNonPagedPoolInBytes;
SIZE_T MmSizeOfPagedPoolInBytes;
ULONG MmSecondaryColors;
ULONG MmNumberOfSystemPtes;
ULONG MmProductType;
PFN_NUMBER MmLowMemoryThreshold;
PFN_NUMBER MmHighMemoryThreshold;
UCHAR MmDisablePagingExecutive;

// HACK
#define MM_PAGED_POOL_INFO ULONG
#define MMSUPPORT ULONG
#define MM_DRIVER_VERIFIER_DATA ULONG
#define MMPFNLIST ULONG

/* For kddata.c */
struct _PHYSICAL_MEMORY_DESCRIPTOR* MmPhysicalMemoryBlock;
struct _MMPTE* MmSystemPtesStart[2];
struct _MMPTE* MmSystemPtesEnd[2];
MM_PAGED_POOL_INFO MmPagedPoolInfo;
PVOID MmSystemCacheStart;
PVOID MmSystemCacheEnd;
MMSUPPORT MmSystemCacheWs;
SIZE_T MmAllocatedNonPagedPool;
ULONG MmSpecialPoolTag;
ULONG_PTR MmSubsectionBase;
PFN_NUMBER MmResidentAvailablePages;
ULONG MmNumberOfPagingFiles;
PVOID MmUnloadedDrivers;
PVOID MmLastUnloadedDrivers;
PVOID MmTriageActionTaken;
PVOID KernelVerifier;
MM_DRIVER_VERIFIER_DATA MmVerifierData;
SIZE_T MmSharedCommit;
SIZE_T MmDriverCommit;
SIZE_T MmProcessCommit;
SIZE_T MmPagedPoolCommit;
//SIZE_T MmPeakCommitment;
MMPFNLIST MmZeroedPageListHead;
MMPFNLIST MmFreePageListHead;
MMPFNLIST MmStandbyPageListHead;
MMPFNLIST MmModifiedPageListHead;
MMPFNLIST MmModifiedNoWritePageListHead;
//SIZE_T MmMaximumNonPagedPoolInBytes;
PVOID MmNonPagedSystemStart;
PVOID MmNonPagedPoolStart;
PVOID MmNonPagedPoolEnd;
PVOID MmPagedPoolStart;
PVOID MmPagedPoolEnd;
PVOID MmSessionBase;
SIZE_T MmSessionSize;
struct _MMPFN* MmPfnDatabase;
SIZE_T MmSizeOfPfnDatabase;
PFN_NUMBER MmNumberOfPhysicalPages;
PFN_NUMBER MmLowestPhysicalPage;
PFN_NUMBER MmHighestPhysicalPage;
PFN_NUMBER MmAvailablePages;
PFN_NUMBER MmBadPagesDetected;
LIST_ENTRY MmLoadedUserImageList;

SIZE_T MmHeapSegmentCommit;
SIZE_T MmHeapSegmentReserve;
SIZE_T MmHeapDeCommitFreeBlockThreshold;
SIZE_T MmHeapDeCommitTotalFreeThreshold;
SIZE_T MmMinimumStackCommitInBytes;
ULONG MmCritsectTimeoutSeconds;

/* Fr thread.c */
ULONG MmReadClusterSize;

/* For sysinfo.c */
PFN_COUNT MiFreeSwapPages;
PFN_COUNT MiUsedSwapPages;

/* Legacy shit */
typedef struct _MM_MEMORY_CONSUMER
{
    ULONG PagesUsed;
    ULONG PagesTarget;
    NTSTATUS (*Trim)(ULONG Target, ULONG Priority, PULONG NrFreed);
} MM_MEMORY_CONSUMER, *PMM_MEMORY_CONSUMER;
MM_MEMORY_CONSUMER MiMemoryConsumers[3];

/* Shouldn't be here! */
LIST_ENTRY PsLoadedModuleList;
ERESOURCE PsLoadedModuleResource;
ULONG_PTR PsNtosImageBase;

}; // extern "C"
