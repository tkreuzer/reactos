
#ifdef SPINLOCK_DBG
enum
{
    SPINLOCK_Dispatcher_Increment = 1,
    SPINLOCK_Dispatcher_Maximum = MAXIMUM_WAIT_OBJECTS, /* 64 */
    SPINLOCK_Thread_Increment = SPINLOCK_Dispatcher_Maximum,
    SPINLOCK_Thread_Maximum = SPINLOCK_Thread_Increment * 2,
}

VOID
FORCEINLINE
DbgSpinlockAcquire(LONG Increment, LONG Maximum)
{
    ASSERT(KeGetCurrentIrql() >= DISPATCH_LEVEL);
    ASSERT(KeGetCurrentPrcb->KeSpinlockOrdering < Maximum);
    KeGetCurrentPrcb->KeSpinlockOrdering += Increment;
}

#define SPINLOCK_ACQUIRE(Type) \
    DbgSpinlockAcquire(SPINLOCK_#Type#_Increment, SPINLOCK_#Type#_Maximum);
#define SPINLOCK_RELEASE(Type)
#else
#define SPINLOCK_ACQUIRE(Type)
#define SPINLOCK_RELEASE(Type)
#endif

extern ULONG (*FrLdrDbgPrint)(const char *Format, ...);
extern PLOADER_PARAMETER_BLOCK KeLoaderBlock;

enum _BUGCHECKCODES
{
    TRAP_CAUSE_UNKNOWN = 0x12,
    KMODE_EXCEPTION_NOT_HANDLED = 0x1e,
    PAGE_FAULT_WITH_INTERRUPTS_OFF = 0x49,
    UNEXPECTED_KERNEL_MODE_TRAP = 0x7f,
    DRIVER_IRQL_NOT_LESS_OR_EQUAL = 0xD1
};

typedef struct _KTHREAD
{
    DISPATCHER_HEADER Header;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    ULONGLONG CycleTime;
#ifndef _WIN64
    ULONG HighCycleTime;
#endif
    ULONGLONG QuantumTarget;
#else
    LIST_ENTRY MutantListHead;
#endif
    PVOID InitialStack;
    ULONG_PTR StackLimit;
    PVOID KernelStack;
    KSPIN_LOCK ThreadLock;
    union
    {
        KAPC_STATE ApcState;
        struct
        {
            UCHAR ApcStateFill[23];
            UCHAR ApcQueueable;
            volatile UCHAR NextProcessor;
            volatile UCHAR DeferredProcessor;
            UCHAR AdjustReason;
            SCHAR AdjustIncrement;
        };
    };
    KSPIN_LOCK ApcQueueLock;
    ULONG ContextSwitches;
    volatile UCHAR State;
    UCHAR NpxState;
    KIRQL WaitIrql;
    KPROCESSOR_MODE WaitMode;
    LONG_PTR WaitStatus;
    union
    {
        PKWAIT_BLOCK WaitBlockList;
        PKGATE GateObject;
    };
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    union
    {
        struct
        {
            ULONG KernelStackResident:1;
            ULONG ReadyTransition:1;
            ULONG ProcessReadyQueue:1;
            ULONG WaitNext:1;
            ULONG SystemAffinityActive:1;
            ULONG Alertable:1;
            ULONG GdiFlushActive:1;
            ULONG Reserved:25;
        };
        LONG MiscFlags;
    };
#else
    BOOLEAN Alertable;
    BOOLEAN WaitNext;
#endif
    UCHAR WaitReason;
    SCHAR Priority;
    BOOLEAN EnableStackSwap;
    volatile UCHAR SwapBusy;
    BOOLEAN Alerted[MaximumMode];
    union
    {
        LIST_ENTRY WaitListEntry;
        SINGLE_LIST_ENTRY SwapListEntry;
    };
    PKQUEUE Queue;
    ULONG WaitTime;
    union
    {
        struct
        {
            SHORT KernelApcDisable;
            SHORT SpecialApcDisable;
        };
        ULONG CombinedApcDisable;
    };
    struct _TEB *Teb;
    union
    {
        KTIMER Timer;
        struct
        {
            UCHAR TimerFill[40];
            union
            {
                struct
                {
                    LONG AutoAlignment:1;
                    LONG DisableBoost:1;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
                    LONG EtwStackTrace1ApcInserted:1;
                    LONG EtwStackTrace2ApcInserted:1;
                    LONG CycleChargePending:1;
                    LONG ReservedFlags:27;
#else
                    LONG ReservedFlags:30;
#endif
                };
                LONG ThreadFlags;
            };
        };
    };
    union
    {
        KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
        struct
        {
            UCHAR WaitBlockFill0[23];
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
            UCHAR IdealProcessor;
#else
            BOOLEAN SystemAffinityActive;
#endif
        };
        struct
        {
            UCHAR WaitBlockFill1[47];
            CCHAR PreviousMode;
        };
        struct
        {
            UCHAR WaitBlockFill2[71];
            UCHAR ResourceIndex;
        };
        struct
        {
            UCHAR WaitBlockFill3[95];
            UCHAR LargeStack;
        };
    };
    LIST_ENTRY QueueListEntry;
    struct _KTRAP_FRAME *TrapFrame;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    PVOID FirstArgument;
#endif
    PVOID CallbackStack;
    PVOID ServiceTable;
    UCHAR ApcStateIndex;
#if (NTDDI_VERSION < NTDDI_LONGHORN)
    UCHAR IdealProcessor;
#endif
    BOOLEAN Preempted;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    BOOLEAN CalloutActive;
#else
    BOOLEAN ProcessReadyQueue;
    BOOLEAN KernelStackResident;
#endif
    SCHAR BasePriority;
    SCHAR PriorityDecrement;
    CHAR Saturation;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    ULONG SystemCallNumber;
    ULONG Spare2;
#endif
    KAFFINITY UserAffinity;
    struct _KPROCESS *Process;
    KAFFINITY Affinity;
    PKAPC_STATE ApcStatePointer[2];
    union
    {
        KAPC_STATE SavedApcState;
        struct
        {
            UCHAR SavedApcStateFill[23];
            CCHAR FreezeCount;
            CCHAR SuspendCount;
            UCHAR UserIdealProcessor;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
            union
            {
                struct
                {
                    UCHAR ReservedBits0:1;
                    UCHAR SegmentsPresent:1;
                    UCHAR Reservedbits1:1;
                };
                UCHAR NestedStateFlags;
            };
#else
            UCHAR CalloutActive;
#endif
            UCHAR Iopl;
        };
    };
    PVOID Win32Thread;
    PVOID StackBase;
    union
    {
        KAPC SuspendApc;
        struct
        {
            UCHAR SuspendApcFill0[1];
            SCHAR Quantum;
        };
        struct
        {
            UCHAR SuspendApcFill1[3];
            UCHAR QuantumReset;
        };
        struct
        {
            UCHAR SuspendApcFill2[4];
            ULONG KernelTime;
        };
        struct
        {
            UCHAR SuspendApcFill3[36];
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
            struct _KPRCB *WaitPrcb;
#else
            PVOID TlsArray;
#endif
        };
        struct
        {
            UCHAR SuspendApcFill4[40];
            PVOID LegoData;
        };
        struct
        {
            UCHAR SuspendApcFill5[47];
            UCHAR PowerState;
            ULONG UserTime;
        };
    };
    union
    {
        KSEMAPHORE SuspendSemaphore;
        struct
        {
            UCHAR SuspendSemaphorefill[20];
            ULONG SListFaultCount;
        };
    };
    LIST_ENTRY ThreadListEntry;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    LIST_ENTRY MutantListHead;
#endif
    PVOID SListFaultAddress;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    PVOID MdlForLockedteb;
#endif
} KTHREAD;

typedef union _KEXECUTE_OPTIONS
{
    struct
    {
        UCHAR ExecuteDisable:1;
        UCHAR ExecuteEnable:1;
        UCHAR DisableThunkEmulation:1;
        UCHAR Permanent:1;
        UCHAR ExecuteDispatchEnable:1;
        UCHAR ImageDispatchEnable:1;
        UCHAR DisableExceptionChainValidation:1;
        UCHAR Spare:1;
    };
    UCHAR ExecuteOptions;
} KEXECUTE_OPTIONS, *PKEXECUTE_OPTIONS;

typedef union _KSTACK_COUNT
{
    LONG Value;
    struct
    {
        ULONG State:3;
        ULONG StackCount:29;
    };
} KSTACK_COUNT, *PKSTACK_COUNT;

typedef struct _KDPC_DATA
{
    LIST_ENTRY DpcListHead;
    ULONG_PTR DpcLock;
#ifdef _M_AMD64
    volatile LONG DpcQueueDepth;
#else
    volatile ULONG DpcQueueDepth;
#endif
    ULONG DpcCount;
} KDPC_DATA, *PKDPC_DATA;

#if defined(_M_AMD64)
#include "amd64/Ke_amd64.h"
#elif defined(_M_IX86)
#include "ix86/Ke_ix86.h"
#else
#error unimplemented architecture
#endif

typedef struct _KPROCESS
{
    DISPATCHER_HEADER Header;
    LIST_ENTRY ProfileListHead;
    ULONG_PTR DirectoryTableBase;
    LIST_ENTRY ThreadListHead;
    KSPIN_LOCK ProcessLock;
    KAFFINITY_EX Affinity;
    LIST_ENTRY ReadyListHead;
    SINGLE_LIST_ENTRY SwapListEntry;
    KAFFINITY_EX ActiveProcessors;
    union
    {
        struct
        {
            ULONG AutoAlignment:1;
            ULONG DisableBoost:1;
            ULONG DisableQuantum:1;
            ULONG AffinitySet:1;
            ULONG DeepFreeze : 1;
            ULONG IdleAware : 1;
            ULONG TimerVirtualization : 1;
            ULONG ActiveGroupsMask : 8;
            ULONG ReservedFlags:17;
        };
        ULONG ProcessFlags;
    };
    SCHAR BasePriority;
    SCHAR QuantumReset;
    UCHAR Visited;
    KEXECUTE_OPTIONS Flags;
    ULONG ThreadSeed[8];
    USHORT IdealNode[8];
    USHORT IdealGlobalNode;
    USHORT Spare0;
    KSTACK_COUNT StackCount;
    LIST_ENTRY ProcessListEntry;
    ULONGLONG CycleTime;
    ULONGLONG ContextSwitches;
    ULONG FreezeCount;
    ULONG KernelTime;
    ULONG UserTime;
    USHORT LdtFreeSelectorHint;
    USHORT LdtTableLength;
    KGDTENTRY64 LdtSystemDescriptor;
    PVOID LdtBaseAddress;
    FAST_MUTEX LdtProcessLock;
    PVOID InstrumentationCallback;
} KPROCESS;

#define KeGetCurrentProcess KxGetCurrentProcess
#define KeGetCurrentPrcb KxGetCurrentPrcb

KPROCESSOR_MODE
FORCEINLINE
_KeGetPreviousMode(VOID)
{
    return KeGetCurrentPrcb()->CurrentThread->PreviousMode;
}
#define KeGetPreviousMode _KeGetPreviousMode

extern PVOID KeUserCallbackDispatcher;
extern ULONG KeTimeIncrement;

ULONG
RawDbgPrint(const char *Format, ...);

PKPCR
NTAPI
KeGetPcrFromNumber(ULONG Number);

BOOLEAN
NTAPI
RtlDispatchException(
    IN PEXCEPTION_RECORD ExceptionRecord,
    IN PCONTEXT Context);


/* BugCheck.c *****************************************************************/

DECLSPEC_NORETURN
VOID
NTAPI
KeBugCheckWithTf(
    IN ULONG BugCheckCode,
    IN ULONG_PTR BugCheckParameter1,
    IN ULONG_PTR BugCheckParameter2,
    IN ULONG_PTR BugCheckParameter3,
    IN ULONG_PTR BugCheckParameter4,
    IN struct _KTRAP_FRAME *TrapFrame);


/* Thread.c *******************************************************************/

VOID
NTAPI
KeInitializeThread(
    PKTHREAD Thread,
    PKPROCESS Process,
    PVOID Stack,
    PVOID Teb,
    PVOID StartRoutine,
    PVOID StartContext);

