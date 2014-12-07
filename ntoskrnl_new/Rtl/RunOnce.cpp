
#include "Rtl.hpp"

extern "C" {

// ntddk.h
typedef union _RTL_RUN_ONCE
{
    PVOID Ptr;
} RTL_RUN_ONCE, *PRTL_RUN_ONCE;

typedef
_Function_class_(RTL_RUN_ONCE_INIT_FN)
_IRQL_requires_same_
ULONG
NTAPI
RTL_RUN_ONCE_INIT_FN (
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _Inout_opt_ PVOID Parameter,
    _Inout_opt_ PVOID *Context);
typedef RTL_RUN_ONCE_INIT_FN *PRTL_RUN_ONCE_INIT_FN;

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
RtlRunOnceInitialize (
    _Out_ PRTL_RUN_ONCE RunOnce)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlRunOnceBeginInitialize (
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ ULONG Flags,
    _Outptr_opt_result_maybenull_ PVOID *Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
_Maybe_raises_SEH_exception_
NTSTATUS
NTAPI
RtlRunOnceExecuteOnce (
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ __callback PRTL_RUN_ONCE_INIT_FN InitFn,
    _Inout_opt_ PVOID Parameter,
    _Outptr_opt_result_maybenull_ PVOID *Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlRunOnceComplete (
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ ULONG Flags,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
