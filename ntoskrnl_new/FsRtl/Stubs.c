
#include <ntifs.h>

typedef ULONG FSRTL_ALLOCATE_ECP_FLAGS;
typedef ULONG FSRTL_ALLOCATE_ECPLIST_FLAGS;
typedef ULONG FSRTL_ECP_LOOKASIDE_FLAGS;
typedef ULONG FSRTL_UNC_PROVIDER_FLAGS; // ntifs.h

typedef enum _FSRTL_CHANGE_BACKING_TYPE
{
    ChangeDataControlArea,
    ChangeImageControlArea,
    ChangeSharedCacheMap
} FSRTL_CHANGE_BACKING_TYPE, *PFSRTL_CHANGE_BACKING_TYPE;

// fltmgrfsrtl.h
typedef struct _FSRTL_FLTMGR_CALLS
{
    VOID (*FltMgrEcpCleanupCallback)( PVOID Filter, PVOID EcpContext );
    NTSTATUS (*FltMgrSupportedFeaturesCallback)( PDEVICE_OBJECT Device, PULONG SupportedFeatures );
    NTSTATUS (*FltMgrGetFileNameCallback)(
        _In_ PFILE_OBJECT FileObject,
        _In_ ULONG NameOptions,
        _Out_ PUNICODE_STRING FileName,
        _Out_ PVOID *FileNameInformation
        );
    VOID (*FltMgrReleaseFileNameInformationCallback)(
        PVOID FilenameInformation
        );
    VOID (*FltMgrAttachDeviceCallback)( PDEVICE_OBJECT SourceDevice, PDEVICE_OBJECT TargetDevice );
} FSRTL_FLTMGR_CALLS, *PFSRTL_FLTMGR_CALLS;
typedef struct _FSRTL_FLTMGR_CALLS const *PCFSRTL_FLTMGR_CALLS;

// ntddk.h
typedef struct _FILE_FS_SECTOR_SIZE_INFORMATION
{
    ULONG LogicalBytesPerSector;
    ULONG PhysicalBytesPerSectorForAtomicity;
    ULONG PhysicalBytesPerSectorForPerformance;
    ULONG FileSystemEffectivePhysicalBytesPerSectorForAtomicity;
    ULONG Flags;
    ULONG ByteOffsetForSectorAlignment;
    ULONG ByteOffsetForPartitionAlignment;
} FILE_FS_SECTOR_SIZE_INFORMATION, *PFILE_FS_SECTOR_SIZE_INFORMATION;

// ntifs.h
typedef struct _FILE_ID_128
{
    UCHAR Identifier[16];
} FILE_ID_128, *PFILE_ID_128;

typedef struct _FSRTL_EOF_LOCK
{
    PETHREAD LockOwner;
    LIST_ENTRY EofListHead;
    PFSRTL_ADVANCED_FCB_HEADER Header;
    KPRIORITY OwnerPriority;
    BOOLEAN IsIoPriorityBoosted;
    BOOLEAN Unused;
    USHORT OwnerCount;
} FSRTL_EOF_LOCK, *PFSRTL_EOF_LOCK;

// ntosp.h
typedef struct _TIERING_HEAT_DATA
{
    ULONG VolumeIdHash;
    ULONG Flags;
} TIERING_HEAT_DATA, *PTIERING_HEAT_DATA;

// ntosifs.h
typedef enum _FSRTL_APP_TERMINATE_REASON
{
    FltRundownWait,
    FsrlOplockBreak,
    ReasonCount
} FSRTL_APP_TERMINATE_REASON, *PFSRTL_APP_TERMINATE_REASON;

typedef VOID
(*PFSRTL_EXTRA_CREATE_PARAMETER_CLEANUP_CALLBACK) (
    _Inout_ PVOID EcpContext,
    _In_ LPCGUID EcpType
    );

typedef struct _ECP_LIST ECP_LIST;
typedef struct _ECP_LIST *PECP_LIST;
typedef struct _ECP_HEADER ECP_HEADER;
typedef struct _ECP_HEADER *PECP_HEADER;

const UCHAR * const FsRtlLegalAnsiCharacterArray;

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlAcknowledgeEcp (
    _In_ PVOID EcpContext)
{
    __debugbreak();
}

VOID
NTAPI
FsRtlAcquireEofLock (
    _Inout_ PFSRTL_EOF_LOCK EofLock)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlAcquireFileExclusive (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
}

