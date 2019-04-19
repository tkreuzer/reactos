          typedef struct _NT_TIB                                    // 8 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _EXCEPTION_REGISTRATION_RECORD* ExceptionList;
/*0x008*/     VOID*        StackBase;
/*0x010*/     VOID*        StackLimit;
/*0x018*/     VOID*        SubSystemTib;
              union                                                 // 2 elements, 0x8 bytes (sizeof)
              {
/*0x020*/         VOID*        FiberData;
/*0x020*/         ULONG32      Version;
              };
/*0x028*/     VOID*        ArbitraryUserPointer;
/*0x030*/     struct _NT_TIB* Self;
          }NT_TIB, *PNT_TIB;

          typedef struct _NT_TIB32               // 8 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      ExceptionList;
/*0x004*/     ULONG32      StackBase;
/*0x008*/     ULONG32      StackLimit;
/*0x00C*/     ULONG32      SubSystemTib;
              union                              // 2 elements, 0x4 bytes (sizeof)
              {
/*0x010*/         ULONG32      FiberData;
/*0x010*/         ULONG32      Version;
              };
/*0x014*/     ULONG32      ArbitraryUserPointer;
/*0x018*/     ULONG32      Self;
          }NT_TIB32, *PNT_TIB32;

          typedef struct _NT_TIB64               // 8 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     UINT64       ExceptionList;
/*0x008*/     UINT64       StackBase;
/*0x010*/     UINT64       StackLimit;
/*0x018*/     UINT64       SubSystemTib;
              union                              // 2 elements, 0x8 bytes (sizeof)
              {
/*0x020*/         UINT64       FiberData;
/*0x020*/         ULONG32      Version;
              };
/*0x028*/     UINT64       ArbitraryUserPointer;
/*0x030*/     UINT64       Self;
          }NT_TIB64, *PNT_TIB64;

          typedef struct _CONTEXT                    // 64 elements, 0x4D0 bytes (sizeof)
          {
/*0x000*/     UINT64       P1Home;
/*0x008*/     UINT64       P2Home;
/*0x010*/     UINT64       P3Home;
/*0x018*/     UINT64       P4Home;
/*0x020*/     UINT64       P5Home;
/*0x028*/     UINT64       P6Home;
/*0x030*/     ULONG32      ContextFlags;
/*0x034*/     ULONG32      MxCsr;
/*0x038*/     UINT16       SegCs;
/*0x03A*/     UINT16       SegDs;
/*0x03C*/     UINT16       SegEs;
/*0x03E*/     UINT16       SegFs;
/*0x040*/     UINT16       SegGs;
/*0x042*/     UINT16       SegSs;
/*0x044*/     ULONG32      EFlags;
/*0x048*/     UINT64       Dr0;
/*0x050*/     UINT64       Dr1;
/*0x058*/     UINT64       Dr2;
/*0x060*/     UINT64       Dr3;
/*0x068*/     UINT64       Dr6;
/*0x070*/     UINT64       Dr7;
/*0x078*/     UINT64       Rax;
/*0x080*/     UINT64       Rcx;
/*0x088*/     UINT64       Rdx;
/*0x090*/     UINT64       Rbx;
/*0x098*/     UINT64       Rsp;
/*0x0A0*/     UINT64       Rbp;
/*0x0A8*/     UINT64       Rsi;
/*0x0B0*/     UINT64       Rdi;
/*0x0B8*/     UINT64       R8;
/*0x0C0*/     UINT64       R9;
/*0x0C8*/     UINT64       R10;
/*0x0D0*/     UINT64       R11;
/*0x0D8*/     UINT64       R12;
/*0x0E0*/     UINT64       R13;
/*0x0E8*/     UINT64       R14;
/*0x0F0*/     UINT64       R15;
/*0x0F8*/     UINT64       Rip;
              union                                  // 2 elements, 0x200 bytes (sizeof)
              {
/*0x100*/         struct _XSAVE_FORMAT FltSave;      // 16 elements, 0x200 bytes (sizeof)
                  struct                             // 18 elements, 0x200 bytes (sizeof)
                  {
/*0x100*/             struct _M128A Header[2];
/*0x120*/             struct _M128A Legacy[8];
/*0x1A0*/             struct _M128A Xmm0;            // 2 elements, 0x10 bytes (sizeof)
/*0x1B0*/             struct _M128A Xmm1;            // 2 elements, 0x10 bytes (sizeof)
/*0x1C0*/             struct _M128A Xmm2;            // 2 elements, 0x10 bytes (sizeof)
/*0x1D0*/             struct _M128A Xmm3;            // 2 elements, 0x10 bytes (sizeof)
/*0x1E0*/             struct _M128A Xmm4;            // 2 elements, 0x10 bytes (sizeof)
/*0x1F0*/             struct _M128A Xmm5;            // 2 elements, 0x10 bytes (sizeof)
/*0x200*/             struct _M128A Xmm6;            // 2 elements, 0x10 bytes (sizeof)
/*0x210*/             struct _M128A Xmm7;            // 2 elements, 0x10 bytes (sizeof)
/*0x220*/             struct _M128A Xmm8;            // 2 elements, 0x10 bytes (sizeof)
/*0x230*/             struct _M128A Xmm9;            // 2 elements, 0x10 bytes (sizeof)
/*0x240*/             struct _M128A Xmm10;           // 2 elements, 0x10 bytes (sizeof)
/*0x250*/             struct _M128A Xmm11;           // 2 elements, 0x10 bytes (sizeof)
/*0x260*/             struct _M128A Xmm12;           // 2 elements, 0x10 bytes (sizeof)
/*0x270*/             struct _M128A Xmm13;           // 2 elements, 0x10 bytes (sizeof)
/*0x280*/             struct _M128A Xmm14;           // 2 elements, 0x10 bytes (sizeof)
/*0x290*/             struct _M128A Xmm15;           // 2 elements, 0x10 bytes (sizeof)
/*0x2A0*/             UINT8        _PADDING0_[0x60];
                  };
              };
/*0x300*/     struct _M128A VectorRegister[26];
/*0x4A0*/     UINT64       VectorControl;
/*0x4A8*/     UINT64       DebugControl;
/*0x4B0*/     UINT64       LastBranchToRip;
/*0x4B8*/     UINT64       LastBranchFromRip;
/*0x4C0*/     UINT64       LastExceptionToRip;
/*0x4C8*/     UINT64       LastExceptionFromRip;
          }CONTEXT, *PCONTEXT;

          typedef struct _CONTEXT32_UPDATE // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      NumberEntries;
          }CONTEXT32_UPDATE, *PCONTEXT32_UPDATE;

          typedef struct _CPU_INFO // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Eax;
/*0x004*/     ULONG32      Ebx;
/*0x008*/     ULONG32      Ecx;
/*0x00C*/     ULONG32      Edx;
          }CPU_INFO, *PCPU_INFO;

          typedef struct _DISPATCHER_HEADER                           // 31 elements, 0x18 bytes (sizeof)
          {
              union                                                   // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                              // 4 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             UINT8        Type;
                      union                                           // 4 elements, 0x1 bytes (sizeof)
                      {
/*0x001*/                 UINT8        TimerControlFlags;
                          struct                                      // 5 elements, 0x1 bytes (sizeof)
                          {
/*0x001*/                     UINT8        Absolute : 1;              // 0 BitPosition
/*0x001*/                     UINT8        Wake : 1;                  // 1 BitPosition
/*0x001*/                     UINT8        Coalescable : 1;           // 2 BitPosition
/*0x001*/                     UINT8        KeepShifting : 1;          // 3 BitPosition
/*0x001*/                     UINT8        EncodedTolerableDelay : 4; // 4 BitPosition
                          };
/*0x001*/                 UINT8        Abandoned;
/*0x001*/                 UINT8        Signalling;
                      };
                      union                                           // 4 elements, 0x1 bytes (sizeof)
                      {
/*0x002*/                 UINT8        ThreadControlFlags;
                          struct                                      // 5 elements, 0x1 bytes (sizeof)
                          {
/*0x002*/                     UINT8        CycleProfiling : 1;        // 0 BitPosition
/*0x002*/                     UINT8        CounterProfiling : 1;      // 1 BitPosition
/*0x002*/                     UINT8        GroupScheduling : 1;       // 2 BitPosition
/*0x002*/                     UINT8        AffinitySet : 1;           // 3 BitPosition
/*0x002*/                     UINT8        Reserved : 4;              // 4 BitPosition
                          };
/*0x002*/                 UINT8        Hand;
/*0x002*/                 UINT8        Size;
                      };
                      union                                           // 5 elements, 0x1 bytes (sizeof)
                      {
/*0x003*/                 UINT8        TimerMiscFlags;
                          struct                                      // 3 elements, 0x1 bytes (sizeof)
                          {
/*0x003*/                     UINT8        Index : 6;                 // 0 BitPosition
/*0x003*/                     UINT8        Inserted : 1;              // 6 BitPosition
/*0x003*/                     UINT8        Expired : 1;               // 7 BitPosition
                          };
/*0x003*/                 UINT8        DebugActive;
                          struct                                      // 5 elements, 0x1 bytes (sizeof)
                          {
/*0x003*/                     UINT8        ActiveDR7 : 1;             // 0 BitPosition
/*0x003*/                     UINT8        Instrumented : 1;          // 1 BitPosition
/*0x003*/                     UINT8        Reserved2 : 4;             // 2 BitPosition
/*0x003*/                     UINT8        UmsScheduled : 1;          // 6 BitPosition
/*0x003*/                     UINT8        UmsPrimary : 1;            // 7 BitPosition
                          };
/*0x003*/                 UINT8        DpcActive;
                      };
                  };
/*0x000*/         LONG32       Lock;
              };
/*0x004*/     LONG32       SignalState;
/*0x008*/     struct _LIST_ENTRY WaitListHead;                        // 2 elements, 0x10 bytes (sizeof)
          }DISPATCHER_HEADER, *PDISPATCHER_HEADER;
          typedef struct _EXCEPTION_POINTERS             // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _EXCEPTION_RECORD* ExceptionRecord;
/*0x008*/     struct _CONTEXT* ContextRecord;
          }EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;

          typedef struct _EXCEPTION_RECORD               // 6 elements, 0x98 bytes (sizeof)
          {
/*0x000*/     LONG32       ExceptionCode;
/*0x004*/     ULONG32      ExceptionFlags;
/*0x008*/     struct _EXCEPTION_RECORD* ExceptionRecord;
/*0x010*/     VOID*        ExceptionAddress;
/*0x018*/     ULONG32      NumberParameters;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     UINT64       ExceptionInformation[15];
          }EXCEPTION_RECORD, *PEXCEPTION_RECORD;

          typedef struct _EXCEPTION_RECORD32         // 6 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     LONG32       ExceptionCode;
/*0x004*/     ULONG32      ExceptionFlags;
/*0x008*/     ULONG32      ExceptionRecord;
/*0x00C*/     ULONG32      ExceptionAddress;
/*0x010*/     ULONG32      NumberParameters;
/*0x014*/     ULONG32      ExceptionInformation[15];
          }EXCEPTION_RECORD32, *PEXCEPTION_RECORD32;

          typedef struct _EXCEPTION_RECORD64         // 7 elements, 0x98 bytes (sizeof)
          {
/*0x000*/     LONG32       ExceptionCode;
/*0x004*/     ULONG32      ExceptionFlags;
/*0x008*/     UINT64       ExceptionRecord;
/*0x010*/     UINT64       ExceptionAddress;
/*0x018*/     ULONG32      NumberParameters;
/*0x01C*/     ULONG32      __unusedAlignment;
/*0x020*/     UINT64       ExceptionInformation[15];
          }EXCEPTION_RECORD64, *PEXCEPTION_RECORD64;

          typedef struct _EXCEPTION_REGISTRATION_RECORD    // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _EXCEPTION_REGISTRATION_RECORD* Next;
/*0x008*/     FUNCT_015A_0159_Handler* Handler;
          }EXCEPTION_REGISTRATION_RECORD, *PEXCEPTION_REGISTRATION_RECORD;

          typedef struct _HARDWARE_PTE           // 16 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;            // 0 BitPosition
/*0x000*/     UINT64       Write : 1;            // 1 BitPosition
/*0x000*/     UINT64       Owner : 1;            // 2 BitPosition
/*0x000*/     UINT64       WriteThrough : 1;     // 3 BitPosition
/*0x000*/     UINT64       CacheDisable : 1;     // 4 BitPosition
/*0x000*/     UINT64       Accessed : 1;         // 5 BitPosition
/*0x000*/     UINT64       Dirty : 1;            // 6 BitPosition
/*0x000*/     UINT64       LargePage : 1;        // 7 BitPosition
/*0x000*/     UINT64       Global : 1;           // 8 BitPosition
/*0x000*/     UINT64       CopyOnWrite : 1;      // 9 BitPosition
/*0x000*/     UINT64       Prototype : 1;        // 10 BitPosition
/*0x000*/     UINT64       reserved0 : 1;        // 11 BitPosition
/*0x000*/     UINT64       PageFrameNumber : 36; // 12 BitPosition
/*0x000*/     UINT64       reserved1 : 4;        // 48 BitPosition
/*0x000*/     UINT64       SoftwareWsIndex : 11; // 52 BitPosition
/*0x000*/     UINT64       NoExecute : 1;        // 63 BitPosition
          }HARDWARE_PTE, *PHARDWARE_PTE;

          typedef struct _INVERTED_FUNCTION_TABLE                    // 5 elements, 0x1810 bytes (sizeof)
          {
/*0x000*/     ULONG32      CurrentSize;
/*0x004*/     ULONG32      MaximumSize;
/*0x008*/     ULONG32      Epoch;
/*0x00C*/     UINT8        Overflow;
/*0x00D*/     UINT8        _PADDING0_[0x3];
/*0x010*/     struct _INVERTED_FUNCTION_TABLE_ENTRY TableEntry[256];
          }INVERTED_FUNCTION_TABLE, *PINVERTED_FUNCTION_TABLE;

          typedef struct _INVERTED_FUNCTION_TABLE_ENTRY         // 5 elements, 0x18 bytes (sizeof)
          {
              union                                             // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         struct _RUNTIME_FUNCTION* FunctionTable;
/*0x000*/         struct _DYNAMIC_FUNCTION_TABLE* DynamicTable;
              };
/*0x008*/     VOID*        ImageBase;
/*0x010*/     ULONG32      SizeOfImage;
/*0x014*/     ULONG32      SizeOfTable;
          }INVERTED_FUNCTION_TABLE_ENTRY, *PINVERTED_FUNCTION_TABLE_ENTRY;

          typedef struct _KAFFINITY_ENUMERATION_CONTEXT // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _KAFFINITY_EX* Affinity;
/*0x008*/     UINT64       CurrentMask;
/*0x010*/     UINT16       CurrentIndex;
/*0x012*/     UINT8        _PADDING0_[0x6];
          }KAFFINITY_ENUMERATION_CONTEXT, *PKAFFINITY_ENUMERATION_CONTEXT;

          typedef struct _KAFFINITY_EX // 4 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     UINT16       Count;
/*0x002*/     UINT16       Size;
/*0x004*/     ULONG32      Reserved;
/*0x008*/     UINT64       Bitmap[8];
          }KAFFINITY_EX, *PKAFFINITY_EX;


          typedef struct _KAPC                                        // 17 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     UINT8        Type;
/*0x001*/     UINT8        SpareByte0;
/*0x002*/     UINT8        Size;
/*0x003*/     UINT8        SpareByte1;
/*0x004*/     ULONG32      SpareLong0;
/*0x008*/     struct _KTHREAD* Thread;
/*0x010*/     struct _LIST_ENTRY ApcListEntry;                        // 2 elements, 0x10 bytes (sizeof)
              union                                                   // 2 elements, 0x18 bytes (sizeof)
              {
                  struct                                              // 3 elements, 0x18 bytes (sizeof)
                  {
/*0x020*/             FUNCT_00AE_06AA_KernelRoutine* KernelRoutine;
/*0x028*/             FUNCT_00AE_06B8_RundownRoutine* RundownRoutine;
/*0x030*/             FUNCT_00AE_06B3_NormalRoutine* NormalRoutine;
                  };
/*0x020*/         VOID*        Reserved[3];
              };
/*0x038*/     VOID*        NormalContext;
/*0x040*/     VOID*        SystemArgument1;
/*0x048*/     VOID*        SystemArgument2;
/*0x050*/     CHAR         ApcStateIndex;
/*0x051*/     CHAR         ApcMode;
/*0x052*/     UINT8        Inserted;
/*0x053*/     UINT8        _PADDING0_[0x5];
          }KAPC, *PKAPC;

          typedef struct _KAPC_STATE             // 5 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ApcListHead[2];
/*0x020*/     struct _KPROCESS* Process;
/*0x028*/     UINT8        KernelApcInProgress;
/*0x029*/     UINT8        KernelApcPending;
/*0x02A*/     UINT8        UserApcPending;
/*0x02B*/     UINT8        _PADDING0_[0x5];
          }KAPC_STATE, *PKAPC_STATE;

          typedef struct _KDESCRIPTOR // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Pad[3];
/*0x006*/     UINT16       Limit;
/*0x008*/     VOID*        Base;
          }KDESCRIPTOR, *PKDESCRIPTOR;

          typedef struct _KDEVICE_QUEUE          // 7 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     INT16        Size;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _LIST_ENTRY DeviceListHead; // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     UINT64       Lock;
              union                              // 2 elements, 0x8 bytes (sizeof)
              {
/*0x020*/         UINT8        Busy;
                  struct                         // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x020*/             INT64        Reserved : 8; // 0 BitPosition
/*0x020*/             INT64        Hint : 56;    // 8 BitPosition
                  };
              };
          }KDEVICE_QUEUE, *PKDEVICE_QUEUE;

          typedef struct _KDEVICE_QUEUE_ENTRY     // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY DeviceListEntry; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      SortKey;
/*0x014*/     UINT8        Inserted;
/*0x015*/     UINT8        _PADDING0_[0x3];
          }KDEVICE_QUEUE_ENTRY, *PKDEVICE_QUEUE_ENTRY;

          typedef struct _KDPC                                  // 9 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     UINT8        Type;
/*0x001*/     UINT8        Importance;
/*0x002*/     UINT16       Number;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _LIST_ENTRY DpcListEntry;                  // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     FUNCT_00AE_0526_DeferredRoutine* DeferredRoutine;
/*0x020*/     VOID*        DeferredContext;
/*0x028*/     VOID*        SystemArgument1;
/*0x030*/     VOID*        SystemArgument2;
/*0x038*/     VOID*        DpcData;
          }KDPC, *PKDPC;

          typedef struct _KDPC_DATA           // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY DpcListHead; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT64       DpcLock;
