/*
 * PROJECT:         ReactOS PCI Bus Driver
 * LICENSE:         BSD - See COPYING.ARM in the top level directory
 * FILE:            drivers/bus/pci/pci.h
 * PURPOSE:         Main Header File
 * PROGRAMMERS:     ReactOS Portable Systems Group
 */

#include <initguid.h>
#include <ntifs.h>
#include <ntagp.h>
#include <wdmguid.h>
#include <wchar.h>
#include <acpiioct.h>
#include <drivers/pci/pci.h>
#include <drivers/acpi/acpi.h>
#include "halfuncs.h"
#include "rtlfuncs.h"
#include "vffuncs.h"
#include "bugcodes.h"

//
// Tag used in all pool allocations (Pci Bus)
//
#define PCI_POOL_TAG    'BicP'

//
// Checks if the specified FDO is the FDO for the Root PCI Bus
//
#define PCI_IS_ROOT_FDO(x)                  ((x)->BusRootFdoExtension == x)

//
// Assertions to make sure we are dealing with the right kind of extension
//
#define ASSERT_FDO(x)                       ASSERT((x)->ExtensionType == PciFdoExtensionType);
#define ASSERT_PDO(x)                       ASSERT((x)->ExtensionType == PciPdoExtensionType);

//
// PCI Hack Entry Name Lengths
//
#define PCI_HACK_ENTRY_SIZE                 sizeof(L"VVVVdddd") - sizeof(UNICODE_NULL)
#define PCI_HACK_ENTRY_REV_SIZE             sizeof(L"VVVVddddRR") - sizeof(UNICODE_NULL)
#define PCI_HACK_ENTRY_SUBSYS_SIZE          sizeof(L"VVVVddddssssIIII") - sizeof(UNICODE_NULL)
#define PCI_HACK_ENTRY_FULL_SIZE            sizeof(L"VVVVddddssssIIIIRR") - sizeof(UNICODE_NULL)

//
// PCI Hack Entry Flags
//
#define PCI_HACK_HAS_REVISION_INFO          0x01
#define PCI_HACK_HAS_SUBSYSTEM_INFO         0x02

//
// PCI Interface Flags
//
#define PCI_INTERFACE_PDO                   0x01
#define PCI_INTERFACE_FDO                   0x02
#define PCI_INTERFACE_ROOT                  0x04

//
// Device Extension, Interface, Translator and Arbiter Signatures
//
typedef enum _PCI_SIGNATURE
{
    PciPdoExtensionType = 'icP0',
    PciFdoExtensionType = 'icP1',
    PciArb_Io = 'icP2',
    PciArb_Memory = 'icP3',
    PciArb_Interrupt = 'icP4',
    PciArb_BusNumber = 'icP5',
    PciTrans_Interrupt = 'icP6',
    PciInterface_BusHandler = 'icP7',
    PciInterface_IntRouteHandler = 'icP8',
    PciInterface_PciCb = 'icP9',
    PciInterface_LegacyDeviceDetection = 'icP:',
    PciInterface_PmeHandler = 'icP;',
    PciInterface_DevicePresent = 'icP<',
    PciInterface_NativeIde = 'icP=',
    PciInterface_AgpTarget = 'icP>',
    PciInterface_Location  = 'icP?'
} PCI_SIGNATURE, *PPCI_SIGNATURE;

//
// Device Extension Logic States
//
typedef enum _PCI_STATE
{
    PciNotStarted,
    PciStarted,
    PciDeleted,
    PciStopped,
    PciSurpriseRemoved,
    PciSynchronizedOperation,
    PciMaxObjectState
} PCI_STATE;

//
// IRP Dispatch Logic Style
//
typedef enum _PCI_DISPATCH_STYLE
{
    IRP_COMPLETE,
    IRP_DOWNWARD,
    IRP_UPWARD,
    IRP_DISPATCH,
} PCI_DISPATCH_STYLE;

//
// PCI Hack Entry Information
//
typedef struct _PCI_HACK_ENTRY
{
    USHORT VendorID;
    USHORT DeviceID;
    USHORT SubVendorID;
    USHORT SubSystemID;
    ULONGLONG HackFlags;
    USHORT RevisionID;
    UCHAR Flags;
} PCI_HACK_ENTRY, *PPCI_HACK_ENTRY;

