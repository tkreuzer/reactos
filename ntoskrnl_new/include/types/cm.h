
          typedef struct _CELL_DATA                    // 1 elements, 0x50 bytes (sizeof)
          {
              union                                    // 7 elements, 0x50 bytes (sizeof)
              {
/*0x000*/         struct _CM_KEY_NODE KeyNode;         // 22 elements, 0x50 bytes (sizeof)
/*0x000*/         struct _CM_KEY_VALUE KeyValue;       // 8 elements, 0x18 bytes (sizeof)
/*0x000*/         struct _CM_KEY_SECURITY KeySecurity; // 7 elements, 0x28 bytes (sizeof)
/*0x000*/         struct _CM_KEY_INDEX KeyIndex;       // 3 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _CM_BIG_DATA ValueData;       // 3 elements, 0x8 bytes (sizeof)
/*0x000*/         ULONG32      KeyList[1];
/*0x000*/         WCHAR        KeyString[1];
              }u;
          }CELL_DATA, *PCELL_DATA;

          typedef struct _CM_BIG_DATA // 3 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT16       Signature;
/*0x002*/     UINT16       Count;
/*0x004*/     ULONG32      List;
          }CM_BIG_DATA, *PCM_BIG_DATA;

          typedef struct _CM_CACHED_VALUE_INDEX // 2 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     ULONG32      CellIndex;
/*0x004*/     UINT8        _PADDING0_[0x4];
              union                             // 2 elements, 0x50 bytes (sizeof)
              {
/*0x008*/         struct _CELL_DATA CellData;   // 1 elements, 0x50 bytes (sizeof)
/*0x008*/         UINT64       List[1];
              }Data;
          }CM_CACHED_VALUE_INDEX, *PCM_CACHED_VALUE_INDEX;

          typedef struct _CM_CELL_REMAP_BLOCK // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      OldCell;
/*0x004*/     ULONG32      NewCell;
          }CM_CELL_REMAP_BLOCK, *PCM_CELL_REMAP_BLOCK;

          typedef struct _CM_FULL_RESOURCE_DESCRIPTOR               // 3 elements, 0x24 bytes (sizeof)
          {
/*0x000*/     enum _INTERFACE_TYPE InterfaceType;
/*0x004*/     ULONG32      BusNumber;
/*0x008*/     struct _CM_PARTIAL_RESOURCE_LIST PartialResourceList; // 4 elements, 0x1C bytes (sizeof)
          }CM_FULL_RESOURCE_DESCRIPTOR, *PCM_FULL_RESOURCE_DESCRIPTOR;

          typedef struct _CM_INDEX_HINT_BLOCK // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     ULONG32      HashKey[1];
          }CM_INDEX_HINT_BLOCK, *PCM_INDEX_HINT_BLOCK;

          typedef struct _CM_INTENT_LOCK       // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      OwnerCount;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _CM_KCB_UOW** OwnerTable;
          }CM_INTENT_LOCK, *PCM_INTENT_LOCK;

          typedef struct _CM_KCB_UOW                               // 20 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY TransactionListEntry;             // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _CM_INTENT_LOCK* KCBLock;
/*0x018*/     struct _CM_INTENT_LOCK* KeyLock;
/*0x020*/     struct _LIST_ENTRY KCBListEntry;                     // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     struct _CM_KEY_CONTROL_BLOCK* KeyControlBlock;
/*0x038*/     struct _CM_TRANS* Transaction;
/*0x040*/     ULONG32      UoWState;
/*0x044*/     enum _UoWActionType ActionType;
/*0x048*/     enum _HSTORAGE_TYPE StorageType;
/*0x04C*/     UINT8        _PADDING0_[0x4];
              union                                                // 8 elements, 0x10 bytes (sizeof)
              {
/*0x050*/         struct _CM_KEY_CONTROL_BLOCK* ChildKCB;
/*0x050*/         ULONG32      VolatileKeyCell;
                  struct                                           // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x050*/             ULONG32      OldValueCell;
/*0x054*/             ULONG32      NewValueCell;
/*0x058*/             UINT8        _PADDING1_[0x8];
                  };
/*0x050*/         ULONG32      UserFlags;
/*0x050*/         union _LARGE_INTEGER LastWriteTime;              // 4 elements, 0x8 bytes (sizeof)
/*0x050*/         ULONG32      TxSecurityCell;
                  struct                                           // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x050*/             struct _CM_KEY_CONTROL_BLOCK* OldChildKCB;
/*0x058*/             struct _CM_KEY_CONTROL_BLOCK* NewChildKCB;
                  };
                  struct                                           // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x050*/             struct _CM_KEY_CONTROL_BLOCK* OtherChildKCB;
/*0x058*/             ULONG32      ThisVolatileKeyCell;
/*0x05C*/             UINT8        _PADDING2_[0x4];
                  };
              };
          }CM_KCB_UOW, *PCM_KCB_UOW;

          typedef struct _CM_KEY_BODY                        // 10 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     ULONG32      Type;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _CM_KEY_CONTROL_BLOCK* KeyControlBlock;
/*0x010*/     struct _CM_NOTIFY_BLOCK* NotifyBlock;
/*0x018*/     VOID*        ProcessID;
/*0x020*/     struct _LIST_ENTRY KeyBodyList;                // 2 elements, 0x10 bytes (sizeof)
              struct                                         // 2 elements, 0x4 bytes (sizeof)
              {
/*0x030*/         ULONG32      Flags : 16;                   // 0 BitPosition
/*0x030*/         ULONG32      HandleTags : 16;              // 16 BitPosition
              };
