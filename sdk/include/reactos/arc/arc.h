#ifndef _ARC_
#define _ARC_

#ifndef NTLDR_VERSION
#define NTLDR_VERSION NTDDI_VISTASP1 // This is what ReactOS uses
#endif

typedef ULONG ARC_STATUS;

/* Avoid conflicts with errno.h */
#undef E2BIG
#undef EACCES
#undef EAGAIN
#undef EBADF
#undef EBUSY
#undef EFAULT
#undef EINVAL
#undef EIO
#undef EISDIR
#undef EMFILE
#undef EMLINK
#undef ENAMETOOLONG
#undef ENODEV
#undef ENOENT
#undef ENOEXEC
#undef ENOMEM
#undef ENOSPC
#undef ENOTDIR
#undef ENOTTY
#undef ENXIO
#undef EROFS
#undef EMAXIMUM

typedef enum _ARC_CODES
{
    ESUCCESS,
    E2BIG,
    EACCES,
    EAGAIN,
    EBADF,
    EBUSY,
    EFAULT,
    EINVAL,
    EIO,
    EISDIR,
    EMFILE,
    EMLINK,
    ENAMETOOLONG,
    ENODEV,
    ENOENT,
    ENOEXEC,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    ENOTTY,
    ENXIO,
    EROFS,
    EMAXIMUM
} ARC_CODES;

typedef enum _SEEKMODE
{
    SeekAbsolute,
    SeekRelative,
} SEEKMODE;

typedef enum _OPENMODE
{
    OpenReadOnly,
    OpenWriteOnly,
    OpenReadWrite,
    CreateWriteOnly,
    CreateReadOnly,
    SupersedeWriteOnly,
    SupersedeReadOnly,
    SupersedeReadWrite,
    OpenDirectory,
    CreateDirectory,
} OPENMODE;

typedef enum _IDENTIFIER_FLAG
{
    Failed = 0x01,
    ReadOnly = 0x02,
    Removable = 0x04,
    ConsoleIn = 0x08,
    ConsoleOut = 0x10,
    Input = 0x20,
    Output = 0x40
} IDENTIFIER_FLAG;

typedef enum _CONFIGURATION_CLASS
{
    SystemClass,
    ProcessorClass,
    CacheClass,
    AdapterClass,
    ControllerClass,
    PeripheralClass,
    MemoryClass,
    MaximumClass
} CONFIGURATION_CLASS;

// CONFIGURATION_TYPE is also defined in ntddk.h
#ifndef _ARC_DDK_
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
#endif /* _ARC_DDK_ */

typedef struct _CONFIGURATION_COMPONENT
{
    CONFIGURATION_CLASS Class;
    CONFIGURATION_TYPE Type;
    IDENTIFIER_FLAG Flags;
    USHORT Version;
    USHORT Revision;
    ULONG Key;
    ULONG AffinityMask;
    ULONG ConfigurationDataLength;
    ULONG IdentifierLength;
    PCHAR Identifier;
} CONFIGURATION_COMPONENT, *PCONFIGURATION_COMPONENT;

typedef struct _CONFIGURATION_COMPONENT_DATA
{
    struct _CONFIGURATION_COMPONENT_DATA *Parent;
    struct _CONFIGURATION_COMPONENT_DATA *Child;
    struct _CONFIGURATION_COMPONENT_DATA *Sibling;
    CONFIGURATION_COMPONENT ComponentEntry;
    PVOID ConfigurationData;
} CONFIGURATION_COMPONENT_DATA, *PCONFIGURATION_COMPONENT_DATA;

typedef enum _TYPE_OF_MEMORY
{
    LoaderExceptionBlock,
    LoaderSystemBlock,
    LoaderFree,
    LoaderBad,
    LoaderLoadedProgram,
    LoaderFirmwareTemporary,
    LoaderFirmwarePermanent,
    LoaderOsloaderHeap,
    LoaderOsloaderStack,
    LoaderSystemCode,
    LoaderHalCode,
    LoaderBootDriver,
    LoaderConsoleInDriver,
    LoaderConsoleOutDriver,
    LoaderStartupDpcStack,
    LoaderStartupKernelStack,
    LoaderStartupPanicStack,
    LoaderStartupPcrPage,
    LoaderStartupPdrPage,
    LoaderRegistryData,
    LoaderMemoryData,
    LoaderNlsData,
    LoaderSpecialMemory,
    LoaderBBTMemory,
    LoaderReserve,
    LoaderXIPRom,
    LoaderHALCachedMemory,
    LoaderLargePageFiller,
    LoaderErrorLogMemory,
    LoaderMaximum
} TYPE_OF_MEMORY;

