          typedef struct _HANDLE_TABLE                            // 16 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     ULONG32      NextHandleNeedingPool;
/*0x004*/     LONG32       ExtraInfoPages;
/*0x008*/     UINT64       TableCode;
/*0x010*/     struct _EPROCESS* QuotaProcess;
/*0x018*/     struct _LIST_ENTRY HandleTableList;                 // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     ULONG32      UniqueProcessId;
              union                                               // 2 elements, 0x4 bytes (sizeof)
              {
/*0x02C*/         ULONG32      Flags;
                  struct                                          // 4 elements, 0x1 bytes (sizeof)
                  {
/*0x02C*/             UINT8        StrictFIFO : 1;                // 0 BitPosition
/*0x02C*/             UINT8        EnableHandleExceptions : 1;    // 1 BitPosition
/*0x02C*/             UINT8        Rundown : 1;                   // 2 BitPosition
/*0x02C*/             UINT8        Duplicated : 1;                // 3 BitPosition
                  };
              };
/*0x030*/     struct _EX_PUSH_LOCK HandleContentionEvent;         // 7 elements, 0x8 bytes (sizeof)
/*0x038*/     struct _EX_PUSH_LOCK HandleTableLock;               // 7 elements, 0x8 bytes (sizeof)
              union                                               // 2 elements, 0x40 bytes (sizeof)
              {
/*0x040*/         struct _HANDLE_TABLE_FREE_LIST FreeLists[1];
                  struct                                          // 2 elements, 0x40 bytes (sizeof)
                  {
/*0x040*/             UINT8        ActualEntry[32];
/*0x060*/             struct _HANDLE_TRACE_DEBUG_INFO* DebugInfo;
/*0x068*/             UINT8        _PADDING0_[0x18];
                  };
              };
          }HANDLE_TABLE, *PHANDLE_TABLE;

          typedef struct _HANDLE_TABLE_ENTRY                       // 13 elements, 0x10 bytes (sizeof)
          {
              union                                                // 4 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         INT64        VolatileLowValue;
/*0x000*/         INT64        LowValue;
/*0x000*/         struct _HANDLE_TABLE_ENTRY_INFO* InfoTable;
                  struct                                           // 4 elements, 0x8 bytes (sizeof)
                  {
/*0x000*/             UINT64       Unlocked : 1;                   // 0 BitPosition
/*0x000*/             UINT64       RefCnt : 19;                    // 1 BitPosition
/*0x000*/             UINT64       Attributes : 3;                 // 20 BitPosition
/*0x000*/             UINT64       ObjectPointerBits : 41;         // 23 BitPosition
                  };
              };
              union                                                // 5 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         INT64        HighValue;
/*0x008*/         struct _HANDLE_TABLE_ENTRY* NextFreeHandleEntry;
/*0x008*/         struct _EXHANDLE LeafHandleValue;                // 4 elements, 0x8 bytes (sizeof)
                  struct                                           // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x008*/             ULONG32      GrantedAccessBits : 25;         // 0 BitPosition
/*0x008*/             ULONG32      Spare : 7;                      // 25 BitPosition
                  };
/*0x00C*/         ULONG32      TypeInfo;
              };
          }HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;

          typedef struct _HANDLE_TABLE_ENTRY_INFO // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      AuditMask;
          }HANDLE_TABLE_ENTRY_INFO, *PHANDLE_TABLE_ENTRY_INFO;

          typedef struct _HANDLE_TABLE_FREE_LIST                // 6 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK FreeListLock;                // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _HANDLE_TABLE_ENTRY* FirstFreeHandleEntry;
/*0x010*/     struct _HANDLE_TABLE_ENTRY* LastFreeHandleEntry;
/*0x018*/     LONG32       HandleCount;
/*0x01C*/     ULONG32      HighWaterMark;
/*0x020*/     ULONG32      Reserved[8];
          }HANDLE_TABLE_FREE_LIST, *PHANDLE_TABLE_FREE_LIST;

          typedef struct _HANDLE_TRACE_DB_ENTRY // 4 elements, 0xA0 bytes (sizeof)
          {
/*0x000*/     struct _CLIENT_ID ClientId;       // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     VOID*        Handle;
/*0x018*/     ULONG32      Type;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     VOID*        StackTrace[16];
          }HANDLE_TRACE_DB_ENTRY, *PHANDLE_TRACE_DB_ENTRY;

          typedef struct _HANDLE_TRACE_DEBUG_INFO       // 6 elements, 0xF0 bytes (sizeof)
          {
/*0x000*/     LONG32       RefCount;
/*0x004*/     ULONG32      TableSize;
/*0x008*/     ULONG32      BitMaskFlags;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     struct _FAST_MUTEX CloseCompactionLock;   // 5 elements, 0x38 bytes (sizeof)
/*0x048*/     ULONG32      CurrentStackIndex;
/*0x04C*/     UINT8        _PADDING1_[0x4];
/*0x050*/     struct _HANDLE_TRACE_DB_ENTRY TraceDb[1];
          }HANDLE_TRACE_DEBUG_INFO, *PHANDLE_TRACE_DEBUG_INFO;

          typedef struct _OB_DUPLICATE_OBJECT_STATE       // 6 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _EPROCESS* SourceProcess;
