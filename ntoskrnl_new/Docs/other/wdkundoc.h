/*
    This is the file wdkundoc.h, release 3.
    The purpose of this include file is to provide information that is
    undocumented in the Microsoft Windows Driver Kit (WDK).
    Copyright (C) 1999-2015 Bo Brantén.
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    The GNU General Public License is also available from:
    http://www.gnu.org/copyleft/gpl.html

    Windows and Windows NT are either registered trademarks or trademarks of
    Microsoft Corporation in the United States and/or other countries.

    DISCLAIMER: I do not encourage anyone to use this include file to build
    drivers used in production. Some of the information in this file may not
    be available in other publications intended for similar use. Some of the
    information in this file may have different names than in other
    publications even though they describe the same thing.

    NOTE: This file should be used with the Microsoft Windows Driver Kit (WDK)
    while the free version of the file ntifs.h should be used with the
    Microsoft® Windows® Driver Development Kit (DDK).

    Please send comments, corrections and contributions to bosse@acc.umu.se.

    The most recent version of this file is available from:
    http://www.acc.umu.se/~bosse/wdkundoc.h

    The most recent free version of the file ntifs.h is available from:
    http://www.acc.umu.se/~bosse/ntifs.h

    Include ntddk.h or ntifs.h before this file:
    #include <ntddk.h>
    #include "wdkundoc.h"
    or
    #include <ntifs.h>
    #include "wdkundoc.h"

    Revision history:

    3. 2015-06-11
        Added:
          Externals:
            KiEnableTimerWatchdog
            KdComPortInUse
            NlsLeadByteInfo
            NlsOemLeadByteInfo
            NlsMbCodePageTag
            NlsMbOemCodePageTag
            NlsAnsiCodePage
            NlsOemCodePage
            KeDcacheFlushCount
            KeIcacheFlushCount
            CcFastReadNotPossible
            CcFastReadWait
            POGOBuffer
            psMUITest
            PsUILanguageComitted

    2. 2015-06-05
        Corrected:
          FsRtlNotifyReportChange
          HalDisplayString
          InbvDisplayString
          InbvInstallDisplayStringFilter
          InbvNotifyDisplayOwnershipLost
          InbvSetTextColor
          KeInitializeApc
          MmMapViewOfSection
          ObCreateObject
          RtlImageNtHeader
          RtlSetSaclSecurityDescriptor
          SeCreateAccessState
          ZwAccessCheckAndAuditAlarm
          ZwAdjustPrivilegesToken
          ZwConnectPort
          ZwOpenThread
          ZwResetEvent
        Added:
          Data types:
            AUX_ACCESS_DATA
            KAPC_ENVIRONMENT
            X86BIOS_REGISTERS
          Function prototypes:
            ExSystemExceptionFilter
            HalAdjustResourceList
            HalAllProcessorsStarted
            HalConvertDeviceIdtToIrql
            HalDisableInterrupt
            HalEnableInterrupt
            HalQueryMaximumProcessorCount
            HalRegisterErrataCallbacks
            KdPollBreakIn
            KeEnterKernelDebugger
            KeGetPreviousMode
            KeGetXSaveFeatureFlags
            KePollFreezeExecution
            KiCoprocessorError
            KiDispatchInterrupt
            NtThawTransactions
            PoUserShutdownInitiated
            PsEnterPriorityRegion
            PsGetCurrentProcessWin32Process
            PsGetCurrentThreadProcess
            PsGetCurrentThreadProcessId
            PsGetCurrentThreadTeb
            PsGetCurrentThreadWin32Thread
            PsLeavePriorityRegion
            TmThawTransactions
            TmInitSystemPhase2
            TmInitSystem
            x86BiosAllocateBuffer
            x86BiosCall
            x86BiosFreeBuffer
            x86BiosReadMemory
            x86BiosWriteMemory

    1. 2015-03-26
       Initial release based on the free version of the file ntifs.h.
*/

#ifndef _GNU_NTIFS_
#ifndef _GNU_WDK_UNDOC_
#define _GNU_WDK_UNDOC_

#ifdef __cplusplus
extern "C" {
#endif

// Available in Windows NT 3.5 and later versions.
typedef struct _HAL_PRIVATE_DISPATCH *PHAL_PRIVATE_DISPATCH;
extern PHAL_PRIVATE_DISPATCH HalPrivateDispatchTable;

// Available in Windows NT 3.5 and later versions.
typedef struct _LOADER_PARAMETER_BLOCK *PLOADER_PARAMETER_BLOCK;
extern PLOADER_PARAMETER_BLOCK KeLoaderBlock;

// Available in Windows NT 3.5 and later versions.
typedef struct _SERVICE_DESCRIPTOR_TABLE *PSERVICE_DESCRIPTOR_TABLE;
extern PSERVICE_DESCRIPTOR_TABLE KeServiceDescriptorTable;

// Available in Windows NT 3.5 and later versions.
extern PSHORT NtBuildNumber;
extern PULONG KeI386MachineType;

// Available in Windows NT 4.0 and later versions.
extern ULONG KiBugCheckData[5];

// Available in Windows 2000 and later versions.
extern PULONG InitSafeBootMode;

// Available from Windows 2000 untill Windows Server 2003.
extern PULONG KiEnableTimerWatchdog;

// Available in Windows NT 3.5 and later versions.
//
// Set by the kernel debugger on the target system to the address of the
// serial port used to communicate with the host.
//
extern PUCHAR *KdComPortInUse;

// Available in Windows 2000 and later versions.
extern PULONG KdEnteredDebugger;

// Available in Windows NT 3.5 and later versions.
extern PUSHORT *NlsLeadByteInfo;
extern PUSHORT *NlsOemLeadByteInfo;
extern PBOOLEAN NlsMbCodePageTag;
extern PBOOLEAN NlsMbOemCodePageTag;

// Available in Windows NT 4.0 and later versions.
extern PUSHORT NlsAnsiCodePage;

// Available in Windows 2000 and later versions.
extern PUSHORT NlsOemCodePage;

// Available in Windows NT 3.5 and later versions.
extern PACL SePublicDefaultDacl;
extern PACL SeSystemDefaultDacl;

// Available from Windows NT 3.5 untill Windows XP.
extern ULONG KeDcacheFlushCount;
extern ULONG KeIcacheFlushCount;

// Available from Windows NT 4.0 untill Windows Server 2003.
extern ULONG CcFastReadNotPossible;
extern ULONG CcFastReadWait;

// The ExEventObjectType, ExSemaphoreObjectType and IoFileObjectType is
// documented in the DDK and the WDK.
//
// The CmKeyObjectType, SeTokenObjectType, PsProcessType, PsThreadType,
// TmEnlistmentObjectType, TmResourceManagerObjectType,
// TmTransactionManagerObjectType and TmTransactionObjectType
// is documented in the WDK.
//
// Available in Windows NT 3.5 and later versions.
extern POBJECT_TYPE *IoAdapterObjectType;
extern POBJECT_TYPE *IoDeviceObjectType;
extern POBJECT_TYPE *IoDriverObjectType;
extern POBJECT_TYPE *MmSectionObjectType;
// Available in Windows NT 4.0 and later versions.
extern POBJECT_TYPE *ExDesktopObjectType;
extern POBJECT_TYPE *ExWindowStationObjectType;
extern POBJECT_TYPE *IoDeviceHandlerObjectType;
// Available in Windows 2000 and later versions.
extern POBJECT_TYPE *LpcPortObjectType;
extern POBJECT_TYPE *PsJobType;

// Available in Windows NT 4.0 and later versions.
extern PULONG IoDeviceHandlerObjectSize;

// Available in Windows Vista and later versions.
extern PVOID POGOBuffer;
extern PVOID psMUITest;
extern PVOID PsUILanguageComitted;

#define FILE_ACTION_ADDED                   0x00000001
#define FILE_ACTION_REMOVED                 0x00000002
#define FILE_ACTION_MODIFIED                0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005
#define FILE_ACTION_ADDED_STREAM            0x00000006
#define FILE_ACTION_REMOVED_STREAM          0x00000007
#define FILE_ACTION_MODIFIED_STREAM         0x00000008
#define FILE_ACTION_REMOVED_BY_DELETE       0x00000009
#define FILE_ACTION_ID_NOT_TUNNELLED        0x0000000A
#define FILE_ACTION_TUNNELLED_ID_COLLISION  0x0000000B

#define FILE_EA_TYPE_BINARY             0xfffe
#define FILE_EA_TYPE_ASCII              0xfffd
#define FILE_EA_TYPE_BITMAP             0xfffb
#define FILE_EA_TYPE_METAFILE           0xfffa
#define FILE_EA_TYPE_ICON               0xfff9
#define FILE_EA_TYPE_EA                 0xffee
#define FILE_EA_TYPE_MVMT               0xffdf
#define FILE_EA_TYPE_MVST               0xffde
#define FILE_EA_TYPE_ASN1               0xffdd
#define FILE_EA_TYPE_FAMILY_IDS         0xff01

#define FILE_NEED_EA                    0x00000080

#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_NAME         0x00000003
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040
#define FILE_NOTIFY_CHANGE_EA           0x00000080
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
#define FILE_NOTIFY_CHANGE_STREAM_NAME  0x00000200
#define FILE_NOTIFY_CHANGE_STREAM_SIZE  0x00000400
#define FILE_NOTIFY_CHANGE_STREAM_WRITE 0x00000800
#define FILE_NOTIFY_VALID_MASK          0x00000fff

#define FILE_OPLOCK_BROKEN_TO_LEVEL_2   0x00000007
#define FILE_OPLOCK_BROKEN_TO_NONE      0x00000008

#define FILE_OPBATCH_BREAK_UNDERWAY     0x00000009

#define FILE_CASE_SENSITIVE_SEARCH      0x00000001
#define FILE_CASE_PRESERVED_NAMES       0x00000002
#define FILE_UNICODE_ON_DISK            0x00000004
#define FILE_PERSISTENT_ACLS            0x00000008
#define FILE_FILE_COMPRESSION           0x00000010
#define FILE_VOLUME_QUOTAS              0x00000020
#define FILE_SUPPORTS_SPARSE_FILES      0x00000040
#define FILE_SUPPORTS_REPARSE_POINTS    0x00000080
#define FILE_SUPPORTS_REMOTE_STORAGE    0x00000100
#define FS_LFN_APIS                     0x00004000
#define FILE_VOLUME_IS_COMPRESSED       0x00008000
#define FILE_SUPPORTS_OBJECT_IDS        0x00010000
#define FILE_SUPPORTS_ENCRYPTION        0x00020000
#define FILE_NAMED_STREAMS              0x00040000
#define FILE_READ_ONLY_VOLUME           0x00080000

#define FILE_PIPE_BYTE_STREAM_TYPE      0x00000000
#define FILE_PIPE_MESSAGE_TYPE          0x00000001

#define FILE_PIPE_BYTE_STREAM_MODE      0x00000000
#define FILE_PIPE_MESSAGE_MODE          0x00000001

#define FILE_PIPE_QUEUE_OPERATION       0x00000000
#define FILE_PIPE_COMPLETE_OPERATION    0x00000001

#define FILE_PIPE_INBOUND               0x00000000
#define FILE_PIPE_OUTBOUND              0x00000001
#define FILE_PIPE_FULL_DUPLEX           0x00000002

#define FILE_PIPE_DISCONNECTED_STATE    0x00000001
#define FILE_PIPE_LISTENING_STATE       0x00000002
#define FILE_PIPE_CONNECTED_STATE       0x00000003
#define FILE_PIPE_CLOSING_STATE         0x00000004

#define FILE_PIPE_CLIENT_END            0x00000000
#define FILE_PIPE_SERVER_END            0x00000001

#define FILE_PIPE_READ_DATA             0x00000000
#define FILE_PIPE_WRITE_SPACE           0x00000001

#define FILE_STORAGE_TYPE_SPECIFIED             0x00000041  // FILE_DIRECTORY_FILE | FILE_NON_DIRECTORY_FILE
#define FILE_STORAGE_TYPE_DEFAULT               (StorageTypeDefault << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_DIRECTORY             (StorageTypeDirectory << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_FILE                  (StorageTypeFile << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_DOCFILE               (StorageTypeDocfile << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_JUNCTION_POINT        (StorageTypeJunctionPoint << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_CATALOG               (StorageTypeCatalog << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_STRUCTURED_STORAGE    (StorageTypeStructuredStorage << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_EMBEDDING             (StorageTypeEmbedding << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_STREAM                (StorageTypeStream << FILE_STORAGE_TYPE_SHIFT)
#define FILE_MINIMUM_STORAGE_TYPE               FILE_STORAGE_TYPE_DEFAULT
#define FILE_MAXIMUM_STORAGE_TYPE               FILE_STORAGE_TYPE_STREAM
#define FILE_STORAGE_TYPE_MASK                  0x000f0000
#define FILE_STORAGE_TYPE_SHIFT                 16

#define FILE_VC_QUOTA_NONE              0x00000000
#define FILE_VC_QUOTA_TRACK             0x00000001
#define FILE_VC_QUOTA_ENFORCE           0x00000002
#define FILE_VC_QUOTA_MASK              0x00000003

#define FILE_VC_QUOTAS_LOG_VIOLATIONS   0x00000004
#define FILE_VC_CONTENT_INDEX_DISABLED  0x00000008

#define FILE_VC_LOG_QUOTA_THRESHOLD     0x00000010
#define FILE_VC_LOG_QUOTA_LIMIT         0x00000020
#define FILE_VC_LOG_VOLUME_THRESHOLD    0x00000040
#define FILE_VC_LOG_VOLUME_LIMIT        0x00000080

#define FILE_VC_QUOTAS_INCOMPLETE       0x00000100
#define FILE_VC_QUOTAS_REBUILDING       0x00000200

#define FILE_VC_VALID_MASK              0x000003ff

#define FSRTL_FCB_HEADER_V0             (0x00)
#define FSRTL_FCB_HEADER_V1             (0x01)

#define FSRTL_FLAG_FILE_MODIFIED        (0x01)
#define FSRTL_FLAG_FILE_LENGTH_CHANGED  (0x02)
#define FSRTL_FLAG_LIMIT_MODIFIED_PAGES (0x04)
#define FSRTL_FLAG_ACQUIRE_MAIN_RSRC_EX (0x08)
#define FSRTL_FLAG_ACQUIRE_MAIN_RSRC_SH (0x10)
#define FSRTL_FLAG_USER_MAPPED_FILE     (0x20)
#define FSRTL_FLAG_ADVANCED_HEADER      (0x40)
#define FSRTL_FLAG_EOF_ADVANCE_ACTIVE   (0x80)

#define FSRTL_FLAG2_DO_MODIFIED_WRITE           (0x01)
#define FSRTL_FLAG2_SUPPORTS_FILTER_CONTEXTS    (0x02)
#define FSRTL_FLAG2_PURGE_WHEN_MAPPED           (0x04)
#define FSRTL_FLAG2_IS_PAGING_FILE              (0x08)

#define FSRTL_VOLUME_DISMOUNT           1
#define FSRTL_VOLUME_DISMOUNT_FAILED    2
#define FSRTL_VOLUME_LOCK               3
#define FSRTL_VOLUME_LOCK_FAILED        4
#define FSRTL_VOLUME_UNLOCK             5
#define FSRTL_VOLUME_MOUNT              6

#define FSRTL_WILD_CHARACTER            0x08

#ifdef _X86_
#define HARDWARE_PTE    HARDWARE_PTE_X86
#define PHARDWARE_PTE   PHARDWARE_PTE_X86
#else
#define HARDWARE_PTE    ULONG
#define PHARDWARE_PTE   PULONG
#endif

#define IO_CHECK_CREATE_PARAMETERS      0x0200
#define IO_ATTACH_DEVICE                0x0400

#define IO_ATTACH_DEVICE_API            0x80000000

#define IO_COMPLETION_QUERY_STATE       0x0001
#define IO_COMPLETION_MODIFY_STATE      0x0002
#define IO_COMPLETION_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

#define IO_FILE_OBJECT_NON_PAGED_POOL_CHARGE    64
#define IO_FILE_OBJECT_PAGED_POOL_CHARGE        1024

#define IO_REPARSE_TAG_RESERVED_ZERO    (0)
#define IO_REPARSE_TAG_RESERVED_ONE     (1)

#define IO_TYPE_APC                     18
#define IO_TYPE_DPC                     19
#define IO_TYPE_DEVICE_QUEUE            20
#define IO_TYPE_EVENT_PAIR              21
#define IO_TYPE_INTERRUPT               22
#define IO_TYPE_PROFILE                 23

#define IRP_BEING_VERIFIED              0x10

#define MAILSLOT_CLASS_FIRSTCLASS       1
#define MAILSLOT_CLASS_SECONDCLASS      2

#define MAILSLOT_SIZE_AUTO              0

#define MAP_PROCESS                     1L
#define MAP_SYSTEM                      2L

#define MEM_DOS_LIM                     0x40000000
#define MEM_IMAGE                       SEC_IMAGE

#define OB_FLAG_CREATE_INFO     0x01 /* Object header has OBJECT_CREATE_INFO */
#define OB_FLAG_KERNEL_MODE     0x02 /* Created by kernel */
#define OB_FLAG_CREATOR_INFO    0x04 /* Object header has OBJECT_CREATOR_INFO */
#define OB_FLAG_EXCLUSIVE       0x08 /* OBJ_EXCLUSIVE */
#define OB_FLAG_PERMAMENT       0x10 /* OBJ_PERMAMENT */
#define OB_FLAG_SECURITY        0x20 /* Object header has SecurityDescriptor != NULL */
#define OB_FLAG_SINGLE_PROCESS  0x40 /* absent HandleDBList */

#define OB_SECURITY_CHARGE      0x00000800

#define OB_TYPE_TYPE                    1
#define OB_TYPE_DIRECTORY               2
#define OB_TYPE_SYMBOLIC_LINK           3
#define OB_TYPE_TOKEN                   4
#define OB_TYPE_PROCESS                 5
#define OB_TYPE_THREAD                  6
#define OB_TYPE_EVENT                   7
#define OB_TYPE_EVENT_PAIR              8
#define OB_TYPE_MUTANT                  9
#define OB_TYPE_SEMAPHORE               10
#define OB_TYPE_TIMER                   11
#define OB_TYPE_PROFILE                 12
#define OB_TYPE_WINDOW_STATION          13
#define OB_TYPE_DESKTOP                 14
#define OB_TYPE_SECTION                 15
#define OB_TYPE_KEY                     16
#define OB_TYPE_PORT                    17
#define OB_TYPE_ADAPTER                 18
#define OB_TYPE_CONTROLLER              19
#define OB_TYPE_DEVICE                  20
#define OB_TYPE_DRIVER                  21
#define OB_TYPE_IO_COMPLETION           22
#define OB_TYPE_FILE                    23

#define PIN_WAIT                        (1)
#define PIN_EXCLUSIVE                   (2)
#define PIN_NO_READ                     (4)
#define PIN_IF_BCB                      (8)

#define MAP_WAIT                        (1)
#define MAP_NO_READ                     (16)

#define PORT_CONNECT                    0x0001
#define PORT_ALL_ACCESS                 (STANDARD_RIGHTS_ALL |\
                                         PORT_CONNECT)

#define SEC_BASED                       0x00200000
#define SEC_NO_CHANGE                   0x00400000
#define SEC_FILE                        0x00800000
#define SEC_IMAGE                       0x01000000
#define SEC_NOCACHE                     0x10000000

#define SECURITY_WORLD_SID_AUTHORITY    {0,0,0,0,0,1}
#define SECURITY_WORLD_RID              (0x00000000L)

#define THREAD_STATE_INITIALIZED        0
#define THREAD_STATE_READY              1
#define THREAD_STATE_RUNNING            2
#define THREAD_STATE_STANDBY            3
#define THREAD_STATE_TERMINATED         4
#define THREAD_STATE_WAIT               5
#define THREAD_STATE_TRANSITION         6
#define THREAD_STATE_UNKNOWN            7

#define TOKEN_ASSIGN_PRIMARY            (0x0001)
#define TOKEN_DUPLICATE                 (0x0002)
#define TOKEN_IMPERSONATE               (0x0004)
#define TOKEN_QUERY                     (0x0008)
#define TOKEN_QUERY_SOURCE              (0x0010)
#define TOKEN_ADJUST_PRIVILEGES         (0x0020)
#define TOKEN_ADJUST_GROUPS             (0x0040)
#define TOKEN_ADJUST_DEFAULT            (0x0080)

#define TOKEN_READ       (STANDARD_RIGHTS_READ     |\
                          TOKEN_QUERY)

#define TOKEN_WRITE      (STANDARD_RIGHTS_WRITE    |\
                          TOKEN_ADJUST_PRIVILEGES  |\
                          TOKEN_ADJUST_GROUPS      |\
                          TOKEN_ADJUST_DEFAULT)

#define TOKEN_EXECUTE    (STANDARD_RIGHTS_EXECUTE)

#define TOKEN_SOURCE_LENGTH 8

#define TOKEN_HAS_ADMIN_GROUP           0x08

