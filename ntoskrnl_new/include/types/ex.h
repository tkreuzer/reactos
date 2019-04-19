          typedef struct _EX_FAST_REF      // 3 elements, 0x8 bytes (sizeof)
          {
              union                        // 3 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         VOID*        Object;
/*0x000*/         UINT64       RefCnt : 4; // 0 BitPosition
/*0x000*/         UINT64       Value;
              };
          }EX_FAST_REF, *PEX_FAST_REF;

          typedef struct _EX_PUSH_LOCK                 // 7 elements, 0x8 bytes (sizeof)
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
          }EX_PUSH_LOCK, *PEX_PUSH_LOCK;

          typedef struct _EX_PUSH_LOCK_CACHE_AWARE // 1 elements, 0x100 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK* Locks[32];
          }EX_PUSH_LOCK_CACHE_AWARE, *PEX_PUSH_LOCK_CACHE_AWARE;

          typedef struct _EX_PUSH_LOCK_WAIT_BLOCK        // 6 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _KEVENT WakeEvent;                  // 1 elements, 0x18 bytes (sizeof)
/*0x018*/     struct _EX_PUSH_LOCK_WAIT_BLOCK* Next;
/*0x020*/     struct _EX_PUSH_LOCK_WAIT_BLOCK* Last;
/*0x028*/     struct _EX_PUSH_LOCK_WAIT_BLOCK* Previous;
/*0x030*/     LONG32       ShareCount;
/*0x034*/     LONG32       Flags;
/*0x038*/     UINT8        _PADDING0_[0x8];
          }EX_PUSH_LOCK_WAIT_BLOCK, *PEX_PUSH_LOCK_WAIT_BLOCK;

          typedef struct _EX_RUNDOWN_REF // 2 elements, 0x8 bytes (sizeof)
          {
              union                      // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       Count;
/*0x000*/         VOID*        Ptr;
              };
          }EX_RUNDOWN_REF, *PEX_RUNDOWN_REF;

          typedef struct _EX_WORK_QUEUE                // 6 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _KQUEUE WorkerQueue;              // 5 elements, 0x40 bytes (sizeof)
/*0x040*/     ULONG32      WorkItemsProcessed;
/*0x044*/     ULONG32      WorkItemsProcessedLastPass;
/*0x048*/     UINT16       ThreadCount;
              struct                                   // 2 elements, 0x2 bytes (sizeof)
              {
/*0x04A*/         UINT16       ThreadMaximum : 15;     // 0 BitPosition
/*0x04A*/         UINT16       WaitMode : 1;           // 15 BitPosition
              };
          }EX_WORK_QUEUE, *PEX_WORK_QUEUE;

          typedef struct _EXHANDLE                   // 4 elements, 0x8 bytes (sizeof)
          {
              union                                  // 3 elements, 0x8 bytes (sizeof)
              {
                  struct                             // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             ULONG32      TagBits : 2;      // 0 BitPosition
/*0x000*/             ULONG32      Index : 30;       // 2 BitPosition
                  };
/*0x000*/         VOID*        GenericHandleOverlay;
/*0x000*/         UINT64       Value;
              };
          }EXHANDLE, *PEXHANDLE;

          typedef struct _GENERAL_LOOKASIDE                                                                                                                                                                                                // 22 elements, 0x80 bytes (sizeof)
          {
              union                                                                                                                                                                                                                        // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         union _SLIST_HEADER ListHead;                                                                                                                                                                                            // 4 elements, 0x10 bytes (sizeof)
/*0x000*/         struct _SINGLE_LIST_ENTRY SingleListHead;                                                                                                                                                                                // 1 elements, 0x8 bytes (sizeof)
              };
/*0x010*/     UINT16       Depth;
/*0x012*/     UINT16       MaximumDepth;
/*0x014*/     ULONG32      TotalAllocates;
              union                                                                                                                                                                                                                        // 2 elements, 0x4 bytes (sizeof)
              {
/*0x018*/         ULONG32      AllocateMisses;
/*0x018*/         ULONG32      AllocateHits;
              };
/*0x01C*/     ULONG32      TotalFrees;
              union                                                                                                                                                                                                                        // 2 elements, 0x4 bytes (sizeof)
              {
/*0x020*/         ULONG32      FreeMisses;
/*0x020*/         ULONG32      FreeHits;
              };
