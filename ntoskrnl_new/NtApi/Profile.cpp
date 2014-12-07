
#include <ntoskrnl.h>
#include <Ex/Ex.hpp>
#include <Ke/Ke.hpp>

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtCreateProfile (
    _Out_ PHANDLE ProfileHandle,
    _In_ HANDLE Process OPTIONAL,
    _In_ PVOID ProfileBase,
    _In_ SIZE_T ProfileSize,
    _In_ ULONG BucketSize,
    _In_reads_bytes_(BufferSize) PULONG Buffer,
    _In_ ULONG BufferSize,
    _In_ KPROFILE_SOURCE ProfileSource,
    _In_ KAFFINITY Affinity)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCreateProfileEx (
    _Out_ PHANDLE ProfileHandle,
    _In_ HANDLE Process OPTIONAL,
    _In_ PVOID ProfileBase,
    _In_ SIZE_T ProfileSize,
    _In_ ULONG BucketSize,
    _In_reads_bytes_(BufferSize) PULONG Buffer,
    _In_ ULONG BufferSize,
    _In_ KPROFILE_SOURCE ProfileSource,
    _In_ USHORT GroupCount,
    _In_reads_(GroupCount) PGROUP_AFFINITY AffinityArray)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtStartProfile (
    _In_ HANDLE ProfileHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtStopProfile (
    _In_ HANDLE ProfileHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


};
