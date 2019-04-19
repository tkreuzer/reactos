

typedef enum
{
    ObjectHeaderCreatorInfo = 0x01,
    ObjectHeaderNameInfo = 0x02,
    ObjectHeaderProcessInfo = 0x04,
    ObjectHeaderQuotaInfo = 0x08,
    ObjectHeaderHandleInfo = 0x10, // FIXME: check this value
    // anything more?
} OBJECT_HEADER_INFO_MASK;

#define OBJECT_HEADER_CREATOR_INFO_MASK 0x01
#define OBJECT_HEADER_NAME_INFO_MASK    0x02
#define OBJECT_HEADER_PROCESS_INFO_MASK 0x04
#define OBJECT_HEADER_QUOTA_INFO_MASK   0x08
#define OBJECT_HEADER_HANDLE_INFO_MASK  0x10

#define MAX_HEADER_INFO 5

typedef struct _OBJECT_HEADER_AUDIT_INFO
{
    PVOID SecurityDescriptor;
    ULONG64 Reserved;
} OBJECT_HEADER_AUDIT_INFO, *POBJECT_HEADER_AUDIT_INFO;

typedef struct _OBJECT_HEADER_CREATOR_INFO
{
    LIST_ENTRY TypeList;
    PVOID CreatorUniqueProcess;
    USHORT CreatorBackTraceIndex;
    USHORT Reserved;
} OBJECT_HEADER_CREATOR_INFO, *POBJECT_HEADER_CREATOR_INFO;

typedef struct _OBJECT_HANDLE_COUNT_ENTRY
{
    struct _EPROCESS* Process;
    struct
    {
        ULONG HandleCount : 24;
        ULONG LockCount : 8;
    };
} OBJECT_HANDLE_COUNT_ENTRY, *POBJECT_HANDLE_COUNT_ENTRY;

typedef struct _OBJECT_HANDLE_COUNT_DATABASE
{
    ULONG CountEntries;
    OBJECT_HANDLE_COUNT_ENTRY HandleCountEntries[1];
} OBJECT_HANDLE_COUNT_DATABASE, *POBJECT_HANDLE_COUNT_DATABASE;

typedef struct _OBJECT_HEADER_HANDLE_INFO
{
    union
    {
        struct _OBJECT_HANDLE_COUNT_DATABASE* HandleCountDataBase;
        OBJECT_HANDLE_COUNT_ENTRY SingleEntry;
    };
} OBJECT_HEADER_HANDLE_INFO, *POBJECT_HEADER_HANDLE_INFO;

typedef struct _OBJECT_HEADER_NAME_INFO
{
    struct _OBJECT_DIRECTORY* Directory;
    UNICODE_STRING Name;
    LONG ReferenceCount;
} OBJECT_HEADER_NAME_INFO, *POBJECT_HEADER_NAME_INFO;

typedef struct _OBJECT_HEADER_PROCESS_INFO
{
    struct _EPROCESS* ExclusiveProcess;
    ULONG64 Reserved;
} OBJECT_HEADER_PROCESS_INFO, *POBJECT_HEADER_PROCESS_INFO;

typedef struct _OBJECT_HEADER_QUOTA_INFO
{
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    ULONG SecurityDescriptorCharge;
    PVOID SecurityDescriptorQuotaBlock;
    ULONG64 Reserved;
} OBJECT_HEADER_QUOTA_INFO, *POBJECT_HEADER_QUOTA_INFO;

/* Make sure all info sizes together don't overflow an UCHAR */
C_ASSERT((sizeof(OBJECT_HEADER_CREATOR_INFO) +
          sizeof(OBJECT_HEADER_NAME_INFO) +
          sizeof(OBJECT_HEADER_PROCESS_INFO) +
          sizeof(OBJECT_HEADER_QUOTA_INFO) +
          sizeof(OBJECT_HEADER_AUDIT_INFO) +
          sizeof(OBJECT_HEADER_HANDLE_INFO)) < 255);

typedef struct _OBJECT_DIRECTORY_ENTRY
{
    struct _OBJECT_DIRECTORY_ENTRY* ChainLink;
    PVOID Object;
    ULONG HashValue;
} OBJECT_DIRECTORY_ENTRY, *POBJECT_DIRECTORY_ENTRY;

