
          typedef struct _MI_ACTIVE_WSLE // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flink;
/*0x004*/     ULONG32      Blink;
          }MI_ACTIVE_WSLE, *PMI_ACTIVE_WSLE;

          typedef struct _MI_CACHED_PTE             // 3 elements, 0x8 bytes (sizeof)
          {
              union                                 // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                            // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x000*/             ULONG32      GlobalTimeStamp;
/*0x004*/             ULONG32      PteIndex;
                  };
/*0x000*/         INT64        Long;
              };
          }MI_CACHED_PTE, *PMI_CACHED_PTE;

          typedef struct _MI_LARGEPAGE_MEMORY_INFO            // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListHead;                    // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _COLORED_PAGE_INFO* ColoredPageInfoBase;
/*0x018*/     ULONG32      PagesNeedZeroing;
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }MI_LARGEPAGE_MEMORY_INFO, *PMI_LARGEPAGE_MEMORY_INFO;

          typedef struct _MI_PAGEFILE_TRACES                   // 11 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     LONG32       Status;
/*0x004*/     UINT8        Priority;
/*0x005*/     UINT8        IrpPriority;
/*0x006*/     UINT8        ReservationWrite;
/*0x007*/     UINT8        _PADDING0_[0x1];
/*0x008*/     union _LARGE_INTEGER CurrentTime;                // 4 elements, 0x8 bytes (sizeof)
/*0x010*/     UINT64       AvailablePages;
/*0x018*/     UINT64       ModifiedPagesTotal;
/*0x020*/     UINT64       ModifiedPagefilePages;
/*0x028*/     UINT64       ModifiedNoWritePages;
/*0x030*/     UINT64       ModifiedPagefileNoReservationPages;
              struct                                           // 2 elements, 0x38 bytes (sizeof)
              {
/*0x038*/         struct _MDL  Mdl;                            // 8 elements, 0x30 bytes (sizeof)
/*0x068*/         UINT64       Page[1];
              }MdlHack;
          }MI_PAGEFILE_TRACES, *PMI_PAGEFILE_TRACES;

          typedef struct _MI_PAGING_FILE_SPACE_BITMAPS          // 5 elements, 0x30 bytes (sizeof)
          {
              union                                             // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         ULONG32      RefCount;
/*0x000*/         struct _MI_PAGING_FILE_SPACE_BITMAPS* Anchor;
              };
/*0x008*/     struct _RTL_BITMAP AllocationBitmap;              // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     struct _RTL_BITMAP ReservationBitmap;             // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _RTL_BITMAP* EvictStoreBitmap;
          }MI_PAGING_FILE_SPACE_BITMAPS, *PMI_PAGING_FILE_SPACE_BITMAPS;

          typedef struct _MI_PHYSMEM_BLOCK     // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _MMIO_TRACKER* IoTracker;
          }MI_PHYSMEM_BLOCK, *PMI_PHYSMEM_BLOCK;

          typedef struct _MI_PTE_CHAIN_HEAD // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _MMPTE Flink;          // 1 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _MMPTE Blink;          // 1 elements, 0x8 bytes (sizeof)
/*0x010*/     struct _MMPTE* PteBase;
          }MI_PTE_CHAIN_HEAD, *PMI_PTE_CHAIN_HEAD;

          typedef struct _MI_REVERSE_VIEW_MAP    // 7 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ViewLinks;      // 2 elements, 0x10 bytes (sizeof)
              union                              // 4 elements, 0x8 bytes (sizeof)
              {
/*0x010*/         VOID*        SystemCacheVa;
/*0x010*/         VOID*        SessionViewVa;
/*0x010*/         struct _EPROCESS* VadsProcess;
/*0x010*/         UINT64       Type : 2;         // 0 BitPosition
              };
/*0x018*/     struct _SUBSECTION* Subsection;
/*0x020*/     UINT64       SectionOffset;
          }MI_REVERSE_VIEW_MAP, *PMI_REVERSE_VIEW_MAP;

          typedef struct _MI_SPECIAL_POOL         // 5 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     UINT64       Lock;
/*0x008*/     struct _MI_PTE_CHAIN_HEAD Paged;    // 3 elements, 0x18 bytes (sizeof)
/*0x020*/     struct _MI_PTE_CHAIN_HEAD NonPaged; // 3 elements, 0x18 bytes (sizeof)
/*0x038*/     UINT64       PagesInUse;
/*0x040*/     struct _RTL_BITMAP SpecialPoolPdes; // 2 elements, 0x10 bytes (sizeof)
          }MI_SPECIAL_POOL, *PMI_SPECIAL_POOL;

          typedef struct _MI_SYSTEM_PTE_TYPE       // 13 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _RTL_BITMAP Bitmap;           // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Flags;
/*0x014*/     ULONG32      Hint;
/*0x018*/     struct _MMPTE* BasePte;
/*0x020*/     ULONG32*     FailureCount;
/*0x028*/     struct _MMSUPPORT* Vm;
/*0x030*/     LONG32       TotalSystemPtes;
/*0x034*/     LONG32       TotalFreeSystemPtes;
/*0x038*/     LONG32       CachedPteCount;
/*0x03C*/     ULONG32      PteFailures;
              union                                // 2 elements, 0x8 bytes (sizeof)
              {
/*0x040*/         UINT64       SpinLock;
/*0x040*/         struct _FAST_MUTEX* GlobalMutex;
              };
