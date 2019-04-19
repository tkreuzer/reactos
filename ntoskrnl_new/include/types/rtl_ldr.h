
          typedef struct _LDR_DATA_TABLE_ENTRY                         // 52 elements, 0x108 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY InLoadOrderLinks;                     // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY InMemoryOrderLinks;                   // 2 elements, 0x10 bytes (sizeof)
              union                                                    // 2 elements, 0x10 bytes (sizeof)
              {
/*0x020*/         struct _LIST_ENTRY InInitializationOrderLinks;       // 2 elements, 0x10 bytes (sizeof)
/*0x020*/         struct _LIST_ENTRY InProgressLinks;                  // 2 elements, 0x10 bytes (sizeof)
              };
/*0x030*/     VOID*        DllBase;
/*0x038*/     VOID*        EntryPoint;
/*0x040*/     ULONG32      SizeOfImage;
/*0x044*/     UINT8        _PADDING0_[0x4];
/*0x048*/     struct _UNICODE_STRING FullDllName;                      // 3 elements, 0x10 bytes (sizeof)
/*0x058*/     struct _UNICODE_STRING BaseDllName;                      // 3 elements, 0x10 bytes (sizeof)
              union                                                    // 3 elements, 0x4 bytes (sizeof)
              {
/*0x068*/         UINT8        FlagGroup[4];
/*0x068*/         ULONG32      Flags;
                  struct                                               // 26 elements, 0x4 bytes (sizeof)
                  {
/*0x068*/             ULONG32      PackagedBinary : 1;                 // 0 BitPosition
/*0x068*/             ULONG32      MarkedForRemoval : 1;               // 1 BitPosition
/*0x068*/             ULONG32      ImageDll : 1;                       // 2 BitPosition
/*0x068*/             ULONG32      LoadNotificationsSent : 1;          // 3 BitPosition
/*0x068*/             ULONG32      TelemetryEntryProcessed : 1;        // 4 BitPosition
/*0x068*/             ULONG32      ProcessStaticImport : 1;            // 5 BitPosition
/*0x068*/             ULONG32      InLegacyLists : 1;                  // 6 BitPosition
/*0x068*/             ULONG32      InIndexes : 1;                      // 7 BitPosition
/*0x068*/             ULONG32      ShimDll : 1;                        // 8 BitPosition
/*0x068*/             ULONG32      InExceptionTable : 1;               // 9 BitPosition
/*0x068*/             ULONG32      ReservedFlags1 : 2;                 // 10 BitPosition
/*0x068*/             ULONG32      LoadInProgress : 1;                 // 12 BitPosition
/*0x068*/             ULONG32      ReservedFlags2 : 1;                 // 13 BitPosition
/*0x068*/             ULONG32      EntryProcessed : 1;                 // 14 BitPosition
/*0x068*/             ULONG32      ReservedFlags3 : 3;                 // 15 BitPosition
/*0x068*/             ULONG32      DontCallForThreads : 1;             // 18 BitPosition
/*0x068*/             ULONG32      ProcessAttachCalled : 1;            // 19 BitPosition
/*0x068*/             ULONG32      ProcessAttachFailed : 1;            // 20 BitPosition
/*0x068*/             ULONG32      CorDeferredValidate : 1;            // 21 BitPosition
/*0x068*/             ULONG32      CorImage : 1;                       // 22 BitPosition
/*0x068*/             ULONG32      DontRelocate : 1;                   // 23 BitPosition
/*0x068*/             ULONG32      CorILOnly : 1;                      // 24 BitPosition
/*0x068*/             ULONG32      ReservedFlags5 : 3;                 // 25 BitPosition
/*0x068*/             ULONG32      Redirected : 1;                     // 28 BitPosition
/*0x068*/             ULONG32      ReservedFlags6 : 2;                 // 29 BitPosition
/*0x068*/             ULONG32      CompatDatabaseProcessed : 1;        // 31 BitPosition
                  };
              };
