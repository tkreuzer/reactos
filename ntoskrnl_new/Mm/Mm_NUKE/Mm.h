
typedef enum _MM_COPY_TYPE
{
    MmDebugCopyRead,
    MmDebugCopyWrite,
    MmDebugCopyWriteReadOnly
} MM_COPY_TYPE;

extern PVOID MmHighestUserAddress;
extern ULONG_PTR MmUserProbeAddress;
extern PVOID MmSystemRangeStart;
extern ULONG_PTR MmLowestPhysicalPage;
extern ULONG_PTR MmHighestPhysicalPage;
extern ULONG_PTR MmNumberOfPhysicalPages;
extern ULONG_PTR MmBadPagesDetected;
extern ULONG_PTR MmAvailablePages;
extern ULONG_PTR MmResidentAvailablePages;
extern ULONG_PTR MmZeroedPageListHead;
extern ULONG_PTR MmFreePageListHead;
extern ULONG_PTR MmStandbyPageListHead;
extern ULONG_PTR MmModifiedPageListHead;
extern ULONG_PTR MmModifiedNoWritePageListHead;
extern ULONG_PTR MmNonPagedPoolStart;
extern ULONG_PTR MmNonPagedPoolEnd;
extern ULONG_PTR MmPagedPoolStart;
extern ULONG_PTR MmPagedPoolEnd;
extern ULONG_PTR MmSystemCacheStart;
extern ULONG_PTR MmSystemCacheEnd;
extern ULONG_PTR MmSystemCacheWs;
extern ULONG_PTR MmSystemPtesStart;
extern ULONG_PTR MmSystemPtesEnd;
extern ULONG_PTR MmSubsectionBase;
extern ULONG_PTR MmSessionBase;
extern ULONG_PTR MmSessionSize;
extern ULONG_PTR NonPagedPoolDescriptor;
extern ULONG_PTR MmMaximumNonPagedPoolInBytes;
extern ULONG_PTR MmNonPagedSystemStart;
extern ULONG_PTR MmPagedPoolInformation;
extern ULONG_PTR MmSizeOfPagedPoolInBytes;
extern ULONG_PTR MmAllocatedNonPagedPool;
extern ULONG_PTR MmTotalCommitLimit;
extern ULONG_PTR MmTotalCommittedPages;
extern ULONG_PTR MmSharedCommit;
extern ULONG_PTR MmDriverCommit;
extern ULONG_PTR MmProcessCommit;
extern ULONG_PTR MmPagedPoolCommit;
extern ULONG_PTR MmExtendedCommit;
extern ULONG_PTR MmLoadedUserImageList;
extern ULONG_PTR MmUnloadedDrivers;
extern ULONG_PTR MmLastUnloadedDriver;
extern ULONG_PTR MmTriageActionTaken;
extern ULONG_PTR MmSpecialPoolTag;
extern ULONG_PTR KernelVerifier;
extern ULONG_PTR MmVerifierData;
extern ULONG_PTR MmPeakCommitment;
extern ULONG_PTR MmTotalCommitLimitMaximum;
extern ULONG_PTR MmPhysicalMemoryBlock;
extern ULONG_PTR MmSystemParentTablePage;
extern ULONG_PTR MmVirtualTranslationBase;
extern ULONG_PTR MmZeroedPageSingleBitErrorsDetected;
extern ULONG_PTR MmNumberOfPagingFiles;
extern union _MIPFNENTRY *MmPfnDatabase;
extern struct _MXPTE *MmDebugPte;

VOID
NTAPI
MmInitialize(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock);

BOOLEAN
NTAPI
MmIsAddressValidForRead(
    IN Address);

BOOLEAN
NTAPI
MmIsAddressValidForWrite(
    IN Address);

NTSTATUS
NTAPI
MmDebugCopyMemory(
    IN PVOID Destination,
    IN PVOID Source,
    IN PULONG ByteCount,
    IN MM_COPY_TYPE CopyType);

NTSTATUS
NTAPI
MmDebugCopyPhysicalMemory(
    PVOID VirtualAddress,
    ULONG64 PhysicalAddress,
    ULONG Size,
    BOOLEAN WriteToPhysical);

NTSTATUS
NTAPI
MmMapPhysicalMemoryForHal(
    IN PHYSICAL_ADDRESS PhysicalAddress,
    IN SIZE_T Size,
    IN OUT PVOID *VirtualAddress);