/*0x038*/     VOID*        KtmTrans;
/*0x040*/     struct _GUID* KtmUow;
/*0x048*/     struct _LIST_ENTRY ContextListHead;            // 2 elements, 0x10 bytes (sizeof)
          }CM_KEY_BODY, *PCM_KEY_BODY;

          typedef struct _CM_KEY_CONTROL_BLOCK               // 48 elements, 0x128 bytes (sizeof)
          {
/*0x000*/     ULONG32      RefCount;
              struct                                         // 7 elements, 0x4 bytes (sizeof)
              {
/*0x004*/         ULONG32      ExtFlags : 16;                // 0 BitPosition
/*0x004*/         ULONG32      PrivateAlloc : 1;             // 16 BitPosition
/*0x004*/         ULONG32      Delete : 1;                   // 17 BitPosition
/*0x004*/         ULONG32      HiveUnloaded : 1;             // 18 BitPosition
/*0x004*/         ULONG32      Decommissioned : 1;           // 19 BitPosition
/*0x004*/         ULONG32      LockTablePresent : 1;         // 20 BitPosition
/*0x004*/         ULONG32      TotalLevels : 10;             // 21 BitPosition
              };
              struct                                         // 3 elements, 0x4 bytes (sizeof)
              {
/*0x008*/         ULONG32      DelayedDeref : 1;             // 0 BitPosition
/*0x008*/         ULONG32      DelayedClose : 1;             // 1 BitPosition
/*0x008*/         ULONG32      Parking : 1;                  // 2 BitPosition
              };
              union                                          // 2 elements, 0x20 bytes (sizeof)
              {
/*0x010*/         struct _CM_KEY_HASH KeyHash;               // 4 elements, 0x20 bytes (sizeof)
                  struct                                     // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x010*/             ULONG32      ConvKey;
/*0x014*/             UINT8        _PADDING0_[0x4];
/*0x018*/             struct _CM_KEY_HASH* NextHash;
/*0x020*/             struct _HHIVE* KeyHive;
/*0x028*/             ULONG32      KeyCell;
/*0x02C*/             UINT8        _PADDING1_[0x4];
                  };
              };
/*0x030*/     struct _EX_PUSH_LOCK KcbPushlock;              // 7 elements, 0x8 bytes (sizeof)
              union                                          // 2 elements, 0x8 bytes (sizeof)
              {
/*0x038*/         struct _KTHREAD* Owner;
/*0x038*/         LONG32       SharedCount;
              };
/*0x040*/     ULONG32      SlotHint;
/*0x044*/     UINT8        _PADDING2_[0x4];
/*0x048*/     struct _CM_KEY_CONTROL_BLOCK* ParentKcb;
/*0x050*/     struct _CM_NAME_CONTROL_BLOCK* NameBlock;
/*0x058*/     struct _CM_KEY_SECURITY_CACHE* CachedSecurity;
/*0x060*/     struct _CACHED_CHILD_LIST ValueCache;          // 3 elements, 0x10 bytes (sizeof)
              union                                          // 3 elements, 0x8 bytes (sizeof)
              {
/*0x070*/         struct _CM_INDEX_HINT_BLOCK* IndexHint;
/*0x070*/         ULONG32      HashKey;
/*0x070*/         ULONG32      SubKeyCount;
              };
              union                                          // 2 elements, 0x10 bytes (sizeof)
              {
/*0x078*/         struct _LIST_ENTRY KeyBodyListHead;        // 2 elements, 0x10 bytes (sizeof)
/*0x078*/         struct _LIST_ENTRY FreeListEntry;          // 2 elements, 0x10 bytes (sizeof)
              };
/*0x088*/     struct _CM_KEY_BODY* KeyBodyArray[4];
/*0x0A8*/     union _LARGE_INTEGER KcbLastWriteTime;         // 4 elements, 0x8 bytes (sizeof)
/*0x0B0*/     UINT16       KcbMaxNameLen;
/*0x0B2*/     UINT16       KcbMaxValueNameLen;
/*0x0B4*/     ULONG32      KcbMaxValueDataLen;
              struct                                         // 4 elements, 0x4 bytes (sizeof)
              {
/*0x0B8*/         ULONG32      KcbUserFlags : 4;             // 0 BitPosition
/*0x0B8*/         ULONG32      KcbVirtControlFlags : 4;      // 4 BitPosition
/*0x0B8*/         ULONG32      KcbDebug : 8;                 // 8 BitPosition
/*0x0B8*/         ULONG32      Flags : 16;                   // 16 BitPosition
              };
/*0x0C0*/     CHAR*        RealKeyName;
/*0x0C8*/     struct _LIST_ENTRY KCBUoWListHead;             // 2 elements, 0x10 bytes (sizeof)
              union                                          // 2 elements, 0x10 bytes (sizeof)
              {
/*0x0D8*/         struct _LIST_ENTRY DelayQueueEntry;        // 2 elements, 0x10 bytes (sizeof)
/*0x0D8*/         UINT8*       Stolen;
              };
