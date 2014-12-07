
#include "Ke/PerfCounter.hpp"

extern "C" {

NTSTATUS
NTAPI
NtQueryPerformanceCounter (
    _Out_ PLARGE_INTEGER Counter,
    _Out_opt_ PLARGE_INTEGER Frequency)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryIntervalProfile (
    _In_ KPROFILE_SOURCE ProfileSource,
    _Out_ PULONG Interval)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetIntervalProfile (
    _In_ ULONG Interval,
    _In_ KPROFILE_SOURCE Source)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntddk.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeSetHardwareCounterConfiguration (
    _In_reads_(Count) PHARDWARE_COUNTER CounterArray,
    _In_ ULONG Count)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
