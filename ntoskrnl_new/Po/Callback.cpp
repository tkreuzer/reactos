
#include "Po.hpp"

extern "C" {

// ntosp.h
typedef
_Function_class_(POWER_SETTING_CALLBACK)
_IRQL_requires_same_
NTSTATUS
NTAPI
POWER_SETTING_CALLBACK (
    _In_ LPCGUID SettingGuid,
    _In_reads_bytes_(ValueLength) PVOID Value,
    _In_ ULONG ValueLength,
    _Inout_opt_ PVOID Context);
typedef POWER_SETTING_CALLBACK *PPOWER_SETTING_CALLBACK;

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PoRegisterPowerSettingCallback (
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _In_ LPCGUID SettingGuid,
    _In_ PPOWER_SETTING_CALLBACK Callback,
    _In_opt_ PVOID Context,
    _Outptr_opt_ PVOID *Handle
    );

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PoUnregisterPowerSettingCallback (
    _Inout_ PVOID Handle
    );

// ntosisf.h
typedef
VOID
NTAPI
PO_COALESCING_CALLBACK (
    _In_ PO_COALESCING_MSG Msg,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ PVOID Context);
typedef PO_COALESCING_CALLBACK *PPO_COALESCING_CALLBACK;

// ntosisf.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PoRegisterCoalescingCallback (
    _In_ PPO_COALESCING_CALLBACK Callback,
    _In_ BOOLEAN Client,
    _Out_ PPO_COALESCING_REGISTRATION Registration,
    _In_opt_ PVOID Context
    );

// ntosisf.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
PoUnregisterCoalescingCallback (
    _In_ PO_COALESCING_REGISTRATION Registration
    );

} // extern "C"
