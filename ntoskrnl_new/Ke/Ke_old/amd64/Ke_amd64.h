
#ifdef _KE_INTERNAL_

#define CPU_NONE       0x0
#define CPU_INTEL      0x1
#define CPU_AMD        0x2
#define CPU_CYRIX      0x3
#define CPU_TRANSMETA  0x4
#define CPU_CENTAUR    0x5
#define CPU_RISE       0x6
#define CPU_UNKNOWN    0x7

/* Seletor constants */
#define RPL_MASK                0x0003
#define MODE_MASK               0x0001
#define KGDT64_NULL             0x0000
#define KGDT64_R0_CODE          0x0010
#define KGDT64_R0_DATA          0x0018
#define KGDT64_R3_CMCODE        0x0020
#define KGDT64_R3_DATA          0x0028
#define KGDT64_R3_CODE          0x0030
#define KGDT64_SYS_TSS          0x0040
#define KGDT64_R3_CMTEB         0x0050

/* Sync level IRQL */
#ifdef CONFIG_SMP
#define SYNCH_LEVEL DISPATCH_LEVEL
#else
#define SYNCH_LEVEL (IPI_LEVEL - 2)
#endif

#include <pshpack1.h>
typedef struct _KI_INTERRUPT_DISPATCH_ENTRY
{
    UCHAR _Op_nop;
    UCHAR _Op_push;
    UCHAR _Vector;
    UCHAR _Op_jmp;
    ULONG RelativeAddress;
} KI_INTERRUPT_DISPATCH_ENTRY, *PKI_INTERRUPT_DISPATCH_ENTRY;
#include <poppack.h>

typedef struct _KNONVOLATILES
{
    ULONG64 Rbp;
    ULONG64 Rbx;
    ULONG64 Rdi;
    ULONG64 Rsi;
    ULONG64 R12;
    ULONG64 R13;
    ULONG64 R14;
    ULONG64 R15;
    ULONG64 Xmm6;
    ULONG64 Xmm7;
    ULONG64 Xmm8;
    ULONG64 Xmm9;
    ULONG64 Xmm10;
    ULONG64 Xmm11;
    ULONG64 Xmm12;
    ULONG64 Xmm13;
    ULONG64 Xmm14;
    ULONG64 Xmm15;
} KNONVOLATILES, *PKNONVOLATILES;

typedef struct _KSTART_FRAME
{
    PVOID StartRoutine;
    PVOID StartContext;
} KSTART_FRAME, *PKSTART_FRAME;

typedef struct _KTRAP_FRAME
{
    UINT64 P1Home;
    UINT64 P2Home;
    UINT64 P3Home;
    UINT64 P4Home;
    UINT64 P5;
    CHAR PreviousMode;
    UCHAR PreviousIrql;
    UCHAR FaultIndicator;
    UCHAR ExceptionActive;
    ULONG MxCsr;
    UINT64 Rax;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    union
    {
        UINT64 GsBase;
        UINT64 GsSwap;
    };
    M128A Xmm0;
    M128A Xmm1;
    M128A Xmm2;
    M128A Xmm3;
    M128A Xmm4;
    M128A Xmm5;
    union
    {
        UINT64 FaultAddress;
        UINT64 ContextRecord;
        UINT64 TimeStampCKCL;
    };
    UINT64 Dr0;
    UINT64 Dr1;
    UINT64 Dr2;
    UINT64 Dr3;
    UINT64 Dr6;
    UINT64 Dr7;
    union
    {
        struct
        {
            UINT64 DebugControl;
            UINT64 LastBranchToRip;
            UINT64 LastBranchFromRip;
            UINT64 LastExceptionToRip;
            UINT64 LastExceptionFromRip;
        };
        struct
        {
            UINT64 LastBranchControl;
            ULONG LastBranchMSR;
        };
    };
    USHORT SegDs;
    USHORT SegEs;
    USHORT SegFs;
    USHORT SegGs;
    UINT64 TrapFrame;
    UINT64 Rbx;
    UINT64 Rdi;
    UINT64 Rsi;
    UINT64 Rbp;
    union
    {
        UINT64 ErrorCode;
        UINT64 ExceptionFrame;
        UINT64 TimeStampKlog;
    };
    UINT64 Rip;
    USHORT SegCs;
    UCHAR Fill0;
    UCHAR Logging;
    USHORT Fill1[2];
    ULONG EFlags;
    ULONG Fill2;
    UINT64 Rsp;
    USHORT SegSs;
    USHORT Fill3;
    LONG CodePatchCycle;
} KTRAP_FRAME, *PKTRAP_FRAME;

