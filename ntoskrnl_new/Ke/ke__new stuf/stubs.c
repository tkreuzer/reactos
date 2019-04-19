
#include <ntoskrnl.h>
#include "Ke_internal.h"

VOID KeHwPolicyLocateResource() { }
VOID KeInitializeEnumerationContext() { }
VOID KeInitializeEnumerationContextFromGroup() { }
VOID KeIsWaitListEmpty() { }
VOID KeQueryPrcbAddress() { }

VOID
NTAPI
KeEnterKernelDebugger(VOID)
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
KeSetDmaIoCoherency(IN ULONG Coherency)
{
    __debugbreak();
}

VOID
NTAPI
KeUpdateRunTime(
    IN PKTRAP_FRAME TrapFrame,
    IN KIRQL Irql)
{
    __debugbreak();
}

VOID KiDpcInterruptHandler(VOID)
{
}

VOID KiRetireDpcList(VOID)
{
}

NTSTATUS
NTAPI
NtRaiseException(
    IN PEXCEPTION_RECORD ExceptionRecord,
    IN PCONTEXT Context,
    IN BOOLEAN SearchFrames)
{
    UNIMPLEMENTED;
    __debugbreak();
    return 0;
}

VOID
KiCpuId()
{
    __debugbreak();
}

volatile CCHAR KeNumberProcessors;

void
KeQueryGroupAffinityEx()
{
    __debugbreak();
}

VOID KiSystemCallHandler(VOID)
{
}

ULONG
NTAPI
KeQueryTimeIncrement(void)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeUpdateSystemTimeAssist()
{
    __debugbreak();
}

VOID
NTAPI
KeSetTimeIncrement(
    IN ULONG MaxIncrement,
    IN ULONG MinIncrement)
{
    __debugbreak();
}

VOID
NTAPI
KiSystemThreadStartup()
{
    __debugbreak();
}

VOID
NTAPI
KiUserThreadStartup()
{
    __debugbreak();
}

// undocumented
void
KeGetNextTimerExpirationDueTime(void)
{
    __debugbreak();
}


