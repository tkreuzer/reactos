
#pragma once

#include "ntoskrnl.h"

#include "include/devpropdef.h"
#include "Ke/Ke.hpp"

/// FIXME!
#define __volatile /* specstrings.h */
#define _Enum_is_bitflag_
typedef struct _TXN_PARAMETER_BLOCK *PTXN_PARAMETER_BLOCK;
typedef struct _KEY_VALUE_FULL_INFORMATION *PKEY_VALUE_FULL_INFORMATION;
typedef struct _ETHREAD *PETHREAD;


//#define DEVICE_TYPE ULONG
typedef ULONG DEVICE_TYPE;

typedef USHORT IRQ_DEVICE_POLICY, *PIRQ_DEVICE_POLICY;

// wdm.h
typedef _Enum_is_bitflag_ enum _WORK_QUEUE_TYPE
{
    CriticalWorkQueue,
    DelayedWorkQueue,
    HyperCriticalWorkQueue,
    NormalWorkQueue,
    BackgroundWorkQueue,
    RealTimeWorkQueue,
    SuperCriticalWorkQueue,
    MaximumWorkQueue,
    CustomPriorityWorkQueue = 32
} WORK_QUEUE_TYPE;

// wdm.h
typedef enum _IO_SESSION_EVENT
{
    IoSessionEventIgnore = 0,
    IoSessionEventCreated,
    IoSessionEventTerminated,
    IoSessionEventConnected,
    IoSessionEventDisconnected,
    IoSessionEventLogon,
    IoSessionEventLogoff,
    IoSessionEventMax
} IO_SESSION_EVENT, *PIO_SESSION_EVENT;

// wdm.h
typedef enum _IO_SESSION_STATE
{
    IoSessionStateCreated = 1,
    IoSessionStateInitialized,
    IoSessionStateConnected,
    IoSessionStateDisconnected,
    IoSessionStateDisconnectedLoggedOn,
    IoSessionStateLoggedOn,
    IoSessionStateLoggedOff,
    IoSessionStateTerminated,
    IoSessionStateMax
} IO_SESSION_STATE, *PIO_SESSION_STATE;

typedef struct _IRP *PIRP;
typedef struct _DRIVER_OBJECT *PDRIVER_OBJECT;
typedef struct _DEVICE_OBJECT *PDEVICE_OBJECT;
typedef struct _FILE_OBJECT *PFILE_OBJECT;
typedef struct _ADAPTER_OBJECT *PADAPTER_OBJECT;
typedef struct _DRIVER_CONTROL *PDRIVER_CONTROL;
typedef struct _CONTROLLER_OBJECT *PCONTROLLER_OBJECT;
typedef struct _FILE_QUOTA_INFORMATION *PFILE_QUOTA_INFORMATION;
typedef struct _IO_WORKITEM *PIO_WORKITEM;
typedef PVOID PBOOT_DRIVER_CALLBACK_FUNCTION; /// FIXME
typedef PVOID PDRIVER_INITIALIZE; /// FIXME
struct _CREATE_DISK;
struct _DEVICE_DESCRIPTION;
struct _DRIVE_LAYOUT_INFORMATION;
struct _DRIVE_LAYOUT_INFORMATION_EX;
struct _SET_PARTITION_INFORMATION_EX;
struct _IO_MINI_COMPLETION_PACKET_USER;

// wdm.h
typedef enum _IO_PRIORITY_HINT
{
    IoPriorityVeryLow = 0,
    IoPriorityLow,
    IoPriorityNormal,
    IoPriorityHigh,
    IoPriorityCritical,
    MaxIoPriorityTypes
} IO_PRIORITY_HINT;

// wdm.h / ntosp.h
typedef enum _IO_PAGING_PRIORITY {
    IoPagingPriorityInvalid,
    IoPagingPriorityNormal,
    IoPagingPriorityHigh,
    IoPagingPriorityReserved1,
    IoPagingPriorityReserved2
} IO_PAGING_PRIORITY;

// wdm.h
typedef enum _INTERFACE_TYPE
{
    InterfaceTypeUndefined = -1,
    Internal,
    Isa,
    Eisa,
    MicroChannel,
    TurboChannel,
    PCIBus,
    VMEBus,
    NuBus,
    PCMCIABus,
    CBus,
    MPIBus,
    MPSABus,
    ProcessorInternal,
    InternalPowerBus,
    PNPISABus,
    PNPBus,
    Vmcs,
    ACPIBus,
    MaximumInterfaceType
} INTERFACE_TYPE, *PINTERFACE_TYPE;

// wdm.h
typedef enum _IRQ_PRIORITY
{
    IrqPriorityUndefined = 0,
    IrqPriorityLow,
    IrqPriorityNormal,
    IrqPriorityHigh
} IRQ_PRIORITY, *PIRQ_PRIORITY;

// wdm.h / ntosp.h
typedef enum _CREATE_FILE_TYPE
{
    CreateFileTypeNone,
    CreateFileTypeNamedPipe,
    CreateFileTypeMailslot
} CREATE_FILE_TYPE;

// wdm.h / ntosp.h
typedef enum _IO_CONTAINER_INFORMATION_CLASS
{
    IoSessionStateInformation,
    IoMaxContainerInformationClass
} IO_CONTAINER_INFORMATION_CLASS;

// wdm.h / ntosp.h
typedef enum _IO_CONTAINER_NOTIFICATION_CLASS
{
    IoSessionStateNotification,
    IoMaxContainerNotificationClass
} IO_CONTAINER_NOTIFICATION_CLASS;

// wdm.h / ntosp.h
typedef
NTSTATUS
(NTAPI *PIO_CONTAINER_NOTIFICATION_FUNCTION) (
    VOID);

// wdm.h / ntosp.h
typedef enum
{
    DevicePropertyDeviceDescription = 0x0 | __string_type,
    DevicePropertyHardwareID = 0x1 | __multiString_type,
    DevicePropertyCompatibleIDs = 0x2 | __multiString_type,
    DevicePropertyBootConfiguration = 0x3,
    DevicePropertyBootConfigurationTranslated = 0x4,
    DevicePropertyClassName = 0x5 | __string_type,
    DevicePropertyClassGuid = 0x6 | __string_type,
    DevicePropertyDriverKeyName = 0x7 | __string_type,
    DevicePropertyManufacturer = 0x8 | __string_type,
    DevicePropertyFriendlyName = 0x9 | __string_type,
    DevicePropertyLocationInformation = 0xa | __string_type,
    DevicePropertyPhysicalDeviceObjectName = 0xb | __string_type,
    DevicePropertyBusTypeGuid = 0xc | __guid_type,
    DevicePropertyLegacyBusType = 0xd,
    DevicePropertyBusNumber = 0xe,
    DevicePropertyEnumeratorName = 0xf | __string_type,
    DevicePropertyAddress = 0x10,
    DevicePropertyUINumber = 0x11,
    DevicePropertyInstallState = 0x12,
    DevicePropertyRemovalPolicy = 0x13,
    DevicePropertyResourceRequirements = 0x14,
    DevicePropertyAllocatedResources = 0x15,
    DevicePropertyContainerID = 0x16 | __string_type
} DEVICE_REGISTRY_PROPERTY;

// wdm.h / ntosp.h
typedef enum _DEVICE_RELATION_TYPE
{
    BusRelations,
    EjectionRelations,
    PowerRelations,
    RemovalRelations,
    TargetDeviceRelation,
    SingleBusRelations,
    TransportRelations
} DEVICE_RELATION_TYPE, *PDEVICE_RELATION_TYPE;

// wdm.h
typedef enum _FSINFOCLASS
{
    FileFsVolumeInformation = 1,
    FileFsLabelInformation = 2,
    FileFsSizeInformation = 3,
    FileFsDeviceInformation = 4,
    FileFsAttributeInformation = 5,
    FileFsControlInformation = 6,
    FileFsFullSizeInformation = 7,
    FileFsObjectIdInformation = 8,
    FileFsDriverPathInformation = 9,
    FileFsVolumeFlagsInformation = 10,
    FileFsSectorSizeInformation = 11,
    FileFsDataCopyInformation = 12,
    FileFsMaximumInformation
} FS_INFORMATION_CLASS, *PFS_INFORMATION_CLASS;

