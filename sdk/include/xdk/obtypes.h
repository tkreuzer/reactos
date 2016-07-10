/******************************************************************************
 *                            Object Manager Types                            *
 ******************************************************************************/

$if (_WDMDDK_)
#define MAXIMUM_FILENAME_LENGTH           256
#define OBJ_NAME_PATH_SEPARATOR           ((WCHAR)L'\\')

#define OBJECT_TYPE_CREATE                0x0001
#define OBJECT_TYPE_ALL_ACCESS            (STANDARD_RIGHTS_REQUIRED | 0x1)

#define DIRECTORY_QUERY                   0x0001
#define DIRECTORY_TRAVERSE                0x0002
#define DIRECTORY_CREATE_OBJECT           0x0004
#define DIRECTORY_CREATE_SUBDIRECTORY     0x0008
#define DIRECTORY_ALL_ACCESS              (STANDARD_RIGHTS_REQUIRED | 0xF)

#define SYMBOLIC_LINK_QUERY               0x0001
#define SYMBOLIC_LINK_ALL_ACCESS          (STANDARD_RIGHTS_REQUIRED | 0x1)

#define DUPLICATE_CLOSE_SOURCE            0x00000001
#define DUPLICATE_SAME_ACCESS             0x00000002
#define DUPLICATE_SAME_ATTRIBUTES         0x00000004

#define OB_FLT_REGISTRATION_VERSION_0100  0x0100
#define OB_FLT_REGISTRATION_VERSION       OB_FLT_REGISTRATION_VERSION_0100

typedef ULONG OB_OPERATION;

#define OB_OPERATION_HANDLE_CREATE        0x00000001
#define OB_OPERATION_HANDLE_DUPLICATE     0x00000002

typedef struct _OB_PRE_CREATE_HANDLE_INFORMATION {
  _Inout_ ACCESS_MASK DesiredAccess;
  _In_ ACCESS_MASK OriginalDesiredAccess;
} OB_PRE_CREATE_HANDLE_INFORMATION, *POB_PRE_CREATE_HANDLE_INFORMATION;

typedef struct _OB_PRE_DUPLICATE_HANDLE_INFORMATION {
  _Inout_ ACCESS_MASK DesiredAccess;
  _In_ ACCESS_MASK OriginalDesiredAccess;
  _In_ PVOID SourceProcess;
  _In_ PVOID TargetProcess;
} OB_PRE_DUPLICATE_HANDLE_INFORMATION, *POB_PRE_DUPLICATE_HANDLE_INFORMATION;

typedef union _OB_PRE_OPERATION_PARAMETERS {
  _Inout_ OB_PRE_CREATE_HANDLE_INFORMATION CreateHandleInformation;
  _Inout_ OB_PRE_DUPLICATE_HANDLE_INFORMATION DuplicateHandleInformation;
} OB_PRE_OPERATION_PARAMETERS, *POB_PRE_OPERATION_PARAMETERS;

