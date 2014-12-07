
#include <ntifs.h>

POBJECT_TYPE CmKeyObjectType;

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
CmCallbackGetKeyObjectID (
    _In_ PLARGE_INTEGER Cookie,
    _In_ PVOID Object,
    _Out_opt_ PULONG_PTR ObjectID,
    _Outptr_opt_ PCUNICODE_STRING *ObjectName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
CmCallbackGetKeyObjectIDEx (
    _In_ PLARGE_INTEGER Cookie,
    _In_ PVOID Object,
    _Out_opt_ PULONG_PTR ObjectID,
    _Outptr_opt_ PCUNICODE_STRING *ObjectName,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
CmCallbackReleaseKeyObjectIDEx (
    _In_ PCUNICODE_STRING ObjectName)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
CmGetBoundTransaction (
    _In_ PLARGE_INTEGER Cookie,
    _In_ PVOID Object)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
CmGetCallbackVersion (
    _Out_opt_ PULONG Major,
    _Out_opt_ PULONG Minor)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
CmRegisterCallback (
    _In_ PEX_CALLBACK_FUNCTION Function,
    _In_opt_ PVOID Context,
    _Out_ PLARGE_INTEGER Cookie)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
CmRegisterCallbackEx (
    _In_ PEX_CALLBACK_FUNCTION Function,
    _In_ PCUNICODE_STRING Altitude,
    _In_ PVOID Driver, // PDRIVER_OBJECT
    _In_opt_ PVOID Context,
    _Out_ PLARGE_INTEGER Cookie,
    _Reserved_  PVOID Reserved)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
CmUnRegisterCallback (
    _In_ LARGE_INTEGER Cookie)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
CmSetCallbackObjectContext (
    _Inout_ PVOID Object,
    _In_ PLARGE_INTEGER Cookie,
    _In_ PVOID NewContext,
    _Out_opt_ PVOID *OldContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