// wdm.h
typedef enum _FILE_INFORMATION_CLASS
{
    FileDirectoryInformation = 1,
    FileFullDirectoryInformation = 2,
    FileBothDirectoryInformation = 3,
    FileBasicInformation = 4,
    FileStandardInformation = 5,
    FileInternalInformation = 6,
    FileEaInformation = 7,
    FileAccessInformation = 8,
    FileNameInformation = 9,
    FileRenameInformation = 10,
    FileLinkInformation = 11,
    FileNamesInformation = 12,
    FileDispositionInformation = 13,
    FilePositionInformation = 14,
    FileFullEaInformation = 15,
    FileModeInformation = 16,
    FileAlignmentInformation = 17,
    FileAllInformation = 18,
    FileAllocationInformation = 19,
    FileEndOfFileInformation = 20,
    FileAlternateNameInformation = 21,
    FileStreamInformation = 22,
    FilePipeInformation = 23,
    FilePipeLocalInformation = 24,
    FilePipeRemoteInformation = 25,
    FileMailslotQueryInformation = 26,
    FileMailslotSetInformation = 27,
    FileCompressionInformation = 28,
    FileObjectIdInformation = 29,
    FileCompletionInformation = 30,
    FileMoveClusterInformation = 31,
    FileQuotaInformation = 32,
    FileReparsePointInformation = 33,
    FileNetworkOpenInformation = 34,
    FileAttributeTagInformation = 35,
    FileTrackingInformation = 36,
    FileIdBothDirectoryInformation = 37,
    FileIdFullDirectoryInformation = 38,
    FileValidDataLengthInformation = 39,
    FileShortNameInformation = 40,
    FileIoCompletionNotificationInformation = 41,
    FileIoStatusBlockRangeInformation = 42,
    FileIoPriorityHintInformation = 43,
    FileSfioReserveInformation = 44,
    FileSfioVolumeInformation = 45,
    FileHardLinkInformation = 46,
    FileProcessIdsUsingFileInformation = 47,
    FileNormalizedNameInformation = 48,
    FileNetworkPhysicalNameInformation = 49,
    FileIdGlobalTxDirectoryInformation = 50,
    FileIsRemoteDeviceInformation = 51,
    FileUnusedInformation = 52,
    FileNumaNodeInformation = 53,
    FileStandardLinkInformation = 54,
    FileRemoteProtocolInformation = 55,
    FileRenameInformationBypassAccessCheck = 56,
    FileLinkInformationBypassAccessCheck = 57,
    FileVolumeNameInformation = 58,
    FileIdInformation = 59,
    FileIdExtdDirectoryInformation = 60,
    FileReplaceCompletionInformation = 61,
    FileHardLinkFullIdInformation = 62,
    FileIdExtdBothDirectoryInformation = 63,
    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

// wdm.h
typedef struct _FILE_FULL_EA_INFORMATION
{
    ULONG NextEntryOffset;
    UCHAR Flags;
    UCHAR EaNameLength;
    USHORT EaValueLength;
    CHAR EaName[1];
} FILE_FULL_EA_INFORMATION, *PFILE_FULL_EA_INFORMATION;

// wdm.h
typedef struct _FILE_NETWORK_OPEN_INFORMATION
{
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG FileAttributes;
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;

// wdm.h
typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    } DUMMYUNIONNAME;
    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

// wdm.h / ntosp.h
typedef enum _IO_NOTIFICATION_EVENT_CATEGORY
{
    EventCategoryReserved,
    EventCategoryHardwareProfileChange,
    EventCategoryDeviceInterfaceChange,
    EventCategoryTargetDeviceChange
} IO_NOTIFICATION_EVENT_CATEGORY;

// wdm.h / ntosp.h
typedef
_Function_class_(DRIVER_NOTIFICATION_CALLBACK_ROUTINE)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
DRIVER_NOTIFICATION_CALLBACK_ROUTINE (
    _In_ PVOID NotificationStructure,
    _Inout_opt_ PVOID Context);
typedef DRIVER_NOTIFICATION_CALLBACK_ROUTINE
    *PDRIVER_NOTIFICATION_CALLBACK_ROUTINE;

// wdm.h / ntosp.h
_Function_class_(DRIVER_CANCEL)
_Requires_lock_held_(_Global_cancel_spin_lock_)
_Releases_lock_(_Global_cancel_spin_lock_)
_IRQL_requires_min_(DISPATCH_LEVEL)
_IRQL_requires_(DISPATCH_LEVEL)
typedef
VOID
NTAPI
DRIVER_CANCEL (
    _Inout_ struct _DEVICE_OBJECT *DeviceObject,
    _Inout_ _IRQL_uses_cancel_ struct _IRP *Irp);
typedef DRIVER_CANCEL *PDRIVER_CANCEL;

// wdm.h
typedef
VOID
(NTAPI *PIO_APC_ROUTINE) (
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG Reserved);

// wdm.h / ntosp.h
_Function_class_(IO_COMPLETION_ROUTINE)
_IRQL_requires_same_
_IRQL_requires_max_(DISPATCH_LEVEL)
typedef
NTSTATUS
NTAPI
IO_COMPLETION_ROUTINE (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp,
    _In_reads_opt_(_Inexpressible_("varies")) PVOID Context);
typedef IO_COMPLETION_ROUTINE *PIO_COMPLETION_ROUTINE;

// wdm.h / ntosp.h
typedef struct _SHARE_ACCESS
{
    ULONG OpenCount;
    ULONG Readers;
    ULONG Writers;
    ULONG Deleters;
    ULONG SharedRead;
    ULONG SharedWrite;
    ULONG SharedDelete;
} SHARE_ACCESS, *PSHARE_ACCESS;

// wdm.h / ntosp.h
typedef
_Function_class_(DEVICE_CHANGE_COMPLETE_CALLBACK)
_IRQL_requires_same_
VOID
NTAPI
DEVICE_CHANGE_COMPLETE_CALLBACK(
    _Inout_opt_ PVOID Context);
typedef DEVICE_CHANGE_COMPLETE_CALLBACK *PDEVICE_CHANGE_COMPLETE_CALLBACK;

// wdm.h / ntosp.h
typedef
VOID
(NTAPI *PIO_DEVICE_EJECT_CALLBACK)(
    _In_ NTSTATUS Status,
    _Inout_opt_ PVOID Context);

// wdm.h
typedef struct _IO_RESOURCE_DESCRIPTOR
{
    UCHAR Option;
    UCHAR Type;
    UCHAR ShareDisposition;
    UCHAR Spare1;
    USHORT Flags;
    USHORT Spare2;
    union
    {
        struct
        {
            ULONG Length;
            ULONG Alignment;
            PHYSICAL_ADDRESS MinimumAddress;
            PHYSICAL_ADDRESS MaximumAddress;
        } Port;
        struct
        {
            ULONG Length;
            ULONG Alignment;
            PHYSICAL_ADDRESS MinimumAddress;
            PHYSICAL_ADDRESS MaximumAddress;
        } Memory;
        struct
        {
            ULONG MinimumVector;
            ULONG MaximumVector;
#if defined(NT_PROCESSOR_GROUPS)
            IRQ_DEVICE_POLICY AffinityPolicy;
            USHORT Group;
#else
            IRQ_DEVICE_POLICY AffinityPolicy;
#endif
            IRQ_PRIORITY PriorityPolicy;
            KAFFINITY TargetedProcessors;
        } Interrupt;
        struct
        {
            ULONG MinimumChannel;
            ULONG MaximumChannel;
        } Dma;
        struct
        {
            ULONG RequestLine;
            ULONG Reserved;
            ULONG Channel;
            ULONG TransferWidth;
        } DmaV3;
        struct
        {
            ULONG Length;
            ULONG Alignment;
            PHYSICAL_ADDRESS MinimumAddress;
            PHYSICAL_ADDRESS MaximumAddress;
        } Generic;
        struct
        {
            ULONG Data[3];
        } DevicePrivate;
        struct
        {
            ULONG Length;
            ULONG MinBusNumber;
            ULONG MaxBusNumber;
            ULONG Reserved;
        } BusNumber;
        struct
        {
            ULONG Priority;
            ULONG Reserved1;
            ULONG Reserved2;
        } ConfigData;
        struct
        {
            ULONG Length40;
            ULONG Alignment40;
            PHYSICAL_ADDRESS MinimumAddress;
            PHYSICAL_ADDRESS MaximumAddress;
        } Memory40;
        struct
        {
            ULONG Length48;
            ULONG Alignment48;
            PHYSICAL_ADDRESS MinimumAddress;
            PHYSICAL_ADDRESS MaximumAddress;
        } Memory48;
        struct
        {
            ULONG Length64;
            ULONG Alignment64;
            PHYSICAL_ADDRESS MinimumAddress;
            PHYSICAL_ADDRESS MaximumAddress;
        } Memory64;
        struct
        {
            UCHAR Class;
            UCHAR Type;
            UCHAR Reserved1;
            UCHAR Reserved2;
            ULONG IdLowPart;
            ULONG IdHighPart;
        } Connection;
    } u;
} IO_RESOURCE_DESCRIPTOR, *PIO_RESOURCE_DESCRIPTOR;

// wdm.h
typedef struct _IO_RESOURCE_LIST
{
    USHORT Version;
    USHORT Revision;
    ULONG Count;
    IO_RESOURCE_DESCRIPTOR Descriptors[1];
} IO_RESOURCE_LIST, *PIO_RESOURCE_LIST;

// wdm.h
typedef struct _IO_RESOURCE_REQUIREMENTS_LIST
{
    ULONG ListSize;
    INTERFACE_TYPE InterfaceType;
    ULONG BusNumber;
    ULONG SlotNumber;
    ULONG Reserved[3];
    ULONG AlternativeLists;
    IO_RESOURCE_LIST List[1];
} IO_RESOURCE_REQUIREMENTS_LIST, *PIO_RESOURCE_REQUIREMENTS_LIST;

// wdm.h / ntosp.h
typedef struct _IO_CONNECT_INTERRUPT_FULLY_SPECIFIED_PARAMETERS
{
    _In_ PDEVICE_OBJECT PhysicalDeviceObject;
    _Out_ PKINTERRUPT *InterruptObject;
    _In_ PKSERVICE_ROUTINE ServiceRoutine;
    _In_ PVOID ServiceContext;
    _In_opt_ PKSPIN_LOCK SpinLock;
    _In_ KIRQL SynchronizeIrql;
    _In_ BOOLEAN FloatingSave;
    _In_ BOOLEAN ShareVector;
    _In_ ULONG Vector;
    _In_ KIRQL Irql;
    _In_ KINTERRUPT_MODE InterruptMode;
    _In_ KAFFINITY ProcessorEnableMask;
    _In_ USHORT Group;
} IO_CONNECT_INTERRUPT_FULLY_SPECIFIED_PARAMETERS,
  *PIO_CONNECT_INTERRUPT_FULLY_SPECIFIED_PARAMETERS;

// wdm.h / ntosp.h
typedef struct _IO_INTERRUPT_MESSAGE_INFO_ENTRY
{
    PHYSICAL_ADDRESS MessageAddress;
    KAFFINITY TargetProcessorSet;
    PKINTERRUPT InterruptObject;
    ULONG MessageData;
    ULONG Vector;
    KIRQL Irql;
    KINTERRUPT_MODE Mode;
    KINTERRUPT_POLARITY Polarity;
} IO_INTERRUPT_MESSAGE_INFO_ENTRY, *PIO_INTERRUPT_MESSAGE_INFO_ENTRY;

// wdm.h / ntosp.h
typedef struct _IO_INTERRUPT_MESSAGE_INFO
{
    KIRQL UnifiedIrql;
    ULONG MessageCount;
    IO_INTERRUPT_MESSAGE_INFO_ENTRY MessageInfo[1];
} IO_INTERRUPT_MESSAGE_INFO, *PIO_INTERRUPT_MESSAGE_INFO;

// wdm.h / ntosp.h
typedef struct _IO_CONNECT_INTERRUPT_MESSAGE_BASED_PARAMETERS
{
    _In_ PDEVICE_OBJECT PhysicalDeviceObject;
    union
    {
        _Out_ PVOID *Generic;
        _Out_ PIO_INTERRUPT_MESSAGE_INFO *InterruptMessageTable;
        _Out_ PKINTERRUPT *InterruptObject;
    } ConnectionContext;
    _In_ PKMESSAGE_SERVICE_ROUTINE MessageServiceRoutine;
    _In_ PVOID ServiceContext;
    _In_opt_ PKSPIN_LOCK SpinLock;
    _In_opt_ KIRQL SynchronizeIrql;
    _In_ BOOLEAN FloatingSave;
    _In_opt_ PKSERVICE_ROUTINE FallBackServiceRoutine;
} IO_CONNECT_INTERRUPT_MESSAGE_BASED_PARAMETERS,
  *PIO_CONNECT_INTERRUPT_MESSAGE_BASED_PARAMETERS;

// wdm.h / ntosp.h
typedef struct _IO_CONNECT_INTERRUPT_LINE_BASED_PARAMETERS {
    _In_ PDEVICE_OBJECT PhysicalDeviceObject;
    _Out_ PKINTERRUPT *InterruptObject;
    _In_ PKSERVICE_ROUTINE ServiceRoutine;
    _In_ PVOID ServiceContext;
    _In_opt_ PKSPIN_LOCK SpinLock;
    _In_opt_ KIRQL SynchronizeIrql;
    _In_ BOOLEAN FloatingSave;
} IO_CONNECT_INTERRUPT_LINE_BASED_PARAMETERS,
  *PIO_CONNECT_INTERRUPT_LINE_BASED_PARAMETERS;

// wdm.h / ntosp.h
typedef struct _IO_CONNECT_INTERRUPT_PARAMETERS
{
    _Inout_ ULONG Version;
    union
    {
        IO_CONNECT_INTERRUPT_FULLY_SPECIFIED_PARAMETERS FullySpecified;
        IO_CONNECT_INTERRUPT_LINE_BASED_PARAMETERS LineBased;
        IO_CONNECT_INTERRUPT_MESSAGE_BASED_PARAMETERS MessageBased;
    };
} IO_CONNECT_INTERRUPT_PARAMETERS, *PIO_CONNECT_INTERRUPT_PARAMETERS;

// wdm.h / ntosp.h
typedef struct _IO_DISCONNECT_INTERRUPT_PARAMETERS
{
    _In_ ULONG Version;
    union
    {
        _In_ PVOID Generic;
        _In_ PKINTERRUPT InterruptObject;
        _In_ PIO_INTERRUPT_MESSAGE_INFO InterruptMessageTable;
    } ConnectionContext;
} IO_DISCONNECT_INTERRUPT_PARAMETERS, *PIO_DISCONNECT_INTERRUPT_PARAMETERS;

// wdm.h / ntosp.h
typedef struct _IO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS
{
    _In_ ULONG Version;
    union
    {
        _In_ PVOID Generic;
        _In_ PKINTERRUPT InterruptObject;
        _In_ PIO_INTERRUPT_MESSAGE_INFO InterruptMessageTable;
    } ConnectionContext;
} IO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS,
  *PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS;

// wdm.h / ntosp.h
_Function_class_(IO_TIMER_ROUTINE)
_IRQL_requires_same_
typedef
VOID
NTAPI
IO_TIMER_ROUTINE (
    _In_ struct _DEVICE_OBJECT *DeviceObject,
    _In_opt_ PVOID Context);
typedef IO_TIMER_ROUTINE *PIO_TIMER_ROUTINE;

// wdm.h / ntosp.h
_Function_class_(IO_WORKITEM_ROUTINE)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
typedef
VOID
NTAPI
IO_WORKITEM_ROUTINE (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ PVOID Context);
typedef IO_WORKITEM_ROUTINE *PIO_WORKITEM_ROUTINE;

// wdm.h / ntosp.h
_Function_class_(IO_WORKITEM_ROUTINE_EX)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
typedef
VOID
NTAPI
IO_WORKITEM_ROUTINE_EX (
    _In_ PVOID IoObject,
    _In_opt_ PVOID Context,
    _In_ PIO_WORKITEM IoWorkItem);
typedef IO_WORKITEM_ROUTINE_EX *PIO_WORKITEM_ROUTINE_EX;

// wdm.h / ntosp.h
typedef struct _BOOTDISK_INFORMATION
{
    LONGLONG BootPartitionOffset;
    LONGLONG SystemPartitionOffset;
    ULONG BootDeviceSignature;
    ULONG SystemDeviceSignature;
} BOOTDISK_INFORMATION, *PBOOTDISK_INFORMATION;

// wdm.h / ntosp.h
#if (NTDDI_VERSION >= NTDDI_WIN7)
typedef struct _LOADER_PARTITION_INFORMATION_EX
{
    ULONG PartitionStyle;
    ULONG PartitionNumber;
    union
    {
        ULONG Signature;
        GUID DeviceId;
    };
    ULONG Flags;
} LOADER_PARTITION_INFORMATION_EX, *PLOADER_PARTITION_INFORMATION_EX;
typedef struct _BOOTDISK_INFORMATION_LITE {
    ULONG NumberEntries;
    LOADER_PARTITION_INFORMATION_EX Entries[1];
} BOOTDISK_INFORMATION_LITE, *PBOOTDISK_INFORMATION_LITE;
#elif (NTDDI_VERSION >= NTDDI_VISTA)
typedef struct _BOOTDISK_INFORMATION_LITE {
    ULONG BootDeviceSignature;
    ULONG SystemDeviceSignature;
    GUID BootDeviceGuid;
    GUID SystemDeviceGuid;
    BOOLEAN BootDeviceIsGpt;
    BOOLEAN SystemDeviceIsGpt;
} BOOTDISK_INFORMATION_LITE, *PBOOTDISK_INFORMATION_LITE;
#endif // NTDDI_VERSION >= NTDDI_VISTA

// wdm.h / ntosp.h
#define MAXIMUM_VOLUME_LABEL_LENGTH (32 * sizeof(WCHAR))
typedef struct _VPB
{
    CSHORT Type;
    CSHORT Size;
    USHORT Flags;
    USHORT VolumeLabelLength;
    struct _DEVICE_OBJECT *DeviceObject;
    struct _DEVICE_OBJECT *RealDevice;
    ULONG SerialNumber;
    ULONG ReferenceCount;
    WCHAR VolumeLabel[MAXIMUM_VOLUME_LABEL_LENGTH / sizeof(WCHAR)];
} VPB, *PVPB;

// wdm.h / ntosp.h
typedef struct _IO_CSQ IO_CSQ, *PIO_CSQ;

typedef
VOID
NTAPI
IO_CSQ_INSERT_IRP (
    _In_ struct _IO_CSQ *Csq,
    _In_ PIRP Irp);
typedef IO_CSQ_INSERT_IRP *PIO_CSQ_INSERT_IRP;

typedef
NTSTATUS
NTAPI
IO_CSQ_INSERT_IRP_EX (
    _In_ struct _IO_CSQ *Csq,
    _In_ PIRP Irp,
    _In_ PVOID InsertContext);
typedef IO_CSQ_INSERT_IRP_EX *PIO_CSQ_INSERT_IRP_EX;

typedef
VOID
NTAPI
IO_CSQ_REMOVE_IRP (
    _In_ PIO_CSQ Csq,
    _In_ PIRP Irp);
typedef IO_CSQ_REMOVE_IRP *PIO_CSQ_REMOVE_IRP;

typedef
PIRP
NTAPI
IO_CSQ_PEEK_NEXT_IRP (
    _In_ PIO_CSQ Csq,
    _In_ PIRP Irp,
    _In_ PVOID PeekContext);
typedef IO_CSQ_PEEK_NEXT_IRP *PIO_CSQ_PEEK_NEXT_IRP;

typedef
VOID
NTAPI
IO_CSQ_ACQUIRE_LOCK (
     _In_ PIO_CSQ Csq,
     _Out_ PKIRQL  Irql);
typedef IO_CSQ_ACQUIRE_LOCK *PIO_CSQ_ACQUIRE_LOCK;

typedef
VOID
NTAPI
IO_CSQ_RELEASE_LOCK (
     _In_ PIO_CSQ Csq,
     _In_ KIRQL Irql);
typedef IO_CSQ_RELEASE_LOCK *PIO_CSQ_RELEASE_LOCK;

typedef
VOID
NTAPI
IO_CSQ_COMPLETE_CANCELED_IRP (
    _In_ PIO_CSQ Csq,
    _In_ PIRP Irp);
typedef IO_CSQ_COMPLETE_CANCELED_IRP *PIO_CSQ_COMPLETE_CANCELED_IRP;

// wdm.h / ntosp.h
typedef struct _IO_CSQ_IRP_CONTEXT
{
    ULONG Type;
    PIRP Irp;
    PIO_CSQ Csq;
} IO_CSQ_IRP_CONTEXT, *PIO_CSQ_IRP_CONTEXT;

// ntddk.h
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

// ntddk.h / ntosp.h
typedef struct _CONFIGURATION_INFORMATION
{
    ULONG DiskCount;
    ULONG FloppyCount;
    ULONG CdRomCount;
    ULONG TapeCount;
    ULONG ScsiPortCount;
    ULONG SerialCount;
    ULONG ParallelCount;
    BOOLEAN AtDiskPrimaryAddressClaimed;
    BOOLEAN AtDiskSecondaryAddressClaimed;
    ULONG Version;
    ULONG MediumChangerCount;
} CONFIGURATION_INFORMATION, *PCONFIGURATION_INFORMATION;

// ntddk.h / ntosp.h
typedef struct _DISK_SIGNATURE
{
    ULONG PartitionStyle;
    union
    {
        struct
        {
            ULONG Signature;
            ULONG CheckSum;
        } Mbr;
        struct
        {
            GUID DiskId;
        } Gpt;
    };
} DISK_SIGNATURE, *PDISK_SIGNATURE;

// ntddk.h / ntosp.h
typedef
VOID
NTAPI
DRIVER_REINITIALIZE (
    _In_ struct _DRIVER_OBJECT *DriverObject,
    _In_opt_ PVOID Context,
    _In_ ULONG Count);
typedef DRIVER_REINITIALIZE *PDRIVER_REINITIALIZE;

// ntddk.h / ntosp.h
typedef
NTSTATUS
(NTAPI *PIO_QUERY_DEVICE_ROUTINE) (
    _In_ PVOID Context,
    _In_ PUNICODE_STRING PathName,
    _In_ INTERFACE_TYPE BusType,
    _In_ ULONG BusNumber,
    _In_ PKEY_VALUE_FULL_INFORMATION *BusInformation,
    _In_ CONFIGURATION_TYPE ControllerType,
    _In_ ULONG ControllerNumber,
    _In_ PKEY_VALUE_FULL_INFORMATION *ControllerInformation,
    _In_ CONFIGURATION_TYPE PeripheralType,
    _In_ ULONG PeripheralNumber,
    _In_ PKEY_VALUE_FULL_INFORMATION *PeripheralInformation);

// ntddk.h / ntosp.h
typedef struct _OPLOCK_KEY_ECP_CONTEXT *POPLOCK_KEY_ECP_CONTEXT;

// ntddk.h / ntosp.h
typedef struct _OPLOCK_KEY_CONTEXT
{
    USHORT Version;
    USHORT Flags;
    GUID ParentOplockKey;
    GUID TargetOplockKey;
    ULONG Reserved;
} OPLOCK_KEY_CONTEXT, *POPLOCK_KEY_CONTEXT;

// ntifs.h
typedef struct _IO_CREATE_STREAM_FILE_OPTIONS
{
    USHORT Size;
    USHORT Flags;
    PDEVICE_OBJECT TargetDeviceObject;
} IO_CREATE_STREAM_FILE_OPTIONS, *PIO_CREATE_STREAM_FILE_OPTIONS;

// ntifs.h
typedef struct _REPARSE_DATA_BUFFER
{
    ULONG  ReparseTag;
    USHORT ReparseDataLength;
    USHORT Reserved;
    union
    {
        struct
        {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            ULONG Flags;
            WCHAR PathBuffer[1];
        } SymbolicLinkReparseBuffer;
        struct
        {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            WCHAR PathBuffer[1];
        } MountPointReparseBuffer;
        struct
        {
            UCHAR DataBuffer[1];
        } GenericReparseBuffer;
    } DUMMYUNIONNAME;
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;

// ntifs.h / ntosp.h
struct _IO_IRP_EXT_TRACK_OFFSET_HEADER;
typedef
VOID
(NTAPI *PIO_IRP_EXT_PROCESS_TRACKED_OFFSET_CALLBACK) (
    _In_ struct _IO_IRP_EXT_TRACK_OFFSET_HEADER *SourceContext,
    _Inout_ struct _IO_IRP_EXT_TRACK_OFFSET_HEADER *TargetContext,
    _In_ LONGLONG RelativeOffset);

// ntifs.h / ntosp.h
typedef struct _IO_IRP_EXT_TRACK_OFFSET_HEADER
{
    USHORT Validation;
    USHORT Flags;
    PIO_IRP_EXT_PROCESS_TRACKED_OFFSET_CALLBACK TrackedOffsetCallback;
} IO_IRP_EXT_TRACK_OFFSET_HEADER, *PIO_IRP_EXT_TRACK_OFFSET_HEADER;

// ntifs.h
typedef
VOID
NTAPI
DRIVER_FS_NOTIFICATION (
    _In_ struct _DEVICE_OBJECT *DeviceObject,
    _In_ BOOLEAN FsActive);
typedef DRIVER_FS_NOTIFICATION *PDRIVER_FS_NOTIFICATION;

// ntosp.h
typedef struct _IO_PRIORITY_INFO {
    ULONG Size;
    ULONG ThreadPriority;
    ULONG PagePriority;
    IO_PRIORITY_HINT IoPriority;
} IO_PRIORITY_INFO, *PIO_PRIORITY_INFO;

// ntosp.h
typedef struct _IO_DRIVER_CREATE_CONTEXT {
    CSHORT Size;
    struct _ECP_LIST *ExtraCreateParameter;
    PVOID DeviceObjectHint;
    PTXN_PARAMETER_BLOCK TxnParameters;
} IO_DRIVER_CREATE_CONTEXT, *PIO_DRIVER_CREATE_CONTEXT;

// ntosp.h
typedef
VOID
NTAPI
IO_MINI_PACKET_CALLBACK_ROUTINE (
    _In_ struct _IO_MINI_COMPLETION_PACKET_USER *MiniPacket,
    _In_opt_ PVOID Context);
typedef IO_MINI_PACKET_CALLBACK_ROUTINE *PIO_MINI_PACKET_CALLBACK_ROUTINE;

// ntosp.h
typedef struct _IO_MINI_COMPLETION_PACKET_USER {
    LIST_ENTRY ListEntry;
    ULONG PacketType;
    PVOID KeyContext;
    PVOID ApcContext;
    NTSTATUS IoStatus;
    ULONG_PTR IoStatusInformation;
    PIO_MINI_PACKET_CALLBACK_ROUTINE MiniPacketCallback;
    PVOID Context;
    BOOLEAN Allocated;
} IO_MINI_COMPLETION_PACKET_USER, *PIO_MINI_COMPLETION_PACKET_USER;

// ntosp.h
typedef struct _IO_REMOVE_LOCK_TRACKING_BLOCK * PIO_REMOVE_LOCK_TRACKING_BLOCK;
typedef struct _IO_REMOVE_LOCK_COMMON_BLOCK
{
    BOOLEAN Removed;
    BOOLEAN Reserved [3];
    __volatile LONG IoCount;
    KEVENT RemoveEvent;
} IO_REMOVE_LOCK_COMMON_BLOCK;
typedef struct _IO_REMOVE_LOCK_DBG_BLOCK
{
    LONG Signature;
    ULONG HighWatermark;
    LONGLONG MaxLockedTicks;
    LONG AllocateTag;
    LIST_ENTRY LockList;
    KSPIN_LOCK Spin;
    __volatile LONG LowMemoryCount;
    ULONG Reserved1[4];
    PVOID Reserved2;
    PIO_REMOVE_LOCK_TRACKING_BLOCK Blocks;
} IO_REMOVE_LOCK_DBG_BLOCK;
typedef struct _IO_REMOVE_LOCK
{
    IO_REMOVE_LOCK_COMMON_BLOCK Common;
#if DBG
    IO_REMOVE_LOCK_DBG_BLOCK Dbg;
#endif
} IO_REMOVE_LOCK, *PIO_REMOVE_LOCK;

// ntosifs.h
typedef struct _FILE_SYMLINK_SUPPORT_INFORMATION
{
    BOOLEAN LocalToLocal;
    BOOLEAN LocalToRemote;
    BOOLEAN RemoteToLocal;
    BOOLEAN RemoteToRemote;
} FILE_SYMLINK_SUPPORT_INFORMATION, *PFILE_SYMLINK_SUPPORT_INFORMATION;

// ntosp.h
typedef struct _IO_LOAD_CRASHDUMP_PARAMS
{
    ULONG Size;
    PUNICODE_STRING NamePrefix;
    PUNICODE_STRING LoadedBaseName;
} IO_LOAD_CRASHDUMP_PARAMS, *PIO_LOAD_CRASHDUMP_PARAMS;

// ntosp.h
typedef struct _IO_LOAD_CRASHDUMP_RESULT {
    ULONG Size;
    PVOID ImageHandle;
    PVOID ImageBaseAddress;
} IO_LOAD_CRASHDUMP_RESULT, *PIO_LOAD_CRASHDUMP_RESULT;

// ntosp.h
typedef struct _IO_TRACKING_CALLBACK_INFO
{
    USHORT Size;
    ULONGLONG ElapsedTime;
    DEVICE_TYPE DeviceType;
} IO_TRACKING_CALLBACK_INFO, *PIO_TRACKING_CALLBACK_INFO;

// ntosp.h
typedef
VOID
(NTAPI *PIO_TRACKING_CALLBACK) (
    _In_ PIO_TRACKING_CALLBACK_INFO CallbackInfo);

// ntosp.h
typedef struct _IO_TRACKING_SETTINGS
{
    USHORT Size;
    PIO_TRACKING_CALLBACK TrackingCallback;
} IO_TRACKING_SETTINGS, *PIO_TRACKING_SETTINGS;

// ntosp.h
typedef
VOID
NTAPI
DRIVER_PRIORITY_CALLBACK (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PETHREAD Thread,
    _In_ IO_PRIORITY_HINT TargetPriority);
typedef DRIVER_PRIORITY_CALLBACK *PDRIVER_PRIORITY_CALLBACK;

#if 0
// ntosp.h
_Acquires_lock_(_Global_cancel_spin_lock_)
_Requires_lock_not_held_(_Global_cancel_spin_lock_)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_raises_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoAcquireCancelSpinLock (
    _Out_ _At_(*Irql, _IRQL_saves_) PKIRQL Irql);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoAcquireRemoveLockEx (
    _Inout_ PIO_REMOVE_LOCK RemoveLock,
    _In_opt_ PVOID Tag,
    _In_ PCSTR File,
    _In_ ULONG Line,
    _In_ ULONG RemlockSize);

NTKERNELAPI
VOID
NTAPI
IoAcquireVpbSpinLock (
    _Out_ PKIRQL Irql);

// ntosifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoAdjustStackSizeForRedirection (
    _In_ PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice,
    _Out_opt_ PCCHAR ExtraStackLocations);

// ntosp.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
__drv_preferredFunction("AllocateAdapterChannel","obsolete")
NTKERNELAPI
NTSTATUS
NTAPI
IoAllocateAdapterChannel (
    _In_ PADAPTER_OBJECT AdapterObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG NumberOfMapRegisters,
    _In_ PDRIVER_CONTROL ExecutionRoutine,
    _In_ PVOID Context);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoAllocateController (
    _In_ PCONTROLLER_OBJECT ControllerObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PDRIVER_CONTROL ExecutionRoutine,
    _In_opt_ PVOID Context);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Ret_range_(<=, 0)
NTKERNELAPI
NTSTATUS
NTAPI
IoAllocateDriverObjectExtension (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PVOID ClientIdentificationAddress,
    _In_ ULONG DriverObjectExtensionSize,
    _Post_ _At_(*DriverObjectExtension, _When_(return==0,
    __drv_aliasesMem __drv_allocatesMem(Mem) _Post_notnull_))
    _When_(return == 0, _Outptr_result_bytebuffer_(DriverObjectExtensionSize))
    PVOID *DriverObjectExtension);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PVOID
NTAPI
IoAllocateErrorLogEntry (
    _In_ PVOID IoObject,
    _In_ UCHAR EntrySize);

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PIRP
NTAPI
IoAllocateIrp (
    _In_ CCHAR StackSize,
    _In_ BOOLEAN ChargeQuota);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PMDL
NTAPI
IoAllocateMdl (
    _In_opt_ __drv_aliasesMem PVOID VirtualAddress,
    _In_ ULONG Length,
    _In_ BOOLEAN SecondaryBuffer,
    _In_ BOOLEAN ChargeQuota,
    _Inout_opt_ PIRP Irp);

// ntosp.h
NTKERNELAPI
PIO_MINI_COMPLETION_PACKET_USER
NTAPI
IoAllocateMiniCompletionPacket (
    _In_ PIO_MINI_PACKET_CALLBACK_ROUTINE CallbackRoutine,
    _In_opt_ PVOID Context);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoAllocateSfioStreamIdentifier (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG Length,
    _In_ PVOID Signature,
    _Out_ PVOID *StreamIdentifier);

// ntosp.h
__drv_allocatesMem(Mem)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTKERNELAPI
PIO_WORKITEM
NTAPI
IoAllocateWorkItem (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoApplyPriorityInfoThread (
    _In_ PIO_PRIORITY_INFO InputPriorityInfo,
    _Out_opt_ PIO_PRIORITY_INFO OutputPriorityInfo,
    _In_ PETHREAD Thread);

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("(see documentation)", "Obsolete")
NTKERNELAPI
NTSTATUS
NTAPI
IoAssignResources (
    _In_ PUNICODE_STRING RegistryPath,
    _In_opt_ PUNICODE_STRING DriverClassName,
    _In_ PDRIVER_OBJECT DriverObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ PIO_RESOURCE_REQUIREMENTS_LIST RequestedResources,
    _Inout_ PCM_RESOURCE_LIST *AllocatedResources);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<=, 0)
NTKERNELAPI
NTSTATUS
NTAPI
IoAttachDevice (
    _In_ _When_(return==0, __drv_aliasesMem)
        PDEVICE_OBJECT SourceDevice,
    _In_ PUNICODE_STRING TargetDevice,
    _Out_ PDEVICE_OBJECT *AttachedDevice);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoAttachDeviceToDeviceStackSafe (
    _In_ PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice,
    _Outptr_ PDEVICE_OBJECT *AttachedToDeviceObject);

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("IoAttachDeviceToDeviceStack", "Obsolete")
NTKERNELAPI
NTSTATUS
NTAPI
IoAttachDeviceByPointer (
    _In_ PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice);

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoAttachDeviceToDeviceStack (
    _In_ _When_(return!=0, __drv_aliasesMem)
        PDEVICE_OBJECT SourceDevice,
    _In_ PDEVICE_OBJECT TargetDevice);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoBoostThreadIo (
    _In_ PETHREAD Thread,
    _In_ IO_PRIORITY_HINT TargetPriority,
    _In_ BOOLEAN Unboost,
    _In_ ULONG Flags);

// ntosp.h
_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PIRP
NTAPI
IoBuildAsynchronousFsdRequest (
    _In_ ULONG MajorFunction,
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_opt_ PVOID Buffer,
    _In_opt_ ULONG Length,
    _In_opt_ PLARGE_INTEGER StartingOffset,
    _In_opt_ PIO_STATUS_BLOCK IoStatusBlock);

// ntosp.h
_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
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
    _Out_ PIO_STATUS_BLOCK IoStatusBlock);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoBuildPartialMdl (
    _In_ PMDL SourceMdl,
    _Inout_ PMDL TargetMdl,
    _Inout_ PVOID VirtualAddress,
    _In_ ULONG Length);

