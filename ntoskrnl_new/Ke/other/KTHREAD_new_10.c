typedef struct _KTHREAD
{
    DISPATCHER_HEADER Header;
    PVOID SListFaultAddress;
    ULONGLONG QuantumTarget;
    PVOID InitialStack;
    PVOID StackLimit;
    PVOID StackBase;
    KSPIN_LOCK ThreadLock;
    ULONGLONG CycleTime;
#ifndef _WIN64 // [
    ULONG HighCycleTime;
    PVOID ServiceTable;
#endif // ]
    ULONG CurrentRunTime;
    ULONG ExpectedRunTime;
    PVOID KernelStack;
    PXSAVE_FORMAT StateSaveArea;
    struct _KSCHEDULING_GROUP* SchedulingGroup;
    KWAIT_STATUS_REGISTER WaitRegister;
    BOOLEAN Running;
    BOOLEAN Alerted[MaximumMode];
    union
    {
        struct
        {
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
            ULONG AutoBoostActive:1;
#else // ][
            ULONG KernelStackResident:1;
#endif // ]
            ULONG ReadyTransition:1;
#if (NTDDI_VERSION < NTDDI_WIN10) // [
            ULONG ProcessReadyQueue:1;
#endif // ]
            ULONG WaitNext:1;
            ULONG SystemAffinityActive:1;
            ULONG Alertable:1;
#if (NTDDI_VERSION < NTDDI_WINBLUE) // [
            ULONG CodePatchInProgress:1;
#endif // ]
            ULONG UserStackWalkActive:1;
            ULONG ApcInterruptRequest:1;
            ULONG QuantumEndMigrate:1;
            ULONG UmsDirectedSwitchEnable:1;
            ULONG TimerActive:1;
            ULONG SystemThread:1;
            ULONG ProcessDetachActive:1;
            ULONG CalloutActive:1;
            ULONG ScbReadyQueue:1;
            ULONG ApcQueueable:1;
            ULONG ReservedStackInUse:1;
            ULONG UmsPerformingSyscall:1;
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
            ULONG TimerSuspended:1;
            ULONG SuspendedWaitMode:1;
            ULONG SuspendSchedulerApcWait:1;
            ULONG Reserved:12;
#else // ][
#if (NTDDI_VERSION >= NTDDI_WINBLUE) // [
            ULONG ApcPendingReload:1;
#endif // ]
            ULONG Reserved:13;
#endif // ]
        };
        LONG MiscFlags;
    };
    union
    {
        struct
        {
            ULONG AutoAlignment:1;
            ULONG DisableBoost:1;
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
            ULONG ThreadFlagsSpare0:1;
#else // ][
            ULONG UserAffinitySet:1;
#endif // ]
            ULONG AlertedByThreadId:1;
            ULONG QuantumDonation:1;
            ULONG EnableStackSwap:1;
            ULONG GuiThread:1;
            ULONG DisableQuantum:1;
#if (NTDDI_VERSION >= NTDDI_WINBLUE) // [
            ULONG ChargeOnlySchedulingGroup:1;
#else // ][
            ULONG ChargeOnlyGroup:1;
#endif // ]
            ULONG DeferPreemption:1;
            ULONG QueueDeferPreemption:1;
            ULONG ForceDeferSchedule:1;
#if (NTDDI_VERSION >= NTDDI_WINBLUE) // [
            ULONG SharedReadyQueueAffinity:1;
#else // ][
            ULONG ExplicitIdealProcessor:1;
#endif // ]
            ULONG FreezeCount:1;
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
            ULONG TerminationApcRequest:1;
            ULONG AutoBoostEntriesExhausted:1;
            ULONG KernelStackResident:1;
            ULONG CommitFailTerminateRequest:1;
            ULONG ProcessStackCountDecremented:1;
            ULONG ThreadFlagsSpare:5;
            ULONG EtwStackTraceApcInserted:8;
#elif (NTDDI_VERSION >= NTDDI_WINBLUE) // ][
            ULONG TerminationApcRequest:1;
            ULONG AutoBoostEntriesExhausted:1;
            ULONG EtwStackTraceApcInserted:8;
            ULONG ReservedFlags:8;
#else // ][
            ULONG EtwStackTraceApcInserted:8;
            ULONG ReservedFlags:10;
#endif // ]
        };
        LONG ThreadFlags;
    };
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
    UCHAR Tag;
    UCHAR SystemHeteroCpuPolicy;
    struct
    {
        UCHAR UserHeteroCpuPolicy:7;
        UCHAR ExplicitSystemHeteroCpuPolicy:1;
    };
    UCHAR Spare0;
#else // ][
    ULONG Spare0;
#endif // ]
    ULONG SystemCallNumber;
#ifdef _WIN64 // [
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
    ULONG Spare10;
#else // ][
    ULONG Spare1;
#endif // ]
#endif // ]
    PVOID FirstArgument;
    PKTRAP_FRAME TrapFrame;
    union
    {
        KAPC_STATE ApcState;
        struct
        {
            UCHAR ApcStateFill[FIELD_OFFSET(KAPC_STATE, UserApcPending) + 1]; // 23/43
            SCHAR Priority;
#ifdef _WIN64 // [
            ULONG UserIdealProcessor;
#endif // ]
        };
    };
#ifndef _WIN64 // [
    ULONG UserIdealProcessor;
    ULONG ContextSwitches;
    volatile UCHAR State;
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
    CHAR Spare12;
#else // ][
    CHAR NpxState;
#endif // ]
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
#if (NTDDI_VERSION >= NTDDI_WINBLUE) // [
    PDISPATCHER_HEADER Queue;
#else // ][
    PKQUEUE Queue;
#endif // ]
    PVOID Teb;
    ULONG64 RelativeTimerBias;
    KTIMER Timer;
    union
    {
        DECLSPEC_ALIGN(8) KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
#ifdef _WIN64 // [
        struct
        {
            UCHAR WaitBlockFill4[FIELD_OFFSET(KWAIT_BLOCK, SpareLong)]; // 20
            ULONG ContextSwitches;
        };
        struct
        {
            UCHAR WaitBlockFill5[1 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareLong)]; // 68
            UCHAR State;
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
            CHAR Spare13;
#else // ][
            CHAR NpxState;
#endif // ]
            UCHAR WaitIrql;
            CHAR WaitMode;
        };
        struct
        {
            UCHAR WaitBlockFill6[2 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareLong)]; // 116
            ULONG WaitTime;
        };
        struct
        {
            UCHAR WaitBlockFill7[3 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareLong)]; // 164
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
        struct
        {
            UCHAR WaitBlockFill8[FIELD_OFFSET(KWAIT_BLOCK, SparePtr)]; // 20/40
            PKTHREAD_COUNTERS ThreadCounters;
        };
        struct
        {
            UCHAR WaitBlockFill9[1 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SparePtr)]; // 44/88
            PXSTATE_SAVE XStateSave;
        };
        struct
        {
            UCHAR WaitBlockFill10[2 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SparePtr)]; // 68/136
            PVOID Win32Thread;
        };
        struct
        {
            UCHAR WaitBlockFill11[3 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, Object)]; // 88/176
