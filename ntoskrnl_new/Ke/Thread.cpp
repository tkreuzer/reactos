
#include "Thread.hpp"

PVOID pKeGetPreviousMode = (PVOID)KeGetPreviousMode;
PVOID pKeGetCurrentThread = (PVOID)KeGetCurrentThread;

extern "C" {

//@ stdcall -stub KeCapturePersistentThreadState(ptr long long long long long ptr)
//@ stdcall -stub KeSetAffinityThread(ptr long)
//@ stub KeSetSelectedCpuSetsThread
//@ stub KiBeginThreadAccountingPeriod
//@ stub KiEndThreadAccountingPeriod

#if 0
#undef KeGetCurrentThread
PKTHREAD
NTAPI
KeGetCurrentThread(
    VOID)
{
    __debugbreak();
    return NULL;
}
#endif

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeAlertThread (
    _Inout_ PKTHREAD Thread,
    _In_ KPROCESSOR_MODE ProcessorMode)
{
    __debugbreak();
    return FALSE;
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeDelayExecutionThread (
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Interval)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
_IRQL_requires_max_(DISPATCH_LEVEL)
UCHAR
NTAPI
KeSetIdealProcessorThread (
    _Inout_ PKTHREAD Thread,
    _In_ UCHAR Processor)
{
    __debugbreak();
    return 0;
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeSetSystemGroupAffinityThread (
    _In_ PGROUP_AFFINITY Affinity,
    _Out_opt_ PGROUP_AFFINITY PreviousAffinity)
{
    __debugbreak();
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeRevertToUserGroupAffinityThread (
    _In_ PGROUP_AFFINITY PreviousAffinity)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
KPRIORITY
NTAPI
KeQueryEffectivePriorityThread (
    _In_ PKTHREAD Thread)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
KHETERO_CPU_POLICY
FASTCALL
KeQueryHeteroCpuPolicyThread (
    _In_ PKTHREAD Thread,
    _In_ LOGICAL UserPolicy)
{
    __debugbreak();
    return (KHETERO_CPU_POLICY)0;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
KHETERO_CPU_POLICY
NTAPI
KeSetHeteroCpuPolicyThread (
    PKTHREAD Thread,
    KHETERO_CPU_POLICY Policy,
    LOGICAL Reset)
{
    __debugbreak();
    return (KHETERO_CPU_POLICY)0;
}

// wdm.h
_IRQL_requires_max_(PASSIVE_LEVEL)
KPRIORITY
NTAPI
KeQueryPriorityThread (
    _In_ PKTHREAD Thread)
{
    __debugbreak();
    return (KPRIORITY)0;
}

// wdm.h
_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
KeQueryRuntimeThread (
    _In_ PKTHREAD Thread,
    _Out_ PULONG UserTime)
{
    __debugbreak();
    return 0;
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_same_
ULONG64
NTAPI
KeQueryTotalCycleTimeThread (
    _Inout_ PKTHREAD Thread,
    _Out_ PULONG64 CycleTimeStamp)
{
    __debugbreak();
    return 0;
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeRevertToUserAffinityThread (
    VOID)
{
    __debugbreak();
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeRevertToUserAffinityThreadEx (
    _In_ KAFFINITY Affinity)
{
    __debugbreak();
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeSetSystemAffinityThread (
    _In_ KAFFINITY Affinity)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
KPRIORITY
NTAPI
KeSetActualBasePriorityThread (
    _Inout_ PKTHREAD Thread,
    _In_ KPRIORITY NewBase)
{
    __debugbreak();
    return (KPRIORITY)0;
}

// ntddk.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeSetBasePriorityThread (
    _Inout_ PKTHREAD Thread,
    _In_ LONG Increment)
{
    __debugbreak();
    return 0;
}

// wdm.h
_IRQL_requires_max_(DISPATCH_LEVEL)
KPRIORITY
NTAPI
KeSetPriorityThread (
    _Inout_ PKTHREAD Thread,
    _In_ KPRIORITY Priority)
{
    __debugbreak();
    return (KPRIORITY)0;
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
KAFFINITY
NTAPI
KeSetSystemAffinityThreadEx (
    _In_ KAFFINITY Affinity)
{
    __debugbreak();
    return (KAFFINITY)0;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
BOOLEAN
NTAPI
KeTestAlertThread (
    _In_ KPROCESSOR_MODE)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
VOID
NTAPI
KeUpdateThreadTag (
    _In_ PKTHREAD Thread,
    _In_ KTHREAD_TAG Tag)
{
    __debugbreak();
}

}; // extern "C"
