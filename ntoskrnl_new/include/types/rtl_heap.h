
          typedef struct _HEAP                                 // 56 elements, 0x298 bytes (sizeof)
          {
/*0x000*/     struct _HEAP_ENTRY Entry;                        // 23 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      SegmentSignature;
/*0x014*/     ULONG32      SegmentFlags;
/*0x018*/     struct _LIST_ENTRY SegmentListEntry;             // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _HEAP* Heap;
/*0x030*/     VOID*        BaseAddress;
/*0x038*/     ULONG32      NumberOfPages;
/*0x03C*/     UINT8        _PADDING0_[0x4];
/*0x040*/     struct _HEAP_ENTRY* FirstEntry;
/*0x048*/     struct _HEAP_ENTRY* LastValidEntry;
/*0x050*/     ULONG32      NumberOfUnCommittedPages;
/*0x054*/     ULONG32      NumberOfUnCommittedRanges;
/*0x058*/     UINT16       SegmentAllocatorBackTraceIndex;
/*0x05A*/     UINT16       Reserved;
/*0x05C*/     UINT8        _PADDING1_[0x4];
/*0x060*/     struct _LIST_ENTRY UCRSegmentList;               // 2 elements, 0x10 bytes (sizeof)
/*0x070*/     ULONG32      Flags;
/*0x074*/     ULONG32      ForceFlags;
/*0x078*/     ULONG32      CompatibilityFlags;
/*0x07C*/     ULONG32      EncodeFlagMask;
/*0x080*/     struct _HEAP_ENTRY Encoding;                     // 23 elements, 0x10 bytes (sizeof)
/*0x090*/     ULONG32      Interceptor;
/*0x094*/     ULONG32      VirtualMemoryThreshold;
/*0x098*/     ULONG32      Signature;
/*0x09C*/     UINT8        _PADDING2_[0x4];
/*0x0A0*/     UINT64       SegmentReserve;
/*0x0A8*/     UINT64       SegmentCommit;
/*0x0B0*/     UINT64       DeCommitFreeBlockThreshold;
/*0x0B8*/     UINT64       DeCommitTotalFreeThreshold;
/*0x0C0*/     UINT64       TotalFreeSize;
/*0x0C8*/     UINT64       MaximumAllocationSize;
/*0x0D0*/     UINT16       ProcessHeapsListIndex;
/*0x0D2*/     UINT16       HeaderValidateLength;
/*0x0D4*/     UINT8        _PADDING3_[0x4];
/*0x0D8*/     VOID*        HeaderValidateCopy;
/*0x0E0*/     UINT16       NextAvailableTagIndex;
/*0x0E2*/     UINT16       MaximumTagIndex;
/*0x0E4*/     UINT8        _PADDING4_[0x4];
/*0x0E8*/     struct _HEAP_TAG_ENTRY* TagEntries;
/*0x0F0*/     struct _LIST_ENTRY UCRList;                      // 2 elements, 0x10 bytes (sizeof)
/*0x100*/     UINT64       AlignRound;
/*0x108*/     UINT64       AlignMask;
/*0x110*/     struct _LIST_ENTRY VirtualAllocdBlocks;          // 2 elements, 0x10 bytes (sizeof)
/*0x120*/     struct _LIST_ENTRY SegmentList;                  // 2 elements, 0x10 bytes (sizeof)
/*0x130*/     UINT16       AllocatorBackTraceIndex;
/*0x132*/     UINT8        _PADDING5_[0x2];
/*0x134*/     ULONG32      NonDedicatedListLength;
/*0x138*/     VOID*        BlocksIndex;
/*0x140*/     VOID*        UCRIndex;
/*0x148*/     struct _HEAP_PSEUDO_TAG_ENTRY* PseudoTagEntries;
/*0x150*/     struct _LIST_ENTRY FreeLists;                    // 2 elements, 0x10 bytes (sizeof)
/*0x160*/     struct _HEAP_LOCK* LockVariable;
/*0x168*/     FUNCT_0064_1A55_CommitRoutine* CommitRoutine;
/*0x170*/     VOID*        FrontEndHeap;
/*0x178*/     UINT16       FrontHeapLockCount;
/*0x17A*/     UINT8        FrontEndHeapType;
/*0x17B*/     UINT8        RequestedFrontEndHeapType;
/*0x17C*/     UINT8        _PADDING6_[0x4];
/*0x180*/     UINT16*      FrontEndHeapUsageData;
/*0x188*/     UINT16       FrontEndHeapMaximumIndex;
/*0x18A*/     UINT8        FrontEndHeapStatusBitmap[129];
/*0x20B*/     UINT8        _PADDING7_[0x5];
/*0x210*/     struct _HEAP_COUNTERS Counters;                  // 23 elements, 0x78 bytes (sizeof)
/*0x288*/     struct _HEAP_TUNING_PARAMETERS TuningParameters; // 2 elements, 0x10 bytes (sizeof)
          }HEAP, *PHEAP;

          typedef struct _HEAP_COUNTERS              // 23 elements, 0x78 bytes (sizeof)
          {
/*0x000*/     UINT64       TotalMemoryReserved;
/*0x008*/     UINT64       TotalMemoryCommitted;
/*0x010*/     UINT64       TotalMemoryLargeUCR;
/*0x018*/     UINT64       TotalSizeInVirtualBlocks;
/*0x020*/     ULONG32      TotalSegments;
/*0x024*/     ULONG32      TotalUCRs;
/*0x028*/     ULONG32      CommittOps;
/*0x02C*/     ULONG32      DeCommitOps;
/*0x030*/     ULONG32      LockAcquires;
/*0x034*/     ULONG32      LockCollisions;
/*0x038*/     ULONG32      CommitRate;
/*0x03C*/     ULONG32      DecommittRate;
/*0x040*/     ULONG32      CommitFailures;
/*0x044*/     ULONG32      InBlockCommitFailures;
/*0x048*/     ULONG32      PollIntervalCounter;
/*0x04C*/     ULONG32      DecommitsSinceLastCheck;
/*0x050*/     ULONG32      HeapPollInterval;
/*0x054*/     ULONG32      AllocAndFreeOps;
/*0x058*/     ULONG32      AllocationIndicesActive;
/*0x05C*/     ULONG32      InBlockDeccommits;
/*0x060*/     UINT64       InBlockDeccomitSize;
/*0x068*/     UINT64       HighWatermarkSize;
/*0x070*/     UINT64       LastPolledSize;
          }HEAP_COUNTERS, *PHEAP_COUNTERS;

          typedef struct _HEAP_ENTRY                          // 23 elements, 0x10 bytes (sizeof)
          {
              union                                           // 3 elements, 0x10 bytes (sizeof)
              {
                  struct                                      // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             VOID*        PreviousBlockPrivateData;
                      union                                   // 2 elements, 0x8 bytes (sizeof)
                      {
                          struct                              // 6 elements, 0x8 bytes (sizeof)
                          {
/*0x008*/                     UINT16       Size;
/*0x00A*/                     UINT8        Flags;
/*0x00B*/                     UINT8        SmallTagIndex;
/*0x00C*/                     UINT16       PreviousSize;
                              union                           // 2 elements, 0x1 bytes (sizeof)
                              {
/*0x00E*/                         UINT8        SegmentOffset;
/*0x00E*/                         UINT8        LFHFlags;
                              };
/*0x00F*/                     UINT8        UnusedBytes;
                          };
/*0x008*/                 UINT64       CompactHeader;
                      };
                  };
                  struct                                      // 5 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             VOID*        Reserved;
                      union                                   // 2 elements, 0x4 bytes (sizeof)
                      {
                          struct                              // 2 elements, 0x4 bytes (sizeof)
                          {
/*0x008*/                     UINT16       FunctionIndex;
/*0x00A*/                     UINT16       ContextValue;
                          };
/*0x008*/                 ULONG32      InterceptorValue;
                      };
/*0x00C*/             UINT16       UnusedBytesLength;
/*0x00E*/             UINT8        EntryOffset;
/*0x00F*/             UINT8        ExtendedBlockSignature;
                  };
                  struct                                      // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             VOID*        ReservedForAlignment;
                      union                                   // 2 elements, 0x8 bytes (sizeof)
                      {
                          struct                              // 2 elements, 0x8 bytes (sizeof)
                          {
/*0x008*/                     ULONG32      Code1;
                              union                           // 2 elements, 0x4 bytes (sizeof)
                              {
                                  struct                      // 3 elements, 0x4 bytes (sizeof)
                                  {
/*0x00C*/                             UINT16       Code2;
/*0x00E*/                             UINT8        Code3;
/*0x00F*/                             UINT8        Code4;
                                  };
/*0x00C*/                         ULONG32      Code234;
                              };
                          };
/*0x008*/                 UINT64       AgregateCode;
                      };
                  };
              };
          }HEAP_ENTRY, *PHEAP_ENTRY;

          typedef struct _HEAP_ENTRY_EXTRA                  // 5 elements, 0x10 bytes (sizeof)
          {
              union                                         // 2 elements, 0x10 bytes (sizeof)
              {
                  struct                                    // 3 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             UINT16       AllocatorBackTraceIndex;
/*0x002*/             UINT16       TagIndex;
/*0x004*/             UINT8        _PADDING0_[0x4];
/*0x008*/             UINT64       Settable;
                  };
                  struct                                    // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             UINT64       ZeroInit;
/*0x008*/             UINT64       ZeroInit1;
                  };
              };
          }HEAP_ENTRY_EXTRA, *PHEAP_ENTRY_EXTRA;

          typedef struct _HEAP_FREE_ENTRY                     // 24 elements, 0x20 bytes (sizeof)
          {
              union                                           // 3 elements, 0x10 bytes (sizeof)
              {
                  struct                                      // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             VOID*        PreviousBlockPrivateData;
                      union                                   // 2 elements, 0x8 bytes (sizeof)
                      {
                          struct                              // 6 elements, 0x8 bytes (sizeof)
                          {
/*0x008*/                     UINT16       Size;
/*0x00A*/                     UINT8        Flags;
/*0x00B*/                     UINT8        SmallTagIndex;
/*0x00C*/                     UINT16       PreviousSize;
                              union                           // 2 elements, 0x1 bytes (sizeof)
                              {
/*0x00E*/                         UINT8        SegmentOffset;
/*0x00E*/                         UINT8        LFHFlags;
                              };
/*0x00F*/                     UINT8        UnusedBytes;
                          };
/*0x008*/                 UINT64       CompactHeader;
                      };
                  };
                  struct                                      // 5 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             VOID*        Reserved;
                      union                                   // 2 elements, 0x4 bytes (sizeof)
                      {
                          struct                              // 2 elements, 0x4 bytes (sizeof)
                          {
/*0x008*/                     UINT16       FunctionIndex;
/*0x00A*/                     UINT16       ContextValue;
                          };
/*0x008*/                 ULONG32      InterceptorValue;
                      };
/*0x00C*/             UINT16       UnusedBytesLength;
/*0x00E*/             UINT8        EntryOffset;
/*0x00F*/             UINT8        ExtendedBlockSignature;
                  };
                  struct                                      // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x000*/             VOID*        ReservedForAlignment;
                      union                                   // 2 elements, 0x8 bytes (sizeof)
                      {
                          struct                              // 2 elements, 0x8 bytes (sizeof)
                          {
/*0x008*/                     ULONG32      Code1;
                              union                           // 2 elements, 0x4 bytes (sizeof)
                              {
                                  struct                      // 3 elements, 0x4 bytes (sizeof)
                                  {
/*0x00C*/                             UINT16       Code2;
/*0x00E*/                             UINT8        Code3;
/*0x00F*/                             UINT8        Code4;
                                  };
/*0x00C*/                         ULONG32      Code234;
                              };
                          };
/*0x008*/                 UINT64       AgregateCode;
                      };
                  };
              };
