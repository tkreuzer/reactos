         typedef struct _ALPC_COMMUNICATION_INFO         // 5 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _ALPC_PORT* ConnectionPort;
/*0x008*/     struct _ALPC_PORT* ServerCommunicationPort;
/*0x010*/     struct _ALPC_PORT* ClientCommunicationPort;
/*0x018*/     struct _LIST_ENTRY CommunicationList;       // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _ALPC_HANDLE_TABLE HandleTable;      // 4 elements, 0x18 bytes (sizeof)
          }ALPC_COMMUNICATION_INFO, *PALPC_COMMUNICATION_INFO;

          typedef struct _ALPC_COMPLETION_LIST             // 21 elements, 0xA0 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Entry;                    // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _EPROCESS* OwnerProcess;
/*0x018*/     struct _EX_PUSH_LOCK CompletionListLock;     // 7 elements, 0x8 bytes (sizeof)
/*0x020*/     struct _MDL* Mdl;
/*0x028*/     VOID*        UserVa;
/*0x030*/     VOID*        UserLimit;
/*0x038*/     VOID*        DataUserVa;
/*0x040*/     VOID*        SystemVa;
/*0x048*/     UINT64       TotalSize;
/*0x050*/     struct _ALPC_COMPLETION_LIST_HEADER* Header;
/*0x058*/     VOID*        List;
/*0x060*/     UINT64       ListSize;
/*0x068*/     VOID*        Bitmap;
/*0x070*/     UINT64       BitmapSize;
/*0x078*/     VOID*        Data;
/*0x080*/     UINT64       DataSize;
/*0x088*/     ULONG32      BitmapLimit;
/*0x08C*/     ULONG32      BitmapNextHint;
/*0x090*/     ULONG32      ConcurrencyCount;
/*0x094*/     ULONG32      AttributeFlags;
/*0x098*/     ULONG32      AttributeSize;
/*0x09C*/     UINT8        _PADDING0_[0x4];
          }ALPC_COMPLETION_LIST, *PALPC_COMPLETION_LIST;

          typedef struct _ALPC_COMPLETION_LIST_HEADER   // 18 elements, 0x180 bytes (sizeof)
          {
/*0x000*/     UINT64       StartMagic;
/*0x008*/     ULONG32      TotalSize;
/*0x00C*/     ULONG32      ListOffset;
/*0x010*/     ULONG32      ListSize;
/*0x014*/     ULONG32      BitmapOffset;
/*0x018*/     ULONG32      BitmapSize;
/*0x01C*/     ULONG32      DataOffset;
/*0x020*/     ULONG32      DataSize;
/*0x024*/     ULONG32      AttributeFlags;
/*0x028*/     ULONG32      AttributeSize;
/*0x02C*/     UINT8        _PADDING0_[0x14];
/*0x040*/     struct _ALPC_COMPLETION_LIST_STATE State; // 1 elements, 0x8 bytes (sizeof)
/*0x048*/     ULONG32      LastMessageId;
/*0x04C*/     ULONG32      LastCallbackId;
/*0x050*/     UINT8        _PADDING1_[0x30];
/*0x080*/     ULONG32      PostCount;
/*0x084*/     UINT8        _PADDING2_[0x3C];
/*0x0C0*/     ULONG32      ReturnCount;
/*0x0C4*/     UINT8        _PADDING3_[0x3C];
/*0x100*/     ULONG32      LogSequenceNumber;
/*0x104*/     UINT8        _PADDING4_[0x3C];
/*0x140*/     struct _RTL_SRWLOCK UserLock;             // 7 elements, 0x8 bytes (sizeof)
/*0x148*/     UINT64       EndMagic;
/*0x150*/     UINT8        _PADDING5_[0x30];
          }ALPC_COMPLETION_LIST_HEADER, *PALPC_COMPLETION_LIST_HEADER;

          typedef struct _ALPC_COMPLETION_LIST_STATE       // 1 elements, 0x8 bytes (sizeof)
          {
              union                                        // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                                   // 3 elements, 0x8 bytes (sizeof)
                  {
/*0x000*/             UINT64       Head : 24;              // 0 BitPosition
/*0x000*/             UINT64       Tail : 24;              // 24 BitPosition
/*0x000*/             UINT64       ActiveThreadCount : 16; // 48 BitPosition
                  }s1;
/*0x000*/         UINT64       Value;
              }u1;
          }ALPC_COMPLETION_LIST_STATE, *PALPC_COMPLETION_LIST_STATE;

          typedef struct _ALPC_COMPLETION_PACKET_LOOKASIDE             // 10 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     UINT64       Lock;
