
#include "Rtl.hpp"

extern "C" {

typedef struct _IMAGE_NT_HEADERS *PIMAGE_NT_HEADERS;

// ntosifs.h
NTSTATUS
NTAPI
RtlImageNtHeaderEx(
    _In_ ULONG Flags,
    _In_ PVOID Base,
    _In_ ULONG64 Size,
    _Outptr_ PIMAGE_NT_HEADERS *OutHeaders)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosifs.h
_Must_inspect_result_
PIMAGE_NT_HEADERS
NTAPI
RtlImageNtHeader (
    _In_ PVOID Base)
{
    __debugbreak();
    return NULL;
}

// http://filelog.net/func/RtlImageDirectoryEntryToData
// On success return NotEqual 0
PVOID
NTAPI
RtlImageDirectoryEntryToData (
    PVOID /* [HMODULE-PVOID] */ BaseAddress,
    BOOLEAN MappedAsImage,
    USHORT Directory,
    PULONG Size)
{
    __debugbreak();
    return NULL;
}

} // extern "C"
