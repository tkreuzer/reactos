
typedef struct _ACTIVATION_CONTEXT // 0 elements, 0x0 bytes (sizeof)
{
}ACTIVATION_CONTEXT, *PACTIVATION_CONTEXT;

typedef struct _ACTIVATION_CONTEXT_DATA // 0 elements, 0x0 bytes (sizeof)
{
}ACTIVATION_CONTEXT_DATA, *PACTIVATION_CONTEXT_DATA;

          typedef struct _ACTIVATION_CONTEXT_STACK                     // 5 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME* ActiveFrame;
/*0x008*/     struct _LIST_ENTRY FrameListCache;                       // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     ULONG32      Flags;
/*0x01C*/     ULONG32      NextCookieSequenceNumber;
/*0x020*/     ULONG32      StackId;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;


          typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME        // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME* Previous;
/*0x008*/     struct _ACTIVATION_CONTEXT* ActivationContext;
/*0x010*/     ULONG32      Flags;
/*0x014*/     UINT8        _PADDING0_[0x4];
          }RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

          typedef struct _RTL_ATOM_TABLE                // 6 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     LONG32       ReferenceCount;
/*0x008*/     struct _EX_PUSH_LOCK PushLock;            // 7 elements, 0x8 bytes (sizeof)
/*0x010*/     struct _HANDLE_TABLE* ExHandleTable;
/*0x018*/     ULONG32      NumberOfBuckets;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     struct _RTL_ATOM_TABLE_ENTRY* Buckets[1];
          }RTL_ATOM_TABLE, *PRTL_ATOM_TABLE;

          typedef struct _RTL_ATOM_TABLE_ENTRY            // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _RTL_ATOM_TABLE_ENTRY* HashLink;
/*0x008*/     UINT16       HandleIndex;
/*0x00A*/     UINT16       Atom;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     struct _RTL_ATOM_TABLE_REFERENCE Reference; // 4 elements, 0x18 bytes (sizeof)
/*0x028*/     UINT8        NameLength;
/*0x029*/     UINT8        _PADDING1_[0x1];
/*0x02A*/     WCHAR        Name[1];
/*0x02C*/     UINT8        _PADDING2_[0x4];
          }RTL_ATOM_TABLE_ENTRY, *PRTL_ATOM_TABLE_ENTRY;

          typedef struct _RTL_ATOM_TABLE_REFERENCE // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY LowBoxList;       // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      LowBoxID;
/*0x014*/     UINT16       ReferenceCount;
/*0x016*/     UINT16       Flags;
          }RTL_ATOM_TABLE_REFERENCE, *PRTL_ATOM_TABLE_REFERENCE;

          typedef struct _RTL_AVL_TABLE                         // 11 elements, 0x68 bytes (sizeof)
          {
/*0x000*/     struct _RTL_BALANCED_LINKS BalancedRoot;          // 5 elements, 0x20 bytes (sizeof)
/*0x020*/     VOID*        OrderedPointer;
/*0x028*/     ULONG32      WhichOrderedElement;
/*0x02C*/     ULONG32      NumberGenericTableElements;
/*0x030*/     ULONG32      DepthOfTree;
/*0x034*/     UINT8        _PADDING0_[0x4];
/*0x038*/     struct _RTL_BALANCED_LINKS* RestartKey;
/*0x040*/     ULONG32      DeleteCount;
/*0x044*/     UINT8        _PADDING1_[0x4];
/*0x048*/     FUNCT_2105_2104_CompareRoutine* CompareRoutine;
/*0x050*/     FUNCT_00B1_210E_AllocateRoutine* AllocateRoutine;
/*0x058*/     FUNCT_00AE_2112_FreeRoutine* FreeRoutine;
/*0x060*/     VOID*        TableContext;
          }RTL_AVL_TABLE, *PRTL_AVL_TABLE;

          typedef struct _RTL_AVL_TREE         // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _RTL_BALANCED_NODE* Root;
          }RTL_AVL_TREE, *PRTL_AVL_TREE;

          typedef struct _RTL_BALANCED_LINKS          // 5 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _RTL_BALANCED_LINKS* Parent;
