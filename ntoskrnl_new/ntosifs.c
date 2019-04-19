
#ifndef _NTOSIFS_
#define _NTOSIFS_

#ifdef __cplusplus
extern "C" {   // extern "C"
#endif

typedef ULONG ECP_HEADER_FLAGS;

#define ECP_FLAG_PROVIDED_BY_CREATE_CALLER      0x00000001
#define ECP_FLAG_ALLOCATED_BY_FSRTL             0x00000002
#define ECP_FLAG_ACCESSED                       0x00000004
#define ECP_FLAG_ACKNOWLEDGED                   0x00000008
#define ECP_FLAG_PASSED_FROM_USER_MODE          0x0000010
#define ECP_FLAG_FLTMGR                         0x00000020
#define ECP_FLAG_NONPAGED                       0x00000040
#define ECP_FLAG_ALL                            (ECP_FLAG_PROVIDED_BY_CREATE_CALLER \
                                                 | ECP_FLAG_ALLOCATED_BY_FSRTL \
                                                 | ECP_FLAG_ACCESSED \
                                                 | ECP_FLAG_ACKNOWLEDGED \
                                               /*| ECP_FLAG_PASSED_FROM_USER_MODE*/ \
                                                 | ECP_FLAG_FLTMGR \
                                                 | ECP_FLAG_NONPAGED)

typedef struct _ECP_LIST
{
    ULONG Signature;
    ULONG Flags;
    LIST_ENTRY EcpList;
} ECP_LIST, *PECP_LIST;

typedef struct _ECP_HEADER
{
    ULONG Signature;
    ULONG Spare;
    LIST_ENTRY ListEntry;
    GUID EcpType;
    PFSRTL_EXTRA_CREATE_PARAMETER_CLEANUP_CALLBACK CleanupCallback;
    ECP_HEADER_FLAGS Flags;
    ULONG Size;
    PVOID ListAllocatedFrom;
    PVOID Filter;
} ECP_HEADER, *PECP_HEADER;

#define FSRTL_ECP_HEADER_SIGNATURE  ((ULONG)('HpcE'))

#define ASSERT_ECP_HEADER(_ecpHdr) \
    NT_ASSERTMSG("Invalid ECP_HEADER structure: ", (_ecpHdr)->Signature == FSRTL_ECP_HEADER_SIGNATURE);

#define ECP_HEADER_SIZE  (sizeof(ECP_HEADER))

#define ECP_HEADER_TO_CONTEXT( hdr ) ((PVOID)((PCHAR)hdr + ECP_HEADER_SIZE))
#define ECP_CONTEXT_TO_HEADER( ctx ) ((PECP_HEADER)((PCHAR)ctx - ECP_HEADER_SIZE))

#define TIERING_HEAT_FLAG_MEASURE_READ      0x00000001
#define TIERING_HEAT_FLAG_MEASURE_WRITE     0x00000002
#define TIERING_HEAT_FLAG_MEASURE_DELETE    0x00000004
#define TIERING_HEAT_FLAG_MEASURE_MASK      0x00000007
#define FSRTL_APP_TERMINATE_DATA_SIZE  4096
#define FSRTL_NOTIFY_FLAG_WATCH_TREE    (0x00000001)
#define FSRTL_NOTIFY_FLAG_IGNORE_BUFFER (0x00000002)
#define FSRTL_NOTIFY_REPORT_FLAG_IS_PARENT   (0x00000001)

#define DO_HIGH_PRIORITY_FILESYSTEM         0x00000200
#define FO_KEEPALIVE_COUNTS_ACTIVE      FO_SECTION_MINSTORE_TREATMENT
#define IRP_BACKPOCKET_POSSIBLE         0x20
#define IRP_BACKPOCKET_IRP              (IRP_BACKPOCKET_POSSIBLE | IRP_QUOTA_CHARGED)

#define IoIsMustSucceedIrp(Irp) (Irp->AllocationFlags & IRP_BACKPOCKET_POSSIBLE)

#define IO_IRPEXT_PROPAGATE_GENERIC         0x00000001
#define IO_IRPEXT_PROPAGATE_ACTIVITY_ID     0x00000002
#define IO_IRPEXT_PROPAGATE_TRACKED_OFFSET  0x00000004

#define IO_IRPEXT_PROPAGATE_ALL             0xffffffff

typedef
NTSTATUS
(*PIO_QOS_CREATE_FLOW_ROUTINE) (
    _In_ LPGUID FlowId
    );

typedef
NTSTATUS
(*PIO_QOS_SET_FLOW_POLICY_ROUTINE) (
    _In_ LPGUID FlowId,
    _In_opt_ PUNICODE_STRING VolumeName,
    _In_ LONG64 MaximumIops,
    _In_ LONG64 MaximumBandwidth,
    _In_ LONG64 ReservationIops
    );

