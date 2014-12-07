
#include "Kep.hpp"

extern "C" {

// ntosp.h
_IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
KeUserModeCallback (
    _In_ ULONG ApiNumber,
    _In_reads_bytes_(InputLength) PVOID InputBuffer,
    _In_ ULONG InputLength,
    _Outptr_result_bytebuffer_maybenull_(*OutputLength) PVOID *OutputBuffer,
    _Out_ PULONG OutputLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
__kernel_entry
NTSTATUS
NTAPI
NtCallbackReturn (
    _In_reads_bytes_opt_(OutputLength) PVOID OutputBuffer,
    _In_ ULONG OutputLength,
    _In_ NTSTATUS Status)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