// ntosp.h
_When_(MajorFunction == IRP_MJ_WRITE, _At_(Buffer, _In_))
_When_(MajorFunction == IRP_MJ_READ, _At_(Buffer, _Out_))
_When_(MajorFunction != IRP_MJ_READ && MajorFunction != IRP_MJ_WRITE, _At_(Buffer, _Pre_null_))
_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PIRP
NTAPI
IoBuildSynchronousFsdRequest (
    _In_ ULONG MajorFunction,
    _In_ PDEVICE_OBJECT DeviceObject,
    PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER StartingOffset,
    _In_ PKEVENT Event,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock);

// prototype from IofCallDriver
_IRQL_requires_max_(DISPATCH_LEVEL)
_Success_(TRUE)
NTKERNELAPI
NTSTATUS
NTAPI
IoCallDriver (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ __drv_aliasesMem PIRP Irp);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoCancelFileOpen (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PFILE_OBJECT FileObject);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
NTAPI
IoCancelIrp (
    _In_ PIRP Irp);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckDesiredAccess (
    _Inout_ PACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK GrantedAccess);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckEaBufferValidity (
    _In_ PFILE_FULL_EA_INFORMATION EaBuffer,
    _In_ ULONG EaLength,
    _Out_ PULONG ErrorOffset);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckFunctionAccess (
    _In_ ACCESS_MASK GrantedAccess,
    _In_ UCHAR MajorFunction,
    _In_ UCHAR MinorFunction,
    _In_ ULONG IoControlCode,
    _In_opt_ PVOID Arg1,
    _In_opt_ PVOID Arg2);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckQuerySetFileInformation (
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG Length,
    _In_ BOOLEAN SetOperation);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckQuerySetVolumeInformation (
    _In_ FS_INFORMATION_CLASS FsInformationClass,
    _In_ ULONG Length,
    _In_ BOOLEAN SetOperation);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckQuotaBufferValidity (
    _In_ PFILE_QUOTA_INFORMATION QuotaBuffer,
    _In_ ULONG QuotaLength,
    _Out_ PULONG ErrorOffset);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckShareAccess (
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess,
    _In_ BOOLEAN Update);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCheckShareAccessEx (
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess,
    _In_ BOOLEAN Update,
    _In_ PBOOLEAN WritePermission);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoClearActivityIdThread (
    _In_ LPCGUID OriginalId);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoClearDependency (
    _In_ PDEVICE_OBJECT DependentPdo,
    _In_ PDEVICE_OBJECT ProviderPdo);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoClearIrpExtraCreateParameter (
    _Inout_ PIRP Irp);