#define FSCTL_NETWORK_SET_CONFIGURATION_INFO    CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 102, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define FSCTL_NETWORK_GET_CONFIGURATION_INFO    CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 103, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define FSCTL_NETWORK_GET_CONNECTION_INFO       CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 104, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_NETWORK_ENUMERATE_CONNECTIONS     CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 105, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_NETWORK_DELETE_CONNECTION         CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 107, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_NETWORK_GET_STATISTICS            CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 116, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_NETWORK_SET_DOMAIN_NAME           CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 120, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_NETWORK_REMOTE_BOOT_INIT_SCRT     CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 250, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef PVOID PEJOB;
typedef PVOID PNOTIFY_SYNC;
typedef PVOID OPLOCK, *POPLOCK;
typedef PVOID PWOW64_PROCESS;

typedef ULONG LBN;
typedef LBN *PLBN;

typedef ULONG VBN;
typedef VBN *PVBN;

typedef struct _CACHE_MANAGER_CALLBACKS         *PCACHE_MANAGER_CALLBACKS;
typedef struct _CACHE_UNINITIALIZE_EVENT        *PCACHE_UNINITIALIZE_EVENT;
typedef struct _EPROCESS_QUOTA_BLOCK            *PEPROCESS_QUOTA_BLOCK;
typedef struct _FILE_GET_QUOTA_INFORMATION      *PFILE_GET_QUOTA_INFORMATION;
typedef struct _HANDLE_TABLE                    *PHANDLE_TABLE;
typedef struct _IMAGE_NT_HEADERS                *PIMAGE_NT_HEADERS;
typedef struct _KEVENT_PAIR                     *PKEVENT_PAIR;
typedef struct _KPROCESS                        *PKPROCESS;
typedef struct _KQUEUE                          *PKQUEUE;
typedef struct _KTRAP_FRAME                     *PKTRAP_FRAME;
typedef struct _LPC_MESSAGE                     *PLPC_MESSAGE;
typedef struct _MAILSLOT_CREATE_PARAMETERS      *PMAILSLOT_CREATE_PARAMETERS;
typedef struct _MMWSL                           *PMMWSL;
typedef struct _NAMED_PIPE_CREATE_PARAMETERS    *PNAMED_PIPE_CREATE_PARAMETERS;
typedef struct _OBJECT_DIRECTORY                *POBJECT_DIRECTORY;
typedef struct _PAGEFAULT_HISTORY               *PPAGEFAULT_HISTORY;
typedef struct _PEB                             *PPEB;
typedef struct _PS_IMPERSONATION_INFORMATION    *PPS_IMPERSONATION_INFORMATION;
typedef struct _SECTION_OBJECT                  *PSECTION_OBJECT;
typedef struct _SERVICE_DESCRIPTOR_TABLE        *PSERVICE_DESCRIPTOR_TABLE;
typedef struct _SHARED_CACHE_MAP                *PSHARED_CACHE_MAP;
typedef struct _SID_AND_ATTRIBUTES              *PSID_AND_ATTRIBUTES;
typedef struct _TERMINATION_PORT                *PTERMINATION_PORT;
typedef struct _TOKEN_PRIVILEGES                *PTOKEN_PRIVILEGES;
typedef struct _VACB                            *PVACB;
typedef struct _VAD_HEADER                      *PVAD_HEADER;

#if (NTDDI_VERSION < NTDDI_WIN2K)
typedef ULONG SIZE_T, *PSIZE_T;
#endif // (NTDDI_VERSION < NTDDI_WIN2K)

typedef enum _FILE_STORAGE_TYPE {
    StorageTypeDefault = 1,
    StorageTypeDirectory,
    StorageTypeFile,
    StorageTypeJunctionPoint,
    StorageTypeCatalog,
    StorageTypeStructuredStorage,
    StorageTypeEmbedding,
    StorageTypeStream
} FILE_STORAGE_TYPE;

typedef enum _IO_COMPLETION_INFORMATION_CLASS {
    IoCompletionBasicInformation
} IO_COMPLETION_INFORMATION_CLASS;

typedef enum _KAPC_ENVIRONMENT {
    OriginalApcEnvironment,
    AttachedApcEnvironment,
    CurrentApcEnvironment
} KAPC_ENVIRONMENT;

typedef enum _LPC_TYPE {
    LPC_NEW_MESSAGE,
    LPC_REQUEST,
    LPC_REPLY,
    LPC_DATAGRAM,
    LPC_LOST_REPLY,
    LPC_PORT_CLOSED,
    LPC_CLIENT_DIED,
    LPC_EXCEPTION,
    LPC_DEBUG_EVENT,
    LPC_ERROR_EVENT,
    LPC_CONNECTION_REQUEST
} LPC_TYPE;

typedef enum _OBJECT_INFO_CLASS {
    ObjectBasicInfo,
    ObjectNameInfo,
    ObjectTypeInfo,
    ObjectAllTypesInfo,
    ObjectProtectionInfo
} OBJECT_INFO_CLASS;

typedef enum _PORT_INFORMATION_CLASS {
    PortNoInformation
} PORT_INFORMATION_CLASS;

typedef enum _SECTION_INFORMATION_CLASS {
    SectionBasicInformation,
    SectionImageInformation
} SECTION_INFORMATION_CLASS;

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation,
    SystemProcessorInformation,
    SystemPerformanceInformation,
    SystemTimeOfDayInformation,
    SystemNotImplemented1,
    SystemProcessesAndThreadsInformation,
    SystemCallCounts,
    SystemConfigurationInformation,
    SystemProcessorTimes,
    SystemGlobalFlag,
    SystemNotImplemented2,
    SystemModuleInformation,
    SystemLockInformation,
    SystemNotImplemented3,
    SystemNotImplemented4,
    SystemNotImplemented5,
    SystemHandleInformation,
    SystemObjectInformation,
    SystemPagefileInformation,
    SystemInstructionEmulationCounts,
    SystemInvalidInfoClass1,
    SystemCacheInformation,
    SystemPoolTagInformation,
    SystemProcessorStatistics,
    SystemDpcInformation,
    SystemNotImplemented6,
    SystemLoadImage,
    SystemUnloadImage,
    SystemTimeAdjustment,
    SystemNotImplemented7,
    SystemNotImplemented8,
    SystemNotImplemented9,
    SystemCrashDumpInformation,
    SystemExceptionInformation,
    SystemCrashDumpStateInformation,
    SystemKernelDebuggerInformation,
    SystemContextSwitchInformation,
    SystemRegistryQuotaInformation,
    SystemLoadAndCallImage,
    SystemPrioritySeparation,
    SystemNotImplemented10,
    SystemNotImplemented11,
    SystemInvalidInfoClass2,
    SystemInvalidInfoClass3,
    SystemTimeZoneInformation,
    SystemLookasideInformation,
    SystemSetTimeSlipEvent,
    SystemCreateSession,
    SystemDeleteSession,
    SystemInvalidInfoClass4,
    SystemRangeStartInformation,
    SystemVerifierInformation,
    SystemAddVerifier,
    SystemSessionProcessesInformation
} SYSTEM_INFORMATION_CLASS;

typedef enum _THREAD_STATE {
    StateInitialized,
    StateReady,
    StateRunning,
    StateStandby,
    StateTerminated,
    StateWait,
    StateTransition,
    StateUnknown
} THREAD_STATE;

#ifndef _NTIFS_

typedef enum _TOKEN_TYPE {
    TokenPrimary = 1,
    TokenImpersonation
} TOKEN_TYPE;

#endif // _NTIFS_

typedef struct _AUX_ACCESS_DATA {
    PPRIVILEGE_SET  PrivilegesUsed;
    GENERIC_MAPPING GenericMapping;
    ACCESS_MASK     AccessesToAudit;
} AUX_ACCESS_DATA, *PAUX_ACCESS_DATA;

typedef struct _HARDWARE_PTE_X86 {
    ULONG Valid             : 1;
    ULONG Write             : 1;
    ULONG Owner             : 1;
    ULONG WriteThrough      : 1;
    ULONG CacheDisable      : 1;
    ULONG Accessed          : 1;
    ULONG Dirty             : 1;
    ULONG LargePage         : 1;
    ULONG Global            : 1;
    ULONG CopyOnWrite       : 1;
    ULONG Prototype         : 1;
    ULONG reserved          : 1;
    ULONG PageFrameNumber   : 20;
} HARDWARE_PTE_X86, *PHARDWARE_PTE_X86;

#ifndef _NTIFS_

typedef struct _KAPC_STATE {
    LIST_ENTRY  ApcListHead[2];
    PKPROCESS   Process;
    BOOLEAN     KernelApcInProgress;
    BOOLEAN     KernelApcPending;
    BOOLEAN     UserApcPending;
} KAPC_STATE, *PKAPC_STATE;

#endif // _NTIFS_

typedef struct _KGDTENTRY {
    USHORT LimitLow;
    USHORT BaseLow;
    union {
        struct {
            UCHAR BaseMid;
            UCHAR Flags1;
            UCHAR Flags2;
            UCHAR BaseHi;
        } Bytes;
        struct {
            ULONG BaseMid       : 8;
            ULONG Type          : 5;
            ULONG Dpl           : 2;
            ULONG Pres          : 1;
            ULONG LimitHi       : 4;
            ULONG Sys           : 1;
            ULONG Reserved_0    : 1;
            ULONG Default_Big   : 1;
            ULONG Granularity   : 1;
            ULONG BaseHi        : 8;
        } Bits;
    } HighWord;
} KGDTENTRY, *PKGDTENTRY;

typedef struct _KIDTENTRY {
    USHORT Offset;
    USHORT Selector;
    USHORT Access;
    USHORT ExtendedOffset;
} KIDTENTRY, *PKIDTENTRY;

#if (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _KPROCESS {
    DISPATCHER_HEADER   Header;
    LIST_ENTRY          ProfileListHead;
    ULONG               DirectoryTableBase[2];
    KGDTENTRY           LdtDescriptor;
    KIDTENTRY           Int21Descriptor;
    USHORT              IopmOffset;
    UCHAR               Iopl;
    UCHAR               Unused;
    ULONG               ActiveProcessors;
    ULONG               KernelTime;
    ULONG               UserTime;
    LIST_ENTRY          ReadyListHead;  
    SINGLE_LIST_ENTRY   SwapListEntry;
    PVOID               VdmTrapcHandler;
    LIST_ENTRY          ThreadListHead;
    KSPIN_LOCK          ProcessLock;
    KAFFINITY           Affinity;
    USHORT              StackCount;
    CHAR                BasePriority;
    CHAR                ThreadQuantum;
    BOOLEAN             AutoAlignment;
    UCHAR               State;
    UCHAR               ThreadSeed;
    BOOLEAN             DisableBoost;
    UCHAR               PowerState;
    BOOLEAN             DisableQuantum;
    UCHAR               IdealNode;
    UCHAR               Spare;
} KPROCESS, *PKPROCESS;

#else

typedef struct _KPROCESS {
    DISPATCHER_HEADER   Header;
    LIST_ENTRY          ProfileListHead;
    ULONG               DirectoryTableBase[2];
    KGDTENTRY           LdtDescriptor;
    KIDTENTRY           Int21Descriptor;
    USHORT              IopmOffset;
    UCHAR               Iopl;
    UCHAR               VdmFlag;
    ULONG               ActiveProcessors;
    ULONG               KernelTime;
    ULONG               UserTime;
    LIST_ENTRY          ReadyListHead;  
    SINGLE_LIST_ENTRY   SwapListEntry;
    PVOID               Reserved1;
    LIST_ENTRY          ThreadListHead;
    KSPIN_LOCK          ProcessLock;
    KAFFINITY           Affinity;
    USHORT              StackCount;
    UCHAR               BasePriority;
    UCHAR               ThreadQuantum;
    BOOLEAN             AutoAlignment;
    UCHAR               State;
    UCHAR               ThreadSeed;
    BOOLEAN             DisableBoost;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    UCHAR               PowerState;
    BOOLEAN             DisableQuantum;
    UCHAR               IdealNode;
    UCHAR               Spare;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
} KPROCESS, *PKPROCESS;

#endif

#if (NTDDI_VERSION >= NTDDI_WS03)

typedef struct _KTHREAD {
    DISPATCHER_HEADER           Header;
    LIST_ENTRY                  MutantListHead; // 0x10
    PVOID                       InitialStack; // 0x18
    PVOID                       StackLimit; // 0x1c
    PVOID                       KernelStack; // 0x20
    ULONG                       ThreadLock; // 0x24
    ULONG                       ContextSwitches; // 0x28
    UCHAR                       State; // 0x2c
    UCHAR                       NpxState; // 0x2d
    UCHAR                       WaitIrql; // 0x2e
    CHAR                        WaitMode; // 0x2f
    struct _TEB                 *Teb; // 0x30
    KAPC_STATE                  ApcState; // 0x34
    KSPIN_LOCK                  ApcQueueLock; // 0x4c
    NTSTATUS                    WaitStatus; // 0x50
    PKWAIT_BLOCK                WaitBlockList; // 0x54
    BOOLEAN                     Alertable; // 0x58
    UCHAR                       WaitNext; // 0x59
    UCHAR                       WaitReason; // 0x5a
    CHAR                        Priority; // 0x5b
    BOOLEAN                     EnableStackSwap; // 0x5c
    BOOLEAN                     SwapBusy; // 0x5d
    UCHAR                       Alerted[2]; // 0x5e
    union {
        LIST_ENTRY              WaitListEntry; // 0x60
        SINGLE_LIST_ENTRY       SwapListEntry; // 0x60
    };
    PKQUEUE                     Queue; // 0x68
    ULONG                       WaitTime; // 0x6c
    union {
        struct {
            USHORT              KernelApcDisable; // 0x70
            USHORT              SpecialApcDisable; // 0x72
        };
        USHORT                  CombinedApcDisable; // 0x70
    };
    KTIMER                      Timer; // 0x78
    KWAIT_BLOCK                 WaitBlock[4]; // 0xa0
    LIST_ENTRY                  QueueListEntry; // 0x100
    UCHAR                       ApcStateIndex; // 0x108
    BOOLEAN                     ApcQueueable; // 0x109
    BOOLEAN                     Preempted; // 0x10a
    BOOLEAN                     ProcessReadyQueue; // 0x10b
    BOOLEAN                     KernelStackResident; // 0x10c
    CHAR                        Saturation; // 0x10d
    UCHAR                       IdealProcessor; // 0x10e
    UCHAR                       NextProcessor; // 0x10f
    CHAR                        BasePriority; // 0x110
    UCHAR                       Spare4; // 0x111
    CHAR                        PriorityDecrement; // 0x112
    CHAR                        Quantum; // 0x113
    BOOLEAN                     SystemAffinityActive; // 0x114
    CHAR                        PreviousMode; // 0x115
    UCHAR                       ResourceIndex; // 0x116
    BOOLEAN                     DisableBoost; // 0x117
    ULONG                       UserAffinity; // 0x118
    PKPROCESS                   Process; // 0x11c
    ULONG                       Affinity; // 0x120
    PSERVICE_DESCRIPTOR_TABLE   ServiceTable; // 0x124
    PKAPC_STATE                 ApcStatePointer[2]; // 0x128
    KAPC_STATE                  SavedApcState; // 0x130
    PVOID                       CallbackStack; // 0x148
    PVOID                       Win32Thread; // 0x14c
    PKTRAP_FRAME                TrapFrame; // 0x150
    ULONG                       KernelTime; // 0x154
    ULONG                       UserTime; // 0x158
    PVOID                       StackBase; // 0x15c
    KAPC                        SuspendApc; // 0x160
    KSEMAPHORE                  SuspendSemaphore; // 0x190
    PVOID                       TlsArray; // 0x1a4
    PVOID                       LegoData; // 0x1a8
    LIST_ENTRY                  ThreadListEntry; // 0x1ac
    BOOLEAN                     LargeStack; // 0x1b4
    UCHAR                       PowerState; // 0x1b5
    UCHAR                       NpxIrql; // 0x1b6
    UCHAR                       Spare5; // 0x1b7
    BOOLEAN                     AutoAlignment; // 0x1b8
    UCHAR                       Iopl; // 0x1b9
    CHAR                        FreezeCount; // 0x1ba
    CHAR                        SuspendCount; // 0x1bb
    UCHAR                       Spare0[1]; // 0x1bc
    UCHAR                       UserIdealProcessor; // 0x1bd
    UCHAR                       DeferredProcessor; // 0x1be
    UCHAR                       AdjustReason; // 0x1bf
    CHAR                        AdjustIncrement; // 0x1c0
    UCHAR                       Spare2[3]; // 0x1c1
} KTHREAD, *PKTHREAD;

#elif (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _KTHREAD {
    DISPATCHER_HEADER           Header;
    LIST_ENTRY                  MutantListHead;
    PVOID                       InitialStack;
    PVOID                       StackLimit;
    struct _TEB                 *Teb;
    PVOID                       TlsArray;
    PVOID                       KernelStack;
    BOOLEAN                     DebugActive;
    UCHAR                       State;
    UCHAR                       Alerted[2];
    UCHAR                       Iopl;
    UCHAR                       NpxState;
    CHAR                        Saturation;
    CHAR                        Priority;
    KAPC_STATE                  ApcState;
    ULONG                       ContextSwitches;
    UCHAR                       IdleSwapBlock;
    UCHAR                       Spare0[3];
    NTSTATUS                    WaitStatus;
    UCHAR                       WaitIrql;
    CHAR                        WaitMode;
    UCHAR                       WaitNext;
    UCHAR                       WaitReason;
    PKWAIT_BLOCK                WaitBlockList;
    union {
        LIST_ENTRY              WaitListEntry;
        SINGLE_LIST_ENTRY       SwapListEntry;
    };
    ULONG                       WaitTime;
    CHAR                        BasePriority;
    UCHAR                       DecrementCount;
    CHAR                        PriorityDecrement;
    CHAR                        Quantum;
    KWAIT_BLOCK                 WaitBlock[4];
    PVOID                       LegoData;
    ULONG                       KernelApcDisable;
    ULONG                       UserAffinity;
    BOOLEAN                     SystemAffinityActive;
    UCHAR                       PowerState;
    UCHAR                       NpxIrql;
    UCHAR                       InitialNode;
    PSERVICE_DESCRIPTOR_TABLE   ServiceTable;
    PKQUEUE                     Queue;
    KSPIN_LOCK                  ApcQueueLock;
    KTIMER                      Timer;
    LIST_ENTRY                  QueueListEntry;
    ULONG                       SoftAffinity;
    ULONG                       Affinity;
    BOOLEAN                     Preempted;
    BOOLEAN                     ProcessReadyQueue;
    BOOLEAN                     KernelStackResident;
    UCHAR                       NextProcessor;
    PVOID                       CallbackStack;
    PVOID                       Win32Thread;
    PKTRAP_FRAME                TrapFrame;
    PKAPC_STATE                 ApcStatePointer[2];
    CHAR                        PreviousMode;
    BOOLEAN                     EnableStackSwap;
    BOOLEAN                     LargeStack;
    UCHAR                       ResourceIndex;
    ULONG                       KernelTime;
    ULONG                       UserTime;
    KAPC_STATE                  SavedApcState;
    BOOLEAN                     Alertable;
    UCHAR                       ApcStateIndex;
    BOOLEAN                     ApcQueueable;
    BOOLEAN                     AutoAlignment;
    PVOID                       StackBase;
    KAPC                        SuspendApc;
    KSEMAPHORE                  SuspendSemaphore;
    LIST_ENTRY                  ThreadListEntry;
    CHAR                        FreezeCount;
    CHAR                        SuspendCount;
    UCHAR                       IdealProcessor;
    BOOLEAN                     DisableBoost;
} KTHREAD, *PKTHREAD;

#else

typedef struct _KTHREAD {
    DISPATCHER_HEADER           Header;
    LIST_ENTRY                  MutantListHead;
    PVOID                       InitialStack;
    PVOID                       StackLimit;
    struct _TEB                 *Teb;
    PVOID                       TlsArray;
    PVOID                       KernelStack;
    BOOLEAN                     DebugActive;
    UCHAR                       State;
    USHORT                      Alerted;
    UCHAR                       Iopl;
    UCHAR                       NpxState;
    UCHAR                       Saturation;
    UCHAR                       Priority;
    KAPC_STATE                  ApcState;
    ULONG                       ContextSwitches;
    NTSTATUS                    WaitStatus;
    UCHAR                       WaitIrql;
    UCHAR                       WaitMode;
    UCHAR                       WaitNext;
    UCHAR                       WaitReason;
    PKWAIT_BLOCK                WaitBlockList;
    LIST_ENTRY                  WaitListEntry;
    ULONG                       WaitTime;
    UCHAR                       BasePriority;
    UCHAR                       DecrementCount;
    UCHAR                       PriorityDecrement;
    UCHAR                       Quantum;
    KWAIT_BLOCK                 WaitBlock[4];
    ULONG                       LegoData;
    ULONG                       KernelApcDisable;
    ULONG                       UserAffinity;
    BOOLEAN                     SystemAffinityActive;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    UCHAR                       PowerState;
    UCHAR                       NpxIrql;
    UCHAR                       Pad[1];
#else // (NTDDI_VERSION < NTDDI_WIN2K)
    UCHAR                       Pad[3];
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
    PSERVICE_DESCRIPTOR_TABLE   ServiceDescriptorTable;
    PKQUEUE                     Queue;
    KSPIN_LOCK                  ApcQueueLock;
    KTIMER                      Timer;
    LIST_ENTRY                  QueueListEntry;
    ULONG                       Affinity;
    BOOLEAN                     Preempted;
    BOOLEAN                     ProcessReadyQueue;
    BOOLEAN                     KernelStackResident;
    UCHAR                       NextProcessor;
    PVOID                       CallbackStack;
    PVOID                       Win32Thread;
    PKTRAP_FRAME                TrapFrame;
    PKAPC_STATE                 ApcStatePointer[2];
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    UCHAR                       PreviousMode;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
    BOOLEAN                     EnableStackSwap;
    BOOLEAN                     LargeStack;
    UCHAR                       ResourceIndex;
#if (NTDDI_VERSION < NTDDI_WIN2K)
    UCHAR                       PreviousMode;
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
    ULONG                       KernelTime;
    ULONG                       UserTime;
    KAPC_STATE                  SavedApcState;
    BOOLEAN                     Alertable;
    UCHAR                       ApcStateIndex;
    BOOLEAN                     ApcQueueable;
    BOOLEAN                     AutoAlignment;
    PVOID                       StackBase;
    KAPC                        SuspendApc;
    KSEMAPHORE                  SuspendSemaphore;
    LIST_ENTRY                  ThreadListEntry;
    UCHAR                       FreezeCount;
    UCHAR                       SuspendCount;
    UCHAR                       IdealProcessor;
    BOOLEAN                     DisableBoost;
} KTHREAD, *PKTHREAD;

