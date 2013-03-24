
#include "ntosbase.h"

extern "C" {

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmAddVerifierThunks (
  _In_reads_bytes_ (ThunkBufferSize) PVOID ThunkBuffer,
  _In_ ULONG ThunkBufferSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

LOGICAL
NTAPI
MmIsDriverVerifying (
  _In_ struct _DRIVER_OBJECT *DriverObject)
{
    UNIMPLEMENTED;
    return 0;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmIsVerifierEnabled (
  _Out_ PULONG VerifierFlags)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
MmPageEntireDriver (
  _In_ PVOID AddressWithinSection)
{
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmResetDriverPaging (
  _In_ PVOID AddressWithinSection)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
PVOID
NTAPI
MmGetSystemRoutineAddress (
  _In_ PUNICODE_STRING SystemRoutineName)
{
    UNIMPLEMENTED;
    return NULL;
}


// private

NTSTATUS
NTAPI
MmLoadSystemImage (
    IN PUNICODE_STRING FileName,
    IN PUNICODE_STRING NamePrefix OPTIONAL,
    IN PUNICODE_STRING LoadedName OPTIONAL,
    IN ULONG Flags,
    OUT PVOID *ModuleObject,
    OUT PVOID *ImageBaseAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmUnloadSystemImage (
    IN PVOID ImageHandle)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCheckSystemImage (
    IN HANDLE ImageHandle,
    IN BOOLEAN PurgeSection)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MiResolveImageReferences (
    IN PVOID ImageBase,
    IN PUNICODE_STRING ImageFileDirectory,
    IN PUNICODE_STRING NamePrefix OPTIONAL,
    OUT PCHAR *MissingApi,
    OUT PWCHAR *MissingDriver,
    OUT struct _LOAD_IMPORTS** LoadImports)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCallDllInitialize (
    IN struct _LDR_DATA_TABLE_ENTRY* LdrEntry,
    IN PLIST_ENTRY ListHead)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
MmFreeDriverInitialization (
    IN struct _LDR_DATA_TABLE_ENTRY* LdrEntry)
{
    UNIMPLEMENTED;
}

}; // extern "C"
