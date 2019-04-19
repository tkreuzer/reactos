
#pragma once

#include "Kep.hpp"
#include "DispatcherObject.hpp"


namespace Ke {

class THREAD : public DISPATCHER_OBJECT
{
#ifdef _REACTOS_ // [ using old win 2l3 structure
    LIST_ENTRY _MutantListHead;
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
    LONG_PTR _WaitStatus;
    union
    {
        PKWAIT_BLOCK _WaitBlockList;
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

/// ***************************************************************************
#else // ][ the real win10 shit!

    typedef union _THREAD_FLAGS
    {
        struct
        {
            ULONG AutoAlignment:1;
            ULONG DisableBoost:1;
            ULONG ThreadFlagsSpare0:1;
            ULONG AlertedByThreadId:1;
            ULONG QuantumDonation:1;
            ULONG EnableStackSwap:1;
            ULONG GuiThread:1;
            ULONG DisableQuantum:1;
            ULONG ChargeOnlySchedulingGroup:1;
            ULONG DeferPreemption:1;
            ULONG QueueDeferPreemption:1;
            ULONG ForceDeferSchedule:1;
            ULONG SharedReadyQueueAffinity:1;
            ULONG FreezeCount:1;
            ULONG TerminationApcRequest:1;
            ULONG AutoBoostEntriesExhausted:1;
            ULONG KernelStackResident:1;
            ULONG CommitFailTerminateRequest:1;
            ULONG ProcessStackCountDecremented:1;
            ULONG ThreadFlagsSpare:5;
            ULONG EtwStackTraceApcInserted:8;
        };
        LONG AsLong;
    } THREAD_FLAGS;

    typedef union _MISC_FLAGS
    {
        struct
        {
            ULONG AutoBoostActive:1;
            ULONG ReadyTransition:1;
            ULONG WaitNext:1;
            ULONG SystemAffinityActive:1;
            ULONG Alertable:1;
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
            ULONG TimerSuspended:1;
            ULONG SuspendedWaitMode:1;
            ULONG SuspendSchedulerApcWait:1;
            ULONG Reserved:12;
        };
        LONG AsLong;
    } MISC_FLAGS ;

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
    MISC_FLAGS MiscFlags;
    THREAD_FLAGS _ThreadFlags;
    UCHAR Tag;
    UCHAR SystemHeteroCpuPolicy;
    struct
    {
        UCHAR UserHeteroCpuPolicy:7;
        UCHAR ExplicitSystemHeteroCpuPolicy:1;
    };
    UCHAR Spare0;
    ULONG SystemCallNumber;
#ifdef _WIN64 // [
    ULONG Spare10;
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
    CHAR Spare12;
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
    PDISPATCHER_HEADER Queue;
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
            CHAR Spare13;
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
    ULONG_PTR AffinityVersion;
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
#ifdef _WIN64 // [
    UINT64 NpxState;
#else // ][
    ULONG Spare15[1];
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
    UCHAR AbEntrySummary;
    UCHAR AbWaitEntryCount;
    USHORT Spare20;
#ifndef _WIN64 // [
    ULONG SecureThreadCookie;
#endif // ]
    KLOCK_ENTRY LockEntries[6];
    SINGLE_LIST_ENTRY PropagateBoostsEntry;
    SINGLE_LIST_ENTRY IoSelfBoostsEntry;
    UCHAR PriorityFloorCounts[16];
    ULONG PriorityFloorSummary;
    LONG AbCompletedIoBoostCount;
    SHORT KeReferenceCount;
    UCHAR AbOrphanedEntrySummary;
    UCHAR AbOwnedEntryCount;
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
#ifdef _WIN64 // [
    INT64 ReadOperationCount;
    INT64 WriteOperationCount;
    INT64 OtherOperationCount;
    INT64 ReadTransferCount;
    INT64 WriteTransferCount;
    INT64 OtherTransferCount;
#endif // ]
    KSCB* QueuedScb;
#ifndef _WIN64 // [
    UINT64 NpxState;
#endif // ]

#endif // ] _REACTOS_

public:

    inline
    BOOLEAN
    TryAcquireWaitStatus (
        _In_ ULONG_PTR NewWaitStatus)
    {
        if (_WaitStatus != MAXULONG_PTR)
        {
            return FALSE;
        }

        return (InterlockedCompareExchange(&_WaitStatus,
                                           NewWaitStatus,
                                           MAXULONG_PTR) == MAXULONG_PTR);
    }

    BOOLEAN
    HasActiveWaitBlocks (
        VOID)
    {
        ULONG i;

        NT_ASSERT(_WaitBlockList != NULL);
        NT_ASSERT(_WaitBlockCount > 1);

        /// \todo This might be slower than an interlocked count-down, needs
        ///       to be investigated (cache miss is likely and expensive)
        for (i = 0; i < _WaitBlockCount; i++)
        {
            if (_WaitBlockList[i].BlockState == WaitBlockActive)
            {
                return TRUE;
            }
        }

        return FALSE;
    }


};


}; // namespace Ke
