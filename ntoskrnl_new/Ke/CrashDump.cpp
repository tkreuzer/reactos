
#include "Kep.hpp"

extern "C" {

// wdm.h / ntosp.h
NTSTATUS
NTAPI
KeInitializeCrashDumpHeader(
    _In_ ULONG DumpType,
    _In_ ULONG Flags,
    _Out_writes_bytes_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG BufferNeeded)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