/*0x048*/     struct _MI_CACHED_PTE* CachedPtes;
          }MI_SYSTEM_PTE_TYPE, *PMI_SYSTEM_PTE_TYPE;

          typedef struct _MI_USER_VA_INFO                    // 17 elements, 0x460 bytes (sizeof)
          {
/*0x000*/     ULONG32      NumberOfCommittedPageTables;
/*0x004*/     ULONG32      PhysicalMappingCount;
/*0x008*/     ULONG32      VadBitMapHint;
/*0x00C*/     ULONG32      LastAllocationSizeHint;
/*0x010*/     ULONG32      LastAllocationSize;
/*0x014*/     ULONG32      LowestBottomUpVadBit;
/*0x018*/     ULONG32      VadBitMapSize;
/*0x01C*/     ULONG32      MaximumLastVadBit;
/*0x020*/     ULONG32*     VadBitBuffer;
/*0x028*/     VOID*        LowestBottomUpAllocationAddress;
/*0x030*/     VOID*        HighestTopDownAllocationAddress;
/*0x038*/     VOID*        FreeTebHint;
/*0x040*/     VOID*        FreeUmsTebHint;
/*0x048*/     ULONG32*     CommittedPageTables;
/*0x050*/     ULONG32      PageTableBitmapPages;
/*0x054*/     UINT8        _PADDING0_[0x4];
/*0x058*/     UINT64       CommittedPageDirectories[128];
/*0x458*/     UINT64       CommittedPageDirectoryParents[1];
          }MI_USER_VA_INFO, *PMI_USER_VA_INFO;


          typedef struct _MI_VERIFIER_POOL_HEADER       // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _VI_POOL_ENTRY* VerifierPoolEntry;
          }MI_VERIFIER_POOL_HEADER, *PMI_VERIFIER_POOL_HEADER;


          typedef struct _MM_DRIVER_VERIFIER_DATA              // 32 elements, 0xA0 bytes (sizeof)
          {
/*0x000*/     ULONG32      Level;
/*0x004*/     ULONG32      RaiseIrqls;
/*0x008*/     ULONG32      AcquireSpinLocks;
/*0x00C*/     ULONG32      SynchronizeExecutions;
/*0x010*/     ULONG32      AllocationsAttempted;
/*0x014*/     ULONG32      AllocationsSucceeded;
/*0x018*/     ULONG32      AllocationsSucceededSpecialPool;
/*0x01C*/     ULONG32      AllocationsWithNoTag;
/*0x020*/     ULONG32      TrimRequests;
/*0x024*/     ULONG32      Trims;
/*0x028*/     ULONG32      AllocationsFailed;
/*0x02C*/     ULONG32      AllocationsFailedDeliberately;
/*0x030*/     ULONG32      Loads;
/*0x034*/     ULONG32      Unloads;
/*0x038*/     ULONG32      UnTrackedPool;
/*0x03C*/     ULONG32      UserTrims;
/*0x040*/     ULONG32      CurrentPagedPoolAllocations;
/*0x044*/     ULONG32      CurrentNonPagedPoolAllocations;
/*0x048*/     ULONG32      PeakPagedPoolAllocations;
/*0x04C*/     ULONG32      PeakNonPagedPoolAllocations;
/*0x050*/     UINT64       PagedBytes;
/*0x058*/     UINT64       NonPagedBytes;
/*0x060*/     UINT64       PeakPagedBytes;
/*0x068*/     UINT64       PeakNonPagedBytes;
/*0x070*/     ULONG32      BurstAllocationsFailedDeliberately;
/*0x074*/     ULONG32      SessionTrims;
/*0x078*/     ULONG32      OptionChanges;
/*0x07C*/     ULONG32      VerifyMode;
/*0x080*/     struct _UNICODE_STRING PreviousBucketName;       // 3 elements, 0x10 bytes (sizeof)
/*0x090*/     ULONG32      ActivityCounter;
/*0x094*/     ULONG32      PreviousActivityCounter;
/*0x098*/     ULONG32      WorkerTrimRequests;
/*0x09C*/     UINT8        _PADDING0_[0x4];
          }MM_DRIVER_VERIFIER_DATA, *PMM_DRIVER_VERIFIER_DATA;

          typedef struct _MM_PAGE_ACCESS_INFO             // 4 elements, 0x8 bytes (sizeof)
          {
              union                                       // 4 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         union _MM_PAGE_ACCESS_INFO_FLAGS Flags; // 2 elements, 0x4 bytes (sizeof)
/*0x000*/         UINT64       FileOffset;
/*0x000*/         VOID*        VirtualAddress;
/*0x000*/         VOID*        PointerProtoPte;
              };
          }MM_PAGE_ACCESS_INFO, *PMM_PAGE_ACCESS_INFO;

          typedef union _MM_PAGE_ACCESS_INFO_FLAGS   // 2 elements, 0x4 bytes (sizeof)
          {
              struct                                 // 4 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      FilePointerIndex : 9; // 0 BitPosition
/*0x000*/         ULONG32      HardFault : 1;        // 9 BitPosition
/*0x000*/         ULONG32      Image : 1;            // 10 BitPosition
/*0x000*/         ULONG32      Spare0 : 1;           // 11 BitPosition
              }File;
              struct                                 // 3 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      FilePointerIndex : 9; // 0 BitPosition
/*0x000*/         ULONG32      HardFault : 1;        // 9 BitPosition
/*0x000*/         ULONG32      Spare1 : 2;           // 10 BitPosition
              }Private;
          }MM_PAGE_ACCESS_INFO_FLAGS, *PMM_PAGE_ACCESS_INFO_FLAGS;

          typedef struct _MM_PAGE_ACCESS_INFO_HEADER          // 14 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     struct _SINGLE_LIST_ENTRY Link;                 // 1 elements, 0x8 bytes (sizeof)
/*0x008*/     enum _MM_PAGE_ACCESS_TYPE Type;
              union                                           // 2 elements, 0x4 bytes (sizeof)
              {
/*0x00C*/         ULONG32      EmptySequenceNumber;
/*0x00C*/         ULONG32      CurrentFileIndex;
              };
/*0x010*/     UINT64       CreateTime;
              union                                           // 2 elements, 0x8 bytes (sizeof)
              {
/*0x018*/         UINT64       EmptyTime;
/*0x018*/         struct _MM_PAGE_ACCESS_INFO* TempEntry;
              };
              union                                           // 2 elements, 0x24 bytes (sizeof)
              {
                  struct                                      // 5 elements, 0x24 bytes (sizeof)
                  {
/*0x020*/             struct _MM_PAGE_ACCESS_INFO* PageEntry;
/*0x028*/             UINT64*      FileEntry;
/*0x030*/             UINT64*      FirstFileEntry;
/*0x038*/             struct _EPROCESS* Process;
/*0x040*/             ULONG32      SessionId;
                  };
                  struct                                      // 2 elements, 0x24 bytes (sizeof)
                  {
/*0x020*/             UINT64*      PageFrameEntry;
/*0x028*/             UINT64*      LastPageFrameEntry;
/*0x030*/             UINT8        _PADDING0_[0x14];
                  };
              };
          }MM_PAGE_ACCESS_INFO_HEADER, *PMM_PAGE_ACCESS_INFO_HEADER;

          typedef struct _MM_PAGED_POOL_INFO             // 5 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _FAST_MUTEX Mutex;                  // 5 elements, 0x38 bytes (sizeof)