/*0x06C*/     UINT16       ObsoleteLoadCount;
/*0x06E*/     UINT16       TlsIndex;
/*0x070*/     struct _LIST_ENTRY HashLinks;                            // 2 elements, 0x10 bytes (sizeof)
/*0x080*/     ULONG32      TimeDateStamp;
/*0x084*/     UINT8        _PADDING1_[0x4];
/*0x088*/     struct _ACTIVATION_CONTEXT* EntryPointActivationContext;
/*0x090*/     VOID*        PatchInformation;
/*0x098*/     struct _LDR_DDAG_NODE* DdagNode;
/*0x0A0*/     struct _LIST_ENTRY NodeModuleLink;                       // 2 elements, 0x10 bytes (sizeof)
/*0x0B0*/     struct _LDRP_DLL_SNAP_CONTEXT* SnapContext;
/*0x0B8*/     VOID*        SwitchBackContext;
/*0x0C0*/     struct _RTL_BALANCED_NODE BaseAddressIndexNode;          // 6 elements, 0x18 bytes (sizeof)
/*0x0D8*/     struct _RTL_BALANCED_NODE MappingInfoIndexNode;          // 6 elements, 0x18 bytes (sizeof)
/*0x0F0*/     UINT64       OriginalBase;
/*0x0F8*/     union _LARGE_INTEGER LoadTime;                           // 4 elements, 0x8 bytes (sizeof)
/*0x100*/     ULONG32      BaseNameHashValue;
/*0x104*/     UINT8        _PADDING2_[0x4];
          }LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

          typedef struct _LDR_DDAG_NODE                       // 12 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Modules;                     // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LDR_SERVICE_TAG_RECORD* ServiceTagList;
/*0x018*/     ULONG32      LoadCount;
/*0x01C*/     ULONG32      ReferenceCount;
/*0x020*/     ULONG32      DependencyCount;
/*0x024*/     UINT8        _PADDING0_[0x4];
              union                                           // 2 elements, 0x8 bytes (sizeof)
              {
/*0x028*/         struct _LDRP_CSLIST Dependencies;           // 1 elements, 0x8 bytes (sizeof)
/*0x028*/         struct _SINGLE_LIST_ENTRY RemovalLink;      // 1 elements, 0x8 bytes (sizeof)
              };
/*0x030*/     struct _LDRP_CSLIST IncomingDependencies;       // 1 elements, 0x8 bytes (sizeof)
/*0x038*/     enum _LDR_DDAG_STATE State;
/*0x03C*/     UINT8        _PADDING1_[0x4];
/*0x040*/     struct _SINGLE_LIST_ENTRY CondenseLink;         // 1 elements, 0x8 bytes (sizeof)
/*0x048*/     ULONG32      PreorderNumber;
/*0x04C*/     ULONG32      LowestLink;
          }LDR_DDAG_NODE, *PLDR_DDAG_NODE;

          typedef struct _LDR_SERVICE_TAG_RECORD    // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _LDR_SERVICE_TAG_RECORD* Next;
/*0x008*/     ULONG32      ServiceTag;
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }LDR_SERVICE_TAG_RECORD, *PLDR_SERVICE_TAG_RECORD;

          typedef struct _LDRP_CSLIST          // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _SINGLE_LIST_ENTRY* Tail;
          }LDRP_CSLIST, *PLDRP_CSLIST;

typedef struct _LDRP_DLL_SNAP_CONTEXT // 0 elements, 0x0 bytes (sizeof)
{
}LDRP_DLL_SNAP_CONTEXT, *PLDRP_DLL_SNAP_CONTEXT;

          typedef struct _LEARNING_MODE_DATA      // 3 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Settings;
/*0x004*/     UINT8        Enabled;
/*0x005*/     UINT8        PermissiveModeEnabled;
/*0x006*/     UINT8        _PADDING0_[0x2];
          }LEARNING_MODE_DATA, *PLEARNING_MODE_DATA;

typedef enum _LDR_DDAG_STATE  // 15 elements, 0x4 bytes
{
    LdrModulesMerged                 = -5 /*0xFB*/,
    LdrModulesInitError              = -4 /*0xFC*/,
    LdrModulesSnapError              = -3 /*0xFD*/,
    LdrModulesUnloaded               = -2 /*0xFE*/,
    LdrModulesUnloading              = -1 /*0xFF*/,
    LdrModulesPlaceHolder            = 0 /*0x0*/,
    LdrModulesMapping                = 1 /*0x1*/,
    LdrModulesMapped                 = 2 /*0x2*/,
    LdrModulesWaitingForDependencies = 3 /*0x3*/,
    LdrModulesSnapping               = 4 /*0x4*/,
    LdrModulesSnapped                = 5 /*0x5*/,
    LdrModulesCondensed              = 6 /*0x6*/,
    LdrModulesReadyToInit            = 7 /*0x7*/,
    LdrModulesInitializing           = 8 /*0x8*/,
    LdrModulesReadyToRun             = 9 /*0x9*/
}LDR_DDAG_STATE, *PLDR_DDAG_STATE;

