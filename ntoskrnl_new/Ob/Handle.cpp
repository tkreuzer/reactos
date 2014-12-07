
#include "Obp.hpp"

typedef struct _OBJECT_HANDLE_ATTRIBUTE_INFORMATION *POBJECT_HANDLE_ATTRIBUTE_INFORMATION;

extern "C"
BOOLEAN
NTAPI
ObIsKernelHandle (
    _In_ HANDLE Handle)
{
    __debugbreak();
    return FALSE;
}

extern "C"
NTSTATUS
NTAPI
ObCloseHandle (
    _In_ HANDLE Handle,
    _In_ KPROCESSOR_MODE PreviousMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObInsertObject (
    _In_ PVOID Object,
    _Inout_opt_ PACCESS_STATE PassedAccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _In_ ULONG ObjectPointerBias,
    _Out_opt_ PVOID *NewObject,
    _Out_opt_ PHANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObOpenObjectByPointerWithTag (
    _In_ PVOID Object,
    _In_ ULONG HandleAttributes,
    _In_opt_ PACCESS_STATE PassedAccessState,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Tag,
    _Out_ PHANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObOpenObjectByPointer (
    _In_ PVOID Object,
    _In_ ULONG HandleAttributes,
    _In_opt_ PACCESS_STATE PassedAccessState,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PHANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObOpenObjectByName (
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_opt_ PACCESS_STATE PassedAccessState,
    _In_ ACCESS_MASK DesiredAccess,
    _Inout_opt_ PVOID ParseContext,
    _Out_ PHANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
ObReferenceObjectByHandle (
    _In_ HANDLE Handle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PVOID *Object,
    _Out_opt_ POBJECT_HANDLE_INFORMATION HandleInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
ObReferenceObjectByHandleWithTag (
    _In_ HANDLE Handle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Tag,
    _Out_ PVOID *Object,
    _Out_opt_ POBJECT_HANDLE_INFORMATION HandleInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObDuplicateObject(
    _In_ PEPROCESS SourceProcess,
    _In_ HANDLE SourceHandle,
    _In_opt_ PEPROCESS TargetProcess,
    _In_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options,
    _In_ KPROCESSOR_MODE PreviousMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObSetHandleAttributes(
    _In_ HANDLE Handle,
    _In_ POBJECT_HANDLE_ATTRIBUTE_INFORMATION HandleFlags,
    _In_ KPROCESSOR_MODE PreviousMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
BOOLEAN
NTAPI
ObFindHandleForObject (
    _In_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ POBJECT_TYPE ObjectType,
    _In_ POBJECT_HANDLE_INFORMATION HandleInformation,
    _Out_ PHANDLE Handle)
{
    __debugbreak();
    return FALSE;
}