/*0x008*/     VOID*        SourceHandle;
/*0x010*/     VOID*        Object;
/*0x018*/     ULONG32      TargetAccess;
/*0x01C*/     struct _HANDLE_TABLE_ENTRY_INFO ObjectInfo; // 1 elements, 0x4 bytes (sizeof)
/*0x020*/     ULONG32      HandleAttributes;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }OB_DUPLICATE_OBJECT_STATE, *POB_DUPLICATE_OBJECT_STATE;

          typedef struct _OBJECT_ATTRIBUTES          // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     ULONG32      Length;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        RootDirectory;
/*0x010*/     struct _UNICODE_STRING* ObjectName;
/*0x018*/     ULONG32      Attributes;
/*0x01C*/     UINT8        _PADDING1_[0x4];
/*0x020*/     VOID*        SecurityDescriptor;
/*0x028*/     VOID*        SecurityQualityOfService;
          }OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

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

typedef struct _OBJECT_DIRECTORY_ENTRY
{
    struct _OBJECT_DIRECTORY_ENTRY* ChainLink;
    PVOID Object;
    ULONG HashValue;
} OBJECT_DIRECTORY_ENTRY, *POBJECT_DIRECTORY_ENTRY;

typedef struct _OBJECT_DIRECTORY
{
    POBJECT_DIRECTORY_ENTRY HashBuckets[37];
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

typedef struct _OBJECT_DUMP_CONTROL
{
    PVOID Stream;
    ULONG Detail;
} OBJECT_DUMP_CONTROL, *POBJECT_DUMP_CONTROL;

          typedef struct _OBJECT_HANDLE_COUNT_DATABASE                 // 2 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      CountEntries;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _OBJECT_HANDLE_COUNT_ENTRY HandleCountEntries[1];
          }OBJECT_HANDLE_COUNT_DATABASE, *POBJECT_HANDLE_COUNT_DATABASE;

          typedef struct _OBJECT_HANDLE_COUNT_ENTRY // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _EPROCESS* Process;
              struct                                // 2 elements, 0x4 bytes (sizeof)
              {
/*0x008*/         ULONG32      HandleCount : 24;    // 0 BitPosition
/*0x008*/         ULONG32      LockCount : 8;       // 24 BitPosition
              };
          }OBJECT_HANDLE_COUNT_ENTRY, *POBJECT_HANDLE_COUNT_ENTRY;

          typedef struct _OBJECT_HANDLE_INFORMATION // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      HandleAttributes;
/*0x004*/     ULONG32      GrantedAccess;
          }OBJECT_HANDLE_INFORMATION, *POBJECT_HANDLE_INFORMATION;

          typedef struct _OBJECT_HEADER                                // 13 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     INT64        PointerCount;
              union                                                    // 2 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         INT64        HandleCount;
/*0x008*/         VOID*        NextToFree;
              };
/*0x010*/     struct _EX_PUSH_LOCK Lock;                               // 7 elements, 0x8 bytes (sizeof)
/*0x018*/     UINT8        TypeIndex;
/*0x019*/     UINT8        TraceFlags;
/*0x01A*/     UINT8        InfoMask;
/*0x01B*/     UINT8        Flags;
/*0x01C*/     ULONG32      Spare;
              union                                                    // 2 elements, 0x8 bytes (sizeof)
              {
/*0x020*/         struct _OBJECT_CREATE_INFORMATION* ObjectCreateInfo;
/*0x020*/         VOID*        QuotaBlockCharged;
              };
/*0x028*/     VOID*        SecurityDescriptor;
/*0x030*/     struct _QUAD Body;                                       // 2 elements, 0x8 bytes (sizeof)
          }OBJECT_HEADER, *POBJECT_HEADER;

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