/*0x008*/     struct _RTL_BALANCED_LINKS* LeftChild;
/*0x010*/     struct _RTL_BALANCED_LINKS* RightChild;
/*0x018*/     CHAR         Balance;
/*0x019*/     UINT8        Reserved[3];
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }RTL_BALANCED_LINKS, *PRTL_BALANCED_LINKS;

          typedef struct _RTL_BALANCED_NODE               // 6 elements, 0x18 bytes (sizeof)
          {
              union                                       // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         struct _RTL_BALANCED_NODE* Children[2];
                  struct                                  // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             struct _RTL_BALANCED_NODE* Left;
/*0x008*/             struct _RTL_BALANCED_NODE* Right;
                  };
              };
              union                                       // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                                  // 2 elements, 0x1 bytes (sizeof)
                  {
/*0x010*/             UINT8        Red : 1;               // 0 BitPosition
/*0x010*/             UINT8        Balance : 2;           // 0 BitPosition
                  };
/*0x010*/         UINT64       ParentValue;
              };
          }RTL_BALANCED_NODE, *PRTL_BALANCED_NODE;

          typedef struct _RTL_BITMAP        // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      SizeOfBitMap;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     ULONG32*     Buffer;
          }RTL_BITMAP, *PRTL_BITMAP;

          typedef struct _RTL_BITMAP_EX  // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       SizeOfBitMap;
/*0x008*/     UINT64*      Buffer;
          }RTL_BITMAP_EX, *PRTL_BITMAP_EX;

          typedef struct _RTL_CRITICAL_SECTION               // 6 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _RTL_CRITICAL_SECTION_DEBUG* DebugInfo;
/*0x008*/     LONG32       LockCount;
/*0x00C*/     LONG32       RecursionCount;
/*0x010*/     VOID*        OwningThread;
/*0x018*/     VOID*        LockSemaphore;
/*0x020*/     UINT64       SpinCount;
          }RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

          typedef struct _RTL_CRITICAL_SECTION_DEBUG         // 9 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     UINT16       Type;
/*0x002*/     UINT16       CreatorBackTraceIndex;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _RTL_CRITICAL_SECTION* CriticalSection;
/*0x010*/     struct _LIST_ENTRY ProcessLocksList;           // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     ULONG32      EntryCount;
/*0x024*/     ULONG32      ContentionCount;
/*0x028*/     ULONG32      Flags;
/*0x02C*/     UINT16       CreatorBackTraceIndexHigh;
/*0x02E*/     UINT16       SpareUSHORT;
          }RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG;

          typedef struct _RTL_DRIVE_LETTER_CURDIR // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT16       Flags;
/*0x002*/     UINT16       Length;
/*0x004*/     ULONG32      TimeStamp;
/*0x008*/     struct _STRING DosPath;             // 3 elements, 0x10 bytes (sizeof)
          }RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

          typedef struct _RTL_DYNAMIC_HASH_TABLE // 9 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flags;
/*0x004*/     ULONG32      Shift;
/*0x008*/     ULONG32      TableSize;
/*0x00C*/     ULONG32      Pivot;
/*0x010*/     ULONG32      DivisorMask;
/*0x014*/     ULONG32      NumEntries;
/*0x018*/     ULONG32      NonEmptyBuckets;
/*0x01C*/     ULONG32      NumEnumerators;
/*0x020*/     VOID*        Directory;
          }RTL_DYNAMIC_HASH_TABLE, *PRTL_DYNAMIC_HASH_TABLE;

          typedef struct _RTL_DYNAMIC_HASH_TABLE_CONTEXT // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY* ChainHead;
/*0x008*/     struct _LIST_ENTRY* PrevLinkage;
/*0x010*/     UINT64       Signature;
          }RTL_DYNAMIC_HASH_TABLE_CONTEXT, *PRTL_DYNAMIC_HASH_TABLE_CONTEXT;

         typedef struct _RTL_DYNAMIC_HASH_TABLE_ENTRY // 2 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Linkage;              // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT64       Signature;
          }RTL_DYNAMIC_HASH_TABLE_ENTRY, *PRTL_DYNAMIC_HASH_TABLE_ENTRY;

         typedef struct _RTL_DYNAMIC_HASH_TABLE_ENUMERATOR   // 3 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _RTL_DYNAMIC_HASH_TABLE_ENTRY HashEntry; // 2 elements, 0x18 bytes (sizeof)
/*0x018*/     struct _LIST_ENTRY* ChainHead;
/*0x020*/     ULONG32      BucketIndex;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }RTL_DYNAMIC_HASH_TABLE_ENUMERATOR, *PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR;

          typedef struct _RTL_RANGE         // 6 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       Start;
