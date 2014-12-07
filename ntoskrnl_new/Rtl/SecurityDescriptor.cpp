
#include "SecurityDescriptor.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlCreateSecurityDescriptor (
    _Out_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Revision)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlValidSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlValidRelativeSecurityDescriptor (
    _In_reads_bytes_(SecurityDescriptorLength) PSECURITY_DESCRIPTOR SecurityDescriptorInput,
    _In_ ULONG SecurityDescriptorLength,
    _In_ SECURITY_INFORMATION RequiredInformation)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
RtlLengthSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlGetSaclSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PBOOLEAN SaclPresent,
    _Out_ PACL *Sacl,
    _Out_ PBOOLEAN SaclDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlSetDaclSecurityDescriptor (
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ BOOLEAN DaclPresent,
    _In_opt_ PACL Dacl,
    _In_ BOOLEAN DaclDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlGetDaclSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PBOOLEAN DaclPresent,
    _Outptr_result_maybenull_ PACL *Dacl,
    _Pre_ _Writable_elements_(1)
    _When_(!(*DaclPresent), _Post_invalid_)
    _When_((*DaclPresent), _Post_valid_)
    PBOOLEAN DaclDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlSetSaclSecurityDescriptor
NTSTATUS
NTAPI
RtlSetSaclSecurityDescriptor (
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    BOOLEAN SaclPresent,
    PACL Sacl,
    BOOLEAN SaclDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlGetOwnerSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_result_maybenull_ PSID *Owner,
    _When_(*Owner == NULL, _Post_invalid_)
    _When_(*Owner != NULL, _Post_valid_)
    _Pre_ _Notnull_ _Pre_ _Writable_elements_(1) PBOOLEAN OwnerDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlSetOwnerSecurityDescriptor (
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID Owner,
    _In_ BOOLEAN OwnerDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlGetGroupSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_result_maybenull_ PSID *Group,
    _Pre_ _Notnull_ _Pre_ _Writable_elements_(1)
    _When_(*Group == NULL, _Post_invalid_)
    _When_(*Group != NULL, _Post_valid_)
    PBOOLEAN GroupDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlSetGroupSecurityDescriptor (
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID Group,
    _In_ BOOLEAN GroupDefaulted)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlGetControlSecurityDescriptor
NTSTATUS
NTAPI
RtlGetControlSecurityDescriptor (
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    PSECURITY_DESCRIPTOR_CONTROL Control,
    PULONG Revision)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlSetControlSecurityDescriptor
NTSTATUS
NTAPI
RtlSetControlSecurityDescriptor (
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
    SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// export?
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlCreateSecurityDescriptorRelative (
    _Out_ PSECURITY_DESCRIPTOR_RELATIVE SecurityDescriptor,
    _In_ ULONG Revision)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlAbsoluteToSelfRelativeSD (
    _In_ PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Out_writes_bytes_to_opt_(*BufferLength, *BufferLength) PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Inout_ PULONG BufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlSelfRelativeToAbsoluteSD (
    _In_ PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Out_writes_bytes_to_opt_(*AbsoluteSecurityDescriptorSize, *AbsoluteSecurityDescriptorSize) PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Inout_ PULONG AbsoluteSecurityDescriptorSize,
    _Out_writes_bytes_to_opt_(*DaclSize, *DaclSize) PACL Dacl,
    _Inout_ PULONG DaclSize,
    _Out_writes_bytes_to_opt_(*SaclSize, *SaclSize) PACL Sacl,
    _Inout_ PULONG SaclSize,
    _Out_writes_bytes_to_opt_(*OwnerSize, *OwnerSize) PSID Owner,
    _Inout_ PULONG OwnerSize,
    _Out_writes_bytes_to_opt_(*PrimaryGroupSize, *PrimaryGroupSize) PSID PrimaryGroup,
    _Inout_ PULONG PrimaryGroupSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlSelfRelativeToAbsoluteSD2
NTSTATUS
NTAPI
RtlSelfRelativeToAbsoluteSD2 (
    PSECURITY_DESCRIPTOR_RELATIVE SelfRelativeSD,
    PULONG BufferSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlReplaceSidInSd (
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PSID OldSid,
    _In_ PSID NewSid,
    _Out_ ULONG *NumChanges)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


} // extern "C"