/*0x018*/     LONG32       DpcQueueDepth;
/*0x01C*/     ULONG32      DpcCount;
          }KDPC_DATA, *PKDPC_DATA;

          typedef struct _KENLISTMENT                            // 26 elements, 0x1E0 bytes (sizeof)
          {
/*0x000*/     ULONG32      cookie;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _KTMOBJECT_NAMESPACE_LINK NamespaceLink;    // 2 elements, 0x28 bytes (sizeof)
/*0x030*/     struct _GUID EnlistmentId;                         // 4 elements, 0x10 bytes (sizeof)
/*0x040*/     struct _KMUTANT Mutex;                             // 5 elements, 0x38 bytes (sizeof)
/*0x078*/     struct _LIST_ENTRY NextSameTx;                     // 2 elements, 0x10 bytes (sizeof)
/*0x088*/     struct _LIST_ENTRY NextSameRm;                     // 2 elements, 0x10 bytes (sizeof)
/*0x098*/     struct _KRESOURCEMANAGER* ResourceManager;
/*0x0A0*/     struct _KTRANSACTION* Transaction;
/*0x0A8*/     enum _KENLISTMENT_STATE State;
/*0x0AC*/     ULONG32      Flags;
/*0x0B0*/     ULONG32      NotificationMask;
/*0x0B4*/     UINT8        _PADDING1_[0x4];
/*0x0B8*/     VOID*        Key;
/*0x0C0*/     ULONG32      KeyRefCount;
/*0x0C4*/     UINT8        _PADDING2_[0x4];
/*0x0C8*/     VOID*        RecoveryInformation;
/*0x0D0*/     ULONG32      RecoveryInformationLength;
/*0x0D4*/     UINT8        _PADDING3_[0x4];
/*0x0D8*/     VOID*        DynamicNameInformation;
/*0x0E0*/     ULONG32      DynamicNameInformationLength;
/*0x0E4*/     UINT8        _PADDING4_[0x4];
/*0x0E8*/     struct _KTMNOTIFICATION_PACKET* FinalNotification;
/*0x0F0*/     struct _KENLISTMENT* SupSubEnlistment;
/*0x0F8*/     VOID*        SupSubEnlHandle;
/*0x100*/     VOID*        SubordinateTxHandle;
/*0x108*/     struct _GUID CrmEnlistmentEnId;                    // 4 elements, 0x10 bytes (sizeof)
/*0x118*/     struct _GUID CrmEnlistmentTmId;                    // 4 elements, 0x10 bytes (sizeof)
/*0x128*/     struct _GUID CrmEnlistmentRmId;                    // 4 elements, 0x10 bytes (sizeof)
/*0x138*/     ULONG32      NextHistory;
/*0x13C*/     struct _KENLISTMENT_HISTORY History[20];
/*0x1DC*/     UINT8        _PADDING5_[0x4];
          }KENLISTMENT, *PKENLISTMENT;

          typedef struct _KENLISTMENT_HISTORY   // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Notification;
/*0x004*/     enum _KENLISTMENT_STATE NewState;
          }KENLISTMENT_HISTORY, *PKENLISTMENT_HISTORY;

          typedef struct _KERNEL_STACK_SEGMENT // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT64       StackBase;
/*0x008*/     UINT64       StackLimit;
/*0x010*/     UINT64       KernelStack;
/*0x018*/     UINT64       InitialStack;
          }KERNEL_STACK_SEGMENT, *PKERNEL_STACK_SEGMENT;

          typedef struct _KEVENT                // 1 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header; // 31 elements, 0x18 bytes (sizeof)
          }KEVENT, *PKEVENT;

          typedef struct _KEXCEPTION_FRAME // 30 elements, 0x140 bytes (sizeof)
          {
/*0x000*/     UINT64       P1Home;
/*0x008*/     UINT64       P2Home;
/*0x010*/     UINT64       P3Home;
/*0x018*/     UINT64       P4Home;
/*0x020*/     UINT64       P5;
/*0x028*/     UINT64       Spare1;
/*0x030*/     struct _M128A Xmm6;          // 2 elements, 0x10 bytes (sizeof)
/*0x040*/     struct _M128A Xmm7;          // 2 elements, 0x10 bytes (sizeof)
/*0x050*/     struct _M128A Xmm8;          // 2 elements, 0x10 bytes (sizeof)
/*0x060*/     struct _M128A Xmm9;          // 2 elements, 0x10 bytes (sizeof)
/*0x070*/     struct _M128A Xmm10;         // 2 elements, 0x10 bytes (sizeof)
/*0x080*/     struct _M128A Xmm11;         // 2 elements, 0x10 bytes (sizeof)
/*0x090*/     struct _M128A Xmm12;         // 2 elements, 0x10 bytes (sizeof)
/*0x0A0*/     struct _M128A Xmm13;         // 2 elements, 0x10 bytes (sizeof)
/*0x0B0*/     struct _M128A Xmm14;         // 2 elements, 0x10 bytes (sizeof)
/*0x0C0*/     struct _M128A Xmm15;         // 2 elements, 0x10 bytes (sizeof)
/*0x0D0*/     UINT64       TrapFrame;
/*0x0D8*/     UINT64       OutputBuffer;
/*0x0E0*/     UINT64       OutputLength;
/*0x0E8*/     UINT64       Spare2;
/*0x0F0*/     UINT64       MxCsr;
/*0x0F8*/     UINT64       Rbp;
/*0x100*/     UINT64       Rbx;
/*0x108*/     UINT64       Rdi;
/*0x110*/     UINT64       Rsi;
/*0x118*/     UINT64       R12;
/*0x120*/     UINT64       R13;
/*0x128*/     UINT64       R14;
/*0x130*/     UINT64       R15;
/*0x138*/     UINT64       Return;
          }KEXCEPTION_FRAME, *PKEXCEPTION_FRAME;

          typedef union _KEXECUTE_OPTIONS                           // 9 elements, 0x1 bytes (sizeof)
          {
              struct                                                // 8 elements, 0x1 bytes (sizeof)
              {
/*0x000*/         UINT8        ExecuteDisable : 1;                  // 0 BitPosition
/*0x000*/         UINT8        ExecuteEnable : 1;                   // 1 BitPosition
/*0x000*/         UINT8        DisableThunkEmulation : 1;           // 2 BitPosition
/*0x000*/         UINT8        Permanent : 1;                       // 3 BitPosition
/*0x000*/         UINT8        ExecuteDispatchEnable : 1;           // 4 BitPosition
/*0x000*/         UINT8        ImageDispatchEnable : 1;             // 5 BitPosition
/*0x000*/         UINT8        DisableExceptionChainValidation : 1; // 6 BitPosition
/*0x000*/         UINT8        Spare : 1;                           // 7 BitPosition
              };
/*0x000*/     UINT8        ExecuteOptions;
          }KEXECUTE_OPTIONS, *PKEXECUTE_OPTIONS;

          typedef struct _KGATE                 // 1 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header; // 31 elements, 0x18 bytes (sizeof)
          }KGATE, *PKGATE;

          typedef union _KGDTENTRY64                    // 8 elements, 0x10 bytes (sizeof)
          {
              struct                                    // 5 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         UINT16       LimitLow;
/*0x002*/         UINT16       BaseLow;
                  union                                 // 2 elements, 0x4 bytes (sizeof)
                  {
                      struct                            // 4 elements, 0x4 bytes (sizeof)
                      {
/*0x004*/                 UINT8        BaseMiddle;
/*0x005*/                 UINT8        Flags1;
/*0x006*/                 UINT8        Flags2;
/*0x007*/                 UINT8        BaseHigh;
                      }Bytes;
                      struct                            // 10 elements, 0x4 bytes (sizeof)
                      {
/*0x004*/                 ULONG32      BaseMiddle : 8;  // 0 BitPosition
/*0x004*/                 ULONG32      Type : 5;        // 8 BitPosition
/*0x004*/                 ULONG32      Dpl : 2;         // 13 BitPosition
/*0x004*/                 ULONG32      Present : 1;     // 15 BitPosition
/*0x004*/                 ULONG32      LimitHigh : 4;   // 16 BitPosition
/*0x004*/                 ULONG32      System : 1;      // 20 BitPosition
/*0x004*/                 ULONG32      LongMode : 1;    // 21 BitPosition
/*0x004*/                 ULONG32      DefaultBig : 1;  // 22 BitPosition
/*0x004*/                 ULONG32      Granularity : 1; // 23 BitPosition
/*0x004*/                 ULONG32      BaseHigh : 8;    // 24 BitPosition
                      }Bits;
                  };
/*0x008*/         ULONG32      BaseUpper;
/*0x00C*/         ULONG32      MustBeZero;
              };
              struct                                    // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         INT64        DataLow;
/*0x008*/         INT64        DataHigh;
              };
          }KGDTENTRY64, *PKGDTENTRY64;

          typedef union _KIDTENTRY64              // 11 elements, 0x10 bytes (sizeof)
          {
              struct                              // 6 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         UINT16       OffsetLow;
/*0x002*/         UINT16       Selector;
                  struct                          // 5 elements, 0x2 bytes (sizeof)
                  {
/*0x004*/             UINT16       IstIndex : 3;  // 0 BitPosition
/*0x004*/             UINT16       Reserved0 : 5; // 3 BitPosition
/*0x004*/             UINT16       Type : 5;      // 8 BitPosition
/*0x004*/             UINT16       Dpl : 2;       // 13 BitPosition
/*0x004*/             UINT16       Present : 1;   // 15 BitPosition
                  };
/*0x006*/         UINT16       OffsetMiddle;
/*0x008*/         ULONG32      OffsetHigh;
/*0x00C*/         ULONG32      Reserved1;
              };
/*0x000*/     UINT64       Alignment;
          }KIDTENTRY64, *PKIDTENTRY64;

typedef struct _KINTERRUPT
{
    SHORT Type;
    SHORT Size;
    LIST_ENTRY InterruptListEntry;
    FUNCT_006E_2255_ServiceRoutine* ServiceRoutine;
    FUNCT_006E_225A_MessageServiceRoutine* MessageServiceRoutine;
    ULONG MessageIndex;
    PVOID ServiceContext;
    KSPIN_LOCK SpinLock;
    ULONG TickCount;
    PKSPIN_LOCK ActualLock;
    FUNCT_00AE_0282_PostProcessInitRoutine_DispatchAddress_FinishRoutine* DispatchAddress;
    ULONG Vector;
    KIRQL Irql;
    KIRQL SynchronizeIrql;
    BOOLEAN FloatingSave;
    BOOLEAN Connected;
    ULONG Number;
    UCHAR ShareVector;
    USHORT ActiveCount;
    LONG InternalState;
    enum _KINTERRUPT_MODE Mode;
    enum _KINTERRUPT_POLARITY Polarity;
    ULONG ServiceCount;
    ULONG DispatchCount;
    struct _KEVENT* PassiveEvent;
    struct _KTRAP_FRAME* TrapFrame;
    ULONG DispatchCode[4];
    PVOID DisconnectData;
    struct _KTHREAD* ServiceThread;
} KINTERRUPT, *PKINTERRUPT;

          typedef struct _KLOCK_QUEUE_HANDLE      // 2 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _KSPIN_LOCK_QUEUE LockQueue; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT8        OldIrql;
/*0x011*/     UINT8        _PADDING0_[0x7];
          }KLOCK_QUEUE_HANDLE, *PKLOCK_QUEUE_HANDLE;

          typedef struct _KMUTANT                 // 5 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header;   // 31 elements, 0x18 bytes (sizeof)