/*0x010*/     struct _LIST_ENTRY FreeList;                    // 2 elements, 0x10 bytes (sizeof)
          }HEAP_FREE_ENTRY, *PHEAP_FREE_ENTRY;

          typedef struct _HEAP_FREE_ENTRY_EXTRA // 2 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     UINT16       TagIndex;
/*0x002*/     UINT16       FreeBackTraceIndex;
          }HEAP_FREE_ENTRY_EXTRA, *PHEAP_FREE_ENTRY_EXTRA;

          typedef struct _HEAP_LIST_LOOKUP              // 9 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _HEAP_LIST_LOOKUP* ExtendedLookup;
/*0x008*/     ULONG32      ArraySize;
/*0x00C*/     ULONG32      ExtraItem;
/*0x010*/     ULONG32      ItemCount;
/*0x014*/     ULONG32      OutOfRangeItems;
/*0x018*/     ULONG32      BaseIndex;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     struct _LIST_ENTRY* ListHead;
/*0x028*/     ULONG32*     ListsInUseUlong;
/*0x030*/     struct _LIST_ENTRY** ListHints;
          }HEAP_LIST_LOOKUP, *PHEAP_LIST_LOOKUP;

          typedef struct _HEAP_LOCK                             // 1 elements, 0x68 bytes (sizeof)
          {
              union                                             // 2 elements, 0x68 bytes (sizeof)
              {
/*0x000*/         struct _RTL_CRITICAL_SECTION CriticalSection; // 6 elements, 0x28 bytes (sizeof)
/*0x000*/         struct _ERESOURCE Resource;                   // 17 elements, 0x68 bytes (sizeof)
              }Lock;
          }HEAP_LOCK, *PHEAP_LOCK;

          typedef struct _HEAP_LOOKASIDE       // 10 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     union _SLIST_HEADER ListHead;    // 4 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT16       Depth;