typedef
NTSTATUS
(*PIO_QOS_SET_HANDLE_FLOW_ROUTINE) (
    _In_ PFILE_OBJECT FileObject,
    _In_ LPGUID FlowId,
    _In_ BOOLEAN ChargeOnly,
    _In_ KWAIT_REASON WaitReason
    );

typedef
NTSTATUS
(*PIO_QOS_DELETE_FLOW_ROUTINE) (
    _In_ LPGUID FlowId
    );

typedef
NTSTATUS
(*PIO_QOS_QUERY_FLOW_HISTORY_ROUTINE) (
    _In_ LPGUID FlowId,
    _Out_ PULONG64 OverQuotaHistory,
    _Out_ PULONG GenerationLength,
    _Out_ PULONG GenerationsPassed
    );

typedef
NTSTATUS
(*PIO_QOS_QUERY_FLOW_INFORMATION_ROUTINE) (
    _In_ LPGUID FlowId,
    _Inout_ PVOID Buffer,
    _In_ ULONG BufferLength,
    _Out_ PULONG CallerActualLength,
    _In_ PRKPROCESS Process,
    _In_ KPROCESSOR_MODE PreviousMode
    );

typedef struct _IO_QOS_ROUTINE_TABLE
{
    PIO_QOS_CREATE_FLOW_ROUTINE CreateFlow;
    PIO_QOS_SET_FLOW_POLICY_ROUTINE SetFlowPolicy;
    PIO_QOS_SET_HANDLE_FLOW_ROUTINE SetHandleFlow;
    PIO_QOS_DELETE_FLOW_ROUTINE DeleteFlow;
    PIO_QOS_QUERY_FLOW_HISTORY_ROUTINE QueryFlowHistory;
    PIO_QOS_QUERY_FLOW_INFORMATION_ROUTINE QueryFlowInformation;
} IO_QOS_ROUTINE_TABLE, *PIO_QOS_ROUTINE_TABLE;


typedef struct _JOBOBJECT_IO_RATE_CONTROL_INFORMATION {
    LONG64 MaxIops;
    LONG64 MaxBandwidth;
    LONG64 ReservationIops;
    PWSTR VolumeName;
    ULONG ControlFlags;
    USHORT VolumeNameLength;
} JOBOBJECT_IO_RATE_CONTROL_INFORMATION, *PJOBOBJECT_IO_RATE_CONTROL_INFORMATION;

#define JOB_OBJECT_IO_RATE_CONTROL_ENABLE 0x1
#define RTL_IMAGE_NT_HEADER_EX_FLAG_NO_RANGE_CHECK      (0x00000001)
#define RTL_IMAGE_NT_HEADER_EX_FLAG_ALLOW_EXCEPTIONS    (0x00000002)

#if !defined(MIDL_PASS) && !defined(_MANAGED)

FORCEINLINE
ULONG64
RtlAtomicRead64 (
    _In_ LONG64 volatile *Target
    )
{
#ifdef _WIN64
    return ReadNoFence64(Target);
#else
    return InterlockedCompareExchangeNoFence64(Target, 0, 0);
#endif
}

FORCEINLINE
VOID
RtlAtomicWrite64 (
    _Inout_ LONG64 volatile *Target,
    _In_ LONGLONG Value)
{
#ifdef _WIN64
    WriteNoFence64(Target, Value);
#else
    LONGLONG OldValue;
    LONGLONG Compare;

    Compare = ReadNoFence64(Target);
    for (;;)
    {
        OldValue = InterlockedCompareExchangeNoFence64(Target, Value, Compare);
        if (OldValue == Compare)
        {
            break;
        }

        Compare = OldValue;
    }
#endif
}

#endif  // !defined(MIDL_PASS) && !defined(_MANAGED)

#define FSCTL_SET_BREAK_ON_STATUS           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 183, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CBAFILT_IGNORE_ADS_CHANGES    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 184, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_MPFILTER_QUERY_FILE_CHANGE    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 186, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_USN_SUBMIT_MODIFIED_RANGES    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 190, METHOD_BUFFERED, FILE_ANY_ACCESS) // RANGETRACK_TRANSFER_PACKET
#define FSCTL_START_OVERLAY_INTEGRITY           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 200, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_STOP_OVERLAY_INTEGRITY            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 201, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_CONTROL_OVERLAY_INTEGRITY         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 202, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_QUERY_OVERLAY_INTEGRITY           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 203, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_SHUFFLE_FILE                      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 208, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS) // SHUFFLE_FILE_DATA
#define FSCTL_CHECK_FOR_SECTION                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 210, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CLOUD_DATA_TRANSFER               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 213, METHOD_IN_DIRECT, FILE_SPECIAL_ACCESS)
#define FSCTL_CLOUD_COMMAND                     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 214, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#define MAX_IMAGE_FILE_NAME_LEN 15  // to match EPROCESS.ImageFileName