#endif

#if (NTDDI_VERSION >= NTDDI_WS03)

typedef struct _MMSUPPORT_FLAGS {
    ULONG SessionSpace              : 1;
    ULONG BeingTrimmed              : 1;
    ULONG SessionLeader             : 1;
    ULONG TrimHard                  : 1;
    ULONG MaximumWorkingSetHard     : 1;
    ULONG ForceTrim                 : 1;
    ULONG MinimumWorkingSetHard     : 1;
    ULONG Available0                : 1;
    ULONG MemoryPriority            : 8;
    ULONG GrowWsleHash              : 1;
    ULONG AcquiredUnsafe            : 1;
    ULONG Available                 : 14;
} MMSUPPORT_FLAGS, *PMMSUPPORT_FLAGS;

#elif (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _MMSUPPORT_FLAGS {
    ULONG SessionSpace              : 1;
    ULONG BeingTrimmed              : 1;
    ULONG SessionLeader             : 1;
    ULONG TrimHard                  : 1;
    ULONG WorkingSetHard            : 1;
    ULONG AddressSpaceBeingDeleted  : 1;
    ULONG Available                 : 10;
    ULONG AllowWorkingSetAdjustment : 8;
    ULONG MemoryPriority            : 8;
} MMSUPPORT_FLAGS, *PMMSUPPORT_FLAGS;

#else

typedef struct _MMSUPPORT_FLAGS {
    ULONG SessionSpace      : 1;
    ULONG BeingTrimmed      : 1;
    ULONG ProcessInSession  : 1;
    ULONG SessionLeader     : 1;
    ULONG TrimHard          : 1;
    ULONG WorkingSetHard    : 1;
    ULONG WriteWatch        : 1;
    ULONG Filler            : 25;
} MMSUPPORT_FLAGS, *PMMSUPPORT_FLAGS;

#endif

#if (NTDDI_VERSION >= NTDDI_WS03)

typedef struct _MMSUPPORT {
    LIST_ENTRY      WorkingSetExpansionLinks;
    LARGE_INTEGER   LastTrimTime; // 0x8
    MMSUPPORT_FLAGS Flags; // 0x10
    ULONG           PageFaultCount; // 0x14
    ULONG           PeakWorkingSetSize; // 0x18
    ULONG           GrowthSinceLastEstimate; // 0x1c
    ULONG           MinimumWorkingSetSize; // 0x20
    ULONG           MaximumWorkingSetSize; // 0x24
    PMMWSL          VmWorkingSetList; // 0x28 
    ULONG           Claim; // 0x2c
    ULONG           NextEstimationSlot; // 0x30
    ULONG           NextAgingSlot; // 0x34
    ULONG           EstimatedAvailable; // 0x38
    ULONG           WorkingSetSize;  //0x3c
    KGUARDED_MUTEX  Mutex; // 0x40
} MMSUPPORT, *PMMSUPPORT;

#elif (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _MMSUPPORT {
    LARGE_INTEGER   LastTrimTime;
    MMSUPPORT_FLAGS Flags;
    ULONG           PageFaultCount;
    ULONG           PeakWorkingSetSize;
    ULONG           WorkingSetSize;
    ULONG           MinimumWorkingSetSize;
    ULONG           MaximumWorkingSetSize;
    PMMWSL          VmWorkingSetList;
    LIST_ENTRY      WorkingSetExpansionLinks;
    ULONG           Claim;
    ULONG           NextEstimationSlot;
    ULONG           NextAgingSlot;
    ULONG           EstimatedAvailable;
    ULONG           GrowthSinceLastEstimate;
} MMSUPPORT, *PMMSUPPORT;

#else

typedef struct _MMSUPPORT {
    LARGE_INTEGER   LastTrimTime;
    ULONG           LastTrimFaultCount;
    ULONG           PageFaultCount;
    ULONG           PeakWorkingSetSize;
    ULONG           WorkingSetSize;
    ULONG           MinimumWorkingSetSize;
    ULONG           MaximumWorkingSetSize;
    PMMWSL          VmWorkingSetList;
    LIST_ENTRY      WorkingSetExpansionLinks;
    BOOLEAN         AllowWorkingSetAdjustment;
    BOOLEAN         AddressSpaceBeingDeleted;
    UCHAR           ForegroundSwitchCount;
    UCHAR           MemoryPriority;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    union {
        ULONG           LongFlags;
        MMSUPPORT_FLAGS Flags;
    } u;
    ULONG           Claim;
    ULONG           NextEstimationSlot;
    ULONG           NextAgingSlot;
    ULONG           EstimatedAvailable;
    ULONG           GrowthSinceLastEstimate;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
} MMSUPPORT, *PMMSUPPORT;

#endif

typedef struct _SE_AUDIT_PROCESS_CREATION_INFO {
    POBJECT_NAME_INFORMATION ImageFileName;
} SE_AUDIT_PROCESS_CREATION_INFO, *PSE_AUDIT_PROCESS_CREATION_INFO;

typedef struct _BITMAP_DESCRIPTOR {
    ULONGLONG   StartLcn;
    ULONGLONG   ClustersToEndOfVol;
    UCHAR       Map[1];
} BITMAP_DESCRIPTOR, *PBITMAP_DESCRIPTOR;

typedef struct _BITMAP_RANGE {
    LIST_ENTRY      Links;
    LARGE_INTEGER   BasePage;
    ULONG           FirstDirtyPage;
    ULONG           LastDirtyPage;
    ULONG           DirtyPages;
    PULONG          Bitmap;
} BITMAP_RANGE, *PBITMAP_RANGE;

typedef struct _DEVICE_MAP {
    POBJECT_DIRECTORY   DosDevicesDirectory;
    POBJECT_DIRECTORY   GlobalDosDevicesDirectory;
    ULONG               ReferenceCount;
    ULONG               DriveMap;
    UCHAR               DriveType[32];
} DEVICE_MAP, *PDEVICE_MAP;

typedef struct _DIRECTORY_BASIC_INFORMATION {
    UNICODE_STRING ObjectName;
    UNICODE_STRING ObjectTypeName;
} DIRECTORY_BASIC_INFORMATION, *PDIRECTORY_BASIC_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _EX_FAST_REF {
    union {
        PVOID Object;
        ULONG RefCnt : 3;
        ULONG Value;
    };
} EX_FAST_REF, *PEX_FAST_REF;

#ifndef _NTIFS_

typedef struct _EX_PUSH_LOCK {
    union {
        struct {
            ULONG   Waiting     : 1;
            ULONG   Exclusive   : 1;
            ULONG   Shared      : 30;
        };
        ULONG   Value;
        PVOID   Ptr;
    };
} EX_PUSH_LOCK, *PEX_PUSH_LOCK;

#endif // _NTIFS_

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

#if (NTDDI_VERSION >= NTDDI_WS03)

typedef struct _MM_ADDRESS_NODE {
    union {
        ULONG                   Balance : 2;
        struct _MM_ADDRESS_NODE *Parent; // lower 2 bits of Parent are Balance and must be zeroed to obtain Parent
    };
    struct _MM_ADDRESS_NODE     *LeftChild;
    struct _MM_ADDRESS_NODE     *RightChild;
    ULONG_PTR                   StartingVpn;
    ULONG_PTR                   EndingVpn;
} MMADDRESS_NODE, *PMMADDRESS_NODE;

typedef struct _MM_AVL_TABLE {
    MMADDRESS_NODE  BalancedRoot; // Vadroot; incorrectly represents the NULL pages (EndingVpn should be 0xf, etc.)
    ULONG           DepthOfTree : 5; // 0x14
    ULONG           Unused : 3;
    ULONG           NumberGenericTableElements : 24; // total number of nodes
    PVOID           NodeHint; // 0x18 (0x270 in _EPROCESS)
    PVOID           NodeFreeHint; // 0x1c
} MM_AVL_TABLE, *PMM_AVL_TABLE;

typedef struct _EPROCESS {
    KPROCESS                        Pcb; // +0x000
    EX_PUSH_LOCK                    ProcessLock; // +0x06c
    LARGE_INTEGER                   CreateTime; // +0x070
    LARGE_INTEGER                   ExitTime; // +0x078
    EX_RUNDOWN_REF                  RundownProtect; // +0x080
    ULONG                           UniqueProcessId; // +0x084
    LIST_ENTRY                      ActiveProcessLinks; // +0x088
    ULONG                           QuotaUsage[3]; // +0x090
    ULONG                           QuotaPeak[3]; // +0x09c
    ULONG                           CommitCharge; // +0x0a8
    ULONG                           PeakVirtualSize; // +0x0ac
    ULONG                           VirtualSize; // +0x0b0
    LIST_ENTRY                      SessionProcessLinks; // +0x0b4
    PVOID                           DebugPort; // +0x0bc
    PVOID                           ExceptionPort; // +0x0c0
    PHANDLE_TABLE                   ObjectTable; // +0x0c4
    EX_FAST_REF                     Token; // +0x0c8
    ULONG                           WorkingSetPage; // +0x0cc
    KGUARDED_MUTEX                  AddressCreationLock; // +0x0d0
    ULONG                           HyperSpaceLock; // +0x0f0
    PETHREAD                        ForkInProgress; // +0x0f4
    ULONG                           HardwareTrigger; // +0x0f8
    PMM_AVL_TABLE                   PhysicalVadRoot; // +0x0fc
    PVOID                           CloneRoot; // +0x100
    ULONG                           NumberOfPrivatePages; // +0x104
    ULONG                           NumberOfLockedPages; // +0x108
    PVOID                           Win32Process; // +0x10c
    PEJOB                           Job; // +0x110
    PVOID                           SectionObject; // +0x114
    PVOID                           SectionBaseAddress; // +0x118
    PEPROCESS_QUOTA_BLOCK           QuotaBlock; // +0x11c
    PPAGEFAULT_HISTORY              WorkingSetWatch; // +0x120
    PVOID                           Win32WindowStation; // +0x124
    ULONG                           InheritedFromUniqueProcessId; // +0x128
    PVOID                           LdtInformation; // +0x12c
    PVOID                           VadFreeHint; // +0x130
    PVOID                           VdmObjects; // +0x134
    PVOID                           DeviceMap; // +0x138
    PVOID                           Spare0[3]; // +0x13c
    union {
        HARDWARE_PTE                PageDirectoryPte; // +0x148
        UINT64                      Filler; // +0x148
    };
    PVOID                           Session; // +0x150
    UCHAR                           ImageFileName[16]; // +0x154
    LIST_ENTRY                      JobLinks; // +0x164
    PVOID                           LockedPagesList; // +0x16c
    LIST_ENTRY                      ThreadListHead; // +0x170
    PVOID                           SecurityPort; // +0x178
    PVOID                           PaeTop; // +0x17c
    ULONG                           ActiveThreads; // +0x180
    ULONG                           GrantedAccess; // +0x184
    ULONG                           DefaultHardErrorProcessing; // +0x188
    SHORT                           LastThreadExitStatus; // +0x18c
    PPEB                            Peb; // +0x190
    EX_FAST_REF                     PrefetchTrace; // +0x194
    LARGE_INTEGER                   ReadOperationCount; // +0x198
    LARGE_INTEGER                   WriteOperationCount; // +0x1a0
    LARGE_INTEGER                   OtherOperationCount; // +0x1a8
    LARGE_INTEGER                   ReadTransferCount; // +0x1b0
    LARGE_INTEGER                   WriteTransferCount; // +0x1b8
    LARGE_INTEGER                   OtherTransferCount; // +0x1c0
    ULONG                           CommitChargeLimit; // +0x1c8
    ULONG                           CommitChargePeak; // +0x1cc
    PVOID                           AweInfo; // +0x1d0
    SE_AUDIT_PROCESS_CREATION_INFO  SeAuditProcessCreationInfo; // +0x1d4
    MMSUPPORT                       Vm; // +0x1d8
    LIST_ENTRY                      MmProcessLinks; // +0x238
    ULONG                           ModifiedPageCount; // +0x240
    ULONG                           JobStatus; // +0x244
    union {
        ULONG                       Flags; // 0x248
        struct {
            ULONG                   CreateReported              : 1;
            ULONG                   NoDebugInherit              : 1;
            ULONG                   ProcessExiting              : 1;
            ULONG                   ProcessDelete               : 1;
            ULONG                   Wow64SplitPages             : 1;
            ULONG                   VmDeleted                   : 1;
            ULONG                   OutswapEnabled              : 1;
            ULONG                   Outswapped                  : 1;
            ULONG                   ForkFailed                  : 1;
            ULONG                   Wow64VaSpace4Gb             : 1;
            ULONG                   AddressSpaceInitialized     : 2;
            ULONG                   SetTimerResolution          : 1;
            ULONG                   BreakOnTermination          : 1;
            ULONG                   SessionCreationUnderway     : 1;
            ULONG                   WriteWatch                  : 1;
            ULONG                   ProcessInSession            : 1;
            ULONG                   OverrideAddressSpace        : 1;
            ULONG                   HasAddressSpace             : 1;
            ULONG                   LaunchPrefetched            : 1;
            ULONG                   InjectInpageErrors          : 1;
            ULONG                   VmTopDown                   : 1;
            ULONG                   ImageNotifyDone             : 1;
            ULONG                   PdeUpdateNeeded             : 1;
            ULONG                   VdmAllowed                  : 1;
            ULONG                   Unused                      : 7;
        };
    };
    NTSTATUS                        ExitStatus; // +0x24c
    USHORT                          NextPageColor; // +0x250
    union {
        struct {
            UCHAR                   SubSystemMinorVersion; // +0x252
            UCHAR                   SubSystemMajorVersion; // +0x253
        };
        USHORT                      SubSystemVersion; // +0x252
    };
    UCHAR                           PriorityClass; // +0x254
    MM_AVL_TABLE                    VadRoot; // +0x258
} REAL_EPROCESS, *PREAL_EPROCESS; // 0x278 in total

#elif (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _EPROCESS {
    KPROCESS                        Pcb;
    EX_PUSH_LOCK                    ProcessLock;
    LARGE_INTEGER                   CreateTime;
    LARGE_INTEGER                   ExitTime;
    EX_RUNDOWN_REF                  RundownProtect;
    ULONG                           UniqueProcessId;
    LIST_ENTRY                      ActiveProcessLinks;
    ULONG                           QuotaUsage[3];
    ULONG                           QuotaPeak[3];
    ULONG                           CommitCharge;
    ULONG                           PeakVirtualSize;
    ULONG                           VirtualSize;
    LIST_ENTRY                      SessionProcessLinks;
    PVOID                           DebugPort;
    PVOID                           ExceptionPort;
    PHANDLE_TABLE                   ObjectTable;
    EX_FAST_REF                     Token;
    FAST_MUTEX                      WorkingSetLock;
    ULONG                           WorkingSetPage;
    FAST_MUTEX                      AddressCreationLock;
    KSPIN_LOCK                      HyperSpaceLock;
    PETHREAD                        ForkInProgress;
    ULONG                           HardwareTrigger;
    PVOID                           VadRoot;
    PVOID                           VadHint;
    PVOID                           CloneRoot;
    ULONG                           NumberOfPrivatePages;
    ULONG                           NumberOfLockedPages;
    PVOID                           Win32Process;
    PEJOB                           Job;
    PSECTION_OBJECT                 SectionObject;
    PVOID                           SectionBaseAddress;
    PEPROCESS_QUOTA_BLOCK           QuotaBlock;
    PPAGEFAULT_HISTORY              WorkingSetWatch;
    PVOID                           Win32WindowStation;
    PVOID                           InheritedFromUniqueProcessId;
    PVOID                           LdtInformation;
    PVOID                           VadFreeHint;
    PVOID                           VdmObjects;
    PDEVICE_MAP                     DeviceMap;
    LIST_ENTRY                      PhysicalVadList;
    union {
        HARDWARE_PTE                PageDirectoryPte;
        ULONGLONG                   Filler;
    };
    PVOID                           Session;
    UCHAR                           ImageFileName[16];
    LIST_ENTRY                      JobLinks;
    PVOID                           LockedPageList;
    LIST_ENTRY                      ThreadListHead;
    PVOID                           SecurityPort;
    PVOID                           PaeTop;
    ULONG                           ActiveThreads;
    ULONG                           GrantedAccess;
    ULONG                           DefaultHardErrorProcessing;
    NTSTATUS                        LastThreadExitStatus;
    PPEB                            Peb;
    EX_FAST_REF                     PrefetchTrace;
    LARGE_INTEGER                   ReadOperationCount;
    LARGE_INTEGER                   WriteOperationCount;
    LARGE_INTEGER                   OtherOperationCount;
    LARGE_INTEGER                   ReadTransferCount;
    LARGE_INTEGER                   WriteTransferCount;
    LARGE_INTEGER                   OtherTransferCount;
    ULONG                           CommitChargeLimit;
    ULONG                           CommitChargePeek;
    PVOID                           AweInfo;
    SE_AUDIT_PROCESS_CREATION_INFO  SeAuditProcessCreationInfo;
    MMSUPPORT                       Vm;
    ULONG                           LastFaultCount;
    ULONG                           ModifiedPageCount;
    ULONG                           NumberOfVads;
    ULONG                           JobStatus;
    union {
        ULONG                       Flags;
        struct {
            ULONG                   CreateReported              : 1;
            ULONG                   NoDebugInherit              : 1;
            ULONG                   ProcessExiting              : 1;
            ULONG                   ProcessDelete               : 1;
            ULONG                   Wow64SplitPages             : 1;
            ULONG                   VmDeleted                   : 1;
            ULONG                   OutswapEnabled              : 1;
            ULONG                   Outswapped                  : 1;
            ULONG                   ForkFailed                  : 1;
            ULONG                   HasPhysicalVad              : 1;
            ULONG                   AddressSpaceInitialized     : 2;
            ULONG                   SetTimerResolution          : 1;
            ULONG                   BreakOnTermination          : 1;
            ULONG                   SessionCreationUnderway     : 1;
            ULONG                   WriteWatch                  : 1;
            ULONG                   ProcessInSession            : 1;
            ULONG                   OverrideAddressSpace        : 1;
            ULONG                   HasAddressSpace             : 1;
            ULONG                   LaunchPrefetched            : 1;
            ULONG                   InjectInpageErrors          : 1;
            ULONG                   Unused                      : 11;
        };
    };
    NTSTATUS                        ExitStatus;
    USHORT                          NextPageColor;
    union {
        struct {
            UCHAR                   SubSystemMinorVersion;
            UCHAR                   SubSystemMajorVersion;
        };
        USHORT                      SubSystemVersion;
    };
    UCHAR                           PriorityClass;
    BOOLEAN                         WorkingSetAcquiredUnsafe;
} REAL_EPROCESS, *PREAL_EPROCESS;

#else

