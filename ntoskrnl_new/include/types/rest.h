

typedef struct _ASSEMBLY_STORAGE_MAP // 0 elements, 0x0 bytes (sizeof)
{
}ASSEMBLY_STORAGE_MAP, *PASSEMBLY_STORAGE_MAP;

          typedef struct _BITMAP_RANGE      // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Links;     // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     INT64        BasePage;
/*0x018*/     ULONG32      FirstDirtyPage;
/*0x01C*/     ULONG32      LastDirtyPage;
/*0x020*/     ULONG32      DirtyPages;
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     ULONG32*     Bitmap;
          }BITMAP_RANGE, *PBITMAP_RANGE;

          typedef struct _BLOB                         // 7 elements, 0x20 bytes (sizeof)
          {
              union                                    // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         struct _LIST_ENTRY ResourceList;     // 2 elements, 0x10 bytes (sizeof)
/*0x000*/         struct _SLIST_ENTRY FreeListEntry;   // 1 elements, 0x10 bytes (sizeof)
              };
              union                                    // 2 elements, 0x1 bytes (sizeof)
              {
                  struct                               // 4 elements, 0x1 bytes (sizeof)
                  {
/*0x010*/             UINT8        ReferenceCache : 1; // 0 BitPosition
/*0x010*/             UINT8        Lookaside : 1;      // 1 BitPosition
/*0x010*/             UINT8        Initializing : 1;   // 2 BitPosition
/*0x010*/             UINT8        Deleted : 1;        // 3 BitPosition
                  }s1;
/*0x010*/         UINT8        Flags;
              }u1;
/*0x011*/     UINT8        ResourceId;
/*0x012*/     INT16        CachedReferences;
/*0x014*/     LONG32       ReferenceCount;
/*0x018*/     struct _EX_PUSH_LOCK Lock;               // 7 elements, 0x8 bytes (sizeof)
          }BLOB, *PBLOB;

          typedef struct _BLOB_COUNTERS    // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      CreatedObjects;
/*0x004*/     ULONG32      DeletedObjects;
          }BLOB_COUNTERS, *PBLOB_COUNTERS;

          typedef struct _BLOB_TYPE                                                                                                                                                                                                               // 8 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     enum _BLOB_ID ResourceId;
/*0x004*/     ULONG32      PoolTag;
/*0x008*/     ULONG32      LookasideIndex;
/*0x00C*/     ULONG32      Flags;
/*0x010*/     struct _BLOB_COUNTERS* Counters;
/*0x018*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* DeleteProcedure;
/*0x020*/     FUNCT_0064_1AF5_DestroyProcedure* DestroyProcedure;
/*0x028*/     UINT64       UsualSize;
          }BLOB_TYPE, *PBLOB_TYPE;

          typedef struct _CALL_HASH_ENTRY   // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     VOID*        CallersAddress;
/*0x018*/     VOID*        CallersCaller;
/*0x020*/     ULONG32      CallCount;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }CALL_HASH_ENTRY, *PCALL_HASH_ENTRY;

          typedef struct _CALL_PERFORMANCE_DATA // 2 elements, 0x408 bytes (sizeof)
          {
/*0x000*/     UINT64       SpinLock;
/*0x008*/     struct _LIST_ENTRY HashTable[64];
          }CALL_PERFORMANCE_DATA, *PCALL_PERFORMANCE_DATA;

typedef struct _CALLBACK_OBJECT // 0 elements, 0x0 bytes (sizeof)
{
}CALLBACK_OBJECT, *PCALLBACK_OBJECT;

          typedef struct _CHILD_LIST // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     ULONG32      List;
          }CHILD_LIST, *PCHILD_LIST;

          typedef union _CLS_LSN             // 2 elements, 0x8 bytes (sizeof)
          {
              struct                         // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT32       idxRecord;
/*0x004*/         ULONG32      cidContainer;
              }offset;
/*0x000*/     UINT64       ullOffset;
          }CLS_LSN, *PCLS_LSN;

          typedef struct _COMPRESSED_DATA_INFO         // 7 elements, 0xC bytes (sizeof)
          {
/*0x000*/     UINT16       CompressionFormatAndEngine;
/*0x002*/     UINT8        CompressionUnitShift;
/*0x003*/     UINT8        ChunkShift;
/*0x004*/     UINT8        ClusterShift;
/*0x005*/     UINT8        Reserved;
/*0x006*/     UINT16       NumberOfChunks;
/*0x008*/     ULONG32      CompressedChunkSizes[1];
          }COMPRESSED_DATA_INFO, *PCOMPRESSED_DATA_INFO;

          typedef struct _COUNTER_READING       // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     enum _HARDWARE_COUNTER_TYPE Type;
/*0x004*/     ULONG32      Index;
/*0x008*/     UINT64       Start;
/*0x010*/     UINT64       Total;
          }COUNTER_READING, *PCOUNTER_READING;

          typedef struct _CURDIR              // 2 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _UNICODE_STRING DosPath; // 3 elements, 0x10 bytes (sizeof)
/*0x010*/     VOID*        Handle;
          }CURDIR, *PCURDIR;

          typedef union _CVDD         // 3 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x000*/     struct _NB10 NB10;      // 5 elements, 0x14 bytes (sizeof)
/*0x000*/     struct _RSDS RsDs;      // 4 elements, 0x1C bytes (sizeof)
          }CVDD, *PCVDD;

          typedef struct _DEFERRED_WRITE                                                                   // 9 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     INT16        NodeTypeCode;
/*0x002*/     INT16        NodeByteSize;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _FILE_OBJECT* FileObject;
/*0x010*/     ULONG32      BytesToWrite;
/*0x014*/     UINT8        _PADDING1_[0x4];
/*0x018*/     struct _LIST_ENTRY DeferredWriteLinks;                                                       // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _KEVENT* Event;
/*0x030*/     FUNCT_00AE_00AD_CleanupGroupCancelCallback_DeRefSecurityDescriptor_PostRoutine* PostRoutine;
/*0x038*/     VOID*        Context1;
/*0x040*/     VOID*        Context2;
          }DEFERRED_WRITE, *PDEFERRED_WRITE;

          typedef struct _DIAGNOSTIC_BUFFER                 // 8 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       Size;
/*0x008*/     enum _REQUESTER_TYPE CallerType;
/*0x00C*/     UINT8        _PADDING0_[0x4];
              union                                         // 2 elements, 0x10 bytes (sizeof)
              {
                  struct                                    // 3 elements, 0x10 bytes (sizeof)
                  {
/*0x010*/             UINT64       ProcessImageNameOffset;
/*0x018*/             ULONG32      ProcessId;
/*0x01C*/             ULONG32      ServiceTag;
                  };
                  struct                                    // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x010*/             UINT64       DeviceDescriptionOffset;
/*0x018*/             UINT64       DevicePathOffset;
                  };
              };
/*0x020*/     UINT64       ReasonOffset;
          }DIAGNOSTIC_BUFFER, *PDIAGNOSTIC_BUFFER;

          typedef struct _DIAGNOSTIC_CONTEXT           // 5 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     enum _REQUESTER_TYPE CallerType;
/*0x004*/     UINT8        _PADDING0_[0x4];
              union                                    // 2 elements, 0x10 bytes (sizeof)
              {
                  struct                               // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             struct _EPROCESS* Process;
/*0x010*/             ULONG32      ServiceTag;
/*0x014*/             UINT8        _PADDING1_[0x4];
                  };
/*0x008*/         struct _DEVICE_OBJECT* DeviceObject;
              };
/*0x018*/     UINT64       ReasonSize;
          }DIAGNOSTIC_CONTEXT, *PDIAGNOSTIC_CONTEXT;

          typedef struct _DUAL                      // 7 elements, 0x278 bytes (sizeof)
          {
/*0x000*/     ULONG32      Length;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _HMAP_DIRECTORY* Map;
/*0x010*/     struct _HMAP_TABLE* SmallDir;
/*0x018*/     ULONG32      Guard;
/*0x01C*/     UINT8        _PADDING1_[0x4];
/*0x020*/     struct _FREE_DISPLAY FreeDisplay[24];
/*0x260*/     struct _LIST_ENTRY FreeBins;          // 2 elements, 0x10 bytes (sizeof)
/*0x270*/     ULONG32      FreeSummary;
/*0x274*/     UINT8        _PADDING2_[0x4];
          }DUAL, *PDUAL;

          typedef struct _DUMMY_FILE_OBJECT       // 2 elements, 0x110 bytes (sizeof)
          {
/*0x000*/     struct _OBJECT_HEADER ObjectHeader; // 13 elements, 0x38 bytes (sizeof)
/*0x038*/     CHAR         FileObjectBody[216];
          }DUMMY_FILE_OBJECT, *PDUMMY_FILE_OBJECT;

          typedef struct _DUMP_INITIALIZATION_CONTEXT                                              // 24 elements, 0x100 bytes (sizeof)
          {
/*0x000*/     ULONG32      Length;
/*0x004*/     ULONG32      Reserved;
/*0x008*/     VOID*        MemoryBlock;
/*0x010*/     VOID*        CommonBuffer[2];
/*0x020*/     union _LARGE_INTEGER PhysicalAddress[2];
/*0x030*/     FUNCT_00AE_084F_BoostPolicyHandler_StallRoutine* StallRoutine;
/*0x038*/     FUNCT_006E_29C5_OpenRoutine* OpenRoutine;
/*0x040*/     FUNCT_0064_29C8_WriteRoutine* WriteRoutine;
/*0x048*/     FUNCT_00AE_0282_PostProcessInitRoutine_DispatchAddress_FinishRoutine* FinishRoutine;
/*0x050*/     struct _ADAPTER_OBJECT* AdapterObject;
/*0x058*/     VOID*        MappedRegisterBase;
/*0x060*/     VOID*        PortConfiguration;
/*0x068*/     UINT8        CrashDump;
/*0x069*/     UINT8        _PADDING0_[0x3];
/*0x06C*/     ULONG32      MaximumTransferSize;
/*0x070*/     ULONG32      CommonBufferSize;
/*0x074*/     UINT8        _PADDING1_[0x4];
/*0x078*/     VOID*        TargetAddress;
/*0x080*/     FUNCT_0064_29CE_WritePendingRoutine* WritePendingRoutine;
/*0x088*/     ULONG32      PartitionStyle;
              union                                                                                // 2 elements, 0x10 bytes (sizeof)
              {
                  struct                                                                           // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x08C*/             ULONG32      Signature;
/*0x090*/             ULONG32      CheckSum;
                  }Mbr;
                  struct                                                                           // 1 elements, 0x10 bytes (sizeof)
                  {
/*0x08C*/             struct _GUID DiskId;                                                         // 4 elements, 0x10 bytes (sizeof)
                  }Gpt;
              }DiskInfo;
/*0x0A0*/     FUNCT_0064_29DC_ReadRoutine* ReadRoutine;
/*0x0A8*/     FUNCT_0064_29E1_GetDriveTelemetryRoutine* GetDriveTelemetryRoutine;
/*0x0B0*/     ULONG32      LogSectionTruncateSize;
/*0x0B4*/     ULONG32      Parameters[16];
/*0x0F4*/     UINT8        _PADDING2_[0x4];
/*0x0F8*/     FUNCT_00AE_29E7_GetTransferSizesRoutine* GetTransferSizesRoutine;
          }DUMP_INITIALIZATION_CONTEXT, *PDUMP_INITIALIZATION_CONTEXT;

          typedef struct _DUMP_STACK_CONTEXT                  // 11 elements, 0x170 bytes (sizeof)
          {
/*0x000*/     struct _DUMP_INITIALIZATION_CONTEXT Init;       // 24 elements, 0x100 bytes (sizeof)
/*0x100*/     union _LARGE_INTEGER PartitionOffset;           // 4 elements, 0x8 bytes (sizeof)
/*0x108*/     VOID*        DumpPointers;
/*0x110*/     ULONG32      PointersLength;
/*0x114*/     UINT8        _PADDING0_[0x4];
/*0x118*/     UINT16*      ModulePrefix;
/*0x120*/     struct _LIST_ENTRY DriverList;                  // 2 elements, 0x10 bytes (sizeof)
/*0x130*/     struct _STRING InitMsg;                         // 3 elements, 0x10 bytes (sizeof)
/*0x140*/     struct _STRING ProgMsg;                         // 3 elements, 0x10 bytes (sizeof)
/*0x150*/     struct _STRING DoneMsg;                         // 3 elements, 0x10 bytes (sizeof)
/*0x160*/     VOID*        FileObject;
/*0x168*/     enum _DEVICE_USAGE_NOTIFICATION_TYPE UsageType;
/*0x16C*/     UINT8        _PADDING1_[0x4];
          }DUMP_STACK_CONTEXT, *PDUMP_STACK_CONTEXT;

          typedef struct _ECP_LIST        // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     ULONG32      Flags;
/*0x008*/     struct _LIST_ENTRY EcpList; // 2 elements, 0x10 bytes (sizeof)
          }ECP_LIST, *PECP_LIST;

          typedef struct _ENTROPY_TIMING_STATE // 7 elements, 0x180 bytes (sizeof)
          {
/*0x000*/     ULONG32      CpuNumber;
/*0x004*/     ULONG32      Count;
/*0x008*/     ULONG32      NextDpcCount;
/*0x00C*/     LONG32       DpcInProgress;
/*0x010*/     UINT64*      RawDataBuffer;
/*0x018*/     struct _KDPC Dpc;                // 9 elements, 0x40 bytes (sizeof)
/*0x058*/     UINT8        _PADDING0_[0x28];
/*0x080*/     UINT64       Buffer[32];
          }ENTROPY_TIMING_STATE, *PENTROPY_TIMING_STATE;

          typedef struct _EVENT_DATA_DESCRIPTOR // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Ptr;
/*0x008*/     ULONG32      Size;
/*0x00C*/     ULONG32      Reserved;
          }EVENT_DATA_DESCRIPTOR, *PEVENT_DATA_DESCRIPTOR;

          typedef struct _EVENT_DESCRIPTOR // 7 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Id;
/*0x002*/     UINT8        Version;
/*0x003*/     UINT8        Channel;
/*0x004*/     UINT8        Level;
/*0x005*/     UINT8        Opcode;
/*0x006*/     UINT16       Task;
/*0x008*/     UINT64       Keyword;
          }EVENT_DESCRIPTOR, *PEVENT_DESCRIPTOR;

          typedef struct _EVENT_FILTER_DESCRIPTOR // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Ptr;
/*0x008*/     ULONG32      Size;
/*0x00C*/     ULONG32      Type;
          }EVENT_FILTER_DESCRIPTOR, *PEVENT_FILTER_DESCRIPTOR;

          typedef struct _EVENT_FILTER_HEADER // 6 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT16       Id;
/*0x002*/     UINT8        Version;
/*0x003*/     UINT8        Reserved[5];
/*0x008*/     UINT64       InstanceId;
/*0x010*/     ULONG32      Size;
/*0x014*/     ULONG32      NextOffset;
          }EVENT_FILTER_HEADER, *PEVENT_FILTER_HEADER;

          typedef struct _EVENT_HEADER                  // 13 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     UINT16       Size;
/*0x002*/     UINT16       HeaderType;
/*0x004*/     UINT16       Flags;
/*0x006*/     UINT16       EventProperty;
/*0x008*/     ULONG32      ThreadId;
/*0x00C*/     ULONG32      ProcessId;
/*0x010*/     union _LARGE_INTEGER TimeStamp;           // 4 elements, 0x8 bytes (sizeof)
/*0x018*/     struct _GUID ProviderId;                  // 4 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _EVENT_DESCRIPTOR EventDescriptor; // 7 elements, 0x10 bytes (sizeof)
              union                                     // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                                // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x038*/             ULONG32      KernelTime;
/*0x03C*/             ULONG32      UserTime;
                  };
/*0x038*/         UINT64       ProcessorTime;
              };
/*0x040*/     struct _GUID ActivityId;                  // 4 elements, 0x10 bytes (sizeof)
          }EVENT_HEADER, *PEVENT_HEADER;

          typedef struct _EVENT_HEADER_EXTENDED_DATA_ITEM // 6 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Reserved1;
/*0x002*/     UINT16       ExtType;
              struct                                      // 2 elements, 0x2 bytes (sizeof)
              {
/*0x004*/         UINT16       Linkage : 1;               // 0 BitPosition
/*0x004*/         UINT16       Reserved2 : 15;            // 1 BitPosition
              };
/*0x006*/     UINT16       DataSize;
/*0x008*/     UINT64       DataPtr;
          }EVENT_HEADER_EXTENDED_DATA_ITEM, *PEVENT_HEADER_EXTENDED_DATA_ITEM;

          typedef struct _EVENT_RECORD                               // 7 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     struct _EVENT_HEADER EventHeader;                      // 13 elements, 0x50 bytes (sizeof)
/*0x050*/     struct _ETW_BUFFER_CONTEXT BufferContext;              // 4 elements, 0x4 bytes (sizeof)
/*0x054*/     UINT16       ExtendedDataCount;
/*0x056*/     UINT16       UserDataLength;
/*0x058*/     struct _EVENT_HEADER_EXTENDED_DATA_ITEM* ExtendedData;
/*0x060*/     VOID*        UserData;
/*0x068*/     VOID*        UserContext;
          }EVENT_RECORD, *PEVENT_RECORD;

          typedef struct _FILE_BASIC_INFORMATION   // 5 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     union _LARGE_INTEGER CreationTime;   // 4 elements, 0x8 bytes (sizeof)
/*0x008*/     union _LARGE_INTEGER LastAccessTime; // 4 elements, 0x8 bytes (sizeof)
/*0x010*/     union _LARGE_INTEGER LastWriteTime;  // 4 elements, 0x8 bytes (sizeof)
/*0x018*/     union _LARGE_INTEGER ChangeTime;     // 4 elements, 0x8 bytes (sizeof)
/*0x020*/     ULONG32      FileAttributes;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

          typedef struct _FILE_GET_QUOTA_INFORMATION // 3 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     ULONG32      NextEntryOffset;
