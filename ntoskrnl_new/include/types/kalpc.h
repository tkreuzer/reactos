          typedef struct _KALPC_HANDLE_DATA                        // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flags;
/*0x004*/     ULONG32      ObjectType;
/*0x008*/     struct _OB_DUPLICATE_OBJECT_STATE* DuplicateContext;
          }KALPC_HANDLE_DATA, *PKALPC_HANDLE_DATA;

          typedef struct _KALPC_MESSAGE                           // 23 elements, 0x108 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Entry;                           // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _ALPC_PORT* PortQueue;
/*0x018*/     struct _ALPC_PORT* OwnerPort;
/*0x020*/     struct _ETHREAD* WaitingThread;
              union                                               // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                          // 12 elements, 0x4 bytes (sizeof)
                  {
/*0x028*/             ULONG32      QueueType : 2;                 // 0 BitPosition
/*0x028*/             ULONG32      QueuePortType : 4;             // 2 BitPosition
/*0x028*/             ULONG32      Canceled : 1;                  // 6 BitPosition
/*0x028*/             ULONG32      Ready : 1;                     // 7 BitPosition
/*0x028*/             ULONG32      ReleaseMessage : 1;            // 8 BitPosition
/*0x028*/             ULONG32      SharedQuota : 1;               // 9 BitPosition
/*0x028*/             ULONG32      ReplyWaitReply : 1;            // 10 BitPosition
/*0x028*/             ULONG32      OwnerPortReference : 1;        // 11 BitPosition
/*0x028*/             ULONG32      ReserveReference : 1;          // 12 BitPosition
/*0x028*/             ULONG32      ReceiverReference : 1;         // 13 BitPosition
/*0x028*/             ULONG32      ViewAttributeRetrieved : 1;    // 14 BitPosition
/*0x028*/             ULONG32      InDispatch : 1;                // 15 BitPosition
                  }s1;
/*0x028*/         ULONG32      State;
              }u1;
/*0x02C*/     LONG32       SequenceNo;
              union                                               // 2 elements, 0x8 bytes (sizeof)
              {
/*0x030*/         struct _EPROCESS* QuotaProcess;
/*0x030*/         VOID*        QuotaBlock;
              };
/*0x038*/     struct _ALPC_PORT* CancelSequencePort;
/*0x040*/     struct _ALPC_PORT* CancelQueuePort;
/*0x048*/     LONG32       CancelSequenceNo;
/*0x04C*/     UINT8        _PADDING0_[0x4];
/*0x050*/     struct _LIST_ENTRY CancelListEntry;                 // 2 elements, 0x10 bytes (sizeof)
/*0x060*/     struct _KALPC_RESERVE* Reserve;
/*0x068*/     struct _KALPC_MESSAGE_ATTRIBUTES MessageAttributes; // 7 elements, 0x38 bytes (sizeof)
/*0x0A0*/     VOID*        DataUserVa;
/*0x0A8*/     VOID*        DataSystemVa;
/*0x0B0*/     struct _ALPC_COMMUNICATION_INFO* CommunicationInfo;
/*0x0B8*/     struct _ALPC_PORT* ConnectionPort;
/*0x0C0*/     struct _ETHREAD* ServerThread;
/*0x0C8*/     VOID*        WakeReference;
/*0x0D0*/     VOID*        ExtensionBuffer;
/*0x0D8*/     UINT64       ExtensionBufferSize;
/*0x0E0*/     struct _PORT_MESSAGE PortMessage;                   // 7 elements, 0x28 bytes (sizeof)
          }KALPC_MESSAGE, *PKALPC_MESSAGE;

          typedef struct _KALPC_MESSAGE_ATTRIBUTES       // 7 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     VOID*        ClientContext;
/*0x008*/     VOID*        ServerContext;
/*0x010*/     VOID*        PortContext;
/*0x018*/     VOID*        CancelPortContext;
/*0x020*/     struct _KALPC_SECURITY_DATA* SecurityData;
/*0x028*/     struct _KALPC_VIEW* View;
/*0x030*/     struct _KALPC_HANDLE_DATA* HandleData;
          }KALPC_MESSAGE_ATTRIBUTES, *PKALPC_MESSAGE_ATTRIBUTES;

          typedef struct _KALPC_REGION            // 10 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY RegionListEntry; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _KALPC_SECTION* Section;