/*0x018*/     struct _LIST_ENTRY MutantListEntry; // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _KTHREAD* OwnerThread;
/*0x030*/     UINT8        Abandoned;
/*0x031*/     UINT8        ApcDisable;
/*0x032*/     UINT8        _PADDING0_[0x6];
          }KMUTANT, *PKMUTANT;

          typedef struct _KNODE                // 17 elements, 0xC0 bytes (sizeof)
          {
/*0x000*/     UINT64       DeepIdleSet;
/*0x008*/     UINT8        _PADDING0_[0x38];
/*0x040*/     ULONG32      ProximityId;
/*0x044*/     UINT16       NodeNumber;
/*0x046*/     UINT16       PrimaryNodeNumber;
/*0x048*/     UINT8        MaximumProcessors;
/*0x049*/     struct _flags Flags;             // 5 elements, 0x1 bytes (sizeof)
/*0x04A*/     UINT8        Stride;
/*0x04B*/     UINT8        NodePad0;
/*0x04C*/     ULONG32      BalanceStride;
/*0x050*/     struct _GROUP_AFFINITY Affinity; // 3 elements, 0x10 bytes (sizeof)
/*0x060*/     UINT64       IdleCpuSet;
/*0x068*/     UINT64       IdleSmtSet;
/*0x070*/     UINT8        _PADDING1_[0x10];
/*0x080*/     ULONG32      Seed;
/*0x084*/     ULONG32      Lowest;
/*0x088*/     ULONG32      Highest;
/*0x08C*/     LONG32       ParkLock;
/*0x090*/     UINT64       NonParkedSet;
/*0x098*/     UINT8        _PADDING2_[0x28];
          }KNODE, *PKNODE;

          typedef struct _KPCR                             // 27 elements, 0x5C00 bytes (sizeof)
          {
              union                                        // 2 elements, 0x38 bytes (sizeof)
              {
/*0x000*/         struct _NT_TIB NtTib;                    // 8 elements, 0x38 bytes (sizeof)
                  struct                                   // 7 elements, 0x38 bytes (sizeof)
                  {
/*0x000*/             union _KGDTENTRY64* GdtBase;
/*0x008*/             struct _KTSS64* TssBase;
/*0x010*/             UINT64       UserRsp;
/*0x018*/             struct _KPCR* Self;
/*0x020*/             struct _KPRCB* CurrentPrcb;
/*0x028*/             struct _KSPIN_LOCK_QUEUE* LockArray;
/*0x030*/             VOID*        Used_Self;
                  };
              };
/*0x038*/     union _KIDTENTRY64* IdtBase;
/*0x040*/     UINT64       Unused[2];
/*0x050*/     UINT8        Irql;
/*0x051*/     UINT8        SecondLevelCacheAssociativity;
/*0x052*/     UINT8        ObsoleteNumber;
/*0x053*/     UINT8        Fill0;
/*0x054*/     ULONG32      Unused0[3];
/*0x060*/     UINT16       MajorVersion;
/*0x062*/     UINT16       MinorVersion;
/*0x064*/     ULONG32      StallScaleFactor;
/*0x068*/     VOID*        Unused1[3];
/*0x080*/     ULONG32      KernelReserved[15];
/*0x0BC*/     ULONG32      SecondLevelCacheSize;
/*0x0C0*/     ULONG32      HalReserved[16];
/*0x100*/     ULONG32      Unused2;
/*0x104*/     UINT8        _PADDING0_[0x4];
/*0x108*/     VOID*        KdVersionBlock;
/*0x110*/     VOID*        Unused3;
/*0x118*/     ULONG32      PcrAlign1[24];
/*0x178*/     UINT8        _PADDING1_[0x8];
/*0x180*/     struct _KPRCB Prcb;                          // 207 elements, 0x5A80 bytes (sizeof)
          }KPCR, *PKPCR;

           typedef struct _KPRCB                                                    // 207 elements, 0x5A80 bytes (sizeof)
           {
/*0x000*/      ULONG32      MxCsr;
/*0x004*/      UINT8        LegacyNumber;
/*0x005*/      UINT8        ReservedMustBeZero;
/*0x006*/      UINT8        InterruptRequest;
/*0x007*/      UINT8        IdleHalt;
/*0x008*/      struct _KTHREAD* CurrentThread;
/*0x010*/      struct _KTHREAD* NextThread;
/*0x018*/      struct _KTHREAD* IdleThread;
/*0x020*/      UINT8        NestingLevel;
/*0x021*/      UINT8        ClockOwner;
/*0x022*/      UINT8        PendingTick;
/*0x023*/      UINT8        PrcbPad00[1];
/*0x024*/      ULONG32      Number;
/*0x028*/      UINT64       RspBase;
/*0x030*/      UINT64       PrcbLock;
/*0x038*/      UINT64       PrcbPad01;
/*0x040*/      struct _KPROCESSOR_STATE ProcessorState;                             // 2 elements, 0x5B0 bytes (sizeof)
/*0x5F0*/      CHAR         CpuType;
/*0x5F1*/      CHAR         CpuID;
               union                                                                // 2 elements, 0x2 bytes (sizeof)
               {
/*0x5F2*/          UINT16       CpuStep;
                   struct                                                           // 2 elements, 0x2 bytes (sizeof)
                   {
/*0x5F2*/              UINT8        CpuStepping;
/*0x5F3*/              UINT8        CpuModel;
                   };
               };
/*0x5F4*/      ULONG32      MHz;
/*0x5F8*/      UINT64       HalReserved[8];
/*0x638*/      UINT16       MinorVersion;
/*0x63A*/      UINT16       MajorVersion;
/*0x63C*/      UINT8        BuildType;
/*0x63D*/      UINT8        CpuVendor;
/*0x63E*/      UINT8        CoresPerPhysicalProcessor;
/*0x63F*/      UINT8        LogicalProcessorsPerCore;
/*0x640*/      ULONG32      ApicMask;
/*0x644*/      ULONG32      CFlushSize;
/*0x648*/      VOID*        AcpiReserved;
/*0x650*/      ULONG32      InitialApicId;
/*0x654*/      ULONG32      Stride;
/*0x658*/      UINT16       Group;
/*0x65A*/      UINT8        _PADDING0_[0x6];
/*0x660*/      UINT64       GroupSetMember;
/*0x668*/      UINT8        GroupIndex;
/*0x669*/      UINT8        _PADDING1_[0x7];
/*0x670*/      struct _KSPIN_LOCK_QUEUE LockQueue[17];
/*0x780*/      struct _PP_LOOKASIDE_LIST PPLookasideList[16];
/*0x880*/      struct _GENERAL_LOOKASIDE_POOL PPNxPagedLookasideList[32];
/*0x1480*/     struct _GENERAL_LOOKASIDE_POOL PPNPagedLookasideList[32];
/*0x2080*/     struct _GENERAL_LOOKASIDE_POOL PPPagedLookasideList[32];
/*0x2C80*/     LONG32       PacketBarrier;
/*0x2C84*/     UINT8        _PADDING2_[0x4];
/*0x2C88*/     struct _SINGLE_LIST_ENTRY DeferredReadyListHead;                     // 1 elements, 0x8 bytes (sizeof)
/*0x2C90*/     LONG32       MmPageFaultCount;
/*0x2C94*/     LONG32       MmCopyOnWriteCount;
/*0x2C98*/     LONG32       MmTransitionCount;
/*0x2C9C*/     LONG32       MmDemandZeroCount;
/*0x2CA0*/     LONG32       MmPageReadCount;
/*0x2CA4*/     LONG32       MmPageReadIoCount;
/*0x2CA8*/     LONG32       MmDirtyPagesWriteCount;
/*0x2CAC*/     LONG32       MmDirtyWriteIoCount;
/*0x2CB0*/     LONG32       MmMappedPagesWriteCount;
/*0x2CB4*/     LONG32       MmMappedWriteIoCount;
/*0x2CB8*/     ULONG32      KeSystemCalls;
/*0x2CBC*/     ULONG32      KeContextSwitches;
/*0x2CC0*/     ULONG32      CcFastReadNoWait;
/*0x2CC4*/     ULONG32      CcFastReadWait;
/*0x2CC8*/     ULONG32      CcFastReadNotPossible;
/*0x2CCC*/     ULONG32      CcCopyReadNoWait;
/*0x2CD0*/     ULONG32      CcCopyReadWait;
/*0x2CD4*/     ULONG32      CcCopyReadNoWaitMiss;
/*0x2CD8*/     LONG32       LookasideIrpFloat;
/*0x2CDC*/     LONG32       IoReadOperationCount;
/*0x2CE0*/     LONG32       IoWriteOperationCount;
/*0x2CE4*/     LONG32       IoOtherOperationCount;
/*0x2CE8*/     union _LARGE_INTEGER IoReadTransferCount;                            // 4 elements, 0x8 bytes (sizeof)
/*0x2CF0*/     union _LARGE_INTEGER IoWriteTransferCount;                           // 4 elements, 0x8 bytes (sizeof)
/*0x2CF8*/     union _LARGE_INTEGER IoOtherTransferCount;                           // 4 elements, 0x8 bytes (sizeof)
/*0x2D00*/     LONG32       TargetCount;
/*0x2D04*/     ULONG32      IpiFrozen;
/*0x2D08*/     ULONG32      PrcbPad40[30];
/*0x2D80*/     struct _KDPC_DATA DpcData[2];
/*0x2DC0*/     VOID*        DpcStack;
/*0x2DC8*/     LONG32       MaximumDpcQueueDepth;
/*0x2DCC*/     ULONG32      DpcRequestRate;
/*0x2DD0*/     ULONG32      MinimumDpcRate;
/*0x2DD4*/     ULONG32      DpcLastCount;
/*0x2DD8*/     UINT8        ThreadDpcEnable;
/*0x2DD9*/     UINT8        QuantumEnd;
/*0x2DDA*/     UINT8        DpcRoutineActive;
/*0x2DDB*/     UINT8        IdleSchedule;
               union                                                                // 3 elements, 0x4 bytes (sizeof)
               {
/*0x2DDC*/         LONG32       DpcRequestSummary;
/*0x2DDC*/         INT16        DpcRequestSlot[2];
                   struct                                                           // 2 elements, 0x4 bytes (sizeof)
                   {
/*0x2DDC*/             INT16        NormalDpcState;
                       union                                                        // 2 elements, 0x2 bytes (sizeof)
                       {
/*0x2DDE*/                 UINT16       DpcThreadActive : 1;                        // 0 BitPosition
/*0x2DDE*/                 INT16        ThreadDpcState;
                       };
                   };
               };
/*0x2DE0*/     ULONG32      TimerHand;
/*0x2DE4*/     LONG32       MasterOffset;
/*0x2DE8*/     ULONG32      LastTick;
/*0x2DEC*/     ULONG32      ClockInterrupts;
/*0x2DF0*/     ULONG32      ReadyScanTick;
/*0x2DF4*/     UINT8        BalanceState;
/*0x2DF5*/     UINT8        PrcbPad50[11];
/*0x2E00*/     struct _KTIMER_TABLE TimerTable;                                     // 2 elements, 0x2200 bytes (sizeof)
/*0x5000*/     struct _KGATE DpcGate;                                               // 1 elements, 0x18 bytes (sizeof)
/*0x5018*/     VOID*        PrcbPad52;
/*0x5020*/     struct _KDPC CallDpc;                                                // 9 elements, 0x40 bytes (sizeof)
/*0x5060*/     LONG32       ClockKeepAlive;
/*0x5064*/     UINT8        PrcbPad60[2];
/*0x5066*/     UINT16       NmiActive;
/*0x5068*/     LONG32       DpcWatchdogPeriod;
/*0x506C*/     LONG32       DpcWatchdogCount;
/*0x5070*/     LONG32       KeSpinLockOrdering;
/*0x5074*/     ULONG32      PrcbPad70[1];
/*0x5078*/     VOID*        CachedPtes;
/*0x5080*/     struct _LIST_ENTRY WaitListHead;                                     // 2 elements, 0x10 bytes (sizeof)
/*0x5090*/     UINT64       WaitLock;
/*0x5098*/     ULONG32      ReadySummary;
/*0x509C*/     ULONG32      QueueIndex;
/*0x50A0*/     struct _KDPC TimerExpirationDpc;                                     // 9 elements, 0x40 bytes (sizeof)
/*0x50E0*/     struct _RTL_RB_TREE ScbQueue;                                        // 2 elements, 0x10 bytes (sizeof)
/*0x50F0*/     struct _LIST_ENTRY ScbList;                                          // 2 elements, 0x10 bytes (sizeof)
/*0x5100*/     struct _LIST_ENTRY DispatcherReadyListHead[32];
/*0x5300*/     ULONG32      InterruptCount;
/*0x5304*/     ULONG32      KernelTime;
/*0x5308*/     ULONG32      UserTime;
/*0x530C*/     ULONG32      DpcTime;
/*0x5310*/     ULONG32      InterruptTime;
/*0x5314*/     ULONG32      AdjustDpcThreshold;
/*0x5318*/     UINT8        DebuggerSavedIRQL;
/*0x5319*/     UINT8        GroupSchedulingOverQuota;
/*0x531A*/     UINT8        PrcbPad80[6];
/*0x5320*/     ULONG32      DpcTimeCount;
/*0x5324*/     ULONG32      DpcTimeLimit;
/*0x5328*/     ULONG32      PeriodicCount;
/*0x532C*/     ULONG32      PeriodicBias;
/*0x5330*/     ULONG32      AvailableTime;
/*0x5334*/     ULONG32      KeExceptionDispatchCount;
/*0x5338*/     struct _KNODE* ParentNode;
/*0x5340*/     UINT64       StartCycles;
/*0x5348*/     UINT64       GenerationTarget;
/*0x5350*/     ULONG32      ScbOffset;
/*0x5354*/     ULONG32      PrcbPad82[1];
/*0x5358*/     UINT64       AffinitizedCycles;
/*0x5360*/     LONG32       MmSpinLockOrdering;
/*0x5364*/     ULONG32      PageColor;
/*0x5368*/     ULONG32      NodeColor;
/*0x536C*/     ULONG32      NodeShiftedColor;
/*0x5370*/     ULONG32      SecondaryColorMask;
/*0x5374*/     ULONG32      PrcbPad83;
/*0x5378*/     UINT64       CycleTime;
/*0x5380*/     ULONG32      CcFastMdlReadNoWait;
/*0x5384*/     ULONG32      CcFastMdlReadWait;
/*0x5388*/     ULONG32      CcFastMdlReadNotPossible;
/*0x538C*/     ULONG32      CcMapDataNoWait;
/*0x5390*/     ULONG32      CcMapDataWait;
/*0x5394*/     ULONG32      CcPinMappedDataCount;
/*0x5398*/     ULONG32      CcPinReadNoWait;
/*0x539C*/     ULONG32      CcPinReadWait;
/*0x53A0*/     ULONG32      CcMdlReadNoWait;
/*0x53A4*/     ULONG32      CcMdlReadWait;
/*0x53A8*/     ULONG32      CcLazyWriteHotSpots;
/*0x53AC*/     ULONG32      CcLazyWriteIos;
/*0x53B0*/     ULONG32      CcLazyWritePages;
/*0x53B4*/     ULONG32      CcDataFlushes;
/*0x53B8*/     ULONG32      CcDataPages;
/*0x53BC*/     ULONG32      CcLostDelayedWrites;
/*0x53C0*/     ULONG32      CcFastReadResourceMiss;
/*0x53C4*/     ULONG32      CcCopyReadWaitMiss;
/*0x53C8*/     ULONG32      CcFastMdlReadResourceMiss;
/*0x53CC*/     ULONG32      CcMapDataNoWaitMiss;
/*0x53D0*/     ULONG32      CcMapDataWaitMiss;
/*0x53D4*/     ULONG32      CcPinReadNoWaitMiss;
/*0x53D8*/     ULONG32      CcPinReadWaitMiss;
/*0x53DC*/     ULONG32      CcMdlReadNoWaitMiss;
/*0x53E0*/     ULONG32      CcMdlReadWaitMiss;
/*0x53E4*/     ULONG32      CcReadAheadIos;
/*0x53E8*/     LONG32       MmCacheTransitionCount;
/*0x53EC*/     LONG32       MmCacheReadCount;
/*0x53F0*/     LONG32       MmCacheIoCount;
/*0x53F4*/     ULONG32      PrcbPad91[3];
/*0x5400*/     struct _PROCESSOR_POWER_STATE PowerState;                            // 29 elements, 0x178 bytes (sizeof)
/*0x5578*/     ULONG32      PrcbPad92[6];
/*0x5590*/     ULONG32      KeAlignmentFixupCount;
/*0x5594*/     UINT8        _PADDING3_[0x4];
/*0x5598*/     struct _KDPC DpcWatchdogDpc;                                         // 9 elements, 0x40 bytes (sizeof)
/*0x55D8*/     struct _KTIMER DpcWatchdogTimer;                                     // 6 elements, 0x40 bytes (sizeof)
/*0x5618*/     struct _CACHE_DESCRIPTOR Cache[5];
/*0x5654*/     ULONG32      CacheCount;
/*0x5658*/     ULONG32      CachedCommit;
/*0x565C*/     ULONG32      CachedResidentAvailable;
/*0x5660*/     VOID*        HyperPte;
/*0x5668*/     VOID*        WheaInfo;
/*0x5670*/     VOID*        EtwSupport;
/*0x5678*/     UINT8        _PADDING4_[0x8];
/*0x5680*/     union _SLIST_HEADER InterruptObjectPool;                             // 4 elements, 0x10 bytes (sizeof)
/*0x5690*/     union _SLIST_HEADER HypercallPageList;                               // 4 elements, 0x10 bytes (sizeof)
/*0x56A0*/     VOID*        HypercallPageVirtual;
/*0x56A8*/     VOID*        VirtualApicAssist;
/*0x56B0*/     UINT64*      StatisticsPage;
/*0x56B8*/     UINT64       CacheProcessorMask[5];
/*0x56E0*/     struct _KAFFINITY_EX PackageProcessorSet;                            // 4 elements, 0x48 bytes (sizeof)
/*0x5728*/     UINT64       CoreProcessorSet;
/*0x5730*/     struct _PROCESSOR_PROFILE_CONTROL_AREA* ProcessorProfileControlArea;
/*0x5738*/     VOID*        ProfileEventIndexAddress;
/*0x5740*/     UINT64       PrcbPad93[8];
/*0x5780*/     struct _SYNCH_COUNTERS SynchCounters;                                // 46 elements, 0xB8 bytes (sizeof)
/*0x5838*/     UINT8        VendorString[13];
/*0x5845*/     UINT8        PrcbPad10[3];
/*0x5848*/     ULONG32      FeatureBits;
/*0x584C*/     UINT8        _PADDING5_[0x4];
/*0x5850*/     union _LARGE_INTEGER UpdateSignature;                                // 4 elements, 0x8 bytes (sizeof)
/*0x5858*/     struct _CONTEXT* Context;
/*0x5860*/     ULONG32      ContextFlags;
/*0x5864*/     UINT8        _PADDING6_[0x4];
/*0x5868*/     struct _XSAVE_AREA* ExtendedState;
/*0x5870*/     UINT8        _PADDING7_[0x10];
/*0x5880*/     struct _ENTROPY_TIMING_STATE EntropyTimingState;                     // 7 elements, 0x180 bytes (sizeof)
/*0x5A00*/     struct _REQUEST_MAILBOX* Mailbox;
/*0x5A08*/     UINT8        _PADDING8_[0x38];
/*0x5A40*/     struct _REQUEST_MAILBOX RequestMailbox[1];
           }KPRCB, *PKPRCB;

          typedef struct _KPROCESS                          // 40 elements, 0x1B8 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header;             // 31 elements, 0x18 bytes (sizeof)
/*0x018*/     struct _LIST_ENTRY ProfileListHead;           // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     UINT64       DirectoryTableBase;
/*0x030*/     struct _LIST_ENTRY ThreadListHead;            // 2 elements, 0x10 bytes (sizeof)
/*0x040*/     UINT64       ProcessLock;
/*0x048*/     struct _KAFFINITY_EX Affinity;                // 4 elements, 0x48 bytes (sizeof)
/*0x090*/     struct _LIST_ENTRY ReadyListHead;             // 2 elements, 0x10 bytes (sizeof)
/*0x0A0*/     struct _SINGLE_LIST_ENTRY SwapListEntry;      // 1 elements, 0x8 bytes (sizeof)
/*0x0A8*/     struct _KAFFINITY_EX ActiveProcessors;        // 4 elements, 0x48 bytes (sizeof)
              union                                         // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                    // 9 elements, 0x4 bytes (sizeof)
                  {
/*0x0F0*/             LONG32       AutoAlignment : 1;       // 0 BitPosition
/*0x0F0*/             LONG32       DisableBoost : 1;        // 1 BitPosition
/*0x0F0*/             LONG32       DisableQuantum : 1;      // 2 BitPosition
/*0x0F0*/             LONG32       AffinitySet : 1;         // 3 BitPosition
/*0x0F0*/             ULONG32      DeepFreeze : 1;          // 4 BitPosition
/*0x0F0*/             ULONG32      IdleAware : 1;           // 5 BitPosition
/*0x0F0*/             ULONG32      TimerVirtualization : 1; // 6 BitPosition
/*0x0F0*/             ULONG32      ActiveGroupsMask : 8;    // 7 BitPosition
/*0x0F0*/             LONG32       ReservedFlags : 17;      // 15 BitPosition
                  };
/*0x0F0*/         LONG32       ProcessFlags;
              };
/*0x0F4*/     CHAR         BasePriority;
/*0x0F5*/     CHAR         QuantumReset;
/*0x0F6*/     UINT8        Visited;
/*0x0F7*/     union _KEXECUTE_OPTIONS Flags;                // 9 elements, 0x1 bytes (sizeof)
/*0x0F8*/     ULONG32      ThreadSeed[8];
/*0x118*/     UINT16       IdealNode[8];
/*0x128*/     UINT16       IdealGlobalNode;
/*0x12A*/     UINT16       Spare0;
/*0x12C*/     union _KSTACK_COUNT StackCount;               // 3 elements, 0x4 bytes (sizeof)
/*0x130*/     struct _LIST_ENTRY ProcessListEntry;          // 2 elements, 0x10 bytes (sizeof)
/*0x140*/     UINT64       CycleTime;
/*0x148*/     UINT64       ContextSwitches;
/*0x150*/     ULONG32      FreezeCount;
/*0x154*/     ULONG32      KernelTime;
/*0x158*/     ULONG32      UserTime;
/*0x15C*/     UINT16       LdtFreeSelectorHint;
/*0x15E*/     UINT16       LdtTableLength;
/*0x160*/     union _KGDTENTRY64 LdtSystemDescriptor;       // 8 elements, 0x10 bytes (sizeof)
/*0x170*/     VOID*        LdtBaseAddress;
/*0x178*/     struct _FAST_MUTEX LdtProcessLock;            // 5 elements, 0x38 bytes (sizeof)
/*0x1B0*/     VOID*        InstrumentationCallback;
          }KPROCESS, *PKPROCESS;

          typedef struct _KPROCESS_VALUES       // 10 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     UINT64       KernelTime;
/*0x008*/     UINT64       UserTime;
/*0x010*/     UINT64       CycleTime;
/*0x018*/     UINT64       ContextSwitches;
/*0x020*/     INT64        ReadOperationCount;
/*0x028*/     INT64        WriteOperationCount;
/*0x030*/     INT64        OtherOperationCount;
/*0x038*/     INT64        ReadTransferCount;
/*0x040*/     INT64        WriteTransferCount;
/*0x048*/     INT64        OtherTransferCount;
          }KPROCESS_VALUES, *PKPROCESS_VALUES;

          typedef struct _KPROCESSOR_STATE                 // 2 elements, 0x5B0 bytes (sizeof)
          {
/*0x000*/     struct _KSPECIAL_REGISTERS SpecialRegisters; // 28 elements, 0xE0 bytes (sizeof)
/*0x0E0*/     struct _CONTEXT ContextFrame;                // 64 elements, 0x4D0 bytes (sizeof)
          }KPROCESSOR_STATE, *PKPROCESSOR_STATE;

          typedef struct _KQUEUE                 // 5 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header;  // 31 elements, 0x18 bytes (sizeof)
/*0x018*/     struct _LIST_ENTRY EntryListHead;  // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     ULONG32      CurrentCount;
/*0x02C*/     ULONG32      MaximumCount;
/*0x030*/     struct _LIST_ENTRY ThreadListHead; // 2 elements, 0x10 bytes (sizeof)
          }KQUEUE, *PKQUEUE;

          typedef struct _KREQUEST_PACKET                   // 2 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     VOID*        CurrentPacket[3];
/*0x018*/     FUNCT_00AE_08E4_WorkerRoutine* WorkerRoutine;
          }KREQUEST_PACKET, *PKREQUEST_PACKET;

          typedef struct _KRESOURCEMANAGER                                   // 20 elements, 0x250 bytes (sizeof)
          {
/*0x000*/     struct _KEVENT NotificationAvailable;                          // 1 elements, 0x18 bytes (sizeof)
/*0x018*/     ULONG32      cookie;
/*0x01C*/     enum _KRESOURCEMANAGER_STATE State;
/*0x020*/     ULONG32      Flags;
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     struct _KMUTANT Mutex;                                         // 5 elements, 0x38 bytes (sizeof)
/*0x060*/     struct _KTMOBJECT_NAMESPACE_LINK NamespaceLink;                // 2 elements, 0x28 bytes (sizeof)
/*0x088*/     struct _GUID RmId;                                             // 4 elements, 0x10 bytes (sizeof)
/*0x098*/     struct _KQUEUE NotificationQueue;                              // 5 elements, 0x40 bytes (sizeof)
/*0x0D8*/     struct _KMUTANT NotificationMutex;                             // 5 elements, 0x38 bytes (sizeof)
/*0x110*/     struct _LIST_ENTRY EnlistmentHead;                             // 2 elements, 0x10 bytes (sizeof)
/*0x120*/     ULONG32      EnlistmentCount;
/*0x124*/     UINT8        _PADDING1_[0x4];
/*0x128*/     FUNCT_0064_20BF_NotificationRoutine* NotificationRoutine;
/*0x130*/     VOID*        Key;
/*0x138*/     struct _LIST_ENTRY ProtocolListHead;                           // 2 elements, 0x10 bytes (sizeof)
/*0x148*/     struct _LIST_ENTRY PendingPropReqListHead;                     // 2 elements, 0x10 bytes (sizeof)
/*0x158*/     struct _LIST_ENTRY CRMListEntry;                               // 2 elements, 0x10 bytes (sizeof)
/*0x168*/     struct _KTM* Tm;
/*0x170*/     struct _UNICODE_STRING Description;                            // 3 elements, 0x10 bytes (sizeof)
/*0x180*/     struct _KTMOBJECT_NAMESPACE Enlistments;                       // 5 elements, 0xA8 bytes (sizeof)
/*0x228*/     struct _KRESOURCEMANAGER_COMPLETION_BINDING CompletionBinding; // 4 elements, 0x28 bytes (sizeof)
          }KRESOURCEMANAGER, *PKRESOURCEMANAGER;

          typedef struct _KRESOURCEMANAGER_COMPLETION_BINDING // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY NotificationListHead;        // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     VOID*        Port;
/*0x018*/     UINT64       Key;
/*0x020*/     struct _EPROCESS* BindingProcess;
          }KRESOURCEMANAGER_COMPLETION_BINDING, *PKRESOURCEMANAGER_COMPLETION_BINDING;

          typedef struct _KSCB                      // 17 elements, 0x160 bytes (sizeof)
          {
/*0x000*/     UINT64       GenerationCycles;
/*0x008*/     UINT64       UnderQuotaCycleTarget;
/*0x010*/     UINT64       RankCycleTarget;
/*0x018*/     UINT64       LongTermCycles;
/*0x020*/     UINT64       LastReportedCycles;
/*0x028*/     UINT64       OverQuotaHistory;
/*0x030*/     struct _LIST_ENTRY PerProcessorList;  // 2 elements, 0x10 bytes (sizeof)
/*0x040*/     struct _RTL_BALANCED_NODE QueueNode;  // 6 elements, 0x18 bytes (sizeof)
              struct                                // 5 elements, 0x1 bytes (sizeof)
              {
/*0x058*/         UINT8        Inserted : 1;        // 0 BitPosition
/*0x058*/         UINT8        OverQuota : 1;       // 1 BitPosition
/*0x058*/         UINT8        HardCap : 1;         // 2 BitPosition
/*0x058*/         UINT8        RankBias : 1;        // 3 BitPosition
/*0x058*/         UINT8        Spare1 : 4;          // 4 BitPosition
              };
/*0x059*/     UINT8        Spare2;
/*0x05A*/     UINT16       ReadySummary;
/*0x05C*/     ULONG32      Rank;
/*0x060*/     struct _LIST_ENTRY ReadyListHead[16];
          }KSCB, *PKSCB;

          typedef struct _KSCHEDULING_GROUP           // 9 elements, 0x1C0 bytes (sizeof)
          {
/*0x000*/     UINT16       Value;
/*0x002*/     UINT8        Type;
/*0x003*/     UINT8        HardCap;
/*0x004*/     ULONG32      RelativeWeight;
/*0x008*/     UINT64       QueryHistoryTimeStamp;
/*0x010*/     INT64        NotificationCycles;
/*0x018*/     struct _LIST_ENTRY SchedulingGroupList; // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _KDPC* NotificationDpc;
/*0x030*/     UINT8        _PADDING0_[0x10];
/*0x040*/     struct _KSCB PerProcessor[1];
/*0x1A0*/     UINT8        _PADDING1_[0x20];
          }KSCHEDULING_GROUP, *PKSCHEDULING_GROUP;

          typedef struct _KSEMAPHORE            // 2 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header; // 31 elements, 0x18 bytes (sizeof)
