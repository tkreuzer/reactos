/*!
 * \file    Ob/Security.cpp
 * \brief   Security related Ob functions
 * \license GPL - See COPYING in the top level directory
 * \author  Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include "Obp.hpp"

#include "Se/Se.hpp"

extern "C"
NTSTATUS
NTAPI
ObQueryObjectAuditingByHandle (
    _In_ HANDLE Handle,
    _Out_ PBOOLEAN GenerateOnClose)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
BOOLEAN
NTAPI
ObCheckCreateObjectAccess (
    _In_ PVOID Object,
    _In_ ACCESS_MASK CreateAccess,
    _In_ PACCESS_STATE AccessState,
    _In_ PUNICODE_STRING ComponentName,
    _In_ BOOLEAN LockHeld,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PNTSTATUS AccessStatus)
{
    __debugbreak();
    return FALSE;
}

extern "C"
BOOLEAN
NTAPI
ObCheckObjectAccess (
    _In_ PVOID Object,
    _Inout_ PACCESS_STATE AccessState,
    _In_ BOOLEAN LockHeld,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PNTSTATUS ReturnedStatus)
{
    __debugbreak();
    return FALSE;
}

extern "C"
NTSTATUS
NTAPI
ObAssignSecurity (
    _In_ PACCESS_STATE AccessState,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PVOID Object,
    _In_ POBJECT_TYPE Type)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
VOID
NTAPI
ObDereferenceSecurityDescriptor (
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Count)
{
    __debugbreak();
}

extern "C"
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
ObGetObjectSecurity (
    _In_ PVOID Object,
    _Out_ PSECURITY_DESCRIPTOR *SecurityDescriptor,
    _Out_ PBOOLEAN MemoryAllocated)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObLogSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR InputSecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *OutputSecurityDescriptor,
    _In_ ULONG RefBias)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
VOID
NTAPI
ObReferenceSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Count)
{
    __debugbreak();
}

extern "C"
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ObReleaseObjectSecurity (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ BOOLEAN MemoryAllocated)
{
    __debugbreak();
}

extern "C"
NTSTATUS
NTAPI
ObSetSecurityDescriptorInfo (
    _In_ PVOID Object,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR *OutputSecurityDescriptor,
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObSetSecurityObjectByPointer (
    _In_ PVOID Object,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObQuerySecurityDescriptorInfo (
    _In_ PVOID Object,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _Out_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Inout_ PULONG Length,
    _Out_ PSECURITY_DESCRIPTOR *OutputSecurityDescriptor)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObDeassignSecurity (
    _Inout_ PSECURITY_DESCRIPTOR *SecurityDescriptor)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObAssignObjectSecurityDescriptor (
    _Inout_ PVOID Object,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
    _In_ POOL_TYPE PoolType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

