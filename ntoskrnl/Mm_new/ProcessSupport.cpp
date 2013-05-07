
#include "ntosbase.h"
#include <ndk/pstypes.h>
#include "AddressSpace.hpp"
#include "VadTable.hpp"

namespace Mm {
extern "C" {

// private

NTSTATUS
NTAPI
MmSetExecuteOptions (
    IN ULONG ExecuteOptions)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmGetExecuteOptions (
    IN PULONG ExecuteOptions)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCreatePeb (
    _In_ PEPROCESS Process,
    _In_ struct _INITIAL_PEB* InitialPeb,
    _Out_ struct _PEB** BasePeb)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCreateTeb (
    _In_ PEPROCESS Process,
    _In_ PCLIENT_ID ClientId,
    _In_ struct _INITIAL_TEB* InitialTeb,
    _Out_ struct _TEB** BaseTeb)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmDeleteTeb (
    struct _EPROCESS *Process,
    struct _TEB* Teb)
{
    UNIMPLEMENTED;
}


NTSTATUS
NTAPI
MmInitializeHandBuiltProcess (
    IN PEPROCESS Process,
    IN PULONG_PTR DirectoryTableBase)
{
    /* Share the directory base with the idle process */
    DirectoryTableBase[0] = PsGetCurrentProcess()->Pcb.DirectoryTableBase[0];
    DirectoryTableBase[1] = PsGetCurrentProcess()->Pcb.DirectoryTableBase[1];

    /* Initialize the Addresss Space */
    KeInitializeGuardedMutex(&Process->AddressCreationLock);
    KeInitializeSpinLock(&Process->HyperSpaceLock);
    Process->Vm.WorkingSetExpansionLinks.Flink = NULL;
    ASSERT(Process->VadRoot.NumberGenericTableElements == 0);
    Process->VadRoot.BalancedRoot.u1.Parent = &Process->VadRoot.BalancedRoot;

    /* Use idle process Working set */
    Process->Vm.VmWorkingSetList = PsGetCurrentProcess()->Vm.VmWorkingSetList;

    GetProcessAddressSpace(Process)->GetVadTable()->Initialize(FALSE);

    /* Done */
    Process->HasAddressSpace = TRUE;//??
    return STATUS_SUCCESS;}

NTSTATUS
NTAPI
MmInitializeHandBuiltProcess2 (
    IN PEPROCESS Process)
{
    /* Nothing to do */
    return STATUS_SUCCESS;
}

BOOLEAN
NTAPI
MmCreateProcessAddressSpace (
    IN ULONG MinWs,
    IN PEPROCESS Dest,
    IN PULONG_PTR DirectoryTableBase)
{
    UNIMPLEMENTED;
    return 0;
}

NTSTATUS
NTAPI
MmInitializeProcessAddressSpace (
    IN PEPROCESS Process,
    IN PEPROCESS Clone OPTIONAL,
    IN PVOID Section OPTIONAL,
    IN OUT PULONG Flags,
    IN POBJECT_NAME_INFORMATION *AuditName OPTIONAL)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmCleanProcessAddressSpace (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmDeleteProcessAddressSpace (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

UCHAR
NTAPI
MmSetMemoryPriorityProcess (
    IN PEPROCESS Process,
    IN UCHAR MemoryPriority)
{
    UCHAR OldPriority;

    /* Save the old priority and update it */
    OldPriority = Process->Vm.Flags.MemoryPriority;
    Process->Vm.Flags.MemoryPriority = MemoryPriority;

    /* Return the old priority */
    return OldPriority;
}

}; // extern "C"
}; // namespace Mm