/*0x018*/     LONG32       Limit;
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }KSEMAPHORE, *PKSEMAPHORE;

          typedef struct _KSPECIAL_REGISTERS     // 28 elements, 0xE0 bytes (sizeof)
          {
/*0x000*/     UINT64       Cr0;
/*0x008*/     UINT64       Cr2;
/*0x010*/     UINT64       Cr3;
/*0x018*/     UINT64       Cr4;
/*0x020*/     UINT64       KernelDr0;
/*0x028*/     UINT64       KernelDr1;
/*0x030*/     UINT64       KernelDr2;
/*0x038*/     UINT64       KernelDr3;
/*0x040*/     UINT64       KernelDr6;
/*0x048*/     UINT64       KernelDr7;
/*0x050*/     struct _KDESCRIPTOR Gdtr;          // 3 elements, 0x10 bytes (sizeof)
/*0x060*/     struct _KDESCRIPTOR Idtr;          // 3 elements, 0x10 bytes (sizeof)
/*0x070*/     UINT16       Tr;
/*0x072*/     UINT16       Ldtr;
/*0x074*/     ULONG32      MxCsr;
/*0x078*/     UINT64       DebugControl;
/*0x080*/     UINT64       LastBranchToRip;
/*0x088*/     UINT64       LastBranchFromRip;
/*0x090*/     UINT64       LastExceptionToRip;
/*0x098*/     UINT64       LastExceptionFromRip;
/*0x0A0*/     UINT64       Cr8;
/*0x0A8*/     UINT64       MsrGsBase;
/*0x0B0*/     UINT64       MsrGsSwap;
/*0x0B8*/     UINT64       MsrStar;
/*0x0C0*/     UINT64       MsrLStar;
/*0x0C8*/     UINT64       MsrCStar;
/*0x0D0*/     UINT64       MsrSyscallMask;
/*0x0D8*/     UINT64       Xcr0;
          }KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;

          typedef struct _KSPIN_LOCK_QUEUE    // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _KSPIN_LOCK_QUEUE* Next;
/*0x008*/     UINT64*      Lock;
          }KSPIN_LOCK_QUEUE, *PKSPIN_LOCK_QUEUE;

          typedef struct _KSTACK_CONTROL             // 4 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     UINT64       StackBase;
              union                                  // 2 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         UINT64       ActualLimit;
/*0x008*/         UINT64       StackExpansion : 1;   // 0 BitPosition
              };
/*0x010*/     struct _KERNEL_STACK_SEGMENT Previous; // 4 elements, 0x20 bytes (sizeof)
          }KSTACK_CONTROL, *PKSTACK_CONTROL;

          typedef union _KSTACK_COUNT           // 3 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     LONG32       Value;
              struct                            // 2 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      State : 3;       // 0 BitPosition
/*0x000*/         ULONG32      StackCount : 29; // 3 BitPosition
              };
          }KSTACK_COUNT, *PKSTACK_COUNT;

          typedef struct _KSYSTEM_TIME // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      LowPart;
/*0x004*/     LONG32       High1Time;
/*0x008*/     LONG32       High2Time;
          }KSYSTEM_TIME, *PKSYSTEM_TIME;

          typedef struct _KTHREAD                                // 144 elements, 0x340 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header;                  // 31 elements, 0x18 bytes (sizeof)
/*0x018*/     VOID*        SListFaultAddress;
/*0x020*/     UINT64       QuantumTarget;
/*0x028*/     VOID*        InitialStack;
/*0x030*/     VOID*        StackLimit;
/*0x038*/     VOID*        StackBase;
/*0x040*/     UINT64       ThreadLock;
/*0x048*/     UINT64       CycleTime;
/*0x050*/     ULONG32      CurrentRunTime;
/*0x054*/     ULONG32      ExpectedRunTime;
/*0x058*/     VOID*        KernelStack;
/*0x060*/     struct _XSAVE_FORMAT* StateSaveArea;
/*0x068*/     struct _KSCHEDULING_GROUP* SchedulingGroup;
/*0x070*/     union _KWAIT_STATUS_REGISTER WaitRegister;         // 8 elements, 0x1 bytes (sizeof)
/*0x071*/     UINT8        Running;
/*0x072*/     UINT8        Alerted[2];
              union                                              // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                         // 21 elements, 0x4 bytes (sizeof)
                  {
/*0x074*/             ULONG32      KernelStackResident : 1;      // 0 BitPosition
/*0x074*/             ULONG32      ReadyTransition : 1;          // 1 BitPosition
/*0x074*/             ULONG32      ProcessReadyQueue : 1;        // 2 BitPosition
/*0x074*/             ULONG32      WaitNext : 1;                 // 3 BitPosition
/*0x074*/             ULONG32      SystemAffinityActive : 1;     // 4 BitPosition
/*0x074*/             ULONG32      Alertable : 1;                // 5 BitPosition
/*0x074*/             ULONG32      CodePatchInProgress : 1;      // 6 BitPosition
/*0x074*/             ULONG32      UserStackWalkActive : 1;      // 7 BitPosition
/*0x074*/             ULONG32      ApcInterruptRequest : 1;      // 8 BitPosition
/*0x074*/             ULONG32      QuantumEndMigrate : 1;        // 9 BitPosition
/*0x074*/             ULONG32      UmsDirectedSwitchEnable : 1;  // 10 BitPosition
/*0x074*/             ULONG32      TimerActive : 1;              // 11 BitPosition
/*0x074*/             ULONG32      SystemThread : 1;             // 12 BitPosition
/*0x074*/             ULONG32      ProcessDetachActive : 1;      // 13 BitPosition
/*0x074*/             ULONG32      CalloutActive : 1;            // 14 BitPosition
/*0x074*/             ULONG32      ScbReadyQueue : 1;            // 15 BitPosition
/*0x074*/             ULONG32      ApcQueueable : 1;             // 16 BitPosition
/*0x074*/             ULONG32      ReservedStackInUse : 1;       // 17 BitPosition
/*0x074*/             ULONG32      UmsPerformingSyscall : 1;     // 18 BitPosition
/*0x074*/             ULONG32      DisableStackCheck : 1;        // 19 BitPosition
/*0x074*/             ULONG32      Reserved : 12;                // 20 BitPosition
                  };
/*0x074*/         LONG32       MiscFlags;
              };
              union                                              // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                         // 16 elements, 0x4 bytes (sizeof)
                  {
/*0x078*/             ULONG32      AutoAlignment : 1;            // 0 BitPosition
/*0x078*/             ULONG32      DisableBoost : 1;             // 1 BitPosition
/*0x078*/             ULONG32      UserAffinitySet : 1;          // 2 BitPosition
/*0x078*/             ULONG32      AlertedByThreadId : 1;        // 3 BitPosition
/*0x078*/             ULONG32      QuantumDonation : 1;          // 4 BitPosition
/*0x078*/             ULONG32      EnableStackSwap : 1;          // 5 BitPosition
/*0x078*/             ULONG32      GuiThread : 1;                // 6 BitPosition
/*0x078*/             ULONG32      DisableQuantum : 1;           // 7 BitPosition
/*0x078*/             ULONG32      ChargeOnlyGroup : 1;          // 8 BitPosition
/*0x078*/             ULONG32      DeferPreemption : 1;          // 9 BitPosition
/*0x078*/             ULONG32      QueueDeferPreemption : 1;     // 10 BitPosition
/*0x078*/             ULONG32      ForceDeferSchedule : 1;       // 11 BitPosition
/*0x078*/             ULONG32      ExplicitIdealProcessor : 1;   // 12 BitPosition
/*0x078*/             ULONG32      FreezeCount : 1;              // 13 BitPosition
/*0x078*/             ULONG32      EtwStackTraceApcInserted : 8; // 14 BitPosition
/*0x078*/             ULONG32      ReservedFlags : 10;           // 22 BitPosition
                  };
/*0x078*/         LONG32       ThreadFlags;
              };
/*0x07C*/     ULONG32      Spare0;
/*0x080*/     ULONG32      SystemCallNumber;
/*0x084*/     ULONG32      Spare1;
/*0x088*/     VOID*        FirstArgument;
/*0x090*/     struct _KTRAP_FRAME* TrapFrame;
              union                                              // 2 elements, 0x30 bytes (sizeof)
              {
/*0x098*/         struct _KAPC_STATE ApcState;                   // 5 elements, 0x30 bytes (sizeof)
                  struct                                         // 3 elements, 0x30 bytes (sizeof)
                  {
/*0x098*/             UINT8        ApcStateFill[43];
/*0x0C3*/             CHAR         Priority;
/*0x0C4*/             ULONG32      UserIdealProcessor;
                  };
              };
/*0x0C8*/     INT64        WaitStatus;
/*0x0D0*/     struct _KWAIT_BLOCK* WaitBlockList;
              union                                              // 2 elements, 0x10 bytes (sizeof)
              {
/*0x0D8*/         struct _LIST_ENTRY WaitListEntry;              // 2 elements, 0x10 bytes (sizeof)
/*0x0D8*/         struct _SINGLE_LIST_ENTRY SwapListEntry;       // 1 elements, 0x8 bytes (sizeof)
              };
/*0x0E8*/     struct _KQUEUE* Queue;
/*0x0F0*/     VOID*        Teb;
/*0x0F8*/     struct _KTIMER Timer;                              // 6 elements, 0x40 bytes (sizeof)
              union                                              // 9 elements, 0xC0 bytes (sizeof)
              {
/*0x138*/         struct _KWAIT_BLOCK WaitBlock[4];
                  struct                                         // 2 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill4[20];
/*0x14C*/             ULONG32      ContextSwitches;
/*0x150*/             UINT8        _PADDING0_[0xA8];
                  };
                  struct                                         // 5 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill5[68];
/*0x17C*/             UINT8        State;
/*0x17D*/             CHAR         NpxState;
/*0x17E*/             UINT8        WaitIrql;
/*0x17F*/             CHAR         WaitMode;
/*0x180*/             UINT8        _PADDING1_[0x78];
                  };
                  struct                                         // 2 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill6[116];
/*0x1AC*/             ULONG32      WaitTime;
/*0x1B0*/             UINT8        _PADDING2_[0x48];
                  };
                  struct                                         // 2 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill7[164];
                      union                                      // 2 elements, 0x4 bytes (sizeof)
                      {
                          struct                                 // 2 elements, 0x4 bytes (sizeof)
                          {
/*0x1DC*/                     INT16        KernelApcDisable;
/*0x1DE*/                     INT16        SpecialApcDisable;
                          };
/*0x1DC*/                 ULONG32      CombinedApcDisable;
                      };
                  };
                  struct                                         // 2 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill8[40];
/*0x160*/             struct _KTHREAD_COUNTERS* ThreadCounters;
/*0x168*/             UINT8        _PADDING3_[0x90];
                  };
                  struct                                         // 2 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill9[88];
/*0x190*/             struct _XSTATE_SAVE* XStateSave;
/*0x198*/             UINT8        _PADDING4_[0x60];
                  };
                  struct                                         // 2 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill10[136];
/*0x1C0*/             VOID*        Win32Thread;
/*0x1C8*/             UINT8        _PADDING5_[0x30];
                  };
                  struct                                         // 3 elements, 0xC0 bytes (sizeof)
                  {
/*0x138*/             UINT8        WaitBlockFill11[176];
/*0x1E8*/             struct _UMS_CONTROL_BLOCK* Ucb;
/*0x1F0*/             struct _KUMS_CONTEXT_HEADER* Uch;
                  };
              };
/*0x1F8*/     VOID*        TebMappedLowVa;
/*0x200*/     struct _LIST_ENTRY QueueListEntry;                 // 2 elements, 0x10 bytes (sizeof)
/*0x210*/     ULONG32      NextProcessor;
/*0x214*/     ULONG32      DeferredProcessor;
/*0x218*/     struct _KPROCESS* Process;
              union                                              // 2 elements, 0x10 bytes (sizeof)
              {
/*0x220*/         struct _GROUP_AFFINITY UserAffinity;           // 3 elements, 0x10 bytes (sizeof)
                  struct                                         // 7 elements, 0x10 bytes (sizeof)
                  {
/*0x220*/             UINT8        UserAffinityFill[10];
/*0x22A*/             CHAR         PreviousMode;
/*0x22B*/             CHAR         BasePriority;
                      union                                      // 2 elements, 0x1 bytes (sizeof)
                      {
/*0x22C*/                 CHAR         PriorityDecrement;
                          struct                                 // 2 elements, 0x1 bytes (sizeof)
                          {
/*0x22C*/                     UINT8        ForegroundBoost : 4;  // 0 BitPosition
/*0x22C*/                     UINT8        UnusualBoost : 4;     // 4 BitPosition
                          };
                      };
/*0x22D*/             UINT8        Preempted;
/*0x22E*/             UINT8        AdjustReason;
/*0x22F*/             CHAR         AdjustIncrement;
                  };
              };
              union                                              // 2 elements, 0x10 bytes (sizeof)
              {
/*0x230*/         struct _GROUP_AFFINITY Affinity;               // 3 elements, 0x10 bytes (sizeof)
                  struct                                         // 4 elements, 0x10 bytes (sizeof)
                  {
/*0x230*/             UINT8        AffinityFill[10];
/*0x23A*/             UINT8        ApcStateIndex;
/*0x23B*/             UINT8        WaitBlockCount;
/*0x23C*/             ULONG32      IdealProcessor;
                  };
              };
/*0x240*/     struct _KAPC_STATE* ApcStatePointer[2];
              union                                              // 2 elements, 0x30 bytes (sizeof)
              {
/*0x250*/         struct _KAPC_STATE SavedApcState;              // 5 elements, 0x30 bytes (sizeof)
                  struct                                         // 5 elements, 0x30 bytes (sizeof)
                  {
/*0x250*/             UINT8        SavedApcStateFill[43];
/*0x27B*/             UINT8        WaitReason;
/*0x27C*/             CHAR         SuspendCount;
/*0x27D*/             CHAR         Saturation;
/*0x27E*/             UINT16       SListFaultCount;
                  };
              };
              union                                              // 7 elements, 0x58 bytes (sizeof)
              {
/*0x280*/         struct _KAPC SchedulerApc;                     // 17 elements, 0x58 bytes (sizeof)
                  struct                                         // 2 elements, 0x58 bytes (sizeof)
                  {
/*0x280*/             UINT8        SchedulerApcFill0[1];
/*0x281*/             UINT8        ResourceIndex;
/*0x282*/             UINT8        _PADDING6_[0x56];
                  };
                  struct                                         // 2 elements, 0x58 bytes (sizeof)
                  {
/*0x280*/             UINT8        SchedulerApcFill1[3];
/*0x283*/             UINT8        QuantumReset;
/*0x284*/             UINT8        _PADDING7_[0x54];
                  };
                  struct                                         // 2 elements, 0x58 bytes (sizeof)
                  {
/*0x280*/             UINT8        SchedulerApcFill2[4];
/*0x284*/             ULONG32      KernelTime;
/*0x288*/             UINT8        _PADDING8_[0x50];
                  };
                  struct                                         // 2 elements, 0x58 bytes (sizeof)
                  {
/*0x280*/             UINT8        SchedulerApcFill3[64];
/*0x2C0*/             struct _KPRCB* WaitPrcb;
/*0x2C8*/             UINT8        _PADDING9_[0x10];
                  };
                  struct                                         // 2 elements, 0x58 bytes (sizeof)
                  {
/*0x280*/             UINT8        SchedulerApcFill4[72];
/*0x2C8*/             VOID*        LegoData;
/*0x2D0*/             UINT8        _PADDING10_[0x8];
                  };
                  struct                                         // 3 elements, 0x58 bytes (sizeof)
                  {
/*0x280*/             UINT8        SchedulerApcFill5[83];
/*0x2D3*/             UINT8        CallbackNestingLevel;
/*0x2D4*/             ULONG32      UserTime;
                  };
              };
/*0x2D8*/     struct _KEVENT SuspendEvent;                       // 1 elements, 0x18 bytes (sizeof)
/*0x2F0*/     struct _LIST_ENTRY ThreadListEntry;                // 2 elements, 0x10 bytes (sizeof)
/*0x300*/     struct _LIST_ENTRY MutantListHead;                 // 2 elements, 0x10 bytes (sizeof)
/*0x310*/     INT64        ReadOperationCount;
/*0x318*/     INT64        WriteOperationCount;
/*0x320*/     INT64        OtherOperationCount;
/*0x328*/     INT64        ReadTransferCount;
/*0x330*/     INT64        WriteTransferCount;
/*0x338*/     INT64        OtherTransferCount;
          }KTHREAD, *PKTHREAD;

          typedef struct _KTHREAD_COUNTERS               // 7 elements, 0x1A8 bytes (sizeof)
          {
/*0x000*/     UINT64       WaitReasonBitMap;
/*0x008*/     struct _THREAD_PERFORMANCE_DATA* UserData;
/*0x010*/     ULONG32      Flags;
/*0x014*/     ULONG32      ContextSwitches;
/*0x018*/     UINT64       CycleTimeBias;
/*0x020*/     UINT64       HardwareCounters;
/*0x028*/     struct _COUNTER_READING HwCounter[16];
          }KTHREAD_COUNTERS, *PKTHREAD_COUNTERS;

          typedef struct _KTIMER                 // 6 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _DISPATCHER_HEADER Header;  // 31 elements, 0x18 bytes (sizeof)
/*0x018*/     union _ULARGE_INTEGER DueTime;     // 4 elements, 0x8 bytes (sizeof)
/*0x020*/     struct _LIST_ENTRY TimerListEntry; // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     struct _KDPC* Dpc;
/*0x038*/     ULONG32      Processor;
/*0x03C*/     ULONG32      Period;
          }KTIMER, *PKTIMER;

          typedef struct _KTIMER_TABLE                      // 2 elements, 0x2200 bytes (sizeof)
          {
/*0x000*/     struct _KTIMER* TimerExpiry[64];
/*0x200*/     struct _KTIMER_TABLE_ENTRY TimerEntries[256];
          }KTIMER_TABLE, *PKTIMER_TABLE;

          typedef struct _KTIMER_TABLE_ENTRY // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT64       Lock;
