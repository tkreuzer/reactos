

#include "Callout.hpp"

extern "C" {

#define MAXIMUM_EXPANSION_SIZE (KERNEL_LARGE_STACK_SIZE – (PAGE_SIZE / 2))

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
KeAllocateCalloutStack (
    _In_ BOOLEAN LargeStack)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeAllocateCalloutStackEx (
    _In_ _Strict_type_match_ KSTACK_TYPE StackType,
    _In_ UCHAR RecursionDepth,
    _In_ _Reserved_ SIZE_T Reserved,
    _Outptr_ PVOID *StackContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeFreeCalloutStack (
    _In_ PVOID Context)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeExpandKernelStackAndCallout (
    _In_ PEXPAND_STACK_CALLOUT Callout,
    _In_opt_ PVOID Parameter,
    _In_ SIZE_T Size)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
KeExpandKernelStackAndCalloutEx (
    _In_ PEXPAND_STACK_CALLOUT Callout,
    _In_opt_ PVOID Parameter,
    _In_ SIZE_T Size,
    _In_ BOOLEAN Wait,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
