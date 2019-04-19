
          typedef struct _IO_CACHE_INFO    // 1 elements, 0x1 bytes (sizeof)
          {
/*0x000*/     UINT8        CacheAttribute;
          }IO_CACHE_INFO, *PIO_CACHE_INFO;

          typedef struct _IO_CLIENT_EXTENSION             // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _IO_CLIENT_EXTENSION* NextExtension;
/*0x008*/     VOID*        ClientIdentificationAddress;
          }IO_CLIENT_EXTENSION, *PIO_CLIENT_EXTENSION;

          typedef struct _IO_COMPLETION_CONTEXT // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        Port;
/*0x008*/     VOID*        Key;
          }IO_COMPLETION_CONTEXT, *PIO_COMPLETION_CONTEXT;

          typedef struct _IO_DRIVER_CREATE_CONTEXT        // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     INT16        Size;
/*0x002*/     UINT8        _PADDING0_[0x6];
/*0x008*/     struct _ECP_LIST* ExtraCreateParameter;
/*0x010*/     VOID*        DeviceObjectHint;
/*0x018*/     struct _TXN_PARAMETER_BLOCK* TxnParameters;
          }IO_DRIVER_CREATE_CONTEXT, *PIO_DRIVER_CREATE_CONTEXT;

          typedef struct _IO_MINI_COMPLETION_PACKET_USER              // 9 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;                           // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      PacketType;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     VOID*        KeyContext;
/*0x020*/     VOID*        ApcContext;
/*0x028*/     LONG32       IoStatus;
/*0x02C*/     UINT8        _PADDING1_[0x4];
/*0x030*/     UINT64       IoStatusInformation;
/*0x038*/     FUNCT_00AE_0C20_MiniPacketCallback* MiniPacketCallback;
/*0x040*/     VOID*        Context;
/*0x048*/     UINT8        Allocated;
/*0x049*/     UINT8        _PADDING2_[0x7];
          }IO_MINI_COMPLETION_PACKET_USER, *PIO_MINI_COMPLETION_PACKET_USER;

          typedef struct _IO_PRIORITY_INFO       // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Size;
/*0x004*/     ULONG32      ThreadPriority;
/*0x008*/     ULONG32      PagePriority;
/*0x00C*/     enum _IO_PRIORITY_HINT IoPriority;
          }IO_PRIORITY_INFO, *PIO_PRIORITY_INFO;

          typedef struct _IO_REMOVE_LOCK                  // 1 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _IO_REMOVE_LOCK_COMMON_BLOCK Common; // 4 elements, 0x20 bytes (sizeof)
          }IO_REMOVE_LOCK, *PIO_REMOVE_LOCK;

          typedef struct _IO_REMOVE_LOCK_COMMON_BLOCK // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT8        Removed;
/*0x001*/     UINT8        Reserved[3];
/*0x004*/     LONG32       IoCount;
/*0x008*/     struct _KEVENT RemoveEvent;             // 1 elements, 0x18 bytes (sizeof)
          }IO_REMOVE_LOCK_COMMON_BLOCK, *PIO_REMOVE_LOCK_COMMON_BLOCK;

          typedef struct _IO_RESOURCE_DESCRIPTOR           // 7 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT8        Option;
/*0x001*/     UINT8        Type;
/*0x002*/     UINT8        ShareDisposition;
/*0x003*/     UINT8        Spare1;
/*0x004*/     UINT16       Flags;
/*0x006*/     UINT16       Spare2;
              union                                        // 13 elements, 0x18 bytes (sizeof)
              {
                  struct                                   // 4 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             ULONG32      Alignment;
/*0x010*/             union _LARGE_INTEGER MinimumAddress; // 4 elements, 0x8 bytes (sizeof)
/*0x018*/             union _LARGE_INTEGER MaximumAddress; // 4 elements, 0x8 bytes (sizeof)
                  }Port;
                  struct                                   // 4 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             ULONG32      Alignment;
/*0x010*/             union _LARGE_INTEGER MinimumAddress; // 4 elements, 0x8 bytes (sizeof)
/*0x018*/             union _LARGE_INTEGER MaximumAddress; // 4 elements, 0x8 bytes (sizeof)
                  }Memory;
                  struct                                   // 6 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      MinimumVector;
/*0x00C*/             ULONG32      MaximumVector;
/*0x010*/             UINT16       AffinityPolicy;
/*0x012*/             UINT16       Group;
/*0x014*/             enum _IRQ_PRIORITY PriorityPolicy;
/*0x018*/             UINT64       TargetedProcessors;
                  }Interrupt;
                  struct                                   // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             ULONG32      MinimumChannel;
/*0x00C*/             ULONG32      MaximumChannel;
                  }Dma;
                  struct                                   // 4 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      RequestLine;
/*0x00C*/             ULONG32      Reserved;
/*0x010*/             ULONG32      Channel;
/*0x014*/             ULONG32      TransferWidth;
                  }DmaV3;
                  struct                                   // 4 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             ULONG32      Alignment;
/*0x010*/             union _LARGE_INTEGER MinimumAddress; // 4 elements, 0x8 bytes (sizeof)
/*0x018*/             union _LARGE_INTEGER MaximumAddress; // 4 elements, 0x8 bytes (sizeof)
                  }Generic;
                  struct                                   // 1 elements, 0xC bytes (sizeof)
                  {
/*0x008*/             ULONG32      Data[3];
                  }DevicePrivate;
                  struct                                   // 4 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             ULONG32      MinBusNumber;
/*0x010*/             ULONG32      MaxBusNumber;
/*0x014*/             ULONG32      Reserved;
                  }BusNumber;
                  struct                                   // 3 elements, 0xC bytes (sizeof)
                  {
/*0x008*/             ULONG32      Priority;
/*0x00C*/             ULONG32      Reserved1;
/*0x010*/             ULONG32      Reserved2;
                  }ConfigData;
                  struct                                   // 4 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length40;
/*0x00C*/             ULONG32      Alignment40;
/*0x010*/             union _LARGE_INTEGER MinimumAddress; // 4 elements, 0x8 bytes (sizeof)
/*0x018*/             union _LARGE_INTEGER MaximumAddress; // 4 elements, 0x8 bytes (sizeof)
                  }Memory40;
                  struct                                   // 4 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length48;
/*0x00C*/             ULONG32      Alignment48;
/*0x010*/             union _LARGE_INTEGER MinimumAddress; // 4 elements, 0x8 bytes (sizeof)
/*0x018*/             union _LARGE_INTEGER MaximumAddress; // 4 elements, 0x8 bytes (sizeof)
                  }Memory48;
                  struct                                   // 4 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length64;
/*0x00C*/             ULONG32      Alignment64;
/*0x010*/             union _LARGE_INTEGER MinimumAddress; // 4 elements, 0x8 bytes (sizeof)
/*0x018*/             union _LARGE_INTEGER MaximumAddress; // 4 elements, 0x8 bytes (sizeof)
                  }Memory64;
                  struct                                   // 6 elements, 0xC bytes (sizeof)
                  {
/*0x008*/             UINT8        Class;
/*0x009*/             UINT8        Type;
/*0x00A*/             UINT8        Reserved1;
/*0x00B*/             UINT8        Reserved2;
/*0x00C*/             ULONG32      IdLowPart;
/*0x010*/             ULONG32      IdHighPart;
                  }Connection;
              }u;
          }IO_RESOURCE_DESCRIPTOR, *PIO_RESOURCE_DESCRIPTOR;

          typedef struct _IO_RESOURCE_LIST                   // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT16       Version;
/*0x002*/     UINT16       Revision;
/*0x004*/     ULONG32      Count;
/*0x008*/     struct _IO_RESOURCE_DESCRIPTOR Descriptors[1];
          }IO_RESOURCE_LIST, *PIO_RESOURCE_LIST;

          typedef struct _IO_RESOURCE_REQUIREMENTS_LIST // 7 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      ListSize;
/*0x004*/     enum _INTERFACE_TYPE InterfaceType;
/*0x008*/     ULONG32      BusNumber;
/*0x00C*/     ULONG32      SlotNumber;
/*0x010*/     ULONG32      Reserved[3];
/*0x01C*/     ULONG32      AlternativeLists;
/*0x020*/     struct _IO_RESOURCE_LIST List[1];
          }IO_RESOURCE_REQUIREMENTS_LIST, *PIO_RESOURCE_REQUIREMENTS_LIST;

          typedef struct _IO_SECURITY_CONTEXT                   // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _SECURITY_QUALITY_OF_SERVICE* SecurityQos;
