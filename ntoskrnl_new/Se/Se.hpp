
#pragma once

#include <ntoskrnl.h>
#include <Rtl/Sid.hpp>
#include <Rtl/SecurityDescriptor.hpp>
#include <Ke/Ke.hpp>
#include <Ex/Ex.hpp>

// winnt.h
typedef UCHAR SE_SIGNING_LEVEL, *PSE_SIGNING_LEVEL;

// wdm.h
typedef PVOID PACCESS_TOKEN;

typedef ULONG SECURITY_INFORMATION, *PSECURITY_INFORMATION;
typedef BOOLEAN SECURITY_CONTEXT_TRACKING_MODE, *PSECURITY_CONTEXT_TRACKING_MODE;

typedef enum _SECURITY_OPERATION_CODE
{
    SetSecurityDescriptor,
    QuerySecurityDescriptor,
    DeleteSecurityDescriptor,
    AssignSecurityDescriptor
} SECURITY_OPERATION_CODE, *PSECURITY_OPERATION_CODE;

typedef struct _ACCESS_STATE *PACCESS_STATE;

typedef struct _GENERIC_MAPPING
{
    ACCESS_MASK GenericRead;
    ACCESS_MASK GenericWrite;
    ACCESS_MASK GenericExecute;
    ACCESS_MASK GenericAll;
} GENERIC_MAPPING, *PGENERIC_MAPPING;

typedef enum _SECURITY_IMPERSONATION_LEVEL
{
    SecurityAnonymous,
    SecurityIdentification,
    SecurityImpersonation,
    SecurityDelegation
} SECURITY_IMPERSONATION_LEVEL, * PSECURITY_IMPERSONATION_LEVEL;

typedef struct _SECURITY_QUALITY_OF_SERVICE
{
    ULONG Length;
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
    SECURITY_CONTEXT_TRACKING_MODE ContextTrackingMode;
    BOOLEAN EffectiveOnly;
} SECURITY_QUALITY_OF_SERVICE, *PSECURITY_QUALITY_OF_SERVICE;

typedef struct _LUID_AND_ATTRIBUTES
{
    LUID Luid;
    ULONG Attributes;
} LUID_AND_ATTRIBUTES, * PLUID_AND_ATTRIBUTES;

typedef LUID_AND_ATTRIBUTES LUID_AND_ATTRIBUTES_ARRAY[ANYSIZE_ARRAY];
typedef LUID_AND_ATTRIBUTES_ARRAY *PLUID_AND_ATTRIBUTES_ARRAY;

typedef struct _PRIVILEGE_SET
{
    ULONG PrivilegeCount;
    ULONG Control;
    LUID_AND_ATTRIBUTES Privilege[ANYSIZE_ARRAY];
} PRIVILEGE_SET, * PPRIVILEGE_SET;

// ntofs.h
typedef struct _OBJECT_TYPE_LIST
{
    USHORT Level;
    USHORT Sbz;
    GUID *ObjectType;
} OBJECT_TYPE_LIST, *POBJECT_TYPE_LIST;

// ntifs.h
typedef enum _AUDIT_EVENT_TYPE
{
    AuditEventObjectAccess,
    AuditEventDirectoryServiceAccess
} AUDIT_EVENT_TYPE, *PAUDIT_EVENT_TYPE;

extern "C"
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
    _In_ PGENERIC_MAPPING GenericMapping);

extern "C"
NTSTATUS
NTAPI
SeDefaultObjectMethodEx (
    _In_ PVOID Object,
    _In_ SECURITY_OPERATION_CODE OperationType,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _In_ PVOID SecurityDescriptor, // PSECURITY_DESCRIPTOR
    _Inout_ PULONG CapturedLength,
    _Inout_ PVOID *ObjectSecurityDescriptor, // PSECURITY_DESCRIPTOR
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode);
