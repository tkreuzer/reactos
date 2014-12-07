
#include <ntifs.h>

POBJECT_TYPE ExDesktopObjectType;
POBJECT_TYPE ExEventObjectType;
POBJECT_TYPE ExSemaphoreObjectType;
POBJECT_TYPE ExWindowStationObjectType;
POBJECT_TYPE ExCompositionObjectType;
POBJECT_TYPE ExCompositionSurfaceObjectType;
POBJECT_TYPE ExRawInputManagerObjectType;

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
ExUuidCreate (
    _Out_ UUID *Uuid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
ExVerifySuite (
    __drv_strictTypeMatch(__drv_typeExpr) _In_ SUITE_TYPE SuiteType)
{
    __debugbreak();
    return FALSE;
}

/// see https://github.com/kedebug/ScDetective/blob/master/ScDetective_Driver/ScDetective/Protect/ScProtect.h
typedef struct _HANDLE_TABLE_ENTRY
{
    union
    {
        PVOID Object;
        ULONG ObAttributes;
    };
    union
    {
        union
        {
            ACCESS_MASK GrantedAccess;
            struct
            {
                USHORT GrantedAccessIndex;
                USHORT CreatorBackTraceIndex;
            };
        };
        LONG NextFreeTableEntry;
    };
} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;

typedef
BOOLEAN
(NTAPI
*EX_ENUMERATE_HANDLE_ROUTINE) (
    _In_ PHANDLE_TABLE_ENTRY HandleTableEntry,
    _In_ HANDLE Handle,
    _In_ PVOID EnumParameter);

BOOLEAN
NTAPI
ExEnumHandleTable (
    _In_ PVOID HandleTable,
    _In_ EX_ENUMERATE_HANDLE_ROUTINE EnumHandleProcedure,
    _In_ PVOID EnumParameter,
    _Out_opt_ PHANDLE Handle)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
ExQueryFastCacheAppOrigin (
    _In_ PUNICODE_STRING PackageFullName,
    _Out_ ULONG* AppOrigin)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
DECLSPEC_DEPRECATED_DDK
BOOLEAN
NTAPI
ExTryQueueWorkItem (
    _Inout_ __drv_aliasesMem PWORK_QUEUE_ITEM WorkItem,
    _In_ WORK_QUEUE_TYPE QueueType)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
DECLSPEC_DEPRECATED_DDK
VOID
NTAPI
ExQueueWorkItem (
    _Inout_ __drv_aliasesMem PWORK_QUEUE_ITEM WorkItem,
    _In_ WORK_QUEUE_TYPE QueueType)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
__analysis_noreturn
NTSTATUS
NTAPI
ExRaiseHardError (
    _In_ NTSTATUS ErrorStatus,
    _In_ ULONG NumberOfParameters,
    _In_ ULONG UnicodeStringParameterMask,
    _In_reads_opt_(NumberOfParameters) PULONG_PTR Parameters,
    _In_ ULONG ValidResponseOptions,
    _Out_ PULONG Response)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
DECLSPEC_NORETURN
VOID
NTAPI
ExRaiseDatatypeMisalignment (
    VOID)
{
    __debugbreak();
    for (;;);
}

VOID NTAPI ExQueryAttributeInformation() { __debugbreak(); }