/*0x008*/     struct _ACCESS_STATE* AccessState;
/*0x010*/     ULONG32      DesiredAccess;
/*0x014*/     ULONG32      FullCreateOptions;
          }IO_SECURITY_CONTEXT, *PIO_SECURITY_CONTEXT;

          typedef struct _IO_STACK_LOCATION                                             // 9 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     UINT8        MajorFunction;
/*0x001*/     UINT8        MinorFunction;
/*0x002*/     UINT8        Flags;
/*0x003*/     UINT8        Control;
/*0x004*/     UINT8        _PADDING0_[0x4];
              union                                                                     // 38 elements, 0x20 bytes (sizeof)
              {
                  struct                                                                // 5 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             struct _IO_SECURITY_CONTEXT* SecurityContext;
/*0x010*/             ULONG32      Options;
/*0x014*/             UINT8        _PADDING1_[0x4];
/*0x018*/             UINT16       FileAttributes;
/*0x01A*/             UINT16       ShareAccess;
/*0x01C*/             UINT8        _PADDING2_[0x4];
/*0x020*/             ULONG32      EaLength;
/*0x024*/             UINT8        _PADDING3_[0x4];
                  }Create;
                  struct                                                                // 5 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             struct _IO_SECURITY_CONTEXT* SecurityContext;
/*0x010*/             ULONG32      Options;
/*0x014*/             UINT8        _PADDING1_[0x4];
/*0x018*/             UINT16       Reserved;
/*0x01A*/             UINT16       ShareAccess;
/*0x01C*/             UINT8        _PADDING2_[0x4];
/*0x020*/             struct _NAMED_PIPE_CREATE_PARAMETERS* Parameters;
                  }CreatePipe;
                  struct                                                                // 5 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             struct _IO_SECURITY_CONTEXT* SecurityContext;
/*0x010*/             ULONG32      Options;
/*0x014*/             UINT8        _PADDING1_[0x4];
/*0x018*/             UINT16       Reserved;
/*0x01A*/             UINT16       ShareAccess;
/*0x01C*/             UINT8        _PADDING2_[0x4];
/*0x020*/             struct _MAILSLOT_CREATE_PARAMETERS* Parameters;
                  }CreateMailslot;
                  struct                                                                // 3 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             ULONG32      Key;
/*0x014*/             UINT8        _PADDING2_[0x4];
/*0x018*/             union _LARGE_INTEGER ByteOffset;                                  // 4 elements, 0x8 bytes (sizeof)
                  }Read;
                  struct                                                                // 3 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             ULONG32      Key;
/*0x014*/             UINT8        _PADDING2_[0x4];
/*0x018*/             union _LARGE_INTEGER ByteOffset;                                  // 4 elements, 0x8 bytes (sizeof)
                  }Write;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             struct _UNICODE_STRING* FileName;
/*0x018*/             enum _FILE_INFORMATION_CLASS FileInformationClass;
/*0x01C*/             UINT8        _PADDING2_[0x4];
/*0x020*/             ULONG32      FileIndex;
/*0x024*/             UINT8        _PADDING3_[0x4];
                  }QueryDirectory;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             ULONG32      CompletionFilter;
/*0x014*/             UINT8        _PADDING2_[0x4];
                  }NotifyDirectory;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             enum _FILE_INFORMATION_CLASS FileInformationClass;
/*0x014*/             UINT8        _PADDING2_[0x4];
                  }QueryFile;
                  struct                                                                // 7 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             enum _FILE_INFORMATION_CLASS FileInformationClass;
/*0x014*/             UINT8        _PADDING2_[0x4];
/*0x018*/             struct _FILE_OBJECT* FileObject;
                      union                                                             // 3 elements, 0x8 bytes (sizeof)
                      {
                          struct                                                        // 2 elements, 0x8 bytes (sizeof)
                          {
/*0x020*/                     UINT8        ReplaceIfExists;
/*0x021*/                     UINT8        AdvanceOnly;
/*0x022*/                     UINT8        _PADDING3_[0x6];
                          };
/*0x020*/                 ULONG32      ClusterCount;
/*0x020*/                 VOID*        DeleteHandle;
                      };
                  }SetFile;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             VOID*        EaList;
/*0x018*/             ULONG32      EaListLength;
/*0x01C*/             UINT8        _PADDING2_[0x4];
/*0x020*/             ULONG32      EaIndex;
/*0x024*/             UINT8        _PADDING3_[0x4];
                  }QueryEa;
                  struct                                                                // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
                  }SetEa;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             enum _FSINFOCLASS FsInformationClass;
/*0x014*/             UINT8        _PADDING2_[0x4];
                  }QueryVolume;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             enum _FSINFOCLASS FsInformationClass;
/*0x014*/             UINT8        _PADDING2_[0x4];
                  }SetVolume;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             ULONG32      OutputBufferLength;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             ULONG32      InputBufferLength;
/*0x014*/             UINT8        _PADDING2_[0x4];
/*0x018*/             ULONG32      FsControlCode;
/*0x01C*/             UINT8        _PADDING3_[0x4];
/*0x020*/             VOID*        Type3InputBuffer;
                  }FileSystemControl;
                  struct                                                                // 3 elements, 0x18 bytes (sizeof)
                  {
/*0x008*/             union _LARGE_INTEGER* Length;
/*0x010*/             ULONG32      Key;
/*0x014*/             UINT8        _PADDING1_[0x4];
/*0x018*/             union _LARGE_INTEGER ByteOffset;                                  // 4 elements, 0x8 bytes (sizeof)
                  }LockControl;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             ULONG32      OutputBufferLength;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             ULONG32      InputBufferLength;
/*0x014*/             UINT8        _PADDING2_[0x4];
/*0x018*/             ULONG32      IoControlCode;
/*0x01C*/             UINT8        _PADDING3_[0x4];
/*0x020*/             VOID*        Type3InputBuffer;
                  }DeviceIoControl;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      SecurityInformation;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             ULONG32      Length;
/*0x014*/             UINT8        _PADDING2_[0x4];
                  }QuerySecurity;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             ULONG32      SecurityInformation;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             VOID*        SecurityDescriptor;
                  }SetSecurity;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             struct _VPB* Vpb;
/*0x010*/             struct _DEVICE_OBJECT* DeviceObject;
                  }MountVolume;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             struct _VPB* Vpb;
/*0x010*/             struct _DEVICE_OBJECT* DeviceObject;
                  }VerifyVolume;
                  struct                                                                // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             struct _SCSI_REQUEST_BLOCK* Srb;
                  }Scsi;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             VOID*        StartSid;
/*0x018*/             struct _FILE_GET_QUOTA_INFORMATION* SidList;
/*0x020*/             ULONG32      SidListLength;
/*0x024*/             UINT8        _PADDING2_[0x4];
                  }QueryQuota;
                  struct                                                                // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x008*/             ULONG32      Length;
                  }SetQuota;
                  struct                                                                // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x008*/             enum _DEVICE_RELATION_TYPE Type;
                  }QueryDeviceRelations;
                  struct                                                                // 5 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             struct _GUID* InterfaceType;
/*0x010*/             UINT16       Size;
/*0x012*/             UINT16       Version;
/*0x014*/             UINT8        _PADDING1_[0x4];
/*0x018*/             struct _INTERFACE* Interface;
/*0x020*/             VOID*        InterfaceSpecificData;
                  }QueryInterface;
                  struct                                                                // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             struct _DEVICE_CAPABILITIES* Capabilities;
                  }DeviceCapabilities;
                  struct                                                                // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             struct _IO_RESOURCE_REQUIREMENTS_LIST* IoResourceRequirementList;
                  }FilterResourceRequirements;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             ULONG32      WhichSpace;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             VOID*        Buffer;
/*0x018*/             ULONG32      Offset;
/*0x01C*/             UINT8        _PADDING2_[0x4];
/*0x020*/             ULONG32      Length;
/*0x024*/             UINT8        _PADDING3_[0x4];
                  }ReadWriteConfig;
                  struct                                                                // 1 elements, 0x1 bytes (sizeof)
                  {
/*0x008*/             UINT8        Lock;
                  }SetLock;
                  struct                                                                // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x008*/             enum _BUS_QUERY_ID_TYPE IdType;
                  }QueryId;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             enum _DEVICE_TEXT_TYPE DeviceTextType;
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             ULONG32      LocaleId;
/*0x014*/             UINT8        _PADDING2_[0x4];
                  }QueryDeviceText;
                  struct                                                                // 3 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             UINT8        InPath;