typedef struct BREAK_ON_STATUS_BUFFER
{
    NTSTATUS NtStatus;
    ULONG Win32Error;
    ULONG ThreadId;
    ULONG ProcessId;
    CHAR ImageFileName[MAX_IMAGE_FILE_NAME_LEN + 1];  // ANSI, case insensitive
} BREAK_ON_STATUS_BUFFER, *PBREAK_ON_STATUS_BUFFER;

typedef struct _WIM_PROVIDER_CONTROL_INTEGRITY
{
    ULONG ControlCode;
} WIM_PROVIDER_CONTROL_INTEGRITY, *PWIM_PROVIDER_CONTROL_INTEGRITY;

#define WIM_PROVIDER_INTEGRITY_CONTROLCODE_SNAPSHOT                 (0)
#define WIM_PROVIDER_INTEGRITY_CONTROLCODE_REVERT_SNAPSHOT          (1)
#define WIM_PROVIDER_INTEGRITY_CONTROLCODE_POWER_HIBERNATE          (2)
#define WIM_PROVIDER_INTEGRITY_CONTROLCODE_POWER_RESUME             (3)
#define WIM_PROVIDER_INTEGRITY_CONTROLCODE_BACKGROUND_VALIDATION    (4)

typedef struct _WIM_PROVIDER_INTEGRITY_STATUS
{
    BOOLEAN IntegrityComplete;
    BOOLEAN IntegrityRunning;
    ULONGLONG IntegrityAvailable;
    ULONGLONG IntegrityRequired;
} WIM_PROVIDER_INTEGRITY_STATUS, *PWIM_PROVIDER_INTEGRITY_STATUS;

typedef struct _WIM_PROVIDER_START_INTEGRITY
{
    LARGE_INTEGER DataSourceId;
} WIM_PROVIDER_START_INTEGRITY, *PWIM_PROVIDER_START_INTEGRITY;

#define CLOUD_PROVIDER_CURRENT_VERSION      (0x00000001)
#define CPEI_FLAG_CONVERT_TO_PLACEHOLDER    (0x00000001)
#define CPEI_FLAG_VALID_FLAGS               (0x00000001)

typedef struct _CLOUD_PROVIDER_EXTERNAL_INFO
{
    ULONG Version;
    ULONG Flags;
    LARGE_INTEGER ServerFileSize;
    GUID SyncServiceId;
    ULONG ServiceDataOffset;
    ULONG ServiceDataSize;
} CLOUD_PROVIDER_EXTERNAL_INFO, *PCLOUD_PROVIDER_EXTERNAL_INFO;

#define CLOUD_DATA_TRANSFER_FLAG_NO_RECALL          (0x00000001)

typedef struct _CLOUD_DATA_TRANSFER
{
    LARGE_INTEGER RequiredOffset;
    LARGE_INTEGER ByteOffset;
    ULONG RequiredLength;
    ULONG Length;
    ULONG Flags;
    NTSTATUS ServiceStatus;
} CLOUD_DATA_TRANSFER, *PCLOUD_DATA_TRANSFER;

#define CLOUD_COMMAND_CURRENT_VERSION       (0x00000001)

#define CLOUD_COMMAND_INITIATE_RECALL       (0)
#define CLOUD_COMMAND_DEFLATE               (1)
#define CLOUD_COMMAND_INVALIDATE_VERSION    (2)
#define CLOUD_COMMAND_GET_SERVICE_DATA      (3)
#define CLOUD_COMMAND_SET_SERVICE_DATA      (4)
#define CLOUD_COMMAND_SET_SYNC_SCOPE        (5)

typedef struct _CLOUD_COMMAND
{
    ULONG Version;
    ULONG CommandCode;

    union {

        struct {
            LARGE_INTEGER RecallOffset;
            ULONG RecallLength;
        } InitiateRecall;

        struct {
            LARGE_INTEGER DeflateOffset;
            ULONG DeflateLength;
        } Deflate;

        struct {
            LARGE_INTEGER NewServerFileSize;
            ULONG ServiceDataOffset;
            ULONG ServiceDataSize;
        } InvalidateVersion;

        struct {
            ULONG ServiceDataOffset;
            ULONG ServiceDataSize;
        } ServiceData;

        struct {
            GUID SyncServiceId;
            BOOLEAN SetScope;
        } SetSyncScope;

    } DUMMYUNIONNAME;
} CLOUD_COMMAND, *PCLOUD_COMMAND;