typedef enum _MEMORY_TYPE
{
    MemoryExceptionBlock,
    MemorySystemBlock,
    MemoryFree,
    MemoryBad,
    MemoryLoadedProgram,
    MemoryFirmwareTemporary,
    MemoryFirmwarePermanent,
    MemoryFreeContiguous,
    MemorySpecialMemory,
    MemoryMaximum
} MEMORY_TYPE;

typedef struct _TIMEINFO
{
    USHORT Year;
    USHORT Month;
    USHORT Day;
    USHORT Hour;
    USHORT Minute;
    USHORT Second;
} TIMEINFO;

typedef struct _MEMORY_DESCRIPTOR
{
    MEMORY_TYPE MemoryType;
    PFN_NUMBER BasePage;
    PFN_NUMBER PageCount;
} MEMORY_DESCRIPTOR, *PMEMORY_DESCRIPTOR;

typedef struct _MEMORY_ALLOCATION_DESCRIPTOR
{
    LIST_ENTRY ListEntry;
    TYPE_OF_MEMORY MemoryType;
    PFN_NUMBER BasePage;
    PFN_NUMBER PageCount;
} MEMORY_ALLOCATION_DESCRIPTOR, *PMEMORY_ALLOCATION_DESCRIPTOR;

typedef struct _BOOT_DRIVER_LIST_ENTRY
{
    LIST_ENTRY Link;
    UNICODE_STRING FilePath;
    UNICODE_STRING RegistryPath;
    struct _LDR_DATA_TABLE_ENTRY *LdrEntry;
} BOOT_DRIVER_LIST_ENTRY, *PBOOT_DRIVER_LIST_ENTRY;

typedef struct _ARC_DISK_SIGNATURE
{
    LIST_ENTRY ListEntry;
    ULONG Signature;
    PCHAR ArcName;
    ULONG CheckSum;
    BOOLEAN ValidPartitionTable;
    BOOLEAN xInt13;
    BOOLEAN IsGpt;
    BOOLEAN Reserved;
    CHAR GptSignature[16];
} ARC_DISK_SIGNATURE, *PARC_DISK_SIGNATURE;

typedef struct _ARC_DISK_INFORMATION
{
    LIST_ENTRY DiskSignatureListHead;
} ARC_DISK_INFORMATION, *PARC_DISK_INFORMATION;

typedef struct _MONITOR_CONFIGURATION_DATA
{
    USHORT Version;
    USHORT Revision;
    USHORT HorizontalResolution;
    USHORT HorizontalDisplayTime;
    USHORT HorizontalBackPorch;
    USHORT HorizontalFrontPorch;
    USHORT HorizontalSync;
    USHORT VerticalResolution;
    USHORT VerticalBackPorch;
    USHORT VerticalFrontPorch;
    USHORT VerticalSync;
    USHORT HorizontalScreenSize;
    USHORT VerticalScreenSize;
} MONITOR_CONFIGURATION_DATA, *PMONITOR_CONFIGURATION_DATA;

typedef struct _FLOPPY_CONFIGURATION_DATA
{
    USHORT Version;
    USHORT Revision;
    CHAR Size[8];
    ULONG MaxDensity;
    ULONG MountDensity;
} FLOPPY_CONFIGURATION_DATA, *PFLOPPY_CONFIGURATION_DATA;

//
// SMBIOS Table Header (FIXME: maybe move to smbios.h?)
//
typedef struct _SMBIOS_TABLE_HEADER
{
   CHAR Signature[4];
   UCHAR Checksum;
   UCHAR Length;
   UCHAR MajorVersion;
   UCHAR MinorVersion;
   USHORT MaximumStructureSize;
   UCHAR EntryPointRevision;
   UCHAR Reserved[5];
   CHAR Signature2[5];
   UCHAR IntermediateChecksum;
   USHORT StructureTableLength;
   ULONG StructureTableAddress;
   USHORT NumberStructures;
   UCHAR Revision;
} SMBIOS_TABLE_HEADER, *PSMBIOS_TABLE_HEADER;

typedef struct _SMBIOS3_TABLE_HEADER
{
   UCHAR Signature[5];
   UCHAR Checksum;
   UCHAR Length;
   UCHAR MajorVersion;
   UCHAR MinorVersion;
   UCHAR Docrev;
   UCHAR EntryPointRevision;
   UCHAR Reserved;
   ULONG StructureTableMaximumSize;
   ULONG64 StructureTableAddress;
} SMBIOS3_TABLE_HEADER, *PSMBIOS3_TABLE_HEADER;

//
// NLS Data Block
//
typedef struct _NLS_DATA_BLOCK
{
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCodePageData;
} NLS_DATA_BLOCK, *PNLS_DATA_BLOCK;