/*0x012*/     UINT16       MaximumDepth;
/*0x014*/     ULONG32      TotalAllocates;
/*0x018*/     ULONG32      AllocateMisses;
/*0x01C*/     ULONG32      TotalFrees;
/*0x020*/     ULONG32      FreeMisses;
/*0x024*/     ULONG32      LastTotalAllocates;
/*0x028*/     ULONG32      LastAllocateMisses;
/*0x02C*/     ULONG32      Counters[2];
/*0x034*/     UINT8        _PADDING0_[0xC];
          }HEAP_LOOKASIDE, *PHEAP_LOOKASIDE;

          typedef struct _HEAP_PSEUDO_TAG_ENTRY // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Allocs;
/*0x004*/     ULONG32      Frees;
/*0x008*/     UINT64       Size;
          }HEAP_PSEUDO_TAG_ENTRY, *PHEAP_PSEUDO_TAG_ENTRY;

          typedef struct _HEAP_SEGMENT                     // 14 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     struct _HEAP_ENTRY Entry;                    // 23 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      SegmentSignature;
/*0x014*/     ULONG32      SegmentFlags;
/*0x018*/     struct _LIST_ENTRY SegmentListEntry;         // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _HEAP* Heap;
/*0x030*/     VOID*        BaseAddress;
/*0x038*/     ULONG32      NumberOfPages;
/*0x03C*/     UINT8        _PADDING0_[0x4];
/*0x040*/     struct _HEAP_ENTRY* FirstEntry;
/*0x048*/     struct _HEAP_ENTRY* LastValidEntry;
/*0x050*/     ULONG32      NumberOfUnCommittedPages;
/*0x054*/     ULONG32      NumberOfUnCommittedRanges;
/*0x058*/     UINT16       SegmentAllocatorBackTraceIndex;
/*0x05A*/     UINT16       Reserved;
/*0x05C*/     UINT8        _PADDING1_[0x4];
/*0x060*/     struct _LIST_ENTRY UCRSegmentList;           // 2 elements, 0x10 bytes (sizeof)
          }HEAP_SEGMENT, *PHEAP_SEGMENT;

          typedef struct _HEAP_STOP_ON_TAG      // 3 elements, 0x4 bytes (sizeof)
          {
              union                             // 2 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      HeapAndTagIndex;
                  struct                        // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             UINT16       TagIndex;
/*0x002*/             UINT16       HeapIndex;
                  };
              };
          }HEAP_STOP_ON_TAG, *PHEAP_STOP_ON_TAG;

          typedef struct _HEAP_STOP_ON_VALUES      // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     UINT64       AllocAddress;
