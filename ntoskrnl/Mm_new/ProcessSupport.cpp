
#include "ntosbase.h"

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
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmInitializeHandBuiltProcess2 (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
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

NTSTATUS
NTAPI
MmSetMemoryPriorityProcess (
    IN PEPROCESS Process,
    IN UCHAR MemoryPriority)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