/*0x009*/             UINT8        Reserved[3];
/*0x00C*/             UINT8        _PADDING1_[0x4];
/*0x010*/             enum _DEVICE_USAGE_NOTIFICATION_TYPE Type;
/*0x014*/             UINT8        _PADDING2_[0x4];
                  }UsageNotification;
                  struct                                                                // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x008*/             enum _SYSTEM_POWER_STATE PowerState;
                  }WaitWake;
                  struct                                                                // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             struct _POWER_SEQUENCE* PowerSequence;
                  }PowerSequence;
                  struct                                                                // 5 elements, 0x20 bytes (sizeof)
                  {
                      union                                                             // 2 elements, 0x8 bytes (sizeof)
                      {
/*0x008*/                 ULONG32      SystemContext;
/*0x008*/                 struct _SYSTEM_POWER_STATE_CONTEXT SystemPowerStateContext;   // 8 elements, 0x4 bytes (sizeof)
                      };
/*0x010*/             enum _POWER_STATE_TYPE Type;
/*0x014*/             UINT8        _PADDING1_[0x4];
/*0x018*/             union _POWER_STATE State;                                         // 2 elements, 0x4 bytes (sizeof)
/*0x01C*/             UINT8        _PADDING2_[0x4];
/*0x020*/             enum _POWER_ACTION ShutdownType;
/*0x024*/             UINT8        _PADDING3_[0x4];
                  }Power;
                  struct                                                                // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x008*/             struct _CM_RESOURCE_LIST* AllocatedResources;
/*0x010*/             struct _CM_RESOURCE_LIST* AllocatedResourcesTranslated;
                  }StartDevice;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             UINT64       ProviderId;
/*0x010*/             VOID*        DataPath;
/*0x018*/             ULONG32      BufferSize;
/*0x01C*/             UINT8        _PADDING1_[0x4];
/*0x020*/             VOID*        Buffer;
                  }WMI;
                  struct                                                                // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x008*/             VOID*        Argument1;
/*0x010*/             VOID*        Argument2;
/*0x018*/             VOID*        Argument3;
/*0x020*/             VOID*        Argument4;
                  }Others;
              }Parameters;
/*0x028*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x030*/     struct _FILE_OBJECT* FileObject;
/*0x038*/     FUNCT_0064_107D_CompletionRoutine* CompletionRoutine;
/*0x040*/     VOID*        Context;
          }IO_STACK_LOCATION, *PIO_STACK_LOCATION;

          typedef struct _IO_STATUS_BLOCK // 3 elements, 0x10 bytes (sizeof)
          {
              union                       // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         LONG32       Status;
/*0x000*/         VOID*        Pointer;
              };
/*0x008*/     UINT64       Information;
          }IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

          typedef struct _IO_STATUS_BLOCK32 // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     LONG32       Status;
/*0x004*/     ULONG32      Information;
          }IO_STATUS_BLOCK32, *PIO_STATUS_BLOCK32;

          typedef struct _IO_TIMER                        // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     INT16        TimerFlag;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _LIST_ENTRY TimerList;               // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     FUNCT_00AE_109D_TimerRoutine* TimerRoutine;
/*0x020*/     VOID*        Context;
/*0x028*/     struct _DEVICE_OBJECT* DeviceObject;
          }IO_TIMER, *PIO_TIMER;

          typedef struct _IO_WORKITEM           // 6 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _WORK_QUEUE_ITEM WorkItem; // 3 elements, 0x20 bytes (sizeof)
/*0x020*/     FUNCT_00AE_22BC_Routine* Routine;
/*0x028*/     VOID*        IoObject;
/*0x030*/     VOID*        Context;
/*0x038*/     ULONG32      Type;
/*0x03C*/     struct _GUID ActivityId;          // 4 elements, 0x10 bytes (sizeof)
/*0x04C*/     UINT8        _PADDING0_[0x4];
          }IO_WORKITEM, *PIO_WORKITEM;


          typedef struct _IOP_FILE_OBJECT_EXTENSION     // 3 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      FoExtFlags;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        FoExtPerTypeExtension[7];
/*0x040*/     enum _IOP_PRIORITY_HINT FoIoPriorityHint;
/*0x044*/     UINT8        _PADDING1_[0x4];
          }IOP_FILE_OBJECT_EXTENSION, *PIOP_FILE_OBJECT_EXTENSION;

          typedef struct _IOP_IRP_EXTENSION         // 6 elements, 0x18 bytes (sizeof)
          {
              union                                 // 2 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         UINT16       ExtensionFlags;
                  struct                            // 3 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             ULONG32      Allocated : 1;   // 0 BitPosition
/*0x000*/             ULONG32      PropagateId : 1; // 1 BitPosition
/*0x000*/             ULONG32      SpareBits : 14;  // 2 BitPosition
                  };
              };
/*0x004*/     UINT16       TypesAllocated;
/*0x006*/     UINT8        _PADDING0_[0x2];
/*0x008*/     struct _GUID ActivityId;              // 4 elements, 0x10 bytes (sizeof)
          }IOP_IRP_EXTENSION, *PIOP_IRP_EXTENSION;

          typedef struct _IOV_FORCED_PENDING_TRACE // 3 elements, 0x200 bytes (sizeof)
          {
/*0x000*/     struct _IRP* Irp;
/*0x008*/     struct _ETHREAD* Thread;
/*0x010*/     VOID*        StackTrace[62];
          }IOV_FORCED_PENDING_TRACE, *PIOV_FORCED_PENDING_TRACE;

          typedef struct _IOV_IRP_TRACE               // 7 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     struct _IRP* Irp;
/*0x008*/     struct _KTHREAD* Thread;
              union                                   // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                              // 2 elements, 0x4 bytes (sizeof)
                  {
/*0x010*/             INT16        KernelApcDisable;
/*0x012*/             INT16        SpecialApcDisable;
                  };
/*0x010*/         ULONG32      CombinedApcDisable;
              };
/*0x014*/     UINT8        Irql;
/*0x015*/     UINT8        _PADDING0_[0x3];
/*0x018*/     VOID*        StackTrace[13];
          }IOV_IRP_TRACE, *PIOV_IRP_TRACE;

          typedef struct _IRP                                              // 21 elements, 0xD0 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     UINT16       Size;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _MDL* MdlAddress;
/*0x010*/     ULONG32      Flags;
/*0x014*/     UINT8        _PADDING1_[0x4];
              union                                                        // 3 elements, 0x8 bytes (sizeof)
              {
/*0x018*/         struct _IRP* MasterIrp;
/*0x018*/         LONG32       IrpCount;
/*0x018*/         VOID*        SystemBuffer;
              }AssociatedIrp;
/*0x020*/     struct _LIST_ENTRY ThreadListEntry;                          // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     struct _IO_STATUS_BLOCK IoStatus;                            // 3 elements, 0x10 bytes (sizeof)
/*0x040*/     CHAR         RequestorMode;
/*0x041*/     UINT8        PendingReturned;
/*0x042*/     CHAR         StackCount;
/*0x043*/     CHAR         CurrentLocation;
/*0x044*/     UINT8        Cancel;
/*0x045*/     UINT8        CancelIrql;
/*0x046*/     CHAR         ApcEnvironment;
/*0x047*/     UINT8        AllocationFlags;
/*0x048*/     struct _IO_STATUS_BLOCK* UserIosb;
/*0x050*/     struct _KEVENT* UserEvent;
              union                                                        // 2 elements, 0x10 bytes (sizeof)
              {
                  struct                                                   // 3 elements, 0x10 bytes (sizeof)
                  {
                      union                                                // 2 elements, 0x8 bytes (sizeof)
                      {
/*0x058*/                 FUNCT_00AE_0DDB_UserApcRoutine* UserApcRoutine;
/*0x058*/                 VOID*        IssuingProcess;
                      };
/*0x060*/             VOID*        UserApcContext;
                  }AsynchronousParameters;
/*0x058*/         union _LARGE_INTEGER AllocationSize;                     // 4 elements, 0x8 bytes (sizeof)
              }Overlay;
