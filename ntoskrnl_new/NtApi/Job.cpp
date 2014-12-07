
#include <ntoskrnl.h>

extern "C" {
// winnt.h
typedef enum _JOBOBJECTINFOCLASS
{
    JobObjectBasicAccountingInformation = 1,
    JobObjectBasicLimitInformation,
    JobObjectBasicProcessIdList,
    JobObjectBasicUIRestrictions,
    JobObjectSecurityLimitInformation,  // deprecated
    JobObjectEndOfJobTimeInformation,
    JobObjectAssociateCompletionPortInformation,
    JobObjectBasicAndIoAccountingInformation,
    JobObjectExtendedLimitInformation,
    JobObjectJobSetInformation,
    JobObjectGroupInformation,
    JobObjectNotificationLimitInformation,
    JobObjectLimitViolationInformation,
    JobObjectGroupInformationEx,
    JobObjectCpuRateControlInformation,
    JobObjectCompletionFilter,
    JobObjectCompletionCounter,
    JobObjectReserved1Information = 18,
    JobObjectReserved2Information,
    JobObjectReserved3Information,
    JobObjectReserved4Information,
    JobObjectReserved5Information,
    JobObjectReserved6Information,
    JobObjectReserved7Information,
    JobObjectReserved8Information,
    JobObjectReserved9Information,
    JobObjectReserved10Information,
    JobObjectReserved11Information,
    JobObjectReserved12Information,
    JobObjectReserved13Information,
    JobObjectReserved14Information,
    JobObjectNetRateControlInformation,
    JobObjectNotificationLimitInformation2,
    JobObjectLimitViolationInformation2,
    JobObjectCreateSilo,
    JobObjectSiloBasicInformation,
    JobObjectSiloRootDirectory,
    JobObjectServerSiloBasicInformation,
    JobObjectServerSiloServiceSessionId,
    JobObjectServerSiloInitialize,
    JobObjectServerSiloRunningState,
    MaxJobObjectInfoClass
} JOBOBJECTINFOCLASS;

__kernel_entry
NTSTATUS
NTAPI
NtCreateJobObject (
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtOpenJobObject (
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationJobObject (
    _In_opt_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength,
    _Out_opt_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetInformationJobObject (
    _In_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtOpenJobObjectToken (
    _In_ HANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE TokenHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtIsProcessInJob (
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE JobHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtAssignProcessToJobObject (
    _In_ HANDLE JobHandle,
    _In_ HANDLE ProcessHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtTerminateJobObject (
    _In_ HANDLE JobHandle,
    _In_ NTSTATUS ExitStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}



}; // extern "C"
