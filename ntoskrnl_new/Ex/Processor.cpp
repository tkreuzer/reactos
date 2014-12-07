
#include "Exp.hpp"

extern "C" {

_IRQL_requires_max_(DISPATCH_LEVEL)
KPROCESSOR_MODE
NTAPI
ExGetPreviousMode (
    VOID)
{
    __debugbreak();
    return KernelMode;
}

VOID
NTAPI
ExGetCurrentProcessorCounts (
    _Out_ PULONG IdleCount,
    _Out_ PULONG KernelAndUser,
    _Out_ PULONG Index)
{
    __debugbreak();
}

VOID
NTAPI
ExGetCurrentProcessorCpuUsage (
    _Out_ PULONG CpuUsage)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("nothing",
    "Drivers should not be dependent on processor features")
BOOLEAN
NTAPI
ExIsProcessorFeaturePresent (
    _In_ ULONG ProcessorFeature)
{
    __debugbreak();
    return FALSE;
}


}; // extern "C"
