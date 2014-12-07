
#include <ntoskrnl.h>
#include <Se/Se.hpp>
#include <Se/Token.hpp>

// see ntlsa.h

extern "C" {

// LsaLookup.h
typedef UNICODE_STRING LSA_UNICODE_STRING, *PLSA_UNICODE_STRING;
typedef STRING LSA_STRING, *PLSA_STRING;
typedef OBJECT_ATTRIBUTES LSA_OBJECT_ATTRIBUTES, *PLSA_OBJECT_ATTRIBUTES;

// ntifs.h
typedef ULONG  LSA_OPERATIONAL_MODE, *PLSA_OPERATIONAL_MODE;

typedef enum _SECURITY_LOGON_TYPE
{
    UndefinedLogonType = 0,
    Interactive = 2,
    Network,
    Batch,
    Service,
    Proxy,
    Unlock,
    NetworkCleartext,
    NewCredentials,
    RemoteInteractive,
    CachedInteractive,
    CachedRemoteInteractive,
    CachedUnlock
} SECURITY_LOGON_TYPE, *PSECURITY_LOGON_TYPE;

typedef struct _QUOTA_LIMITS
{
    SIZE_T PagedPoolLimit;
    SIZE_T NonPagedPoolLimit;
    SIZE_T MinimumWorkingSetSize;
    SIZE_T MaximumWorkingSetSize;
    SIZE_T PagefileLimit;
    LARGE_INTEGER TimeLimit;
} QUOTA_LIMITS, *PQUOTA_LIMITS;

_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
LsaCallAuthenticationPackage (
    _In_ HANDLE LsaHandle,
    _In_ ULONG AuthenticationPackage,
    _In_reads_bytes_(SubmitBufferLength) PVOID ProtocolSubmitBuffer,
    _In_ ULONG SubmitBufferLength,
    _Out_opt_ PVOID *ProtocolReturnBuffer,
    _Out_opt_ PULONG ReturnBufferLength,
    _Out_opt_ PNTSTATUS ProtocolStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
LsaDeregisterLogonProcess (
    _In_ HANDLE LsaHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_same_
NTSTATUS
NTAPI
LsaFreeReturnBuffer (
    _In_ PVOID Buffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
LsaLogonUser (
    _In_ HANDLE LsaHandle,
    _In_ PLSA_STRING OriginName,
    _In_ SECURITY_LOGON_TYPE LogonType,
    _In_ ULONG AuthenticationPackage,
    _In_reads_bytes_(AuthenticationInformationLength) PVOID AuthenticationInformation,
    _In_ ULONG AuthenticationInformationLength,
    _In_opt_ PTOKEN_GROUPS LocalGroups,
    _In_ PTOKEN_SOURCE SourceContext,
    _Out_ PVOID *ProfileBuffer,
    _Out_ PULONG ProfileBufferLength,
    _Inout_ PLUID LogonId,
    _Out_ PHANDLE Token,
    _Out_ PQUOTA_LIMITS Quotas,
    _Out_ PNTSTATUS SubStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
LsaLookupAuthenticationPackage (
    _In_ HANDLE LsaHandle,
    _In_ PLSA_STRING PackageName,
    _Out_ PULONG AuthenticationPackage)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
LsaRegisterLogonProcess (
    _In_ PLSA_STRING LogonProcessName,
    _Out_ PHANDLE LsaHandle,
    _Out_ PLSA_OPERATIONAL_MODE SecurityMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