/*0x024*/     enum _POOL_TYPE Type;
/*0x028*/     ULONG32      Tag;
/*0x02C*/     ULONG32      Size;
              union                                                                                                                                                                                                                        // 2 elements, 0x8 bytes (sizeof)
              {
/*0x030*/         FUNCT_00B1_0731_AllocateEx* AllocateEx;
/*0x030*/         FUNCT_00B1_073B_Allocate* Allocate;
              };
              union                                                                                                                                                                                                                        // 2 elements, 0x8 bytes (sizeof)
              {
/*0x038*/         FUNCT_00AE_0740_FreeEx* FreeEx;
/*0x038*/         FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* Free;
              };
/*0x040*/     struct _LIST_ENTRY ListEntry;                                                                                                                                                                                                // 2 elements, 0x10 bytes (sizeof)
/*0x050*/     ULONG32      LastTotalAllocates;
              union                                                                                                                                                                                                                        // 2 elements, 0x4 bytes (sizeof)
              {
/*0x054*/         ULONG32      LastAllocateMisses;
/*0x054*/         ULONG32      LastAllocateHits;
              };
/*0x058*/     ULONG32      Future[2];
/*0x060*/     UINT8        _PADDING0_[0x20];
          }GENERAL_LOOKASIDE, *PGENERAL_LOOKASIDE;

          typedef struct _GENERAL_LOOKASIDE_POOL                                                                                                                                                                                           // 22 elements, 0x60 bytes (sizeof)
          {
              union                                                                                                                                                                                                                        // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         union _SLIST_HEADER ListHead;                                                                                                                                                                                            // 4 elements, 0x10 bytes (sizeof)
/*0x000*/         struct _SINGLE_LIST_ENTRY SingleListHead;                                                                                                                                                                                // 1 elements, 0x8 bytes (sizeof)
              };
/*0x010*/     UINT16       Depth;
/*0x012*/     UINT16       MaximumDepth;
/*0x014*/     ULONG32      TotalAllocates;
              union                                                                                                                                                                                                                        // 2 elements, 0x4 bytes (sizeof)
              {
/*0x018*/         ULONG32      AllocateMisses;
/*0x018*/         ULONG32      AllocateHits;
              };
/*0x01C*/     ULONG32      TotalFrees;
              union                                                                                                                                                                                                                        // 2 elements, 0x4 bytes (sizeof)
              {
/*0x020*/         ULONG32      FreeMisses;
/*0x020*/         ULONG32      FreeHits;
              };
/*0x024*/     enum _POOL_TYPE Type;
/*0x028*/     ULONG32      Tag;
/*0x02C*/     ULONG32      Size;
              union                                                                                                                                                                                                                        // 2 elements, 0x8 bytes (sizeof)
              {
/*0x030*/         FUNCT_00B1_0731_AllocateEx* AllocateEx;
/*0x030*/         FUNCT_00B1_073B_Allocate* Allocate;
              };
              union                                                                                                                                                                                                                        // 2 elements, 0x8 bytes (sizeof)
              {
/*0x038*/         FUNCT_00AE_0740_FreeEx* FreeEx;
/*0x038*/         FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* Free;
              };
/*0x040*/     struct _LIST_ENTRY ListEntry;                                                                                                                                                                                                // 2 elements, 0x10 bytes (sizeof)
/*0x050*/     ULONG32      LastTotalAllocates;
              union                                                                                                                                                                                                                        // 2 elements, 0x4 bytes (sizeof)
              {
/*0x054*/         ULONG32      LastAllocateMisses;
/*0x054*/         ULONG32      LastAllocateHits;
              };
/*0x058*/     ULONG32      Future[2];
          }GENERAL_LOOKASIDE_POOL, *PGENERAL_LOOKASIDE_POOL;

          typedef struct _LOOKASIDE_LIST_EX     // 1 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _GENERAL_LOOKASIDE_POOL L; // 22 elements, 0x60 bytes (sizeof)
          }LOOKASIDE_LIST_EX, *PLOOKASIDE_LIST_EX;


          typedef struct _NPAGED_LOOKASIDE_LIST // 1 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     struct _GENERAL_LOOKASIDE L;      // 22 elements, 0x80 bytes (sizeof)
          }NPAGED_LOOKASIDE_LIST, *PNPAGED_LOOKASIDE_LIST;

          typedef struct _OWNER_ENTRY                     // 5 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       OwnerThread;
              union                                       // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                                  // 3 elements, 0x4 bytes (sizeof)
                  {
/*0x008*/             ULONG32      IoPriorityBoosted : 1; // 0 BitPosition
/*0x008*/             ULONG32      OwnerReferenced : 1;   // 1 BitPosition
/*0x008*/             ULONG32      OwnerCount : 30;       // 2 BitPosition
                  };
