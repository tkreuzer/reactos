
#include <Ex/Ex.hpp>

extern "C"
__kernel_entry
NTSTATUS
NTAPI
NtCreateKeyedEvent (
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
__kernel_entry
NTSTATUS
NTAPI
NtOpenKeyedEvent (
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtWaitForKeyedEvent (
    _In_opt_ HANDLE Handle,
    _In_ PVOID Key,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtReleaseKeyedEvent (
    _In_opt_ HANDLE Handle,
    _In_ PVOID Key,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