// copied from IofCompleteRequest(ptr long)
NTKERNELAPI
VOID
NTAPI
IoCompleteRequest (
    _In_ PIRP Irp,
    _In_ CCHAR PriorityBoost);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
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
    _In_ BOOLEAN FloatingSave);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoConnectInterruptEx (
    _Inout_ PIO_CONNECT_INTERRUPT_PARAMETERS Parameters);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoConvertFileHandleToKernelHandle (
    _In_opt_ HANDLE Handle,
    _In_ KPROCESSOR_MODE PreviousMode,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OverrideAccessCheck,
    _Out_ HANDLE* KernelHandle
    );

// ntosifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCopyDeviceObjectHint (
    _In_ PFILE_OBJECT SourceFile,
    _Inout_ PFILE_OBJECT TargetFile);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCreateArcName (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PCONTROLLER_OBJECT
NTAPI
IoCreateController(
    _In_ ULONG Size);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<=, 0)
NTKERNELAPI
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
    PDEVICE_OBJECT *DeviceObject);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCreateDisk (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_opt_ struct _CREATE_DISK* Disk);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCreateDriver (
    _In_opt_ PUNICODE_STRING DriverName,
    _In_ PDRIVER_INITIALIZE InitializationFunction);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
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
    _In_ ULONG Options);