/*0x004*/     ULONG32      SidLength;
/*0x008*/     struct _SID  Sid;                      // 4 elements, 0xC bytes (sizeof)
          }FILE_GET_QUOTA_INFORMATION, *PFILE_GET_QUOTA_INFORMATION;

          typedef struct _FILE_NETWORK_OPEN_INFORMATION // 7 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     union _LARGE_INTEGER CreationTime;        // 4 elements, 0x8 bytes (sizeof)
/*0x008*/     union _LARGE_INTEGER LastAccessTime;      // 4 elements, 0x8 bytes (sizeof)
/*0x010*/     union _LARGE_INTEGER LastWriteTime;       // 4 elements, 0x8 bytes (sizeof)
/*0x018*/     union _LARGE_INTEGER ChangeTime;          // 4 elements, 0x8 bytes (sizeof)
/*0x020*/     union _LARGE_INTEGER AllocationSize;      // 4 elements, 0x8 bytes (sizeof)
/*0x028*/     union _LARGE_INTEGER EndOfFile;           // 4 elements, 0x8 bytes (sizeof)
/*0x030*/     ULONG32      FileAttributes;
/*0x034*/     UINT8        _PADDING0_[0x4];
          }FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;

          typedef struct _flags                      // 5 elements, 0x1 bytes (sizeof)
          {
/*0x000*/     UINT8        Removable : 1;            // 0 BitPosition
/*0x000*/     UINT8        GroupAssigned : 1;        // 1 BitPosition
/*0x000*/     UINT8        GroupCommitted : 1;       // 2 BitPosition
/*0x000*/     UINT8        GroupAssignmentFixed : 1; // 3 BitPosition
/*0x000*/     UINT8        Fill : 4;                 // 4 BitPosition
          }flags, *Pflags;

typedef struct _FLS_CALLBACK_INFO // 0 elements, 0x0 bytes (sizeof)
{
}FLS_CALLBACK_INFO, *PFLS_CALLBACK_INFO;

          typedef struct _FREE_DISPLAY     // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      RealVectorSize;
/*0x004*/     ULONG32      Hint;
/*0x008*/     struct _RTL_BITMAP Display;  // 2 elements, 0x10 bytes (sizeof)
          }FREE_DISPLAY, *PFREE_DISPLAY;

          typedef struct _GDI_TEB_BATCH     // 3 elements, 0x4E8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Offset;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT64       HDC;
/*0x010*/     ULONG32      Buffer[310];
          }GDI_TEB_BATCH, *PGDI_TEB_BATCH;

          typedef struct _GDI_TEB_BATCH32 // 3 elements, 0x4E0 bytes (sizeof)
          {
/*0x000*/     ULONG32      Offset;
/*0x004*/     ULONG32      HDC;
/*0x008*/     ULONG32      Buffer[310];
          }GDI_TEB_BATCH32, *PGDI_TEB_BATCH32;

          typedef struct _GDI_TEB_BATCH64   // 3 elements, 0x4E8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Offset;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT64       HDC;
/*0x010*/     ULONG32      Buffer[310];
          }GDI_TEB_BATCH64, *PGDI_TEB_BATCH64;

          typedef struct _GUID       // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Data1;
/*0x004*/     UINT16       Data2;
/*0x006*/     UINT16       Data3;
/*0x008*/     UINT8        Data4[8];
          }GUID, *PGUID;

typedef struct _HAL_PMC_COUNTERS // 0 elements, 0x0 bytes (sizeof)
{
}HAL_PMC_COUNTERS, *PHAL_PMC_COUNTERS;


          typedef struct _HMAP_DIRECTORY           // 1 elements, 0x2000 bytes (sizeof)
          {
/*0x000*/     struct _HMAP_TABLE* Directory[1024];
          }HMAP_DIRECTORY, *PHMAP_DIRECTORY;

          typedef struct _HMAP_ENTRY        // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT64       BlockAddress;
/*0x008*/     UINT64       BinAddress;
/*0x010*/     ULONG32      MemAlloc;
/*0x014*/     UINT8        _PADDING0_[0x4];
          }HMAP_ENTRY, *PHMAP_ENTRY;

          typedef struct _HMAP_TABLE         // 1 elements, 0x3000 bytes (sizeof)
          {
/*0x000*/     struct _HMAP_ENTRY Table[512];
          }HMAP_TABLE, *PHMAP_TABLE;

          typedef struct _iobuf             // 8 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     CHAR*        _ptr;
/*0x008*/     INT32        _cnt;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     CHAR*        _base;
/*0x018*/     INT32        _flag;
/*0x01C*/     INT32        _file;
/*0x020*/     INT32        _charbuf;
/*0x024*/     INT32        _bufsiz;
/*0x028*/     CHAR*        _tmpfname;
          }iobuf, *Piobuf;

          typedef struct _KTM                                   // 33 elements, 0x3C0 bytes (sizeof)
          {
/*0x000*/     ULONG32      cookie;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _KMUTANT Mutex;                            // 5 elements, 0x38 bytes (sizeof)
/*0x040*/     enum _KTM_STATE State;
/*0x044*/     UINT8        _PADDING1_[0x4];
/*0x048*/     struct _KTMOBJECT_NAMESPACE_LINK NamespaceLink;   // 2 elements, 0x28 bytes (sizeof)
/*0x070*/     struct _GUID TmIdentity;                          // 4 elements, 0x10 bytes (sizeof)
/*0x080*/     ULONG32      Flags;
/*0x084*/     ULONG32      VolatileFlags;
/*0x088*/     struct _UNICODE_STRING LogFileName;               // 3 elements, 0x10 bytes (sizeof)
/*0x098*/     struct _FILE_OBJECT* LogFileObject;
/*0x0A0*/     VOID*        MarshallingContext;
/*0x0A8*/     VOID*        LogManagementContext;
/*0x0B0*/     struct _KTMOBJECT_NAMESPACE Transactions;         // 5 elements, 0xA8 bytes (sizeof)
/*0x158*/     struct _KTMOBJECT_NAMESPACE ResourceManagers;     // 5 elements, 0xA8 bytes (sizeof)
/*0x200*/     struct _KMUTANT LsnOrderedMutex;                  // 5 elements, 0x38 bytes (sizeof)
/*0x238*/     struct _LIST_ENTRY LsnOrderedList;                // 2 elements, 0x10 bytes (sizeof)
/*0x248*/     union _LARGE_INTEGER CommitVirtualClock;          // 4 elements, 0x8 bytes (sizeof)
/*0x250*/     struct _FAST_MUTEX CommitVirtualClockMutex;       // 5 elements, 0x38 bytes (sizeof)
/*0x288*/     union _CLS_LSN BaseLsn;                           // 2 elements, 0x8 bytes (sizeof)
/*0x290*/     union _CLS_LSN CurrentReadLsn;                    // 2 elements, 0x8 bytes (sizeof)
/*0x298*/     union _CLS_LSN LastRecoveredLsn;                  // 2 elements, 0x8 bytes (sizeof)
/*0x2A0*/     VOID*        TmRmHandle;
/*0x2A8*/     struct _KRESOURCEMANAGER* TmRm;
/*0x2B0*/     struct _KEVENT LogFullNotifyEvent;                // 1 elements, 0x18 bytes (sizeof)
/*0x2C8*/     struct _WORK_QUEUE_ITEM CheckpointWorkItem;       // 3 elements, 0x20 bytes (sizeof)
/*0x2E8*/     union _CLS_LSN CheckpointTargetLsn;               // 2 elements, 0x8 bytes (sizeof)
/*0x2F0*/     struct _WORK_QUEUE_ITEM LogFullCompletedWorkItem; // 3 elements, 0x20 bytes (sizeof)
/*0x310*/     struct _ERESOURCE LogWriteResource;               // 17 elements, 0x68 bytes (sizeof)
/*0x378*/     ULONG32      LogFlags;
/*0x37C*/     LONG32       LogFullStatus;
/*0x380*/     LONG32       RecoveryStatus;
/*0x384*/     UINT8        _PADDING2_[0x4];
/*0x388*/     union _CLS_LSN LastCheckBaseLsn;                  // 2 elements, 0x8 bytes (sizeof)
/*0x390*/     struct _LIST_ENTRY RestartOrderedList;            // 2 elements, 0x10 bytes (sizeof)
/*0x3A0*/     struct _WORK_QUEUE_ITEM OfflineWorkItem;          // 3 elements, 0x20 bytes (sizeof)
          }KTM, *PKTM;

typedef struct _KTMNOTIFICATION_PACKET // 0 elements, 0x0 bytes (sizeof)
{
}KTMNOTIFICATION_PACKET, *PKTMNOTIFICATION_PACKET;

          typedef struct _KTMOBJECT_NAMESPACE // 5 elements, 0xA8 bytes (sizeof)
          {
/*0x000*/     struct _RTL_AVL_TABLE Table;    // 11 elements, 0x68 bytes (sizeof)
/*0x068*/     struct _KMUTANT Mutex;          // 5 elements, 0x38 bytes (sizeof)
/*0x0A0*/     UINT16       LinksOffset;
/*0x0A2*/     UINT16       GuidOffset;
/*0x0A4*/     UINT8        Expired;
/*0x0A5*/     UINT8        _PADDING0_[0x3];
          }KTMOBJECT_NAMESPACE, *PKTMOBJECT_NAMESPACE;

          typedef struct _KTMOBJECT_NAMESPACE_LINK // 2 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _RTL_BALANCED_LINKS Links;    // 5 elements, 0x20 bytes (sizeof)
/*0x020*/     UINT8        Expired;
/*0x021*/     UINT8        _PADDING0_[0x7];
          }KTMOBJECT_NAMESPACE_LINK, *PKTMOBJECT_NAMESPACE_LINK;

          typedef struct _KTRANSACTION                              // 41 elements, 0x2D8 bytes (sizeof)
          {
/*0x000*/     struct _KEVENT OutcomeEvent;                          // 1 elements, 0x18 bytes (sizeof)
/*0x018*/     ULONG32      cookie;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     struct _KMUTANT Mutex;                                // 5 elements, 0x38 bytes (sizeof)
/*0x058*/     struct _KTRANSACTION* TreeTx;
/*0x060*/     struct _KTMOBJECT_NAMESPACE_LINK GlobalNamespaceLink; // 2 elements, 0x28 bytes (sizeof)
/*0x088*/     struct _KTMOBJECT_NAMESPACE_LINK TmNamespaceLink;     // 2 elements, 0x28 bytes (sizeof)
/*0x0B0*/     struct _GUID UOW;                                     // 4 elements, 0x10 bytes (sizeof)
/*0x0C0*/     enum _KTRANSACTION_STATE State;
/*0x0C4*/     ULONG32      Flags;
/*0x0C8*/     struct _LIST_ENTRY EnlistmentHead;                    // 2 elements, 0x10 bytes (sizeof)
/*0x0D8*/     ULONG32      EnlistmentCount;
/*0x0DC*/     ULONG32      RecoverableEnlistmentCount;
/*0x0E0*/     ULONG32      PrePrepareRequiredEnlistmentCount;
/*0x0E4*/     ULONG32      PrepareRequiredEnlistmentCount;
/*0x0E8*/     ULONG32      OutcomeRequiredEnlistmentCount;
/*0x0EC*/     ULONG32      PendingResponses;
/*0x0F0*/     struct _KENLISTMENT* SuperiorEnlistment;
/*0x0F8*/     union _CLS_LSN LastLsn;                               // 2 elements, 0x8 bytes (sizeof)
/*0x100*/     struct _LIST_ENTRY PromotedEntry;                     // 2 elements, 0x10 bytes (sizeof)
/*0x110*/     struct _KTRANSACTION* PromoterTransaction;
/*0x118*/     VOID*        PromotePropagation;
/*0x120*/     ULONG32      IsolationLevel;
/*0x124*/     ULONG32      IsolationFlags;
/*0x128*/     union _LARGE_INTEGER Timeout;                         // 4 elements, 0x8 bytes (sizeof)
/*0x130*/     struct _UNICODE_STRING Description;                   // 3 elements, 0x10 bytes (sizeof)
/*0x140*/     struct _KTHREAD* RollbackThread;
/*0x148*/     struct _WORK_QUEUE_ITEM RollbackWorkItem;             // 3 elements, 0x20 bytes (sizeof)
/*0x168*/     struct _KDPC RollbackDpc;                             // 9 elements, 0x40 bytes (sizeof)
/*0x1A8*/     struct _KTIMER RollbackTimer;                         // 6 elements, 0x40 bytes (sizeof)
/*0x1E8*/     struct _LIST_ENTRY LsnOrderedEntry;                   // 2 elements, 0x10 bytes (sizeof)
/*0x1F8*/     enum _KTRANSACTION_OUTCOME Outcome;
/*0x1FC*/     UINT8        _PADDING1_[0x4];
/*0x200*/     struct _KTM* Tm;
/*0x208*/     INT64        CommitReservation;
/*0x210*/     struct _KTRANSACTION_HISTORY TransactionHistory[10];
/*0x260*/     ULONG32      TransactionHistoryCount;
/*0x264*/     UINT8        _PADDING2_[0x4];
/*0x268*/     VOID*        DTCPrivateInformation;
/*0x270*/     ULONG32      DTCPrivateInformationLength;
/*0x274*/     UINT8        _PADDING3_[0x4];
/*0x278*/     struct _KMUTANT DTCPrivateInformationMutex;           // 5 elements, 0x38 bytes (sizeof)
/*0x2B0*/     VOID*        PromotedTxSelfHandle;
/*0x2B8*/     ULONG32      PendingPromotionCount;
/*0x2BC*/     UINT8        _PADDING4_[0x4];
/*0x2C0*/     struct _KEVENT PromotionCompletedEvent;               // 1 elements, 0x18 bytes (sizeof)
          }KTRANSACTION, *PKTRANSACTION;

          typedef struct _KTRANSACTION_HISTORY                                 // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     enum ___2011110910380E024B8CE6D17A03D5CB0_RecordType RecordType;
/*0x004*/     ULONG32      Payload;
          }KTRANSACTION_HISTORY, *PKTRANSACTION_HISTORY;


          typedef struct _LAZY_WRITER            // 8 elements, 0x88 bytes (sizeof)
          {
/*0x000*/     struct _KDPC ScanDpc;              // 9 elements, 0x40 bytes (sizeof)
/*0x040*/     struct _KTIMER ScanTimer;          // 6 elements, 0x40 bytes (sizeof)
/*0x080*/     UINT8        ScanActive;
/*0x081*/     UINT8        OtherWork;
/*0x082*/     UINT8        PendingTeardownScan;
/*0x083*/     UINT8        PendingPeriodicScan;
/*0x084*/     UINT8        PendingLowMemoryScan;
/*0x085*/     UINT8        PendingPowerScan;
/*0x086*/     UINT8        _PADDING0_[0x2];
          }LAZY_WRITER, *PLAZY_WRITER;

          typedef struct _LOG_HANDLE_CONTEXT                                        // 11 elements, 0x78 bytes (sizeof)
          {
/*0x000*/     VOID*        LogHandle;
/*0x008*/     FUNCT_00AE_1924_FlushToLsnRoutine* FlushToLsnRoutine;
/*0x010*/     FUNCT_00AE_1928_QueryLogHandleInfoRoutine* QueryLogHandleInfoRoutine;
/*0x018*/     struct _DIRTY_PAGE_STATISTICS DirtyPageStatistics;                    // 3 elements, 0x18 bytes (sizeof)
/*0x030*/     struct _DIRTY_PAGE_THRESHOLDS DirtyPageThresholds;                    // 4 elements, 0x20 bytes (sizeof)
/*0x050*/     ULONG32      AdditionalPagesToWrite;
/*0x054*/     ULONG32      CcLWScanDPThreshold;
/*0x058*/     union _LARGE_INTEGER LargestLsnForCurrentLWScan;                      // 4 elements, 0x8 bytes (sizeof)
/*0x060*/     UINT64       LargestLsnFileObjectKey;
/*0x068*/     union _LARGE_INTEGER LastLWTimeStamp;                                 // 4 elements, 0x8 bytes (sizeof)
/*0x070*/     ULONG32      Flags;
/*0x074*/     UINT8        _PADDING0_[0x4];
          }LOG_HANDLE_CONTEXT, *PLOG_HANDLE_CONTEXT;

          typedef struct _LOGGED_STREAM_CALLBACK_V1                 // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        LogHandle;
/*0x008*/     FUNCT_00AE_1924_FlushToLsnRoutine* FlushToLsnRoutine;
          }LOGGED_STREAM_CALLBACK_V1, *PLOGGED_STREAM_CALLBACK_V1;

          typedef struct _LOGGED_STREAM_CALLBACK_V2         // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _LOG_HANDLE_CONTEXT* LogHandleContext;
          }LOGGED_STREAM_CALLBACK_V2, *PLOGGED_STREAM_CALLBACK_V2;

          typedef struct _LUID_AND_ATTRIBUTES // 2 elements, 0xC bytes (sizeof)
          {
/*0x000*/     struct _LUID Luid;              // 2 elements, 0x8 bytes (sizeof)
/*0x008*/     ULONG32      Attributes;
          }LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;

          typedef struct _MAILSLOT_CREATE_PARAMETERS // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      MailslotQuota;