/*0x008*/     UINT64       End;
/*0x010*/     VOID*        UserData;
/*0x018*/     VOID*        Owner;
/*0x020*/     UINT8        Attributes;
/*0x021*/     UINT8        Flags;
/*0x022*/     UINT8        _PADDING0_[0x6];
          }RTL_RANGE, *PRTL_RANGE;

          typedef struct _RTL_RANGE_LIST    // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListHead;  // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Flags;
/*0x014*/     ULONG32      Count;
/*0x018*/     ULONG32      Stamp;
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }RTL_RANGE_LIST, *PRTL_RANGE_LIST;

          typedef struct _RTL_RB_TREE          // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _RTL_BALANCED_NODE* Root;
/*0x008*/     struct _RTL_BALANCED_NODE* Min;
          }RTL_RB_TREE, *PRTL_RB_TREE;

          typedef struct _RTL_SPLAY_LINKS          // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _RTL_SPLAY_LINKS* Parent;
/*0x008*/     struct _RTL_SPLAY_LINKS* LeftChild;
/*0x010*/     struct _RTL_SPLAY_LINKS* RightChild;
          }RTL_SPLAY_LINKS, *PRTL_SPLAY_LINKS;

         typedef struct _RTL_SRWLOCK                  // 7 elements, 0x8 bytes (sizeof)
          {
              union                                    // 3 elements, 0x8 bytes (sizeof)
              {
                  struct                               // 5 elements, 0x8 bytes (sizeof)
                  {
/*0x000*/             UINT64       Locked : 1;         // 0 BitPosition
/*0x000*/             UINT64       Waiting : 1;        // 1 BitPosition
/*0x000*/             UINT64       Waking : 1;         // 2 BitPosition
/*0x000*/             UINT64       MultipleShared : 1; // 3 BitPosition
/*0x000*/             UINT64       Shared : 60;        // 4 BitPosition
                  };
/*0x000*/         UINT64       Value;
/*0x000*/         VOID*        Ptr;
              };
          }RTL_SRWLOCK, *PRTL_SRWLOCK;

          typedef struct _RTL_TIME_ZONE_INFORMATION // 7 elements, 0xAC bytes (sizeof)
          {
/*0x000*/     LONG32       Bias;
/*0x004*/     WCHAR        StandardName[32];
/*0x044*/     struct _TIME_FIELDS StandardStart;    // 8 elements, 0x10 bytes (sizeof)
/*0x054*/     LONG32       StandardBias;
/*0x058*/     WCHAR        DaylightName[32];
/*0x098*/     struct _TIME_FIELDS DaylightStart;    // 8 elements, 0x10 bytes (sizeof)
/*0x0A8*/     LONG32       DaylightBias;
          }RTL_TIME_ZONE_INFORMATION, *PRTL_TIME_ZONE_INFORMATION;

          typedef struct _RTL_UMS_CONTEXT                       // 20 elements, 0x520 bytes (sizeof)
          {
/*0x000*/     struct _SINGLE_LIST_ENTRY Link;                   // 1 elements, 0x8 bytes (sizeof)
/*0x008*/     UINT8        _PADDING0_[0x8];
/*0x010*/     struct _CONTEXT Context;                          // 64 elements, 0x4D0 bytes (sizeof)
/*0x4E0*/     VOID*        Teb;
/*0x4E8*/     VOID*        UserContext;
              union                                             // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                                        // 7 elements, 0x4 bytes (sizeof)
                  {
/*0x4F0*/             ULONG32      ScheduledThread : 1;         // 0 BitPosition
/*0x4F0*/             ULONG32      Suspended : 1;               // 1 BitPosition
/*0x4F0*/             ULONG32      VolatileContext : 1;         // 2 BitPosition
/*0x4F0*/             ULONG32      Terminated : 1;              // 3 BitPosition
/*0x4F0*/             ULONG32      DebugActive : 1;             // 4 BitPosition
/*0x4F0*/             ULONG32      RunningOnSelfThread : 1;     // 5 BitPosition
/*0x4F0*/             ULONG32      DenyRunningOnSelfThread : 1; // 6 BitPosition
                  };
/*0x4F0*/         LONG32       Flags;
              };
              union                                             // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                                        // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x4F8*/             UINT64       KernelUpdateLock : 2;        // 0 BitPosition
/*0x4F8*/             UINT64       PrimaryClientID : 62;        // 2 BitPosition
                  };
/*0x4F8*/         UINT64       ContextLock;
              };