/*0x008*/         ULONG32      TableSize;
              };
          }OWNER_ENTRY, *POWNER_ENTRY;

          typedef struct _ENODE                                  // 8 elements, 0x280 bytes (sizeof)
          {
/*0x000*/     struct _KNODE Ncb;                                 // 17 elements, 0xC0 bytes (sizeof)
/*0x0C0*/     struct _EX_WORK_QUEUE ExWorkerQueues[5];
/*0x250*/     struct _KEVENT ExpThreadSetManagerEvent;           // 1 elements, 0x18 bytes (sizeof)
/*0x268*/     struct _ETHREAD* ExpWorkerThreadBalanceManagerPtr;
/*0x270*/     ULONG32      ExpWorkerSeed;
              union                                              // 2 elements, 0xC bytes (sizeof)
              {
                  struct                                         // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x274*/             ULONG32      ExWorkerFullInit : 1;         // 0 BitPosition
/*0x274*/             ULONG32      ExWorkerStructInit : 1;       // 1 BitPosition
                  };
/*0x274*/         ULONG32      ExWorkerFlags;
              };
          }ENODE, *PENODE;

          typedef struct _ERESOURCE                   // 17 elements, 0x68 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY SystemResourcesList; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _OWNER_ENTRY* OwnerTable;
/*0x018*/     INT16        ActiveCount;
              union                                   // 2 elements, 0x6 bytes (sizeof)
              {
/*0x01A*/         UINT16       Flag;
                  struct                              // 2 elements, 0x6 bytes (sizeof)
                  {
/*0x01A*/             UINT8        ReservedLowFlags;
/*0x01B*/             UINT8        WaiterPriority;
/*0x01C*/             UINT8        _PADDING0_[0x4];
                  };
              };
/*0x020*/     struct _KSEMAPHORE* SharedWaiters;
/*0x028*/     struct _KEVENT* ExclusiveWaiters;
/*0x030*/     struct _OWNER_ENTRY OwnerEntry;         // 5 elements, 0x10 bytes (sizeof)
/*0x040*/     ULONG32      ActiveEntries;
/*0x044*/     ULONG32      ContentionCount;
/*0x048*/     ULONG32      NumberOfSharedWaiters;
/*0x04C*/     ULONG32      NumberOfExclusiveWaiters;
/*0x050*/     VOID*        Reserved2;
              union                                   // 2 elements, 0x8 bytes (sizeof)
              {
/*0x058*/         VOID*        Address;
/*0x058*/         UINT64       CreatorBackTraceIndex;
              };
/*0x060*/     UINT64       SpinLock;
          }ERESOURCE, *PERESOURCE;

          typedef struct _ETIMER                        // 19 elements, 0x138 bytes (sizeof)
          {
/*0x000*/     struct _KTIMER KeTimer;                   // 6 elements, 0x40 bytes (sizeof)
/*0x040*/     UINT64       Lock;
/*0x048*/     struct _KAPC TimerApc;                    // 17 elements, 0x58 bytes (sizeof)
/*0x0A0*/     struct _KDPC TimerDpc;                    // 9 elements, 0x40 bytes (sizeof)
/*0x0E0*/     struct _LIST_ENTRY ActiveTimerListEntry;  // 2 elements, 0x10 bytes (sizeof)
/*0x0F0*/     ULONG32      Period;
              union                                     // 2 elements, 0x1 bytes (sizeof)
              {
/*0x0F4*/         CHAR         TimerFlags;
                  struct                                // 4 elements, 0x1 bytes (sizeof)
                  {
/*0x0F4*/             UINT8        ApcAssociated : 1;   // 0 BitPosition
/*0x0F4*/             UINT8        FlushDpcs : 1;       // 1 BitPosition
/*0x0F4*/             UINT8        Paused : 1;          // 2 BitPosition
/*0x0F4*/             UINT8        Spare1 : 5;          // 3 BitPosition
                  };
              };
/*0x0F5*/     UINT8        DueTimeType;
/*0x0F6*/     UINT16       Spare2;
/*0x0F8*/     struct _DIAGNOSTIC_CONTEXT* WakeReason;
/*0x100*/     struct _LIST_ENTRY WakeTimerListEntry;    // 2 elements, 0x10 bytes (sizeof)
/*0x110*/     VOID*        VirtualizedTimerCookie;
/*0x118*/     struct _LIST_ENTRY VirtualizedTimerLinks; // 2 elements, 0x10 bytes (sizeof)
/*0x128*/     UINT64       DueTime;
/*0x130*/     ULONG32      CoalescingWindow;
/*0x134*/     UINT8        _PADDING0_[0x4];
          }ETIMER, *PETIMER;