/*0x004*/     ULONG32      MaximumMessageSize;
/*0x008*/     union _LARGE_INTEGER ReadTimeout;      // 4 elements, 0x8 bytes (sizeof)
/*0x010*/     UINT8        TimeoutSpecified;
/*0x011*/     UINT8        _PADDING0_[0x7];
          }MAILSLOT_CREATE_PARAMETERS, *PMAILSLOT_CREATE_PARAMETERS;


          typedef struct _MBCB                      // 11 elements, 0xC0 bytes (sizeof)
          {
/*0x000*/     INT16        NodeTypeCode;
/*0x002*/     INT16        NodeIsInZone;
/*0x004*/     ULONG32      PagesToWrite;
/*0x008*/     ULONG32      DirtyPages;
/*0x00C*/     ULONG32      Reserved;
/*0x010*/     struct _LIST_ENTRY BitmapRanges;      // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     INT64        ResumeWritePage;
/*0x028*/     INT64        MostRecentlyDirtiedPage;
/*0x030*/     struct _BITMAP_RANGE BitmapRange1;    // 6 elements, 0x30 bytes (sizeof)
/*0x060*/     struct _BITMAP_RANGE BitmapRange2;    // 6 elements, 0x30 bytes (sizeof)
/*0x090*/     struct _BITMAP_RANGE BitmapRange3;    // 6 elements, 0x30 bytes (sizeof)
          }MBCB, *PMBCB;

          typedef struct _MCGEN_TRACE_CONTEXT  // 12 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     UINT64       RegistrationHandle;
/*0x008*/     UINT64       Logger;
/*0x010*/     UINT64       MatchAnyKeyword;
/*0x018*/     UINT64       MatchAllKeyword;
/*0x020*/     ULONG32      Flags;
/*0x024*/     ULONG32      IsEnabled;
/*0x028*/     UINT8        Level;
/*0x029*/     UINT8        Reserve;
/*0x02A*/     UINT16       EnableBitsCount;
/*0x02C*/     UINT8        _PADDING0_[0x4];
/*0x030*/     ULONG32*     EnableBitMask;
/*0x038*/     UINT64*      EnableKeyWords;
/*0x040*/     UINT8*       EnableLevel;
          }MCGEN_TRACE_CONTEXT, *PMCGEN_TRACE_CONTEXT;


          typedef struct _MODWRITER_FLAGS   // 3 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      KeepForever : 1; // 0 BitPosition
/*0x000*/     ULONG32      Networked : 1;   // 1 BitPosition
/*0x000*/     ULONG32      IoPriority : 3;  // 2 BitPosition
          }MODWRITER_FLAGS, *PMODWRITER_FLAGS;

          typedef struct _NAMED_PIPE_CREATE_PARAMETERS // 8 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     ULONG32      NamedPipeType;
/*0x004*/     ULONG32      ReadMode;
/*0x008*/     ULONG32      CompletionMode;
/*0x00C*/     ULONG32      MaximumInstances;
/*0x010*/     ULONG32      InboundQuota;
/*0x014*/     ULONG32      OutboundQuota;
/*0x018*/     union _LARGE_INTEGER DefaultTimeout;     // 4 elements, 0x8 bytes (sizeof)
/*0x020*/     UINT8        TimeoutSpecified;
/*0x021*/     UINT8        _PADDING0_[0x7];
          }NAMED_PIPE_CREATE_PARAMETERS, *PNAMED_PIPE_CREATE_PARAMETERS;

          typedef struct _NB10              // 5 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     ULONG32      Offset;
/*0x008*/     ULONG32      TimeStamp;
/*0x00C*/     ULONG32      Age;
/*0x010*/     CHAR         PdbName[1];
/*0x011*/     UINT8        _PADDING0_[0x3];
          }NB10, *PNB10;

          typedef struct _NONOPAQUE_OPLOCK                // 11 elements, 0x88 bytes (sizeof)
          {
/*0x000*/     struct _IRP* IrpExclusiveOplock;
/*0x008*/     struct _FILE_OBJECT* FileObject;
/*0x010*/     struct _EPROCESS* ExclusiveOplockOwner;
/*0x018*/     struct _LIST_ENTRY IrpOplocksR;             // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _LIST_ENTRY IrpOplocksRH;            // 2 elements, 0x10 bytes (sizeof)
/*0x038*/     struct _LIST_ENTRY RHBreakQueue;            // 2 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _LIST_ENTRY WaitingIrps;             // 2 elements, 0x10 bytes (sizeof)
/*0x058*/     struct _LIST_ENTRY DelayAckFileObjectQueue; // 2 elements, 0x10 bytes (sizeof)
/*0x068*/     struct _LIST_ENTRY AtomicQueue;             // 2 elements, 0x10 bytes (sizeof)
/*0x078*/     ULONG32      OplockState;
/*0x07C*/     UINT8        _PADDING0_[0x4];
/*0x080*/     struct _FAST_MUTEX* FastMutex;
          }NONOPAQUE_OPLOCK, *PNONOPAQUE_OPLOCK;


typedef struct _PAGEFAULT_HISTORY // 0 elements, 0x0 bytes (sizeof)
{
}PAGEFAULT_HISTORY, *PPAGEFAULT_HISTORY;

          typedef struct _PEBS_DS_SAVE_AREA        // 12 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     UINT64       BtsBufferBase;
/*0x008*/     UINT64       BtsIndex;
/*0x010*/     UINT64       BtsAbsoluteMaximum;
/*0x018*/     UINT64       BtsInterruptThreshold;
/*0x020*/     UINT64       PebsBufferBase;
/*0x028*/     UINT64       PebsIndex;
/*0x030*/     UINT64       PebsAbsoluteMaximum;
/*0x038*/     UINT64       PebsInterruptThreshold;
/*0x040*/     UINT64       PebsCounterReset0;
/*0x048*/     UINT64       PebsCounterReset1;
/*0x050*/     UINT64       PebsCounterReset2;
/*0x058*/     UINT64       PebsCounterReset3;
          }PEBS_DS_SAVE_AREA, *PPEBS_DS_SAVE_AREA;

          typedef struct _PERFINFO_GROUPMASK // 1 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     ULONG32      Masks[8];
          }PERFINFO_GROUPMASK, *PPERFINFO_GROUPMASK;

          typedef struct _PF_KERNEL_GLOBALS           // 8 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     UINT64       AccessBufferAgeThreshold;
/*0x008*/     struct _EX_RUNDOWN_REF AccessBufferRef; // 2 elements, 0x8 bytes (sizeof)
/*0x010*/     struct _KEVENT AccessBufferExistsEvent; // 1 elements, 0x18 bytes (sizeof)
/*0x028*/     ULONG32      AccessBufferMax;
/*0x02C*/     UINT8        _PADDING0_[0x14];
/*0x040*/     union _SLIST_HEADER AccessBufferList;   // 4 elements, 0x10 bytes (sizeof)
/*0x050*/     LONG32       StreamSequenceNumber;
/*0x054*/     ULONG32      Flags;
/*0x058*/     LONG32       ScenarioPrefetchCount;
/*0x05C*/     UINT8        _PADDING1_[0x4];
          }PF_KERNEL_GLOBALS, *PPF_KERNEL_GLOBALS;

          typedef struct _PI_BUS_EXTENSION                // 17 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flags;
/*0x004*/     UINT8        NumberCSNs;
/*0x005*/     UINT8        _PADDING0_[0x3];
/*0x008*/     UINT8*       ReadDataPort;
/*0x010*/     UINT8        DataPortMapped;
/*0x011*/     UINT8        _PADDING1_[0x7];
/*0x018*/     UINT8*       AddressPort;
/*0x020*/     UINT8        AddrPortMapped;
/*0x021*/     UINT8        _PADDING2_[0x7];
/*0x028*/     UINT8*       CommandPort;
/*0x030*/     UINT8        CmdPortMapped;
/*0x031*/     UINT8        _PADDING3_[0x3];
/*0x034*/     ULONG32      NextSlotNumber;
/*0x038*/     struct _SINGLE_LIST_ENTRY DeviceList;       // 1 elements, 0x8 bytes (sizeof)
/*0x040*/     struct _SINGLE_LIST_ENTRY CardList;         // 1 elements, 0x8 bytes (sizeof)
/*0x048*/     struct _DEVICE_OBJECT* PhysicalBusDevice;
/*0x050*/     struct _DEVICE_OBJECT* FunctionalBusDevice;
/*0x058*/     struct _DEVICE_OBJECT* AttachedDevice;
/*0x060*/     ULONG32      BusNumber;
/*0x064*/     enum _SYSTEM_POWER_STATE SystemPowerState;
/*0x068*/     enum _DEVICE_POWER_STATE DevicePowerState;
/*0x06C*/     UINT8        _PADDING4_[0x4];
          }PI_BUS_EXTENSION, *PPI_BUS_EXTENSION;

          typedef struct _PI_RESOURCE_ARBITER_ENTRY        // 10 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY DeviceArbiterList;        // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT8        ResourceType;
/*0x011*/     UINT8        _PADDING0_[0x7];
/*0x018*/     struct _ARBITER_INTERFACE* ArbiterInterface;
/*0x020*/     struct _DEVICE_NODE* DeviceNode;
/*0x028*/     struct _LIST_ENTRY ResourceList;             // 2 elements, 0x10 bytes (sizeof)
/*0x038*/     struct _LIST_ENTRY BestResourceList;         // 2 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _LIST_ENTRY BestConfig;               // 2 elements, 0x10 bytes (sizeof)
/*0x058*/     struct _LIST_ENTRY ActiveArbiterList;        // 2 elements, 0x10 bytes (sizeof)
/*0x068*/     UINT8        State;
/*0x069*/     UINT8        ResourcesChanged;
/*0x06A*/     UINT8        _PADDING1_[0x6];
          }PI_RESOURCE_ARBITER_ENTRY, *PPI_RESOURCE_ARBITER_ENTRY;

          typedef struct _PORT_MESSAGE             // 7 elements, 0x28 bytes (sizeof)
          {
              union                                // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                           // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             INT16        DataLength;
/*0x002*/             INT16        TotalLength;
                  }s1;
/*0x000*/         ULONG32      Length;
              }u1;
              union                                // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                           // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x004*/             INT16        Type;
/*0x006*/             INT16        DataInfoOffset;
                  }s2;
/*0x004*/         ULONG32      ZeroInit;
              }u2;
              union                                // 2 elements, 0x10 bytes (sizeof)
              {
/*0x008*/         struct _CLIENT_ID ClientId;      // 2 elements, 0x10 bytes (sizeof)
/*0x008*/         FLOAT64      DoNotUseThisField;
              };
/*0x018*/     ULONG32      MessageId;
/*0x01C*/     UINT8        _PADDING0_[0x4];
              union                                // 2 elements, 0x8 bytes (sizeof)
              {
/*0x020*/         UINT64       ClientViewSize;
/*0x020*/         ULONG32      CallbackId;
              };
          }PORT_MESSAGE, *PPORT_MESSAGE;

          typedef struct _PORT_MESSAGE32           // 7 elements, 0x18 bytes (sizeof)
          {
              union                                // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                           // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             INT16        DataLength;
/*0x002*/             INT16        TotalLength;
                  }s1;
/*0x000*/         ULONG32      Length;
              }u1;
              union                                // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                           // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x004*/             INT16        Type;
/*0x006*/             INT16        DataInfoOffset;
                  }s2;
/*0x004*/         ULONG32      ZeroInit;
              }u2;
              union                                // 2 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         struct _CLIENT_ID32 ClientId;    // 2 elements, 0x8 bytes (sizeof)
/*0x008*/         FLOAT64      DoNotUseThisField;
              };
/*0x010*/     ULONG32      MessageId;
              union                                // 2 elements, 0x4 bytes (sizeof)
              {
/*0x014*/         ULONG32      ClientViewSize;
/*0x014*/         ULONG32      CallbackId;
              };
          }PORT_MESSAGE32, *PPORT_MESSAGE32;

          typedef struct _POWER_SEQUENCE // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      SequenceD1;
/*0x004*/     ULONG32      SequenceD2;
/*0x008*/     ULONG32      SequenceD3;
          }POWER_SEQUENCE, *PPOWER_SEQUENCE;

          typedef union _POWER_STATE                // 2 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     enum _SYSTEM_POWER_STATE SystemState;
/*0x000*/     enum _DEVICE_POWER_STATE DeviceState;
          }POWER_STATE, *PPOWER_STATE;


          typedef struct _PPM_CONCURRENCY_ACCOUNTING // 6 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       Lock;
/*0x008*/     ULONG32      Processors;
/*0x00C*/     ULONG32      ActiveProcessors;
/*0x010*/     UINT64       LastUpdateTime;
/*0x018*/     UINT64       TotalTime;
/*0x020*/     UINT64       AccumulatedTime[1];
          }PPM_CONCURRENCY_ACCOUNTING, *PPPM_CONCURRENCY_ACCOUNTING;

          typedef struct _PPM_FFH_THROTTLE_STATE_INFO // 5 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT8        EnableLogging;
/*0x001*/     UINT8        _PADDING0_[0x3];
/*0x004*/     ULONG32      MismatchCount;
/*0x008*/     UINT8        Initialized;
/*0x009*/     UINT8        _PADDING1_[0x7];
/*0x010*/     UINT64       LastValue;
/*0x018*/     union _LARGE_INTEGER LastLogTickCount;  // 4 elements, 0x8 bytes (sizeof)
          }PPM_FFH_THROTTLE_STATE_INFO, *PPPM_FFH_THROTTLE_STATE_INFO;

          typedef struct _PPM_IDLE_STATE          // 9 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _KAFFINITY_EX DomainMembers; // 4 elements, 0x48 bytes (sizeof)
/*0x048*/     ULONG32      Latency;
/*0x04C*/     ULONG32      Power;
/*0x050*/     ULONG32      StateFlags;
/*0x054*/     UINT8        StateType;
/*0x055*/     UINT8        InterruptsEnabled;
/*0x056*/     UINT8        Interruptible;
/*0x057*/     UINT8        ContextRetained;
/*0x058*/     UINT8        CacheCoherent;
/*0x059*/     UINT8        _PADDING0_[0x7];
          }PPM_IDLE_STATE, *PPPM_IDLE_STATE;

          typedef struct _PPM_IDLE_STATES                                                                                                                                                                                                      // 24 elements, 0x180 bytes (sizeof)
          {
/*0x000*/     UINT8        ForceIdle;
/*0x001*/     UINT8        AllowScaling;
/*0x002*/     UINT8        PromotePercentBase;
/*0x003*/     UINT8        DemotePercentBase;
/*0x004*/     ULONG32      Count;
/*0x008*/     ULONG32      TargetState;
/*0x00C*/     ULONG32      ActualState;
/*0x010*/     ULONG32      OldState;
/*0x014*/     ULONG32      OverrideIndex;
/*0x018*/     ULONG32      DependencyCount;
/*0x01C*/     ULONG32      MaximumDependencies;
/*0x020*/     struct _KAFFINITY_EX PrimaryProcessorMask;                                                                                                                                                                                       // 4 elements, 0x48 bytes (sizeof)
/*0x068*/     struct _KAFFINITY_EX SecondaryProcessorMask;                                                                                                                                                                                     // 4 elements, 0x48 bytes (sizeof)
/*0x0B0*/     struct _PROCESSOR_IDLE_DEPENDENCY* DependencyArray;
/*0x0B8*/     union _PPM_IDLE_SYNCHRONIZATION_STATE Synchronization;                                                                                                                                                                           // 3 elements, 0x4 bytes (sizeof)
/*0x0BC*/     UINT8        _PADDING0_[0x4];
/*0x0C0*/     VOID*        Context;
/*0x0C8*/     FUNCT_0009_07B8_IdlePrepare* IdlePrepare;
/*0x0D0*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* IdleExecute;
/*0x0D8*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* IdleComplete;
/*0x0E0*/     FUNCT_00AE_07CA_IdleCancel_Free_ComponentActive_ComponentIdle* IdleCancel;
/*0x0E8*/     FUNCT_006E_07CE_IdleIsHalted_IdleInitiateWake* IdleIsHalted;
/*0x0F0*/     FUNCT_006E_07CE_IdleIsHalted_IdleInitiateWake* IdleInitiateWake;
/*0x0F8*/     struct _PROCESSOR_IDLE_CONSTRAINTS Constraints;                                                                                                                                                                                  // 9 elements, 0x28 bytes (sizeof)
/*0x120*/     struct _PPM_IDLE_STATE State[1];
          }PPM_IDLE_STATES, *PPPM_IDLE_STATES;

          typedef union _PPM_IDLE_SYNCHRONIZATION_STATE // 3 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     LONG32       AsLong;
/*0x000*/     LONG32       RefCount : 24;               // 0 BitPosition
/*0x000*/     ULONG32      State : 8;                   // 24 BitPosition
          }PPM_IDLE_SYNCHRONIZATION_STATE, *PPPM_IDLE_SYNCHRONIZATION_STATE;

          typedef struct _PRIVATE_CACHE_MAP                 // 18 elements, 0x78 bytes (sizeof)
          {
              union                                         // 2 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         INT16        NodeTypeCode;
/*0x000*/         struct _PRIVATE_CACHE_MAP_FLAGS Flags;    // 6 elements, 0x4 bytes (sizeof)
              };
/*0x004*/     ULONG32      ReadAheadMask;
/*0x008*/     struct _FILE_OBJECT* FileObject;
/*0x010*/     union _LARGE_INTEGER FileOffset1;             // 4 elements, 0x8 bytes (sizeof)
/*0x018*/     union _LARGE_INTEGER BeyondLastByte1;         // 4 elements, 0x8 bytes (sizeof)
/*0x020*/     union _LARGE_INTEGER FileOffset2;             // 4 elements, 0x8 bytes (sizeof)
/*0x028*/     union _LARGE_INTEGER BeyondLastByte2;         // 4 elements, 0x8 bytes (sizeof)
/*0x030*/     ULONG32      SequentialReadCount;
/*0x034*/     ULONG32      ReadAheadLength;
/*0x038*/     union _LARGE_INTEGER ReadAheadOffset;         // 4 elements, 0x8 bytes (sizeof)
/*0x040*/     union _LARGE_INTEGER ReadAheadBeyondLastByte; // 4 elements, 0x8 bytes (sizeof)
/*0x048*/     UINT64       PrevReadAheadBeyondLastByte;
/*0x050*/     UINT64       ReadAheadSpinLock;
/*0x058*/     ULONG32      PipelinedReadAheadRequestSize;
/*0x05C*/     ULONG32      ReadAheadGrowth;
/*0x060*/     struct _LIST_ENTRY PrivateLinks;              // 2 elements, 0x10 bytes (sizeof)
/*0x070*/     VOID*        ReadAheadWorkItem;
          }PRIVATE_CACHE_MAP, *PPRIVATE_CACHE_MAP;

          typedef struct _PRIVATE_CACHE_MAP_FLAGS  // 6 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      DontUse : 16;           // 0 BitPosition
