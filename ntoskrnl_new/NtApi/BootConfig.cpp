
#include <ntoskrnl.h>
#include <Ex/Ex.hpp>

extern "C" {

typedef struct _BOOT_OPTIONS *PBOOT_OPTIONS;
typedef struct _BOOT_ENTRY *PBOOT_ENTRY;
typedef struct _EFI_DRIVER_ENTRY *PEFI_DRIVER_ENTRY;
typedef struct _FILE_PATH *PFILE_PATH;

typedef enum _FILTER_BOOT_OPTION_OPERATION
{
    Unknown,
} FILTER_BOOT_OPTION_OPERATION;

__kernel_entry
NTSTATUS
NTAPI
NtQueryBootOptions (
    _Out_writes_bytes_opt_(*BootOptionsLength) PBOOT_OPTIONS BootOptions,
    _Inout_ PULONG BootOptionsLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetBootOptions (
    _In_ PBOOT_OPTIONS BootOptions,
    _In_ ULONG FieldsToChange)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtFilterBootOption (
    _In_ FILTER_BOOT_OPTION_OPERATION FilterOperation,
    _In_ ULONG ObjectType,
    _In_ ULONG ElementType,
    _In_reads_bytes_opt_(DataSize) PVOID Data,
    _In_ ULONG DataSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtEnumerateBootEntries (
    _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
    _Inout_ PULONG BufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryBootEntryOrder (
    _Out_writes_opt_(*Count) PULONG Ids,
    _Inout_ PULONG Count)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetBootEntryOrder (
    _In_reads_(Count) PULONG Ids,
    _In_ ULONG Count)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtAddBootEntry (
    _In_ PBOOT_ENTRY BootEntry,
    _Out_opt_ PULONG Id)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtModifyBootEntry (
    _In_ PBOOT_ENTRY BootEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDeleteBootEntry (
    _In_ ULONG Id)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtEnumerateDriverEntries (
    _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
    _Inout_ PULONG BufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryDriverEntryOrder (
    _Out_writes_opt_(*Count) PULONG Ids,
    _Inout_ PULONG Count)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetDriverEntryOrder (
    _In_reads_(Count) PULONG Ids,
    _In_ ULONG Count)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtAddDriverEntry (
    _In_ PEFI_DRIVER_ENTRY DriverEntry,
    _Out_opt_ PULONG Id)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtModifyDriverEntry (
    _In_ PEFI_DRIVER_ENTRY DriverEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDeleteDriverEntry (
    _In_ ULONG Id)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtEnumerateSystemEnvironmentValuesEx (
    _In_ ULONG InformationClass,
    _Out_ PVOID Buffer,
    _Inout_ PULONG BufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQuerySystemEnvironmentValue (
    _In_ PUNICODE_STRING VariableName,
    _Out_writes_bytes_(ValueLength) PWSTR VariableValue,
    _In_ USHORT ValueLength,
    _Out_opt_ PUSHORT ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQuerySystemEnvironmentValueEx (
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _Out_writes_bytes_opt_(*ValueLength) PVOID Value,
    _Inout_ PULONG ValueLength,
    _Out_opt_ PULONG Attributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetSystemEnvironmentValue (
    _In_ PUNICODE_STRING VariableName,
    _In_ PUNICODE_STRING VariableValue)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetSystemEnvironmentValueEx (
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _In_reads_bytes_opt_(ValueLength) PVOID Value,
    _In_ ULONG ValueLength,
    _In_ ULONG Attributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtTranslateFilePath (
    _In_ PFILE_PATH InputFilePath,
    _In_ ULONG OutputType,
    _Out_writes_bytes_opt_(*OutputFilePathLength) PFILE_PATH OutputFilePath,
    _Inout_opt_ PULONG OutputFilePathLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
