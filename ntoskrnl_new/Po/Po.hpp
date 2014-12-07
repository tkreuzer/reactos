
#pragma once

#include <ntoskrnl.h>
#include <Io/Io.hpp>

// ntosp.h
DECLARE_HANDLE(POHANDLE);

// wdm.h
typedef ULONG EXECUTION_STATE, *PEXECUTION_STATE;

// ntosifs.h
typedef PVOID PO_COALESCING_REGISTRATION, *PPO_COALESCING_REGISTRATION;

// ntpoapi.h
typedef enum _PO_SLEEP_DISABLE_REASON
{
    PoSleepDisableReasonVideo = 0,
    PoSleepDisableReasonHypervisor,
    PoSleepDisableReasonVhdBoot,
    PoSleepDisableReasonPortableWorkspace,
    PoSleepDisableReasonMax
} PO_SLEEP_DISABLE_REASON, *PPO_SLEEP_DISABLE_REASON;

// wdm.h
typedef enum
{
    PowerActionNone = 0,
    PowerActionReserved,
    PowerActionSleep,
    PowerActionHibernate,
    PowerActionShutdown,
    PowerActionShutdownReset,
    PowerActionShutdownOff,
    PowerActionWarmEject,
    PowerActionDisplayOff
} POWER_ACTION, *PPOWER_ACTION;

// wdm.h
typedef enum _POWER_STATE_TYPE
{
    SystemPowerState = 0,
    DevicePowerState
} POWER_STATE_TYPE, *PPOWER_STATE_TYPE;

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
typedef enum _SHUTDOWN_ACTION
{
    ShutdownNoReboot = 0,
    ShutdownReboot = 1,
    ShutdownPowerOff = 2
} SHUTDOWN_ACTION;

// wdm.h
typedef enum _SYSTEM_POWER_STATE
{
    PowerSystemUnspecified = 0,
    PowerSystemWorking     = 1,
    PowerSystemSleeping1   = 2,
    PowerSystemSleeping2   = 3,
    PowerSystemSleeping3   = 4,
    PowerSystemHibernate   = 5,
    PowerSystemShutdown    = 6,
    PowerSystemMaximum     = 7
} SYSTEM_POWER_STATE, *PSYSTEM_POWER_STATE;

// wdm.h
typedef enum _DEVICE_POWER_STATE
{
    PowerDeviceUnspecified = 0,
    PowerDeviceD0,
    PowerDeviceD1,
    PowerDeviceD2,
    PowerDeviceD3,
    PowerDeviceMaximum
} DEVICE_POWER_STATE, *PDEVICE_POWER_STATE;

// wdm.h
typedef union _POWER_STATE
{
    SYSTEM_POWER_STATE SystemState;
    DEVICE_POWER_STATE DeviceState;
} POWER_STATE, *PPOWER_STATE;

// wdm.h
typedef enum _POWER_REQUEST_TYPE
{
    PowerRequestDisplayRequired,
    PowerRequestSystemRequired,
    PowerRequestAwayModeRequired,
    PowerRequestExecutionRequired
} POWER_REQUEST_TYPE, *PPOWER_REQUEST_TYPE;

// wdm.h
typedef enum
{
    SystemPowerPolicyAc,
    SystemPowerPolicyDc,
    VerifySystemPolicyAc,
    VerifySystemPolicyDc,
    SystemPowerCapabilities,
    SystemBatteryState,
    SystemPowerStateHandler,
    ProcessorStateHandler,
    SystemPowerPolicyCurrent,
    AdministratorPowerPolicy,
    SystemReserveHiberFile,
    ProcessorInformation,
    SystemPowerInformation,
    ProcessorStateHandler2,
    LastWakeTime,
    LastSleepTime,
    SystemExecutionState,
    SystemPowerStateNotifyHandler,
    ProcessorPowerPolicyAc,
    ProcessorPowerPolicyDc,
    VerifyProcessorPowerPolicyAc,
    VerifyProcessorPowerPolicyDc,
    ProcessorPowerPolicyCurrent,
    SystemPowerStateLogging,
    SystemPowerLoggingEntry,
    SetPowerSettingValue,
    NotifyUserPowerSetting,
    PowerInformationLevelUnused0,
    SystemMonitorHiberBootPowerOff,
    SystemVideoState,
    TraceApplicationPowerMessage,
    TraceApplicationPowerMessageEnd,
    ProcessorPerfStates,
    ProcessorIdleStates,
    ProcessorCap,
    SystemWakeSource,
    SystemHiberFileInformation,
    TraceServicePowerMessage,
    ProcessorLoad,
    PowerShutdownNotification,
    MonitorCapabilities,
    SessionPowerInit,
    SessionDisplayState,
    PowerRequestCreate,
    PowerRequestAction,
    GetPowerRequestList,
    ProcessorInformationEx,
    NotifyUserModeLegacyPowerEvent,
    GroupPark,
    ProcessorIdleDomains,
    WakeTimerList,
    SystemHiberFileSize,
    ProcessorIdleStatesHv,
    ProcessorPerfStatesHv,
    ProcessorPerfCapHv,
    ProcessorSetIdle,
    LogicalProcessorIdling,
    UserPresence,
    PowerSettingNotificationName,
    GetPowerSettingValue,
    IdleResiliency,
    SessionRITState,
    SessionConnectNotification,
    SessionPowerCleanup,
    SessionLockState,
    SystemHiberbootState,
    PlatformInformation,
    PdcInvocation,
    MonitorInvocation,
    FirmwareTableInformationRegistered,
    SetShutdownSelectedTime,
    SuspendResumeInvocation,
    PlmPowerRequestCreate,
    ScreenOff,
    CsDeviceNotification,
    PlatformRole,
    LastResumePerformance,
    DisplayBurst,
    ExitLatencySamplingPercentage,
    RegisterSpmPowerSettings,
    PlatformIdleStates,
    ProcessorIdleVeto,
    PlatformIdleVeto,
    SystemBatteryStatePrecise,
    ThermalEvent,
    PowerRequestActionInternal,
    BatteryDeviceState,
    PowerInformationInternal,
    ThermalStandby,
    SystemHiberFileType,
    PowerInformationLevelMaximum
} POWER_INFORMATION_LEVEL;

