
#include <ntoskrnl.h>

extern "C" {

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtGetWriteWatch (
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _Out_writes_opt_(*EntriesInUserAddressArray) PVOID *UserAddressArray,
    _Inout_opt_ PULONG_PTR EntriesInUserAddressArray,
    _Out_opt_ PULONG Granularity)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtResetWriteWatch (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
