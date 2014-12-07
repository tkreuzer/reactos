
#include "Ps.hpp"
#include "Thread.hpp"

extern "C" {

ULONG PsUILanguageComitted;

// wdm.h
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("RtlGetVersion", "Obsolete")
BOOLEAN
NTAPI
PsGetVersion (
    _Out_opt_ PULONG MajorVersion,
    _Out_opt_ PULONG MinorVersion,
    _Out_opt_ PULONG BuildNumber,
    _Out_opt_ PUNICODE_STRING CSDVersion)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
typedef
_IRQL_requires_same_
_Function_class_(EX_CALLBACK_FUNCTION)
NTSTATUS
NTAPI
EX_CALLBACK_FUNCTION (
    _In_ PVOID CallbackContext,
    _In_opt_ PVOID Argument1,
    _In_opt_ PVOID Argument2);
typedef EX_CALLBACK_FUNCTION *PEX_CALLBACK_FUNCTION;

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PsEstablishWin32Callouts (
    _In_ PEX_CALLBACK_FUNCTION CalloutDispatchRoutine)
{
    __debugbreak();
}


// ntosp.h
BOOLEAN
NTAPI
PsIsDiskCountersEnabled (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
VOID
NTAPI
PsUpdateDiskCounters (
    _Inout_ PEPROCESS Process,
    _In_ ULONG64 BytesRead,
    _In_ ULONG64 BytesWritten,
    _In_ ULONG ReadOperationCount,
    _In_ ULONG WriteOperationCount,
    _In_ ULONG FlushOperationCount)
{
    __debugbreak();
}

// ntosp.h
typedef enum _CONTAINER_TYPE
{
    ContainerTypeCpu,
    ContainerTypeDiskIo,
    ContainerTypeNetIo,
//    ContainerTypeWorkingSet,
    ContainerTypeHeap,
    ContainerTypeImmediate,
    ContainerTypeMaximumList
} CONTAINER_TYPE, *PCONTAINER_TYPE;

// ntosp.h
typedef struct _CONTAINER_ID_INFO
{
    GUID ContainerId;
    ULONG Flags;
} CONTAINER_ID_INFO, *PCONTAINER_ID_INFO;

// ntosp.h
NTSTATUS
NTAPI
PsGetEffectiveContainerId (
    _In_ CONTAINER_TYPE ContainerType,
    _In_ PETHREAD Thread,
    _Out_ PCONTAINER_ID_INFO ContainerIdInfo)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
typedef ULONG PROCESS_ENERGY_COMPONENT_TYPE_NUM;

// ntosp.h
VOID
NTAPI
PsUpdateComponentPower (
    _Inout_ PEPROCESS Process,
    _In_ PROCESS_ENERGY_COMPONENT_TYPE_NUM ComponentType,
    _In_ ULONG64 IncrementEnergy)
{
    __debugbreak();
}

// reactos
ULONG
NTAPI
PsSetLegoNotifyRoutine (
    _In_ PVOID LegoNotifyRoutine)
{
    __debugbreak();
    return 0;
}

#if 0 // internal? from ntosp.h
#if !defined(_WIN64) && !defined(_ARM_)
NTSTATUS
PsSetLdtEntries (
    _In_ ULONG Selector0,
    _In_ ULONG Entry0Low,
    _In_ ULONG Entry0Hi,
    _In_ ULONG Selector1,
    _In_ ULONG Entry1Low,
    _In_ ULONG Entry1Hi);

NTSTATUS
PsSetProcessLdtInfo (
    _In_ PPROCESS_LDT_INFORMATION LdtInformation,
    _In_ ULONG LdtInformationLength);
#endif // !defined(_WIN64) && !defined(_ARM_)

#endif // 0

} // extern "C"