/*0x008*/     ULONG32      Size;
/*0x00C*/     ULONG32      ActiveCount;
/*0x010*/     ULONG32      PendingNullCount;
/*0x014*/     ULONG32      PendingCheckCompletionListCount;
/*0x018*/     ULONG32      PendingDelete;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     struct _SINGLE_LIST_ENTRY FreeListHead;                  // 1 elements, 0x8 bytes (sizeof)
/*0x028*/     VOID*        CompletionPort;
/*0x030*/     VOID*        CompletionKey;
/*0x038*/     struct _ALPC_COMPLETION_PACKET_LOOKASIDE_ENTRY Entry[1];
          }ALPC_COMPLETION_PACKET_LOOKASIDE, *PALPC_COMPLETION_PACKET_LOOKASIDE;

          typedef struct _ALPC_COMPLETION_PACKET_LOOKASIDE_ENTRY   // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _SINGLE_LIST_ENTRY ListEntry;                 // 1 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _IO_MINI_COMPLETION_PACKET_USER* Packet;
/*0x010*/     struct _ALPC_COMPLETION_PACKET_LOOKASIDE* Lookaside;
          }ALPC_COMPLETION_PACKET_LOOKASIDE_ENTRY, *PALPC_COMPLETION_PACKET_LOOKASIDE_ENTRY;

         typedef struct _ALPC_DISPATCH_CONTEXT                   // 11 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _ALPC_PORT* PortObject;
/*0x008*/     struct _KALPC_MESSAGE* Message;
/*0x010*/     struct _ALPC_COMMUNICATION_INFO* CommunicationInfo;
/*0x018*/     struct _ETHREAD* TargetThread;
/*0x020*/     struct _ALPC_PORT* TargetPort;
/*0x028*/     ULONG32      Flags;
/*0x02C*/     UINT16       TotalLength;
/*0x02E*/     UINT16       Type;
/*0x030*/     UINT16       DataInfoOffset;
/*0x032*/     UINT8        SignalCompletion;
/*0x033*/     UINT8        PostedToCompletionList;
/*0x034*/     UINT8        _PADDING0_[0x4];
          }ALPC_DISPATCH_CONTEXT, *PALPC_DISPATCH_CONTEXT;

          typedef struct _ALPC_HANDLE_ENTRY // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     VOID*        Object;
          }ALPC_HANDLE_ENTRY, *PALPC_HANDLE_ENTRY;

          typedef struct _ALPC_HANDLE_TABLE       // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _ALPC_HANDLE_ENTRY* Handles;
/*0x008*/     ULONG32      TotalHandles;
/*0x00C*/     ULONG32      Flags;
/*0x010*/     struct _EX_PUSH_LOCK Lock;          // 7 elements, 0x8 bytes (sizeof)
          }ALPC_HANDLE_TABLE, *PALPC_HANDLE_TABLE;

          typedef struct _ALPC_MESSAGE_ATTRIBUTES // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      AllocatedAttributes;
/*0x004*/     ULONG32      ValidAttributes;
          }ALPC_MESSAGE_ATTRIBUTES, *PALPC_MESSAGE_ATTRIBUTES;

          typedef struct _ALPC_MESSAGE_ZONE // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _MDL* Mdl;
/*0x008*/     VOID*        UserVa;
/*0x010*/     VOID*        UserLimit;
/*0x018*/     VOID*        SystemVa;
/*0x020*/     VOID*        SystemLimit;
/*0x028*/     UINT64       Size;
          }ALPC_MESSAGE_ZONE, *PALPC_MESSAGE_ZONE;

          typedef struct _ALPC_PORT                                                // 36 elements, 0x1B8 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY PortListEntry;                                    // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _ALPC_COMMUNICATION_INFO* CommunicationInfo;
/*0x018*/     struct _EPROCESS* OwnerProcess;
/*0x020*/     VOID*        CompletionPort;
/*0x028*/     VOID*        CompletionKey;
/*0x030*/     struct _ALPC_COMPLETION_PACKET_LOOKASIDE* CompletionPacketLookaside;
/*0x038*/     VOID*        PortContext;
/*0x040*/     struct _SECURITY_CLIENT_CONTEXT StaticSecurity;                      // 6 elements, 0x48 bytes (sizeof)
/*0x088*/     struct _EX_PUSH_LOCK IncomingQueueLock;                              // 7 elements, 0x8 bytes (sizeof)
/*0x090*/     struct _LIST_ENTRY MainQueue;                                        // 2 elements, 0x10 bytes (sizeof)
/*0x0A0*/     struct _LIST_ENTRY LargeMessageQueue;                                // 2 elements, 0x10 bytes (sizeof)
/*0x0B0*/     struct _EX_PUSH_LOCK PendingQueueLock;                               // 7 elements, 0x8 bytes (sizeof)
/*0x0B8*/     struct _LIST_ENTRY PendingQueue;                                     // 2 elements, 0x10 bytes (sizeof)
/*0x0C8*/     struct _EX_PUSH_LOCK WaitQueueLock;                                  // 7 elements, 0x8 bytes (sizeof)
/*0x0D0*/     struct _LIST_ENTRY WaitQueue;                                        // 2 elements, 0x10 bytes (sizeof)
              union                                                                // 2 elements, 0x8 bytes (sizeof)
              {
/*0x0E0*/         struct _KSEMAPHORE* Semaphore;
/*0x0E0*/         struct _KEVENT* DummyEvent;
              };
