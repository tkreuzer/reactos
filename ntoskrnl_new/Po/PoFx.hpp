
#pragma once

#include "Po.hpp"

typedef
_Function_class_(PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK (
    _In_ PVOID Context,
    _In_ ULONG Component);
typedef PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK
    *PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK;

typedef
_Function_class_(PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK (
    _In_ PVOID Context,
    _In_ ULONG Component);
typedef PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK
    *PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK;

typedef
_Function_class_(PO_FX_COMPONENT_IDLE_STATE_CALLBACK)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PO_FX_COMPONENT_IDLE_STATE_CALLBACK (
    _In_ PVOID Context,
    _In_ ULONG Component,
    _In_ ULONG State);
typedef PO_FX_COMPONENT_IDLE_STATE_CALLBACK
    *PPO_FX_COMPONENT_IDLE_STATE_CALLBACK;

typedef
_Function_class_(PO_FX_DEVICE_POWER_REQUIRED_CALLBACK)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PO_FX_DEVICE_POWER_REQUIRED_CALLBACK (
    _In_ PVOID Context);
typedef PO_FX_DEVICE_POWER_REQUIRED_CALLBACK
    *PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK;

typedef
_Function_class_(PO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK (
    _In_ PVOID Context);
typedef PO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK
    *PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK;

typedef
_Function_class_(PO_FX_POWER_CONTROL_CALLBACK)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
PO_FX_POWER_CONTROL_CALLBACK (
    _In_ PVOID DeviceContext,
    _In_ LPCGUID PowerControlCode,
    _In_reads_bytes_opt_(InBufferSize) PVOID InBuffer,
    _In_ SIZE_T InBufferSize,
    _Out_writes_bytes_opt_(OutBufferSize) PVOID OutBuffer,
    _In_ SIZE_T OutBufferSize,
    _Out_opt_ PSIZE_T BytesReturned);
typedef PO_FX_POWER_CONTROL_CALLBACK *PPO_FX_POWER_CONTROL_CALLBACK;

typedef
_Function_class_(PO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK)
_IRQL_requires_max_(HIGH_LEVEL)
VOID
NTAPI
PO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK (
    _In_ PVOID Context,
    _In_ ULONG Component,
    _In_ BOOLEAN Active);
typedef PO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK
    *PPO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK;

typedef
_Function_class_(PO_FX_COMPONENT_PERF_STATE_CALLBACK)
VOID
NTAPI
PO_FX_COMPONENT_PERF_STATE_CALLBACK(
    _In_ PVOID Context,
    _In_ ULONG Component,
    _In_ BOOLEAN Succeeded,
    _In_ PVOID RequestContext);
typedef PO_FX_COMPONENT_PERF_STATE_CALLBACK
    *PPO_FX_COMPONENT_PERF_STATE_CALLBACK;

typedef struct _PO_FX_COMPONENT_IDLE_STATE
{
    ULONGLONG TransitionLatency;
    ULONGLONG ResidencyRequirement;
    ULONG NominalPower;
} PO_FX_COMPONENT_IDLE_STATE, *PPO_FX_COMPONENT_IDLE_STATE;

typedef struct _PO_FX_COMPONENT_V1
{
    GUID Id;
    ULONG IdleStateCount;
    ULONG DeepestWakeableIdleState;
    _Field_size_full_(IdleStateCount) PPO_FX_COMPONENT_IDLE_STATE IdleStates;
} PO_FX_COMPONENT_V1, *PPO_FX_COMPONENT_V1;

typedef struct _PO_FX_DEVICE_V1
{
    ULONG Version;
    ULONG ComponentCount;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK ComponentIdleStateCallback;
    PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK DevicePowerRequiredCallback;
    PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK DevicePowerNotRequiredCallback;
    PPO_FX_POWER_CONTROL_CALLBACK PowerControlCallback;
    PVOID DeviceContext;
    _Field_size_full_(ComponentCount) PO_FX_COMPONENT_V1 Components[ANYSIZE_ARRAY];
} PO_FX_DEVICE_V1, *PPO_FX_DEVICE_V1;

#define PO_FX_COMPONENT_FLAG_F0_ON_DX 0x0000000000000001
#define PO_FX_COMPONENT_FLAG_NO_DEBOUNCE 0x0000000000000002

typedef struct _PO_FX_COMPONENT_V2
{
    GUID Id;
    ULONGLONG Flags;
    ULONG DeepestWakeableIdleState;
    ULONG IdleStateCount;
    _Field_size_full_(IdleStateCount) PPO_FX_COMPONENT_IDLE_STATE IdleStates;
    ULONG ProviderCount;
    _Field_size_full_(ProviderCount) PULONG Providers;
} PO_FX_COMPONENT_V2, *PPO_FX_COMPONENT_V2;

typedef struct _PO_FX_DEVICE_V2
{
    ULONG Version;
    ULONGLONG Flags;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK ComponentIdleStateCallback;
    PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK DevicePowerRequiredCallback;
    PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK DevicePowerNotRequiredCallback;
    PPO_FX_POWER_CONTROL_CALLBACK PowerControlCallback;
    PVOID DeviceContext;
    ULONG ComponentCount;
    _Field_size_full_(ComponentCount) PO_FX_COMPONENT_V2 Components[ANYSIZE_ARRAY];
} PO_FX_DEVICE_V2, *PPO_FX_DEVICE_V2;

#if (PO_FX_VERSION == PO_FX_VERSION_V1)
typedef PO_FX_COMPONENT_V1 PO_FX_COMPONENT, *PPO_FX_COMPONENT;
typedef PO_FX_DEVICE_V1 PO_FX_DEVICE, *PPO_FX_DEVICE;
#elif (PO_FX_VERSION == PO_FX_VERSION_V2)
typedef PO_FX_COMPONENT_V2 PO_FX_COMPONENT, *PPO_FX_COMPONENT;
typedef PO_FX_DEVICE_V2 PO_FX_DEVICE, *PPO_FX_DEVICE;
#else
#error PO_FX_VERSION undefined!
#endif

typedef enum _PO_FX_PERF_STATE_UNIT {
    PoFxPerfStateUnitOther,
    PoFxPerfStateUnitFrequency,
    PoFxPerfStateUnitBandwidth,
    PoFxPerfStateUnitMaximum
} PO_FX_PERF_STATE_UNIT, *PPO_FX_PERF_STATE_UNIT;

typedef enum _PO_FX_PERF_STATE_TYPE {
    PoFxPerfStateTypeDiscrete,
    PoFxPerfStateTypeRange,
    PoFxPerfStateTypeMaximum
} PO_FX_PERF_STATE_TYPE, *PPO_FX_PERF_STATE_TYPE;

typedef struct _PO_FX_PERF_STATE {
    ULONGLONG Value;
    PVOID Context;
} PO_FX_PERF_STATE, *PPO_FX_PERF_STATE;

typedef struct _PO_FX_COMPONENT_PERF_SET {
    UNICODE_STRING Name;
    ULONGLONG Flags;
    PO_FX_PERF_STATE_UNIT Unit;
    PO_FX_PERF_STATE_TYPE Type;
    union {
        struct {
            ULONG Count;
            _Field_size_full_(Count) PPO_FX_PERF_STATE States;
        } Discrete;
        struct {
            ULONGLONG Minimum;
            ULONGLONG Maximum;
        } Range;
    };
} PO_FX_COMPONENT_PERF_SET, *PPO_FX_COMPONENT_PERF_SET;

typedef struct _PO_FX_COMPONENT_PERF_INFO {
    ULONG PerfStateSetsCount;
    PO_FX_COMPONENT_PERF_SET PerfStateSets[ANYSIZE_ARRAY];
} PO_FX_COMPONENT_PERF_INFO, *PPO_FX_COMPONENT_PERF_INFO;

typedef struct _PO_FX_PERF_STATE_CHANGE {
    ULONG Set;
    union {
        ULONG StateIndex;
        ULONGLONG StateValue;
    };
} PO_FX_PERF_STATE_CHANGE, *PPO_FX_PERF_STATE_CHANGE;

typedef struct _PO_FX_PRIMARY_DEVICE {
    ULONG Version;
    ULONG ComponentCount;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK ComponentIdleStateCallback;
    PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK DevicePowerRequiredCallback;
    PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK DevicePowerNotRequiredCallback;
    PPO_FX_POWER_CONTROL_CALLBACK PowerControlCallback;
    PPO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK ComponentCriticalTransitionCallback;
    PVOID DeviceContext;
    _Field_size_full_(ComponentCount) PO_FX_COMPONENT Components[ANYSIZE_ARRAY];
} PO_FX_PRIMARY_DEVICE, *PPO_FX_PRIMARY_DEVICE;

#define PO_FX_UNKNOWN_POWER                         0xFFFFFFFF
#define PO_FX_UNKNOWN_TIME                          0xFFFFFFFFFFFFFFFF
#define PO_FX_FLAG_BLOCKING                         0x01
#define PO_FX_FLAG_ASYNC_ONLY                       0x02

#define PO_FX_FLAG_PERF_PEP_OPTIONAL                0x01
#define PO_FX_FLAG_PERF_QUERY_ON_F0                 0x02
#define PO_FX_FLAG_PERF_QUERY_ON_ALL_IDLE_STATES    0x04