/*0x068*/     FUNCT_00AE_0DE0_DriverStartIo_CancelRoutine* CancelRoutine;
/*0x070*/     VOID*        UserBuffer;
              union                                                        // 3 elements, 0x58 bytes (sizeof)
              {
                  struct                                                   // 9 elements, 0x58 bytes (sizeof)
                  {
                      union                                                // 2 elements, 0x20 bytes (sizeof)
                      {
/*0x078*/                 struct _KDEVICE_QUEUE_ENTRY DeviceQueueEntry;    // 3 elements, 0x18 bytes (sizeof)
/*0x078*/                 VOID*        DriverContext[4];
                      };
/*0x098*/             struct _ETHREAD* Thread;
/*0x0A0*/             CHAR*        AuxiliaryBuffer;
/*0x0A8*/             struct _LIST_ENTRY ListEntry;                        // 2 elements, 0x10 bytes (sizeof)
                      union                                                // 2 elements, 0x8 bytes (sizeof)
                      {
/*0x0B8*/                 struct _IO_STACK_LOCATION* CurrentStackLocation;
/*0x0B8*/                 ULONG32      PacketType;
                      };
/*0x0C0*/             struct _FILE_OBJECT* OriginalFileObject;
/*0x0C8*/             VOID*        IrpExtension;
                  }Overlay;
/*0x078*/         struct _KAPC Apc;                                        // 17 elements, 0x58 bytes (sizeof)
/*0x078*/         VOID*        CompletionKey;
              }Tail;
          }IRP, *PIRP;

typedef enum _IO_ALLOCATION_ACTION  // 3 elements, 0x4 bytes
{
    KeepObject                    = 1 /*0x1*/,
    DeallocateObject              = 2 /*0x2*/,
    DeallocateObjectKeepRegisters = 3 /*0x3*/
}IO_ALLOCATION_ACTION, *PIO_ALLOCATION_ACTION;

typedef enum _IO_PAGING_PRIORITY  // 5 elements, 0x4 bytes
{
    IoPagingPriorityInvalid   = 0 /*0x0*/,
    IoPagingPriorityNormal    = 1 /*0x1*/,
    IoPagingPriorityHigh      = 2 /*0x2*/,
    IoPagingPriorityReserved1 = 3 /*0x3*/,
    IoPagingPriorityReserved2 = 4 /*0x4*/
}IO_PAGING_PRIORITY, *PIO_PAGING_PRIORITY;

typedef enum _IO_PRIORITY_HINT  // 6 elements, 0x4 bytes
{
    IoPriorityVeryLow  = 0 /*0x0*/,
    IoPriorityLow      = 1 /*0x1*/,
    IoPriorityNormal   = 2 /*0x2*/,
    IoPriorityHigh     = 3 /*0x3*/,
    IoPriorityCritical = 4 /*0x4*/,
    MaxIoPriorityTypes = 5 /*0x5*/
}IO_PRIORITY_HINT, *PIO_PRIORITY_HINT;

typedef enum _IO_SESSION_STATE  // 9 elements, 0x4 bytes
{
    IoSessionStateCreated              = 1 /*0x1*/,
    IoSessionStateInitialized          = 2 /*0x2*/,
    IoSessionStateConnected            = 3 /*0x3*/,
    IoSessionStateDisconnected         = 4 /*0x4*/,
    IoSessionStateDisconnectedLoggedOn = 5 /*0x5*/,
    IoSessionStateLoggedOn             = 6 /*0x6*/,
    IoSessionStateLoggedOff            = 7 /*0x7*/,
    IoSessionStateTerminated           = 8 /*0x8*/,
    IoSessionStateMax                  = 9 /*0x9*/
}IO_SESSION_STATE, *PIO_SESSION_STATE;

typedef enum _IOP_PRIORITY_HINT  // 7 elements, 0x4 bytes
{
    IopIoPriorityNotSet   = 0 /*0x0*/,
    IopIoPriorityVeryLow  = 1 /*0x1*/,
    IopIoPriorityLow      = 2 /*0x2*/,
    IopIoPriorityNormal   = 3 /*0x3*/,
    IopIoPriorityHigh     = 4 /*0x4*/,
    IopIoPriorityCritical = 5 /*0x5*/,
    MaxIopIoPriorityTypes = 6 /*0x6*/
}IOP_PRIORITY_HINT, *PIOP_PRIORITY_HINT;

          typedef struct _BUS_EXTENSION_LIST          // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        Next;
/*0x008*/     struct _PI_BUS_EXTENSION* BusExtension;
          }BUS_EXTENSION_LIST, *PBUS_EXTENSION_LIST;

          typedef struct _DEVICE_CAPABILITIES          // 30 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     UINT16       Size;
/*0x002*/     UINT16       Version;
              struct                                   // 20 elements, 0x4 bytes (sizeof)
              {
/*0x004*/         ULONG32      DeviceD1 : 1;           // 0 BitPosition
/*0x004*/         ULONG32      DeviceD2 : 1;           // 1 BitPosition
/*0x004*/         ULONG32      LockSupported : 1;      // 2 BitPosition
/*0x004*/         ULONG32      EjectSupported : 1;     // 3 BitPosition
/*0x004*/         ULONG32      Removable : 1;          // 4 BitPosition
/*0x004*/         ULONG32      DockDevice : 1;         // 5 BitPosition
/*0x004*/         ULONG32      UniqueID : 1;           // 6 BitPosition
/*0x004*/         ULONG32      SilentInstall : 1;      // 7 BitPosition
/*0x004*/         ULONG32      RawDeviceOK : 1;        // 8 BitPosition
/*0x004*/         ULONG32      SurpriseRemovalOK : 1;  // 9 BitPosition
/*0x004*/         ULONG32      WakeFromD0 : 1;         // 10 BitPosition
/*0x004*/         ULONG32      WakeFromD1 : 1;         // 11 BitPosition
/*0x004*/         ULONG32      WakeFromD2 : 1;         // 12 BitPosition
/*0x004*/         ULONG32      WakeFromD3 : 1;         // 13 BitPosition
/*0x004*/         ULONG32      HardwareDisabled : 1;   // 14 BitPosition
/*0x004*/         ULONG32      NonDynamic : 1;         // 15 BitPosition
/*0x004*/         ULONG32      WarmEjectSupported : 1; // 16 BitPosition
/*0x004*/         ULONG32      NoDisplayInUI : 1;      // 17 BitPosition
/*0x004*/         ULONG32      Reserved1 : 1;          // 18 BitPosition
/*0x004*/         ULONG32      Reserved : 13;          // 19 BitPosition
              };
/*0x008*/     ULONG32      Address;
/*0x00C*/     ULONG32      UINumber;
/*0x010*/     enum _DEVICE_POWER_STATE DeviceState[7];
/*0x02C*/     enum _SYSTEM_POWER_STATE SystemWake;
/*0x030*/     enum _DEVICE_POWER_STATE DeviceWake;
/*0x034*/     ULONG32      D1Latency;
/*0x038*/     ULONG32      D2Latency;
/*0x03C*/     ULONG32      D3Latency;
          }DEVICE_CAPABILITIES, *PDEVICE_CAPABILITIES;

          typedef struct _DEVICE_MAP                               // 6 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _OBJECT_DIRECTORY* DosDevicesDirectory;
