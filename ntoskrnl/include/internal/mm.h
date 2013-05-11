#pragma once

#include <internal/arch/mm.h>

/* CONSTANTS *****************************************************************/

/* Although Microsoft says this isn't hardcoded anymore,
   they won't be able to change it. Stuff depends on it */
#define MM_VIRTMEM_GRANULARITY              (64 * 1024)


#ifdef __cplusplus
extern "C" {
#endif

/* TYPES *********************************************************************/

typedef struct _MM_PAGED_POOL_INFO
{
    PRTL_BITMAP PagedPoolAllocationMap;
    PRTL_BITMAP EndOfPagedPoolBitmap;
    PMMPTE FirstPteForPagedPool;
    PMMPTE LastPteForPagedPool;
    PMMPDE NextPdeForPagedPoolExpansion;
    ULONG PagedPoolHint;
    SIZE_T PagedPoolCommit;
    SIZE_T AllocatedPagedPool;
} MM_PAGED_POOL_INFO, *PMM_PAGED_POOL_INFO;


/* GLOBALS *******************************************************************/

extern PFN_COUNT MiFreeSwapPages;
extern PFN_COUNT MiUsedSwapPages;
extern PFN_COUNT MmNumberOfPhysicalPages;
extern UCHAR MmDisablePagingExecutive;
extern PFN_NUMBER MmLowestPhysicalPage;
extern PFN_NUMBER MmHighestPhysicalPage;
extern PFN_NUMBER MmAvailablePages;
extern PFN_NUMBER MmResidentAvailablePages;
extern ULONG MmThrottleTop;
extern ULONG MmThrottleBottom;

extern LIST_ENTRY MmLoadedUserImageList;
extern ULONG MmNumberOfPagingFiles;
extern SIZE_T MmTotalNonPagedPoolQuota;
extern SIZE_T MmTotalPagedPoolQuota;

extern PVOID MmUnloadedDrivers;
extern PVOID MmLastUnloadedDrivers;
extern PVOID MmTriageActionTaken;
extern PVOID KernelVerifier;
extern MM_DRIVER_VERIFIER_DATA MmVerifierData;
extern SIZE_T MmTotalCommitLimit;
extern SIZE_T MmTotalCommittedPages;
extern SIZE_T MmSharedCommit;
extern SIZE_T MmDriverCommit;
extern SIZE_T MmProcessCommit;
extern SIZE_T MmPagedPoolCommit;
extern SIZE_T MmPeakCommitment;
extern SIZE_T MmtotalCommitLimitMaximum;
extern BOOLEAN MmLargeSystemCache;
extern BOOLEAN MmZeroPageFile;
extern BOOLEAN MmProtectFreedNonPagedPool;
extern BOOLEAN MmTrackLockedPages;
extern BOOLEAN MmTrackPtes;
extern BOOLEAN MmDynamicPfn;
extern BOOLEAN MmMirroring;
extern BOOLEAN MmMakeLowMemory;
extern BOOLEAN MmEnforceWriteProtection;
extern SIZE_T MmAllocationFragment;
extern ULONG MmConsumedPoolPercentage;
extern ULONG MmVerifyDriverBufferType;
extern ULONG MmVerifyDriverLevel;
extern WCHAR MmVerifyDriverBuffer[512];
extern ULONG MmVerifyDriverBufferLength;
extern SIZE_T MmSizeOfNonPagedPoolInBytes;
extern SIZE_T MmMaximumNonPagedPoolInBytes;
extern PFN_NUMBER MmMaximumNonPagedPoolInPages;
extern PFN_NUMBER MmSizeOfPagedPoolInPages;
extern PVOID MmNonPagedSystemStart;
extern PVOID MmNonPagedPoolStart;
extern PVOID MmNonPagedPoolEnd;
extern SIZE_T MmSizeOfPagedPoolInBytes;
extern PVOID MmPagedPoolStart;
extern PVOID MmPagedPoolEnd;
extern PVOID MmSessionBase;
extern SIZE_T MmSessionSize;
extern struct _PHYSICAL_MEMORY_DESCRIPTOR* MmPhysicalMemoryBlock;
extern PMMPTE MmSystemPtesStart[];
extern PMMPTE MmSystemPtesEnd[];
extern MM_PAGED_POOL_INFO MmPagedPoolInfo;
extern PVOID MmSystemCacheStart;
extern PVOID MmSystemCacheEnd;
extern MMSUPPORT MmSystemCacheWs;
extern SIZE_T MmAllocatedNonPagedPool;
extern ULONG MmSpecialPoolTag;
extern ULONG MmSecondaryColors;
extern ULONG MmNumberOfSystemPtes;
extern PFN_NUMBER MmLowMemoryThreshold;
extern PFN_NUMBER MmHighMemoryThreshold;
extern ULONG_PTR MmSubsectionBase;
extern struct _MMPFN* MmPfnDatabase;

typedef struct _MMPFNLIST
{
    PFN_NUMBER Total;
    MMLISTS ListName;
    PFN_NUMBER Flink;
    PFN_NUMBER Blink;
} MMPFNLIST, *PMMPFNLIST;

extern MMPFNLIST MmZeroedPageListHead;
extern MMPFNLIST MmFreePageListHead;
extern MMPFNLIST MmStandbyPageListHead;
extern MMPFNLIST MmModifiedPageListHead;
extern MMPFNLIST MmModifiedNoWritePageListHead;

typedef struct _MM_MEMORY_CONSUMER
{
    ULONG PagesUsed;
    ULONG PagesTarget;
    NTSTATUS (*Trim)(ULONG Target, ULONG Priority, PULONG NrFreed);
} MM_MEMORY_CONSUMER, *PMM_MEMORY_CONSUMER;

#define MC_CACHE                            (0)
#define MC_USER                             (1)
#define MC_SYSTEM                           (2)
#define MC_MAXIMUM                          (3)

extern MM_MEMORY_CONSUMER MiMemoryConsumers[];


/* MmDbgCopyMemory Flags */
#define MMDBG_COPY_WRITE            0x00000001
#define MMDBG_COPY_PHYSICAL         0x00000002
#define MMDBG_COPY_UNSAFE           0x00000004
#define MMDBG_COPY_CACHED           0x00000008
#define MMDBG_COPY_UNCACHED         0x00000010
#define MMDBG_COPY_WRITE_COMBINED   0x00000020

/* Maximum chunk size per copy */
#define MMDBG_COPY_MAX_SIZE         0x8

#ifdef _M_IX86
VOID
NTAPI
MmSetPageProtect(
    struct _EPROCESS* Process,
    PVOID Address,
    ULONG flProtect
);
#endif

/* Mm copy support for Kd */
NTSTATUS
NTAPI
MmDbgCopyMemory(
    IN ULONG64 Address,
    IN PVOID Buffer,
    IN ULONG Size,
    IN ULONG Flags
);

BOOLEAN
NTAPI
MmArmInitSystem(
    IN ULONG Phase,
    IN PLOADER_PARAMETER_BLOCK LoaderBlock
);

//
// Determines if a given address is a session address
//
BOOLEAN
NTAPI
MmIsSessionAddress(
    IN PVOID Address
);

ULONG
NTAPI
MmGetSessionId(
    IN PEPROCESS Process
);


/* npool.c *******************************************************************/

PVOID
NTAPI
MiAllocatePoolPages(
    IN POOL_TYPE PoolType,
    IN SIZE_T SizeInBytes
);

POOL_TYPE
NTAPI
MmDeterminePoolType(
    IN PVOID VirtualAddress
);

ULONG
NTAPI
MiFreePoolPages(
    IN PVOID StartingAddress
);


_Requires_lock_held_(PspQuotaLock)
VOID
NTAPI
MmReturnPoolQuota(
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T QuotaToReturn
);

/* mdl.c *********************************************************************/

VOID
NTAPI
MmBuildMdlFromPages(
    PMDL Mdl,
    PPFN_NUMBER Pages
);

/* mminit.c ******************************************************************/

CODE_SEG("INIT")
BOOLEAN
NTAPI
MmInitSystem(IN ULONG Phase,
             IN PLOADER_PARAMETER_BLOCK LoaderBlock);


/* pagefile.c ****************************************************************/

BOOLEAN
NTAPI
MmIsFileObjectAPagingFile(PFILE_OBJECT FileObject);


/* process.c ****************************************************************/

NTSTATUS
NTAPI
MmInitializeProcessAddressSpace(
    IN PEPROCESS Process,
    IN PEPROCESS Clone OPTIONAL,
    IN PVOID Section OPTIONAL,
    IN OUT PULONG Flags,
    IN POBJECT_NAME_INFORMATION *AuditName OPTIONAL
);

NTSTATUS
NTAPI
MmCreatePeb(
    IN PEPROCESS Process,
    IN PINITIAL_PEB InitialPeb,
    OUT PPEB *BasePeb
);

NTSTATUS
NTAPI
MmCreateTeb(
    IN PEPROCESS Process,
    IN PCLIENT_ID ClientId,
    IN PINITIAL_TEB InitialTeb,
    OUT PTEB* BaseTeb
);

VOID
NTAPI
MmDeleteTeb(
    struct _EPROCESS *Process,
    PTEB Teb
);

VOID
NTAPI
MmCleanProcessAddressSpace(IN PEPROCESS Process);

VOID
NTAPI
MmDeleteProcessAddressSpace(IN PEPROCESS Process);

ULONG
NTAPI
MmGetSessionLocaleId(VOID);

UCHAR
NTAPI
MmSetMemoryPriorityProcess(
    IN PEPROCESS Process,
    IN UCHAR MemoryPriority
);


/* special.c *****************************************************************/

VOID
NTAPI
MiInitializeSpecialPool(VOID);

BOOLEAN
NTAPI
MmUseSpecialPool(
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag);

BOOLEAN
NTAPI
MmIsSpecialPoolAddress(
    IN PVOID P);

BOOLEAN
NTAPI
MmIsSpecialPoolAddressFree(
    IN PVOID P);

PVOID
NTAPI
MmAllocateSpecialPool(
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag,
    IN POOL_TYPE PoolType,
    IN ULONG SpecialType);

VOID
NTAPI
MmFreeSpecialPool(
    IN PVOID P);

/* mm.c **********************************************************************/

NTSTATUS
NTAPI
MmAccessFault(
    IN ULONG FaultCode,
    IN PVOID Address,
    IN KPROCESSOR_MODE Mode,
    IN PVOID TrapInformation
);


/* process.c *****************************************************************/

PVOID
NTAPI
MmCreateKernelStack(BOOLEAN GuiStack, UCHAR Node);

VOID
NTAPI
MmDeleteKernelStack(PVOID Stack,
                    BOOLEAN GuiStack);


/* freelist.c **********************************************************/
_IRQL_raises_(DISPATCH_LEVEL)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_not_held_(MmPfnLock)
_Acquires_lock_(MmPfnLock)
_IRQL_saves_
FORCEINLINE
KIRQL
MiAcquirePfnLock(VOID)
{
    return KeAcquireQueuedSpinLock(LockQueuePfnLock);
}

_Requires_lock_held_(MmPfnLock)
_Releases_lock_(MmPfnLock)
_IRQL_requires_(DISPATCH_LEVEL)
FORCEINLINE
VOID
MiReleasePfnLock(
    _In_ _IRQL_restores_ KIRQL OldIrql)
{
    KeReleaseQueuedSpinLock(LockQueuePfnLock, OldIrql);
}

_IRQL_requires_min_(DISPATCH_LEVEL)
_Requires_lock_not_held_(MmPfnLock)
_Acquires_lock_(MmPfnLock)
FORCEINLINE
VOID
MiAcquirePfnLockAtDpcLevel(VOID)
{
    PKSPIN_LOCK_QUEUE LockQueue;

    ASSERT(KeGetCurrentIrql() >= DISPATCH_LEVEL);
    LockQueue = &KeGetCurrentPrcb()->LockQueue[LockQueuePfnLock];
    KeAcquireQueuedSpinLockAtDpcLevel(LockQueue);
}

_Requires_lock_held_(MmPfnLock)
_Releases_lock_(MmPfnLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
FORCEINLINE
VOID
MiReleasePfnLockFromDpcLevel(VOID)
{
    PKSPIN_LOCK_QUEUE LockQueue;

    LockQueue = &KeGetCurrentPrcb()->LockQueue[LockQueuePfnLock];
    KeReleaseQueuedSpinLockFromDpcLevel(LockQueue);
    ASSERT(KeGetCurrentIrql() >= DISPATCH_LEVEL);
}

#define MI_ASSERT_PFN_LOCK_HELD() NT_ASSERT((KeGetCurrentIrql() >= DISPATCH_LEVEL) && (MmPfnLock != 0))

VOID
NTAPI
MmDumpArmPfnDatabase(
   IN BOOLEAN StatusOnly
);

VOID
NTAPI
MmZeroPageThread(
    VOID
);


/* i386/page.c *********************************************************/

BOOLEAN
NTAPI
MmCreateProcessAddressSpace(
    IN ULONG MinWs,
    IN PEPROCESS Dest,
    IN PULONG_PTR DirectoryTableBase
);

CODE_SEG("INIT")
NTSTATUS
NTAPI
MmInitializeHandBuiltProcess(
    IN PEPROCESS Process,
    IN PULONG_PTR DirectoryTableBase
);

CODE_SEG("INIT")
NTSTATUS
NTAPI
MmInitializeHandBuiltProcess2(
    IN PEPROCESS Process
);

NTSTATUS
NTAPI
MmSetExecuteOptions(IN ULONG ExecuteOptions);

NTSTATUS
NTAPI
MmGetExecuteOptions(IN PULONG ExecuteOptions);


/* section.c *****************************************************************/

PFILE_OBJECT
NTAPI
MmGetFileObjectForSection(
    IN PVOID Section
);

NTSTATUS
NTAPI
MmGetFileNameForAddress(
    IN PVOID Address,
    OUT PUNICODE_STRING ModuleName
);

NTSTATUS
NTAPI
MmGetFileNameForSection(
    IN PVOID Section,
    OUT POBJECT_NAME_INFORMATION *ModuleName
);


/* Exported from NT 6.2 Onward. We keep it internal. */
NTSTATUS
NTAPI
MmMapViewInSystemSpaceEx (
    _In_ PVOID Section,
    _Outptr_result_bytebuffer_ (*ViewSize) PVOID *MappedBase,
    _Inout_ PSIZE_T ViewSize,
    _Inout_ PLARGE_INTEGER SectionOffset,
    _In_ ULONG_PTR Flags
    );

BOOLEAN
NTAPI
MmArePagesResident(
    _In_ PEPROCESS Process,
    _In_ PVOID BaseAddress,
    _In_ ULONG Length);

NTSTATUS
NTAPI
MmMakePagesDirty(
    _In_ PEPROCESS Process,
    _In_ PVOID Address,
    _In_ ULONG Length);

NTSTATUS
NTAPI
MmFlushSegment(
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER Offset,
    _In_ ULONG Length,
    _Out_opt_ PIO_STATUS_BLOCK Iosb);

NTSTATUS
NTAPI
MmMakeDataSectionResident(
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ LONGLONG Offset,
    _In_ ULONG Length,
    _In_ PLARGE_INTEGER ValidDataLength);

BOOLEAN
NTAPI
MmPurgeSegment(
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER Offset,
    _In_ ULONG Length);

BOOLEAN
NTAPI
MmCheckDirtySegment(
    PMM_SECTION_SEGMENT Segment,
    PLARGE_INTEGER Offset,
    BOOLEAN ForceDirty,
    BOOLEAN PageOut);

BOOLEAN
NTAPI
MmUnsharePageEntrySectionSegment(PMEMORY_AREA MemoryArea,
                                 PMM_SECTION_SEGMENT Segment,
                                 PLARGE_INTEGER Offset,
                                 BOOLEAN Dirty,
                                 BOOLEAN PageOut,
                                 ULONG_PTR *InEntry);

_When_(OldIrql == MM_NOIRQL, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(OldIrql == MM_NOIRQL, _Requires_lock_not_held_(MmPfnLock))
_When_(OldIrql != MM_NOIRQL, _Requires_lock_held_(MmPfnLock))
_When_(OldIrql != MM_NOIRQL, _Releases_lock_(MmPfnLock))
_When_(OldIrql != MM_NOIRQL, _IRQL_requires_(DISPATCH_LEVEL))
VOID
NTAPI
MmDereferenceSegmentWithLock(
    _In_ PMM_SECTION_SEGMENT Segment,
    _In_ _When_(OldIrql != MM_NOIRQL, _IRQL_restores_) KIRQL OldIrql);

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_not_held_(MmPfnLock)
FORCEINLINE
VOID
MmDereferenceSegment(PMM_SECTION_SEGMENT Segment)
{
    MmDereferenceSegmentWithLock(Segment, MM_NOIRQL);
}

NTSTATUS
NTAPI
MmExtendSection(
    _In_ PVOID Section,
    _Inout_ PLARGE_INTEGER NewSize);

/* sptab.c *******************************************************************/

NTSTATUS
NTAPI
_MmSetPageEntrySectionSegment(PMM_SECTION_SEGMENT Segment,
                              PLARGE_INTEGER Offset,
                              ULONG_PTR Entry,
                              const char *file,
                              int line);

ULONG_PTR
NTAPI
_MmGetPageEntrySectionSegment(PMM_SECTION_SEGMENT Segment,
                              PLARGE_INTEGER Offset,
                              const char *file,
                              int line);

#define MmSetPageEntrySectionSegment(S,O,E) _MmSetPageEntrySectionSegment(S,O,E,__FILE__,__LINE__)

#define MmGetPageEntrySectionSegment(S,O) _MmGetPageEntrySectionSegment(S,O,__FILE__,__LINE__)

/* sysldr.c ******************************************************************/

BOOLEAN
NTAPI
MmChangeKernelResourceSectionProtection(IN ULONG_PTR ProtectionMask);

VOID
NTAPI
MmMakeKernelResourceSectionWritable(VOID);

NTSTATUS
NTAPI
MmLoadSystemImage(
    IN PUNICODE_STRING FileName,
    IN PUNICODE_STRING NamePrefix OPTIONAL,
    IN PUNICODE_STRING LoadedName OPTIONAL,
    IN ULONG Flags,
    OUT PVOID *ModuleObject,
    OUT PVOID *ImageBaseAddress
);

NTSTATUS
NTAPI
MmUnloadSystemImage(
    IN PVOID ImageHandle
);

NTSTATUS
NTAPI
MmCheckSystemImage(
    IN HANDLE ImageHandle,
    IN BOOLEAN PurgeSection
);

NTSTATUS
NTAPI
MmCallDllInitialize(
    IN PLDR_DATA_TABLE_ENTRY LdrEntry,
    IN PLIST_ENTRY ListHead
);

VOID
NTAPI
MmFreeDriverInitialization(
    IN PLDR_DATA_TABLE_ENTRY LdrEntry);

/* procsup.c *****************************************************************/

NTSTATUS
NTAPI
MmGrowKernelStack(
    IN PVOID StackPointer
);


/* expool.c ******************************************************************/

VOID
NTAPI
ExpCheckPoolAllocation(
    PVOID P,
    POOL_TYPE PoolType,
    ULONG Tag);

VOID
NTAPI
ExReturnPoolQuota(
    IN PVOID P);


/* mmsup.c *****************************************************************/

NTSTATUS
NTAPI
MmAdjustWorkingSetSize(
    IN SIZE_T WorkingSetMinimumInBytes,
    IN SIZE_T WorkingSetMaximumInBytes,
    IN ULONG SystemCache,
    IN BOOLEAN IncreaseOkay);


/* session.c *****************************************************************/

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmAttachSession(
    _Inout_ PVOID SessionEntry,
    _Out_ PKAPC_STATE ApcState);

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmDetachSession(
    _Inout_ PVOID SessionEntry,
    _Out_ PKAPC_STATE ApcState);

VOID
NTAPI
MmQuitNextSession(
    _Inout_ PVOID SessionEntry);

PVOID
NTAPI
MmGetSessionById(
    _In_ ULONG SessionId);

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmSetSessionLocaleId(
    _In_ LCID LocaleId);

/* shutdown.c *****************************************************************/

VOID
MmShutdownSystem(IN ULONG Phase);

/* virtual.c *****************************************************************/

NTSTATUS
NTAPI
CcShutdownSystem(VOID);