//
// ACPI Docking State
//
typedef struct _PROFILE_ACPI_DOCKING_STATE
{
    USHORT DockingState;
    USHORT SerialLength;
    WCHAR SerialNumber[1];
} PROFILE_ACPI_DOCKING_STATE, *PPROFILE_ACPI_DOCKING_STATE;

//
// Subsystem Specific Loader Blocks
//
typedef struct _PROFILE_PARAMETER_BLOCK
{
    USHORT Status;
    USHORT Reserved;
    USHORT DockingState;
    USHORT Capabilities;
    ULONG DockID;
    ULONG SerialNumber;
} PROFILE_PARAMETER_BLOCK, *PPROFILE_PARAMETER_BLOCK;

typedef struct _HEADLESS_LOADER_BLOCK
{
    UCHAR UsedBiosSettings;
    UCHAR DataBits;
    UCHAR StopBits;
    UCHAR Parity;
    ULONG BaudRate;
    ULONG PortNumber;
    PUCHAR PortAddress;
    USHORT PciDeviceId;
    USHORT PciVendorId;
    UCHAR PciBusNumber;
#if (NTLDR_VERSION >= NTDDI_VISTA)
    USHORT PciBusSegment;
#endif // (NTLDR_VERSION >= NTDDI_VISTA)
    UCHAR PciSlotNumber;
    UCHAR PciFunctionNumber;
    ULONG PciFlags;
    GUID SystemGUID;
    UCHAR IsMMIODevice;
    UCHAR TerminalType;
#if (NTLDR_VERSION >= NTDDI_WIN10)
    UCHAR InterfaceType;
    UCHAR RegisterBitWidth;
    UCHAR RegisterAccessSize;
#endif // (NTLDR_VERSION >= NTDDI_WIN10)
} HEADLESS_LOADER_BLOCK, *PHEADLESS_LOADER_BLOCK;

typedef struct _NETWORK_LOADER_BLOCK
{
    PCHAR DHCPServerACK;
    ULONG DHCPServerACKLength;
    PCHAR BootServerReplyPacket;
    ULONG BootServerReplyPacketLength;
} NETWORK_LOADER_BLOCK, *PNETWORK_LOADER_BLOCK;

typedef struct _LOADER_PERFORMANCE_DATA
{
    ULONGLONG StartTime;
    ULONGLONG EndTime;
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    ULONGLONG PreloadEndTime;
    ULONGLONG TcbLoaderStartTime;
    ULONGLONG LoadHypervisorTime;
    ULONGLONG LaunchHypervisorTime;
    ULONGLONG LoadVsmTime;
    ULONGLONG LaunchVsmTime;
#if (NTLDR_VERSION >= NTDDI_WIN10_19H1)
    ULONGLONG ExecuteTransitionStartTime;
    ULONGLONG ExecuteTransitionEndTime;
#endif // (NTLDR_VERSION >= NTDDI_WIN10_19H1)
    ULONGLONG LoadDriversTime;
#endif // (NTLDR_VERSION >= NTDDI_WIN10_RS5)
#if (NTLDR_VERSION >= NTDDI_WIN10_19H1)
    ULONGLONG CleanupVsmTime;
#endif // (NTLDR_VERSION >= NTDDI_WIN10_19H1)
} LOADER_PERFORMANCE_DATA, *PLOADER_PERFORMANCE_DATA;

#if (NTLDR_VERSION == NTDDI_WIN7)

typedef enum _TPM_BOOT_ENTROPY_RESULT_CODE
{
    TpmBootEntropyStructureUninitialized = 0,
    TpmBootEntropyDisabledByPolicy = 1,
    TpmBootEntropyNoTpmFound = 2,
    TpmBootEntropyTpmError = 3,
    TpmBootEntropySuccess = 4,
} TPM_BOOT_ENTROPY_RESULT_CODE;

typedef struct _TPM_BOOT_ENTROPY_LDR_RESULT
{
    ULONGLONG Policy;
    TPM_BOOT_ENTROPY_RESULT_CODE ResultCode;
    NTSTATUS ResultStatus;
    ULONGLONG Time;
    ULONG EntropyLength;
    UCHAR EntropyData[4];
    long __PADDING__[1];
} TPM_BOOT_ENTROPY_LDR_RESULT, *PTPM_BOOT_ENTROPY_LDR_RESULT;

#endif // (NTLDR_VERSION == NTDDI_WIN7)

#if (NTLDR_VERSION >= NTDDI_WIN8)