/*0x0E8*/     struct _CM_TRANS* TransKCBOwner;
/*0x0F0*/     struct _CM_INTENT_LOCK KCBLock;                // 2 elements, 0x10 bytes (sizeof)
/*0x100*/     struct _CM_INTENT_LOCK KeyLock;                // 2 elements, 0x10 bytes (sizeof)
/*0x110*/     struct _CHILD_LIST TransValueCache;            // 2 elements, 0x8 bytes (sizeof)
/*0x118*/     struct _CM_TRANS* TransValueListOwner;
/*0x120*/     struct _UNICODE_STRING* FullKCBName;
          }CM_KEY_CONTROL_BLOCK, *PCM_KEY_CONTROL_BLOCK;

          typedef struct _CM_KEY_HASH        // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     ULONG32      ConvKey;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _CM_KEY_HASH* NextHash;
/*0x010*/     struct _HHIVE* KeyHive;
/*0x018*/     ULONG32      KeyCell;
/*0x01C*/     UINT8        _PADDING1_[0x4];
          }CM_KEY_HASH, *PCM_KEY_HASH;

          typedef struct _CM_KEY_HASH_TABLE_ENTRY // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK Lock;          // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _KTHREAD* Owner;
/*0x010*/     struct _CM_KEY_HASH* Entry;
          }CM_KEY_HASH_TABLE_ENTRY, *PCM_KEY_HASH_TABLE_ENTRY;

          typedef struct _CM_KEY_INDEX // 3 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT16       Signature;
/*0x002*/     UINT16       Count;
/*0x004*/     ULONG32      List[1];
          }CM_KEY_INDEX, *PCM_KEY_INDEX;

          typedef struct _CM_KEY_NODE                          // 22 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     UINT16       Signature;
/*0x002*/     UINT16       Flags;
/*0x004*/     union _LARGE_INTEGER LastWriteTime;              // 4 elements, 0x8 bytes (sizeof)
/*0x00C*/     ULONG32      AccessBits;
/*0x010*/     ULONG32      Parent;
/*0x014*/     ULONG32      SubKeyCounts[2];
              union                                            // 2 elements, 0x10 bytes (sizeof)
              {
                  struct                                       // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x01C*/             ULONG32      SubKeyLists[2];
/*0x024*/             struct _CHILD_LIST ValueList;            // 2 elements, 0x8 bytes (sizeof)
                  };
/*0x01C*/         struct _CM_KEY_REFERENCE ChildHiveReference; // 2 elements, 0x10 bytes (sizeof)
              };
/*0x02C*/     ULONG32      Security;
/*0x030*/     ULONG32      Class;
              struct                                           // 4 elements, 0x4 bytes (sizeof)
              {
/*0x034*/         ULONG32      MaxNameLen : 16;                // 0 BitPosition
/*0x034*/         ULONG32      UserFlags : 4;                  // 16 BitPosition
/*0x034*/         ULONG32      VirtControlFlags : 4;           // 20 BitPosition
/*0x034*/         ULONG32      Debug : 8;                      // 24 BitPosition
              };
/*0x038*/     ULONG32      MaxClassLen;
/*0x03C*/     ULONG32      MaxValueNameLen;
/*0x040*/     ULONG32      MaxValueDataLen;
/*0x044*/     ULONG32      WorkVar;
/*0x048*/     UINT16       NameLength;
/*0x04A*/     UINT16       ClassLength;
/*0x04C*/     WCHAR        Name[1];
/*0x04E*/     UINT8        _PADDING0_[0x2];
          }CM_KEY_NODE, *PCM_KEY_NODE;

          typedef struct _CM_KEY_REFERENCE  // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      KeyCell;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _HHIVE* KeyHive;
          }CM_KEY_REFERENCE, *PCM_KEY_REFERENCE;

          typedef struct _CM_KEY_SECURITY                      // 7 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT16       Signature;
/*0x002*/     UINT16       Reserved;
/*0x004*/     ULONG32      Flink;
/*0x008*/     ULONG32      Blink;
/*0x00C*/     ULONG32      ReferenceCount;
/*0x010*/     ULONG32      DescriptorLength;
/*0x014*/     struct _SECURITY_DESCRIPTOR_RELATIVE Descriptor; // 7 elements, 0x14 bytes (sizeof)
          }CM_KEY_SECURITY, *PCM_KEY_SECURITY;

          typedef struct _CM_KEY_SECURITY_CACHE                // 6 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     ULONG32      Cell;
/*0x004*/     ULONG32      ConvKey;
/*0x008*/     struct _LIST_ENTRY List;                         // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     ULONG32      DescriptorLength;
/*0x01C*/     ULONG32      RealRefCount;
/*0x020*/     struct _SECURITY_DESCRIPTOR_RELATIVE Descriptor; // 7 elements, 0x14 bytes (sizeof)
/*0x034*/     UINT8        _PADDING0_[0x4];
          }CM_KEY_SECURITY_CACHE, *PCM_KEY_SECURITY_CACHE;

          typedef struct _CM_KEY_SECURITY_CACHE_ENTRY        // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Cell;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _CM_KEY_SECURITY_CACHE* CachedSecurity;
          }CM_KEY_SECURITY_CACHE_ENTRY, *PCM_KEY_SECURITY_CACHE_ENTRY;

          typedef struct _CM_KEY_VALUE      // 8 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT16       Signature;