typedef struct _OB_PRE_OPERATION_INFORMATION {
  _In_ OB_OPERATION Operation;
  _ANONYMOUS_UNION union {
    _In_ ULONG Flags;
    _ANONYMOUS_STRUCT struct {
      _In_ ULONG KernelHandle:1;
      _In_ ULONG Reserved:31;
    } DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
  _In_ PVOID Object;
  _In_ POBJECT_TYPE ObjectType;
  _Out_ PVOID CallContext;
  _In_ POB_PRE_OPERATION_PARAMETERS Parameters;
} OB_PRE_OPERATION_INFORMATION, *POB_PRE_OPERATION_INFORMATION;

typedef struct _OB_POST_CREATE_HANDLE_INFORMATION {
  _In_ ACCESS_MASK GrantedAccess;
} OB_POST_CREATE_HANDLE_INFORMATION, *POB_POST_CREATE_HANDLE_INFORMATION;

typedef struct _OB_POST_DUPLICATE_HANDLE_INFORMATION {
  _In_ ACCESS_MASK GrantedAccess;
} OB_POST_DUPLICATE_HANDLE_INFORMATION, *POB_POST_DUPLICATE_HANDLE_INFORMATION;

typedef union _OB_POST_OPERATION_PARAMETERS {
  _In_ OB_POST_CREATE_HANDLE_INFORMATION CreateHandleInformation;
  _In_ OB_POST_DUPLICATE_HANDLE_INFORMATION DuplicateHandleInformation;
} OB_POST_OPERATION_PARAMETERS, *POB_POST_OPERATION_PARAMETERS;

typedef struct _OB_POST_OPERATION_INFORMATION {
  _In_ OB_OPERATION Operation;
  _ANONYMOUS_UNION union {
    _In_ ULONG Flags;
    _ANONYMOUS_STRUCT struct {
      _In_ ULONG KernelHandle:1;
      _In_ ULONG Reserved:31;
    } DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
  _In_ PVOID Object;
  _In_ POBJECT_TYPE ObjectType;
  _In_ PVOID CallContext;
  _In_ NTSTATUS ReturnStatus;
  _In_ POB_POST_OPERATION_PARAMETERS Parameters;
} OB_POST_OPERATION_INFORMATION,*POB_POST_OPERATION_INFORMATION;

typedef enum _OB_PREOP_CALLBACK_STATUS {
  OB_PREOP_SUCCESS
} OB_PREOP_CALLBACK_STATUS, *POB_PREOP_CALLBACK_STATUS;

typedef OB_PREOP_CALLBACK_STATUS
(NTAPI *POB_PRE_OPERATION_CALLBACK)(
  _In_ PVOID RegistrationContext,
  _Inout_ POB_PRE_OPERATION_INFORMATION OperationInformation);

typedef VOID
(NTAPI *POB_POST_OPERATION_CALLBACK)(
  _In_ PVOID RegistrationContext,
  _In_ POB_POST_OPERATION_INFORMATION OperationInformation);

typedef struct _OB_OPERATION_REGISTRATION {
  _In_ POBJECT_TYPE *ObjectType;
  _In_ OB_OPERATION Operations;
  _In_ POB_PRE_OPERATION_CALLBACK PreOperation;
  _In_ POB_POST_OPERATION_CALLBACK PostOperation;
} OB_OPERATION_REGISTRATION, *POB_OPERATION_REGISTRATION;

typedef struct _OB_CALLBACK_REGISTRATION {
  _In_ USHORT Version;
  _In_ USHORT OperationRegistrationCount;
  _In_ UNICODE_STRING Altitude;
  _In_ PVOID RegistrationContext;
  _In_ OB_OPERATION_REGISTRATION *OperationRegistration;
} OB_CALLBACK_REGISTRATION, *POB_CALLBACK_REGISTRATION;

typedef struct _OBJECT_NAME_INFORMATION {
  UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

/* Exported object types */
#ifdef _NTSYSTEM_
extern POBJECT_TYPE NTSYSAPI CmKeyObjectType;
extern POBJECT_TYPE NTSYSAPI ExEventObjectType;
extern POBJECT_TYPE NTSYSAPI ExSemaphoreObjectType;
extern POBJECT_TYPE NTSYSAPI IoFileObjectType;
extern POBJECT_TYPE NTSYSAPI PsThreadType;
extern POBJECT_TYPE NTSYSAPI SeTokenObjectType;
extern POBJECT_TYPE NTSYSAPI PsProcessType;
#else
__CREATE_NTOS_DATA_IMPORT_ALIAS(CmKeyObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(IoFileObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(ExEventObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(ExSemaphoreObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(TmTransactionManagerObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(TmResourceManagerObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(TmEnlistmentObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(TmTransactionObjectType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(PsProcessType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(PsThreadType)
__CREATE_NTOS_DATA_IMPORT_ALIAS(SeTokenObjectType)
extern POBJECT_TYPE *CmKeyObjectType;
extern POBJECT_TYPE *IoFileObjectType;
extern POBJECT_TYPE *ExEventObjectType;
extern POBJECT_TYPE *ExSemaphoreObjectType;
extern POBJECT_TYPE *TmTransactionManagerObjectType;
extern POBJECT_TYPE *TmResourceManagerObjectType;
extern POBJECT_TYPE *TmEnlistmentObjectType;
extern POBJECT_TYPE *TmTransactionObjectType;
extern POBJECT_TYPE *PsProcessType;
extern POBJECT_TYPE *PsThreadType;
extern POBJECT_TYPE *SeTokenObjectType;
#endif

$endif (_WDMDDK_)
$if (_NTIFS_)
typedef enum _OBJECT_INFORMATION_CLASS {
  ObjectBasicInformation = 0,
  ObjectTypeInformation = 2,
$endif (_NTIFS_)
$if (_NTIFS_) // we should remove these, but the kernel needs them :-/
  /* Not for public use */
  ObjectNameInformation = 1,
  ObjectTypesInformation = 3,
  ObjectHandleFlagInformation = 4,
  ObjectSessionInformation = 5,
  MaxObjectInfoClass
$endif (_NTIFS_)
$if (_NTIFS_)
} OBJECT_INFORMATION_CLASS;

$endif (_NTIFS_)

$if (0)

/* Object flags */
#define OB_FLAG_CREATE_INFO                     0x01
#define OB_FLAG_KERNEL_MODE                     0x02
#define OB_FLAG_CREATOR_INFO                    0x04
#define OB_FLAG_EXCLUSIVE                       0x08
#define OB_FLAG_PERMANENT                       0x10
#define OB_FLAG_SECURITY                        0x20
#define OB_FLAG_SINGLE_PROCESS                  0x40
#define OB_FLAG_DEFER_DELETE                    0x80

/* Reasons for open callback */
typedef enum _OB_OPEN_REASON
{
    ObCreateHandle,
    ObOpenHandle,
    ObDuplicateHandle,
    ObInheritHandle,
    ObMaxOpenReason
} OB_OPEN_REASON;

/* Object duplication flags */
#define DUPLICATE_SAME_ATTRIBUTES               0x00000004

/* Types for DosDeviceDriveType */
#define DOSDEVICE_DRIVE_UNKNOWN                 0
#define DOSDEVICE_DRIVE_CALCULATE               1
#define DOSDEVICE_DRIVE_REMOVABLE               2
#define DOSDEVICE_DRIVE_FIXED                   3
#define DOSDEVICE_DRIVE_REMOTE                  4
#define DOSDEVICE_DRIVE_CDROM                   5
#define DOSDEVICE_DRIVE_RAMDISK                 6

typedef struct _OBJECT_DUMP_CONTROL
{
    PVOID Stream;
    ULONG Detail;
} OBJECT_DUMP_CONTROL, *POBJECT_DUMP_CONTROL;

typedef
VOID
(NTAPI *POB_DUMP_PROCEDURE)(
    PVOID,
    POBJECT_DUMP_CONTROL);

typedef
LONG
(NTAPI *POB_OPEN_PROCEDURE)(
    OB_OPEN_REASON,
    CHAR,
    PEPROCESS,
    PVOID,
    ULONG32*,
    ULONG32);

typedef
VOID
(NTAPI *POB_CLOSE_PROCEDURE)(
    PEPROCESS,
    PVOID,
    ACCESS_MASK,
    ULONG_PTR,
    // additional
    ULONG_PTR);

typedef
VOID
(NTAPI *POB_DELETE_PROCEDURE)(
    PVOID);

typedef
LONG
(NTAPI *POB_PARSE_PROCEDURE)(
    PVOID,
    PVOID,
    PACCESS_STATE,
    CHAR,
    ULONG,
    PUNICODE_STRING,
    PUNICODE_STRING,
    PVOID,
    PSECURITY_QUALITY_OF_SERVICE,
    PVOID*);

typedef
LONG
(NTAPI *POB_SECURITY_PROCEDURE)(
    PVOID,
    SECURITY_OPERATION_CODE,
    PULONG,
    PVOID,
    PULONG,
    PVOID*,
    POOL_TYPE,
    PGENERIC_MAPPING
//    CHAR
);

typedef
NTSTATUS
(NTAPI *POB_QUERY_NAME_PROCEDURE)(
    PVOID,
    UCHAR,
    POBJECT_NAME_INFORMATION,
    ULONG,
    PULONG,
    CHAR);

typedef
BOOLEAN
(NTAPI *POB_OK_TO_CLOSE_PROCEDURE)(
    PEPROCESS,
    PVOID,
    PVOID,
    CHAR);

typedef struct _OBJECT_HANDLE_ATTRIBUTE_INFORMATION
{
    BOOLEAN Inherit;
    BOOLEAN ProtectFromClose;
} OBJECT_HANDLE_ATTRIBUTE_INFORMATION, *POBJECT_HANDLE_ATTRIBUTE_INFORMATION;

typedef struct _OBJECT_DIRECTORY_INFORMATION
{
    UNICODE_STRING Name;
    UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

typedef struct _OBJECT_TYPE_INITIALIZER
{
    USHORT Length;
    union
    {
        UCHAR ObjectTypeFlags;
        struct
        {
            UCHAR CaseInsensitive : 1;
            UCHAR UnnamedObjectsOnly : 1;
            UCHAR UseDefaultObject : 1;
            UCHAR SecurityRequired : 1;
            UCHAR MaintainHandleCount : 1;
            UCHAR MaintainTypeList : 1;
            UCHAR SupportsObjectCallbacks : 1;
            UCHAR CacheAligned : 1;
        };
    };
    ULONG ObjectTypeCode;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    ULONG RetainAccess;
    POOL_TYPE PoolType;
    ULONG DefaultPagedPoolCharge;
    ULONG DefaultNonPagedPoolCharge;
    POB_DUMP_PROCEDURE DumpProcedure;
    POB_OPEN_PROCEDURE OpenProcedure;
    POB_CLOSE_PROCEDURE CloseProcedure;
    POB_DELETE_PROCEDURE DeleteProcedure;
    POB_PARSE_PROCEDURE ParseProcedure;
    POB_SECURITY_PROCEDURE SecurityProcedure;
    POB_QUERY_NAME_PROCEDURE QueryNameProcedure;
    POB_OK_TO_CLOSE_PROCEDURE OkayToCloseProcedure;
    ULONG WaitObjectFlagMask;
    USHORT WaitObjectFlagOffset;
    USHORT WaitObjectPointerOffset;
} OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;

$endif (0)
