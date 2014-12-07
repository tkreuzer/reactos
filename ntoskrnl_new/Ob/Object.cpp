
#include "Obp.hpp"

typedef struct _OBJECT_CREATE_INFORMATION *POBJECT_CREATE_INFORMATION;

extern "C"
VOID
NTAPI
ObFreeObjectCreateInfoBuffer(
    _Pre_notnull_ __drv_freesMem(Mem)
        POBJECT_CREATE_INFORMATION ObjectCreateInfo)
{
    __debugbreak();
}

extern "C"
VOID
NTAPI
ObDeleteCapturedInsertInfo (
    _In_ PVOID Object)
{
    __debugbreak();
}

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObCreateObject (
    _In_ KPROCESSOR_MODE ProbeMode,
    _In_ POBJECT_TYPE ObjectType,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ KPROCESSOR_MODE OwnershipMode,
    _Inout_opt_ PVOID ParseContext,
    _In_ ULONG ObjectBodySize,
    _In_ ULONG PagedPoolCharge,
    _In_ ULONG NonPagedPoolCharge,
    _Outptr_ PVOID *Object)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
VOID
NTAPI
ObMakeTemporaryObject (
    _In_ PVOID Object)
{
    __debugbreak();
}