typedef struct _EPROCESS {
    KPROCESS                        Pcb;
    NTSTATUS                        ExitStatus;
    KEVENT                          LockEvent;
    ULONG                           LockCount;
    LARGE_INTEGER                   CreateTime;
    LARGE_INTEGER                   ExitTime;
    PKTHREAD                        LockOwner;
    ULONG                           UniqueProcessId;
    LIST_ENTRY                      ActiveProcessLinks;
    ULONGLONG                       QuotaPeakPoolUsage;
    ULONGLONG                       QuotaPoolUsage;
    ULONG                           PagefileUsage;
    ULONG                           CommitCharge;
    ULONG                           PeakPagefileUsage;
    ULONG                           PeakVirtualSize;
    ULONGLONG                       VirtualSize;
    MMSUPPORT                       Vm;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    LIST_ENTRY                      SessionProcessLinks;
#else // (NTDDI_VERSION < NTDDI_WIN2K)
    ULONG                           LastProtoPteFault;
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
    ULONG                           DebugPort;
    ULONG                           ExceptionPort;
    PHANDLE_TABLE                   ObjectTable;
    PACCESS_TOKEN                   Token;
    FAST_MUTEX                      WorkingSetLock;
    ULONG                           WorkingSetPage;
    BOOLEAN                         ProcessOutswapEnabled;
    BOOLEAN                         ProcessOutswapped;
    BOOLEAN                         AddressSpaceInitialized;
    BOOLEAN                         AddressSpaceDeleted;
    FAST_MUTEX                      AddressCreationLock;
    KSPIN_LOCK                      HyperSpaceLock;
    PETHREAD                        ForkInProgress;
    USHORT                          VmOperation;
    BOOLEAN                         ForkWasSuccessful;
    UCHAR                           MmAgressiveWsTrimMask;
    PKEVENT                         VmOperationEvent;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    PVOID                           PaeTop;
#else // (NTDDI_VERSION < NTDDI_WIN2K)
    HARDWARE_PTE                    PageDirectoryPte;
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
    ULONG                           LastFaultCount;
    ULONG                           ModifiedPageCount;
    PVOID                           VadRoot;
    PVOID                           VadHint;
    ULONG                           CloneRoot;
    ULONG                           NumberOfPrivatePages;
    ULONG                           NumberOfLockedPages;
    USHORT                          NextPageColor;
    BOOLEAN                         ExitProcessCalled;
    BOOLEAN                         CreateProcessReported;
    HANDLE                          SectionHandle;
    PPEB                            Peb;
    PVOID                           SectionBaseAddress;
    PEPROCESS_QUOTA_BLOCK           QuotaBlock;
    NTSTATUS                        LastThreadExitStatus;
    PPROCESS_WS_WATCH_INFORMATION   WorkingSetWatch;
    HANDLE                          Win32WindowStation;
    HANDLE                          InheritedFromUniqueProcessId;
    ACCESS_MASK                     GrantedAccess;
    ULONG                           DefaultHardErrorProcessing;
    PVOID                           LdtInformation;
    PVOID                           VadFreeHint;
    PVOID                           VdmObjects;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    PDEVICE_MAP                     DeviceMap;
    ULONG                           SessionId;
    LIST_ENTRY                      PhysicalVadList;
    HARDWARE_PTE                    PageDirectoryPte;
    ULONG                           Filler;
    ULONG                           PaePageDirectoryPage;
#else // (NTDDI_VERSION < NTDDI_WIN2K)
    KMUTANT                         ProcessMutant;
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
    UCHAR                           ImageFileName[16];
    ULONG                           VmTrimFaultValue;
    UCHAR                           SetTimerResolution;
    UCHAR                           PriorityClass;
    union {
        struct {
            UCHAR                   SubSystemMinorVersion;
            UCHAR                   SubSystemMajorVersion;
        };
        USHORT                      SubSystemVersion;
    };
    PVOID                           Win32Process;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    PEJOB                           Job;
    ULONG                           JobStatus;
    LIST_ENTRY                      JobLinks;
    PVOID                           LockedPageList;
    PVOID                           SecurityPort;
    PWOW64_PROCESS                  Wow64Process;
    LARGE_INTEGER                   ReadOperationCount;
    LARGE_INTEGER                   WriteOperationCount;
    LARGE_INTEGER                   OtherOperationCount;
    LARGE_INTEGER                   ReadTransferCount;
    LARGE_INTEGER                   WriteTransferCount;
    LARGE_INTEGER                   OtherTransferCount;
    ULONG                           CommitChargeLimit;
    ULONG                           CommitChargePeek;
    LIST_ENTRY                      ThreadListHead;
    PRTL_BITMAP                     VadPhysicalPagesBitMap;
    ULONG                           VadPhysicalPages;
    ULONG                           AweLock;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
} REAL_EPROCESS, *PREAL_EPROCESS;

#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _ETHREAD {
    KTHREAD                         Tcb;
    union {
        LARGE_INTEGER               CreateTime;
        struct {
            ULONG                   NestedFaultCount    : 2;
            ULONG                   ApcNeeded           : 1;
        };
    };
    union {
        LARGE_INTEGER               ExitTime;
        LIST_ENTRY                  LpcReplyChain;
        LIST_ENTRY                  KeyedWaitChain;
    };
    union {
        NTSTATUS                    ExitStatus;
        PVOID                       OfsChain;
    };
    LIST_ENTRY                      PostBlockList;
    union {
        PTERMINATION_PORT           TerminationPort;
        PETHREAD                    ReaperLink;
        PVOID                       KeyedWaitValue;
    };
    KSPIN_LOCK                      ActiveTimerListLock;
    LIST_ENTRY                      ActiveTimerListHead;
    CLIENT_ID                       Cid;
    union {
        KSEMAPHORE                  LpcReplySemaphore;
        KSEMAPHORE                  KeyedWaitSemaphore;
    };
    union {
        PLPC_MESSAGE                LpcReplyMessage;
        PVOID                       LpcWaitingOnPort;
    };
    PPS_IMPERSONATION_INFORMATION   ImpersonationInfo;
    LIST_ENTRY                      IrpList;
    ULONG                           TopLevelIrp;
    PDEVICE_OBJECT                  DeviceToVerify;
    PEPROCESS                       ThreadsProcess;
    PKSTART_ROUTINE                 StartAddress;
    union {
        PVOID                       Win32StartAddress;
        ULONG                       LpcReceivedMessageId;
    };
    LIST_ENTRY                      ThreadListEntry;
    EX_RUNDOWN_REF                  RundownProtect;
    EX_PUSH_LOCK                    ThreadLock;
    ULONG                           LpcReplyMessageId;
    ULONG                           ReadClusterSize;
    ACCESS_MASK                     GrantedAccess;
    union {
        ULONG                       CrossThreadFlags;
        struct {
            ULONG                   Terminated              : 1;
            ULONG                   DeadThread              : 1;
            ULONG                   HideFromDebugger        : 1;
            ULONG                   ActiveImpersonationInfo : 1;
            ULONG                   SystemThread            : 1;
            ULONG                   HardErrorsAreDisabled   : 1;
            ULONG                   BreakOnTermination      : 1;
            ULONG                   SkipCreationMsg         : 1;
            ULONG                   SkipTerminationMsg      : 1;
        };
    };
    union {
        ULONG                       SameThreadPassiveFlags;
        struct {
            ULONG                   ActiveExWorker          : 1;
            ULONG                   ExWorkerCanWaitUser     : 1;
            ULONG                   MemoryMaker             : 1;
            ULONG                   KeyedEventInUse         : 1;
        };
    };
    union {
        ULONG                       SameThreadApcFlags;
        struct {
            BOOLEAN                 LpcReceivedMsgIdValid   : 1;
            BOOLEAN                 LpcExitThreadCalled     : 1;
            BOOLEAN                 AddressSpaceOwner       : 1;
        };
    };
    BOOLEAN                         ForwardClusterOnly;
    BOOLEAN                         DisablePageFaultClustering;
} REAL_ETHREAD, *PREAL_ETHREAD;

#else

typedef struct _ETHREAD {
    KTHREAD                         Tcb;
    LARGE_INTEGER                   CreateTime;
    union {
        LARGE_INTEGER               ExitTime;
        LIST_ENTRY                  LpcReplyChain;
    };
    union {
        NTSTATUS                    ExitStatus;
        PVOID                       OfsChain;
    };
    LIST_ENTRY                      PostBlockList;
    LIST_ENTRY                      TerminationPortList;
    KSPIN_LOCK                      ActiveTimerListLock;
    LIST_ENTRY                      ActiveTimerListHead;
    CLIENT_ID                       Cid;
    KSEMAPHORE                      LpcReplySemaphore;
    PLPC_MESSAGE                    LpcReplyMessage;
    ULONG                           LpcReplyMessageId;
    ULONG                           PerformanceCountLow;
    PPS_IMPERSONATION_INFORMATION   ImpersonationInfo;
    LIST_ENTRY                      IrpList;
    PVOID                           TopLevelIrp;
    PDEVICE_OBJECT                  DeviceToVerify;
    ULONG                           ReadClusterSize;
    BOOLEAN                         ForwardClusterOnly;
    BOOLEAN                         DisablePageFaultClustering;
    BOOLEAN                         DeadThread;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    BOOLEAN                         HideFromDebugger;
    ULONG                           HasTerminated;
#else // (NTDDI_VERSION < NTDDI_WIN2K)
    BOOLEAN                         HasTerminated;
    PKEVENT_PAIR                    EventPair;
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
    ACCESS_MASK                     GrantedAccess;
    PEPROCESS                       ThreadsProcess;
    PKSTART_ROUTINE                 StartAddress;
    union {
        PVOID                       Win32StartAddress;
        ULONG                       LpcReceivedMessageId;
    };
    BOOLEAN                         LpcExitThreadCalled;
    BOOLEAN                         HardErrorsAreDisabled;
    BOOLEAN                         LpcReceivedMsgIdValid;
    BOOLEAN                         ActiveImpersonationInfo;
    ULONG                           PerformanceCountHigh;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    LIST_ENTRY                      ThreadListEntry;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
} REAL_ETHREAD, *PREAL_ETHREAD;

#endif

typedef struct _EPROCESS_QUOTA_ENTRY {
    ULONG Usage;
    ULONG Limit;
    ULONG Peak;
    ULONG Return;
} EPROCESS_QUOTA_ENTRY, *PEPROCESS_QUOTA_ENTRY;

typedef struct _EPROCESS_QUOTA_BLOCK {
    EPROCESS_QUOTA_ENTRY    QuotaEntry[3];
    LIST_ENTRY              QuotaList;
    ULONG                   ReferenceCount;
    ULONG                   ProcessCount;
} EPROCESS_QUOTA_BLOCK, *PEPROCESS_QUOTA_BLOCK;

typedef struct _EXCEPTION_REGISTRATION_RECORD {
   struct _EXCEPTION_REGISTRATION_RECORD    *Next;
   PVOID                                    Handler;
} EXCEPTION_REGISTRATION_RECORD, *PEXCEPTION_REGISTRATION_RECORD;

/*
 * When needing these parameters cast your PIO_STACK_LOCATION to
 * PEXTENDED_IO_STACK_LOCATION
 */
#if !defined(_ALPHA_) && !defined(_AMD64_) && !defined(_IA64_)
#include <pshpack4.h>
#endif
typedef struct _EXTENDED_IO_STACK_LOCATION {

    /* Included for padding */
    UCHAR MajorFunction;
    UCHAR MinorFunction;
    UCHAR Flags;
    UCHAR Control;

    union {

       struct {
          PIO_SECURITY_CONTEXT              SecurityContext;
          ULONG                             Options;
          USHORT                            Reserved;
          USHORT                            ShareAccess;
          PMAILSLOT_CREATE_PARAMETERS       Parameters;
       } CreateMailslot;

        struct {
            PIO_SECURITY_CONTEXT            SecurityContext;
            ULONG                           Options;
            USHORT                          Reserved;
            USHORT                          ShareAccess;
            PNAMED_PIPE_CREATE_PARAMETERS   Parameters;
        } CreatePipe;

        struct {
            ULONG                           OutputBufferLength;
            ULONG                           InputBufferLength;
            ULONG                           FsControlCode;
            PVOID                           Type3InputBuffer;
        } FileSystemControl;

        struct {
            PLARGE_INTEGER                  Length;
            ULONG                           Key;
            LARGE_INTEGER                   ByteOffset;
        } LockControl;

        struct {
            ULONG                           Length;
            ULONG                           CompletionFilter;
        } NotifyDirectory;

        struct {
            ULONG                           Length;
            PUNICODE_STRING                 FileName;
            FILE_INFORMATION_CLASS          FileInformationClass;
            ULONG                           FileIndex;
        } QueryDirectory;

        struct {
            ULONG                           Length;
            PVOID                           EaList;
            ULONG                           EaListLength;
            ULONG                           EaIndex;
        } QueryEa;

        struct {
            ULONG                           Length;
            PSID                            StartSid;
            PFILE_GET_QUOTA_INFORMATION     SidList;
            ULONG                           SidListLength;
        } QueryQuota;

        struct {
            ULONG                           Length;
        } SetEa;

        struct {
            ULONG                           Length;
        } SetQuota;

        struct {
            ULONG                           Length;
            FS_INFORMATION_CLASS            FsInformationClass;
        } SetVolume;

    } Parameters;

} EXTENDED_IO_STACK_LOCATION, *PEXTENDED_IO_STACK_LOCATION;
#if !defined(_ALPHA_) && !defined(_AMD64_) && !defined(_IA64_)
#include <poppack.h>
#endif

typedef struct _FILE_COPY_ON_WRITE_INFORMATION {
    BOOLEAN ReplaceIfExists;
    HANDLE  RootDirectory;
    ULONG   FileNameLength;
    WCHAR   FileName[1];
} FILE_COPY_ON_WRITE_INFORMATION, *PFILE_COPY_ON_WRITE_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN2K)

typedef struct _FILE_FS_OBJECT_ID_INFORMATION {
    UCHAR ObjectId[16];
    UCHAR ExtendedInfo[48];
} FILE_FS_OBJECT_ID_INFORMATION, *PFILE_FS_OBJECT_ID_INFORMATION;

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

#ifndef _NTIFS_

typedef struct _FILE_LOCK_INFO {
    LARGE_INTEGER   StartingByte;
    LARGE_INTEGER   Length;
    BOOLEAN         ExclusiveLock;
    ULONG           Key;
    PFILE_OBJECT    FileObject;
    PEPROCESS       Process;
    LARGE_INTEGER   EndingByte;
} FILE_LOCK_INFO, *PFILE_LOCK_INFO;

#endif // _NTIFS_

// raw internal file lock struct returned from FsRtlGetNextFileLock
typedef struct _FILE_SHARED_LOCK_ENTRY {
    PVOID           Unknown1;
    PVOID           Unknown2;
    FILE_LOCK_INFO  FileLock;
} FILE_SHARED_LOCK_ENTRY, *PFILE_SHARED_LOCK_ENTRY;

// raw internal file lock struct returned from FsRtlGetNextFileLock
typedef struct _FILE_EXCLUSIVE_LOCK_ENTRY {
    LIST_ENTRY      ListEntry;
    PVOID           Unknown1;
    PVOID           Unknown2;
    FILE_LOCK_INFO  FileLock;
} FILE_EXCLUSIVE_LOCK_ENTRY, *PFILE_EXCLUSIVE_LOCK_ENTRY;

typedef struct _FILE_MAILSLOT_PEEK_BUFFER {
    ULONG ReadDataAvailable;
    ULONG NumberOfMessages;
    ULONG MessageLength;
} FILE_MAILSLOT_PEEK_BUFFER, *PFILE_MAILSLOT_PEEK_BUFFER;

typedef struct _FILE_OLE_CLASSID_INFORMATION {
    GUID ClassId;
} FILE_OLE_CLASSID_INFORMATION, *PFILE_OLE_CLASSID_INFORMATION;

#ifdef _NTIFS_

typedef struct _FILE_OLE_ALL_INFORMATION {
    FILE_BASIC_INFORMATION          BasicInformation;
    FILE_STANDARD_INFORMATION       StandardInformation;
    FILE_INTERNAL_INFORMATION       InternalInformation;
    FILE_EA_INFORMATION             EaInformation;
    FILE_ACCESS_INFORMATION         AccessInformation;
    FILE_POSITION_INFORMATION       PositionInformation;
    FILE_MODE_INFORMATION           ModeInformation;
    FILE_ALIGNMENT_INFORMATION      AlignmentInformation;
    USN                             LastChangeUsn;
    USN                             ReplicationUsn;
    LARGE_INTEGER                   SecurityChangeTime;
    FILE_OLE_CLASSID_INFORMATION    OleClassIdInformation;
    FILE_OBJECTID_INFORMATION       ObjectIdInformation;
    FILE_STORAGE_TYPE               StorageType;
    ULONG                           OleStateBits;
    ULONG                           OleId;
    ULONG                           NumberOfStreamReferences;
    ULONG                           StreamIndex;
    ULONG                           SecurityId;
    BOOLEAN                         ContentIndexDisable;
    BOOLEAN                         InheritContentIndexDisable;
    FILE_NAME_INFORMATION           NameInformation;
} FILE_OLE_ALL_INFORMATION, *PFILE_OLE_ALL_INFORMATION;

#endif // _NTIFS_

typedef struct _FILE_OLE_DIR_INFORMATION {
    ULONG               NextEntryOffset;
    ULONG               FileIndex;
    LARGE_INTEGER       CreationTime;
    LARGE_INTEGER       LastAccessTime;
    LARGE_INTEGER       LastWriteTime;
    LARGE_INTEGER       ChangeTime;
    LARGE_INTEGER       EndOfFile;
    LARGE_INTEGER       AllocationSize;
    ULONG               FileAttributes;
    ULONG               FileNameLength;
    FILE_STORAGE_TYPE   StorageType;
    GUID                OleClassId;
    ULONG               OleStateBits;
    BOOLEAN             ContentIndexDisable;
    BOOLEAN             InheritContentIndexDisable;
    WCHAR               FileName[1];
} FILE_OLE_DIR_INFORMATION, *PFILE_OLE_DIR_INFORMATION;

#ifdef _NTIFS_

typedef struct _FILE_OLE_INFORMATION {
    LARGE_INTEGER                   SecurityChangeTime;
    FILE_OLE_CLASSID_INFORMATION    OleClassIdInformation;
    FILE_OBJECTID_INFORMATION       ObjectIdInformation;
    FILE_STORAGE_TYPE               StorageType;
    ULONG                           OleStateBits;
    BOOLEAN                         ContentIndexDisable;
    BOOLEAN                         InheritContentIndexDisable;
} FILE_OLE_INFORMATION, *PFILE_OLE_INFORMATION;

#endif // _NTIFS_

typedef struct _FILE_OLE_STATE_BITS_INFORMATION {
    ULONG StateBits;
    ULONG StateBitsMask;
} FILE_OLE_STATE_BITS_INFORMATION, *PFILE_OLE_STATE_BITS_INFORMATION;

typedef struct _HANDLE_INFO {       // Information about open handles
    union {
        PEPROCESS   Process;        // Pointer to PEPROCESS owning the Handle
        ULONG       Count;          // Count of HANDLE_INFO structures following this structure
    } HandleInfo;
    USHORT          HandleCount;
} HANDLE_INFO, *PHANDLE_INFO;

typedef struct _HANDLE_TABLE_ENTRY_INFO {
    ULONG AuditMask;
} HANDLE_TABLE_ENTRY_INFO, *PHANDLE_TABLE_ENTRY_INFO;

typedef struct _HANDLE_TABLE_ENTRY {
    union {
        PVOID                       Object;
        ULONG                       ObAttributes;
        PHANDLE_TABLE_ENTRY_INFO    InfoTable;
        ULONG                       Value;
    };
    union {
        ULONG                       GrantedAccess;
        USHORT                      GrantedAccessIndex;
        LONG                        NextFreeTableEntry;
    };
    USHORT                          CreatorBackTraceIndex;
} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;

typedef struct _MAPPING_PAIR {
    ULONGLONG Vcn;
    ULONGLONG Lcn;
} MAPPING_PAIR, *PMAPPING_PAIR;

typedef struct _GET_RETRIEVAL_DESCRIPTOR {
    ULONG           NumberOfPairs;
    ULONGLONG       StartVcn;
    MAPPING_PAIR    Pair[1];
} GET_RETRIEVAL_DESCRIPTOR, *PGET_RETRIEVAL_DESCRIPTOR;

typedef struct _INITIAL_TEB {
    ULONG Unknown_1;
    ULONG Unknown_2;
    PVOID StackTop;
    PVOID StackBase;
    PVOID Unknown_3;
} INITIAL_TEB, *PINITIAL_TEB;

typedef struct _IO_CLIENT_EXTENSION {
    struct _IO_CLIENT_EXTENSION *NextExtension;
    PVOID                       ClientIdentificationAddress;
} IO_CLIENT_EXTENSION, *PIO_CLIENT_EXTENSION;

typedef struct _IO_COMPLETION_BASIC_INFORMATION {
    LONG Depth;
} IO_COMPLETION_BASIC_INFORMATION, *PIO_COMPLETION_BASIC_INFORMATION;

typedef struct _KEVENT_PAIR {
    USHORT Type;
    USHORT Size;
    KEVENT Event1;
    KEVENT Event2;
} KEVENT_PAIR, *PKEVENT_PAIR;

typedef struct _KINTERRUPT {
    CSHORT              Type;
    CSHORT              Size;
    LIST_ENTRY          InterruptListEntry;
    PKSERVICE_ROUTINE   ServiceRoutine;
    PVOID               ServiceContext;
    KSPIN_LOCK          SpinLock;
    ULONG               TickCount;
    PKSPIN_LOCK         ActualLock;
    PVOID               DispatchAddress;
    ULONG               Vector;
    KIRQL               Irql;
    KIRQL               SynchronizeIrql;
    BOOLEAN             FloatingSave;
    BOOLEAN             Connected;
    CHAR                Number;
    UCHAR               ShareVector;
    KINTERRUPT_MODE     Mode;
    ULONG               ServiceCount;
    ULONG               DispatchCount;
    ULONG               DispatchCode[106];
} KINTERRUPT, *PKINTERRUPT;

#ifndef _NTIFS_