/*0x038*/     struct _RTL_BITMAP PagedPoolAllocationMap; // 2 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _MMPTE* FirstPteForPagedPool;
/*0x050*/     ULONG32      PagedPoolHint;
/*0x054*/     UINT8        _PADDING0_[0x4];
/*0x058*/     UINT64       AllocatedPagedPool;
          }MM_PAGED_POOL_INFO, *PMM_PAGED_POOL_INFO;

           typedef struct _MM_SESSION_SPACE                   // 43 elements, 0x1F80 bytes (sizeof)
           {
/*0x000*/      LONG32       ReferenceCount;
               union                                          // 2 elements, 0x4 bytes (sizeof)
               {
/*0x004*/          ULONG32      LongFlags;
/*0x004*/          struct _MM_SESSION_SPACE_FLAGS Flags;      // 8 elements, 0x4 bytes (sizeof)
               }u;
/*0x008*/      ULONG32      SessionId;
/*0x00C*/      LONG32       ProcessReferenceToSession;
/*0x010*/      struct _LIST_ENTRY ProcessList;                // 2 elements, 0x10 bytes (sizeof)
/*0x020*/      UINT64       SessionPageDirectoryIndex;
/*0x028*/      UINT64       NonPagablePages;
/*0x030*/      UINT64       CommittedPages;
/*0x038*/      VOID*        PagedPoolStart;
/*0x040*/      VOID*        PagedPoolEnd;
/*0x048*/      VOID*        SessionObject;
/*0x050*/      VOID*        SessionObjectHandle;
/*0x058*/      ULONG32      SessionPoolAllocationFailures[4];
/*0x068*/      struct _LIST_ENTRY ImageList;                  // 2 elements, 0x10 bytes (sizeof)
/*0x078*/      ULONG32      LocaleId;
/*0x07C*/      ULONG32      AttachCount;
/*0x080*/      struct _KGATE AttachGate;                      // 1 elements, 0x18 bytes (sizeof)
/*0x098*/      struct _LIST_ENTRY WsListEntry;                // 2 elements, 0x10 bytes (sizeof)
/*0x0A8*/      UINT8        _PADDING0_[0x18];
/*0x0C0*/      struct _GENERAL_LOOKASIDE Lookaside[21];
/*0xB40*/      struct _MMSESSION Session;                     // 7 elements, 0x58 bytes (sizeof)
/*0xB98*/      struct _MM_PAGED_POOL_INFO PagedPoolInfo;      // 5 elements, 0x60 bytes (sizeof)
/*0xBF8*/      struct _MMSUPPORT Vm;                          // 22 elements, 0x88 bytes (sizeof)
/*0xC80*/      struct _MMWSLE* Wsle;
/*0xC88*/      FUNCT_00AE_108F_DriverUnload* DriverUnload;
/*0xC90*/      UINT8        _PADDING1_[0x30];
/*0xCC0*/      struct _POOL_DESCRIPTOR PagedPool;             // 13 elements, 0x1140 bytes (sizeof)
/*0x1E00*/     struct _MMPTE PageDirectory;                   // 1 elements, 0x8 bytes (sizeof)
/*0x1E08*/     struct _FAST_MUTEX SessionVaLock;              // 5 elements, 0x38 bytes (sizeof)
/*0x1E40*/     struct _RTL_BITMAP DynamicVaBitMap;            // 2 elements, 0x10 bytes (sizeof)
/*0x1E50*/     ULONG32      DynamicVaHint;
/*0x1E54*/     UINT8        _PADDING2_[0x4];
/*0x1E58*/     struct _MI_SPECIAL_POOL SpecialPool;           // 5 elements, 0x50 bytes (sizeof)
/*0x1EA8*/     struct _FAST_MUTEX SessionPteLock;             // 5 elements, 0x38 bytes (sizeof)
/*0x1EE0*/     LONG32       PoolBigEntriesInUse;
/*0x1EE4*/     ULONG32      PagedPoolPdeCount;
/*0x1EE8*/     ULONG32      SpecialPoolPdeCount;
/*0x1EEC*/     ULONG32      DynamicSessionPdeCount;
/*0x1EF0*/     struct _MI_SYSTEM_PTE_TYPE SystemPteInfo;      // 13 elements, 0x50 bytes (sizeof)
/*0x1F40*/     VOID*        PoolTrackTableExpansion;
/*0x1F48*/     UINT64       PoolTrackTableExpansionSize;
/*0x1F50*/     VOID*        PoolTrackBigPages;
/*0x1F58*/     UINT64       PoolTrackBigPagesSize;
/*0x1F60*/     enum _IO_SESSION_STATE IoState;
/*0x1F64*/     ULONG32      IoStateSequence;
/*0x1F68*/     struct _KEVENT IoNotificationEvent;            // 1 elements, 0x18 bytes (sizeof)
           }MM_SESSION_SPACE, *PMM_SESSION_SPACE;

          typedef struct _MM_SESSION_SPACE_FLAGS     // 8 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      Initialized : 1;          // 0 BitPosition
/*0x000*/     ULONG32      DeletePending : 1;        // 1 BitPosition
/*0x000*/     ULONG32      PoolInitialized : 1;      // 2 BitPosition
/*0x000*/     ULONG32      DynamicVaInitialized : 1; // 3 BitPosition
/*0x000*/     ULONG32      WsInitialized : 1;        // 4 BitPosition
/*0x000*/     ULONG32      PoolDestroyed : 1;        // 5 BitPosition
/*0x000*/     ULONG32      ObjectInitialized : 1;    // 6 BitPosition
/*0x000*/     ULONG32      Filler : 25;              // 7 BitPosition
          }MM_SESSION_SPACE_FLAGS, *PMM_SESSION_SPACE_FLAGS;

          typedef union _MM_STORE_KEY       // 3 elements, 0x8 bytes (sizeof)
          {
              struct                        // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       KeyLow : 60; // 0 BitPosition
/*0x000*/         UINT64       KeyHigh : 4; // 60 BitPosition
              };
/*0x000*/     UINT64       EntireKey;
          }MM_STORE_KEY, *PMM_STORE_KEY;

          typedef struct _MMADDRESS_LIST        // 2 elements, 0x10 bytes (sizeof)
          {
              union                             // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         struct _MMSECURE_FLAGS Flags; // 4 elements, 0x4 bytes (sizeof)
/*0x000*/         VOID*        StartVa;
              }u1;
/*0x008*/     VOID*        EndVa;
          }MMADDRESS_LIST, *PMMADDRESS_LIST;

          typedef struct _MMEXTEND_INFO     // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       CommittedSize;
/*0x008*/     ULONG32      ReferenceCount;
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }MMEXTEND_INFO, *PMMEXTEND_INFO;

          typedef struct _MMINPAGE_FLAGS                    // 18 elements, 0x4 bytes (sizeof)
          {
              struct                                        // 2 elements, 0x1 bytes (sizeof)
              {
/*0x000*/         UINT8        InjectRetry : 1;             // 0 BitPosition
/*0x000*/         UINT8        CrossThreadPadding : 7;      // 1 BitPosition
              };
              struct                                        // 7 elements, 0x1 bytes (sizeof)
              {
/*0x001*/         UINT8        PrefetchSystemVmType : 2;    // 0 BitPosition
/*0x001*/         UINT8        VaPrefetchReadBlock : 1;     // 2 BitPosition
/*0x001*/         UINT8        CollidedFlowThrough : 1;     // 3 BitPosition
/*0x001*/         UINT8        ForceCollisions : 1;         // 4 BitPosition
/*0x001*/         UINT8        InPageExpanded : 1;          // 5 BitPosition
/*0x001*/         UINT8        IssuedAtLowPriority : 1;     // 6 BitPosition
/*0x001*/         UINT8        FaultFromStore : 1;          // 7 BitPosition
              };
              struct                                        // 4 elements, 0x1 bytes (sizeof)
              {
/*0x002*/         UINT8        PagePriority : 3;            // 0 BitPosition
/*0x002*/         UINT8        PerformRelocations : 1;      // 3 BitPosition
/*0x002*/         UINT8        ClusteredPagePriority : 3;   // 4 BitPosition
/*0x002*/         UINT8        MakeClusterValid : 1;        // 7 BitPosition
              };
              struct                                        // 5 elements, 0x1 bytes (sizeof)
              {
/*0x003*/         UINT8        ZeroLastPage : 1;            // 0 BitPosition
/*0x003*/         UINT8        UserFault : 1;               // 1 BitPosition
/*0x003*/         UINT8        BoostedPriority : 1;         // 2 BitPosition
/*0x003*/         UINT8        StandbyProtectionNeeded : 1; // 3 BitPosition
/*0x003*/         UINT8        Spare1 : 4;                  // 4 BitPosition
              };
          }MMINPAGE_FLAGS, *PMMINPAGE_FLAGS;

          typedef struct _MMINPAGE_SUPPORT                          // 22 elements, 0x170 bytes (sizeof)
          {
/*0x000*/     struct _SINGLE_LIST_ENTRY ListEntry;                  // 1 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _ETHREAD* Thread;
/*0x010*/     struct _LIST_ENTRY ListHead;                          // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     struct _KEVENT Event;                                 // 1 elements, 0x18 bytes (sizeof)
/*0x038*/     struct _KEVENT CollidedEvent;                         // 1 elements, 0x18 bytes (sizeof)
/*0x050*/     struct _IO_STATUS_BLOCK IoStatus;                     // 3 elements, 0x10 bytes (sizeof)
/*0x060*/     union _LARGE_INTEGER ReadOffset;                      // 4 elements, 0x8 bytes (sizeof)
/*0x068*/     struct _MMPTE PteContents;                            // 1 elements, 0x8 bytes (sizeof)
/*0x070*/     struct _MMPFN* LockedProtoPfn;
/*0x078*/     LONG32       WaitCount;
/*0x07C*/     ULONG32      ByteCount;
/*0x080*/     ULONG32      ImagePteOffset;
              union                                                 // 2 elements, 0x4 bytes (sizeof)
              {
/*0x084*/         struct _MMINPAGE_FLAGS e1;                        // 18 elements, 0x4 bytes (sizeof)
/*0x084*/         ULONG32      LongFlags;
              }u1;
/*0x088*/     struct _FILE_OBJECT* FilePointer;
              union                                                 // 2 elements, 0x8 bytes (sizeof)
              {
/*0x090*/         struct _CONTROL_AREA* ControlArea;
/*0x090*/         struct _MI_IMAGE_SECURITY_REFERENCE* SeImageStub;
              }u2;
/*0x098*/     VOID*        FaultingAddress;
/*0x0A0*/     struct _MMPTE* PointerPte;
/*0x0A8*/     struct _MMPTE* BasePte;
/*0x0B0*/     struct _MMPFN* Pfn;
/*0x0B8*/     struct _MDL* PrefetchMdl;
/*0x0C0*/     struct _MDL  Mdl;                                     // 8 elements, 0x30 bytes (sizeof)
/*0x0F0*/     UINT64       Page[16];
          }MMINPAGE_SUPPORT, *PMMINPAGE_SUPPORT;

          typedef struct _MMIO_TRACKER              // 9 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;         // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT64       PageFrameIndex;