/*0x008*/     struct _OBJECT_DIRECTORY* GlobalDosDevicesDirectory;
/*0x010*/     VOID*        DosDevicesDirectoryHandle;
/*0x018*/     ULONG32      ReferenceCount;
/*0x01C*/     ULONG32      DriveMap;
/*0x020*/     UINT8        DriveType[32];
          }DEVICE_MAP, *PDEVICE_MAP;

          typedef struct _DEVICE_NODE                                      // 63 elements, 0x2A8 bytes (sizeof)
          {
/*0x000*/     struct _DEVICE_NODE* Sibling;
/*0x008*/     struct _DEVICE_NODE* Child;
/*0x010*/     struct _DEVICE_NODE* Parent;
/*0x018*/     struct _DEVICE_NODE* LastChild;
/*0x020*/     struct _DEVICE_OBJECT* PhysicalDeviceObject;
/*0x028*/     struct _UNICODE_STRING InstancePath;                         // 3 elements, 0x10 bytes (sizeof)
/*0x038*/     struct _UNICODE_STRING ServiceName;                          // 3 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _IRP* PendingIrp;
/*0x050*/     ULONG32      Level;
/*0x054*/     UINT8        _PADDING0_[0x4];
/*0x058*/     struct _PO_DEVICE_NOTIFY Notify;                             // 12 elements, 0x68 bytes (sizeof)
/*0x0C0*/     struct _PO_IRP_MANAGER PoIrpManager;                         // 2 elements, 0x20 bytes (sizeof)
/*0x0E0*/     struct _POP_FX_DEVICE* FxDevice;
/*0x0E8*/     LONG32       FxDeviceLock;
/*0x0EC*/     LONG32       FxActivationCount;
/*0x0F0*/     LONG32       FxSleepCount;
/*0x0F4*/     UINT8        _PADDING1_[0x4];
/*0x0F8*/     struct _POP_FX_PLUGIN* Plugin;
/*0x100*/     struct _UNICODE_STRING UniqueId;                             // 3 elements, 0x10 bytes (sizeof)
/*0x110*/     ULONG32      PowerFlags;
/*0x114*/     enum _PNP_DEVNODE_STATE State;
/*0x118*/     enum _PNP_DEVNODE_STATE PreviousState;
/*0x11C*/     enum _PNP_DEVNODE_STATE StateHistory[20];
/*0x16C*/     ULONG32      StateHistoryEntry;
/*0x170*/     LONG32       CompletionStatus;
/*0x174*/     ULONG32      Flags;
/*0x178*/     ULONG32      UserFlags;
/*0x17C*/     ULONG32      Problem;
/*0x180*/     struct _CM_RESOURCE_LIST* ResourceList;
/*0x188*/     struct _CM_RESOURCE_LIST* ResourceListTranslated;
/*0x190*/     struct _DEVICE_OBJECT* DuplicatePDO;
/*0x198*/     struct _IO_RESOURCE_REQUIREMENTS_LIST* ResourceRequirements;
/*0x1A0*/     enum _INTERFACE_TYPE InterfaceType;
/*0x1A4*/     ULONG32      BusNumber;
/*0x1A8*/     enum _INTERFACE_TYPE ChildInterfaceType;
/*0x1AC*/     ULONG32      ChildBusNumber;
/*0x1B0*/     UINT16       ChildBusTypeIndex;
/*0x1B2*/     UINT8        RemovalPolicy;
/*0x1B3*/     UINT8        HardwareRemovalPolicy;
/*0x1B4*/     UINT8        _PADDING2_[0x4];
/*0x1B8*/     struct _LIST_ENTRY TargetDeviceNotify;                       // 2 elements, 0x10 bytes (sizeof)
/*0x1C8*/     struct _LIST_ENTRY DeviceArbiterList;                        // 2 elements, 0x10 bytes (sizeof)
/*0x1D8*/     struct _LIST_ENTRY DeviceTranslatorList;                     // 2 elements, 0x10 bytes (sizeof)
/*0x1E8*/     UINT16       NoTranslatorMask;
/*0x1EA*/     UINT16       QueryTranslatorMask;
/*0x1EC*/     UINT16       NoArbiterMask;
/*0x1EE*/     UINT16       QueryArbiterMask;
              union                                                        // 3 elements, 0x8 bytes (sizeof)
              {
/*0x1F0*/         struct _DEVICE_NODE* LegacyDeviceNode;
/*0x1F0*/         struct _DEVICE_RELATIONS* PendingDeviceRelations;
/*0x1F0*/         VOID*        Information;
              }OverUsed1;
              union                                                        // 1 elements, 0x8 bytes (sizeof)
              {
/*0x1F8*/         struct _DEVICE_NODE* NextResourceDeviceNode;
              }OverUsed2;
/*0x200*/     struct _CM_RESOURCE_LIST* BootResources;
/*0x208*/     struct _CM_RESOURCE_LIST* BootResourcesTranslated;
/*0x210*/     ULONG32      CapabilityFlags;
/*0x214*/     UINT8        _PADDING3_[0x4];
              struct                                                       // 3 elements, 0x20 bytes (sizeof)
              {
/*0x218*/         enum _PROFILE_STATUS DockStatus;
/*0x21C*/         UINT8        _PADDING4_[0x4];
/*0x220*/         struct _LIST_ENTRY ListEntry;                            // 2 elements, 0x10 bytes (sizeof)
/*0x230*/         UINT16*      SerialNumber;
              }DockInfo;
/*0x238*/     ULONG32      DisableableDepends;
/*0x23C*/     UINT8        _PADDING4_[0x4];
/*0x240*/     struct _LIST_ENTRY PendedSetInterfaceState;                  // 2 elements, 0x10 bytes (sizeof)
/*0x250*/     struct _LIST_ENTRY LegacyBusListEntry;                       // 2 elements, 0x10 bytes (sizeof)
/*0x260*/     ULONG32      DriverUnloadRetryCount;
/*0x264*/     UINT8        _PADDING5_[0x4];
/*0x268*/     struct _DEVICE_NODE* PreviousParent;
/*0x270*/     ULONG32      DeletedChildren;
/*0x274*/     ULONG32      NumaNodeIndex;
/*0x278*/     struct _GUID ContainerID;                                    // 4 elements, 0x10 bytes (sizeof)
/*0x288*/     UINT8        OverrideFlags;
/*0x289*/     UINT8        _PADDING6_[0x3];
/*0x28C*/     ULONG32      DeviceIdsHash;
/*0x290*/     UINT8        RequiresUnloadedDriver;
/*0x291*/     UINT8        _PADDING7_[0x7];
/*0x298*/     struct _PENDING_RELATIONS_LIST_ENTRY* PendingEjectRelations;
/*0x2A0*/     ULONG32      StateFlags;
/*0x2A4*/     UINT8        _PADDING8_[0x4];
          }DEVICE_NODE, *PDEVICE_NODE;

          typedef struct _DEVICE_OBJECT                        // 25 elements, 0x150 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     UINT16       Size;
/*0x004*/     LONG32       ReferenceCount;
/*0x008*/     struct _DRIVER_OBJECT* DriverObject;
/*0x010*/     struct _DEVICE_OBJECT* NextDevice;
/*0x018*/     struct _DEVICE_OBJECT* AttachedDevice;
/*0x020*/     struct _IRP* CurrentIrp;
/*0x028*/     struct _IO_TIMER* Timer;
/*0x030*/     ULONG32      Flags;
/*0x034*/     ULONG32      Characteristics;
/*0x038*/     struct _VPB* Vpb;
/*0x040*/     VOID*        DeviceExtension;
/*0x048*/     ULONG32      DeviceType;
/*0x04C*/     CHAR         StackSize;
/*0x04D*/     UINT8        _PADDING0_[0x3];
              union                                            // 2 elements, 0x48 bytes (sizeof)
              {
/*0x050*/         struct _LIST_ENTRY ListEntry;                // 2 elements, 0x10 bytes (sizeof)
/*0x050*/         struct _WAIT_CONTEXT_BLOCK Wcb;              // 12 elements, 0x48 bytes (sizeof)
              }Queue;
/*0x098*/     ULONG32      AlignmentRequirement;
/*0x09C*/     UINT8        _PADDING1_[0x4];
/*0x0A0*/     struct _KDEVICE_QUEUE DeviceQueue;               // 7 elements, 0x28 bytes (sizeof)
/*0x0C8*/     struct _KDPC Dpc;                                // 9 elements, 0x40 bytes (sizeof)
/*0x108*/     ULONG32      ActiveThreadCount;
/*0x10C*/     UINT8        _PADDING2_[0x4];
/*0x110*/     VOID*        SecurityDescriptor;
/*0x118*/     struct _KEVENT DeviceLock;                       // 1 elements, 0x18 bytes (sizeof)
/*0x130*/     UINT16       SectorSize;
/*0x132*/     UINT16       Spare1;
/*0x134*/     UINT8        _PADDING3_[0x4];
/*0x138*/     struct _DEVOBJ_EXTENSION* DeviceObjectExtension;
/*0x140*/     VOID*        Reserved;
/*0x148*/     UINT8        _PADDING4_[0x8];
          }DEVICE_OBJECT, *PDEVICE_OBJECT;

          typedef struct _DEVICE_OBJECT_POWER_EXTENSION // 13 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     ULONG32      IdleCount;
/*0x004*/     ULONG32      BusyCount;
/*0x008*/     ULONG32      BusyReference;
/*0x00C*/     ULONG32      TotalBusyCount;
/*0x010*/     ULONG32      ConservationIdleTime;
/*0x014*/     ULONG32      PerformanceIdleTime;
/*0x018*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x020*/     struct _LIST_ENTRY IdleList;              // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     enum _POP_DEVICE_IDLE_TYPE IdleType;
/*0x034*/     enum _DEVICE_POWER_STATE IdleState;
/*0x038*/     enum _DEVICE_POWER_STATE CurrentState;
/*0x03C*/     UINT8        _PADDING0_[0x4];
/*0x040*/     struct _LIST_ENTRY Volume;                // 2 elements, 0x10 bytes (sizeof)
              union                                     // 1 elements, 0x8 bytes (sizeof)
              {
                  struct                                // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x050*/             ULONG32      IdleTime;
/*0x054*/             ULONG32      NonIdleTime;
                  }Disk;
              }Specific;
          }DEVICE_OBJECT_POWER_EXTENSION, *PDEVICE_OBJECT_POWER_EXTENSION;

          typedef struct _DEVICE_RELATIONS       // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _DEVICE_OBJECT* Objects[1];
          }DEVICE_RELATIONS, *PDEVICE_RELATIONS;

          typedef struct _DEVOBJ_EXTENSION                 // 14 elements, 0x70 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     UINT16       Size;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x010*/     ULONG32      PowerFlags;
