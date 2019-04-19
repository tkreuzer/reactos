
#include "SmpSupport.hpp"

extern "C" {

    volatile UCHAR KeNumberProcessors;

//@ stub KeNotifyProcessorFreezeSupported

// wdm.h / ntosp.h
ULONG
NTAPI
KeQueryMaximumProcessorCount (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
ULONG
NTAPI
KeQueryMaximumProcessorCountEx (
    _In_ USHORT GroupNumber)
{
    __debugbreak();
    return 0;
}

ULONG
NTAPI
NtGetCurrentProcessorNumber (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
ULONG
NTAPI
KeGetCurrentProcessorNumberEx (
    _Out_opt_ PPROCESSOR_NUMBER ProcNumber)
{
    __debugbreak();
    return 0;
}

ULONG
NTAPI
NtGetCurrentProcessorNumberEx (
    _Out_opt_ PPROCESSOR_NUMBER ProcNumber)
{
    return KeGetCurrentProcessorNumberEx(ProcNumber);
}

// wdm.h / ntosp.h
NTSTATUS
NTAPI
KeGetProcessorNumberFromIndex (
    _In_ ULONG ProcIndex,
    _Out_ PPROCESSOR_NUMBER ProcNumber)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h / ntosp.h
ULONG
NTAPI
KeGetProcessorIndexFromNumber (
    _In_ PPROCESSOR_NUMBER ProcNumber)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
ULONG
NTAPI
KeQueryActiveProcessorCount (
    _Out_opt_ PKAFFINITY ActiveProcessors)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
ULONG
NTAPI
KeQueryActiveProcessorCountEx (
    _In_ USHORT GroupNumber)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
KAFFINITY
NTAPI
KeQueryActiveProcessors (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_(_Old_(*Length) == 0, _Post_satisfies_(return < 0))
NTSTATUS
NTAPI
KeQueryLogicalProcessorRelationship (
    _In_opt_ PPROCESSOR_NUMBER ProcessorNumber,
    _In_ LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType,
    _Out_writes_bytes_opt_(*Length) PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Information,
    _Always_(_Inout_) PULONG Length)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
KeEnumerateNextProcessor (
    _Out_ PULONG ProcIndex,
    _Inout_ PKAFFINITY_ENUMERATION_CONTEXT Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h / ntosp.h
USHORT
NTAPI
KeGetCurrentNodeNumber (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
USHORT
NTAPI
KeQueryHighestNodeNumber (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
VOID
NTAPI
KeQueryNodeActiveAffinity (
    _In_ USHORT NodeNumber,
    _Out_opt_ PGROUP_AFFINITY Affinity,
    _Out_opt_ PUSHORT Count)
{
    __debugbreak();
}

// wdm.h / ntosp.h
USHORT
NTAPI
KeQueryNodeMaximumProcessorCount (
    _In_ USHORT NodeNumber)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
USHORT
NTAPI
KeQueryMaximumGroupCount (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
USHORT
NTAPI
KeQueryActiveGroupCount (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
KAFFINITY
NTAPI
KeQueryGroupAffinity (
    _In_ USHORT GroupNumber)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeStartDynamicProcessor (
    _In_ ULONG ProcessorId,
    _In_ ULONG ApicId,
    _In_ USHORT NsNodeNumber,
    _Out_ PULONG NtNumber)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
KeRegisterProcessorChangeCallback (
    _In_ PPROCESSOR_CALLBACK_FUNCTION CallbackFunction,
    _In_opt_ PVOID CallbackContext,
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}


// wdm.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeDeregisterProcessorChangeCallback (
    _In_ PVOID CallbackHandle)
{
    __debugbreak();
}


}; // extern "C"
