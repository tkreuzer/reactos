
#include "Ps.hpp"
#include "Thread.hpp"
#include <Se/Se.hpp>

extern "C" {

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsImpersonateClient (
    _Inout_ PETHREAD Thread,
    _In_opt_ PACCESS_TOKEN Token,
    _In_ BOOLEAN CopyOnOpen,
    _In_ BOOLEAN EffectiveOnly,
    _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsRevertToSelf (
    VOID)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsRevertThreadToSelf (
    _Inout_ PETHREAD Thread)
{
    __debugbreak();
}

// wdm.h
typedef struct _SE_IMPERSONATION_STATE
{
    PACCESS_TOKEN Token;
    BOOLEAN CopyOnOpen;
    BOOLEAN EffectiveOnly;
    SECURITY_IMPERSONATION_LEVEL Level;
} SE_IMPERSONATION_STATE, *PSE_IMPERSONATION_STATE;

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
NTAPI
PsDisableImpersonation (
    _Inout_ PETHREAD Thread,
    _Inout_ PSE_IMPERSONATION_STATE ImpersonationState)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsRestoreImpersonation (
    _Inout_ PETHREAD Thread,
    _In_ PSE_IMPERSONATION_STATE ImpersonationState)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
PACCESS_TOKEN
NTAPI
PsReferencePrimaryToken (
    _Inout_ PEPROCESS Process)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsDereferencePrimaryToken (
    _In_ PACCESS_TOKEN PrimaryToken)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PACCESS_TOKEN
NTAPI
PsReferenceImpersonationToken (
    _Inout_ PETHREAD Thread,
    _Out_ PBOOLEAN CopyOnOpen,
    _Out_ PBOOLEAN EffectiveOnly,
    _Out_ PSECURITY_IMPERSONATION_LEVEL ImpersonationLevel)
{
    __debugbreak();
    return NULL;
}

// == PsDereferencePrimaryToken
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsDereferenceImpersonationToken (
    _In_ PACCESS_TOKEN ImpersonationToken)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsAssignImpersonationToken (
    _In_ PETHREAD Thread,
    _In_opt_ HANDLE Token)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