typedef struct _LARGE_MCB {
    PFAST_MUTEX FastMutex;
    ULONG       MaximumPairCount;
    ULONG       PairCount;
    POOL_TYPE   PoolType;
    PVOID       Mapping;
} LARGE_MCB, *PLARGE_MCB;

typedef struct _MCB {
    LARGE_MCB LargeMcb;
} MCB, *PMCB;

#endif // _NTIFS_

typedef struct _LPC_MESSAGE {
    USHORT      DataSize;
    USHORT      MessageSize;
    USHORT      MessageType;
    USHORT      VirtualRangesOffset;
    CLIENT_ID   ClientId;
    ULONG       MessageId;
    ULONG       SectionSize;
    UCHAR       Data[1];
} LPC_MESSAGE, *PLPC_MESSAGE;

typedef struct _LPC_SECTION_READ {
    ULONG Length;
    ULONG ViewSize;
    PVOID ViewBase;
} LPC_SECTION_READ, *PLPC_SECTION_READ;

typedef struct _LPC_SECTION_WRITE {
    ULONG   Length;
    HANDLE  SectionHandle;
    ULONG   SectionOffset;
    ULONG   ViewSize;
    PVOID   ViewBase;
    PVOID   TargetViewBase;
} LPC_SECTION_WRITE, *PLPC_SECTION_WRITE;

typedef struct _MAILSLOT_CREATE_PARAMETERS {
    ULONG           MailslotQuota;
    ULONG           MaximumMessageSize;
    LARGE_INTEGER   ReadTimeout;
    BOOLEAN         TimeoutSpecified;
} MAILSLOT_CREATE_PARAMETERS, *PMAILSLOT_CREATE_PARAMETERS;

typedef struct _MBCB {
    CSHORT          NodeTypeCode;
    CSHORT          NodeIsInZone;
    ULONG           PagesToWrite;
    ULONG           DirtyPages;
    ULONG           Reserved;
    LIST_ENTRY      BitmapRanges;
    LONGLONG        ResumeWritePage;
    BITMAP_RANGE    BitmapRange1;
    BITMAP_RANGE    BitmapRange2;
    BITMAP_RANGE    BitmapRange3;
} MBCB, *PMBCB;

typedef struct _MOVEFILE_DESCRIPTOR {
     HANDLE         FileHandle; 
     ULONG          Reserved;   
     LARGE_INTEGER  StartVcn; 
     LARGE_INTEGER  TargetLcn;
     ULONG          NumVcns; 
     ULONG          Reserved1;  
} MOVEFILE_DESCRIPTOR, *PMOVEFILE_DESCRIPTOR;

typedef struct _NAMED_PIPE_CREATE_PARAMETERS {
    ULONG           NamedPipeType;
    ULONG           ReadMode;
    ULONG           CompletionMode;
    ULONG           MaximumInstances;
    ULONG           InboundQuota;
    ULONG           OutboundQuota;
    LARGE_INTEGER   DefaultTimeout;
    BOOLEAN         TimeoutSpecified;
} NAMED_PIPE_CREATE_PARAMETERS, *PNAMED_PIPE_CREATE_PARAMETERS;

typedef struct _QUOTA_BLOCK {
    KSPIN_LOCK  QuotaLock;
    ULONG       ReferenceCount; // Number of processes using this block
    ULONG       PeakNonPagedPoolUsage;
    ULONG       PeakPagedPoolUsage;
    ULONG       NonPagedpoolUsage;
    ULONG       PagedPoolUsage;
    ULONG       NonPagedPoolLimit;
    ULONG       PagedPoolLimit;
    ULONG       PeakPagefileUsage;
    ULONG       PagefileUsage;
    ULONG       PageFileLimit;
} QUOTA_BLOCK, *PQUOTA_BLOCK;

typedef struct _OBJECT_BASIC_INFO {
    ULONG           Attributes;
    ACCESS_MASK     GrantedAccess;
    ULONG           HandleCount;
    ULONG           ReferenceCount;
    ULONG           PagedPoolUsage;
    ULONG           NonPagedPoolUsage;
    ULONG           Reserved[3];
    ULONG           NameInformationLength;
    ULONG           TypeInformationLength;
    ULONG           SecurityDescriptorLength;
    LARGE_INTEGER   CreateTime;
} OBJECT_BASIC_INFO, *POBJECT_BASIC_INFO;

typedef struct _OBJECT_CREATE_INFORMATION {
    ULONG                           Attributes;
    HANDLE                          RootDirectory; // 0x4
    PVOID                           ParseContext; // 0x8
    KPROCESSOR_MODE                 ProbeMode; // 0xc
    ULONG                           PagedPoolCharge; // 0x10
    ULONG                           NonPagedPoolCharge; // 0x14
    ULONG                           SecurityDescriptorCharge; // 0x18
    PSECURITY_DESCRIPTOR            SecurityDescriptor; // 0x1c
    PSECURITY_QUALITY_OF_SERVICE    SecurityQos; // 0x20
    SECURITY_QUALITY_OF_SERVICE     SecurityQualityOfService; // 0x24
} OBJECT_CREATE_INFORMATION, *POBJECT_CREATE_INFORMATION;

typedef struct _OBJECT_CREATOR_INFO {
    LIST_ENTRY  Creator;
    ULONG       UniqueProcessId; // Creator's Process ID
    ULONG       Reserved; // Alignment
} OBJECT_CREATOR_INFO, *POBJECT_CREATOR_INFO;

typedef struct _OBJECT_DIRECTORY_ITEM {
    struct _OBJECT_DIRECTORY_ITEM   *Next;
    PVOID                           Object;
} OBJECT_DIRECTORY_ITEM, *POBJECT_DIRECTORY_ITEM;

typedef struct _OBJECT_DIRECTORY {
    POBJECT_DIRECTORY_ITEM  HashEntries[0x25];
    POBJECT_DIRECTORY_ITEM  LastHashAccess;
    ULONG                   LastHashResult;
} OBJECT_DIRECTORY, *POBJECT_DIRECTORY;

typedef struct _OBJECT_HANDLE_ATTRIBUTE_INFO {
    BOOLEAN Inherit;
    BOOLEAN ProtectFromClose;
} OBJECT_HANDLE_ATTRIBUTE_INFO, *POBJECT_HANDLE_ATTRIBUTE_INFO;

typedef struct _OBJECT_HANDLE_DB {
    union {
        struct _EPROCESS                *Process;
        struct _OBJECT_HANDLE_DB_LIST   *HandleDBList;
    };
    ULONG                               HandleCount;
} OBJECT_HANDLE_DB, *POBJECT_HANDLE_DB;

typedef struct _OBJECT_HANDLE_DB_LIST {
    ULONG               Count;
    OBJECT_HANDLE_DB    Entries[1];
} OBJECT_HANDLE_DB_LIST, *POBJECT_HANDLE_DB_LIST;

typedef struct _OBJECT_HEADER_FLAGS {
    ULONG NameInfoOffset     : 8;
    ULONG HandleInfoOffset   : 8;
    ULONG QuotaInfoOffset    : 8;
    ULONG QuotaBlock         : 1;   // QuotaBlock/ObjectInfo
    ULONG KernelMode         : 1;   // UserMode/KernelMode
    ULONG CreatorInfo        : 1;
    ULONG Exclusive          : 1;
    ULONG Permanent          : 1;
    ULONG SecurityDescriptor : 1;
    ULONG HandleInfo         : 1;
    ULONG Reserved           : 1;
} OBJECT_HEADER_FLAGS, *POBJECT_HEADER_FLAGS;

typedef struct _OBJECT_HEADER {
    ULONG                           ReferenceCount;
    union {
        ULONG                       HandleCount;
        PSINGLE_LIST_ENTRY          NextToFree;
    }; // 0x4
    POBJECT_TYPE                    ObjectType; // 0x8
    OBJECT_HEADER_FLAGS             Flags; // 0xc
    union {
        POBJECT_CREATE_INFORMATION  ObjectCreateInfo;
        PQUOTA_BLOCK                QuotaBlock;
    }; // 0x10
    PSECURITY_DESCRIPTOR            SecurityDescriptor; // 0x14
    QUAD                            Body; // 0x18
} OBJECT_HEADER, *POBJECT_HEADER;

typedef struct _OBJECT_NAME {
    POBJECT_DIRECTORY   Directory; 
    UNICODE_STRING      ObjectName;
    ULONG               Reserved;
} OBJECT_NAME, *POBJECT_NAME;

typedef struct _OBJECT_NAME_INFO {
    UNICODE_STRING  ObjectName;
    WCHAR           ObjectNameBuffer[1];
} OBJECT_NAME_INFO, *POBJECT_NAME_INFO;

typedef struct _OBJECT_PROTECTION_INFO {
    BOOLEAN Inherit;
    BOOLEAN ProtectHandle;
} OBJECT_PROTECTION_INFO, *POBJECT_PROTECTION_INFO;

typedef struct _OBJECT_QUOTA_CHARGES {
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    ULONG SecurityCharge;
    ULONG Reserved;
} OBJECT_QUOTA_CHARGES, *POBJECT_QUOTA_CHARGES;

typedef struct _OBJECT_QUOTA_INFO {
    ULONG       PagedPoolQuota;
    ULONG       NonPagedPoolQuota;
    ULONG       QuotaInformationSize;
    PEPROCESS   Process; // Owning process
} OBJECT_QUOTA_INFO, *POBJECT_QUOTA_INFO;

typedef struct _OBJECT_TYPE_INITIALIZER {
    USHORT          Length;
    BOOLEAN         UseDefaultObject;
    BOOLEAN         Reserved1;
    ULONG           InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ACCESS_MASK     ValidAccessMask;
    BOOLEAN         SecurityRequired;
    BOOLEAN         MaintainHandleCount;  /* OBJECT_HANDLE_DB */
    BOOLEAN         MaintainTypeList;     /* OBJECT_CREATOR_INFO */
    UCHAR           Reserved2;
    BOOLEAN         PagedPool;
    ULONG           DefaultPagedPoolCharge;
    ULONG           DefaultNonPagedPoolCharge;
    PVOID           DumpProcedure;
    PVOID           OpenProcedure;
    PVOID           CloseProcedure;
    PVOID           DeleteProcedure;
    PVOID           ParseProcedure;
    PVOID           SecurityProcedure;    /* SeDefaultObjectMethod */
    PVOID           QueryNameProcedure;
    PVOID           OkayToCloseProcedure;
} OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;

typedef struct _OBJECT_TYPE {
    ERESOURCE               Lock;
    LIST_ENTRY              ObjectListHead; /* OBJECT_CREATOR_INFO */
    UNICODE_STRING          ObjectTypeName;
    union {
        PVOID               DefaultObject;  /* ObpDefaultObject */
        ULONG               Code; /* File: 5C, WaitablePort: A0 */
    };
    ULONG                   ObjectTypeIndex; /* OB_TYPE_INDEX_* */
    ULONG                   ObjectCount;
    ULONG                   HandleCount;
    ULONG                   PeakObjectCount;
    ULONG                   PeakHandleCount;
    OBJECT_TYPE_INITIALIZER TypeInfo;
    ULONG                   ObjectTypeTag;   /* OB_TYPE_TAG_* */
} OBJECT_TYPE, *POBJECT_TYPE;

typedef struct _OBJECT_TYPE_INFO {
    UNICODE_STRING  ObjectTypeName;
    UCHAR           Unknown[0x58];
    WCHAR           ObjectTypeNameBuffer[1];
} OBJECT_TYPE_INFO, *POBJECT_TYPE_INFO;

typedef struct _OBJECT_ALL_TYPES_INFO {
    ULONG               NumberOfObjectTypes;
    OBJECT_TYPE_INFO    ObjectsTypeInfo[1];
} OBJECT_ALL_TYPES_INFO, *POBJECT_ALL_TYPES_INFO;

typedef struct _PAGEFAULT_HISTORY {
    ULONG                           CurrentIndex;
    ULONG                           MaxIndex;
    KSPIN_LOCK                      SpinLock;
    PVOID                           Reserved;
    PROCESS_WS_WATCH_INFORMATION    WatchInfo[1];
} PAGEFAULT_HISTORY, *PPAGEFAULT_HISTORY;

#if (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _PRIVATE_CACHE_MAP_FLAGS {
    ULONG DontUse           : 16;
    ULONG ReadAheadActive   : 1;
    ULONG ReadAheadEnabled  : 1;
    ULONG Available         : 14;
} PRIVATE_CACHE_MAP_FLAGS, *PPRIVATE_CACHE_MAP_FLAGS;

typedef struct _PRIVATE_CACHE_MAP {
    union {
        CSHORT                  NodeTypeCode;
        PRIVATE_CACHE_MAP_FLAGS Flags;
        ULONG                   UlongFlags;
    };
    ULONG                       ReadAheadMask;
    PFILE_OBJECT                FileObject;
    LARGE_INTEGER               FileOffset1;
    LARGE_INTEGER               BeyondLastByte1;
    LARGE_INTEGER               FileOffset2;
    LARGE_INTEGER               BeyondLastByte2;
    LARGE_INTEGER               ReadAheadOffset[2];
    ULONG                       ReadAheadLength[2];
    KSPIN_LOCK                  ReadAheadSpinLock;
    LIST_ENTRY                  PrivateLinks;
} PRIVATE_CACHE_MAP, *PPRIVATE_CACHE_MAP;

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _PROCESS_PRIORITY_CLASS {
    BOOLEAN Foreground;
    UCHAR   PriorityClass;
} PROCESS_PRIORITY_CLASS, *PPROCESS_PRIORITY_CLASS;

typedef struct _PS_IMPERSONATION_INFORMATION {
    PACCESS_TOKEN                   Token;
    BOOLEAN                         CopyOnOpen;
    BOOLEAN                         EffectiveOnly;
    SECURITY_IMPERSONATION_LEVEL    ImpersonationLevel;
} PS_IMPERSONATION_INFORMATION, *PPS_IMPERSONATION_INFORMATION;

typedef struct _SECTION_BASIC_INFORMATION {
    PVOID           BaseAddress;
    ULONG           Attributes;
    LARGE_INTEGER   Size;
} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

typedef struct _SECTION_IMAGE_INFORMATION {
    PVOID   EntryPoint;
    ULONG   Unknown1;
    ULONG   StackReserve;
    ULONG   StackCommit;
    ULONG   Subsystem;
    USHORT  MinorSubsystemVersion;
    USHORT  MajorSubsystemVersion;
    ULONG   Unknown2;
    ULONG   Characteristics;
    USHORT  ImageNumber;
    BOOLEAN Executable;
    UCHAR   Unknown3;
    ULONG   Unknown4[3];
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _SECTION_OBJECT {
    PVOID                   StartingVa;
    PVOID                   EndingVa;
    struct _SECTION_OBJECT  *Parent;
    struct _SECTION_OBJECT  *LeftChild;
    struct _SECTION_OBJECT  *RightChild;
    PVOID                   Segment;
} SECTION_OBJECT, *PSECTION_OBJECT;

typedef struct _SEP_AUDIT_POLICY {
    // _SEP_AUDIT_POLICY_CATEGORIES
    ULONGLONG System                    : 4;
    ULONGLONG Logon                     : 4;
    ULONGLONG ObjectAccess              : 4;
    ULONGLONG PrivilegeUse              : 4;
    ULONGLONG DetailedTracking          : 4;
    ULONGLONG PolicyChange              : 4;
    ULONGLONG AccountManagement         : 4;
    ULONGLONG DirectoryServiceAccess    : 4;
    ULONGLONG AccountLogon              : 4;
    // _SEP_AUDIT_POLICY_OVERLAY
    ULONGLONG SetBit                    : 1;
} SEP_AUDIT_POLICY, *PSEP_AUDIT_POLICY;

/* size 0x1C */
typedef struct _SEP_AUDIT_POLICY_VISTA {
    UCHAR   PerUserPolicy[25];  /* +0x000 */
    UCHAR   PolicySetStatus;    /* +0x019 */
    USHORT  Alignment;          /* +0x01A */
} SEP_AUDIT_POLICY_VISTA, *PSEP_AUDIT_POLICY_VISTA;

typedef struct _SERVICE_DESCRIPTOR_TABLE {
    /*
     * Table containing cServices elements of pointers to service handler
     * functions, indexed by service ID.
     */
    PVOID   *ServiceTable;
    /*
     * Table that counts how many times each service is used. This table
     * is only updated in checked builds.
     */
    PULONG  CounterTable;
    /*
     * Number of services contained in this table.
     */
    ULONG   TableSize;
    /*
     * Table containing the number of bytes of parameters the handler
     * function takes.
     */
    PUCHAR  ArgumentTable;
} SERVICE_DESCRIPTOR_TABLE, *PSERVICE_DESCRIPTOR_TABLE;

#if (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _SHARED_CACHE_MAP {
    CSHORT                      NodeTypeCode;
    CSHORT                      NodeByteSize;
    ULONG                       OpenCount;
    LARGE_INTEGER               FileSize;
    LIST_ENTRY                  BcbList;
    LARGE_INTEGER               SectionSize;
    LARGE_INTEGER               ValidDataLength;
    LARGE_INTEGER               ValidDataGoal;
    PVACB                       InitialVacbs[4];
    PVACB                       *Vacbs;
    PFILE_OBJECT                FileObject;
    PVACB                       ActiveVacb;
    PVOID                       NeedToZero;
    ULONG                       ActivePage;
    ULONG                       NeedToZeroPage;
    KSPIN_LOCK                  ActiveVacbSpinLock;
    ULONG                       VacbActiveCount;
    ULONG                       DirtyPages;
    LIST_ENTRY                  SharedCacheMapLinks;
    ULONG                       Flags;
    NTSTATUS                    Status;
    PMBCB                       Mbcb;
    PVOID                       Section;
    PKEVENT                     CreateEvent;
    PKEVENT                     WaitOnActiveCount;
    ULONG                       PagesToWrite;
    LONGLONG                    BeyondLastFlush;
    PCACHE_MANAGER_CALLBACKS    Callbacks;
    PVOID                       LazyWriteContext;
    LIST_ENTRY                  PrivateList;
    PVOID                       LogHandle;
    PVOID                       FlushToLsnRoutine;
    ULONG                       DirtyPageThreshold;
    ULONG                       LazyWritePassCount;
    PCACHE_UNINITIALIZE_EVENT   UninitializeEvent;
    PVACB                       NeedToZeroVacb;
    KSPIN_LOCK                  BcbSpinLock;
    PVOID                       Reserved;
    KEVENT                      Event;
    EX_PUSH_LOCK                VacbPushLock;
    PRIVATE_CACHE_MAP           PrivateCacheMap;
} SHARED_CACHE_MAP, *PSHARED_CACHE_MAP;

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

#ifndef _NTIFS_

typedef struct _SID_AND_ATTRIBUTES {
    PSID    Sid;
    ULONG   Attributes;
} SID_AND_ATTRIBUTES, *PSID_AND_ATTRIBUTES;

typedef struct _SID_AND_ATTRIBUTES_HASH {
    ULONG               SidCount;   /* +0x000 */
    PSID_AND_ATTRIBUTES SidAttr;    /* +0x004 */
    ULONG               Hash[32];   /* +0x008 */
} SID_AND_ATTRIBUTES_HASH, *PSID_AND_ATTRIBUTES_HASH;

#endif // _NTIFS_

// SystemBasicInformation
typedef struct _SYSTEM_BASIC_INFORMATION {
    ULONG Unknown;
    ULONG MaximumIncrement;
    ULONG PhysicalPageSize;
    ULONG NumberOfPhysicalPages;
    ULONG LowestPhysicalPage;
    ULONG HighestPhysicalPage;
    ULONG AllocationGranularity;
    ULONG LowestUserAddress;
    ULONG HighestUserAddress;
    ULONG ActiveProcessors;
    UCHAR NumberProcessors;
} SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

// SystemProcessorInformation
typedef struct _SYSTEM_PROCESSOR_INFORMATION {
    USHORT  ProcessorArchitecture;
    USHORT  ProcessorLevel;
    USHORT  ProcessorRevision;
    USHORT  Unknown;
    ULONG   FeatureBits;
} SYSTEM_PROCESSOR_INFORMATION, *PSYSTEM_PROCESSOR_INFORMATION;