#ifdef _WIN64 // [
            struct _UMS_CONTROL_BLOCK* Ucb;
            struct _KUMS_CONTEXT_HEADER* Uch;
#else // ][
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
        };
    };
#ifdef _WIN64 // [
    PVOID TebMappedLowVa;
#endif // ]
    LIST_ENTRY QueueListEntry;
#if (NTDDI_VERSION >= NTDDI_WINBLUE) // [
    union
    {
        ULONG NextProcessor;
        struct
        {
            ULONG NextProcessorNumber : 31;
            ULONG SharedReadyQueue : 1;
        };
    };
    LONG QueuePriority;
#else // ][
    ULONG NextProcessor;
    ULONG DeferredProcessor;
#endif // ]
    PKPROCESS Process;
    union
    {
        GROUP_AFFINITY UserAffinity;
        struct
        {
            UCHAR UserAffinityFill[FIELD_OFFSET(GROUP_AFFINITY, Reserved)]; // 6/10
            CCHAR PreviousMode;
            SCHAR BasePriority;
            union
            {
                SCHAR PriorityDecrement;
                struct
                {
                    UCHAR ForegroundBoost : 4;
                    UCHAR UnusualBoost : 4;
                };
            };
            BOOLEAN Preempted;
            UCHAR AdjustReason;
            SCHAR AdjustIncrement;
        };
    };
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
    ULONG_PTR AffinityVersion;
