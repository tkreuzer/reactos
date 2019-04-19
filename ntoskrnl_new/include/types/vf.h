          typedef struct _VF_ADDRESS_RANGE // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT8*       Start;
/*0x008*/     UINT8*       End;
          }VF_ADDRESS_RANGE, *PVF_ADDRESS_RANGE;

          typedef struct _VF_AVL_TABLE                // 2 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     struct _RTL_AVL_TABLE RtlTable;         // 11 elements, 0x68 bytes (sizeof)
/*0x068*/     struct _VF_AVL_TREE_NODE* ReservedNode;
          }VF_AVL_TABLE, *PVF_AVL_TABLE;

          typedef struct _VF_AVL_TREE        // 7 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     LONG32       Lock;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        NodeToFree;
/*0x010*/     UINT64       NodeRangeSize;
/*0x018*/     UINT64       NodeCount;
/*0x020*/     struct _VF_AVL_TABLE* Tables;
/*0x028*/     ULONG32      TablesNo;
              union                          // 2 elements, 0x4 bytes (sizeof)
              {
/*0x02C*/         ULONG32      NodeSize;
/*0x02C*/         ULONG32      UseLookaside;
              }u1;
          }VF_AVL_TREE, *PVF_AVL_TREE;

          typedef struct _VF_AVL_TREE_NODE // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        p;
/*0x008*/     UINT64       RangeSize;
          }VF_AVL_TREE_NODE, *PVF_AVL_TREE_NODE;

          typedef struct _VF_KE_CRITICAL_REGION_TRACE // 2 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _ETHREAD* Thread;
/*0x008*/     VOID*        StackTrace[7];
          }VF_KE_CRITICAL_REGION_TRACE, *PVF_KE_CRITICAL_REGION_TRACE;

          typedef struct _VF_POOL_TRACE    // 4 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     VOID*        Address;
/*0x008*/     UINT64       Size;
/*0x010*/     struct _ETHREAD* Thread;
/*0x018*/     VOID*        StackTrace[13];
          }VF_POOL_TRACE, *PVF_POOL_TRACE;

          typedef struct _VF_SUSPECT_DRIVER_ENTRY // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Links;           // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Loads;
/*0x014*/     ULONG32      Unloads;
/*0x018*/     struct _UNICODE_STRING BaseName;    // 3 elements, 0x10 bytes (sizeof)
          }VF_SUSPECT_DRIVER_ENTRY, *PVF_SUSPECT_DRIVER_ENTRY;

          typedef struct _VF_TARGET_ALL_SHARED_EXPORT_THUNKS                          // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _VERIFIER_SHARED_EXPORT_THUNK* SharedExportThunks;
/*0x008*/     struct _VERIFIER_SHARED_EXPORT_THUNK* PoolSharedExportThunks;
/*0x010*/     struct _VERIFIER_SHARED_EXPORT_THUNK* OrderDependentSharedExportThunks;
/*0x018*/     struct _VERIFIER_SHARED_EXPORT_THUNK* XdvSharedExportThunks;
          }VF_TARGET_ALL_SHARED_EXPORT_THUNKS, *PVF_TARGET_ALL_SHARED_EXPORT_THUNKS;

          typedef struct _VF_TARGET_DRIVER                                          // 3 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _VF_AVL_TREE_NODE TreeNode;                                    // 2 elements, 0x10 bytes (sizeof)
              union                                                                 // 2 elements, 0x20 bytes (sizeof)
              {
/*0x010*/         struct _VF_TARGET_ALL_SHARED_EXPORT_THUNKS AllSharedExportThunks; // 4 elements, 0x20 bytes (sizeof)
                  struct                                                            // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x010*/             ULONG32      SnapSharedExportsFailed : 1;                     // 0 BitPosition
/*0x010*/             ULONG32      Spare : 31;                                      // 1 BitPosition
                  }Flags;
              }u1;
/*0x030*/     struct _VF_TARGET_VERIFIED_DRIVER_DATA* VerifiedData;
          }VF_TARGET_DRIVER, *PVF_TARGET_DRIVER;

          typedef struct _VF_TARGET_VERIFIED_DRIVER_DATA           // 32 elements, 0x100 bytes (sizeof)
          {
/*0x000*/     struct _VF_SUSPECT_DRIVER_ENTRY* SuspectDriverEntry;
/*0x008*/     VOID*        WMICallback;
/*0x010*/     struct _LIST_ENTRY EtwHandlesListHead;               // 2 elements, 0x10 bytes (sizeof)
              union                                                // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                           // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x020*/             ULONG32      MissedEtwRegistration : 1;      // 0 BitPosition
/*0x020*/             ULONG32      Spare : 31;                     // 1 BitPosition
                  }Flags;
