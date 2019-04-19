typedef struct _KTHREAD
{
    DISPATCHER_HEADER Header;
    LIST_ENTRY MutantListHead;
    PVOID InitialStack;
    ULONG_PTR StackLimit; // FIXME: PVOID
    PVOID KernelStack;
    KSPIN_LOCK ThreadLock;
    union
    {
        KAPC_STATE ApcState;
        struct
        {
            UCHAR ApcStateFill[FIELD_OFFSET(KAPC_STATE, UserApcPending) + 1];
            UCHAR ApcQueueable;
            /* On x86, the following members "fall out" of the union */
            volatile UCHAR NextProcessor;
            volatile UCHAR DeferredProcessor;
            UCHAR AdjustReason;
            SCHAR AdjustIncrement;
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
    union
    {
        PKWAIT_BLOCK WaitBlockList;
        PKGATE GateObject;
    };
    BOOLEAN Alertable;
    BOOLEAN WaitNext;
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
    union
    {
        KTIMER Timer;
        struct
        {
            UCHAR TimerFill[FIELD_OFFSET(KTIMER, Period) + sizeof(LONG)];
#if !defined(_WIN64) // [
        };
    };
#endif // ]
            union
            {
                struct
                {
                    ULONG AutoAlignment:1;
                    ULONG DisableBoost:1;
                    LONG ReservedFlags:30;
                };
                LONG ThreadFlags;
            };
#if defined(_WIN64) // [
        };
    };
#endif // ]
    union
    {
        DECLSPEC_ALIGN(8) KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
        struct
        {
            UCHAR WaitBlockFill0[FIELD_OFFSET(KWAIT_BLOCK, SpareByte)]; // 32bit = 23, 64bit = 43
            BOOLEAN SystemAffinityActive;
        };
        struct
        {
            UCHAR WaitBlockFill1[1 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareByte)]; // 47 / 91
            CCHAR PreviousMode;
        };
        struct
        {
            UCHAR WaitBlockFill2[2 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareByte)]; // 71 / 139
            UCHAR ResourceIndex;
        };
        struct
        {
            UCHAR WaitBlockFill3[3 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareByte)]; // 95 / 187
            UCHAR LargeStack;
        };
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
            UCHAR WaitBlockFill7[3 * sizeof(KWAIT_BLOCK) + FIELD_OFFSET(KWAIT_BLOCK, SpareLong)];
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
    PVOID CallbackStack;
    PVOID ServiceTable;
#if defined(_WIN64) // [
    ULONG KernelLimit;
#endif // ]
    UCHAR ApcStateIndex;
    UCHAR IdealProcessor;
    BOOLEAN Preempted;
    BOOLEAN ProcessReadyQueue;
#ifdef _WIN64 // [
    PVOID Win32kTable;
    ULONG Win32kLimit;
#endif // ]
    BOOLEAN KernelStackResident;
    SCHAR BasePriority;
    SCHAR PriorityDecrement;
    CHAR Saturation;
    KAFFINITY UserAffinity;
    struct _KPROCESS *Process;
    KAFFINITY Affinity;
    PKAPC_STATE ApcStatePointer[2];
    union
    {
        KAPC_STATE SavedApcState;
        struct
        {
            UCHAR SavedApcStateFill[FIELD_OFFSET(KAPC_STATE, UserApcPending) + 1];
            CCHAR FreezeCount;
#ifdef _WIN64 // [
            CCHAR SuspendCount;
            UCHAR UserIdealProcessor;
            UCHAR CalloutActive;
            UCHAR CodePatchInProgress;
#endif // ]
        };
    };
#ifndef _WIN64 // [
    CCHAR SuspendCount;
    UCHAR UserIdealProcessor;
    UCHAR CalloutActive;
#endif // ]
#if defined(_M_IX86) // [
    UCHAR Iopl;
#endif // ]
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
            UCHAR SuspendApcFill3[FIELD_OFFSET(KAPC, SystemArgument1)];
            PVOID TlsArray;
        };
        struct
        {
            UCHAR SuspendApcFill4[FIELD_OFFSET(KAPC, SystemArgument2)]; // 40 / 72
            PVOID LegoData;
        };
        struct
        {
            UCHAR SuspendApcFill5[FIELD_OFFSET(KAPC, Inserted) + 1]; // 47 / 83
            UCHAR PowerState;
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
    PVOID SListFaultAddress;
#ifdef _M_AMD64 // [
    LONG64 ReadOperationCount;
    LONG64 WriteOperationCount;
    LONG64 OtherOperationCount;
    LONG64 ReadTransferCount;
    LONG64 WriteTransferCount;
    LONG64 OtherTransferCount;
#endif // ]
} KTHREAD;