#define CLOUDPROV_PORT_NAME L"\\CloudFileFilterPort"
#define CLOUDPROV_SERVICE_PREFIX L"\\CloudServicePort"

#define CLOUD_PROVIDER_MESSAGE_CURRENT_VERSION      (0x00000001)
#define CLOUD_PROVIDER_MESSAGE_CODE_FILE_OPEN               (1)
#define CLOUD_PROVIDER_MESSAGE_CODE_FETCH_DATA              (2)
#define CLOUD_PROVIDER_MESSAGE_CODE_FILE_LEAVING_SCOPE      (3)
#define CLOUD_PROVIDER_MESSAGE_CODE_DELETE_PENDING          (4)
#define CLOUD_PROVIDER_MESSAGE_CODE_LAST_USER_HANDLE_CLOSE  (5)

#define FETCH_DATA_FLAG_READ    (0x00000001)
#define FETCH_DATA_FLAG_WRITE   (0x00000002)

#define CLOUD_PROVIDER_VOLUME_GUID_NAME_SIZE   48

typedef struct _CLOUD_PROVIDER_MESSAGE
{
    ULONG Version;
    ULONG MessageCode;

    union {
        struct {
            FILE_ID_128 FileId;
            WCHAR VolumeGuidName[CLOUD_PROVIDER_VOLUME_GUID_NAME_SIZE];
        } FileOpen;

        struct {
            FILE_ID_128 FileId;
            LARGE_INTEGER ContainingOffset;
            LARGE_INTEGER ContainingLength;
            LARGE_INTEGER RequiredOffset;
            ULONG RequiredLength;
            ULONG Flags;
            ULONG Alignment;
            WCHAR VolumeGuidName[CLOUD_PROVIDER_VOLUME_GUID_NAME_SIZE];
        } FetchData;

        struct {
            FILE_ID_128 FileId;
            FILE_ID_128 TargetDirectoryFileId;
            WCHAR VolumeGuidName[CLOUD_PROVIDER_VOLUME_GUID_NAME_SIZE];
        } FileLeavingScope;

        struct {
            FILE_ID_128 FileId;
            WCHAR VolumeGuidName[CLOUD_PROVIDER_VOLUME_GUID_NAME_SIZE];
        } DeletePending;

        struct {
            FILE_ID_128 FileId;
            WCHAR VolumeGuidName[CLOUD_PROVIDER_VOLUME_GUID_NAME_SIZE];
        } LastUserHandleClose;

    } DUMMYUNIONNAME;
} CLOUD_PROVIDER_MESSAGE, *PCLOUD_PROVIDER_MESSAGE;

#define SHUFFLE_FILE_FLAG_SKIP_INITIALIZING_NEW_CLUSTERS                (0x00000001)

typedef struct _SHUFFLE_FILE_DATA
{

    LONGLONG StartingOffset;
    LONGLONG Length;
    ULONG Flags;

} SHUFFLE_FILE_DATA, *PSHUFFLE_FILE_DATA;

typedef struct _SPARSE_OVERALLOCATE_DATA
{
    ULONG SparseOverAllocateSize;
} SPARSE_OVERALLOCATE_DATA, *PSPARSE_OVERALLOCATE_DATA;

typedef enum _FILE_METADATA_OPTIMIZATION_STATE
{
    FileMetadataOptimizationNone = 0,
    FileMetadataOptimizationInProgress,
    FileMetadataOptimizationPending
} FILE_METADATA_OPTIMIZATION_STATE, *PFILE_METADATA_OPTIMIZATION_STATE;

typedef struct _FILE_QUERY_METADATA_OPTIMIZATION_OUTPUT
{
    FILE_METADATA_OPTIMIZATION_STATE State;
    ULONG AttributeListSize;
    ULONG MetadataSpaceUsed;
    ULONG MetadataSpaceAllocated;
    ULONG NumberOfFileRecords;
    ULONG NumberOfResidentAttributes;
    ULONG NumberOfNonresidentAttributes;
    ULONG TotalInProgress;
    ULONG TotalPending;
} FILE_QUERY_METADATA_OPTIMIZATION_OUTPUT, *PFILE_QUERY_METADATA_OPTIMIZATION_OUTPUT;

NTSTATUS
NTAPI
DbgkWerAddSecondaryData (
    _In_ HANDLE ReportHandle,
    _In_reads_bytes_(sizeof(GUID)) LPCGUID Identifier,
    _In_reads_bytes_(Size) PVOID Data,
    _In_ ULONG Size
    );

#ifdef __cplusplus
}    // extern "C"
#endif

#endif // _NTOSIFS_