/*0x000*/     ULONG32      ReadAheadActive : 1;    // 16 BitPosition
/*0x000*/     ULONG32      ReadAheadEnabled : 1;   // 17 BitPosition
/*0x000*/     ULONG32      PagePriority : 3;       // 18 BitPosition
/*0x000*/     ULONG32      PipelineReadAheads : 1; // 21 BitPosition
/*0x000*/     ULONG32      Available : 10;         // 22 BitPosition
          }PRIVATE_CACHE_MAP_FLAGS, *PPRIVATE_CACHE_MAP_FLAGS;

          typedef struct _PROCESS_DISK_COUNTERS // 5 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       BytesRead;
/*0x008*/     UINT64       BytesWritten;
/*0x010*/     UINT64       ReadOperationCount;
/*0x018*/     UINT64       WriteOperationCount;
/*0x020*/     UINT64       FlushOperationCount;
          }PROCESS_DISK_COUNTERS, *PPROCESS_DISK_COUNTERS;

          typedef struct _PROCESSOR_IDLE_CONSTRAINTS // 9 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       TotalTime;
/*0x008*/     UINT64       IdleTime;
/*0x010*/     UINT64       ExpectedIdleDuration;
/*0x018*/     ULONG32      OverrideState;
/*0x01C*/     ULONG32      TimeCheck;
/*0x020*/     UINT8        PromotePercent;
/*0x021*/     UINT8        DemotePercent;
/*0x022*/     UINT8        Parked;
/*0x023*/     UINT8        Interruptible;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }PROCESSOR_IDLE_CONSTRAINTS, *PPROCESSOR_IDLE_CONSTRAINTS;

          typedef struct _PROCESSOR_IDLE_DEPENDENCY // 2 elements, 0x6 bytes (sizeof)
          {
/*0x000*/     struct _PROCESSOR_NUMBER Processor;   // 3 elements, 0x4 bytes (sizeof)
/*0x004*/     UINT8        ExpectedState;
/*0x005*/     UINT8        _PADDING0_[0x1];
          }PROCESSOR_IDLE_DEPENDENCY, *PPROCESSOR_IDLE_DEPENDENCY;

          typedef struct _PROCESSOR_NUMBER // 3 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     UINT16       Group;
/*0x002*/     UINT8        Number;
/*0x003*/     UINT8        Reserved;
          }PROCESSOR_NUMBER, *PPROCESSOR_NUMBER;

          typedef struct _PROCESSOR_POWER_STATE                         // 29 elements, 0x178 bytes (sizeof)
          {
/*0x000*/     struct _PPM_IDLE_STATES* IdleStates;
/*0x008*/     struct _PROC_IDLE_ACCOUNTING* IdleAccounting;
/*0x010*/     UINT64       IdleTimeLast;
/*0x018*/     UINT64       IdleTimeTotal;
/*0x020*/     UINT64       IdleTimeEntry;
/*0x028*/     struct _PROC_FEEDBACK PerfFeedback;                       // 10 elements, 0x48 bytes (sizeof)
/*0x070*/     enum _PROC_HYPERVISOR_STATE Hypervisor;
/*0x074*/     ULONG32      LastSysTime;
/*0x078*/     UINT64       WmiDispatchPtr;
/*0x080*/     LONG32       WmiInterfaceEnabled;
/*0x084*/     UINT8        _PADDING0_[0x4];
/*0x088*/     struct _PPM_FFH_THROTTLE_STATE_INFO FFHThrottleStateInfo; // 5 elements, 0x20 bytes (sizeof)
/*0x0A8*/     struct _KDPC PerfActionDpc;                               // 9 elements, 0x40 bytes (sizeof)
/*0x0E8*/     LONG32       PerfActionMask;
/*0x0EC*/     UINT8        _PADDING1_[0x4];
/*0x0F0*/     struct _PROC_IDLE_SNAP HvIdleCheck;                       // 2 elements, 0x10 bytes (sizeof)
/*0x100*/     struct _PROC_PERF_SNAP PerfCheck;                         // 7 elements, 0x38 bytes (sizeof)
/*0x138*/     struct _PROC_PERF_DOMAIN* Domain;
/*0x140*/     struct _PROC_PERF_CONSTRAINT* PerfConstraint;
/*0x148*/     struct _PPM_CONCURRENCY_ACCOUNTING* Concurrency;
/*0x150*/     struct _PROC_PERF_LOAD* Load;
/*0x158*/     struct _PROC_PERF_HISTORY* PerfHistory;
/*0x160*/     ULONG32      AverageFrequency;
/*0x164*/     UINT8        ThermalConstraint;
/*0x165*/     UINT8        HvTargetState;
/*0x166*/     UINT8        Parked;
/*0x167*/     UINT8        OverUtilized;
/*0x168*/     ULONG32      LatestFrequency;
/*0x16C*/     ULONG32      LatestAffinitizedPercent;
/*0x170*/     ULONG32      Utility;
/*0x174*/     ULONG32      AffinitizedUtility;
          }PROCESSOR_POWER_STATE, *PPROCESSOR_POWER_STATE;

          typedef struct _PROCESSOR_PROFILE_CONTROL_AREA // 1 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _PEBS_DS_SAVE_AREA PebsDsSaveArea;  // 12 elements, 0x60 bytes (sizeof)
          }PROCESSOR_PROFILE_CONTROL_AREA, *PPROCESSOR_PROFILE_CONTROL_AREA;

          typedef struct _PROVIDER_BINARY_ENTRY // 4 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;     // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT8        ConsumersNotified;
/*0x011*/     UINT8        _PADDING0_[0x3];
/*0x014*/     ULONG32      DebugIdSize;
/*0x018*/     union _CVDD  DebugId;             // 3 elements, 0x1C bytes (sizeof)
/*0x034*/     UINT8        _PADDING1_[0x4];
          }PROVIDER_BINARY_ENTRY, *PPROVIDER_BINARY_ENTRY;


          typedef struct _QUAD                     // 2 elements, 0x8 bytes (sizeof)
          {
              union                                // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         INT64        UseThisFieldToCopy;
/*0x000*/         FLOAT64      DoNotUseThisField;
              };
          }QUAD, *PQUAD;

          typedef struct _RELATION_LIST                // 5 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     ULONG32      TagCount;
/*0x008*/     ULONG32      FirstLevel;
/*0x00C*/     ULONG32      MaxLevel;
/*0x010*/     struct _RELATION_LIST_ENTRY* Entries[1];
          }RELATION_LIST, *PRELATION_LIST;

          typedef struct _RELATION_LIST_ENTRY    // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     ULONG32      MaxCount;
/*0x008*/     struct _DEVICE_OBJECT* Devices[1];
          }RELATION_LIST_ENTRY, *PRELATION_LIST_ENTRY;

          typedef struct _RELATIVE_SYMLINK_INFO                  // 6 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT16       ExposedNamespaceLength;
/*0x002*/     UINT16       Flags;
/*0x004*/     UINT16       DeviceNameLength;
/*0x006*/     UINT16       Reserved;
/*0x008*/     struct _RELATIVE_SYMLINK_INFO* InteriorMountPoint;
/*0x010*/     struct _UNICODE_STRING OpenedName;                 // 3 elements, 0x10 bytes (sizeof)
          }RELATIVE_SYMLINK_INFO, *PRELATIVE_SYMLINK_INFO;

          typedef struct _REMOTE_PORT_VIEW  // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      Length;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT64       ViewSize;
/*0x010*/     VOID*        ViewBase;
          }REMOTE_PORT_VIEW, *PREMOTE_PORT_VIEW;

          typedef struct _REQUEST_MAILBOX            // 3 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _REQUEST_MAILBOX* Next;
/*0x008*/     INT64        RequestSummary;
/*0x010*/     struct _KREQUEST_PACKET RequestPacket; // 2 elements, 0x20 bytes (sizeof)
/*0x030*/     UINT8        _PADDING0_[0x10];
          }REQUEST_MAILBOX, *PREQUEST_MAILBOX;

          typedef struct _RSDS              // 4 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     struct _GUID Guid;            // 4 elements, 0x10 bytes (sizeof)
/*0x014*/     ULONG32      Age;
/*0x018*/     CHAR         PdbName[1];
/*0x019*/     UINT8        _PADDING0_[0x3];
          }RSDS, *PRSDS;

typedef struct _SCSI_REQUEST_BLOCK // 0 elements, 0x0 bytes (sizeof)
{
}SCSI_REQUEST_BLOCK, *PSCSI_REQUEST_BLOCK;

          typedef struct _SESSION_LOWBOX_MAP               // 3 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;                // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      SessionId;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     struct _SEP_LOWBOX_NUMBER_MAPPING LowboxMap; // 4 elements, 0x28 bytes (sizeof)
          }SESSION_LOWBOX_MAP, *PSESSION_LOWBOX_MAP;

          typedef struct _SHARED_CACHE_MAP                         // 41 elements, 0x208 bytes (sizeof)
          {
/*0x000*/     INT16        NodeTypeCode;
/*0x002*/     INT16        NodeByteSize;
/*0x004*/     ULONG32      OpenCount;
/*0x008*/     union _LARGE_INTEGER FileSize;                       // 4 elements, 0x8 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY BcbList;                          // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     union _LARGE_INTEGER SectionSize;                    // 4 elements, 0x8 bytes (sizeof)
/*0x028*/     union _LARGE_INTEGER ValidDataLength;                // 4 elements, 0x8 bytes (sizeof)
/*0x030*/     union _LARGE_INTEGER ValidDataGoal;                  // 4 elements, 0x8 bytes (sizeof)
/*0x038*/     struct _VACB* InitialVacbs[4];
/*0x058*/     struct _VACB** Vacbs;
/*0x060*/     struct _EX_FAST_REF FileObjectFastRef;               // 3 elements, 0x8 bytes (sizeof)
/*0x068*/     struct _EX_PUSH_LOCK VacbLock;                       // 7 elements, 0x8 bytes (sizeof)
/*0x070*/     ULONG32      DirtyPages;
/*0x074*/     UINT8        _PADDING0_[0x4];
/*0x078*/     struct _LIST_ENTRY LoggedStreamLinks;                // 2 elements, 0x10 bytes (sizeof)
/*0x088*/     struct _LIST_ENTRY SharedCacheMapLinks;              // 2 elements, 0x10 bytes (sizeof)
/*0x098*/     ULONG32      Flags;
/*0x09C*/     LONG32       Status;
/*0x0A0*/     struct _MBCB* Mbcb;
/*0x0A8*/     VOID*        Section;
/*0x0B0*/     struct _KEVENT* CreateEvent;
/*0x0B8*/     struct _KEVENT* WaitOnActiveCount;
/*0x0C0*/     ULONG32      PagesToWrite;
/*0x0C4*/     UINT8        _PADDING1_[0x4];
/*0x0C8*/     INT64        BeyondLastFlush;
/*0x0D0*/     struct _CACHE_MANAGER_CALLBACKS* Callbacks;
/*0x0D8*/     VOID*        LazyWriteContext;
/*0x0E0*/     struct _LIST_ENTRY PrivateList;                      // 2 elements, 0x10 bytes (sizeof)
              union                                                // 2 elements, 0x10 bytes (sizeof)
              {
/*0x0F0*/         struct _LOGGED_STREAM_CALLBACK_V1 V1;            // 2 elements, 0x10 bytes (sizeof)
/*0x0F0*/         struct _LOGGED_STREAM_CALLBACK_V2 V2;            // 1 elements, 0x8 bytes (sizeof)
              };
/*0x100*/     union _LARGE_INTEGER LargestLSN;                     // 4 elements, 0x8 bytes (sizeof)
/*0x108*/     ULONG32      DirtyPageThreshold;
/*0x10C*/     ULONG32      LazyWritePassCount;
/*0x110*/     struct _CACHE_UNINITIALIZE_EVENT* UninitializeEvent;
/*0x118*/     struct _FAST_MUTEX BcbLock;                          // 5 elements, 0x38 bytes (sizeof)
/*0x150*/     union _LARGE_INTEGER LastUnmapBehindOffset;          // 4 elements, 0x8 bytes (sizeof)
/*0x158*/     struct _KEVENT Event;                                // 1 elements, 0x18 bytes (sizeof)
/*0x170*/     union _LARGE_INTEGER HighWaterMappingOffset;         // 4 elements, 0x8 bytes (sizeof)
/*0x178*/     struct _PRIVATE_CACHE_MAP PrivateCacheMap;           // 18 elements, 0x78 bytes (sizeof)
/*0x1F0*/     VOID*        WriteBehindWorkQueueEntry;
/*0x1F8*/     struct _VOLUME_CACHE_MAP* VolumeCacheMap;
/*0x200*/     ULONG32      ProcImagePathHash;
/*0x204*/     ULONG32      WritesInProgress;
          }SHARED_CACHE_MAP, *PSHARED_CACHE_MAP;

          typedef struct _SHARED_CACHE_MAP_LIST_CURSOR // 2 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY SharedCacheMapLinks;  // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Flags;
/*0x014*/     UINT8        _PADDING0_[0x4];
          }SHARED_CACHE_MAP_LIST_CURSOR, *PSHARED_CACHE_MAP_LIST_CURSOR;

          typedef struct _SYNCH_COUNTERS                                          // 46 elements, 0xB8 bytes (sizeof)
          {
/*0x000*/     ULONG32      SpinLockAcquireCount;
/*0x004*/     ULONG32      SpinLockContentionCount;
/*0x008*/     ULONG32      SpinLockSpinCount;
/*0x00C*/     ULONG32      IpiSendRequestBroadcastCount;
/*0x010*/     ULONG32      IpiSendRequestRoutineCount;
/*0x014*/     ULONG32      IpiSendSoftwareInterruptCount;
/*0x018*/     ULONG32      ExInitializeResourceCount;
/*0x01C*/     ULONG32      ExReInitializeResourceCount;
/*0x020*/     ULONG32      ExDeleteResourceCount;
/*0x024*/     ULONG32      ExecutiveResourceAcquiresCount;
/*0x028*/     ULONG32      ExecutiveResourceContentionsCount;
/*0x02C*/     ULONG32      ExecutiveResourceReleaseExclusiveCount;
/*0x030*/     ULONG32      ExecutiveResourceReleaseSharedCount;
/*0x034*/     ULONG32      ExecutiveResourceConvertsCount;
/*0x038*/     ULONG32      ExAcqResExclusiveAttempts;
/*0x03C*/     ULONG32      ExAcqResExclusiveAcquiresExclusive;
/*0x040*/     ULONG32      ExAcqResExclusiveAcquiresExclusiveRecursive;
/*0x044*/     ULONG32      ExAcqResExclusiveWaits;
/*0x048*/     ULONG32      ExAcqResExclusiveNotAcquires;
/*0x04C*/     ULONG32      ExAcqResSharedAttempts;
/*0x050*/     ULONG32      ExAcqResSharedAcquiresExclusive;
/*0x054*/     ULONG32      ExAcqResSharedAcquiresShared;
/*0x058*/     ULONG32      ExAcqResSharedAcquiresSharedRecursive;
/*0x05C*/     ULONG32      ExAcqResSharedWaits;
/*0x060*/     ULONG32      ExAcqResSharedNotAcquires;
/*0x064*/     ULONG32      ExAcqResSharedStarveExclusiveAttempts;
/*0x068*/     ULONG32      ExAcqResSharedStarveExclusiveAcquiresExclusive;
/*0x06C*/     ULONG32      ExAcqResSharedStarveExclusiveAcquiresShared;
/*0x070*/     ULONG32      ExAcqResSharedStarveExclusiveAcquiresSharedRecursive;
/*0x074*/     ULONG32      ExAcqResSharedStarveExclusiveWaits;
/*0x078*/     ULONG32      ExAcqResSharedStarveExclusiveNotAcquires;
/*0x07C*/     ULONG32      ExAcqResSharedWaitForExclusiveAttempts;
/*0x080*/     ULONG32      ExAcqResSharedWaitForExclusiveAcquiresExclusive;
/*0x084*/     ULONG32      ExAcqResSharedWaitForExclusiveAcquiresShared;
/*0x088*/     ULONG32      ExAcqResSharedWaitForExclusiveAcquiresSharedRecursive;
/*0x08C*/     ULONG32      ExAcqResSharedWaitForExclusiveWaits;
/*0x090*/     ULONG32      ExAcqResSharedWaitForExclusiveNotAcquires;
/*0x094*/     ULONG32      ExSetResOwnerPointerExclusive;
/*0x098*/     ULONG32      ExSetResOwnerPointerSharedNew;
/*0x09C*/     ULONG32      ExSetResOwnerPointerSharedOld;
/*0x0A0*/     ULONG32      ExTryToAcqExclusiveAttempts;
/*0x0A4*/     ULONG32      ExTryToAcqExclusiveAcquires;
/*0x0A8*/     ULONG32      ExBoostExclusiveOwner;
/*0x0AC*/     ULONG32      ExBoostSharedOwners;
/*0x0B0*/     ULONG32      ExEtwSynchTrackingNotificationsCount;
/*0x0B4*/     ULONG32      ExEtwSynchTrackingNotificationsAccountedCount;
          }SYNCH_COUNTERS, *PSYNCH_COUNTERS;

          typedef struct _TERMINATION_PORT    // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _TERMINATION_PORT* Next;