//
// Power State Information for Device Extension
//
typedef struct _PCI_POWER_STATE
{
    SYSTEM_POWER_STATE CurrentSystemState;
    DEVICE_POWER_STATE CurrentDeviceState;
    SYSTEM_POWER_STATE SystemWakeLevel;
    DEVICE_POWER_STATE DeviceWakeLevel;
    DEVICE_POWER_STATE SystemStateMapping[7];
    PIRP WaitWakeIrp;
    PVOID SavedCancelRoutine;
    LONG Paging;
    LONG Hibernate;
    LONG CrashDump;
} PCI_POWER_STATE, *PPCI_POWER_STATE;

//
// Internal PCI Lock Structure
//
typedef struct _PCI_LOCK
{
    LONG Atom;
    BOOLEAN OldIrql;
} PCI_LOCK, *PPCI_LOCK;

//
// Device Extension for a Bus FDO
//
typedef struct _PCI_FDO_EXTENSION
{
    SINGLE_LIST_ENTRY List;
    ULONG ExtensionType;
    struct _PCI_MJ_DISPATCH_TABLE *IrpDispatchTable;
    BOOLEAN DeviceState;
    BOOLEAN TentativeNextState;
    KEVENT SecondaryExtLock;
    PDEVICE_OBJECT PhysicalDeviceObject;
    PDEVICE_OBJECT FunctionalDeviceObject;
    PDEVICE_OBJECT AttachedDeviceObject;
    KEVENT ChildListLock;
    struct _PCI_PDO_EXTENSION *ChildPdoList;
    struct _PCI_FDO_EXTENSION *BusRootFdoExtension;
    struct _PCI_FDO_EXTENSION *ParentFdoExtension;
    struct _PCI_PDO_EXTENSION *ChildBridgePdoList;
    PPCI_BUS_INTERFACE_STANDARD PciBusInterface;
    BOOLEAN MaxSubordinateBus;
    BUS_HANDLER *BusHandler;
    BOOLEAN BaseBus;
    BOOLEAN Fake;
    BOOLEAN ChildDelete;
    BOOLEAN Scanned;
    BOOLEAN ArbitersInitialized;
    BOOLEAN BrokenVideoHackApplied;
    BOOLEAN Hibernated;
    PCI_POWER_STATE PowerState;
    SINGLE_LIST_ENTRY SecondaryExtension;
    LONG ChildWaitWakeCount;
    PPCI_COMMON_CONFIG PreservedConfig;
    PCI_LOCK Lock;
    struct
    {
        BOOLEAN Acquired;
        BOOLEAN CacheLineSize;
        BOOLEAN LatencyTimer;
        BOOLEAN EnablePERR;
        BOOLEAN EnableSERR;
    } HotPlugParameters;
    LONG BusHackFlags;
} PCI_FDO_EXTENSION, *PPCI_FDO_EXTENSION;