typedef enum _BOOT_ENTROPY_SOURCE_ID
{
    BootEntropySourceNone = 0,
    BootEntropySourceSeedfile = 1,
    BootEntropySourceExternal = 2,
    BootEntropySourceTpm = 3,
    BootEntropySourceRdrand = 4,
    BootEntropySourceTime = 5,
    BootEntropySourceAcpiOem0 = 6,
    BootEntropySourceUefi = 7,

    // Windows 8.1+:
    BootEntropySourceCng = 8,

    // RS5+:
    BootEntropySourceTcbTpm = 9,
    BootEntropySourceTcbRdrand = 10,

    //BootMaxEntropySources = 8,
} BOOT_ENTROPY_SOURCE_ID, *PBOOT_ENTROPY_SOURCE_ID;

typedef enum _BOOT_ENTROPY_SOURCE_RESULT_CODE
{
    BootEntropySourceStructureUninitialized = 0,
    BootEntropySourceDisabledByPolicy = 1,
    BootEntropySourceNotPresent = 2,
    BootEntropySourceError = 3,
    BootEntropySourceSuccess = 4,
} BOOT_ENTROPY_SOURCE_RESULT_CODE, *PBOOT_ENTROPY_SOURCE_RESULT_CODE;

typedef struct _BOOT_ENTROPY_SOURCE_LDR_RESULT
{
    BOOT_ENTROPY_SOURCE_ID SourceId;
    LONG64 Policy;
    BOOT_ENTROPY_SOURCE_RESULT_CODE ResultCode;
    NTSTATUS ResultStatus;
    ULONG64 Time;
    ULONG EntropyLength;
    UCHAR EntropyData[64];
    long __PADDING__[1];
} BOOT_ENTROPY_SOURCE_LDR_RESULT, *PBOOT_ENTROPY_SOURCE_LDR_RESULT;

typedef struct _BOOT_ENTROPY_LDR_RESULT
{
    ULONG maxEntropySources;
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    BOOT_ENTROPY_SOURCE_LDR_RESULT EntropySourceResult[10];
#elif (NTLDR_VERSION >= NTDDI_WINBLUE)
    BOOT_ENTROPY_SOURCE_LDR_RESULT EntropySourceResult[8];
#else // Windows 8
    BOOT_ENTROPY_SOURCE_LDR_RESULT EntropySourceResult[7];
#endif
    UCHAR SeedBytesForCng[48];
    UCHAR RngBytesForNtoskrnl[1024];
#if (NTLDR_VERSION >= NTDDI_WIN10_RS1)
    UCHAR KdEntropy[32];
#endif
} BOOT_ENTROPY_LDR_RESULT, *PBOOT_ENTROPY_LDR_RESULT;

typedef struct _LOADER_PARAMETER_HYPERVISOR_EXTENSION
{
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    ULONG InitialHypervisorCrashdumpAreaPageCount;
#endif
    ULONG HypervisorCrashdumpAreaPageCount;
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    ULONG64 InitialHypervisorCrashdumpAreaSpa;
#endif
    ULONG64 HypervisorCrashdumpAreaSpa;
    ULONG64 HypervisorLaunchStatus;
    ULONG64 HypervisorLaunchStatusArg1;
    ULONG64 HypervisorLaunchStatusArg2;
    ULONG64 HypervisorLaunchStatusArg3;
    ULONG64 HypervisorLaunchStatusArg4;
} LOADER_PARAMETER_HYPERVISOR_EXTENSION, *PLOADER_PARAMETER_HYPERVISOR_EXTENSION;

#endif // (NTLDR_VERSION >= NTDDI_WIN8)

#if (NTLDR_VERSION == NTDDI_WIN8)
typedef struct LOADER_PARAMETER_KD_EXTENSION
{
    ULONG64 Reserved[18];
} LOADER_PARAMETER_KD_EXTENSION, *PLOADER_PARAMETER_KD_EXTENSION;
#endif

#if (NTLDR_VERSION >= NTDDI_WINBLUE)
typedef struct _LOADER_BUGCHECK_PARAMETERS
{
    ULONG BugcheckCode;
    ULONG_PTR BugcheckParameter1;
    ULONG_PTR BugcheckParameter2;
    ULONG_PTR BugcheckParameter3;
    ULONG_PTR BugcheckParameter4;
} LOADER_BUGCHECK_PARAMETERS, *PLOADER_BUGCHECK_PARAMETERS;

typedef struct _OFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V1
{
    UINT32 Version;
    UINT32 AbnormalResetOccurred;
    UINT32 OfflineMemoryDumpCapable;
} OFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V1, *POFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V1;

typedef struct _OFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V2
{
    UINT32 Version;
    UINT32 AbnormalResetOccurred;
    UINT32 OfflineMemoryDumpCapable;
    UINT64 ResetDataAddress;
    UINT32 ResetDataSize;
  /* 0x001c */ long __PADDING__[1];
} OFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V2, *POFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V2;