/*0x014*/     UINT8        _PADDING1_[0x4];
/*0x018*/     struct _DEVICE_OBJECT_POWER_EXTENSION* Dope;
/*0x020*/     ULONG32      ExtensionFlags;
/*0x024*/     UINT8        _PADDING2_[0x4];
/*0x028*/     VOID*        DeviceNode;
/*0x030*/     struct _DEVICE_OBJECT* AttachedTo;
/*0x038*/     LONG32       StartIoCount;
/*0x03C*/     LONG32       StartIoKey;
/*0x040*/     ULONG32      StartIoFlags;
/*0x044*/     UINT8        _PADDING3_[0x4];
/*0x048*/     struct _VPB* Vpb;
/*0x050*/     struct _LIST_ENTRY DependentList;            // 2 elements, 0x10 bytes (sizeof)
/*0x060*/     struct _LIST_ENTRY ProviderList;             // 2 elements, 0x10 bytes (sizeof)
          }DEVOBJ_EXTENSION, *PDEVOBJ_EXTENSION;

          typedef struct _DRIVER_EXTENSION                        // 8 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     struct _DRIVER_OBJECT* DriverObject;
/*0x008*/     FUNCT_0064_0A0A_AddDevice* AddDevice;
/*0x010*/     ULONG32      Count;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     struct _UNICODE_STRING ServiceKeyName;              // 3 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _IO_CLIENT_EXTENSION* ClientDriverExtension;
/*0x030*/     struct _FS_FILTER_CALLBACKS* FsFilterCallbacks;
/*0x038*/     VOID*        KseCallbacks;
/*0x040*/     VOID*        DvCallbacks;
          }DRIVER_EXTENSION, *PDRIVER_EXTENSION;

          typedef struct _DRIVER_OBJECT                                   // 15 elements, 0x150 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     INT16        Size;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x010*/     ULONG32      Flags;
/*0x014*/     UINT8        _PADDING1_[0x4];
/*0x018*/     VOID*        DriverStart;
/*0x020*/     ULONG32      DriverSize;
/*0x024*/     UINT8        _PADDING2_[0x4];
/*0x028*/     VOID*        DriverSection;
/*0x030*/     struct _DRIVER_EXTENSION* DriverExtension;
/*0x038*/     struct _UNICODE_STRING DriverName;                          // 3 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _UNICODE_STRING* HardwareDatabase;
/*0x050*/     struct _FAST_IO_DISPATCH* FastIoDispatch;
/*0x058*/     FUNCT_0064_108B_DriverInit* DriverInit;
/*0x060*/     FUNCT_00AE_0DE0_DriverStartIo_CancelRoutine* DriverStartIo;
/*0x068*/     FUNCT_00AE_108F_DriverUnload* DriverUnload;
/*0x070*/     FUNCT_0064_1093_MajorFunction* MajorFunction[28];
          }DRIVER_OBJECT, *PDRIVER_OBJECT;

          typedef struct _FAST_IO_DISPATCH                                                                                // 28 elements, 0xE0 bytes (sizeof)
          {
/*0x000*/     ULONG32      SizeOfFastIoDispatch;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     FUNCT_006E_0AC1_FastIoCheckIfPossible* FastIoCheckIfPossible;
/*0x010*/     FUNCT_006E_0ACC_FastIoRead_FastIoWrite* FastIoRead;
/*0x018*/     FUNCT_006E_0ACC_FastIoRead_FastIoWrite* FastIoWrite;
/*0x020*/     FUNCT_006E_0AD6_FastIoQueryBasicInfo* FastIoQueryBasicInfo;
/*0x028*/     FUNCT_006E_0AE4_FastIoQueryStandardInfo* FastIoQueryStandardInfo;
/*0x030*/     FUNCT_006E_0AF2_FastIoLock* FastIoLock;
/*0x038*/     FUNCT_006E_0D42_FastIoUnlockSingle* FastIoUnlockSingle;
/*0x040*/     FUNCT_006E_0D4B_FastIoUnlockAll* FastIoUnlockAll;
/*0x048*/     FUNCT_006E_0D51_FastIoUnlockAllByKey* FastIoUnlockAllByKey;
/*0x050*/     FUNCT_006E_0D58_FastIoDeviceControl* FastIoDeviceControl;
/*0x058*/     FUNCT_00AE_0D63_AcquireFileForNtCreateSection_ReleaseFileForNtCreateSection* AcquireFileForNtCreateSection;
/*0x060*/     FUNCT_00AE_0D63_AcquireFileForNtCreateSection_ReleaseFileForNtCreateSection* ReleaseFileForNtCreateSection;
/*0x068*/     FUNCT_00AE_0D66_FastIoDetachDevice* FastIoDetachDevice;
/*0x070*/     FUNCT_006E_0D6A_FastIoQueryNetworkOpenInfo* FastIoQueryNetworkOpenInfo;
/*0x078*/     FUNCT_0064_0D7A_AcquireForModWrite* AcquireForModWrite;
/*0x080*/     FUNCT_006E_0D80_MdlRead_PrepareMdlWrite* MdlRead;
/*0x088*/     FUNCT_006E_0D94_MdlReadComplete_MdlReadCompleteCompressed* MdlReadComplete;
/*0x090*/     FUNCT_006E_0D80_MdlRead_PrepareMdlWrite* PrepareMdlWrite;
/*0x098*/     FUNCT_006E_0D99_MdlWriteComplete_MdlWriteCompleteCompressed* MdlWriteComplete;
/*0x0A0*/     FUNCT_006E_0D9F_FastIoReadCompressed_FastIoWriteCompressed* FastIoReadCompressed;
/*0x0A8*/     FUNCT_006E_0D9F_FastIoReadCompressed_FastIoWriteCompressed* FastIoWriteCompressed;
/*0x0B0*/     FUNCT_006E_0D94_MdlReadComplete_MdlReadCompleteCompressed* MdlReadCompleteCompressed;
/*0x0B8*/     FUNCT_006E_0D99_MdlWriteComplete_MdlWriteCompleteCompressed* MdlWriteCompleteCompressed;
/*0x0C0*/     FUNCT_006E_0DB4_FastIoQueryOpen* FastIoQueryOpen;
/*0x0C8*/     FUNCT_0064_1082_ReleaseForModWrite* ReleaseForModWrite;
/*0x0D0*/     FUNCT_0064_1087_AcquireForCcFlush_ReleaseForCcFlush* AcquireForCcFlush;
/*0x0D8*/     FUNCT_0064_1087_AcquireForCcFlush_ReleaseForCcFlush* ReleaseForCcFlush;
          }FAST_IO_DISPATCH, *PFAST_IO_DISPATCH;

          typedef struct _FILE_OBJECT                                // 30 elements, 0xD8 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     INT16        Size;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x010*/     struct _VPB* Vpb;
/*0x018*/     VOID*        FsContext;
/*0x020*/     VOID*        FsContext2;
/*0x028*/     struct _SECTION_OBJECT_POINTERS* SectionObjectPointer;
/*0x030*/     VOID*        PrivateCacheMap;
/*0x038*/     LONG32       FinalStatus;
/*0x03C*/     UINT8        _PADDING1_[0x4];
/*0x040*/     struct _FILE_OBJECT* RelatedFileObject;
/*0x048*/     UINT8        LockOperation;
/*0x049*/     UINT8        DeletePending;
/*0x04A*/     UINT8        ReadAccess;
/*0x04B*/     UINT8        WriteAccess;
/*0x04C*/     UINT8        DeleteAccess;
/*0x04D*/     UINT8        SharedRead;
/*0x04E*/     UINT8        SharedWrite;
/*0x04F*/     UINT8        SharedDelete;
/*0x050*/     ULONG32      Flags;
/*0x054*/     UINT8        _PADDING2_[0x4];
/*0x058*/     struct _UNICODE_STRING FileName;                       // 3 elements, 0x10 bytes (sizeof)
/*0x068*/     union _LARGE_INTEGER CurrentByteOffset;                // 4 elements, 0x8 bytes (sizeof)
/*0x070*/     ULONG32      Waiters;
/*0x074*/     ULONG32      Busy;
/*0x078*/     VOID*        LastLock;
/*0x080*/     struct _KEVENT Lock;                                   // 1 elements, 0x18 bytes (sizeof)
/*0x098*/     struct _KEVENT Event;                                  // 1 elements, 0x18 bytes (sizeof)
/*0x0B0*/     struct _IO_COMPLETION_CONTEXT* CompletionContext;
/*0x0B8*/     UINT64       IrpListLock;
/*0x0C0*/     struct _LIST_ENTRY IrpList;                            // 2 elements, 0x10 bytes (sizeof)
/*0x0D0*/     VOID*        FileObjectExtension;
          }FILE_OBJECT, *PFILE_OBJECT;

          typedef union _FILE_SEGMENT_ELEMENT // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     VOID*        Buffer;
