
#include <ntoskrnl.h>
#include "Ke_internal.h"

VOID KeFindConfigurationEntry() { }
VOID KeFindConfigurationNextEntry() { }
VOID KeHwPolicyLocateResource() { }
VOID KeInitializeEnumerationContext() { }
VOID KeInitializeEnumerationContextFromGroup() { }
VOID KeSweepLocalCaches() { }
VOID KeIsWaitListEmpty() { }
VOID KeQueryPrcbAddress() { }

VOID
NTAPI
KeEnterKernelDebugger(VOID)
{
    __debugbreak();
}

VOID
FASTCALL
KeInvalidateRangeAllCaches(
    IN PVOID BaseAddress,
    IN ULONG Length)
{
    __debugbreak();
}


NTSTATUS
NTAPI
KeQueryHardwareCounterConfiguration(
    __out  PHARDWARE_COUNTER CounterArray,
    __in   ULONG MaximumCount,
    __out  PULONG Count)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
KeSetHardwareCounterConfiguration(
    __in  PHARDWARE_COUNTER CounterArray,
    __in  ULONG Count)
{
    __debugbreak();
    return 0;
}

#undef KeRaiseIrqlToDpcLevel
KIRQL
NTAPI
KeRaiseIrqlToDpcLevel(void)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeSetProfileIrql(IN KIRQL ProfileIrql)
{
    __debugbreak();
}

VOID
NTAPI
KeSetDmaIoCoherency(IN ULONG Coherency)
{
    __debugbreak();
}

BOOLEAN
NTAPI
KeSetKernelStackSwapEnable(
    __in  BOOLEAN Enable)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeUpdateRunTime(
    IN PKTRAP_FRAME TrapFrame,
    IN KIRQL Irql)
{
    __debugbreak();
}

#undef KeGetPreviousMode
KPROCESSOR_MODE
NTAPI
KeGetPreviousMode(VOID)
{
    return _KeGetPreviousMode();
}