#endif

//
// Extended Loader Parameter Block
//
// See http://www.geoffchappell.com/studies/windows/km/ntoskrnl/structs/loader_parameter_extension.htm
// for more details.
//
typedef struct _LOADER_PARAMETER_EXTENSION
{
    ULONG Size;
    PROFILE_PARAMETER_BLOCK Profile;
#if (NTLDR_VERSION < NTDDI_WIN7)
    ULONG MajorVersion;
    ULONG MinorVersion;
#endif
    PVOID EmInfFileImage;
    ULONG EmInfFileSize;
    PVOID TriageDumpBlock;
    //
    // NT 5.1
    //
#if (NTLDR_VERSION >= NTDDI_WINXP)
#if (NTLDR_VERSION < NTDDI_WIN8)
    ULONG_PTR LoaderPagesSpanned;
#endif
    PHEADLESS_LOADER_BLOCK HeadlessLoaderBlock;
#if (NTLDR_VERSION >= NTDDI_WIN10)
    PSMBIOS3_TABLE_HEADER SMBiosEPSHeader;
#else
    PSMBIOS_TABLE_HEADER SMBiosEPSHeader;
#endif
    PVOID DrvDBImage;
    ULONG DrvDBSize;
#if (NTLDR_VERSION >= NTDDI_WINXPSP1)
    PNETWORK_LOADER_BLOCK NetworkLoaderBlock;
#endif // (NTLDR_VERSION >= NTDDI_WINXPSP1)

    //
    // NT 5.2+
    //
#ifdef _X86_
    PUCHAR HalpIRQLToTPR;
    PUCHAR HalpVectorToIRQL;
#endif
    LIST_ENTRY FirmwareDescriptorListHead;
#endif // (NTLDR_VERSION >= NTDDI_WINXP)

    //
    // NT 5.2 SP1+
    //
#if (NTLDR_VERSION >= NTDDI_WS03SP1)
    PVOID AcpiTable;
    ULONG AcpiTableSize;
#endif // (NTLDR_VERSION >= NTDDI_WS03SP1)

#if  (NTLDR_VERSION >= NTDDI_VISTA)
    struct
    {
        // NT-version-dependent flags
#if (NTLDR_VERSION == NTDDI_VISTA) || (NTLDR_VERSION == NTDDI_VISTASP1)
        ULONG BootViaWinload:1; // 6.0 only
#endif
#if (NTLDR_VERSION >= NTDDI_WIN7)
        ULONG LastBootSucceeded : 1; // 6.1 and higher
        ULONG LastBootShutdown : 1; // 6.1 and higher
        ULONG IoPortAccessSupported : 1; // 6.1 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN8)
        ULONG BootDebuggerActive : 1; // 6.2 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WINBLUE)
        ULONG StrongCodeGuarantees : 1; // 6.3 and higher
        ULONG HardStrongCodeGuarantees : 1; // 6.3 and higher
        ULONG SidSharingDisabled : 1; // 6.3 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10)
        ULONG TpmInitialized : 1; // 10.0 and higher
        ULONG VsmConfigured : 1; // 10.0 and higher
        ULONG IumEnabled : 1; // 10.0 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_TH2)
        ULONG IsSmbboot : 1; // 1511 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_RS1)
        ULONG BootLogEnabled : 1; // 1607 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
        ULONG DriverVerifierEnabled : 1; // 1809 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_19H1)
        ULONG SuppressMonitorX : 1; // 1903 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_VB)
        ULONG KernelCetEnabled : 1; // 2004 and higher
        ULONG SuppressSmap : 1; // 2004 and higher
#endif
#if (NTLDR_VERSION == NTDDI_WIN10_RS4)
        ULONG FeatureSettings : 7; // 1803 only
#else // ...
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_RS4)
        ULONG FeatureSimulations : 6; // 1803 and higher
#endif
#if (NTLDR_VERSION == NTDDI_WIN10_RS4)
        ULONG MicrocodeOptedOut : 1; // 1803 only
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
        ULONG MicrocodeSelfHosting : 1; // 1809 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_RS4)
        ULONG XhciLegacyHandoffSkip : 1; // 1803 and higher
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
        ULONG DisableInsiderOptInHVCI : 1; // 1809 and higher
#endif
        // ULONG Reserved : ?;
    };
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    LOADER_PERFORMANCE_DATA LoaderPerformanceData;
#else
    PLOADER_PERFORMANCE_DATA LoaderPerformanceData;
#endif // (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    LIST_ENTRY BootApplicationPersistentData;
    PVOID WmdTestResult;
    GUID BootIdentifier;