/*0x000*/     UINT64       Alignment;
          }FILE_SEGMENT_ELEMENT, *PFILE_SEGMENT_ELEMENT;

          typedef struct _FILE_STANDARD_INFORMATION // 5 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     union _LARGE_INTEGER AllocationSize;  // 4 elements, 0x8 bytes (sizeof)
/*0x008*/     union _LARGE_INTEGER EndOfFile;       // 4 elements, 0x8 bytes (sizeof)
/*0x010*/     ULONG32      NumberOfLinks;
/*0x014*/     UINT8        DeletePending;
/*0x015*/     UINT8        Directory;
/*0x016*/     UINT8        _PADDING0_[0x2];
          }FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

          typedef struct _INTERFACE                                                                                                                                                                                                                    // 5 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT16       Size;
/*0x002*/     UINT16       Version;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        Context;
/*0x010*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* InterfaceReference;
/*0x018*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* InterfaceDereference;
          }INTERFACE, *PINTERFACE;

          typedef struct _OPEN_PACKET                                    // 29 elements, 0xB8 bytes (sizeof)
          {
/*0x000*/     INT16        Type;
/*0x002*/     INT16        Size;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _FILE_OBJECT* FileObject;
/*0x010*/     LONG32       FinalStatus;
/*0x014*/     UINT8        _PADDING1_[0x4];
/*0x018*/     UINT64       Information;
/*0x020*/     ULONG32      ParseCheck;
/*0x024*/     UINT8        _PADDING2_[0x4];
              union                                                      // 2 elements, 0x8 bytes (sizeof)
              {
/*0x028*/         struct _FILE_OBJECT* RelatedFileObject;
/*0x028*/         struct _DEVICE_OBJECT* ReferencedDeviceObject;
              };
/*0x030*/     struct _OBJECT_ATTRIBUTES* OriginalAttributes;
/*0x038*/     union _LARGE_INTEGER AllocationSize;                       // 4 elements, 0x8 bytes (sizeof)
/*0x040*/     ULONG32      CreateOptions;
/*0x044*/     UINT16       FileAttributes;
/*0x046*/     UINT16       ShareAccess;
/*0x048*/     VOID*        EaBuffer;
/*0x050*/     ULONG32      EaLength;
/*0x054*/     ULONG32      Options;
/*0x058*/     ULONG32      Disposition;
/*0x05C*/     UINT8        _PADDING3_[0x4];
/*0x060*/     struct _FILE_BASIC_INFORMATION* BasicInformation;
/*0x068*/     struct _FILE_NETWORK_OPEN_INFORMATION* NetworkInformation;
/*0x070*/     enum _CREATE_FILE_TYPE CreateFileType;
/*0x074*/     UINT8        _PADDING4_[0x4];
/*0x078*/     VOID*        MailslotOrPipeParameters;
/*0x080*/     UINT8        Override;
/*0x081*/     UINT8        QueryOnly;
/*0x082*/     UINT8        DeleteOnly;
/*0x083*/     UINT8        FullAttributes;
/*0x084*/     UINT8        _PADDING5_[0x4];
/*0x088*/     struct _DUMMY_FILE_OBJECT* LocalFileObject;
/*0x090*/     ULONG32      InternalFlags;
/*0x094*/     CHAR         AccessMode;
/*0x095*/     UINT8        _PADDING6_[0x3];
/*0x098*/     struct _IO_DRIVER_CREATE_CONTEXT DriverCreateContext;      // 4 elements, 0x20 bytes (sizeof)
          }OPEN_PACKET, *POPEN_PACKET;

          typedef struct _PENDING_RELATIONS_LIST_ENTRY     // 12 elements, 0x68 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;                     // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _WORK_QUEUE_ITEM WorkItem;            // 3 elements, 0x20 bytes (sizeof)
/*0x030*/     struct _PNP_DEVICE_EVENT_ENTRY* DeviceEvent;
/*0x038*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x040*/     struct _RELATION_LIST* RelationsList;
/*0x048*/     struct _IRP* EjectIrp;
/*0x050*/     enum _IRPLOCK Lock;
/*0x054*/     ULONG32      Problem;
/*0x058*/     UINT8        ProfileChangingEject;
/*0x059*/     UINT8        DisplaySafeRemovalDialog;
/*0x05A*/     UINT8        _PADDING0_[0x2];
/*0x05C*/     enum _SYSTEM_POWER_STATE LightestSleepState;
/*0x060*/     struct _DOCK_INTERFACE* DockInterface;
          }PENDING_RELATIONS_LIST_ENTRY, *PPENDING_RELATIONS_LIST_ENTRY;

          typedef struct _WORK_QUEUE_ENTRY                      // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY WorkQueueLinks;                // 2 elements, 0x10 bytes (sizeof)
              union                                             // 4 elements, 0x8 bytes (sizeof)
              {
                  struct                                        // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x010*/             struct _FILE_OBJECT* FileObject;
                  }Read;
                  struct                                        // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x010*/             struct _SHARED_CACHE_MAP* SharedCacheMap;
                  }Write;
                  struct                                        // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x010*/             struct _KEVENT* Event;
                  }Event;
                  struct                                        // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x010*/             ULONG32      Reason;
                  }Notification;
              }Parameters;
/*0x018*/     UINT8        Function;
/*0x019*/     UINT8        _PADDING0_[0x7];
          }WORK_QUEUE_ENTRY, *PWORK_QUEUE_ENTRY;

          typedef struct _WORK_QUEUE_ITEM                                                                                                                                                                                                       // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY List;                                                                                                                                                                                                          // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* WorkerRoutine;
/*0x018*/     VOID*        Parameter;
          }WORK_QUEUE_ITEM, *PWORK_QUEUE_ITEM;

typedef enum _CREATE_FILE_TYPE  // 3 elements, 0x4 bytes
{
    CreateFileTypeNone      = 0 /*0x0*/,
    CreateFileTypeNamedPipe = 1 /*0x1*/,
    CreateFileTypeMailslot  = 2 /*0x2*/
}CREATE_FILE_TYPE, *PCREATE_FILE_TYPE;

typedef enum _DEVICE_POWER_STATE  // 6 elements, 0x4 bytes
{
    PowerDeviceUnspecified = 0 /*0x0*/,
    PowerDeviceD0          = 1 /*0x1*/,
    PowerDeviceD1          = 2 /*0x2*/,
    PowerDeviceD2          = 3 /*0x3*/,
    PowerDeviceD3          = 4 /*0x4*/,
    PowerDeviceMaximum     = 5 /*0x5*/
}DEVICE_POWER_STATE, *PDEVICE_POWER_STATE;

typedef enum _DEVICE_RELATION_TYPE  // 7 elements, 0x4 bytes
{
    BusRelations         = 0 /*0x0*/,
    EjectionRelations    = 1 /*0x1*/,
    PowerRelations       = 2 /*0x2*/,
    RemovalRelations     = 3 /*0x3*/,
    TargetDeviceRelation = 4 /*0x4*/,
    SingleBusRelations   = 5 /*0x5*/,
    TransportRelations   = 6 /*0x6*/
}DEVICE_RELATION_TYPE, *PDEVICE_RELATION_TYPE;

typedef enum _DEVICE_USAGE_NOTIFICATION_TYPE  // 5 elements, 0x4 bytes
{
    DeviceUsageTypeUndefined   = 0 /*0x0*/,
    DeviceUsageTypePaging      = 1 /*0x1*/,
    DeviceUsageTypeHibernation = 2 /*0x2*/,
    DeviceUsageTypeDumpFile    = 3 /*0x3*/,
    DeviceUsageTypeBoot        = 4 /*0x4*/
}DEVICE_USAGE_NOTIFICATION_TYPE, *PDEVICE_USAGE_NOTIFICATION_TYPE;