/*0x008*/     struct _HEAP_STOP_ON_TAG AllocTag;   // 3 elements, 0x4 bytes (sizeof)
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     UINT64       ReAllocAddress;
/*0x018*/     struct _HEAP_STOP_ON_TAG ReAllocTag; // 3 elements, 0x4 bytes (sizeof)
/*0x01C*/     UINT8        _PADDING1_[0x4];
/*0x020*/     UINT64       FreeAddress;
/*0x028*/     struct _HEAP_STOP_ON_TAG FreeTag;    // 3 elements, 0x4 bytes (sizeof)
/*0x02C*/     UINT8        _PADDING2_[0x4];
          }HEAP_STOP_ON_VALUES, *PHEAP_STOP_ON_VALUES;

          typedef struct _HEAP_TAG_ENTRY          // 6 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      Allocs;
/*0x004*/     ULONG32      Frees;
/*0x008*/     UINT64       Size;
/*0x010*/     UINT16       TagIndex;
/*0x012*/     UINT16       CreatorBackTraceIndex;
/*0x014*/     WCHAR        TagName[24];
/*0x044*/     UINT8        _PADDING0_[0x4];
          }HEAP_TAG_ENTRY, *PHEAP_TAG_ENTRY;

          typedef struct _HEAP_TUNING_PARAMETERS   // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      CommittThresholdShift;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT64       MaxPreCommittThreshold;
          }HEAP_TUNING_PARAMETERS, *PHEAP_TUNING_PARAMETERS;

          typedef struct _HEAP_UCR_DESCRIPTOR  // 4 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;    // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY SegmentEntry; // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     VOID*        Address;
