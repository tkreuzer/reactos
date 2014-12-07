
#include <Po/Po.hpp>

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtShutdownSystem (
    IN SHUTDOWN_ACTION Action)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtPowerInformation (
    _In_ POWER_INFORMATION_LEVEL InformationLevel,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtInitiatePowerAction (
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags,
    _In_ BOOLEAN Asynchronous)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSetSystemPowerState (
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtGetDevicePowerState (
    _In_ HANDLE Device,
    _Out_ PDEVICE_POWER_STATE State)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtIsSystemResumeAutomatic (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSetThreadExecutionState(
    _In_ EXECUTION_STATE NewFlags,
    _Out_ PEXECUTION_STATE PreviousFlags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