// SystemPerformanceInformation
typedef struct _SYSTEM_PERFORMANCE_INFORMATION {
    LARGE_INTEGER   IdleTime;
    LARGE_INTEGER   ReadTransferCount;
    LARGE_INTEGER   WriteTransferCount;
    LARGE_INTEGER   OtherTransferCount;
    ULONG           ReadOperationCount;
    ULONG           WriteOperationCount;
    ULONG           OtherOperationCount;
    ULONG           AvailablePages;
    ULONG           TotalCommittedPages;
    ULONG           TotalCommitLimit;
    ULONG           PeakCommitment;
    ULONG           PageFaults;
    ULONG           WriteCopyFaults;
    ULONG           TransistionFaults;
    ULONG           Reserved1;
    ULONG           DemandZeroFaults;
    ULONG           PagesRead;
    ULONG           PageReadIos;
    ULONG           Reserved2[2];
    ULONG           PagefilePagesWritten;
    ULONG           PagefilePageWriteIos;
    ULONG           MappedFilePagesWritten;
    ULONG           MappedFilePageWriteIos;
    ULONG           PagedPoolUsage;
    ULONG           NonPagedPoolUsage;
    ULONG           PagedPoolAllocs;
    ULONG           PagedPoolFrees;
    ULONG           NonPagedPoolAllocs;
    ULONG           NonPagedPoolFrees;
    ULONG           TotalFreeSystemPtes;
    ULONG           SystemCodePage;
    ULONG           TotalSystemDriverPages;
    ULONG           TotalSystemCodePages;
    ULONG           SmallNonPagedLookasideListAllocateHits;
    ULONG           SmallPagedLookasideListAllocateHits;
    ULONG           Reserved3;
    ULONG           MmSystemCachePage;
    ULONG           PagedPoolPage;
    ULONG           SystemDriverPage;
    ULONG           FastReadNoWait;
    ULONG           FastReadWait;
    ULONG           FastReadResourceMiss;
    ULONG           FastReadNotPossible;
    ULONG           FastMdlReadNoWait;
    ULONG           FastMdlReadWait;
    ULONG           FastMdlReadResourceMiss;
    ULONG           FastMdlReadNotPossible;
    ULONG           MapDataNoWait;
    ULONG           MapDataWait;
    ULONG           MapDataNoWaitMiss;
    ULONG           MapDataWaitMiss;
    ULONG           PinMappedDataCount;
    ULONG           PinReadNoWait;
    ULONG           PinReadWait;
    ULONG           PinReadNoWaitMiss;
    ULONG           PinReadWaitMiss;
    ULONG           CopyReadNoWait;
    ULONG           CopyReadWait;
    ULONG           CopyReadNoWaitMiss;
    ULONG           CopyReadWaitMiss;
    ULONG           MdlReadNoWait;
    ULONG           MdlReadWait;
    ULONG           MdlReadNoWaitMiss;
    ULONG           MdlReadWaitMiss;
    ULONG           ReadAheadIos;
    ULONG           LazyWriteIos;
    ULONG           LazyWritePages;
    ULONG           DataFlushes;
    ULONG           DataPages;
    ULONG           ContextSwitches;
    ULONG           FirstLevelTbFills;
    ULONG           SecondLevelTbFills;
    ULONG           SystemCalls;
} SYSTEM_PERFORMANCE_INFORMATION, *PSYSTEM_PERFORMANCE_INFORMATION;

// SystemTimeOfDayInformation
typedef struct _SYSTEM_TIME_OF_DAY_INFORMATION {
    LARGE_INTEGER   BootTime;
    LARGE_INTEGER   CurrentTime;
    LARGE_INTEGER   TimeZoneBias;
    ULONG           CurrentTimeZoneId;
} SYSTEM_TIME_OF_DAY_INFORMATION, *PSYSTEM_TIME_OF_DAY_INFORMATION;

typedef struct _SYSTEM_THREADS_INFORMATION {
    LARGE_INTEGER   KernelTime;
    LARGE_INTEGER   UserTime;
    LARGE_INTEGER   CreateTime;
    ULONG           WaitTime;
    PVOID           StartAddress;
    CLIENT_ID       ClientId;
    KPRIORITY       Priority;
    KPRIORITY       BasePriority;
    ULONG           ContextSwitchCount;
    THREAD_STATE    State;
    KWAIT_REASON    WaitReason;
} SYSTEM_THREADS_INFORMATION, *PSYSTEM_THREADS_INFORMATION;

// SystemProcessesAndThreadsInformation
typedef struct _SYSTEM_PROCESSES_INFORMATION {
    ULONG                       NextEntryDelta;
    ULONG                       ThreadCount;
    ULONG                       Reserved1[6];
    LARGE_INTEGER               CreateTime;
    LARGE_INTEGER               UserTime;
    LARGE_INTEGER               KernelTime;
    UNICODE_STRING              ProcessName;
    KPRIORITY                   BasePriority;
    ULONG                       ProcessId;
    ULONG                       InheritedFromProcessId;
    ULONG                       HandleCount;
    ULONG                       SessionId;
    ULONG                       Reserved2;
    VM_COUNTERS                 VmCounters;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    IO_COUNTERS                 IoCounters;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
    SYSTEM_THREADS_INFORMATION  Threads[1];
} SYSTEM_PROCESSES_INFORMATION, *PSYSTEM_PROCESSES_INFORMATION;

// SystemCallCounts
typedef struct _SYSTEM_CALL_COUNTS {
    ULONG Size;
    ULONG NumberOfDescriptorTables;
    ULONG NumberOfRoutinesInTable[1];
    // On checked build this is followed by a ULONG CallCounts[1] variable length array.
} SYSTEM_CALL_COUNTS, *PSYSTEM_CALL_COUNTS;

// SystemConfigurationInformation
typedef struct _SYSTEM_CONFIGURATION_INFORMATION {
    ULONG DiskCount;
    ULONG FloppyCount;
    ULONG CdRomCount;
    ULONG TapeCount;
    ULONG SerialCount;
    ULONG ParallelCount;
} SYSTEM_CONFIGURATION_INFORMATION, *PSYSTEM_CONFIGURATION_INFORMATION;

// SystemProcessorTimes
typedef struct _SYSTEM_PROCESSOR_TIMES {
    LARGE_INTEGER   IdleTime;
    LARGE_INTEGER   KernelTime;
    LARGE_INTEGER   UserTime;
    LARGE_INTEGER   DpcTime;
    LARGE_INTEGER   InterruptTime;
    ULONG           InterruptCount;
} SYSTEM_PROCESSOR_TIMES, *PSYSTEM_PROCESSOR_TIMES;

// SystemGlobalFlag
typedef struct _SYSTEM_GLOBAL_FLAG {
    ULONG GlobalFlag;
} SYSTEM_GLOBAL_FLAG, *PSYSTEM_GLOBAL_FLAG;

// SystemModuleInformation
typedef struct _SYSTEM_MODULE_INFORMATION {
    ULONG   Reserved[2];
    PVOID   Base;
    ULONG   Size;
    ULONG   Flags;
    USHORT  Index;
    USHORT  Unknown;
    USHORT  LoadCount;
    USHORT  ModuleNameOffset;
    CHAR    ImageName[256];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

// SystemLockInformation
typedef struct _SYSTEM_LOCK_INFORMATION {
    PVOID   Address;
    USHORT  Type;
    USHORT  Reserved1;
    ULONG   ExclusiveOwnerThreadId;
    ULONG   ActiveCount;
    ULONG   ContentionCount;
    ULONG   Reserved2[2];
    ULONG   NumberOfSharedWaiters;
    ULONG   NumberOfExclusiveWaiters;
} SYSTEM_LOCK_INFORMATION, *PSYSTEM_LOCK_INFORMATION;

// SystemHandleInformation
typedef struct _SYSTEM_HANDLE_INFORMATION {
    ULONG       ProcessId;
    UCHAR       ObjectTypeNumber;
    UCHAR       Flags;
    USHORT      Handle;
    PVOID       Object;
    ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

// SystemObjectInformation
typedef struct _SYSTEM_OBJECT_TYPE_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           ObjectCount;
    ULONG           HandleCount;
    ULONG           TypeNumber;
    ULONG           InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ACCESS_MASK     ValidAccessMask;
    POOL_TYPE       PoolType;
    UCHAR           Unknown;
    UNICODE_STRING  Name;
} SYSTEM_OBJECT_TYPE_INFORMATION, *PSYSTEM_OBJECT_TYPE_INFORMATION;

typedef struct _SYSTEM_OBJECT_INFORMATION {
    ULONG                   NextEntryOffset;
    PVOID                   Object;
    ULONG                   CreatorProcessId;
    USHORT                  Unknown;
    USHORT                  Flags;
    ULONG                   PointerCount;
    ULONG                   HandleCount;
    ULONG                   PagedPoolUsage;
    ULONG                   NonPagedPoolUsage;
    ULONG                   ExclusiveProcessId;
    PSECURITY_DESCRIPTOR    SecurityDescriptor;
    UNICODE_STRING          Name;
} SYSTEM_OBJECT_INFORMATION, *PSYSTEM_OBJECT_INFORMATION;

// SystemPagefileInformation
typedef struct _SYSTEM_PAGEFILE_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           CurrentSize;
    ULONG           TotalUsed;
    ULONG           PeakUsed;
    UNICODE_STRING  FileName;
} SYSTEM_PAGEFILE_INFORMATION, *PSYSTEM_PAGEFILE_INFORMATION;

// SystemInstructionEmulationCounts
typedef struct _SYSTEM_INSTRUCTION_EMULATION_COUNTS {
    ULONG GenericInvalidOpcode;
    ULONG TwoByteOpcode;
    ULONG ESprefix;
    ULONG CSprefix;
    ULONG SSprefix;
    ULONG DSprefix;
    ULONG FSPrefix;
    ULONG GSprefix;
    ULONG OPER32prefix;
    ULONG ADDR32prefix;
    ULONG INSB;
    ULONG INSW;
    ULONG OUTSB;
    ULONG OUTSW;
    ULONG PUSHFD;
    ULONG POPFD;
    ULONG INTnn;
    ULONG INTO;
    ULONG IRETD;
    ULONG FloatingPointOpcode;
    ULONG INBimm;
    ULONG INWimm;
    ULONG OUTBimm;
    ULONG OUTWimm;
    ULONG INB;
    ULONG INW;
    ULONG OUTB;
    ULONG OUTW;
    ULONG LOCKprefix;
    ULONG REPNEprefix;
    ULONG REPprefix;
    ULONG CLI;
    ULONG STI;
    ULONG HLT;
} SYSTEM_INSTRUCTION_EMULATION_COUNTS, *PSYSTEM_INSTRUCTION_EMULATION_COUNTS;

// SystemCacheInformation
typedef struct _SYSTEM_CACHE_INFORMATION {
    ULONG SystemCacheWsSize;
    ULONG SystemCacheWsPeakSize;
    ULONG SystemCacheWsFaults;
    ULONG SystemCacheWsMinimum;
    ULONG SystemCacheWsMaximum;
    ULONG TransitionSharedPages;
    ULONG TransitionSharedPagesPeak;
    ULONG Reserved[2];
} SYSTEM_CACHE_INFORMATION, *PSYSTEM_CACHE_INFORMATION;

// SystemPoolTagInformation
typedef struct _SYSTEM_POOL_TAG_INFORMATION {
    CHAR    Tag[4];
    ULONG   PagedPoolAllocs;
    ULONG   PagedPoolFrees;
    ULONG   PagedPoolUsage;
    ULONG   NonPagedPoolAllocs;
    ULONG   NonPagedPoolFrees;
    ULONG   NonPagedPoolUsage;
} SYSTEM_POOL_TAG_INFORMATION, *PSYSTEM_POOL_TAG_INFORMATION;

// SystemProcessorStatistics
typedef struct _SYSTEM_PROCESSOR_STATISTICS {
    ULONG ContextSwitches;
    ULONG DpcCount;
    ULONG DpcRequestRate;
    ULONG TimeIncrement;
    ULONG DpcBypassCount;
    ULONG ApcBypassCount;
} SYSTEM_PROCESSOR_STATISTICS, *PSYSTEM_PROCESSOR_STATISTICS;

// SystemDpcInformation
typedef struct _SYSTEM_DPC_INFORMATION {
    ULONG Reserved;
    ULONG MaximumDpcQueueDepth;
    ULONG MinimumDpcRate;
    ULONG AdjustDpcThreshold;
    ULONG IdealDpcRate;
} SYSTEM_DPC_INFORMATION, *PSYSTEM_DPC_INFORMATION;

// SystemLoadImage
typedef struct _SYSTEM_LOAD_IMAGE {
    UNICODE_STRING  ModuleName;
    PVOID           ModuleBase;
    PVOID           Unknown;
    PVOID           EntryPoint;
    PVOID           ExportDirectory;
} SYSTEM_LOAD_IMAGE, *PSYSTEM_LOAD_IMAGE;

// SystemUnloadImage
typedef struct _SYSTEM_UNLOAD_IMAGE {
    PVOID ModuleBase;
} SYSTEM_UNLOAD_IMAGE, *PSYSTEM_UNLOAD_IMAGE;

// SystemTimeAdjustment
typedef struct _SYSTEM_QUERY_TIME_ADJUSTMENT {
    ULONG   TimeAdjustment;
    ULONG   MaximumIncrement;
    BOOLEAN TimeSynchronization;
} SYSTEM_QUERY_TIME_ADJUSTMENT, *PSYSTEM_QUERY_TIME_ADJUSTMENT;

// SystemTimeAdjustment
typedef struct _SYSTEM_SET_TIME_ADJUSTMENT {
    ULONG   TimeAdjustment;
    BOOLEAN TimeSynchronization;
} SYSTEM_SET_TIME_ADJUSTMENT, *PSYSTEM_SET_TIME_ADJUSTMENT;

// SystemCrashDumpInformation
typedef struct _SYSTEM_CRASH_DUMP_INFORMATION {
    HANDLE CrashDumpSectionHandle;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    HANDLE Unknown;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
} SYSTEM_CRASH_DUMP_INFORMATION, *PSYSTEM_CRASH_DUMP_INFORMATION;

// SystemExceptionInformation
typedef struct _SYSTEM_EXCEPTION_INFORMATION {
    ULONG AlignmentFixupCount;
    ULONG ExceptionDispatchCount;
    ULONG FloatingEmulationCount;
    ULONG Reserved;
} SYSTEM_EXCEPTION_INFORMATION, *PSYSTEM_EXCEPTION_INFORMATION;

// SystemCrashDumpStateInformation
typedef struct _SYSTEM_CRASH_DUMP_STATE_INFORMATION {
    ULONG ValidCrashDump;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    ULONG Unknown;
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
} SYSTEM_CRASH_DUMP_STATE_INFORMATION, *PSYSTEM_CRASH_DUMP_STATE_INFORMATION;

// SystemKernelDebuggerInformation
typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION {
    BOOLEAN DebuggerEnabled;
    BOOLEAN DebuggerNotPresent;
} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

// SystemContextSwitchInformation
typedef struct _SYSTEM_CONTEXT_SWITCH_INFORMATION {
    ULONG ContextSwitches;
    ULONG ContextSwitchCounters[11];
} SYSTEM_CONTEXT_SWITCH_INFORMATION, *PSYSTEM_CONTEXT_SWITCH_INFORMATION;

// SystemRegistryQuotaInformation
typedef struct _SYSTEM_REGISTRY_QUOTA_INFORMATION {
    ULONG RegistryQuota;
    ULONG RegistryQuotaInUse;
    ULONG PagedPoolSize;
} SYSTEM_REGISTRY_QUOTA_INFORMATION, *PSYSTEM_REGISTRY_QUOTA_INFORMATION;

// SystemLoadAndCallImage
typedef struct _SYSTEM_LOAD_AND_CALL_IMAGE {
    UNICODE_STRING ModuleName;
} SYSTEM_LOAD_AND_CALL_IMAGE, *PSYSTEM_LOAD_AND_CALL_IMAGE;

// SystemPrioritySeparation
typedef struct _SYSTEM_PRIORITY_SEPARATION {
    ULONG PrioritySeparation;
} SYSTEM_PRIORITY_SEPARATION, *PSYSTEM_PRIORITY_SEPARATION;

// SystemTimeZoneInformation
typedef struct _SYSTEM_TIME_ZONE_INFORMATION {
    LONG        Bias;
    WCHAR       StandardName[32];
    TIME_FIELDS StandardDate;
    LONG        StandardBias;
    WCHAR       DaylightName[32];
    TIME_FIELDS DaylightDate;
    LONG        DaylightBias;
} SYSTEM_TIME_ZONE_INFORMATION, *PSYSTEM_TIME_ZONE_INFORMATION;

// SystemLookasideInformation
typedef struct _SYSTEM_LOOKASIDE_INFORMATION {
    USHORT      Depth;
    USHORT      MaximumDepth;
    ULONG       TotalAllocates;
    ULONG       AllocateMisses;
    ULONG       TotalFrees;
    ULONG       FreeMisses;
    POOL_TYPE   Type;
    ULONG       Tag;
    ULONG       Size;
} SYSTEM_LOOKASIDE_INFORMATION, *PSYSTEM_LOOKASIDE_INFORMATION;

// SystemSetTimeSlipEvent
typedef struct _SYSTEM_SET_TIME_SLIP_EVENT {
    HANDLE TimeSlipEvent;
} SYSTEM_SET_TIME_SLIP_EVENT, *PSYSTEM_SET_TIME_SLIP_EVENT;

// SystemCreateSession
typedef struct _SYSTEM_CREATE_SESSION {
    ULONG Session;
} SYSTEM_CREATE_SESSION, *PSYSTEM_CREATE_SESSION;

// SystemDeleteSession
typedef struct _SYSTEM_DELETE_SESSION {
    ULONG Session;
} SYSTEM_DELETE_SESSION, *PSYSTEM_DELETE_SESSION;

// SystemRangeStartInformation
typedef struct _SYSTEM_RANGE_START_INFORMATION {
    PVOID SystemRangeStart;
} SYSTEM_RANGE_START_INFORMATION, *PSYSTEM_RANGE_START_INFORMATION;

// SystemSessionProcessesInformation
typedef struct _SYSTEM_SESSION_PROCESS_INFORMATION {
    ULONG SessionId;
    ULONG BufferSize;
    PVOID Buffer;
} SYSTEM_SESSION_PROCESS_INFORMATION, *PSYSTEM_SESSION_PROCESS_INFORMATION;

typedef struct _GDI_TEB_BATCH {
    ULONG Offset;
    ULONG HDC;
    ULONG Buffer[(NTDDI_VERSION >= NTDDI_WIN2K) ? 0x133 : 0x136];
} GDI_TEB_BATCH, *PGDI_TEB_BATCH;

#if (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME {
    struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME* Previous;
    struct _ACTIVATION_CONTEXT*                 ActivationContext; // 0x4
    ULONG                                       Flags; // 0x8
} RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

typedef struct _ACTIVATION_CONTEXT_STACK {
    ULONG                               Flags;
    ULONG                               NextCookieSequenceNumber;
    PRTL_ACTIVATION_CONTEXT_STACK_FRAME ActiveFrame; // 0x8
    LIST_ENTRY                          FrameListCache; // 0xc
} ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

