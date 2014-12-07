
#include <ntifs.h>

PSE_EXPORTS SeExports;
PACL SePublicDefaultDacl;
PACL SeSystemDefaultDacl;
POBJECT_TYPE SeTokenObjectType;

NTSTATUS
NTAPI
SeDefaultObjectMethod (
    _In_ PVOID Object,
    _In_ SECURITY_OPERATION_CODE OperationType,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _In_ PVOID SecurityDescriptor, // PSECURITY_DESCRIPTOR
    _Inout_ PULONG CapturedLength,
    _Inout_ PVOID *ObjectSecurityDescriptor, // PSECURITY_DESCRIPTOR
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
SeDefaultObjectMethodEx1 (
    _In_ PVOID Object,
    _In_ SECURITY_OPERATION_CODE OperationType,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _In_ PVOID SecurityDescriptor, // PSECURITY_DESCRIPTOR
    _Inout_ PULONG CapturedLength,
    _Inout_ PVOID *ObjectSecurityDescriptor, // PSECURITY_DESCRIPTOR
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