/*0x008*/     struct _LIST_ENTRY Entry;      // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     union _ULARGE_INTEGER Time;    // 4 elements, 0x8 bytes (sizeof)
          }KTIMER_TABLE_ENTRY, *PKTIMER_TABLE_ENTRY;

          typedef struct _KTRAP_FRAME                    // 64 elements, 0x190 bytes (sizeof)
          {
/*0x000*/     UINT64       P1Home;
/*0x008*/     UINT64       P2Home;
/*0x010*/     UINT64       P3Home;
/*0x018*/     UINT64       P4Home;
/*0x020*/     UINT64       P5;
/*0x028*/     CHAR         PreviousMode;
/*0x029*/     UINT8        PreviousIrql;
/*0x02A*/     UINT8        FaultIndicator;
/*0x02B*/     UINT8        ExceptionActive;
/*0x02C*/     ULONG32      MxCsr;
/*0x030*/     UINT64       Rax;
/*0x038*/     UINT64       Rcx;
/*0x040*/     UINT64       Rdx;
/*0x048*/     UINT64       R8;
/*0x050*/     UINT64       R9;
/*0x058*/     UINT64       R10;
/*0x060*/     UINT64       R11;
              union                                      // 2 elements, 0x8 bytes (sizeof)
              {
/*0x068*/         UINT64       GsBase;
/*0x068*/         UINT64       GsSwap;
              };
/*0x070*/     struct _M128A Xmm0;                        // 2 elements, 0x10 bytes (sizeof)
/*0x080*/     struct _M128A Xmm1;                        // 2 elements, 0x10 bytes (sizeof)
/*0x090*/     struct _M128A Xmm2;                        // 2 elements, 0x10 bytes (sizeof)
/*0x0A0*/     struct _M128A Xmm3;                        // 2 elements, 0x10 bytes (sizeof)
/*0x0B0*/     struct _M128A Xmm4;                        // 2 elements, 0x10 bytes (sizeof)
/*0x0C0*/     struct _M128A Xmm5;                        // 2 elements, 0x10 bytes (sizeof)
              union                                      // 3 elements, 0x8 bytes (sizeof)
              {
/*0x0D0*/         UINT64       FaultAddress;
/*0x0D0*/         UINT64       ContextRecord;
/*0x0D0*/         UINT64       TimeStampCKCL;
              };
/*0x0D8*/     UINT64       Dr0;
/*0x0E0*/     UINT64       Dr1;
/*0x0E8*/     UINT64       Dr2;
/*0x0F0*/     UINT64       Dr3;
/*0x0F8*/     UINT64       Dr6;
/*0x100*/     UINT64       Dr7;
              union                                      // 2 elements, 0x28 bytes (sizeof)
              {
                  struct                                 // 5 elements, 0x28 bytes (sizeof)
                  {
/*0x108*/             UINT64       DebugControl;
/*0x110*/             UINT64       LastBranchToRip;
/*0x118*/             UINT64       LastBranchFromRip;
/*0x120*/             UINT64       LastExceptionToRip;
/*0x128*/             UINT64       LastExceptionFromRip;
                  };
                  struct                                 // 2 elements, 0x28 bytes (sizeof)
                  {
/*0x108*/             UINT64       LastBranchControl;
/*0x110*/             ULONG32      LastBranchMSR;
/*0x114*/             UINT8        _PADDING0_[0x1C];
                  };
              };
/*0x130*/     UINT16       SegDs;
/*0x132*/     UINT16       SegEs;
/*0x134*/     UINT16       SegFs;
/*0x136*/     UINT16       SegGs;
/*0x138*/     UINT64       TrapFrame;
/*0x140*/     UINT64       Rbx;
/*0x148*/     UINT64       Rdi;
/*0x150*/     UINT64       Rsi;
/*0x158*/     UINT64       Rbp;
              union                                      // 3 elements, 0x8 bytes (sizeof)
              {
/*0x160*/         UINT64       ErrorCode;
/*0x160*/         UINT64       ExceptionFrame;
/*0x160*/         UINT64       TimeStampKlog;
              };
/*0x168*/     UINT64       Rip;
/*0x170*/     UINT16       SegCs;
/*0x172*/     UINT8        Fill0;
/*0x173*/     UINT8        Logging;
/*0x174*/     UINT16       Fill1[2];
/*0x178*/     ULONG32      EFlags;
/*0x17C*/     ULONG32      Fill2;
/*0x180*/     UINT64       Rsp;
/*0x188*/     UINT16       SegSs;
/*0x18A*/     UINT16       Fill3;
/*0x18C*/     LONG32       CodePatchCycle;
          }KTRAP_FRAME, *PKTRAP_FRAME;

          typedef struct _KTSS64      // 8 elements, 0x68 bytes (sizeof)
          {
/*0x000*/     ULONG32      Reserved0;
/*0x004*/     UINT64       Rsp0;
/*0x00C*/     UINT64       Rsp1;
/*0x014*/     UINT64       Rsp2;
/*0x01C*/     UINT64       Ist[8];
/*0x05C*/     UINT64       Reserved1;
/*0x064*/     UINT16       Reserved2;
/*0x066*/     UINT16       IoMapBase;
          }KTSS64, *PKTSS64;

          typedef struct _KUMS_CONTEXT_HEADER           // 16 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     UINT64       P1Home;
/*0x008*/     UINT64       P2Home;
/*0x010*/     UINT64       P3Home;
/*0x018*/     UINT64       P4Home;
/*0x020*/     VOID*        StackTop;
/*0x028*/     UINT64       StackSize;
/*0x030*/     UINT64       RspOffset;
/*0x038*/     UINT64       Rip;
/*0x040*/     struct _XSAVE_FORMAT* FltSave;
              union                                     // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                                // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x048*/             UINT64       Volatile : 1;        // 0 BitPosition
/*0x048*/             UINT64       Reserved : 63;       // 1 BitPosition
                  };
/*0x048*/         UINT64       Flags;
              };
/*0x050*/     struct _KTRAP_FRAME* TrapFrame;
/*0x058*/     struct _KEXCEPTION_FRAME* ExceptionFrame;
/*0x060*/     struct _KTHREAD* SourceThread;
/*0x068*/     UINT64       Return;
          }KUMS_CONTEXT_HEADER, *PKUMS_CONTEXT_HEADER;

          typedef struct _KUSER_SHARED_DATA                                // 84 elements, 0x5D0 bytes (sizeof)
          {
/*0x000*/     ULONG32      TickCountLowDeprecated;
/*0x004*/     ULONG32      TickCountMultiplier;
/*0x008*/     struct _KSYSTEM_TIME InterruptTime;                          // 3 elements, 0xC bytes (sizeof)
/*0x014*/     struct _KSYSTEM_TIME SystemTime;                             // 3 elements, 0xC bytes (sizeof)
/*0x020*/     struct _KSYSTEM_TIME TimeZoneBias;                           // 3 elements, 0xC bytes (sizeof)
/*0x02C*/     UINT16       ImageNumberLow;
/*0x02E*/     UINT16       ImageNumberHigh;
/*0x030*/     WCHAR        NtSystemRoot[260];
/*0x238*/     ULONG32      MaxStackTraceDepth;
/*0x23C*/     ULONG32      CryptoExponent;
/*0x240*/     ULONG32      TimeZoneId;
/*0x244*/     ULONG32      LargePageMinimum;
/*0x248*/     ULONG32      AitSamplingValue;
/*0x24C*/     ULONG32      AppCompatFlag;
/*0x250*/     UINT64       RNGSeedVersion;
/*0x258*/     ULONG32      GlobalValidationRunlevel;
/*0x25C*/     ULONG32      Reserved2[2];
/*0x264*/     enum _NT_PRODUCT_TYPE NtProductType;
/*0x268*/     UINT8        ProductTypeIsValid;
/*0x269*/     UINT8        Reserved0[1];
/*0x26A*/     UINT16       NativeProcessorArchitecture;
/*0x26C*/     ULONG32      NtMajorVersion;
/*0x270*/     ULONG32      NtMinorVersion;
/*0x274*/     UINT8        ProcessorFeatures[64];
/*0x2B4*/     ULONG32      Reserved1;
/*0x2B8*/     ULONG32      Reserved3;
/*0x2BC*/     ULONG32      TimeSlip;
/*0x2C0*/     enum _ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture;
/*0x2C4*/     ULONG32      AltArchitecturePad[1];
/*0x2C8*/     union _LARGE_INTEGER SystemExpirationDate;                   // 4 elements, 0x8 bytes (sizeof)
/*0x2D0*/     ULONG32      SuiteMask;
/*0x2D4*/     UINT8        KdDebuggerEnabled;
              union                                                        // 2 elements, 0x1 bytes (sizeof)
              {
/*0x2D5*/         UINT8        MitigationPolicies;
                  struct                                                   // 4 elements, 0x1 bytes (sizeof)
                  {
/*0x2D5*/             UINT8        NXSupportPolicy : 2;                    // 0 BitPosition
/*0x2D5*/             UINT8        SEHValidationPolicy : 2;                // 2 BitPosition
/*0x2D5*/             UINT8        CurDirDevicesSkippedForDlls : 2;        // 4 BitPosition
/*0x2D5*/             UINT8        Reserved : 2;                           // 6 BitPosition
                  };
              };
/*0x2D6*/     UINT8        Reserved6[2];
/*0x2D8*/     ULONG32      ActiveConsoleId;
/*0x2DC*/     ULONG32      DismountCount;
/*0x2E0*/     ULONG32      ComPlusPackage;
/*0x2E4*/     ULONG32      LastSystemRITEventTickCount;
/*0x2E8*/     ULONG32      NumberOfPhysicalPages;
/*0x2EC*/     UINT8        SafeBootMode;
/*0x2ED*/     UINT8        Reserved12[3];
              union                                                        // 2 elements, 0x4 bytes (sizeof)
              {
/*0x2F0*/         ULONG32      SharedDataFlags;
                  struct                                                   // 8 elements, 0x4 bytes (sizeof)
                  {
/*0x2F0*/             ULONG32      DbgErrorPortPresent : 1;                // 0 BitPosition
/*0x2F0*/             ULONG32      DbgElevationEnabled : 1;                // 1 BitPosition
/*0x2F0*/             ULONG32      DbgVirtEnabled : 1;                     // 2 BitPosition
/*0x2F0*/             ULONG32      DbgInstallerDetectEnabled : 1;          // 3 BitPosition
/*0x2F0*/             ULONG32      DbgLkgEnabled : 1;                      // 4 BitPosition
/*0x2F0*/             ULONG32      DbgDynProcessorEnabled : 1;             // 5 BitPosition
/*0x2F0*/             ULONG32      DbgConsoleBrokerEnabled : 1;            // 6 BitPosition
/*0x2F0*/             ULONG32      SpareBits : 25;                         // 7 BitPosition
                  };
              };
/*0x2F4*/     ULONG32      DataFlagsPad[1];
/*0x2F8*/     UINT64       TestRetInstruction;
/*0x300*/     ULONG32      Reserved9;
/*0x304*/     ULONG32      Reserved10;
/*0x308*/     UINT64       SystemCallPad[3];
              union                                                        // 3 elements, 0xC bytes (sizeof)
              {
/*0x320*/         struct _KSYSTEM_TIME TickCount;                          // 3 elements, 0xC bytes (sizeof)
/*0x320*/         UINT64       TickCountQuad;
/*0x320*/         ULONG32      ReservedTickCountOverlay[3];
              };
/*0x32C*/     ULONG32      TickCountPad[1];
/*0x330*/     ULONG32      Cookie;
/*0x334*/     ULONG32      CookiePad[1];
/*0x338*/     INT64        ConsoleSessionForegroundProcessId;
/*0x340*/     UINT64       TimeUpdateSequence;
/*0x348*/     UINT64       LastTimeUpdateQpcValue;
/*0x350*/     UINT64       LastInterruptTimeUpdateQpcValue;
/*0x358*/     UINT64       QpcTimeIncrement;
/*0x360*/     ULONG32      QpcTimeIncrement32;
/*0x364*/     ULONG32      Reserved8[7];
/*0x380*/     UINT16       UserModeGlobalLogger[16];
/*0x3A0*/     ULONG32      ImageFileExecutionOptions;
/*0x3A4*/     ULONG32      LangGenerationCount;
/*0x3A8*/     UINT64       InterruptTimeBias;
/*0x3B0*/     UINT64       TscQpcBias;
/*0x3B8*/     ULONG32      ActiveProcessorCount;
/*0x3BC*/     UINT8        ActiveGroupCount;
/*0x3BD*/     UINT8        QpcTimeIncrementShift;
              union                                                        // 2 elements, 0x2 bytes (sizeof)
              {
/*0x3BE*/         UINT16       TscQpcData;
                  struct                                                   // 2 elements, 0x2 bytes (sizeof)
                  {
/*0x3BE*/             UINT8        TscQpcEnabled;
/*0x3BF*/             UINT8        TscQpcShift;
                  };
              };
/*0x3C0*/     struct _XSTATE_CONFIGURATION XState;                         // 4 elements, 0x210 bytes (sizeof)
          }KUSER_SHARED_DATA, *PKUSER_SHARED_DATA;

          typedef struct _KWAIT_BLOCK                // 9 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY WaitListEntry;      // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT8        WaitType;
/*0x011*/     UINT8        BlockState;
/*0x012*/     UINT16       WaitKey;
/*0x014*/     LONG32       SpareLong;
              union                                  // 2 elements, 0x8 bytes (sizeof)
              {
/*0x018*/         struct _KTHREAD* Thread;
/*0x018*/         struct _KQUEUE* NotificationQueue;
              };
/*0x020*/     VOID*        Object;
/*0x028*/     VOID*        SparePtr;
          }KWAIT_BLOCK, *PKWAIT_BLOCK;

          typedef union _KWAIT_STATUS_REGISTER // 8 elements, 0x1 bytes (sizeof)
          {
/*0x000*/     UINT8        Flags;
              struct                           // 7 elements, 0x1 bytes (sizeof)
              {
/*0x000*/         UINT8        State : 2;      // 0 BitPosition
/*0x000*/         UINT8        Affinity : 1;   // 2 BitPosition
/*0x000*/         UINT8        Priority : 1;   // 3 BitPosition
/*0x000*/         UINT8        Apc : 1;        // 4 BitPosition
/*0x000*/         UINT8        UserApc : 1;    // 5 BitPosition
/*0x000*/         UINT8        Alert : 1;      // 6 BitPosition
/*0x000*/         UINT8        Unused : 1;     // 7 BitPosition
              };
          }KWAIT_STATUS_REGISTER, *PKWAIT_STATUS_REGISTER;
          typedef struct _PEB                                                                               // 93 elements, 0x388 bytes (sizeof)
          {
/*0x000*/     UINT8        InheritedAddressSpace;
/*0x001*/     UINT8        ReadImageFileExecOptions;
/*0x002*/     UINT8        BeingDebugged;
              union                                                                                         // 2 elements, 0x1 bytes (sizeof)
              {
/*0x003*/         UINT8        BitField;
                  struct                                                                                    // 6 elements, 0x1 bytes (sizeof)
                  {
/*0x003*/             UINT8        ImageUsesLargePages : 1;                                                 // 0 BitPosition
/*0x003*/             UINT8        IsProtectedProcess : 1;                                                  // 1 BitPosition
/*0x003*/             UINT8        IsLegacyProcess : 1;                                                     // 2 BitPosition
/*0x003*/             UINT8        IsImageDynamicallyRelocated : 1;                                         // 3 BitPosition
/*0x003*/             UINT8        SkipPatchingUser32Forwarders : 1;                                        // 4 BitPosition
/*0x003*/             UINT8        SpareBits : 3;                                                           // 5 BitPosition
                  };
              };
/*0x008*/     VOID*        Mutant;
/*0x010*/     VOID*        ImageBaseAddress;
/*0x018*/     struct _PEB_LDR_DATA* Ldr;
/*0x020*/     struct _RTL_USER_PROCESS_PARAMETERS* ProcessParameters;
/*0x028*/     VOID*        SubSystemData;
/*0x030*/     VOID*        ProcessHeap;
/*0x038*/     struct _RTL_CRITICAL_SECTION* FastPebLock;
/*0x040*/     VOID*        AtlThunkSListPtr;
/*0x048*/     VOID*        IFEOKey;
              union                                                                                         // 2 elements, 0x4 bytes (sizeof)
              {
/*0x050*/         ULONG32      CrossProcessFlags;
                  struct                                                                                    // 6 elements, 0x4 bytes (sizeof)
                  {
/*0x050*/             ULONG32      ProcessInJob : 1;                                                        // 0 BitPosition
/*0x050*/             ULONG32      ProcessInitializing : 1;                                                 // 1 BitPosition
/*0x050*/             ULONG32      ProcessUsingVEH : 1;                                                     // 2 BitPosition
/*0x050*/             ULONG32      ProcessUsingVCH : 1;                                                     // 3 BitPosition
/*0x050*/             ULONG32      ProcessUsingFTH : 1;                                                     // 4 BitPosition
/*0x050*/             ULONG32      ReservedBits0 : 27;                                                      // 5 BitPosition
                  };
              };
              union                                                                                         // 2 elements, 0x8 bytes (sizeof)
              {
/*0x058*/         VOID*        KernelCallbackTable;
/*0x058*/         VOID*        UserSharedInfoPtr;
              };
/*0x060*/     ULONG32      SystemReserved[1];
/*0x064*/     ULONG32      AtlThunkSListPtr32;
/*0x068*/     VOID*        ApiSetMap;
/*0x070*/     ULONG32      TlsExpansionCounter;
/*0x074*/     UINT8        _PADDING0_[0x4];
/*0x078*/     VOID*        TlsBitmap;
/*0x080*/     ULONG32      TlsBitmapBits[2];
/*0x088*/     VOID*        ReadOnlySharedMemoryBase;
/*0x090*/     VOID*        HotpatchInformation;
/*0x098*/     VOID**       ReadOnlyStaticServerData;
/*0x0A0*/     VOID*        AnsiCodePageData;
/*0x0A8*/     VOID*        OemCodePageData;
/*0x0B0*/     VOID*        UnicodeCaseTableData;
/*0x0B8*/     ULONG32      NumberOfProcessors;
/*0x0BC*/     ULONG32      NtGlobalFlag;
/*0x0C0*/     union _LARGE_INTEGER CriticalSectionTimeout;                                                  // 4 elements, 0x8 bytes (sizeof)
/*0x0C8*/     UINT64       HeapSegmentReserve;
/*0x0D0*/     UINT64       HeapSegmentCommit;
/*0x0D8*/     UINT64       HeapDeCommitTotalFreeThreshold;
/*0x0E0*/     UINT64       HeapDeCommitFreeBlockThreshold;
/*0x0E8*/     ULONG32      NumberOfHeaps;
/*0x0EC*/     ULONG32      MaximumNumberOfHeaps;
/*0x0F0*/     VOID**       ProcessHeaps;
/*0x0F8*/     VOID*        GdiSharedHandleTable;
/*0x100*/     VOID*        ProcessStarterHelper;
/*0x108*/     ULONG32      GdiDCAttributeList;
/*0x10C*/     UINT8        _PADDING1_[0x4];
/*0x110*/     struct _RTL_CRITICAL_SECTION* LoaderLock;
/*0x118*/     ULONG32      OSMajorVersion;
/*0x11C*/     ULONG32      OSMinorVersion;
/*0x120*/     UINT16       OSBuildNumber;
/*0x122*/     UINT16       OSCSDVersion;
/*0x124*/     ULONG32      OSPlatformId;
/*0x128*/     ULONG32      ImageSubsystem;
/*0x12C*/     ULONG32      ImageSubsystemMajorVersion;
/*0x130*/     ULONG32      ImageSubsystemMinorVersion;
/*0x134*/     UINT8        _PADDING2_[0x4];
/*0x138*/     UINT64       ActiveProcessAffinityMask;
/*0x140*/     ULONG32      GdiHandleBuffer[60];
/*0x230*/     FUNCT_00AE_0282_PostProcessInitRoutine_DispatchAddress_FinishRoutine* PostProcessInitRoutine;
/*0x238*/     VOID*        TlsExpansionBitmap;
/*0x240*/     ULONG32      TlsExpansionBitmapBits[32];
/*0x2C0*/     ULONG32      SessionId;
/*0x2C4*/     UINT8        _PADDING3_[0x4];
/*0x2C8*/     union _ULARGE_INTEGER AppCompatFlags;                                                         // 4 elements, 0x8 bytes (sizeof)
/*0x2D0*/     union _ULARGE_INTEGER AppCompatFlagsUser;                                                     // 4 elements, 0x8 bytes (sizeof)
/*0x2D8*/     VOID*        pShimData;
/*0x2E0*/     VOID*        AppCompatInfo;
/*0x2E8*/     struct _UNICODE_STRING CSDVersion;                                                            // 3 elements, 0x10 bytes (sizeof)
/*0x2F8*/     struct _ACTIVATION_CONTEXT_DATA* ActivationContextData;
/*0x300*/     struct _ASSEMBLY_STORAGE_MAP* ProcessAssemblyStorageMap;
/*0x308*/     struct _ACTIVATION_CONTEXT_DATA* SystemDefaultActivationContextData;
/*0x310*/     struct _ASSEMBLY_STORAGE_MAP* SystemAssemblyStorageMap;
/*0x318*/     UINT64       MinimumStackCommit;
/*0x320*/     struct _FLS_CALLBACK_INFO* FlsCallback;
/*0x328*/     struct _LIST_ENTRY FlsListHead;                                                               // 2 elements, 0x10 bytes (sizeof)
/*0x338*/     VOID*        FlsBitmap;
/*0x340*/     ULONG32      FlsBitmapBits[4];
/*0x350*/     ULONG32      FlsHighIndex;
/*0x354*/     UINT8        _PADDING4_[0x4];
/*0x358*/     VOID*        WerRegistrationData;
/*0x360*/     VOID*        WerShipAssertPtr;
/*0x368*/     VOID*        pUnused;
/*0x370*/     VOID*        pImageHeaderHash;
              union                                                                                         // 2 elements, 0x4 bytes (sizeof)
              {
/*0x378*/         ULONG32      TracingFlags;
                  struct                                                                                    // 4 elements, 0x4 bytes (sizeof)
                  {
/*0x378*/             ULONG32      HeapTracingEnabled : 1;                                                  // 0 BitPosition
/*0x378*/             ULONG32      CritSecTracingEnabled : 1;                                               // 1 BitPosition
/*0x378*/             ULONG32      LibLoaderTracingEnabled : 1;                                             // 2 BitPosition
/*0x378*/             ULONG32      SpareTracingBits : 29;                                                   // 3 BitPosition
                  };
              };
/*0x380*/     UINT64       CsrServerReadOnlySharedMemoryBase;
          }PEB, *PPEB;

          typedef struct _PEB_LDR_DATA                            // 9 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     ULONG32      Length;