/*0x002*/     UINT16       NameLength;
/*0x004*/     ULONG32      DataLength;
/*0x008*/     ULONG32      Data;
/*0x00C*/     ULONG32      Type;
/*0x010*/     UINT16       Flags;
/*0x012*/     UINT16       Spare;
/*0x014*/     WCHAR        Name[1];
/*0x016*/     UINT8        _PADDING0_[0x2];
          }CM_KEY_VALUE, *PCM_KEY_VALUE;

          typedef struct _CM_NAME_CONTROL_BLOCK      // 7 elements, 0x20 bytes (sizeof)
          {
              struct                                 // 2 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      Compressed : 1;       // 0 BitPosition
/*0x000*/         ULONG32      RefCount : 31;        // 1 BitPosition
              };
              union                                  // 2 elements, 0x18 bytes (sizeof)
              {
/*0x008*/         struct _CM_NAME_HASH NameHash;     // 4 elements, 0x18 bytes (sizeof)
                  struct                             // 4 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      ConvKey;
/*0x00C*/             UINT8        _PADDING0_[0x4];
/*0x010*/             struct _CM_KEY_HASH* NextHash;
/*0x018*/             UINT16       NameLength;
/*0x01A*/             WCHAR        Name[1];
/*0x01C*/             UINT8        _PADDING1_[0x4];
                  };
              };
          }CM_NAME_CONTROL_BLOCK, *PCM_NAME_CONTROL_BLOCK;

          typedef struct _CM_NAME_HASH        // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      ConvKey;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _CM_NAME_HASH* NextHash;
/*0x010*/     UINT16       NameLength;
/*0x012*/     WCHAR        Name[1];
/*0x014*/     UINT8        _PADDING1_[0x4];
          }CM_NAME_HASH, *PCM_NAME_HASH;

          typedef struct _CM_NOTIFY_BLOCK                      // 8 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY HiveList;                     // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY PostList;                     // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     struct _CM_KEY_CONTROL_BLOCK* KeyControlBlock;
/*0x028*/     struct _CM_KEY_BODY* KeyBody;
              struct                                           // 3 elements, 0x4 bytes (sizeof)
              {
/*0x030*/         ULONG32      Filter : 30;                    // 0 BitPosition
/*0x030*/         ULONG32      WatchTree : 1;                  // 30 BitPosition
/*0x030*/         ULONG32      NotifyPending : 1;              // 31 BitPosition
              };
/*0x038*/     struct _SECURITY_SUBJECT_CONTEXT SubjectContext; // 4 elements, 0x20 bytes (sizeof)
          }CM_NOTIFY_BLOCK, *PCM_NOTIFY_BLOCK;

          typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR // 4 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     UINT8        Type;
/*0x001*/     UINT8        ShareDisposition;
/*0x002*/     UINT16       Flags;
              union                                      // 14 elements, 0x10 bytes (sizeof)
              {
                  struct                                 // 2 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             union _LARGE_INTEGER Start;        // 4 elements, 0x8 bytes (sizeof)
/*0x00C*/             ULONG32      Length;
                  }Generic;
                  struct                                 // 2 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             union _LARGE_INTEGER Start;        // 4 elements, 0x8 bytes (sizeof)
/*0x00C*/             ULONG32      Length;
                  }Port;
                  struct                                 // 4 elements, 0x10 bytes (sizeof)
                  {
/*0x004*/             UINT16       Level;
/*0x006*/             UINT16       Group;
/*0x008*/             ULONG32      Vector;
/*0x00C*/             UINT64       Affinity;
                  }Interrupt;
                  struct                                 // 2 elements, 0x10 bytes (sizeof)
                  {
                      union                              // 2 elements, 0x10 bytes (sizeof)
                      {
                          struct                         // 4 elements, 0x10 bytes (sizeof)
                          {
/*0x004*/                     UINT16       Group;
/*0x006*/                     UINT16       MessageCount;
/*0x008*/                     ULONG32      Vector;
/*0x00C*/                     UINT64       Affinity;
                          }Raw;
                          struct                         // 4 elements, 0x10 bytes (sizeof)
                          {
/*0x004*/                     UINT16       Level;
/*0x006*/                     UINT16       Group;
/*0x008*/                     ULONG32      Vector;
/*0x00C*/                     UINT64       Affinity;
                          }Translated;
                      };
                  }MessageInterrupt;
                  struct                                 // 2 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             union _LARGE_INTEGER Start;        // 4 elements, 0x8 bytes (sizeof)
/*0x00C*/             ULONG32      Length;
                  }Memory;
                  struct                                 // 3 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             ULONG32      Channel;
/*0x008*/             ULONG32      Port;
/*0x00C*/             ULONG32      Reserved1;
                  }Dma;
                  struct                                 // 3 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             ULONG32      Channel;
/*0x008*/             ULONG32      RequestLine;
/*0x00C*/             ULONG32      Reserved1;
                  }DmaV3;
                  struct                                 // 1 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             ULONG32      Data[3];
                  }DevicePrivate;
                  struct                                 // 3 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             ULONG32      Start;
/*0x008*/             ULONG32      Length;
/*0x00C*/             ULONG32      Reserved;
                  }BusNumber;
                  struct                                 // 3 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             ULONG32      DataSize;
/*0x008*/             ULONG32      Reserved1;
/*0x00C*/             ULONG32      Reserved2;
                  }DeviceSpecificData;
                  struct                                 // 2 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             union _LARGE_INTEGER Start;        // 4 elements, 0x8 bytes (sizeof)