// ntosp.h
NTKERNELAPI
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
    _In_opt_ PIO_DRIVER_CREATE_CONTEXT DriverContext);

// ntosp.h
NTKERNELAPI
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
    _In_opt_ PVOID DeviceObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PKEVENT
NTAPI
IoCreateNotificationEvent (
    _In_ PUNICODE_STRING EventName,
    _Out_ PHANDLE EventHandle);

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PFILE_OBJECT
NTAPI
IoCreateStreamFileObject (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject);

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PFILE_OBJECT
NTAPI
IoCreateStreamFileObjectEx (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _Out_opt_ PHANDLE FileHandle);

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoCreateStreamFileObjectEx2 (
    _In_ PIO_CREATE_STREAM_FILE_OPTIONS CreateOptions,
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _Out_ PFILE_OBJECT* StreamFileObject,
    _Out_opt_ PHANDLE FileHandle);

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PFILE_OBJECT
NTAPI
IoCreateStreamFileObjectLite (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoCreateSymbolicLink (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ PUNICODE_STRING DeviceName);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PKEVENT
NTAPI
IoCreateSynchronizationEvent (
    _In_ PUNICODE_STRING EventName,
    _Out_ PHANDLE EventHandle);

// ntosp.h
_IRQL_requires_same_
_IRQL_requires_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
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
    _In_opt_ PVOID StartContext);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoCreateUnprotectedSymbolicLink (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ PUNICODE_STRING DeviceName);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCsqInitialize (
    _Out_ PIO_CSQ Csq,
    _In_ PIO_CSQ_INSERT_IRP CsqInsertIrp,
    _In_ PIO_CSQ_REMOVE_IRP CsqRemoveIrp,
    _In_ PIO_CSQ_PEEK_NEXT_IRP CsqPeekNextIrp,
    _In_ PIO_CSQ_ACQUIRE_LOCK CsqAcquireLock,
    _In_ PIO_CSQ_RELEASE_LOCK CsqReleaseLock,
    _In_ PIO_CSQ_COMPLETE_CANCELED_IRP CsqCompleteCanceledIrp);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCsqInitializeEx (
    _Out_ PIO_CSQ Csq,
    _In_ PIO_CSQ_INSERT_IRP_EX CsqInsertIrp,
    _In_ PIO_CSQ_REMOVE_IRP CsqRemoveIrp,
    _In_ PIO_CSQ_PEEK_NEXT_IRP CsqPeekNextIrp,
    _In_ PIO_CSQ_ACQUIRE_LOCK CsqAcquireLock,
    _In_ PIO_CSQ_RELEASE_LOCK CsqReleaseLock,
    _In_ PIO_CSQ_COMPLETE_CANCELED_IRP CsqCompleteCanceledIrp);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoCsqInsertIrp (
    _Inout_ PIO_CSQ Csq,
    _Inout_ PIRP Irp,
    _Out_opt_ PIO_CSQ_IRP_CONTEXT Context);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoCsqInsertIrpEx (
    _Inout_ PIO_CSQ Csq,
    _Inout_ PIRP Irp,
    _Out_opt_ PIO_CSQ_IRP_CONTEXT Context,
    _In_opt_ PVOID InsertContext);

// ntosp.h
NTKERNELAPI
PIRP
NTAPI
IoCsqRemoveIrp (
    _Inout_ PIO_CSQ Csq,
    _Inout_ PIO_CSQ_IRP_CONTEXT Context);

