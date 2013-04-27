#include "ntosbase.h"

extern "C" {


ULONG
NTAPI
MmTrimAllSystemPageableMemory (
    IN ULONG PurgeTransitionList)
{
    UNIMPLEMENTED;
    return 0;
}

BOOLEAN
NTAPI
MmIsFileObjectAPagingFile (
    PFILE_OBJECT FileObject)
{
    UNIMPLEMENTED;
    return 0;
}

NTSTATUS
NTAPI
NtCreatePagingFile (
    _In_ PUNICODE_STRING FileName,
    _In_ PLARGE_INTEGER InitialSize,
    _In_ PLARGE_INTEGER MaxiumSize,
    _In_ ULONG Reserved)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}



}; // extern "C"
