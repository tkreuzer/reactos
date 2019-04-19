
#include <ntbase.h>
#include <wdbgexts.h>
#include <LinkedList.hpp>
#include "..\Ke\KeData.hpp"

CHAR NtBuildLab[] = "7600.16385.amd64fre.win7_rtm.090713-1255";

static const ULONG Kd::PRINT_CIRCULAR_BUFFER_SIZE = 8192;
CHAR Kd::PrintCircularBuffer[Kd::PRINT_CIRCULAR_BUFFER_SIZE];
PVOID Kd::PrintWritePointer;
ULONG Kd::PrintRolloverCount;
PVOID Kd::PrintCircularBufferPtr;
ULONG Kd::PrintBufferSize;
extern BOOLEAN KdDebuggerNotPresent;
extern BOOLEAN KdDebuggerEnabled;
extern BOOLEAN KdEnteredDebugger;
static LINKED_LIST Kd::DebuggerDataListHead;
static PVOID Kd::BreakPointTable[KDP_MAX_BREAK_POINTS];
static UCHAR Kd::BreakPointBackupTable[KDP_MAX_BREAK_POINTS][KDP_BREAKPOINT_LENGTH];
static BOOLEAN Kd::DebuggerActive;

C_ASSERT(sizeof(KDDEBUGGER_DATA64) == 0x340);