/*0x008*/     VOID*        Port;
          }TERMINATION_PORT, *PTERMINATION_PORT;

          typedef struct _THREAD_PERFORMANCE_DATA       // 10 elements, 0x1C0 bytes (sizeof)
          {
/*0x000*/     UINT16       Size;
/*0x002*/     UINT16       Version;
/*0x004*/     struct _PROCESSOR_NUMBER ProcessorNumber; // 3 elements, 0x4 bytes (sizeof)
/*0x008*/     ULONG32      ContextSwitches;
/*0x00C*/     ULONG32      HwCountersCount;
/*0x010*/     UINT64       UpdateCount;
/*0x018*/     UINT64       WaitReasonBitMap;
/*0x020*/     UINT64       HardwareCounters;
/*0x028*/     struct _COUNTER_READING CycleTime;        // 4 elements, 0x18 bytes (sizeof)
/*0x040*/     struct _COUNTER_READING HwCounters[16];
          }THREAD_PERFORMANCE_DATA, *PTHREAD_PERFORMANCE_DATA;

          typedef struct _TP_CALLBACK_ENVIRON_V3                                                                          // 10 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      Version;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _TP_POOL* Pool;
/*0x010*/     struct _TP_CLEANUP_GROUP* CleanupGroup;
/*0x018*/     FUNCT_00AE_00AD_CleanupGroupCancelCallback_DeRefSecurityDescriptor_PostRoutine* CleanupGroupCancelCallback;
/*0x020*/     VOID*        RaceDll;
/*0x028*/     struct _ACTIVATION_CONTEXT* ActivationContext;
/*0x030*/     FUNCT_00AE_00B5_FinalizationCallback* FinalizationCallback;
              union                                                                                                       // 2 elements, 0x4 bytes (sizeof)
              {
/*0x038*/         ULONG32      Flags;
                  struct                                                                                                  // 3 elements, 0x4 bytes (sizeof)
                  {
/*0x038*/             ULONG32      LongFunction : 1;                                                                      // 0 BitPosition
/*0x038*/             ULONG32      Persistent : 1;                                                                        // 1 BitPosition
/*0x038*/             ULONG32      Private : 30;                                                                          // 2 BitPosition
                  }s;
              }u;
/*0x03C*/     enum _TP_CALLBACK_PRIORITY CallbackPriority;
/*0x040*/     ULONG32      Size;
/*0x044*/     UINT8        _PADDING1_[0x4];
          }TP_CALLBACK_ENVIRON_V3, *PTP_CALLBACK_ENVIRON_V3;

typedef struct _TP_CALLBACK_INSTANCE // 0 elements, 0x0 bytes (sizeof)
{
}TP_CALLBACK_INSTANCE, *PTP_CALLBACK_INSTANCE;

typedef struct _TP_CLEANUP_GROUP // 0 elements, 0x0 bytes (sizeof)
{
}TP_CLEANUP_GROUP, *PTP_CLEANUP_GROUP;

typedef struct _TP_POOL // 0 elements, 0x0 bytes (sizeof)
{
}TP_POOL, *PTP_POOL;

          typedef struct _TP_TASK                   // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _TP_TASK_CALLBACKS* Callbacks;
/*0x008*/     ULONG32      NumaNode;
/*0x00C*/     UINT8        IdealProcessor;
/*0x00D*/     UINT8        _PADDING0_[0x3];
/*0x010*/     struct _LIST_ENTRY ListEntry;         // 2 elements, 0x10 bytes (sizeof)
          }TP_TASK, *PTP_TASK;

          typedef struct _TP_TASK_CALLBACKS                     // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     FUNCT_00AE_00D2_ExecuteCallback* ExecuteCallback;
/*0x008*/     FUNCT_00AE_00D7_Unposted* Unposted;
          }TP_TASK_CALLBACKS, *PTP_TASK_CALLBACKS;

          typedef struct _TRACE_ENABLE_CONTEXT // 4 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT16       LoggerId;
/*0x002*/     UINT8        Level;
/*0x003*/     UINT8        InternalFlag;
/*0x004*/     ULONG32      EnableFlags;
          }TRACE_ENABLE_CONTEXT, *PTRACE_ENABLE_CONTEXT;

          typedef struct _TRACE_ENABLE_CONTEXT_EX // 6 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       LoggerId;
/*0x002*/     UINT8        Level;
/*0x003*/     UINT8        InternalFlag;
/*0x004*/     ULONG32      EnableFlags;
/*0x008*/     ULONG32      EnableFlagsHigh;
/*0x00C*/     ULONG32      Reserved;
          }TRACE_ENABLE_CONTEXT_EX, *PTRACE_ENABLE_CONTEXT_EX;

          typedef struct _TRACE_ENABLE_INFO // 8 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     ULONG32      IsEnabled;
/*0x004*/     UINT8        Level;
/*0x005*/     UINT8        Reserved1;
/*0x006*/     UINT16       LoggerId;
/*0x008*/     ULONG32      EnableProperty;
/*0x00C*/     ULONG32      Reserved2;
/*0x010*/     UINT64       MatchAnyKeyword;
/*0x018*/     UINT64       MatchAllKeyword;
          }TRACE_ENABLE_INFO, *PTRACE_ENABLE_INFO;

          typedef struct _TRACE_LOGFILE_HEADER            // 23 elements, 0x118 bytes (sizeof)
          {
/*0x000*/     ULONG32      BufferSize;
              union                                       // 2 elements, 0x4 bytes (sizeof)
              {
/*0x004*/         ULONG32      Version;
                  struct                                  // 4 elements, 0x4 bytes (sizeof)
                  {
/*0x004*/             UINT8        MajorVersion;
/*0x005*/             UINT8        MinorVersion;
/*0x006*/             UINT8        SubVersion;
/*0x007*/             UINT8        SubMinorVersion;
                  }VersionDetail;
              };
/*0x008*/     ULONG32      ProviderVersion;
/*0x00C*/     ULONG32      NumberOfProcessors;
/*0x010*/     union _LARGE_INTEGER EndTime;               // 4 elements, 0x8 bytes (sizeof)
/*0x018*/     ULONG32      TimerResolution;
/*0x01C*/     ULONG32      MaximumFileSize;
/*0x020*/     ULONG32      LogFileMode;
/*0x024*/     ULONG32      BuffersWritten;
              union                                       // 2 elements, 0x10 bytes (sizeof)
              {
/*0x028*/         struct _GUID LogInstanceGuid;           // 4 elements, 0x10 bytes (sizeof)
                  struct                                  // 4 elements, 0x10 bytes (sizeof)
                  {
/*0x028*/             ULONG32      StartBuffers;
/*0x02C*/             ULONG32      PointerSize;
/*0x030*/             ULONG32      EventsLost;
/*0x034*/             ULONG32      CpuSpeedInMHz;
                  };
              };
/*0x038*/     UINT16*      LoggerName;
/*0x040*/     UINT16*      LogFileName;
/*0x048*/     struct _RTL_TIME_ZONE_INFORMATION TimeZone; // 7 elements, 0xAC bytes (sizeof)
/*0x0F4*/     UINT8        _PADDING0_[0x4];
/*0x0F8*/     union _LARGE_INTEGER BootTime;              // 4 elements, 0x8 bytes (sizeof)
/*0x100*/     union _LARGE_INTEGER PerfFreq;              // 4 elements, 0x8 bytes (sizeof)
/*0x108*/     union _LARGE_INTEGER StartTime;             // 4 elements, 0x8 bytes (sizeof)
/*0x110*/     ULONG32      ReservedFlags;
/*0x114*/     ULONG32      BuffersLost;
          }TRACE_LOGFILE_HEADER, *PTRACE_LOGFILE_HEADER;

          typedef struct _TXN_PARAMETER_BLOCK // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Length;
/*0x002*/     UINT16       TxFsContext;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        TransactionObject;
          }TXN_PARAMETER_BLOCK, *PTXN_PARAMETER_BLOCK;

          typedef struct _UMS_CONTROL_BLOCK                                // 18 elements, 0x90 bytes (sizeof)
          {
/*0x000*/     struct _RTL_UMS_CONTEXT* UmsContext;
/*0x008*/     struct _SINGLE_LIST_ENTRY* CompletionListEntry;
/*0x010*/     struct _KEVENT* CompletionListEvent;
/*0x018*/     ULONG32      ServiceSequenceNumber;
/*0x01C*/     UINT8        _PADDING0_[0x4];
              union                                                        // 2 elements, 0x68 bytes (sizeof)
              {
                  struct                                                   // 5 elements, 0x68 bytes (sizeof)
                  {
/*0x020*/             struct _KQUEUE UmsQueue;                             // 5 elements, 0x40 bytes (sizeof)
/*0x060*/             struct _LIST_ENTRY QueueEntry;                       // 2 elements, 0x10 bytes (sizeof)
/*0x070*/             struct _RTL_UMS_CONTEXT* YieldingUmsContext;
/*0x078*/             VOID*        YieldingParam;
/*0x080*/             VOID*        UmsTeb;
                  };
                  struct                                                   // 5 elements, 0x68 bytes (sizeof)
                  {
/*0x020*/             struct _KQUEUE* UmsAssociatedQueue;
/*0x028*/             struct _LIST_ENTRY* UmsQueueListEntry;
/*0x030*/             struct _KEVENT UmsWaitEvent;                         // 1 elements, 0x18 bytes (sizeof)
/*0x048*/             VOID*        StagingArea;
                      union                                                // 2 elements, 0x38 bytes (sizeof)
                      {
                          struct                                           // 3 elements, 0x4 bytes (sizeof)
                          {
/*0x050*/                     ULONG32      UmsPrimaryDeliveredContext : 1; // 0 BitPosition
/*0x050*/                     ULONG32      UmsAssociatedQueueUsed : 1;     // 1 BitPosition
/*0x050*/                     ULONG32      UmsThreadParked : 1;            // 2 BitPosition
                          };
/*0x050*/                 ULONG32      UmsFlags;
                      };
                  };
              };
/*0x088*/     UINT16       TebSelector;
/*0x08A*/     UINT8        _PADDING1_[0x6];
          }UMS_CONTROL_BLOCK, *PUMS_CONTROL_BLOCK;

          typedef struct _VACB                          // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     VOID*        BaseAddress;
/*0x008*/     struct _SHARED_CACHE_MAP* SharedCacheMap;
              union                                     // 3 elements, 0x10 bytes (sizeof)
              {
/*0x010*/         union _LARGE_INTEGER FileOffset;      // 4 elements, 0x8 bytes (sizeof)
/*0x010*/         UINT16       ActiveCount;
/*0x010*/         struct _LIST_ENTRY Links;             // 2 elements, 0x10 bytes (sizeof)
              }Overlay;
/*0x020*/     struct _VACB_ARRAY_HEADER* ArrayHead;
          }VACB, *PVACB;

          typedef struct _VACB_ARRAY_HEADER    // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      VacbArrayIndex;
/*0x004*/     ULONG32      MappingCount;
/*0x008*/     ULONG32      HighestMappedIndex;
/*0x00C*/     ULONG32      Reserved;
          }VACB_ARRAY_HEADER, *PVACB_ARRAY_HEADER;

          typedef struct _VACB_LEVEL_REFERENCE // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     LONG32       Reference;
/*0x004*/     LONG32       SpecialReference;
          }VACB_LEVEL_REFERENCE, *PVACB_LEVEL_REFERENCE;

typedef struct _VERIFIER_SHARED_EXPORT_THUNK // 0 elements, 0x0 bytes (sizeof)
{
}VERIFIER_SHARED_EXPORT_THUNK, *PVERIFIER_SHARED_EXPORT_THUNK;

          typedef struct _VOLUME_CACHE_MAP                 // 10 elements, 0xB0 bytes (sizeof)
          {
/*0x000*/     INT16        NodeTypeCode;
/*0x002*/     INT16        NodeByteCode;
/*0x004*/     ULONG32      UseCount;
/*0x008*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x010*/     struct _LIST_ENTRY VolumeCacheMapLinks;      // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     UINT64       DirtyPages;
/*0x028*/     struct _LOG_HANDLE_CONTEXT LogHandleContext; // 11 elements, 0x78 bytes (sizeof)
/*0x0A0*/     ULONG32      Flags;
/*0x0A4*/     ULONG32      PagesQueuedToDisk;
/*0x0A8*/     ULONG32      LoggedPagesQueuedToDisk;
/*0x0AC*/     UINT8        _PADDING0_[0x4];
          }VOLUME_CACHE_MAP, *PVOLUME_CACHE_MAP;

          typedef struct _VPB                      // 9 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     INT16        Size;
/*0x004*/     UINT16       Flags;
/*0x006*/     UINT16       VolumeLabelLength;
/*0x008*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x010*/     struct _DEVICE_OBJECT* RealDevice;
/*0x018*/     ULONG32      SerialNumber;
/*0x01C*/     ULONG32      ReferenceCount;
/*0x020*/     WCHAR        VolumeLabel[32];
          }VPB, *PVPB;

          typedef struct _WAIT_CONTEXT_BLOCK                  // 12 elements, 0x48 bytes (sizeof)
          {
              union                                           // 2 elements, 0x18 bytes (sizeof)
              {
/*0x000*/         struct _KDEVICE_QUEUE_ENTRY WaitQueueEntry; // 3 elements, 0x18 bytes (sizeof)
                  struct                                      // 3 elements, 0x18 bytes (sizeof)
                  {
/*0x000*/             struct _LIST_ENTRY DmaWaitEntry;        // 2 elements, 0x10 bytes (sizeof)
/*0x010*/             ULONG32      NumberOfChannels;
                      struct                                  // 3 elements, 0x4 bytes (sizeof)
                      {
/*0x014*/                 ULONG32      SyncCallback : 1;      // 0 BitPosition
/*0x014*/                 ULONG32      DmaContext : 1;        // 1 BitPosition
/*0x014*/                 ULONG32      Reserved : 30;         // 2 BitPosition
                      };
                  };
              };
/*0x018*/     FUNCT_10B2_10B1_DeviceRoutine* DeviceRoutine;
/*0x020*/     VOID*        DeviceContext;
/*0x028*/     ULONG32      NumberOfMapRegisters;
/*0x02C*/     UINT8        _PADDING0_[0x4];
/*0x030*/     VOID*        DeviceObject;
/*0x038*/     VOID*        CurrentIrp;
/*0x040*/     struct _KDPC* BufferChainingDpc;
          }WAIT_CONTEXT_BLOCK, *PWAIT_CONTEXT_BLOCK;

          typedef struct _WNF_STATE_NAME // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Data[2];
          }WNF_STATE_NAME, *PWNF_STATE_NAME;

          typedef struct _XSTATE_CONFIGURATION     // 4 elements, 0x210 bytes (sizeof)
          {
/*0x000*/     UINT64       EnabledFeatures;
/*0x008*/     ULONG32      Size;
/*0x00C*/     ULONG32      OptimizedSave : 1;      // 0 BitPosition
/*0x010*/     struct _XSTATE_FEATURE Features[64];
          }XSTATE_CONFIGURATION, *PXSTATE_CONFIGURATION;

          typedef struct _XSTATE_CONTEXT // 5 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT64       Mask;
/*0x008*/     ULONG32      Length;
/*0x00C*/     ULONG32      Reserved1;
/*0x010*/     struct _XSAVE_AREA* Area;
/*0x018*/     VOID*        Buffer;
          }XSTATE_CONTEXT, *PXSTATE_CONTEXT;

          typedef struct _XSTATE_FEATURE // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Offset;
/*0x004*/     ULONG32      Size;
          }XSTATE_FEATURE, *PXSTATE_FEATURE;

          typedef struct _XSTATE_SAVE               // 4 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _XSTATE_SAVE* Prev;
/*0x008*/     struct _KTHREAD* Thread;
/*0x010*/     UINT8        Level;
/*0x011*/     UINT8        _PADDING0_[0x7];
/*0x018*/     struct _XSTATE_CONTEXT XStateContext; // 5 elements, 0x20 bytes (sizeof)
          }XSTATE_SAVE, *PXSTATE_SAVE;

          typedef struct _DOCK_INTERFACE                                                                                                                                                                                                               // 7 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     UINT16       Size;
/*0x002*/     UINT16       Version;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        Context;
/*0x010*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* InterfaceReference;
/*0x018*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* InterfaceDereference;
/*0x020*/     FUNCT_0009_17AB_ProfileDepartureSetMode* ProfileDepartureSetMode;
/*0x028*/     FUNCT_0009_17B4_ProfileDepartureUpdate* ProfileDepartureUpdate;
          }DOCK_INTERFACE, *PDOCK_INTERFACE;

          typedef struct _PEPHANDLE__ // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     INT32        unused;
          }PEPHANDLE__, *PPEPHANDLE__;

          typedef struct _tagSWITCH_CONTEXT                  // 2 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _tagSWITCH_CONTEXT_ATTRIBUTE Attribute; // 4 elements, 0x18 bytes (sizeof)
/*0x018*/     struct _tagSWITCH_CONTEXT_DATA Data;           // 4 elements, 0x34 bytes (sizeof)
/*0x04C*/     UINT8        _PADDING0_[0x4];
          }tagSWITCH_CONTEXT, *PtagSWITCH_CONTEXT;

          typedef struct _tagSWITCH_CONTEXT_ATTRIBUTE // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT64       ulContextUpdateCounter;
