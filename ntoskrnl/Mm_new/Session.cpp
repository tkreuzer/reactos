
#include "ntosbase.h"

extern "C" {

// private

NTSTATUS
NTAPI
MmSessionCreate (
    OUT PULONG SessionId)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmSessionDelete (
    IN ULONG SessionId)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

ULONG
NTAPI
MmGetSessionId (
    IN PEPROCESS Process)
{
    UNIMPLEMENTED;
    return 0;
}

ULONG
NTAPI
MmGetSessionLocaleId (
    VOID)
{
    UNIMPLEMENTED;
    return 0;
}

BOOLEAN
NTAPI
MmIsSessionAddress (
    IN PVOID Address)
{
    UNIMPLEMENTED;
    return 0;
}

}; // extern "C"