/*0x020*/         ULONG32      Whole;
              }u1;
/*0x028*/     UINT64       Signature;
/*0x030*/     union _SLIST_HEADER PoolPageHeaders;                 // 4 elements, 0x10 bytes (sizeof)
/*0x040*/     union _SLIST_HEADER PoolTrackers;                    // 4 elements, 0x10 bytes (sizeof)
/*0x050*/     ULONG32      CurrentPagedPoolAllocations;
/*0x054*/     ULONG32      CurrentNonPagedPoolAllocations;
/*0x058*/     ULONG32      PeakPagedPoolAllocations;
/*0x05C*/     ULONG32      PeakNonPagedPoolAllocations;
/*0x060*/     UINT64       PagedBytes;
/*0x068*/     UINT64       NonPagedBytes;
/*0x070*/     UINT64       PeakPagedBytes;
/*0x078*/     UINT64       PeakNonPagedBytes;
/*0x080*/     ULONG32      RaiseIrqls;
/*0x084*/     ULONG32      AcquireSpinLocks;
/*0x088*/     ULONG32      SynchronizeExecutions;
/*0x08C*/     ULONG32      AllocationsWithNoTag;
/*0x090*/     ULONG32      AllocationsFailed;
/*0x094*/     ULONG32      AllocationsFailedDeliberately;
/*0x098*/     UINT64       LockedBytes;
/*0x0A0*/     UINT64       PeakLockedBytes;
/*0x0A8*/     UINT64       MappedLockedBytes;
/*0x0B0*/     UINT64       PeakMappedLockedBytes;
/*0x0B8*/     UINT64       MappedIoSpaceBytes;
/*0x0C0*/     UINT64       PeakMappedIoSpaceBytes;
/*0x0C8*/     UINT64       PagesForMdlBytes;
/*0x0D0*/     UINT64       PeakPagesForMdlBytes;
/*0x0D8*/     UINT64       ContiguousMemoryBytes;
/*0x0E0*/     UINT64       PeakContiguousMemoryBytes;
/*0x0E8*/     struct _LIST_ENTRY ContiguousMemoryListHead;         // 2 elements, 0x10 bytes (sizeof)
/*0x0F8*/     UINT8        _PADDING0_[0x8];
          }VF_TARGET_VERIFIED_DRIVER_DATA, *PVF_TARGET_VERIFIED_DRIVER_DATA;

          typedef struct _VF_TRACKER     // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      TrackerFlags;
/*0x004*/     ULONG32      TrackerSize;
/*0x008*/     ULONG32      TrackerIndex;
/*0x00C*/     ULONG32      TraceDepth;
          }VF_TRACKER, *PVF_TRACKER;

          typedef struct _VF_TRACKER_STAMP  // 5 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        Thread;
/*0x008*/     UINT8        Flags : 8;       // 0 BitPosition
/*0x009*/     UINT8        OldIrql : 8;     // 0 BitPosition
/*0x00A*/     UINT8        NewIrql : 8;     // 0 BitPosition
/*0x00B*/     UINT8        Processor : 8;   // 0 BitPosition
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }VF_TRACKER_STAMP, *PVF_TRACKER_STAMP;

          typedef struct _VF_WATCHDOG_IRP        // 6 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;      // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _IRP* Irp;
