
#include "Thread.hpp"
#include <Ob/Ob.hpp>

extern "C" {

POBJECT_TYPE PsThreadType;

//@ stdcall -stub PsGetCurrentThread() KeGetCurrentThread
// @ stdcall -stub PsGetCurrentThreadPreviousMode() PsGetCurrentThreadPreviousMode

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PsLookupThreadByThreadId (
    _In_ HANDLE ThreadId,
    _Outptr_ PETHREAD *Thread)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
HANDLE
NTAPI
PsGetCurrentThreadId (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
HANDLE
NTAPI
PsGetThreadId (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
PsGetThreadSessionId (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return 0;
}

// ntosp.h
PVOID
NTAPI
PsGetThreadWin32Thread (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PVOID
NTAPI
PsGetCurrentThreadWin32Thread (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
VOID
NTAPI
PsSetThreadWin32Thread (
    _Inout_ PETHREAD Thread,
    _In_opt_ PVOID Win32Thread,
    _In_ PVOID PrevWin32Thread)
{
    __debugbreak();
}

// ntosp.h
LONGLONG
NTAPI
PsGetThreadCreateTime (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return 0;
}

// ntosp.h
PVOID
NTAPI
PsGetThreadTeb (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PVOID
NTAPI
PsGetCurrentThreadTeb (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PEPROCESS
NTAPI
PsGetThreadProcess (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PEPROCESS
NTAPI
PsGetCurrentThreadProcess (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
HANDLE
NTAPI
PsGetThreadProcessId (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
HANDLE
NTAPI
PsGetCurrentThreadProcessId (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
NTAPI
PsGetCurrentThreadStackBase (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
NTAPI
PsGetCurrentThreadStackLimit (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
ULONG
NTAPI
PsGetThreadFreezeCount (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return 0;
}

// ntosp.h
NTSTATUS
NTAPI
PsGetContextThread (
    _In_ PETHREAD Thread,
    _Inout_ PCONTEXT ThreadContext,
    _In_ KPROCESSOR_MODE Mode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
PsSetContextThread (
    _In_ PETHREAD Thread,
    _In_ PCONTEXT ThreadContext,
    _In_ KPROCESSOR_MODE Mode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PsGetThreadExitStatus (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
BOOLEAN
NTAPI
PsGetThreadHardErrorsAreDisabled (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
VOID
NTAPI
PsSetThreadHardErrorsAreDisabled (
    _In_ PETHREAD Thread,
    _In_ BOOLEAN HardErrorsAreDisabled)
{
    __debugbreak();
}

// ntosp.h
BOOLEAN
NTAPI
PsIsSystemThread (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
BOOLEAN
NTAPI
PsIsThreadImpersonating (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
PsIsThreadTerminating (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return FALSE;
}

// ntddk.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
PsIsCurrentThreadPrefetching (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// ntddk.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
PsSetCurrentThreadPrefetching (
    _In_ BOOLEAN Prefetching)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
typedef
VOID
(NTAPI *PCREATE_THREAD_NOTIFY_ROUTINE) (
    _In_ HANDLE ProcessId,
    _In_ HANDLE ThreadId,
    _In_ BOOLEAN Create);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsSetCreateThreadNotifyRoutine (
    _In_ PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
PsRemoveCreateThreadNotifyRoutine (
    _In_ PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
PsCreateSystemThreadEx (
    _Out_ PHANDLE ThreadHandle,
    _In_ ULONG DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_  HANDLE ProcessHandle,
    _Out_opt_ PCLIENT_ID ClientId,
    _In_ PKSTART_ROUTINE StartRoutine,
    _In_opt_ _When_(return >= 0, __drv_aliasesMem) PVOID StartContext,
    _In_opt_ PGROUP_AFFINITY GroupAffinity,
    _In_opt_ PULONG IdealProcessor)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
PsCreateSystemThread (
    _Out_ PHANDLE ThreadHandle,
    _In_ ULONG DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_  HANDLE ProcessHandle,
    _Out_opt_ PCLIENT_ID ClientId,
    _In_ PKSTART_ROUTINE StartRoutine,
    _In_opt_ _When_(return >= 0, __drv_aliasesMem) PVOID StartContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsTerminateSystemThread (
    _In_ NTSTATUS ExitStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PsReferenceKernelStack (
    _Inout_ PETHREAD Thread)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PsDereferenceKernelStack (
    _Inout_ PETHREAD Thread)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
PsEnterPriorityRegion (
    VOID)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
PsLeavePriorityRegion (
    VOID)
{
    __debugbreak();
}

// ntosp.h
PVOID
NTAPI
PsGetCurrentThreadWin32ThreadAndEnterCriticalRegion (
    _Out_ PHANDLE ProcessId)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
PsWrapApcWow64Thread (
    _Inout_ PVOID *ApcContext,
    _Inout_ PVOID *ApcRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#if 0 // internal? from ntosp.h
// ntosp.h
typedef
NTSTATUS
NTAPI
PS_SUSPEND_THREAD (
    _In_ PETHREAD Thread,
    _Out_opt_ PULONG PreviousSuspendCount);
typedef PS_SUSPEND_THREAD *PPS_SUSPEND_THREAD;

// ntosp.h
PS_SUSPEND_THREAD PsSuspendThread;

// ntosp.h
typedef
NTSTATUS
NTAPI
PS_RESUME_THREAD (
    _In_ PETHREAD Thread,
    _Out_opt_ PULONG PreviousSuspendCount);
typedef PS_RESUME_THREAD *PPS_RESUME_THREAD;

// ntosp.h
PS_RESUME_THREAD PsResumeThread;

typedef enum _PSCREATETHREADNOTIFYTYPE {
    PsCreateThreadNotifyNonSystem = 0
} PSCREATETHREADNOTIFYTYPE;

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
PsSetCreateThreadNotifyRoutineEx(
    _In_ PSCREATETHREADNOTIFYTYPE NotifyType,
    _In_ PVOID NotifyInformation
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PVOID
PsGetThreadProperty(
    _In_ PETHREAD Thread,
    _In_ ULONG_PTR Key,
    _In_ ULONG Flags
    );

#endif // 0

} // extern "C"
