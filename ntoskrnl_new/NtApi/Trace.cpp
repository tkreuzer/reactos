
#include <ntoskrnl.h>

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtTraceControl (
    _In_ ULONG FunctionCode,
    _In_reads_bytes_opt_(InBufferLen) PVOID InBuffer,
    _In_ ULONG InBufferLen,
    _Out_writes_bytes_opt_(OutBufferLen) PVOID OutBuffer,
    _In_ ULONG OutBufferLen,
    _Out_ PULONG ReturnSize
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtTraceEvent(
    _In_opt_ HANDLE TraceHandle,
    _In_ ULONG Flags,
    _In_ ULONG FieldSize,
    _In_ PVOID Fields)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