typedef enum _DEVICE_WAKE_DEPTH  // 7 elements, 0x4 bytes
{
    DeviceWakeDepthNotWakeable = 0 /*0x0*/,
    DeviceWakeDepthD0          = 1 /*0x1*/,
    DeviceWakeDepthD1          = 2 /*0x2*/,
    DeviceWakeDepthD2          = 3 /*0x3*/,
    DeviceWakeDepthD3hot       = 4 /*0x4*/,
    DeviceWakeDepthD3cold      = 5 /*0x5*/,
    DeviceWakeDepthMaximum     = 6 /*0x6*/
}DEVICE_WAKE_DEPTH, *PDEVICE_WAKE_DEPTH;

typedef enum _FILE_INFORMATION_CLASS  // 60 elements, 0x4 bytes
{
    FileDirectoryInformation                = 1 /*0x1*/,
    FileFullDirectoryInformation            = 2 /*0x2*/,
    FileBothDirectoryInformation            = 3 /*0x3*/,
    FileBasicInformation                    = 4 /*0x4*/,
    FileStandardInformation                 = 5 /*0x5*/,
    FileInternalInformation                 = 6 /*0x6*/,
    FileEaInformation                       = 7 /*0x7*/,
    FileAccessInformation                   = 8 /*0x8*/,
    FileNameInformation                     = 9 /*0x9*/,
    FileRenameInformation                   = 10 /*0xA*/,
    FileLinkInformation                     = 11 /*0xB*/,
    FileNamesInformation                    = 12 /*0xC*/,
    FileDispositionInformation              = 13 /*0xD*/,
    FilePositionInformation                 = 14 /*0xE*/,
    FileFullEaInformation                   = 15 /*0xF*/,
    FileModeInformation                     = 16 /*0x10*/,
    FileAlignmentInformation                = 17 /*0x11*/,
    FileAllInformation                      = 18 /*0x12*/,
    FileAllocationInformation               = 19 /*0x13*/,
    FileEndOfFileInformation                = 20 /*0x14*/,
    FileAlternateNameInformation            = 21 /*0x15*/,
    FileStreamInformation                   = 22 /*0x16*/,
    FilePipeInformation                     = 23 /*0x17*/,
    FilePipeLocalInformation                = 24 /*0x18*/,
    FilePipeRemoteInformation               = 25 /*0x19*/,
    FileMailslotQueryInformation            = 26 /*0x1A*/,
    FileMailslotSetInformation              = 27 /*0x1B*/,
    FileCompressionInformation              = 28 /*0x1C*/,
    FileObjectIdInformation                 = 29 /*0x1D*/,
    FileCompletionInformation               = 30 /*0x1E*/,
    FileMoveClusterInformation              = 31 /*0x1F*/,
    FileQuotaInformation                    = 32 /*0x20*/,
    FileReparsePointInformation             = 33 /*0x21*/,
    FileNetworkOpenInformation              = 34 /*0x22*/,
    FileAttributeTagInformation             = 35 /*0x23*/,
    FileTrackingInformation                 = 36 /*0x24*/,
    FileIdBothDirectoryInformation          = 37 /*0x25*/,
    FileIdFullDirectoryInformation          = 38 /*0x26*/,
    FileValidDataLengthInformation          = 39 /*0x27*/,
    FileShortNameInformation                = 40 /*0x28*/,
    FileIoCompletionNotificationInformation = 41 /*0x29*/,
    FileIoStatusBlockRangeInformation       = 42 /*0x2A*/,
    FileIoPriorityHintInformation           = 43 /*0x2B*/,
    FileSfioReserveInformation              = 44 /*0x2C*/,
    FileSfioVolumeInformation               = 45 /*0x2D*/,
    FileHardLinkInformation                 = 46 /*0x2E*/,
    FileProcessIdsUsingFileInformation      = 47 /*0x2F*/,
    FileNormalizedNameInformation           = 48 /*0x30*/,
    FileNetworkPhysicalNameInformation      = 49 /*0x31*/,
    FileIdGlobalTxDirectoryInformation      = 50 /*0x32*/,
    FileIsRemoteDeviceInformation           = 51 /*0x33*/,
    FileAttributeCacheInformation           = 52 /*0x34*/,
    FileNumaNodeInformation                 = 53 /*0x35*/,
    FileStandardLinkInformation             = 54 /*0x36*/,
    FileRemoteProtocolInformation           = 55 /*0x37*/,
    FileRenameInformationBypassAccessCheck  = 56 /*0x38*/,
    FileLinkInformationBypassAccessCheck    = 57 /*0x39*/,
    FileIntegrityStreamInformation          = 58 /*0x3A*/,
    FileVolumeNameInformation               = 59 /*0x3B*/,
    FileMaximumInformation                  = 60 /*0x3C*/
}FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

typedef enum _FILE_OBJECT_EXTENSION_TYPE  // 8 elements, 0x4 bytes
{
    FoExtTypeTransactionParams = 0 /*0x0*/,
    FoExtTypeInternal          = 1 /*0x1*/,
    FoExtTypeIosbRange         = 2 /*0x2*/,
    FoExtTypeGeneric           = 3 /*0x3*/,
    FoExtTypeSfio              = 4 /*0x4*/,
    FoExtTypeSymlink           = 5 /*0x5*/,
    FoExtTypeOplockKey         = 6 /*0x6*/,
    MaxFoExtTypes              = 7 /*0x7*/
}FILE_OBJECT_EXTENSION_TYPE, *PFILE_OBJECT_EXTENSION_TYPE;

typedef enum _INTERFACE_TYPE  // 20 elements, 0x4 bytes
{
    InterfaceTypeUndefined = -1 /*0xFF*/,
    Internal               = 0 /*0x0*/,
    Isa                    = 1 /*0x1*/,
    Eisa                   = 2 /*0x2*/,
    MicroChannel           = 3 /*0x3*/,
    TurboChannel           = 4 /*0x4*/,
    PCIBus                 = 5 /*0x5*/,
    VMEBus                 = 6 /*0x6*/,
    NuBus                  = 7 /*0x7*/,
    PCMCIABus              = 8 /*0x8*/,
    CBus                   = 9 /*0x9*/,
    MPIBus                 = 10 /*0xA*/,
    MPSABus                = 11 /*0xB*/,
    ProcessorInternal      = 12 /*0xC*/,
    InternalPowerBus       = 13 /*0xD*/,
    PNPISABus              = 14 /*0xE*/,
    PNPBus                 = 15 /*0xF*/,
    Vmcs                   = 16 /*0x10*/,
    ACPIBus                = 17 /*0x11*/,
    MaximumInterfaceType   = 18 /*0x12*/
}INTERFACE_TYPE, *PINTERFACE_TYPE;

typedef enum _WORK_QUEUE_TYPE  // 6 elements, 0x4 bytes
{
    CriticalWorkQueue      = 0 /*0x0*/,
    DelayedWorkQueue       = 1 /*0x1*/,
    HyperCriticalWorkQueue = 2 /*0x2*/,
    NormalWorkQueue        = 3 /*0x3*/,
    BackgroundWorkQueue    = 4 /*0x4*/,
    MaximumWorkQueue       = 5 /*0x5*/
}WORK_QUEUE_TYPE, *PWORK_QUEUE_TYPE;

typedef enum _BUS_QUERY_ID_TYPE  // 6 elements, 0x4 bytes
{
    BusQueryDeviceID           = 0 /*0x0*/,
    BusQueryHardwareIDs        = 1 /*0x1*/,
    BusQueryCompatibleIDs      = 2 /*0x2*/,
    BusQueryInstanceID         = 3 /*0x3*/,
    BusQueryDeviceSerialNumber = 4 /*0x4*/,
    BusQueryContainerID        = 5 /*0x5*/
}BUS_QUERY_ID_TYPE, *PBUS_QUERY_ID_TYPE;

typedef enum _DEVICE_TEXT_TYPE  // 2 elements, 0x4 bytes
{
    DeviceTextDescription         = 0 /*0x0*/,
    DeviceTextLocationInformation = 1 /*0x1*/
}DEVICE_TEXT_TYPE, *PDEVICE_TEXT_TYPE;

typedef enum _IRPLOCK  // 4 elements, 0x4 bytes
{
    IRPLOCK_CANCELABLE      = 0 /*0x0*/,
    IRPLOCK_CANCEL_STARTED  = 1 /*0x1*/,
    IRPLOCK_CANCEL_COMPLETE = 2 /*0x2*/,
    IRPLOCK_COMPLETED       = 3 /*0x3*/
}IRPLOCK, *PIRPLOCK;

typedef struct _ADAPTER_OBJECT // 0 elements, 0x0 bytes (sizeof)
{
}ADAPTER_OBJECT, *PADAPTER_OBJECT;