/*0x018*/     UINT64       NumberOfPages;
              union                                 // 2 elements, 0x8 bytes (sizeof)
              {
/*0x020*/         VOID*        BaseVa;
/*0x020*/         ULONG32      CacheFlushTimeStamp;
              };
/*0x028*/     struct _MDL* Mdl;
/*0x030*/     UINT64       MdlPages;
/*0x038*/     VOID*        StackTrace[6];
/*0x068*/     struct _IO_CACHE_INFO CacheInfo[1];
/*0x069*/     UINT8        _PADDING0_[0x7];
          }MMIO_TRACKER, *PMMIO_TRACKER;

          typedef struct _MMMOD_WRITER_MDL_ENTRY    // 14 elements, 0xA0 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Links;             // 2 elements, 0x10 bytes (sizeof)
              union                                 // 1 elements, 0x10 bytes (sizeof)
              {
/*0x010*/         struct _IO_STATUS_BLOCK IoStatus; // 3 elements, 0x10 bytes (sizeof)
              }u;
/*0x020*/     struct _IRP* Irp;
/*0x028*/     struct _MODWRITER_FLAGS u1;           // 3 elements, 0x4 bytes (sizeof)
/*0x02C*/     ULONG32      ByteCount;
/*0x030*/     struct _MMPAGING_FILE* PagingFile;
/*0x038*/     struct _FILE_OBJECT* File;
/*0x040*/     struct _CONTROL_AREA* ControlArea;
/*0x048*/     struct _ERESOURCE* FileResource;
/*0x050*/     union _LARGE_INTEGER WriteOffset;     // 4 elements, 0x8 bytes (sizeof)
/*0x058*/     union _LARGE_INTEGER IssueTime;       // 4 elements, 0x8 bytes (sizeof)
/*0x060*/     struct _MDL* PointerMdl;
/*0x068*/     struct _MDL  Mdl;                     // 8 elements, 0x30 bytes (sizeof)
/*0x098*/     UINT64       Page[1];
          }MMMOD_WRITER_MDL_ENTRY, *PMMMOD_WRITER_MDL_ENTRY;

          typedef struct _MMPAGING_FILE                      // 28 elements, 0xA8 bytes (sizeof)
          {
/*0x000*/     UINT64       Size;
/*0x008*/     UINT64       MaximumSize;
/*0x010*/     UINT64       MinimumSize;
/*0x018*/     UINT64       FreeSpace;
/*0x020*/     UINT64       PeakUsage;
/*0x028*/     UINT64       HighestPage;
/*0x030*/     UINT64       FreeReservationSpace;
/*0x038*/     UINT64       LargestReserveCluster;
/*0x040*/     struct _FILE_OBJECT* File;
/*0x048*/     struct _MMMOD_WRITER_MDL_ENTRY* Entry[2];
/*0x058*/     struct _UNICODE_STRING PageFileName;           // 3 elements, 0x10 bytes (sizeof)
/*0x068*/     struct _MI_PAGING_FILE_SPACE_BITMAPS* Bitmaps;
/*0x070*/     ULONG32      AllocationBitmapHint;
/*0x074*/     ULONG32      ReservationBitmapHint;
/*0x078*/     ULONG32      LargestNonReservedClusterSize;
/*0x07C*/     ULONG32      RefreshClusterSize;
/*0x080*/     ULONG32      LastRefreshClusterSize;
/*0x084*/     ULONG32      ReservedClusterSizeAggregate;
/*0x088*/     ULONG32      ToBeEvictedCount;
              struct                                         // 3 elements, 0x2 bytes (sizeof)
              {
/*0x08C*/         UINT16       PageFileNumber : 4;           // 0 BitPosition
/*0x08C*/         UINT16       BootPartition : 1;            // 4 BitPosition
/*0x08C*/         UINT16       Spare0 : 11;                  // 5 BitPosition
              };
              struct                                         // 2 elements, 0x1 bytes (sizeof)
              {
/*0x08E*/         UINT8        AdriftMdls : 1;               // 0 BitPosition
/*0x08E*/         UINT8        Spare1 : 7;                   // 1 BitPosition
              };
/*0x08F*/     UINT8        Spare2 : 8;                       // 0 BitPosition
/*0x090*/     VOID*        FileHandle;
/*0x098*/     UINT64       Lock;
/*0x0A0*/     struct _ETHREAD* LockOwner;
          }MMPAGING_FILE, *PMMPAGING_FILE;

          typedef struct _MMPFN                                // 13 elements, 0x30 bytes (sizeof)
          {
              union                                            // 7 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       Flink;
/*0x000*/         ULONG32      WsIndex;
/*0x000*/         struct _KEVENT* Event;
/*0x000*/         VOID*        Next;
/*0x000*/         VOID*        VolatileNext;
/*0x000*/         struct _KTHREAD* KernelStackOwner;
/*0x000*/         struct _SINGLE_LIST_ENTRY NextStackPfn;      // 1 elements, 0x8 bytes (sizeof)
              }u1;
              union                                            // 3 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         UINT64       Blink;
/*0x008*/         struct _MMPTE* ImageProtoPte;
/*0x008*/         UINT64       ShareCount;
              }u2;
              union                                            // 4 elements, 0x8 bytes (sizeof)
              {
/*0x010*/         struct _MMPTE* PteAddress;
/*0x010*/         VOID*        VolatilePteAddress;
/*0x010*/         LONG32       Lock;
/*0x010*/         UINT64       PteLong;
              };
              union                                            // 3 elements, 0x4 bytes (sizeof)
              {
                  struct                                       // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x018*/             UINT16       ReferenceCount;
/*0x01A*/             struct _MMPFNENTRY e1;                   // 11 elements, 0x2 bytes (sizeof)
                  };
                  struct                                       // 3 elements, 0x4 bytes (sizeof)
                  {
                      union                                    // 2 elements, 0x2 bytes (sizeof)
                      {
/*0x018*/                 UINT16       ReferenceCount;
/*0x018*/                 INT16        VolatileReferenceCount;
                      };
/*0x01A*/             UINT16       ShortFlags;
                  }e2;
              }u3;
/*0x01C*/     UINT16       UsedPageTableEntries;
              struct                                           // 2 elements, 0x1 bytes (sizeof)
              {
/*0x01E*/         UINT8        StandbyBits : 4;                // 0 BitPosition
/*0x01E*/         UINT8        VaType : 4;                     // 4 BitPosition
              };
