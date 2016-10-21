
#include <ntoskrnl.h>

typedef struct _DEVICE_OBJECT *PDEVICE_OBJECT;
typedef ULONG_PTR PFN_NUMBER;
typedef enum _CONFIGURATION_TYPE
{
    ArcSystem,
    CentralProcessor,
    FloatingPointProcessor,
    PrimaryIcache,
    PrimaryDcache,
    SecondaryIcache,
    SecondaryDcache,
    SecondaryCache,
    EisaAdapter,
    TcAdapter,
    ScsiAdapter,
    DtiAdapter,
    MultiFunctionAdapter,
    DiskController,
    TapeController,
    CdromController,
    WormController,
    SerialController,
    NetworkController,
    DisplayController,
    ParallelController,
    PointerController,
    KeyboardController,
    AudioController,
    OtherController,
    DiskPeripheral,
    FloppyDiskPeripheral,
    TapePeripheral,
    ModemPeripheral,
    MonitorPeripheral,
    PrinterPeripheral,
    PointerPeripheral,
    KeyboardPeripheral,
    TerminalPeripheral,
    OtherPeripheral,
    LinePeripheral,
    NetworkPeripheral,
    SystemMemory,
    DockingInformation,
    RealModeIrqRoutingTable,
    RealModePCIEnumeration,
    MaximumType
} CONFIGURATION_TYPE, *PCONFIGURATION_TYPE;

#include <arc/arc.h>
#include <ioaccess.h>

VOID FASTCALL ExAcquireFastMutexUnsafe(PVOID FastMutex);
NTSTATUS NTAPI NtQueryDebugFilterState(ULONG ComponentId, ULONG Level);
NTSTATUS NTAPI NtWaitForKeyedEvent(HANDLE Handle, PVOID Key, BOOLEAN Alertable, PLARGE_INTEGER Timeout);
BOOLEAN FASTCALL ExAcquireRundownProtection(PVOID RunRef);
VOID FASTCALL KeAcquireGuardedMutex(PVOID Mutex);
VOID FASTCALL KeAcquireInStackQueuedSpinLock(PVOID SpinLock, PVOID LockHandle);
VOID FASTCALL PoNotifyMediaBuffering(BOOLEAN Engaged);
#undef InterlockedDecrement
LONG FASTCALL InterlockedDecrement(LONG volatile *Addend);

/* Pull in some files */
PVOID pExAcquireFastMutexUnsafe = (PVOID)ExAcquireFastMutexUnsafe;
PVOID pExAcquireRundownProtection = (PVOID)ExAcquireRundownProtection;
PVOID pKeAcquireGuardedMutex = (PVOID)KeAcquireGuardedMutex;
PVOID pKeAcquireInStackQueuedSpinLock = (PVOID)KeAcquireInStackQueuedSpinLock;
PVOID pNtQueryDebugFilterState = (PVOID)NtQueryDebugFilterState;
PVOID pNtWaitForKeyedEvent = (PVOID)NtWaitForKeyedEvent;
PVOID pPoNotifyMediaBuffering = (PVOID)PoNotifyMediaBuffering;

PVOID pREAD_REGISTER_UCHAR = (PVOID)READ_REGISTER_UCHAR;
PVOID pREAD_REGISTER_USHORT = (PVOID)READ_REGISTER_USHORT;
PVOID pREAD_REGISTER_ULONG = (PVOID)READ_REGISTER_ULONG;
PVOID pREAD_REGISTER_BUFFER_UCHAR = (PVOID)READ_REGISTER_BUFFER_UCHAR;
PVOID pREAD_REGISTER_BUFFER_USHORT = (PVOID)READ_REGISTER_BUFFER_USHORT;
PVOID pREAD_REGISTER_BUFFER_ULONG = (PVOID)READ_REGISTER_BUFFER_ULONG;
PVOID pWRITE_REGISTER_UCHAR = (PVOID)WRITE_REGISTER_UCHAR;
PVOID pWRITE_REGISTER_USHORT = (PVOID)WRITE_REGISTER_USHORT;
PVOID pWRITE_REGISTER_ULONG = (PVOID)WRITE_REGISTER_ULONG;
PVOID pWRITE_REGISTER_BUFFER_UCHAR = (PVOID)WRITE_REGISTER_BUFFER_UCHAR;
PVOID pWRITE_REGISTER_BUFFER_USHORT = (PVOID)WRITE_REGISTER_BUFFER_USHORT;
PVOID pWRITE_REGISTER_BUFFER_ULONG = (PVOID)WRITE_REGISTER_BUFFER_ULONG;
PVOID pInterlockedDecrement = (PVOID)InterlockedDecrement;