//
// IRP Dispatch Function Type
//
typedef NTSTATUS (NTAPI *PCI_DISPATCH_FUNCTION)(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

//
// IRP Dispatch Minor Table
//
typedef struct _PCI_MN_DISPATCH_TABLE
{
    PCI_DISPATCH_STYLE DispatchStyle;
    PCI_DISPATCH_FUNCTION DispatchFunction;
} PCI_MN_DISPATCH_TABLE, *PPCI_MN_DISPATCH_TABLE;

//
// IRP Dispatch Major Table
//
typedef struct _PCI_MJ_DISPATCH_TABLE
{
    ULONG PnpIrpMaximumMinorFunction;
    PPCI_MN_DISPATCH_TABLE PnpIrpDispatchTable;
    ULONG PowerIrpMaximumMinorFunction;
    PPCI_MN_DISPATCH_TABLE PowerIrpDispatchTable;
    PCI_DISPATCH_STYLE SystemControlIrpDispatchStyle;
    PCI_DISPATCH_FUNCTION SystemControlIrpDispatchFunction;
    PCI_DISPATCH_STYLE OtherIrpDispatchStyle;
    PCI_DISPATCH_FUNCTION OtherIrpDispatchFunction;
} PCI_MJ_DISPATCH_TABLE, *PPCI_MJ_DISPATCH_TABLE;

//
// Generic PCI Interface Constructor and Initializer
//
struct _PCI_INTERFACE;
typedef NTSTATUS (NTAPI *PCI_INTERFACE_CONSTRUCTOR)(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

typedef NTSTATUS (NTAPI *PCI_INTERFACE_INITIALIZER)(
    IN PVOID Instance
);

//
// Generic PCI Interface (Interface, Translator, Arbiter)
//
typedef struct _PCI_INTERFACE
{
    CONST GUID *InterfaceType;
    USHORT MinSize;
    USHORT MinVersion;
    USHORT MaxVersion;
    USHORT Flags;
    LONG ReferenceCount;
    PCI_SIGNATURE Signature;
    PCI_INTERFACE_CONSTRUCTOR Constructor;
    PCI_INTERFACE_INITIALIZER Initializer;
} PCI_INTERFACE, *PPCI_INTERFACE;

//
// Generic Secondary Extension Instance Header (Interface, Translator, Arbiter)
//
typedef struct PCI_SECONDARY_EXTENSION
{
    SINGLE_LIST_ENTRY List;
    PCI_SIGNATURE ExtensionType;
    PVOID Destructor;
} PCI_SECONDARY_EXTENSION, *PPCI_SECONDARY_EXTENSION;

//
// PCI Arbiter Instance
//
typedef struct PCI_ARBITER_INSTANCE
{
    PCI_SECONDARY_EXTENSION Header;
    PPCI_INTERFACE Interface;
    PPCI_FDO_EXTENSION BusFdoExtension;
    WCHAR InstanceName[24];
    //ARBITER_INSTANCE CommonInstance; FIXME: Need Arbiter Headers
} PCI_ARBITER_INSTANCE, *PPCI_ARBITER_INSTANCE;

//
// IRP Dispatch Routines
//
NTSTATUS
NTAPI
PciDispatchIrp(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
);

NTSTATUS
NTAPI
PciIrpNotSupported(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciPassIrpFromFdoToPdo(
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN PIRP Irp
);

NTSTATUS
NTAPI
PciCallDownIrpStack(
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN PIRP Irp
);

//
// Power Routines
//
NTSTATUS
NTAPI
PciFdoWaitWake(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoSetPowerState(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpQueryPower(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

//
// Bus FDO Routines
//
NTSTATUS
NTAPI
PciAddDevice(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT PhysicalDeviceObject
);

NTSTATUS
NTAPI
PciFdoIrpStartDevice(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpQueryRemoveDevice(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpRemoveDevice(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpCancelRemoveDevice(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpStopDevice(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpQueryStopDevice(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpCancelStopDevice(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpQueryDeviceRelations(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpQueryInterface(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpQueryCapabilities(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpDeviceUsageNotification(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpSurpriseRemoval(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciFdoIrpQueryLegacyBusInformation(
    IN PIRP Irp,
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension
);

//
// HAL Callback/Hook Routines
//
VOID
NTAPI
PciHookHal(
    VOID
);

//
// PCI Verifier Routines
//
VOID
NTAPI
PciVerifierInit(
    IN PDRIVER_OBJECT DriverObject
);

//
// Utility Routines
//
BOOLEAN
NTAPI
PciStringToUSHORT(
    IN PWCHAR String,
    OUT PUSHORT Value
);

BOOLEAN
NTAPI
PciIsDatacenter(
    VOID
);

NTSTATUS
NTAPI
PciBuildDefaultExclusionLists(
    VOID
);

BOOLEAN
NTAPI
PciUnicodeStringStrStr(
    IN PUNICODE_STRING InputString,
    IN PCUNICODE_STRING EqualString,
    IN BOOLEAN CaseInSensitive
);

BOOLEAN
NTAPI
PciOpenKey(
    IN PWCHAR KeyName,
    IN HANDLE RootKey,
    IN ACCESS_MASK DesiredAccess,
    OUT PHANDLE KeyHandle,
    OUT PNTSTATUS KeyStatus
);

NTSTATUS
NTAPI
PciGetRegistryValue(
    IN PWCHAR ValueName,
    IN PWCHAR KeyName,
    IN HANDLE RootHandle,
    IN ULONG Type,
    OUT PVOID *OutputBuffer,
    OUT PULONG OutputLength
);

PPCI_FDO_EXTENSION
NTAPI
PciFindParentPciFdoExtension(
    IN PDEVICE_OBJECT DeviceObject,
    IN PKEVENT Lock
);

VOID
NTAPI
PciInsertEntryAtTail(
    IN PSINGLE_LIST_ENTRY ListHead,
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN PKEVENT Lock
);

NTSTATUS
NTAPI
PciGetDeviceProperty(
    IN PDEVICE_OBJECT DeviceObject,
    IN DEVICE_REGISTRY_PROPERTY DeviceProperty,
    OUT PVOID *OutputBuffer
);

NTSTATUS
NTAPI
PciSendIoctl(
    IN PDEVICE_OBJECT DeviceObject,
    IN ULONG IoControlCode,
    IN PVOID InputBuffer,
    IN ULONG InputBufferLength,
    IN PVOID OutputBuffer,
    IN ULONG OutputBufferLength
);

VOID
NTAPI
PcipLinkSecondaryExtension(
    IN PSINGLE_LIST_ENTRY List,
    IN PVOID Lock,
    IN PPCI_SECONDARY_EXTENSION SecondaryExtension,
    IN PCI_SIGNATURE ExtensionType,
    IN PVOID Destructor
);

PPCI_SECONDARY_EXTENSION
NTAPI
PciFindNextSecondaryExtension(
    IN PSINGLE_LIST_ENTRY ListHead,
    IN PCI_SIGNATURE ExtensionType
);

//
// Configuration Routines
//
NTSTATUS
NTAPI
PciGetConfigHandlers(
    IN PPCI_FDO_EXTENSION FdoExtension
);

//
// State Machine Logic Transition Routines
//
VOID
NTAPI
PciInitializeState(
    IN PPCI_FDO_EXTENSION DeviceExtension
);

NTSTATUS
NTAPI
PciBeginStateTransition(
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN PCI_STATE NewState
);

NTSTATUS
NTAPI
PciCancelStateTransition(
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN PCI_STATE NewState
);

VOID
NTAPI
PciCommitStateTransition(
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN PCI_STATE NewState
);


//
// Arbiter Support
//
NTSTATUS
NTAPI
PciInitializeArbiters(
    IN PPCI_FDO_EXTENSION FdoExtension
);

NTSTATUS
NTAPI
PciInitializeArbiterRanges(
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN PCM_RESOURCE_LIST Resources
);

//
// Debug Helpers
//
BOOLEAN
NTAPI
PciDebugIrpDispatchDisplay(
    IN PIO_STACK_LOCATION IoStackLocation,
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN USHORT MaxMinor
);

//
// Interface Support
//
NTSTATUS
NTAPI
PciQueryInterface(
    IN PPCI_FDO_EXTENSION DeviceExtension,
    IN CONST GUID* InterfaceType,
    IN ULONG Size,
    IN ULONG Version,
    IN PVOID InterfaceData,
    IN PINTERFACE Interface,
    IN BOOLEAN LastChance
);

NTSTATUS
NTAPI
PciPmeInterfaceInitializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
routeintrf_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
arbusno_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
agpintrf_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
tranirq_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
busintrf_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
armem_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
ario_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
locintrf_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
pcicbintrf_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
lddintrf_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
devpresent_Initializer(
    IN PVOID Instance
);

NTSTATUS
NTAPI
agpintrf_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
arbusno_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
tranirq_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
armem_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
busintrf_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
ario_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
pcicbintrf_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
lddintrf_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
locintrf_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
PciPmeInterfaceConstructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
routeintrf_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

NTSTATUS
NTAPI
devpresent_Constructor(
    IN PVOID DeviceExtension,
    IN PVOID Instance,
    IN PVOID InterfaceData,
    IN USHORT Version,
    IN USHORT Size,
    IN PINTERFACE Interface
);

//
// External Resources
//
extern SINGLE_LIST_ENTRY PciFdoExtensionListHead;
extern KEVENT PciGlobalLock;
extern PPCI_INTERFACE PciInterfaces[];
extern PCI_INTERFACE ArbiterInterfaceBusNumber;
extern PCI_INTERFACE ArbiterInterfaceMemory;
extern PCI_INTERFACE ArbiterInterfaceIo;
extern PCI_INTERFACE BusHandlerInterface;
extern PCI_INTERFACE PciRoutingInterface;
extern PCI_INTERFACE PciCardbusPrivateInterface;
extern PCI_INTERFACE PciLegacyDeviceDetectionInterface;
extern PCI_INTERFACE PciPmeInterface;
extern PCI_INTERFACE PciDevicePresentInterface;
//extern PCI_INTERFACE PciNativeIdeInterface;
extern PCI_INTERFACE PciLocationInterface;
extern PCI_INTERFACE AgpTargetInterface;
extern PCI_INTERFACE TranslatorInterfaceInterrupt;

/* EOF */