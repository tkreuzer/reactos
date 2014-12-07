
#include "Acl.hpp"
#include "Sid.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlCreateAcl (
    _Out_writes_bytes_(AclLength) PACL Acl,
    _In_ ULONG AclLength,
    _In_ ULONG AclRevision)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlQueryInformationAcl
NTSTATUS
NTAPI
RtlQueryInformationAcl (
    _In_ PACL Acl,
    _Out_writes_bytes_(InformationLength) PVOID Information,
    _In_ ULONG InformationLength,
    _In_ ACL_INFORMATION_CLASS InformationClass)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlValidAcl
BOOLEAN
NTAPI
RtlValidAcl (
    _In_ PACL Acl)
{
    __debugbreak();
    return FALSE;
}

NTSTATUS
NTAPI
RtlGetAce (
    _In_ PACL Acl,
    _In_ ULONG AceIndex,
    _Outptr_ PVOID *Ace)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlAddAce (
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG StartingAceIndex,
    _In_reads_bytes_(AceListLength) PVOID AceList,
    _In_ ULONG AceListLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlAddAccessAllowedAce (
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlAddAccessAllowedAceEx (
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlDeleteAce (
    _Inout_ PACL Acl,
    _In_ ULONG AceIndex)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlAddAccessAllowedObjectAce
NTSTATUS
NTAPI
RtlAddAccessAllowedObjectAce (
    _Inout_ PACL pAcl,
    _In_ ULONG dwAceRevision,
    _In_ ULONG /* [ACE_FLAGS_ULONG] */ AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ LPGUID ObjectTypeGuid,
    _In_ LPGUID InheritedObjectTypeGuid,
    _In_ PSID pSid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlAddAccessDeniedAceEx
NTSTATUS
NTAPI
RtlAddAccessDeniedAceEx (
    _Inout_ PACL Acl,
    _In_ ULONG Revision,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlAddAccessDeniedObjectAce
NTSTATUS
NTAPI
RtlAddAccessDeniedObjectAce (
    _Inout_ PACL pAcl,
    _In_ ULONG dwAceRevision,
    _In_ ULONG /* [ACE_FLAGS_ULONG] */ AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ LPGUID ObjectTypeGuid,
    _In_ LPGUID InheritedObjectTypeGuid,
    _In_ PSID pSid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlAddAuditAccessAceEx
NTSTATUS
NTAPI
RtlAddAuditAccessAceEx (
    _Inout_ PACL Acl,
    _In_ ULONG Revision,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid,
    _In_ BOOLEAN Success,
    _In_ BOOLEAN Failure)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlAddAuditAccessObjectAce
NTSTATUS
NTAPI
RtlAddAuditAccessObjectAce (
    _Inout_ PACL Acl,
    _In_ ULONG Revision,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK AccessMask,
    _In_ LPGUID ObjectTypeGuid,
    _In_ LPGUID InheritedObjectTypeGuid,
    _In_ PSID Sid,
    _In_ BOOLEAN Success,
    _In_ BOOLEAN Failure)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
RtlAddResourceAttributeAce (
    _Inout_ PACL Acl,
    PVOID P2,
    PVOID P3,
    PVOID P4,
    PVOID P5,
    PVOID P6,
    PVOID P7)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

/*!
    \return On success return NotEqual 0

    \ref http://filelog.net/func/RtlFindAceByType
*/
PVOID
NTAPI
RtlFindAceByType (
    _In_ PACL pAcl,
    _In_ UCHAR /*[ACE_TYPE|UCHAR]*/ AceType,
    _In_ PULONG pIndex)
{
    __debugbreak();
    return NULL;
}

// http://filelog.net/func/RtlFirstFreeAce
BOOLEAN
NTAPI
RtlFirstFreeAce (
    _In_ PACL Acl,
    _Outptr_ PACE* Ace)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlOwnerAcesPresent
BOOLEAN
NTAPI
RtlOwnerAcesPresent (
    _In_ PACL Acl)
{
    __debugbreak();
    return FALSE;
}

} // extern "C"
