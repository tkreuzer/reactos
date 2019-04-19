
#include <ntoskrnl.h>
#include "Ke_internal.h"
#define _Inout_
#define _Out_

PKPROCESS KiGlobalSystemProcess;

typedef struct _KINITIAL_SYSTEM_FRAME
{
    ULONG64 Return;
    KSTART_FRAME;
} KINITIAL_SYSTEM_FRAME, *PKINITIAL_SYSTEM_FRAME;

typedef struct _KINITIAL_USER_FRAME
{
    ULONG64 Return;
    KTRAP_FRAME TrapFrame;
    XSAVE_FORMAT LegacyFloatingSave;
} KINITIAL_USER_FRAME, *PKINITIAL_USER_FRAME;

typedef struct _KSWITCH_FRAME
{
    ULONG64 Return;
    KNONVOLATILES;
} KSWITCH_FRAME, *PKSWITCH_FRAME;

void KxUserThreadEntryPoint(void);
void KxSystemThreadEntryPoint(void);

VOID
NTAPI
KiSystemThreadStartup()
{
    __debugbreak();
}

VOID
NTAPI
KiUserThreadStartup()
{
    __debugbreak();
}

VOID
KxInitializeStartFrame(
    PKTHREAD Thread,
    struct _TEB *Teb,
    PVOID StartRoutine,
    PVOID StartContext)
{

    /* Check if this is a user thread */
    if (Teb)
    {
        PKINITIAL_USER_FRAME InitialFrame;

        InitialFrame = (PKINITIAL_USER_FRAME)Thread->InitialStack - 1;

        Thread->KernelStack = InitialFrame;
        //Thread->StateSaveArea = &InitialFrame->LegacyFloatingSave;
        Thread->TrapFrame = &InitialFrame->TrapFrame;

        InitialFrame->Return = (ULONG64)KxUserThreadEntryPoint;

        RtlZeroMemory(&InitialFrame->TrapFrame, sizeof(KTRAP_FRAME));
        InitialFrame->TrapFrame.Rip = (ULONG64)StartRoutine;
        InitialFrame->TrapFrame.Rcx = (ULONG64)StartContext;
        InitialFrame->TrapFrame.SegCs = KGDT64_R3_CODE | RPL_MASK;
        InitialFrame->TrapFrame.SegDs = KGDT64_R3_DATA | RPL_MASK;
        InitialFrame->TrapFrame.SegEs = KGDT64_R3_DATA | RPL_MASK;
        InitialFrame->TrapFrame.SegFs = KGDT64_R3_CMTEB | RPL_MASK;
        InitialFrame->TrapFrame.SegGs = KGDT64_R3_DATA | RPL_MASK;
        InitialFrame->TrapFrame.SegSs = KGDT64_R3_DATA | RPL_MASK;
        //InitialFrame->TrapFrame.Rsp = Teb->NtTib.StackBase;
    }
    else
    {
        PKINITIAL_SYSTEM_FRAME InitialFrame;

        InitialFrame = (PKINITIAL_SYSTEM_FRAME)Thread->InitialStack - 1;

        Thread->KernelStack = InitialFrame;
        //Thread->StateSaveArea = NULL;
        Thread->TrapFrame = NULL;

        InitialFrame->Return = (ULONG64)KxSystemThreadEntryPoint;
        InitialFrame->StartRoutine = StartRoutine;
        InitialFrame->StartContext = StartContext;

    }

}


VOID
FORCEINLINE
KxSaveNpxState(PKTHREAD Thread)
{
    //if (Thread->StateSaveArea)
    {
        //__
    }
}