/*0x004*/     UINT8        Initialized;
/*0x005*/     UINT8        _PADDING0_[0x3];
/*0x008*/     VOID*        SsHandle;
/*0x010*/     struct _LIST_ENTRY InLoadOrderModuleList;           // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     struct _LIST_ENTRY InMemoryOrderModuleList;         // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     struct _LIST_ENTRY InInitializationOrderModuleList; // 2 elements, 0x10 bytes (sizeof)
/*0x040*/     VOID*        EntryInProgress;
/*0x048*/     UINT8        ShutdownInProgress;
/*0x049*/     UINT8        _PADDING1_[0x7];
/*0x050*/     VOID*        ShutdownThreadId;
          }PEB_LDR_DATA, *PPEB_LDR_DATA;

          typedef struct _PEB32                                      // 93 elements, 0x250 bytes (sizeof)
          {
/*0x000*/     UINT8        InheritedAddressSpace;
/*0x001*/     UINT8        ReadImageFileExecOptions;
/*0x002*/     UINT8        BeingDebugged;
              union                                                  // 2 elements, 0x1 bytes (sizeof)
              {
/*0x003*/         UINT8        BitField;
                  struct                                             // 6 elements, 0x1 bytes (sizeof)
                  {
/*0x003*/             UINT8        ImageUsesLargePages : 1;          // 0 BitPosition
/*0x003*/             UINT8        IsProtectedProcess : 1;           // 1 BitPosition
/*0x003*/             UINT8        IsLegacyProcess : 1;              // 2 BitPosition
/*0x003*/             UINT8        IsImageDynamicallyRelocated : 1;  // 3 BitPosition
/*0x003*/             UINT8        SkipPatchingUser32Forwarders : 1; // 4 BitPosition
/*0x003*/             UINT8        SpareBits : 3;                    // 5 BitPosition
                  };
              };
/*0x004*/     ULONG32      Mutant;
/*0x008*/     ULONG32      ImageBaseAddress;
/*0x00C*/     ULONG32      Ldr;
/*0x010*/     ULONG32      ProcessParameters;
/*0x014*/     ULONG32      SubSystemData;
/*0x018*/     ULONG32      ProcessHeap;
/*0x01C*/     ULONG32      FastPebLock;
/*0x020*/     ULONG32      AtlThunkSListPtr;
/*0x024*/     ULONG32      IFEOKey;
              union                                                  // 2 elements, 0x4 bytes (sizeof)
              {
/*0x028*/         ULONG32      CrossProcessFlags;
                  struct                                             // 6 elements, 0x4 bytes (sizeof)
                  {
/*0x028*/             ULONG32      ProcessInJob : 1;                 // 0 BitPosition
/*0x028*/             ULONG32      ProcessInitializing : 1;          // 1 BitPosition
/*0x028*/             ULONG32      ProcessUsingVEH : 1;              // 2 BitPosition
/*0x028*/             ULONG32      ProcessUsingVCH : 1;              // 3 BitPosition
/*0x028*/             ULONG32      ProcessUsingFTH : 1;              // 4 BitPosition
/*0x028*/             ULONG32      ReservedBits0 : 27;               // 5 BitPosition
                  };
              };
              union                                                  // 2 elements, 0x4 bytes (sizeof)
              {
/*0x02C*/         ULONG32      KernelCallbackTable;
/*0x02C*/         ULONG32      UserSharedInfoPtr;
              };
/*0x030*/     ULONG32      SystemReserved[1];
/*0x034*/     ULONG32      AtlThunkSListPtr32;
/*0x038*/     ULONG32      ApiSetMap;
/*0x03C*/     ULONG32      TlsExpansionCounter;
/*0x040*/     ULONG32      TlsBitmap;
/*0x044*/     ULONG32      TlsBitmapBits[2];
/*0x04C*/     ULONG32      ReadOnlySharedMemoryBase;
/*0x050*/     ULONG32      HotpatchInformation;
/*0x054*/     ULONG32      ReadOnlyStaticServerData;
/*0x058*/     ULONG32      AnsiCodePageData;
/*0x05C*/     ULONG32      OemCodePageData;
/*0x060*/     ULONG32      UnicodeCaseTableData;
/*0x064*/     ULONG32      NumberOfProcessors;
/*0x068*/     ULONG32      NtGlobalFlag;
/*0x06C*/     UINT8        _PADDING0_[0x4];
/*0x070*/     union _LARGE_INTEGER CriticalSectionTimeout;           // 4 elements, 0x8 bytes (sizeof)
/*0x078*/     ULONG32      HeapSegmentReserve;
/*0x07C*/     ULONG32      HeapSegmentCommit;
/*0x080*/     ULONG32      HeapDeCommitTotalFreeThreshold;
/*0x084*/     ULONG32      HeapDeCommitFreeBlockThreshold;
/*0x088*/     ULONG32      NumberOfHeaps;
/*0x08C*/     ULONG32      MaximumNumberOfHeaps;
/*0x090*/     ULONG32      ProcessHeaps;
/*0x094*/     ULONG32      GdiSharedHandleTable;
/*0x098*/     ULONG32      ProcessStarterHelper;
/*0x09C*/     ULONG32      GdiDCAttributeList;
/*0x0A0*/     ULONG32      LoaderLock;
/*0x0A4*/     ULONG32      OSMajorVersion;
/*0x0A8*/     ULONG32      OSMinorVersion;
/*0x0AC*/     UINT16       OSBuildNumber;
/*0x0AE*/     UINT16       OSCSDVersion;
/*0x0B0*/     ULONG32      OSPlatformId;
/*0x0B4*/     ULONG32      ImageSubsystem;
/*0x0B8*/     ULONG32      ImageSubsystemMajorVersion;
/*0x0BC*/     ULONG32      ImageSubsystemMinorVersion;
/*0x0C0*/     ULONG32      ActiveProcessAffinityMask;
/*0x0C4*/     ULONG32      GdiHandleBuffer[34];
/*0x14C*/     ULONG32      PostProcessInitRoutine;
/*0x150*/     ULONG32      TlsExpansionBitmap;
/*0x154*/     ULONG32      TlsExpansionBitmapBits[32];
/*0x1D4*/     ULONG32      SessionId;
/*0x1D8*/     union _ULARGE_INTEGER AppCompatFlags;                  // 4 elements, 0x8 bytes (sizeof)
/*0x1E0*/     union _ULARGE_INTEGER AppCompatFlagsUser;              // 4 elements, 0x8 bytes (sizeof)
/*0x1E8*/     ULONG32      pShimData;
/*0x1EC*/     ULONG32      AppCompatInfo;
/*0x1F0*/     struct _STRING32 CSDVersion;                           // 3 elements, 0x8 bytes (sizeof)
/*0x1F8*/     ULONG32      ActivationContextData;
/*0x1FC*/     ULONG32      ProcessAssemblyStorageMap;
/*0x200*/     ULONG32      SystemDefaultActivationContextData;
/*0x204*/     ULONG32      SystemAssemblyStorageMap;
/*0x208*/     ULONG32      MinimumStackCommit;
/*0x20C*/     ULONG32      FlsCallback;
/*0x210*/     struct _LIST_ENTRY32 FlsListHead;                      // 2 elements, 0x8 bytes (sizeof)
/*0x218*/     ULONG32      FlsBitmap;
/*0x21C*/     ULONG32      FlsBitmapBits[4];
/*0x22C*/     ULONG32      FlsHighIndex;
/*0x230*/     ULONG32      WerRegistrationData;
/*0x234*/     ULONG32      WerShipAssertPtr;
/*0x238*/     ULONG32      pUnused;
/*0x23C*/     ULONG32      pImageHeaderHash;
              union                                                  // 2 elements, 0x4 bytes (sizeof)
              {
/*0x240*/         ULONG32      TracingFlags;
                  struct                                             // 4 elements, 0x4 bytes (sizeof)
                  {
/*0x240*/             ULONG32      HeapTracingEnabled : 1;           // 0 BitPosition
/*0x240*/             ULONG32      CritSecTracingEnabled : 1;        // 1 BitPosition
/*0x240*/             ULONG32      LibLoaderTracingEnabled : 1;      // 2 BitPosition
/*0x240*/             ULONG32      SpareTracingBits : 29;            // 3 BitPosition
                  };
              };
/*0x248*/     UINT64       CsrServerReadOnlySharedMemoryBase;
          }PEB32, *PPEB32;

          typedef struct _PEB64                                      // 93 elements, 0x388 bytes (sizeof)
          {
/*0x000*/     UINT8        InheritedAddressSpace;
/*0x001*/     UINT8        ReadImageFileExecOptions;
/*0x002*/     UINT8        BeingDebugged;
              union                                                  // 2 elements, 0x1 bytes (sizeof)
              {
/*0x003*/         UINT8        BitField;
                  struct                                             // 6 elements, 0x1 bytes (sizeof)
                  {
/*0x003*/             UINT8        ImageUsesLargePages : 1;          // 0 BitPosition
/*0x003*/             UINT8        IsProtectedProcess : 1;           // 1 BitPosition
/*0x003*/             UINT8        IsLegacyProcess : 1;              // 2 BitPosition
/*0x003*/             UINT8        IsImageDynamicallyRelocated : 1;  // 3 BitPosition
/*0x003*/             UINT8        SkipPatchingUser32Forwarders : 1; // 4 BitPosition
/*0x003*/             UINT8        SpareBits : 3;                    // 5 BitPosition
                  };
              };
/*0x008*/     UINT64       Mutant;
/*0x010*/     UINT64       ImageBaseAddress;
/*0x018*/     UINT64       Ldr;
/*0x020*/     UINT64       ProcessParameters;
/*0x028*/     UINT64       SubSystemData;
/*0x030*/     UINT64       ProcessHeap;
/*0x038*/     UINT64       FastPebLock;
/*0x040*/     UINT64       AtlThunkSListPtr;
/*0x048*/     UINT64       IFEOKey;
              union                                                  // 2 elements, 0x4 bytes (sizeof)
              {
/*0x050*/         ULONG32      CrossProcessFlags;
                  struct                                             // 6 elements, 0x4 bytes (sizeof)
                  {
/*0x050*/             ULONG32      ProcessInJob : 1;                 // 0 BitPosition
/*0x050*/             ULONG32      ProcessInitializing : 1;          // 1 BitPosition
/*0x050*/             ULONG32      ProcessUsingVEH : 1;              // 2 BitPosition
/*0x050*/             ULONG32      ProcessUsingVCH : 1;              // 3 BitPosition
/*0x050*/             ULONG32      ProcessUsingFTH : 1;              // 4 BitPosition
/*0x050*/             ULONG32      ReservedBits0 : 27;               // 5 BitPosition
                  };
              };
              union                                                  // 2 elements, 0x8 bytes (sizeof)
              {
/*0x058*/         UINT64       KernelCallbackTable;
/*0x058*/         UINT64       UserSharedInfoPtr;
              };
/*0x060*/     ULONG32      SystemReserved[1];
/*0x064*/     ULONG32      AtlThunkSListPtr32;
/*0x068*/     UINT64       ApiSetMap;
/*0x070*/     ULONG32      TlsExpansionCounter;
/*0x074*/     UINT8        _PADDING0_[0x4];
/*0x078*/     UINT64       TlsBitmap;
/*0x080*/     ULONG32      TlsBitmapBits[2];
/*0x088*/     UINT64       ReadOnlySharedMemoryBase;
/*0x090*/     UINT64       HotpatchInformation;
/*0x098*/     UINT64       ReadOnlyStaticServerData;
/*0x0A0*/     UINT64       AnsiCodePageData;
/*0x0A8*/     UINT64       OemCodePageData;
/*0x0B0*/     UINT64       UnicodeCaseTableData;
/*0x0B8*/     ULONG32      NumberOfProcessors;
/*0x0BC*/     ULONG32      NtGlobalFlag;
/*0x0C0*/     union _LARGE_INTEGER CriticalSectionTimeout;           // 4 elements, 0x8 bytes (sizeof)
/*0x0C8*/     UINT64       HeapSegmentReserve;
/*0x0D0*/     UINT64       HeapSegmentCommit;
/*0x0D8*/     UINT64       HeapDeCommitTotalFreeThreshold;
/*0x0E0*/     UINT64       HeapDeCommitFreeBlockThreshold;
/*0x0E8*/     ULONG32      NumberOfHeaps;
/*0x0EC*/     ULONG32      MaximumNumberOfHeaps;
/*0x0F0*/     UINT64       ProcessHeaps;
/*0x0F8*/     UINT64       GdiSharedHandleTable;
/*0x100*/     UINT64       ProcessStarterHelper;
/*0x108*/     ULONG32      GdiDCAttributeList;
/*0x10C*/     UINT8        _PADDING1_[0x4];
/*0x110*/     UINT64       LoaderLock;
/*0x118*/     ULONG32      OSMajorVersion;
/*0x11C*/     ULONG32      OSMinorVersion;
/*0x120*/     UINT16       OSBuildNumber;
/*0x122*/     UINT16       OSCSDVersion;
/*0x124*/     ULONG32      OSPlatformId;
/*0x128*/     ULONG32      ImageSubsystem;
/*0x12C*/     ULONG32      ImageSubsystemMajorVersion;
/*0x130*/     ULONG32      ImageSubsystemMinorVersion;
/*0x134*/     UINT8        _PADDING2_[0x4];
/*0x138*/     UINT64       ActiveProcessAffinityMask;
/*0x140*/     ULONG32      GdiHandleBuffer[60];
/*0x230*/     UINT64       PostProcessInitRoutine;
/*0x238*/     UINT64       TlsExpansionBitmap;
/*0x240*/     ULONG32      TlsExpansionBitmapBits[32];
/*0x2C0*/     ULONG32      SessionId;
/*0x2C4*/     UINT8        _PADDING3_[0x4];
/*0x2C8*/     union _ULARGE_INTEGER AppCompatFlags;                  // 4 elements, 0x8 bytes (sizeof)
/*0x2D0*/     union _ULARGE_INTEGER AppCompatFlagsUser;              // 4 elements, 0x8 bytes (sizeof)
/*0x2D8*/     UINT64       pShimData;
/*0x2E0*/     UINT64       AppCompatInfo;
/*0x2E8*/     struct _STRING64 CSDVersion;                           // 3 elements, 0x10 bytes (sizeof)
/*0x2F8*/     UINT64       ActivationContextData;
/*0x300*/     UINT64       ProcessAssemblyStorageMap;
/*0x308*/     UINT64       SystemDefaultActivationContextData;
/*0x310*/     UINT64       SystemAssemblyStorageMap;
/*0x318*/     UINT64       MinimumStackCommit;
/*0x320*/     UINT64       FlsCallback;
/*0x328*/     struct _LIST_ENTRY64 FlsListHead;                      // 2 elements, 0x10 bytes (sizeof)
/*0x338*/     UINT64       FlsBitmap;
/*0x340*/     ULONG32      FlsBitmapBits[4];
/*0x350*/     ULONG32      FlsHighIndex;
/*0x354*/     UINT8        _PADDING4_[0x4];
/*0x358*/     UINT64       WerRegistrationData;
/*0x360*/     UINT64       WerShipAssertPtr;
/*0x368*/     UINT64       pUnused;
/*0x370*/     UINT64       pImageHeaderHash;
              union                                                  // 2 elements, 0x4 bytes (sizeof)
              {
/*0x378*/         ULONG32      TracingFlags;
                  struct                                             // 4 elements, 0x4 bytes (sizeof)
                  {
/*0x378*/             ULONG32      HeapTracingEnabled : 1;           // 0 BitPosition
/*0x378*/             ULONG32      CritSecTracingEnabled : 1;        // 1 BitPosition
/*0x378*/             ULONG32      LibLoaderTracingEnabled : 1;      // 2 BitPosition
/*0x378*/             ULONG32      SpareTracingBits : 29;            // 3 BitPosition
                  };
              };
/*0x380*/     UINT64       CsrServerReadOnlySharedMemoryBase;
          }PEB64, *PPEB64;


          typedef struct _RUNTIME_FUNCTION // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      BeginAddress;
/*0x004*/     ULONG32      EndAddress;
/*0x008*/     ULONG32      UnwindData;
          }RUNTIME_FUNCTION, *PRUNTIME_FUNCTION;

          typedef struct _DYNAMIC_FUNCTION_TABLE       // 11 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;            // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _RUNTIME_FUNCTION* FunctionTable;
