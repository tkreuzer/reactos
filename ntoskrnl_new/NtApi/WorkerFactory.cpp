
#include <Ex/Ex.hpp>

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtCreateWorkerFactory (
    ULONG_PTR P1,
    ULONG_PTR P2,
    ULONG_PTR P3,
    ULONG_PTR P4,
    ULONG_PTR P5,
    ULONG_PTR P6,
    ULONG_PTR P7,
    ULONG_PTR P8,
    ULONG_PTR P9,
    ULONG_PTR P10)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtReleaseWorkerFactoryWorker (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationWorkerFactory (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetInformationWorkerFactory (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtShutdownWorkerFactory (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWaitForWorkViaWorkerFactory (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWorkerFactoryWorkerReady (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


};