/*0x01F*/     UINT8        ViewCount;
/*0x020*/     struct _MMPTE OriginalPte;                       // 1 elements, 0x8 bytes (sizeof)
              union                                            // 9 elements, 0x8 bytes (sizeof)
              {
                  struct                                       // 8 elements, 0x8 bytes (sizeof)
                  {
/*0x028*/             UINT64       PteFrame : 36;              // 0 BitPosition
/*0x028*/             UINT64       Channel : 2;                // 36 BitPosition
/*0x028*/             UINT64       Unused : 16;                // 38 BitPosition
/*0x028*/             UINT64       PfnExists : 1;              // 54 BitPosition
/*0x028*/             UINT64       PfnImageVerified : 1;       // 55 BitPosition
/*0x028*/             UINT64       AweAllocation : 1;          // 56 BitPosition
/*0x028*/             UINT64       PrototypePte : 1;           // 57 BitPosition
/*0x028*/             UINT64       PageColor : 6;              // 58 BitPosition
                  };
/*0x028*/         UINT64       EntireField;
              }u4;
          }MMPFN, *PMMPFN;

          typedef struct _MMPFNENTRY                   // 11 elements, 0x2 bytes (sizeof)
          {
              struct                                   // 5 elements, 0x1 bytes (sizeof)
              {
/*0x000*/         UINT8        PageLocation : 3;       // 0 BitPosition
/*0x000*/         UINT8        WriteInProgress : 1;    // 3 BitPosition
/*0x000*/         UINT8        Modified : 1;           // 4 BitPosition
/*0x000*/         UINT8        ReadInProgress : 1;     // 5 BitPosition
/*0x000*/         UINT8        CacheAttribute : 2;     // 6 BitPosition
              };
              struct                                   // 6 elements, 0x1 bytes (sizeof)
              {
/*0x001*/         UINT8        Priority : 3;           // 0 BitPosition
/*0x001*/         UINT8        OnProtectedStandby : 1; // 3 BitPosition
/*0x001*/         UINT8        InPageError : 1;        // 4 BitPosition
/*0x001*/         UINT8        KernelStack : 1;        // 5 BitPosition
/*0x001*/         UINT8        RemovalRequested : 1;   // 6 BitPosition
/*0x001*/         UINT8        ParityError : 1;        // 7 BitPosition
              };
          }MMPFNENTRY, *PMMPFNENTRY;

          typedef struct _MMPFNLIST         // 5 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       Total;
/*0x008*/     enum _MMLISTS ListName;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     UINT64       Flink;
/*0x018*/     UINT64       Blink;
/*0x020*/     UINT64       Lock;
          }MMPFNLIST, *PMMPFNLIST;

          typedef struct _MMPTE                      // 1 elements, 0x8 bytes (sizeof)
          {
              union                                  // 10 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       Long;
/*0x000*/         UINT64       VolatileLong;
/*0x000*/         struct _MMPTE_HARDWARE Hard;       // 16 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _HARDWARE_PTE Flush;        // 16 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _MMPTE_PROTOTYPE Proto;     // 9 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _MMPTE_SOFTWARE Soft;       // 11 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _MMPTE_TIMESTAMP TimeStamp; // 7 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _MMPTE_TRANSITION Trans;    // 10 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _MMPTE_SUBSECTION Subsect;  // 6 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _MMPTE_LIST List;           // 8 elements, 0x8 bytes (sizeof)
              }u;
          }MMPTE, *PMMPTE;

          typedef struct _MMPTE_HARDWARE         // 16 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;            // 0 BitPosition
/*0x000*/     UINT64       Dirty1 : 1;           // 1 BitPosition
/*0x000*/     UINT64       Owner : 1;            // 2 BitPosition
/*0x000*/     UINT64       WriteThrough : 1;     // 3 BitPosition
/*0x000*/     UINT64       CacheDisable : 1;     // 4 BitPosition
/*0x000*/     UINT64       Accessed : 1;         // 5 BitPosition
/*0x000*/     UINT64       Dirty : 1;            // 6 BitPosition
/*0x000*/     UINT64       LargePage : 1;        // 7 BitPosition
/*0x000*/     UINT64       Global : 1;           // 8 BitPosition
/*0x000*/     UINT64       CopyOnWrite : 1;      // 9 BitPosition
/*0x000*/     UINT64       Unused : 1;           // 10 BitPosition
/*0x000*/     UINT64       Write : 1;            // 11 BitPosition
/*0x000*/     UINT64       PageFrameNumber : 36; // 12 BitPosition
/*0x000*/     UINT64       reserved1 : 4;        // 48 BitPosition
/*0x000*/     UINT64       SoftwareWsIndex : 11; // 52 BitPosition
/*0x000*/     UINT64       NoExecute : 1;        // 63 BitPosition
          }MMPTE_HARDWARE, *PMMPTE_HARDWARE;

          typedef struct _MMPTE_LIST       // 8 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;      // 0 BitPosition
/*0x000*/     UINT64       OneEntry : 1;   // 1 BitPosition
/*0x000*/     UINT64       filler0 : 3;    // 2 BitPosition
/*0x000*/     UINT64       Protection : 5; // 5 BitPosition
/*0x000*/     UINT64       Prototype : 1;  // 10 BitPosition
/*0x000*/     UINT64       Transition : 1; // 11 BitPosition
/*0x000*/     UINT64       filler1 : 20;   // 12 BitPosition
/*0x000*/     UINT64       NextEntry : 32; // 32 BitPosition
          }MMPTE_LIST, *PMMPTE_LIST;

          typedef struct _MMPTE_PROTOTYPE            // 9 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;                // 0 BitPosition
/*0x000*/     UINT64       DemandFillProto : 1;      // 1 BitPosition
/*0x000*/     UINT64       HiberVerifyConverted : 1; // 2 BitPosition
/*0x000*/     UINT64       Unused1 : 5;              // 3 BitPosition
/*0x000*/     UINT64       ReadOnly : 1;             // 8 BitPosition
/*0x000*/     UINT64       Combined : 1;             // 9 BitPosition
/*0x000*/     UINT64       Prototype : 1;            // 10 BitPosition
/*0x000*/     UINT64       Protection : 5;           // 11 BitPosition
/*0x000*/     INT64        ProtoAddress : 48;        // 16 BitPosition
          }MMPTE_PROTOTYPE, *PMMPTE_PROTOTYPE;

          typedef struct _MMPTE_SOFTWARE              // 11 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;                 // 0 BitPosition
/*0x000*/     UINT64       PageFileLow : 4;           // 1 BitPosition
/*0x000*/     UINT64       Protection : 5;            // 5 BitPosition
/*0x000*/     UINT64       Prototype : 1;             // 10 BitPosition
/*0x000*/     UINT64       Transition : 1;            // 11 BitPosition
/*0x000*/     UINT64       UsedPageTableEntries : 10; // 12 BitPosition
/*0x000*/     UINT64       InStore : 1;               // 22 BitPosition
/*0x000*/     UINT64       PageFileReserved : 1;      // 23 BitPosition
/*0x000*/     UINT64       PageFileAllocated : 1;     // 24 BitPosition
/*0x000*/     UINT64       DbgCrc : 7;                // 25 BitPosition
/*0x000*/     UINT64       PageFileHigh : 32;         // 32 BitPosition
          }MMPTE_SOFTWARE, *PMMPTE_SOFTWARE;

          typedef struct _MMPTE_SUBSECTION         // 6 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;              // 0 BitPosition