/*0x008*/     INT32        fAllowContextUpdate;
/*0x00C*/     INT32        fEnableTrace;
/*0x010*/     UINT64       EtwHandle;
          }tagSWITCH_CONTEXT_ATTRIBUTE, *PtagSWITCH_CONTEXT_ATTRIBUTE;

          typedef struct _tagSWITCH_CONTEXT_DATA // 4 elements, 0x34 bytes (sizeof)
          {
/*0x000*/     struct _GUID guPlatform;           // 4 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _GUID guMinPlatform;        // 4 elements, 0x10 bytes (sizeof)
/*0x020*/     ULONG32      ulElementCount;
/*0x024*/     struct _GUID guElements[1];
          }tagSWITCH_CONTEXT_DATA, *PtagSWITCH_CONTEXT_DATA;

          typedef struct _VACB_LEVEL_ALLOCATION_LIST  // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY VacbLevelList;       // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     VOID*        VacbLevelWithBcbListHeads;
/*0x018*/     ULONG32      VacbLevelsAllocated;
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }VACB_LEVEL_ALLOCATION_LIST, *PVACB_LEVEL_ALLOCATION_LIST;

typedef enum ___2011110910380E024B8CE6D17A03D5CB0_RecordType  // 2 elements, 0x4 bytes
{
    KTMOH_CommitTransaction_Result   = 1 /*0x1*/,
    KTMOH_RollbackTransaction_Result = 2 /*0x2*/
}__2011110910380E024B8CE6D17A03D5CB0_RecordType, *P__2011110910380E024B8CE6D17A03D5CB0_RecordType;

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE  // 3 elements, 0x4 bytes
{
    StandardDesign  = 0 /*0x0*/,
    NEC98x86        = 1 /*0x1*/,
    EndAlternatives = 2 /*0x2*/
}ALTERNATIVE_ARCHITECTURE_TYPE, *PALTERNATIVE_ARCHITECTURE_TYPE;

typedef enum _BLOB_ID  // 11 elements, 0x4 bytes
{
    BLOB_TYPE_UNKNOWN          = 0 /*0x0*/,
    BLOB_TYPE_CONNECTION_INFO  = 1 /*0x1*/,
    BLOB_TYPE_MESSAGE          = 2 /*0x2*/,
    BLOB_TYPE_SECURITY_CONTEXT = 3 /*0x3*/,
    BLOB_TYPE_SECTION          = 4 /*0x4*/,
    BLOB_TYPE_REGION           = 5 /*0x5*/,
    BLOB_TYPE_VIEW             = 6 /*0x6*/,
    BLOB_TYPE_RESERVE          = 7 /*0x7*/,
    BLOB_TYPE_DIRECT_TRANSFER  = 8 /*0x8*/,
    BLOB_TYPE_HANDLE_DATA      = 9 /*0x9*/,
    BLOB_TYPE_MAX_ID           = 10 /*0xA*/
}BLOB_ID, *PBLOB_ID;

typedef enum _DEVPROP_OPERATOR  // 27 elements, 0x4 bytes
{
    DEVPROP_OPERATOR_MODIFIER_NOT              = 65536 /*0x10000*/,
    DEVPROP_OPERATOR_MODIFIER_IGNORE_CASE      = 131072 /*0x20000*/,
    DEVPROP_OPERATOR_NONE                      = 0 /*0x0*/,
    DEVPROP_OPERATOR_EXISTS                    = 1 /*0x1*/,
    DEVPROP_OPERATOR_EQUALS                    = 2 /*0x2*/,
    DEVPROP_OPERATOR_NOT_EQUALS                = 65538 /*0x10002*/,
    DEVPROP_OPERATOR_GREATER_THAN              = 3 /*0x3*/,
    DEVPROP_OPERATOR_LESS_THAN                 = 4 /*0x4*/,
    DEVPROP_OPERATOR_GREATER_THAN_EQUALS       = 5 /*0x5*/,
    DEVPROP_OPERATOR_LESS_THAN_EQUALS          = 6 /*0x6*/,
    DEVPROP_OPERATOR_EQUALS_IGNORE_CASE        = 131074 /*0x20002*/,
    DEVPROP_OPERATOR_NOT_EQUALS_IGNORE_CASE    = 196610 /*0x30002*/,
    DEVPROP_OPERATOR_BITWISE_AND               = 7 /*0x7*/,
    DEVPROP_OPERATOR_BITWISE_OR                = 8 /*0x8*/,
    DEVPROP_OPERATOR_LIST_CONTAINS             = 4096 /*0x1000*/,
    DEVPROP_OPERATOR_LIST_CONTAINS_IGNORE_CASE = 135168 /*0x21000*/,
    DEVPROP_OPERATOR_AND_OPEN                  = 1048576 /*0x100000*/,
    DEVPROP_OPERATOR_AND_CLOSE                 = 2097152 /*0x200000*/,
    DEVPROP_OPERATOR_OR_OPEN                   = 3145728 /*0x300000*/,
    DEVPROP_OPERATOR_OR_CLOSE                  = 4194304 /*0x400000*/,
    DEVPROP_OPERATOR_NOT_OPEN                  = 5242880 /*0x500000*/,
    DEVPROP_OPERATOR_NOT_CLOSE                 = 6291456 /*0x600000*/,
    DEVPROP_OPERATOR_MASK_EVAL                 = 4095 /*0xFFF*/,
    DEVPROP_OPERATOR_MASK_LIST                 = 61440 /*0xF000*/,
    DEVPROP_OPERATOR_MASK_MODIFIER             = 983040 /*0xF0000*/,
    DEVPROP_OPERATOR_MASK_NOT_LOGICAL          = 1048575 /*0xFFFFF*/,
    DEVPROP_OPERATOR_MASK_LOGICAL              = -1048576 /*0xFFF00000*/
}DEVPROP_OPERATOR, *PDEVPROP_OPERATOR;

typedef enum _DPFLTR_TYPE  // 150 elements, 0x4 bytes
{
    DPFLTR_SYSTEM_ID         = 0 /*0x0*/,
    DPFLTR_SMSS_ID           = 1 /*0x1*/,
    DPFLTR_SETUP_ID          = 2 /*0x2*/,
    DPFLTR_NTFS_ID           = 3 /*0x3*/,
    DPFLTR_FSTUB_ID          = 4 /*0x4*/,
    DPFLTR_CRASHDUMP_ID      = 5 /*0x5*/,
    DPFLTR_CDAUDIO_ID        = 6 /*0x6*/,
    DPFLTR_CDROM_ID          = 7 /*0x7*/,
    DPFLTR_CLASSPNP_ID       = 8 /*0x8*/,
    DPFLTR_DISK_ID           = 9 /*0x9*/,
    DPFLTR_REDBOOK_ID        = 10 /*0xA*/,
    DPFLTR_STORPROP_ID       = 11 /*0xB*/,
    DPFLTR_SCSIPORT_ID       = 12 /*0xC*/,
    DPFLTR_SCSIMINIPORT_ID   = 13 /*0xD*/,
    DPFLTR_CONFIG_ID         = 14 /*0xE*/,
    DPFLTR_I8042PRT_ID       = 15 /*0xF*/,
    DPFLTR_SERMOUSE_ID       = 16 /*0x10*/,
    DPFLTR_LSERMOUS_ID       = 17 /*0x11*/,
    DPFLTR_KBDHID_ID         = 18 /*0x12*/,
    DPFLTR_MOUHID_ID         = 19 /*0x13*/,
    DPFLTR_KBDCLASS_ID       = 20 /*0x14*/,
    DPFLTR_MOUCLASS_ID       = 21 /*0x15*/,
    DPFLTR_TWOTRACK_ID       = 22 /*0x16*/,
    DPFLTR_WMILIB_ID         = 23 /*0x17*/,
    DPFLTR_ACPI_ID           = 24 /*0x18*/,
    DPFLTR_AMLI_ID           = 25 /*0x19*/,
    DPFLTR_HALIA64_ID        = 26 /*0x1A*/,
    DPFLTR_VIDEO_ID          = 27 /*0x1B*/,
    DPFLTR_SVCHOST_ID        = 28 /*0x1C*/,
    DPFLTR_VIDEOPRT_ID       = 29 /*0x1D*/,
    DPFLTR_TCPIP_ID          = 30 /*0x1E*/,
    DPFLTR_DMSYNTH_ID        = 31 /*0x1F*/,
    DPFLTR_NTOSPNP_ID        = 32 /*0x20*/,
    DPFLTR_FASTFAT_ID        = 33 /*0x21*/,
    DPFLTR_SAMSS_ID          = 34 /*0x22*/,
    DPFLTR_PNPMGR_ID         = 35 /*0x23*/,
    DPFLTR_NETAPI_ID         = 36 /*0x24*/,
    DPFLTR_SCSERVER_ID       = 37 /*0x25*/,
    DPFLTR_SCCLIENT_ID       = 38 /*0x26*/,
    DPFLTR_SERIAL_ID         = 39 /*0x27*/,
    DPFLTR_SERENUM_ID        = 40 /*0x28*/,
    DPFLTR_UHCD_ID           = 41 /*0x29*/,
    DPFLTR_RPCPROXY_ID       = 42 /*0x2A*/,
    DPFLTR_AUTOCHK_ID        = 43 /*0x2B*/,
    DPFLTR_DCOMSS_ID         = 44 /*0x2C*/,
    DPFLTR_UNIMODEM_ID       = 45 /*0x2D*/,
    DPFLTR_SIS_ID            = 46 /*0x2E*/,
    DPFLTR_FLTMGR_ID         = 47 /*0x2F*/,
    DPFLTR_WMICORE_ID        = 48 /*0x30*/,
    DPFLTR_BURNENG_ID        = 49 /*0x31*/,
    DPFLTR_IMAPI_ID          = 50 /*0x32*/,
    DPFLTR_SXS_ID            = 51 /*0x33*/,
    DPFLTR_FUSION_ID         = 52 /*0x34*/,
    DPFLTR_IDLETASK_ID       = 53 /*0x35*/,
    DPFLTR_SOFTPCI_ID        = 54 /*0x36*/,
    DPFLTR_TAPE_ID           = 55 /*0x37*/,
    DPFLTR_MCHGR_ID          = 56 /*0x38*/,
    DPFLTR_IDEP_ID           = 57 /*0x39*/,
    DPFLTR_PCIIDE_ID         = 58 /*0x3A*/,
    DPFLTR_FLOPPY_ID         = 59 /*0x3B*/,
    DPFLTR_FDC_ID            = 60 /*0x3C*/,
    DPFLTR_TERMSRV_ID        = 61 /*0x3D*/,
    DPFLTR_W32TIME_ID        = 62 /*0x3E*/,
    DPFLTR_PREFETCHER_ID     = 63 /*0x3F*/,
    DPFLTR_RSFILTER_ID       = 64 /*0x40*/,
    DPFLTR_FCPORT_ID         = 65 /*0x41*/,
    DPFLTR_PCI_ID            = 66 /*0x42*/,
    DPFLTR_DMIO_ID           = 67 /*0x43*/,
    DPFLTR_DMCONFIG_ID       = 68 /*0x44*/,
    DPFLTR_DMADMIN_ID        = 69 /*0x45*/,
    DPFLTR_WSOCKTRANSPORT_ID = 70 /*0x46*/,
    DPFLTR_VSS_ID            = 71 /*0x47*/,
    DPFLTR_PNPMEM_ID         = 72 /*0x48*/,
    DPFLTR_PROCESSOR_ID      = 73 /*0x49*/,
    DPFLTR_DMSERVER_ID       = 74 /*0x4A*/,
    DPFLTR_SR_ID             = 75 /*0x4B*/,
    DPFLTR_INFINIBAND_ID     = 76 /*0x4C*/,
    DPFLTR_IHVDRIVER_ID      = 77 /*0x4D*/,
    DPFLTR_IHVVIDEO_ID       = 78 /*0x4E*/,
    DPFLTR_IHVAUDIO_ID       = 79 /*0x4F*/,
    DPFLTR_IHVNETWORK_ID     = 80 /*0x50*/,
    DPFLTR_IHVSTREAMING_ID   = 81 /*0x51*/,
    DPFLTR_IHVBUS_ID         = 82 /*0x52*/,
    DPFLTR_HPS_ID            = 83 /*0x53*/,
    DPFLTR_RTLTHREADPOOL_ID  = 84 /*0x54*/,
    DPFLTR_LDR_ID            = 85 /*0x55*/,
    DPFLTR_TCPIP6_ID         = 86 /*0x56*/,
    DPFLTR_ISAPNP_ID         = 87 /*0x57*/,
    DPFLTR_SHPC_ID           = 88 /*0x58*/,
    DPFLTR_STORPORT_ID       = 89 /*0x59*/,
    DPFLTR_STORMINIPORT_ID   = 90 /*0x5A*/,
    DPFLTR_PRINTSPOOLER_ID   = 91 /*0x5B*/,
    DPFLTR_VSSDYNDISK_ID     = 92 /*0x5C*/,
    DPFLTR_VERIFIER_ID       = 93 /*0x5D*/,
    DPFLTR_VDS_ID            = 94 /*0x5E*/,
    DPFLTR_VDSBAS_ID         = 95 /*0x5F*/,
    DPFLTR_VDSDYN_ID         = 96 /*0x60*/,
    DPFLTR_VDSDYNDR_ID       = 97 /*0x61*/,
    DPFLTR_VDSLDR_ID         = 98 /*0x62*/,
    DPFLTR_VDSUTIL_ID        = 99 /*0x63*/,
    DPFLTR_DFRGIFC_ID        = 100 /*0x64*/,
    DPFLTR_DEFAULT_ID        = 101 /*0x65*/,
    DPFLTR_MM_ID             = 102 /*0x66*/,
    DPFLTR_DFSC_ID           = 103 /*0x67*/,
    DPFLTR_WOW64_ID          = 104 /*0x68*/,
    DPFLTR_ALPC_ID           = 105 /*0x69*/,
    DPFLTR_WDI_ID            = 106 /*0x6A*/,
    DPFLTR_PERFLIB_ID        = 107 /*0x6B*/,
    DPFLTR_KTM_ID            = 108 /*0x6C*/,
    DPFLTR_IOSTRESS_ID       = 109 /*0x6D*/,
    DPFLTR_HEAP_ID           = 110 /*0x6E*/,
    DPFLTR_WHEA_ID           = 111 /*0x6F*/,
    DPFLTR_USERGDI_ID        = 112 /*0x70*/,
    DPFLTR_MMCSS_ID          = 113 /*0x71*/,
    DPFLTR_TPM_ID            = 114 /*0x72*/,
    DPFLTR_THREADORDER_ID    = 115 /*0x73*/,
    DPFLTR_ENVIRON_ID        = 116 /*0x74*/,
    DPFLTR_EMS_ID            = 117 /*0x75*/,
    DPFLTR_WDT_ID            = 118 /*0x76*/,
    DPFLTR_FVEVOL_ID         = 119 /*0x77*/,
    DPFLTR_NDIS_ID           = 120 /*0x78*/,
    DPFLTR_NVCTRACE_ID       = 121 /*0x79*/,
    DPFLTR_LUAFV_ID          = 122 /*0x7A*/,
    DPFLTR_APPCOMPAT_ID      = 123 /*0x7B*/,
    DPFLTR_USBSTOR_ID        = 124 /*0x7C*/,
    DPFLTR_SBP2PORT_ID       = 125 /*0x7D*/,
    DPFLTR_COVERAGE_ID       = 126 /*0x7E*/,
    DPFLTR_CACHEMGR_ID       = 127 /*0x7F*/,
    DPFLTR_MOUNTMGR_ID       = 128 /*0x80*/,
    DPFLTR_CFR_ID            = 129 /*0x81*/,
    DPFLTR_TXF_ID            = 130 /*0x82*/,
    DPFLTR_KSECDD_ID         = 131 /*0x83*/,
    DPFLTR_FLTREGRESS_ID     = 132 /*0x84*/,
    DPFLTR_MPIO_ID           = 133 /*0x85*/,
    DPFLTR_MSDSM_ID          = 134 /*0x86*/,
    DPFLTR_UDFS_ID           = 135 /*0x87*/,
    DPFLTR_PSHED_ID          = 136 /*0x88*/,
    DPFLTR_STORVSP_ID        = 137 /*0x89*/,
    DPFLTR_LSASS_ID          = 138 /*0x8A*/,
    DPFLTR_SSPICLI_ID        = 139 /*0x8B*/,
    DPFLTR_CNG_ID            = 140 /*0x8C*/,
    DPFLTR_EXFAT_ID          = 141 /*0x8D*/,
    DPFLTR_FILETRACE_ID      = 142 /*0x8E*/,
    DPFLTR_XSAVE_ID          = 143 /*0x8F*/,
    DPFLTR_SE_ID             = 144 /*0x90*/,
    DPFLTR_DRIVEEXTENDER_ID  = 145 /*0x91*/,
    DPFLTR_POWER_ID          = 146 /*0x92*/,
    DPFLTR_CRASHDUMPXHCI_ID  = 147 /*0x93*/,
    DPFLTR_GPIO_ID           = 148 /*0x94*/,
    DPFLTR_ENDOFTABLE_ID     = 149 /*0x95*/
}DPFLTR_TYPE, *PDPFLTR_TYPE;

typedef enum _HARDWARE_COUNTER_TYPE  // 2 elements, 0x4 bytes
{
    PMCCounter             = 0 /*0x0*/,
    MaxHardwareCounterType = 1 /*0x1*/
}HARDWARE_COUNTER_TYPE, *PHARDWARE_COUNTER_TYPE;

typedef enum _INTERLOCKED_RESULT  // 3 elements, 0x4 bytes
{
    ResultNegative = 1 /*0x1*/,
    ResultZero     = 0 /*0x0*/,
    ResultPositive = 2 /*0x2*/
}INTERLOCKED_RESULT, *PINTERLOCKED_RESULT;

typedef enum _IRQ_PRIORITY  // 4 elements, 0x4 bytes
{
    IrqPriorityUndefined = 0 /*0x0*/,
    IrqPriorityLow       = 1 /*0x1*/,
    IrqPriorityNormal    = 2 /*0x2*/,
    IrqPriorityHigh      = 3 /*0x3*/
}IRQ_PRIORITY, *PIRQ_PRIORITY;

