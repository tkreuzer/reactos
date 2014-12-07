
#include "PerfCounter.hpp"

extern "C" {

// wdm.h
NTSTATUS
NTAPI
KeConvertAuxiliaryCounterToPerformanceCounter (
    _In_ ULONG64 AuxiliaryCounterValue,
    _Out_ PULONG64 PerformanceCounterValue,
    _Out_opt_ PULONG64 ConversionError)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h
NTSTATUS
NTAPI
KeConvertPerformanceCounterToAuxiliaryCounter (
    _In_ ULONG64 PerformanceCounterValue,
    _Out_ PULONG64 AuxiliaryCounterValue,
    _Out_opt_ PULONG64 ConversionError)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h
NTSTATUS
NTAPI
KeQueryAuxiliaryCounterFrequency (
    _Out_ PULONG64 AuxiliaryCounterFrequency)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntddk.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeQueryHardwareCounterConfiguration (
    _Out_writes_to_(MaximumCount, *Count) PHARDWARE_COUNTER CounterArray,
    _In_ ULONG MaximumCount,
    _Out_ PULONG Count)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