#endif // (NTLDR_VERSION >= NTDDI_VISTA)

    //
    // NT 6 SP1
    //
#if (NTLDR_VERSION >= NTDDI_VISTASP1)
    ULONG ResumePages;
    PVOID DumpHeader;
#endif // (NTLDR_VERSION >= 0x06000100)

#if (NTLDR_VERSION >= NTDDI_WIN7)
    PVOID BgContext;
    PVOID NumaLocalityInfo;
    PVOID NumaGroupAssignment;
    LIST_ENTRY AttachedHives;
    ULONG MemoryCachingRequirementsCount;
    PVOID MemoryCachingRequirements;
#if (NTLDR_VERSION >= NTDDI_WIN8)
    BOOT_ENTROPY_LDR_RESULT BootEntropyResult;
#else
    TPM_BOOT_ENTROPY_LDR_RESULT TpmBootEntropyResult;
#endif
    ULONG64 ProcessorCounterFrequency;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN8)
    LOADER_PARAMETER_HYPERVISOR_EXTENSION HypervisorExtension;
    GUID HardwareConfigurationId;
    LIST_ENTRY HalExtensionModuleList;
    ULONG64 SystemTime;
    ULONG64 TimeStampAtSystemTimeRead;
    union
    {
        ULONG64 BootFlags;
        struct
        {
            ULONG64 DbgMenuOsSelection : 1; /* bit position: 0 */
            ULONG64 DbgHiberBoot : 1; /* bit position: 1 */
            ULONG64 DbgSoftRestart : 1; /* bit position: 2 */
        };
    };
    union
    {
        ULONG64 InternalBootFlags;
        struct
        {
            ULONG64 DbgUtcBootTime : 1; /* bit position: 0 */
            ULONG64 DbgRtcBootTime : 1; /* bit position: 1 */
            ULONG64 DbgNoLegacyServices : 1; /* bit position: 2 */
        };
    };
    PVOID WfsFPData;
    ULONG WfsFPDataSize;
#if (NTLDR_VERSION == NTDDI_WIN8)
    LOADER_PARAMETER_KD_EXTENSION KdExtension;
#endif
#endif

#if (NTLDR_VERSION >= NTDDI_WINBLUE)
    LOADER_BUGCHECK_PARAMETERS BugcheckParameters;
    PVOID  ApiSetSchema;
    ULONG ApiSetSchemaSize;
    LIST_ENTRY ApiSetSchemaExtensions;
    UNICODE_STRING AcpiBiosVersion;
    UNICODE_STRING SmbiosVersion;
    UNICODE_STRING EfiVersion;
    struct _DEBUG_DEVICE_DESCRIPTOR* KdDebugDevice;
#if (NTLDR_VERSION >= NTDDI_WIN10)
    OFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V2 OfflineCrashdumpConfigurationTable;
#else
    OFFLINE_CRASHDUMP_CONFIGURATION_TABLE_V1 OfflineCrashdumpConfigurationTable;
#endif
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10)
    UNICODE_STRING ManufacturingProfile;
    PVOID BbtBuffer;
    ULONG64 XsaveAllowedFeatures;
    ULONG XsaveFlags;
    PVOID BootOptions;
#if (NTLDR_VERSION >= NTDDI_WIN10_RS1)
    ULONG IumEnablement;
    ULONG IumPolicy;
    INT32 IumStatus;
#endif
    ULONG BootId;
    struct _LOADER_PARAMETER_CI_EXTENSION* CodeIntegrityData;
    ULONG CodeIntegrityDataSize;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10_TH2)
    LOADER_HIVE_RECOVERY_INFO SystemHiveRecoveryInfo;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10_RS1)
    ULONG SoftRestartCount;
    INT64 SoftRestartTime;
    PVOID HypercallCodeVa;
    PVOID HalVirtualAddress;
    ULONG64 HalNumberOfBytes;
#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    struct _LEAP_SECOND_DATA *LeapSecondData;
#endif
    ULONG MajorRelease;
    ULONG Reserved1;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10_RS2)
    CHAR NtBuildLab[224];
    CHAR NtBuildLabEx[224];
    LOADER_RESET_REASON ResetReason;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10_RS4)
    ULONG MaxPciBusNumber;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10_RS5)
    ULONG FeatureSettings;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10_19H1)
    ULONG HotPatchReserveSize;
    ULONG RetpolineReserveSize;
    struct
    {
        PVOID CodeBase;
        ULONGLONG CodeSize;
    } MiniExecutive;
    VSM_PERFORMANCE_DATA VsmPerformanceData;
#endif

