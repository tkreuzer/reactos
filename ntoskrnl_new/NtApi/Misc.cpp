
#include <ntoskrnl.h>
#include <Io/Io.hpp>
#include <Ob/Ob.hpp>
#include <Se/Token.hpp>
#include <Tm/Tm.hpp>

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtQueryLicenseValue (
    _In_ PUNICODE_STRING ValueName,
    _Out_opt_ PULONG Type,
    _Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
    _In_ ULONG DataSize,
    _Out_ PULONG ResultDataSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtLockProductActivationKeys (
    _Inout_opt_ ULONG   *pPrivateVer,
    _Out_opt_ ULONG   *pSafeMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtAllocateLocallyUniqueId (
    _Out_ PLUID Luid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
__kernel_entry
NTSTATUS
NTAPI
NtAllocateUuids (
    _Out_ PULARGE_INTEGER Time,
    _Out_ PULONG Range,
    _Out_ PULONG Sequence,
    _Out_writes_bytes_(6) PCHAR Seed)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetUuidSeed (
    _In_reads_bytes_(6) PCHAR Seed)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtDisableLastKnownGood (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtEnableLastKnownGood (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__analysis_noreturn
__kernel_entry
NTSTATUS
NTAPI
NtRaiseHardError (
    _In_ NTSTATUS ErrorStatus,
    _In_ ULONG NumberOfParameters,
    _In_ ULONG UnicodeStringParameterMask,
    _In_reads_(NumberOfParameters) PULONG_PTR Parameters,
    _In_ ULONG ValidResponseOptions,
    _Out_ PULONG Response)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryTimerResolution (
    _Out_ PULONG MaximumTime,
    _Out_ PULONG MinimumTime,
    _Out_ PULONG CurrentTime)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetTimerResolution (
    _In_ ULONG DesiredTime,
    _In_ BOOLEAN SetResolution,
    _Out_ PULONG ActualTime)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDisplayString (
    _In_ PUNICODE_STRING String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDrawText (
    _In_ PUNICODE_STRING String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtReplacePartitionUnit (
    _In_ PUNICODE_STRING TargetInstancePath,
    _In_ PUNICODE_STRING SpareInstancePath,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h
typedef union _FILE_SEGMENT_ELEMENT {
    PVOID64 Buffer;
    ULONGLONG Alignment;
} FILE_SEGMENT_ELEMENT, *PFILE_SEGMENT_ELEMENT;

__kernel_entry
NTSTATUS
NTAPI
NtWriteFileGather (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtReadFileScatter (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtLoadDriver (
    _In_ PUNICODE_STRING DriverServiceName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtUnloadDriver(
    _In_ PUNICODE_STRING DriverServiceName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtFlushInstructionCache (
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG FlushSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtFlushWriteBuffer (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
__kernel_entry
NTSTATUS
NTAPI
NtFlushProcessWriteBuffers (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtClose (
    _In_ HANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDuplicateObject (
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_ HANDLE TargetProcessHandle,
    _Out_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQueryObject(
    _In_opt_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetInformationObject(
    _In_ HANDLE ObjectHandle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _In_ PVOID ObjectInformation,
    _In_ ULONG Length)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtMakeTemporaryObject(
    _In_ HANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtMakePermanentObject (
    _In_ HANDLE Object)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQuerySecurityObject (
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Length,
    _Out_ PULONG LengthNeeded)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetSecurityObject (
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryInstallUILanguage (
    _Out_ LANGID *InstallUILanguageId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtFlushInstallUILanguage (
    _In_ ULONG InstallUILanguage,
    _In_ ULONG SetComittedFlag)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtIsUILanguageComitted (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetDefaultHardErrorPort (
    _In_ HANDLE DefaultHardErrorPort)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryDefaultLocale (
    _In_ BOOLEAN UserProfile,
    _Out_ PLCID DefaultLocaleId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryDefaultUILanguage (
    _Out_ LANGID *DefaultUILanguageId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef UCHAR SE_SIGNING_LEVEL, *PSE_SIGNING_LEVEL;

__kernel_entry
NTSTATUS
NTAPI
NtGetCachedSigningLevel(
    _In_ HANDLE File,
    _Out_ PULONG Flags,
    _Out_ PSE_SIGNING_LEVEL SigningLevel,
    _Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
    _Inout_opt_ PULONG ThumbprintSize,
    _Out_opt_ PULONG ThumbprintAlgorithm)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetCachedSigningLevel(
    _In_ ULONG Flags,
    _In_ SE_SIGNING_LEVEL InputSigningLevel,
    _In_reads_(SourceFileCount) PHANDLE SourceFiles,
    _In_ ULONG SourceFileCount,
    _In_opt_ HANDLE TargetFile)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtImpersonateThread (
    _In_ HANDLE ServerThreadHandle,
    _In_ HANDLE ClientThreadHandle,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


typedef int APPHELPCACHESERVICECLASS;

typedef PVOID PAPPHELP_CACHE_SERVICE_LOOKUP;

__kernel_entry
NTSTATUS
NTAPI
NtApphelpCacheControl (
    _In_ APPHELPCACHESERVICECLASS Service,
    _In_opt_ PAPPHELP_CACHE_SERVICE_LOOKUP ServiceData)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
typedef enum _MEMORY_RESERVE_TYPE
{
	MemoryReserveUserApc = 0,
	MemoryReserveIoCompletion = 1,
	MemoryReserveTypeMax = 2
} MEMORY_RESERVE_TYPE;

__kernel_entry
NTSTATUS
NTAPI
NtAllocateReserveObject (
    _Out_ PHANDLE MemoryReserveHandle,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ MEMORY_RESERVE_TYPE Type)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
typedef enum _PLUGPLAY_CONTROL_CLASS
{
	PlugPlayControlEnumerateDevice = 0,
	PlugPlayControlRegisterNewDevice = 1,
	PlugPlayControlDeregisterDevice = 2,
	PlugPlayControlInitializeDevice = 3,
	PlugPlayControlStartDevice = 4,
	PlugPlayControlUnlockDevice = 5,
	PlugPlayControlQueryAndRemoveDevice = 6,
	PlugPlayControlUserResponse = 7,
	PlugPlayControlGenerateLegacyDevice = 8,
	PlugPlayControlGetInterfaceDeviceList = 9,
	PlugPlayControlProperty = 10,
	PlugPlayControlDeviceClassAssociation = 11,
	PlugPlayControlGetRelatedDevice = 12,
	PlugPlayControlGetInterfaceDeviceAlias = 13,
	PlugPlayControlDeviceStatus = 14,
	PlugPlayControlGetDeviceDepth = 15,
	PlugPlayControlQueryDeviceRelations = 16,
	PlugPlayControlTargetDeviceRelation = 17,
	PlugPlayControlQueryConflictList = 18,
	PlugPlayControlRetrieveDock = 19,
	PlugPlayControlResetDevice = 20,
	PlugPlayControlHaltDevice = 21,
	PlugPlayControlGetBlockedDriverList = 22,
	MaxPlugPlayControl = 23
} PLUGPLAY_CONTROL_CLASS;

__kernel_entry
NTSTATUS
NTAPI
NtPlugPlayControl (
    _In_ PLUGPLAY_CONTROL_CLASS PnPControlClass,
    _Inout_updates_bytes_(PnPControlDataLength) PVOID PnPControlData,
    _In_ ULONG PnPControlDataLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSerializeBoot (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtOpenPartition (
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef int MEMORY_PARTITION_INFORMATION_CLASS;

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtManagePartition (
    _In_ MEMORY_PARTITION_INFORMATION_CLASS PartitionInformationClass,
    _In_ PVOID PartitionInformation,
    _In_ ULONG PartitionInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtRevertContainerImpersonation (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtCreatePartition (
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG PreferredNode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCompareObjects (
    _In_ HANDLE FirstObjectHandle,
    _In_ HANDLE SecondObjectHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtAdjustTokenClaimsAndDeviceGroups (
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN UserResetToDefault,
    _In_ BOOLEAN DeviceResetToDefault,
    _In_ BOOLEAN DeviceGroupsResetToDefault,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewUserState,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewDeviceState,
    _In_opt_ PTOKEN_GROUPS NewDeviceGroupsState,
    _In_ ULONG UserBufferLength,
    _Out_writes_bytes_to_opt_(UserBufferLength, *UserReturnLength)
        PTOKEN_SECURITY_ATTRIBUTES_INFORMATION  PreviousUserState,
    _In_ ULONG DeviceBufferLength,
    _Out_writes_bytes_to_opt_(DeviceBufferLength, *DeviceReturnLength)
        PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousDeviceState,
    _In_ ULONG DeviceGroupsBufferLength,
    _Out_writes_bytes_to_opt_(DeviceGroupsBufferLength, *DeviceGroupsReturnBufferLength)
        PTOKEN_GROUPS PreviousDeviceGroups,
    _Out_opt_ PULONG UserReturnLength,
    _Out_opt_ PULONG DeviceReturnLength,
    _Out_opt_ PULONG DeviceGroupsReturnBufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtFilterTokenEx (
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _In_ ULONG DisableUserClaimsCount,
    _In_opt_ PUNICODE_STRING UserClaimsToDisable,
    _In_ ULONG DisableDeviceClaimsCount,
    _In_opt_ PUNICODE_STRING DeviceClaimsToDisable,
    _In_opt_ PTOKEN_GROUPS DeviceGroupsToDisable,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedUserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedDeviceAttributes,
    _In_opt_ PTOKEN_GROUPS RestrictedDeviceGroups,
    _Out_ PHANDLE NewTokenHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetLdtEntries (
    _In_ ULONG Selector0,
    _In_ ULONG Entry0Low,
    _In_ ULONG Entry0Hi,
    _In_ ULONG Selector1,
    _In_ ULONG Entry1Low,
    _In_ ULONG Entry1Hi)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRegisterProtocolAddressInformation (
    _In_ HANDLE ResourceManager,
    _In_ PCRM_PROTOCOL_ID ProtocolId,
    _In_ ULONG ProtocolInformationSize,
    _In_ PVOID ProtocolInformation,
    _In_opt_ ULONG CreateOptions)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtNotifyChangeSession (
    _In_ HANDLE SessionHandle,
    _In_ ULONG ChangeSequenceNumber,
    _In_ PLARGE_INTEGER ChangeTimeStamp,
    _In_ IO_SESSION_EVENT Event,
    _In_ IO_SESSION_STATE NewState,
    _In_ IO_SESSION_STATE PreviousState,
    _In_reads_bytes_opt_(PayloadSize) PVOID Payload,
    _In_ ULONG PayloadSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryPortInformationProcess (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