/*0x00C*/             ULONG32      Length40;
                  }Memory40;
                  struct                                 // 2 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             union _LARGE_INTEGER Start;        // 4 elements, 0x8 bytes (sizeof)
/*0x00C*/             ULONG32      Length48;
                  }Memory48;
                  struct                                 // 2 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             union _LARGE_INTEGER Start;        // 4 elements, 0x8 bytes (sizeof)
/*0x00C*/             ULONG32      Length64;
                  }Memory64;
                  struct                                 // 6 elements, 0xC bytes (sizeof)
                  {
/*0x004*/             UINT8        Class;
/*0x005*/             UINT8        Type;
/*0x006*/             UINT8        Reserved1;
/*0x007*/             UINT8        Reserved2;
/*0x008*/             ULONG32      IdLowPart;
/*0x00C*/             ULONG32      IdHighPart;
                  }Connection;
              }u;
          }CM_PARTIAL_RESOURCE_DESCRIPTOR, *PCM_PARTIAL_RESOURCE_DESCRIPTOR;

          typedef struct _CM_PARTIAL_RESOURCE_LIST                          // 4 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     UINT16       Version;
/*0x002*/     UINT16       Revision;
/*0x004*/     ULONG32      Count;
/*0x008*/     struct _CM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptors[1];
          }CM_PARTIAL_RESOURCE_LIST, *PCM_PARTIAL_RESOURCE_LIST;

          typedef struct _CM_RESOURCE_LIST                 // 2 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     struct _CM_FULL_RESOURCE_DESCRIPTOR List[1];
          }CM_RESOURCE_LIST, *PCM_RESOURCE_LIST;

          typedef struct _CM_RM                       // 17 elements, 0x88 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY RmListEntry;         // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY TransactionListHead; // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     VOID*        TmHandle;
/*0x028*/     VOID*        Tm;
/*0x030*/     VOID*        RmHandle;
/*0x038*/     VOID*        KtmRm;
/*0x040*/     ULONG32      RefCount;
/*0x044*/     ULONG32      ContainerNum;
/*0x048*/     UINT64       ContainerSize;
/*0x050*/     struct _CMHIVE* CmHive;
/*0x058*/     VOID*        LogFileObject;
/*0x060*/     VOID*        MarshallingContext;
/*0x068*/     ULONG32      RmFlags;
/*0x06C*/     LONG32       LogStartStatus1;
/*0x070*/     LONG32       LogStartStatus2;
/*0x074*/     UINT8        _PADDING0_[0x4];
/*0x078*/     UINT64       BaseLsn;
/*0x080*/     struct _ERESOURCE* RmLock;
          }CM_RM, *PCM_RM;

          typedef struct _CM_TRANS                      // 12 elements, 0xA8 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY TransactionListEntry;  // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY KCBUoWListHead;        // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     struct _LIST_ENTRY LazyCommitListEntry;   // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     VOID*        KtmTrans;
/*0x038*/     struct _CM_RM* CmRm;
/*0x040*/     struct _KENLISTMENT* KtmEnlistmentObject;
/*0x048*/     VOID*        KtmEnlistmentHandle;
/*0x050*/     struct _GUID KtmUow;                      // 4 elements, 0x10 bytes (sizeof)
/*0x060*/     UINT64       StartLsn;
/*0x068*/     ULONG32      TransState;
/*0x06C*/     ULONG32      HiveCount;
/*0x070*/     struct _CMHIVE* HiveArray[7];
          }CM_TRANS, *PCM_TRANS;

          typedef struct _CM_WORKITEM                                                                                                                                                                                                           // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;                                                                                                                                                                                                     // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Private;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* WorkerRoutine;
