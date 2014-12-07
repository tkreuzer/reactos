
#include "Cpu.hpp"

typedef struct _MDL *PMDL;

extern "C" {

#ifdef _M_AMD64
ULONG KeLastBranchMSR;
#endif // _M_AMD64
#ifdef _M_IX86
ULONG KeI386MachineType;
#endif // _M_IX86

//@ stub KeForceEnableNx
//@ stdcall -stub KeFlushEntireTb(long long)
//@ stub KeGetXSaveFeatureFlags
//@ stub KeSystemFullyCacheCoherent
//@ cdecl KeSaveStateForHibernate(ptr)

// wdm.h / ntosp.h
VOID
NTAPI
KeFlushIoBuffers (
    _In_ PMDL Mdl,
    _In_ BOOLEAN ReadOperation,
    _In_ BOOLEAN DmaOperation)
{
    __debugbreak();
}

// ntddk.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeInvalidateAllCaches (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntddk.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FASTCALL
KeInvalidateRangeAllCaches (
    _In_ PVOID BaseAddress,
    _In_ ULONG Length)
{
    __debugbreak();
}

// wdm.h / ntosp.h
_IRQL_requires_max_(IPI_LEVEL-1)
ULONG_PTR
NTAPI
KeIpiGenericCall (
    _In_ PKIPI_BROADCAST_WORKER BroadcastFunction,
    _In_ ULONG_PTR Context)
{
    __debugbreak();
    return 0;
}

#if (defined(_X86_) || defined(_AMD64_)) && !defined(XBOX_SYSTEMOS)

typedef struct _PROCESSOR_LOCKSTEP {
    ULONG Processor;
    LONG Limit;
    volatile LONG TargetCount;
    LONG volatile *TargetPhase;
} PROCESSOR_LOCKSTEP, *PPROCESSOR_LOCKSTEP;

// ntosp.h
NTSTATUS
NTAPI
KeLoadMTRR (
    _Inout_ PPROCESSOR_LOCKSTEP IpiContext)

{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}
#endif

#if !defined(XBOX_SYSTEMOS)
// ntosp.h
VOID
NTAPI
KeWriteProtectPAT (
    VOID)
{
    __debugbreak();
}
#endif

// wdm.h / ntosp.h
ULONG
NTAPI
KeGetRecommendedSharedDataAlignment (
    VOID)
{
    __debugbreak();
    return 0;
}

#if defined(_M_AMD64)
// ntosp.h
PKPRCB
NTAPI
KeQueryPrcbAddress (
    _In_ ULONG Number)
{
    __debugbreak();
    return NULL;
}
#endif // _M_AMD64

// ntosp.h
_IRQL_requires_max_(HIGH_LEVEL)
VOID
NTAPI
KeSweepLocalCaches (
    VOID)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_(IPI_LEVEL);
BOOLEAN
NTAPI
KiIpiServiceRoutine (
    _In_ PVOID Interrupt,
    _In_ PVOID Context)
{
    __debugbreak();
    return FALSE;
}

VOID
__cdecl
KeSaveStateForHibernate (
    struct _KPROCESSOR_STATE *State)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_(return>=0, _Kernel_float_saved_)
_At_(*FloatSave, _When_(return>=0, _Kernel_acquires_resource_(FloatState)))
NTKERNELAPI
NTSTATUS
NTAPI
KeSaveFloatingPointState (
    _Out_ PKFLOATING_SAVE FloatSave)
{
    UNREFERENCED_PARAMETER(FloatSave);
    return STATUS_SUCCESS;
}

_Success_(1)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Kernel_float_restored_
_At_(*FloatSave, _Kernel_requires_resource_held_(FloatState) _Kernel_releases_resource_(FloatState))
NTKERNELAPI
NTSTATUS
NTAPI
KeRestoreFloatingPointState (
    _In_ PKFLOATING_SAVE FloatSave)
{
    UNREFERENCED_PARAMETER(FloatSave);
    return STATUS_SUCCESS;
}

BOOLEAN
NTAPI
Ke386QueryIoAccessMap (
    _In_range_(<, IOPM_COUNT) ULONG MapNumber,
    _Out_writes_bytes_(IOPM_SIZE) PKIO_ACCESS_MAP IoAccessMap)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
Ke386SetIoAccessMap (
    _In_range_(<, IOPM_COUNT) ULONG MapNumber,
    _In_reads_bytes_(IOPM_SIZE) PKIO_ACCESS_MAP IoAccessMap)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_(return>=0, _Kernel_float_saved_)
_At_(*XStateSave, _When_(return>=0, _Kernel_acquires_resource_(FloatState)))
NTSTATUS
NTAPI
KeSaveExtendedProcessorState (
    _In_ ULONG64 Mask,
    _Out_ PXSTATE_SAVE XStateSave)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Kernel_float_restored_
_At_(*XStateSave, _Kernel_requires_resource_held_(FloatState) _Kernel_releases_resource_(FloatState))
VOID
NTAPI
KeRestoreExtendedProcessorState (
    _In_ PXSTATE_SAVE XStateSave)
{
    __debugbreak();
}

// wdm.h / ntosp.h
_IRQL_requires_min_(DISPATCH_LEVEL)
LOGICAL
NTAPI
KeShouldYieldProcessor (
    VOID)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"