/*0x000*/     UINT64       Unused0 : 4;            // 1 BitPosition
/*0x000*/     UINT64       Protection : 5;         // 5 BitPosition
/*0x000*/     UINT64       Prototype : 1;          // 10 BitPosition
/*0x000*/     UINT64       Unused1 : 5;            // 11 BitPosition
/*0x000*/     INT64        SubsectionAddress : 48; // 16 BitPosition
          }MMPTE_SUBSECTION, *PMMPTE_SUBSECTION;

          typedef struct _MMPTE_TIMESTAMP        // 7 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       MustBeZero : 1;       // 0 BitPosition
/*0x000*/     UINT64       PageFileLow : 4;      // 1 BitPosition
/*0x000*/     UINT64       Protection : 5;       // 5 BitPosition
/*0x000*/     UINT64       Prototype : 1;        // 10 BitPosition
/*0x000*/     UINT64       Transition : 1;       // 11 BitPosition
/*0x000*/     UINT64       Reserved : 20;        // 12 BitPosition
/*0x000*/     UINT64       GlobalTimeStamp : 32; // 32 BitPosition
          }MMPTE_TIMESTAMP, *PMMPTE_TIMESTAMP;

          typedef struct _MMPTE_TRANSITION       // 10 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;            // 0 BitPosition
/*0x000*/     UINT64       Write : 1;            // 1 BitPosition
/*0x000*/     UINT64       Spare : 1;            // 2 BitPosition
/*0x000*/     UINT64       WriteThrough : 1;     // 3 BitPosition
/*0x000*/     UINT64       CacheDisable : 1;     // 4 BitPosition
/*0x000*/     UINT64       Protection : 5;       // 5 BitPosition
/*0x000*/     UINT64       Prototype : 1;        // 10 BitPosition
/*0x000*/     UINT64       Transition : 1;       // 11 BitPosition
/*0x000*/     UINT64       PageFrameNumber : 36; // 12 BitPosition
/*0x000*/     UINT64       Unused : 16;          // 48 BitPosition
          }MMPTE_TRANSITION, *PMMPTE_TRANSITION;

          typedef struct _MMSECURE_FLAGS    // 4 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      ReadOnly : 1;    // 0 BitPosition
/*0x000*/     ULONG32      NoWrite : 1;     // 1 BitPosition
/*0x000*/     ULONG32      SecNoChange : 1; // 2 BitPosition
/*0x000*/     ULONG32      Spare : 9;       // 3 BitPosition
          }MMSECURE_FLAGS, *PMMSECURE_FLAGS;

          typedef struct _MMSESSION                           // 7 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     struct _FAST_MUTEX SystemSpaceViewLock;         // 5 elements, 0x38 bytes (sizeof)
/*0x038*/     struct _FAST_MUTEX* SystemSpaceViewLockPointer;
/*0x040*/     struct _MMVIEW* SystemSpaceViewTable;
/*0x048*/     ULONG32      SystemSpaceHashSize;
/*0x04C*/     ULONG32      SystemSpaceHashEntries;
/*0x050*/     ULONG32      SystemSpaceHashKey;
/*0x054*/     ULONG32      BitmapFailures;
          }MMSESSION, *PMMSESSION;


          typedef struct _MMSUPPORT                        // 22 elements, 0x88 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK WorkingSetMutex;        // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _KGATE* ExitGate;
/*0x010*/     VOID*        AccessLog;
/*0x018*/     struct _LIST_ENTRY WorkingSetExpansionLinks; // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     ULONG32      AgeDistribution[7];
/*0x044*/     ULONG32      MinimumWorkingSetSize;
/*0x048*/     ULONG32      WorkingSetSize;
/*0x04C*/     ULONG32      WorkingSetPrivateSize;
/*0x050*/     ULONG32      MaximumWorkingSetSize;
/*0x054*/     ULONG32      ChargedWslePages;
/*0x058*/     ULONG32      ActualWslePages;
/*0x05C*/     ULONG32      WorkingSetSizeOverhead;
/*0x060*/     ULONG32      PeakWorkingSetSize;
/*0x064*/     ULONG32      HardFaultCount;
/*0x068*/     struct _MMWSL* VmWorkingSetList;
/*0x070*/     UINT16       NextPageColor;
/*0x072*/     UINT16       LastTrimStamp;
/*0x074*/     ULONG32      PageFaultCount;
/*0x078*/     ULONG32      TrimmedPageCount;
/*0x07C*/     ULONG32      Spare;
/*0x080*/     ULONG32      ForceTrimPages;
/*0x084*/     struct _MMSUPPORT_FLAGS Flags;               // 14 elements, 0x4 bytes (sizeof)
          }MMSUPPORT, *PMMSUPPORT;

          typedef struct _MMSUPPORT_FLAGS                 // 14 elements, 0x4 bytes (sizeof)
          {
              struct                                      // 5 elements, 0x1 bytes (sizeof)
              {
/*0x000*/         UINT8        WorkingSetType : 3;        // 0 BitPosition
/*0x000*/         UINT8        Spare : 2;                 // 3 BitPosition
/*0x000*/         UINT8        MaximumWorkingSetHard : 1; // 5 BitPosition
/*0x000*/         UINT8        ForceTrim : 1;             // 6 BitPosition
/*0x000*/         UINT8        MinimumWorkingSetHard : 1; // 7 BitPosition
              };
              struct                                      // 4 elements, 0x1 bytes (sizeof)
              {
/*0x001*/         UINT8        SessionMaster : 1;         // 0 BitPosition
/*0x001*/         UINT8        TrimmerState : 2;          // 1 BitPosition
/*0x001*/         UINT8        Reserved : 1;              // 3 BitPosition
/*0x001*/         UINT8        PageStealers : 4;          // 4 BitPosition
              };
/*0x002*/     UINT8        MemoryPriority : 8;            // 0 BitPosition
              struct                                      // 4 elements, 0x1 bytes (sizeof)
              {
/*0x003*/         UINT8        WsleDeleted : 1;           // 0 BitPosition
/*0x003*/         UINT8        VmExiting : 1;             // 1 BitPosition
/*0x003*/         UINT8        ExpansionFailed : 1;       // 2 BitPosition
/*0x003*/         UINT8        Available : 5;             // 3 BitPosition
              };
          }MMSUPPORT_FLAGS, *PMMSUPPORT_FLAGS;

          typedef struct _MMVIEW                     // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     UINT64       Entry;
              union                                  // 2 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         UINT64       Writable : 1;         // 0 BitPosition
/*0x008*/         struct _CONTROL_AREA* ControlArea;
              };
/*0x010*/     struct _LIST_ENTRY ViewLinks;          // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     VOID*        SessionViewVa;
/*0x028*/     ULONG32      SessionId;
/*0x02C*/     UINT8        _PADDING0_[0x4];
          }MMVIEW, *PMMVIEW;

          typedef struct _MMWSL                                 // 17 elements, 0x510 bytes (sizeof)
          {
/*0x000*/     ULONG32      FirstFree;
/*0x004*/     ULONG32      FirstDynamic;
/*0x008*/     ULONG32      LastEntry;
/*0x00C*/     ULONG32      NextSlot;
/*0x010*/     ULONG32      LastInitializedWsle;
/*0x014*/     ULONG32      NextAgingSlot;
/*0x018*/     ULONG32      LastAgingRemainder;
/*0x01C*/     ULONG32      WsleSize;
/*0x020*/     ULONG32      NonDirectCount;
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     VOID*        LowestPagableAddress;
/*0x030*/     struct _MMWSLE_NONDIRECT_HASH* NonDirectHash;
/*0x038*/     struct _MMWSLE_HASH* HashTableStart;
/*0x040*/     struct _MMWSLE_HASH* HighestPermittedHashAddress;
/*0x048*/     ULONG32      ActiveWsleCounts[8];
/*0x068*/     struct _MI_ACTIVE_WSLE ActiveWsles[8];
/*0x0A8*/     struct _MMWSLE* Wsle;
/*0x0B0*/     struct _MI_USER_VA_INFO UserVaInfo;               // 17 elements, 0x460 bytes (sizeof)
          }MMWSL, *PMMWSL;

          typedef struct _MMWSLE                // 1 elements, 0x8 bytes (sizeof)
          {
              union                             // 4 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         VOID*        VirtualAddress;
/*0x000*/         UINT64       Long;
/*0x000*/         struct _MMWSLENTRY e1;        // 7 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _MMWSLE_FREE_ENTRY e2; // 3 elements, 0x8 bytes (sizeof)
              }u1;
          }MMWSLE, *PMMWSLE;

          typedef struct _MMWSLE_FREE_ENTRY   // 3 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       MustBeZero : 1;    // 0 BitPosition