// ntosp.h
NTKERNELAPI
PIRP
NTAPI
IoCsqRemoveNextIrp (
    _Inout_ PIO_CSQ Csq,
    _In_opt_ PVOID PeekContext);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoDecrementKeepAliveCount (
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PEPROCESS Process);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoDeleteAllDependencyRelations (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoDeleteController (
    _In_ PCONTROLLER_OBJECT ControllerObject);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_Kernel_clear_do_init_(__yes)
NTKERNELAPI
VOID
NTAPI
IoDeleteDevice (
    _In_ __drv_freesMem(Mem) PDEVICE_OBJECT DeviceObject);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoDeleteDriver (
    _In_ PDRIVER_OBJECT DriverObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoDeleteSymbolicLink (
    _In_ PUNICODE_STRING SymbolicLinkName);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoDetachDevice (
    _Inout_ PDEVICE_OBJECT TargetDevice);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoDisconnectInterrupt (
    _In_ PKINTERRUPT InterruptObject);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoDisconnectInterruptEx (
    _In_ PIO_DISCONNECT_INTERRUPT_PARAMETERS Parameters);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoDuplicateDependency (
    _In_ PDEVICE_OBJECT ProviderPdo,
    _In_ PDEVICE_OBJECT NewProviderPdo);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoEnqueueIrp (
    _In_ PIRP Irp);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoEnumerateDeviceObjectList (
    _In_  PDRIVER_OBJECT DriverObject,
    _Out_writes_bytes_to_opt_(DeviceObjectListSize,(*ActualNumberDeviceObjects)*sizeof(PDEVICE_OBJECT))
        PDEVICE_OBJECT *DeviceObjectList,
    _In_  ULONG DeviceObjectListSize,
    _Out_ PULONG ActualNumberDeviceObjects);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoEnumerateRegisteredFiltersList (
    _Out_writes_bytes_to_opt_(DriverObjectListSize,(*ActualNumberDriverObjects)*sizeof(PDRIVER_OBJECT)) PDRIVER_OBJECT *DriverObjectList,
    _In_ ULONG  DriverObjectListSize,
    _Out_ PULONG ActualNumberDriverObjects);

// ntifs.h
NTKERNELAPI
BOOLEAN
NTAPI
IoFastQueryNetworkAttributes (
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG OpenOptions,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _Out_ PFILE_NETWORK_OPEN_INFORMATION Buffer);

// ntosp.h
NTKERNELAPI
BOOLEAN
NTAPI
IoForwardIrpSynchronously (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoFreeController (
    _In_ PCONTROLLER_OBJECT ControllerObject);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoFreeErrorLogEntry (
    _In_ PVOID ElEntry);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoFreeIrp (
    _In_ __drv_freesMem(Mem) PIRP Irp);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoFreeMdl (
    PMDL Mdl);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoFreeMiniCompletionPacket (
    _Inout_ PIO_MINI_COMPLETION_PACKET_USER MiniPacket);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoFreeSfioStreamIdentifier (
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID Signature);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoFreeWorkItem (
    _In_ __drv_freesMem(Mem) PIO_WORKITEM IoWorkItem);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetActivityIdIrp (
    _In_ PIRP Irp,
    _Out_ LPGUID Guid);

// ntosp.h
NTKERNELAPI
LPCGUID
NTAPI
IoGetActivityIdThread (
    VOID);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetAffinityInterrupt (
    _In_ PKINTERRUPT InterruptObject,
    _Out_ PGROUP_AFFINITY GroupAffinity);

// ntosp.h
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetAttachedDevice (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetAttachedDeviceReference (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetBaseFileSystemDeviceObject (
    _In_ PFILE_OBJECT FileObject);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetBootDiskInformation (
    _Inout_ PBOOTDISK_INFORMATION BootDiskInformation,
    _In_ ULONG Size);

// ntosp.h
#if (NTDDI_VERSION >= NTDDI_VISTA)
NTKERNELAPI
NTSTATUS
NTAPI
IoGetBootDiskInformationLite (
    _Outptr_ PBOOTDISK_INFORMATION_LITE *BootDiskInformation);
#endif // NTDDI_VERSION >= NTDDI_VISTA

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PCONFIGURATION_INFORMATION
NTAPI
IoGetConfigurationInformation (
    VOID);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetContainerInformation (
    _In_ IO_CONTAINER_INFORMATION_CLASS InformationClass,
    _In_opt_ PVOID ContainerObject,
    _Inout_updates_bytes_opt_(BufferLength) PVOID Buffer,
    _In_ ULONG BufferLength);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PEPROCESS
NTAPI
IoGetCurrentProcess (
    VOID);

// ntosp.h
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetDeviceAttachmentBaseRef (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoGetDeviceInterfaceAlias (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ const GUID *AliasInterfaceClassGuid,
    _Out_
    _When_(return==0, _At_(AliasSymbolicLinkName->Buffer, __drv_allocatesMem(Mem)))
        PUNICODE_STRING AliasSymbolicLinkName);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
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
    _Out_ PDEVPROPTYPE Type);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoGetDeviceInterfaces (
    _In_ const GUID *InterfaceClassGuid,
    _In_opt_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ ULONG Flags,
    _Outptr_result_nullonfailure_
    _At_(*SymbolicLinkList, _When_(return==0, __drv_allocatesMem(Mem)))
        PZZWSTR *SymbolicLinkList);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoGetDeviceNumaNode (
    _In_ PDEVICE_OBJECT Pdo,
    _Out_ PUSHORT NodeNumber);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoGetDeviceObjectPointer (
    _In_ PUNICODE_STRING ObjectName,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PFILE_OBJECT *FileObject,
    _Out_ PDEVICE_OBJECT *DeviceObject);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetDeviceProperty (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ DEVICE_REGISTRY_PROPERTY DeviceProperty,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_opt_(BufferLength) PVOID PropertyBuffer,
    _Out_ _Deref_out_range_(<=, BufferLength) PULONG ResultLength);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
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
    _Out_ PDEVPROPTYPE Type);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetDeviceToVerify (
    _In_ PETHREAD Thread);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetDiskDeviceObject (
    _In_ PDEVICE_OBJECT FileSystemDeviceObject,
    _Out_ PDEVICE_OBJECT *DiskDeviceObject);

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
struct _DMA_ADAPTER *
NTAPI
IoGetDmaAdapter (
    _In_opt_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ struct _DEVICE_DESCRIPTION *DeviceDescription,
    _Out_ _When_(return!=0, _Kernel_IoGetDmaAdapter_ _At_(*NumberOfMapRegisters, _Must_inspect_result_))
        PULONG NumberOfMapRegisters);

// ntosp.h
__drv_aliasesMem
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PVOID
NTAPI
IoGetDriverObjectExtension (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PVOID ClientIdentificationAddress);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PGENERIC_MAPPING
NTAPI
IoGetFileObjectGenericMapping (
    VOID);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetFsTrackOffsetState (
    _In_ PIRP Irp,
    _Out_ PIO_IRP_EXT_TRACK_OFFSET_HEADER *RetFsTrackOffsetBlob,
    _Out_ LONGLONG *RetTrackedOffset);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetFsZeroingOffset (
    _In_ PIRP Irp,
    _Out_ PULONG ZeroingOffset);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetGenericIrpExtension (
    _In_ PIRP Irp,
    _Out_writes_(GenericExtensionDataSize) PUCHAR GenericExtensionData,
    _In_ USHORT GenericExtensionDataSize);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PVOID
NTAPI
IoGetInitialStack (
    VOID);

// ntosp.h
NTKERNELAPI
PEPROCESS
NTAPI
IoGetInitiatorProcess (
    _In_ PFILE_OBJECT FileObject);

// ntosp.h
NTKERNELAPI
IO_PRIORITY_HINT
NTAPI
IoGetIoPriorityHint (
    _In_ PIRP Irp);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetIrpExtraCreateParameter (
    _In_ PIRP Irp,
    _Outptr_result_maybenull_ struct _ECP_LIST **ExtraCreateParameter);

// ntosp.h
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetLowerDeviceObject (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
NTKERNELAPI
POPLOCK_KEY_ECP_CONTEXT
NTAPI
IoGetOplockKeyContext (
    _In_ PFILE_OBJECT FileObject);

// ntosp.h
NTKERNELAPI
POPLOCK_KEY_CONTEXT
NTAPI
IoGetOplockKeyContextEx (
    _In_ PFILE_OBJECT FileObject);

// ntosp.h
NTKERNELAPI
IO_PAGING_PRIORITY
FASTCALL
IoGetPagingIoPriority (
    _In_ PIRP Irp);

// ntosp.h
NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetRelatedDeviceObject (
    _In_ PFILE_OBJECT FileObject);

// ntosp.h
NTKERNELAPI
PEPROCESS
NTAPI
IoGetRequestorProcess (
    _In_ PIRP Irp);

// ntosp.h
NTKERNELAPI
ULONG
NTAPI
IoGetRequestorProcessId (
    _In_ PIRP Irp);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetRequestorSessionId (
    _In_ PIRP Irp,
    _Out_ PULONG pSessionId);

// ntosp.h
NTKERNELAPI
PVOID
NTAPI
IoGetSfioStreamIdentifier (
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID Signature);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoGetStackLimits (
    _Out_ PULONG_PTR LowLimit,
    _Out_ PULONG_PTR HighLimit);

// ntosifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoGetSymlinkSupportInformation (
    _Out_writes_bytes_(SupportInfoSize) PFILE_SYMLINK_SUPPORT_INFORMATION SupportInfo,
    _In_ ULONG SupportInfoSize);

// ntosp.h
NTKERNELAPI
PIRP
NTAPI
IoGetTopLevelIrp (
    VOID);

// ntosp.h
NTKERNELAPI
PTXN_PARAMETER_BLOCK
NTAPI
IoGetTransactionParameterBlock (
    _In_ PFILE_OBJECT FileObject);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoIncrementKeepAliveCount (
    _Inout_ PFILE_OBJECT FileObject,
    _Inout_ PEPROCESS Process);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoInitializeIrp (
    _Inout_ PIRP Irp,
    _In_ USHORT PacketSize,
    _In_ CCHAR StackSize);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoInitializeMiniCompletionPacket (
    _Inout_ PIO_MINI_COMPLETION_PACKET_USER MiniPacket,
    _In_ PIO_MINI_PACKET_CALLBACK_ROUTINE CallbackRoutine,
    _In_opt_ PVOID Context);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoInitializeRemoveLockEx (
    _Out_ PIO_REMOVE_LOCK Lock,
    _In_ ULONG AllocateTag,
    _In_ ULONG MaxLockedMinutes,
    _In_ ULONG HighWatermark,
    _In_ ULONG RemlockSize);

// ntosp.h
#if defined(_AMD64_) || defined(_X86_)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoInitializeTimer (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIO_TIMER_ROUTINE TimerRoutine,
    _In_opt_ __drv_aliasesMem PVOID Context);
#endif

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoInitializeWorkItem (
    _In_ PVOID IoObject,
    _Out_ PIO_WORKITEM IoWorkItem);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoInvalidateDeviceRelations (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ DEVICE_RELATION_TYPE Type);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoInvalidateDeviceState (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject);

// ntosp.h
#if BUILD_WOW64_ENABLED
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
IoIs32bitProcess (
    _In_opt_ PIRP Irp);
#endif // BUILD_WOW64_ENABLED && defined(_WIN64)

// ntosp.h
NTKERNELAPI
BOOLEAN
NTAPI
IoIsActivityTracingEnabled (
    VOID);

// ntddk.h
NTKERNELAPI
BOOLEAN
IoIsFileObjectIgnoringSharing (
  _In_ PFILE_OBJECT FileObject);

// ntddk.h
NTKERNELAPI
BOOLEAN
NTAPI
IoIsFileOriginRemote (
    _In_ PFILE_OBJECT FileObject);

#if BUILD_WOW64_ENABLED
// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
NTAPI
IoIsInitiator32bitProcess (
    _In_ PIRP Irp);
#endif // BUILD_WOW64_ENABLED && defined(_WIN64)

// ntifs.h
NTKERNELAPI
BOOLEAN
NTAPI
IoIsOperationSynchronous (
    _In_ PIRP Irp);

// ntifs.h
NTKERNELAPI
BOOLEAN
NTAPI
IoIsSystemThread (
    _In_ PETHREAD Thread);

// ntosp.h
NTKERNELAPI
LOGICAL
NTAPI
IoIsValidIrpStatus (
    _In_ NTSTATUS Status);

#if defined(_X86_) || defined(_AMD64_)
// ntifs.h
NTKERNELAPI
BOOLEAN
NTAPI
IoIsValidNameGraftingBuffer (
    _In_ PIRP Irp,
    _In_ PREPARSE_DATA_BUFFER ReparseBuffer);
#endif

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("RtlIsNtDdiVersionAvailable","Preferred")
NTKERNELAPI
BOOLEAN
NTAPI
IoIsWdmVersionAvailable (
    _When_(MajorVersion!=1&&MajorVersion!=6,
    _In_ __drv_reportError("MajorVersion must be 1 or 6")) UCHAR MajorVersion,
    _In_ _When_(MinorVersion!=0 && MinorVersion!=5 && MinorVersion!=16
                    && MinorVersion!=32 && MinorVersion!=48,
    __drv_reportError("MinorVersion must be 0, 0x5, 0x10, 0x20, or 0x30"))
    UCHAR MinorVersion);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoLoadCrashDumpDriver (
    _In_ PUNICODE_STRING DriverName,
    _In_ PIO_LOAD_CRASHDUMP_PARAMS LoadCrashDumpParams,
    _Inout_ PIO_LOAD_CRASHDUMP_RESULT LoadCrashDumpResult);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PIRP
NTAPI
IoMakeAssociatedIrp (
    _In_ PIRP Irp,
    _In_ CCHAR StackSize);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoOpenDeviceInterfaceRegistryKey (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE DeviceInterfaceKey);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoOpenDeviceRegistryKey (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG DevInstKeyType,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE DevInstRegKey);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoPageRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MemoryDescriptorList,
    _In_ PLARGE_INTEGER StartingOffset,
    _In_ PKEVENT Event,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoPropagateActivityIdToThread (
    _In_ PIRP Irp,
    _Out_ LPGUID PropagatedId,
    _Outptr_ LPCGUID *OriginalId);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoPropagateIrpExtension (
    _In_ PIRP SourceIrp,
    _In_ PIRP TargetIrp,
    _In_ ULONG Flags);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoPropagateIrpExtensionEx (
    _In_ PIRP SourceIrp,
    _In_ PIRP TargetIrp,
    _In_ LONGLONG TrackedOffset,
    _In_ ULONG Flags);

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("IoGetDeviceProperty", "Obsolete")
NTKERNELAPI
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
    _Inout_opt_ PVOID Context);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoQueryFileDosDeviceName (
    _In_ PFILE_OBJECT FileObject,
    _Out_ POBJECT_NAME_INFORMATION *ObjectNameInformation);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoQueryFileInformation (
    _In_ PFILE_OBJECT FileObject,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG Length,
    _Out_ PVOID FileInformation,
    _Out_ PULONG ReturnedLength);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoQueryFullDriverPath (
    _In_ PDRIVER_OBJECT DriverObject,
    _Out_ PUNICODE_STRING FullPath);

//@ stdcall -stub IoQueryInterface(ptr ptr ptr ptr ptr ptr ptr)

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoQueryVolumeInformation (
    _In_ PFILE_OBJECT FileObject,
    _In_ FS_INFORMATION_CLASS FsInformationClass,
    _In_ ULONG Length,
    _Out_ PVOID FsInformation,
    _Out_ PULONG ReturnedLength);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoQueueThreadIrp (
    _In_ PIRP Irp);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoQueueWorkItem (
    _Inout_ __drv_aliasesMem PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoQueueWorkItemEx (
    _Inout_ __drv_aliasesMem PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE_EX WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context);

// ntosifs.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
NTAPI
IoQueueWorkItemToNode (
    _Inout_ _When_(return != 0, __drv_aliasesMem) PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE_EX WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context,
    _In_ ULONG NodeNumber);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoRaiseHardError (
    _In_ PIRP Irp,
    _In_opt_ PVPB Vpb,
    _In_ PDEVICE_OBJECT RealDeviceObject);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
NTAPI
IoRaiseInformationalHardError (
    _In_ NTSTATUS ErrorStatus,
    _In_opt_ PUNICODE_STRING String,
    _In_opt_ PKTHREAD Thread);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoReadDiskSignature (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG BytesPerSector,
    _Out_ PDISK_SIGNATURE Signature);

// ntddk.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("IoReadPartitionTableEx", "Obsolete")
NTKERNELAPI
NTSTATUS
FASTCALL
IoReadPartitionTable (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ BOOLEAN ReturnRecognizedPartitions,
    _Out_ struct _DRIVE_LAYOUT_INFORMATION **PartitionBuffer);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoReadPartitionTableEx (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_ struct _DRIVE_LAYOUT_INFORMATION_EX** DriveLayout);

// ntosp.h
NTKERNELAPI
PVOID
NTAPI
IoRegisterBootDriverCallback (
    _In_ PBOOT_DRIVER_CALLBACK_FUNCTION CallbackFunction,
    _In_opt_ PVOID CallbackContext);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoRegisterBootDriverReinitialization (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_REINITIALIZE DriverReinitializationRoutine,
    _In_opt_ PVOID Context);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterContainerNotification (
    _In_ IO_CONTAINER_NOTIFICATION_CLASS NotificationClass,
    _In_ PIO_CONTAINER_NOTIFICATION_FUNCTION CallbackFunction,
    _In_reads_bytes_opt_(NotificationInformationLength) PVOID NotificationInformation,
    _In_ ULONG NotificationInformationLength,
    _Out_ PVOID CallbackRegistration);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterDeviceInterface (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ CONST GUID *InterfaceClassGuid,
    _In_opt_ PUNICODE_STRING ReferenceString,
    _Out_ _When_(return==0,
                     _At_(SymbolicLinkName->Buffer, __drv_allocatesMem(Mem)))
    PUNICODE_STRING SymbolicLinkName);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoRegisterDriverReinitialization (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_REINITIALIZE DriverReinitializationRoutine,
    _In_opt_ PVOID Context);

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoRegisterFileSystem (
    _In_ __drv_aliasesMem PDEVICE_OBJECT DeviceObject);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterFsRegistrationChange (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_FS_NOTIFICATION DriverNotificationRoutine);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterFsRegistrationChangeMountAware (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_FS_NOTIFICATION DriverNotificationRoutine,
    _In_ BOOLEAN SynchronizeWithMounts);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterIoTracking (
    _In_ PIO_TRACKING_SETTINGS IoTrackingSettings,
    _Outptr_ PVOID *IoTracker);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterLastChanceShutdownNotification (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
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
    PVOID *NotificationEntry);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterPriorityCallback (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_PRIORITY_CALLBACK Callback);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoRegisterShutdownNotification (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_Requires_lock_held_(_Global_cancel_spin_lock_)
_Releases_lock_(_Global_cancel_spin_lock_)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoReleaseCancelSpinLock (
    _In_ _IRQL_restores_ _IRQL_uses_cancel_ KIRQL Irql);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoReleaseRemoveLockAndWaitEx (
    _Inout_ PIO_REMOVE_LOCK RemoveLock,
    _In_opt_ PVOID Tag,
    _In_ ULONG RemlockSize);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoReleaseRemoveLockEx (
    _Inout_ PIO_REMOVE_LOCK RemoveLock,
    _In_opt_ PVOID Tag,
    _In_ ULONG RemlockSize);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoReleaseVpbSpinLock (
    _In_ KIRQL Irql);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoRemoveShareAccess (
    _In_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoReplaceFileObjectName (
    _In_ PFILE_OBJECT FileObject,
    _In_reads_bytes_(FileNameLength) PWSTR NewFileName,
    _In_ USHORT FileNameLength);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoReplacePartitionUnit (
    _In_ PDEVICE_OBJECT TargetPdo,
    _In_ PDEVICE_OBJECT SparePdo,
    _In_ ULONG Flags);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
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
    _Inout_ PDEVICE_OBJECT *DeviceObject);

//@ stdcall -stub IoReportHalResourceUsage(ptr ptr ptr long)

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoReportInterruptActive (
    _In_ PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS Parameters);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoReportInterruptInactive (
    _In_ PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS Parameters);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoReportResourceForDetection (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_reads_bytes_opt_(DriverListSize) PCM_RESOURCE_LIST DriverList,
    _In_opt_ ULONG DriverListSize,
    _In_opt_ PDEVICE_OBJECT DeviceObject,
    _In_reads_bytes_opt_(DeviceListSize) PCM_RESOURCE_LIST DeviceList,
    _In_opt_ ULONG DeviceListSize,
    _Out_ PBOOLEAN ConflictDetected);

// ntosp.h
DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("IoReportResourceForDetection if needed", "Obsolete")
NTKERNELAPI
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
    _Out_ PBOOLEAN ConflictDetected);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoReportRootDevice (
    _In_ PDRIVER_OBJECT DriverObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoReportTargetDeviceChange (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ PVOID NotificationStructure);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoReportTargetDeviceChangeAsynchronous (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ PVOID NotificationStructure,
    _In_opt_ PDEVICE_CHANGE_COMPLETE_CALLBACK Callback,
    _In_opt_ PVOID Context);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoRequestDeviceEject (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoRequestDeviceEjectEx (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_opt_ PIO_DEVICE_EJECT_CALLBACK Callback,
    _In_opt_ PVOID Context,
    _In_opt_ PDRIVER_OBJECT DriverObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoRequestDeviceRemovalForReset (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ ULONG Flags);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoReserveDependency (
    _In_ PDEVICE_OBJECT DependentDevice,
    _In_ PCUNICODE_STRING ProviderId,
    _In_ ULONG DependencyTypes);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoResolveDependency (
    _In_ PCUNICODE_STRING BindingId,
    _In_ PDEVICE_OBJECT Device);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoRetrievePriorityInfo (
    _In_opt_ PIRP Irp,
    _In_opt_ PFILE_OBJECT FileObject,
    _In_opt_ PETHREAD Thread,
    _Inout_ PIO_PRIORITY_INFO PriorityInfo);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoReuseIrp (
    _Inout_ PIRP Irp,
    _In_ NTSTATUS Iostatus);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetActivityIdIrp (
    _Inout_ PIRP Irp,
    _In_opt_ LPCGUID Guid);

// ntosp.h
NTKERNELAPI
LPCGUID
NTAPI
IoSetActivityIdThread (
    _In_ LPCGUID ActivityId);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
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
    _In_ BOOLEAN InvokeOnCancel);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetDependency (
    _In_ PDEVICE_OBJECT DependentDevice,
    _In_ PDEVICE_OBJECT ProviderDevice,
    _In_ ULONG DependencyTypes);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoSetDeviceInterfacePropertyData (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ CONST DEVPROPKEY *PropertyKey,
    _In_ LCID Lcid,
    _In_ ULONG Flags,
    _In_ DEVPROPTYPE Type,
    _In_ ULONG Size,
    _In_reads_bytes_opt_(Size) PVOID Data);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoSetDeviceInterfaceState (
    _In_ PUNICODE_STRING SymbolicLinkName,
    _In_ BOOLEAN Enable);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTKERNELAPI
NTSTATUS
NTAPI
IoSetDevicePropertyData (
    _In_ PDEVICE_OBJECT Pdo,
    _In_ CONST DEVPROPKEY *PropertyKey,
    _In_ LCID Lcid,
    _In_ ULONG Flags,
    _In_ DEVPROPTYPE Type,
    _In_ ULONG Size,
    _In_reads_bytes_opt_(Size) PVOID Data);

// ntifs.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoSetDeviceToVerify (
    _In_ PETHREAD Thread,
    _In_opt_ PDEVICE_OBJECT DeviceObject);

// ntddk-h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetFileObjectIgnoreSharing (
  _In_ PFILE_OBJECT FileObject);

// ntddk-h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetFileOrigin (
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN Remote);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetFsTrackOffsetState (
    _Inout_ PIRP Irp,
    _In_ PIO_IRP_EXT_TRACK_OFFSET_HEADER FsTrackOffsetBlob,
    _In_ LONGLONG TrackedOffset);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetFsZeroingOffset (
    _Inout_ PIRP Irp,
    _In_ ULONG ZeroingOffset);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetFsZeroingOffsetRequired (
    _Inout_ PIRP Irp);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetGenericIrpExtension (
    _In_ PIRP Irp,
    _In_reads_(GenericExtensionDataSize) PUCHAR GenericExtensionData,
    _In_ USHORT GenericExtensionDataSize,
    _In_ BOOLEAN OverwriteIfPresent);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoSetHardErrorOrVerifyDevice (
    _In_ PIRP Irp,
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetInformation (
    _In_ PFILE_OBJECT FileObject,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG Length,
    _In_ PVOID FileInformation);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetIoCompletion (
    _In_ PVOID IoCompletion,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation,
    _In_ BOOLEAN Quota);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetIoCompletionEx (
    _In_ PVOID IoCompletion,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation,
    _In_ BOOLEAN Quota,
    _In_opt_ PIO_MINI_COMPLETION_PACKET_USER MiniPacket);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetIoPriorityHint (
    _In_ PIRP Irp,
    _In_ IO_PRIORITY_HINT PriorityHint);

// ntosifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetIoPriorityHintIntoFileObject (
    _In_ PFILE_OBJECT FileObject,
    _In_ IO_PRIORITY_HINT PriorityHint);

// ntosifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetIoPriorityHintIntoThread (
    _In_ PETHREAD Thread,
    _In_ IO_PRIORITY_HINT PriorityHint);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetIrpExtraCreateParameter (
    _Inout_ PIRP Irp,
    _In_ struct _ECP_LIST *ExtraCreateParameter);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoSetMasterIrpStatus (
    _Inout_ PIRP MasterIrp,
    _In_ NTSTATUS Status);

// ntifs.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("IoSetPartitionInformationEx", "Obsolete")
NTKERNELAPI
NTSTATUS
FASTCALL
IoSetPartitionInformation (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG PartitionNumber,
    _In_ ULONG PartitionType);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoSetPartitionInformationEx (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG PartitionNumber,
    _In_ struct _SET_PARTITION_INFORMATION_EX* PartitionInfo);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoSetShareAccess (
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Out_ PSHARE_ACCESS ShareAccess);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoSetShareAccessEx (
    _In_  ACCESS_MASK DesiredAccess,
    _In_  ULONG DesiredShareAccess,
    _Inout_ PFILE_OBJECT FileObject,
    _Out_ PSHARE_ACCESS ShareAccess,
    _In_ PBOOLEAN WritePermission);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoSetStartIoAttributes (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN DeferredStartIo,
    _In_ BOOLEAN NonCancelable);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSetSystemPartition (
    _In_ PUNICODE_STRING VolumeNameString);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
NTAPI
IoSetThreadHardErrorMode (
    _In_ BOOLEAN EnableHardErrors);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoSetTopLevelIrp (
    _In_opt_ PIRP Irp);

// ntosp.h
NTKERNELAPI
USHORT
NTAPI
IoSizeofGenericIrpExtension (
    VOID);

// ntosp.h
NTKERNELAPI
ULONG
NTAPI
IoSizeofWorkItem (
    VOID);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL) _IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoStartNextPacket (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN Cancelable);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoStartNextPacketByKey (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN Cancelable,
    _In_ ULONG Key);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoStartPacket (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp,
    _In_opt_ PULONG Key,
    _In_opt_ PDRIVER_CANCEL CancelFunction);

