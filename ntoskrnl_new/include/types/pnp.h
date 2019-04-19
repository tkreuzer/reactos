
          typedef struct _PLUGPLAY_EVENT_BLOCK                // 7 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _GUID EventGuid;                         // 4 elements, 0x10 bytes (sizeof)
/*0x010*/     enum _PLUGPLAY_EVENT_CATEGORY EventCategory;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     ULONG32*     Result;
/*0x020*/     ULONG32      Flags;
/*0x024*/     ULONG32      TotalSize;
/*0x028*/     VOID*        DeviceObject;
              union                                           // 12 elements, 0x20 bytes (sizeof)
              {
                  struct                                      // 2 elements, 0x14 bytes (sizeof)
                  {
/*0x030*/             struct _GUID ClassGuid;                 // 4 elements, 0x10 bytes (sizeof)
/*0x040*/             WCHAR        SymbolicLinkName[1];
/*0x042*/             UINT8        _PADDING1_[0x2];
                  }DeviceClass;
                  struct                                      // 1 elements, 0x2 bytes (sizeof)
                  {
/*0x030*/             WCHAR        DeviceId[1];
                  }TargetDevice;
                  struct                                      // 1 elements, 0x2 bytes (sizeof)
                  {
/*0x030*/             WCHAR        DeviceId[1];
                  }InstallDevice;
                  struct                                      // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x030*/             VOID*        NotificationStructure;
/*0x038*/             WCHAR        DeviceId[1];
/*0x03A*/             UINT8        _PADDING1_[0x6];
                  }CustomNotification;
                  struct                                      // 1 elements, 0x8 bytes (sizeof)
                  {
/*0x030*/             VOID*        Notification;
                  }ProfileNotification;
                  struct                                      // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x030*/             ULONG32      NotificationCode;
/*0x034*/             ULONG32      NotificationData;
                  }PowerNotification;
                  struct                                      // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x030*/             enum _PNP_VETO_TYPE VetoType;
/*0x034*/             WCHAR        DeviceIdVetoNameBuffer[1];
/*0x036*/             UINT8        _PADDING1_[0x2];
                  }VetoNotification;
                  struct                                      // 1 elements, 0x10 bytes (sizeof)
                  {
/*0x030*/             struct _GUID BlockedDriverGuid;         // 4 elements, 0x10 bytes (sizeof)
                  }BlockedDriverNotification;
                  struct                                      // 1 elements, 0x2 bytes (sizeof)
                  {
/*0x030*/             WCHAR        ParentId[1];
                  }InvalidIDNotification;
                  struct                                      // 5 elements, 0x20 bytes (sizeof)
                  {
/*0x030*/             struct _GUID PowerSettingGuid;          // 4 elements, 0x10 bytes (sizeof)
/*0x040*/             ULONG32      Flags;
/*0x044*/             ULONG32      SessionId;
/*0x048*/             ULONG32      DataLength;
/*0x04C*/             UINT8        Data[1];
/*0x04D*/             UINT8        _PADDING1_[0x3];
                  }PowerSettingNotification;
                  struct                                      // 1 elements, 0x2 bytes (sizeof)
                  {
/*0x030*/             WCHAR        DeviceId[1];
                  }PropertyChangeNotification;
                  struct                                      // 1 elements, 0x2 bytes (sizeof)
                  {
/*0x030*/             WCHAR        DeviceId[1];
                  }DeviceInstanceNotification;
              }u;
          }PLUGPLAY_EVENT_BLOCK, *PPLUGPLAY_EVENT_BLOCK;

          typedef struct _PNP_ASSIGN_RESOURCES_CONTEXT // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      IncludeFailedDevices;
/*0x004*/     ULONG32      DeviceCount;
/*0x008*/     struct _DEVICE_OBJECT* DeviceList[1];
          }PNP_ASSIGN_RESOURCES_CONTEXT, *PPNP_ASSIGN_RESOURCES_CONTEXT;

          typedef struct _PNP_DEVICE_ACTION_ENTRY          // 7 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;                // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x018*/     enum _PNP_DEVICE_ACTION_REQUEST RequestType;
/*0x01C*/     UINT8        ReorderingBarrier;
/*0x01D*/     UINT8        _PADDING0_[0x3];
/*0x020*/     UINT64       RequestArgument;
/*0x028*/     struct _KEVENT* CompletionEvent;
/*0x030*/     LONG32*      CompletionStatus;
          }PNP_DEVICE_ACTION_ENTRY, *PPNP_DEVICE_ACTION_ENTRY;

          typedef struct _PNP_DEVICE_COMPLETION_QUEUE // 5 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY DispatchedList;      // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      DispatchedCount;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     struct _LIST_ENTRY CompletedList;       // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _KSEMAPHORE CompletedSemaphore;  // 2 elements, 0x20 bytes (sizeof)