// ntosp.h
typedef enum
{
    PoLatencyHintMouse,
    PoLatencyHintKeyboard,
    PoLatencyHintTouch,
    PoLatencyHintLowLatencyWorkload,
    PoLatencyHintDeadline,
    PoLatencyHintMaximum
} PO_LATENCY_HINT_TYPE, *PPO_LATENCY_HINT_TYPE;

// wdm.h
typedef struct _COUNTED_REASON_CONTEXT
{
    ULONG Version;
    ULONG Flags;
    union
    {
        struct
        {
            UNICODE_STRING ResourceFileName;
            USHORT ResourceReasonId;
            ULONG StringCount;
            _Field_size_(StringCount) PUNICODE_STRING ReasonStrings;
        } DUMMYSTRUCTNAME;
        UNICODE_STRING SimpleString;
    } DUMMYUNIONNAME;
} COUNTED_REASON_CONTEXT, *PCOUNTED_REASON_CONTEXT;

// ntosifs.h
typedef
_Function_class_(REQUEST_POWER_COMPLETE)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
VOID
NTAPI
REQUEST_POWER_COMPLETE (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ UCHAR MinorFunction,
    _In_ POWER_STATE PowerState,
    _In_opt_ PVOID Context,
    _In_ PIO_STATUS_BLOCK IoStatus);
typedef REQUEST_POWER_COMPLETE *PREQUEST_POWER_COMPLETE;

// ntosifs.h
typedef enum _PO_COALESCING_MSG
{

     REGISTRY_FIRST_DIRTY_WRITE_AFTER_COMMAND_FLUSH,
     PM_COALESCE_ON,
     PM_COALESCE_OFF,
     PM_COMMAND_FLUSH,
     DISK_SPINUP,
     CACHE_FIRST_DIRTY_WRITE_AFTER_COMMAND_FLUSH
} PO_COALESCING_MSG;

// ntosifs.h
typedef
VOID
NTAPI
PO_COALESCING_CALLBACK (
    _In_ PO_COALESCING_MSG Msg,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ PVOID Context);
typedef PO_COALESCING_CALLBACK *PPO_COALESCING_CALLBACK;

typedef enum
{
    MonitorRequestReasonUnknown,
    MonitorRequestReasonPowerButton,
    MonitorRequestReasonRemoteConnection,
    MonitorRequestReasonScMonitorpower,
    MonitorRequestReasonUserInput,
    MonitorRequestReasonAcDcDisplayBurst,
    MonitorRequestReasonUserDisplayBurst,
    MonitorRequestReasonPoSetSystemState,
    MonitorRequestReasonSetThreadExecutionState,
    MonitorRequestReasonFullWake,
    MonitorRequestReasonSessionUnlock,
    MonitorRequestReasonScreenOffRequest,
    MonitorRequestReasonIdleTimeout,
    MonitorRequestReasonPolicyChange,
    MonitorRequestReasonSleepButton,
    MonitorRequestReasonLid,
    MonitorRequestReasonBatteryCountChange,
    MonitorRequestReasonGracePeriod,
    MonitorRequestReasonPnP,
    MonitorRequestReasonDP,
    MonitorRequestReasonSxTransition,
    MonitorRequestReasonSystemIdle,
    MonitorRequestReasonNearProximity,
    MonitorRequestReasonMax
} POWER_MONITOR_REQUEST_REASON;