typedef struct _Wx86ThreadState {
    PULONG  CallBx86Eip;
    PVOID   DeallocationCpu;
    UCHAR   UseKnownWx86Dll; // 0x8
    UCHAR   OleStubInvoked; // 0x9
} Wx86ThreadState, *PWx86ThreadState;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT {
    ULONG Flags;
    PCHAR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, *PTEB_ACTIVE_FRAME_CONTEXT;

typedef struct _TEB_ACTIVE_FRAME {
    ULONG                       Flags;
    struct _TEB_ACTIVE_FRAME    *Previous;
    PTEB_ACTIVE_FRAME_CONTEXT   Context;
} TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;

typedef struct _TEB // from Reactos, Native API; checked and corrected for 2003 and nt 4.0
                    // should also work on XP and 2000
                    // the reactos version was probably from NT 3.51 SP3
{
   NT_TIB Tib;                         /* 00h */
   PVOID EnvironmentPointer;           /* 1Ch */
   CLIENT_ID Cid;                      /* 20h */
   HANDLE RpcHandle;                   /* 28h */
   PVOID *ThreadLocalStorage;          /* 2Ch */
   PPEB Peb;                           /* 30h */
   ULONG LastErrorValue;               /* 34h */
   ULONG CountOfOwnedCriticalSections; /* 38h */
   PVOID CsrClientThread;              /* 3Ch */
   struct _W32THREAD* Win32ThreadInfo; /* 40h */    
   ULONG User32Reserved[26];           /* 44h */
   ULONG UserReserved[5];              /* ACh */
   PVOID WOW32Reserved;                /* C0h */
   LCID CurrentLocale;                 /* C4h */
   ULONG FpSoftwareStatusRegister;     /* C8h */
   PVOID SystemReserved1[0x36];        /* CCh */
#if (NTDDI_VERSION < NTDDI_WIN2K)
   PVOID Spare1;                       /* 1A4h */
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
   LONG ExceptionCode;                 /* 1A4h */
#if (NTDDI_VERSION >= NTDDI_WINXP)
   ACTIVATION_CONTEXT_STACK 
        ActivationContextStack;        /* 1A8h */
   UCHAR SpareBytes1[24];              /* 1BCh */
#elif (NTDDI_VERSION >= NTDDI_WIN2K)
   UCHAR SpareBytes1[0x2c];            /* 1A8h */
#else // (NTDDI_VERSION < NTDDI_WIN2K)
   ULONG SpareBytes1[0x14];            /* 1ACh */
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
   GDI_TEB_BATCH GdiTebBatch;          /* 1D4h */ /* 1FC for nt 4.0 */
   ULONG gdiRgn;                       /* 6A8h */ /* 6DCh for nt 4.0 */
   ULONG gdiPen;                       /* 6ACh */
   ULONG gdiBrush;                     /* 6B0h */
   CLIENT_ID RealClientId;             /* 6B4h */ /* 6E8h for nt 4.0 */
   PVOID GdiCachedProcessHandle;       /* 6BCh */
   ULONG GdiClientPID;                 /* 6C0h */
   ULONG GdiClientTID;                 /* 6C4h */
   PVOID GdiThreadLocaleInfo;          /* 6C8h */
#if (NTDDI_VERSION >= NTDDI_WIN2K)
   PVOID Win32ClientInfo[0x3e];        /* 6CCh */
   PVOID glDispatchTable[0xe9];        /* 7C4h */
   ULONG glReserved1[0x1d];            /* B68h */
#else // (NTDDI_VERSION < NTDDI_WIN2K)
   PVOID Win32ClientInfo[5];           /* 700h */
   PVOID glDispatchTable[0x118];       /* 714h */
   ULONG glReserved1[0x1a];            /* B74h */   
#endif // (NTDDI_VERSION < NTDDI_WIN2K)
   PVOID glReserved2;                  /* BDCh */
   PVOID glSectionInfo;                /* BE0h */
   PVOID glSection;                    /* BE4h */
   PVOID glTable;                      /* BE8h */
   PVOID glCurrentRC;                  /* BECh */
   PVOID glContext;                    /* BF0h */
   NTSTATUS LastStatusValue;           /* BF4h */
   UNICODE_STRING StaticUnicodeString; /* BF8h */
   WCHAR StaticUnicodeBuffer[0x105];   /* C00h */
   PVOID DeallocationStack;            /* E0Ch */
   PVOID TlsSlots[0x40];               /* E10h */
   LIST_ENTRY TlsLinks;                /* F10h */
   PVOID Vdm;                          /* F18h */
   PVOID ReservedForNtRpc;             /* F1Ch */
   PVOID DbgSsReserved[0x2];           /* F20h */
   ULONG HardErrorDisabled;            /* F28h */
   PVOID Instrumentation[0x10];        /* F2Ch */
   PVOID WinSockData;                  /* F6Ch */
   ULONG GdiBatchCount;                /* F70h */
   BOOLEAN InDbgPrint;                 /* F74h */
   BOOLEAN FreeStackOnTermination;     /* F75h */
   BOOLEAN HasFiberData;               /* F76h */
   UCHAR IdealProcessor;               /* F77h */
   ULONG Spare3;                       /* F78h */
   ULONG ReservedForPerf;              /* F7Ch */
   PVOID ReservedForOle;               /* F80h */
   ULONG WaitingOnLoaderLock;          /* F84h */
#if (NTDDI_VERSION >= NTDDI_WIN2K)
   Wx86ThreadState Wx86Thread;         /* F88h */
   PVOID* TlsExpansionSlots;           /* F94h */
   ULONG ImpersonationLocale;          /* F98h */
   ULONG IsImpersonating;              /* F9Ch */
   PVOID NlsCache;                     /* FA0h */
   PVOID pShimData;                    /* FA4h */
   ULONG HeapVirtualAffinity;          /* FA8h */
   PVOID CurrentTransactionHandle;     /* FACh */
   PTEB_ACTIVE_FRAME ActiveFrame;      /* FB0h*/
   PVOID FlsSlots;                     /* FB4h */
#endif // (NTDDI_VERSION >= NTDDI_WIN2K)
} TEB, *PTEB;

typedef struct _TERMINATION_PORT {
    struct _TERMINATION_PORT*   Next;
    PVOID                       Port;
} TERMINATION_PORT, *PTERMINATION_PORT;

typedef struct _THREAD_BASIC_INFORMATION {
    NTSTATUS    ExitStatus;
    PVOID       TebBaseAddress;
    ULONG       UniqueProcessId;
    ULONG       UniqueThreadId;
    KAFFINITY   AffinityMask;
    KPRIORITY   BasePriority;
    ULONG       DiffProcessPriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

#ifndef _NTIFS_

typedef struct _TOKEN_SOURCE {
    CCHAR   SourceName[TOKEN_SOURCE_LENGTH];
    LUID    SourceIdentifier;
} TOKEN_SOURCE, *PTOKEN_SOURCE;

#endif // _NTIFS_

/* XP SP2 has same TOKEN_OBJECT structure as Windows Server 2003 (stucture K23 in union). */
#include <pshpack1.h>
typedef union
{
  struct
   {
    TOKEN_SOURCE TokenSource;     /* 0x0: CHAR SourceName[8] = "*SYSTEM*" | "User32  " + LUID SourceIdentifier = 0x10, *SYSTEM* id == 0 */
    LUID TokenId;         /* 0x10: */
    LUID AuthenticationId;    /* 0x18: */
    LARGE_INTEGER ExpirationTime; /* 0x20: -1 no expired. *SYSTEM* has expired? */
    LUID ModifiedId;          /* 0x28: */
    ULONG UserAndGroupCount;      /* 0x30: 3 */
    ULONG PrivilegeCount;     /* 0x34: 14 */
    ULONG VariableLength;     /* 0x38: 0x37C */
    ULONG DynamicCharged;     /* 0x3C: 0x1F4 */
    ULONG DynamicAvailable;   /* 0x40: 0x1A4 */
    ULONG DefaultOwnerIndex;      /* 0x44: 1 */
    PSID_AND_ATTRIBUTES UserAndGroups;/* 0x48: TOKEN_USER Owners [UserAndGroupCount] DefaultOwnerIndex */
    PSID  PrimaryGroup;       /* 0x4C: */
    PLUID_AND_ATTRIBUTES Privileges;/* 0x50: */
    PULONG DynamicPart;       /* 0x54: */
    PACL   DefaultDacl;       /* 0x58: */
    TOKEN_TYPE TokenType;     /* 0x5C: TokenPrimary | TokenImpersonation */
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;/* 0x60: 0 */
    UCHAR   TokenFlags;       /* 0x64: 1 */
    BOOLEAN TokenInUse;       /* 0x65: 1 */
    USHORT  Alignment;        /* 0x66: 0 */
    PVOID   ProxyData;        /* 0x68: 0 */
    PVOID   AuditData;        /* 0x6C: 0 */
    ULONG VariablePart;       /* 0x70: */
   } NT;
  struct
   {
    TOKEN_SOURCE TokenSource;     /* 0x0: CHAR SourceName[8] = "*SYSTEM*" | "User32  " + LUID SourceIdentifier = 0x10 */
    LUID TokenId;         /* 0x10: */
    LUID AuthenticationId;    /* 0x18: */
    LUID ParentTokenId;       /* 0x20: 0 */
    LARGE_INTEGER ExpirationTime; /* 0x28: -1 no expired */
    LUID ModifiedId;          /* 0x30: */
    ULONG SessionId;          /* 0x38: 0 */
    ULONG UserAndGroupCount;      /* 0x3C: 9 */
    ULONG RestrictedSidCount;     /*+0x40: 0 */
    ULONG PrivilegeCount;     /* 0x44: 11 */
    ULONG VariableLength;     /* 0x48: 0x1F0 */
    ULONG DynamicCharged;     /* 0x4C: 0x1F4 */
    ULONG DynamicAvailable;   /* 0x50: 0x1A4 */
    ULONG DefaultOwnerIndex;      /* 0x54: 3 */
    PSID_AND_ATTRIBUTES UserAndGroups; /* 0x58: TOKEN_USER Owners [UserAndGroupCount] DefaultOwnerIndex */
    PSID_AND_ATTRIBUTES RestrictedSids;/* 0x5C: 0 */
    PSID  PrimaryGroup;       /* 0x60: */
    PLUID_AND_ATTRIBUTES Privileges;/* 0x64: */
    PULONG DynamicPart;       /* 0x68: */
    PACL   DefaultDacl;       /* 0x6C: */
    TOKEN_TYPE TokenType;     /* 0x70: TokenPrimary | TokenImpersonation */
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;/* 0x74: 0 */
    UCHAR   TokenFlags;       /* 0x78: 9 */
    BOOLEAN TokenInUse;       /* 0x79: 1 */
    USHORT  Alignment;        /* 0x7A: 0 */
    PVOID   ProxyData;        /* 0x7C: 0 */
    PVOID   AuditData;        /* 0x80: 0 */
    ULONG VariablePart;           /* 0x84: */
   } K2;
  struct
   {
    TOKEN_SOURCE TokenSource;     /* 0x0: CHAR SourceName[8] = "*SYSTEM*" | "User32  " + LUID SourceIdentifier = 0x10 */
    LUID TokenId;         /* 0x10: 0x6F68 */
    LUID AuthenticationId;    /* 0x18: */
    LUID ParentTokenId;       /* 0x20: 0 */
    LARGE_INTEGER ExpirationTime; /* 0x28: -1 no expired */
    PERESOURCE TokenLock;     /*+0x30: 0x8xxxxxxxx */
    LUID ModifiedId;          /* 0x34: */
    ULONG SessionId;          /* 0x3C: 0x6F6A */
    ULONG UserAndGroupCount;      /* 0x40: 4 */
    ULONG RestrictedSidCount;     /*+0x44: 0 */
    ULONG VariableLength;     /* 0x48: 0x160 */
    ULONG DynamicCharged;     /* 0x4C: 0x164 */
    ULONG DynamicAvailable;   /* 0x50: 0x1F4 */
    ULONG PrivilegeCount;     /* 0x54: 0 */
    ULONG DefaultOwnerIndex;      /* 0x58: 1 */
    PSID_AND_ATTRIBUTES UserAndGroups; /* 0x5C: TOKEN_USER Owners [UserAndGroupCount] DefaultOwnerIndex */
    PSID_AND_ATTRIBUTES RestrictedSids;/* 0x60: 0 */
    PSID  PrimaryGroup;       /* 0x64: */
    PLUID_AND_ATTRIBUTES Privileges;/* 0x68: */
    PULONG DynamicPart;       /* 0x6C: */
    PACL   DefaultDacl;       /* 0x70: */
    TOKEN_TYPE TokenType;     /* 0x74: TokenPrimary | TokenImpersonation */
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;/* 0x78: 0 */
    UCHAR   TokenFlags;       /* 0x7C: 9 */
    BOOLEAN TokenInUse;       /* 0x7D: 1 */
    USHORT  Alignment;        /* 0x7E: 4BB4 */
    PVOID   ProxyData;        /* 0x80: 0 */
    PVOID   AuditData;        /* 0x84: 0 */
    ULONG VariablePart;       /* 0x88: */
   } XP;
  struct
   {
    TOKEN_SOURCE TokenSource;     /* 0x0: CHAR SourceName[8] = "*SYSTEM*" | "User32  " + LUID SourceIdentifier = 0x10 */
    LUID TokenId;         /* 0x10: 0x6F68 */
    LUID AuthenticationId;    /* 0x18: */
    LUID ParentTokenId;       /* 0x20: 0 */
    LARGE_INTEGER ExpirationTime; /* 0x28: -1 no expired */
    PERESOURCE TokenLock;     /*+0x30: 0x8xxxxxxxx */
    ULONG Padding64;          /*+0x34: 0xXxxxxxxxx */
    SEP_AUDIT_POLICY AuditPolicy; /*+0x38: */
    LUID ModifiedId;          /*+0x040: 0x6F6A */
    ULONG SessionId;          /*+0x048: */
    ULONG UserAndGroupCount;      /* 0x4C: 4 */
    ULONG RestrictedSidCount;     /*+0x50: 0 */
    ULONG VariableLength;     /* 0x54: 0x18 */
    ULONG DynamicCharged;     /* 0x58: 0x17C */
    ULONG DynamicAvailable;   /* 0x5C: 0x1F4 */
    ULONG PrivilegeCount;     /* 0x60: 0 */
    ULONG DefaultOwnerIndex;      /* 0x64: 1 */
    PSID_AND_ATTRIBUTES UserAndGroups; /* 0x68: TOKEN_USER Owners [UserAndGroupCount] DefaultOwnerIndex */
    PSID_AND_ATTRIBUTES RestrictedSids;/* 0x6C: 0 */
    PSID  PrimaryGroup;       /* 0x70: */
    PLUID_AND_ATTRIBUTES Privileges;/* 0x74: */
    PULONG DynamicPart;       /* 0x78: */
    PACL   DefaultDacl;       /* 0x7C: */
    TOKEN_TYPE TokenType;     /* 0x80: TokenPrimary | TokenImpersonation */
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;/* 0x84: 0 */
    UCHAR   TokenFlags;       /* 0x88: 9 */
    BOOLEAN TokenInUse;       /* 0x89: 1 */
    USHORT  Alignment;        /* 0x8A: 4BB4 */
    PVOID   ProxyData;        /* 0x8C: 0x8xxxxxxxx */
    PVOID   AuditData;        /* 0x90: 0 */
    ULONG VariablePart;       /* 0x94: */
   } K23;
  struct
   {
    TOKEN_SOURCE TokenSource;       /* +0x0: CHAR SourceName[8] = "*SYSTEM*" | "User32  " + LUID SourceIdentifier = 0x10 */
    LUID     TokenId;       /* +0x10: 0x6F68 */
    LUID     AuthenticationId;  /* +0x18: */
    LUID     ParentTokenId;     /* +0x20: 0 */
    LARGE_INTEGER ExpirationTime;   /* +0x28: -1 no expired */
    PERESOURCE   TokenLock;     /* +0x30: 0x8xxxxxxxx */
    ULONG    Padding64;     /* +0x34: 0xXxxxxxxxx */
    SEP_AUDIT_POLICY AuditPolicy;   /* +0x38: */
    LUID     ModifiedId;        /* +0x040: 0x6F6A */
    ULONG    SessionId;     /* +0x048: */
    ULONG    UserAndGroupCount; /* +0x04c: 4 */
    ULONG    RestrictedSidCount;    /* +0x050: 0 */
    ULONG    PrivilegeCount;    /* +0x054: 0x18 */
    ULONG    VariableLength;    /* +0x058: 0x17C */
    ULONG    DynamicCharged;    /* +0x05c: 0x1F4 */
    ULONG    DynamicAvailable;  /* +0x060: 0 */
    ULONG    DefaultOwnerIndex; /* +0x064: 1 */
    PSID_AND_ATTRIBUTES UserAndGroups;  /* +0x68: TOKEN_USER Owners [UserAndGroupCount] DefaultOwnerIndex */
    PSID_AND_ATTRIBUTES RestrictedSids; /* +0x6C: 0 */
    PSID     PrimaryGroup;      /* +0x70: */
    PLUID_AND_ATTRIBUTES Privileges;    /* +0x74: */
    PULONG   DynamicPart;       /* +0x78: */
    PACL     DefaultDacl;       /* +0x7C: */
    TOKEN_TYPE   TokenType;     /* +0x80: TokenPrimary | TokenImpersonation */
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;/* +0x84: 0 */
    UCHAR    TokenFlags;        /* +0x88: 9 */
    BOOLEAN  TokenInUse;        /* +0x89: 1 */
    USHORT   Alignment;     /* +0x8A: 4BB4 */
    PVOID    ProxyData;     /* +0x8C: 0x8xxxxxxxx */
    PVOID    AuditData;     /* +0x90: 0 */
    PVOID    LogonSession;      /* +0x94: */
    LUID     OriginatingLogonSession;/* +0x98: */
    ULONG    VariablePart;      /* +0xa0: */
   } K23SP1;
  struct
   {
    TOKEN_SOURCE TokenSource;       /* +0x000 */
    LUID     TokenId;       /* +0x010 */
    LUID     AuthenticationId;  /* +0x018 */
    LUID     ParentTokenId;     /* +0x020 */
    LARGE_INTEGER ExpirationTime;   /* +0x028 */
    PERESOURCE   TokenLock;     /* +0x030 */
    LUID     ModifiedId;        /* +0x034 */
    SEP_AUDIT_POLICY_VISTA AuditPolicy; /* +0x03c */
    ULONG    SessionId;     /* +0x058 */
    ULONG    UserAndGroupCount; /* +0x05c */
    ULONG    RestrictedSidCount;    /* +0x060 */
    ULONG    PrivilegeCount;    /* +0x064 */
    ULONG    VariableLength;    /* +0x068 */
    ULONG    DynamicCharged;    /* +0x06c */
    ULONG    DynamicAvailable;  /* +0x070 */
    ULONG    DefaultOwnerIndex; /* +0x074 */
    PSID_AND_ATTRIBUTES UserAndGroups;  /* +0x078 */
    PSID_AND_ATTRIBUTES RestrictedSids; /* +0x07c */
    PSID     PrimaryGroup;      /* +0x080 */
    PLUID_AND_ATTRIBUTES Privileges;    /* +0x084 */
    PULONG   DynamicPart;       /* +0x088 */
    PACL     DefaultDacl;       /* +0x08c */
    TOKEN_TYPE   TokenType;     /* +0x090 */
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;/* +0x094 */
    ULONG    TokenFlags;        /* +0x098 */
    BOOLEAN  TokenInUse;        /* +0x09c */
    BOOLEAN  WriterPresent;     /* +0x09d */
    USHORT   Alignment;     /* +0x09e */
    ULONG    IntegrityLevelIndex;   /* +0x0a0 */
    ULONG    DesktopIntegrityLevelIndex;/* +0x0a4 */
    ULONG    MandatoryPolicy;   /* +0x0a8 */
    PVOID    ProxyData;     /* +0x0ac */
    PVOID    AuditData;     /* +0x0b0 */
    PVOID    LogonSession;      /* +0x0b4 */
    LUID     OriginatingLogonSession;/* +0x0b8 */
    SID_AND_ATTRIBUTES_HASH SidHash;    /* +0x0c0 */
    SID_AND_ATTRIBUTES_HASH RestrictedSidHash;/* +0x148 */
    ULONG    VariablePart;      /* +0x1d0 */
   } VISTA;
  struct
   {
    TOKEN_SOURCE TokenSource;       /* +0x000 */
    LUID     TokenId;       /* +0x010 */
    LUID     AuthenticationId;  /* +0x018 */
    LUID     ParentTokenId;     /* +0x020 */
    LARGE_INTEGER ExpirationTime;   /* +0x028 */
    PERESOURCE   TokenLock;     /* +0x030 */
    SEP_AUDIT_POLICY AuditPolicy;   /* +0x038 */
    LUID     ModifiedId;        /* +0x040 */
    ULONG    SessionId;     /* +0x048 */
    ULONG    UserAndGroupCount; /* +0x04c */
    ULONG    RestrictedSidCount;    /* +0x050 */
    ULONG    PrivilegeCount;    /* +0x054 */
    ULONG    VariableLength;    /* +0x058 */
    ULONG    DynamicCharged;    /* +0x05c */
    ULONG    DynamicAvailable;  /* +0x060 */
    ULONG    DefaultOwnerIndex; /* +0x064 */
    PSID_AND_ATTRIBUTES UserAndGroups;  /* +0x068 */
    PSID_AND_ATTRIBUTES RestrictedSids; /* +0x070 */
    PSID     PrimaryGroup;      /* +0x078 */
    PLUID_AND_ATTRIBUTES Privileges;    /* +0x080 */
    PULONG   DynamicPart;       /* +0x088 */
    PACL     DefaultDacl;       /* +0x090 */
    TOKEN_TYPE   TokenType;     /* +0x098 */
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel; /* +0x09c */
    UCHAR    TokenFlags;        /* +0x0a0 */
    BOOLEAN  TokenInUse;        /* +0x0a1 */
    UCHAR    Padding64 [6];     /* +0x0a2 */
    PVOID    ProxyData;     /* +0x0a8 */
    PVOID    AuditData;     /* +0x0b0 */
    PVOID    LogonSession;      /* +0x0b8 */
    LUID     OriginatingLogonSession;/* +0x0c0 */
    ULONG    VariablePart;      /* +0x0c8 */
   } XP64; /* equial 2K3SP1x64 */
  /* VariablePart */
} TOKEN_OBJECT, *PTOKEN_OBJECT;
#include <poppack.h>

typedef struct _VACB {
    PVOID               BaseAddress;
    PSHARED_CACHE_MAP   SharedCacheMap;
    union {
        LARGE_INTEGER   FileOffset;
        USHORT          ActiveCount;
    } Overlay;
    LIST_ENTRY          LruList;
} VACB, *PVACB;

typedef struct _VAD_HEADER {
    PVOID       StartVPN;
    PVOID       EndVPN;
    PVAD_HEADER ParentLink;
    PVAD_HEADER LeftLink;
    PVAD_HEADER RightLink;
    ULONG       Flags;          // LSB = CommitCharge
    PVOID       ControlArea;
    PVOID       FirstProtoPte;
    PVOID       LastPTE;
    ULONG       Unknown;
    LIST_ENTRY  Secured;
} VAD_HEADER, *PVAD_HEADER;

typedef struct _X86BIOS_REGISTERS {
    ULONG   Eax;
    ULONG   Ecx;
    ULONG   Edx;
    ULONG   Ebx;
    ULONG   Ebp;
    ULONG   Esi;
    ULONG   Edi;
    USHORT  SegDs;
    USHORT  SegEs;
} X86BIOS_REGISTERS, *PX86BIOS_REGISTERS;

NTKERNELAPI
LARGE_INTEGER
CcGetLsnForFileObject (
    IN PFILE_OBJECT     FileObject,
    OUT PLARGE_INTEGER  OldestLsn OPTIONAL
);

NTKERNELAPI
INT
ExSystemExceptionFilter (
    VOID
);

NTKERNELAPI
PVOID
FsRtlAllocatePool (
    IN POOL_TYPE    PoolType,
    IN ULONG        NumberOfBytes
);

NTKERNELAPI
PVOID
FsRtlAllocatePoolWithQuota (
    IN POOL_TYPE    PoolType,
    IN ULONG        NumberOfBytes
);

#ifdef FsRtlAllocatePoolWithQuotaTag
#undef FsRtlAllocatePoolWithQuotaTag
#endif

NTKERNELAPI
PVOID
FsRtlAllocatePoolWithQuotaTag (
    IN POOL_TYPE    PoolType,
    IN ULONG        NumberOfBytes,
    IN ULONG        Tag
);

#ifdef FsRtlAllocatePoolWithTag
#undef FsRtlAllocatePoolWithTag
#endif

NTKERNELAPI
PVOID
FsRtlAllocatePoolWithTag (
    IN POOL_TYPE    PoolType,
    IN ULONG        NumberOfBytes,
    IN ULONG        Tag
);

NTKERNELAPI
VOID
FsRtlNotifyChangeDirectory (
    IN PNOTIFY_SYNC NotifySync,
    IN PVOID        FsContext,
    IN PSTRING      FullDirectoryName,
    IN PLIST_ENTRY  NotifyList,
    IN BOOLEAN      WatchTree,
    IN ULONG        CompletionFilter,
    IN PIRP         NotifyIrp
);

NTKERNELAPI
VOID
FsRtlNotifyReportChange (
    IN PNOTIFY_SYNC NotifySync,
    IN PLIST_ENTRY  NotifyList,
    IN PSTRING      FullTargetName,
    IN PSTRING      TargetName,
    IN ULONG        FilterMatch
);

NTSYSAPI
NTSTATUS
NTAPI
HalAdjustResourceList (
    IN OUT PIO_RESOURCE_REQUIREMENTS_LIST *pResourceList
);

NTSYSAPI
BOOLEAN
NTAPI
HalAllProcessorsStarted (
    VOID
);

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
KIRQL
NTAPI
HalConvertDeviceIdtToIrql (
    IN ULONG Vector
);

NTSYSAPI
NTSTATUS
NTAPI
HalDisableInterrupt (
    IN ULONG Unknown
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

//
// If using HalDisplayString during boot on Windows 2000 or later
// you must first call InbvEnableDisplayString.
//
NTSYSAPI
VOID
NTAPI
HalDisplayString (
    IN PUCHAR String
);

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
HalEnableInterrupt (
    IN ULONG Unknown
);

NTSYSAPI
ULONG
NTAPI
HalQueryMaximumProcessorCount (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
BOOLEAN
NTAPI
HalQueryRealTimeClock (
    OUT PTIME_FIELDS TimeFields
);

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
HalRegisterErrataCallbacks (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
BOOLEAN
NTAPI
HalSetRealTimeClock (
    IN PTIME_FIELDS TimeFields
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTKERNELAPI
VOID
InbvAcquireDisplayOwnership (
    VOID
);

NTKERNELAPI
BOOLEAN
InbvCheckDisplayOwnership (
    VOID
);

NTKERNELAPI
BOOLEAN
InbvDisplayString (
    IN PUCHAR String
);

NTKERNELAPI
VOID
InbvEnableBootDriver (
    IN BOOLEAN Enable
);

NTKERNELAPI
BOOLEAN
InbvEnableDisplayString (
    IN BOOLEAN Enable
);

typedef
VOID
(*INBV_DISPLAY_STRING_FILTER) (
    PUCHAR *String
);

NTKERNELAPI
VOID
InbvInstallDisplayStringFilter (
    IN INBV_DISPLAY_STRING_FILTER DisplayStringFilter
);

NTKERNELAPI
BOOLEAN
InbvIsBootDriverInstalled (
    VOID
);

typedef
BOOLEAN
(*INBV_RESET_DISPLAY_PARAMETERS) (
    ULONG Cols,
    ULONG Rows
);

NTKERNELAPI
VOID
InbvNotifyDisplayOwnershipLost (
    IN INBV_RESET_DISPLAY_PARAMETERS ResetDisplayParameters
);

NTKERNELAPI
BOOLEAN
InbvResetDisplay (
    VOID
);

NTKERNELAPI
VOID
InbvSetScrollRegion (
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Width,
    IN ULONG Height
);

NTKERNELAPI
ULONG
InbvSetTextColor (
    IN ULONG Color
);

NTKERNELAPI
VOID
InbvSolidColorFill (
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Width,
    IN ULONG Height,
    IN ULONG Color
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTKERNELAPI
BOOLEAN
KdPollBreakIn (
    VOID
);

NTKERNELAPI
VOID
KeEnterKernelDebugger (
    VOID
);

NTKERNELAPI
KPROCESSOR_MODE
KeGetPreviousMode (
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WIN7)

NTKERNELAPI
ULONG
KeGetXSaveFeatureFlags (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_WIN7)

NTKERNELAPI
VOID
KeInitializeApc (
    IN PKAPC                Apc,
    IN PKTHREAD             Thread,
    IN KAPC_ENVIRONMENT     Environment,
    IN PKKERNEL_ROUTINE     KernelRoutine,
    IN PKRUNDOWN_ROUTINE    RundownRoutine OPTIONAL,
    IN PKNORMAL_ROUTINE     NormalRoutine OPTIONAL,
    IN KPROCESSOR_MODE      ProcessorMode OPTIONAL,
    IN PVOID                NormalContext OPTIONAL
);

NTKERNELAPI
BOOLEAN
KeInsertQueueApc (
    IN PKAPC        Apc,
    IN PVOID        SystemArgument1,
    IN PVOID        SystemArgument2,
    IN KPRIORITY    Increment
);

#if (NTDDI_VERSION >= NTDDI_WINXP)

NTKERNELAPI
BOOLEAN
KeIsAttachedProcess (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

NTKERNELAPI
BOOLEAN
KeIsExecutingDpc (
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WIN7)

NTKERNELAPI
NTSTATUS
KePollFreezeExecution (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_WIN7)

NTKERNELAPI
NTSTATUS
KeUpdateSystemTime (
    VOID
);

NTKERNELAPI
VOID
KiCoprocessorError (
    VOID
);

NTKERNELAPI
VOID
KiDispatchInterrupt (
    VOID
);

NTKERNELAPI
NTSTATUS
MmCreateSection (
    OUT PVOID               *SectionObject,
    IN ACCESS_MASK          DesiredAccess,
    IN POBJECT_ATTRIBUTES   ObjectAttributes OPTIONAL,
    IN PLARGE_INTEGER       MaximumSize,
    IN ULONG                SectionPageProtection,
    IN ULONG                AllocationAttributes,
    IN HANDLE               FileHandle OPTIONAL,
    IN PFILE_OBJECT         FileObject OPTIONAL
);

NTKERNELAPI
NTSTATUS
MmMapViewOfSection (
    IN PVOID                SectionObject,
    IN PEPROCESS            Process,
    IN OUT PVOID            *BaseAddress,
    IN ULONG_PTR            ZeroBits,
    IN ULONG                CommitSize,
    IN OUT PLARGE_INTEGER   SectionOffset,
    IN OUT PULONG           ViewSize,
    IN SECTION_INHERIT      InheritDisposition,
    IN ULONG                AllocationType,
    IN ULONG                Protect
);

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
NtThawTransactions (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

NTKERNELAPI
NTSTATUS
ObCreateObject (
    IN KPROCESSOR_MODE      ProbeMode,
    IN POBJECT_TYPE         ObjectType,
    IN POBJECT_ATTRIBUTES   ObjectAttributes OPTIONAL,
    IN KPROCESSOR_MODE      OwnershipMode,
    IN OUT PVOID            ParseContext OPTIONAL,
    IN ULONG                ObjectBodySize,
    IN ULONG                PagedPoolCharge,
    IN ULONG                NonPagedPoolCharge,
    OUT PVOID               *Object
);

#if (NTDDI_VERSION >= NTDDI_WINXP)

NTKERNELAPI
VOID
ObDereferenceSecurityDescriptor (
    IN PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN ULONG                Count
);

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

#if (NTDDI_VERSION <= NTDDI_WIN2K)

NTKERNELAPI
ULONG
ObGetObjectPointerCount (
    IN PVOID Object
);

#endif // (NTDDI_VERSION <= NTDDI_WIN2K)

#if (NTDDI_VERSION >= NTDDI_WINXP)

NTKERNELAPI
NTSTATUS
ObLogSecurityDescriptor (
    IN PSECURITY_DESCRIPTOR     InputSecurityDescriptor,
    OUT PSECURITY_DESCRIPTOR    *OutputSecurityDescriptor,
    IN ULONG                    RefBias
);

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

NTKERNELAPI
NTSTATUS
ObReferenceObjectByName (
    IN PUNICODE_STRING  ObjectName,
    IN ULONG            Attributes,
    IN PACCESS_STATE    PassedAccessState OPTIONAL,
    IN ACCESS_MASK      DesiredAccess OPTIONAL,
    IN POBJECT_TYPE     ObjectType,
    IN KPROCESSOR_MODE  AccessMode,
    IN OUT PVOID        ParseContext OPTIONAL,
    OUT PVOID           *Object
);

#if (NTDDI_VERSION >= NTDDI_WINXP)

NTKERNELAPI
VOID
ObReferenceSecurityDescriptor (
    IN PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN ULONG                Count
);

#endif // (NTDDI_VERSION >= NTDDI_XP)

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTKERNELAPI
NTSTATUS
PoUserShutdownInitiated (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_XP)

NTKERNELAPI
NTSTATUS
PsChargeProcessNonPagedPoolQuota (
    IN PEPROCESS Process,
    IN ULONG_PTR Amount
);

NTKERNELAPI
NTSTATUS
PsChargeProcessPagedPoolQuota (
    IN PEPROCESS Process,
    IN ULONG_PTR Amount
);

#endif // (NTDDI_VERSION >= NTDDI_XP)

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTKERNELAPI
NTSTATUS
PsEnterPriorityRegion (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

NTKERNELAPI
ULONG
PsGetCurrentProcessSessionId (
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WS03)

NTKERNELAPI
PVOID
PsGetCurrentProcessWin32Process (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_WS03)

NTKERNELAPI
KPROCESSOR_MODE
PsGetCurrentThreadPreviousMode (
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WS03)

NTKERNELAPI
PEPROCESS
PsGetCurrentThreadProcess (
    VOID
);

NTKERNELAPI
ULONG
PsGetCurrentThreadProcessId (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_WS03)

NTKERNELAPI
PVOID
PsGetCurrentThreadStackBase (
    VOID
);

NTKERNELAPI
PVOID
PsGetCurrentThreadStackLimit (
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WS03)

NTKERNELAPI
PTEB
PsGetCurrentThreadTeb (
    VOID
);

NTKERNELAPI
PVOID
PsGetCurrentThreadWin32Thread (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_WS03)

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTKERNELAPI
NTSTATUS
PsLeavePriorityRegion (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

NTKERNELAPI
NTSTATUS
PsLookupProcessThreadByCid (
    IN PCLIENT_ID   Cid,
    OUT PEPROCESS   *Process OPTIONAL,
    OUT PETHREAD    *Thread
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
ULONG
NTAPI
RtlGetNtGlobalFlags (
    VOID
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
PIMAGE_NT_HEADERS
NTAPI
RtlImageNtHeader (
    IN PVOID BaseAddress
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetSaclSecurityDescriptor (
    IN OUT PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN BOOLEAN                  SaclPresent,
    IN PACL                     Sacl OPTIONAL,
    IN BOOLEAN                  SaclDefaulted OPTIONAL
);

NTKERNELAPI
NTSTATUS
SeCreateAccessState (
    OUT PACCESS_STATE   AccessState,
    IN PAUX_ACCESS_DATA AuxData,
    IN ACCESS_MASK      AccessMask,
    IN PGENERIC_MAPPING GenericMapping
);

NTKERNELAPI
VOID
SeDeleteAccessState (
    IN PACCESS_STATE AccessState
);

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
TmThawTransactions (
    VOID
);

NTSYSAPI
NTSTATUS
NTAPI
TmInitSystemPhase2 (
    VOID
);

NTSYSAPI
NTSTATUS
NTAPI
TmInitSystem (
    VOID
);

NTSYSAPI
NTSTATUS
NTAPI
x86BiosAllocateBuffer (
    ULONG   *Size,
    USHORT  *Segment,
    USHORT  *Offset
);

NTSYSAPI
BOOLEAN
NTAPI
x86BiosCall (
    ULONG               InterruptNumber,
    X86BIOS_REGISTERS   *Registers
);

NTSYSAPI
NTSTATUS
NTAPI
x86BiosFreeBuffer (
    USHORT  Segment,
    USHORT  Offset
);

NTSYSAPI
NTSTATUS
NTAPI
x86BiosReadMemory (
    USHORT  Segment,
    USHORT  Offset,
    PVOID   Buffer,
    ULONG   Size
);

NTSYSAPI
NTSTATUS
NTAPI
x86BiosWriteMemory (
    USHORT  Segment,
    USHORT  Offset,
    PVOID   Buffer,
    ULONG   Size
);

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwAdjustPrivilegesToken (
    IN HANDLE                   TokenHandle,
    IN BOOLEAN                  DisableAllPrivileges,
    IN PTOKEN_PRIVILEGES        NewState OPTIONAL,
    IN ULONG                    BufferLength OPTIONAL,
    OUT PTOKEN_PRIVILEGES       PreviousState OPTIONAL,
    OUT PULONG                  ReturnLength
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwAlertThread (
    IN HANDLE ThreadHandle
);

NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheckAndAuditAlarm (
    IN PUNICODE_STRING      SubsystemName,
    IN PVOID                HandleId,
    IN PUNICODE_STRING      ObjectTypeName,
    IN PUNICODE_STRING      ObjectName,
    IN PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN ACCESS_MASK          DesiredAccess,
    IN PGENERIC_MAPPING     GenericMapping,
    IN BOOLEAN              ObjectCreation,
    OUT PACCESS_MASK        GrantedAccess,
    OUT PNTSTATUS           AccessStatus,
    OUT PBOOLEAN            GenerateOnClose
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwCancelIoFile (
    IN HANDLE               FileHandle,
    OUT PIO_STATUS_BLOCK    IoStatusBlock
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwClearEvent (
    IN HANDLE EventHandle
);

NTSYSAPI
NTSTATUS
NTAPI
ZwConnectPort (
    OUT PHANDLE                     ClientPortHandle,
    IN PUNICODE_STRING              ServerPortName,
    IN PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    IN OUT PLPC_SECTION_WRITE       ClientSharedMemory OPTIONAL,
    IN OUT PLPC_SECTION_READ        ServerSharedMemory OPTIONAL,
    OUT PULONG                      MaximumMessageLength OPTIONAL,
    IN OUT PVOID                    ConnectionInformation OPTIONAL,
    IN OUT PULONG                   ConnectionInformationLength OPTIONAL
);

NTSYSAPI
NTSTATUS
NTAPI
ZwCloseObjectAuditAlarm (
    IN PUNICODE_STRING  SubsystemName,
    IN PVOID            HandleId,
    IN BOOLEAN          GenerateOnClose
);

NTSYSAPI
NTSTATUS
NTAPI
ZwCreateSymbolicLinkObject (
    OUT PHANDLE             SymbolicLinkHandle,
    IN ACCESS_MASK          DesiredAccess,
    IN POBJECT_ATTRIBUTES   ObjectAttributes,
    IN PUNICODE_STRING      TargetName
);

NTSYSAPI
NTSTATUS
NTAPI
ZwFlushInstructionCache (
    IN HANDLE   ProcessHandle,
    IN PVOID    BaseAddress OPTIONAL,
    IN ULONG    FlushSize
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwInitiatePowerAction (
    IN POWER_ACTION         SystemAction,
    IN SYSTEM_POWER_STATE   MinSystemState,
    IN ULONG                Flags,
    IN BOOLEAN              Asynchronous
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwLoadKey (
    IN POBJECT_ATTRIBUTES KeyObjectAttributes,
    IN POBJECT_ATTRIBUTES FileObjectAttributes
);

NTSYSAPI
NTSTATUS
NTAPI
ZwOpenProcessToken (
    IN HANDLE       ProcessHandle,
    IN ACCESS_MASK  DesiredAccess,
    OUT PHANDLE     TokenHandle
);

NTSYSAPI
NTSTATUS
NTAPI
ZwOpenThread (
    OUT PHANDLE             ThreadHandle,
    IN ACCESS_MASK          DesiredAccess,
    IN POBJECT_ATTRIBUTES   ObjectAttributes,
    IN PCLIENT_ID           ClientId OPTIONAL
);

NTSYSAPI
NTSTATUS
NTAPI
ZwOpenThreadToken (
    IN HANDLE       ThreadHandle,
    IN ACCESS_MASK  DesiredAccess,
    IN BOOLEAN      OpenAsSelf,
    OUT PHANDLE     TokenHandle
);

NTSYSAPI
NTSTATUS
NTAPI
ZwPulseEvent (
    IN HANDLE   EventHandle,
    OUT PULONG  PreviousState OPTIONAL
);

NTSYSAPI
NTSTATUS
NTAPI
ZwQueryDefaultLocale (
    IN BOOLEAN  ThreadOrSystem,
    OUT PLCID   Locale
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwQueryDefaultUILanguage (
    OUT LANGID *LanguageId
);

NTSYSAPI
NTSTATUS
NTAPI
ZwQueryDirectoryObject (
    IN HANDLE       DirectoryHandle,
    OUT PVOID       Buffer,
    IN ULONG        Length,
    IN BOOLEAN      ReturnSingleEntry,
    IN BOOLEAN      RestartScan,
    IN OUT PULONG   Context,
    OUT PULONG      ReturnLength OPTIONAL
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInformationProcess (
    IN HANDLE           ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID           ProcessInformation,
    IN ULONG            ProcessInformationLength,
    OUT PULONG          ReturnLength OPTIONAL
);

#if (NTDDI_VERSION >= NTDDI_WINXP)

NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInformationThread (
    IN HANDLE           ThreadHandle,
    IN THREADINFOCLASS  ThreadInformationClass,
    OUT PVOID           ThreadInformation,
    IN ULONG            ThreadInformationLength,
    OUT PULONG          ReturnLength OPTIONAL
);

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInstallUILanguage (
    OUT LANGID *LanguageId
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySection (
    IN HANDLE                       SectionHandle,
    IN SECTION_INFORMATION_CLASS    SectionInformationClass,
    OUT PVOID                       SectionInformation,
    IN ULONG                        SectionInformationLength,
    OUT PULONG                      ReturnLength OPTIONAL
);

NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySystemInformation (
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID                   SystemInformation,
    IN ULONG                    SystemInformationLength,
    OUT PULONG                  ReturnLength OPTIONAL
);

NTSYSAPI
NTSTATUS
NTAPI
ZwReplaceKey (
    IN POBJECT_ATTRIBUTES   NewFileObjectAttributes,
    IN HANDLE               KeyHandle,
    IN POBJECT_ATTRIBUTES   OldFileObjectAttributes
);

NTSYSAPI
NTSTATUS
NTAPI
ZwRequestWaitReplyPort (
    IN HANDLE           PortHandle,
    IN PLPC_MESSAGE     Request,
    OUT PLPC_MESSAGE    Reply
);

NTSYSAPI
NTSTATUS
NTAPI
ZwResetEvent (
    IN HANDLE   EventHandle,
    OUT PLONG   PreviousState OPTIONAL
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwRestoreKey (
    IN HANDLE   KeyHandle,
    IN HANDLE   FileHandle,
    IN ULONG    Flags
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwSaveKey (
    IN HANDLE KeyHandle,
    IN HANDLE FileHandle
);

NTSYSAPI
NTSTATUS
NTAPI
ZwSetDefaultLocale (
    IN BOOLEAN  ThreadOrSystem,
    IN LCID     Locale
);

#if (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwSetDefaultUILanguage (
    IN LANGID LanguageId
);

#endif // (NTDDI_VERSION >= NTDDI_WIN2K)

NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationObject (
    IN HANDLE               ObjectHandle,
    IN OBJECT_INFO_CLASS    ObjectInformationClass,
    IN PVOID                ObjectInformation,
    IN ULONG                ObjectInformationLength
);

NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationProcess (
    IN HANDLE           ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    IN PVOID            ProcessInformation,
    IN ULONG            ProcessInformationLength
);

NTSYSAPI
NTSTATUS
NTAPI
ZwSetSystemInformation (
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    IN PVOID                    SystemInformation,
    IN ULONG                    SystemInformationLength
);

NTSYSAPI
NTSTATUS
NTAPI
ZwSetSystemTime (
    IN PLARGE_INTEGER   NewTime,
    OUT PLARGE_INTEGER  OldTime OPTIONAL
);

NTSYSAPI
NTSTATUS
NTAPI
ZwUnloadKey (
    IN POBJECT_ATTRIBUTES KeyObjectAttributes
);

NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForMultipleObjects (
    IN ULONG            HandleCount,
    IN HANDLE           Handles[],
    IN WAIT_TYPE        WaitType,
    IN BOOLEAN          Alertable,
    IN PLARGE_INTEGER   Timeout OPTIONAL
);

NTSYSAPI
NTSTATUS
NTAPI
ZwYieldExecution (
    VOID
);

#ifdef __cplusplus
}
#endif

#endif // _GNU_WDK_UNDOC_

#endif // _GNU_NTIFS_