/*0x048*/     UINT64       SpinLock;
          }PNP_DEVICE_COMPLETION_QUEUE, *PPNP_DEVICE_COMPLETION_QUEUE;

          typedef struct _PNP_DEVICE_COMPLETION_REQUEST // 8 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;             // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _DEVICE_NODE* DeviceNode;
/*0x018*/     VOID*        Context;
/*0x020*/     enum _PNP_DEVNODE_STATE CompletionState;
/*0x024*/     ULONG32      IrpPended;
/*0x028*/     LONG32       Status;
/*0x02C*/     UINT8        _PADDING0_[0x4];
/*0x030*/     VOID*        Information;
/*0x038*/     LONG32       ReferenceCount;
/*0x03C*/     UINT8        _PADDING1_[0x4];
          }PNP_DEVICE_COMPLETION_REQUEST, *PPNP_DEVICE_COMPLETION_REQUEST;

          typedef struct _PNP_DEVICE_EVENT_ENTRY                                                                                                                                                                                           // 12 elements, 0xA8 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;                                                                                                                                                                                                // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Argument;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     struct _KEVENT* CallerEvent;
/*0x020*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* Callback;
/*0x028*/     VOID*        Context;
/*0x030*/     enum _PNP_VETO_TYPE* VetoType;
/*0x038*/     struct _UNICODE_STRING* VetoName;
/*0x040*/     ULONG32      RefCount;
/*0x044*/     ULONG32      Lock;
/*0x048*/     UINT8        Cancel;
/*0x049*/     UINT8        _PADDING1_[0x7];
/*0x050*/     struct _PNP_DEVICE_EVENT_ENTRY* Parent;
/*0x058*/     struct _PLUGPLAY_EVENT_BLOCK Data;                                                                                                                                                                                           // 7 elements, 0x50 bytes (sizeof)
          }PNP_DEVICE_EVENT_ENTRY, *PPNP_DEVICE_EVENT_ENTRY;

          typedef struct _PNP_DEVICE_EVENT_LIST // 4 elements, 0x88 bytes (sizeof)
          {
/*0x000*/     LONG32       Status;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _KMUTANT EventQueueMutex;  // 5 elements, 0x38 bytes (sizeof)
/*0x040*/     struct _FAST_MUTEX Lock;          // 5 elements, 0x38 bytes (sizeof)
/*0x078*/     struct _LIST_ENTRY List;          // 2 elements, 0x10 bytes (sizeof)
          }PNP_DEVICE_EVENT_LIST, *PPNP_DEVICE_EVENT_LIST;

          typedef struct _PNP_RESOURCE_REQUEST                             // 10 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     struct _DEVICE_OBJECT* PhysicalDevice;
/*0x008*/     ULONG32      Flags;
/*0x00C*/     enum _ARBITER_REQUEST_SOURCE AllocationType;
/*0x010*/     ULONG32      Priority;
/*0x014*/     ULONG32      Position;
/*0x018*/     struct _IO_RESOURCE_REQUIREMENTS_LIST* ResourceRequirements;
/*0x020*/     VOID*        ReqList;
/*0x028*/     struct _CM_RESOURCE_LIST* ResourceAssignment;
/*0x030*/     struct _CM_RESOURCE_LIST* TranslatedResourceAssignment;
/*0x038*/     LONG32       Status;
/*0x03C*/     UINT8        _PADDING0_[0x4];
          }PNP_RESOURCE_REQUEST, *PPNP_RESOURCE_REQUEST;

typedef enum _PLUGPLAY_EVENT_CATEGORY  // 13 elements, 0x4 bytes
{
    HardwareProfileChangeEvent = 0 /*0x0*/,
    TargetDeviceChangeEvent    = 1 /*0x1*/,
    DeviceClassChangeEvent     = 2 /*0x2*/,
    CustomDeviceEvent          = 3 /*0x3*/,
    DeviceInstallEvent         = 4 /*0x4*/,
    DeviceArrivalEvent         = 5 /*0x5*/,
    VetoEvent                  = 6 /*0x6*/,
    BlockedDriverEvent         = 7 /*0x7*/,
    InvalidIDEvent             = 8 /*0x8*/,
    DevicePropertyChangeEvent  = 9 /*0x9*/,
    DeviceInstanceRemovalEvent = 10 /*0xA*/,
    DeviceInstanceStartedEvent = 11 /*0xB*/,
    MaxPlugEventCategory       = 12 /*0xC*/
}PLUGPLAY_EVENT_CATEGORY, *PPLUGPLAY_EVENT_CATEGORY;

