
#pragma once

#include <ntoskrnl.h>
#include <Ex/Ex.hpp>
#include <Se/Se.hpp>

typedef enum _OBJECT_INFORMATION_CLASS
{
    ObjectBasicInformation = 0,
    ObjectTypeInformation = 2
} OBJECT_INFORMATION_CLASS;

typedef struct _OB_CALLBACK_REGISTRATION *POB_CALLBACK_REGISTRATION;
typedef struct _OBJECT_TYPE *POBJECT_TYPE;
typedef struct _OBJECT_HANDLE_INFORMATION *POBJECT_HANDLE_INFORMATION;
typedef struct _OBJECT_NAME_INFORMATION *POBJECT_NAME_INFORMATION;
typedef struct _PROCESS_DEVICEMAP_INFORMATION *PPROCESS_DEVICEMAP_INFORMATION;

#define DELETE                   0x00010000L
#define READ_CONTROL             0x00020000L
#define WRITE_DAC                0x00040000L
#define WRITE_OWNER              0x00080000L
#define SYNCHRONIZE              0x00100000L
#define STANDARD_RIGHTS_REQUIRED 0x000F0000L
#define STANDARD_RIGHTS_READ     READ_CONTROL
#define STANDARD_RIGHTS_WRITE    READ_CONTROL
#define STANDARD_RIGHTS_EXECUTE  READ_CONTROL
#define STANDARD_RIGHTS_ALL      0x001F0000L
#define SPECIFIC_RIGHTS_ALL      0x0000FFFFL
#define ACCESS_SYSTEM_SECURITY   0x01000000L
#define MAXIMUM_ALLOWED          0x02000000L
#define GENERIC_READ             0x80000000L
#define GENERIC_WRITE            0x40000000L
#define GENERIC_EXECUTE          0x20000000L
#define GENERIC_ALL              0x10000000L

#define DIRECTORY_QUERY                 0x0001
#define DIRECTORY_TRAVERSE              0x0002
#define DIRECTORY_CREATE_OBJECT         0x0004
#define DIRECTORY_CREATE_SUBDIRECTORY   0x0008
#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|0xF)

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

enum OB_OPEN_REASON
{
    ObCreateHandle,
    ObOpenHandle,
    ObDuplicateHandle,
    ObInheritHandle,
    ObMaxOpenReason
};

typedef struct _OB_DUMP_CONTROL
{
    PVOID Stream;
    ULONG Detail;
} OB_DUMP_CONTROL, *POB_DUMP_CONTROL;

// ntosifs.h: OB_DUMP_METHOD
typedef
VOID
NTAPI
OB_DUMP_PROCEDURE (
    _In_ PVOID Object,
    _In_opt_ POB_DUMP_CONTROL Control);
typedef OB_DUMP_PROCEDURE *POB_DUMP_PROCEDURE;

// ntosifs.h: OB_OPEN_METHOD
typedef
NTSTATUS
NTAPI
OB_OPEN_PROCEDURE (
    _In_ OB_OPEN_REASON OpenReason,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _Inout_ PACCESS_MASK GrantedAccess,
    _In_ ULONG HandleCount);
typedef OB_OPEN_PROCEDURE *POB_OPEN_PROCEDURE;

// ntosifs.h: OB_CLOSE_METHOD
typedef
VOID
NTAPI
OB_CLOSE_PROCEDURE (
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ ULONG_PTR ProcessHandleCount,
    _In_ ULONG_PTR SystemHandleCount);
typedef OB_CLOSE_PROCEDURE *POB_CLOSE_PROCEDURE;

// ntosifs.h: OB_DELETE_METHOD
typedef
VOID
NTAPI
OB_DELETE_PROCEDURE (
    _In_  PVOID Object);
typedef OB_DELETE_PROCEDURE *POB_DELETE_PROCEDURE;

// ntosifs.h: OB_PARSE_METHOD
typedef
NTSTATUS
NTAPI
OB_PARSE_PROCEDURE (
    _In_ PVOID ParseObject,
    _In_ PVOID ObjectType,
    _Inout_ PACCESS_STATE AccessState,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Attributes,
    _Inout_ PUNICODE_STRING CompleteName,
    _Inout_ PUNICODE_STRING RemainingName,
    _Inout_opt_ PVOID Context,
    _In_opt_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Out_ PVOID *Object);
typedef OB_PARSE_PROCEDURE *POB_PARSE_PROCEDURE;

// ntosifs.h: OB_SECURITY_METHOD
typedef
NTSTATUS
NTAPI
OB_SECURITY_PROCEDURE (
    _In_ PVOID Object,
    _In_ SECURITY_OPERATION_CODE OperationCode,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _Inout_ PVOID SecurityDescriptor, // PSECURITY_DESCRIPTOR
    _Inout_ PULONG CapturedLength,
    _Inout_ PVOID *ObjectsSecurityDescriptor, // PSECURITY_DESCRIPTOR*
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE Mode);
typedef OB_SECURITY_PROCEDURE *POB_SECURITY_PROCEDURE;

// ntosifs.h: OB_QUERYNAME_METHOD
typedef
NTSTATUS
NTAPI
OB_QUERYNAME_PROCEDURE (
    _In_ PVOID Object,
    _In_ BOOLEAN HasObjectName,
    _Out_writes_bytes_opt_(Length) POBJECT_NAME_INFORMATION ObjectNameInfo,
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength,
    _In_ KPROCESSOR_MODE Mode);
typedef OB_QUERYNAME_PROCEDURE *POB_QUERYNAME_PROCEDURE;

// ntosifs.h: OB_OKAYTOCLOSE_METHOD
typedef
BOOLEAN
NTAPI
OB_OKAYTOCLOSE_PROCEDURE (
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ HANDLE Handle,
    _In_ KPROCESSOR_MODE PreviousMode);
typedef OB_OKAYTOCLOSE_PROCEDURE *POB_OKAYTOCLOSE_PROCEDURE;

typedef struct _OBJECT_TYPE_INITIALIZER
{
    USHORT Length;
#if 0
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
#else
    BOOLEAN UseDefaultObject;
    BOOLEAN CaseInsensitive;
#endif
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
#if 0
    ULONG RetainAccess;
#else
    BOOLEAN SecurityRequired;
    BOOLEAN MaintainHandleCount;
    BOOLEAN MaintainTypeList;
#endif
    POOL_TYPE PoolType;
    ULONG DefaultPagedPoolCharge;
    ULONG DefaultNonPagedPoolCharge;
    POB_DUMP_PROCEDURE DumpProcedure;
    POB_OPEN_PROCEDURE OpenProcedure;
    POB_CLOSE_PROCEDURE CloseProcedure;
    POB_DELETE_PROCEDURE DeleteProcedure;
    POB_PARSE_PROCEDURE ParseProcedure;
    POB_SECURITY_PROCEDURE SecurityProcedure;
    POB_QUERYNAME_PROCEDURE QueryNameProcedure;
    POB_OKAYTOCLOSE_PROCEDURE OkayToCloseProcedure;
#if 0
    ULONG WaitObjectFlagMask;
    USHORT WaitObjectFlagOffset;
    USHORT WaitObjectPointerOffset;
#endif
} OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;


