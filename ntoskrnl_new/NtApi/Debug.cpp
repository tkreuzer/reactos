
#include <ntoskrnl.h>

extern "C" {

_IRQL_requires_same_
__kernel_entry
NTSTATUS
NTAPI
NtQueryDebugFilterState (
    _In_ ULONG ComponentId,
    _In_ ULONG Level)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
__kernel_entry
NTSTATUS
NTAPI
NtSetDebugFilterState (
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCreateDebugObject (
    _Out_ PHANDLE DebugHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDebugActiveProcess (
    _In_ HANDLE Process,
    _In_ HANDLE DebugObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDebugContinue (
    _In_ HANDLE DebugObject,
    _In_ PCLIENT_ID AppClientId,
    _In_ NTSTATUS ContinueStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtRemoveProcessDebug (
    _In_ HANDLE Process,
    _In_ HANDLE DebugObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef enum _DEBUGOBJECTINFOCLASS
{
    Unknown,
} DEBUGOBJECTINFOCLASS;

__kernel_entry
NTSTATUS
NTAPI
NtSetInformationDebugObject (
    _In_ HANDLE DebugObject,
    _In_ DEBUGOBJECTINFOCLASS InformationClass,
    _In_ PVOID Information,
    _In_ ULONG InformationLength,
    _Out_opt_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
typedef enum _SYSDBG_COMMAND
{
    SysDbgQueryModuleInformation = 0,
    SysDbgQueryTraceInformation = 1,
    SysDbgSetTracepoint = 2,
    SysDbgSetSpecialCall = 3,
    SysDbgClearSpecialCalls = 4,
    SysDbgQuerySpecialCalls = 5,
    SysDbgBreakPoint = 6,
    SysDbgQueryVersion = 7,
    SysDbgReadVirtual = 8,
    SysDbgWriteVirtual = 9,
    SysDbgReadPhysical = 10,
    SysDbgWritePhysical = 11,
    SysDbgReadControlSpace = 12,
    SysDbgWriteControlSpace = 13,
    SysDbgReadIoSpace = 14,
    SysDbgWriteIoSpace = 15,
    SysDbgReadMsr = 16,
    SysDbgWriteMsr = 17,
    SysDbgReadBusData = 18,
    SysDbgWriteBusData = 19,
    SysDbgCheckLowMemory = 20,
    SysDbgEnableKernelDebugger = 21,
    SysDbgDisableKernelDebugger = 22,
    SysDbgGetAutoKdEnable = 23,
    SysDbgSetAutoKdEnable = 24,
    SysDbgGetPrintBufferSize = 25,
    SysDbgSetPrintBufferSize = 26,
    SysDbgGetKdUmExceptionEnable = 27,
    SysDbgSetKdUmExceptionEnable = 28,
    SysDbgGetTriageDump = 29,
    SysDbgGetKdBlockEnable = 30,
    SysDbgSetKdBlockEnable = 31,
    SysDbgRegisterForUmBreakInfo = 32,
    SysDbgGetUmBreakPid = 33,
    SysDbgClearUmBreakPid = 34,
    SysDbgGetUmAttachPid = 35,
    SysDbgClearUmAttachPid = 36
} SYSDBG_COMMAND;

__kernel_entry
NTSTATUS
NTAPI
NtSystemDebugControl (
    _In_ SYSDBG_COMMAND Command,
    _Inout_updates_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_opt_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef PVOID PDBGUI_WAIT_STATE_CHANGE;

__kernel_entry
NTSTATUS
NTAPI
NtWaitForDebugEvent (
    _In_ HANDLE DebugObject,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_ PDBGUI_WAIT_STATE_CHANGE StateChange)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