/*0x000*/     UINT64       PreviousFree : 31; // 1 BitPosition
/*0x000*/     UINT64       NextFree : 32;     // 32 BitPosition
          }MMWSLE_FREE_ENTRY, *PMMWSLE_FREE_ENTRY;

          typedef struct _MMWSLE_HASH // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      Index;
          }MMWSLE_HASH, *PMMWSLE_HASH;

          typedef struct _MMWSLE_NONDIRECT_HASH // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        Key;
/*0x008*/     ULONG32      Index;
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }MMWSLE_NONDIRECT_HASH, *PMMWSLE_NONDIRECT_HASH;

          typedef struct _MMWSLENTRY               // 7 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       Valid : 1;              // 0 BitPosition
/*0x000*/     UINT64       Spare : 1;              // 1 BitPosition
/*0x000*/     UINT64       Hashed : 1;             // 2 BitPosition
/*0x000*/     UINT64       Direct : 1;             // 3 BitPosition
/*0x000*/     UINT64       Protection : 5;         // 4 BitPosition
/*0x000*/     UINT64       Age : 3;                // 9 BitPosition
/*0x000*/     UINT64       VirtualPageNumber : 52; // 12 BitPosition
          }MMWSLENTRY, *PMMWSLENTRY;

          typedef struct _MEMORY_ALLOCATION_DESCRIPTOR // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;            // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     enum _TYPE_OF_MEMORY MemoryType;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     UINT64       BasePage;
/*0x020*/     UINT64       PageCount;
          }MEMORY_ALLOCATION_DESCRIPTOR, *PMEMORY_ALLOCATION_DESCRIPTOR;



          typedef struct _MDL               // 8 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _MDL* Next;
/*0x008*/     INT16        Size;
/*0x00A*/     INT16        MdlFlags;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     struct _EPROCESS* Process;
/*0x018*/     VOID*        MappedSystemVa;
/*0x020*/     VOID*        StartVa;
/*0x028*/     ULONG32      ByteCount;
/*0x02C*/     ULONG32      ByteOffset;
          }MDL, *PMDL;
          typedef struct _PHYSICAL_MEMORY_DESCRIPTOR // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     ULONG32      NumberOfRuns;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT64       NumberOfPages;
/*0x010*/     struct _PHYSICAL_MEMORY_RUN Run[1];
          }PHYSICAL_MEMORY_DESCRIPTOR, *PPHYSICAL_MEMORY_DESCRIPTOR;

          typedef struct _PHYSICAL_MEMORY_RUN // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       BasePage;
/*0x008*/     UINT64       PageCount;
          }PHYSICAL_MEMORY_RUN, *PPHYSICAL_MEMORY_RUN;

         typedef struct _PTE_TRACKER              // 13 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;        // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _MDL* Mdl;
/*0x018*/     UINT64       Count;
/*0x020*/     VOID*        SystemVa;
/*0x028*/     VOID*        StartVa;
/*0x030*/     ULONG32      Offset;
/*0x034*/     ULONG32      Length;
/*0x038*/     UINT64       Page;
              struct                               // 4 elements, 0x4 bytes (sizeof)
              {
/*0x040*/         ULONG32      IoMapping : 1;      // 0 BitPosition
/*0x040*/         ULONG32      Matched : 1;        // 1 BitPosition
/*0x040*/         ULONG32      CacheAttribute : 2; // 2 BitPosition
/*0x040*/         ULONG32      Spare : 28;         // 4 BitPosition
              };
/*0x048*/     VOID*        StackTrace[7];
          }PTE_TRACKER, *PPTE_TRACKER;

          typedef struct _SYSPTES_HEADER        // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListHead;      // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT64       Count;
/*0x018*/     UINT64       NumberOfEntries;
/*0x020*/     UINT64       NumberOfEntriesPeak;
          }SYSPTES_HEADER, *PSYSPTES_HEADER;

typedef enum _MEMORY_CACHING_TYPE  // 7 elements, 0x4 bytes
{
    MmNonCached              = 0 /*0x0*/,
    MmCached                 = 1 /*0x1*/,
    MmWriteCombined          = 2 /*0x2*/,
    MmHardwareCoherentCached = 3 /*0x3*/,
    MmNonCachedUnordered     = 4 /*0x4*/,
    MmUSWCCached             = 5 /*0x5*/,
    MmMaximumCacheType       = 6 /*0x6*/
}MEMORY_CACHING_TYPE, *PMEMORY_CACHING_TYPE;

typedef enum _MEMORY_CACHING_TYPE_ORIG  // 1 elements, 0x4 bytes
{
    MmFrameBufferCached = 2 /*0x2*/
}MEMORY_CACHING_TYPE_ORIG, *PMEMORY_CACHING_TYPE_ORIG;

typedef enum _MI_PFN_CACHE_ATTRIBUTE  // 4 elements, 0x4 bytes
{
    MiNonCached     = 0 /*0x0*/,
    MiCached        = 1 /*0x1*/,
    MiWriteCombined = 2 /*0x2*/,
    MiNotMapped     = 3 /*0x3*/
}MI_PFN_CACHE_ATTRIBUTE, *PMI_PFN_CACHE_ATTRIBUTE;

typedef enum _MI_STORE_BIT_TYPE  // 3 elements, 0x4 bytes
{
    MiStoreBitTypeInStore = 0 /*0x0*/,
    MiStoreBitTypeEvicted = 1 /*0x1*/,
    MiStoreBitTypeMax     = 2 /*0x2*/
}MI_STORE_BIT_TYPE, *PMI_STORE_BIT_TYPE;

typedef enum _MI_SYSTEM_VA_TYPE  // 15 elements, 0x4 bytes
{
    MiVaUnused              = 0 /*0x0*/,
    MiVaSessionSpace        = 1 /*0x1*/,
    MiVaProcessSpace        = 2 /*0x2*/,
    MiVaBootLoaded          = 3 /*0x3*/,
    MiVaPfnDatabase         = 4 /*0x4*/,
    MiVaNonPagedPool        = 5 /*0x5*/,
    MiVaPagedPool           = 6 /*0x6*/,
    MiVaSpecialPoolPaged    = 7 /*0x7*/,
    MiVaSystemCache         = 8 /*0x8*/,
    MiVaSystemPtes          = 9 /*0x9*/,
    MiVaHal                 = 10 /*0xA*/,
    MiVaSessionGlobalSpace  = 11 /*0xB*/,
    MiVaDriverImages        = 12 /*0xC*/,
    MiVaSpecialPoolNonPaged = 13 /*0xD*/,
    MiVaMaximumType         = 14 /*0xE*/
}MI_SYSTEM_VA_TYPE, *PMI_SYSTEM_VA_TYPE;

