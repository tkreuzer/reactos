typedef struct _KTHREAD
{
    DISPATCHER_HEADER Header;
    ULONGLONG CycleTime;
#ifndef _WIN64 // [
    ULONG HighCycleTime;
#endif // ]
    ULONGLONG QuantumTarget;
    PVOID InitialStack;
    ULONG_PTR StackLimit; // FIXME: PVOID
    PVOID KernelStack;
    KSPIN_LOCK ThreadLock;
    KWAIT_STATUS_REGISTER WaitRegister;
    BOOLEAN Running;
    BOOLEAN Alerted[MaximumMode];
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
            ULONG UserStackWalkActive:1;
            ULONG ApcInterruptRequest:1;
            ULONG ForceDeferSchedule:1;
            ULONG QuantumEndMigrate:1;
            ULONG UmsDirectedSwitchEnable:1;
            ULONG TimerActive:1;
            ULONG Reserved:19;
        };
        LONG MiscFlags;
    };
    union
    {
        KAPC_STATE ApcState;
        struct
        {
            UCHAR ApcStateFill[FIELD_OFFSET(KAPC_STATE, UserApcPending) + 1]; // 23/43
            SCHAR Priority;
            /* On x86, the following members "fall out" of the union */
            volatile ULONG NextProcessor;
            volatile ULONG DeferredProcessor;
        };
    };
    KSPIN_LOCK ApcQueueLock;
#ifndef _M_AMD64 // [
    ULONG ContextSwitches;
    volatile UCHAR State;
    UCHAR NpxState;
    KIRQL WaitIrql;
    KPROCESSOR_MODE WaitMode;
#endif // ]
    LONG_PTR WaitStatus;
    PKWAIT_BLOCK WaitBlockList;
    union
    {
        LIST_ENTRY WaitListEntry;
        SINGLE_LIST_ENTRY SwapListEntry;
    };
    PKQUEUE Queue;
#ifndef _M_AMD64 // [
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
#endif // ]
    struct _TEB *Teb;
    KTIMER Timer;
    union
    {
        struct
        {
            ULONG AutoAlignment:1;
            ULONG DisableBoost:1;
            ULONG EtwStackTraceApc1Inserted:1;
            ULONG EtwStackTraceApc2Inserted:1;
            ULONG CycleChargePending:1;
            ULONG CalloutActive:1;
            ULONG ApcQueueable:1;
            ULONG EnableStackSwap:1;
            ULONG GuiThread:1;
            ULONG ReservedFlags:23;
        };
        LONG ThreadFlags;
    };
#if defined(_WIN64) // [
    ULONG Spare0;
#else // ][
    PVOID ServiceTable;
#endif // ]
    union
    {
        DECLSPEC_ALIGN(8) KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
#ifdef _M_AMD64 // [
        struct
        {
            UCHAR WaitBlockFill4[FIELD_OFFSET(KWAIT_BLOCK, SpareLong)];
            ULONG ContextSwitches;
        };
        struct
        {
            UCHAR WaitBlockFill5[1 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareLong)];
            UCHAR State;
            UCHAR NpxState;
            UCHAR WaitIrql;
            CHAR WaitMode;
        };
        struct
        {
            UCHAR WaitBlockFill6[2 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareLong)];
            ULONG WaitTime;
        };
        struct
        {
            UCHAR WaitBlockFill7[3 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, Object)];
            PVOID TebMappedLowVa;
            struct _UMS_CONTROL_BLOCK* Ucb;
        };
        struct
        {
            UCHAR WaitBlockFill8[3 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareLong)];
            union
            {
                struct
                {
                    SHORT KernelApcDisable;
                    SHORT SpecialApcDisable;
                };
                ULONG CombinedApcDisable;
            };
        };
#endif // ]
    };
    LIST_ENTRY QueueListEntry;
    PKTRAP_FRAME TrapFrame;
    PVOID FirstArgument;
    union
    {
        PVOID CallbackStack;
        ULONG_PTR CallbackDepth;
    };
    UCHAR ApcStateIndex;
    SCHAR BasePriority;
    SCHAR PriorityDecrement;
    BOOLEAN Preempted;
    UCHAR AdjustReason;
    SCHAR AdjustIncrement;
    CCHAR PreviousMode;
    CHAR Saturation;
    ULONG SystemCallNumber;
    ULONG FreezeCount;
    GROUP_AFFINITY UserAffinity;
    struct _KPROCESS *Process;
    GROUP_AFFINITY Affinity;
    ULONG IdealProcessor;
    ULONG UserIdealProcessor;
    PKAPC_STATE ApcStatePointer[2];
    union
    {
        KAPC_STATE SavedApcState;
        struct
        {
            UCHAR SavedApcStateFill[FIELD_OFFSET(KAPC_STATE, UserApcPending) + 1];
            UCHAR WaitReason;
#ifdef _WIN64 // [
            CCHAR SuspendCount;
            CCHAR Spare1;
            UCHAR CodePatchInProgress;
#endif // ]
        };
    };
#ifndef _WIN64 // [
    CCHAR SuspendCount;
    CCHAR Spare1;
#endif // ]
#if defined(_M_IX86) // [
    UCHAR OtherPlatformFill;
#endif // ]
    PVOID Win32Thread;
    PVOID StackBase;
    union
    {
        KAPC SuspendApc;
        struct
        {
            UCHAR SuspendApcFill0[1];
            UCHAR ResourceIndex;
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
            UCHAR SuspendApcFill3[FIELD_OFFSET(KAPC, SystemArgument1)];
            PKPRCB WaitPrcb;
        };
        struct
        {
            UCHAR SuspendApcFill4[FIELD_OFFSET(KAPC, SystemArgument2)]; // 40 / 72
            PVOID LegoData;
        };
        struct
        {
            UCHAR SuspendApcFill5[FIELD_OFFSET(KAPC, Inserted) + 1]; // 47 / 83
            UCHAR LargeStack;
#ifdef _WIN64 // [
            ULONG UserTime;
#endif // ]
        };
    };
#ifndef _WIN64 // [
    ULONG UserTime;
#endif // ]
    union
    {
        KSEMAPHORE SuspendSemaphore;
        struct
        {
            UCHAR SuspendSemaphorefill[FIELD_OFFSET(KSEMAPHORE, Limit) + 4]; // 20 / 28
#ifdef _WIN64 // [
            ULONG SListFaultCount;
#endif // ]
        };
    };
#ifndef _WIN64 // [
    ULONG SListFaultCount;
#endif // ]
    LIST_ENTRY ThreadListEntry;
    LIST_ENTRY MutantListHead;
    PVOID SListFaultAddress;
#ifdef _M_AMD64 // [
    LONG64 ReadOperationCount;
    LONG64 WriteOperationCount;
    LONG64 OtherOperationCount;
    LONG64 ReadTransferCount;
    LONG64 WriteTransferCount;
    LONG64 OtherTransferCount;
#endif // ]
    PKTHREAD_COUNTERS ThreadCounters;
    PXSTATE_SAVE XStateSave;
} KTHREAD;