const
KDDEBUGGER_DATA64
Kd::DebuggerData =
{
    { 
        {
            MAKESIGNED64(&Kd::DebuggerDataListHead),
            MAKESIGNED64(&Kd::DebuggerDataListHead)
        },
        KDBG_TAG, sizeof(KDDEBUGGER_DATA64)
    }, // Header;
    MAKESIGNED64(&__ImageBase), // KernBase;
    MAKESIGNED64(&RtlpBreakWithStatusInstruction), // ULONG64 BreakpointWithStatus;
    0, // ULONG64 SavedContext;
    FIELD_OFFSET(KTHREAD, CallbackStack), // USHORT ThCallbackStack;
    0, // USHORT NextCallback;
    0, // USHORT FramePointer;
    0, // USHORT PaeEnabled:1;
    MAKESIGNED64(&KiCallUserMode),
    0, // ULONG64 KeUserCallbackDispatcher;
    MAKESIGNED64(&PsLoadedModuleList),
    MAKESIGNED64(&PsActiveProcessHead;
    MAKESIGNED64(&PspCidTable;
    MAKESIGNED64(&ExpSystemResourcesList;
    MAKESIGNED64(&ExpPagedPoolDescriptor;
    MAKESIGNED64(&ExpNumberOfPagedPools;
    MAKESIGNED64(&KeTimeIncrement;
    MAKESIGNED64(&KeBugCheckCallbackListHead;
    MAKESIGNED64(&KiBugcheckData;
    MAKESIGNED64(&IopErrorLogListHead;
    MAKESIGNED64(&ObpRootDirectoryObject;
    MAKESIGNED64(&ObpTypeObjectType;
    0, //MAKESIGNED64(&MmSystemCacheStart),
    0, //MAKESIGNED64(&MmSystemCacheEnd),
    MAKESIGNED64(&MmSystemCacheWs),
    MAKESIGNED64(&MmPfnDatabase),
    0, //MAKESIGNED64(&MmSystemPtesStart),
    0, //MAKESIGNED64(&MmSystemPtesEnd),
    MAKESIGNED64(&MmSubsectionBase),
    MAKESIGNED64(&MmNumberOfPagingFiles),
    MAKESIGNED64(&MmLowestPhysicalPage),
    MAKESIGNED64(&MmHighestPhysicalPage),
    MAKESIGNED64(&MmNumberOfPhysicalPages),
    MAKESIGNED64(&MmMaximumNonPagedPoolInBytes),
    0, //MAKESIGNED64(&MmNonPagedSystemStart),
    MAKESIGNED64(&MmNonPagedPoolStart),
    0, //MAKESIGNED64(&MmNonPagedPoolEnd),
    0, //MAKESIGNED64(&MmPagedPoolStart),
    MAKESIGNED64(&MmPagedPoolEnd),
    MAKESIGNED64(&MmPagedPoolInformation),
    PAGE_SIZE,
    MAKESIGNED64(&MmSizeOfPagedPoolInBytes),
    MAKESIGNED64(&MmTotalCommitLimit),
    MAKESIGNED64(&MmTotalCommittedPages),
    MAKESIGNED64(&MmSharedCommit),
    MAKESIGNED64(&MmDriverCommit),
    MAKESIGNED64(&MmProcessCommit),
    0, //MAKESIGNED64(&MmPagedPoolCommit),
    0, //MAKESIGNED64(&MmExtendedCommit),
    MAKESIGNED64(&MmZeroedPageListHead),
    MAKESIGNED64(&MmFreePageListHead),
    MAKESIGNED64(&MmStandbyPageListHead),
    MAKESIGNED64(&MmModifiedPageListHead),
    MAKESIGNED64(&MmModifiedNoWritePageListHead),
    MAKESIGNED64(&MmAvailablePages),
    MAKESIGNED64(&MmResidentAvailablePages),
    MAKESIGNED64(&PoolTrackTable;
    MAKESIGNED64(&NonPagedPoolDescriptor;
    MAKESIGNED64(&MmHighestUserAddress),
    MAKESIGNED64(&MmSystemRangeStart),
    MAKESIGNED64(&MmUserProbeAddress),
    MAKESIGNED64(&Kd::PrintCircularBuffer),
    MAKESIGNED64(&Kd::PrintCircularBuffer[Kd::PRINT_CIRCULAR_BUFFER_SIZE-1]),
    MAKESIGNED64(&Kd::PrintWritePointer),
    MAKESIGNED64(&Kd::PrintRolloverCount),
    0, //MAKESIGNED64(&MmLoadedUserImageList),
    MAKESIGNED64(&NtBuildLabEx), // ULONG64 NtBuildLab;
    0, // ULONG64 KiNormalSystemCall;
    MAKESIGNED64(&KiProcessorBlock;
    MAKESIGNED64(&MmUnloadedDrivers),
    MAKESIGNED64(&MmLastUnloadedDriver),
    MAKESIGNED64(&MmTriageActionTaken),
    MAKESIGNED64(&MmSpecialPoolTag),
    MAKESIGNED64(&KernelVerifier;
    MAKESIGNED64(&MmVerifierData),
    MAKESIGNED64(&MmAllocatedNonPagedPool),
    MAKESIGNED64(&MmPeakCommitment),
    MAKESIGNED64(&MmTotalCommitLimitMaximum),
    MAKESIGNED64(&CmNtCSDVersion;
    MAKESIGNED64(&MmPhysicalMemoryBlock),
    0, //MAKESIGNED64(&MmSessionBase),
    0, //MAKESIGNED64(&MmSessionSize),
    0, //MAKESIGNED64(&MmSystemParentTablePage),
    0, //MAKESIGNED64(&MmVirtualTranslationBase),
    FIELD_OFFSET(KTHREAD, NextProcessor), // USHORT OffsetKThreadNextProcessor;
    FIELD_OFFSET(KTHREAD, Teb), // USHORT OffsetKThreadTeb;
    FIELD_OFFSET(KTHREAD, KernelStack), // USHORT OffsetKThreadKernelStack;
    FIELD_OFFSET(KTHREAD, InitialStack), // USHORT OffsetKThreadInitialStack;
    FIELD_OFFSET(KTHREAD, ApcState.Process), // USHORT OffsetKThreadApcProcess;
    FIELD_OFFSET(KTHREAD, State), // USHORT OffsetKThreadState;
    0, // USHORT OffsetKThreadBStore;
    0, // USHORT OffsetKThreadBStoreLimit;
    sizeof(EPROCESS), // USHORT SizeEProcess;
    FIELD_OFFSET(EPROCESS, Peb), // USHORT OffsetEprocessPeb;
    FIELD_OFFSET(EPROCESS, InheritedFromUniqueProcessId), // USHORT OffsetEprocessParentCID;
    FIELD_OFFSET(EPROCESS, Pcb.DirectoryTableBase), // USHORT OffsetEprocessDirectoryTableBase;
    sizeof(KPRCB), // USHORT SizePrcb;
    FIELD_OFFSET(KPRCB, DpcRoutineActive), // USHORT OffsetPrcbDpcRoutine;
    FIELD_OFFSET(KPRCB, CurrentThread), // USHORT OffsetPrcbCurrentThread;
    FIELD_OFFSET(KPRCB, MHz), // USHORT OffsetPrcbMhz;
    FIELD_OFFSET(KPRCB, CpuType), // USHORT OffsetPrcbCpuType;
    FIELD_OFFSET(KPRCB, VendorString), // USHORT OffsetPrcbVendorString;
    FIELD_OFFSET(KPRCB, ProcessorState.ContextFrame), // USHORT OffsetPrcbProcStateContext;
    FIELD_OFFSET(KPRCB, LegacyNumber), // USHORT OffsetPrcbNumber;
    sizeof(ETHREAD), // USHORT SizeEThread;
    // alignment
    MAKESIGNED64(&KdPrintCircularBufferPtr),
    MAKESIGNED64(&KdPrintBufferSize),
    MAKESIGNED64(&KeLoaderBlock),
    sizeof(KPCREX), // USHORT SizePcr;
    FIELD_OFFSET(KPCR, Self), // USHORT OffsetPcrSelfPcr;
    FIELD_OFFSET(KPCR, CurrentPrcb), // USHORT OffsetPcrCurrentPrcb;
    FIELD_OFFSET(KPCREX, Prcb), // USHORT OffsetPcrContainedPrcb;
    0, // USHORT OffsetPcrInitialBStore;
    0, // USHORT OffsetPcrBStoreLimit;
    0, // USHORT OffsetPcrInitialStack;
    0, // USHORT OffsetPcrStackLimit;
    0, // USHORT OffsetPrcbPcrPage;
    FIELD_OFFSET(KPRCB, ProcessorState.SpecialRegisters), // USHORT OffsetPrcbProcStateSpecialReg;
#if defined(_M_IX86) || defined(_M_AMD64)
    KGDT_R0_CODE, // USHORT GdtR0Code;
    KGDT_R0_DATA, // USHORT GdtR0Data;
    KGDT_R0_PCR, // USHORT GdtR0Pcr;
    KGDT_R3_CODE, // USHORT GdtR3Code;
    KGDT_R3_DATA, // USHORT GdtR3Data;
    KGDT_R3_TEB, // USHORT GdtR3Teb;
    KGDT_LDT, // USHORT GdtLdt;
    KGDT_SYS_TSS, // USHORT GdtTss;
    KGDT_R3_CMCODE, // USHORT Gdt64R3CmCode;
    KGDT_R3_CMTEB, // USHORT Gdt64R3CmTeb;
#else
 #error Unimplemented
#endif
    MAKESIGNED64(&IopNumTriageDumpDataBlocks;
    MAKESIGNED64(&IopTriageDumpDataBlocks;

    /* Longhorn additions */
    0, // GCC_ULONG64 VfCrashDataBlock;
    MAKESIGNED64(&MmBadPagesDetected),
    MAKESIGNED64(&MmZeroedPageSingleBitErrorsDetected)

    /* Windows 7 additions */
    MAKESIGNED64(&EtwpDebuggerData), // ULONG64 EtwpDebuggerData
    FIELD_OFFSET(KPCR, Context), // USHORT OffsetPrcbContext;

    /* Windows 8 additions */
    0, //USHORT OffsetPrcbMaxBreakpoints;
    0, //USHORT OffsetPrcbMaxWatchpoints;
    // align 2 bytes
    FIELD_OFFSET(KTHREAD, StackLimit), //ULONG OffsetKThreadStackLimit;
    FIELD_OFFSET(KTHREAD, StackBase), //ULONG OffsetKThreadStackBase;
    FIELD_OFFSET(KTHREAD, QueueListEntry), //ULONG OffsetKThreadQueueListEntry;
    FIELD_OFFSET(ETHREAD, IrpList), //ULONG OffsetEThreadIrpList;
    FIELD_OFFSET(KPRCB, IdleThread), //USHORT OffsetPrcbIdleThread;
    FIELD_OFFSET(KPRCB, NormalDpcState), //USHORT OffsetPrcbNormalDpcState;
    FIELD_OFFSET(KPRCB, DpcStack), //USHORT OffsetPrcbDpcStack;
    FIELD_OFFSET(KPRCB, IsrStack), //USHORT OffsetPrcbIsrStack;
    sizeof(KDPC_STACK_FRAME), //USHORT SizeKDPC_STACK_FRAME;
};