/*0x018*/     UINT64       Offset;
/*0x020*/     UINT64       Size;
/*0x028*/     UINT64       ViewSize;
              union                               // 1 elements, 0x4 bytes (sizeof)
              {
                  struct                          // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x030*/             ULONG32      Secure : 1;    // 0 BitPosition
                  }s1;
              }u1;
/*0x034*/     ULONG32      NumberOfViews;
/*0x038*/     struct _LIST_ENTRY ViewListHead;    // 2 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _KALPC_VIEW* ReadOnlyView;
/*0x050*/     struct _KALPC_VIEW* ReadWriteView;
          }KALPC_REGION, *PKALPC_REGION;

          typedef struct _KALPC_RESERVE               // 5 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _ALPC_PORT* OwnerPort;
/*0x008*/     struct _ALPC_HANDLE_TABLE* HandleTable;
/*0x010*/     VOID*        Handle;
/*0x018*/     struct _KALPC_MESSAGE* Message;
/*0x020*/     LONG32       Active;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }KALPC_RESERVE, *PKALPC_RESERVE;

          typedef struct _KALPC_SECTION               // 9 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     VOID*        SectionObject;
/*0x008*/     UINT64       Size;
/*0x010*/     struct _ALPC_HANDLE_TABLE* HandleTable;
/*0x018*/     VOID*        SectionHandle;
/*0x020*/     struct _EPROCESS* OwnerProcess;
/*0x028*/     struct _ALPC_PORT* OwnerPort;
              union                                   // 1 elements, 0x4 bytes (sizeof)
              {
                  struct                              // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x030*/             ULONG32      Internal : 1;      // 0 BitPosition
/*0x030*/             ULONG32      Secure : 1;        // 1 BitPosition
                  }s1;
              }u1;
/*0x034*/     ULONG32      NumberOfRegions;
/*0x038*/     struct _LIST_ENTRY RegionListHead;      // 2 elements, 0x10 bytes (sizeof)
          }KALPC_SECTION, *PKALPC_SECTION;

          typedef struct _KALPC_SECURITY_DATA                  // 6 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     struct _ALPC_HANDLE_TABLE* HandleTable;
/*0x008*/     VOID*        ContextHandle;
/*0x010*/     struct _EPROCESS* OwningProcess;
/*0x018*/     struct _ALPC_PORT* OwnerPort;
/*0x020*/     struct _SECURITY_CLIENT_CONTEXT DynamicSecurity; // 6 elements, 0x48 bytes (sizeof)
              union                                            // 1 elements, 0x4 bytes (sizeof)
              {
                  struct                                       // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x068*/             ULONG32      Revoked : 1;                // 0 BitPosition
/*0x068*/             ULONG32      Impersonated : 1;           // 1 BitPosition
                  }s1;
              }u1;
          }KALPC_SECURITY_DATA, *PKALPC_SECURITY_DATA;

          typedef struct _KALPC_VIEW                   // 11 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ViewListEntry;        // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _KALPC_REGION* Region;
/*0x018*/     struct _ALPC_PORT* OwnerPort;
/*0x020*/     struct _EPROCESS* OwnerProcess;
/*0x028*/     VOID*        Address;
/*0x030*/     UINT64       Size;
/*0x038*/     VOID*        SecureViewHandle;
/*0x040*/     VOID*        WriteAccessHandle;
              union                                    // 1 elements, 0x4 bytes (sizeof)
              {
                  struct                               // 3 elements, 0x4 bytes (sizeof)
                  {
/*0x048*/             ULONG32      WriteAccess : 1;    // 0 BitPosition
/*0x048*/             ULONG32      AutoRelease : 1;    // 1 BitPosition
/*0x048*/             ULONG32      ForceUnlink : 1;    // 2 BitPosition
                  }s1;
              }u1;
/*0x04C*/     ULONG32      NumberOfOwnerMessages;
/*0x050*/     struct _LIST_ENTRY ProcessViewListEntry; // 2 elements, 0x10 bytes (sizeof)
          }KALPC_VIEW, *PKALPC_VIEW;