typedef enum _LOCK_OPERATION  // 3 elements, 0x4 bytes
{
    IoReadAccess   = 0 /*0x0*/,
    IoWriteAccess  = 1 /*0x1*/,
    IoModifyAccess = 2 /*0x2*/
}LOCK_OPERATION, *PLOCK_OPERATION;

typedef enum _NT_PRODUCT_TYPE  // 3 elements, 0x4 bytes
{
    NtProductWinNt    = 1 /*0x1*/,
    NtProductLanManNt = 2 /*0x2*/,
    NtProductServer   = 3 /*0x3*/
}NT_PRODUCT_TYPE, *PNT_PRODUCT_TYPE;

typedef enum _OBJECT_INFORMATION_CLASS  // 7 elements, 0x4 bytes
{
    ObjectBasicInformation      = 0 /*0x0*/,
    ObjectNameInformation       = 1 /*0x1*/,
    ObjectTypeInformation       = 2 /*0x2*/,
    ObjectTypesInformation      = 3 /*0x3*/,
    ObjectHandleFlagInformation = 4 /*0x4*/,
    ObjectSessionInformation    = 5 /*0x5*/,
    MaxObjectInfoClass          = 6 /*0x6*/
}OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;

typedef enum _PCW_CALLBACK_TYPE  // 4 elements, 0x4 bytes
{
    PcwCallbackAddCounter         = 0 /*0x0*/,
    PcwCallbackRemoveCounter      = 1 /*0x1*/,
    PcwCallbackEnumerateInstances = 2 /*0x2*/,
    PcwCallbackCollectData        = 3 /*0x3*/
}PCW_CALLBACK_TYPE, *PPCW_CALLBACK_TYPE;

typedef enum _PERFINFO_KERNELMEMORY_USAGE_TYPE  // 2 elements, 0x4 bytes
{
    PerfInfoMemUsagePfnMetadata = 0 /*0x0*/,
    PerfInfoMemUsageMax         = 1 /*0x1*/
}PERFINFO_KERNELMEMORY_USAGE_TYPE, *PPERFINFO_KERNELMEMORY_USAGE_TYPE;

typedef enum _PERFINFO_MM_STAT  // 4 elements, 0x4 bytes
{
    PerfInfoMMStatNotUsed              = 0 /*0x0*/,
    PerfInfoMMStatAggregatePageCombine = 1 /*0x1*/,
    PerfInfoMMStatIterationPageCombine = 2 /*0x2*/,
    PerfInfoMMStatMax                  = 3 /*0x3*/
}PERFINFO_MM_STAT, *PPERFINFO_MM_STAT;

typedef enum _PF_FILE_ACCESS_TYPE  // 3 elements, 0x4 bytes
{
    PfFileAccessTypeRead  = 0 /*0x0*/,
    PfFileAccessTypeWrite = 1 /*0x1*/,
    PfFileAccessTypeMax   = 2 /*0x2*/
}PF_FILE_ACCESS_TYPE, *PPF_FILE_ACCESS_TYPE;

typedef enum _PROC_HYPERVISOR_STATE  // 3 elements, 0x4 bytes
{
    ProcHypervisorNone    = 0 /*0x0*/,
    ProcHypervisorPresent = 1 /*0x1*/,
    ProcHypervisorPower   = 2 /*0x2*/
}PROC_HYPERVISOR_STATE, *PPROC_HYPERVISOR_STATE;

typedef enum _PROCESSOR_CACHE_TYPE  // 4 elements, 0x4 bytes
{
    CacheUnified     = 0 /*0x0*/,
    CacheInstruction = 1 /*0x1*/,
    CacheData        = 2 /*0x2*/,
    CacheTrace       = 3 /*0x3*/
}PROCESSOR_CACHE_TYPE, *PPROCESSOR_CACHE_TYPE;

typedef enum _REG_NOTIFY_CLASS  // 59 elements, 0x4 bytes
{
    RegNtDeleteKey                    = 0 /*0x0*/,
    RegNtPreDeleteKey                 = 0 /*0x0*/,
    RegNtSetValueKey                  = 1 /*0x1*/,
    RegNtPreSetValueKey               = 1 /*0x1*/,
    RegNtDeleteValueKey               = 2 /*0x2*/,
    RegNtPreDeleteValueKey            = 2 /*0x2*/,
    RegNtSetInformationKey            = 3 /*0x3*/,
    RegNtPreSetInformationKey         = 3 /*0x3*/,
    RegNtRenameKey                    = 4 /*0x4*/,
    RegNtPreRenameKey                 = 4 /*0x4*/,
    RegNtEnumerateKey                 = 5 /*0x5*/,
    RegNtPreEnumerateKey              = 5 /*0x5*/,
    RegNtEnumerateValueKey            = 6 /*0x6*/,
    RegNtPreEnumerateValueKey         = 6 /*0x6*/,
    RegNtQueryKey                     = 7 /*0x7*/,
    RegNtPreQueryKey                  = 7 /*0x7*/,
    RegNtQueryValueKey                = 8 /*0x8*/,
    RegNtPreQueryValueKey             = 8 /*0x8*/,
    RegNtQueryMultipleValueKey        = 9 /*0x9*/,
    RegNtPreQueryMultipleValueKey     = 9 /*0x9*/,
    RegNtPreCreateKey                 = 10 /*0xA*/,
    RegNtPostCreateKey                = 11 /*0xB*/,
    RegNtPreOpenKey                   = 12 /*0xC*/,
    RegNtPostOpenKey                  = 13 /*0xD*/,
    RegNtKeyHandleClose               = 14 /*0xE*/,
    RegNtPreKeyHandleClose            = 14 /*0xE*/,
    RegNtPostDeleteKey                = 15 /*0xF*/,
    RegNtPostSetValueKey              = 16 /*0x10*/,
    RegNtPostDeleteValueKey           = 17 /*0x11*/,
    RegNtPostSetInformationKey        = 18 /*0x12*/,
    RegNtPostRenameKey                = 19 /*0x13*/,
    RegNtPostEnumerateKey             = 20 /*0x14*/,
    RegNtPostEnumerateValueKey        = 21 /*0x15*/,
    RegNtPostQueryKey                 = 22 /*0x16*/,
    RegNtPostQueryValueKey            = 23 /*0x17*/,
    RegNtPostQueryMultipleValueKey    = 24 /*0x18*/,
    RegNtPostKeyHandleClose           = 25 /*0x19*/,
    RegNtPreCreateKeyEx               = 26 /*0x1A*/,
    RegNtPostCreateKeyEx              = 27 /*0x1B*/,
    RegNtPreOpenKeyEx                 = 28 /*0x1C*/,
    RegNtPostOpenKeyEx                = 29 /*0x1D*/,
    RegNtPreFlushKey                  = 30 /*0x1E*/,
    RegNtPostFlushKey                 = 31 /*0x1F*/,
    RegNtPreLoadKey                   = 32 /*0x20*/,
    RegNtPostLoadKey                  = 33 /*0x21*/,
    RegNtPreUnLoadKey                 = 34 /*0x22*/,
    RegNtPostUnLoadKey                = 35 /*0x23*/,
    RegNtPreQueryKeySecurity          = 36 /*0x24*/,
    RegNtPostQueryKeySecurity         = 37 /*0x25*/,
    RegNtPreSetKeySecurity            = 38 /*0x26*/,
    RegNtPostSetKeySecurity           = 39 /*0x27*/,
    RegNtCallbackObjectContextCleanup = 40 /*0x28*/,
    RegNtPreRestoreKey                = 41 /*0x29*/,
    RegNtPostRestoreKey               = 42 /*0x2A*/,
    RegNtPreSaveKey                   = 43 /*0x2B*/,
    RegNtPostSaveKey                  = 44 /*0x2C*/,
    RegNtPreReplaceKey                = 45 /*0x2D*/,
    RegNtPostReplaceKey               = 46 /*0x2E*/,
    MaxRegNtNotifyClass               = 47 /*0x2F*/
}REG_NOTIFY_CLASS, *PREG_NOTIFY_CLASS;

typedef enum _REQUESTER_TYPE  // 3 elements, 0x4 bytes
{
    KernelRequester            = 0 /*0x0*/,
    UserProcessRequester       = 1 /*0x1*/,
    UserSharedServiceRequester = 2 /*0x2*/
}REQUESTER_TYPE, *PREQUESTER_TYPE;

typedef enum _TP_CALLBACK_PRIORITY  // 5 elements, 0x4 bytes
{
    TP_CALLBACK_PRIORITY_HIGH    = 0 /*0x0*/,
    TP_CALLBACK_PRIORITY_NORMAL  = 1 /*0x1*/,
    TP_CALLBACK_PRIORITY_LOW     = 2 /*0x2*/,
    TP_CALLBACK_PRIORITY_INVALID = 3 /*0x3*/,
    TP_CALLBACK_PRIORITY_COUNT   = 3 /*0x3*/
}TP_CALLBACK_PRIORITY, *PTP_CALLBACK_PRIORITY;

typedef enum _TRANSFER_TYPE  // 3 elements, 0x4 bytes
{
    ReadTransfer  = 0 /*0x0*/,
    WriteTransfer = 1 /*0x1*/,
    OtherTransfer = 2 /*0x2*/
}TRANSFER_TYPE, *PTRANSFER_TYPE;

typedef enum _USER_ACTIVITY_PRESENCE  // 5 elements, 0x4 bytes
{
    PowerUserPresent    = 0 /*0x0*/,
    PowerUserNotPresent = 1 /*0x1*/,
    PowerUserInactive   = 2 /*0x2*/,
    PowerUserMaximum    = 3 /*0x3*/,
    PowerUserInvalid    = 3 /*0x3*/
}USER_ACTIVITY_PRESENCE, *PUSER_ACTIVITY_PRESENCE;

typedef enum _WOW64_SHARED_INFORMATION  // 15 elements, 0x4 bytes
{
    SharedNtdll32LdrInitializeThunk                  = 0 /*0x0*/,
    SharedNtdll32KiUserExceptionDispatcher           = 1 /*0x1*/,
    SharedNtdll32KiUserApcDispatcher                 = 2 /*0x2*/,
    SharedNtdll32KiUserCallbackDispatcher            = 3 /*0x3*/,
    SharedNtdll32LdrHotPatchRoutine                  = 4 /*0x4*/,
    SharedNtdll32ExpInterlockedPopEntrySListFault    = 5 /*0x5*/,
    SharedNtdll32ExpInterlockedPopEntrySListResume   = 6 /*0x6*/,
    SharedNtdll32ExpInterlockedPopEntrySListEnd      = 7 /*0x7*/,
    SharedNtdll32RtlUserThreadStart                  = 8 /*0x8*/,
    SharedNtdll32pQueryProcessDebugInformationRemote = 9 /*0x9*/,
    SharedNtdll32EtwpNotificationThread              = 10 /*0xA*/,
    SharedNtdll32BaseAddress                         = 11 /*0xB*/,
    SharedNtdll32RtlpWnfNotificationThread           = 12 /*0xC*/,
    SharedNtdll32LdrSystemDllInitBlock               = 13 /*0xD*/,
    Wow64SharedPageEntriesCount                      = 14 /*0xE*/
}WOW64_SHARED_INFORMATION, *PWOW64_SHARED_INFORMATION;

typedef enum _HSTORAGE_TYPE  // 3 elements, 0x4 bytes
{
    Stable         = 0 /*0x0*/,
    Volatile       = 1 /*0x1*/,
    InvalidStorage = 2 /*0x2*/
}HSTORAGE_TYPE, *PHSTORAGE_TYPE;

typedef enum _KTM_STATE  // 6 elements, 0x4 bytes
{
    KKtmUninitialized  = 0 /*0x0*/,
    KKtmInitialized    = 1 /*0x1*/,
    KKtmRecovering     = 2 /*0x2*/,
    KKtmOnline         = 3 /*0x3*/,
    KKtmRecoveryFailed = 4 /*0x4*/,
    KKtmOffline        = 5 /*0x5*/
}KTM_STATE, *PKTM_STATE;

typedef enum _LSA_FOREST_TRUST_RECORD_TYPE  // 4 elements, 0x4 bytes
{
    ForestTrustTopLevelName   = 0 /*0x0*/,
    ForestTrustTopLevelNameEx = 1 /*0x1*/,
    ForestTrustDomainInfo     = 2 /*0x2*/,
    ForestTrustRecordTypeLast = 2 /*0x2*/
}LSA_FOREST_TRUST_RECORD_TYPE, *PLSA_FOREST_TRUST_RECORD_TYPE;

typedef enum _PROFILE_DEPARTURE_STYLE  // 4 elements, 0x4 bytes
{
    PDS_UPDATE_DEFAULT      = 1 /*0x1*/,
    PDS_UPDATE_ON_REMOVE    = 2 /*0x2*/,
    PDS_UPDATE_ON_INTERFACE = 3 /*0x3*/,
    PDS_UPDATE_ON_EJECT     = 4 /*0x4*/
}PROFILE_DEPARTURE_STYLE, *PPROFILE_DEPARTURE_STYLE;

typedef enum _PROFILE_STATUS  // 5 elements, 0x4 bytes
{
    DOCK_NOTDOCKDEVICE      = 0 /*0x0*/,
    DOCK_QUIESCENT          = 1 /*0x1*/,
    DOCK_ARRIVING           = 2 /*0x2*/,
    DOCK_DEPARTING          = 3 /*0x3*/,
    DOCK_EJECTIRP_COMPLETED = 4 /*0x4*/
}PROFILE_STATUS, *PPROFILE_STATUS;

typedef enum _ReplacesCorHdrNumericDefines  // 24 elements, 0x4 bytes
{
    COMIMAGE_FLAGS_ILONLY                      = 1 /*0x1*/,
    COMIMAGE_FLAGS_32BITREQUIRED               = 2 /*0x2*/,
    COMIMAGE_FLAGS_IL_LIBRARY                  = 4 /*0x4*/,
    COMIMAGE_FLAGS_STRONGNAMESIGNED            = 8 /*0x8*/,
    COMIMAGE_FLAGS_NATIVE_ENTRYPOINT           = 16 /*0x10*/,
    COMIMAGE_FLAGS_TRACKDEBUGDATA              = 65536 /*0x10000*/,
    COR_VERSION_MAJOR_V2                       = 2 /*0x2*/,
    COR_VERSION_MAJOR                          = 2 /*0x2*/,
    COR_VERSION_MINOR                          = 5 /*0x5*/,
    COR_DELETED_NAME_LENGTH                    = 8 /*0x8*/,
    COR_VTABLEGAP_NAME_LENGTH                  = 8 /*0x8*/,
    NATIVE_TYPE_MAX_CB                         = 1 /*0x1*/,
    COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE       = 255 /*0xFF*/,
    IMAGE_COR_MIH_METHODRVA                    = 1 /*0x1*/,
    IMAGE_COR_MIH_EHRVA                        = 2 /*0x2*/,
    IMAGE_COR_MIH_BASICBLOCK                   = 8 /*0x8*/,
    COR_VTABLE_32BIT                           = 1 /*0x1*/,
    COR_VTABLE_64BIT                           = 2 /*0x2*/,
    COR_VTABLE_FROM_UNMANAGED                  = 4 /*0x4*/,
    COR_VTABLE_FROM_UNMANAGED_RETAIN_APPDOMAIN = 8 /*0x8*/,
    COR_VTABLE_CALL_MOST_DERIVED               = 16 /*0x10*/,
    IMAGE_COR_EATJ_THUNK_SIZE                  = 32 /*0x20*/,
    MAX_CLASS_NAME                             = 1024 /*0x400*/,
    MAX_PACKAGE_NAME                           = 1024 /*0x400*/
}ReplacesCorHdrNumericDefines, *PReplacesCorHdrNumericDefines;

typedef enum _UoWActionType  // 15 elements, 0x4 bytes
{
    UoWAddThisKey            = 0 /*0x0*/,
    UoWAddChildKey           = 1 /*0x1*/,
    UoWDeleteThisKey         = 2 /*0x2*/,
    UoWDeleteChildKey        = 3 /*0x3*/,
    UoWSetValueNew           = 4 /*0x4*/,
    UoWSetValueExisting      = 5 /*0x5*/,
    UoWDeleteValue           = 6 /*0x6*/,
    UoWSetKeyUserFlags       = 7 /*0x7*/,
    UoWSetLastWriteTime      = 8 /*0x8*/,
    UoWSetSecurityDescriptor = 9 /*0x9*/,
    UoWRenameSubKey          = 10 /*0xA*/,
    UoWRenameOldSubKey       = 11 /*0xB*/,
    UoWRenameNewSubKey       = 12 /*0xC*/,
    UoWIsolation             = 13 /*0xD*/,
    UoWInvalid               = 14 /*0xE*/
}UoWActionType, *PUoWActionType;