/*0x018*/     ULONG32      DueTickCount;
/*0x01C*/     UINT8        Inserted;
/*0x01D*/     CHAR         TrackedStackLocation;
/*0x01E*/     UINT16       CancelTimeoutTicks;
          }VF_WATCHDOG_IRP, *PVF_WATCHDOG_IRP;

           typedef struct _VI_DEADLOCK_GLOBALS                      // 28 elements, 0x8168 bytes (sizeof)
           {
/*0x000*/      INT64        TimeAcquire;
/*0x008*/      INT64        TimeRelease;
/*0x010*/      struct _LIST_ENTRY* ResourceDatabase;
/*0x018*/      UINT64       ResourceDatabaseCount;
/*0x020*/      struct _VF_ADDRESS_RANGE ResourceAddressRange[1023];
/*0x4010*/     struct _LIST_ENTRY* ThreadDatabase;
/*0x4018*/     UINT64       ThreadDatabaseCount;
/*0x4020*/     struct _VF_ADDRESS_RANGE ThreadAddressRange[1023];
/*0x8010*/     ULONG32      AllocationFailures;
/*0x8014*/     ULONG32      NodesTrimmedBasedOnAge;
/*0x8018*/     ULONG32      NodesTrimmedBasedOnCount;
/*0x801C*/     ULONG32      NodesSearched;
/*0x8020*/     ULONG32      MaxNodesSearched;
/*0x8024*/     ULONG32      SequenceNumber;
/*0x8028*/     ULONG32      RecursionDepthLimit;
/*0x802C*/     ULONG32      SearchedNodesLimit;
/*0x8030*/     ULONG32      DepthLimitHits;
/*0x8034*/     ULONG32      SearchLimitHits;
/*0x8038*/     ULONG32      ABC_ACB_Skipped;
/*0x803C*/     ULONG32      OutOfOrderReleases;
/*0x8040*/     ULONG32      NodesReleasedOutOfOrder;
/*0x8044*/     ULONG32      TotalReleases;
/*0x8048*/     ULONG32      RootNodesDeleted;
/*0x804C*/     ULONG32      ForgetHistoryCounter;
/*0x8050*/     VOID*        Instigator;
/*0x8058*/     ULONG32      NumberOfParticipants;
/*0x805C*/     UINT8        _PADDING0_[0x4];
/*0x8060*/     struct _VI_DEADLOCK_NODE* Participant[32];
/*0x8160*/     LONG32       ChildrenCountWatermark;
/*0x8164*/     UINT8        _PADDING1_[0x4];
           }VI_DEADLOCK_GLOBALS, *PVI_DEADLOCK_GLOBALS;

          typedef struct _VI_DEADLOCK_NODE                 // 11 elements, 0xD0 bytes (sizeof)
          {
/*0x000*/     struct _VI_DEADLOCK_NODE* Parent;
/*0x008*/     struct _LIST_ENTRY ChildrenList;             // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     struct _LIST_ENTRY SiblingsList;             // 2 elements, 0x10 bytes (sizeof)
              union                                        // 2 elements, 0x10 bytes (sizeof)
              {
/*0x028*/         struct _LIST_ENTRY ResourceList;         // 2 elements, 0x10 bytes (sizeof)
/*0x028*/         struct _LIST_ENTRY FreeListEntry;        // 2 elements, 0x10 bytes (sizeof)
              };
/*0x038*/     struct _VI_DEADLOCK_RESOURCE* Root;
/*0x040*/     struct _VI_DEADLOCK_THREAD* ThreadEntry;
              union                                        // 5 elements, 0x4 bytes (sizeof)
              {
                  struct                                   // 4 elements, 0x4 bytes (sizeof)
                  {
/*0x048*/             ULONG32      Active : 1;             // 0 BitPosition
/*0x048*/             ULONG32      OnlyTryAcquireUsed : 1; // 1 BitPosition
/*0x048*/             ULONG32      ReleasedOutOfOrder : 1; // 2 BitPosition
/*0x048*/             ULONG32      SequenceNumber : 29;    // 3 BitPosition
                  };
/*0x048*/         ULONG32      Whole;
              }u1;
/*0x04C*/     LONG32       ChildrenCount;
/*0x050*/     VOID*        StackTrace[8];
/*0x090*/     VOID*        ParentStackTrace[8];
          }VI_DEADLOCK_NODE, *PVI_DEADLOCK_NODE;

          typedef struct _VI_DEADLOCK_RESOURCE         // 11 elements, 0xF8 bytes (sizeof)
          {
/*0x000*/     enum _VI_DEADLOCK_RESOURCE_TYPE Type;
              struct                                   // 2 elements, 0x4 bytes (sizeof)
              {
/*0x004*/         ULONG32      NodeCount : 16;         // 0 BitPosition
/*0x004*/         ULONG32      RecursionCount : 16;    // 16 BitPosition
              };
/*0x008*/     VOID*        ResourceAddress;
/*0x010*/     struct _VI_DEADLOCK_THREAD* ThreadOwner;
/*0x018*/     struct _LIST_ENTRY ResourceList;         // 2 elements, 0x10 bytes (sizeof)
              union                                    // 2 elements, 0x10 bytes (sizeof)
              {
/*0x028*/         struct _LIST_ENTRY HashChainList;    // 2 elements, 0x10 bytes (sizeof)
/*0x028*/         struct _LIST_ENTRY FreeListEntry;    // 2 elements, 0x10 bytes (sizeof)
              };
/*0x038*/     VOID*        StackTrace[8];
/*0x078*/     VOID*        LastAcquireTrace[8];
/*0x0B8*/     VOID*        LastReleaseTrace[8];
          }VI_DEADLOCK_RESOURCE, *PVI_DEADLOCK_RESOURCE;

          typedef struct _VI_DEADLOCK_THREAD              // 8 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _KTHREAD* Thread;
