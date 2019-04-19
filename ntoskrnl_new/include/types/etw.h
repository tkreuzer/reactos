
          typedef struct _ETW_BUFFER_CONTEXT        // 4 elements, 0x4 bytes (sizeof)
          {
              union                                 // 2 elements, 0x2 bytes (sizeof)
              {
                  struct                            // 2 elements, 0x2 bytes (sizeof)
                  {
/*0x000*/             UINT8        ProcessorNumber;
/*0x001*/             UINT8        Alignment;
                  };
/*0x000*/         UINT16       ProcessorIndex;
              };
/*0x002*/     UINT16       LoggerId;
          }ETW_BUFFER_CONTEXT, *PETW_BUFFER_CONTEXT;

          typedef struct _ETW_BUFFER_QUEUE          // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _SINGLE_LIST_ENTRY* QueueHead;
/*0x008*/     struct _SINGLE_LIST_ENTRY* QueueTail;
/*0x010*/     struct _SINGLE_LIST_ENTRY QueueEntry; // 1 elements, 0x8 bytes (sizeof)
          }ETW_BUFFER_QUEUE, *PETW_BUFFER_QUEUE;

          typedef struct _ETW_GUID_ENTRY                    // 10 elements, 0x1B0 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY GuidList;                  // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     LONG32       RefCount;
/*0x014*/     struct _GUID Guid;                            // 4 elements, 0x10 bytes (sizeof)
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     struct _LIST_ENTRY RegListHead;               // 2 elements, 0x10 bytes (sizeof)
/*0x038*/     VOID*        SecurityDescriptor;
              union                                         // 2 elements, 0x10 bytes (sizeof)
              {
/*0x040*/         struct _ETW_LAST_ENABLE_INFO LastEnable;  // 5 elements, 0x10 bytes (sizeof)
/*0x040*/         UINT64       MatchId;
              };
/*0x050*/     struct _TRACE_ENABLE_INFO ProviderEnableInfo; // 8 elements, 0x20 bytes (sizeof)
/*0x070*/     struct _TRACE_ENABLE_INFO EnableInfo[8];
/*0x170*/     struct _EVENT_FILTER_HEADER* FilterData[8];
          }ETW_GUID_ENTRY, *PETW_GUID_ENTRY;

          typedef struct _ETW_LAST_ENABLE_INFO   // 5 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     union _LARGE_INTEGER EnableFlags;  // 4 elements, 0x8 bytes (sizeof)
/*0x008*/     UINT16       LoggerId;
/*0x00A*/     UINT8        Level;
              struct                             // 2 elements, 0x1 bytes (sizeof)
              {
/*0x00B*/         UINT8        Enabled : 1;      // 0 BitPosition
/*0x00B*/         UINT8        InternalFlag : 7; // 1 BitPosition
              };
          }ETW_LAST_ENABLE_INFO, *PETW_LAST_ENABLE_INFO;

          typedef struct _ETW_LOGGER_HANDLE     // 1 elements, 0x1 bytes (sizeof)
          {
/*0x000*/     UINT8        DereferenceAndLeave;
          }ETW_LOGGER_HANDLE, *PETW_LOGGER_HANDLE;

          typedef struct _ETW_PERF_COUNTERS               // 6 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     LONG32       TotalActiveSessions;
/*0x004*/     LONG32       TotalBufferMemoryNonPagedPool;
/*0x008*/     LONG32       TotalBufferMemoryPagedPool;
/*0x00C*/     LONG32       TotalGuidsEnabled;
/*0x010*/     LONG32       TotalGuidsNotEnabled;
/*0x014*/     LONG32       TotalGuidsPreEnabled;
          }ETW_PERF_COUNTERS, *PETW_PERF_COUNTERS;

          typedef struct _ETW_PMC_SUPPORT                 // 5 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     enum _KPROFILE_SOURCE Source[4];
/*0x010*/     ULONG32      HookIdCount;
/*0x014*/     UINT16       HookId[4];
/*0x01C*/     ULONG32      CountersCount;
/*0x020*/     struct _HAL_PMC_COUNTERS* ProcessorCtrs[1];
          }ETW_PMC_SUPPORT, *PETW_PMC_SUPPORT;

          typedef struct _ETW_QUEUE_ENTRY                  // 8 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;                // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _ETWP_NOTIFICATION_HEADER* DataBlock;
/*0x018*/     struct _ETW_REG_ENTRY* RegEntry;
/*0x020*/     struct _ETW_REG_ENTRY* ReplyObject;
/*0x028*/     VOID*        WakeReference;
/*0x030*/     UINT16       RegIndex;
/*0x032*/     UINT16       ReplyIndex;
/*0x034*/     ULONG32      Flags;
          }ETW_QUEUE_ENTRY, *PETW_QUEUE_ENTRY;

          typedef struct _ETW_REALTIME_CONSUMER              // 23 elements, 0x88 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Links;                      // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     VOID*        ProcessHandle;