/*0x020*/     VOID*        Parameter;
          }CM_WORKITEM, *PCM_WORKITEM;

          typedef struct _CMHIVE                                  // 63 elements, 0xDA8 bytes (sizeof)
          {
/*0x000*/     struct _HHIVE Hive;                                 // 27 elements, 0x580 bytes (sizeof)
/*0x580*/     VOID*        FileHandles[6];
/*0x5B0*/     struct _LIST_ENTRY NotifyList;                      // 2 elements, 0x10 bytes (sizeof)
/*0x5C0*/     struct _LIST_ENTRY HiveList;                        // 2 elements, 0x10 bytes (sizeof)
/*0x5D0*/     struct _LIST_ENTRY PreloadedHiveList;               // 2 elements, 0x10 bytes (sizeof)
/*0x5E0*/     struct _EX_RUNDOWN_REF HiveRundown;                 // 2 elements, 0x8 bytes (sizeof)
/*0x5E8*/     struct _LIST_ENTRY ParseCacheEntries;               // 2 elements, 0x10 bytes (sizeof)
/*0x5F8*/     struct _CM_KEY_HASH_TABLE_ENTRY* KcbCacheTable;
/*0x600*/     ULONG32      KcbCacheTableSize;
/*0x604*/     ULONG32      Identity;
/*0x608*/     struct _FAST_MUTEX* HiveLock;
/*0x610*/     struct _FAST_MUTEX* WriterLock;
/*0x618*/     struct _ERESOURCE* FlusherLock;
/*0x620*/     struct _RTL_BITMAP FlushDirtyVector;                // 2 elements, 0x10 bytes (sizeof)
/*0x630*/     struct _CMP_OFFSET_ARRAY* FlushOffsetArray;
/*0x638*/     ULONG32      FlushOffsetArrayCount;
/*0x63C*/     UINT8        _PADDING0_[0x4];
/*0x640*/     struct _HBASE_BLOCK* FlushBaseBlock;
/*0x648*/     ULONG32      FlushHiveTruncated;
/*0x64C*/     UINT8        _PADDING1_[0x4];
/*0x650*/     struct _EX_PUSH_LOCK SecurityLock;                  // 7 elements, 0x8 bytes (sizeof)
/*0x658*/     ULONG32      UseCount;
/*0x65C*/     ULONG32      LastShrinkHiveSize;
/*0x660*/     union _LARGE_INTEGER ActualFileSize;                // 4 elements, 0x8 bytes (sizeof)
/*0x668*/     struct _UNICODE_STRING FileFullPath;                // 3 elements, 0x10 bytes (sizeof)
/*0x678*/     struct _UNICODE_STRING FileUserName;                // 3 elements, 0x10 bytes (sizeof)
/*0x688*/     struct _UNICODE_STRING HiveRootPath;                // 3 elements, 0x10 bytes (sizeof)
/*0x698*/     ULONG32      SecurityCount;
/*0x69C*/     ULONG32      SecurityCacheSize;
/*0x6A0*/     LONG32       SecurityHitHint;
/*0x6A4*/     UINT8        _PADDING2_[0x4];
/*0x6A8*/     struct _CM_KEY_SECURITY_CACHE_ENTRY* SecurityCache;
/*0x6B0*/     struct _LIST_ENTRY SecurityHash[64];
/*0xAB0*/     ULONG32      UnloadEventCount;
/*0xAB4*/     UINT8        _PADDING3_[0x4];
/*0xAB8*/     struct _KEVENT** UnloadEventArray;
/*0xAC0*/     struct _CM_KEY_CONTROL_BLOCK* RootKcb;
/*0xAC8*/     UINT8        Frozen;
/*0xAC9*/     UINT8        _PADDING4_[0x7];
/*0xAD0*/     struct _CM_WORKITEM* UnloadWorkItem;
/*0xAD8*/     struct _CM_WORKITEM UnloadWorkItemHolder;           // 4 elements, 0x28 bytes (sizeof)
/*0xB00*/     UINT8        GrowOnlyMode;
/*0xB01*/     UINT8        _PADDING5_[0x3];
/*0xB04*/     ULONG32      GrowOffset;
/*0xB08*/     struct _LIST_ENTRY KcbConvertListHead;              // 2 elements, 0x10 bytes (sizeof)
/*0xB18*/     struct _LIST_ENTRY KnodeConvertListHead;            // 2 elements, 0x10 bytes (sizeof)
/*0xB28*/     struct _CM_CELL_REMAP_BLOCK* CellRemapArray;
/*0xB30*/     ULONG32      Flags;
/*0xB34*/     UINT8        _PADDING6_[0x4];
/*0xB38*/     struct _LIST_ENTRY TrustClassEntry;                 // 2 elements, 0x10 bytes (sizeof)
/*0xB48*/     UINT64       DirtyTime;
/*0xB50*/     struct _CM_RM* CmRm;
/*0xB58*/     ULONG32      CmRmInitFailPoint;
/*0xB5C*/     LONG32       CmRmInitFailStatus;
/*0xB60*/     struct _KTHREAD* CreatorOwner;
/*0xB68*/     struct _KTHREAD* RundownThread;
/*0xB70*/     union _LARGE_INTEGER LastWriteTime;                 // 4 elements, 0x8 bytes (sizeof)
/*0xB78*/     LONG32       ReferenceCount;
              union                                               // 2 elements, 0x4 bytes (sizeof)
              {
/*0xB7C*/         ULONG32      FlushFlags;
                  struct                                          // 2 elements, 0x4 bytes (sizeof)
                  {
/*0xB7C*/             ULONG32      FlushActive : 1;               // 0 BitPosition
/*0xB7C*/             ULONG32      DiskFileBad : 1;               // 1 BitPosition
                  };
              };
/*0xB80*/     struct _HIVE_WAIT_PACKET* FlushWaitList;
/*0xB88*/     LONG32       UnloadHistoryIndex;
/*0xB8C*/     ULONG32      UnloadHistory[128];
/*0xD8C*/     ULONG32      BootStart;
/*0xD90*/     ULONG32      UnaccessedStart;
/*0xD94*/     ULONG32      UnaccessedEnd;
/*0xD98*/     ULONG32      LoadedKeyCount;
/*0xD9C*/     ULONG32      HandleClosePending;
/*0xDA0*/     struct _EX_PUSH_LOCK HandleClosePendingEvent;       // 7 elements, 0x8 bytes (sizeof)
          }CMHIVE, *PCMHIVE;

          typedef struct _HBASE_BLOCK          // 26 elements, 0x1000 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     ULONG32      Sequence1;