typedef struct _KEXCEPTION_FRAME
{
    UINT64 P1Home;
    UINT64 P2Home;
    UINT64 P3Home;
    UINT64 P4Home;
    UINT64 P5;
    UINT64 InitialStack;
    M128A Xmm6;
    M128A Xmm7;
    M128A Xmm8;
    M128A Xmm9;
    M128A Xmm10;
    M128A Xmm11;
    M128A Xmm12;
    M128A Xmm13;
    M128A Xmm14;
    M128A Xmm15;
    UINT64 TrapFrame;
    UINT64 CallbackStack;
    UINT64 OutputBuffer;
    UINT64 OutputLength;
    UINT64 MxCsr;
    UINT64 Rbp;
    UINT64 Rbx;
    UINT64 Rdi;
    UINT64 Rsi;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;
    UINT64 Return;
} KEXCEPTION_FRAME, *PKEXCEPTION_FRAME;

typedef union _KIDTENTRY64
{
    struct
    {
        USHORT OffsetLow;
        USHORT Selector;
        USHORT IstIndex:3;
        USHORT Reserved0:5;
        USHORT Type:5;
        USHORT Dpl:2;
        USHORT Present:1;
        USHORT OffsetMiddle;
        ULONG OffsetHigh;
        ULONG Reserved1;
    };
    UINT64 Alignment;
} KIDTENTRY64, *PKIDTENTRY64;
#define KIDTENTRY KIDTENTRY64
#define PKIDTENTRY PKIDTENTRY64

typedef struct _KIDT_INIT
{
    UCHAR InterruptId;
    UCHAR Dpl;
    UCHAR IstIndex;
    PVOID ServiceRoutine;
} KIDT_INIT, *PKIDT_INIT;

extern KDESCRIPTOR Amd64IdtDescriptor;

void __sgdt(OUT void *Descriptor);
void __sldt(void *Destination);
void __ltr(unsigned short Source);
void __str(unsigned short *Destination);
void __stmxcsr(unsigned int *Destination);

PKGDTENTRY64
FORCEINLINE
KxGetGdtEntry(PVOID pGdt, USHORT Selector)
{
    return (PKGDTENTRY64)((ULONG64)pGdt + (Selector & ~RPL_MASK));
}

PVOID
FORCEINLINE
KxGetGdtDescriptorBase(PKGDTENTRY Entry)
{
    return (PVOID)((ULONG64)Entry->BaseLow |
                   (ULONG64)Entry->Bytes.BaseMiddle << 16 |
                   (ULONG64)Entry->Bytes.BaseHigh << 24 |
                   (ULONG64)Entry->BaseUpper << 32);
}

VOID
INITAPI
x86GetCpuInfo(PKPRCB Prcb);

VOID
INITAPI
x86GetCacheInformation(PKPCR Pcr);

#else /* _KE_INTERNAL_ */

typedef AMD64_GDTENTRY KGDTENTRY64, *PKGDTENTRY64;
#define KGDTENTRY KGDTENTRY64
#define PKGDTENTRY PKGDTENTRY64

typedef struct _KDESCRIPTOR
{
    USHORT Pad[3];
    USHORT Limit;
    PVOID Base;
} KDESCRIPTOR, *PKDESCRIPTOR;

#pragma pack(push,4)
typedef struct _KTSS64
{
 /* 000 */  ULONG Reserved0;
 /* 004 */  UINT64 Rsp0;
 /* 00c */  UINT64 Rsp1;
 /* 014 */  UINT64 Rsp2;
 /* 01c */  UINT64 Ist[8];
 /* 05c */  UINT64 Reserved1;
 /* 064 */  USHORT Reserved2;
 /* 066 */  USHORT IoMapBase;
} KTSS64, *PKTSS64;
#pragma pack(pop)
#define KTSS KTSS64
#define PKTSS PKTSS64
#define AMD64_TSS 9

