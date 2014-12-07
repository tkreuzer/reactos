
#include "Ke/Thread.hpp"

extern "C" {

typedef PVOID PPS_ATTRIBUTE_LIST;
typedef PVOID PINITIAL_TEB;

// ntddk.h
typedef enum _THREADINFOCLASS
{
    ThreadBasicInformation          = 0,
    ThreadTimes                     = 1,
    ThreadPriority                  = 2,
    ThreadBasePriority              = 3,
    ThreadAffinityMask              = 4,
    ThreadImpersonationToken        = 5,
    ThreadDescriptorTableEntry      = 6,
    ThreadEnableAlignmentFaultFixup = 7,
    ThreadEventPair_Reusable        = 8,
    ThreadQuerySetWin32StartAddress = 9,
    ThreadZeroTlsCell               = 10,
    ThreadPerformanceCount          = 11,
    ThreadAmILastThread             = 12,
    ThreadIdealProcessor            = 13,
    ThreadPriorityBoost             = 14,
    ThreadSetTlsArrayAddress        = 15,
    ThreadIsIoPending               = 16,
    ThreadHideFromDebugger          = 17,
    ThreadBreakOnTermination        = 18,
    ThreadSwitchLegacyState         = 19,
    ThreadIsTerminated              = 20,
    ThreadLastSystemCall            = 21,
    ThreadIoPriority                = 22,
    ThreadCycleTime                 = 23,
    ThreadPagePriority              = 24,
    ThreadActualBasePriority        = 25,
    ThreadTebInformation            = 26,
    ThreadCSwitchMon                = 27,
    ThreadCSwitchPmu                = 28,
    ThreadWow64Context              = 29,
    ThreadGroupInformation          = 30,
    ThreadUmsInformation            = 31,
    ThreadCounterProfiling          = 32,
    ThreadIdealProcessorEx          = 33,
    ThreadCpuAccountingInformation  = 34,
    ThreadSuspendCount              = 35,
    MaxThreadInfoClass              = 40,
} THREADINFOCLASS;

__kernel_entry
NTSTATUS
NTAPI
NtCreateThread (
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _Out_ PCLIENT_ID ClientId,
    _In_ PCONTEXT ThreadContext,
    _In_ PINITIAL_TEB InitialTeb,
    _In_ BOOLEAN CreateSuspended)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCreateThreadEx (
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_ PVOID /* PUSER_THREAD_START_ROUTINE */ StartRoutine,
    _In_opt_ PVOID Argument,
    _In_ ULONG CreateFlags,
    _In_ SIZE_T ZeroBits,
    _In_ SIZE_T StackSize,
    _In_ SIZE_T MaximumStackSize,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtOpenThread (
  _Out_  PHANDLE ThreadHandle,
  _In_   ACCESS_MASK DesiredAccess,
  _In_   POBJECT_ATTRIBUTES ObjectAttributes,
  _In_   PCLIENT_ID ClientId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationThread (
    IN HANDLE ThreadHandle,
    IN THREADINFOCLASS ThreadInformationClass,
    OUT PVOID ThreadInformation,
    IN ULONG ThreadInformationLength,
    OUT PULONG ReturnLength OPTIONAL)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetInformationThread (
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _In_reads_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtGetContextThread (
    _In_ HANDLE ThreadHandle,
    _Inout_ PCONTEXT ThreadContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetContextThread (
    _In_ HANDLE ThreadHandle,
    _In_ PCONTEXT ThreadContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtGetNextThread (
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewThreadHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSuspendThread (
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtResumeThread (
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtAlertResumeThread (
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtAlertThread (
    _In_ HANDLE ThreadHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtAlertThreadByThreadId (
    _In_ HANDLE ThreadId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtTestAlert (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtUmsThreadYield (
    _In_ PVOID SchedulerParam)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtRegisterThreadTerminatePort (
    _In_ HANDLE PortHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtTerminateThread (
    _In_opt_ HANDLE ThreadHandle,
    _In_ NTSTATUS ExitStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"
