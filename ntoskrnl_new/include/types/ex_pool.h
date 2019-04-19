
          typedef struct _POOL_BLOCK_HEAD // 2 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _POOL_HEADER Header; // 9 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY List;    // 2 elements, 0x10 bytes (sizeof)
          }POOL_BLOCK_HEAD, *PPOOL_BLOCK_HEAD;

          typedef struct _POOL_DESCRIPTOR              // 13 elements, 0x1140 bytes (sizeof)
          {
/*0x000*/     enum _POOL_TYPE PoolType;
/*0x004*/     UINT8        _PADDING0_[0x4];
              union                                    // 2 elements, 0x38 bytes (sizeof)
              {
/*0x008*/         struct _FAST_MUTEX PagedLock;        // 5 elements, 0x38 bytes (sizeof)
/*0x008*/         UINT64       NonPagedLock;
              };
/*0x040*/     LONG32       RunningAllocs;
/*0x044*/     LONG32       RunningDeAllocs;
/*0x048*/     LONG32       TotalBigPages;
/*0x04C*/     LONG32       ThreadsProcessingDeferrals;
/*0x050*/     UINT64       TotalBytes;
/*0x058*/     UINT8        _PADDING1_[0x28];
/*0x080*/     ULONG32      PoolIndex;
/*0x084*/     UINT8        _PADDING2_[0x3C];
/*0x0C0*/     LONG32       TotalPages;
/*0x0C4*/     UINT8        _PADDING3_[0x3C];
/*0x100*/     VOID**       PendingFrees;
/*0x108*/     LONG32       PendingFreeDepth;
/*0x10C*/     UINT8        _PADDING4_[0x34];
/*0x140*/     struct _LIST_ENTRY ListHeads[256];
          }POOL_DESCRIPTOR, *PPOOL_DESCRIPTOR;

          typedef struct _POOL_HACKER     // 2 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _POOL_HEADER Header; // 9 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Contents[8];
          }POOL_HACKER, *PPOOL_HACKER;

          typedef struct _POOL_HEADER                       // 9 elements, 0x10 bytes (sizeof)
          {
              union                                         // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                    // 4 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             ULONG32      PreviousSize : 8;        // 0 BitPosition
/*0x000*/             ULONG32      PoolIndex : 8;           // 8 BitPosition
/*0x000*/             ULONG32      BlockSize : 8;           // 16 BitPosition
/*0x000*/             ULONG32      PoolType : 8;            // 24 BitPosition
                  };
/*0x000*/         ULONG32      Ulong1;
              };
/*0x004*/     ULONG32      PoolTag;
              union                                         // 2 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         struct _EPROCESS* ProcessBilled;
                  struct                                    // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             UINT16       AllocatorBackTraceIndex;
/*0x00A*/             UINT16       PoolTagHash;
/*0x00C*/             UINT8        _PADDING0_[0x4];
                  };
              };
          }POOL_HEADER, *PPOOL_HEADER;

          typedef struct _POOL_TRACKER_BIG_PAGES // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     VOID*        Va;
/*0x008*/     ULONG32      Key;
/*0x00C*/     ULONG32      PoolType;
/*0x010*/     UINT64       NumberOfBytes;
          }POOL_TRACKER_BIG_PAGES, *PPOOL_TRACKER_BIG_PAGES;

          typedef struct _POOL_TRACKER_TABLE // 7 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     LONG32       Key;
/*0x004*/     ULONG32      NonPagedAllocs;
/*0x008*/     ULONG32      NonPagedFrees;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     UINT64       NonPagedBytes;
/*0x018*/     ULONG32      PagedAllocs;
/*0x01C*/     ULONG32      PagedFrees;
/*0x020*/     UINT64       PagedBytes;
          }POOL_TRACKER_TABLE, *PPOOL_TRACKER_TABLE;

