
#include "Sid.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlInitializeSid (
    _Out_ PSID Sid,
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
__cdecl
RtlInitializeSidEx (
    _Out_writes_bytes_(SECURITY_SID_SIZE(SubAuthorityCount)) PSID Sid,
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    ...)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
RtlLengthRequiredSid (
    _In_ ULONG SubAuthorityCount)
{
    __debugbreak();
    return 0;
}

_Post_satisfies_(return >= 8 && return <= SECURITY_MAX_SID_SIZE)
ULONG
NTAPI
RtlLengthSid (
    _In_ PSID Sid)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlValidSid (
    _In_ PSID Sid)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlEqualSid (
    _In_ PSID Sid1,
    _In_ PSID Sid2)
{
    __debugbreak();
    return FALSE;
}

PUCHAR
NTAPI
RtlSubAuthorityCountSid (
    _In_ PSID Sid)
{
    __debugbreak();
    return NULL;
}

PULONG
NTAPI
RtlSubAuthoritySid (
    _In_ PSID Sid,
    _In_ ULONG SubAuthority)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlCopySid (
    _In_ ULONG DestinationSidLength,
    _Out_writes_bytes_(DestinationSidLength) PSID DestinationSid,
    _In_ PSID SourceSid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlConvertSidToUnicodeString (
    _Inout_ PUNICODE_STRING UnicodeString,
    _In_ PSID Sid,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlCopySidAndAttributesArray
NTSTATUS
NTAPI
RtlCopySidAndAttributesArray (
    ULONG Count,
    PSID_AND_ATTRIBUTES Src,
    ULONG SidAreaSize,
    PSID_AND_ATTRIBUTES Dest,
    PVOID SidArea,
    PVOID* RemainingSidArea,
    PULONG RemainingSidAreaSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#if 0
_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlEqualPrefixSid (
    _In_ PSID Sid1,
    _In_ PSID Sid2)
{
    __debugbreak();
    return FALSE;
}

PVOID
NTAPI
RtlFreeSid(
    _In_ _Post_invalid_ PSID Sid)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
NTSTATUS
NTAPI
RtlAllocateAndInitializeSid(
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    _In_ ULONG SubAuthority0,
    _In_ ULONG SubAuthority1,
    _In_ ULONG SubAuthority2,
    _In_ ULONG SubAuthority3,
    _In_ ULONG SubAuthority4,
    _In_ ULONG SubAuthority5,
    _In_ ULONG SubAuthority6,
    _In_ ULONG SubAuthority7,
    _Outptr_ PSID *Sid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
NTSTATUS
NTAPI
RtlAllocateAndInitializeSidEx(
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    _In_reads_(SubAuthorityCount) PULONG SubAuthorities,
    _Outptr_ PSID *Sid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


_IRQL_requires_max_(APC_LEVEL)
PSID_IDENTIFIER_AUTHORITY
NTAPI
RtlIdentifierAuthoritySid (
    _In_ PSID Sid)
{
    __debugbreak();
    return NULL;
}

NTSTATUS
NTAPI
RtlCreateServiceSid(
    _In_ PUNICODE_STRING ServiceName,
    _Out_writes_bytes_opt_(*ServiceSidLength) PSID ServiceSid,
    _Inout_ PULONG ServiceSidLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlCreateVirtualAccountSid (
    _In_ PCUNICODE_STRING Name,
    _In_ ULONG BaseSubAuthority,
    _Out_writes_bytes_(*SidLength) PSID Sid,
    _Inout_ PULONG SidLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}
#endif // 0

} // extern "C"