/*0x018*/     struct _EPROCESS* ProcessObject;
/*0x020*/     VOID*        NextNotDelivered;
/*0x028*/     VOID*        RealtimeConnectContext;
/*0x030*/     struct _KEVENT* DisconnectEvent;
/*0x038*/     struct _KEVENT* DataAvailableEvent;
/*0x040*/     ULONG32*     UserBufferCount;
/*0x048*/     struct _SINGLE_LIST_ENTRY* UserBufferListHead;
/*0x050*/     ULONG32      BuffersLost;
/*0x054*/     ULONG32      EmptyBuffersCount;
/*0x058*/     UINT16       LoggerId;
              union                                          // 2 elements, 0x1 bytes (sizeof)
              {
/*0x05A*/         UINT8        Flags;
                  struct                                     // 5 elements, 0x1 bytes (sizeof)
                  {
/*0x05A*/             UINT8        ShutDownRequested : 1;    // 0 BitPosition
/*0x05A*/             UINT8        NewBuffersLost : 1;       // 1 BitPosition
/*0x05A*/             UINT8        Disconnected : 1;         // 2 BitPosition
/*0x05A*/             UINT8        Notified : 1;             // 3 BitPosition
/*0x05A*/             UINT8        Wow : 1;                  // 4 BitPosition
                  };
              };
/*0x060*/     struct _RTL_BITMAP ReservedBufferSpaceBitMap;  // 2 elements, 0x10 bytes (sizeof)
/*0x070*/     UINT8*       ReservedBufferSpace;
/*0x078*/     ULONG32      ReservedBufferSpaceSize;
/*0x07C*/     ULONG32      UserPagesAllocated;
/*0x080*/     ULONG32      UserPagesReused;
/*0x084*/     UINT8        _PADDING0_[0x4];
          }ETW_REALTIME_CONSUMER, *PETW_REALTIME_CONSUMER;

          typedef struct _ETW_REF_CLOCK            // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     union _LARGE_INTEGER StartTime;      // 4 elements, 0x8 bytes (sizeof)
/*0x008*/     union _LARGE_INTEGER StartPerfClock; // 4 elements, 0x8 bytes (sizeof)
          }ETW_REF_CLOCK, *PETW_REF_CLOCK;

          typedef struct _ETW_REG_ENTRY                  // 11 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY RegList;                // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _ETW_GUID_ENTRY* GuidEntry;
/*0x018*/     UINT16       Index;
/*0x01A*/     UINT16       Flags;
/*0x01C*/     UINT8        EnableMask;
/*0x01D*/     UINT8        _PADDING0_[0x3];
              union                                      // 3 elements, 0x20 bytes (sizeof)
              {
/*0x020*/         ULONG32      SessionId;
/*0x020*/         struct _ETW_REPLY_QUEUE* ReplyQueue;
/*0x020*/         struct _ETW_QUEUE_ENTRY* ReplySlot[4];
              };
              union                                      // 2 elements, 0x8 bytes (sizeof)
              {
/*0x040*/         struct _EPROCESS* Process;
/*0x040*/         VOID*        CallbackContext;
              };
/*0x048*/     VOID*        Callback;
          }ETW_REG_ENTRY, *PETW_REG_ENTRY;

          typedef struct _ETW_REPLY_QUEUE   // 2 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     struct _KQUEUE Queue;         // 5 elements, 0x40 bytes (sizeof)
/*0x040*/     LONG32       EventsLost;
/*0x044*/     UINT8        _PADDING0_[0x4];
          }ETW_REPLY_QUEUE, *PETW_REPLY_QUEUE;

          typedef struct _ETW_SESSION_PERF_COUNTERS  // 5 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     LONG32       BufferMemoryPagedPool;
/*0x004*/     LONG32       BufferMemoryNonPagedPool;
/*0x008*/     UINT64       EventsLoggedCount;
/*0x010*/     LONG32       EventsLost;
/*0x014*/     LONG32       NumConsumers;
          }ETW_SESSION_PERF_COUNTERS, *PETW_SESSION_PERF_COUNTERS;

typedef struct _ETW_STACK_CACHE // 0 elements, 0x0 bytes (sizeof)
{
}ETW_STACK_CACHE, *PETW_STACK_CACHE;

          typedef struct _ETW_SYSTEMTIME // 8 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Year;
