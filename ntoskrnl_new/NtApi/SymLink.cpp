
#include <Ob/Ob.hpp>

extern "C"
__kernel_entry
NTSTATUS
NTAPI
NtCreateSymbolicLinkObject (
    _Out_ PHANDLE SymbolicLinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PUNICODE_STRING Name)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtOpenSymbolicLinkObject (
    _Out_ PHANDLE SymbolicLinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
__kernel_entry
NTSTATUS
NTAPI
NtQuerySymbolicLinkObject (
    _In_ HANDLE SymLinkObjHandle,
    _Out_ PUNICODE_STRING LinkTarget,
    _Out_opt_ PULONG DataWritten)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