/*0x008*/     ULONG32      Sequence2;
/*0x00C*/     union _LARGE_INTEGER TimeStamp;  // 4 elements, 0x8 bytes (sizeof)
/*0x014*/     ULONG32      Major;
/*0x018*/     ULONG32      Minor;
/*0x01C*/     ULONG32      Type;
/*0x020*/     ULONG32      Format;
/*0x024*/     ULONG32      RootCell;
/*0x028*/     ULONG32      Length;
/*0x02C*/     ULONG32      Cluster;
/*0x030*/     UINT8        FileName[64];
/*0x070*/     struct _GUID RmId;               // 4 elements, 0x10 bytes (sizeof)
/*0x080*/     struct _GUID LogId;              // 4 elements, 0x10 bytes (sizeof)
/*0x090*/     ULONG32      Flags;
/*0x094*/     struct _GUID TmId;               // 4 elements, 0x10 bytes (sizeof)
/*0x0A4*/     ULONG32      GuidSignature;
/*0x0A8*/     UINT64       LastReorganizeTime;
/*0x0B0*/     ULONG32      Reserved1[83];
/*0x1FC*/     ULONG32      CheckSum;
/*0x200*/     ULONG32      Reserved2[882];
/*0xFC8*/     struct _GUID ThawTmId;           // 4 elements, 0x10 bytes (sizeof)
/*0xFD8*/     struct _GUID ThawRmId;           // 4 elements, 0x10 bytes (sizeof)
/*0xFE8*/     struct _GUID ThawLogId;          // 4 elements, 0x10 bytes (sizeof)
/*0xFF8*/     ULONG32      BootType;
/*0xFFC*/     ULONG32      BootRecover;
          }HBASE_BLOCK, *PHBASE_BLOCK;

          typedef struct _HBIN                // 6 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     ULONG32      FileOffset;
/*0x008*/     ULONG32      Size;
/*0x00C*/     ULONG32      Reserved1[2];
/*0x014*/     union _LARGE_INTEGER TimeStamp; // 4 elements, 0x8 bytes (sizeof)
/*0x01C*/     ULONG32      Spare;
          }HBIN, *PHBIN;

          typedef struct _HCELL                  // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     LONG32       Size;
              union                              // 1 elements, 0x4 bytes (sizeof)
              {
                  struct                         // 1 elements, 0x4 bytes (sizeof)
                  {
                      union                      // 2 elements, 0x4 bytes (sizeof)
                      {
/*0x004*/                 ULONG32      UserData;
/*0x004*/                 ULONG32      Next;
                      }u;
                  }NewCell;
              }u;
          }HCELL, *PHCELL;

          typedef struct _HHIVE                                                    // 27 elements, 0x580 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     FUNCT_14C5_14C4_GetCellRoutine* GetCellRoutine;
/*0x010*/     FUNCT_00B1_1512_Allocate* Allocate;
/*0x018*/     FUNCT_00AE_07CA_IdleCancel_Free_ComponentActive_ComponentIdle* Free;
/*0x020*/     FUNCT_006E_1517_FileWrite* FileWrite;
/*0x028*/     FUNCT_006E_1523_FileRead* FileRead;
/*0x030*/     VOID*        HiveLoadFailure;
/*0x038*/     struct _HBASE_BLOCK* BaseBlock;
/*0x040*/     struct _RTL_BITMAP DirtyVector;                                      // 2 elements, 0x10 bytes (sizeof)
/*0x050*/     ULONG32      DirtyCount;
/*0x054*/     ULONG32      DirtyAlloc;
/*0x058*/     ULONG32      BaseBlockAlloc;
/*0x05C*/     ULONG32      Cluster;
/*0x060*/     UINT8        Flat;
/*0x061*/     UINT8        ReadOnly;
/*0x062*/     UINT8        DirtyFlag;
/*0x063*/     UINT8        _PADDING1_[0x1];
/*0x064*/     ULONG32      HvBinHeadersUse;
/*0x068*/     ULONG32      HvFreeCellsUse;
/*0x06C*/     ULONG32      HvUsedCellsUse;
/*0x070*/     ULONG32      CmUsedCellsUse;
/*0x074*/     ULONG32      HiveFlags;
/*0x078*/     ULONG32      CurrentLog;
/*0x07C*/     ULONG32      LogSize[2];
/*0x084*/     ULONG32      RefreshCount;
/*0x088*/     ULONG32      StorageTypeCount;
/*0x08C*/     ULONG32      Version;
/*0x090*/     struct _DUAL Storage[2];
          }HHIVE, *PHHIVE;

          typedef struct _HIVE_LIST_ENTRY   // 16 elements, 0x88 bytes (sizeof)
          {
/*0x000*/     UINT16*      FileName;
/*0x008*/     UINT16*      BaseName;
/*0x010*/     UINT16*      RegRootName;
/*0x018*/     struct _CMHIVE* CmHive;
/*0x020*/     ULONG32      HHiveFlags;
/*0x024*/     ULONG32      CmHiveFlags;
/*0x028*/     ULONG32      CmKcbCacheSize;
/*0x02C*/     UINT8        _PADDING0_[0x4];
/*0x030*/     struct _CMHIVE* CmHive2;
/*0x038*/     UINT8        HiveMounted;
/*0x039*/     UINT8        ThreadFinished;
/*0x03A*/     UINT8        ThreadStarted;
/*0x03B*/     UINT8        Allocate;
/*0x03C*/     UINT8        WinPERequired;
/*0x03D*/     UINT8        _PADDING1_[0x3];
/*0x040*/     struct _KEVENT StartEvent;    // 1 elements, 0x18 bytes (sizeof)
/*0x058*/     struct _KEVENT FinishedEvent; // 1 elements, 0x18 bytes (sizeof)
/*0x070*/     struct _KEVENT MountLock;     // 1 elements, 0x18 bytes (sizeof)
          }HIVE_LIST_ENTRY, *PHIVE_LIST_ENTRY;

          typedef struct _HIVE_LOAD_FAILURE                                                                      // 13 elements, 0x160 bytes (sizeof)
          {
/*0x000*/     struct _HHIVE* Hive;
/*0x008*/     ULONG32      Index;
/*0x00C*/     ULONG32      RecoverableIndex;
/*0x010*/     struct __2011110910380E00B38CE6D179FFF1B30_Locations_RecoverableLocations Locations[8];
/*0x070*/     struct __2011110910380E00B38CE6D179FFF1B30_Locations_RecoverableLocations RecoverableLocations[8];
              struct                                                                                             // 3 elements, 0x18 bytes (sizeof)
              {
/*0x0D0*/         ULONG32      Action;
/*0x0D4*/         UINT8        _PADDING0_[0x4];
/*0x0D8*/         VOID*        Handle;
/*0x0E0*/         LONG32       Status;
/*0x0E4*/         UINT8        _PADDING1_[0x4];
              }RegistryIO;
              struct                                                                                             // 1 elements, 0x8 bytes (sizeof)
              {
/*0x0E8*/         VOID*        CheckStack;
              }CheckRegistry2;
              struct                                                                                             // 4 elements, 0x20 bytes (sizeof)
              {
/*0x0F0*/         ULONG32      Cell;
/*0x0F4*/         UINT8        _PADDING0_[0x4];
/*0x0F8*/         struct _CELL_DATA* CellPoint;
/*0x100*/         VOID*        RootPoint;
/*0x108*/         ULONG32      Index;
/*0x10C*/         UINT8        _PADDING1_[0x4];
              }CheckKey;
              struct                                                                                             // 4 elements, 0x18 bytes (sizeof)
              {
/*0x110*/         struct _CELL_DATA* List;
/*0x118*/         ULONG32      Index;
/*0x11C*/         ULONG32      Cell;
/*0x120*/         struct _CELL_DATA* CellPoint;
              }CheckValueList;
              struct                                                                                             // 3 elements, 0x10 bytes (sizeof)
              {
/*0x128*/         ULONG32      Space;
/*0x12C*/         ULONG32      MapPoint;
/*0x130*/         struct _HBIN* BinPoint;
              }CheckHive;
              struct                                                                                             // 3 elements, 0x10 bytes (sizeof)
              {
/*0x138*/         ULONG32      Space;
/*0x13C*/         ULONG32      MapPoint;
/*0x140*/         struct _HBIN* BinPoint;
              }CheckHive1;
              struct                                                                                             // 2 elements, 0x10 bytes (sizeof)
              {
/*0x148*/         struct _HBIN* Bin;
/*0x150*/         struct _HCELL* CellPoint;
              }CheckBin;
              struct                                                                                             // 1 elements, 0x4 bytes (sizeof)
              {
/*0x158*/         ULONG32      FileOffset;
              }RecoverData;
          }HIVE_LOAD_FAILURE, *PHIVE_LOAD_FAILURE;

          typedef struct _HIVE_WAIT_PACKET    // 3 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _KEVENT WakeEvent;       // 1 elements, 0x18 bytes (sizeof)