#if defined(_AMD64_) || defined(_X86_)
// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoStartTimer (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoStopTimer (
    _In_ PDEVICE_OBJECT DeviceObject);
#endif

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSynchronousCallDriver (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIRP Irp);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSynchronousInvalidateDeviceRelations (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ DEVICE_RELATION_TYPE Type);

// ntifs.h
NTKERNELAPI
NTSTATUS
NTAPI
IoSynchronousPageWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MemoryDescriptorList,
    _In_ PLARGE_INTEGER StartingOffset,
    _In_ PKEVENT Event,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoTestDependency (
    _In_ PDEVICE_OBJECT Dependent,
    _In_ PDEVICE_OBJECT Provider,
    _Out_ PPNP_DEPENDENCY_PATH_TYPE PathType,
    _Out_ PULONG DependencyTypes);

// ntosp.h
NTKERNELAPI
PEPROCESS
NTAPI
IoThreadToProcess (
    _In_ PETHREAD Thread);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoTransferActivityId (
    _In_ LPCGUID ActivityId,
    _In_ LPCGUID RelatedActivityId);

// ntosp.h
NTKERNELAPI
BOOLEAN
NTAPI
IoTranslateBusAddress (
    _In_ INTERFACE_TYPE InterfaceType,
    _In_ ULONG BusNumber,
    _In_ PHYSICAL_ADDRESS BusAddress,
    _Inout_ PULONG AddressSpace,
    _Out_ PPHYSICAL_ADDRESS TranslatedAddress);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