typedef ULONG32 (NEAR CDECL FUNCT_0009_07B8_IdlePrepare) (VOID*, struct _PROCESSOR_IDLE_CONSTRAINTS*, ULONG32, ULONG32*, struct _PROCESSOR_IDLE_DEPENDENCY*);
typedef ULONG32 (NEAR CDECL FUNCT_0009_0852_PerfSelectionHandler) (UINT64, ULONG32, ULONG32, ULONG32, ULONG32, ULONG32*, ULONG32*);
typedef ULONG32 (NEAR CDECL FUNCT_0009_17AB_ProfileDepartureSetMode) (VOID*, enum _PROFILE_DEPARTURE_STYLE);
typedef ULONG32 (NEAR CDECL FUNCT_0009_17B4_ProfileDepartureUpdate) (VOID*);
typedef LONG32 (NEAR CDECL FUNCT_0064_0A0A_AddDevice) (struct _DRIVER_OBJECT*, struct _DEVICE_OBJECT*);
typedef LONG32 (NEAR CDECL FUNCT_0064_0A22_PreAcquireForSectionSynchronization_PreReleaseForSectionSynchronization_PreAcquireForCcFlush_PreReleaseForCcFlush_PreAcquireForModifiedPageWriter_PreReleaseForModifiedPageWriter) (struct _FS_FILTER_CALLBACK_DATA*, VOID**);
typedef LONG32 (NEAR CDECL FUNCT_0064_0D7A_AcquireForModWrite) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, struct _ERESOURCE**, struct _DEVICE_OBJECT*);
typedef LONG32 (NEAR CDECL FUNCT_0064_107D_CompletionRoutine) (struct _DEVICE_OBJECT*, struct _IRP*, VOID*);
typedef LONG32 (NEAR CDECL FUNCT_0064_1082_ReleaseForModWrite) (struct _FILE_OBJECT*, struct _ERESOURCE*, struct _DEVICE_OBJECT*);
typedef LONG32 (NEAR CDECL FUNCT_0064_1087_AcquireForCcFlush_ReleaseForCcFlush) (struct _FILE_OBJECT*, struct _DEVICE_OBJECT*);
typedef LONG32 (NEAR CDECL FUNCT_0064_108B_DriverInit) (struct _DRIVER_OBJECT*, struct _UNICODE_STRING*);
typedef LONG32 (NEAR CDECL FUNCT_0064_1093_MajorFunction) (struct _DEVICE_OBJECT*, struct _IRP*);
typedef LONG32 (NEAR CDECL FUNCT_0064_1166_OpenProcedure) (enum _OB_OPEN_REASON, CHAR, struct _EPROCESS*, VOID*, ULONG32*, ULONG32);
typedef LONG32 (NEAR CDECL FUNCT_0064_117A_ParseProcedure) (VOID*, VOID*, struct _ACCESS_STATE*, CHAR, ULONG32, struct _UNICODE_STRING*, struct _UNICODE_STRING*, VOID*, struct _SECURITY_QUALITY_OF_SERVICE*, VOID**);
typedef LONG32 (NEAR CDECL FUNCT_0064_1186_SecurityProcedure) (VOID*, enum _SECURITY_OPERATION_CODE, ULONG32*, VOID*, ULONG32*, VOID**, enum _POOL_TYPE, struct _GENERIC_MAPPING*, CHAR);
typedef LONG32 (NEAR CDECL FUNCT_0064_1197_QueryNameProcedure) (VOID*, UINT8, struct _OBJECT_NAME_INFORMATION*, ULONG32, ULONG32*, CHAR);
typedef LONG32 (NEAR CDECL FUNCT_0064_15CD_Callback) (enum _PCW_CALLBACK_TYPE, union _PCW_CALLBACK_INFORMATION*, VOID*);
typedef LONG32 (NEAR CDECL FUNCT_0064_16B0_PowerControl) (VOID*, struct _GUID*, VOID*, UINT64, VOID*, UINT64, UINT64*);
typedef LONG32 (NEAR CDECL FUNCT_0064_16BE_DeviceInformation) (VOID*, VOID*, ULONG32);
typedef LONG32 (NEAR CDECL FUNCT_0064_1A55_CommitRoutine) (VOID*, VOID**, UINT64*);
typedef LONG32 (NEAR CDECL FUNCT_0064_1AF5_DestroyProcedure) (VOID*);
typedef LONG32 (NEAR CDECL FUNCT_0064_20BF_NotificationRoutine) (struct _KENLISTMENT*, VOID*, VOID*, ULONG32, union _LARGE_INTEGER*, ULONG32, VOID*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2593_ArbiterHandler) (VOID*, enum _ARBITER_ACTION, struct _ARBITER_PARAMETERS*);
typedef LONG32 (NEAR CDECL FUNCT_0064_25F5_UnpackRequirement) (struct _IO_RESOURCE_DESCRIPTOR*, UINT64*, UINT64*, UINT64*, UINT64*);
typedef LONG32 (NEAR CDECL FUNCT_0064_25FC_PackResource) (struct _IO_RESOURCE_DESCRIPTOR*, UINT64, struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2601_UnpackResource) (struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*, UINT64*, UINT64*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2606_ScoreRequirement) (struct _IO_RESOURCE_DESCRIPTOR*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2609_TestAllocation) (struct _ARBITER_INSTANCE*, struct _ARBITER_TEST_ALLOCATION_PARAMETERS*);
typedef LONG32 (NEAR CDECL FUNCT_0064_260F_RetestAllocation) (struct _ARBITER_INSTANCE*, struct _ARBITER_RETEST_ALLOCATION_PARAMETERS*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2614_CommitAllocation_RollbackAllocation) (struct _ARBITER_INSTANCE*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2617_BootAllocation) (struct _ARBITER_INSTANCE*, struct _ARBITER_BOOT_ALLOCATION_PARAMETERS*);
typedef LONG32 (NEAR CDECL FUNCT_0064_261C_QueryArbitrate) (struct _ARBITER_INSTANCE*, struct _ARBITER_QUERY_ARBITRATE_PARAMETERS*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2621_QueryConflict) (struct _ARBITER_INSTANCE*, struct _ARBITER_QUERY_CONFLICT_PARAMETERS*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2626_AddReserved) (struct _ARBITER_INSTANCE*, struct _ARBITER_ADD_RESERVED_PARAMETERS*);
typedef LONG32 (NEAR CDECL FUNCT_0064_262B_StartArbiter) (struct _ARBITER_INSTANCE*, struct _CM_RESOURCE_LIST*);
typedef LONG32 (NEAR CDECL FUNCT_0064_262F_PreprocessEntry_AllocateEntry) (struct _ARBITER_INSTANCE*, struct _ARBITER_ALLOCATION_STATE*);
typedef LONG32 (NEAR CDECL FUNCT_0064_2637_InitializeRangeList) (struct _ARBITER_INSTANCE*, ULONG32, struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*, struct _RTL_RANGE_LIST*);
typedef LONG32 (NEAR CDECL FUNCT_0064_29C8_WriteRoutine) (union _LARGE_INTEGER*, struct _MDL*);
typedef LONG32 (NEAR CDECL FUNCT_0064_29CE_WritePendingRoutine) (LONG32, union _LARGE_INTEGER*, struct _MDL*, VOID*);
typedef LONG32 (NEAR CDECL FUNCT_0064_29DC_ReadRoutine) (LONG32, union _LARGE_INTEGER*, struct _MDL*);
typedef LONG32 (NEAR CDECL FUNCT_0064_29E1_GetDriveTelemetryRoutine) (ULONG32, ULONG32, VOID*, ULONG32);
typedef UINT8 (NEAR CDECL FUNCT_006E_07CE_IdleIsHalted_IdleInitiateWake) (VOID*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0AC1_FastIoCheckIfPossible) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, ULONG32, UINT8, ULONG32, UINT8, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0ACC_FastIoRead_FastIoWrite) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, ULONG32, UINT8, ULONG32, VOID*, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0AD6_FastIoQueryBasicInfo) (struct _FILE_OBJECT*, UINT8, struct _FILE_BASIC_INFORMATION*, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0AE4_FastIoQueryStandardInfo) (struct _FILE_OBJECT*, UINT8, struct _FILE_STANDARD_INFORMATION*, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0AF2_FastIoLock) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, union _LARGE_INTEGER*, struct _EPROCESS*, ULONG32, UINT8, UINT8, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D42_FastIoUnlockSingle) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, union _LARGE_INTEGER*, struct _EPROCESS*, ULONG32, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D4B_FastIoUnlockAll) (struct _FILE_OBJECT*, struct _EPROCESS*, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D51_FastIoUnlockAllByKey) (struct _FILE_OBJECT*, VOID*, ULONG32, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D58_FastIoDeviceControl) (struct _FILE_OBJECT*, UINT8, VOID*, ULONG32, VOID*, ULONG32, ULONG32, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D6A_FastIoQueryNetworkOpenInfo) (struct _FILE_OBJECT*, UINT8, struct _FILE_NETWORK_OPEN_INFORMATION*, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D80_MdlRead_PrepareMdlWrite) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, ULONG32, ULONG32, struct _MDL**, struct _IO_STATUS_BLOCK*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D94_MdlReadComplete_MdlReadCompleteCompressed) (struct _FILE_OBJECT*, struct _MDL*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D99_MdlWriteComplete_MdlWriteCompleteCompressed) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, struct _MDL*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0D9F_FastIoReadCompressed_FastIoWriteCompressed) (struct _FILE_OBJECT*, union _LARGE_INTEGER*, ULONG32, ULONG32, VOID*, struct _MDL**, struct _IO_STATUS_BLOCK*, struct _COMPRESSED_DATA_INFO*, ULONG32, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_0DB4_FastIoQueryOpen) (struct _IRP*, struct _FILE_NETWORK_OPEN_INFORMATION*, struct _DEVICE_OBJECT*);
typedef UINT8 (NEAR CDECL FUNCT_006E_119F_OkayToCloseProcedure) (struct _EPROCESS*, VOID*, VOID*, CHAR);
typedef UINT8 (NEAR CDECL FUNCT_006E_1517_FileWrite) (struct _HHIVE*, ULONG32, struct _CMP_OFFSET_ARRAY*, ULONG32, ULONG32*);
typedef UINT8 (NEAR CDECL FUNCT_006E_1523_FileRead) (struct _HHIVE*, ULONG32, ULONG32*, VOID*, ULONG32);
typedef UINT8 (NEAR CDECL FUNCT_006E_16CE_AcceptDeviceNotification) (ULONG32, VOID*);
typedef UINT8 (NEAR CDECL FUNCT_006E_16D2_AcceptProcessorNotification) (struct _PEPHANDLE__*, ULONG32, VOID*);
typedef UINT8 (NEAR CDECL FUNCT_006E_198D_AcquireForLazyWrite_AcquireForReadAhead) (VOID*, UINT8);
typedef UINT8 (NEAR CDECL FUNCT_006E_2255_ServiceRoutine) (struct _KINTERRUPT*, VOID*);
typedef UINT8 (NEAR CDECL FUNCT_006E_225A_MessageServiceRoutine) (struct _KINTERRUPT*, VOID*, ULONG32);
typedef UINT8 (NEAR CDECL FUNCT_006E_2633_GetNextAllocationRange_FindSuitableRange_OverrideConflict) (struct _ARBITER_INSTANCE*, struct _ARBITER_ALLOCATION_STATE*);
typedef UINT8 (NEAR CDECL FUNCT_006E_263D_ConflictCallback) (VOID*, struct _RTL_RANGE*);
typedef UINT8 (NEAR CDECL FUNCT_006E_29C5_OpenRoutine) (union _LARGE_INTEGER);
typedef INT64 (NEAR CDECL FUNCT_007F_1DE5_GetCpuClock) ();
typedef VOID (NEAR CDECL FUNCT_00AE_00AD_CleanupGroupCancelCallback_DeRefSecurityDescriptor_PostRoutine) (VOID*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_00B5_FinalizationCallback) (struct _TP_CALLBACK_INSTANCE*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_00D2_ExecuteCallback) (struct _TP_CALLBACK_INSTANCE*, struct _TP_TASK*);
typedef VOID (NEAR CDECL FUNCT_00AE_00D7_Unposted) (struct _TP_TASK*, struct _TP_POOL*);
typedef VOID (NEAR CDECL FUNCT_00AE_0282_PostProcessInitRoutine_DispatchAddress_FinishRoutine) ();
typedef VOID (NEAR CDECL FUNCT_00AE_0526_DeferredRoutine) (struct _KDPC*, VOID*, VOID*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_06AA_KernelRoutine) (struct _KAPC*, FUNCT_00AE_06B3_NormalRoutine**, VOID**, VOID**, VOID**);
typedef VOID (NEAR CDECL FUNCT_00AE_06B3_NormalRoutine) (VOID*, VOID*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_06B8_RundownRoutine) (struct _KAPC*);
typedef VOID (NEAR CDECL FUNCT_00AE_0740_FreeEx) (VOID*, struct _LOOKASIDE_LIST_EX*);
typedef VOID (NEAR CDECL FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead) (VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_07CA_IdleCancel_Free_ComponentActive_ComponentIdle) (VOID*, ULONG32);
typedef VOID (NEAR CDECL FUNCT_00AE_080A_InstantaneousRead) (UINT64, ULONG32*);
typedef VOID (NEAR CDECL FUNCT_00AE_080E_DifferentialRead) (UINT64, UINT64*, UINT64*);
typedef VOID (NEAR CDECL FUNCT_00AE_0846_FeedbackLazyRead) (UINT64, UINT8, UINT8, ULONG32*);
typedef VOID (NEAR CDECL FUNCT_00AE_084C_GetFFHThrottleState) (UINT64*);
typedef VOID (NEAR CDECL FUNCT_00AE_084F_BoostPolicyHandler_StallRoutine) (ULONG32);
typedef VOID (NEAR CDECL FUNCT_00AE_085B_PerfHandler) (UINT64, ULONG32, UINT8);
typedef VOID (NEAR CDECL FUNCT_00AE_08E4_WorkerRoutine) (VOID*, VOID*, VOID*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_0A9D_PostAcquireForSectionSynchronization_PostReleaseForSectionSynchronization_PostAcquireForCcFlush_PostReleaseForCcFlush_PostAcquireForModifiedPageWriter_PostReleaseForModifiedPageWriter) (struct _FS_FILTER_CALLBACK_DATA*, LONG32, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_0C20_MiniPacketCallback) (struct _IO_MINI_COMPLETION_PACKET_USER*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_0D63_AcquireFileForNtCreateSection_ReleaseFileForNtCreateSection) (struct _FILE_OBJECT*);
typedef VOID (NEAR CDECL FUNCT_00AE_0D66_FastIoDetachDevice) (struct _DEVICE_OBJECT*, struct _DEVICE_OBJECT*);
typedef VOID (NEAR CDECL FUNCT_00AE_0DDB_UserApcRoutine) (VOID*, struct _IO_STATUS_BLOCK*, ULONG32);
typedef VOID (NEAR CDECL FUNCT_00AE_0DE0_DriverStartIo_CancelRoutine) (struct _DEVICE_OBJECT*, struct _IRP*);
typedef VOID (NEAR CDECL FUNCT_00AE_108F_DriverUnload) (struct _DRIVER_OBJECT*);
typedef VOID (NEAR CDECL FUNCT_00AE_109D_TimerRoutine) (struct _DEVICE_OBJECT*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_115E_DumpProcedure) (VOID*, struct _OBJECT_DUMP_CONTROL*);
typedef VOID (NEAR CDECL FUNCT_00AE_1174_CloseProcedure) (struct _EPROCESS*, VOID*, UINT64, UINT64);
typedef VOID (NEAR CDECL FUNCT_00AE_16AB_ComponentIdleState) (VOID*, ULONG32, ULONG32);
typedef VOID (NEAR CDECL FUNCT_00AE_16B9_ComponentCriticalTransition) (VOID*, ULONG32, UINT8);
typedef VOID (NEAR CDECL FUNCT_00AE_1924_FlushToLsnRoutine) (VOID*, union _LARGE_INTEGER);
typedef VOID (NEAR CDECL FUNCT_00AE_1928_QueryLogHandleInfoRoutine) (VOID*, UINT16*);
typedef VOID (NEAR CDECL FUNCT_00AE_19CE_Callback) (VOID*, UINT64, ULONG32);
typedef VOID (NEAR CDECL FUNCT_00AE_1E0A_BufferCallback) (struct _WMI_BUFFER_HEADER*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_2112_FreeRoutine) (struct _RTL_AVL_TABLE*, VOID*);
typedef VOID (NEAR CDECL FUNCT_00AE_22BC_Routine) (VOID*, VOID*, struct _IO_WORKITEM*);
typedef VOID (NEAR CDECL FUNCT_00AE_2635_AddAllocation_BacktrackAllocation) (struct _ARBITER_INSTANCE*, struct _ARBITER_ALLOCATION_STATE*);
typedef VOID (NEAR CDECL FUNCT_00AE_2665_CallerCompletion) (struct _DEVICE_OBJECT*, UINT8, union _POWER_STATE, VOID*, struct _IO_STATUS_BLOCK*);
typedef VOID (NEAR CDECL FUNCT_00AE_29E7_GetTransferSizesRoutine) (ULONG32*, ULONG32*);
typedef VOID* (NEAR CDECL FUNCT_00B1_0731_AllocateEx) (enum _POOL_TYPE, UINT64, ULONG32, struct _LOOKASIDE_LIST_EX*);
typedef VOID* (NEAR CDECL FUNCT_00B1_073B_Allocate) (enum _POOL_TYPE, UINT64, ULONG32);
typedef VOID* (NEAR CDECL FUNCT_00B1_1512_Allocate) (ULONG32, UINT8, ULONG32);
typedef VOID* (NEAR CDECL FUNCT_00B1_210E_AllocateRoutine) (struct _RTL_AVL_TABLE*, ULONG32);
typedef enum _EXCEPTION_DISPOSITION (NEAR CDECL FUNCT_015A_0159_Handler) (struct _EXCEPTION_RECORD*, VOID*, struct _CONTEXT*, VOID*);
typedef struct _RUNTIME_FUNCTION* (NEAR CDECL FUNCT_0D1D_0D30_Callback) (UINT64, VOID*);
typedef enum _IO_ALLOCATION_ACTION (NEAR CDECL FUNCT_10B2_10B1_DeviceRoutine) (struct _DEVICE_OBJECT*, struct _IRP*, VOID*, VOID*);
typedef struct _CELL_DATA* (NEAR CDECL FUNCT_14C5_14C4_GetCellRoutine) (struct _HHIVE*, ULONG32);
typedef enum _RTL_GENERIC_COMPARE_RESULTS (NEAR CDECL FUNCT_2105_2104_CompareRoutine) (struct _RTL_AVL_TABLE*, VOID*, VOID*);