#if (NTLDR_VERSION >= NTDDI_WIN10_VB)
    NUMA_MEMORY_RANGE *NumaMemoryRanges;
    ULONG NumaMemoryRangeCount;
    ULONG IommuFaultPolicy;
#endif
} LOADER_PARAMETER_EXTENSION, *PLOADER_PARAMETER_EXTENSION;

//
// Architecture specific Loader Parameter Blocks
//
typedef struct _IA64_LOADER_BLOCK
{
    ULONG PlaceHolder;
} IA64_LOADER_BLOCK, *PIA64_LOADER_BLOCK;

typedef struct _ALPHA_LOADER_BLOCK
{
    ULONG PlaceHolder;
} ALPHA_LOADER_BLOCK, *PALPHA_LOADER_BLOCK;

typedef struct _I386_LOADER_BLOCK
{
    PVOID CommonDataArea;
    ULONG MachineType;
    ULONG VirtualBias;
} I386_LOADER_BLOCK, *PI386_LOADER_BLOCK;

typedef struct _PPC_LOADER_BLOCK
{
    PVOID BootInfo;
    ULONG MachineType;
} PPC_LOADER_BLOCK, *PPPC_LOADER_BLOCK;

typedef struct _ARM_LOADER_BLOCK
{
#ifdef _ARM_
    ULONG InterruptStack;
    ULONG FirstLevelDcacheSize;
    ULONG FirstLevelDcacheFillSize;
    ULONG FirstLevelIcacheSize;
    ULONG FirstLevelIcacheFillSize;
    ULONG GpBase;
    ULONG PanicStack;
    ULONG PcrPage;
    ULONG PdrPage;
    ULONG SecondLevelDcacheSize;
    ULONG SecondLevelDcacheFillSize;
    ULONG SecondLevelIcacheSize;
    ULONG SecondLevelIcacheFillSize;
    ULONG PcrPage2;
#else
    ULONG PlaceHolder;
#endif
} ARM_LOADER_BLOCK, *PARM_LOADER_BLOCK;

//
// Firmware information block (NT6+)
//

typedef struct _VIRTUAL_EFI_RUNTIME_SERVICES
{
    ULONG_PTR GetTime;
    ULONG_PTR SetTime;
    ULONG_PTR GetWakeupTime;
    ULONG_PTR SetWakeupTime;
    ULONG_PTR SetVirtualAddressMap;
    ULONG_PTR ConvertPointer;
    ULONG_PTR GetVariable;
    ULONG_PTR GetNextVariableName;
    ULONG_PTR SetVariable;
    ULONG_PTR GetNextHighMonotonicCount;
    ULONG_PTR ResetSystem;
    ULONG_PTR UpdateCapsule;
    ULONG_PTR QueryCapsuleCapabilities;
    ULONG_PTR QueryVariableInfo;
} VIRTUAL_EFI_RUNTIME_SERVICES, *PVIRTUAL_EFI_RUNTIME_SERVICES;

typedef struct _EFI_FIRMWARE_INFORMATION
{
    ULONG FirmwareVersion;
    PVIRTUAL_EFI_RUNTIME_SERVICES VirtualEfiRuntimeServices;
    NTSTATUS SetVirtualAddressMapStatus;
    ULONG MissedMappingsCount;
#if (NTLDR_VERSION >= NTDDI_WIN8)
    LIST_ENTRY FirmwareResourceList;
#endif // (NTLDR_VERSION >= NTDDI_WIN8)
#if (NTLDR_VERSION >= NTDDI_WINBLUE)
    PVOID EfiMemoryMap;
    ULONG EfiMemoryMapSize;
    ULONG EfiMemoryMapDescriptorSize;
#endif // (NTLDR_VERSION >= NTDDI_WINBLUE)
} EFI_FIRMWARE_INFORMATION, *PEFI_FIRMWARE_INFORMATION;

typedef struct _PCAT_FIRMWARE_INFORMATION
{
    ULONG PlaceHolder;
} PCAT_FIRMWARE_INFORMATION, *PPCAT_FIRMWARE_INFORMATION;

typedef struct _FIRMWARE_INFORMATION_LOADER_BLOCK
{
    ULONG FirmwareTypeEfi:1;
    ULONG Reserved:31;
    union
    {
        EFI_FIRMWARE_INFORMATION EfiInformation;
        PCAT_FIRMWARE_INFORMATION PcatInformation;
    } u;
} FIRMWARE_INFORMATION_LOADER_BLOCK, *PFIRMWARE_INFORMATION_LOADER_BLOCK;