typedef struct { PVOID p; } HAL_DISPATCH;

HAL_DISPATCH HalDispatchTable;
char HalPrivateDispatchTable;
BOOLEAN InitSafeBootMode;

errno_t
_strnset_s (
   char *str,
   size_t numberOfElements,
   int c,
   size_t count)
{
    __debugbreak();
    return -1;
}

errno_t
_strset_s (
   char *str,
   size_t numberOfElements,
   int c )
{
    __debugbreak();
    return -1;
}

errno_t
_wcslwr_s (
   wchar_t *str,
   size_t numberOfElements)
{
    __debugbreak();
    return -1;
}

errno_t
_wcsnset_s (
   wchar_t *str,
   size_t numberOfElements,
   wchar_t c,
   size_t count)
{
    __debugbreak();
    return -1;
}

errno_t
_wcsset_s (
   wchar_t *str,
   size_t numberOfElements,
   wchar_t c)
{
    __debugbreak();
    return -1;
}

errno_t
strcat_s (
   char *strDestination,
   size_t numberOfElements,
   const char *strSource)
{
    __debugbreak();
    return -1;
}

errno_t
strcpy_s (
   char *strDestination,
   size_t numberOfElements,
   const char *strSource)
{
    __debugbreak();
    return -1;
}

#undef ProbeForRead
_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ProbeForRead (
    __in_data_source(USER_MODE) _In_reads_bytes_(Length) const volatile VOID *Address,
    _In_ SIZE_T Length,
    _In_ ULONG Alignment)
{
    __debugbreak();
}

VOID
NTAPI
ProbeForWrite (
    __in_data_source(USER_MODE) _Inout_updates_bytes_(Length) volatile VOID *Address,
    _In_ SIZE_T Length,
    _In_ ULONG Alignment)
{
    __debugbreak();
}

// prototype from pHalExamineMBR
VOID
FASTCALL
HalExamineMBR (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG MBRTypeIdentifier,
    _Out_ PVOID *Buffer)
{
    __debugbreak();
}

VOID
NTAPI
RaiseException(IN ULONG dwExceptionCode,
    IN ULONG dwExceptionFlags,
    IN ULONG nNumberOfArguments,
    IN CONST ULONG_PTR *lpArguments OPTIONAL)
{
    __debugbreak();
}

