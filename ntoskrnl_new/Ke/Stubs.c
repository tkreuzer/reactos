
#include <ntoskrnl.h>

//@ stub KePollFreezeExecution
//@ stub KeHwPolicyLocateResource
//@ stdcall -stub KeSetDmaIoCoherency(long)
//@ stub KeSynchronizeTimeToQpc
//@ stub KiAccumulateCycleStats
//@ stub KitLogFeatureUsage
//@ stub -arch=i386,arm KiCheckForSListAddress

NTSTATUS
NTAPI
NtVdmControl (
    _In_ ULONG ControlCode,
    _In_ PVOID ControlData)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
KeReportCacheIncoherentDevice (
    VOID)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
KeStallWhileFrozen (
    _In_ ULONG MicroSeconds)
{
    __debugbreak();
}