/*0x018*/     union _LARGE_INTEGER TimeStamp;          // 4 elements, 0x8 bytes (sizeof)
/*0x020*/     UINT64       MinimumAddress;
/*0x028*/     UINT64       MaximumAddress;
/*0x030*/     UINT64       BaseAddress;
/*0x038*/     FUNCT_0D1D_0D30_Callback* Callback;
/*0x040*/     VOID*        Context;
/*0x048*/     UINT16*      OutOfProcessCallbackDll;
/*0x050*/     enum _FUNCTION_TABLE_TYPE Type;
/*0x054*/     ULONG32      EntryCount;
          }DYNAMIC_FUNCTION_TABLE, *PDYNAMIC_FUNCTION_TABLE;

           typedef struct _TEB                                                  // 105 elements, 0x1820 bytes (sizeof)
           {
/*0x000*/      struct _NT_TIB NtTib;                                            // 8 elements, 0x38 bytes (sizeof)
/*0x038*/      VOID*        EnvironmentPointer;
/*0x040*/      struct _CLIENT_ID ClientId;                                      // 2 elements, 0x10 bytes (sizeof)
/*0x050*/      VOID*        ActiveRpcHandle;
/*0x058*/      VOID*        ThreadLocalStoragePointer;
/*0x060*/      struct _PEB* ProcessEnvironmentBlock;
/*0x068*/      ULONG32      LastErrorValue;
/*0x06C*/      ULONG32      CountOfOwnedCriticalSections;
/*0x070*/      VOID*        CsrClientThread;
/*0x078*/      VOID*        Win32ThreadInfo;
/*0x080*/      ULONG32      User32Reserved[26];
/*0x0E8*/      ULONG32      UserReserved[5];
/*0x0FC*/      UINT8        _PADDING0_[0x4];
/*0x100*/      VOID*        WOW32Reserved;
/*0x108*/      ULONG32      CurrentLocale;
/*0x10C*/      ULONG32      FpSoftwareStatusRegister;
/*0x110*/      VOID*        SystemReserved1[54];
/*0x2C0*/      LONG32       ExceptionCode;
/*0x2C4*/      UINT8        _PADDING1_[0x4];
/*0x2C8*/      struct _ACTIVATION_CONTEXT_STACK* ActivationContextStackPointer;
/*0x2D0*/      UINT8        SpareBytes[24];
/*0x2E8*/      ULONG32      TxFsContext;
/*0x2EC*/      UINT8        _PADDING2_[0x4];
/*0x2F0*/      struct _GDI_TEB_BATCH GdiTebBatch;                               // 3 elements, 0x4E8 bytes (sizeof)
/*0x7D8*/      struct _CLIENT_ID RealClientId;                                  // 2 elements, 0x10 bytes (sizeof)
/*0x7E8*/      VOID*        GdiCachedProcessHandle;
/*0x7F0*/      ULONG32      GdiClientPID;
/*0x7F4*/      ULONG32      GdiClientTID;
/*0x7F8*/      VOID*        GdiThreadLocalInfo;
/*0x800*/      UINT64       Win32ClientInfo[62];
/*0x9F0*/      VOID*        glDispatchTable[233];
/*0x1138*/     UINT64       glReserved1[29];
/*0x1220*/     VOID*        glReserved2;
/*0x1228*/     VOID*        glSectionInfo;
/*0x1230*/     VOID*        glSection;
/*0x1238*/     VOID*        glTable;
/*0x1240*/     VOID*        glCurrentRC;
/*0x1248*/     VOID*        glContext;
/*0x1250*/     ULONG32      LastStatusValue;
/*0x1254*/     UINT8        _PADDING3_[0x4];
/*0x1258*/     struct _UNICODE_STRING StaticUnicodeString;                      // 3 elements, 0x10 bytes (sizeof)
/*0x1268*/     WCHAR        StaticUnicodeBuffer[261];
/*0x1472*/     UINT8        _PADDING4_[0x6];
/*0x1478*/     VOID*        DeallocationStack;
/*0x1480*/     VOID*        TlsSlots[64];
/*0x1680*/     struct _LIST_ENTRY TlsLinks;                                     // 2 elements, 0x10 bytes (sizeof)
/*0x1690*/     VOID*        Vdm;
/*0x1698*/     VOID*        ReservedForNtRpc;
/*0x16A0*/     VOID*        DbgSsReserved[2];
/*0x16B0*/     ULONG32      HardErrorMode;
/*0x16B4*/     UINT8        _PADDING5_[0x4];
/*0x16B8*/     VOID*        Instrumentation[11];
/*0x1710*/     struct _GUID ActivityId;                                         // 4 elements, 0x10 bytes (sizeof)
/*0x1720*/     VOID*        SubProcessTag;
/*0x1728*/     VOID*        EtwLocalData;
/*0x1730*/     VOID*        EtwTraceData;
/*0x1738*/     VOID*        WinSockData;
/*0x1740*/     ULONG32      GdiBatchCount;
               union                                                            // 3 elements, 0x4 bytes (sizeof)
               {
/*0x1744*/         struct _PROCESSOR_NUMBER CurrentIdealProcessor;              // 3 elements, 0x4 bytes (sizeof)
/*0x1744*/         ULONG32      IdealProcessorValue;
                   struct                                                       // 4 elements, 0x4 bytes (sizeof)
                   {
/*0x1744*/             UINT8        ReservedPad0;
/*0x1745*/             UINT8        ReservedPad1;
/*0x1746*/             UINT8        ReservedPad2;
/*0x1747*/             UINT8        IdealProcessor;
                   };
               };
/*0x1748*/     ULONG32      GuaranteedStackBytes;
/*0x174C*/     UINT8        _PADDING6_[0x4];
/*0x1750*/     VOID*        ReservedForPerf;
/*0x1758*/     VOID*        ReservedForOle;
/*0x1760*/     ULONG32      WaitingOnLoaderLock;
/*0x1764*/     UINT8        _PADDING7_[0x4];
/*0x1768*/     VOID*        SavedPriorityState;
/*0x1770*/     UINT64       ReservedForCodeCoverage;
/*0x1778*/     VOID*        ThreadPoolData;
/*0x1780*/     VOID**       TlsExpansionSlots;
/*0x1788*/     VOID*        DeallocationBStore;
/*0x1790*/     VOID*        BStoreLimit;
/*0x1798*/     ULONG32      MuiGeneration;
/*0x179C*/     ULONG32      IsImpersonating;
/*0x17A0*/     VOID*        NlsCache;
/*0x17A8*/     VOID*        pShimData;
/*0x17B0*/     UINT16       HeapVirtualAffinity;
/*0x17B2*/     UINT16       LowFragHeapDataSlot;
/*0x17B4*/     UINT8        _PADDING8_[0x4];
/*0x17B8*/     VOID*        CurrentTransactionHandle;
/*0x17C0*/     struct _TEB_ACTIVE_FRAME* ActiveFrame;
/*0x17C8*/     VOID*        FlsData;
/*0x17D0*/     VOID*        PreferredLanguages;
/*0x17D8*/     VOID*        UserPrefLanguages;
/*0x17E0*/     VOID*        MergedPrefLanguages;
/*0x17E8*/     ULONG32      MuiImpersonation;
               union                                                            // 2 elements, 0x2 bytes (sizeof)
               {
/*0x17EC*/         UINT16       CrossTebFlags;
/*0x17EC*/         UINT16       SpareCrossTebBits : 16;                         // 0 BitPosition
               };
               union                                                            // 2 elements, 0x2 bytes (sizeof)
               {
/*0x17EE*/         UINT16       SameTebFlags;
                   struct                                                       // 14 elements, 0x2 bytes (sizeof)
                   {
/*0x17EE*/             UINT16       SafeThunkCall : 1;                          // 0 BitPosition
/*0x17EE*/             UINT16       InDebugPrint : 1;                           // 1 BitPosition
/*0x17EE*/             UINT16       HasFiberData : 1;                           // 2 BitPosition
/*0x17EE*/             UINT16       SkipThreadAttach : 1;                       // 3 BitPosition
/*0x17EE*/             UINT16       WerInShipAssertCode : 1;                    // 4 BitPosition
/*0x17EE*/             UINT16       RanProcessInit : 1;                         // 5 BitPosition
/*0x17EE*/             UINT16       ClonedThread : 1;                           // 6 BitPosition
/*0x17EE*/             UINT16       SuppressDebugMsg : 1;                       // 7 BitPosition
/*0x17EE*/             UINT16       DisableUserStackWalk : 1;                   // 8 BitPosition
/*0x17EE*/             UINT16       RtlExceptionAttached : 1;                   // 9 BitPosition
/*0x17EE*/             UINT16       InitialThread : 1;                          // 10 BitPosition
/*0x17EE*/             UINT16       SessionAware : 1;                           // 11 BitPosition
/*0x17EE*/             UINT16       DisabledStackCheck : 1;                     // 12 BitPosition
/*0x17EE*/             UINT16       SpareSameTebBits : 3;                       // 13 BitPosition
                   };
               };
/*0x17F0*/     VOID*        TxnScopeEnterCallback;
/*0x17F8*/     VOID*        TxnScopeExitCallback;
/*0x1800*/     VOID*        TxnScopeContext;
/*0x1808*/     ULONG32      LockCount;
/*0x180C*/     ULONG32      SpareUlong0;
/*0x1810*/     VOID*        ResourceRetValue;
/*0x1818*/     VOID*        ReservedForWdf;
           }TEB, *PTEB;

          typedef struct _TEB_ACTIVE_FRAME               // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flags;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _TEB_ACTIVE_FRAME* Previous;
/*0x010*/     struct _TEB_ACTIVE_FRAME_CONTEXT* Context;
          }TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;

          typedef struct _TEB_ACTIVE_FRAME_CONTEXT // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flags;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     CHAR*        FrameName;
          }TEB_ACTIVE_FRAME_CONTEXT, *PTEB_ACTIVE_FRAME_CONTEXT;

          typedef struct _TEB32                                   // 103 elements, 0xFE8 bytes (sizeof)
          {
/*0x000*/     struct _NT_TIB32 NtTib;                             // 8 elements, 0x1C bytes (sizeof)
/*0x01C*/     ULONG32      EnvironmentPointer;
/*0x020*/     struct _CLIENT_ID32 ClientId;                       // 2 elements, 0x8 bytes (sizeof)
/*0x028*/     ULONG32      ActiveRpcHandle;
/*0x02C*/     ULONG32      ThreadLocalStoragePointer;
/*0x030*/     ULONG32      ProcessEnvironmentBlock;
/*0x034*/     ULONG32      LastErrorValue;
/*0x038*/     ULONG32      CountOfOwnedCriticalSections;
/*0x03C*/     ULONG32      CsrClientThread;
/*0x040*/     ULONG32      Win32ThreadInfo;
/*0x044*/     ULONG32      User32Reserved[26];
/*0x0AC*/     ULONG32      UserReserved[5];
/*0x0C0*/     ULONG32      WOW32Reserved;
/*0x0C4*/     ULONG32      CurrentLocale;
/*0x0C8*/     ULONG32      FpSoftwareStatusRegister;
/*0x0CC*/     ULONG32      SystemReserved1[54];
/*0x1A4*/     LONG32       ExceptionCode;
/*0x1A8*/     ULONG32      ActivationContextStackPointer;
/*0x1AC*/     UINT8        SpareBytes[36];
/*0x1D0*/     ULONG32      TxFsContext;
/*0x1D4*/     struct _GDI_TEB_BATCH32 GdiTebBatch;                // 3 elements, 0x4E0 bytes (sizeof)
/*0x6B4*/     struct _CLIENT_ID32 RealClientId;                   // 2 elements, 0x8 bytes (sizeof)
/*0x6BC*/     ULONG32      GdiCachedProcessHandle;
/*0x6C0*/     ULONG32      GdiClientPID;
/*0x6C4*/     ULONG32      GdiClientTID;
/*0x6C8*/     ULONG32      GdiThreadLocalInfo;
/*0x6CC*/     ULONG32      Win32ClientInfo[62];
/*0x7C4*/     ULONG32      glDispatchTable[233];
/*0xB68*/     ULONG32      glReserved1[29];
/*0xBDC*/     ULONG32      glReserved2;
/*0xBE0*/     ULONG32      glSectionInfo;
/*0xBE4*/     ULONG32      glSection;
/*0xBE8*/     ULONG32      glTable;
/*0xBEC*/     ULONG32      glCurrentRC;
/*0xBF0*/     ULONG32      glContext;
/*0xBF4*/     ULONG32      LastStatusValue;
/*0xBF8*/     struct _STRING32 StaticUnicodeString;               // 3 elements, 0x8 bytes (sizeof)
/*0xC00*/     WCHAR        StaticUnicodeBuffer[261];
/*0xE0A*/     UINT8        _PADDING0_[0x2];
/*0xE0C*/     ULONG32      DeallocationStack;
/*0xE10*/     ULONG32      TlsSlots[64];
/*0xF10*/     struct _LIST_ENTRY32 TlsLinks;                      // 2 elements, 0x8 bytes (sizeof)
/*0xF18*/     ULONG32      Vdm;
/*0xF1C*/     ULONG32      ReservedForNtRpc;
/*0xF20*/     ULONG32      DbgSsReserved[2];
/*0xF28*/     ULONG32      HardErrorMode;
/*0xF2C*/     ULONG32      Instrumentation[9];
/*0xF50*/     struct _GUID ActivityId;                            // 4 elements, 0x10 bytes (sizeof)
/*0xF60*/     ULONG32      SubProcessTag;
/*0xF64*/     ULONG32      EtwLocalData;
/*0xF68*/     ULONG32      EtwTraceData;
/*0xF6C*/     ULONG32      WinSockData;
/*0xF70*/     ULONG32      GdiBatchCount;
              union                                               // 3 elements, 0x4 bytes (sizeof)
              {
/*0xF74*/         struct _PROCESSOR_NUMBER CurrentIdealProcessor; // 3 elements, 0x4 bytes (sizeof)
/*0xF74*/         ULONG32      IdealProcessorValue;
                  struct                                          // 4 elements, 0x4 bytes (sizeof)
                  {
/*0xF74*/             UINT8        ReservedPad0;
/*0xF75*/             UINT8        ReservedPad1;
/*0xF76*/             UINT8        ReservedPad2;
/*0xF77*/             UINT8        IdealProcessor;
                  };
              };
/*0xF78*/     ULONG32      GuaranteedStackBytes;
/*0xF7C*/     ULONG32      ReservedForPerf;
/*0xF80*/     ULONG32      ReservedForOle;
/*0xF84*/     ULONG32      WaitingOnLoaderLock;
/*0xF88*/     ULONG32      SavedPriorityState;
/*0xF8C*/     ULONG32      ReservedForCodeCoverage;
/*0xF90*/     ULONG32      ThreadPoolData;
/*0xF94*/     ULONG32      TlsExpansionSlots;
/*0xF98*/     ULONG32      MuiGeneration;
/*0xF9C*/     ULONG32      IsImpersonating;
/*0xFA0*/     ULONG32      NlsCache;
/*0xFA4*/     ULONG32      pShimData;
/*0xFA8*/     UINT16       HeapVirtualAffinity;
/*0xFAA*/     UINT16       LowFragHeapDataSlot;
/*0xFAC*/     ULONG32      CurrentTransactionHandle;
/*0xFB0*/     ULONG32      ActiveFrame;
/*0xFB4*/     ULONG32      FlsData;
/*0xFB8*/     ULONG32      PreferredLanguages;
/*0xFBC*/     ULONG32      UserPrefLanguages;
/*0xFC0*/     ULONG32      MergedPrefLanguages;
/*0xFC4*/     ULONG32      MuiImpersonation;
              union                                               // 2 elements, 0x2 bytes (sizeof)
              {
/*0xFC8*/         UINT16       CrossTebFlags;
/*0xFC8*/         UINT16       SpareCrossTebBits : 16;            // 0 BitPosition
              };
              union                                               // 2 elements, 0x2 bytes (sizeof)
              {
/*0xFCA*/         UINT16       SameTebFlags;
                  struct                                          // 14 elements, 0x2 bytes (sizeof)
                  {
/*0xFCA*/             UINT16       SafeThunkCall : 1;             // 0 BitPosition
/*0xFCA*/             UINT16       InDebugPrint : 1;              // 1 BitPosition
/*0xFCA*/             UINT16       HasFiberData : 1;              // 2 BitPosition
/*0xFCA*/             UINT16       SkipThreadAttach : 1;          // 3 BitPosition
/*0xFCA*/             UINT16       WerInShipAssertCode : 1;       // 4 BitPosition
/*0xFCA*/             UINT16       RanProcessInit : 1;            // 5 BitPosition
/*0xFCA*/             UINT16       ClonedThread : 1;              // 6 BitPosition
/*0xFCA*/             UINT16       SuppressDebugMsg : 1;          // 7 BitPosition
/*0xFCA*/             UINT16       DisableUserStackWalk : 1;      // 8 BitPosition
/*0xFCA*/             UINT16       RtlExceptionAttached : 1;      // 9 BitPosition
/*0xFCA*/             UINT16       InitialThread : 1;             // 10 BitPosition
/*0xFCA*/             UINT16       SessionAware : 1;              // 11 BitPosition
/*0xFCA*/             UINT16       DisabledStackCheck : 1;        // 12 BitPosition
/*0xFCA*/             UINT16       SpareSameTebBits : 3;          // 13 BitPosition
                  };
              };
/*0xFCC*/     ULONG32      TxnScopeEnterCallback;
/*0xFD0*/     ULONG32      TxnScopeExitCallback;
/*0xFD4*/     ULONG32      TxnScopeContext;
/*0xFD8*/     ULONG32      LockCount;
/*0xFDC*/     ULONG32      SpareUlong0;
/*0xFE0*/     ULONG32      ResourceRetValue;
/*0xFE4*/     ULONG32      ReservedForWdf;
          }TEB32, *PTEB32;

           typedef struct _TEB64                                   // 105 elements, 0x1820 bytes (sizeof)
           {
/*0x000*/      struct _NT_TIB64 NtTib;                             // 8 elements, 0x38 bytes (sizeof)
/*0x038*/      UINT64       EnvironmentPointer;
/*0x040*/      struct _CLIENT_ID64 ClientId;                       // 2 elements, 0x10 bytes (sizeof)
/*0x050*/      UINT64       ActiveRpcHandle;
/*0x058*/      UINT64       ThreadLocalStoragePointer;
/*0x060*/      UINT64       ProcessEnvironmentBlock;
/*0x068*/      ULONG32      LastErrorValue;
/*0x06C*/      ULONG32      CountOfOwnedCriticalSections;
/*0x070*/      UINT64       CsrClientThread;
/*0x078*/      UINT64       Win32ThreadInfo;
/*0x080*/      ULONG32      User32Reserved[26];
/*0x0E8*/      ULONG32      UserReserved[5];
/*0x0FC*/      UINT8        _PADDING0_[0x4];
/*0x100*/      UINT64       WOW32Reserved;
/*0x108*/      ULONG32      CurrentLocale;
/*0x10C*/      ULONG32      FpSoftwareStatusRegister;
/*0x110*/      UINT64       SystemReserved1[54];
/*0x2C0*/      LONG32       ExceptionCode;
/*0x2C4*/      UINT8        _PADDING1_[0x4];
/*0x2C8*/      UINT64       ActivationContextStackPointer;
/*0x2D0*/      UINT8        SpareBytes[24];
/*0x2E8*/      ULONG32      TxFsContext;
/*0x2EC*/      UINT8        _PADDING2_[0x4];
/*0x2F0*/      struct _GDI_TEB_BATCH64 GdiTebBatch;                // 3 elements, 0x4E8 bytes (sizeof)
/*0x7D8*/      struct _CLIENT_ID64 RealClientId;                   // 2 elements, 0x10 bytes (sizeof)
/*0x7E8*/      UINT64       GdiCachedProcessHandle;
/*0x7F0*/      ULONG32      GdiClientPID;
/*0x7F4*/      ULONG32      GdiClientTID;
/*0x7F8*/      UINT64       GdiThreadLocalInfo;
/*0x800*/      UINT64       Win32ClientInfo[62];
/*0x9F0*/      UINT64       glDispatchTable[233];
/*0x1138*/     UINT64       glReserved1[29];
/*0x1220*/     UINT64       glReserved2;
/*0x1228*/     UINT64       glSectionInfo;
/*0x1230*/     UINT64       glSection;
/*0x1238*/     UINT64       glTable;
/*0x1240*/     UINT64       glCurrentRC;
/*0x1248*/     UINT64       glContext;
/*0x1250*/     ULONG32      LastStatusValue;
/*0x1254*/     UINT8        _PADDING3_[0x4];
/*0x1258*/     struct _STRING64 StaticUnicodeString;               // 3 elements, 0x10 bytes (sizeof)
/*0x1268*/     WCHAR        StaticUnicodeBuffer[261];
/*0x1472*/     UINT8        _PADDING4_[0x6];
/*0x1478*/     UINT64       DeallocationStack;
/*0x1480*/     UINT64       TlsSlots[64];
/*0x1680*/     struct _LIST_ENTRY64 TlsLinks;                      // 2 elements, 0x10 bytes (sizeof)
/*0x1690*/     UINT64       Vdm;
/*0x1698*/     UINT64       ReservedForNtRpc;
/*0x16A0*/     UINT64       DbgSsReserved[2];
/*0x16B0*/     ULONG32      HardErrorMode;
/*0x16B4*/     UINT8        _PADDING5_[0x4];
/*0x16B8*/     UINT64       Instrumentation[11];
/*0x1710*/     struct _GUID ActivityId;                            // 4 elements, 0x10 bytes (sizeof)
/*0x1720*/     UINT64       SubProcessTag;
/*0x1728*/     UINT64       EtwLocalData;
/*0x1730*/     UINT64       EtwTraceData;
/*0x1738*/     UINT64       WinSockData;
/*0x1740*/     ULONG32      GdiBatchCount;
               union                                               // 3 elements, 0x4 bytes (sizeof)
               {
/*0x1744*/         struct _PROCESSOR_NUMBER CurrentIdealProcessor; // 3 elements, 0x4 bytes (sizeof)
/*0x1744*/         ULONG32      IdealProcessorValue;
                   struct                                          // 4 elements, 0x4 bytes (sizeof)
                   {
/*0x1744*/             UINT8        ReservedPad0;
/*0x1745*/             UINT8        ReservedPad1;
/*0x1746*/             UINT8        ReservedPad2;
/*0x1747*/             UINT8        IdealProcessor;
                   };
               };
/*0x1748*/     ULONG32      GuaranteedStackBytes;
/*0x174C*/     UINT8        _PADDING6_[0x4];
/*0x1750*/     UINT64       ReservedForPerf;
/*0x1758*/     UINT64       ReservedForOle;
/*0x1760*/     ULONG32      WaitingOnLoaderLock;
/*0x1764*/     UINT8        _PADDING7_[0x4];
/*0x1768*/     UINT64       SavedPriorityState;
/*0x1770*/     UINT64       ReservedForCodeCoverage;
/*0x1778*/     UINT64       ThreadPoolData;
/*0x1780*/     UINT64       TlsExpansionSlots;
/*0x1788*/     UINT64       DeallocationBStore;
/*0x1790*/     UINT64       BStoreLimit;
/*0x1798*/     ULONG32      MuiGeneration;
/*0x179C*/     ULONG32      IsImpersonating;
/*0x17A0*/     UINT64       NlsCache;
/*0x17A8*/     UINT64       pShimData;
/*0x17B0*/     UINT16       HeapVirtualAffinity;
/*0x17B2*/     UINT16       LowFragHeapDataSlot;
/*0x17B4*/     UINT8        _PADDING8_[0x4];
/*0x17B8*/     UINT64       CurrentTransactionHandle;
/*0x17C0*/     UINT64       ActiveFrame;
/*0x17C8*/     UINT64       FlsData;
/*0x17D0*/     UINT64       PreferredLanguages;
/*0x17D8*/     UINT64       UserPrefLanguages;
/*0x17E0*/     UINT64       MergedPrefLanguages;
/*0x17E8*/     ULONG32      MuiImpersonation;
               union                                               // 2 elements, 0x2 bytes (sizeof)
               {
/*0x17EC*/         UINT16       CrossTebFlags;
/*0x17EC*/         UINT16       SpareCrossTebBits : 16;            // 0 BitPosition
               };
               union                                               // 2 elements, 0x2 bytes (sizeof)
               {
/*0x17EE*/         UINT16       SameTebFlags;
                   struct                                          // 14 elements, 0x2 bytes (sizeof)
                   {
/*0x17EE*/             UINT16       SafeThunkCall : 1;             // 0 BitPosition
/*0x17EE*/             UINT16       InDebugPrint : 1;              // 1 BitPosition
/*0x17EE*/             UINT16       HasFiberData : 1;              // 2 BitPosition
/*0x17EE*/             UINT16       SkipThreadAttach : 1;          // 3 BitPosition
/*0x17EE*/             UINT16       WerInShipAssertCode : 1;       // 4 BitPosition
/*0x17EE*/             UINT16       RanProcessInit : 1;            // 5 BitPosition
/*0x17EE*/             UINT16       ClonedThread : 1;              // 6 BitPosition
/*0x17EE*/             UINT16       SuppressDebugMsg : 1;          // 7 BitPosition
/*0x17EE*/             UINT16       DisableUserStackWalk : 1;      // 8 BitPosition
/*0x17EE*/             UINT16       RtlExceptionAttached : 1;      // 9 BitPosition
/*0x17EE*/             UINT16       InitialThread : 1;             // 10 BitPosition
/*0x17EE*/             UINT16       SessionAware : 1;              // 11 BitPosition
/*0x17EE*/             UINT16       DisabledStackCheck : 1;        // 12 BitPosition
/*0x17EE*/             UINT16       SpareSameTebBits : 3;          // 13 BitPosition
                   };
               };
/*0x17F0*/     UINT64       TxnScopeEnterCallback;
/*0x17F8*/     UINT64       TxnScopeExitCallback;
/*0x1800*/     UINT64       TxnScopeContext;
/*0x1808*/     ULONG32      LockCount;
/*0x180C*/     ULONG32      SpareUlong0;
/*0x1810*/     UINT64       ResourceRetValue;
/*0x1818*/     UINT64       ReservedForWdf;
           }TEB64, *PTEB64;

          typedef struct _UNEXPECTED_INTERRUPT
          { // packed!!!
/*0x000*/     UINT8        PushImmOp;
/*0x001*/     ULONG32      PushImm;
/*0x005*/     UINT8        PushRbp;
/*0x006*/     UINT8        JmpOp;
/*0x007*/     LONG32       JmpOffset;
/*0x00B*/     UINT8        _PADDING0_[0x5];
          }UNEXPECTED_INTERRUPT, *PUNEXPECTED_INTERRUPT;

          typedef struct _XSAVE_AREA            // 2 elements, 0x240 bytes (sizeof)
          {
/*0x000*/     struct _XSAVE_FORMAT LegacyState; // 16 elements, 0x200 bytes (sizeof)
/*0x200*/     struct _XSAVE_AREA_HEADER Header; // 2 elements, 0x40 bytes (sizeof)
          }XSAVE_AREA, *PXSAVE_AREA;

          typedef struct _XSAVE_AREA_HEADER // 2 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     UINT64       Mask;