#define NUMBER_HASH_BUCKETS 37
typedef struct _OBJECT_DIRECTORY
{
    POBJECT_DIRECTORY_ENTRY HashBuckets[NUMBER_HASH_BUCKETS];
    EX_PUSH_LOCK Lock;
    union
    {
        PDEVICE_MAP DeviceMap;
        struct _OBJECT_DIRECTORY* ShadowDirectory;
    };
    ULONG SessionId;
    PVOID NamespaceEntry;
    ULONG Flags;
} OBJECT_DIRECTORY, *POBJECT_DIRECTORY;

typedef struct _OBJECT_TYPE
{
    LIST_ENTRY TypeList;
    UNICODE_STRING Name;
    PVOID DefaultObject;
    UCHAR Index;
    ULONG TotalNumberOfObjects;
    ULONG TotalNumberOfHandles;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    OBJECT_TYPE_INITIALIZER TypeInfo;
    EX_PUSH_LOCK TypeLock;
    ULONG Key;
    LIST_ENTRY CallbackList;
} OBJECT_TYPE, *POBJECT_TYPE;

// should go to ob_private, but io uses it :-/
typedef struct _OBJECT_HEADER
{
    LONG_PTR PointerCount;
    union
    {
        LONG_PTR HandleCount;
        PVOID NextToFree;
    };
    EX_PUSH_LOCK Lock;
    UCHAR TypeIndex;
    UCHAR TraceFlags;
    UCHAR InfoMask;
    UCHAR Flags;
#ifdef _WIN64
    ULONG Spare;
#endif
    union
    {
        struct _OBJECT_CREATE_INFORMATION* ObjectCreateInfo;
        PVOID QuotaBlockCharged;
    };
    PVOID SecurityDescriptor;
    QUAD Body;
} OBJECT_HEADER, *POBJECT_HEADER;

#define MAX_OBJECT_TYPES 255

extern UCHAR ObpObjectHeaderInfoSize[];
extern LONG ObpLastObjectIndex;
extern POBJECT_TYPE ObpObjectType[MAX_OBJECT_TYPES];
extern POBJECT_DIRECTORY ObpTypeDirectoryObject;

#define ObpGetObjectHeader(Object) (((POBJECT_HEADER)Object) - 1)

#define ObpIncrementPointerCount(Object, Count) \
    InterlockedExchangeAddSizeT(&ObpGetObjectHeader(Object)->PointerCount, Count)

PVOID
FORCEINLINE
ObpGetHeaderInfo(POBJECT_HEADER Header, UCHAR Mask)
{
    UCHAR Index = Header->InfoMask & (Mask | (Mask - 1));
    UCHAR Offset = ObpObjectHeaderInfoSize[Index];
    return (PUCHAR)Header - Offset;
}

#define ObpGetHeaderCreatorInfo(Header) \
    ObpGetHeaderInfo(Header, OBJECT_HEADER_CREATOR_INFO_MASK)

#define ObpGetHeaderNameInfo(Header) \
    ObpGetHeaderInfo(Header, OBJECT_HEADER_NAME_INFO_MASK)

#define ObpGetHeaderProcessInfo(Header) \
    ObpGetHeaderInfo(Header, OBJECT_HEADER_PROCESS_INFO_MASK)

#define ObpGetHeaderQuotaInfo(Header) \
    ObpGetHeaderInfo(Header, OBJECT_HEADER_QUOTA_INFO_MASK)

#define ObpGetHeaderHandleInfo(Header) \
    ObpGetHeaderInfo(Header, OBJECT_HEADER_HANDLE_INFO_MASK)

NTSTATUS
NTAPI
ObpDuplicateString(
    OUT PUNICODE_STRING Destination,
    IN PUNICODE_STRING Source,
    IN KPROCESSOR_MODE AccessMode);

NTSTATUS
NTAPI
ObpAllocateObject(
    IN POBJECT_TYPE ObjectType,
    IN ULONG ObjectSize,
    IN UCHAR InfoMask,
    IN PUNICODE_STRING ObjectName OPTIONAL,
    IN KPROCESSOR_MODE NameProbeMode OPTIONAL,
    OUT PVOID *ResultObject);

VOID
NTAPI
ObpCloseDirectoryObject(
    PEPROCESS Process,
    PVOID Object,
    ACCESS_MASK GrantedAccess,
    ULONG_PTR ProcessHandleCount,
    ULONG_PTR SystemHandleCount);

NTSTATUS
NTAPI
ObpInsertDirectoryEntry(
    IN POBJECT_DIRECTORY ParentDirectory,
    IN PVOID Object);