typedef struct _KSPECIAL_REGISTERS
{
    UINT64 Cr0;
    UINT64 Cr2;
    UINT64 Cr3;
    UINT64 Cr4;
    UINT64 KernelDr0;
    UINT64 KernelDr1;
    UINT64 KernelDr2;
    UINT64 KernelDr3;
    UINT64 KernelDr6;
    UINT64 KernelDr7;
    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;
    USHORT Tr;
    USHORT Ldtr;
    ULONG MxCsr;
    UINT64 DebugControl;
    UINT64 LastBranchToRip;
    UINT64 LastBranchFromRip;
    UINT64 LastExceptionToRip;
    UINT64 LastExceptionFromRip;
    UINT64 Cr8;
    UINT64 MsrGsBase;
    UINT64 MsrGsSwap;
    UINT64 MsrStar;
    UINT64 MsrLStar;
    UINT64 MsrCStar;
    UINT64 MsrSyscallMask;
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;

typedef struct _KPROCESSOR_STATE
{
    KSPECIAL_REGISTERS SpecialRegisters;
    CONTEXT ContextFrame;
} KPROCESSOR_STATE, *PKPROCESSOR_STATE;

typedef struct _KREQUEST_PACKET
{
    PVOID CurrentPacket[3];
    PVOID WorkerRoutine;
} KREQUEST_PACKET, *PKREQUEST_PACKET;

typedef struct _REQUEST_MAILBOX
{
    INT64 RequestSummary;
    KREQUEST_PACKET RequestPacket;
    PVOID Virtual[7];
} REQUEST_MAILBOX, *PREQUEST_MAILBOX;

typedef struct _KPRCB
{
    ULONG MxCsr;
    UCHAR LegacyNumber;
    UCHAR ReservedMustBeZero;
    UCHAR InterruptRequest;
    UCHAR IdleHalt;
    struct _KTHREAD *CurrentThread;
    struct _KTHREAD *NextThread;
    struct _KTHREAD *IdleThread;
    UCHAR NestingLevel;
    UCHAR ClockOwner;
    UCHAR PendingTick;
    UCHAR PrcbPad00[1];
    ULONG Number;
    UINT64 RspBase;
    UINT64 PrcbLock;
    UINT64 PrcbPad01;
    KPROCESSOR_STATE ProcessorState;
    CHAR CpuType;
    CHAR CpuID;
    union
    {
        USHORT CpuStep;
        struct
        {
            UCHAR CpuStepping;
            UCHAR CpuModel;
        };
    };
    ULONG MHz;
    UINT64 HalReserved[8];
    USHORT MinorVersion;
    USHORT MajorVersion;
    UCHAR BuildType;
    UCHAR CpuVendor;
    UCHAR CoresPerPhysicalProcessor;
    UCHAR LogicalProcessorsPerCore;
    ULONG ApicMask;
    ULONG CFlushSize;
    PVOID AcpiReserved;
    ULONG InitialApicId;
    ULONG Stride;
    USHORT Group;
    ULONG64 GroupSetMember;
    UCHAR GroupIndex;
    KSPIN_LOCK_QUEUE LockQueue[LockQueueMaximumLock]; // 2003: 33, vista:49 // win8 64: 17
//    PP_LOOKASIDE_LIST PPLookasideList[16];
//    GENERAL_LOOKASIDE_POOL PPNPagedLookasideList[32];
//    GENERAL_LOOKASIDE_POOL PPPagedLookasideList[32];
    UINT64 PacketBarrier;
    SINGLE_LIST_ENTRY DeferredReadyListHead;
    LONG MmPageFaultCount;
    LONG MmCopyOnWriteCount;
    LONG MmTransitionCount;
    LONG MmDemandZeroCount;
    LONG MmPageReadCount;
    LONG MmPageReadIoCount;
    LONG MmDirtyPagesWriteCount;
    LONG MmDirtyWriteIoCount;
    LONG MmMappedPagesWriteCount;
    LONG MmMappedWriteIoCount;
    ULONG KeSystemCalls;
    ULONG KeContextSwitches;
    ULONG CcFastReadNoWait;
    ULONG CcFastReadWait;
    ULONG CcFastReadNotPossible;
    ULONG CcCopyReadNoWait;
    ULONG CcCopyReadWait;
    ULONG CcCopyReadNoWaitMiss;
    LONG LookasideIrpFloat;
    LONG IoReadOperationCount;
    LONG IoWriteOperationCount;
    LONG IoOtherOperationCount;
    LARGE_INTEGER IoReadTransferCount;
    LARGE_INTEGER IoWriteTransferCount;
    LARGE_INTEGER IoOtherTransferCount;
    ULONG64 TargetCount;
    ULONG IpiFrozen;
    ULONG PrcbPad40[30];
    REQUEST_MAILBOX RequestMailbox[64];
    ULONG64 SenderSummary;
    UCHAR PrcbPad4[120];
    KDPC_DATA DpcData[2];
    PVOID DpcStack;
    LONG MaximumDpcQueueDepth;
    ULONG DpcRequestRate;
    ULONG MinimumDpcRate;
    ULONG DpcLastCount;
    UCHAR ThreadDpcEnable;
    UCHAR QuantumEnd;
    UCHAR DpcRoutineActive;
    UCHAR IdleSchedule;
    union
    {
        LONG DpcRequestSummary;
        SHORT DpcRequestSlot[2];
        struct
        {
            SHORT NormalDpcState;
            union
            {
                USHORT DpcThreadActive : 1;
                SHORT ThreadDpcState;
            };
        };
    };
    ULONG64 TimerHand;
    LONG MasterOffset;
    ULONG LastTick;
    ULONG ClockInterrupts;
    ULONG ReadyScanTick;
    UCHAR BalanceState;
    UCHAR PrcbPad50[11];
//    KTIMER_TABLE TimerTable;
    KGATE DpcGate;
    PVOID PrcbPad52;
    KDPC CallDpc;
    LONG ClockKeepAlive;
    UCHAR PrcbPad60[2];
    USHORT NmiActive;
    LONG DpcWatchdogPeriod;
    LONG DpcWatchdogCount;
    LONG KeSpinLockOrdering;
    ULONG PrcbPad70[1];
    PVOID CachedPtes;
    LIST_ENTRY WaitListHead;
    ULONG64 WaitLock;
    ULONG ReadySummary;
    ULONG QueueIndex;
    KDPC TimerExpirationDpc;
    //RTL_RB_TREE ScbQueue;
    LIST_ENTRY ScbList;
    LIST_ENTRY DispatcherReadyListHead[32];
    ULONG InterruptCount;
    ULONG KernelTime;
    ULONG UserTime;
    ULONG DpcTime;
    ULONG InterruptTime;
    ULONG AdjustDpcThreshold;
    UCHAR DebuggerSavedIRQL;
    UCHAR GroupSchedulingOverQuota;
    UCHAR PrcbPad80[6];
    ULONG DpcTimeCount;
    ULONG DpcTimeLimit;
    ULONG PeriodicCount;
    ULONG PeriodicBias;
    ULONG AvailableTime;
    ULONG KeExceptionDispatchCount;
    struct _KNODE* ParentNode;
    ULONG64 StartCycles;
    ULONG64 GenerationTarget;
    ULONG ScbOffset;
    ULONG PrcbPad82[1];
    ULONG64 AffinitizedCycles;
    LONG32 MmSpinLockOrdering;
    ULONG PageColor;
    ULONG NodeColor;
    ULONG NodeShiftedColor;
    ULONG SecondaryColorMask;
    ULONG PrcbPad83;
    ULONG64 CycleTime;
    ULONG CcFastMdlReadNoWait;
    ULONG CcFastMdlReadWait;
    ULONG CcFastMdlReadNotPossible;
    ULONG CcMapDataNoWait;
    ULONG CcMapDataWait;
    ULONG CcPinMappedDataCount;
    ULONG CcPinReadNoWait;
    ULONG CcPinReadWait;
    ULONG CcMdlReadNoWait;
    ULONG CcMdlReadWait;
    ULONG CcLazyWriteHotSpots;
    ULONG CcLazyWriteIos;
    ULONG CcLazyWritePages;
    ULONG CcDataFlushes;
    ULONG CcDataPages;
    ULONG CcLostDelayedWrites;
    ULONG CcFastReadResourceMiss;
    ULONG CcCopyReadWaitMiss;
    ULONG CcFastMdlReadResourceMiss;
    ULONG CcMapDataNoWaitMiss;
    ULONG CcMapDataWaitMiss;
    ULONG CcPinReadNoWaitMiss;
    ULONG CcPinReadWaitMiss;
    ULONG CcMdlReadNoWaitMiss;
    ULONG CcMdlReadWaitMiss;
    ULONG CcReadAheadIos;
    LONG MmCacheTransitionCount;
    LONG MmCacheReadCount;
    LONG MmCacheIoCount;
    ULONG PrcbPad91[3];
//    PROCESSOR_POWER_STATE PowerState;
    ULONG PrcbPad92[6];
    ULONG KeAlignmentFixupCount;
    KDPC DpcWatchdogDpc;
    KTIMER DpcWatchdogTimer;
    CACHE_DESCRIPTOR Cache[5];
    ULONG CacheCount;
    ULONG CachedCommit;
    ULONG CachedResidentAvailable;
    PVOID HyperPte;
    PVOID WheaInfo;
    PVOID EtwSupport;
    SLIST_HEADER InterruptObjectPool;
    SLIST_HEADER HypercallPageList;
    PVOID HypercallPageVirtual;
    PVOID VirtualApicAssist;
    ULONG64* StatisticsPage;
    ULONG64 CacheProcessorMask[5];
//    KAFFINITY_EX PackageProcessorSet;
    ULONG64 CoreProcessorSet;
    struct _PROCESSOR_PROFILE_CONTROL_AREA* ProcessorProfileControlArea;
    PVOID ProfileEventIndexAddress;
    ULONG64       PrcbPad93[8];
//    SYNCH_COUNTERS SynchCounters;
    UCHAR VendorString[13];
    UCHAR PrcbPad10[3];
    ULONG FeatureBits;
    LARGE_INTEGER UpdateSignature;
    PCONTEXT Context;
    ULONG ContextFlags;
    struct _XSAVE_AREA* ExtendedState;
    //ENTROPY_TIMING_STATE EntropyTimingState;
    struct _REQUEST_MAILBOX* Mailbox;
    //REQUEST_MAILBOX RequestMailbox[1];

    // private
    ULONG_PTR SpinLockQueue;
} KPRCB, *PKPRCB;

typedef struct _KPCREX
{
    KPCR;
    KPRCB Prcb;
} KPCREX, *PKPCREX;


PKPRCB
FORCEINLINE
KxPrcbFromPcr(PKPCR Pcr)
{
    return (PKPRCB)((ULONG64)Pcr + ALIGN_UP_BY(sizeof(KPCR), 16));
}

VOID
FORCEINLINE
KxSetCurrentIrql(KIRQL Irql)
{
    __writecr8(Irql);
}

PKPRCB
FORCEINLINE
KxGetCurrentPrcb()
{
    return (PKPRCB)__readgsqword(FIELD_OFFSET(KPCR, CurrentPrcb));
}

ULONG64
FORCEINLINE
KxContextGetPc(PCONTEXT Context)
{
    return Context->Rip;
}

VOID
FORCEINLINE
KxContextEnableSingleStep(PCONTEXT Context, ULONG TraceFlag)
{
    if (TraceFlag) Context->EFlags |= EFLAGS_TF;
    else Context->EFlags &= ~EFLAGS_TF;
}

FORCEINLINE
struct _KTHREAD*
KxGetCurrentThread(void)
{
    return (struct _KTHREAD*)__readgsqword(FIELD_OFFSET(KPCREX, Prcb.CurrentThread));
}

FORCEINLINE
struct _KTRAP_FRAME*
KxGetCurrentTrapFrame(VOID)
{
    return KxGetCurrentThread()->TrapFrame;
}

FORCEINLINE
struct _KPROCESS*
KxGetCurrentProcess(void)
{
    return KxGetCurrentThread()->Process;
}

VOID KiSystemCallEntry64(VOID);
VOID KiSystemCallEntry32(VOID);
VOID Amd64InitializeSegments(VOID);

VOID
INIT_FUNCTION
Amd64InitializeIDT(VOID);

#endif /* _KE_INTERNAL_ */
