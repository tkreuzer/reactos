
          typedef struct _LPCP_MESSAGE                     // 7 elements, 0x50 bytes (sizeof)
          {
              union                                        // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         struct _LIST_ENTRY Entry;                // 2 elements, 0x10 bytes (sizeof)
                  struct                                   // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             struct _SINGLE_LIST_ENTRY FreeEntry; // 1 elements, 0x8 bytes (sizeof)
/*0x008*/             ULONG32      Reserved0;
/*0x00C*/             UINT8        _PADDING0_[0x4];
                  };
              };
/*0x010*/     VOID*        SenderPort;
/*0x018*/     struct _ETHREAD* RepliedToThread;
/*0x020*/     VOID*        PortContext;
/*0x028*/     struct _PORT_MESSAGE Request;                // 7 elements, 0x28 bytes (sizeof)
          }LPCP_MESSAGE, *PLPCP_MESSAGE;

          typedef struct _LPCP_NONPAGED_PORT_QUEUE   // 2 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _KSEMAPHORE Semaphore;          // 2 elements, 0x20 bytes (sizeof)
/*0x020*/     struct _LPCP_PORT_OBJECT* BackPointer;
          }LPCP_NONPAGED_PORT_QUEUE, *PLPCP_NONPAGED_PORT_QUEUE;

          typedef struct _LPCP_PORT_OBJECT                     // 18 elements, 0x100 bytes (sizeof)
          {
/*0x000*/     struct _LPCP_PORT_OBJECT* ConnectionPort;
/*0x008*/     struct _LPCP_PORT_OBJECT* ConnectedPort;
/*0x010*/     struct _LPCP_PORT_QUEUE MsgQueue;                // 3 elements, 0x20 bytes (sizeof)
/*0x030*/     struct _CLIENT_ID Creator;                       // 2 elements, 0x10 bytes (sizeof)
/*0x040*/     VOID*        ClientSectionBase;
/*0x048*/     VOID*        ServerSectionBase;
/*0x050*/     VOID*        PortContext;
/*0x058*/     struct _ETHREAD* ClientThread;
/*0x060*/     struct _SECURITY_QUALITY_OF_SERVICE SecurityQos; // 4 elements, 0xC bytes (sizeof)
/*0x06C*/     UINT8        _PADDING0_[0x4];
/*0x070*/     struct _SECURITY_CLIENT_CONTEXT StaticSecurity;  // 6 elements, 0x48 bytes (sizeof)
/*0x0B8*/     struct _LIST_ENTRY LpcReplyChainHead;            // 2 elements, 0x10 bytes (sizeof)
/*0x0C8*/     struct _LIST_ENTRY LpcDataInfoChainHead;         // 2 elements, 0x10 bytes (sizeof)
              union                                            // 2 elements, 0x8 bytes (sizeof)
              {
/*0x0D8*/         struct _EPROCESS* ServerProcess;
/*0x0D8*/         struct _EPROCESS* MappingProcess;
              };
/*0x0E0*/     UINT16       MaxMessageLength;
/*0x0E2*/     UINT16       MaxConnectionInfoLength;
/*0x0E4*/     ULONG32      Flags;
/*0x0E8*/     struct _KEVENT WaitEvent;                        // 1 elements, 0x18 bytes (sizeof)
          }LPCP_PORT_OBJECT, *PLPCP_PORT_OBJECT;

          typedef struct _LPCP_PORT_QUEUE                          // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LPCP_NONPAGED_PORT_QUEUE* NonPagedPortQueue;
/*0x008*/     struct _KSEMAPHORE* Semaphore;
/*0x010*/     struct _LIST_ENTRY ReceiveHead;                      // 2 elements, 0x10 bytes (sizeof)
          }LPCP_PORT_QUEUE, *PLPCP_PORT_QUEUE;