VOID
NTAPI
FsRtlAcquireHeaderMutex (
    _Inout_ PFSRTL_EOF_LOCK EofLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlAddBaseMcbEntry (
    _Inout_ PBASE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _In_ LONGLONG Lbn,
    _In_ LONGLONG SectorCount)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlAddBaseMcbEntryEx (
    _Inout_ PBASE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _In_ LONGLONG Lbn,
    _In_ LONGLONG SectorCount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlAddLargeMcbEntry (
    _Inout_ PLARGE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _In_ LONGLONG Lbn,
    _In_ LONGLONG SectorCount)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlAddMcbEntry (
    _Inout_ PMCB Mcb,
    _In_ VBN Vbn,
    _In_ LBN Lbn,
    _In_ ULONG SectorCount)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlAddToTunnelCache (
    _Inout_ TUNNEL *Cache,
    _In_ ULONGLONG DirectoryKey,
    _In_ UNICODE_STRING *ShortName,
    _In_ UNICODE_STRING *LongName,
    _In_ BOOLEAN KeyByShortName,
    _In_ ULONG DataLength,
    _In_reads_bytes_(DataLength) VOID *Data)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlAllocateExtraCreateParameter (
    _In_ LPCGUID EcpType,
    _In_ ULONG SizeOfContext,
    _In_ FSRTL_ALLOCATE_ECP_FLAGS Flags,
    _In_opt_ PFSRTL_EXTRA_CREATE_PARAMETER_CLEANUP_CALLBACK CleanupCallback,
    _In_ ULONG PoolTag,
    _Outptr_result_bytebuffer_(SizeOfContext) PVOID *EcpContext
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlAllocateExtraCreateParameterFromLookasideList (
    _In_ LPCGUID EcpType,
     ULONG SizeOfContext,
    _In_ FSRTL_ALLOCATE_ECP_FLAGS Flags,
    _In_opt_ PFSRTL_EXTRA_CREATE_PARAMETER_CLEANUP_CALLBACK CleanupCallback,
    _Inout_ PVOID LookasideList,
    _Outptr_ PVOID *EcpContext
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlAllocateExtraCreateParameterList (
    _In_ FSRTL_ALLOCATE_ECPLIST_FLAGS Flags,
    _Outptr_ PECP_LIST *EcpList
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFILE_LOCK
NTAPI
FsRtlAllocateFileLock (
    _In_opt_ PCOMPLETE_LOCK_IRP_ROUTINE CompleteLockIrpRoutine,
    _In_opt_ PUNLOCK_ROUTINE UnlockRoutine
    )
{
    __debugbreak();
    return NULL;
}

PVOID
NTAPI
FsRtlAllocatePool (
    _In_ POOL_TYPE PoolType,
    _In_ ULONG NumberOfBytes
    )
{
    __debugbreak();
    return NULL;
}

PVOID
NTAPI
FsRtlAllocatePoolWithQuota (
    _In_ POOL_TYPE PoolType,
    _In_ ULONG NumberOfBytes
    )
{
    __debugbreak();
    return NULL;
}

PVOID
NTAPI
FsRtlAllocatePoolWithQuotaTag (
    _In_ POOL_TYPE PoolType,
    _In_ ULONG NumberOfBytes,
    _In_ ULONG Tag
    )
{
    return ExAllocatePoolWithQuotaTag(
        (POOL_TYPE)((ULONG)PoolType | POOL_RAISE_IF_ALLOCATION_FAILURE),
        NumberOfBytes,
        Tag);
}

PVOID
NTAPI
FsRtlAllocatePoolWithTag (
    _In_ __drv_strictTypeMatch(__drv_typeExpr) POOL_TYPE PoolType,
    _In_ ULONG NumberOfBytes,
    _In_ ULONG Tag
    )
{
    return ExAllocatePoolWithTag(
        (POOL_TYPE)((ULONG)PoolType | POOL_RAISE_IF_ALLOCATION_FAILURE),
        NumberOfBytes,
        Tag);
}

_IRQL_requires_max_(APC_LEVEL)
__drv_preferredFunction(ExAllocateFromNPagedLookasideList, "The FsRtlAllocateResource routine is obsolete, but is exported to support existing driver binaries. Use ExAllocateFromNPagedLookasideList and ExInitializeResourceLite instead.")
PERESOURCE
NTAPI
FsRtlAllocateResource (
    VOID
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
NTAPI
FsRtlAreNamesEqual (
    _In_ PCUNICODE_STRING ConstantNameA,
    _In_ PCUNICODE_STRING ConstantNameB,
    _In_ BOOLEAN IgnoreCase,
    _In_reads_opt_(0x10000) PCWCH UpcaseTable
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlAreThereCurrentOrInProgressFileLocks (
    _In_ PFILE_LOCK FileLock
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlAreThereWaitingFileLocks (
    _In_ PFILE_LOCK FileLock
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlAreVolumeStartupApplicationsComplete(
    VOID
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlBalanceReads (
    _In_ PDEVICE_OBJECT TargetDevice
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_When_(Irp != NULL, _IRQL_requires_max_(PASSIVE_LEVEL))
_When_(Irp == NULL, _IRQL_requires_max_(APC_LEVEL))
NTSTATUS
NTAPI
FsRtlCancellableWaitForMultipleObjects(
    _In_ ULONG Count,
    _In_reads_(Count) PVOID ObjectArray[],
    _In_ WAIT_TYPE WaitType,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_opt_ PKWAIT_BLOCK WaitBlockArray,
    _In_opt_ PIRP Irp
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_When_(Irp!=NULL, _IRQL_requires_max_(PASSIVE_LEVEL))
_When_(Irp==NULL, _IRQL_requires_max_(APC_LEVEL))
NTSTATUS
NTAPI
FsRtlCancellableWaitForSingleObject(
    _In_ PVOID Object,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_opt_ PIRP Irp
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlChangeBackingFileObject (
    _In_opt_ PFILE_OBJECT CurrentFileObject,
    _In_ PFILE_OBJECT NewFileObject,
    _In_ FSRTL_CHANGE_BACKING_TYPE ChangeBackingType,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlCheckLockForOplockRequest (
    _In_ PFILE_LOCK FileLock,
    _In_ PLARGE_INTEGER AllocationSize
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlCheckLockForReadAccess (
    _In_ PFILE_LOCK FileLock,
    _In_ PIRP Irp
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlCheckLockForWriteAccess (
    _In_ PFILE_LOCK FileLock,
    _In_ PIRP Irp
    )
{
    __debugbreak();
    return FALSE;
}

_When_(CompletionRoutine != NULL, _Must_inspect_result_)
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlCheckOplock (
    _In_ POPLOCK Oplock,
    _In_ PIRP Irp,
    _In_opt_ PVOID Context,
    _In_opt_ POPLOCK_WAIT_COMPLETE_ROUTINE CompletionRoutine,
    _In_opt_ POPLOCK_FS_PREPOST_IRP PostIrpRoutine
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_When_(Flags | OPLOCK_FLAG_BACK_OUT_ATOMIC_OPLOCK, _Must_inspect_result_)
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlCheckOplockEx (
    _In_ POPLOCK Oplock,
    _In_ PIRP Irp,
    _In_ ULONG Flags,
    _In_opt_ PVOID Context,
    _In_opt_ POPLOCK_WAIT_COMPLETE_ROUTINE CompletionRoutine,
    _In_opt_ POPLOCK_FS_PREPOST_IRP PostIrpRoutine
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_When_(CompletionRoutine != NULL, _Must_inspect_result_)
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlCheckUpperOplock (
    _In_ POPLOCK Oplock,
    _In_ ULONG NewLowerOplockState,
    _In_opt_ PVOID CompletionRoutineContext,
    _In_opt_ POPLOCK_WAIT_COMPLETE_ROUTINE CompletionRoutine,
    _In_opt_ POPLOCK_FS_PREPOST_IRP PrePendRoutine,
    _In_ ULONG Flags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
_Function_class_(FAST_IO_READ)
BOOLEAN
NTAPI
FsRtlCopyRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _In_ ULONG LockKey,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ PDEVICE_OBJECT DeviceObject
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
_Function_class_(FAST_IO_WRITE)
BOOLEAN
NTAPI
FsRtlCopyWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _In_ ULONG LockKey,
    _In_reads_bytes_(Length) PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ PDEVICE_OBJECT DeviceObject
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlCreateSectionForDataScan(
    _Out_ PHANDLE SectionHandle,
    _Outptr_ PVOID *SectionObject,
    _Out_opt_ PLARGE_INTEGER SectionFileSize,
    _In_ PFILE_OBJECT FileObject,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_ ULONG Flags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlCurrentBatchOplock (
    _In_ POPLOCK Oplock
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlCurrentOplock (
    _In_ POPLOCK Oplock
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlCurrentOplockH (
    _In_ POPLOCK Oplock
    )
{
    __debugbreak();
    return FALSE;
}

_When_(Flags|FSRTL_ECP_LOOKASIDE_FLAG_NONPAGED_POOL, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(!(Flags|FSRTL_ECP_LOOKASIDE_FLAG_NONPAGED_POOL), _IRQL_requires_max_(APC_LEVEL))
VOID
NTAPI
FsRtlDeleteExtraCreateParameterLookasideList (
    _Inout_ PVOID Lookaside,
    _In_ FSRTL_ECP_LOOKASIDE_FLAGS Flags
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlDeleteKeyFromTunnelCache (
    _Inout_ TUNNEL *Cache,
    _In_ ULONGLONG DirectoryKey
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlDeleteTunnelCache (
    _Inout_ TUNNEL *Cache
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlDeregisterUncProvider(
    _In_ HANDLE Handle
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlDismountComplete (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ NTSTATUS DismountStatus
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlDissectDbcs (
    _In_ ANSI_STRING Path,
    _Out_ PANSI_STRING FirstName,
    _Out_ PANSI_STRING RemainingName
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlDissectName (
    _In_ UNICODE_STRING Path,
    _Out_ PUNICODE_STRING FirstName,
    _Out_ PUNICODE_STRING RemainingName
    )
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlDoesDbcsContainWildCards (
    _In_ PANSI_STRING Name
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlDoesNameContainWildCards (
    _In_ PUNICODE_STRING Name
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlFastCheckLockForRead (
    _In_ PFILE_LOCK FileLock,
    _In_ PLARGE_INTEGER StartingByte,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key,
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID ProcessId
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlFastCheckLockForWrite (
    _In_ PFILE_LOCK FileLock,
    _In_ PLARGE_INTEGER StartingByte,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key,
    _In_ PFILE_OBJECT FileObject, // DDK: PVOID
    _In_ PVOID ProcessId)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlFastUnlockAll (
    _In_ PFILE_LOCK FileLock,
    _In_ PFILE_OBJECT FileObject,
    _In_ PEPROCESS ProcessId,
    _In_opt_ PVOID Context
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlFastUnlockAllByKey (
    _In_ PFILE_LOCK FileLock,
    _In_ PFILE_OBJECT FileObject,
    _In_ PEPROCESS ProcessId,
    _In_ ULONG Key,
    _In_opt_ PVOID Context
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlFastUnlockSingle (
    _In_ PFILE_LOCK FileLock,
    _In_ PFILE_OBJECT FileObject,
    _In_ LARGE_INTEGER UNALIGNED *FileOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ PEPROCESS ProcessId,
    _In_ ULONG Key,
    _In_opt_ PVOID Context,
    _In_ BOOLEAN AlreadySynchronized
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlFindExtraCreateParameter (
    _In_ PECP_LIST EcpList,
    _In_ LPCGUID EcpType,
    _Outptr_opt_ PVOID *EcpContext,
    _Out_opt_ ULONG *EcpContextSize
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_At_(ShortName->MaximumLength, _In_range_(>=,8+1+3))
_Unchanged_(ShortName->MaximumLength)
_Unchanged_(ShortName->Buffer)
_When_(_Old_(LongName->Buffer) != LongName->Buffer, _At_(LongName->Buffer, __drv_allocatesMem(Mem)))
_At_(LongName->Buffer, _Must_inspect_result_)
_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlFindInTunnelCache (
    _In_ TUNNEL *Cache,
    _In_ ULONGLONG DirectoryKey,
    _In_ UNICODE_STRING *Name,
    _Inout_ UNICODE_STRING *ShortName,
    _Inout_ UNICODE_STRING *LongName,
    _Inout_ ULONG  *DataLength,
    _Out_writes_bytes_to_(*DataLength, *DataLength) VOID *Data
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlFreeExtraCreateParameter (
    _In_ PVOID EcpContext
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlFreeExtraCreateParameterList (
    _In_ PECP_LIST EcpList
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlFreeFileLock (
    _In_ PFILE_LOCK FileLock
    )
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlGetEcpListFromIrp (
    _In_ PIRP Irp,
    _Outptr_result_maybenull_ PECP_LIST *EcpList
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlGetFileNameInformation (
    _In_ PFILE_OBJECT File,
    _In_ ULONG NameOptions,
    _Out_ PUNICODE_STRING FileName,
    _Out_ PVOID *FileNameInformation
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlGetFileSize(
    _In_ PFILE_OBJECT FileObject,
    _Out_ PLARGE_INTEGER FileSize
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlGetIoAtEof (
    _Inout_ PFSRTL_EOF_LOCK EofLock,
    _In_ LONGLONG StartingVbo,
    _In_ LONGLONG ByteCount,
    _In_ BOOLEAN Wait,
    _Out_ PBOOLEAN DoingIoAtEof
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlGetNextBaseMcbEntry (
    _In_ PBASE_MCB Mcb,
    _In_ ULONG RunIndex,
    _Out_ PLONGLONG Vbn,
    _Out_ PLONGLONG Lbn,
    _Out_ PLONGLONG SectorCount
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlGetNextExtraCreateParameter (
    _In_ PECP_LIST EcpList,
    _In_opt_ PVOID CurrentEcpContext,
    _Out_opt_ LPGUID NextEcpType,
    _Outptr_opt_ PVOID *NextEcpContext,
    _Out_opt_ ULONG *NextEcpContextSize
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFILE_LOCK_INFO
NTAPI
FsRtlGetNextFileLock (
    _In_ PFILE_LOCK FileLock,
    _In_ BOOLEAN Restart
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlGetNextLargeMcbEntry (
    _In_ PLARGE_MCB Mcb,
    _In_ ULONG RunIndex,
    _Out_ PLONGLONG Vbn,
    _Out_ PLONGLONG Lbn,
    _Out_ PLONGLONG SectorCount
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlGetNextMcbEntry (
    _In_ PMCB Mcb,
    _In_ ULONG RunIndex,
    _Out_ PVBN Vbn,
    _Out_ PLBN Lbn,
    _Out_ PULONG SectorCount
    )
{
    __debugbreak();
    return FALSE;
}

NTSTATUS
NTAPI
FsRtlGetSectorSizeInformation (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_ PFILE_FS_SECTOR_SIZE_INFORMATION SectorSizeInfo
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlGetSupportedFeatures (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_ PULONG SupportedFeatures
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlGetVirtualDiskNestingLevel (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_ PULONG NestingLevel,
    _Out_opt_ PULONG NestingFlags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlHeatInit (
    _Inout_ PTIERING_HEAT_DATA TieringData,
    _In_ LPCGUID VolumeGuid,
    _In_opt_ LPCGUID ActivityId
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlHeatLogIo (
    _In_ PTIERING_HEAT_DATA TieringData,
    _In_ PIRP Irp,
    _In_ PFILE_ID_128 FileId,
    _In_ ULONG Flags,
    _In_opt_ LPCGUID ActivityId
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlHeatLogTierMove (
    _In_ PTIERING_HEAT_DATA TieringData,
    _In_ PFILE_ID_128 FileId,
    _In_ ULONGLONG Vbo,
    _In_ ULONG Length,
    _In_ ULONG Source,
    _In_ ULONG Destination,
    _In_opt_ LPCGUID ActivityId
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
FsRtlHeatUninit (
    _In_ PTIERING_HEAT_DATA TieringData,
    _In_ LPCGUID VolumeGuid
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlIncrementCcFastMdlReadWait(
    VOID
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlIncrementCcFastReadNoWait(
    VOID
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlIncrementCcFastReadNotPossible(
    VOID
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlIncrementCcFastReadResourceMiss(
    VOID
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlIncrementCcFastReadWait(
    VOID
    )
{
    __debugbreak();
}

_When_(Flags|FSRTL_ECP_LOOKASIDE_FLAG_NONPAGED_POOL, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(!(Flags|FSRTL_ECP_LOOKASIDE_FLAG_NONPAGED_POOL), _IRQL_requires_max_(APC_LEVEL))
VOID
NTAPI
FsRtlInitExtraCreateParameterLookasideList (
    _Inout_ PVOID Lookaside,
    _In_ FSRTL_ECP_LOOKASIDE_FLAGS Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlInitializeBaseMcb (
    _Out_ PBASE_MCB Mcb,
    _In_ POOL_TYPE PoolType
    )
{
    __debugbreak();
}

_When_(!Flags & MCB_FLAG_RAISE_ON_ALLOCATION_FAILURE, _Must_inspect_result_)
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlInitializeBaseMcbEx (
    _Out_ PBASE_MCB Mcb,
    _In_ POOL_TYPE PoolType,
    _In_ USHORT Flags
    )
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
FsRtlInitializeEofLock (
    _Out_ PFSRTL_EOF_LOCK EofLock,
    _In_ PFSRTL_ADVANCED_FCB_HEADER Header
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlInitializeExtraCreateParameter(
    _Out_ PECP_HEADER Ecp,
    _In_ ULONG EcpFlags,
    _In_opt_ PFSRTL_EXTRA_CREATE_PARAMETER_CLEANUP_CALLBACK CleanupCallback,
    _In_ ULONG TotalSize,
    _In_ LPCGUID EcpType,
    _In_opt_ PVOID ListAllocatedFrom
    )
{
    __debugbreak();
}

NTSTATUS
NTAPI
FsRtlInitializeExtraCreateParameterList (
    _Inout_ PECP_LIST EcpList
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlInitializeFileLock (
    _Out_ PFILE_LOCK FileLock,
    _In_opt_ PCOMPLETE_LOCK_IRP_ROUTINE CompleteLockIrpRoutine,
    _In_opt_ PUNLOCK_ROUTINE UnlockRoutine
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlInitializeLargeMcb (
    _Out_ PLARGE_MCB Mcb,
    _In_ POOL_TYPE PoolType
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
__drv_preferredFunction(FsRtlInitializeLargeMcb, "Obsolete")
VOID
NTAPI
FsRtlInitializeMcb (
    _Out_ PMCB Mcb,
    _In_ POOL_TYPE PoolType
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlInitializeOplock (
    _Out_ POPLOCK Oplock
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlInitializeTunnelCache (
    _Out_ TUNNEL *Cache
    )
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlInsertExtraCreateParameter (
    _Inout_ PECP_LIST EcpList,
    _Inout_ PVOID EcpContext
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlInsertPerFileContext (
    _In_ PVOID* PerFileContextPointer,
    _In_ PFSRTL_PER_FILE_CONTEXT Ptr
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlInsertPerFileObjectContext (
    _In_ PFILE_OBJECT FileObject,
    _In_ PFSRTL_PER_FILEOBJECT_CONTEXT Ptr
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlInsertPerStreamContext (
    _In_ PFSRTL_ADVANCED_FCB_HEADER PerStreamContext,
    _In_ PFSRTL_PER_STREAM_CONTEXT Ptr
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlInsertReservedPerFileContext (
    _In_ PVOID* PerFileContextPointer,
    _In_ PFSRTL_PER_FILE_CONTEXT Ptr
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlInsertReservedPerStreamContext (
    _In_ PFSRTL_ADVANCED_FCB_HEADER AdvFcbHeader,
    _In_ PFSRTL_PER_STREAM_CONTEXT Ptr
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlIsDbcsInExpression (
    _In_ PANSI_STRING Expression,
    _In_ PANSI_STRING Name
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlIsEcpAcknowledged (
    _In_ PVOID EcpContext
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlIsEcpFromUserMode (
    _In_ PVOID EcpContext
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlIsFatDbcsLegal (
    _In_ ANSI_STRING DbcsName,
    _In_ BOOLEAN WildCardsPermissible,
    _In_ BOOLEAN PathNamePermissible,
    _In_ BOOLEAN LeadingBackslashPermissible
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlIsHpfsDbcsLegal (
    _In_ ANSI_STRING DbcsName,
    _In_ BOOLEAN WildCardsPermissible,
    _In_ BOOLEAN PathNamePermissible,
    _In_ BOOLEAN LeadingBackslashPermissible
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
NTAPI
FsRtlIsNameInExpression (
    _In_ PUNICODE_STRING Expression,
    _In_ PUNICODE_STRING Name,
    _In_ BOOLEAN IgnoreCase,
    _In_opt_ PWCH UpcaseTable
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
BOOLEAN
NTAPI
FsRtlIsNtstatusExpected (
    _In_ NTSTATUS Exception
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
LOGICAL
NTAPI
FsRtlIsPagingFile (
    _In_ PFILE_OBJECT FileObject
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
LOGICAL
NTAPI
FsRtlIsSystemPagingFile (
    _In_ PFILE_OBJECT FileObject
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
BOOLEAN
NTAPI
FsRtlIsTotalDeviceFailure(
    _In_ NTSTATUS Status
    )
{
    __debugbreak();
    return FALSE;
}

NTSTATUS
NTAPI
FsRtlIssueDeviceIoControl (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG IoCtl,
    _In_ UCHAR Flags,
    _In_opt_ PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _In_opt_ PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_opt_ PULONG_PTR IosbInformation
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlKernelFsControlFile(
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG FsControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_ PULONG RetOutputBufferSize
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlLogCcFlushError(
    _In_ PUNICODE_STRING FileName,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ NTSTATUS FlushError,
    _In_ ULONG Flags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupBaseMcbEntry (
    _In_ PBASE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _Out_opt_ PLONGLONG Lbn,
    _Out_opt_ PLONGLONG SectorCountFromLbn,
    _Out_opt_ PLONGLONG StartingLbn,
    _Out_opt_ PLONGLONG SectorCountFromStartingLbn,
    _Out_opt_ PULONG Index
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupLargeMcbEntry (
    _In_ PLARGE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _Out_opt_ PLONGLONG Lbn,
    _Out_opt_ PLONGLONG SectorCountFromLbn,
    _Out_opt_ PLONGLONG StartingLbn,
    _Out_opt_ PLONGLONG SectorCountFromStartingLbn,
    _Out_opt_ PULONG Index
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupLastBaseMcbEntry (
    _In_ PBASE_MCB Mcb,
    _Out_ PLONGLONG Vbn,
    _Out_ PLONGLONG Lbn
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupLastBaseMcbEntryAndIndex (
    _In_ PBASE_MCB OpaqueMcb,
    _Inout_ PLONGLONG LargeVbn,
    _Inout_ PLONGLONG LargeLbn,
    _Inout_ PULONG Index
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupLastLargeMcbEntry (
    _In_ PLARGE_MCB Mcb,
    _Out_ PLONGLONG Vbn,
    _Out_ PLONGLONG Lbn
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupLastLargeMcbEntryAndIndex (
    _In_ PLARGE_MCB OpaqueMcb,
    _Out_ PLONGLONG LargeVbn,
    _Out_ PLONGLONG LargeLbn,
    _Out_ PULONG Index
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupLastMcbEntry (
    _In_ PMCB Mcb,
    _Out_ PVBN Vbn,
    _Out_ PLBN Lbn
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlLookupMcbEntry (
    _In_ PMCB Mcb,
    _In_ VBN Vbn,
    _Out_ PLBN Lbn,
    _Out_opt_ PULONG SectorCount,
    _Out_ PULONG Index
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_FILE_CONTEXT
NTAPI
FsRtlLookupPerFileContext (
    _In_ PVOID* PerFileContextPointer,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_FILEOBJECT_CONTEXT
NTAPI
FsRtlLookupPerFileObjectContext (
    _In_ PFILE_OBJECT FileObject,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_STREAM_CONTEXT
NTAPI
FsRtlLookupPerStreamContextInternal (
    _In_ PFSRTL_ADVANCED_FCB_HEADER StreamContext,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_FILE_CONTEXT
NTAPI
FsRtlLookupReservedPerFileContext (
    _In_ PVOID* PerFileContextPointer,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_STREAM_CONTEXT
NTAPI
FsRtlLookupReservedPerStreamContext (
    _In_ PFSRTL_ADVANCED_FCB_HEADER AdvFcbHeader,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
NTAPI
FsRtlMdlRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Outptr_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
NTAPI
FsRtlMdlReadComplete (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MdlChain
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Function_class_(FAST_IO_MDL_READ_COMPLETE)
BOOLEAN
NTAPI
FsRtlMdlReadCompleteDev (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MdlChain,
    _In_opt_ PDEVICE_OBJECT DeviceObject
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Function_class_(FAST_IO_MDL_READ)
BOOLEAN
NTAPI
FsRtlMdlReadDev (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Outptr_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_opt_ PDEVICE_OBJECT DeviceObject
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlMdlReadEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Outptr_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// reactos ntifs.h
BOOLEAN
NTAPI
FsRtlMdlWriteComplete (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PMDL MdlChain)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
_Function_class_(FAST_IO_MDL_WRITE_COMPLETE)
BOOLEAN
NTAPI
FsRtlMdlWriteCompleteDev (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PMDL MdlChain,
    _In_opt_ PDEVICE_OBJECT DeviceObject
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlMupGetProviderIdFromName(
    _In_    PCUNICODE_STRING    pProviderName,
    _Out_   PULONG32            pProviderId
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlMupGetProviderInfoFromFileObject(
    _In_                        PFILE_OBJECT    pFileObject,
    _In_                        ULONG           Level,
    _Out_writes_bytes_(*pBufferSize)  PVOID           pBuffer,
    _Inout_                     PULONG          pBufferSize
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlNormalizeNtstatus (
    _In_ NTSTATUS Exception,
    _In_ NTSTATUS GenericException
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// reactos ntifs.h
VOID
NTAPI
FsRtlNotifyChangeDirectory (
    _In_ PNOTIFY_SYNC NotifySync,
    _In_ PVOID FsContext,
    _In_ PSTRING FullDirectoryName,
    _In_ PLIST_ENTRY NotifyList,
    _In_ BOOLEAN WatchTree,
    _In_ ULONG CompletionFilter,
    _In_ PIRP NotifyIrp)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlNotifyCleanup (
    _In_ PNOTIFY_SYNC NotifySync,
    _In_ PLIST_ENTRY NotifyList,
    _In_ PVOID FsContext
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlNotifyCleanupAll (
    _In_ PNOTIFY_SYNC NotifySync,
    _In_ PLIST_ENTRY NotifyList
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlNotifyFilterChangeDirectory (
    _In_ PNOTIFY_SYNC NotifySync,
    _In_ PLIST_ENTRY NotifyList,
    _In_ PVOID FsContext,
    _In_ PSTRING FullDirectoryName,
    _In_ BOOLEAN WatchTree,
    _In_ BOOLEAN IgnoreBuffer,
    _In_ ULONG CompletionFilter,
    _In_opt_ PIRP NotifyIrp,
    _In_opt_ PCHECK_FOR_TRAVERSE_ACCESS TraverseCallback,
    _In_opt_ PSECURITY_SUBJECT_CONTEXT SubjectContext,
    _In_opt_ PFILTER_REPORT_CHANGE FilterCallback
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlNotifyFilterChangeDirectoryLite (
    _In_ PNOTIFY_SYNC *NotifySync,
    _In_ PLIST_ENTRY NotifyList,
    _In_opt_ PVOID FsContext,
    _In_ ULONG NotifyFlags,
    _In_ ULONG CompletionFilter,
    _In_opt_ PIRP NotifyIrp,
    _In_opt_ PCHECK_FOR_TRAVERSE_ACCESS TraverseCallback,
    _In_opt_ PSECURITY_SUBJECT_CONTEXT SubjectContext,
    _In_opt_ PFILTER_REPORT_CHANGE FilterCallback
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlNotifyFilterReportChange (
    _In_ PNOTIFY_SYNC NotifySync,
    _In_ PLIST_ENTRY NotifyList,
    _In_ PSTRING FullTargetName,
    _In_ USHORT TargetNameOffset,
    _In_opt_ PSTRING StreamName,
    _In_opt_ PSTRING NormalizedParentName,
    _In_ ULONG FilterMatch,
    _In_ ULONG Action,
    _In_opt_ PVOID TargetContext,
    _In_opt_ PVOID FilterContext
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlNotifyFilterReportChangeLite (
    _In_ PNOTIFY_SYNC *NotifySync,
    _In_ PLIST_ENTRY NotifyList,
    _In_ PUNICODE_STRING RelativeName,
    _In_opt_ PUNICODE_STRING StreamName,
    _In_ ULONG FilterMatch,
    _In_ ULONG Action,
    _In_opt_ PVOID TargetContext,
    _In_opt_ PVOID FilterContext,
    _In_ ULONG NotifyReportFlags
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(NotifyIrp == NULL, _At_(FullDirectoryName, _In_opt_))
_When_(NotifyIrp != NULL, _At_(FullDirectoryName, _In_))
VOID
NTAPI
FsRtlNotifyFullChangeDirectory (
    _In_ PNOTIFY_SYNC NotifySync,
    _In_ PLIST_ENTRY NotifyList,
    _In_ PVOID FsContext,
    PSTRING FullDirectoryName,
    _In_ BOOLEAN WatchTree,
    _In_ BOOLEAN IgnoreBuffer,
    _In_ ULONG CompletionFilter,
    _In_opt_ PIRP NotifyIrp,
    _In_opt_ PCHECK_FOR_TRAVERSE_ACCESS TraverseCallback,
    _In_opt_ PSECURITY_SUBJECT_CONTEXT SubjectContext
    )
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
FsRtlNotifyFullReportChange (
    _In_ PNOTIFY_SYNC NotifySync,
    _In_ PLIST_ENTRY NotifyList,
    _In_ PSTRING FullTargetName,
    _In_ USHORT TargetNameOffset,
    _In_opt_ PSTRING StreamName,
    _In_opt_ PSTRING NormalizedParentName,
    _In_ ULONG FilterMatch,
    _In_ ULONG Action,
    _In_opt_ PVOID TargetContext
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlNotifyInitializeSync (
    _Outptr_result_maybenull_ PNOTIFY_SYNC *NotifySync
    )
{
    __debugbreak();
}

// FsRtlNotifyReportChange

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlNotifyUninitializeSync (
    _Inout_ PNOTIFY_SYNC *NotifySync
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlNotifyVolumeEvent (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG EventCode
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
FsRtlNotifyVolumeEventEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG EventCode,
    _In_ PTARGET_DEVICE_CUSTOM_NOTIFICATION Event
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
FsRtlNumberOfRunsInBaseMcb (
    _In_ PBASE_MCB Mcb
    )
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
FsRtlNumberOfRunsInLargeMcb (
    _In_ PLARGE_MCB Mcb
    )
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
FsRtlNumberOfRunsInMcb (
    _In_ PMCB Mcb
    )
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlOplockBreakH (
    _In_ POPLOCK Oplock,
    _In_ PIRP Irp,
    _In_ ULONG Flags,
    _In_opt_ PVOID Context,
    _In_opt_ POPLOCK_WAIT_COMPLETE_ROUTINE CompletionRoutine,
    _In_opt_ POPLOCK_FS_PREPOST_IRP PostIrpRoutine
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlOplockBreakToNone(
    _Inout_ POPLOCK Oplock,
    _In_opt_ PIO_STACK_LOCATION IrpSp,
    _In_ PIRP Irp,
    _In_opt_ PVOID Context,
    _In_opt_ POPLOCK_WAIT_COMPLETE_ROUTINE CompletionRoutine,
    _In_opt_ POPLOCK_FS_PREPOST_IRP PostIrpRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlOplockBreakToNoneEx (
    _Inout_ POPLOCK Oplock,
    _In_ PIRP Irp,
    _In_ ULONG Flags,
    _In_opt_ PVOID Context,
    _In_opt_ POPLOCK_WAIT_COMPLETE_ROUTINE CompletionRoutine,
    _In_opt_ POPLOCK_FS_PREPOST_IRP PostIrpRoutine
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlOplockFsctrl (
    _In_ POPLOCK Oplock,
    _In_ PIRP Irp,
    _In_ ULONG OpenCount
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlOplockFsctrlEx (
    _In_ POPLOCK Oplock,
    _In_ PIRP Irp,
    _In_ ULONG OpenCount,
    _In_ ULONG Flags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlOplockIsFastIoPossible (
    _In_ POPLOCK Oplock
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlOplockIsSharedRequest(
    _In_ PIRP Irp
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlOplockKeysEqual (
    _In_opt_ PFILE_OBJECT Fo1,
    _In_opt_ PFILE_OBJECT Fo2
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
FsRtlPostPagingFileStackOverflow (
    _In_ PVOID Context,
    _In_ PKEVENT Event,
    _In_ PFSRTL_STACK_OVERFLOW_ROUTINE StackOverflowRoutine
    )
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
FsRtlPostStackOverflow (
    _In_ PVOID Context,
    _In_ PKEVENT Event,
    _In_ PFSRTL_STACK_OVERFLOW_ROUTINE StackOverflowRoutine
    )
{
    __debugbreak();
}

// FsRtlPrepareMdlWrite

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Function_class_(FAST_IO_PREPARE_MDL_WRITE)
BOOLEAN
NTAPI
FsRtlPrepareMdlWriteDev (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Outptr_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ PDEVICE_OBJECT DeviceObject
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlPrepareMdlWriteEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Outptr_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlPrepareToReuseEcp (
    _In_ PVOID EcpContext
    )
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
__drv_preferredFunction(FsRtlFastLock, "Obsolete")
BOOLEAN
NTAPI
FsRtlPrivateLock (
    _In_ PFILE_LOCK FileLock,
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ PEPROCESS ProcessId,
    _In_ ULONG Key,
    _In_ BOOLEAN FailImmediately,
    _In_ BOOLEAN ExclusiveLock,
    _Out_ PIO_STATUS_BLOCK Iosb,
    _In_opt_ PIRP Irp,
    _In_opt_ __drv_aliasesMem PVOID Context,
    _In_ BOOLEAN AlreadySynchronized
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlProcessFileLock (
    _In_ PFILE_LOCK FileLock,
    _In_ PIRP Irp,
    _In_opt_ PVOID Context
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlQueryCachedVdl(
    _In_ PFILE_OBJECT FileObject,
    _Out_ PLONGLONG Vdl
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlQueryKernelEaFile(
    _In_ PFILE_OBJECT FileObject,
    _Out_writes_bytes_to_(Length,*LengthReturned) PVOID ReturnedEaData,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_reads_bytes_opt_(EaListLength) PVOID EaList,
    _In_ ULONG EaListLength,
    _In_opt_ PULONG EaIndex,
    _In_ BOOLEAN RestartScan,
    _Out_opt_ PULONG LengthReturned
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

ULONG
NTAPI
FsRtlQueryMaximumVirtualDiskNestingLevel (
    VOID
    )
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
FsRtlRegisterFileSystemFilterCallbacks (
    _In_ struct _DRIVER_OBJECT *FilterDriverObject,
    _In_ PFS_FILTER_CALLBACKS Callbacks
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
FsRtlRegisterFltMgrCalls(
    _In_ PCFSRTL_FLTMGR_CALLS FltMgrFsrtlCalls
    )
{
    __debugbreak();
}

// FsRtlRegisterMupCalls

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlRegisterUncProvider(
    _Out_ PHANDLE MupHandle,
    _In_ PCUNICODE_STRING RedirectorDeviceName,
    _In_ BOOLEAN MailslotsSupported
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlRegisterUncProviderEx(
    _Out_ PHANDLE MupHandle,
    _In_ PCUNICODE_STRING RedirDevName,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ FSRTL_UNC_PROVIDER_FLAGS Flags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
FsRtlReleaseEofLock (
    _Inout_ PFSRTL_EOF_LOCK EofLock
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlReleaseFile (
    _In_ PFILE_OBJECT FileObject
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlReleaseFileNameInformation (
    _In_ PVOID FileNameInformation
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlReleaseHeaderMutex (
    _Inout_ PFSRTL_EOF_LOCK EofLock
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlRemoveBaseMcbEntry (
    _Inout_ PBASE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _In_ LONGLONG SectorCount
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlRemoveDotsFromPath(
    _Inout_updates_bytes_(PathLength) PWSTR OriginalString,
    _In_ USHORT PathLength,
    _Out_ USHORT *NewLength
)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlRemoveExtraCreateParameter (
    _Inout_ PECP_LIST EcpList,
    _In_ LPCGUID EcpType,
    _Outptr_ PVOID *EcpContext,
    _Out_opt_ ULONG *EcpContextSize
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlRemoveLargeMcbEntry (
    _Inout_ PLARGE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _In_ LONGLONG SectorCount
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlRemoveMcbEntry (
    _Inout_ PMCB Mcb,
    _In_ VBN Vbn,
    _In_ ULONG SectorCount
    )
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_FILE_CONTEXT
NTAPI
FsRtlRemovePerFileContext (
    _In_ PVOID* PerFileContextPointer,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_FILEOBJECT_CONTEXT
NTAPI
FsRtlRemovePerFileObjectContext (
    _In_ PFILE_OBJECT FileObject,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_STREAM_CONTEXT
NTAPI
FsRtlRemovePerStreamContext (
    _In_ PFSRTL_ADVANCED_FCB_HEADER StreamContext,
    _In_opt_ PVOID OwnerId,
    _In_opt_ PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_FILE_CONTEXT
NTAPI
FsRtlRemoveReservedPerFileContext (
    __in PVOID* PerFileContextPointer,
    __in_opt PVOID OwnerId,
    __in_opt PVOID InstanceId
    )
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PFSRTL_PER_STREAM_CONTEXT
NTAPI
FsRtlRemoveReservedPerStreamContext (
    __in PFSRTL_ADVANCED_FCB_HEADER AdvFcbHeader,
    __in_opt PVOID OwnerId,
    __in_opt PVOID InstanceId
  )
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlResetBaseMcb (
    _Out_ PBASE_MCB Mcb
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlResetLargeMcb (
    _Inout_ PLARGE_MCB Mcb,
    _In_ BOOLEAN SelfSynchronized
    )
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlSendModernAppTermination (
    _In_reads_bytes_opt_(PidListSize) PULONG PidList,
    _In_ ULONG PidListSize,
    _In_ FSRTL_APP_TERMINATE_REASON Reason
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlSetDriverBacking(
    _In_ PDRIVER_OBJECT DriverObj,
    _In_ ULONG Flags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlSetEcpListIntoIrp (
    _Inout_ PIRP Irp,
    _In_ PECP_LIST EcpList
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
FsRtlSetKernelEaFile (
    _In_ PFILE_OBJECT FileObject,
    _In_reads_bytes_(Length) PVOID EaBuffer,
    _In_ ULONG Length
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlSplitBaseMcb (
    _Inout_ PBASE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _In_ LONGLONG Amount
    )
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
FsRtlSplitLargeMcb (
    _Inout_ PLARGE_MCB Mcb,
    _In_ LONGLONG Vbn,
    _In_ LONGLONG Amount
    )
{
    __debugbreak();
    return FALSE;
}

// FsRtlSyncVolumes

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlTeardownPerFileContexts (
    _In_ PVOID* PerFileContextPointer
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlTeardownPerStreamContexts (
    _In_ PFSRTL_ADVANCED_FCB_HEADER AdvancedHeader
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlTruncateBaseMcb (
    _Inout_ PBASE_MCB Mcb,
    _In_ LONGLONG Vbn
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlTruncateLargeMcb (
    _Inout_ PLARGE_MCB Mcb,
    _In_ LONGLONG Vbn
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlTruncateMcb (
    _Inout_ PMCB Mcb,
    _In_ VBN Vbn
    )
{
    __debugbreak();
}

BOOLEAN
NTAPI
FsRtlTryToAcquireHeaderMutex (
    _Inout_ PFSRTL_EOF_LOCK EofLock
    )
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlUninitializeBaseMcb (
    _In_ PBASE_MCB Mcb
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlUninitializeFileLock (
    _Inout_ PFILE_LOCK FileLock
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlUninitializeLargeMcb (
    _Inout_ PLARGE_MCB Mcb
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlUninitializeMcb (
    _Inout_ PMCB Mcb
    )
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
FsRtlUninitializeOplock (
    _Inout_ POPLOCK Oplock
    )
{
    __debugbreak();
}

VOID
NTAPI
FsRtlUpdateDiskCounters (
    _In_ ULONG64 BytesRead,
    _In_ ULONG64 BytesWritten
    )
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
FsRtlUpperOplockFsctrl (
    _In_ POPLOCK Oplock,
    _In_ PIRP Irp,
    _In_ ULONG OpenCount,
    _In_ ULONG LowerOplockState,
    _In_ ULONG Flags
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
FsRtlValidateReparsePointBuffer (
    _In_ ULONG BufferLength,
    _In_reads_bytes_(BufferLength) PREPARSE_DATA_BUFFER ReparseBuffer
)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