/*0x002*/     UINT16       Month;
/*0x004*/     UINT16       DayOfWeek;
/*0x006*/     UINT16       Day;
/*0x008*/     UINT16       Hour;
/*0x00A*/     UINT16       Minute;
/*0x00C*/     UINT16       Second;
/*0x00E*/     UINT16       Milliseconds;
          }ETW_SYSTEMTIME, *PETW_SYSTEMTIME;

          typedef struct _ETW_WMITRACE_WORK          // 15 elements, 0xF0 bytes (sizeof)
          {
/*0x000*/     ULONG32      LoggerId;
/*0x004*/     UINT8        _PADDING0_[0x4];
              union                                  // 2 elements, 0xE0 bytes (sizeof)
              {
                  struct                             // 8 elements, 0xE0 bytes (sizeof)
                  {
/*0x008*/             CHAR         LoggerName[65];
/*0x049*/             CHAR         FileName[129];
/*0x0CA*/             UINT8        _PADDING1_[0x2];
/*0x0CC*/             ULONG32      MaximumFileSize;
/*0x0D0*/             ULONG32      MinBuffers;
/*0x0D4*/             ULONG32      MaxBuffers;
/*0x0D8*/             ULONG32      BufferSize;
/*0x0DC*/             ULONG32      Mode;
/*0x0E0*/             ULONG32      FlushTimer;
/*0x0E4*/             UINT8        _PADDING2_[0x4];
                  };
                  struct                             // 5 elements, 0xE0 bytes (sizeof)
                  {
/*0x008*/             UINT64       MatchAny;
/*0x010*/             UINT64       MatchAll;
/*0x018*/             ULONG32      EnableProperty;
/*0x01C*/             struct _GUID Guid;             // 4 elements, 0x10 bytes (sizeof)
/*0x02C*/             UINT8        Level;
/*0x02D*/             UINT8        _PADDING3_[0xBB];
                  };
              };
/*0x0E8*/     LONG32       Status;
/*0x0EC*/     UINT8        _PADDING4_[0x4];
          }ETW_WMITRACE_WORK, *PETW_WMITRACE_WORK;

          typedef struct _ETWP_NOTIFICATION_HEADER          // 15 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     enum _ETW_NOTIFICATION_TYPE NotificationType;
/*0x004*/     ULONG32      NotificationSize;
/*0x008*/     LONG32       RefCount;
/*0x00C*/     UINT8        ReplyRequested;
/*0x00D*/     UINT8        _PADDING0_[0x3];
              union                                         // 2 elements, 0x4 bytes (sizeof)
              {
/*0x010*/         ULONG32      ReplyIndex;
/*0x010*/         ULONG32      Timeout;
              };
              union                                         // 2 elements, 0x4 bytes (sizeof)
              {
/*0x014*/         ULONG32      ReplyCount;
/*0x014*/         ULONG32      NotifyeeCount;
              };
              union                                         // 3 elements, 0x8 bytes (sizeof)
              {
/*0x018*/         UINT64       ReplyHandle;
/*0x018*/         VOID*        ReplyObject;
/*0x018*/         ULONG32      RegIndex;
              };
/*0x020*/     ULONG32      TargetPID;
/*0x024*/     ULONG32      SourcePID;
/*0x028*/     struct _GUID DestinationGuid;                 // 4 elements, 0x10 bytes (sizeof)
/*0x038*/     struct _GUID SourceGuid;                      // 4 elements, 0x10 bytes (sizeof)
          }ETWP_NOTIFICATION_HEADER, *PETWP_NOTIFICATION_HEADER;

typedef enum _ETW_BUFFER_STATE  // 5 elements, 0x4 bytes
{
    EtwBufferStateFree           = 0 /*0x0*/,
    EtwBufferStateGeneralLogging = 1 /*0x1*/,
    EtwBufferStateCSwitch        = 2 /*0x2*/,
    EtwBufferStateFlush          = 3 /*0x3*/,
    EtwBufferStateMaximum        = 4 /*0x4*/
}ETW_BUFFER_STATE, *PETW_BUFFER_STATE;

typedef enum _ETW_HEADER_TYPE  // 3 elements, 0x4 bytes
{
    EtwHeaderTypeNative = 0 /*0x0*/,
    EtwHeaderTypeWow    = 1 /*0x1*/,
    EtwHeaderTypeMax    = 2 /*0x2*/
}ETW_HEADER_TYPE, *PETW_HEADER_TYPE;

typedef enum _ETW_NOTIFICATION_TYPE  // 10 elements, 0x4 bytes
{
    EtwNotificationTypeNoReply       = 1 /*0x1*/,
    EtwNotificationTypeLegacyEnable  = 2 /*0x2*/,
    EtwNotificationTypeEnable        = 3 /*0x3*/,
    EtwNotificationTypePrivateLogger = 4 /*0x4*/,
    EtwNotificationTypePerflib       = 5 /*0x5*/,
    EtwNotificationTypeAudio         = 6 /*0x6*/,
    EtwNotificationTypeSession       = 7 /*0x7*/,
    EtwNotificationTypeReserved      = 8 /*0x8*/,
    EtwNotificationTypeCredentialUI  = 9 /*0x9*/,
    EtwNotificationTypeMax           = 10 /*0xA*/
}ETW_NOTIFICATION_TYPE, *PETW_NOTIFICATION_TYPE;

typedef enum _ETW_RT_EVENT_LOSS  // 5 elements, 0x4 bytes
{
    EtwRtEventNoLoss  = 0 /*0x0*/,
    EtwRtEventLost    = 1 /*0x1*/,
    EtwRtBufferLost   = 2 /*0x2*/,
    EtwRtBackupLost   = 3 /*0x3*/,
    EtwRtEventLossMax = 4 /*0x4*/
}ETW_RT_EVENT_LOSS, *PETW_RT_EVENT_LOSS;

