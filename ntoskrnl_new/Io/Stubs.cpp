
#include "Io.hpp"

#define BUILD_WOW64_ENABLED 1

extern "C" {
// Ob:
typedef struct _OBJECT_TYPE *POBJECT_TYPE;
typedef struct _OBJECT_NAME_INFORMATION *POBJECT_NAME_INFORMATION;
typedef struct _GENERIC_MAPPING *PGENERIC_MAPPING;

// Ex:
typedef struct _EPROCESS *PEPROCESS;

// Se:
typedef struct _SID *PSID;

// Cm:
typedef struct _CM_RESOURCE_LIST *PCM_RESOURCE_LIST;

// Mm:
typedef struct _MDL *PMDL;

// Wmi:
typedef PVOID WMI_NOTIFICATION_CALLBACK; /// FIXME

// Pnp:
typedef struct _PNP_DEPENDENCY_PATH_TYPE *PPNP_DEPENDENCY_PATH_TYPE;

///

POBJECT_TYPE IoAdapterObjectType;
POBJECT_TYPE IoCompletionObjectType;
POBJECT_TYPE IoDeviceHandlerObjectType;
POBJECT_TYPE IoDeviceObjectType;
POBJECT_TYPE IoDriverObjectType;
POBJECT_TYPE IoFileObjectType;
ULONG IoDeviceHandlerObjectSize;
ULONG IoReadOperationCount;
LARGE_INTEGER IoReadTransferCount;
KSPIN_LOCK IoStatisticsLock;
ULONG IoWriteOperationCount;
LARGE_INTEGER IoWriteTransferCount;

// ntosp.h
_Acquires_lock_(_Global_cancel_spin_lock_)
_Requires_lock_not_held_(_Global_cancel_spin_lock_)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_raises_(DISPATCH_LEVEL)
VOID
NTAPI
IoAcquireCancelSpinLock (
    _Out_ _At_(*Irql, _IRQL_saves_) PKIRQL Irql)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
IoAcquireRemoveLockEx (
    _Inout_ PIO_REMOVE_LOCK RemoveLock,
    _In_opt_ PVOID Tag,
    _In_ PCSTR File,
    _In_ ULONG Line,
    _In_ ULONG RemlockSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
IoAcquireVpbSpinLock (
    _Out_ PKIRQL Irql)
{
    __debugbreak();
}

// ntosifs.h
NTSTATUS
NTAPI
IoAdjustStackSizeForRedirection (
    _In_ PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice,
    _Out_opt_ PCCHAR ExtraStackLocations)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
__drv_preferredFunction("AllocateAdapterChannel","obsolete")
NTSTATUS
NTAPI
IoAllocateAdapterChannel (
    _In_ PADAPTER_OBJECT AdapterObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG NumberOfMapRegisters,
    _In_ PDRIVER_CONTROL ExecutionRoutine,
    _In_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
IoAllocateController (
    _In_ PCONTROLLER_OBJECT ControllerObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PDRIVER_CONTROL ExecutionRoutine,
    _In_opt_ PVOID Context)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Ret_range_(<=, 0)
NTSTATUS
NTAPI
IoAllocateDriverObjectExtension (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PVOID ClientIdentificationAddress,
    _In_ ULONG DriverObjectExtensionSize,
    _Post_ _At_(*DriverObjectExtension, _When_(return==0,
    __drv_aliasesMem __drv_allocatesMem(Mem) _Post_notnull_))
    _When_(return == 0, _Outptr_result_bytebuffer_(DriverObjectExtensionSize))
    PVOID *DriverObjectExtension)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
NTAPI
IoAllocateErrorLogEntry (
    _In_ PVOID IoObject,
    _In_ UCHAR EntrySize)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PIRP
NTAPI
IoAllocateIrp (
    _In_ CCHAR StackSize,
    _In_ BOOLEAN ChargeQuota)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PMDL
NTAPI
IoAllocateMdl (
    _In_opt_ __drv_aliasesMem PVOID VirtualAddress,
    _In_ ULONG Length,
    _In_ BOOLEAN SecondaryBuffer,
    _In_ BOOLEAN ChargeQuota,
    _Inout_opt_ PIRP Irp)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PIO_MINI_COMPLETION_PACKET_USER
NTAPI
IoAllocateMiniCompletionPacket (
    _In_ PIO_MINI_PACKET_CALLBACK_ROUTINE CallbackRoutine,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoAllocateSfioStreamIdentifier (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG Length,
    _In_ PVOID Signature,
    _Out_ PVOID *StreamIdentifier)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
__drv_allocatesMem(Mem)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
PIO_WORKITEM
NTAPI
IoAllocateWorkItem (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoApplyPriorityInfoThread (
    _In_ PIO_PRIORITY_INFO InputPriorityInfo,
    _Out_opt_ PIO_PRIORITY_INFO OutputPriorityInfo,
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("(see documentation)", "Obsolete")
NTSTATUS
NTAPI
IoAssignResources (
    _In_ PUNICODE_STRING RegistryPath,
    _In_opt_ PUNICODE_STRING DriverClassName,
    _In_ PDRIVER_OBJECT DriverObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ PIO_RESOURCE_REQUIREMENTS_LIST RequestedResources,
    _Inout_ PCM_RESOURCE_LIST *AllocatedResources)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<=, 0)
NTSTATUS
NTAPI
IoAttachDevice (
    _In_ _When_(return==0, __drv_aliasesMem)
        PDEVICE_OBJECT SourceDevice,
    _In_ PUNICODE_STRING TargetDevice,
    _Out_ PDEVICE_OBJECT *AttachedDevice)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoAttachDeviceToDeviceStackSafe (
    _In_ PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice,
    _Outptr_ PDEVICE_OBJECT *AttachedToDeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("IoAttachDeviceToDeviceStack", "Obsolete")
NTSTATUS
NTAPI
IoAttachDeviceByPointer (
    _In_ PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PDEVICE_OBJECT
NTAPI
IoAttachDeviceToDeviceStack (
    _In_ _When_(return!=0, __drv_aliasesMem)
        PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoBoostThreadIo (
    _In_ PETHREAD Thread,
    _In_ IO_PRIORITY_HINT TargetPriority,
    _In_ BOOLEAN Unboost,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(DISPATCH_LEVEL)
PIRP
NTAPI
IoBuildAsynchronousFsdRequest (
    _In_ ULONG MajorFunction,
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_opt_ PVOID Buffer,
    _In_opt_ ULONG Length,
    _In_opt_ PLARGE_INTEGER StartingOffset,
    _In_opt_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(PASSIVE_LEVEL)
PIRP
NTAPI
IoBuildDeviceIoControlRequest (
    _In_ ULONG IoControlCode,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ PVOID InputBuffer,
    _In_  ULONG InputBufferLength,
    _Out_opt_ PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _In_ BOOLEAN InternalDeviceIoControl,
    _In_opt_ PKEVENT Event,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoBuildPartialMdl (
    _In_ PMDL SourceMdl,
    _Inout_ PMDL TargetMdl,
    _Inout_ PVOID VirtualAddress,
    _In_ ULONG Length)
{
    __debugbreak();
}

// ntosp.h
_When_(MajorFunction == IRP_MJ_WRITE, _At_(Buffer, _In_))
_When_(MajorFunction == IRP_MJ_READ, _At_(Buffer, _Out_))
_When_(MajorFunction != IRP_MJ_READ && MajorFunction != IRP_MJ_WRITE, _At_(Buffer, _Pre_null_))
_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(PASSIVE_LEVEL)
PIRP
NTAPI
IoBuildSynchronousFsdRequest (
    _In_ ULONG MajorFunction,
    _In_ PDEVICE_OBJECT DeviceObject,
    PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER StartingOffset,
    _In_ PKEVENT Event,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return NULL;
}

// prototype from IofCallDriver
_IRQL_requires_max_(DISPATCH_LEVEL)
_Success_(TRUE)
NTSTATUS
NTAPI
IoCallDriver (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ __drv_aliasesMem PIRP Irp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoCancelFileOpen (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
IoCancelIrp (
    _In_ PIRP Irp)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
NTSTATUS
NTAPI
IoCheckDesiredAccess (
    _Inout_ PACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK GrantedAccess)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoCheckEaBufferValidity (
    _In_ PFILE_FULL_EA_INFORMATION EaBuffer,
    _In_ ULONG EaLength,
    _Out_ PULONG ErrorOffset)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoCheckFunctionAccess (
    _In_ ACCESS_MASK GrantedAccess,
    _In_ UCHAR MajorFunction,
    _In_ UCHAR MinorFunction,
    _In_ ULONG IoControlCode,
    _In_opt_ PVOID Arg1,
    _In_opt_ PVOID Arg2)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoCheckQuerySetFileInformation (
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG Length,
    _In_ BOOLEAN SetOperation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoCheckQuerySetVolumeInformation (
    _In_ FS_INFORMATION_CLASS FsInformationClass,
    _In_ ULONG Length,
    _In_ BOOLEAN SetOperation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoCheckQuotaBufferValidity (
    _In_ PFILE_QUOTA_INFORMATION QuotaBuffer,
    _In_ ULONG QuotaLength,
    _Out_ PULONG ErrorOffset)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
IoCheckShareAccess (
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess,
    _In_ BOOLEAN Update)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCheckShareAccessEx (
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess,
    _In_ BOOLEAN Update,
    _In_ PBOOLEAN WritePermission)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoClearActivityIdThread (
    _In_ LPCGUID OriginalId)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoClearDependency (
    _In_ PDEVICE_OBJECT DependentPdo,
    _In_ PDEVICE_OBJECT ProviderPdo)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoClearIrpExtraCreateParameter (
    _Inout_ PIRP Irp)
{
    __debugbreak();
}

// copied from IofCompleteRequest(ptr long)
VOID
NTAPI
IoCompleteRequest (
    _In_ PIRP Irp,
    _In_ CCHAR PriorityBoost)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoConnectInterrupt (
    _Out_ PKINTERRUPT *InterruptObject,
    _In_ PKSERVICE_ROUTINE ServiceRoutine,
    _In_opt_ PVOID ServiceContext,
    _In_opt_ PKSPIN_LOCK SpinLock,
    _In_ ULONG Vector,
    _In_ KIRQL Irql,
    _In_ KIRQL SynchronizeIrql,
    _In_ KINTERRUPT_MODE InterruptMode,
    _In_ BOOLEAN ShareVector,
    _In_ KAFFINITY ProcessorEnableMask,
    _In_ BOOLEAN FloatingSave)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoConnectInterruptEx (
    _Inout_ PIO_CONNECT_INTERRUPT_PARAMETERS Parameters)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoConvertFileHandleToKernelHandle (
    _In_opt_ HANDLE Handle,
    _In_ KPROCESSOR_MODE PreviousMode,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OverrideAccessCheck,
    _Out_ HANDLE* KernelHandle
    )
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosifs.h
NTSTATUS
NTAPI
IoCopyDeviceObjectHint (
    _In_ PFILE_OBJECT SourceFile,
    _Inout_ PFILE_OBJECT TargetFile)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCreateArcName (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
PCONTROLLER_OBJECT
NTAPI
IoCreateController(
    _In_ ULONG Size)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<=, 0)
NTSTATUS
NTAPI
IoCreateDevice (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ ULONG DeviceExtensionSize,
    _In_opt_ PUNICODE_STRING DeviceName,
    _In_ DEVICE_TYPE DeviceType,
    _In_ ULONG DeviceCharacteristics,
    _In_ BOOLEAN Exclusive,
    _Outptr_result_nullonfailure_
    _At_(*DeviceObject,
        __drv_allocatesMem(Mem)
        _When_((((_In_function_class_(DRIVER_INITIALIZE))
               ||(_In_function_class_(DRIVER_DISPATCH)))),
             __drv_aliasesMem))
    PDEVICE_OBJECT *DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCreateDisk (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ struct _CREATE_DISK* Disk)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCreateDriver (
    _In_opt_ PUNICODE_STRING DriverName,
    _In_ PDRIVER_INITIALIZE InitializationFunction)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoCreateFile (
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG Disposition,
    _In_ ULONG CreateOptions,
    _In_opt_ PVOID EaBuffer,
    _In_ ULONG EaLength,
    _In_ CREATE_FILE_TYPE CreateFileType,
    _In_opt_ PVOID InternalParameters,
    _In_ ULONG Options)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCreateFileEx (
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG Disposition,
    _In_ ULONG CreateOptions,
    _In_opt_ PVOID EaBuffer,
    _In_ ULONG EaLength,
    _In_ CREATE_FILE_TYPE CreateFileType,
    _In_opt_ PVOID InternalParameters,
    _In_ ULONG Options,
    _In_opt_ PIO_DRIVER_CREATE_CONTEXT DriverContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCreateFileSpecifyDeviceObjectHint (
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG Disposition,
    _In_ ULONG CreateOptions,
    _In_opt_ PVOID EaBuffer,
    _In_ ULONG EaLength,
    _In_ CREATE_FILE_TYPE CreateFileType,
    _In_opt_ PVOID InternalParameters,
    _In_ ULONG Options,
    _In_opt_ PVOID DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
PKEVENT
NTAPI
IoCreateNotificationEvent (
    _In_ PUNICODE_STRING EventName,
    _Out_ PHANDLE EventHandle)
{
    __debugbreak();
    return NULL;
}

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
PFILE_OBJECT
NTAPI
IoCreateStreamFileObject (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return NULL;
}

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
PFILE_OBJECT
NTAPI
IoCreateStreamFileObjectEx (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _Out_opt_ PHANDLE FileHandle)
{
    __debugbreak();
    return NULL;
}

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoCreateStreamFileObjectEx2 (
    _In_ PIO_CREATE_STREAM_FILE_OPTIONS CreateOptions,
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _Out_ PFILE_OBJECT* StreamFileObject,
    _Out_opt_ PHANDLE FileHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
PFILE_OBJECT
NTAPI
IoCreateStreamFileObjectLite (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoCreateSymbolicLink (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ PUNICODE_STRING DeviceName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
PKEVENT
NTAPI
IoCreateSynchronizationEvent (
    _In_ PUNICODE_STRING EventName,
    _Out_ PHANDLE EventHandle)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_same_
_IRQL_requires_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoCreateSystemThread (
    _Inout_ PVOID IoObject,
    _Out_ PHANDLE ThreadHandle,
    _In_ ULONG DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ HANDLE ProcessHandle,
    _Out_opt_ PCLIENT_ID ClientId,
    _In_ PKSTART_ROUTINE StartRoutine,
    _In_opt_ PVOID StartContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoCreateUnprotectedSymbolicLink (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ PUNICODE_STRING DeviceName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCsqInitialize (
    _Out_ PIO_CSQ Csq,
    _In_ PIO_CSQ_INSERT_IRP CsqInsertIrp,
    _In_ PIO_CSQ_REMOVE_IRP CsqRemoveIrp,
    _In_ PIO_CSQ_PEEK_NEXT_IRP CsqPeekNextIrp,
    _In_ PIO_CSQ_ACQUIRE_LOCK CsqAcquireLock,
    _In_ PIO_CSQ_RELEASE_LOCK CsqReleaseLock,
    _In_ PIO_CSQ_COMPLETE_CANCELED_IRP CsqCompleteCanceledIrp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoCsqInitializeEx (
    _Out_ PIO_CSQ Csq,
    _In_ PIO_CSQ_INSERT_IRP_EX CsqInsertIrp,
    _In_ PIO_CSQ_REMOVE_IRP CsqRemoveIrp,
    _In_ PIO_CSQ_PEEK_NEXT_IRP CsqPeekNextIrp,
    _In_ PIO_CSQ_ACQUIRE_LOCK CsqAcquireLock,
    _In_ PIO_CSQ_RELEASE_LOCK CsqReleaseLock,
    _In_ PIO_CSQ_COMPLETE_CANCELED_IRP CsqCompleteCanceledIrp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoCsqInsertIrp (
    _Inout_ PIO_CSQ Csq,
    _Inout_ PIRP Irp,
    _Out_opt_ PIO_CSQ_IRP_CONTEXT Context)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoCsqInsertIrpEx (
    _Inout_ PIO_CSQ Csq,
    _Inout_ PIRP Irp,
    _Out_opt_ PIO_CSQ_IRP_CONTEXT Context,
    _In_opt_ PVOID InsertContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PIRP
NTAPI
IoCsqRemoveIrp (
    _Inout_ PIO_CSQ Csq,
    _Inout_ PIO_CSQ_IRP_CONTEXT Context)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PIRP
NTAPI
IoCsqRemoveNextIrp (
    _Inout_ PIO_CSQ Csq,
    _In_opt_ PVOID PeekContext)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoDecrementKeepAliveCount (
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoDeleteAllDependencyRelations (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoDeleteController (
    _In_ PCONTROLLER_OBJECT ControllerObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_Kernel_clear_do_init_(__yes)
VOID
NTAPI
IoDeleteDevice (
    _In_ __drv_freesMem(Mem) PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoDeleteDriver (
    _In_ PDRIVER_OBJECT DriverObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoDeleteSymbolicLink (
    _In_ PUNICODE_STRING SymbolicLinkName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoDetachDevice (
    _Inout_ PDEVICE_OBJECT TargetDevice)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoDisconnectInterrupt (
    _In_ PKINTERRUPT InterruptObject)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoDisconnectInterruptEx (
    _In_ PIO_DISCONNECT_INTERRUPT_PARAMETERS Parameters)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoDuplicateDependency (
    _In_ PDEVICE_OBJECT ProviderPdo,
    _In_ PDEVICE_OBJECT NewProviderPdo)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoEnqueueIrp (
    _In_ PIRP Irp)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoEnumerateDeviceObjectList (
    _In_  PDRIVER_OBJECT DriverObject,
    _Out_writes_bytes_to_opt_(DeviceObjectListSize,(*ActualNumberDeviceObjects)*sizeof(PDEVICE_OBJECT))
        PDEVICE_OBJECT *DeviceObjectList,
    _In_  ULONG DeviceObjectListSize,
    _Out_ PULONG ActualNumberDeviceObjects)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoEnumerateRegisteredFiltersList (
    _Out_writes_bytes_to_opt_(DriverObjectListSize,(*ActualNumberDriverObjects)*sizeof(PDRIVER_OBJECT)) PDRIVER_OBJECT *DriverObjectList,
    _In_ ULONG  DriverObjectListSize,
    _Out_ PULONG ActualNumberDriverObjects)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
BOOLEAN
NTAPI
IoFastQueryNetworkAttributes (
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG OpenOptions,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _Out_ PFILE_NETWORK_OPEN_INFORMATION Buffer)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
BOOLEAN
NTAPI
IoForwardIrpSynchronously (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
IoFreeController (
    _In_ PCONTROLLER_OBJECT ControllerObject)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoFreeErrorLogEntry (
    _In_ PVOID ElEntry)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoFreeIrp (
    _In_ __drv_freesMem(Mem) PIRP Irp)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoFreeMdl (
    PMDL Mdl)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoFreeMiniCompletionPacket (
    _Inout_ PIO_MINI_COMPLETION_PACKET_USER MiniPacket)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoFreeSfioStreamIdentifier (
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID Signature)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoFreeWorkItem (
    _In_ __drv_freesMem(Mem) PIO_WORKITEM IoWorkItem)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoGetActivityIdIrp (
    _In_ PIRP Irp,
    _Out_ LPGUID Guid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
LPCGUID
NTAPI
IoGetActivityIdThread (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetAffinityInterrupt (
    _In_ PKINTERRUPT InterruptObject,
    _Out_ PGROUP_AFFINITY GroupAffinity)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PDEVICE_OBJECT
NTAPI
IoGetAttachedDevice (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PDEVICE_OBJECT
NTAPI
IoGetAttachedDeviceReference (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PDEVICE_OBJECT
NTAPI
IoGetBaseFileSystemDeviceObject (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetBootDiskInformation (
    _Inout_ PBOOTDISK_INFORMATION BootDiskInformation,
    _In_ ULONG Size)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSTATUS
NTAPI
IoGetBootDiskInformationLite (
    _Outptr_ PBOOTDISK_INFORMATION_LITE *BootDiskInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}
#endif // NTDDI_VERSION >= NTDDI_VISTA

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
PCONFIGURATION_INFORMATION
NTAPI
IoGetConfigurationInformation (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetContainerInformation (
    _In_ IO_CONTAINER_INFORMATION_CLASS InformationClass,
    _In_opt_ PVOID ContainerObject,
    _Inout_updates_bytes_opt_(BufferLength) PVOID Buffer,
    _In_ ULONG BufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PEPROCESS
NTAPI
IoGetCurrentProcess (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PDEVICE_OBJECT
NTAPI
IoGetDeviceAttachmentBaseRef (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoGetDeviceInterfaceAlias (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ const GUID *AliasInterfaceClassGuid,
    _Out_
    _When_(return==0, _At_(AliasSymbolicLinkName->Buffer, __drv_allocatesMem(Mem)))
        PUNICODE_STRING AliasSymbolicLinkName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoGetDeviceInterfacePropertyData (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ const DEVPROPKEY *PropertyKey,
    _In_ LCID Lcid,
    _Reserved_ ULONG Flags,
    _In_ ULONG Size,
    _Out_writes_bytes_to_(Size, *RequiredSize) PVOID Data,
    _Out_ PULONG RequiredSize,
    _Out_ PDEVPROPTYPE Type)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoGetDeviceInterfaces (
    _In_ const GUID *InterfaceClassGuid,
    _In_opt_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ ULONG Flags,
    _Outptr_result_nullonfailure_
    _At_(*SymbolicLinkList, _When_(return==0, __drv_allocatesMem(Mem)))
        PZZWSTR *SymbolicLinkList)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoGetDeviceNumaNode (
    _In_ PDEVICE_OBJECT Pdo,
    _Out_ PUSHORT NodeNumber)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoGetDeviceObjectPointer (
    _In_ PUNICODE_STRING ObjectName,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PFILE_OBJECT *FileObject,
    _Out_ PDEVICE_OBJECT *DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetDeviceProperty (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ DEVICE_REGISTRY_PROPERTY DeviceProperty,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_opt_(BufferLength) PVOID PropertyBuffer,
    _Out_ _Deref_out_range_(<=, BufferLength) PULONG ResultLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoGetDevicePropertyData (
    _In_ PDEVICE_OBJECT Pdo,
    _In_ const DEVPROPKEY *PropertyKey,
    _In_ LCID Lcid,
    _Reserved_ ULONG Flags,
    _In_ ULONG Size,
    _Out_writes_bytes_to_(Size, *RequiredSize) PVOID Data,
    _Out_ PULONG RequiredSize,
    _Out_ PDEVPROPTYPE Type)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PDEVICE_OBJECT
NTAPI
IoGetDeviceToVerify (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetDiskDeviceObject (
    _In_ PDEVICE_OBJECT FileSystemDeviceObject,
    _Out_ PDEVICE_OBJECT *DiskDeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
struct _DMA_ADAPTER *
NTAPI
IoGetDmaAdapter (
    _In_opt_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ struct _DEVICE_DESCRIPTION *DeviceDescription,
    _Out_ _When_(return!=0, _Kernel_IoGetDmaAdapter_ _At_(*NumberOfMapRegisters, _Must_inspect_result_))
        PULONG NumberOfMapRegisters)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
__drv_aliasesMem
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
NTAPI
IoGetDriverObjectExtension (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PVOID ClientIdentificationAddress)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
PGENERIC_MAPPING
NTAPI
IoGetFileObjectGenericMapping (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetFsTrackOffsetState (
    _In_ PIRP Irp,
    _Out_ PIO_IRP_EXT_TRACK_OFFSET_HEADER *RetFsTrackOffsetBlob,
    _Out_ LONGLONG *RetTrackedOffset)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetFsZeroingOffset (
    _In_ PIRP Irp,
    _Out_ PULONG ZeroingOffset)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetGenericIrpExtension (
    _In_ PIRP Irp,
    _Out_writes_(GenericExtensionDataSize) PUCHAR GenericExtensionData,
    _In_ USHORT GenericExtensionDataSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
IoGetInitialStack (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PEPROCESS
NTAPI
IoGetInitiatorProcess (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
IO_PRIORITY_HINT
NTAPI
IoGetIoPriorityHint (
    _In_ PIRP Irp)
{
    __debugbreak();
    return (IO_PRIORITY_HINT)0;
}

// ntosp.h
NTSTATUS
NTAPI
IoGetIrpExtraCreateParameter (
    _In_ PIRP Irp,
    _Outptr_result_maybenull_ struct _ECP_LIST **ExtraCreateParameter)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PDEVICE_OBJECT
NTAPI
IoGetLowerDeviceObject (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
POPLOCK_KEY_ECP_CONTEXT
NTAPI
IoGetOplockKeyContext (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
POPLOCK_KEY_CONTEXT
NTAPI
IoGetOplockKeyContextEx (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
IO_PAGING_PRIORITY
FASTCALL
IoGetPagingIoPriority (
    _In_ PIRP Irp)
{
    __debugbreak();
    return (IO_PAGING_PRIORITY)0;
}

// ntosp.h
PDEVICE_OBJECT
NTAPI
IoGetRelatedDeviceObject (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PEPROCESS
NTAPI
IoGetRequestorProcess (
    _In_ PIRP Irp)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
ULONG
NTAPI
IoGetRequestorProcessId (
    _In_ PIRP Irp)
{
    __debugbreak();
    return 0;
}

// ntifs.h
NTSTATUS
NTAPI
IoGetRequestorSessionId (
    _In_ PIRP Irp,
    _Out_ PULONG pSessionId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PVOID
NTAPI
IoGetSfioStreamIdentifier (
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID Signature)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
IoGetStackLimits (
    _Out_ PULONG_PTR LowLimit,
    _Out_ PULONG_PTR HighLimit)
{
    __debugbreak();
}

// ntosifs.h
NTSTATUS
NTAPI
IoGetSymlinkSupportInformation (
    _Out_writes_bytes_(SupportInfoSize) PFILE_SYMLINK_SUPPORT_INFORMATION SupportInfo,
    _In_ ULONG SupportInfoSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PIRP
NTAPI
IoGetTopLevelIrp (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
PTXN_PARAMETER_BLOCK
NTAPI
IoGetTransactionParameterBlock (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
NTSTATUS
NTAPI
IoIncrementKeepAliveCount (
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoInitializeIrp (
    _Inout_ PIRP Irp,
    _In_ USHORT PacketSize,
    _In_ CCHAR StackSize)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoInitializeMiniCompletionPacket (
    _Inout_ PIO_MINI_COMPLETION_PACKET_USER MiniPacket,
    _In_ PIO_MINI_PACKET_CALLBACK_ROUTINE CallbackRoutine,
    _In_opt_ PVOID Context)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoInitializeRemoveLockEx (
    _Out_ PIO_REMOVE_LOCK Lock,
    _In_ ULONG AllocateTag,
    _In_ ULONG MaxLockedMinutes,
    _In_ ULONG HighWatermark,
    _In_ ULONG RemlockSize)
{
    __debugbreak();
}

// ntosp.h
#if defined(_AMD64_) || defined(_X86_)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoInitializeTimer (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIO_TIMER_ROUTINE TimerRoutine,
    _In_opt_ __drv_aliasesMem PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}
#endif

// ntosp.h
VOID
NTAPI
IoInitializeWorkItem (
    _In_ PVOID IoObject,
    _Out_ PIO_WORKITEM IoWorkItem)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoInvalidateDeviceRelations (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ DEVICE_RELATION_TYPE Type)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoInvalidateDeviceState (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject)
{
    __debugbreak();
}

// ntosp.h
#if BUILD_WOW64_ENABLED
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
IoIs32bitProcess (
    _In_opt_ PIRP Irp)
{
    __debugbreak();
    return FALSE;
}
#endif // BUILD_WOW64_ENABLED && defined(_WIN64)

// ntosp.h
BOOLEAN
NTAPI
IoIsActivityTracingEnabled (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// ntddk.h
BOOLEAN
NTAPI
IoIsFileObjectIgnoringSharing (
  _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return FALSE;
}

// ntddk.h
BOOLEAN
NTAPI
IoIsFileOriginRemote (
    _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return FALSE;
}

#if BUILD_WOW64_ENABLED
// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
IoIsInitiator32bitProcess (
    _In_ PIRP Irp)
{
    __debugbreak();
    return FALSE;
}
#endif // BUILD_WOW64_ENABLED && defined(_WIN64)

// ntifs.h
BOOLEAN
NTAPI
IoIsOperationSynchronous (
    _In_ PIRP Irp)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
BOOLEAN
NTAPI
IoIsSystemThread (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
LOGICAL
NTAPI
IoIsValidIrpStatus (
    _In_ NTSTATUS Status)
{
    __debugbreak();
    return FALSE;
}

#if defined(_X86_) || defined(_AMD64_)
// ntifs.h
BOOLEAN
NTAPI
IoIsValidNameGraftingBuffer (
    _In_ PIRP Irp,
    _In_ PREPARSE_DATA_BUFFER ReparseBuffer)
{
    __debugbreak();
    return FALSE;
}
#endif

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("RtlIsNtDdiVersionAvailable","Preferred")
BOOLEAN
NTAPI
IoIsWdmVersionAvailable (
    _When_(MajorVersion!=1&&MajorVersion!=6,
    _In_ __drv_reportError("MajorVersion must be 1 or 6")) UCHAR MajorVersion,
    _In_ _When_(MinorVersion!=0 && MinorVersion!=5 && MinorVersion!=16
                    && MinorVersion!=32 && MinorVersion!=48,
    __drv_reportError("MinorVersion must be 0, 0x5, 0x10, 0x20, or 0x30"))
    UCHAR MinorVersion)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
NTSTATUS
NTAPI
IoLoadCrashDumpDriver (
    _In_ PUNICODE_STRING DriverName,
    _In_ PIO_LOAD_CRASHDUMP_PARAMS LoadCrashDumpParams,
    _Inout_ PIO_LOAD_CRASHDUMP_RESULT LoadCrashDumpResult)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PIRP
NTAPI
IoMakeAssociatedIrp (
    _In_ PIRP Irp,
    _In_ CCHAR StackSize)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoOpenDeviceInterfaceRegistryKey (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE DeviceInterfaceKey)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoOpenDeviceRegistryKey (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG DevInstKeyType,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE DevInstRegKey)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoPageRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MemoryDescriptorList,
    _In_ PLARGE_INTEGER StartingOffset,
    _In_ PKEVENT Event,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoPropagateActivityIdToThread (
    _In_ PIRP Irp,
    _Out_ LPGUID PropagatedId,
    _Outptr_ LPCGUID *OriginalId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoPropagateIrpExtension (
    _In_ PIRP SourceIrp,
    _In_ PIRP TargetIrp,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoPropagateIrpExtensionEx (
    _In_ PIRP SourceIrp,
    _In_ PIRP TargetIrp,
    _In_ LONGLONG TrackedOffset,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("IoGetDeviceProperty", "Obsolete")
NTSTATUS
NTAPI
IoQueryDeviceDescription (
    _In_opt_ PINTERFACE_TYPE BusType,
    _In_opt_ PULONG BusNumber,
    _In_opt_ PCONFIGURATION_TYPE ControllerType,
    _In_opt_ PULONG ControllerNumber,
    _In_opt_ PCONFIGURATION_TYPE PeripheralType,
    _In_opt_ PULONG PeripheralNumber,
    _In_ PIO_QUERY_DEVICE_ROUTINE CalloutRoutine,
    _Inout_opt_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoQueryFileDosDeviceName (
    _In_ PFILE_OBJECT FileObject,
    _Out_ POBJECT_NAME_INFORMATION *ObjectNameInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoQueryFileInformation (
    _In_ PFILE_OBJECT FileObject,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG Length,
    _Out_ PVOID FileInformation,
    _Out_ PULONG ReturnedLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoQueryFullDriverPath (
    _In_ PDRIVER_OBJECT DriverObject,
    _Out_ PUNICODE_STRING FullPath)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//@ stdcall -stub IoQueryInterface(ptr ptr ptr ptr ptr ptr ptr)

// ntosp.h
NTSTATUS
NTAPI
IoQueryVolumeInformation (
    _In_ PFILE_OBJECT FileObject,
    _In_ FS_INFORMATION_CLASS FsInformationClass,
    _In_ ULONG Length,
    _Out_ PVOID FsInformation,
    _Out_ PULONG ReturnedLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoQueueThreadIrp (
    _In_ PIRP Irp)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoQueueWorkItem (
    _Inout_ __drv_aliasesMem PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoQueueWorkItemEx (
    _Inout_ __drv_aliasesMem PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE_EX WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context)
{
    __debugbreak();
}

// ntosifs.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
IoQueueWorkItemToNode (
    _Inout_ _When_(return != 0, __drv_aliasesMem) PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE_EX WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context,
    _In_ ULONG NodeNumber)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
IoRaiseHardError (
    _In_ PIRP Irp,
    _In_opt_ PVPB Vpb,
    _In_ PDEVICE_OBJECT RealDeviceObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
IoRaiseInformationalHardError (
    _In_ NTSTATUS ErrorStatus,
    _In_opt_ PUNICODE_STRING String,
    _In_opt_ PKTHREAD Thread)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
NTSTATUS
NTAPI
IoReadDiskSignature (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG BytesPerSector,
    _Out_ PDISK_SIGNATURE Signature)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntddk.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("IoReadPartitionTableEx", "Obsolete")
NTSTATUS
FASTCALL
IoReadPartitionTable (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ BOOLEAN ReturnRecognizedPartitions,
    _Out_ struct _DRIVE_LAYOUT_INFORMATION **PartitionBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoReadPartitionTableEx (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_ struct _DRIVE_LAYOUT_INFORMATION_EX** DriveLayout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PVOID
NTAPI
IoRegisterBootDriverCallback (
    _In_ PBOOT_DRIVER_CALLBACK_FUNCTION CallbackFunction,
    _In_opt_ PVOID CallbackContext)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoRegisterBootDriverReinitialization (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_REINITIALIZE DriverReinitializationRoutine,
    _In_opt_ PVOID Context)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoRegisterContainerNotification (
    _In_ IO_CONTAINER_NOTIFICATION_CLASS NotificationClass,
    _In_ PIO_CONTAINER_NOTIFICATION_FUNCTION CallbackFunction,
    _In_reads_bytes_opt_(NotificationInformationLength) PVOID NotificationInformation,
    _In_ ULONG NotificationInformationLength,
    _Out_ PVOID CallbackRegistration)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoRegisterDeviceInterface (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ CONST GUID *InterfaceClassGuid,
    _In_opt_ PUNICODE_STRING ReferenceString,
    _Out_ _When_(return==0,
                     _At_(SymbolicLinkName->Buffer, __drv_allocatesMem(Mem)))
    PUNICODE_STRING SymbolicLinkName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoRegisterDriverReinitialization (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_REINITIALIZE DriverReinitializationRoutine,
    _In_opt_ PVOID Context)
{
    __debugbreak();
}

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
IoRegisterFileSystem (
    _In_ __drv_aliasesMem PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}

// ntifs.h
NTSTATUS
NTAPI
IoRegisterFsRegistrationChange (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_FS_NOTIFICATION DriverNotificationRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoRegisterFsRegistrationChangeMountAware (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_FS_NOTIFICATION DriverNotificationRoutine,
    _In_ BOOLEAN SynchronizeWithMounts)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
IoRegisterIoTracking (
    _In_ PIO_TRACKING_SETTINGS IoTrackingSettings,
    _Outptr_ PVOID *IoTracker)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoRegisterLastChanceShutdownNotification (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoRegisterPlugPlayNotification (
    _In_ IO_NOTIFICATION_EVENT_CATEGORY EventCategory,
    _In_ ULONG EventCategoryFlags,
    _In_opt_ PVOID EventCategoryData,
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_NOTIFICATION_CALLBACK_ROUTINE CallbackRoutine,
    _Inout_opt_ __drv_aliasesMem PVOID Context,
    _Outptr_result_nullonfailure_
    _At_(*NotificationEntry,
        _When_(return==0, __drv_allocatesMem(Mem)))
    PVOID *NotificationEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoRegisterPriorityCallback (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_PRIORITY_CALLBACK Callback)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoRegisterShutdownNotification (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_Requires_lock_held_(_Global_cancel_spin_lock_)
_Releases_lock_(_Global_cancel_spin_lock_)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
IoReleaseCancelSpinLock (
    _In_ _IRQL_restores_ _IRQL_uses_cancel_ KIRQL Irql)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoReleaseRemoveLockAndWaitEx (
    _Inout_ PIO_REMOVE_LOCK RemoveLock,
    _In_opt_ PVOID Tag,
    _In_ ULONG RemlockSize)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoReleaseRemoveLockEx (
    _Inout_ PIO_REMOVE_LOCK RemoveLock,
    _In_opt_ PVOID Tag,
    _In_ ULONG RemlockSize)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoReleaseVpbSpinLock (
    _In_ KIRQL Irql)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoRemoveShareAccess (
    _In_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess)
{
    __debugbreak();
}

// ntifs.h
NTSTATUS
NTAPI
IoReplaceFileObjectName (
    _In_ PFILE_OBJECT FileObject,
    _In_reads_bytes_(FileNameLength) PWSTR NewFileName,
    _In_ USHORT FileNameLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoReplacePartitionUnit (
    _In_ PDEVICE_OBJECT TargetPdo,
    _In_ PDEVICE_OBJECT SparePdo,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoReportDetectedDevice (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ INTERFACE_TYPE LegacyBusType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _In_opt_ PCM_RESOURCE_LIST ResourceList,
    _In_opt_ PIO_RESOURCE_REQUIREMENTS_LIST ResourceRequirements,
    _In_ BOOLEAN ResourceAssigned,
    _Inout_ PDEVICE_OBJECT *DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//@ stdcall -stub IoReportHalResourceUsage(ptr ptr ptr long)

// ntosp.h
VOID
NTAPI
IoReportInterruptActive (
    _In_ PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS Parameters)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoReportInterruptInactive (
    _In_ PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS Parameters)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoReportResourceForDetection (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_reads_bytes_opt_(DriverListSize) PCM_RESOURCE_LIST DriverList,
    _In_opt_ ULONG DriverListSize,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _In_reads_bytes_opt_(DeviceListSize) PCM_RESOURCE_LIST DeviceList,
    _In_opt_ ULONG DeviceListSize,
    _Out_ PBOOLEAN ConflictDetected)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("IoReportResourceForDetection if needed", "Obsolete")
NTSTATUS
NTAPI
IoReportResourceUsage (
    _In_opt_ PUNICODE_STRING DriverClassName,
    _In_  PDRIVER_OBJECT DriverObject,
    _In_reads_bytes_opt_(DriverListSize) PCM_RESOURCE_LIST DriverList,
    _In_opt_ ULONG DriverListSize,
    _In_opt_  PDEVICE_OBJECT DeviceObject,
    _In_reads_bytes_opt_(DeviceListSize) PCM_RESOURCE_LIST DeviceList,
    _In_opt_ ULONG DeviceListSize,
    _In_  BOOLEAN OverrideConflict,
    _Out_ PBOOLEAN ConflictDetected)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoReportRootDevice (
    _In_ PDRIVER_OBJECT DriverObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoReportTargetDeviceChange (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ PVOID NotificationStructure)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
IoReportTargetDeviceChangeAsynchronous (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ PVOID NotificationStructure,
    _In_opt_ PDEVICE_CHANGE_COMPLETE_CALLBACK Callback,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoRequestDeviceEject (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoRequestDeviceEjectEx (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_opt_ PIO_DEVICE_EJECT_CALLBACK Callback,
    _In_opt_ PVOID Context,
    _In_opt_ PDRIVER_OBJECT DriverObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoRequestDeviceRemovalForReset (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoReserveDependency (
    _In_ PDEVICE_OBJECT DependentDevice,
    _In_ PCUNICODE_STRING ProviderId,
    _In_ ULONG DependencyTypes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoResolveDependency (
    _In_ PCUNICODE_STRING BindingId,
    _In_ PDEVICE_OBJECT Device)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoRetrievePriorityInfo (
    _In_opt_ PIRP Irp,
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PETHREAD Thread,
    _Inout_ PIO_PRIORITY_INFO PriorityInfo)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoReuseIrp (
    _Inout_ PIRP Irp,
    _In_ NTSTATUS Iostatus)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoSetActivityIdIrp (
    _Inout_ PIRP Irp,
    _In_opt_ LPCGUID Guid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
LPCGUID
NTAPI
IoSetActivityIdThread (
    _In_ LPCGUID ActivityId)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoSetCompletionRoutineEx (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp,
    _In_ PIO_COMPLETION_ROUTINE CompletionRoutine,
    _In_opt_ PVOID Context,
    _In_ BOOLEAN InvokeOnSuccess,
    _In_ BOOLEAN InvokeOnError,
    _In_ BOOLEAN InvokeOnCancel)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetDependency (
    _In_ PDEVICE_OBJECT DependentDevice,
    _In_ PDEVICE_OBJECT ProviderDevice,
    _In_ ULONG DependencyTypes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoSetDeviceInterfacePropertyData (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ CONST DEVPROPKEY *PropertyKey,
    _In_ LCID Lcid,
    _In_ ULONG Flags,
    _In_ DEVPROPTYPE Type,
    _In_ ULONG Size,
    _In_reads_bytes_opt_(Size) PVOID Data)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoSetDeviceInterfaceState (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ BOOLEAN Enable)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
IoSetDevicePropertyData (
    _In_ PDEVICE_OBJECT Pdo,
    _In_ CONST DEVPROPKEY *PropertyKey,
    _In_ LCID Lcid,
    _In_ ULONG Flags,
    _In_ DEVPROPTYPE Type,
    _In_ ULONG Size,
    _In_reads_bytes_opt_(Size) PVOID Data)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoSetDeviceToVerify (
    _In_ PETHREAD Thread,
    _In_opt_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}

// ntddk-h
NTSTATUS
NTAPI
IoSetFileObjectIgnoreSharing (
  _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntddk-h
NTSTATUS
NTAPI
IoSetFileOrigin (
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN Remote)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetFsTrackOffsetState (
    _Inout_ PIRP Irp,
    _In_ PIO_IRP_EXT_TRACK_OFFSET_HEADER FsTrackOffsetBlob,
    _In_ LONGLONG TrackedOffset)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetFsZeroingOffset (
    _Inout_ PIRP Irp,
    _In_ ULONG ZeroingOffset)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetFsZeroingOffsetRequired (
    _Inout_ PIRP Irp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetGenericIrpExtension (
    _In_ PIRP Irp,
    _In_reads_(GenericExtensionDataSize) PUCHAR GenericExtensionData,
    _In_ USHORT GenericExtensionDataSize,
    _In_ BOOLEAN OverwriteIfPresent)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoSetHardErrorOrVerifyDevice (
    _In_ PIRP Irp,
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoSetInformation (
    _In_ PFILE_OBJECT FileObject,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG Length,
    _In_ PVOID FileInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetIoCompletion (
    _In_ PVOID IoCompletion,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation,
    _In_ BOOLEAN Quota)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetIoCompletionEx (
    _In_ PVOID IoCompletion,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation,
    _In_ BOOLEAN Quota,
    _In_opt_ PIO_MINI_COMPLETION_PACKET_USER MiniPacket)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetIoPriorityHint (
    _In_ PIRP Irp,
    _In_ IO_PRIORITY_HINT PriorityHint)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosifs.h
NTSTATUS
NTAPI
IoSetIoPriorityHintIntoFileObject (
    _In_ PFILE_OBJECT FileObject,
    _In_ IO_PRIORITY_HINT PriorityHint)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosifs.h
NTSTATUS
NTAPI
IoSetIoPriorityHintIntoThread (
    _In_ PETHREAD Thread,
    _In_ IO_PRIORITY_HINT PriorityHint)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSetIrpExtraCreateParameter (
    _Inout_ PIRP Irp,
    _In_ struct _ECP_LIST *ExtraCreateParameter)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoSetMasterIrpStatus (
    _Inout_ PIRP MasterIrp,
    _In_ NTSTATUS Status)
{
    __debugbreak();
}

// ntifs.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("IoSetPartitionInformationEx", "Obsolete")
NTSTATUS
FASTCALL
IoSetPartitionInformation (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG PartitionNumber,
    _In_ ULONG PartitionType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoSetPartitionInformationEx (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG PartitionNumber,
    _In_ struct _SET_PARTITION_INFORMATION_EX* PartitionInfo)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoSetShareAccess (
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Out_ PSHARE_ACCESS ShareAccess)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoSetShareAccessEx (
    _In_  ACCESS_MASK DesiredAccess,
    _In_  ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Out_ PSHARE_ACCESS ShareAccess,
    _In_ PBOOLEAN WritePermission)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoSetStartIoAttributes (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN DeferredStartIo,
    _In_ BOOLEAN NonCancelable)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoSetSystemPartition (
    _In_ PUNICODE_STRING VolumeNameString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
IoSetThreadHardErrorMode (
    _In_ BOOLEAN EnableHardErrors)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
VOID
NTAPI
IoSetTopLevelIrp (
    _In_opt_ PIRP Irp)
{
    __debugbreak();
}

// ntosp.h
USHORT
NTAPI
IoSizeofGenericIrpExtension (
    VOID)
{
    __debugbreak();
    return 0;
}

// ntosp.h
ULONG
NTAPI
IoSizeofWorkItem (
    VOID)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL) _IRQL_requires_min_(DISPATCH_LEVEL)
VOID
NTAPI
IoStartNextPacket (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN Cancelable)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoStartNextPacketByKey (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN Cancelable,
    _In_ ULONG Key)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoStartPacket (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp,
    _In_opt_ PULONG Key,
    _In_opt_ PDRIVER_CANCEL CancelFunction)
{
    __debugbreak();
}

#if defined(_AMD64_) || defined(_X86_)
// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoStartTimer (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoStopTimer (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}
#endif

// ntosp.h
NTSTATUS
NTAPI
IoSynchronousCallDriver (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoSynchronousInvalidateDeviceRelations (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ DEVICE_RELATION_TYPE Type)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
IoSynchronousPageWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MemoryDescriptorList,
    _In_ PLARGE_INTEGER StartingOffset,
    _In_ PKEVENT Event,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoTestDependency (
    _In_ PDEVICE_OBJECT Dependent,
    _In_ PDEVICE_OBJECT Provider,
    _Out_ PPNP_DEPENDENCY_PATH_TYPE PathType,
    _Out_ PULONG DependencyTypes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
PEPROCESS
NTAPI
IoThreadToProcess (
    _In_ PETHREAD Thread)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
VOID
NTAPI
IoTransferActivityId (
    _In_ LPCGUID ActivityId,
    _In_ LPCGUID RelatedActivityId)
{
    __debugbreak();
}

// ntosp.h
BOOLEAN
NTAPI
IoTranslateBusAddress (
    _In_ INTERFACE_TYPE InterfaceType,
    _In_ ULONG BusNumber,
    _In_ PHYSICAL_ADDRESS BusAddress,
    _Inout_ PULONG AddressSpace,
    _Out_ PPHYSICAL_ADDRESS TranslatedAddress)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
IoTryQueueWorkItem (
    _Inout_ __drv_when(return != 0, __drv_aliasesMem) PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE_EX WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
VOID
NTAPI
IoUninitializeWorkItem (
    _Inout_ PIO_WORKITEM IoWorkItem)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoUnregisterBootDriverCallback (
    _In_ PVOID CallbackHandle)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
IoUnregisterContainerNotification (
    _In_ PVOID CallbackRegistration)
{
    __debugbreak();
}

// ntifs.h
VOID
NTAPI
IoUnregisterFileSystem (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}

// ntifs.h
VOID
NTAPI
IoUnregisterFsRegistrationChange (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_FS_NOTIFICATION DriverNotificationRoutine)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
IoUnregisterIoTracking (
    _In_ PVOID IoTracker)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoUnregisterPlugPlayNotification (
    _In_ __drv_freesMem(Pool) PVOID NotificationEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoUnregisterPlugPlayNotificationEx (
    _In_ __drv_freesMem(Pool) PVOID NotificationEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
IoUnregisterPriorityCallback (
    _In_ PDRIVER_OBJECT DriverObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
IoUnregisterShutdownNotification (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
IoUpdateShareAccess (
    _In_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess)
{
    __debugbreak();
}

// ntosp.h
NTSTATUS
NTAPI
IoValidateDeviceIoControlAccess (
    _In_ PIRP Irp,
    _In_ ULONG RequiredAccess)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
IoVerifyPartitionTable (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN FixErrors)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoVerifyVolume (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN AllowRawMount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoVolumeDeviceToDosName (
    _In_ PVOID VolumeDeviceObject,
    _Out_ _When_(return==0, _At_(DosName->Buffer, __drv_allocatesMem(Mem)))
          PUNICODE_STRING DosName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoVolumeDeviceToGuid (
    _In_ PVOID VolumeDeviceObject,
    _Out_ GUID *Guid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoVolumeDeviceToGuidPath (
    _In_ PVOID VolumeDeviceObject,
    _Out_ _When_(return==0, _At_(DosName->Buffer, __drv_allocatesMem(Mem)))
          PUNICODE_STRING GuidPath)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoWMIAllocateInstanceIds (
    _In_ LPCGUID Guid,
    _In_ ULONG InstanceCount,
    _Out_ ULONG *FirstInstanceId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMIDeviceObjectToInstanceName (
    _In_ PVOID DataBlockObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_ PUNICODE_STRING InstanceName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
#if defined(_WIN64)
ULONG
NTAPI
IoWMIDeviceObjectToProviderId (
    _In_ PDEVICE_OBJECT DeviceObject)
{
    __debugbreak();
    return 0;
}
#else
#define IoWMIDeviceObjectToProviderId(DeviceObject) ((ULONG)(DeviceObject))
#endif

// ntosp.h
NTSTATUS
NTAPI
IoWMIExecuteMethod (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _In_ ULONG MethodId,
    _In_ ULONG InBufferSize,
    _Inout_ PULONG OutBufferSize,
    _Inout_updates_bytes_to_opt_(*OutBufferSize, InBufferSize) PUCHAR InOutBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMIHandleToInstanceName (
    _In_ PVOID DataBlockObject,
    _In_ HANDLE FileHandle,
    _Out_ PUNICODE_STRING InstanceName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMIOpenBlock (
    _In_ LPCGUID Guid,
    _In_ ULONG DesiredAccess,
    _Out_ PVOID *DataBlockObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMIQueryAllData (
    _In_ PVOID DataBlockObject,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMIQueryAllDataMultiple (
    _In_reads_(ObjectCount) PVOID *DataBlockObjectList,
    _In_ ULONG ObjectCount,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMIQuerySingleInstance (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMIQuerySingleInstanceMultiple (
    _In_reads_(ObjectCount) PVOID *DataBlockObjectList,
    _In_reads_(ObjectCount) PUNICODE_STRING InstanceNames,
    _In_ ULONG ObjectCount,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoWMIRegistrationControl (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG Action)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMISetNotificationCallback (
    _Inout_ PVOID Object,
    _In_ WMI_NOTIFICATION_CALLBACK Callback,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMISetSingleInstance (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _In_ ULONG Version,
    _In_ ULONG ValueBufferSize,
    _In_reads_bytes_(ValueBufferSize) PVOID ValueBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMISetSingleItem (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _In_ ULONG DataItemId,
    _In_ ULONG Version,
    _In_ ULONG ValueBufferSize,
    _In_reads_bytes_(ValueBufferSize) PVOID ValueBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
IoWMISuggestInstanceName (
    _In_opt_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_opt_ PUNICODE_STRING SymbolicLinkName,
    _In_ BOOLEAN CombineNames,
    _Out_ PUNICODE_STRING SuggestedInstanceName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Ret_range_(<=, 0)
NTSTATUS
NTAPI
IoWMIWriteEvent (
    _Inout_ _When_(return==0, __drv_aliasesMem) PVOID WnodeEventItem)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
LOGICAL
NTAPI
IoWithinStackLimits (
    _In_ ULONG_PTR RegionStart,
    _In_ SIZE_T RegionSize)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
IoWriteErrorLogEntry (
    _In_ PVOID ElEntry)
{
    __debugbreak();
}

// ntosp.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("IoWritePartitionTableEx", "Obsolete")
NTSTATUS
FASTCALL
IoWritePartitionTable (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG SectorsPerTrack,
    _In_ ULONG NumberOfHeads,
    _In_ struct _DRIVE_LAYOUT_INFORMATION *PartitionBuffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
IoWritePartitionTableEx (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_reads_(_Inexpressible_(FIELD_OFFSET(DRIVE_LAYOUT_INFORMATION_EX, PartitionEntry[0])))
        struct _DRIVE_LAYOUT_INFORMATION_EX* DriveLayout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Success_(TRUE)
NTSTATUS
FASTCALL
IofCallDriver (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ __drv_aliasesMem PIRP Irp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FASTCALL
IofCompleteRequest (
    _In_ PIRP Irp,
    _In_ CCHAR PriorityBoost)
{
    __debugbreak();
}

}; // extern "C"
