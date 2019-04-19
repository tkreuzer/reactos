
#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

ULONG
NTAPI
ObGetProcessHandleCount(
    IN PEPROCESS Process)
{
    __debugbreak();
    return 0;
}

LONG
FASTCALL
ObDereferenceObjectEx(
    IN PVOID Object,
    IN LONG Count)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
ObFreeObjectCreateInfoBuffer(
    IN POBJECT_CREATE_INFORMATION ObjectCreateInfo)
{
    __debugbreak();
}

PVOID
NTAPI
ObpAllocateObjectCreateInfoBuffer(
    IN PP_NPAGED_LOOKASIDE_NUMBER Type)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
ObpFreeCapturedAttributes(
    IN PVOID Buffer,
    IN PP_NPAGED_LOOKASIDE_NUMBER Type)
{
    __debugbreak();
}

VOID
NTAPI
ObClearProcessHandleTable(
    IN PEPROCESS Process)
{
    __debugbreak();
}

VOID
NTAPI
ObDereferenceDeviceMap(
    IN PEPROCESS Process)
{
    __debugbreak();
}

VOID
NTAPI
ObKillProcess(
    IN PEPROCESS Process)
{
    __debugbreak();
}

NTSTATUS
NTAPI
ObInitProcess(
    IN PEPROCESS Parent OPTIONAL,
    IN PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
ObInheritDeviceMap(
    IN PEPROCESS Parent,
    IN PEPROCESS Process)
{
    __debugbreak();
}

VOID
NTAPI
ObQueryDeviceMapInformation(
    IN PEPROCESS Process,
    OUT PPROCESS_DEVICEMAP_INFORMATION DeviceMapInfo)
{
    __debugbreak();
}

LONG
FASTCALL
ObReferenceObjectEx(
    IN PVOID Object,
    IN LONG Count)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
ObAssignObjectSecurityDescriptor(
    IN PVOID Object,
    IN PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
    IN POOL_TYPE PoolType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
ObDeassignSecurity(
    IN OUT PSECURITY_DESCRIPTOR *SecurityDescriptor)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
ObQuerySecurityDescriptorInfo(
    IN PVOID Object,
    IN PSECURITY_INFORMATION SecurityInformation,
    OUT PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN OUT PULONG Length,
    IN PSECURITY_DESCRIPTOR *OutputSecurityDescriptor)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

