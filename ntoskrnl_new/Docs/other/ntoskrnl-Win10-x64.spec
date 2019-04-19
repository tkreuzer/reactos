@ stub ntoskrnl_1
@ stub ntoskrnl_2
@ stub ntoskrnl_3
@ stub AlpcGetHeaderSize
@ stub AlpcGetMessageAttribute
@ stub AlpcInitializeMessageAttribute
@ stub BgkDisplayCharacter
@ stub BgkGetConsoleState
@ stub BgkGetCursorState
@ stub BgkSetCursor
@ stub CcAddDirtyPagesToExternalCache
@ stub CcAsyncCopyRead
@ stdcall CcCanIWrite(ptr long long long)
@ stub CcCoherencyFlushAndPurgeCache
@ stdcall CcCopyRead(ptr ptr long long ptr ptr)
@ stub CcCopyReadEx
@ stdcall CcCopyWrite(ptr ptr long long ptr)
@ stub CcCopyWriteEx
@ stub CcCopyWriteWontFlush
@ stub CcDeductDirtyPagesFromExternalCache
@ stdcall CcDeferWrite(ptr ptr ptr ptr long long)
@ stdcall CcFastCopyRead(ptr long long long ptr ptr)
@ stdcall CcFastCopyWrite(ptr long long ptr)
@ extern CcFastMdlReadWait
@ stdcall CcFlushCache(ptr ptr long ptr)
@ stub CcFlushCacheToLsn
@ stdcall CcGetDirtyPages(ptr ptr ptr ptr)
@ stdcall CcGetFileObjectFromBcb(ptr)
@ stdcall CcGetFileObjectFromSectionPtrs(ptr)
@ stub CcGetFileObjectFromSectionPtrsRef
@ stdcall CcGetFlushedValidData(ptr long)
@ stdcall CcGetLsnForFileObject(ptr ptr)
@ stdcall CcInitializeCacheMap(ptr ptr long ptr ptr)
@ stdcall CcIsThereDirtyData(ptr)
@ stub CcIsThereDirtyDataEx
@ stub CcIsThereDirtyLoggedPages
@ stdcall CcMapData(ptr ptr long long ptr ptr)
@ stdcall CcMdlRead(ptr ptr long ptr ptr)
@ stdcall CcMdlReadComplete(ptr ptr)
@ stdcall CcMdlWriteAbort(ptr ptr)
@ stdcall CcMdlWriteComplete(ptr ptr ptr)
@ stdcall CcPinMappedData(ptr ptr long long ptr)
@ stdcall CcPinRead(ptr ptr long long ptr ptr)
@ stdcall CcPrepareMdlWrite(ptr ptr long ptr ptr)
@ stdcall CcPreparePinWrite(ptr ptr long long long ptr ptr)
@ stdcall CcPurgeCacheSection(ptr ptr long long)
@ stub CcRegisterExternalCache
@ stdcall CcRemapBcb(ptr)
@ stdcall CcRepinBcb(ptr)
@ stdcall CcScheduleReadAhead(ptr ptr long)
@ stub CcScheduleReadAheadEx
@ stdcall CcSetAdditionalCacheAttributes(ptr long long)
@ stub CcSetAdditionalCacheAttributesEx
@ stdcall CcSetBcbOwnerPointer(ptr ptr)
@ stdcall CcSetDirtyPageThreshold(ptr long)
@ stdcall CcSetDirtyPinnedData(ptr ptr)
@ stdcall CcSetFileSizes(ptr ptr)
@ stub CcSetFileSizesEx
@ stdcall CcSetLogHandleForFile(ptr ptr ptr)
@ stub CcSetLogHandleForFileEx
@ stub CcSetLoggedDataThreshold
@ stub CcSetParallelFlushFile
@ stdcall CcSetReadAheadGranularity(ptr long)
@ stub CcSetReadAheadGranularityEx
@ stub CcTestControl
@ stdcall CcUninitializeCacheMap(ptr ptr ptr)
@ stub CcUnmapFileOffsetFromSystemCache
@ stdcall CcUnpinData(ptr)
@ stdcall CcUnpinDataForThread(ptr ptr)
@ stdcall CcUnpinRepinnedBcb(ptr long ptr)
CcUnregisterExternalCache
@ stdcall CcWaitForCurrentLazyWriterActivity()
@ stdcall CcZeroData(ptr ptr ptr long)
CcZeroDataOnDisk
CmCallbackGetKeyObjectID
CmCallbackGetKeyObjectIDEx
CmCallbackReleaseKeyObjectIDEx
CmGetBoundTransaction
CmGetCallbackVersion
CmKeyObjectType
@ stdcall CmRegisterCallback(ptr ptr ptr)
CmRegisterCallbackEx
CmSetCallbackObjectContext
@ stdcall CmUnRegisterCallback(long long)
@ stdcall DbgBreakPoint()
@ stdcall DbgBreakPointWithStatus(long)
@ stdcall DbgCommandString(ptr ptr)
@ stdcall DbgLoadImageSymbols(ptr ptr long)
@ cdecl DbgPrint(str)
@ cdecl DbgPrintEx(long long str)
@ cdecl DbgPrintReturnControlC(str)
@ stdcall DbgPrompt(str ptr long)
@ stdcall DbgQueryDebugFilterState(long long)
@ stdcall DbgSetDebugFilterState(long long long)
DbgSetDebugPrintCallback
DbgkLkmdRegisterCallback
DbgkLkmdUnregisterCallback
DbgkWerCaptureLiveKernelDump
EmClientQueryRuleState
EmClientRuleDeregisterNotification
EmClientRuleEvaluate
EmClientRuleRegisterNotification
EmProviderDeregister
EmProviderDeregisterEntry
EmProviderRegister
EmProviderRegisterEntry
EmpProviderRegister
EtwActivityIdControl
EtwEnableTrace
EtwEventEnabled
EtwProviderEnabled
EtwRegister
EtwRegisterClassicProvider
EtwSendTraceBuffer
EtwSetInformation
EtwUnregister
EtwWrite
EtwWriteEndScenario
EtwWriteEx
EtwWriteStartScenario
EtwWriteString
EtwWriteTransfer
ExAcquireAutoExpandPushLockExclusive
ExAcquireAutoExpandPushLockShared
ExAcquireCacheAwarePushLockExclusive
ExAcquireCacheAwarePushLockExclusiveEx
ExAcquireCacheAwarePushLockSharedEx
@ stdcall -arch=x86_64 ExAcquireFastMutex(ptr)
@ fastcall ExAcquireFastMutexUnsafe(ptr)
@ stub ExAcquirePushLockExclusiveEx
@ stub ExAcquirePushLockSharedEx
@ stdcall ExAcquireResourceExclusiveLite(ptr long)
@ stdcall ExAcquireResourceSharedLite(ptr long)
@ fastcall ExAcquireRundownProtection(ptr) ExfAcquireRundownProtection
@ fastcall ExAcquireRundownProtectionCacheAware(ptr) ExfAcquireRundownProtectionCacheAware
@ fastcall ExAcquireRundownProtectionCacheAwareEx(ptr long) ExfAcquireRundownProtectionCacheAwareEx
@ fastcall ExAcquireRundownProtectionEx(ptr long) ExfAcquireRundownProtectionEx
@ stdcall ExAcquireSharedStarveExclusive(ptr long)
@ stdcall ExAcquireSharedWaitForExclusive(ptr long)
ExAcquireSpinLockExclusive
ExAcquireSpinLockExclusiveAtDpcLevel
ExAcquireSpinLockShared
ExAcquireSpinLockSharedAtDpcLevel
ExAllocateAutoExpandPushLock
ExAllocateCacheAwarePushLock
@ stdcall ExAllocateCacheAwareRundownProtection(long long)
@ stdcall ExAllocatePool(long long)
@ stdcall ExAllocatePoolWithQuota(long long)
@ stdcall ExAllocatePoolWithQuotaTag(long long long)
@ stdcall ExAllocatePoolWithTag(long long long)
@ stdcall ExAllocatePoolWithTagPriority(long long long long)
ExAllocateTimer
ExBlockOnAddressPushLock
ExBlockPushLock
ExCancelTimer
ExCleanupAutoExpandPushLock
ExCleanupRundownProtectionCacheAware
ExCompositionObjectType
@ stdcall ExConvertExclusiveToSharedLite(ptr)
@ stdcall ExCreateCallback(ptr ptr long long)
ExDeleteLookasideListEx
@ stdcall ExDeleteNPagedLookasideList(ptr)
@ stdcall ExDeletePagedLookasideList(ptr)
@ stdcall ExDeleteResourceLite(ptr)
ExDeleteTimer
@ extern ExDesktopObjectType
@ stdcall ExDisableResourceBoostLite(ptr)
@ fastcall ExEnterCriticalRegionAndAcquireFastMutexUnsafe(ptr)
@ stdcall ExEnterCriticalRegionAndAcquireResourceExclusive(ptr)
@ stdcall ExEnterCriticalRegionAndAcquireResourceShared(ptr)
@ stdcall ExEnterCriticalRegionAndAcquireSharedWaitForExclusive(ptr)
ExEnterPriorityRegionAndAcquireResourceExclusive
ExEnterPriorityRegionAndAcquireResourceShared
@ stdcall ExEnumHandleTable(ptr ptr ptr ptr)
@ extern ExEventObjectType
@ stdcall ExExtendZone(ptr ptr long)
ExFetchLicenseData
ExFlushLookasideListEx
ExFreeAutoExpandPushLock
ExFreeCacheAwarePushLock
@ stdcall ExFreeCacheAwareRundownProtection(ptr)
@ stdcall ExFreePool(ptr)
@ stdcall ExFreePoolWithTag(ptr long)
@ stdcall ExGetCurrentProcessorCounts(ptr ptr ptr)
@ stdcall ExGetCurrentProcessorCpuUsage(ptr)
@ stdcall ExGetExclusiveWaiterCount(ptr)
ExGetFirmwareEnvironmentVariable
ExGetLicenseTamperState
@ stdcall ExGetPreviousMode()
@ stdcall ExGetSharedWaiterCount(ptr)
@ stub ExInitializeAutoExpandPushLock
@ stub ExInitializeLookasideListEx
@ stdcall ExInitializeNPagedLookasideList(ptr ptr ptr long long long long)
@ stdcall ExInitializePagedLookasideList(ptr ptr ptr long long long long)
@ stub ExInitializePushLock
@ stdcall ExInitializeResourceLite(ptr)
@ fastcall ExInitializeRundownProtection(ptr) ExfInitializeRundownProtection
@ stdcall ExInitializeRundownProtectionCacheAware(ptr long)
ExInitializeRundownProtectionCacheAwareEx
@ stdcall ExInitializeZone(ptr long ptr long)
@ stdcall ExInterlockedAddLargeInteger(ptr long long ptr)
@ stdcall ExInterlockedAddUlong(ptr long ptr)
@ stdcall ExInterlockedExtendZone(ptr ptr long ptr)
@ stdcall ExInterlockedInsertHeadList(ptr ptr ptr)
@ stdcall ExInterlockedInsertTailList(ptr ptr ptr)
@ stdcall ExInterlockedPopEntryList(ptr ptr)
@ stdcall ExInterlockedPushEntryList(ptr ptr ptr)
@ stdcall ExInterlockedRemoveHeadList(ptr ptr)
@ stub ExIsManufacturingModeEnabled
@ stdcall ExIsProcessorFeaturePresent(long)
@ stdcall ExIsResourceAcquiredExclusiveLite(ptr)
@ stdcall ExIsResourceAcquiredSharedLite(ptr)
@ stdcall ExLocalTimeToSystemTime(ptr ptr)
@ stub ExNotifyBootDeviceRemoval
@ stdcall ExNotifyCallback(ptr ptr ptr)
@ stdcall -arch=x86_64 ExQueryDepthSList(ptr)
@ stub ExQueryFastCacheAppOrigin
@ stub ExQueryFastCacheDevLicense
@ stdcall ExQueryPoolBlockSize(ptr ptr)
@ stub ExQueryTimerResolution
@ stub ExQueryWnfStateData
@ stdcall ExQueueWorkItem(ptr long)
@ stdcall ExRaiseAccessViolation()
@ stdcall ExRaiseDatatypeMisalignment()
@ stdcall ExRaiseException(ptr) RtlRaiseException
@ stdcall ExRaiseHardError(long long long ptr long ptr)
@ stdcall ExRaiseStatus(long) RtlRaiseStatus
@ stub ExRawInputManagerObjectType
@ fastcall ExReInitializeRundownProtection(ptr) ExfReInitializeRundownProtection
@ fastcall ExReInitializeRundownProtectionCacheAware(ptr) ExfReInitializeRundownProtectionCacheAware
@ stub ExRealTimeIsUniversal
@ stub ExRegisterBootDevice
@ stdcall ExRegisterCallback(ptr ptr ptr)
@ stub ExRegisterExtension
@ stdcall ExReinitializeResourceLite(ptr)
@ stub ExReleaseAutoExpandPushLockExclusive
@ stub ExReleaseAutoExpandPushLockShared
@ stub ExReleaseCacheAwarePushLockExclusive
@ stub ExReleaseCacheAwarePushLockExclusiveEx
@ stub ExReleaseCacheAwarePushLockSharedEx
@ stdcall -arch=x86_64 ExReleaseFastMutex(ptr)
@ fastcall ExReleaseFastMutexUnsafe(ptr)
@ fastcall ExReleaseFastMutexUnsafeAndLeaveCriticalRegion(ptr)
@ stub ExReleasePushLockEx
@ stub ExReleasePushLockExclusiveEx
@ stub ExReleasePushLockSharedEx
@ fastcall ExReleaseResourceAndLeaveCriticalRegion(ptr)
@ stub ExReleaseResourceAndLeavePriorityRegion
@ stdcall ExReleaseResourceForThreadLite(ptr long)
@ fastcall ExReleaseResourceLite(ptr)
@ fastcall ExReleaseRundownProtection(ptr) ExfReleaseRundownProtection
@ fastcall ExReleaseRundownProtectionCacheAware(ptr) ExfReleaseRundownProtectionCacheAware
@ fastcall ExReleaseRundownProtectionCacheAwareEx(ptr long) ExfReleaseRundownProtectionCacheAwareEx
@ fastcall ExReleaseRundownProtectionEx(ptr long) ExfReleaseRundownProtectionEx
@ stub ExReleaseSpinLockExclusive
@ stub ExReleaseSpinLockExclusiveFromDpcLevel
@ stub ExReleaseSpinLockShared
@ stub ExReleaseSpinLockSharedFromDpcLevel
@ fastcall ExRundownCompleted(ptr) ExfRundownCompleted
@ fastcall ExRundownCompletedCacheAware(ptr) ExfRundownCompletedCacheAware
@ extern ExSemaphoreObjectType
@ stub ExSetFirmwareEnvironmentVariable
@ stub ExSetLicenseTamperState
@ stdcall ExSetResourceOwnerPointer(ptr ptr)
@ stub ExSetResourceOwnerPointerEx
@ stub ExSetTimer
@ stdcall ExSetTimerResolution(long long)
ExSizeOfAutoExpandPushLock
@ stdcall ExSizeOfRundownProtectionCacheAware()
ExSubscribeWnfStateChange
@ stdcall ExSystemExceptionFilter()
@ stdcall ExSystemTimeToLocalTime(ptr ptr)
ExTimedWaitForUnblockPushLock
ExTimerObjectType
ExTryAcquireAutoExpandPushLockExclusive
ExTryAcquireAutoExpandPushLockShared
ExTryAcquireCacheAwarePushLockExclusiveEx
ExTryAcquireCacheAwarePushLockSharedEx
ExTryAcquirePushLockExclusiveEx
ExTryAcquirePushLockSharedEx
ExTryConvertPushLockSharedToExclusiveEx
ExTryConvertSharedSpinLockExclusive
ExTryQueueWorkItem
@ stdcall -arch=x86_64 ExTryToAcquireFastMutex(ptr)
ExTryToAcquireResourceExclusiveLite
ExUnblockOnAddressPushLockEx
ExUnblockPushLockEx
@ stdcall ExUnregisterCallback(ptr)
ExUnregisterExtension
ExUnsubscribeWnfStateChange
@ stdcall ExUuidCreate(ptr)
@ stdcall ExVerifySuite(long)
@ fastcall ExWaitForRundownProtectionRelease(ptr) ExfWaitForRundownProtectionRelease
@ fastcall ExWaitForRundownProtectionReleaseCacheAware(ptr) ExfWaitForRundownProtectionReleaseCacheAware
ExWaitForUnblockPushLock
@ extern ExWindowStationObjectType
@ fastcall ExfAcquirePushLockExclusive(ptr)
@ fastcall ExfAcquirePushLockShared(ptr)
@ fastcall ExfReleasePushLock(ptr)
@ fastcall ExfReleasePushLockExclusive(ptr)
@ fastcall ExfReleasePushLockShared(ptr)
ExfTryAcquirePushLockShared
@ fastcall ExfTryToWakePushLock(ptr)
@ fastcall ExfUnblockPushLock(ptr ptr)
@ stdcall -arch=x86_64 ExpInterlockedFlushSList(ptr)
@ stdcall -arch=x86_64 ExpInterlockedPopEntrySList(ptr ptr)
@ stdcall -arch=x86_64 ExpInterlockedPushEntrySList(ptr ptr)
FirstEntrySList
FsRtlAcknowledgeEcp
FsRtlAcquireEofLock
@ stdcall FsRtlAcquireFileExclusive(ptr)
FsRtlAcquireHeaderMutex
@ stdcall FsRtlAddBaseMcbEntry(ptr long long long long long long)
FsRtlAddBaseMcbEntryEx
@ stdcall FsRtlAddLargeMcbEntry(ptr long long long long long long)
@ stdcall FsRtlAddMcbEntry(ptr long long long)
@ stdcall FsRtlAddToTunnelCache(ptr long long ptr ptr long long ptr)
FsRtlAllocateExtraCreateParameter
FsRtlAllocateExtraCreateParameterFromLookasideList
FsRtlAllocateExtraCreateParameterList
@ stdcall FsRtlAllocateFileLock(ptr ptr)
@ stdcall FsRtlAllocatePool(long long)
@ stdcall FsRtlAllocatePoolWithQuota(long long)
@ stdcall FsRtlAllocatePoolWithQuotaTag(long long long)
@ stdcall FsRtlAllocatePoolWithTag(long long long)
@ stdcall FsRtlAllocateResource()
@ stdcall FsRtlAreNamesEqual(ptr ptr long wstr)
FsRtlAreThereCurrentOrInProgressFileLocks
FsRtlAreThereWaitingFileLocks
FsRtlAreVolumeStartupApplicationsComplete
@ stdcall FsRtlBalanceReads(ptr)
FsRtlCancellableWaitForMultipleObjects
FsRtlCancellableWaitForSingleObject
FsRtlChangeBackingFileObject
FsRtlCheckLockForOplockRequest
@ stdcall FsRtlCheckLockForReadAccess(ptr ptr)
@ stdcall FsRtlCheckLockForWriteAccess(ptr ptr)
@ stdcall FsRtlCheckOplock(ptr ptr ptr ptr ptr)
FsRtlCheckOplockEx
FsRtlCheckUpperOplock
@ stdcall FsRtlCopyRead(ptr ptr long long long ptr ptr ptr)
@ stdcall FsRtlCopyWrite(ptr ptr long long long ptr ptr ptr)
@ stdcall FsRtlCreateSectionForDataScan(ptr ptr ptr ptr long ptr ptr long long long)
@ stdcall FsRtlCurrentBatchOplock(ptr)
FsRtlCurrentOplock
FsRtlCurrentOplockH
FsRtlDeleteExtraCreateParameterLookasideList
@ stdcall FsRtlDeleteKeyFromTunnelCache(ptr long long)
@ stdcall FsRtlDeleteTunnelCache(ptr)
@ stdcall FsRtlDeregisterUncProvider(ptr)
FsRtlDismountComplete
@ stdcall FsRtlDissectDbcs(long ptr ptr ptr)
@ stdcall FsRtlDissectName(long ptr ptr ptr)
@ stdcall FsRtlDoesDbcsContainWildCards(ptr)
@ stdcall FsRtlDoesNameContainWildCards(ptr)
@ stdcall FsRtlFastCheckLockForRead(ptr ptr ptr long ptr ptr)
@ stdcall FsRtlFastCheckLockForWrite(ptr ptr ptr long ptr ptr)
@ stdcall FsRtlFastUnlockAll(ptr ptr ptr ptr)
@ stdcall FsRtlFastUnlockAllByKey(ptr ptr ptr long ptr)
@ stdcall FsRtlFastUnlockSingle(ptr ptr ptr ptr ptr long ptr long)
FsRtlFindExtraCreateParameter
@ stdcall FsRtlFindInTunnelCache(ptr long long ptr ptr ptr ptr ptr)
FsRtlFreeExtraCreateParameter
FsRtlFreeExtraCreateParameterList
@ stdcall FsRtlFreeFileLock(ptr)
FsRtlGetEcpListFromIrp
FsRtlGetFileNameInformation
@ stdcall FsRtlGetFileSize(ptr ptr)
FsRtlGetIoAtEof
@ stdcall FsRtlGetNextBaseMcbEntry(ptr long ptr ptr ptr)
FsRtlGetNextExtraCreateParameter
@ stdcall FsRtlGetNextFileLock(ptr long)
@ stdcall FsRtlGetNextLargeMcbEntry(ptr long ptr ptr ptr)
@ stdcall FsRtlGetNextMcbEntry(ptr long ptr ptr ptr)
FsRtlGetSectorSizeInformation
FsRtlGetSupportedFeatures
FsRtlGetVirtualDiskNestingLevel
FsRtlHeatInit
FsRtlHeatLogIo
FsRtlHeatLogTierMove
FsRtlHeatUninit
FsRtlIncrementCcFastMdlReadWait
@ stdcall FsRtlIncrementCcFastReadNoWait()
@ stdcall FsRtlIncrementCcFastReadNotPossible()
@ stdcall FsRtlIncrementCcFastReadResourceMiss()
@ stdcall FsRtlIncrementCcFastReadWait()
FsRtlInitExtraCreateParameterLookasideList
@ stdcall FsRtlInitializeBaseMcb(ptr ptr)
FsRtlInitializeBaseMcbEx
FsRtlInitializeEofLock
FsRtlInitializeExtraCreateParameter
FsRtlInitializeExtraCreateParameterList
@ stdcall FsRtlInitializeFileLock(ptr ptr ptr)
@ stdcall FsRtlInitializeLargeMcb(ptr long)
@ stdcall FsRtlInitializeMcb(ptr long)
@ stdcall FsRtlInitializeOplock(ptr)
@ stdcall FsRtlInitializeTunnelCache(ptr)
FsRtlInsertExtraCreateParameter
FsRtlInsertPerFileContext
@ stdcall FsRtlInsertPerFileObjectContext(ptr ptr)
@ stdcall FsRtlInsertPerStreamContext(ptr ptr)
FsRtlInsertReservedPerFileContext
FsRtlInsertReservedPerStreamContext
@ stdcall FsRtlIsDbcsInExpression(ptr ptr)
FsRtlIsEcpAcknowledged
FsRtlIsEcpFromUserMode
@ stdcall FsRtlIsFatDbcsLegal(long ptr long long long)
@ stdcall FsRtlIsHpfsDbcsLegal(long ptr long long long)
@ stdcall FsRtlIsNameInExpression(ptr ptr long wstr)
@ stdcall FsRtlIsNtstatusExpected(long)
@ stdcall FsRtlIsPagingFile(ptr)
FsRtlIsSystemPagingFile
@ stdcall FsRtlIsTotalDeviceFailure(ptr)
FsRtlIssueDeviceIoControl
FsRtlKernelFsControlFile
@ extern FsRtlLegalAnsiCharacterArray
FsRtlLogCcFlushError
@ stdcall FsRtlLookupBaseMcbEntry(ptr long long ptr ptr ptr ptr ptr)
@ stdcall FsRtlLookupLargeMcbEntry(ptr long long ptr ptr ptr ptr ptr)
@ stdcall FsRtlLookupLastBaseMcbEntry(ptr ptr ptr)
@ stdcall FsRtlLookupLastBaseMcbEntryAndIndex(ptr ptr ptr ptr)
@ stdcall FsRtlLookupLastLargeMcbEntry(ptr ptr ptr)
@ stdcall FsRtlLookupLastLargeMcbEntryAndIndex(ptr ptr ptr ptr)
@ stdcall FsRtlLookupLastMcbEntry(ptr ptr ptr)
@ stdcall FsRtlLookupMcbEntry(ptr long ptr ptr ptr)
FsRtlLookupPerFileContext
@ stdcall FsRtlLookupPerFileObjectContext(ptr ptr ptr)
@ stdcall FsRtlLookupPerStreamContextInternal(ptr ptr ptr)
FsRtlLookupReservedPerFileContext
FsRtlLookupReservedPerStreamContext
@ stdcall FsRtlMdlRead(ptr ptr long long ptr ptr)
@ stdcall FsRtlMdlReadComplete(ptr ptr)
@ stdcall FsRtlMdlReadCompleteDev(ptr ptr ptr)
@ stdcall FsRtlMdlReadDev(ptr ptr long long ptr ptr ptr)
FsRtlMdlReadEx
@ stdcall FsRtlMdlWriteComplete(ptr ptr ptr)
@ stdcall FsRtlMdlWriteCompleteDev(ptr ptr ptr ptr)
FsRtlMupGetProviderIdFromName
FsRtlMupGetProviderInfoFromFileObject
@ stdcall FsRtlNormalizeNtstatus(long long)
@ stdcall FsRtlNotifyChangeDirectory(ptr ptr ptr ptr long long ptr)
@ stdcall FsRtlNotifyCleanup(ptr ptr ptr)
FsRtlNotifyCleanupAll
@ stdcall FsRtlNotifyFilterChangeDirectory(ptr ptr ptr ptr long long long ptr ptr ptr ptr)
FsRtlNotifyFilterChangeDirectoryLite
@ stdcall FsRtlNotifyFilterReportChange(ptr ptr ptr long ptr ptr long long ptr ptr)
FsRtlNotifyFilterReportChangeLite
@ stdcall FsRtlNotifyFullChangeDirectory(ptr ptr ptr ptr long long long ptr ptr ptr)
@ stdcall FsRtlNotifyFullReportChange(ptr ptr ptr long ptr ptr long long ptr)
@ stdcall FsRtlNotifyInitializeSync(ptr)
@ stdcall FsRtlNotifyReportChange(ptr ptr ptr ptr long)
@ stdcall FsRtlNotifyUninitializeSync(ptr)
@ stdcall FsRtlNotifyVolumeEvent(ptr long)
FsRtlNotifyVolumeEventEx
@ stdcall FsRtlNumberOfRunsInBaseMcb(ptr)
@ stdcall FsRtlNumberOfRunsInLargeMcb(ptr)
@ stdcall FsRtlNumberOfRunsInMcb(ptr)
FsRtlOplockBreakH
FsRtlOplockBreakToNone
FsRtlOplockBreakToNoneEx
@ stdcall FsRtlOplockFsctrl(ptr ptr long)
FsRtlOplockFsctrlEx
@ stdcall FsRtlOplockIsFastIoPossible(ptr)
FsRtlOplockIsSharedRequest
FsRtlOplockKeysEqual
@ stdcall FsRtlPostPagingFileStackOverflow(ptr ptr ptr)
@ stdcall FsRtlPostStackOverflow(ptr ptr ptr)
@ stdcall FsRtlPrepareMdlWrite(ptr ptr long long ptr ptr)
@ stdcall FsRtlPrepareMdlWriteDev(ptr ptr long long ptr ptr ptr)
FsRtlPrepareMdlWriteEx
FsRtlPrepareToReuseEcp
@ stdcall FsRtlPrivateLock(ptr ptr ptr ptr ptr long long long ptr ptr ptr long)
@ stdcall FsRtlProcessFileLock(ptr ptr ptr)
FsRtlQueryCachedVdl
FsRtlQueryKernelEaFile
FsRtlQueryMaximumVirtualDiskNestingLevel
@ stdcall FsRtlRegisterFileSystemFilterCallbacks(ptr ptr)
FsRtlRegisterFltMgrCalls
FsRtlRegisterMupCalls
@ stdcall FsRtlRegisterUncProvider(ptr ptr long)
FsRtlRegisterUncProviderEx
FsRtlReleaseEofLock
@ stdcall FsRtlReleaseFile(ptr)
FsRtlReleaseFileNameInformation
FsRtlReleaseHeaderMutex
@ stdcall FsRtlRemoveBaseMcbEntry(ptr long long long long)
FsRtlRemoveDotsFromPath
FsRtlRemoveExtraCreateParameter
@ stdcall FsRtlRemoveLargeMcbEntry(ptr long long long long)
@ stdcall FsRtlRemoveMcbEntry(ptr long long)
FsRtlRemovePerFileContext
@ stdcall FsRtlRemovePerFileObjectContext(ptr ptr ptr)
@ stdcall FsRtlRemovePerStreamContext(ptr ptr ptr)
FsRtlRemoveReservedPerFileContext
FsRtlRemoveReservedPerStreamContext
@ stdcall FsRtlResetBaseMcb(ptr)
@ stdcall FsRtlResetLargeMcb(ptr long)
FsRtlSendModernAppTermination
FsRtlSetDriverBacking
FsRtlSetEcpListIntoIrp
FsRtlSetKernelEaFile
@ stdcall FsRtlSplitBaseMcb(ptr long long long long)
@ stdcall FsRtlSplitLargeMcb(ptr long long long long)
@ stdcall FsRtlSyncVolumes(long long long)
FsRtlTeardownPerFileContexts
@ stdcall FsRtlTeardownPerStreamContexts(ptr)
@ stdcall FsRtlTruncateBaseMcb(ptr long long)
@ stdcall FsRtlTruncateLargeMcb(ptr long long)
@ stdcall FsRtlTruncateMcb(ptr long)
FsRtlTryToAcquireHeaderMutex
@ stdcall FsRtlUninitializeBaseMcb(ptr)
@ stdcall FsRtlUninitializeFileLock(ptr)
@ stdcall FsRtlUninitializeLargeMcb(ptr)
@ stdcall FsRtlUninitializeMcb(ptr)
@ stdcall FsRtlUninitializeOplock(ptr)
FsRtlUpdateDiskCounters
FsRtlUpperOplockFsctrl
FsRtlValidateReparsePointBuffer
@ extern HalDispatchTable
@ fastcall HalExamineMBR(ptr long long ptr)
@ extern HalPrivateDispatchTable
@ stdcall HeadlessDispatch(long ptr long ptr ptr)
HvlGetLpIndexFromApicId
HvlPerformEndOfInterrupt
HvlQueryActiveHypervisorProcessorCount
HvlQueryActiveProcessors
HvlQueryConnection
HvlQueryHypervisorProcessorNodeNumber
HvlQueryNumaDistance
HvlQueryProcessorTopology
HvlQueryProcessorTopologyCount
HvlQueryProcessorTopologyHighestId
HvlReadPerformanceStateCounters
HvlRegisterInterruptCallback
HvlRegisterWheaErrorNotification
HvlUnregisterInterruptCallback
HvlUnregisterWheaErrorNotification
@ stdcall InbvAcquireDisplayOwnership()
@ stdcall InbvCheckDisplayOwnership()
@ stdcall InbvDisplayString(str)
@ stdcall InbvEnableBootDriver(long)
@ stdcall InbvEnableDisplayString(long)
@ stdcall InbvInstallDisplayStringFilter(ptr)
@ stdcall InbvIsBootDriverInstalled()
InbvNotifyDisplayOwnershipChange
@ stdcall InbvNotifyDisplayOwnershipLost(ptr)
@ stdcall InbvResetDisplay()
@ stdcall InbvSetScrollRegion(long long long long)
@ stdcall InbvSetTextColor(long)
@ stdcall InbvSolidColorFill(long long long long long)
@ extern InitSafeBootMode
@ stdcall -arch=x86_64 InitializeSListHead(ptr) RtlInitializeSListHead
@ stub InterlockedPushListSList
@ stdcall IoAcquireCancelSpinLock(ptr)
@ stdcall IoAcquireRemoveLockEx(ptr ptr str long long)
@ stdcall IoAcquireVpbSpinLock(ptr)
@ extern IoAdapterObjectType
@ stub IoAdjustStackSizeForRedirection
@ stdcall IoAllocateAdapterChannel(ptr ptr long ptr ptr)
@ stdcall IoAllocateController(ptr ptr ptr ptr)
@ stdcall IoAllocateDriverObjectExtension(ptr ptr long ptr)
@ stdcall IoAllocateErrorLogEntry(ptr long)
@ stdcall IoAllocateIrp(long long)
@ stdcall IoAllocateMdl(ptr long long long ptr)
@ stub IoAllocateMiniCompletionPacket
@ stub IoAllocateSfioStreamIdentifier
@ stdcall IoAllocateWorkItem(ptr)
@ stub IoApplyPriorityInfoThread
@ stdcall IoAssignResources(ptr ptr ptr ptr ptr ptr)
@ stdcall IoAttachDevice(ptr ptr ptr)
@ stdcall IoAttachDeviceByPointer(ptr ptr)
@ stdcall IoAttachDeviceToDeviceStack(ptr ptr)
@ stdcall IoAttachDeviceToDeviceStackSafe(ptr ptr ptr)
@ stub IoBoostThreadIo
@ stdcall IoBuildAsynchronousFsdRequest(long ptr ptr long ptr ptr)
@ stdcall IoBuildDeviceIoControlRequest(long ptr ptr long ptr long long ptr ptr)
@ stdcall IoBuildPartialMdl(ptr ptr ptr long)
@ stdcall IoBuildSynchronousFsdRequest(long ptr ptr long ptr ptr ptr)
@ stdcall IoCallDriver(ptr ptr)
@ stdcall IoCancelFileOpen(ptr ptr)
@ stdcall IoCancelIrp(ptr)
@ stdcall IoCheckDesiredAccess(ptr long)
@ stdcall IoCheckEaBufferValidity(ptr long ptr)
@ stdcall IoCheckFunctionAccess(long long long long ptr ptr)
@ stdcall IoCheckQuerySetFileInformation(long long long)
@ stdcall IoCheckQuerySetVolumeInformation(long long long)
@ stdcall IoCheckQuotaBufferValidity(ptr long ptr)
@ stdcall IoCheckShareAccess(long long ptr ptr long)
@ stub IoCheckShareAccessEx
@ stub IoClearActivityIdThread
@ stub IoClearDependency
@ stub IoClearIrpExtraCreateParameter
@ stdcall IoCompleteRequest(ptr long)
@ stub IoCompletionObjectType
@ stdcall IoConnectInterrupt(ptr ptr ptr ptr long long long long long long long)
@ stub IoConnectInterruptEx
@ stub IoConvertFileHandleToKernelHandle
@ stub IoCopyDeviceObjectHint
@ stub IoCreateArcName
@ stdcall IoCreateController(long)
@ stdcall IoCreateDevice(ptr long ptr long long long ptr)
@ stdcall IoCreateDisk(ptr ptr)
@ stdcall IoCreateDriver(ptr ptr)
@ stdcall IoCreateFile(ptr long ptr ptr ptr long long long long ptr long long ptr long)
@ stub IoCreateFileEx
@ stdcall IoCreateFileSpecifyDeviceObjectHint(ptr long ptr ptr ptr long long long long ptr long long ptr long ptr)
@ stdcall IoCreateNotificationEvent(ptr ptr)
@ stdcall IoCreateStreamFileObject(ptr ptr)
@ stdcall IoCreateStreamFileObjectEx(ptr ptr ptr)
@ stub IoCreateStreamFileObjectEx2
@ stdcall IoCreateStreamFileObjectLite(ptr ptr)
@ stdcall IoCreateSymbolicLink(ptr ptr)
@ stdcall IoCreateSynchronizationEvent(ptr ptr)
@ stub IoCreateSystemThread
@ stdcall IoCreateUnprotectedSymbolicLink(ptr ptr)
@ stdcall IoCsqInitialize(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall IoCsqInitializeEx(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall IoCsqInsertIrp(ptr ptr ptr)
@ stdcall IoCsqInsertIrpEx(ptr ptr ptr ptr)
@ stdcall IoCsqRemoveIrp(ptr ptr)
@ stdcall IoCsqRemoveNextIrp(ptr ptr)
@ stub IoDecrementKeepAliveCount
@ stub IoDeleteAllDependencyRelations
@ stub IoDeleteController
@ stdcall IoDeleteDevice(ptr)
@ stdcall IoDeleteDriver(ptr)
@ stdcall IoDeleteSymbolicLink(ptr)
@ stdcall IoDetachDevice(ptr)
@ extern IoDeviceHandlerObjectSize
@ extern IoDeviceHandlerObjectType
@ extern IoDeviceObjectType
@ stdcall IoDisconnectInterrupt(ptr)
IoDisconnectInterruptEx
@ extern IoDriverObjectType
IoDuplicateDependency
@ stdcall IoEnqueueIrp(ptr)
@ stdcall IoEnumerateDeviceObjectList(ptr ptr long ptr)
@ stdcall IoEnumerateRegisteredFiltersList(ptr long ptr)
@ stdcall IoFastQueryNetworkAttributes(ptr long long ptr ptr)
@ extern IoFileObjectType
@ stdcall IoForwardAndCatchIrp(ptr ptr) IoForwardIrpSynchronously
@ stdcall IoForwardIrpSynchronously(ptr ptr)
@ stdcall IoFreeController(ptr)
@ stdcall IoFreeErrorLogEntry(ptr)
@ stdcall IoFreeIrp(ptr)
@ stdcall IoFreeMdl(ptr)
IoFreeMiniCompletionPacket
IoFreeSfioStreamIdentifier
@ stdcall IoFreeWorkItem(ptr)
IoGetActivityIdIrp
IoGetActivityIdThread
IoGetAffinityInterrupt
@ stdcall IoGetAttachedDevice(ptr)
@ stdcall IoGetAttachedDeviceReference(ptr)
@ stdcall IoGetBaseFileSystemDeviceObject(ptr)
@ stdcall IoGetBootDiskInformation(ptr long)
IoGetBootDiskInformationLite
@ stdcall IoGetConfigurationInformation()
IoGetContainerInformation
@ stdcall IoGetCurrentProcess()
@ stdcall IoGetDeviceAttachmentBaseRef(ptr)
@ stdcall IoGetDeviceInterfaceAlias(ptr ptr ptr)
IoGetDeviceInterfacePropertyData
@ stdcall IoGetDeviceInterfaces(ptr ptr long ptr)
IoGetDeviceNumaNode
@ stdcall IoGetDeviceObjectPointer(ptr long ptr ptr)
@ stdcall IoGetDeviceProperty(ptr long long ptr ptr)
IoGetDevicePropertyData
@ stdcall IoGetDeviceToVerify(ptr)
@ stdcall IoGetDiskDeviceObject(ptr ptr)
@ stdcall IoGetDmaAdapter(ptr ptr ptr)
@ stdcall IoGetDriverObjectExtension(ptr ptr)
@ stdcall IoGetFileObjectGenericMapping()
IoGetFsTrackOffsetState
IoGetFsZeroingOffset
IoGetGenericIrpExtension
@ stdcall IoGetInitialStack()
IoGetInitiatorProcess
IoGetIoPriorityHint
IoGetIrpExtraCreateParameter
@ stdcall IoGetLowerDeviceObject(ptr)
IoGetOplockKeyContext
IoGetOplockKeyContextEx
@ fastcall IoGetPagingIoPriority(ptr)
@ stdcall IoGetRelatedDeviceObject(ptr)
@ stdcall IoGetRequestorProcess(ptr)
@ stdcall IoGetRequestorProcessId(ptr)
@ stdcall IoGetRequestorSessionId(ptr ptr)
IoGetSfioStreamIdentifier
@ stdcall IoGetStackLimits(ptr ptr)
IoGetSymlinkSupportInformation
@ stdcall IoGetTopLevelIrp()
IoGetTransactionParameterBlock
IoIncrementKeepAliveCount
@ stdcall IoInitializeIrp(ptr long long)
IoInitializeMiniCompletionPacket
@ stdcall IoInitializeRemoveLockEx(ptr long long long long)
@ stdcall IoInitializeTimer(ptr ptr ptr)
IoInitializeWorkItem
@ stdcall IoInvalidateDeviceRelations(ptr long)
@ stdcall IoInvalidateDeviceState(ptr)
@ stdcall -arch=x86_64 IoIs32bitProcess(ptr)
IoIsActivityTracingEnabled
IoIsFileObjectIgnoringSharing
@ stdcall IoIsFileOriginRemote(ptr)
IoIsInitiator32bitProcess
@ stdcall IoIsOperationSynchronous(ptr)
@ stdcall IoIsSystemThread(ptr)
IoIsValidIrpStatus
@ stdcall IoIsValidNameGraftingBuffer(ptr ptr)
@ stdcall IoIsWdmVersionAvailable(long long)
IoLoadCrashDumpDriver
@ stdcall IoMakeAssociatedIrp(ptr long)
@ stdcall IoOpenDeviceInterfaceRegistryKey(ptr long ptr)
@ stdcall IoOpenDeviceRegistryKey(ptr long long ptr)
@ stdcall IoPageRead(ptr ptr ptr ptr ptr)
IoPropagateActivityIdToThread
IoPropagateIrpExtension
IoPropagateIrpExtensionEx
@ stdcall IoQueryDeviceDescription(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall IoQueryFileDosDeviceName(ptr ptr)
@ stdcall IoQueryFileInformation(ptr long long ptr ptr)
IoQueryFullDriverPath
IoQueryInterface
@ stdcall IoQueryVolumeInformation(ptr long long ptr ptr)
@ stdcall IoQueueThreadIrp(ptr)
@ stdcall IoQueueWorkItem(ptr ptr long ptr)
IoQueueWorkItemEx
IoQueueWorkItemToNode
@ stdcall IoRaiseHardError(ptr ptr ptr)
@ stdcall IoRaiseInformationalHardError(long ptr ptr)
@ stdcall IoReadDiskSignature(ptr long ptr)
@ extern IoReadOperationCount
@ fastcall IoReadPartitionTable(ptr long long ptr)
@ stdcall IoReadPartitionTableEx(ptr ptr)
@ extern IoReadTransferCount
@ stub IoRegisterBootDriverCallback
@ stdcall IoRegisterBootDriverReinitialization(ptr ptr ptr)
@ stub IoRegisterContainerNotification
@ stdcall IoRegisterDeviceInterface(ptr ptr ptr ptr)
@ stdcall IoRegisterDriverReinitialization(ptr ptr ptr)
@ stdcall IoRegisterFileSystem(ptr)
@ stdcall IoRegisterFsRegistrationChange(ptr ptr)
@ stub IoRegisterFsRegistrationChangeMountAware
@ stub IoRegisterIoTracking
@ stdcall IoRegisterLastChanceShutdownNotification(ptr)
@ stdcall IoRegisterPlugPlayNotification(long long ptr ptr ptr ptr ptr)
@ stub IoRegisterPriorityCallback
@ stdcall IoRegisterShutdownNotification(ptr)
@ stdcall IoReleaseCancelSpinLock(long)
@ stdcall IoReleaseRemoveLockAndWaitEx(ptr ptr long)
@ stdcall IoReleaseRemoveLockEx(ptr ptr long)
@ stdcall IoReleaseVpbSpinLock(long)
@ stdcall IoRemoveShareAccess(ptr ptr)
@ stub IoReplaceFileObjectName
@ stub IoReplacePartitionUnit
@ stdcall IoReportDetectedDevice(ptr long long long ptr ptr long ptr)
@ stdcall IoReportHalResourceUsage(ptr ptr ptr long)
@ stub IoReportInterruptActive
@ stub IoReportInterruptInactive
@ stdcall IoReportResourceForDetection(ptr ptr long ptr ptr long ptr)
@ stdcall IoReportResourceUsage(ptr ptr ptr long ptr ptr long long ptr)
@ stub IoReportRootDevice
@ stdcall IoReportTargetDeviceChange(ptr ptr)
@ stdcall IoReportTargetDeviceChangeAsynchronous(ptr ptr ptr ptr)
@ stdcall IoRequestDeviceEject(ptr)
@ stub IoRequestDeviceEjectEx
@ stub IoRequestDeviceRemovalForReset
@ stub IoReserveDependency
@ stub IoResolveDependency
@ stub IoRetrievePriorityInfo
@ stdcall IoReuseIrp(ptr long)
@ stub IoSetActivityIdIrp
@ stub IoSetActivityIdThread
@ stdcall IoSetCompletionRoutineEx(ptr ptr ptr ptr long long long)
@ stub IoSetDependency
@ stub IoSetDeviceInterfacePropertyData
@ stdcall IoSetDeviceInterfaceState(ptr long)
@ stub IoSetDevicePropertyData
@ stdcall IoSetDeviceToVerify(ptr ptr)
@ stub IoSetFileObjectIgnoreSharing
@ stdcall IoSetFileOrigin(ptr long)
@ stub IoSetFsTrackOffsetState
@ stub IoSetFsZeroingOffset
@ stub IoSetFsZeroingOffsetRequired
@ stub IoSetGenericIrpExtension
@ stdcall IoSetHardErrorOrVerifyDevice(ptr ptr)
@ stdcall IoSetInformation(ptr ptr long ptr)
@ stdcall IoSetIoCompletion(ptr ptr ptr long ptr long)
@ stub IoSetIoCompletionEx
@ stub IoSetIoPriorityHint
@ stub IoSetIoPriorityHintIntoFileObject
@ stub IoSetIoPriorityHintIntoThread
@ stub IoSetIrpExtraCreateParameter
@ stub IoSetMasterIrpStatus
@ fastcall IoSetPartitionInformation(ptr long long long)
@ stdcall IoSetPartitionInformationEx(ptr long ptr)
@ stdcall IoSetShareAccess(long long ptr ptr)
@ stub IoSetShareAccessEx
@ stdcall IoSetStartIoAttributes(ptr long long)
@ stdcall IoSetSystemPartition(ptr)
@ stdcall IoSetThreadHardErrorMode(long)
@ stdcall IoSetTopLevelIrp(ptr)
@ stub IoSizeofGenericIrpExtension
@ stub IoSizeofWorkItem
@ stdcall IoStartNextPacket(ptr long)
@ stdcall IoStartNextPacketByKey(ptr long long)
@ stdcall IoStartPacket(ptr ptr ptr ptr)
@ stdcall IoStartTimer(ptr)
@ extern IoStatisticsLock
@ stdcall IoStopTimer(ptr)
@ stub IoSynchronousCallDriver
@ stdcall IoSynchronousInvalidateDeviceRelations(ptr long)
@ stdcall IoSynchronousPageWrite(ptr ptr ptr ptr ptr)
@ stub IoTestDependency
@ stdcall IoThreadToProcess(ptr)
@ stub IoTransferActivityId
@ stdcall IoTranslateBusAddress(long long long long ptr ptr)
@ stub IoTryQueueWorkItem
@ stub IoUninitializeWorkItem
@ stub IoUnregisterBootDriverCallback
@ stub IoUnregisterContainerNotification
@ stdcall IoUnregisterFileSystem(ptr)
@ stdcall IoUnregisterFsRegistrationChange(ptr ptr)
@ stub IoUnregisterIoTracking
@ stdcall IoUnregisterPlugPlayNotification(ptr)
@ stub IoUnregisterPlugPlayNotificationEx
@ stub IoUnregisterPriorityCallback
@ stdcall IoUnregisterShutdownNotification(ptr)
@ stdcall IoUpdateShareAccess(ptr ptr)
@ stdcall IoValidateDeviceIoControlAccess(ptr long)
@ stdcall IoVerifyPartitionTable(ptr long)
@ stdcall IoVerifyVolume(ptr long)
@ stdcall IoVolumeDeviceToDosName(ptr ptr)
@ stub IoVolumeDeviceToGuid
@ stub IoVolumeDeviceToGuidPath
@ stdcall IoWMIAllocateInstanceIds(ptr long ptr)
@ stdcall IoWMIDeviceObjectToInstanceName(ptr ptr ptr)
@ stdcall -arch=x86_64 IoWMIDeviceObjectToProviderId(ptr)
@ stdcall IoWMIExecuteMethod(ptr ptr long long ptr ptr)
@ stdcall IoWMIHandleToInstanceName(ptr ptr ptr)
@ stdcall IoWMIOpenBlock(ptr long ptr)
@ stdcall IoWMIQueryAllData(ptr ptr ptr)
@ stdcall IoWMIQueryAllDataMultiple(ptr long ptr ptr)
@ stdcall IoWMIQuerySingleInstance(ptr ptr ptr ptr)
@ stdcall IoWMIQuerySingleInstanceMultiple(ptr ptr long ptr ptr)
@ stdcall IoWMIRegistrationControl(ptr long)
@ stdcall IoWMISetNotificationCallback(ptr ptr ptr)
@ stdcall IoWMISetSingleInstance(ptr ptr long long ptr)
@ stdcall IoWMISetSingleItem(ptr ptr long long long ptr)
@ stdcall IoWMISuggestInstanceName(ptr ptr long ptr)
@ stdcall IoWMIWriteEvent(ptr)
@ stub IoWithinStackLimits
@ stdcall IoWriteErrorLogEntry(ptr)
@ extern IoWriteOperationCount
@ fastcall IoWritePartitionTable(ptr long long long ptr)
@ stdcall IoWritePartitionTableEx(ptr ptr)
@ extern IoWriteTransferCount
@ fastcall IofCallDriver(ptr ptr)
@ fastcall IofCompleteRequest(ptr long)
@ stub KdAcquireDebuggerLock
@ stdcall KdChangeOption(long long ptr long ptr ptr)
@ extern KdDebuggerEnabled
@ extern KdDebuggerNotPresent
@ stub KdDeregisterPowerHandler
@ stdcall KdDisableDebugger()
@ stdcall KdEnableDebugger()
@ extern KdEnteredDebugger
@ stub KdLogDbgPrint
@ stdcall KdPollBreakIn()
@ stdcall KdPowerTransition(long)
@ stdcall KdRefreshDebuggerNotPresent()
@ stub KdRegisterPowerHandler
@ stub KdReleaseDebuggerLock
@ stub KdSetEventLoggingPresent
@ stdcall KdSystemDebugControl(long ptr long ptr long ptr long)
@ fastcall KeAcquireGuardedMutex(ptr)
@ fastcall KeAcquireGuardedMutexUnsafe(ptr)
@ cdecl -arch=x86_64 KeAcquireInStackQueuedSpinLock(ptr ptr)
@ fastcall KeAcquireInStackQueuedSpinLockAtDpcLevel(ptr ptr)
@ fastcall KeAcquireInStackQueuedSpinLockForDpc(ptr ptr)
@ cdecl -arch=x86_64 KeAcquireInStackQueuedSpinLockRaiseToSynch(ptr ptr)
@ stdcall KeAcquireInterruptSpinLock(ptr)
@ cdecl -arch=x86_64 KeAcquireQueuedSpinLock(long)
@ cdecl -arch=x86_64 KeAcquireQueuedSpinLockRaiseToSynch(long)
@ stdcall KeAcquireSpinLockAtDpcLevel(ptr)
@ fastcall KeAcquireSpinLockForDpc(ptr)
@ stdcall -arch=x86_64 KeAcquireSpinLockRaiseToDpc(ptr)
@ stdcall -arch=x86_64 KeAcquireSpinLockRaiseToSynch(ptr)
@ stub KeAddGroupAffinityEx
@ stub KeAddProcessorAffinityEx
@ stub KeAddProcessorGroupAffinity
@ stdcall KeAddSystemServiceTable(ptr ptr long ptr long)
@ stub KeAlertThread
@ stub KeAllocateCalloutStack
@ stub KeAllocateCalloutStackEx
@ stub KeAndAffinityEx
@ stub KeAndGroupAffinityEx
@ stdcall KeAreAllApcsDisabled()
@ stdcall KeAreApcsDisabled()
@ stdcall KeAttachProcess(ptr)
@ stdcall KeBugCheck(long)
@ stdcall KeBugCheckEx(long ptr ptr ptr ptr)
@ stdcall KeCancelTimer(ptr)
@ stub KeCancelTimer2
@ stdcall KeCapturePersistentThreadState(ptr long long long long long ptr)
@ stub KeCheckProcessorAffinityEx
@ stub KeCheckProcessorGroupAffinity
@ stdcall KeClearEvent(ptr)
@ stub KeClockInterruptNotify
@ stub KeClockTimerPowerChange
@ stub KeComplementAffinityEx
@ stub KeCopyAffinityEx
@ stub KeCountSetBitsAffinityEx
@ stub KeCountSetBitsGroupAffinity
@ stdcall KeDelayExecutionThread(long long ptr)
@ stdcall KeDeregisterBugCheckCallback(ptr)
@ stdcall KeDeregisterBugCheckReasonCallback(ptr)
@ stdcall KeDeregisterNmiCallback(ptr)
@ stub KeDeregisterProcessorChangeCallback
@ stdcall KeDetachProcess()
@ stub KeDispatchSecondaryInterrupt
@ stdcall KeEnterCriticalRegion() _KeEnterCriticalRegion
@ stdcall KeEnterGuardedRegion() _KeEnterGuardedRegion
@ stdcall KeEnterKernelDebugger()
@ stub KeEnumerateNextProcessor
;@ stdcall -arch=x86_64 KeExpandKernelStackAndCallout(ptr ptr double)
@ stub KeExpandKernelStackAndCalloutEx
@ stdcall KeFindConfigurationEntry(ptr long long ptr)
@ stdcall KeFindConfigurationNextEntry(ptr long long ptr ptr)
@ stub KeFindFirstSetLeftAffinityEx
@ stub KeFindFirstSetLeftGroupAffinity
@ stub KeFindFirstSetRightAffinityEx
@ stub KeFindFirstSetRightGroupAffinity
@ stub KeFirstGroupAffinityEx
@ stdcall KeFlushEntireTb(long long)
@ stub KeFlushIoBuffers
@ stdcall KeFlushQueuedDpcs()
@ stub KeForceEnableNx
@ stub KeFreeCalloutStack
@ stdcall KeGenericCallDpc(ptr ptr)
@ stub KeGetClockOwner
@ stub KeGetClockTimerResolution
@ stub KeGetCurrentIrql
@ stub KeGetCurrentNodeNumber
@ stub KeGetCurrentProcessorNumberEx
@ stdcall KeGetCurrentThread()
@ stub KeGetNextClockTickDuration
@ stub KeGetProcessorIndexFromNumber
@ stub KeGetProcessorNumberFromIndex
@ stdcall KeGetRecommendedSharedDataAlignment()
@ stub KeGetXSaveFeatureFlags
@ stub KeHwPolicyLocateResource
@ stub KeInitializeAffinityEx
@ stdcall KeInitializeApc(ptr ptr long ptr ptr ptr long ptr)
@ stdcall KeInitializeCrashDumpHeader(long long ptr long ptr)
@ stdcall KeInitializeDeviceQueue(ptr)
@ stdcall KeInitializeDpc(ptr ptr ptr)
@ stub KeInitializeEnumerationContext
@ stub KeInitializeEnumerationContextFromGroup
@ stdcall KeInitializeEvent(ptr long long)
@ fastcall KeInitializeGuardedMutex(ptr)
@ stdcall KeInitializeInterrupt(ptr ptr ptr ptr long long long long long long long)
@ stdcall KeInitializeMutant(ptr long)
@ stdcall KeInitializeMutex(ptr long)
@ stdcall KeInitializeQueue(ptr long)
@ stub KeInitializeSecondaryInterruptServices
@ stdcall KeInitializeSemaphore(ptr long long)
@ stdcall KeInitializeSpinLock(ptr) _KeInitializeSpinLock
@ stdcall KeInitializeThreadedDpc(ptr ptr ptr)
@ stdcall KeInitializeTimer(ptr)
@ stub KeInitializeTimer2
@ stdcall KeInitializeTimerEx(ptr long)
@ stdcall KeInsertByKeyDeviceQueue(ptr ptr long)
@ stdcall KeInsertDeviceQueue(ptr ptr)
@ stdcall KeInsertHeadQueue(ptr ptr)
@ stdcall KeInsertQueue(ptr ptr)
@ stdcall KeInsertQueueApc(ptr ptr ptr long)
@ stdcall KeInsertQueueDpc(ptr ptr ptr)
@ stub KeInterlockedClearProcessorAffinityEx
@ stub KeInterlockedSetProcessorAffinityEx
@ stdcall KeInvalidateAllCaches()
@ stub KeInvalidateRangeAllCaches
@ stdcall KeIpiGenericCall(ptr ptr)
@ stdcall KeIsAttachedProcess()
@ stub KeIsEmptyAffinityEx
@ stub KeIsEqualAffinityEx
@ stdcall KeIsExecutingDpc()
@ stub KeIsSingleGroupAffinityEx
@ stub KeIsSubsetAffinityEx
;KeIsWaitListEmpty
;@ cdecl -arch=x86_64 KeLastBranchMSR()
@ stdcall KeLeaveCriticalRegion() _KeLeaveCriticalRegion
@ stdcall KeLeaveGuardedRegion() _KeLeaveGuardedRegion
@ stub KeLoadMTRR
@ extern KeLoaderBlock
@ cdecl -arch=x86_64 -private KeLowerIrql(long)
@ stub KeNotifyProcessorFreezeSupported
@ extern KeNumberProcessors _KeNumberProcessors
@ stub KeOrAffinityEx
@ stub KeProcessorGroupAffinity
@ stdcall KeProfileInterruptWithSource(ptr long)
@ stdcall KePulseEvent(ptr long long)
@ stub KeQueryActiveGroupCount
@ stub KeQueryActiveProcessorAffinity
@ stub KeQueryActiveProcessorCount
@ stub KeQueryActiveProcessorCountEx
@ stdcall KeQueryActiveProcessors()
@ stub KeQueryDpcWatchdogInformation
@ stub KeQueryEffectivePriorityThread
@ stub KeQueryGroupAffinity
@ stub KeQueryGroupAffinityEx
@ stub KeQueryHardwareCounterConfiguration
@ stub KeQueryHeteroCpuPolicyThread
@ stub KeQueryHighestNodeNumber
@ stub KeQueryInterruptTimePrecise
@ stub KeQueryLogicalProcessorRelationship
@ stub KeQueryMaximumGroupCount
@ stub KeQueryMaximumProcessorCount
@ stub KeQueryMaximumProcessorCountEx
@ stub KeQueryNodeActiveAffinity
@ stub KeQueryNodeMaximumProcessorCount
;@ cdecl -arch=x86_64 KeQueryPrcbAddress
@ stdcall KeQueryPriorityThread(ptr)
@ stdcall KeQueryRuntimeThread(ptr ptr)
@ stub KeQuerySystemTimePrecise
@ stdcall KeQueryTimeIncrement()
@ stub KeQueryTotalCycleTimeThread
@ stub KeQueryUnbiasedInterruptTime
@ cdecl -arch=x86_64 -private KeRaiseIrqlToDpcLevel()
@ stdcall KeRaiseUserException(long)
@ stdcall KeReadStateEvent(ptr)
@ stdcall KeReadStateMutant(ptr)
@ stdcall KeReadStateMutex(ptr) KeReadStateMutant
@ stdcall KeReadStateQueue(ptr)
@ stdcall KeReadStateSemaphore(ptr)
@ stdcall KeReadStateTimer(ptr)
@ stdcall KeRegisterBugCheckCallback(ptr ptr ptr long ptr)
@ stdcall KeRegisterBugCheckReasonCallback(ptr ptr ptr ptr)
@ stdcall KeRegisterNmiCallback(ptr ptr)
@ stub KeRegisterProcessorChangeCallback
@ fastcall KeReleaseGuardedMutex(ptr)
@ fastcall KeReleaseGuardedMutexUnsafe(ptr)
@ cdecl -arch=x86_64 KeReleaseInStackQueuedSpinLock(ptr)
@ fastcall KeReleaseInStackQueuedSpinLockForDpc(ptr)
@ fastcall KeReleaseInStackQueuedSpinLockFromDpcLevel(ptr)
@ stdcall KeReleaseInterruptSpinLock(ptr long)
@ stdcall KeReleaseMutant(ptr long long long)
@ stdcall KeReleaseMutex(ptr long)
@ cdecl -arch=x86_64 KeReleaseQueuedSpinLock(long long)
@ stdcall KeReleaseSemaphore(ptr long long long)
@ stdcall -arch=x86_64 KeReleaseSpinLock(ptr long)
@ fastcall KeReleaseSpinLockForDpc(ptr long)
@ stdcall KeReleaseSpinLockFromDpcLevel(ptr)
@ stdcall KeRemoveByKeyDeviceQueue(ptr long)
@ stdcall KeRemoveByKeyDeviceQueueIfBusy(ptr long)
@ stdcall KeRemoveDeviceQueue(ptr)
@ stdcall KeRemoveEntryDeviceQueue(ptr ptr)
@ stub KeRemoveGroupAffinityEx
@ stub KeRemoveProcessorAffinityEx
@ stub KeRemoveProcessorGroupAffinity
@ stdcall KeRemoveQueue(ptr long ptr)
@ stdcall KeRemoveQueueDpc(ptr)
@ stub KeRemoveQueueDpcEx
@ stub KeRemoveQueueEx
@ stdcall KeRemoveSystemServiceTable(long)
@ stub KeReportCacheIncoherentDevice
@ stdcall KeResetEvent(ptr)
@ stub KeRestoreExtendedProcessorState
@ stdcall -arch=x86_64 KeRestoreFloatingPointState(ptr) KxRestoreFloatingPointState
@ stdcall KeRevertToUserAffinityThread()
@ stub KeRevertToUserAffinityThreadEx
@ stub KeRevertToUserGroupAffinityThread
@ stdcall KeRundownQueue(ptr)
@ stub KeSaveExtendedProcessorState
@ stdcall -arch=x86_64 KeSaveFloatingPointState(ptr) KxSaveFloatingPointState
@ cdecl KeSaveStateForHibernate(ptr)
@ stub KeSetActualBasePriorityThread
@ stdcall KeSetAffinityThread(ptr long)
@ stdcall KeSetBasePriorityThread(ptr long)
@ stub KeSetCoalescableTimer
@ stdcall KeSetDmaIoCoherency(long)
@ stdcall KeSetEvent(ptr long long)
@ stdcall KeSetEventBoostPriority(ptr ptr)
@ stub KeSetHardwareCounterConfiguration
@ stub KeSetHeteroCpuPolicyThread
@ stdcall KeSetIdealProcessorThread(ptr long)
@ stdcall KeSetImportanceDpc(ptr long)
@ stdcall KeSetKernelStackSwapEnable(long)
@ stdcall KeSetPriorityThread(ptr long)
@ stdcall KeSetProfileIrql(long)
@ stdcall KeSetSystemAffinityThread(long)
KeSetSystemAffinityThreadEx
KeSetSystemGroupAffinityThread
@ stdcall KeSetTargetProcessorDpc(ptr long)
KeSetTargetProcessorDpcEx
@ stdcall KeSetTimer(ptr long long ptr)
KeSetTimer2
@ stdcall KeSetTimerEx(ptr long long long ptr)
KeShouldYieldProcessor
@ stdcall KeSignalCallDpcDone(ptr)
@ stdcall KeSignalCallDpcSynchronize(ptr)
@ stdcall KeStackAttachProcess(ptr ptr)
KeStallWhileFrozen
KeStartDynamicProcessor
KeSubtractAffinityEx
KeSweepLocalCaches
@ stdcall KeSynchronizeExecution(ptr ptr ptr)
KeSynchronizeTimeToQpc
KeSystemFullyCacheCoherent
KeTestAlertThread
@ fastcall KeTestSpinLock(ptr)
@ fastcall KeTryToAcquireGuardedMutex(ptr)
@ cdecl -arch=x86_64 KeTryToAcquireQueuedSpinLock(long long)
@ cdecl -arch=x86_64 KeTryToAcquireQueuedSpinLockRaiseToSynch(long long)
@ fastcall KeTryToAcquireSpinLockAtDpcLevel(ptr)
@ stdcall KeUnstackDetachProcess(ptr)
KeUpdateThreadTag
@ stdcall KeUserModeCallback(long ptr long ptr ptr)
@ stdcall KeWaitForMultipleObjects(long ptr long long long long ptr ptr)
@ stdcall KeWaitForMutexObject(ptr long long long ptr) KeWaitForSingleObject
@ stdcall KeWaitForSingleObject(ptr long long long ptr)
KeWriteProtectPAT
@ cdecl -arch=x86_64 -private KfRaiseIrql(long)
@ extern KiBugCheckData
@ stdcall KiCheckForKernelApcDelivery()
KitLogFeatureUsage
KseQueryDeviceData
KseQueryDeviceDataList
KseQueryDeviceFlags
KseRegisterShim
KseRegisterShimEx
KseSetDeviceFlags
KseUnregisterShim
@ stdcall LdrAccessResource(ptr ptr ptr ptr)
@ stdcall LdrEnumResources(ptr ptr long ptr ptr)
@ stdcall LdrFindResourceDirectory_U(ptr ptr long ptr)
LdrFindResourceEx_U
@ stdcall LdrFindResource_U(ptr ptr long ptr)
LdrResFindResource
LdrResFindResourceDirectory
LdrResSearchResource
@ extern LpcPortObjectType
LpcReplyWaitReplyPort
@ stdcall LpcRequestPort(ptr ptr)
@ stdcall LpcRequestWaitReplyPort(ptr ptr ptr)
LpcRequestWaitReplyPortEx
LpcSendWaitReceivePort
@ stdcall LsaCallAuthenticationPackage(long long long long long long long)
@ stdcall LsaDeregisterLogonProcess(long long)
@ stdcall LsaFreeReturnBuffer(ptr)
@ stdcall LsaLogonUser(ptr ptr long long ptr long ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall LsaLookupAuthenticationPackage(long long long)
@ stdcall LsaRegisterLogonProcess(ptr ptr ptr)
@ extern Mm64BitPhysicalAddress
@ stdcall MmAddPhysicalMemory(ptr ptr)
@ stdcall MmAddVerifierThunks(ptr long)
@ stdcall MmAdjustWorkingSetSize(long long long long)
@ stdcall MmAdvanceMdl(ptr long)
@ stdcall MmAllocateContiguousMemory(long long long)
@ stdcall MmAllocateContiguousMemorySpecifyCache(long long long long long long long long)
MmAllocateContiguousMemorySpecifyCacheNode
MmAllocateContiguousNodeMemory
@ stdcall MmAllocateMappingAddress(long long)
MmAllocateMdlForIoSpace
MmAllocateNodePagesForMdlEx
@ stdcall MmAllocateNonCachedMemory(long)
@ stdcall MmAllocatePagesForMdl(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall MmAllocatePagesForMdlEx(long long long long long long long long long)
@ stub MmAreMdlPagesCached
@ stub MmBadPointer
@ stdcall MmBuildMdlForNonPagedPool(ptr)
@ stdcall MmCanFileBeTruncated(ptr ptr)
@ stdcall MmCommitSessionMappedView(ptr ptr)
@ stub MmCopyMemory
@ stub MmCopyVirtualMemory
@ stdcall MmCreateMdl(ptr ptr long)
@ stub MmCreateMirror
@ stdcall MmCreateSection(ptr long ptr ptr long long ptr ptr)
@ stdcall MmDisableModifiedWriteOfSection(long)
@ stub MmDoesFileHaveUserWritableReferences
@ stdcall MmFlushImageSection(ptr long)
@ stdcall MmForceSectionClosed(ptr long)
@ stdcall MmFreeContiguousMemory(ptr)
@ stdcall MmFreeContiguousMemorySpecifyCache(ptr long long)
@ stdcall MmFreeMappingAddress(ptr long)
@ stdcall MmFreeNonCachedMemory(ptr long)
@ stdcall MmFreePagesFromMdl(ptr)
@ stub MmGetCacheAttribute
@ stub MmGetMaximumFileSectionSize
@ stdcall MmGetPhysicalAddress(ptr)
@ stdcall MmGetPhysicalMemoryRanges()
@ stdcall MmGetSystemRoutineAddress(ptr)
@ stdcall MmGetVirtualForPhysical(long long)
@ stdcall MmGrowKernelStack(ptr)
@ extern MmHighestUserAddress
@ stdcall MmIsAddressValid(ptr)
@ stub MmIsDriverSuspectForVerifier
@ stdcall MmIsDriverVerifying(ptr)
@ stub MmIsDriverVerifyingByAddress
@ stub MmIsIoSpaceActive
@ stdcall MmIsNonPagedSystemAddressValid(ptr)
@ stdcall MmIsRecursiveIoFault()
@ stdcall MmIsThisAnNtAsSystem()
@ stdcall MmIsVerifierEnabled(ptr)
@ stub MmLoadSystemImage
@ stdcall MmLockPagableDataSection(ptr) MmLockPageableDataSection
@ stdcall MmLockPagableImageSection(ptr) MmLockPageableDataSection
@ stdcall MmLockPagableSectionByHandle(ptr) MmLockPageableSectionByHandle
@ stdcall MmMapIoSpace(long long long long)
@ stdcall MmMapLockedPages(ptr long)
@ stdcall MmMapLockedPagesSpecifyCache(ptr long long ptr long long)
@ stdcall MmMapLockedPagesWithReservedMapping(ptr long ptr long)
@ stdcall MmMapMemoryDumpMdl(ptr)
@ stdcall MmMapUserAddressesToPage(ptr long ptr)
@ stdcall MmMapVideoDisplay(long long long long)
@ stdcall MmMapViewInSessionSpace(ptr ptr ptr)
@ stub MmMapViewInSessionSpaceEx
@ stdcall MmMapViewInSystemSpace(ptr ptr ptr)
@ stub MmMapViewInSystemSpaceEx
@ stdcall MmMapViewOfSection(ptr ptr ptr long long ptr ptr long long long)
@ stdcall MmMarkPhysicalMemoryAsBad(ptr ptr)
@ stdcall MmMarkPhysicalMemoryAsGood(ptr ptr)
@ stub MmMdlPageContentsState
@ stub MmMdlPagesAreZero
@ stdcall MmPageEntireDriver(ptr)
@ stdcall MmPrefetchPages(long ptr)
@ stub MmPrefetchVirtualAddresses
@ stdcall MmProbeAndLockPages(ptr long long)
@ stdcall MmProbeAndLockProcessPages(ptr ptr long long)
@ stdcall MmProbeAndLockSelectedPages(ptr ptr long long)
@ stdcall MmProtectMdlSystemAddress(ptr long)
@ stdcall MmQuerySystemSize()
@ stdcall MmRemovePhysicalMemory(ptr ptr)
@ stdcall MmResetDriverPaging(ptr)
@ stub MmRotatePhysicalView
@ extern MmSectionObjectType
@ stdcall MmSecureVirtualMemory(ptr long long)
@ stdcall MmSetAddressRangeModified(ptr long)
@ stdcall MmSetBankedSection(long long long long long long)
@ stdcall MmSizeOfMdl(ptr long)
@ extern MmSystemRangeStart
@ stdcall MmTrimAllSystemPagableMemory(long) MmTrimAllSystemPageableMemory
@ stub MmUnloadSystemImage
@ stdcall MmUnlockPagableImageSection(ptr) MmUnlockPageableImageSection
@ stdcall MmUnlockPages(ptr)
@ stdcall MmUnmapIoSpace(ptr long)
@ stdcall MmUnmapLockedPages(ptr ptr)
@ stdcall MmUnmapReservedMapping(ptr long ptr)
@ stdcall MmUnmapVideoDisplay(ptr long)
@ stdcall MmUnmapViewInSessionSpace(ptr)
@ stdcall MmUnmapViewInSystemSpace(ptr)
@ stdcall MmUnmapViewOfSection(ptr ptr)
@ stdcall MmUnsecureVirtualMemory(ptr)
@ extern MmUserProbeAddress
@ extern NlsAnsiCodePage
@ extern NlsLeadByteInfo
@ extern NlsMbCodePageTag
@ extern NlsMbOemCodePageTag
@ extern NlsOemCodePage
@ extern NlsOemLeadByteInfo
@ stdcall NtAddAtom(wstr long ptr)
@ stdcall NtAdjustPrivilegesToken(ptr long ptr long ptr ptr)
@ stdcall NtAllocateLocallyUniqueId(ptr)
@ stdcall NtAllocateUuids(ptr ptr ptr ptr)
@ stdcall NtAllocateVirtualMemory(ptr ptr long ptr long long)
@ extern NtBuildGUID
@ extern NtBuildLab
@ extern NtBuildNumber
@ stdcall NtClose(ptr)
@ stub NtCommitComplete
@ stub NtCommitEnlistment
@ stub NtCommitTransaction
@ stdcall NtConnectPort(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stub NtCreateEnlistment
@ stdcall NtCreateEvent(ptr long ptr long long)
@ stdcall NtCreateFile(ptr long ptr ptr ptr long long long long ptr long)
@ stub NtCreateResourceManager
@ stdcall NtCreateSection(ptr long ptr ptr long long ptr)
@ stub NtCreateTransaction
@ stub NtCreateTransactionManager
@ stdcall NtDeleteAtom(ptr)
@ stdcall NtDeleteFile(ptr)
@ stdcall NtDeviceIoControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
@ stdcall NtDuplicateObject(ptr ptr ptr ptr long long long)
@ stdcall NtDuplicateToken(ptr long ptr long long ptr)
NtEnumerateTransactionObject
@ stdcall NtFindAtom(wstr long ptr)
@ stdcall NtFreeVirtualMemory(ptr ptr ptr long)
NtFreezeTransactions
@ stdcall NtFsControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
NtGetEnvironmentVariableEx
NtGetNotificationResourceManager
@ extern NtGlobalFlag
@ stdcall NtLockFile(ptr ptr ptr ptr ptr ptr ptr long long long)
@ stdcall NtMakePermanentObject(ptr)
@ stdcall NtMapViewOfSection(ptr ptr ptr long long ptr ptr long long long)
@ stdcall NtNotifyChangeDirectoryFile(ptr ptr ptr ptr ptr ptr long long long)
NtOpenEnlistment
@ stdcall NtOpenFile(ptr long ptr ptr long long)
@ stdcall NtOpenProcess(ptr long ptr ptr)
@ stdcall NtOpenProcessToken(ptr long ptr)
@ stdcall NtOpenProcessTokenEx(ptr long long ptr)
NtOpenResourceManager
@ stdcall NtOpenThread(ptr long ptr ptr)
@ stdcall NtOpenThreadToken(ptr long long ptr)
@ stdcall NtOpenThreadTokenEx(ptr long long long ptr)
NtOpenTransaction
NtOpenTransactionManager
NtPrePrepareComplete
NtPrePrepareEnlistment
NtPrepareComplete
NtPrepareEnlistment
NtPropagationComplete
NtPropagationFailed
@ stdcall NtQueryDirectoryFile(ptr ptr ptr ptr ptr ptr long long long ptr long)
@ stdcall NtQueryEaFile(ptr ptr ptr long long ptr long ptr long)
NtQueryEnvironmentVariableInfoEx
@ stdcall NtQueryInformationAtom(ptr long ptr long ptr)
NtQueryInformationEnlistment
@ stdcall NtQueryInformationFile(ptr ptr ptr long long)
@ stdcall NtQueryInformationProcess(ptr ptr ptr long ptr)
NtQueryInformationResourceManager
@ stdcall NtQueryInformationThread(ptr long ptr long ptr)
@ stdcall NtQueryInformationToken(ptr long ptr long ptr)
NtQueryInformationTransaction
NtQueryInformationTransactionManager
@ stdcall NtQueryQuotaInformationFile(ptr ptr ptr long long ptr long ptr long)
NtQuerySecurityAttributesToken
@ stdcall NtQuerySecurityObject(ptr long ptr long ptr)
@ stdcall NtQuerySystemInformation(long ptr long ptr)
NtQuerySystemInformationEx
@ stdcall NtQueryVolumeInformationFile(ptr ptr ptr long long)
@ stdcall NtReadFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
NtReadOnlyEnlistment
NtRecoverEnlistment
NtRecoverResourceManager
NtRecoverTransactionManager
@ stdcall NtRequestPort(ptr ptr)
@ stdcall NtRequestWaitReplyPort(ptr ptr ptr)
NtRollbackComplete
NtRollbackEnlistment
NtRollbackTransaction
NtSetCachedSigningLevel
@ stdcall NtSetEaFile(ptr ptr ptr long)
@ stdcall NtSetEvent(ptr ptr)
NtSetInformationEnlistment
@ stdcall NtSetInformationFile(ptr ptr ptr long long)
@ stdcall NtSetInformationProcess(ptr ptr ptr long)
NtSetInformationResourceManager
@ stdcall NtSetInformationThread(ptr long ptr long)
NtSetInformationToken
NtSetInformationTransaction
NtSetInformationVirtualMemory
@ stdcall NtSetQuotaInformationFile(ptr ptr ptr long)
@ stdcall NtSetSecurityObject(ptr long ptr)
@ stdcall NtSetVolumeInformationFile(ptr ptr ptr long long)
@ stdcall NtShutdownSystem(long)
NtThawTransactions
NtTraceControl
@ stdcall NtTraceEvent(long long long ptr)
@ stdcall NtUnlockFile(ptr ptr ptr ptr long)
@ stdcall NtVdmControl(long ptr)
@ stdcall NtWaitForSingleObject(ptr long ptr)
@ stdcall NtWriteFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
@ stdcall ObAssignSecurity(ptr ptr ptr ptr)
@ stdcall ObCheckCreateObjectAccess(ptr long ptr ptr long long ptr)
@ stdcall ObCheckObjectAccess(ptr ptr long long ptr)
@ stdcall ObCloseHandle(ptr long)
@ stdcall ObCreateObject(long ptr ptr long ptr long long long ptr)
@ stdcall ObCreateObjectType(ptr ptr ptr ptr)
@ stdcall ObDeleteCapturedInsertInfo(ptr)
@ stdcall ObDereferenceObject(ptr)
@ stdcall ObDereferenceObjectDeferDelete(ptr)
@ stdcall ObDereferenceObjectDeferDeleteWithTag(ptr long)
@ stdcall ObDereferenceSecurityDescriptor(ptr long)
@ stdcall ObDuplicateObject(ptr ptr ptr ptr long long long long)
@ stdcall ObFindHandleForObject(ptr ptr ptr ptr ptr)
@ stdcall ObGetFilterVersion()
@ stdcall ObGetObjectSecurity(ptr ptr ptr)
@ stdcall ObGetObjectType(ptr)
@ stdcall ObInsertObject(ptr ptr long long ptr ptr)
@ stdcall ObIsDosDeviceLocallyMapped(long ptr)
@ stdcall ObIsKernelHandle(ptr)
@ stdcall ObLogSecurityDescriptor(ptr ptr long)
@ stdcall ObMakeTemporaryObject(ptr)
@ stdcall ObOpenObjectByName(ptr ptr long ptr long ptr ptr)
@ stdcall ObOpenObjectByPointer(ptr long ptr long ptr long ptr)
@ stub ObOpenObjectByPointerWithTag
@ stub ObQueryNameInfo
@ stdcall ObQueryNameString(ptr ptr long ptr)
@ stdcall ObQueryObjectAuditingByHandle(ptr ptr)
@ stdcall ObReferenceObjectByHandle(ptr long ptr long ptr ptr)
@ stub ObReferenceObjectByHandleWithTag
@ stdcall ObReferenceObjectByName(ptr long ptr long ptr long ptr ptr)
@ stdcall ObReferenceObjectByPointer(ptr long ptr long)
@ stub ObReferenceObjectByPointerWithTag
@ stub ObReferenceObjectSafe
@ stub ObReferenceObjectSafeWithTag
@ stdcall ObReferenceSecurityDescriptor(ptr long)
@ stub ObRegisterCallbacks
@ stdcall ObReleaseObjectSecurity(ptr long)
@ stdcall ObSetHandleAttributes(ptr ptr long)
@ stdcall ObSetSecurityDescriptorInfo(ptr ptr ptr ptr long ptr)
@ stdcall ObSetSecurityObjectByPointer(ptr long ptr)
@ stub ObUnRegisterCallbacks
@ stub ObWaitForMultipleObjects
@ stub ObWaitForSingleObject
@ fastcall ObfDereferenceObject(ptr)
@ stub ObfDereferenceObjectWithTag
@ fastcall ObfReferenceObject(ptr)
@ stub ObfReferenceObjectWithTag
@ stub POGOBuffer
@ stub PcwAddInstance
@ stub PcwCloseInstance
@ stub PcwCreateInstance
@ stub PcwRegister
@ stub PcwUnregister
@ stub PfFileInfoNotify
@ stub PfxFindPrefix
@ stub PfxInitialize
@ stub PfxInsertPrefix
@ stub PfxRemovePrefix
@ stdcall PoCallDriver(ptr ptr)
@ stdcall PoCancelDeviceNotify(ptr)
@ stub PoClearPowerRequest
@ stub PoCpuIdledSinceLastCallImprecise
@ stub PoCreatePowerRequest
@ stub PoDeletePowerRequest
@ stub PoDisableSleepStates
@ stub PoEndDeviceBusy
@ stub PoEnergyEstimationEnabled
@ stub PoFxActivateComponent
@ stub PoFxCompleteDevicePowerNotRequired
@ stub PoFxCompleteIdleCondition
@ stub PoFxCompleteIdleState
@ stub PoFxEnableDStateReporting
@ stub PoFxIdleComponent
@ stub PoFxIssueComponentPerfStateChange
@ stub PoFxIssueComponentPerfStateChangeMultiple
@ stub PoFxNotifySurprisePowerOn
@ stub PoFxPowerControl
@ stub PoFxPowerOnCrashdumpDevice
@ stub PoFxProcessorNotification
@ stub PoFxQueryCurrentComponentPerfState
@ stub PoFxRegisterComponentPerfStates
@ stub PoFxRegisterCoreDevice
@ stub PoFxRegisterCrashdumpDevice
@ stub PoFxRegisterDevice
@ stub PoFxRegisterPlugin
@ stub PoFxRegisterPluginEx
@ stub PoFxRegisterPrimaryDevice
@ stub PoFxReportDevicePoweredOn
@ stub PoFxSetComponentLatency
@ stub PoFxSetComponentResidency
@ stub PoFxSetComponentWake
@ stub PoFxSetDeviceIdleTimeout
@ stub PoFxStartDevicePowerManagement
@ stub PoFxUnregisterDevice
@ stub PoGetProcessorIdleAccounting
@ stub PoGetSystemWake
@ stub PoInitiateProcessorWake
@ stub PoLatencySensitivityHint
@ stub PoNotifyMediaBuffering
@ stub PoNotifyVSyncChange
@ stub PoQueryWatchdogTime
@ stdcall PoQueueShutdownWorkItem(ptr)
@ stub PoReenableSleepStates
PoRegisterCoalescingCallback
@ stdcall PoRegisterDeviceForIdleDetection(ptr long long long)
@ stdcall PoRegisterDeviceNotify(ptr long long long ptr ptr)
PoRegisterPowerSettingCallback
@ stdcall PoRegisterSystemState(ptr long)
@ stdcall PoRequestPowerIrp(ptr long long ptr ptr ptr)
@ stdcall PoRequestShutdownEvent(ptr)
PoSetDeviceBusyEx
PoSetFixedWakeSource
@ stdcall PoSetHiberRange(ptr long ptr long long)
PoSetPowerRequest
@ stdcall PoSetPowerState(ptr long long)
@ stdcall PoSetSystemState(long)
PoSetSystemWake
PoSetUserPresent
@ stdcall PoShutdownBugCheck(long long ptr ptr ptr ptr)
PoStartDeviceBusy
@ stdcall PoStartNextPowerIrp(ptr)
PoUnregisterCoalescingCallback
PoUnregisterPowerSettingCallback
@ stdcall PoUnregisterSystemState(ptr)
PoUserShutdownCancelled
PoUserShutdownInitiated
@ stdcall ProbeForRead(ptr long long)
@ stdcall ProbeForWrite(ptr long long)
PsAcquireProcessExitSynchronization
@ stdcall PsAssignImpersonationToken(ptr ptr)
@ stdcall PsChargePoolQuota(ptr long long)
@ stdcall PsChargeProcessNonPagedPoolQuota(ptr long)
@ stdcall PsChargeProcessPagedPoolQuota(ptr long)
@ stdcall PsChargeProcessPoolQuota(ptr long long)
PsChargeProcessWakeCounter
@ stdcall PsCreateSystemThread(ptr long ptr ptr ptr ptr ptr)
PsCreateSystemThreadEx
@ stdcall PsDereferenceImpersonationToken(ptr) PsDereferencePrimaryToken
PsDereferenceKernelStack
@ stdcall PsDereferencePrimaryToken(ptr)
@ stdcall PsDisableImpersonation(ptr ptr)
PsEnterPriorityRegion
@ stdcall PsEstablishWin32Callouts(ptr)
@ stdcall PsGetContextThread(ptr ptr long)
@ stdcall PsGetCurrentProcess() IoGetCurrentProcess
@ stdcall PsGetCurrentProcessId()
@ stdcall PsGetCurrentProcessSessionId()
@ stdcall PsGetCurrentProcessWin32Process()
;@ cdecl -arch=x86_64 PsGetCurrentProcessWow64Process()
@ stdcall PsGetCurrentThread() KeGetCurrentThread
@ stdcall PsGetCurrentThreadId()
@ stdcall PsGetCurrentThreadPreviousMode()
@ stdcall PsGetCurrentThreadProcess()
@ stdcall PsGetCurrentThreadProcessId()
@ stdcall PsGetCurrentThreadStackBase()
@ stdcall PsGetCurrentThreadStackLimit()
@ stdcall PsGetCurrentThreadTeb()
@ stdcall PsGetCurrentThreadWin32Thread()
@ stdcall PsGetCurrentThreadWin32ThreadAndEnterCriticalRegion(ptr)
PsGetEffectiveContainerId
@ stdcall PsGetJobLock(ptr)
@ stdcall PsGetJobSessionId(ptr)
@ stdcall PsGetJobUIRestrictionsClass(ptr)
PsGetProcessCommonJob
@ stdcall PsGetProcessCreateTimeQuadPart(ptr)
@ stdcall PsGetProcessDebugPort(ptr)
@ stdcall PsGetProcessExitProcessCalled(ptr)
@ stdcall PsGetProcessExitStatus(ptr)
@ stdcall PsGetProcessExitTime()
@ stdcall PsGetProcessId(ptr)
@ stdcall PsGetProcessImageFileName(ptr)
@ stdcall PsGetProcessInheritedFromUniqueProcessId(ptr)
@ stdcall PsGetProcessJob(ptr)
@ stdcall PsGetProcessPeb(ptr)
@ stdcall PsGetProcessPriorityClass(ptr)
@ stub PsGetProcessProtection
@ stdcall PsGetProcessSectionBaseAddress(ptr)
@ stdcall PsGetProcessSecurityPort(ptr)
@ stdcall PsGetProcessSessionId(ptr)
@ stdcall PsGetProcessSessionIdEx(ptr)
@ stub PsGetProcessSignatureLevel
@ stdcall PsGetProcessWin32Process(ptr)
@ stdcall PsGetProcessWin32WindowStation(ptr)
;@ cdecl -arch=x86_64 PsGetProcessWow64Process()
@ stub PsGetThreadCreateTime
@ stub PsGetThreadExitStatus
@ stdcall PsGetThreadFreezeCount(ptr)
@ stdcall PsGetThreadHardErrorsAreDisabled(ptr)
@ stdcall PsGetThreadId(ptr)
@ stdcall PsGetThreadProcess(ptr)
@ stdcall PsGetThreadProcessId(ptr)
@ stdcall PsGetThreadSessionId(ptr)
@ stdcall PsGetThreadTeb(ptr)
@ stdcall PsGetThreadWin32Thread(ptr)
@ stdcall PsGetVersion(ptr ptr ptr ptr)
@ stdcall PsImpersonateClient(ptr ptr long long long)
@ extern PsInitialSystemProcess
@ stub PsIsCurrentThreadPrefetching
@ stub PsIsDiskCountersEnabled
@ stdcall PsIsProcessBeingDebugged(ptr)
@ stub PsIsProtectedProcess
@ stub PsIsProtectedProcessLight
@ stdcall PsIsSystemProcess(ptr)
@ stdcall PsIsSystemThread(ptr)
@ stdcall PsIsThreadImpersonating(ptr)
@ stdcall PsIsThreadTerminating(ptr)
@ extern PsJobType
@ stub PsLeavePriorityRegion
@ stub PsLoadedModuleList
@ stub PsLoadedModuleResource
@ stdcall PsLookupProcessByProcessId(ptr ptr)
@ stdcall PsLookupProcessThreadByCid(ptr ptr ptr)
@ stdcall PsLookupThreadByThreadId(ptr ptr)
@ extern PsProcessType
PsQueryProcessAttributesByToken
PsQueryProcessExceptionFlags
PsQueryTotalCycleTimeProcess
@ stdcall PsReferenceImpersonationToken(ptr ptr ptr ptr)
PsReferenceKernelStack
@ stdcall PsReferencePrimaryToken(ptr)
PsReferenceProcessFilePointer
PsReleaseProcessExitSynchronization
PsReleaseProcessWakeCounter
@ stdcall PsRemoveCreateThreadNotifyRoutine(ptr)
@ stdcall PsRemoveLoadImageNotifyRoutine(ptr)
@ stdcall PsRestoreImpersonation(ptr ptr)
PsResumeProcess
@ stdcall PsReturnPoolQuota(ptr long long)
@ stdcall PsReturnProcessNonPagedPoolQuota(ptr long)
@ stdcall PsReturnProcessPagedPoolQuota(ptr long)
@ stdcall PsRevertThreadToSelf(ptr)
@ stdcall PsRevertToSelf()
@ stdcall PsSetContextThread(ptr ptr long)
@ stdcall PsSetCreateProcessNotifyRoutine(ptr long)
PsSetCreateProcessNotifyRoutineEx
@ stdcall PsSetCreateThreadNotifyRoutine(ptr)
PsSetCurrentThreadPrefetching
@ stdcall PsSetLegoNotifyRoutine(ptr)
@ stdcall PsSetLoadImageNotifyRoutine(ptr)
@ stdcall PsSetProcessPriorityByClass(ptr ptr)
@ stdcall PsSetProcessPriorityClass(ptr long)
@ stdcall PsSetProcessSecurityPort(ptr ptr)
@ stdcall PsSetProcessWin32Process(ptr ptr ptr)
@ stdcall PsSetProcessWindowStation(ptr ptr)
@ stdcall PsSetThreadHardErrorsAreDisabled(ptr long)
@ stdcall PsSetThreadWin32Thread(ptr ptr ptr)
PsSuspendProcess
@ stdcall PsTerminateSystemThread(long)
@ extern PsThreadType
PsUILanguageComitted
PsUpdateComponentPower
PsUpdateDiskCounters
PsWrapApcWow64Thread
@ stdcall RtlAbsoluteToSelfRelativeSD(ptr ptr ptr)
@ stdcall RtlAddAccessAllowedAce(ptr long long ptr)
@ stdcall RtlAddAccessAllowedAceEx(ptr long long long ptr)
RtlAddAccessAllowedObjectAce
RtlAddAccessDeniedAceEx
RtlAddAccessDeniedObjectAce
@ stdcall RtlAddAce(ptr long long ptr long)
@ stdcall RtlAddAtomToAtomTable(ptr wstr ptr)
RtlAddAtomToAtomTableEx
RtlAddAuditAccessAceEx
RtlAddAuditAccessObjectAce
@ stdcall RtlAddRange(ptr long long long long long long ptr ptr)
RtlAddResourceAttributeAce
@ stdcall RtlAllocateHeap(ptr long long)
@ stdcall RtlAnsiCharToUnicodeChar(ptr)
@ stdcall RtlAnsiStringToUnicodeSize(ptr) RtlxAnsiStringToUnicodeSize
@ stdcall RtlAnsiStringToUnicodeString(ptr ptr long)
@ stdcall RtlAppendAsciizToString(ptr str)
@ stdcall RtlAppendStringToString(ptr ptr)
@ stdcall RtlAppendUnicodeStringToString(ptr ptr)
@ stdcall RtlAppendUnicodeToString(ptr wstr)
@ stdcall RtlAreAllAccessesGranted(long long)
@ stdcall RtlAreAnyAccessesGranted(long long)
@ stdcall RtlAreBitsClear(ptr long long)
RtlAreBitsClearEx
@ stdcall RtlAreBitsSet(ptr long long)
RtlAreBitsSetEx
@ stdcall RtlAssert(str str long str)
RtlAvlInsertNodeEx
RtlAvlRemoveNode
@ stdcall RtlCaptureContext(ptr)
@ stdcall RtlCaptureStackBackTrace(long long ptr ptr)
@ stdcall RtlCharToInteger(str long ptr)
RtlCheckPortableOperatingSystem
@ stdcall RtlCheckRegistryKey(long wstr)
RtlCheckTokenCapability
RtlCheckTokenMembership
RtlCheckTokenMembershipEx
@ stdcall RtlClearAllBits(ptr)
RtlClearAllBitsEx
@ stdcall RtlClearBit(ptr long)
RtlClearBitEx
@ stdcall RtlClearBits(ptr long long)
RtlClearBitsEx
RtlCmDecodeMemIoResource
RtlCmEncodeMemIoResource
RtlCompareAltitudes
@ stdcall RtlCompareMemory(ptr ptr long)
@ stdcall RtlCompareMemoryUlong(ptr long long)
@ stdcall RtlCompareString(ptr ptr long)
@ stdcall RtlCompareUnicodeString(ptr ptr long)
RtlCompareUnicodeStrings
@ stdcall RtlCompressBuffer(long ptr long ptr long long ptr ptr)
@ stdcall RtlCompressChunks(ptr long ptr long ptr long ptr)
RtlComputeCrc32
RtlContractHashTable
@ stdcall RtlConvertSidToUnicodeString(ptr ptr long)
RtlCopyBitMap
@ stdcall RtlCopyLuid(ptr ptr)
RtlCopyLuidAndAttributesArray
@ stdcall -arch=x86_64 RtlCopyMemory(ptr ptr int64) memmove
@ stdcall -arch=x86_64 RtlCopyMemoryNonTemporal(ptr ptr int64) memmove
@ stdcall RtlCopyRangeList(ptr ptr)
@ stdcall RtlCopySid(long ptr ptr)
RtlCopySidAndAttributesArray
@ stdcall RtlCopyString(ptr ptr)
@ stdcall RtlCopyUnicodeString(ptr ptr)
RtlCrc32
RtlCrc64
@ stdcall RtlCreateAcl(ptr long long)
@ stdcall RtlCreateAtomTable(long ptr)
RtlCreateAtomTableEx
RtlCreateHashTable
RtlCreateHashTableEx
@ stdcall RtlCreateHeap(long ptr long long ptr ptr)
@ stdcall RtlCreateRegistryKey(long wstr)
@ stdcall RtlCreateSecurityDescriptor(ptr long)
@ stdcall RtlCreateSystemVolumeInformationFolder(ptr)
@ stdcall RtlCreateUnicodeString(ptr wstr)
RtlCreateUserThread
RtlCultureNameToLCID
@ stdcall RtlCustomCPToUnicodeN(ptr wstr long ptr ptr long)
@ stdcall RtlDecompressBuffer(long ptr long ptr long ptr)
RtlDecompressBufferEx
RtlDecompressBufferEx2
@ stdcall RtlDecompressChunks(ptr long ptr long ptr long ptr)
@ stdcall RtlDecompressFragment(long ptr long ptr long long ptr ptr)
RtlDecompressFragmentEx
@ stdcall RtlDelete(ptr)
@ stdcall RtlDeleteAce(ptr long)
@ stdcall RtlDeleteAtomFromAtomTable(ptr ptr)
@ stdcall RtlDeleteElementGenericTable(ptr ptr)
@ stdcall RtlDeleteElementGenericTableAvl(ptr ptr)
RtlDeleteElementGenericTableAvlEx
RtlDeleteHashTable
@ stdcall RtlDeleteNoSplay(ptr ptr)
@ stdcall RtlDeleteOwnersRanges(ptr ptr)
@ stdcall RtlDeleteRange(ptr long long long long ptr)
@ stdcall RtlDeleteRegistryValue(long wstr wstr)
@ stdcall RtlDescribeChunk(long ptr ptr ptr ptr)
@ stdcall RtlDestroyAtomTable(ptr)
@ stdcall RtlDestroyHeap(ptr)
RtlDowncaseUnicodeChar
@ stdcall RtlDowncaseUnicodeString(ptr ptr long)
RtlDuplicateUnicodeString
@ stdcall RtlEmptyAtomTable(ptr long)
RtlEndEnumerationHashTable
RtlEndWeakEnumerationHashTable
RtlEnumerateEntryHashTable
@ stdcall RtlEnumerateGenericTable(ptr long)
@ stdcall RtlEnumerateGenericTableAvl(ptr long)
@ stdcall RtlEnumerateGenericTableLikeADirectory(ptr ptr ptr long ptr ptr ptr)
@ stdcall RtlEnumerateGenericTableWithoutSplaying(ptr ptr)
@ stdcall RtlEnumerateGenericTableWithoutSplayingAvl(ptr ptr)
@ stdcall RtlEqualLuid(ptr ptr)
@ stdcall RtlEqualSid(ptr ptr)
@ stdcall RtlEqualString(ptr ptr long)
@ stdcall RtlEqualUnicodeString(ptr ptr long)
RtlEqualWnfChangeStamps
RtlEthernetAddressToStringA
RtlEthernetAddressToStringW
RtlEthernetStringToAddressA
RtlEthernetStringToAddressW
RtlExpandHashTable
RtlExtractBitMap
@ stdcall RtlFillMemory(ptr long long)
RtlFindAceByType
@ stdcall RtlFindClearBits(ptr long long)
@ stdcall RtlFindClearBitsAndSet(ptr long long)
RtlFindClearBitsAndSetEx
RtlFindClearBitsEx
@ stdcall RtlFindClearRuns(ptr ptr long long)
RtlFindClosestEncodableLength
@ stdcall RtlFindFirstRunClear(ptr ptr)
@ stdcall RtlFindLastBackwardRunClear(ptr long ptr)
@ stdcall RtlFindLeastSignificantBit(long long)
@ stdcall RtlFindLongestRunClear(ptr ptr)
@ stdcall RtlFindMessage(ptr long long long ptr)
@ stdcall RtlFindMostSignificantBit(long long)
@ stdcall RtlFindNextForwardRunClear(ptr long ptr)
RtlFindNextForwardRunClearEx
@ stdcall RtlFindRange(ptr long long long long long long long long ptr ptr ptr)
@ stdcall RtlFindSetBits(ptr long long)
@ stdcall RtlFindSetBitsAndClear(ptr long long)
RtlFindSetBitsAndClearEx
RtlFindSetBitsEx
@ stdcall RtlFindUnicodePrefix(ptr ptr long)
RtlFirstFreeAce
@ stdcall RtlFormatCurrentUserKeyPath(ptr)
RtlFormatMessage
@ stdcall RtlFreeAnsiString(ptr)
@ stdcall RtlFreeHeap(ptr long ptr)
@ stdcall RtlFreeOemString(ptr)
@ stdcall RtlFreeRangeList(ptr)
@ stdcall RtlFreeUnicodeString(ptr)
@ stdcall RtlGUIDFromString(ptr ptr)
@ stdcall RtlGenerate8dot3Name(ptr ptr long ptr)
RtlGenerateClass5Guid
@ stdcall RtlGetAce(ptr long ptr)
RtlGetAppContainerNamedObjectPath
RtlGetAppContainerParent
RtlGetAppContainerSidType
@ stdcall RtlGetCallersAddress(ptr ptr)
@ stdcall RtlGetCompressionWorkSpaceSize(long ptr ptr)
RtlGetControlSecurityDescriptor
@ stdcall RtlGetDaclSecurityDescriptor(ptr ptr ptr ptr)
@ stdcall RtlGetDefaultCodePage(ptr ptr)
@ stdcall RtlGetElementGenericTable(ptr long)
@ stdcall RtlGetElementGenericTableAvl(ptr long)
RtlGetEnabledExtendedFeatures
@ stdcall RtlGetFirstRange(ptr ptr ptr)
@ stdcall RtlGetGroupSecurityDescriptor(ptr ptr ptr)
RtlGetIntegerAtom
RtlGetLastRange
RtlGetNextEntryHashTable
@ stdcall RtlGetNextRange(ptr ptr long)
@ stdcall RtlGetNtGlobalFlags()
@ stdcall RtlGetOwnerSecurityDescriptor(ptr ptr ptr)
RtlGetProductInfo
@ stdcall RtlGetSaclSecurityDescriptor(ptr ptr ptr ptr)
@ stdcall RtlGetSetBootStatusData(ptr long long ptr long long)
RtlGetThreadLangIdByIndex
@ stdcall RtlGetVersion(ptr)
@ stdcall RtlHashUnicodeString(ptr long long ptr)
RtlIdnToAscii
RtlIdnToNameprepUnicode
RtlIdnToUnicode
@ stdcall RtlImageDirectoryEntryToData(ptr long long ptr)
@ stdcall RtlImageNtHeader(ptr)
RtlImageNtHeaderEx
@ stdcall RtlInitAnsiString(ptr str)
@ stdcall RtlInitAnsiStringEx(ptr str)
@ stdcall RtlInitCodePageTable(ptr ptr)
RtlInitEnumerationHashTable
@ stdcall RtlInitString(ptr str)
RtlInitStringEx
@ stdcall RtlInitUnicodeString(ptr wstr)
@ stdcall RtlInitUnicodeStringEx(ptr wstr)
RtlInitWeakEnumerationHashTable
@ stdcall RtlInitializeBitMap(ptr ptr long)
RtlInitializeBitMapEx
@ stdcall RtlInitializeGenericTable(ptr ptr ptr ptr ptr)
@ stdcall RtlInitializeGenericTableAvl(ptr ptr ptr ptr ptr)
@ stdcall RtlInitializeRangeList(ptr)
@ stdcall RtlInitializeSid(ptr ptr long)
RtlInitializeSidEx
@ stdcall RtlInitializeUnicodePrefix(ptr)
@ stdcall RtlInsertElementGenericTable(ptr ptr long ptr)
@ stdcall RtlInsertElementGenericTableAvl(ptr ptr long ptr)
@ stdcall RtlInsertElementGenericTableFull(ptr ptr long ptr ptr long)
@ stdcall RtlInsertElementGenericTableFullAvl(ptr ptr long ptr ptr ptr)
RtlInsertEntryHashTable
@ stdcall RtlInsertUnicodePrefix(ptr ptr ptr)
@ stdcall RtlInt64ToUnicodeString(long long long ptr)
@ stdcall RtlIntegerToChar(long long long ptr)
@ stdcall RtlIntegerToUnicode(long long long ptr)
@ stdcall RtlIntegerToUnicodeString(long long ptr)
RtlInterlockedClearBitRun
RtlInterlockedSetBitRun
RtlInterlockedSetClearRun
@ stdcall RtlInvertRangeList(ptr ptr)
RtlInvertRangeListEx
RtlIoDecodeMemIoResource
RtlIoEncodeMemIoResource
@ stdcall RtlIpv4AddressToStringA(ptr ptr)
@ stdcall RtlIpv4AddressToStringExA(ptr long ptr ptr)
@ stdcall RtlIpv4AddressToStringExW(ptr long ptr ptr)
@ stdcall RtlIpv4AddressToStringW(ptr ptr)
@ stdcall RtlIpv4StringToAddressA(str long ptr ptr)
@ stdcall RtlIpv4StringToAddressExA(str long ptr ptr)
@ stdcall RtlIpv4StringToAddressExW(wstr long ptr ptr)
@ stdcall RtlIpv4StringToAddressW(wstr long ptr ptr)
@ stdcall RtlIpv6AddressToStringA(ptr ptr)
@ stdcall RtlIpv6AddressToStringExA(ptr long long ptr ptr)
@ stdcall RtlIpv6AddressToStringExW(ptr long long ptr ptr)
@ stdcall RtlIpv6AddressToStringW(ptr ptr)
@ stdcall RtlIpv6StringToAddressA(str ptr ptr)
@ stdcall RtlIpv6StringToAddressExA(str ptr ptr ptr)
@ stdcall RtlIpv6StringToAddressExW(wstr ptr ptr ptr)
@ stdcall RtlIpv6StringToAddressW(wstr ptr ptr)
@ stdcall RtlIsGenericTableEmpty(ptr)
@ stdcall RtlIsGenericTableEmptyAvl(ptr)
@ stdcall RtlIsNameLegalDOS8Dot3(ptr ptr ptr)
@ stub RtlIsNormalizedString
@ stub RtlIsNtDdiVersionAvailable
@ stdcall RtlIsRangeAvailable(ptr long long long long long long ptr ptr ptr)
@ stub RtlIsServicePackVersionInstalled
@ stub RtlIsUntrustedObject
@ stdcall RtlIsValidOemCharacter(ptr)
@ stub RtlLCIDToCultureName
@ stdcall RtlLengthRequiredSid(long)
@ stdcall RtlLengthSecurityDescriptor(ptr)
@ stdcall RtlLengthSid(ptr)
@ stub RtlLoadString
RtlLocalTimeToSystemTime
@ stdcall RtlLockBootStatusData(ptr)
@ stdcall RtlLookupAtomInAtomTable(ptr wstr ptr)
@ stdcall RtlLookupElementGenericTable(ptr ptr)
@ stdcall RtlLookupElementGenericTableAvl(ptr ptr)
@ stdcall RtlLookupElementGenericTableFull(ptr ptr ptr ptr)
@ stdcall RtlLookupElementGenericTableFullAvl(ptr ptr ptr ptr)
RtlLookupEntryHashTable
RtlLookupFirstMatchingElementGenericTableAvl
@ cdecl -arch=x86_64 RtlLookupFunctionEntry(double ptr ptr)
@ stdcall RtlMapGenericMask(ptr ptr)
@ stdcall RtlMapSecurityErrorToNtStatus(long)
@ stdcall RtlMergeRangeLists(ptr ptr ptr long)
@ stdcall RtlMoveMemory(ptr ptr long)
@ stdcall RtlMultiByteToUnicodeN(ptr long ptr str long)
@ stdcall RtlMultiByteToUnicodeSize(ptr str long)
@ stdcall RtlNextUnicodePrefix(ptr long)
@ stub RtlNormalizeString
@ stdcall RtlNtStatusToDosError(long)
@ stdcall RtlNtStatusToDosErrorNoTeb(long)
@ stdcall RtlNumberGenericTableElements(ptr)
@ stdcall RtlNumberGenericTableElementsAvl(ptr)
@ stdcall RtlNumberOfClearBits(ptr)
RtlNumberOfClearBitsEx
RtlNumberOfClearBitsInRange
@ stdcall RtlNumberOfSetBits(ptr)
RtlNumberOfSetBitsEx
RtlNumberOfSetBitsInRange
RtlNumberOfSetBitsUlongPtr
@ stdcall RtlOemStringToCountedUnicodeString(ptr ptr long)
@ stdcall RtlOemStringToUnicodeSize(ptr) RtlxOemStringToUnicodeSize
@ stdcall RtlOemStringToUnicodeString(ptr ptr long)
@ stdcall RtlOemToUnicodeN(wstr long ptr ptr long)
RtlOpenCurrentUser
RtlOwnerAcesPresent
@ cdecl -arch=x86_64 RtlPcToFileHeader(ptr ptr)
@ stdcall RtlPinAtomInAtomTable(ptr ptr)
@ fastcall RtlPrefetchMemoryNonTemporal(ptr long)
@ stdcall RtlPrefixString(ptr ptr long)
@ stdcall RtlPrefixUnicodeString(ptr ptr long)
@ stdcall RtlQueryAtomInAtomTable(ptr ptr ptr ptr ptr ptr)
RtlQueryDynamicTimeZoneInformation
RtlQueryElevationFlags
RtlQueryInformationAcl
RtlQueryModuleInformation
RtlQueryPackageIdentity
@ stdcall RtlQueryRegistryValues(long wstr ptr ptr ptr)
RtlQueryRegistryValuesEx
@ stdcall RtlQueryTimeZoneInformation(ptr)
RtlQueryValidationRunlevel
@ stdcall RtlRaiseException(ptr)
@ stdcall RtlRandom(ptr)
@ stdcall RtlRandomEx(ptr)
RtlRbInsertNodeEx
RtlRbRemoveNode
@ stdcall RtlRealPredecessor(ptr)
@ stdcall RtlRealSuccessor(ptr)
RtlRemoveEntryHashTable
@ stdcall RtlRemoveUnicodePrefix(ptr ptr)
RtlReplaceSidInSd
@ stdcall RtlReserveChunk(long ptr ptr ptr long)
@ cdecl -arch=x86_64 RtlRestoreContext(ptr ptr)
RtlRunOnceBeginInitialize
RtlRunOnceComplete
RtlRunOnceExecuteOnce
RtlRunOnceInitialize
@ stdcall RtlSecondsSince1970ToTime(long ptr)
@ stdcall RtlSecondsSince1980ToTime(long ptr)
@ stdcall RtlSelfRelativeToAbsoluteSD(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall RtlSelfRelativeToAbsoluteSD2(ptr long)
@ stdcall RtlSetAllBits(ptr)
RtlSetAllBitsEx
@ stdcall RtlSetBit(ptr long)
RtlSetBitEx
@ stdcall RtlSetBits(ptr long long)
RtlSetBitsEx
RtlSetControlSecurityDescriptor
@ stdcall RtlSetDaclSecurityDescriptor(ptr long ptr long)
RtlSetDynamicTimeZoneInformation
@ stdcall RtlSetGroupSecurityDescriptor(ptr ptr long)
@ stdcall RtlSetOwnerSecurityDescriptor(ptr ptr long)
RtlSetPortableOperatingSystem
@ stdcall RtlSetSaclSecurityDescriptor(ptr long ptr long)
@ stdcall RtlSetTimeZoneInformation(ptr)
RtlSidHashInitialize
RtlSidHashLookup
@ stdcall RtlSizeHeap(ptr long ptr)
@ stdcall RtlSplay(ptr)
@ stdcall RtlStringFromGUID(ptr ptr)
@ stdcall RtlSubAuthorityCountSid(ptr)
@ stdcall RtlSubAuthoritySid(ptr long)
@ stdcall RtlSubtreePredecessor(ptr)
@ stdcall RtlSubtreeSuccessor(ptr)
RtlSystemTimeToLocalTime
@ stdcall RtlTestBit(ptr long)
RtlTestBitEx
@ stdcall RtlTimeFieldsToTime(ptr ptr)
@ stdcall RtlTimeToElapsedTimeFields(ptr ptr)
@ stdcall RtlTimeToSecondsSince1970(ptr ptr)
@ stdcall RtlTimeToSecondsSince1980(ptr ptr)
@ stdcall RtlTimeToTimeFields(ptr ptr)
;RtlTraceDatabaseAdd
;RtlTraceDatabaseCreate
;RtlTraceDatabaseDestroy
;RtlTraceDatabaseEnumerate
;RtlTraceDatabaseFind
;RtlTraceDatabaseLock
;RtlTraceDatabaseUnlock
;RtlTraceDatabaseValidate
@ stub RtlUTF8ToUnicodeN
@ stdcall RtlUnicodeStringToAnsiSize(ptr) RtlxUnicodeStringToAnsiSize
@ stdcall RtlUnicodeStringToAnsiString(ptr ptr long)
@ stdcall RtlUnicodeStringToCountedOemString(ptr ptr long)
@ stub RtlUnicodeStringToInt64
@ stdcall RtlUnicodeStringToInteger(ptr long ptr)
@ stdcall RtlUnicodeStringToOemSize(ptr) RtlxUnicodeStringToOemSize
@ stdcall RtlUnicodeStringToOemString(ptr ptr long)
@ stdcall RtlUnicodeToCustomCPN(ptr ptr long ptr wstr long)
@ stdcall RtlUnicodeToMultiByteN(ptr long ptr wstr long)
@ stdcall RtlUnicodeToMultiByteSize(ptr wstr long)
@ stdcall RtlUnicodeToOemN(ptr long ptr wstr long)
@ stub RtlUnicodeToUTF8N
@ stdcall RtlUnlockBootStatusData(ptr)
@ stdcall RtlUnwind(ptr ptr ptr ptr)
@ cdecl -arch=x86_64 RtlUnwindEx(double double ptr ptr ptr ptr)
@ stdcall RtlUpcaseUnicodeChar(long)
@ stdcall RtlUpcaseUnicodeString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeStringToAnsiString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeStringToCountedOemString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeStringToOemString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeToCustomCPN(ptr ptr long ptr wstr long)
@ stdcall RtlUpcaseUnicodeToMultiByteN(ptr long ptr wstr long)
@ stdcall RtlUpcaseUnicodeToOemN(ptr long ptr wstr long)
@ stdcall RtlUpperChar(long)
@ stdcall RtlUpperString(ptr ptr)
@ stdcall RtlValidAcl(ptr)
@ stdcall RtlValidRelativeSecurityDescriptor(ptr long long)
@ stdcall RtlValidSecurityDescriptor(ptr)
@ stdcall RtlValidSid(ptr)
RtlValidateUnicodeString
@ stdcall RtlVerifyVersionInfo(ptr long long long)
@ cdecl -arch=x86_64 RtlVirtualUnwind(long double double ptr ptr ptr ptr ptr)
@ stdcall RtlVolumeDeviceToDosName(ptr ptr) IoVolumeDeviceToDosName
@ stdcall RtlWalkFrameChain(ptr long long)
RtlWeaklyEnumerateEntryHashTable
@ stdcall RtlWriteRegistryValue(long wstr wstr long ptr long)
@ stdcall RtlZeroHeap(ptr long)
@ stdcall RtlZeroMemory(ptr long)
@ stdcall RtlxAnsiStringToUnicodeSize(ptr)
@ stdcall RtlxOemStringToUnicodeSize(ptr)
@ stdcall RtlxUnicodeStringToAnsiSize(ptr)
@ stdcall RtlxUnicodeStringToOemSize(ptr)
@ stdcall SeAccessCheck(ptr ptr ptr long long ptr ptr long ptr ptr)
@ stub SeAccessCheckEx
@ stub SeAccessCheckFromState
@ stub SeAccessCheckFromStateEx
@ stub SeAccessCheckWithHint
@ stub SeAdjustAccessStateForTrustLabel
@ stdcall SeAppendPrivileges(ptr ptr)
@ stdcall SeAssignSecurity(ptr ptr ptr long ptr ptr ptr)
@ stdcall SeAssignSecurityEx(ptr ptr ptr ptr long long ptr ptr ptr)
@ stdcall SeAuditHardLinkCreation(ptr ptr long)
@ stub SeAuditHardLinkCreationWithTransaction
@ stub SeAuditTransactionStateChange
@ stub SeAuditingAnyFileEventsWithContext
@ stub SeAuditingAnyFileEventsWithContextEx
@ stdcall SeAuditingFileEvents(long ptr)
@ stdcall SeAuditingFileEventsWithContext(long ptr ptr)
@ stub SeAuditingFileEventsWithContextEx
@ stdcall SeAuditingFileOrGlobalEvents(long ptr ptr)
@ stdcall SeAuditingHardLinkEvents(long ptr)
@ stdcall SeAuditingHardLinkEventsWithContext(long ptr ptr)
@ stub SeAuditingWithTokenForSubcategory
@ stdcall SeCaptureSecurityDescriptor(ptr long long long ptr)
@ stdcall SeCaptureSubjectContext(ptr)
@ stub SeCaptureSubjectContextEx
@ stdcall SeCloseObjectAuditAlarm(ptr ptr long)
@ stub SeCloseObjectAuditAlarmForNonObObject
@ stub SeComputeAutoInheritByObjectType
@ stdcall SeCreateAccessState(ptr ptr long ptr)
@ stub SeCreateAccessStateEx
@ stdcall SeCreateClientSecurity(ptr ptr long ptr)
@ stub SeCreateClientSecurityEx
@ stdcall SeCreateClientSecurityFromSubjectContext(ptr ptr long ptr)
@ stub SeCreateClientSecurityFromSubjectContextEx
@ stdcall SeDeassignSecurity(ptr)
@ stdcall SeDeleteAccessState(ptr)
@ stdcall SeDeleteObjectAuditAlarm(ptr ptr)
@ stub SeDeleteObjectAuditAlarmWithTransaction
@ stub SeExamineSacl
@ extern SeExports
@ stdcall SeFilterToken(ptr long ptr ptr ptr ptr)
@ stdcall SeFreePrivileges(ptr)
@ stub SeGetCachedSigningLevel
@ stub SeGetLinkedToken
@ stub SeGetLogonSessionToken
@ stdcall SeImpersonateClient(ptr ptr)
@ stdcall SeImpersonateClientEx(ptr ptr)
@ stub SeIsParentOfChildAppContainer
@ stub SeLocateProcessImageName
@ stdcall SeLockSubjectContext(ptr)
@ stdcall SeMarkLogonSessionForTerminationNotification(ptr)
@ stdcall SeOpenObjectAuditAlarm(ptr ptr ptr ptr ptr long long long ptr)
@ stub SeOpenObjectAuditAlarmForNonObObject
@ stub SeOpenObjectAuditAlarmWithTransaction
@ stdcall SeOpenObjectForDeleteAuditAlarm(ptr ptr ptr ptr ptr long long long ptr)
@ stub SeOpenObjectForDeleteAuditAlarmWithTransaction
@ stdcall SePrivilegeCheck(ptr ptr long)
@ stdcall SePrivilegeObjectAuditAlarm(ptr ptr long ptr long long)
@ extern SePublicDefaultDacl
@ stdcall SeQueryAuthenticationIdToken(ptr ptr)
@ stdcall SeQueryInformationToken(ptr long ptr)
@ stub SeQuerySecureBootPolicyValue
@ stub SeQuerySecurityAttributesToken
@ stdcall SeQuerySecurityDescriptorInfo(ptr ptr ptr ptr)
@ stdcall SeQuerySessionIdToken(ptr ptr)
@ stub SeRegisterImageVerificationCallback
@ stdcall SeRegisterLogonSessionTerminatedRoutine(ptr)
@ stdcall SeReleaseSecurityDescriptor(ptr long long)
@ stdcall SeReleaseSubjectContext(ptr)
@ stdcall SeReportSecurityEvent(long ptr ptr ptr)
@ stub SeReportSecurityEventWithSubCategory
@ stub SeSecurityAttributePresent
@ stdcall SeSetAccessStateGenericMapping(ptr ptr)
@ stdcall SeSetAuditParameter(ptr long long ptr)
@ stub SeSetSecurityAttributesToken
@ stdcall SeSetSecurityDescriptorInfo(ptr ptr ptr ptr long ptr)
@ stdcall SeSetSecurityDescriptorInfoEx(ptr ptr ptr ptr long long ptr)
@ stub SeShouldCheckForAccessRightsFromParent
@ stdcall SeSinglePrivilegeCheck(long long long)
@ stub SeSrpAccessCheck
@ extern SeSystemDefaultDacl
@ stub SeSystemDefaultSd
@ stub SeTokenFromAccessInformation
@ stdcall SeTokenImpersonationLevel(ptr)
@ stdcall SeTokenIsAdmin(ptr)
@ stdcall SeTokenIsRestricted(ptr)
@ stdcall SeTokenIsWriteRestricted(ptr)
@ extern SeTokenObjectType
@ stdcall SeTokenType(ptr)
@ stdcall SeUnlockSubjectContext(ptr)
@ stub SeUnregisterImageVerificationCallback
@ stdcall SeUnregisterLogonSessionTerminatedRoutine(ptr)
@ stdcall SeValidSecurityDescriptor(long ptr)
TmCancelPropagationRequest
TmCommitComplete
TmCommitEnlistment
TmCommitTransaction
TmCreateEnlistment
TmCurrentTransaction
TmDereferenceEnlistmentKey
TmEnableCallbacks
TmEndPropagationRequest
TmEnlistmentObjectType
TmFreezeTransactions
TmGetTransactionId
TmInitSystem
TmInitSystemPhase2
TmInitializeTransactionManager
TmIsKTMCommitCoordinator
TmIsTransactionActive
TmPrePrepareComplete
TmPrePrepareEnlistment
TmPrepareComplete
TmPrepareEnlistment
TmPropagationComplete
TmPropagationFailed
TmReadOnlyEnlistment
TmRecoverEnlistment
TmRecoverResourceManager
TmRecoverTransactionManager
TmReferenceEnlistmentKey
TmRenameTransactionManager
TmRequestOutcomeEnlistment
TmResourceManagerObjectType
TmRollbackComplete
TmRollbackEnlistment
TmRollbackTransaction
TmSetCurrentTransaction
TmSinglePhaseReject
TmThawTransactions
TmTransactionManagerObjectType
TmTransactionObjectType
@ stdcall VerSetConditionMask(long long long long)
VfCheckNxPagePriority
VfCheckNxPageProtection
VfCheckNxPoolType
@ cdecl VfFailDeviceNode(ptr long long long ptr ptr ptr)
;VfFailDriver
@ cdecl VfFailSystemBIOS(long long long ptr ptr ptr)
@ stub VfInsertContext
@ stdcall VfIsVerificationEnabled(long ptr)
@ stub VfQueryDeviceContext
@ stub VfQueryDispatchTable
@ stub VfQueryDriverContext
@ stub VfQueryIrpContext
@ stub VfQueryThreadContext
@ stub VfRemoveContext
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
@ stdcall WmiQueryTraceInformation(long ptr long ptr ptr)
@ cdecl WmiTraceMessage()
@ stdcall WmiTraceMessageVa(double long ptr long ptr)
;XIPDispatch
@ stdcall ZwAccessCheckAndAuditAlarm(ptr ptr ptr ptr ptr long ptr long ptr ptr ptr)
@ stdcall ZwAddBootEntry(ptr long)
@ stdcall ZwAddDriverEntry(ptr long)
@ stdcall ZwAdjustPrivilegesToken(ptr long ptr long ptr ptr)
@ stdcall ZwAlertThread(ptr)
@ stub ZwAllocateLocallyUniqueId
@ stdcall ZwAllocateVirtualMemory(ptr ptr long ptr long long)
ZwAlpcAcceptConnectPort
ZwAlpcCancelMessage
ZwAlpcConnectPort
ZwAlpcConnectPortEx
ZwAlpcCreatePort
ZwAlpcCreatePortSection
ZwAlpcCreateResourceReserve
ZwAlpcCreateSectionView
ZwAlpcCreateSecurityContext
ZwAlpcDeletePortSection
ZwAlpcDeleteResourceReserve
ZwAlpcDeleteSectionView
ZwAlpcDeleteSecurityContext
ZwAlpcDisconnectPort
ZwAlpcOpenSenderThread
ZwAlpcQueryInformation
ZwAlpcSendWaitReceivePort
ZwAlpcSetInformation
@ stdcall ZwAssignProcessToJobObject(ptr ptr)
ZwAssociateWaitCompletionPacket
@ stdcall ZwCancelIoFile(ptr ptr)
ZwCancelIoFileEx
@ stdcall ZwCancelTimer(ptr ptr)
@ stdcall ZwClearEvent(ptr)
@ stdcall ZwClose(ptr)
@ stdcall ZwCloseObjectAuditAlarm(ptr ptr long)
ZwCommitComplete
ZwCommitEnlistment
ZwCommitTransaction
@ stdcall ZwConnectPort(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall ZwCreateDirectoryObject(ptr long ptr)
ZwCreateEnlistment
@ stdcall ZwCreateEvent(ptr long ptr long long)
@ stdcall ZwCreateFile(ptr long ptr ptr ptr long long long long ptr long)
ZwCreateIoCompletion
@ stdcall ZwCreateJobObject(ptr long ptr)
@ stdcall ZwCreateKey(ptr long ptr long ptr long ptr)
ZwCreateKeyTransacted
ZwCreateResourceManager
@ stdcall ZwCreateSection(ptr long ptr ptr long long ptr)
@ stdcall ZwCreateSymbolicLinkObject(ptr long ptr ptr)
@ stdcall ZwCreateTimer(ptr long ptr long)
ZwCreateTransaction
ZwCreateTransactionManager
ZwCreateWaitCompletionPacket
ZwCreateWnfStateName
@ stdcall ZwDeleteBootEntry(long)
@ stdcall ZwDeleteDriverEntry(long)
@ stdcall ZwDeleteFile(ptr)
@ stdcall ZwDeleteKey(ptr)
@ stdcall ZwDeleteValueKey(ptr ptr)
ZwDeleteWnfStateData
ZwDeleteWnfStateName
@ stdcall ZwDeviceIoControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
@ stdcall ZwDisplayString(ptr)
@ stdcall ZwDuplicateObject(ptr ptr ptr ptr long long long)
@ stdcall ZwDuplicateToken(ptr long ptr long long ptr)
@ stdcall ZwEnumerateBootEntries(ptr ptr)
@ stdcall ZwEnumerateDriverEntries(ptr ptr)
@ stdcall ZwEnumerateKey(ptr long long ptr long ptr)
ZwEnumerateTransactionObject
@ stdcall ZwEnumerateValueKey(ptr long long ptr long ptr)
ZwFlushBuffersFile
ZwFlushBuffersFileEx
@ stdcall ZwFlushInstructionCache(ptr ptr long)
@ stdcall ZwFlushKey(ptr)
@ stdcall ZwFlushVirtualMemory(ptr ptr ptr ptr)
@ stdcall ZwFreeVirtualMemory(ptr ptr ptr long)
@ stdcall ZwFsControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
ZwGetNotificationResourceManager
ZwImpersonateAnonymousToken
@ stdcall ZwInitiatePowerAction(long long long long)
@ stdcall ZwIsProcessInJob(ptr ptr)
@ stdcall ZwLoadDriver(ptr)
@ stdcall ZwLoadKey(ptr ptr)
ZwLoadKeyEx
ZwLockFile
ZwLockProductActivationKeys
ZwLockVirtualMemory
@ stdcall ZwMakeTemporaryObject(ptr)
@ stdcall ZwMapViewOfSection(ptr ptr ptr long long ptr ptr long long long)
@ stdcall ZwModifyBootEntry(ptr)
@ stdcall ZwModifyDriverEntry(ptr)
@ stdcall ZwNotifyChangeKey(ptr ptr ptr ptr ptr long long ptr long long)
ZwNotifyChangeSession
@ stdcall ZwOpenDirectoryObject(ptr long ptr)
ZwOpenEnlistment
@ stdcall ZwOpenEvent(ptr long ptr)
@ stdcall ZwOpenFile(ptr long ptr ptr long long)
@ stdcall ZwOpenJobObject(ptr long ptr)
@ stdcall ZwOpenKey(ptr long ptr)
ZwOpenKeyEx
ZwOpenKeyTransacted
ZwOpenKeyTransactedEx
@ stdcall ZwOpenProcess(ptr long ptr ptr)
@ stdcall ZwOpenProcessToken(ptr long ptr)
@ stdcall ZwOpenProcessTokenEx(ptr long long ptr)
ZwOpenResourceManager
@ stdcall ZwOpenSection(ptr long ptr)
ZwOpenSession
@ stdcall ZwOpenSymbolicLinkObject(ptr long ptr)
@ stdcall ZwOpenThread(ptr long ptr ptr)
@ stdcall ZwOpenThreadToken(ptr long long ptr)
@ stdcall ZwOpenThreadTokenEx(ptr long long long ptr)
@ stdcall ZwOpenTimer(ptr long ptr)
ZwOpenTransaction
ZwOpenTransactionManager
@ stdcall ZwPowerInformation(long ptr long ptr long)
ZwPrePrepareComplete
ZwPrePrepareEnlistment
ZwPrepareComplete
ZwPrepareEnlistment
ZwPropagationComplete
ZwPropagationFailed
ZwProtectVirtualMemory
@ stdcall ZwPulseEvent(ptr ptr)
@ stdcall ZwQueryBootEntryOrder(ptr ptr)
@ stdcall ZwQueryBootOptions(ptr ptr)
@ stdcall ZwQueryDefaultLocale(long ptr)
@ stdcall ZwQueryDefaultUILanguage(ptr)
@ stdcall ZwQueryDirectoryFile(ptr ptr ptr ptr ptr ptr long long long ptr long)
@ stdcall ZwQueryDirectoryObject(ptr ptr long long long ptr ptr)
@ stdcall ZwQueryDriverEntryOrder(ptr ptr)
@ stdcall ZwQueryEaFile(ptr ptr ptr long long ptr long ptr long)
@ stdcall ZwQueryFullAttributesFile(ptr ptr)
ZwQueryInformationEnlistment
@ stdcall ZwQueryInformationFile(ptr ptr ptr long long)
@ stdcall ZwQueryInformationJobObject(ptr long ptr long ptr)
@ stdcall ZwQueryInformationProcess(ptr long ptr long ptr)
ZwQueryInformationResourceManager
@ stdcall ZwQueryInformationThread(ptr long ptr long ptr)
@ stdcall ZwQueryInformationToken(ptr long long long ptr)
ZwQueryInformationTransaction
ZwQueryInformationTransactionManager
@ stdcall ZwQueryInstallUILanguage(ptr)
@ stdcall ZwQueryKey(ptr long ptr long ptr)
ZwQueryLicenseValue
@ stdcall ZwQueryObject(ptr long ptr long ptr)
ZwQueryQuotaInformationFile
@ stdcall ZwQuerySection(ptr long ptr long ptr)
ZwQuerySecurityAttributesToken
@ stdcall ZwQuerySecurityObject(ptr long ptr long ptr)
@ stdcall ZwQuerySymbolicLinkObject(ptr ptr ptr)
ZwQuerySystemEnvironmentValueEx
@ stdcall ZwQuerySystemInformation(long ptr long ptr)
ZwQuerySystemInformationEx
@ stdcall ZwQueryValueKey(ptr ptr long ptr long ptr)
ZwQueryVirtualMemory
@ stdcall ZwQueryVolumeInformationFile(ptr ptr ptr long long)
ZwQueryWnfStateData
ZwQueryWnfStateNameInformation
@ stdcall ZwReadFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
ZwReadOnlyEnlistment
ZwRecoverEnlistment
ZwRecoverResourceManager
ZwRecoverTransactionManager
ZwRemoveIoCompletion
ZwRemoveIoCompletionEx
ZwRenameKey
@ stdcall ZwReplaceKey(ptr ptr ptr)
ZwRequestPort
@ stdcall ZwRequestWaitReplyPort(ptr ptr ptr)
@ stdcall ZwResetEvent(ptr ptr)
@ stdcall ZwRestoreKey(ptr ptr long)
ZwRollbackComplete
ZwRollbackEnlistment
ZwRollbackTransaction
@ stdcall ZwSaveKey(ptr ptr)
@ stdcall ZwSaveKeyEx(ptr ptr long)
@ stdcall ZwSecureConnectPort(ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall ZwSetBootEntryOrder(ptr ptr)
@ stdcall ZwSetBootOptions(ptr long)
ZwSetCachedSigningLevel
@ stdcall ZwSetDefaultLocale(long long)
@ stdcall ZwSetDefaultUILanguage(long)
@ stdcall ZwSetDriverEntryOrder(ptr ptr)
@ stdcall ZwSetEaFile(ptr ptr ptr long)
@ stdcall ZwSetEvent(ptr ptr)
ZwSetInformationEnlistment
@ stdcall ZwSetInformationFile(ptr ptr ptr long long)
@ stdcall ZwSetInformationJobObject(ptr long ptr long)
ZwSetInformationKey
@ stdcall ZwSetInformationObject(ptr long ptr long)
@ stdcall ZwSetInformationProcess(ptr long ptr long)
ZwSetInformationResourceManager
@ stdcall ZwSetInformationThread(ptr long ptr long)
ZwSetInformationToken
ZwSetInformationTransaction
ZwSetInformationVirtualMemory
ZwSetQuotaInformationFile
@ stdcall ZwSetSecurityObject(ptr long ptr)
ZwSetSystemEnvironmentValueEx
@ stdcall ZwSetSystemInformation(long ptr long)
@ stdcall ZwSetSystemTime(ptr ptr)
@ stdcall ZwSetTimer(ptr ptr ptr ptr long long ptr)
ZwSetTimerEx
@ stdcall ZwSetValueKey(ptr ptr long long ptr long)
@ stdcall ZwSetVolumeInformationFile(ptr ptr ptr long long)
@ stdcall ZwTerminateJobObject(ptr long)
@ stdcall ZwTerminateProcess(ptr long)
ZwTraceEvent
@ stdcall ZwTranslateFilePath(ptr long ptr long)
@ stdcall ZwUnloadDriver(ptr)
@ stdcall ZwUnloadKey(ptr)
ZwUnloadKeyEx
ZwUnlockFile
ZwUnlockVirtualMemory
@ stdcall ZwUnmapViewOfSection(ptr ptr)
ZwUpdateWnfStateData
@ stdcall ZwWaitForMultipleObjects(long ptr long long ptr)
@ stdcall ZwWaitForSingleObject(ptr long ptr)
@ stdcall ZwWriteFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
@ stdcall ZwYieldExecution()
@ cdecl -arch=x86_64 __C_specific_handler(ptr long ptr ptr)
@ cdecl -arch=x86_64 __chkstk()
;@ cdecl -arch=x86_64 __misaligned_access()
_finite
_i64toa_s
_i64tow_s
@ cdecl _itoa()
_itoa_s
@ cdecl _itow()
_itow_s
@ cdecl -arch=x86_64 _local_unwind()
_ltoa_s
_ltow_s
_makepath_s
@ cdecl _purecall()
@ cdecl -arch=x86_64 _setjmp(ptr ptr)
@ cdecl -arch=x86_64 _setjmpex(ptr ptr)
@ cdecl _snprintf()
_snprintf_s
_snscanf_s
@ cdecl _snwprintf()
_snwprintf_s
_snwscanf_s
_splitpath_s
@ cdecl _stricmp()
@ cdecl _strlwr()
@ cdecl _strnicmp()
@ cdecl _strnset()
_strnset_s
@ cdecl _strrev()
@ cdecl _strset()
_strset_s
_strtoui64
@ cdecl _strupr()
_swprintf
_ui64toa_s
_ui64tow_s
_ultoa_s
_ultow_s
@ cdecl _vsnprintf()
_vsnprintf_s
@ cdecl _vsnwprintf()
_vsnwprintf_s
_vswprintf
@ cdecl _wcsicmp()
@ cdecl _wcslwr()
_wcslwr_s
@ cdecl _wcsnicmp()
@ cdecl _wcsnset()
_wcsnset_s
@ cdecl _wcsrev()
_wcsset_s
@ cdecl _wcsupr()
_wmakepath_s
_wsplitpath_s
_wtoi
_wtol
@ cdecl atoi()
@ cdecl atol()
bsearch
bsearch_s
@ cdecl isdigit()
@ cdecl islower()
@ cdecl isprint()
@ cdecl isspace()
@ cdecl isupper()
iswalnum
iswdigit
iswspace
@ cdecl isxdigit()
@ cdecl -arch=x86_64 longjmp(ptr long)
@ cdecl mbstowcs()
@ cdecl mbtowc()
@ cdecl memchr()
@ cdecl -arch=x86_64 memcmp()
@ cdecl memcpy()
memcpy_s
@ cdecl memmove()
memmove_s
@ cdecl memset()
psMUITest
@ cdecl qsort()
@ cdecl rand()
@ cdecl sprintf()
sprintf_s
sqrt
sqrtf
@ cdecl srand()
sscanf_s
@ cdecl strcat()
strcat_s
@ cdecl strchr()
@ cdecl strcmp()
@ cdecl strcpy()
strcpy_s
@ cdecl strlen()
@ cdecl strncat()
strncat_s
@ cdecl strncmp()
@ cdecl strncpy()
strncpy_s
strnlen
@ cdecl strrchr()
@ cdecl strspn()
@ cdecl strstr()
strtok_s
@ cdecl swprintf()
swprintf_s
swscanf_s
@ cdecl tolower()
@ cdecl toupper()
@ cdecl towlower()
@ cdecl towupper()
@ stdcall vDbgPrintEx(long long str ptr)
@ stdcall vDbgPrintExWithPrefix(str long long str ptr)
@ cdecl vsprintf()
vsprintf_s
vswprintf_s
@ cdecl wcscat()
wcscat_s
@ cdecl wcschr()
@ cdecl wcscmp()
@ cdecl wcscpy()
wcscpy_s
@ cdecl wcscspn()
@ cdecl wcslen()
@ cdecl wcsncat()
wcsncat_s
@ cdecl wcsncmp()
@ cdecl wcsncpy()
wcsncpy_s
wcsnlen
@ cdecl wcsrchr()
@ cdecl wcsspn()
@ cdecl wcsstr()
@ cdecl wcstombs()
wcstoul
@ cdecl wctomb()