/*0x018*/     LONG32       Status;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     struct _HIVE_WAIT_PACKET* Next;
          }HIVE_WAIT_PACKET, *PHIVE_WAIT_PACKET;

          typedef struct _CMP_OFFSET_ARRAY  // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      FileOffset;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        DataBuffer;
/*0x010*/     ULONG32      DataLength;
/*0x014*/     UINT8        _PADDING1_[0x4];
          }CMP_OFFSET_ARRAY, *PCMP_OFFSET_ARRAY;

typedef enum _CM_LOAD_FAILURE_TYPE  // 18 elements, 0x4 bytes
{
    _None                               = 0 /*0x0*/,
    _CmInitializeHive                   = 1 /*0x1*/,
    _HvInitializeHive                   = 2 /*0x2*/,
    _HvpBuildMap                        = 3 /*0x3*/,
    _HvpBuildMapAndCopy                 = 4 /*0x4*/,
    _HvpInitMap                         = 5 /*0x5*/,
    _HvLoadHive                         = 6 /*0x6*/,
    _HvpReadFileImageAndBuildMap        = 7 /*0x7*/,
    _HvpRecoverData                     = 8 /*0x8*/,
    _CmpValidateHiveSecurityDescriptors = 9 /*0x9*/,
    _HvpEnlistBinInMap                  = 10 /*0xA*/,
    _CmCheckRegistry                    = 11 /*0xB*/,
    _CmRegistryIO                       = 12 /*0xC*/,
    _CmCheckRegistry2                   = 13 /*0xD*/,
    _CmpCheckKey                        = 14 /*0xE*/,
    _CmpCheckValueList                  = 15 /*0xF*/,
    _HvCheckHive                        = 16 /*0x10*/,
    _HvCheckBin                         = 17 /*0x11*/
}CM_LOAD_FAILURE_TYPE, *PCM_LOAD_FAILURE_TYPE;

typedef enum _CM_SHARE_DISPOSITION  // 4 elements, 0x4 bytes
{
    CmResourceShareUndetermined    = 0 /*0x0*/,
    CmResourceShareDeviceExclusive = 1 /*0x1*/,
    CmResourceShareDriverExclusive = 2 /*0x2*/,
    CmResourceShareShared          = 3 /*0x3*/
}CM_SHARE_DISPOSITION, *PCM_SHARE_DISPOSITION;

