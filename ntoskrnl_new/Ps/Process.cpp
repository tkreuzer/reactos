
#include "Process.hpp"
#include "Job.hpp"
#include <Ob/Ob.hpp>
#include <Se/Se.hpp>

extern "C" {

POBJECT_TYPE PsProcessType;
PEPROCESS PsInitialSystemProcess;

//NTSTATUS
//NTAPI
//PsTerminateProcess (
//    _Inout_ PEPROCESS Process,
//    _In_ NTSTATUS Status);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PEPROCESS
NTAPI
_PsGetCurrentProcess (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PsLookupProcessByProcessId (
    _In_ HANDLE ProcessId,
    _Outptr_ PEPROCESS *Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//@ stdcall -stub PsLookupProcessThreadByCid(ptr ptr ptr)

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
HANDLE
NTAPI
PsGetProcessId (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
HANDLE
NTAPI
PsGetCurrentProcessId(
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
ULONG
NTAPI
PsGetProcessSessionId (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return 0;
}

// ntosp.h
ULONG
NTAPI
PsGetProcessSessionIdEx (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG
NTAPI
PsGetCurrentProcessSessionId (
    VOID)
{
    __debugbreak();
    return 0;
}

// ntosp.h
PVOID
NTAPI
PsGetProcessWin32Process (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
PsSetProcessWin32Process (
    _In_ PEPROCESS Process,
    _In_opt_ PVOID Win32Process,
    _In_ PVOID PrevWin32Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PVOID
NTAPI
PsGetCurrentProcessWin32Process (
    VOID)
{
    __debugbreak();
    return NULL;
}

#ifdef _M_AMD64

// ntosp.h
PVOID
NTAPI
PsGetProcessWow64Process (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PVOID
NTAPI
PsGetCurrentProcessWow64Process (
    VOID)
{
    __debugbreak();
    return NULL;
}

#endif

// ntosp.h
HANDLE
NTAPI
PsGetProcessWin32WindowStation (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
VOID
NTAPI
PsSetProcessWindowStation(
    _Out_ PEPROCESS Process,
    _In_opt_ HANDLE Win32WindowStation)
{
    __debugbreak();
}

// ntosp.h
PEJOB
NTAPI
PsGetProcessJob (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PVOID
NTAPI
PsGetProcessCommonJob (
    _In_ PEPROCESS Process1,
    _In_ PEPROCESS Process2)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PPEB
NTAPI
PsGetProcessPeb (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// undocumented
typedef ULONG PS_PROTECTION;

// ntosp.h
PS_PROTECTION
NTAPI
PsGetProcessProtection (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PsGetProcessExitStatus (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
LARGE_INTEGER
NTAPI
PsGetProcessExitTime(
    VOID)
{
    LARGE_INTEGER exitTime;
    exitTime.QuadPart = 0;
    __debugbreak();
    return exitTime;
}

// ntosp.h
BOOLEAN
NTAPI
PsGetProcessExitProcessCalled (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
UCHAR
NTAPI
PsGetProcessPriorityClass (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return 0;
}

// ntosp.h
VOID
NTAPI
PsSetProcessPriorityClass (
    _Out_ PEPROCESS Process,
    _In_ UCHAR PriorityClass)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PsSetProcessPriorityByClass (
    _Inout_ PEPROCESS Process,
    _In_ PSPROCESSPRIORITYMODE PriorityMode)
{
    __debugbreak();
}

// ntosp.h
PVOID
NTAPI
PsGetProcessSecurityPort (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
PsSetProcessSecurityPort (
    _Out_ PEPROCESS Process,
    _In_ PVOID Port)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
SE_SIGNING_LEVEL
NTAPI
PsGetProcessSignatureLevel (
    _In_ PEPROCESS Process,
    _Out_opt_ PSE_SIGNING_LEVEL SectionSignatureLevel)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONGLONG
NTAPI
PsGetProcessCreateTimeQuadPart (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return 0;
}

// ntosp.h
PVOID
NTAPI
PsGetProcessDebugPort (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
UCHAR *
NTAPI
PsGetProcessImageFileName (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PVOID
NTAPI
PsGetProcessSectionBaseAddress (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
HANDLE
NTAPI
PsGetProcessInheritedFromUniqueProcessId (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
BOOLEAN
NTAPI
PsIsSystemProcess (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
LOGICAL
NTAPI
PsIsProtectedProcess (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
LOGICAL
NTAPI
PsIsProtectedProcessLight (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
BOOLEAN
NTAPI
PsIsProcessBeingDebugged (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsQueryProcessAttributesByToken (
    _Inout_ PACCESS_TOKEN Token,
    _Out_opt_ PBOOLEAN SystemAppIdentifier,
    _Out_opt_ PBOOLEAN PackagedApplication)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsQueryProcessExceptionFlags (
    _Inout_ PEPROCESS TargetProcess,
    _In_ ULONG Flags,
    _Out_ PPS_EXCEPTION_FLAGS ExceptionFlags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG64
NTAPI
PsQueryTotalCycleTimeProcess (
    _Inout_ PEPROCESS Process,
    _Out_ PULONG64 CycleTimeStamp)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PsChargeProcessPagedPoolQuota (
    _Inout_ PEPROCESS Process,
    _In_ SIZE_T Amount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PsChargeProcessNonPagedPoolQuota (
    _Inout_ PEPROCESS Process,
    _In_ SIZE_T Amount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PsChargeProcessPoolQuota (
    _In_ PEPROCESS Process,
    _In_ POOL_TYPE PoolType,
    _In_ ULONG_PTR Amount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PsChargePoolQuota (
    _In_ PEPROCESS Process,
    _In_ POOL_TYPE PoolType,
    _In_ ULONG_PTR Amount)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PsReturnProcessPagedPoolQuota (
    _Inout_ PEPROCESS Process,
    _In_ SIZE_T Amount)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PsReturnProcessNonPagedPoolQuota (
    _Inout_ PEPROCESS Process,
    _In_ SIZE_T Amount)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PsReturnPoolQuota (
    _In_ PEPROCESS Process,
    _In_ POOL_TYPE PoolType,
    _In_ ULONG_PTR Amount)
{
    __debugbreak();
}

// ntosp.h
PVOID
NTAPI
PsChargeProcessWakeCounter (
    _Inout_ PEPROCESS Process,
    _In_ ULONG Flags,
    _In_ PS_WAKE_REASON WakeReason,
    _In_ ULONG_PTR Tag)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
VOID
NTAPI
PsReleaseProcessWakeCounter (
    _In_ PVOID Reference,
    _In_ ULONG_PTR Tag)
{
    __debugbreak();
}



// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsAcquireProcessExitSynchronization (
    _Inout_ PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsReleaseProcessExitSynchronization (
    _Inout_ PEPROCESS Process)
{
    __debugbreak();
}


// ntosp.h
NTSTATUS
NTAPI
PsSuspendProcess (
    _Inout_ PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
PsResumeProcess (
    _Inout_ PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsSetCreateProcessNotifyRoutine (
    _In_ PCREATE_PROCESS_NOTIFY_ROUTINE NotifyRoutine,
    _In_ BOOLEAN Remove)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsSetCreateProcessNotifyRoutineEx (
    _In_ PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine,
    _In_ BOOLEAN Remove)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsReferenceProcessFilePointer (
    _In_ PEPROCESS Process,
    _Out_ PVOID *pFilePointer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#if 0 // internal? from ntosp.h
NTSTATUS
PsCaptureUserProcessParameters (
    _Outptr_ PRTL_USER_PROCESS_PARAMETERS *CapturedProcessParameters,
    _In_ PRTL_USER_PROCESS_PARAMETERS UserProcessParameters
    );
#endif // 0

} // extern "C"
