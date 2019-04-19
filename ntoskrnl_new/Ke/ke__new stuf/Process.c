
#include <ntoskrnl.h>
#include "Ke_internal.h"

KPROCESS KiGlobalSystemProcess;

#define _Inout_

typedef PKPROCESS PRKPROCESS;

VOID
NTAPI
KeInitializeProcess(
    __out PKPROCESS Process,
    __in ULONG_PTR DirectoryTableBase)
{

    Process->Header.Lock = 0;
    Process->Header.Type = ProcessObject;
    Process->Header.SignalState = 0;
    InitializeListHead(&Process->Header.WaitListHead);

    KeInitializeSpinLock(&Process->ProcessLock);


    Process->DirectoryTableBase = DirectoryTableBase;

    /* Initialize list heads */
    InitializeListHead(&Process->ProfileListHead);
    InitializeListHead(&Process->ThreadListHead);
    InitializeListHead(&Process->ReadyListHead);

    /* Flags */
    Process->ProcessFlags = 0;
    Process->Flags.ExecuteOptions = 0;

    Process->ProcessListEntry;
    Process->SwapListEntry.Next = NULL;

    /* SMP stuff */
    //Process->Affinity = 1;
    //Process->ActiveProcessors = 1; // FIXME: what to put here?
    Process->IdealGlobalNode = 0;


    Process->InstrumentationCallback = NULL;

    Process->BasePriority = LOW_PRIORITY;
    Process->QuantumReset;

    Process->Visited = 0;
    Process->ThreadSeed[8];
    Process->IdealNode[8];
    Process->Spare0 = 0;
    Process->StackCount.State = 0;
    Process->StackCount.StackCount = 0;

    /* LDT stuff */
    Process->LdtFreeSelectorHint = 0;
    Process->LdtTableLength = 0;
    //Process->LdtSystemDescriptor = 0;
    Process->LdtBaseAddress = 0;
    //Process->LdtProcessLock = 0;

    /* Initialize stats */
    Process->CycleTime = 0;
    Process->ContextSwitches = 0;
    Process->FreezeCount = 0;
    Process->KernelTime = 0;
    Process->UserTime = 0;
}


BOOLEAN
NTAPI
KeIsAttachedProcess(VOID)
{
    return (KeGetCurrentThread()->ApcStateIndex > 0);
}


VOID
NTAPI
KeAttachProcess(
    IN OUT PKPROCESS Process)
{
    KeStackAttachProcess(Process, &KeGetCurrentThread()->SavedApcState);
}

VOID
NTAPI
KeDetachProcess(void)
{
    KeUnstackDetachProcess(&KeGetCurrentThread()->SavedApcState);
}

ULONG64
NTAPI
KeQueryTotalCycleTimeProcess(
  IN OUT PKPROCESS Process,
  OUT PULONG64 CycleTimeStamp)

{
    return Process->CycleTime;
}

