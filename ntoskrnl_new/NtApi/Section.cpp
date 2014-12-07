
#include <ntoskrnl.h>

extern "C" {

// wdm.h
typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
typedef enum _SECTION_INFORMATION_CLASS
{
    SectionBasicInformation = 0,
    SectionImageInformation = 1,
    SectionRelocationInformation = 2,
    MaxSectionInfoClass = 3
} SECTION_INFORMATION_CLASS;

_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSection (
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtQuerySection (
    _In_ HANDLE SectionHandle,
    _In_ SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
    _In_ SIZE_T SectionInformationLength,
    _Out_opt_ PSIZE_T ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtExtendSection (
    _In_ HANDLE SectionHandle,
    _Inout_ PLARGE_INTEGER NewSectionSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_Post_satisfies_(*ViewSize >= _Old_(*ViewSize))
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtMapViewOfSection (
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_ (*BaseAddress, _Readable_bytes_ (*ViewSize) _Writable_bytes_ (*ViewSize) _Post_readable_byte_size_ (*ViewSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnmapViewOfSection(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtUnmapViewOfSectionEx (
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtAreMappedFilesTheSame (
    _In_ PVOID File1MappedAsAnImage,
    _In_ PVOID File2MappedAsFile)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
