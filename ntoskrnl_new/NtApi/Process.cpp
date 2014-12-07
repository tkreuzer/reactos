
#include "Ke/Process.hpp"

extern "C" {

typedef PVOID PPS_CREATE_INFO;
typedef PVOID PPS_ATTRIBUTE_LIST;

typedef enum _PROCESSINFOCLASS
{
    ProcessBasicInformation                 = 0,
    ProcessQuotaLimits                      = 1,
    ProcessIoCounters                       = 2,
    ProcessVmCounters                       = 3,
    ProcessTimes                            = 4,
    ProcessBasePriority                     = 5,
    ProcessRaisePriority                    = 6,
    ProcessDebugPort                        = 7,
    ProcessExceptionPort                    = 8,
    ProcessAccessToken                      = 9,
    ProcessLdtInformation                   = 10,
    ProcessLdtSize                          = 11,
    ProcessDefaultHardErrorMode             = 12,
    ProcessIoPortHandlers                   = 13,
    ProcessPooledUsageAndLimits             = 14,
    ProcessWorkingSetWatch                  = 15,
    ProcessUserModeIOPL                     = 16,
    ProcessEnableAlignmentFaultFixup        = 17,
    ProcessPriorityClass                    = 18,
    ProcessWx86Information                  = 19,
    ProcessHandleCount                      = 20,
    ProcessAffinityMask                     = 21,
    ProcessPriorityBoost                    = 22,
    ProcessDeviceMap                        = 23,
    ProcessSessionInformation               = 24,
    ProcessForegroundInformation            = 25,
    ProcessWow64Information                 = 26,
    ProcessImageFileName                    = 27,
    ProcessLUIDDeviceMapsEnabled            = 28,
    ProcessBreakOnTermination               = 29,
    ProcessDebugObjectHandle                = 30,
    ProcessDebugFlags                       = 31,
    ProcessHandleTracing                    = 32,
    ProcessIoPriority                       = 33,
    ProcessExecuteFlags                     = 34,
    ProcessTlsInformation                   = 35,
    ProcessCookie                           = 36,
    ProcessImageInformation                 = 37,
    ProcessCycleTime                        = 38,
    ProcessPagePriority                     = 39,
    ProcessInstrumentationCallback          = 40,
    ProcessThreadStackAllocation            = 41,
    ProcessWorkingSetWatchEx                = 42,
    ProcessImageFileNameWin32               = 43,
    ProcessImageFileMapping                 = 44,
    ProcessAffinityUpdateMode               = 45,
    ProcessMemoryAllocationMode             = 46,
    ProcessGroupInformation                 = 47,
    ProcessTokenVirtualizationEnabled       = 48,
    ProcessOwnerInformation                 = 49,
    ProcessWindowInformation                = 50,
    ProcessHandleInformation                = 51,
    ProcessMitigationPolicy                 = 52,
    ProcessDynamicFunctionTableInformation  = 53,
    ProcessHandleCheckingMode               = 54,
    ProcessKeepAliveCount                   = 55,
    ProcessRevokeFileHandles                = 56,
    ProcessWorkingSetControl                = 57,
    ProcessHandleTable                      = 58,
    ProcessCheckStackExtentsMode            = 59,
    ProcessCommandLineInformation           = 60,
    ProcessProtectionInformation            = 61,
    ProcessMemoryExhaustion                 = 62,
    ProcessFaultInformation                 = 63,
    ProcessTelemetryIdInformation           = 64,
    ProcessCommitReleaseEligibility         = 65,
    MaxProcessInfoClass
} PROCESSINFOCLASS;

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtCreateProcess (
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritObjectTable,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtCreateProcessEx (
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ ULONG Flags,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle,
    _In_ ULONG JobMemberLevel)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCreateUserProcess (
    _Out_ PHANDLE ProcessHandle,
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK ProcessDesiredAccess,
    _In_ ACCESS_MASK ThreadDesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ProcessObjectAttributes,
    _In_opt_ POBJECT_ATTRIBUTES ThreadObjectAttributes,
    _In_ ULONG ProcessFlags,
    _In_ ULONG ThreadFlags,
    _In_opt_ PVOID /* PRTL_USER_PROCESS_PARAMETERS */ ProcessParameters,
    _Inout_ PPS_CREATE_INFO CreateInfo,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtOpenProcess (
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationProcess (
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_opt_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtSetInformationProcess (
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _In_reads_bytes_opt_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtGetNextProcess (
    _In_opt_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewProcessHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtSuspendProcess (
    _In_ HANDLE ProcessHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtResumeProcess (
    _In_ HANDLE ProcessHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// zwapi.h
__kernel_entry
NTSTATUS
NTAPI
NtTerminateProcess (
    _In_opt_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"