typedef enum _MM_PAGE_ACCESS_TYPE  // 4 elements, 0x4 bytes
{
    MmPteAccessType         = 0 /*0x0*/,
    MmCcReadAheadType       = 1 /*0x1*/,
    MmPfnRepurposeType      = 2 /*0x2*/,
    MmMaximumPageAccessType = 3 /*0x3*/
}MM_PAGE_ACCESS_TYPE, *PMM_PAGE_ACCESS_TYPE;

typedef enum _MM_POOL_FAILURE_REASONS  // 12 elements, 0x4 bytes
{
    MmNonPagedNoPtes               = 0 /*0x0*/,
    MmPriorityTooLow               = 1 /*0x1*/,
    MmNonPagedNoPagesAvailable     = 2 /*0x2*/,
    MmPagedNoPtes                  = 3 /*0x3*/,
    MmSessionPagedNoPtes           = 4 /*0x4*/,
    MmPagedNoPagesAvailable        = 5 /*0x5*/,
    MmSessionPagedNoPagesAvailable = 6 /*0x6*/,
    MmPagedNoCommit                = 7 /*0x7*/,
    MmSessionPagedNoCommit         = 8 /*0x8*/,
    MmNonPagedNoResidentAvailable  = 9 /*0x9*/,
    MmNonPagedNoCommit             = 10 /*0xA*/,
    MmMaximumFailureReason         = 11 /*0xB*/
}MM_POOL_FAILURE_REASONS, *PMM_POOL_FAILURE_REASONS;

typedef enum _MM_POOL_PRIORITIES  // 4 elements, 0x4 bytes
{
    MmHighPriority        = 0 /*0x0*/,
    MmNormalPriority      = 1 /*0x1*/,
    MmLowPriority         = 2 /*0x2*/,
    MmMaximumPoolPriority = 3 /*0x3*/
}MM_POOL_PRIORITIES, *PMM_POOL_PRIORITIES;

typedef enum _MM_POOL_TYPES  // 4 elements, 0x4 bytes
{
    MmNonPagedPool     = 0 /*0x0*/,
    MmPagedPool        = 1 /*0x1*/,
    MmSessionPagedPool = 2 /*0x2*/,
    MmMaximumPoolType  = 3 /*0x3*/
}MM_POOL_TYPES, *PMM_POOL_TYPES;

typedef enum _MM_PREEMPTIVE_TRIMS  // 5 elements, 0x4 bytes
{
    MmPreemptForNonPaged         = 0 /*0x0*/,
    MmPreemptForPaged            = 1 /*0x1*/,
    MmPreemptForNonPagedPriority = 2 /*0x2*/,
    MmPreemptForPagedPriority    = 3 /*0x3*/,
    MmMaximumPreempt             = 4 /*0x4*/
}MM_PREEMPTIVE_TRIMS, *PMM_PREEMPTIVE_TRIMS;

typedef enum _MMLISTS  // 8 elements, 0x4 bytes
{
    ZeroedPageList          = 0 /*0x0*/,
    FreePageList            = 1 /*0x1*/,
    StandbyPageList         = 2 /*0x2*/,
    ModifiedPageList        = 3 /*0x3*/,
    ModifiedNoWritePageList = 4 /*0x4*/,
    BadPageList             = 5 /*0x5*/,
    ActiveAndValid          = 6 /*0x6*/,
    TransitionPage          = 7 /*0x7*/
}MMLISTS, *PMMLISTS;

typedef enum _TYPE_OF_MEMORY  // 30 elements, 0x4 bytes
{
    LoaderExceptionBlock     = 0 /*0x0*/,
    LoaderSystemBlock        = 1 /*0x1*/,
    LoaderFree               = 2 /*0x2*/,
    LoaderBad                = 3 /*0x3*/,
    LoaderLoadedProgram      = 4 /*0x4*/,
    LoaderFirmwareTemporary  = 5 /*0x5*/,
    LoaderFirmwarePermanent  = 6 /*0x6*/,
    LoaderOsloaderHeap       = 7 /*0x7*/,
    LoaderOsloaderStack      = 8 /*0x8*/,
    LoaderSystemCode         = 9 /*0x9*/,
    LoaderHalCode            = 10 /*0xA*/,
    LoaderBootDriver         = 11 /*0xB*/,
    LoaderConsoleInDriver    = 12 /*0xC*/,
    LoaderConsoleOutDriver   = 13 /*0xD*/,
    LoaderStartupDpcStack    = 14 /*0xE*/,
    LoaderStartupKernelStack = 15 /*0xF*/,
    LoaderStartupPanicStack  = 16 /*0x10*/,
    LoaderStartupPcrPage     = 17 /*0x11*/,
    LoaderStartupPdrPage     = 18 /*0x12*/,
    LoaderRegistryData       = 19 /*0x13*/,
    LoaderMemoryData         = 20 /*0x14*/,
    LoaderNlsData            = 21 /*0x15*/,
    LoaderSpecialMemory      = 22 /*0x16*/,
    LoaderBBTMemory          = 23 /*0x17*/,
    LoaderReserve            = 24 /*0x18*/,
    LoaderXIPRom             = 25 /*0x19*/,
    LoaderHALCachedMemory    = 26 /*0x1A*/,
    LoaderLargePageFiller    = 27 /*0x1B*/,
    LoaderErrorLogMemory     = 28 /*0x1C*/,
    LoaderMaximum            = 29 /*0x1D*/
}TYPE_OF_MEMORY, *PTYPE_OF_MEMORY;

typedef enum _WORKING_SET_TYPE  // 7 elements, 0x4 bytes
{
    WorkingSetTypeUser        = 0 /*0x0*/,
    WorkingSetTypeSession     = 1 /*0x1*/,
    WorkingSetTypeSystemTypes = 2 /*0x2*/,
    WorkingSetTypeSystemCache = 2 /*0x2*/,
    WorkingSetTypePagedPool   = 3 /*0x3*/,
    WorkingSetTypeSystemPtes  = 4 /*0x4*/,
    WorkingSetTypeMaximum     = 5 /*0x5*/
}WORKING_SET_TYPE, *PWORKING_SET_TYPE;

          typedef struct _COLORED_PAGE_INFO // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     LONG32       BeingZeroed;
/*0x004*/     ULONG32      Processor;
/*0x008*/     UINT64       PagesQueued;
/*0x010*/     struct _MMPFN* PfnAllocation;
          }COLORED_PAGE_INFO, *PCOLORED_PAGE_INFO;

           typedef struct _DIRTY_PAGE_STATISTICS         // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT64       DirtyPages;
/*0x008*/     UINT64       DirtyPagesLastScan;
/*0x010*/     ULONG32      DirtyPagesScheduledLastScan;
/*0x014*/     UINT8        _PADDING0_[0x4];
          }DIRTY_PAGE_STATISTICS, *PDIRTY_PAGE_STATISTICS;

          typedef struct _DIRTY_PAGE_THRESHOLDS      // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT64       DirtyPageThreshold;
/*0x008*/     UINT64       DirtyPageThresholdTop;
/*0x010*/     UINT64       DirtyPageThresholdBottom;
/*0x018*/     ULONG32      DirtyPageTarget;
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }DIRTY_PAGE_THRESHOLDS, *PDIRTY_PAGE_THRESHOLDS;

          typedef struct _GENERIC_MAPPING  // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      GenericRead;
/*0x004*/     ULONG32      GenericWrite;
/*0x008*/     ULONG32      GenericExecute;
/*0x00C*/     ULONG32      GenericAll;
          }GENERIC_MAPPING, *PGENERIC_MAPPING;