#endif // ]
    union
    {
        GROUP_AFFINITY Affinity;
        struct
        {
            UCHAR AffinityFill[FIELD_OFFSET(GROUP_AFFINITY, Reserved)]; // 6/10
            UCHAR ApcStateIndex;
            UCHAR WaitBlockCount;
            ULONG IdealProcessor;
        };
    };
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
#ifdef _WIN64 // [
    UINT64 NpxState;
#else // ][
    ULONG Spare15[1];
#endif // ]
#else // ][
    PKAPC_STATE ApcStatePointer[2];
#endif // ]
    union
    {
        KAPC_STATE SavedApcState;
        struct
        {
            UCHAR SavedApcStateFill[FIELD_OFFSET(KAPC_STATE, UserApcPending) + 1]; // 23/43
            UCHAR WaitReason;
#ifdef _WIN64 // [
            CCHAR SuspendCount;
            CHAR Saturation;
            USHORT SListFaultCount;
#endif // ]
        };
    };
#ifndef _WIN64 // [
    CCHAR SuspendCount;
    CHAR Saturation;
    USHORT SListFaultCount;
#endif // ]
    union
    {
        KAPC SchedulerApc;
        struct
        {
            UCHAR SchedulerApcFill0[FIELD_OFFSET(KAPC, SpareByte0)]; // 1
            UCHAR ResourceIndex;
        };
        struct
        {
            UCHAR SchedulerApcFill1[FIELD_OFFSET(KAPC, SpareByte1)]; // 3
            UCHAR QuantumReset;
        };
        struct
        {
            UCHAR SchedulerApcFill2[FIELD_OFFSET(KAPC, SpareLong0)]; // 4
            ULONG KernelTime;
        };
        struct
        {
            UCHAR SchedulerApcFill3[FIELD_OFFSET(KAPC, SystemArgument1)]; // 36/64
            PKPRCB WaitPrcb;
        };
        struct
        {
            UCHAR SchedulerApcFill4[FIELD_OFFSET(KAPC, SystemArgument2)]; // 40/72
            PVOID LegoData;
        };
        struct
        {
            UCHAR SchedulerApcFill5[FIELD_OFFSET(KAPC, Inserted) + 1]; // 47/83
            UCHAR CallbackNestingLevel;
#ifdef _WIN64 // [
            ULONG UserTime;
#endif // ]
        };
    };
#ifndef _WIN64 // [
    ULONG UserTime;
#endif // ]
    KEVENT SuspendEvent;
    LIST_ENTRY ThreadListEntry;
    LIST_ENTRY MutantListHead;
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
    UCHAR AbEntrySummary;
    UCHAR AbWaitEntryCount;
    USHORT Spare20;
#ifdef _WIN64 // [
    ULONG SecureThreadCookie;
#endif // ]
#endif // ]
#if (NTDDI_VERSION >= NTDDI_WINBLUE) // [
#if (NTDDI_VERSION < NTDDI_WIN10) // [
    SINGLE_LIST_ENTRY LockEntriesFreeList;
#endif // ]
    KLOCK_ENTRY LockEntries[6];
    SINGLE_LIST_ENTRY PropagateBoostsEntry;
    SINGLE_LIST_ENTRY IoSelfBoostsEntry;
    UCHAR PriorityFloorCounts[16];
    ULONG PriorityFloorSummary;
    LONG AbCompletedIoBoostCount;
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
    SHORT KeReferenceCount;
    UCHAR AbOrphanedEntrySummary;
    UCHAR AbOwnedEntryCount;
#else // ][
    SHORT AbReferenceCount;
    UCHAR AbFreeEntryCount;
    UCHAR AbWaitEntryCount;
#endif // ]
    ULONG ForegroundLossTime;
    union
    {
        LIST_ENTRY GlobalForegroundListEntry;
        struct
        {
            SINGLE_LIST_ENTRY ForegroundDpcStackListEntry;
            ULONG_PTR InGlobalForegroundList;
        };
    };
#endif // ]
#ifdef _WIN64 // [
    INT64 ReadOperationCount;
    INT64 WriteOperationCount;
    INT64 OtherOperationCount;
    INT64 ReadTransferCount;
    INT64 WriteTransferCount;
    INT64 OtherTransferCount;
#endif // ]
#if (NTDDI_VERSION >= NTDDI_WIN10) // [
    struct _KSCB* QueuedScb;
#ifndef _WIN64 // [
    UINT64 NpxState;
#endif // ]
#endif // ]
} KTHREAD, *PKTHREAD;