NTSTATUS
NTAPI
LdrShutdownThread(
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// Process Hacker: ntlpcapi.h
NTSYSAPI
ULONG
NTAPI
AlpcGetHeaderSize (
    _In_ ULONG Flags);

// Process Hacker: ntlpcapi.h
NTSYSAPI 
PVOID
NTAPI
AlpcGetMessageAttribute (
    _In_ PALPC_MESSAGE_ATTRIBUTES Buffer,
    _In_ ULONG AttributeFlag)

// Process Hacker: ntlpcapi.h
NTSYSAPI
NTSTATUS
NTAPI
AlpcInitializeMessageAttribute (
    _In_ ULONG AttributeFlags,
    _Out_opt_ PALPC_MESSAGE_ATTRIBUTES Buffer,
    _In_ ULONG BufferSize,
    _Out_ PULONG RequiredBufferSize)

// reversed
NTSTATUS
NTAPI
CcTestControl()
{
    return STATUS_NOT_IMPLEMENTED;
}

// reversed
NTSTATUS
NTAPI
SkIsSecureKernel()
{
    return STATUS_NOT_IMPLEMENTED;
}

// reversed
NTSTATUS
NTAPI
CcZeroDataOnDisk (
    PFILE_OBJECT FileObject,
    PLARGE_INTEGER StartOffset,
    PLARGE_INTEGER EndOffset)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// mings def EtwWriteStartScenario@24
NTSTATUS
NTAPI
EtwWriteStartScenario (
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1)

// mings def EtwWriteEndScenario@24
NTSTATUS
NTAPI
EtwWriteEndScenario (
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1,
    ULONG_PTR P1)

// HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\TimeZoneInformation\RealTimeIsUniversal 
ULONG ExpRealTimeIsUniversalValue;

BOOLEAN
NTAPI
ExRealTimeIsUniversal (
    VOID)
{
    return ExpRealTimeIsUniversalValue != 0;
}

// mings def FsRtlRegisterMupCalls@4
NTSTATUS
NTAPI
FsRtlRegisterMupCalls (
    PVOID P1)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#if 0
@ stub Ntoskrnl_1 // PsCaptureUserProcessParameters@8
@ stub Ntoskrnl_2 // ZwCreateUserProcess@44 
@ stub Ntoskrnl_3 // ExAllocateTimerInternal@12
@ stub AlpcGetHeaderSize
@ stub AlpcGetMessageAttribute
@ stub AlpcInitializeMessageAttribute
@ stub BgkDisplayCharacter
@ stub BgkGetConsoleState
@ stub BgkGetCursorState
@ stub BgkSetCursor
@ stub CcTestControl
@ stub CcZeroDataOnDisk
@ stub EtwWriteEndScenario
@ stub EtwWriteStartScenario
@ fastcall -arch=i386,arm ExInterlockedAddLargeStatistic(ptr long)
@ stdcall -stub -arch=i386 ExInterlockedDecrementLong(ptr ptr)
@ stdcall -stub -arch=i386 ExInterlockedExchangeUlong(ptr long ptr)
@ stdcall -stub -arch=i386,arm ExInterlockedIncrementLong(ptr ptr)
@ stub ExRealTimeIsUniversal
@ stdcall -stub FsRtlNotifyReportChange(ptr ptr ptr ptr long)
@ stdcall -stub FsRtlPrepareMdlWrite(ptr ptr long long ptr ptr)
@ stub FsRtlRegisterMupCalls
@ stdcall -stub FsRtlSyncVolumes(long long long)
@ stdcall -stub HeadlessDispatch(long ptr long ptr ptr)
@ stub HvlGetLpIndexFromApicId
@ stub HvlPerformEndOfInterrupt
@ stub HvlQueryActiveHypervisorProcessorCount
@ stub HvlQueryActiveProcessors
@ stub HvlQueryConnection
@ stub HvlQueryHypervisorProcessorNodeNumber
@ stub HvlQueryNumaDistance
@ stub HvlQueryProcessorTopology
@ stub HvlQueryProcessorTopologyCount
@ stub HvlQueryProcessorTopologyHighestId
@ stub HvlReadPerformanceStateCounters
@ stub HvlRegisterInterruptCallback
@ stub HvlRegisterWheaErrorNotification
@ stub HvlUnregisterInterruptCallback
@ stub HvlUnregisterWheaErrorNotification
@ stub IoQueryInterface
@ fastcall -stub IoReadPartitionTable(ptr long long ptr)

NTSTATUS FASTCALL IoSetPartitionInformation(
  _In_ PDEVICE_OBJECT DeviceObject,
  _In_ ULONG          SectorSize,
  _In_ ULONG          PartitionNumber,
  _In_ ULONG          PartitionType
);

#@ fastcall IoWritePartitionTable(ptr long long long ptr)
NTSTATUS FASTCALL IoWritePartitionTable(
  _In_ PDEVICE_OBJECT                   DeviceObject,
  _In_ ULONG                            SectorSize,
  _In_ ULONG                            SectorsPerTrack,
  _In_ ULONG                            NumberOfHeads,
  _In_ struct _DRIVE_LAYOUT_INFORMATION *PartitionBuffer
);

@ stub KdAcquireDebuggerLock
@ stub KdDeregisterPowerHandler
@ stub KdEventLoggingEnabled
@ stub KdGetDebugDevice
@ stub KdLogDbgPrint
@ stub KdRegisterPowerHandler
@ stub KdReleaseDebuggerLock
@ stub KdSetEventLoggingPresent
@ stub KeCancelTimer2
@ stdcall -stub KeCapturePersistentThreadState(ptr long long long long long ptr)
@ stub KeClockInterruptNotify
@ stub KeClockTimerPowerChange
@ stdcall -stub KeEnterKernelDebugger()
@ stdcall -stub KeFindConfigurationEntry(ptr long long ptr)
@ stdcall -stub KeFindConfigurationNextEntry(ptr long long ptr ptr)
@ stdcall -stub KeFlushEntireTb(long long)
@ stub KeForceEnableNx
@ stub KeGetClockOwner
@ stub KeGetClockTimerResolution
@ stub KeGetNextClockTickDuration
@ stub KeGetXSaveFeatureFlags
@ stub KeHwPolicyLocateResource
@ stub KeInitializeEnumerationContextFromAffinity
@ stdcall -stub KeInitializeInterrupt(ptr ptr ptr ptr long long long long long long long)
@ stub KeInitializeTimer2
ULONG? KeLastBranchMSR
@ stub KeNotifyProcessorFreezeSupported
@ stub KePollFreezeExecution
@ cdecl -arch=x86_64 KeQueryPrcbAddress(long)
@ stdcall -stub KeRaiseUserException(long)
@ stdcall -stub KeSetAffinityThread(ptr long)
@ stdcall -stub KeSetDmaIoCoherency(long)
@ stdcall -stub KeSetProfileIrql(long)
@ stub KeSetSelectedCpuSetsThread
@ stub KeSetTimer2
@ stub KeSynchronizeTimeToQpc
@ stub KeSystemFullyCacheCoherent
@ stdcall -stub -arch=i386 Kei386EoiHelper()
@ stub KiAccumulateCycleStats
@ stub KiBeginThreadAccountingPeriod
@ stub KitLogFeatureUsage
@ stub -arch=i386,arm KiCheckForSListAddress
@ stdcall -stub -arch=i386 KiDispatchInterrupt()
@ stub KiEndThreadAccountingPeriod
@ stub KiEntropyQueueDpc
@ cdecl -stub -arch=i386,arm KiUnexpectedInterrupt()
@ stub KseQueryDeviceData
@ stub KseQueryDeviceDataList
@ stub KseQueryDeviceFlags
@ stub KseRegisterShim
@ stub KseRegisterShimEx
@ stub KseSetDeviceFlags
@ stub KseUnregisterShim
@ stub LdrResFindResource
@ stub LdrResFindResourceDirectory
@ stub LdrResSearchResource
@ stdcall -stub MmDisableModifiedWriteOfSection(long)
@ stub MmLoadSystemImage
@ stdcall -stub MmLockPagableImageSection(ptr)
@ stdcall -stub MmTrimAllSystemPagableMemory(long)
@ stub MmUnloadSystemImage
@ stdcall -stub NtGetEnvironmentVariableEx() ; FIXME
@ stdcall -stub NtQueryEnvironmentVariableInfoEx() ; FIXME
@ stub POGOBuffer
@ stub PfFileInfoNotify
@ stub PfxFindPrefix
@ stub PfxInitialize
@ stub PfxInsertPrefix
@ stub PfxRemovePrefix
@ stdcall -stub PoCancelDeviceNotify(ptr)
@ stub PoFxRegisterCoreDevice
@ stub PoFxRegisterPlugin
@ stub PoFxRegisterPluginEx
@ stub PoGetProcessorIdleAccounting
@ stub PoInitiateProcessorWake
@ stub PoRegisterCoalescingCallback
@ stdcall -stub PoRegisterDeviceNotify(ptr long long long ptr ptr)
@ stub PoRegisterPowerSettingCallback
@ stdcall -stub PoShutdownBugCheck(long long ptr ptr ptr ptr)
@ stub PoUnregisterCoalescingCallback
@ stub PoUnregisterPowerSettingCallback
@ stdcall -stub PsLookupProcessThreadByCid(ptr ptr ptr)
@ stub RtlEqualWnfChangeStamps
@ stub RtlGetAppContainerNamedObjectPath
@ stub RtlGetAppContainerParent
@ stub RtlGetAppContainerSidType
@ stdcall -stub SeAccessCheck(ptr ptr ptr long long ptr ptr long ptr ptr)
@ stub SeAccessCheckEx
@ stub SeAccessCheckFromState
@ stub SeAccessCheckFromStateEx
@ stub SeAccessCheckWithHint
@ stub SeAdjustAccessStateForTrustLabel
@ stdcall -stub SeAppendPrivileges(ptr ptr)
@ stdcall -stub SeAssignSecurity(ptr ptr ptr long ptr ptr ptr)
@ stdcall -stub SeAssignSecurityEx(ptr ptr ptr ptr long long ptr ptr ptr)
@ stdcall -stub SeAuditHardLinkCreation(ptr ptr long)
@ stub SeAuditHardLinkCreationWithTransaction
@ stub SeAuditTransactionStateChange
@ stub SeAuditingAnyFileEventsWithContext
@ stub SeAuditingAnyFileEventsWithContextEx
@ stdcall -stub SeAuditingFileEvents(long ptr)
@ stdcall -stub SeAuditingFileEventsWithContext(long ptr ptr)
@ stub SeAuditingFileEventsWithContextEx
@ stdcall -stub SeAuditingFileOrGlobalEvents(long ptr ptr)
@ stdcall -stub SeAuditingHardLinkEvents(long ptr)
@ stdcall -stub SeAuditingHardLinkEventsWithContext(long ptr ptr)
@ stub SeAuditingWithTokenForSubcategory
@ stdcall -stub SeCaptureSecurityDescriptor(ptr long long long ptr)
@ stdcall -stub SeCaptureSubjectContext(ptr)
@ stub SeCaptureSubjectContextEx
@ stdcall -stub SeCloseObjectAuditAlarm(ptr ptr long)
@ stub SeCloseObjectAuditAlarmForNonObObject
@ stub SeComputeAutoInheritByObjectType
@ stdcall -stub SeCreateAccessState(ptr ptr long ptr)
@ stub SeCreateAccessStateEx
@ stdcall -stub SeCreateClientSecurity(ptr ptr long ptr)
@ stub SeCreateClientSecurityEx
@ stdcall -stub SeCreateClientSecurityFromSubjectContext(ptr ptr long ptr)
@ stub SeCreateClientSecurityFromSubjectContextEx
@ stdcall -stub SeDeassignSecurity(ptr)
@ stdcall -stub SeDeleteAccessState(ptr)
@ stdcall -stub SeDeleteObjectAuditAlarm(ptr ptr)
@ stub SeDeleteObjectAuditAlarmWithTransaction
@ stub SeExamineSacl
@ stdcall -stub SeFilterToken(ptr long ptr ptr ptr ptr)
@ stdcall -stub SeFreePrivileges(ptr)
@ stub SeGetCachedSigningLevel
@ stub SeGetLinkedToken
@ stub SeGetLogonSessionToken
@ stdcall -stub SeImpersonateClient(ptr ptr)
@ stdcall -stub SeImpersonateClientEx(ptr ptr)
@ stub SeIsParentOfChildAppContainer
@ stub SeLocateProcessImageName
@ stdcall -stub SeLockSubjectContext(ptr)
@ stdcall -stub SeMarkLogonSessionForTerminationNotification(ptr)
@ stdcall -stub SeOpenObjectAuditAlarm(ptr ptr ptr ptr ptr long long long ptr)
@ stub SeOpenObjectAuditAlarmForNonObObject
@ stub SeOpenObjectAuditAlarmWithTransaction
@ stdcall -stub SeOpenObjectForDeleteAuditAlarm(ptr ptr ptr ptr ptr long long long ptr)
@ stub SeOpenObjectForDeleteAuditAlarmWithTransaction
@ stdcall -stub SePrivilegeCheck(ptr ptr long)
@ stdcall -stub SePrivilegeObjectAuditAlarm(ptr ptr long ptr long long)
@ stdcall -stub SeQueryAuthenticationIdToken(ptr ptr)
@ stdcall -stub SeQueryInformationToken(ptr long ptr)
@ stub SeQuerySecureBootPolicyValue
@ stub SeQuerySecurityAttributesToken
@ stdcall -stub SeQuerySecurityDescriptorInfo(ptr ptr ptr ptr)
@ stdcall -stub SeQuerySessionIdToken(ptr ptr)
@ stub SeRegisterImageVerificationCallback
@ stdcall -stub SeRegisterLogonSessionTerminatedRoutine(ptr)
@ stdcall -stub SeReleaseSecurityDescriptor(ptr long long)
@ stdcall -stub SeReleaseSubjectContext(ptr)
@ stdcall -stub SeReportSecurityEvent(long ptr ptr ptr)
@ stub SeReportSecurityEventWithSubCategory
@ stub SeSecurityAttributePresent
@ stdcall -stub SeSetAccessStateGenericMapping(ptr ptr)
@ stdcall -stub SeSetAuditParameter(ptr long long ptr)
@ stub SeSetSecurityAttributesToken
@ stdcall -stub SeSetSecurityDescriptorInfo(ptr ptr ptr ptr long ptr)
@ stdcall -stub SeSetSecurityDescriptorInfoEx(ptr ptr ptr ptr long long ptr)
@ stub SeShouldCheckForAccessRightsFromParent
@ stdcall -stub SeSinglePrivilegeCheck(long long long)
@ stub SeSrpAccessCheck
@ stub SeSystemDefaultSd
@ stub SeTokenFromAccessInformation
@ stdcall -stub SeTokenImpersonationLevel(ptr)
@ stdcall -stub SeTokenIsAdmin(ptr)
@ stdcall -stub SeTokenIsRestricted(ptr)
@ stdcall -stub SeTokenIsWriteRestricted(ptr)
@ stdcall -stub SeTokenType(ptr)
@ stdcall -stub SeUnlockSubjectContext(ptr)
@ stub SeUnregisterImageVerificationCallback
@ stdcall -stub SeUnregisterLogonSessionTerminatedRoutine(ptr)
@ stdcall -stub SeValidSecurityDescriptor(long ptr)
@ stub TmCancelPropagationRequest
@ stub TmCurrentTransaction
@ stub TmEndPropagationRequest
@ stub TmEnlistmentObjectType
@ stub TmFreezeTransactions
@ stub TmInitSystem
@ stub TmInitSystemPhase2
@ stub TmIsKTMCommitCoordinator
@ stub TmResourceManagerObjectType
@ stub TmSetCurrentTransaction
@ stub TmThawTransactions
@ stub TmTransactionManagerObjectType
@ stub TmTransactionObjectType
@ stub VmAccessFault
@ stub VmCreateMemoryRange
@ stub VmDeleteMemoryRange
@ stub WheaAddErrorSource
@ stub WheaAttemptPhysicalPageOffline
@ stub WheaConfigureErrorSource
@ stub WheaDeferredRecoveryService
@ stub WheaGetErrorSource
@ stub WheaInitializeDeferredRecoveryObject
@ stub WheaInitializeRecordHeader
@ stub WheaRegisterInUsePageOfflineNotification
@ stub WheaReportHwError
@ stub WheaRequestDeferredRecovery
@ stub WheaUnregisterInUsePageOfflineNotification
@ stub WmiGetClock
@ stub XIPDispatch

@ cdecl -stub -arch=x86_64 __misaligned_access()
@ cdecl -stub -arch=i386 _CIcos()
@ cdecl -stub -arch=i386 _CIsin()
@ cdecl -stub -arch=i386 _CIsqrt()
@ cdecl -stub -arch=i386 _alldiv()
@ cdecl -stub -arch=i386 _alldvrm()
@ cdecl -stub -arch=i386 _allmul()
@ cdecl -stub -arch=i386 _alloca_probe()
@ cdecl -stub -arch=i386 _alloca_probe_16()
@ cdecl -stub -arch=i386 _alloca_probe_8()
@ cdecl -stub -arch=i386 _allrem()
@ cdecl -stub -arch=i386 _allshl()
@ cdecl -stub -arch=i386 _allshr()
@ cdecl -stub -arch=i386 _aulldiv()
@ cdecl -stub -arch=i386 _aulldvrm()
@ cdecl -stub -arch=i386 _aullrem()
@ cdecl -stub -arch=i386 _aullshr()
@ cdecl -stub -arch=x86_64 _local_unwind()
@ stub _makepath_s
@ cdecl -stub _purecall()
@ stub _snprintf_s
@ stub _snscanf_s
@ stub _snwprintf_s
@ stub _snwscanf_s
@ stub _splitpath_s
@ stub _strtoui64
@ stub _swprintf
@ stub _ultoa_s
@ stub _ultow_s
@ stub _vsnprintf_s
@ stub _vsnwprintf_s
@ stub _vswprintf
@ stub _wmakepath_s
@ stub _wsplitpath_s
@ stub _wtoi
@ stub _wtol
@ stub bsearch
@ stub bsearch_s
@ stub memcpy_s
@ stub memmove_s
@ stub psMUITest
@ stub sprintf_s
@ cdecl -stub -arch=x86_64 sqrtf(double)
@ stub sscanf_s
@ stub strncat_s
@ stub strncpy_s
@ stub strtok_s
@ stub swprintf_s
@ stub swscanf_s
@ stub vsprintf_s
@ stub vswprintf_s
@ stub wcstoul
#endif
