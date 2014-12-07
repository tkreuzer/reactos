
#include <ntifs.h>

BOOLEAN KdDebuggerEnabled;
BOOLEAN KdDebuggerNotPresent;
BOOLEAN KdEnteredDebugger;

NTSTATUS
NTAPI
KdEnableDebugger (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
KdDisableDebugger (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
KdChangeOption (
    _In_ KD_OPTION Option,
    _In_opt_ ULONG InBufferBytes,
    _In_ PVOID InBuffer,
    _In_opt_ ULONG OutBufferBytes,
    _Out_ PVOID OutBuffer,
    _Out_opt_ PULONG OutBufferNeeded)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
KdPollBreakIn (
    VOID)
{
    __debugbreak();
    return FALSE;
}

NTSTATUS
NTAPI
KdPowerTransition (
    _In_ ULONG PowerState)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
KdRefreshDebuggerNotPresent (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
enum _SYSDBG_COMMAND
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
};

NTSTATUS
NTAPI
KdSystemDebugControl(
    _In_ enum _SYSDBG_COMMAND Command,
    _In_reads_bytes_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_ PULONG ReturnLength,
    _In_ KPROCESSOR_MODE PreviousMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