/*0x0E8*/     struct _ALPC_PORT_ATTRIBUTES PortAttributes;                         // 10 elements, 0x48 bytes (sizeof)
/*0x130*/     struct _EX_PUSH_LOCK ResourceListLock;                               // 7 elements, 0x8 bytes (sizeof)
/*0x138*/     struct _LIST_ENTRY ResourceListHead;                                 // 2 elements, 0x10 bytes (sizeof)
/*0x148*/     struct _EX_PUSH_LOCK PortObjectLock;                                 // 7 elements, 0x8 bytes (sizeof)
/*0x150*/     struct _ALPC_COMPLETION_LIST* CompletionList;
/*0x158*/     struct _ALPC_MESSAGE_ZONE* MessageZone;
/*0x160*/     struct _CALLBACK_OBJECT* CallbackObject;
/*0x168*/     VOID*        CallbackContext;
/*0x170*/     struct _LIST_ENTRY CanceledQueue;                                    // 2 elements, 0x10 bytes (sizeof)
/*0x180*/     LONG32       SequenceNo;
              union                                                                // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                                           // 16 elements, 0x4 bytes (sizeof)
                  {
/*0x184*/             ULONG32      Initialized : 1;                                // 0 BitPosition
/*0x184*/             ULONG32      Type : 2;                                       // 1 BitPosition
/*0x184*/             ULONG32      ConnectionPending : 1;                          // 3 BitPosition
/*0x184*/             ULONG32      ConnectionRefused : 1;                          // 4 BitPosition
/*0x184*/             ULONG32      Disconnected : 1;                               // 5 BitPosition
/*0x184*/             ULONG32      Closed : 1;                                     // 6 BitPosition
/*0x184*/             ULONG32      NoFlushOnClose : 1;                             // 7 BitPosition
/*0x184*/             ULONG32      ReturnExtendedInfo : 1;                         // 8 BitPosition
/*0x184*/             ULONG32      Waitable : 1;                                   // 9 BitPosition
/*0x184*/             ULONG32      DynamicSecurity : 1;                            // 10 BitPosition
/*0x184*/             ULONG32      Wow64CompletionList : 1;                        // 11 BitPosition
/*0x184*/             ULONG32      Lpc : 1;                                        // 12 BitPosition
/*0x184*/             ULONG32      LpcToLpc : 1;                                   // 13 BitPosition
/*0x184*/             ULONG32      HasCompletionList : 1;                          // 14 BitPosition
/*0x184*/             ULONG32      HadCompletionList : 1;                          // 15 BitPosition
/*0x184*/             ULONG32      EnableCompletionList : 1;                       // 16 BitPosition
                  }s1;
/*0x184*/         ULONG32      State;
              }u1;
/*0x188*/     struct _ALPC_PORT* TargetQueuePort;
/*0x190*/     struct _ALPC_PORT* TargetSequencePort;
/*0x198*/     struct _KALPC_MESSAGE* CachedMessage;
/*0x1A0*/     ULONG32      MainQueueLength;
/*0x1A4*/     ULONG32      LargeMessageQueueLength;
/*0x1A8*/     ULONG32      PendingQueueLength;
/*0x1AC*/     ULONG32      CanceledQueueLength;
/*0x1B0*/     ULONG32      WaitQueueLength;
/*0x1B4*/     UINT8        _PADDING0_[0x4];
          }ALPC_PORT, *PALPC_PORT;

          typedef struct _ALPC_PORT_ATTRIBUTES                 // 10 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flags;
/*0x004*/     struct _SECURITY_QUALITY_OF_SERVICE SecurityQos; // 4 elements, 0xC bytes (sizeof)
/*0x010*/     UINT64       MaxMessageLength;
/*0x018*/     UINT64       MemoryBandwidth;
/*0x020*/     UINT64       MaxPoolUsage;
/*0x028*/     UINT64       MaxSectionSize;
/*0x030*/     UINT64       MaxViewSize;
/*0x038*/     UINT64       MaxTotalSectionSize;
/*0x040*/     ULONG32      DupObjectTypes;
/*0x044*/     ULONG32      Reserved;
          }ALPC_PORT_ATTRIBUTES, *PALPC_PORT_ATTRIBUTES;

          typedef struct _ALPC_PROCESS_CONTEXT  // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK Lock;        // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _LIST_ENTRY ViewListHead;  // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     UINT64       PagedPoolQuotaCache;
          }ALPC_PROCESS_CONTEXT, *PALPC_PROCESS_CONTEXT;