VOID
NTAPI
KeInitializeThread(
    PKTHREAD Thread,
    PKPROCESS Process,
    PVOID Stack,
    PVOID Teb,
    PVOID StartRoutine,
    PVOID StartContext)
{
    /* zero out the structure */
    RtlZeroMemory(Thread, sizeof(KTHREAD));

    /* Initialize the dispatcher header */
    Thread->Header.Lock = 0;
    Thread->Header.Type = ThreadObject;
    InitializeListHead(&(Thread->Header.WaitListHead));

    /* Set the process */
    Thread->Process = Process;

    /* Set previous mode and the TEB for user threads */
    Thread->PreviousMode = Teb ? UserMode : KernelMode;
    Thread->Teb = Teb;

    /* Setup the stack (KernelStack is set later) */
    Thread->StackBase = Stack;
    Thread->StackLimit = (ULONG64)Stack - KERNEL_STACK_SIZE;
    Thread->InitialStack = Thread->StackBase;


    Thread->Priority = LOW_PRIORITY;
    // Thread->BasePriority = Process->BasePriority;

    InitializeListHead(&Thread->MutantListHead);

    /* Do the arcitecture specific initialization of the initial stack frame */
    KxInitializeStartFrame(Thread, Teb, StartRoutine, StartContext);

    Thread->KernelStackResident = TRUE;
    //Thread->Running = FALSE;
    Thread->State = Initialized;

#if 0
    Thread->QuantumTarget;
    Thread->ThreadLock;
    Thread->CycleTime;
    Thread->CurrentRunTime;
    Thread->ExpectedRunTime;
    Thread->SchedulingGroup;
    Thread->WaitRegister;
    Thread->Alerted[2];
    Thread->ReadyTransition : 1;
    Thread->ProcessReadyQueue : 1;
    Thread->SystemAffinityActive : 1;
    Thread->Alertable : 1;
    Thread->ApcInterruptRequest : 1;
    Thread->QuantumEndMigrate : 1;
    Thread->UmsDirectedSwitchEnable : 1;
    Thread->SystemThread : 1;
    Thread->ScbReadyQueue : 1;
    Thread->ApcQueueable : 1;
    Thread->AutoAlignment : 1;
    Thread->DisableBoost : 1;
    Thread->UserAffinitySet : 1;
    Thread->AlertedByThreadId : 1;
    Thread->QuantumDonation : 1;
    Thread->EnableStackSwap : 1;
    Thread->DisableQuantum : 1;
    Thread->ChargeOnlyGroup : 1;
    Thread->DeferPreemption : 1;
    Thread->QueueDeferPreemption : 1;
    Thread->ForceDeferSchedule : 1;
    Thread->ExplicitIdealProcessor : 1;
    Thread->FreezeCount : 1;
    Thread->EtwStackTraceApcInserted : 8;
    Thread->FirstArgument;
    Thread->ApcState;
    Thread->UserIdealProcessor;
    Thread->WaitStatus;
    Thread->WaitListEntry;
    Thread->Queue;
    Thread->Timer;
    Thread->NpxState;
    Thread->WaitIrql;
    Thread->WaitMode;
    Thread->WaitTime;
    Thread->XStateSave;
    Thread->Ucb;
    Thread->Uch;
    Thread->TebMappedLowVa;
    Thread->QueueListEntry;
    Thread->NextProcessor;
    Thread->DeferredProcessor;
    Thread->UserAffinity;
    Thread->BasePriority;
    Thread->PriorityDecrement;
    Thread->ForegroundBoost : 4;
    Thread->UnusualBoost : 4;
    Thread->Preempted;
    Thread->AdjustReason;
    Thread->AdjustIncrement;
    Thread->Affinity;
    Thread->ApcStateIndex;
    Thread->WaitBlockCount;
    Thread->IdealProcessor;
    Thread->ApcStatePointer[2];
    Thread->SchedulerApc;
    Thread->ResourceIndex;
    Thread->QuantumReset;
    Thread->KernelTime;
    Thread->WaitPrcb;
    Thread->UserTime;
    Thread->SuspendEvent;
    Thread->ThreadListEntry;
#endif
}

VOID
NTAPI
KxAttachProcessAddressSpace(
    PKPROCESS Process)
{
    __debugbreak();
}


#undef KeGetCurrentThread
PKTHREAD
NTAPI
KeGetCurrentThread(VOID)
{
    return _KeGetCurrentThread();
}


BOOLEAN
NTAPI
KeAlertThread(
    IN PKTHREAD Thread,
    IN KPROCESSOR_MODE AlertMode)
{
    __debugbreak();
    return 0;
}

LONG
NTAPI
KeCapturePersistentThreadState(
	PCONTEXT Context,
	PKTHREAD Thread,
	ULONG BugCheckCode,
	ULONG BugCheckParameter1,
	ULONG BugCheckParameter2,
	ULONG BugCheckParameter3,
	ULONG BugCheckParameter4,
	PVOID VirtualAddress)
{
    __debugbreak();
    return 0;
}

KPRIORITY
NTAPI
KeQueryPriorityThread(
    IN PRKTHREAD  Thread)
{
    __debugbreak();
    return 0;
}

ULONG
NTAPI
KeQueryRuntimeThread(
    __in   PKTHREAD Thread,
    __out  PULONG UserTime)
{
    __debugbreak();
    return 0;
}

ULONG64
NTAPI
KeQueryTotalCycleTimeThread (
    _Inout_  PKTHREAD Thread,
    _Out_    PULONG64 CycleTimeStamp)
{
    __debugbreak();
    return 0;
}

KPRIORITY
NTAPI
KeSetPriorityThread(
  IN OUT PKTHREAD Thread,
  IN KPRIORITY Priority)
{
    KPRIORITY OldPriority;

    OldPriority = Thread->Priority;

    Thread->Priority = (SCHAR)Priority;

    return OldPriority;
}

LONG
NTAPI
KeSetBasePriorityThread(
  IN OUT PRKTHREAD Thread,
  IN LONG Increment)
{
    PKPROCESS Process = Thread->Process;
    LONG OldPriority;

    OldPriority = Thread->BasePriority - Process->BasePriority;

    Thread->BasePriority = (SCHAR)(Process->BasePriority + Increment);

    return OldPriority;
}

VOID
NTAPI
KeSetActualBasePriorityThread()
{
    __debugbreak();
}

VOID
NTAPI
KeSetAffinityThread()
{
    __debugbreak();
}

VOID
NTAPI
KeSetSystemAffinityThread(
  IN KAFFINITY Affinity)
{
    __debugbreak();
}

KAFFINITY
NTAPI
KeSetSystemAffinityThreadEx(
  IN KAFFINITY Affinity)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeSetSystemGroupAffinityThread(
  IN PGROUP_AFFINITY Affinity,
  OUT PGROUP_AFFINITY PreviousAffinity OPTIONAL)
{
    __debugbreak();
}

UCHAR
NTAPI
KeSetIdealProcessorThread(
  IN OUT PKTHREAD Thread,
  IN UCHAR Processor)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeRevertToUserAffinityThread()
{
}

VOID
NTAPI
KeRevertToUserAffinityThreadEx(
  IN KAFFINITY Affinity)
{
    __debugbreak();
}

VOID
NTAPI
KeRevertToUserGroupAffinityThread(
  IN PGROUP_AFFINITY PreviousAffinity)
{
    __debugbreak();
}

VOID
NTAPI
KeTestAlertThread()
{
    __debugbreak();
}