/*0x500*/     struct _RTL_UMS_CONTEXT* PrimaryUmsContext;
/*0x508*/     ULONG32      SwitchCount;
/*0x50C*/     ULONG32      KernelYieldCount;
/*0x510*/     ULONG32      MixedYieldCount;
/*0x514*/     ULONG32      YieldCount;
/*0x518*/     UINT8        _PADDING1_[0x8];
          }RTL_UMS_CONTEXT, *PRTL_UMS_CONTEXT;

          typedef struct _RTL_USER_PROCESS_PARAMETERS                // 33 elements, 0x420 bytes (sizeof)
          {
/*0x000*/     ULONG32      MaximumLength;
/*0x004*/     ULONG32      Length;
/*0x008*/     ULONG32      Flags;
/*0x00C*/     ULONG32      DebugFlags;
/*0x010*/     VOID*        ConsoleHandle;
/*0x018*/     ULONG32      ConsoleFlags;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     VOID*        StandardInput;
/*0x028*/     VOID*        StandardOutput;
/*0x030*/     VOID*        StandardError;
/*0x038*/     struct _CURDIR CurrentDirectory;                       // 2 elements, 0x18 bytes (sizeof)
/*0x050*/     struct _UNICODE_STRING DllPath;                        // 3 elements, 0x10 bytes (sizeof)
/*0x060*/     struct _UNICODE_STRING ImagePathName;                  // 3 elements, 0x10 bytes (sizeof)
/*0x070*/     struct _UNICODE_STRING CommandLine;                    // 3 elements, 0x10 bytes (sizeof)
/*0x080*/     VOID*        Environment;
/*0x088*/     ULONG32      StartingX;
/*0x08C*/     ULONG32      StartingY;
/*0x090*/     ULONG32      CountX;
/*0x094*/     ULONG32      CountY;
/*0x098*/     ULONG32      CountCharsX;
/*0x09C*/     ULONG32      CountCharsY;
/*0x0A0*/     ULONG32      FillAttribute;
/*0x0A4*/     ULONG32      WindowFlags;
/*0x0A8*/     ULONG32      ShowWindowFlags;
/*0x0AC*/     UINT8        _PADDING1_[0x4];
/*0x0B0*/     struct _UNICODE_STRING WindowTitle;                    // 3 elements, 0x10 bytes (sizeof)
/*0x0C0*/     struct _UNICODE_STRING DesktopInfo;                    // 3 elements, 0x10 bytes (sizeof)
/*0x0D0*/     struct _UNICODE_STRING ShellInfo;                      // 3 elements, 0x10 bytes (sizeof)
/*0x0E0*/     struct _UNICODE_STRING RuntimeData;                    // 3 elements, 0x10 bytes (sizeof)
/*0x0F0*/     struct _RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
/*0x3F0*/     UINT64       EnvironmentSize;
/*0x3F8*/     UINT64       EnvironmentVersion;
/*0x400*/     struct _UNICODE_STRING PackageMoniker;                 // 3 elements, 0x10 bytes (sizeof)
/*0x410*/     VOID*        PackageDependencyData;
/*0x418*/     ULONG32      ProcessGroupId;
/*0x41C*/     UINT8        _PADDING2_[0x4];
          }RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

          typedef struct _RTLP_RANGE_LIST_ENTRY    // 8 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     UINT64       Start;
/*0x008*/     UINT64       End;
              union                                // 2 elements, 0x10 bytes (sizeof)
              {
                  struct                           // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x010*/             VOID*        UserData;
/*0x018*/             VOID*        Owner;
                  }Allocated;
                  struct                           // 1 elements, 0x10 bytes (sizeof)
                  {
/*0x010*/             struct _LIST_ENTRY ListHead; // 2 elements, 0x10 bytes (sizeof)
                  }Merged;
              };
/*0x020*/     UINT8        Attributes;
/*0x021*/     UINT8        PublicFlags;
/*0x022*/     UINT16       PrivateFlags;
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     struct _LIST_ENTRY ListEntry;        // 2 elements, 0x10 bytes (sizeof)
          }RTLP_RANGE_LIST_ENTRY, *PRTLP_RANGE_LIST_ENTRY;

typedef enum _RTL_GENERIC_COMPARE_RESULTS  // 3 elements, 0x4 bytes
{
    GenericLessThan    = 0 /*0x0*/,
    GenericGreaterThan = 1 /*0x1*/,
    GenericEqual       = 2 /*0x2*/
}RTL_GENERIC_COMPARE_RESULTS, *PRTL_GENERIC_COMPARE_RESULTS;

