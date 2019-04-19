          typedef struct _WMI_BUFFER_HEADER              // 19 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      BufferSize;
/*0x004*/     ULONG32      SavedOffset;
/*0x008*/     ULONG32      CurrentOffset;
/*0x00C*/     LONG32       ReferenceCount;
/*0x010*/     union _LARGE_INTEGER TimeStamp;            // 4 elements, 0x8 bytes (sizeof)
/*0x018*/     INT64        SequenceNumber;
              union                                      // 3 elements, 0x8 bytes (sizeof)
              {
/*0x020*/         ULONG32      Padding0[2];
/*0x020*/         struct _SINGLE_LIST_ENTRY SlistEntry;  // 1 elements, 0x8 bytes (sizeof)
/*0x020*/         struct _WMI_BUFFER_HEADER* NextBuffer;
              };
/*0x028*/     struct _ETW_BUFFER_CONTEXT ClientContext;  // 4 elements, 0x4 bytes (sizeof)
/*0x02C*/     enum _ETW_BUFFER_STATE State;
/*0x030*/     ULONG32      Offset;
/*0x034*/     UINT16       BufferFlag;
/*0x036*/     UINT16       BufferType;
              union                                      // 4 elements, 0x10 bytes (sizeof)
              {
/*0x038*/         ULONG32      Padding1[4];
/*0x038*/         struct _ETW_REF_CLOCK ReferenceTime;   // 2 elements, 0x10 bytes (sizeof)
/*0x038*/         struct _LIST_ENTRY GlobalEntry;        // 2 elements, 0x10 bytes (sizeof)
                  struct                                 // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x038*/             VOID*        Pointer0;
/*0x040*/             VOID*        Pointer1;
                  };
              };
          }WMI_BUFFER_HEADER, *PWMI_BUFFER_HEADER;

          typedef struct _WMI_LOGGER_CONTEXT                         // 106 elements, 0x380 bytes (sizeof)
          {
/*0x000*/     ULONG32      LoggerId;
/*0x004*/     ULONG32      BufferSize;
/*0x008*/     ULONG32      MaximumEventSize;
/*0x00C*/     ULONG32      LoggerMode;
/*0x010*/     LONG32       AcceptNewEvents;
/*0x014*/     ULONG32      EventMarker[2];
/*0x01C*/     ULONG32      ErrorMarker;
/*0x020*/     ULONG32      SizeMask;
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     FUNCT_007F_1DE5_GetCpuClock* GetCpuClock;
/*0x030*/     struct _ETHREAD* LoggerThread;
/*0x038*/     LONG32       LoggerStatus;
/*0x03C*/     UINT8        _PADDING1_[0x4];
/*0x040*/     struct _ETW_BUFFER_QUEUE BufferQueue;                  // 3 elements, 0x18 bytes (sizeof)
/*0x058*/     struct _ETW_BUFFER_QUEUE OverflowQueue;                // 3 elements, 0x18 bytes (sizeof)
/*0x070*/     struct _LIST_ENTRY GlobalList;                         // 2 elements, 0x10 bytes (sizeof)
              union                                                  // 2 elements, 0x8 bytes (sizeof)
              {
/*0x080*/         struct _WMI_BUFFER_HEADER* BatchedBufferList;
/*0x080*/         struct _EX_FAST_REF CurrentBuffer;                 // 3 elements, 0x8 bytes (sizeof)
              };
/*0x088*/     struct _UNICODE_STRING LoggerName;                     // 3 elements, 0x10 bytes (sizeof)
/*0x098*/     struct _UNICODE_STRING LogFileName;                    // 3 elements, 0x10 bytes (sizeof)
/*0x0A8*/     struct _UNICODE_STRING LogFilePattern;                 // 3 elements, 0x10 bytes (sizeof)
/*0x0B8*/     struct _UNICODE_STRING NewLogFileName;                 // 3 elements, 0x10 bytes (sizeof)
/*0x0C8*/     ULONG32      ClockType;
/*0x0CC*/     ULONG32      MaximumFileSize;
/*0x0D0*/     LONG32       CollectionOn;
/*0x0D4*/     ULONG32      LastFlushedBuffer;
/*0x0D8*/     ULONG32      FlushTimer;
/*0x0DC*/     ULONG32      FlushThreshold;
/*0x0E0*/     union _LARGE_INTEGER ByteOffset;                       // 4 elements, 0x8 bytes (sizeof)
/*0x0E8*/     ULONG32      MinimumBuffers;
/*0x0EC*/     LONG32       BuffersAvailable;
/*0x0F0*/     LONG32       NumberOfBuffers;
/*0x0F4*/     ULONG32      MaximumBuffers;
/*0x0F8*/     ULONG32      EventsLost;
/*0x0FC*/     ULONG32      BuffersWritten;
/*0x100*/     ULONG32      LogBuffersLost;
/*0x104*/     ULONG32      RealTimeBuffersDelivered;
/*0x108*/     ULONG32      RealTimeBuffersLost;
/*0x10C*/     UINT8        _PADDING2_[0x4];
/*0x110*/     LONG32*      SequencePtr;
/*0x118*/     ULONG32      LocalSequence;
/*0x11C*/     struct _GUID InstanceGuid;                             // 4 elements, 0x10 bytes (sizeof)
/*0x12C*/     LONG32       FileCounter;
/*0x130*/     FUNCT_00AE_1E0A_BufferCallback* BufferCallback;
/*0x138*/     enum _POOL_TYPE PoolType;
/*0x13C*/     UINT8        _PADDING3_[0x4];
/*0x140*/     struct _ETW_REF_CLOCK ReferenceTime;                   // 2 elements, 0x10 bytes (sizeof)
/*0x150*/     struct _LIST_ENTRY Consumers;                          // 2 elements, 0x10 bytes (sizeof)
/*0x160*/     ULONG32      NumConsumers;
/*0x164*/     UINT8        _PADDING4_[0x4];
/*0x168*/     struct _ETW_REALTIME_CONSUMER* TransitionConsumer;
/*0x170*/     VOID*        RealtimeLogfileHandle;
/*0x178*/     struct _UNICODE_STRING RealtimeLogfileName;            // 3 elements, 0x10 bytes (sizeof)
/*0x188*/     union _LARGE_INTEGER RealtimeWriteOffset;              // 4 elements, 0x8 bytes (sizeof)
/*0x190*/     union _LARGE_INTEGER RealtimeReadOffset;               // 4 elements, 0x8 bytes (sizeof)
/*0x198*/     union _LARGE_INTEGER RealtimeLogfileSize;              // 4 elements, 0x8 bytes (sizeof)
/*0x1A0*/     UINT64       RealtimeLogfileUsage;
/*0x1A8*/     UINT64       RealtimeMaximumFileSize;
/*0x1B0*/     ULONG32      RealtimeBuffersSaved;
/*0x1B4*/     UINT8        _PADDING5_[0x4];
/*0x1B8*/     struct _ETW_REF_CLOCK RealtimeReferenceTime;           // 2 elements, 0x10 bytes (sizeof)
/*0x1C8*/     enum _ETW_RT_EVENT_LOSS NewRTEventsLost;
/*0x1CC*/     UINT8        _PADDING6_[0x4];
/*0x1D0*/     struct _KEVENT LoggerEvent;                            // 1 elements, 0x18 bytes (sizeof)
/*0x1E8*/     struct _KEVENT FlushEvent;                             // 1 elements, 0x18 bytes (sizeof)
/*0x200*/     struct _KTIMER FlushTimeOutTimer;                      // 6 elements, 0x40 bytes (sizeof)
/*0x240*/     struct _KDPC LoggerDpc;                                // 9 elements, 0x40 bytes (sizeof)
/*0x280*/     struct _KMUTANT LoggerMutex;                           // 5 elements, 0x38 bytes (sizeof)
/*0x2B8*/     struct _EX_PUSH_LOCK LoggerLock;                       // 7 elements, 0x8 bytes (sizeof)
              union                                                  // 2 elements, 0x8 bytes (sizeof)
              {
/*0x2C0*/         UINT64       BufferListSpinLock;
/*0x2C0*/         struct _EX_PUSH_LOCK BufferListPushLock;           // 7 elements, 0x8 bytes (sizeof)
              };
/*0x2C8*/     struct _SECURITY_CLIENT_CONTEXT ClientSecurityContext; // 6 elements, 0x48 bytes (sizeof)
/*0x310*/     struct _EX_FAST_REF SecurityDescriptor;                // 3 elements, 0x8 bytes (sizeof)
/*0x318*/     union _LARGE_INTEGER StartTime;                        // 4 elements, 0x8 bytes (sizeof)
/*0x320*/     VOID*        LogFileHandle;
/*0x328*/     INT64        BufferSequenceNumber;
              union                                                  // 2 elements, 0x4 bytes (sizeof)
              {
/*0x330*/         ULONG32      Flags;
                  struct                                             // 17 elements, 0x4 bytes (sizeof)
                  {
/*0x330*/             ULONG32      Persistent : 1;                   // 0 BitPosition
/*0x330*/             ULONG32      AutoLogger : 1;                   // 1 BitPosition
/*0x330*/             ULONG32      FsReady : 1;                      // 2 BitPosition
/*0x330*/             ULONG32      RealTime : 1;                     // 3 BitPosition
/*0x330*/             ULONG32      Wow : 1;                          // 4 BitPosition
/*0x330*/             ULONG32      KernelTrace : 1;                  // 5 BitPosition
/*0x330*/             ULONG32      NoMoreEnable : 1;                 // 6 BitPosition
/*0x330*/             ULONG32      StackTracing : 1;                 // 7 BitPosition
/*0x330*/             ULONG32      ErrorLogged : 1;                  // 8 BitPosition
/*0x330*/             ULONG32      RealtimeLoggerContextFreed : 1;   // 9 BitPosition
/*0x330*/             ULONG32      PebsTracing : 1;                  // 10 BitPosition
/*0x330*/             ULONG32      PmcCounters : 1;                  // 11 BitPosition
/*0x330*/             ULONG32      PageAlignBuffers : 1;             // 12 BitPosition
/*0x330*/             ULONG32      SpareFlags1 : 3;                  // 13 BitPosition
/*0x330*/             ULONG32      SystemLoggerIndex : 8;            // 16 BitPosition
/*0x330*/             ULONG32      StackCaching : 1;                 // 24 BitPosition
/*0x330*/             ULONG32      SpareFlags2 : 7;                  // 25 BitPosition
                  };
              };
              union                                                  // 2 elements, 0x4 bytes (sizeof)
              {
/*0x334*/         ULONG32      RequestFlag;
                  struct                                             // 12 elements, 0x4 bytes (sizeof)
                  {
/*0x334*/             ULONG32      RequestNewFie : 1;                // 0 BitPosition
/*0x334*/             ULONG32      RequestUpdateFile : 1;            // 1 BitPosition
/*0x334*/             ULONG32      RequestFlush : 1;                 // 2 BitPosition
/*0x334*/             ULONG32      RequestDisableRealtime : 1;       // 3 BitPosition
/*0x334*/             ULONG32      RequestDisconnectConsumer : 1;    // 4 BitPosition
/*0x334*/             ULONG32      RequestConnectConsumer : 1;       // 5 BitPosition
/*0x334*/             ULONG32      RequestNotifyConsumer : 1;        // 6 BitPosition
/*0x334*/             ULONG32      RequestUpdateHeader : 1;          // 7 BitPosition
/*0x334*/             ULONG32      RequestDefferdFlush : 1;          // 8 BitPosition
/*0x334*/             ULONG32      RequestDefferdFlushTimer : 1;     // 9 BitPosition
/*0x334*/             ULONG32      RequestFlushTimer : 1;            // 10 BitPosition
/*0x334*/             ULONG32      SpareRequestFlags : 21;           // 11 BitPosition
                  };
              };
/*0x338*/     struct _RTL_BITMAP HookIdMap;                          // 2 elements, 0x10 bytes (sizeof)
/*0x348*/     struct _ETW_STACK_CACHE* StackCache;
/*0x350*/     struct _ETW_PMC_SUPPORT* PmcData;
/*0x358*/     struct _LIST_ENTRY ProviderBinaryList;                 // 2 elements, 0x10 bytes (sizeof)
/*0x368*/     struct _LIST_ENTRY WinRtProviderBinaryList;            // 2 elements, 0x10 bytes (sizeof)
/*0x378*/     struct _WMI_BUFFER_HEADER** ScratchArray;
          }WMI_LOGGER_CONTEXT, *PWMI_LOGGER_CONTEXT;