typedef struct _OBJECT_HEADER_HANDLE_INFO
{
    union
    {
        struct _OBJECT_HANDLE_COUNT_DATABASE* HandleCountDataBase;
        struct _OBJECT_HANDLE_COUNT_ENTRY SingleEntry;
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

          typedef struct _OBJECT_NAME_INFORMATION // 1 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _UNICODE_STRING Name;        // 3 elements, 0x10 bytes (sizeof)
          }OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _OBJECT_REF_STACK_INFO
{
    ULONG Sequence;
    USHORT Index;
    USHORT NumTraces;
    ULONG Tag;
} OBJECT_REF_STACK_INFO, *POBJECT_REF_STACK_INFO;

typedef struct _OBJECT_REF_INFO
{
    POBJECT_HEADER ObjectHeader;
    PVOID NextRef;
    UCHAR ImageFileName[16];
    USHORT NextPos;
    USHORT MaxStacks;
    OBJECT_REF_STACK_INFO StackInfo[0];
} OBJECT_REF_INFO, *POBJECT_REF_INFO;

typedef struct _OBJECT_REF_TRACE
{
    PVOID StackTrace[16];
} OBJECT_REF_TRACE, *POBJECT_REF_TRACE;

typedef struct _STACK_TABLE
{
    USHORT NumStackTraces;
    USHORT TraceCapacity;
    POBJECT_REF_TRACE StackTrace[16];
    USHORT StackTableHash[16381];
} STACK_TABLE, *PSTACK_TABLE;

typedef struct _OBJECT_SYMBOLIC_LINK
{
    LARGE_INTEGER CreationTime;
    UNICODE_STRING LinkTarget;
    ULONG DosDeviceDriveIndex;
} OBJECT_SYMBOLIC_LINK, *POBJECT_SYMBOLIC_LINK;

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

typedef
VOID
(*POB_DUMP_PROCEDURE)(
    PVOID,
    struct _OBJECT_DUMP_CONTROL*);

typedef
LONG
(*POB_OPEN_PROCEDURE)(
    enum _OB_OPEN_REASON,
    CHAR,
    struct _EPROCESS*,
    VOID*, ULONG32*, ULONG32);

typedef
VOID
(*POB_CLOSE_PROCEDURE)(
    struct _EPROCESS*,
    PVOID,
    UINT64,
    UINT64);

typedef
VOID
(*POB_DELETE_PROCEDURE)(
    PVOID);

typedef
LONG
(*POB_PARSE_PROCEDURE)(
    PVOID,
    PVOID,
    struct _ACCESS_STATE*,
    CHAR,
    ULONG,
    PUNICODE_STRING,
    PUNICODE_STRING,
    PVOID,
    struct _SECURITY_QUALITY_OF_SERVICE*,
    PVOID*);

typedef
LONG
(*POB_SECURITY_PROCEDURE)(
    PVOID,
    enum _SECURITY_OPERATION_CODE,
    PULONG,
    PVOID,
    PULONG,
    PVOID*,
    POOL_TYPE,
    struct _GENERIC_MAPPING*,
    CHAR);

typedef
LONG
(*POB_QUERY_NAME_PROCEDURE)(
    PVOID,
    UCHAR,
    struct _OBJECT_NAME_INFORMATION*,
    ULONG,
    PULONG,
    CHAR);

typedef
BOOLEAN
(*POB_OK_TO_CLOSE_PROCEDURE)(
    struct _EPROCESS*,
    PVOID,
    PVOID,
    CHAR);

typedef struct _OBJECT_TYPE_INITIALIZER                                                                                                                                                                                                 // 29 elements, 0x78 bytes (sizeof)
{
    USHORT Length;
    union                                                                                                                                                                                                                               // 2 elements, 0x1 bytes (sizeof)
    {
        UCHAR ObjectTypeFlags;
        struct                                                                                                                                                                                                                          // 8 elements, 0x1 bytes (sizeof)
        {
            UCHAR CaseInsensitive : 1;                                                                                                                                                                                           // 0 BitPosition
            UCHAR UnnamedObjectsOnly : 1;                                                                                                                                                                                        // 1 BitPosition
            UCHAR UseDefaultObject : 1;                                                                                                                                                                                          // 2 BitPosition
            UCHAR SecurityRequired : 1;                                                                                                                                                                                          // 3 BitPosition
            UCHAR MaintainHandleCount : 1;                                                                                                                                                                                       // 4 BitPosition
            UCHAR MaintainTypeList : 1;                                                                                                                                                                                          // 5 BitPosition
            UCHAR SupportsObjectCallbacks : 1;                                                                                                                                                                                   // 6 BitPosition
            UCHAR CacheAligned : 1;                                                                                                                                                                                              // 7 BitPosition
        };
    };
    ULONG ObjectTypeCode;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;                                                                                                                                                                                             // 4 elements, 0x10 bytes (sizeof)
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

          typedef struct _OBP_LOOKUP_CONTEXT              // 8 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _OBJECT_DIRECTORY* Directory;
/*0x008*/     VOID*        Object;
/*0x010*/     struct _OBJECT_DIRECTORY_ENTRY** EntryLink;
/*0x018*/     ULONG32      HashValue;
/*0x01C*/     USHORT       HashIndex;
/*0x01E*/     UINT8        DirectoryLocked;
/*0x01F*/     UINT8        LockedExclusive;
/*0x020*/     ULONG32      LockStateSignature;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }OBP_LOOKUP_CONTEXT, *POBP_LOOKUP_CONTEXT;

typedef enum _OB_OPEN_REASON  // 5 elements, 0x4 bytes
{
    ObCreateHandle    = 0 /*0x0*/,
    ObOpenHandle      = 1 /*0x1*/,
    ObDuplicateHandle = 2 /*0x2*/,
    ObInheritHandle   = 3 /*0x3*/,
    ObMaxOpenReason   = 4 /*0x4*/
}OB_OPEN_REASON, *POB_OPEN_REASON;

