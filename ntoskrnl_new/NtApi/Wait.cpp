
#include "Ke/Wait.hpp"

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtWaitForSingleObject (
    _In_ HANDLE Object,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Time)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSignalAndWaitForSingleObject (
    _In_ HANDLE SignalObject,
    _In_ HANDLE WaitObject,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Time)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWaitForMultipleObjects (
    _In_ ULONG Count,
    _In_count_(Count) HANDLE Objects[],
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Time)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWaitForMultipleObjects32 (
    _In_ ULONG ObjectCount,
    _In_ PLONG Handles,
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER TimeOut)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDelayExecution (
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER DelayInterval)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_same_
__kernel_entry
NTSTATUS
NTAPI
NtYieldExecution (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWaitForAlertByThreadId (
    _In_ HANDLE ThreadId,
    _In_ PVOID Unknown)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"
