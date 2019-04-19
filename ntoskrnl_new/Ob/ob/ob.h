

typedef struct _OBJECT_CREATE_INFORMATION
{
    ULONG Attributes;
    PVOID RootDirectory;
    CHAR ProbeMode;
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    ULONG SecurityDescriptorCharge;
    PVOID SecurityDescriptor;
    struct _SECURITY_QUALITY_OF_SERVICE* SecurityQos;
    struct _SECURITY_QUALITY_OF_SERVICE SecurityQualityOfService;
} OBJECT_CREATE_INFORMATION, *POBJECT_CREATE_INFORMATION;

typedef struct _DEVICE_MAP
{
    struct _OBJECT_DIRECTORY* DosDevicesDirectory;
    struct _OBJECT_DIRECTORY* GlobalDosDevicesDirectory;
    PVOID DosDevicesDirectoryHandle;
    ULONG ReferenceCount;
    ULONG DriveMap;
    UINT8 DriveType[32];
} DEVICE_MAP, *PDEVICE_MAP;


extern struct _OBJECT_DIRECTORY *ObpRootDirectoryObject;
extern KGUARDED_MUTEX ObpDeviceMapLock;
extern POBJECT_TYPE ObpTypeObjectType;
extern PDEVICE_MAP NTSYSAPI ObSystemDeviceMap;


NTSTATUS
NTAPI
ObAssignObjectSecurityDescriptor(
    IN PVOID Object,
    IN PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
    IN POOL_TYPE PoolType);

/* exported */
BOOLEAN
NTAPI
ObCheckObjectAccess(
    IN PVOID Object,
    IN OUT PACCESS_STATE AccessState,
    IN BOOLEAN LockHeld,
    IN KPROCESSOR_MODE AccessMode,
    OUT PNTSTATUS ReturnedStatus);

VOID
NTAPI
ObClearProcessHandleTable(
    IN PEPROCESS Process);

NTSTATUS
NTAPI
ObDeassignSecurity(
    IN OUT PSECURITY_DESCRIPTOR *SecurityDescriptor);

VOID
NTAPI
ObDereferenceDeviceMap(
    IN PEPROCESS Process);

LONG
FASTCALL
ObDereferenceObjectEx(
    IN PVOID Object,
    IN LONG Count);

/* exported */
NTSTATUS
NTAPI
ObDuplicateObject(
    IN PEPROCESS SourceProcess,
    IN HANDLE SourceHandle,
    IN PEPROCESS TargetProcess OPTIONAL,
    IN PHANDLE TargetHandle OPTIONAL,
    IN ACCESS_MASK DesiredAccess,
    IN ULONG HandleAttributes,
    IN ULONG Options,
    IN KPROCESSOR_MODE PreviousMode);

VOID
FASTCALL
ObFastDereferenceObject(
    IN PEX_FAST_REF FastRef,
    IN PVOID Object);

PVOID
FASTCALL
ObFastReferenceObject(
    IN PEX_FAST_REF FastRef);

PVOID
FASTCALL
ObFastReferenceObjectLocked(
    IN PEX_FAST_REF FastRef);

PVOID
FASTCALL
ObFastReplaceObject(
    IN PEX_FAST_REF FastRef,
    IN PVOID Object);

VOID
NTAPI
ObFreeObjectCreateInfoBuffer(
    IN PVOID Object);

ULONG
NTAPI
ObGetProcessHandleCount(
    IN PEPROCESS Process);

VOID
NTAPI
ObInheritDeviceMap(
    IN PEPROCESS Parent,
    IN PEPROCESS Process);

VOID
FASTCALL
ObInitializeFastReference(
    IN PEX_FAST_REF FastRef,
    IN PVOID Object);

NTSTATUS
NTAPI
ObInitProcess(
    IN PEPROCESS Parent OPTIONAL,
    IN PEPROCESS Process);

BOOLEAN
NTAPI
ObInitSystem(VOID);

VOID
NTAPI
ObKillProcess(
    IN PEPROCESS Process);

VOID
NTAPI
ObQueryDeviceMapInformation(
    IN PEPROCESS Process,
    OUT PPROCESS_DEVICEMAP_INFORMATION DeviceMapInfo);

NTSTATUS
NTAPI
ObQuerySecurityDescriptorInfo(
    IN PVOID Object,
    IN PSECURITY_INFORMATION SecurityInformation,
    OUT PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN OUT PULONG Length,
    IN PSECURITY_DESCRIPTOR *OutputSecurityDescriptor);

LONG_PTR
FASTCALL
ObReferenceObjectEx(
    IN PVOID Object,
    IN LONG Count);

/* exported */
BOOLEAN
FASTCALL
ObReferenceObjectSafe(
    IN PVOID Object);

/* exported */
NTSTATUS
NTAPI
ObSetSecurityDescriptorInfo(
    IN PVOID Object,
    IN PSECURITY_INFORMATION SecurityInformation,
    IN OUT PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN OUT PSECURITY_DESCRIPTOR *OutputSecurityDescriptor,
    IN POOL_TYPE PoolType,
    IN PGENERIC_MAPPING GenericMapping);

PVOID
NTAPI
ObpAllocateObjectCreateInfoBuffer(
    IN PP_NPAGED_LOOKASIDE_NUMBER Type);

VOID
NTAPI
ObpFreeCapturedAttributes(
    IN PVOID Buffer,
    IN PP_NPAGED_LOOKASIDE_NUMBER Type);

LONG_PTR
FASTCALL
ObfReferenceObjectWithTag(
    IN PVOID Object,
    IN ULONG Tag);

/***** formerly NDK: ****/

#define DOSDEVICE_DRIVE_UNKNOWN                 0
#define DOSDEVICE_DRIVE_CALCULATE               1
#define DOSDEVICE_DRIVE_REMOVABLE               2
#define DOSDEVICE_DRIVE_FIXED                   3
#define DOSDEVICE_DRIVE_REMOTE                  4
#define DOSDEVICE_DRIVE_CDROM                   5
#define DOSDEVICE_DRIVE_RAMDISK                 6

NTSTATUS
NTAPI
ObCreateObjectType(
    IN PUNICODE_STRING TypeName,
    IN POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    IN PVOID Reserved,
    OUT POBJECT_TYPE *ObjectType);