//
// Loader Parameter Block
//
// See http://www.geoffchappell.com/studies/windows/km/ntoskrnl/structs/loader_parameter_block.htm
// for more details.
//
typedef struct _LOADER_PARAMETER_BLOCK
{
#if (NTLDR_VERSION >= NTDDI_WIN7)
    ULONG OsMajorVersion;
    ULONG OsMinorVersion;
    ULONG Size;
#if (NTLDR_VERSION >= NTDDI_WIN10_TH2)
    ULONG OsLoaderSecurityVersion;
#else
    ULONG Reserved;
#endif (NTLDR_VERSION >= NTDDI_WIN10_TH2)
#endif // (NTLDR_VERSION >= NTDDI_WIN7)
    LIST_ENTRY LoadOrderListHead;
    LIST_ENTRY MemoryDescriptorListHead;
    LIST_ENTRY BootDriverListHead;
#if (NTLDR_VERSION >= NTDDI_WIN8)
    LIST_ENTRY EarlyLaunchListHead;
    LIST_ENTRY CoreDriverListHead;
#endif // (NTLDR_VERSION >= NTDDI_WIN8)
#if (NTLDR_VERSION >= NTDDI_WIN10)
    LIST_ENTRY CoreExtensionsDriverListHead;
    LIST_ENTRY TpmCoreDriverListHead;
#endif // (NTLDR_VERSION >= NTDDI_WIN10)
    ULONG_PTR KernelStack;
    ULONG_PTR Prcb;
    ULONG_PTR Process;
    ULONG_PTR Thread;
#if (NTLDR_VERSION >= NTDDI_WIN8)
    ULONG KernelStackSize;
#endif // (NTLDR_VERSION >= NTDDI_WIN8)
    ULONG RegistryLength;
    PVOID RegistryBase;
    PCONFIGURATION_COMPONENT_DATA ConfigurationRoot;
    PSTR ArcBootDeviceName;
    PSTR ArcHalDeviceName;
    PSTR NtBootPathName;
    PSTR NtHalPathName;
    PSTR LoadOptions;
    PNLS_DATA_BLOCK NlsData;
    PARC_DISK_INFORMATION ArcDiskInformation;
#if (NTLDR_VERSION < NTDDI_WIN8)
    PVOID OemFontFile;
#endif // (NTLDR_VERSION < NTDDI_WIN8)
#if (NTLDR_VERSION < NTDDI_WIN7)
    union
    {
        struct _SETUP_LOADER_BLOCK* SetupLdrBlock; // old name?
        struct _SETUP_LOADER_BLOCK* SetupLoaderBlock;
    };
#endif // (NTLDR_VERSION < NTDDI_WIN7)
    PLOADER_PARAMETER_EXTENSION Extension;
    union
    {
        I386_LOADER_BLOCK I386;
        ALPHA_LOADER_BLOCK Alpha;
        IA64_LOADER_BLOCK Ia64; // Windows 2003: IA64
        PPC_LOADER_BLOCK PowerPC; // Not in Vista
        ARM_LOADER_BLOCK Arm; // Not in Vista
    } u;
#if (NTLDR_VERSION >= NTDDI_VISTA)
    FIRMWARE_INFORMATION_LOADER_BLOCK FirmwareInformation;
#endif // (NTLDR_VERSION < NTDDI_VISTA)
#if (NTLDR_VERSION >= NTDDI_WIN10_RS4)
    PSTR OsBootstatPathName;
    PSTR ArcOSDataDeviceName;
    PSTR ArcWindowsSysPartName;
#endif // (NTLDR_VERSION == NTDDI_WIN10_RS4)
} LOADER_PARAMETER_BLOCK, *PLOADER_PARAMETER_BLOCK;

typedef int CONFIGTYPE;
typedef struct tagFILEINFORMATION
{
    LARGE_INTEGER StartingAddress;
    LARGE_INTEGER EndingAddress;
    LARGE_INTEGER CurrentAddress;
    CONFIGTYPE Type;
    ULONG FileNameLength;
    UCHAR Attributes;
    CHAR Filename[32];
} FILEINFORMATION;

typedef
ARC_STATUS
(*ARC_CLOSE)(
    ULONG FileId
);

typedef
ARC_STATUS
(*ARC_GET_FILE_INFORMATION)(
    ULONG FileId,
    FILEINFORMATION* Information
);

typedef
ARC_STATUS
(*ARC_OPEN)(
    CHAR* Path,
    OPENMODE OpenMode,
    ULONG* FileId
);

typedef
ARC_STATUS
(*ARC_READ)(
    ULONG FileId,
    VOID* Buffer,
    ULONG N, ULONG* Count
);

typedef
ARC_STATUS
(*ARC_SEEK)(
    ULONG FileId,
    LARGE_INTEGER* Position,
    SEEKMODE SeekMode
);

#endif
