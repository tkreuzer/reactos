
#include <Ex/Ex.hpp>

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtOpenEventPair (
    _Out_ PHANDLE EventPairHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWaitLowEventPair (
    _In_ HANDLE EventPairHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWaitHighEventPair (
    _In_ HANDLE EventPairHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetLowEventPair (
    _In_ HANDLE EventPairHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetHighEventPair (
    _In_ HANDLE EventPairHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetLowWaitHighEventPair (
    _In_ HANDLE EventPairHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetHighWaitLowEventPair (
    _In_ HANDLE EventPairHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