/*0x008*/     UINT64       Reserved[7];
          }XSAVE_AREA_HEADER, *PXSAVE_AREA_HEADER;

          typedef struct _XSAVE_FORMAT         // 16 elements, 0x200 bytes (sizeof)
          {
/*0x000*/     UINT16       ControlWord;
/*0x002*/     UINT16       StatusWord;
/*0x004*/     UINT8        TagWord;
/*0x005*/     UINT8        Reserved1;
/*0x006*/     UINT16       ErrorOpcode;
/*0x008*/     ULONG32      ErrorOffset;
/*0x00C*/     UINT16       ErrorSelector;
/*0x00E*/     UINT16       Reserved2;
/*0x010*/     ULONG32      DataOffset;
/*0x014*/     UINT16       DataSelector;
/*0x016*/     UINT16       Reserved3;
/*0x018*/     ULONG32      MxCsr;
/*0x01C*/     ULONG32      MxCsr_Mask;
/*0x020*/     struct _M128A FloatRegisters[8];
/*0x0A0*/     struct _M128A XmmRegisters[16];
/*0x1A0*/     UINT8        Reserved4[96];
          }XSAVE_FORMAT, *PXSAVE_FORMAT;

typedef enum _EXCEPTION_DISPOSITION  // 4 elements, 0x4 bytes
{
    ExceptionContinueExecution = 0 /*0x0*/,
    ExceptionContinueSearch    = 1 /*0x1*/,
    ExceptionNestedException   = 2 /*0x2*/,
    ExceptionCollidedUnwind    = 3 /*0x3*/
}EXCEPTION_DISPOSITION, *PEXCEPTION_DISPOSITION;

typedef enum _FUNCTION_TABLE_TYPE  // 4 elements, 0x4 bytes
{
    RF_SORTED         = 0 /*0x0*/,
    RF_UNSORTED       = 1 /*0x1*/,
    RF_CALLBACK       = 2 /*0x2*/,
    RF_KERNEL_DYNAMIC = 3 /*0x3*/
}FUNCTION_TABLE_TYPE, *PFUNCTION_TABLE_TYPE;

typedef enum _KENLISTMENT_STATE  // 20 elements, 0x4 bytes
{
    KEnlistmentUninitialized         = 0 /*0x0*/,
    KEnlistmentActive                = 256 /*0x100*/,
    KEnlistmentPreparing             = 257 /*0x101*/,
    KEnlistmentPrepared              = 258 /*0x102*/,
    KEnlistmentInDoubt               = 259 /*0x103*/,
    KEnlistmentCommitted             = 260 /*0x104*/,
    KEnlistmentCommittedNotify       = 261 /*0x105*/,
    KEnlistmentCommitRequested       = 262 /*0x106*/,
    KEnlistmentAborted               = 263 /*0x107*/,
    KEnlistmentDelegated             = 264 /*0x108*/,
    KEnlistmentDelegatedDisconnected = 265 /*0x109*/,
    KEnlistmentPrePreparing          = 266 /*0x10A*/,
    KEnlistmentForgotten             = 267 /*0x10B*/,
    KEnlistmentRecovering            = 268 /*0x10C*/,
    KEnlistmentAborting              = 269 /*0x10D*/,
    KEnlistmentReadOnly              = 270 /*0x10E*/,
    KEnlistmentOutcomeUnavailable    = 271 /*0x10F*/,
    KEnlistmentOffline               = 272 /*0x110*/,
    KEnlistmentPrePrepared           = 273 /*0x111*/,
    KEnlistmentInitialized           = 274 /*0x112*/
}KENLISTMENT_STATE, *PKENLISTMENT_STATE;

typedef enum _KINTERRUPT_MODE  // 2 elements, 0x4 bytes
{
    LevelSensitive = 0 /*0x0*/,
    Latched        = 1 /*0x1*/
}KINTERRUPT_MODE, *PKINTERRUPT_MODE;

typedef enum _KINTERRUPT_POLARITY  // 6 elements, 0x4 bytes
{
    InterruptPolarityUnknown = 0 /*0x0*/,
    InterruptActiveHigh      = 1 /*0x1*/,
    InterruptRisingEdge      = 1 /*0x1*/,
    InterruptActiveLow       = 2 /*0x2*/,
    InterruptFallingEdge     = 2 /*0x2*/,
    InterruptActiveBoth      = 3 /*0x3*/
}KINTERRUPT_POLARITY, *PKINTERRUPT_POLARITY;

typedef enum _KOBJECTS  // 26 elements, 0x4 bytes
{
    EventNotificationObject    = 0 /*0x0*/,
    EventSynchronizationObject = 1 /*0x1*/,
    MutantObject               = 2 /*0x2*/,
    ProcessObject              = 3 /*0x3*/,
    QueueObject                = 4 /*0x4*/,
    SemaphoreObject            = 5 /*0x5*/,
    ThreadObject               = 6 /*0x6*/,
    GateObject                 = 7 /*0x7*/,
    TimerNotificationObject    = 8 /*0x8*/,
    TimerSynchronizationObject = 9 /*0x9*/,
    Spare2Object               = 10 /*0xA*/,
    Spare3Object               = 11 /*0xB*/,
    Spare4Object               = 12 /*0xC*/,
    Spare5Object               = 13 /*0xD*/,
    Spare6Object               = 14 /*0xE*/,
    Spare7Object               = 15 /*0xF*/,
    Spare8Object               = 16 /*0x10*/,
    ProfileCallbackObject      = 17 /*0x11*/,
    ApcObject                  = 18 /*0x12*/,
    DpcObject                  = 19 /*0x13*/,
    DeviceQueueObject          = 20 /*0x14*/,
    EventPairObject            = 21 /*0x15*/,
    InterruptObject            = 22 /*0x16*/,
    ProfileObject              = 23 /*0x17*/,
    ThreadedDpcObject          = 24 /*0x18*/,
    MaximumKernelObject        = 25 /*0x19*/
}KOBJECTS, *PKOBJECTS;

typedef enum _KPROCESS_STATE  // 7 elements, 0x4 bytes
{
    ProcessInMemory      = 0 /*0x0*/,
    ProcessOutOfMemory   = 1 /*0x1*/,
    ProcessInTransition  = 2 /*0x2*/,
    ProcessOutTransition = 3 /*0x3*/,
    ProcessInSwap        = 4 /*0x4*/,
    ProcessOutSwap       = 5 /*0x5*/,
    ProcessAllSwapStates = 6 /*0x6*/
}KPROCESS_STATE, *PKPROCESS_STATE;

typedef enum _KPROFILE_SOURCE  // 25 elements, 0x4 bytes
{
    ProfileTime                 = 0 /*0x0*/,
    ProfileAlignmentFixup       = 1 /*0x1*/,
    ProfileTotalIssues          = 2 /*0x2*/,
    ProfilePipelineDry          = 3 /*0x3*/,
    ProfileLoadInstructions     = 4 /*0x4*/,
    ProfilePipelineFrozen       = 5 /*0x5*/,
    ProfileBranchInstructions   = 6 /*0x6*/,
    ProfileTotalNonissues       = 7 /*0x7*/,
    ProfileDcacheMisses         = 8 /*0x8*/,
    ProfileIcacheMisses         = 9 /*0x9*/,
    ProfileCacheMisses          = 10 /*0xA*/,
    ProfileBranchMispredictions = 11 /*0xB*/,
    ProfileStoreInstructions    = 12 /*0xC*/,
    ProfileFpInstructions       = 13 /*0xD*/,
    ProfileIntegerInstructions  = 14 /*0xE*/,
    Profile2Issue               = 15 /*0xF*/,
    Profile3Issue               = 16 /*0x10*/,
    Profile4Issue               = 17 /*0x11*/,
    ProfileSpecialInstructions  = 18 /*0x12*/,
    ProfileTotalCycles          = 19 /*0x13*/,
    ProfileIcacheIssues         = 20 /*0x14*/,
    ProfileDcacheAccesses       = 21 /*0x15*/,
    ProfileMemoryBarrierCycles  = 22 /*0x16*/,
    ProfileLoadLinkedIssues     = 23 /*0x17*/,
    ProfileMaximum              = 24 /*0x18*/
}KPROFILE_SOURCE, *PKPROFILE_SOURCE;

typedef enum _KRESOURCEMANAGER_STATE  // 3 elements, 0x4 bytes
{
    KResourceManagerUninitialized = 0 /*0x0*/,
    KResourceManagerOffline       = 1 /*0x1*/,
    KResourceManagerOnline        = 2 /*0x2*/
}KRESOURCEMANAGER_STATE, *PKRESOURCEMANAGER_STATE;

typedef enum _KTHREAD_STATE  // 9 elements, 0x4 bytes
{
    Initialized      = 0 /*0x0*/,
    Ready            = 1 /*0x1*/,
    Running          = 2 /*0x2*/,
    Standby          = 3 /*0x3*/,
    Terminated       = 4 /*0x4*/,
    Waiting          = 5 /*0x5*/,
    Transition       = 6 /*0x6*/,
    DeferredReady    = 7 /*0x7*/,
    GateWaitObsolete = 8 /*0x8*/
}KTHREAD_STATE, *PKTHREAD_STATE;

typedef enum _KTRANSACTION_OUTCOME  // 5 elements, 0x4 bytes
{
    KTxOutcomeUninitialized = 0 /*0x0*/,
    KTxOutcomeUndetermined  = 1 /*0x1*/,
    KTxOutcomeCommitted     = 2 /*0x2*/,
    KTxOutcomeAborted       = 3 /*0x3*/,
    KTxOutcomeUnavailable   = 4 /*0x4*/
}KTRANSACTION_OUTCOME, *PKTRANSACTION_OUTCOME;

typedef enum _KTRANSACTION_STATE  // 12 elements, 0x4 bytes
{
    KTransactionUninitialized = 0 /*0x0*/,
    KTransactionActive        = 1 /*0x1*/,
    KTransactionPreparing     = 2 /*0x2*/,
    KTransactionPrepared      = 3 /*0x3*/,
    KTransactionInDoubt       = 4 /*0x4*/,
    KTransactionCommitted     = 5 /*0x5*/,
    KTransactionAborted       = 6 /*0x6*/,
    KTransactionDelegated     = 7 /*0x7*/,
    KTransactionPrePreparing  = 8 /*0x8*/,
    KTransactionForgotten     = 9 /*0x9*/,
    KTransactionRecovering    = 10 /*0xA*/,
    KTransactionPrePrepared   = 11 /*0xB*/
}KTRANSACTION_STATE, *PKTRANSACTION_STATE;

typedef enum _KWAIT_BLOCK_STATE  // 5 elements, 0x4 bytes
{
    WaitBlockBypassStart    = 0 /*0x0*/,
    WaitBlockBypassComplete = 1 /*0x1*/,
    WaitBlockActive         = 2 /*0x2*/,
    WaitBlockInactive       = 3 /*0x3*/,
    WaitBlockAllStates      = 4 /*0x4*/
}KWAIT_BLOCK_STATE, *PKWAIT_BLOCK_STATE;

typedef enum _KWAIT_REASON  // 40 elements, 0x4 bytes
{
    Executive         = 0 /*0x0*/,
    FreePage          = 1 /*0x1*/,
    PageIn            = 2 /*0x2*/,
    PoolAllocation    = 3 /*0x3*/,
    DelayExecution    = 4 /*0x4*/,
    Suspended         = 5 /*0x5*/,
    UserRequest       = 6 /*0x6*/,
    WrExecutive       = 7 /*0x7*/,
    WrFreePage        = 8 /*0x8*/,
    WrPageIn          = 9 /*0x9*/,
    WrPoolAllocation  = 10 /*0xA*/,
    WrDelayExecution  = 11 /*0xB*/,
    WrSuspended       = 12 /*0xC*/,
    WrUserRequest     = 13 /*0xD*/,
    WrEventPair       = 14 /*0xE*/,
    WrQueue           = 15 /*0xF*/,
    WrLpcReceive      = 16 /*0x10*/,
    WrLpcReply        = 17 /*0x11*/,
    WrVirtualMemory   = 18 /*0x12*/,
    WrPageOut         = 19 /*0x13*/,
    WrRendezvous      = 20 /*0x14*/,
    WrKeyedEvent      = 21 /*0x15*/,
    WrTerminated      = 22 /*0x16*/,
    WrProcessInSwap   = 23 /*0x17*/,
    WrCpuRateControl  = 24 /*0x18*/,
    WrCalloutStack    = 25 /*0x19*/,
    WrKernel          = 26 /*0x1A*/,
    WrResource        = 27 /*0x1B*/,
    WrPushLock        = 28 /*0x1C*/,
    WrMutex           = 29 /*0x1D*/,
    WrQuantumEnd      = 30 /*0x1E*/,
    WrDispatchInt     = 31 /*0x1F*/,
    WrPreempted       = 32 /*0x20*/,
    WrYieldExecution  = 33 /*0x21*/,
    WrFastMutex       = 34 /*0x22*/,
    WrGuardedMutex    = 35 /*0x23*/,
    WrRundown         = 36 /*0x24*/,
    WrAlertByThreadId = 37 /*0x25*/,
    WrDeferredPreempt = 38 /*0x26*/,
    MaximumWaitReason = 39 /*0x27*/
}KWAIT_REASON, *PKWAIT_REASON;

typedef enum _KWAIT_STATE  // 4 elements, 0x4 bytes
{
    WaitInProgress   = 0 /*0x0*/,
    WaitCommitted    = 1 /*0x1*/,
    WaitAborted      = 2 /*0x2*/,
    MaximumWaitState = 3 /*0x3*/
}KWAIT_STATE, *PKWAIT_STATE;

typedef enum _MODE  // 3 elements, 0x4 bytes
{
    KernelMode  = 0 /*0x0*/,
    UserMode    = 1 /*0x1*/,
    MaximumMode = 2 /*0x2*/
}MODE, *PMODE;

          typedef struct _FAST_MUTEX        // 5 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     LONG32       Count;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        Owner;
/*0x010*/     ULONG32      Contention;
/*0x014*/     UINT8        _PADDING1_[0x4];
/*0x018*/     struct _KEVENT Event;         // 1 elements, 0x18 bytes (sizeof)
/*0x030*/     ULONG32      OldIrql;
/*0x034*/     UINT8        _PADDING2_[0x4];
          }FAST_MUTEX, *PFAST_MUTEX;

          typedef struct _GROUP_AFFINITY // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Mask;
/*0x008*/     UINT16       Group;
/*0x00A*/     UINT16       Reserved[3];
          }GROUP_AFFINITY, *PGROUP_AFFINITY;

typedef enum _EVENT_TYPE  // 2 elements, 0x4 bytes
{
    NotificationEvent    = 0 /*0x0*/,
    SynchronizationEvent = 1 /*0x1*/
}EVENT_TYPE, *PEVENT_TYPE;