typedef enum _PNP_DEVICE_ACTION_REQUEST  // 21 elements, 0x4 bytes
{
    AssignResources                = 0 /*0x0*/,
    ClearDeviceProblem             = 1 /*0x1*/,
    ClearProblem                   = 2 /*0x2*/,
    ClearEjectProblem              = 3 /*0x3*/,
    HaltDevice                     = 4 /*0x4*/,
    QueryPowerRelations            = 5 /*0x5*/,
    Rebalance                      = 6 /*0x6*/,
    ReenumerateBootDevices         = 7 /*0x7*/,
    ReenumerateDeviceOnly          = 8 /*0x8*/,
    ReenumerateDeviceTree          = 9 /*0x9*/,
    ReenumerateRootDevices         = 10 /*0xA*/,
    RequeryDeviceState             = 11 /*0xB*/,
    ResetDevice                    = 12 /*0xC*/,
    ResourceRequirementsChanged    = 13 /*0xD*/,
    RestartEnumeration             = 14 /*0xE*/,
    SetDeviceProblem               = 15 /*0xF*/,
    StartDevice                    = 16 /*0x10*/,
    StartSystemDevicesPass0        = 17 /*0x11*/,
    StartSystemDevicesPass1        = 18 /*0x12*/,
    NotifyTransportRelationsChange = 19 /*0x13*/,
    NotifyEjectionRelationsChange  = 20 /*0x14*/
}PNP_DEVICE_ACTION_REQUEST, *PPNP_DEVICE_ACTION_REQUEST;

typedef enum _PNP_DEVNODE_STATE  // 22 elements, 0x4 bytes
{
    DeviceNodeUnspecified            = 768 /*0x300*/,
    DeviceNodeUninitialized          = 769 /*0x301*/,
    DeviceNodeInitialized            = 770 /*0x302*/,
    DeviceNodeDriversAdded           = 771 /*0x303*/,
    DeviceNodeResourcesAssigned      = 772 /*0x304*/,
    DeviceNodeStartPending           = 773 /*0x305*/,
    DeviceNodeStartCompletion        = 774 /*0x306*/,
    DeviceNodeStartPostWork          = 775 /*0x307*/,
    DeviceNodeStarted                = 776 /*0x308*/,
    DeviceNodeQueryStopped           = 777 /*0x309*/,
    DeviceNodeStopped                = 778 /*0x30A*/,
    DeviceNodeRestartCompletion      = 779 /*0x30B*/,
    DeviceNodeEnumeratePending       = 780 /*0x30C*/,
    DeviceNodeEnumerateCompletion    = 781 /*0x30D*/,
    DeviceNodeAwaitingQueuedDeletion = 782 /*0x30E*/,
    DeviceNodeAwaitingQueuedRemoval  = 783 /*0x30F*/,
    DeviceNodeQueryRemoved           = 784 /*0x310*/,
    DeviceNodeRemovePendingCloses    = 785 /*0x311*/,
    DeviceNodeRemoved                = 786 /*0x312*/,
    DeviceNodeDeletePendingCloses    = 787 /*0x313*/,
    DeviceNodeDeleted                = 788 /*0x314*/,
    MaxDeviceNodeState               = 789 /*0x315*/
}PNP_DEVNODE_STATE, *PPNP_DEVNODE_STATE;

typedef enum _PNP_VETO_TYPE  // 13 elements, 0x4 bytes
{
    PNP_VetoTypeUnknown          = 0 /*0x0*/,
    PNP_VetoLegacyDevice         = 1 /*0x1*/,
    PNP_VetoPendingClose         = 2 /*0x2*/,
    PNP_VetoWindowsApp           = 3 /*0x3*/,
    PNP_VetoWindowsService       = 4 /*0x4*/,
    PNP_VetoOutstandingOpen      = 5 /*0x5*/,
    PNP_VetoDevice               = 6 /*0x6*/,
    PNP_VetoDriver               = 7 /*0x7*/,
    PNP_VetoIllegalDeviceRequest = 8 /*0x8*/,
    PNP_VetoInsufficientPower    = 9 /*0x9*/,
    PNP_VetoNonDisableable       = 10 /*0xA*/,
    PNP_VetoLegacyDriver         = 11 /*0xB*/,
    PNP_VetoInsufficientRights   = 12 /*0xC*/
}PNP_VETO_TYPE, *PPNP_VETO_TYPE;