typedef enum _EX_POOL_PRIORITY  // 9 elements, 0x4 bytes
{
    LowPoolPriority                       = 0 /*0x0*/,
    LowPoolPrioritySpecialPoolOverrun     = 8 /*0x8*/,
    LowPoolPrioritySpecialPoolUnderrun    = 9 /*0x9*/,
    NormalPoolPriority                    = 16 /*0x10*/,
    NormalPoolPrioritySpecialPoolOverrun  = 24 /*0x18*/,
    NormalPoolPrioritySpecialPoolUnderrun = 25 /*0x19*/,
    HighPoolPriority                      = 32 /*0x20*/,
    HighPoolPrioritySpecialPoolOverrun    = 40 /*0x28*/,
    HighPoolPrioritySpecialPoolUnderrun   = 41 /*0x29*/
}EX_POOL_PRIORITY, *PEX_POOL_PRIORITY;

typedef enum _POOL_TYPE  // 23 elements, 0x4 bytes
{
    NonPagedPool                         = 0 /*0x0*/,
    NonPagedPoolExecute                  = 0 /*0x0*/,
    PagedPool                            = 1 /*0x1*/,
    NonPagedPoolMustSucceed              = 2 /*0x2*/,
    DontUseThisType                      = 3 /*0x3*/,
    NonPagedPoolCacheAligned             = 4 /*0x4*/,
    PagedPoolCacheAligned                = 5 /*0x5*/,
    NonPagedPoolCacheAlignedMustS        = 6 /*0x6*/,
    MaxPoolType                          = 7 /*0x7*/,
    NonPagedPoolBase                     = 0 /*0x0*/,
    NonPagedPoolBaseMustSucceed          = 2 /*0x2*/,
    NonPagedPoolBaseCacheAligned         = 4 /*0x4*/,
    NonPagedPoolBaseCacheAlignedMustS    = 6 /*0x6*/,
    NonPagedPoolSession                  = 32 /*0x20*/,
    PagedPoolSession                     = 33 /*0x21*/,
    NonPagedPoolMustSucceedSession       = 34 /*0x22*/,
    DontUseThisTypeSession               = 35 /*0x23*/,
    NonPagedPoolCacheAlignedSession      = 36 /*0x24*/,
    PagedPoolCacheAlignedSession         = 37 /*0x25*/,
    NonPagedPoolCacheAlignedMustSSession = 38 /*0x26*/,
    NonPagedPoolNx                       = 512 /*0x200*/,
    NonPagedPoolNxCacheAligned           = 516 /*0x204*/,
    NonPagedPoolSessionNx                = 544 /*0x220*/
}POOL_TYPE, *PPOOL_TYPE;

typedef enum _PP_NPAGED_LOOKASIDE_NUMBER  // 10 elements, 0x4 bytes
{
    LookasideSmallIrpList      = 0 /*0x0*/,
    LookasideMediumIrpList     = 1 /*0x1*/,
    LookasideLargeIrpList      = 2 /*0x2*/,
    LookasideMdlList           = 3 /*0x3*/,
    LookasideCreateInfoList    = 4 /*0x4*/,
    LookasideNameBufferList    = 5 /*0x5*/,
    LookasideTwilightList      = 6 /*0x6*/,
    LookasideCompletionList    = 7 /*0x7*/,
    LookasideScratchBufferList = 8 /*0x8*/,
    LookasideMaximumList       = 9 /*0x9*/
}PP_NPAGED_LOOKASIDE_NUMBER, *PPP_NPAGED_LOOKASIDE_NUMBER;

          typedef struct _PAGED_LOOKASIDE_LIST // 1 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     struct _GENERAL_LOOKASIDE L;     // 22 elements, 0x80 bytes (sizeof)
          }PAGED_LOOKASIDE_LIST, *PPAGED_LOOKASIDE_LIST;

          typedef struct _PP_LOOKASIDE_LIST // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _GENERAL_LOOKASIDE* P;
/*0x008*/     struct _GENERAL_LOOKASIDE* L;
          }PP_LOOKASIDE_LIST, *PPP_LOOKASIDE_LIST;

