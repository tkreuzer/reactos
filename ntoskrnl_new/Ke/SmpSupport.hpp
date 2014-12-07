
#pragma once

#include "Kep.hpp"

typedef enum _LOGICAL_PROCESSOR_RELATIONSHIP
{
    RelationProcessorCore,
    RelationNumaNode,
    RelationCache,
    RelationProcessorPackage,
    RelationGroup,
    RelationAll = 0xffff
} LOGICAL_PROCESSOR_RELATIONSHIP;

typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX;

typedef struct _KAFFINITY_ENUMERATION_CONTEXT *PKAFFINITY_ENUMERATION_CONTEXT;

typedef enum
{
    KeProcessorAddStartNotify = 0,
    KeProcessorAddCompleteNotify,
    KeProcessorAddFailureNotify
} KE_PROCESSOR_CHANGE_NOTIFY_STATE;

typedef struct _KE_PROCESSOR_CHANGE_NOTIFY_CONTEXT
{
    KE_PROCESSOR_CHANGE_NOTIFY_STATE State;
    ULONG NtNumber;
    NTSTATUS Status;
#if (NTDDI_VERSION >= NTDDI_WIN7)
    PROCESSOR_NUMBER ProcNumber;
#endif
    ULONG ProcessorId;
} KE_PROCESSOR_CHANGE_NOTIFY_CONTEXT, *PKE_PROCESSOR_CHANGE_NOTIFY_CONTEXT;

typedef
_IRQL_requires_same_
_Function_class_(PROCESSOR_CALLBACK_FUNCTION)
VOID
NTAPI
PROCESSOR_CALLBACK_FUNCTION (
    _In_ PVOID CallbackContext,
    _In_ PKE_PROCESSOR_CHANGE_NOTIFY_CONTEXT ChangeContext,
    _Inout_ PNTSTATUS OperationStatus);
typedef PROCESSOR_CALLBACK_FUNCTION *PPROCESSOR_CALLBACK_FUNCTION;