/*0x008*/     struct _VI_DEADLOCK_NODE* CurrentSpinNode;
/*0x010*/     struct _VI_DEADLOCK_NODE* CurrentOtherNode;
              union                                       // 2 elements, 0x10 bytes (sizeof)
              {
/*0x018*/         struct _LIST_ENTRY ListEntry;           // 2 elements, 0x10 bytes (sizeof)
/*0x018*/         struct _LIST_ENTRY FreeListEntry;       // 2 elements, 0x10 bytes (sizeof)
              };
/*0x028*/     ULONG32      NodeCount;
/*0x02C*/     ULONG32      PagingCount;
/*0x030*/     UINT8        ThreadUsesEresources;
/*0x031*/     UINT8        _PADDING0_[0x7];
          }VI_DEADLOCK_THREAD, *PVI_DEADLOCK_THREAD;

          typedef struct _VI_FAULT_TRACE  // 2 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     struct _ETHREAD* Thread;
/*0x008*/     VOID*        StackTrace[8];
          }VI_FAULT_TRACE, *PVI_FAULT_TRACE;

          typedef struct _VI_POOL_ENTRY                   // 3 elements, 0x20 bytes (sizeof)
          {
              union                                       // 3 elements, 0x20 bytes (sizeof)
              {
/*0x000*/         struct _VI_POOL_PAGE_HEADER PageHeader; // 3 elements, 0x18 bytes (sizeof)
/*0x000*/         struct _VI_POOL_ENTRY_INUSE InUse;      // 4 elements, 0x20 bytes (sizeof)
/*0x000*/         struct _SLIST_ENTRY* NextFree;
              };
          }VI_POOL_ENTRY, *PVI_POOL_ENTRY;

          typedef struct _VI_POOL_ENTRY_INUSE // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     VOID*        VirtualAddress;
/*0x008*/     VOID*        CallingAddress;
/*0x010*/     UINT64       NumberOfBytes;
/*0x018*/     UINT64       Tag;
          }VI_POOL_ENTRY_INUSE, *PVI_POOL_ENTRY_INUSE;

          typedef struct _VI_POOL_PAGE_HEADER // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _SLIST_ENTRY* NextPage;
/*0x008*/     VOID*        VerifierEntry;
/*0x010*/     UINT64       Signature;
          }VI_POOL_PAGE_HEADER, *PVI_POOL_PAGE_HEADER;

          typedef struct _VI_TRACK_IRQL   // 6 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     VOID*        Thread;
/*0x008*/     UINT8        OldIrql;
/*0x009*/     UINT8        NewIrql;
/*0x00A*/     UINT16       Processor;
/*0x00C*/     ULONG32      TickCount;
/*0x010*/     VOID*        StackTrace[5];
          }VI_TRACK_IRQL, *PVI_TRACK_IRQL;

          typedef struct _VI_VERIFIER_ISSUE // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT64       IssueType;
/*0x008*/     VOID*        Address;
/*0x010*/     UINT64       Parameters[2];
          }VI_VERIFIER_ISSUE, *PVI_VERIFIER_ISSUE;

typedef enum _VI_DEADLOCK_RESOURCE_TYPE  // 10 elements, 0x4 bytes
{
    VfDeadlockUnknown               = 0 /*0x0*/,
    VfDeadlockMutex                 = 1 /*0x1*/,
    VfDeadlockMutexAbandoned        = 2 /*0x2*/,
    VfDeadlockFastMutex             = 3 /*0x3*/,
    VfDeadlockFastMutexUnsafe       = 4 /*0x4*/,
    VfDeadlockSpinLock              = 5 /*0x5*/,
    VfDeadlockInStackQueuedSpinLock = 6 /*0x6*/,
    VfDeadlockUnusedSpinLock        = 7 /*0x7*/,
    VfDeadlockEresource             = 8 /*0x8*/,
    VfDeadlockTypeMaximum           = 9 /*0x9*/
}VI_DEADLOCK_RESOURCE_TYPE, *PVI_DEADLOCK_RESOURCE_TYPE;