NTAPI
IoTryQueueWorkItem (
    _Inout_ __drv_when(return != 0, __drv_aliasesMem) PIO_WORKITEM IoWorkItem,
    _In_ PIO_WORKITEM_ROUTINE_EX WorkerRoutine,
    _In_ WORK_QUEUE_TYPE QueueType,
    _In_opt_ __drv_aliasesMem PVOID Context);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoUninitializeWorkItem (
    _Inout_ PIO_WORKITEM IoWorkItem);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoUnregisterBootDriverCallback (
    _In_ PVOID CallbackHandle);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoUnregisterContainerNotification (
    _In_ PVOID CallbackRegistration);

// ntifs.h
NTKERNELAPI
VOID
NTAPI
IoUnregisterFileSystem (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntifs.h
NTKERNELAPI
VOID
NTAPI
IoUnregisterFsRegistrationChange (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDRIVER_FS_NOTIFICATION DriverNotificationRoutine);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoUnregisterIoTracking (
    _In_ PVOID IoTracker);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoUnregisterPlugPlayNotification (
    _In_ __drv_freesMem(Pool) PVOID NotificationEntry);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoUnregisterPlugPlayNotificationEx (
    _In_ __drv_freesMem(Pool) PVOID NotificationEntry);

// ntosp.h
NTKERNELAPI
VOID
NTAPI
IoUnregisterPriorityCallback (
    _In_ PDRIVER_OBJECT DriverObject);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoUnregisterShutdownNotification (
    _In_ PDEVICE_OBJECT DeviceObject);

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoUpdateShareAccess (
    _In_ PFILE_OBJECT FileObject,
    _Inout_ PSHARE_ACCESS ShareAccess);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoValidateDeviceIoControlAccess (
    _In_ PIRP Irp,
    _In_ ULONG RequiredAccess);

NTKERNELAPI
NTSTATUS
NTAPI
IoVerifyPartitionTable (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN FixErrors);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoVerifyVolume (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ BOOLEAN AllowRawMount);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoVolumeDeviceToDosName (
    _In_ PVOID VolumeDeviceObject,
    _Out_ _When_(return==0, _At_(DosName->Buffer, __drv_allocatesMem(Mem)))
          PUNICODE_STRING DosName);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoVolumeDeviceToGuid (
    _In_ PVOID VolumeDeviceObject,
    _Out_ GUID *Guid);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoVolumeDeviceToGuidPath (
    _In_ PVOID VolumeDeviceObject,
    _Out_ _When_(return==0, _At_(DosName->Buffer, __drv_allocatesMem(Mem)))
          PUNICODE_STRING GuidPath);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIAllocateInstanceIds (
    _In_ LPCGUID Guid,
    _In_ ULONG InstanceCount,
    _Out_ ULONG *FirstInstanceId);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIDeviceObjectToInstanceName (
    _In_ PVOID DataBlockObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_ PUNICODE_STRING InstanceName);

// ntosp.h
#if defined(_WIN64)
NTKERNELAPI
ULONG
NTAPI
IoWMIDeviceObjectToProviderId (
    _In_ PDEVICE_OBJECT DeviceObject);
#else
#define IoWMIDeviceObjectToProviderId(DeviceObject) ((ULONG)(DeviceObject))
#endif

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIExecuteMethod (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _In_ ULONG MethodId,
    _In_ ULONG InBufferSize,
    _Inout_ PULONG OutBufferSize,
    _Inout_updates_bytes_to_opt_(*OutBufferSize, InBufferSize) PUCHAR InOutBuffer);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIHandleToInstanceName (
    _In_ PVOID DataBlockObject,
    _In_ HANDLE FileHandle,
    _Out_ PUNICODE_STRING InstanceName);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIOpenBlock (
    _In_ LPCGUID Guid,
    _In_ ULONG DesiredAccess,
    _Out_ PVOID *DataBlockObject);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIQueryAllData (
    _In_ PVOID DataBlockObject,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIQueryAllDataMultiple (
    _In_reads_(ObjectCount) PVOID *DataBlockObjectList,
    _In_ ULONG ObjectCount,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIQuerySingleInstance (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIQuerySingleInstanceMultiple (
    _In_reads_(ObjectCount) PVOID *DataBlockObjectList,
    _In_reads_(ObjectCount) PUNICODE_STRING InstanceNames,
    _In_ ULONG ObjectCount,
    _Inout_ PULONG InOutBufferSize,
    _Out_writes_bytes_opt_(*InOutBufferSize) PVOID OutBuffer);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIRegistrationControl (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG Action);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMISetNotificationCallback (
    _Inout_ PVOID Object,
    _In_ WMI_NOTIFICATION_CALLBACK Callback,
    _In_opt_ PVOID Context);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMISetSingleInstance (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _In_ ULONG Version,
    _In_ ULONG ValueBufferSize,
    _In_reads_bytes_(ValueBufferSize) PVOID ValueBuffer);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMISetSingleItem (
    _In_ PVOID DataBlockObject,
    _In_ PUNICODE_STRING InstanceName,
    _In_ ULONG DataItemId,
    _In_ ULONG Version,
    _In_ ULONG ValueBufferSize,
    _In_reads_bytes_(ValueBufferSize) PVOID ValueBuffer);

// ntosp.h
NTKERNELAPI
NTSTATUS
NTAPI
IoWMISuggestInstanceName (
    _In_opt_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_opt_ PUNICODE_STRING SymbolicLinkName,
    _In_ BOOLEAN CombineNames,
    _Out_ PUNICODE_STRING SuggestedInstanceName);

// ntosp.h
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Ret_range_(<=, 0)
NTKERNELAPI
NTSTATUS
NTAPI
IoWMIWriteEvent (
    _Inout_ _When_(return==0, __drv_aliasesMem) PVOID WnodeEventItem);

// ntosp.h
NTKERNELAPI
LOGICAL
NTAPI
IoWithinStackLimits (
    _In_ ULONG_PTR RegionStart,
    _In_ SIZE_T RegionSize);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
IoWriteErrorLogEntry (
    _In_ PVOID ElEntry);

// ntosp.h
DECLSPEC_DEPRECATED_DDK
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("IoWritePartitionTableEx", "Obsolete")
NTKERNELAPI
NTSTATUS
FASTCALL
IoWritePartitionTable (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG SectorsPerTrack,
    _In_ ULONG NumberOfHeads,
    _In_ struct _DRIVE_LAYOUT_INFORMATION *PartitionBuffer);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoWritePartitionTableEx (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_reads_(_Inexpressible_(FIELD_OFFSET(DRIVE_LAYOUT_INFORMATION_EX, PartitionEntry[0])))
        struct _DRIVE_LAYOUT_INFORMATION_EX* DriveLayout);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
_Success_(TRUE)
NTKERNELAPI
NTSTATUS
FASTCALL
IofCallDriver (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ __drv_aliasesMem PIRP Irp);

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
FASTCALL
IofCompleteRequest (
    _In_ PIRP Irp,
    _In_ CCHAR PriorityBoost);

#endif // 0