/*0x028*/     UINT64       Size;
          }HEAP_UCR_DESCRIPTOR, *PHEAP_UCR_DESCRIPTOR;

          typedef struct _HEAP_VIRTUAL_ALLOC_ENTRY // 5 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Entry;            // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _HEAP_ENTRY_EXTRA ExtraStuff; // 5 elements, 0x10 bytes (sizeof)
/*0x020*/     UINT64       CommitSize;
/*0x028*/     UINT64       ReserveSize;
/*0x030*/     struct _HEAP_ENTRY BusyBlock;        // 23 elements, 0x10 bytes (sizeof)
          }HEAP_VIRTUAL_ALLOC_ENTRY, *PHEAP_VIRTUAL_ALLOC_ENTRY;

typedef enum _HEAP_FAILURE_TYPE  // 15 elements, 0x4 bytes
{
    heap_failure_internal                    = 0 /*0x0*/,
    heap_failure_unknown                     = 1 /*0x1*/,
    heap_failure_generic                     = 2 /*0x2*/,
    heap_failure_entry_corruption            = 3 /*0x3*/,
    heap_failure_multiple_entries_corruption = 4 /*0x4*/,
    heap_failure_virtual_block_corruption    = 5 /*0x5*/,
    heap_failure_buffer_overrun              = 6 /*0x6*/,
    heap_failure_buffer_underrun             = 7 /*0x7*/,
    heap_failure_block_not_busy              = 8 /*0x8*/,
    heap_failure_invalid_argument            = 9 /*0x9*/,
    heap_failure_usage_after_free            = 10 /*0xA*/,
    heap_failure_cross_heap_operation        = 11 /*0xB*/,
    heap_failure_freelists_corruption        = 12 /*0xC*/,
    heap_failure_listentry_corruption        = 13 /*0xD*/,
    heap_failure_lfh_bitmap_mismatch         = 14 /*0xE*/
}HEAP_FAILURE_TYPE, *PHEAP_FAILURE_TYPE;

