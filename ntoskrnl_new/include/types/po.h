
          typedef struct _PO_DEVICE_NOTIFY         // 12 elements, 0x68 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;             // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LIST_ENTRY PowerChildren;    // 2 elements, 0x10 bytes (sizeof)
/*0x020*/     struct _LIST_ENTRY PowerParents;     // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     struct _DEVICE_OBJECT* TargetDevice;
/*0x038*/     UINT8        OrderLevel;
/*0x039*/     UINT8        _PADDING0_[0x7];
/*0x040*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x048*/     UINT16*      DeviceName;
/*0x050*/     UINT16*      DriverName;
/*0x058*/     ULONG32      ChildCount;
/*0x05C*/     ULONG32      ActiveChild;
/*0x060*/     ULONG32      ParentCount;
/*0x064*/     ULONG32      ActiveParent;
          }PO_DEVICE_NOTIFY, *PPO_DEVICE_NOTIFY;

          typedef struct _PO_DEVICE_NOTIFY_ORDER           // 3 elements, 0x298 bytes (sizeof)
          {
/*0x000*/     UINT8        Locked;
/*0x001*/     UINT8        _PADDING0_[0x7];
/*0x008*/     struct _DEVICE_OBJECT** WarmEjectPdoPointer;
/*0x010*/     struct _PO_NOTIFY_ORDER_LEVEL OrderLevel[9];
          }PO_DEVICE_NOTIFY_ORDER, *PPO_DEVICE_NOTIFY_ORDER;

          typedef struct _PO_DIAG_STACK_RECORD // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      StackDepth;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        Stack[1];
          }PO_DIAG_STACK_RECORD, *PPO_DIAG_STACK_RECORD;

          typedef struct _PO_HIBER_PERF                           // 51 elements, 0x188 bytes (sizeof)
          {
/*0x000*/     UINT64       HiberIoTicks;
/*0x008*/     UINT64       HiberIoCpuTicks;
/*0x010*/     UINT64       HiberInitTicks;
/*0x018*/     UINT64       HiberHiberFileTicks;
/*0x020*/     UINT64       HiberCompressTicks;
/*0x028*/     UINT64       HiberSharedBufferTicks;
/*0x030*/     UINT64       TotalHibernateTime;
/*0x038*/     ULONG32      POSTTime;
/*0x03C*/     ULONG32      ResumeBootMgrTime;
/*0x040*/     UINT64       ResumeAppTicks;
/*0x048*/     UINT64       ResumeAppStartTimestamp;
/*0x050*/     UINT64       ResumeLibraryInitTicks;
/*0x058*/     UINT64       ResumeInitTicks;
/*0x060*/     UINT64       ResumeRestoreImageStartTimestamp;
/*0x068*/     UINT64       ResumeHiberFileTicks;
/*0x070*/     UINT64       ResumeIoTicks;
/*0x078*/     UINT64       ResumeDecompressTicks;
/*0x080*/     UINT64       ResumeAllocateTicks;
/*0x088*/     UINT64       ResumeUserInOutTicks;
/*0x090*/     UINT64       ResumeMapTicks;
/*0x098*/     UINT64       ResumeUnmapTicks;
/*0x0A0*/     UINT64       ResumeKernelSwitchTimestamp;
/*0x0A8*/     UINT64       WriteLogDataTimestamp;
/*0x0B0*/     UINT64       KernelReturnFromHandler;
/*0x0B8*/     UINT64       TimeStampCounterAtSwitchTime;
/*0x0C0*/     UINT64       SavedTimeAtSwitchTime;
/*0x0C8*/     UINT64       SleeperThreadEnd;
/*0x0D0*/     UINT64       KernelReturnSystemPowerStateTimestamp;
/*0x0D8*/     UINT64       IoBoundedness;
/*0x0E0*/     UINT64       KernelDecompressTicks;
/*0x0E8*/     UINT64       KernelIoTicks;
/*0x0F0*/     UINT64       KernelCopyTicks;
/*0x0F8*/     UINT64       ReadCheckCount;
/*0x100*/     UINT64       KernelInitTicks;
/*0x108*/     UINT64       KernelResumeHiberFileTicks;
/*0x110*/     UINT64       KernelIoCpuTicks;
/*0x118*/     UINT64       KernelSharedBufferTicks;
/*0x120*/     UINT64       KernelAnimationTicks;
/*0x128*/     union _LARGE_INTEGER AnimationStart;                // 4 elements, 0x8 bytes (sizeof)
/*0x130*/     union _LARGE_INTEGER AnimationStop;                 // 4 elements, 0x8 bytes (sizeof)
/*0x138*/     ULONG32      DeviceResumeTime;
/*0x13C*/     UINT8        _PADDING0_[0x4];
/*0x140*/     UINT64       BootPagesProcessed;
/*0x148*/     UINT64       KernelPagesProcessed;
/*0x150*/     UINT64       BootBytesWritten;
/*0x158*/     UINT64       KernelBytesWritten;
/*0x160*/     UINT64       BootPagesWritten;
/*0x168*/     UINT64       KernelPagesWritten;
/*0x170*/     UINT64       BytesWritten;
/*0x178*/     ULONG32      PagesWritten;
/*0x17C*/     ULONG32      FileRuns;
/*0x180*/     ULONG32      NoMultiStageResumeReason;
/*0x184*/     UINT8        _PADDING1_[0x4];
          }PO_HIBER_PERF, *PPO_HIBER_PERF;

          typedef struct _PO_IRP_MANAGER           // 2 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _PO_IRP_QUEUE DeviceIrpQueue; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _PO_IRP_QUEUE SystemIrpQueue; // 2 elements, 0x10 bytes (sizeof)
          }PO_IRP_MANAGER, *PPO_IRP_MANAGER;

          typedef struct _PO_IRP_QUEUE     // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _IRP* CurrentIrp;
/*0x008*/     struct _IRP* PendingIrpList;
          }PO_IRP_QUEUE, *PPO_IRP_QUEUE;

          typedef struct _PO_NOTIFY_ORDER_LEVEL // 6 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      DeviceCount;
/*0x004*/     ULONG32      ActiveCount;
/*0x008*/     struct _LIST_ENTRY WaitSleep;     // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     struct _LIST_ENTRY ReadySleep;    // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _LIST_ENTRY ReadyS0;       // 2 elements, 0x10 bytes (sizeof)
/*0x038*/     struct _LIST_ENTRY WaitS0;        // 2 elements, 0x10 bytes (sizeof)
          }PO_NOTIFY_ORDER_LEVEL, *PPO_NOTIFY_ORDER_LEVEL;


          typedef struct _POP_ACTION_TRIGGER       // 5 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     enum _POWER_POLICY_DEVICE_TYPE Type;
/*0x004*/     ULONG32      Flags;
/*0x008*/     struct _POP_TRIGGER_WAIT* Wait;
              union                                // 2 elements, 0x8 bytes (sizeof)
              {
                  struct                           // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x010*/             ULONG32      Level;
                  }Battery;
                  struct                           // 1 elements, 0x4 bytes (sizeof)
                  {
/*0x010*/             ULONG32      Type;
                  }Button;
              };
          }POP_ACTION_TRIGGER, *PPOP_ACTION_TRIGGER;

          typedef struct _POP_CURRENT_BROADCAST                 // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT8        InProgress;
/*0x001*/     UINT8        _PADDING0_[0x3];
/*0x004*/     struct _SYSTEM_POWER_STATE_CONTEXT SystemContext; // 8 elements, 0x4 bytes (sizeof)
/*0x008*/     enum _POWER_ACTION PowerAction;
/*0x00C*/     UINT8        _PADDING1_[0x4];
/*0x010*/     struct _POP_DEVICE_SYS_STATE* DeviceState;
          }POP_CURRENT_BROADCAST, *PPOP_CURRENT_BROADCAST;

          typedef struct _POP_DEVICE_SYS_STATE       // 16 elements, 0x2F0 bytes (sizeof)
          {
/*0x000*/     UINT8        IrpMinor;
/*0x001*/     UINT8        _PADDING0_[0x3];
/*0x004*/     enum _SYSTEM_POWER_STATE SystemState;
/*0x008*/     UINT64       SpinLock;
/*0x010*/     struct _KTHREAD* Thread;
/*0x018*/     struct _KEVENT* AbortEvent;
/*0x020*/     struct _KSEMAPHORE* ReadySemaphore;
/*0x028*/     struct _KSEMAPHORE* FinishedSemaphore;
/*0x030*/     struct _PO_DEVICE_NOTIFY_ORDER Order;  // 3 elements, 0x298 bytes (sizeof)
/*0x2C8*/     struct _LIST_ENTRY Pending;            // 2 elements, 0x10 bytes (sizeof)
/*0x2D8*/     LONG32       Status;
/*0x2DC*/     UINT8        _PADDING1_[0x4];
/*0x2E0*/     struct _DEVICE_OBJECT* FailedDevice;
/*0x2E8*/     UINT8        Waking;
/*0x2E9*/     UINT8        Cancelled;
/*0x2EA*/     UINT8        IgnoreErrors;
/*0x2EB*/     UINT8        IgnoreNotImplemented;
/*0x2EC*/     UINT8        TimeRefreshLockAcquired;
/*0x2ED*/     UINT8        _PADDING2_[0x3];
          }POP_DEVICE_SYS_STATE, *PPOP_DEVICE_SYS_STATE;

          typedef struct _POP_FX_COMPONENT           // 13 elements, 0x90 bytes (sizeof)
          {
/*0x000*/     struct _GUID Id;                       // 4 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      Index;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     struct _POP_FX_WORK_ORDER WorkOrder;   // 2 elements, 0x28 bytes (sizeof)
/*0x040*/     struct _POP_FX_DEVICE* Device;
/*0x048*/     union _POP_FX_COMPONENT_FLAGS Flags;   // 4 elements, 0x4 bytes (sizeof)
/*0x04C*/     UINT8        _PADDING1_[0x4];
/*0x050*/     struct _KEVENT ActiveEvent;            // 1 elements, 0x18 bytes (sizeof)
/*0x068*/     UINT64       IdleLock;
/*0x070*/     LONG32       IdleConditionComplete;
/*0x074*/     LONG32       IdleStateComplete;
/*0x078*/     ULONG32      CurrentIdleState;
/*0x07C*/     ULONG32      IdleStateCount;
/*0x080*/     struct _POP_FX_IDLE_STATE* IdleStates;
/*0x088*/     ULONG32      DeepestWakeableIdleState;
/*0x08C*/     UINT8        _PADDING2_[0x4];
          }POP_FX_COMPONENT, *PPOP_FX_COMPONENT;

          typedef union _POP_FX_COMPONENT_FLAGS // 4 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     LONG32       Value;
              struct                            // 3 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      RefCount : 30;   // 0 BitPosition
/*0x000*/         ULONG32      Idling : 1;      // 30 BitPosition
/*0x000*/         ULONG32      Active : 1;      // 31 BitPosition
              };
          }POP_FX_COMPONENT_FLAGS, *PPOP_FX_COMPONENT_FLAGS;

          typedef struct _POP_FX_DEVICE                  // 14 elements, 0xB8 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;                   // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _DEVICE_NODE* DevNode;
/*0x018*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x020*/     ULONG32      ComponentCount;
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     struct _POP_FX_DRIVER_CALLBACKS Callbacks; // 8 elements, 0x40 bytes (sizeof)
/*0x068*/     LONG32       PowerReqComplete;
/*0x06C*/     LONG32       PowerNotReqComplete;
/*0x070*/     LONG32       PEPD0Notify;
/*0x074*/     UINT8        SystemTransition;
/*0x075*/     UINT8        _PADDING1_[0x3];
/*0x078*/     VOID*        DriverContext;
/*0x080*/     struct _POP_FX_PLUGIN* Plugin;
/*0x088*/     struct _PEPHANDLE__* PluginHandle;
/*0x090*/     struct _IO_REMOVE_LOCK RemoveLock;         // 1 elements, 0x20 bytes (sizeof)
/*0x0B0*/     struct _POP_FX_COMPONENT* Components[1];
          }POP_FX_DEVICE, *PPOP_FX_DEVICE;

          typedef struct _POP_FX_DRIVER_CALLBACKS                                                                                                                                                                                                        // 8 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     FUNCT_00AE_07CA_IdleCancel_Free_ComponentActive_ComponentIdle* ComponentActive;
/*0x008*/     FUNCT_00AE_07CA_IdleCancel_Free_ComponentActive_ComponentIdle* ComponentIdle;
/*0x010*/     FUNCT_00AE_16AB_ComponentIdleState* ComponentIdleState;
/*0x018*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* DevicePowerRequired;
/*0x020*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* DevicePowerNotRequired;
/*0x028*/     FUNCT_0064_16B0_PowerControl* PowerControl;
/*0x030*/     FUNCT_00AE_16B9_ComponentCriticalTransition* ComponentCriticalTransition;
/*0x038*/     FUNCT_0064_16BE_DeviceInformation* DeviceInformation;
          }POP_FX_DRIVER_CALLBACKS, *PPOP_FX_DRIVER_CALLBACKS;

          typedef struct _POP_FX_IDLE_STATE      // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT64       TransitionLatency;
/*0x008*/     UINT64       ResidencyRequirement;
/*0x010*/     ULONG32      NominalPower;
/*0x014*/     UINT8        _PADDING0_[0x4];
          }POP_FX_IDLE_STATE, *PPOP_FX_IDLE_STATE;

          typedef struct _POP_FX_PLUGIN                                                 // 6 elements, 0x90 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;                                                  // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT64       Flags;
/*0x018*/     struct _POP_FX_WORK_ORDER WorkOrder;                                      // 2 elements, 0x28 bytes (sizeof)
/*0x040*/     struct _KQUEUE WorkQueue;                                                 // 5 elements, 0x40 bytes (sizeof)
/*0x080*/     FUNCT_006E_16CE_AcceptDeviceNotification* AcceptDeviceNotification;
/*0x088*/     FUNCT_006E_16D2_AcceptProcessorNotification* AcceptProcessorNotification;
          }POP_FX_PLUGIN, *PPOP_FX_PLUGIN;

          typedef struct _POP_FX_WORK_ORDER     // 2 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _WORK_QUEUE_ITEM WorkItem; // 3 elements, 0x20 bytes (sizeof)
/*0x020*/     LONG32       WorkCount;
/*0x024*/     UINT8        _PADDING0_[0x4];
          }POP_FX_WORK_ORDER, *PPOP_FX_WORK_ORDER;

          typedef struct _POP_HIBER_CONTEXT                        // 47 elements, 0x190 bytes (sizeof)
          {
/*0x000*/     UINT8        Reset;
/*0x001*/     UINT8        HiberFlags;
/*0x002*/     UINT8        WroteHiberFile;
/*0x003*/     UINT8        VerifyKernelPhaseOnResume;
/*0x004*/     UINT8        KernelPhaseVerificationActive;
/*0x005*/     UINT8        InitializationFinished;
/*0x006*/     UINT8        _PADDING0_[0x2];
/*0x008*/     LONG32       NextTableLockHeld;
/*0x00C*/     LONG32       BootPhaseFinishedBarrier;
/*0x010*/     LONG32       KernelResumeFinishedBarrier;
/*0x014*/     UINT8        MapFrozen;
/*0x015*/     UINT8        _PADDING1_[0x3];
              union                                                // 2 elements, 0x10 bytes (sizeof)
              {
/*0x018*/         struct _RTL_BITMAP DiscardMap;                   // 2 elements, 0x10 bytes (sizeof)
/*0x018*/         struct _RTL_BITMAP KernelPhaseMap;               // 2 elements, 0x10 bytes (sizeof)
              };
/*0x028*/     struct _RTL_BITMAP BootPhaseMap;                     // 2 elements, 0x10 bytes (sizeof)
/*0x038*/     struct _LIST_ENTRY ClonedRanges;                     // 2 elements, 0x10 bytes (sizeof)
/*0x048*/     ULONG32      ClonedRangeCount;
/*0x04C*/     UINT8        _PADDING2_[0x4];
/*0x050*/     UINT64       ClonedPageCount;
/*0x058*/     struct _RTL_BITMAP* CurrentMap;
/*0x060*/     struct _LIST_ENTRY* NextCloneRange;
/*0x068*/     UINT64       NextPreserve;
/*0x070*/     struct _MDL* LoaderMdl;
/*0x078*/     struct _MDL* AllocatedMdl;
/*0x080*/     UINT64       PagesOut;
/*0x088*/     VOID*        IoPages;
/*0x090*/     ULONG32      IoPagesCount;
/*0x094*/     UINT8        _PADDING3_[0x4];
/*0x098*/     VOID*        CurrentMcb;
/*0x0A0*/     struct _DUMP_STACK_CONTEXT* DumpStack;
/*0x0A8*/     struct _KPROCESSOR_STATE* WakeState;
/*0x0B0*/     ULONG32      IoProgress;
/*0x0B4*/     LONG32       Status;
/*0x0B8*/     ULONG32      GraphicsProc;
/*0x0BC*/     UINT8        _PADDING4_[0x4];
/*0x0C0*/     struct _PO_MEMORY_IMAGE* MemoryImage;
/*0x0C8*/     ULONG32*     PerformanceStats;
/*0x0D0*/     struct _MDL* BootLoaderLogMdl;
/*0x0D8*/     ULONG32      SiLogOffset;
/*0x0DC*/     UINT8        _PADDING5_[0x4];
/*0x0E0*/     struct _MDL* FirmwareRuntimeInformationMdl;
/*0x0E8*/     VOID*        FirmwareRuntimeInformationVa;
/*0x0F0*/     VOID*        ResumeContext;
/*0x0F8*/     ULONG32      ResumeContextPages;
/*0x0FC*/     ULONG32      ProcessorCount;
/*0x100*/     struct _POP_PER_PROCESSOR_CONTEXT* ProcessorContext;
/*0x108*/     CHAR*        ProdConsBuffer;
/*0x110*/     ULONG32      ProdConsSize;
/*0x114*/     ULONG32      MaxDataPages;
/*0x118*/     VOID*        ExtraBuffer;
/*0x120*/     UINT64       ExtraBufferSize;
/*0x128*/     VOID*        ExtraMapVa;
/*0x130*/     struct _POP_IO_INFO IoInfo;                          // 12 elements, 0x60 bytes (sizeof)
          }POP_HIBER_CONTEXT, *PPOP_HIBER_CONTEXT;

          typedef struct _POP_IO_INFO          // 12 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _MDL* DumpMdl;
/*0x008*/     enum _POP_IO_STATUS IoStatus;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     UINT64       IoStartCount;
/*0x018*/     UINT64       IoBytesCompleted;
/*0x020*/     UINT64       IoBytesInProgress;
/*0x028*/     UINT64       RequestSize;
/*0x030*/     union _LARGE_INTEGER IoLocation; // 4 elements, 0x8 bytes (sizeof)
/*0x038*/     UINT64       FileOffset;
/*0x040*/     VOID*        Buffer;
/*0x048*/     UINT8        AsyncCapable;
/*0x049*/     UINT8        _PADDING1_[0x7];
/*0x050*/     UINT64       BytesToRead;
/*0x058*/     ULONG32      Pages;
/*0x05C*/     UINT8        _PADDING2_[0x4];
          }POP_IO_INFO, *PPOP_IO_INFO;

          typedef struct _POP_IRP_DATA                                    // 14 elements, 0x78 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;                                    // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _IRP* Irp;
/*0x018*/     struct _DEVICE_OBJECT* Pdo;
/*0x020*/     struct _DEVICE_OBJECT* TargetDevice;
/*0x028*/     struct _DEVICE_OBJECT* CurrentDevice;
/*0x030*/     UINT8        MinorFunction;
/*0x031*/     UINT8        _PADDING0_[0x3];
/*0x034*/     enum _POWER_STATE_TYPE PowerStateType;
/*0x038*/     union _POWER_STATE PowerState;                              // 2 elements, 0x4 bytes (sizeof)
/*0x03C*/     ULONG32      WatchdogCount;
/*0x040*/     UINT8        WatchdogState;
/*0x041*/     UINT8        _PADDING1_[0x7];
/*0x048*/     struct _POP_FX_DEVICE* FxDevice;
/*0x050*/     UINT8        SystemTransition;
/*0x051*/     UINT8        _PADDING2_[0x7];
              union                                                       // 2 elements, 0x20 bytes (sizeof)
              {
                  struct                                                  // 4 elements, 0x20 bytes (sizeof)
                  {
/*0x058*/             FUNCT_00AE_2665_CallerCompletion* CallerCompletion;
/*0x060*/             VOID*        CallerContext;
/*0x068*/             struct _DEVICE_OBJECT* CallerDevice;
/*0x070*/             UINT8        SystemWake;
/*0x071*/             UINT8        _PADDING3_[0x7];
                  }Device;
                  struct                                                  // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x058*/             struct _PO_DEVICE_NOTIFY* NotifyDevice;
/*0x060*/             UINT8        FxDeviceActivated;
/*0x061*/             UINT8        _PADDING3_[0x7];
                  }System;
              };
          }POP_IRP_DATA, *PPOP_IRP_DATA;

          typedef struct _POP_IRP_WORKER_ENTRY // 5 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;         // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _ETHREAD* Thread;
/*0x018*/     struct _IRP* Irp;
/*0x020*/     struct _DEVICE_OBJECT* Device;
/*0x028*/     UINT8        Static;
/*0x029*/     UINT8        _PADDING0_[0x7];
          }POP_IRP_WORKER_ENTRY, *PPOP_IRP_WORKER_ENTRY;

          typedef struct _POP_PER_PROCESSOR_CONTEXT    // 15 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     UINT8*       UncompressedData;
/*0x008*/     VOID*        MappingVa;
/*0x010*/     VOID*        XpressEncodeWorkspace;
/*0x018*/     UINT8*       CompressedDataBuffer;
/*0x020*/     UINT64       CopyTicks;
/*0x028*/     UINT64       CompressTicks;
/*0x030*/     UINT64       BytesCopied;
/*0x038*/     UINT64       PagesProcessed;
/*0x040*/     UINT64       DecompressTicks;
/*0x048*/     UINT64       ResumeCopyTicks;
/*0x050*/     UINT64       SharedBufferTicks;
/*0x058*/     UINT64       DecompressTicksByMethod[2];
/*0x068*/     UINT64       DecompressSizeByMethod[2];
/*0x078*/     ULONG32      CompressCount;
/*0x07C*/     ULONG32      HuffCompressCount;
          }POP_PER_PROCESSOR_CONTEXT, *PPOP_PER_PROCESSOR_CONTEXT;

          typedef struct _POP_POWER_ACTION                                       // 23 elements, 0xE0 bytes (sizeof)
          {
/*0x000*/     UINT8        Updates;
/*0x001*/     UINT8        State;
/*0x002*/     UINT8        Shutdown;
/*0x003*/     UINT8        _PADDING0_[0x1];
/*0x004*/     enum _POWER_ACTION Action;
/*0x008*/     enum _SYSTEM_POWER_STATE LightestState;
/*0x00C*/     ULONG32      Flags;
/*0x010*/     LONG32       Status;
/*0x014*/     enum _POWER_POLICY_DEVICE_TYPE DeviceType;
/*0x018*/     ULONG32      DeviceTypeFlags;
/*0x01C*/     UINT8        IrpMinor;
/*0x01D*/     UINT8        Waking;
/*0x01E*/     UINT8        _PADDING1_[0x2];
/*0x020*/     enum _SYSTEM_POWER_STATE SystemState;
/*0x024*/     enum _SYSTEM_POWER_STATE NextSystemState;
/*0x028*/     enum _SYSTEM_POWER_STATE EffectiveSystemState;
/*0x02C*/     enum _SYSTEM_POWER_STATE CurrentSystemState;
/*0x030*/     struct _POP_SHUTDOWN_BUG_CHECK* ShutdownBugCode;
/*0x038*/     struct _POP_DEVICE_SYS_STATE* DevState;
/*0x040*/     struct _POP_HIBER_CONTEXT* HiberContext;
/*0x048*/     UINT64       WakeTime;
/*0x050*/     UINT64       SleepTime;
/*0x058*/     enum _SYSTEM_POWER_CONDITION WakeAlarmSignaled;
/*0x05C*/     UINT8        _PADDING2_[0x4];
/*0x060*/     struct __2011110910380F00288CE6D17A0827C00_WakeAlarm WakeAlarm[3];
/*0x090*/     struct _SYSTEM_POWER_CAPABILITIES FilteredCapabilities;            // 31 elements, 0x4C bytes (sizeof)
/*0x0DC*/     UINT8        _PADDING3_[0x4];
          }POP_POWER_ACTION, *PPOP_POWER_ACTION;

          typedef struct _POP_RW_LOCK    // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK Lock; // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _KTHREAD* Thread;
          }POP_RW_LOCK, *PPOP_RW_LOCK;

          typedef struct _POP_SHUTDOWN_BUG_CHECK // 8 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     VOID*        ThreadHandle;
/*0x008*/     VOID*        ThreadId;
/*0x010*/     VOID*        ProcessId;
/*0x018*/     ULONG32      Code;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     UINT64       Parameter1;
/*0x028*/     UINT64       Parameter2;
/*0x030*/     UINT64       Parameter3;
/*0x038*/     UINT64       Parameter4;
          }POP_SHUTDOWN_BUG_CHECK, *PPOP_SHUTDOWN_BUG_CHECK;

          typedef struct _POP_SYSTEM_IDLE          // 12 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     LONG32       AverageIdleness;
/*0x004*/     LONG32       LowestIdleness;
/*0x008*/     ULONG32      Time;
/*0x00C*/     ULONG32      Timeout;
/*0x010*/     ULONG32      LastUserInput;
/*0x014*/     struct _POWER_ACTION_POLICY Action;  // 3 elements, 0xC bytes (sizeof)
/*0x020*/     enum _SYSTEM_POWER_STATE MinState;
/*0x024*/     ULONG32      SystemRequired;
/*0x028*/     UINT8        IdleWorker;
/*0x029*/     UINT8        Sampling;
/*0x02A*/     UINT8        _PADDING0_[0x6];
/*0x030*/     UINT64       LastTick;
/*0x038*/     ULONG32      LastSystemRequiredTime;
/*0x03C*/     UINT8        _PADDING1_[0x4];
          }POP_SYSTEM_IDLE, *PPOP_SYSTEM_IDLE;

          typedef struct _POP_THERMAL_ZONE              // 18 elements, 0x208 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;                  // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     UINT8        State;
/*0x011*/     UINT8        Flags;
/*0x012*/     UINT8        Mode;
/*0x013*/     UINT8        PendingMode;
/*0x014*/     UINT8        ActivePoint;
/*0x015*/     UINT8        PendingActivePoint;
/*0x016*/     UINT8        _PADDING0_[0x2];
/*0x018*/     LONG32       Throttle;
/*0x01C*/     UINT8        _PADDING1_[0x4];
/*0x020*/     UINT64       LastTime;
/*0x028*/     ULONG32      SampleRate;
/*0x02C*/     ULONG32      LastTemp;
/*0x030*/     struct _KTIMER PassiveTimer;              // 6 elements, 0x40 bytes (sizeof)
/*0x070*/     struct _KDPC PassiveDpc;                  // 9 elements, 0x40 bytes (sizeof)
/*0x0B0*/     struct _POP_ACTION_TRIGGER OverThrottled; // 5 elements, 0x18 bytes (sizeof)
/*0x0C8*/     struct _IRP* Irp;
/*0x0D0*/     struct _THERMAL_INFORMATION_EX Info;      // 11 elements, 0x98 bytes (sizeof)
/*0x168*/     union _LARGE_INTEGER InfoLastUpdateTime;  // 4 elements, 0x8 bytes (sizeof)
/*0x170*/     struct _POP_THERMAL_ZONE_METRICS Metrics; // 8 elements, 0x98 bytes (sizeof)
          }POP_THERMAL_ZONE, *PPOP_THERMAL_ZONE;

          typedef struct _POP_THERMAL_ZONE_METRICS          // 8 elements, 0x98 bytes (sizeof)
          {
/*0x000*/     struct _ERESOURCE MetricsResource;            // 17 elements, 0x68 bytes (sizeof)
/*0x068*/     ULONG32      ActiveCount;
/*0x06C*/     ULONG32      PassiveCount;
/*0x070*/     union _LARGE_INTEGER LastActiveStartTick;     // 4 elements, 0x8 bytes (sizeof)
/*0x078*/     union _LARGE_INTEGER AverageActiveTime;       // 4 elements, 0x8 bytes (sizeof)
/*0x080*/     union _LARGE_INTEGER LastPassiveStartTick;    // 4 elements, 0x8 bytes (sizeof)
/*0x088*/     union _LARGE_INTEGER AveragePassiveTime;      // 4 elements, 0x8 bytes (sizeof)
/*0x090*/     union _LARGE_INTEGER StartTickSinceLastReset; // 4 elements, 0x8 bytes (sizeof)
          }POP_THERMAL_ZONE_METRICS, *PPOP_THERMAL_ZONE_METRICS;

          typedef struct _POP_TRIGGER_WAIT         // 4 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _KEVENT Event;                // 1 elements, 0x18 bytes (sizeof)
/*0x018*/     LONG32       Status;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     struct _LIST_ENTRY Link;             // 2 elements, 0x10 bytes (sizeof)
/*0x030*/     struct _POP_ACTION_TRIGGER* Trigger;
          }POP_TRIGGER_WAIT, *PPOP_TRIGGER_WAIT;

          typedef struct _PO_MEMORY_IMAGE                   // 36 elements, 0x318 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     ULONG32      ImageType;
/*0x008*/     ULONG32      CheckSum;
/*0x00C*/     ULONG32      LengthSelf;
/*0x010*/     UINT64       PageSelf;
/*0x018*/     ULONG32      PageSize;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     union _LARGE_INTEGER SystemTime;              // 4 elements, 0x8 bytes (sizeof)
/*0x028*/     UINT64       InterruptTime;
/*0x030*/     ULONG32      FeatureFlags;
/*0x034*/     UINT8        HiberFlags;
/*0x035*/     UINT8        spare[3];
/*0x038*/     ULONG32      NoHiberPtes;
/*0x03C*/     UINT8        _PADDING1_[0x4];
/*0x040*/     UINT64       HiberVa;
/*0x048*/     ULONG32      NoFreePages;
/*0x04C*/     ULONG32      FreeMapCheck;
/*0x050*/     ULONG32      WakeCheck;
/*0x054*/     UINT8        _PADDING2_[0x4];
/*0x058*/     UINT64       NumPagesForLoader;
/*0x060*/     UINT64       FirstBootRestorePage;
/*0x068*/     UINT64       FirstKernelRestorePage;
/*0x070*/     struct _PO_HIBER_PERF PerfInfo;               // 51 elements, 0x188 bytes (sizeof)
/*0x1F8*/     ULONG32      FirmwareRuntimeInformationPages;
/*0x1FC*/     UINT8        _PADDING3_[0x4];
/*0x200*/     UINT64       FirmwareRuntimeInformation[1];
/*0x208*/     ULONG32      SiLogOffset;
/*0x20C*/     ULONG32      NoBootLoaderLogPages;
/*0x210*/     UINT64       BootLoaderLogPages[24];
/*0x2D0*/     ULONG32      NotUsed;
/*0x2D4*/     ULONG32      ResumeContextCheck;
/*0x2D8*/     ULONG32      ResumeContextPages;
/*0x2DC*/     UINT8        Hiberboot;
/*0x2DD*/     UINT8        _PADDING4_[0x3];
/*0x2E0*/     UINT64       HvCr3;
/*0x2E8*/     UINT64       HvEntryPoint;
/*0x2F0*/     UINT64       HvReservedTransitionAddress;
/*0x2F8*/     UINT64       HvReservedTransitionAddressSize;
/*0x300*/     UINT64       BootFlags;
/*0x308*/     UINT64       HalEntryPointPhysical;
/*0x310*/     UINT64       HighestPhysicalPage;
          }PO_MEMORY_IMAGE, *PPO_MEMORY_IMAGE;

          typedef struct _POWER_ACTION_POLICY // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     enum _POWER_ACTION Action;
/*0x004*/     ULONG32      Flags;
/*0x008*/     ULONG32      EventCode;
          }POWER_ACTION_POLICY, *PPOWER_ACTION_POLICY;

          typedef struct _SYSTEM_POWER_CAPABILITIES            // 31 elements, 0x4C bytes (sizeof)
          {
/*0x000*/     UINT8        PowerButtonPresent;
/*0x001*/     UINT8        SleepButtonPresent;
/*0x002*/     UINT8        LidPresent;
/*0x003*/     UINT8        SystemS1;
/*0x004*/     UINT8        SystemS2;
/*0x005*/     UINT8        SystemS3;
/*0x006*/     UINT8        SystemS4;
/*0x007*/     UINT8        SystemS5;
/*0x008*/     UINT8        HiberFilePresent;
/*0x009*/     UINT8        FullWake;
/*0x00A*/     UINT8        VideoDimPresent;
/*0x00B*/     UINT8        ApmPresent;
/*0x00C*/     UINT8        UpsPresent;
/*0x00D*/     UINT8        ThermalControl;
/*0x00E*/     UINT8        ProcessorThrottle;
/*0x00F*/     UINT8        ProcessorMinThrottle;
/*0x010*/     UINT8        ProcessorMaxThrottle;
/*0x011*/     UINT8        FastSystemS4;
/*0x012*/     UINT8        Hiberboot;
/*0x013*/     UINT8        WakeAlarmPresent;
/*0x014*/     UINT8        AoAc;
/*0x015*/     UINT8        DiskSpinDown;
/*0x016*/     UINT8        spare3[8];
/*0x01E*/     UINT8        SystemBatteriesPresent;
/*0x01F*/     UINT8        BatteriesAreShortTerm;
/*0x020*/     struct _BATTERY_REPORTING_SCALE BatteryScale[3];
/*0x038*/     enum _SYSTEM_POWER_STATE AcOnLineWake;
/*0x03C*/     enum _SYSTEM_POWER_STATE SoftLidWake;
/*0x040*/     enum _SYSTEM_POWER_STATE RtcWake;
/*0x044*/     enum _SYSTEM_POWER_STATE MinDeviceWakeState;
/*0x048*/     enum _SYSTEM_POWER_STATE DefaultLowLatencyWake;
          }SYSTEM_POWER_CAPABILITIES, *PSYSTEM_POWER_CAPABILITIES;

          typedef struct _SYSTEM_POWER_LEVEL           // 5 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT8        Enable;
/*0x001*/     UINT8        Spare[3];
/*0x004*/     ULONG32      BatteryLevel;
/*0x008*/     struct _POWER_ACTION_POLICY PowerPolicy; // 3 elements, 0xC bytes (sizeof)
/*0x014*/     enum _SYSTEM_POWER_STATE MinSystemState;
          }SYSTEM_POWER_LEVEL, *PSYSTEM_POWER_LEVEL;

typedef enum _POP_DEVICE_IDLE_TYPE  // 2 elements, 0x4 bytes
{
    DeviceIdleNormal = 0 /*0x0*/,
    DeviceIdleDisk   = 1 /*0x1*/
}POP_DEVICE_IDLE_TYPE, *PPOP_DEVICE_IDLE_TYPE;

typedef enum _POP_IO_STATUS  // 3 elements, 0x4 bytes
{
    IoReady   = 0 /*0x0*/,
    IoPending = 1 /*0x1*/,
    IoDone    = 2 /*0x2*/
}POP_IO_STATUS, *PPOP_IO_STATUS;

typedef enum _POWER_STATE_TYPE  // 2 elements, 0x4 bytes
{
    SystemPowerState = 0 /*0x0*/,
    DevicePowerState = 1 /*0x1*/
}POWER_STATE_TYPE, *PPOWER_STATE_TYPE;

typedef enum _SYSTEM_POWER_CONDITION  // 4 elements, 0x4 bytes
{
    PoAc               = 0 /*0x0*/,
    PoDc               = 1 /*0x1*/,
    PoHot              = 2 /*0x2*/,
    PoConditionMaximum = 3 /*0x3*/
}SYSTEM_POWER_CONDITION, *PSYSTEM_POWER_CONDITION;

          typedef struct _SYSTEM_POWER_POLICY                // 28 elements, 0xE8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Revision;
/*0x004*/     struct _POWER_ACTION_POLICY PowerButton;       // 3 elements, 0xC bytes (sizeof)
/*0x010*/     struct _POWER_ACTION_POLICY SleepButton;       // 3 elements, 0xC bytes (sizeof)
/*0x01C*/     struct _POWER_ACTION_POLICY LidClose;          // 3 elements, 0xC bytes (sizeof)
/*0x028*/     enum _SYSTEM_POWER_STATE LidOpenWake;
/*0x02C*/     ULONG32      Reserved;
/*0x030*/     struct _POWER_ACTION_POLICY Idle;              // 3 elements, 0xC bytes (sizeof)
/*0x03C*/     ULONG32      IdleTimeout;
/*0x040*/     UINT8        IdleSensitivity;
/*0x041*/     UINT8        DynamicThrottle;
/*0x042*/     UINT8        Spare2[2];
/*0x044*/     enum _SYSTEM_POWER_STATE MinSleep;
/*0x048*/     enum _SYSTEM_POWER_STATE MaxSleep;
/*0x04C*/     enum _SYSTEM_POWER_STATE ReducedLatencySleep;
/*0x050*/     ULONG32      WinLogonFlags;
/*0x054*/     ULONG32      Spare3;
/*0x058*/     ULONG32      DozeS4Timeout;
/*0x05C*/     ULONG32      BroadcastCapacityResolution;
/*0x060*/     struct _SYSTEM_POWER_LEVEL DischargePolicy[4];
/*0x0C0*/     ULONG32      VideoTimeout;
/*0x0C4*/     UINT8        VideoDimDisplay;
/*0x0C5*/     UINT8        _PADDING0_[0x3];
/*0x0C8*/     ULONG32      VideoReserved[3];
/*0x0D4*/     ULONG32      SpindownTimeout;
/*0x0D8*/     UINT8        OptimizeForPower;
/*0x0D9*/     UINT8        FanThrottleTolerance;
/*0x0DA*/     UINT8        ForcedThrottle;
/*0x0DB*/     UINT8        MinThrottle;
/*0x0DC*/     struct _POWER_ACTION_POLICY OverThrottled;     // 3 elements, 0xC bytes (sizeof)
          }SYSTEM_POWER_POLICY, *PSYSTEM_POWER_POLICY;

          typedef struct _SYSTEM_POWER_STATE_CONTEXT          // 8 elements, 0x4 bytes (sizeof)
          {
              union                                           // 2 elements, 0x4 bytes (sizeof)
              {
                  struct                                      // 7 elements, 0x4 bytes (sizeof)
                  {
/*0x000*/             ULONG32      Reserved1 : 8;             // 0 BitPosition
/*0x000*/             ULONG32      TargetSystemState : 4;     // 8 BitPosition
/*0x000*/             ULONG32      EffectiveSystemState : 4;  // 12 BitPosition
/*0x000*/             ULONG32      CurrentSystemState : 4;    // 16 BitPosition
/*0x000*/             ULONG32      IgnoreHibernationPath : 1; // 20 BitPosition
/*0x000*/             ULONG32      PseudoTransition : 1;      // 21 BitPosition
/*0x000*/             ULONG32      Reserved2 : 10;            // 22 BitPosition
                  };
/*0x000*/         ULONG32      ContextAsUlong;
              };
          }SYSTEM_POWER_STATE_CONTEXT, *PSYSTEM_POWER_STATE_CONTEXT;

          typedef struct _THERMAL_INFORMATION    // 10 elements, 0x58 bytes (sizeof)
          {
/*0x000*/     ULONG32      ThermalStamp;
/*0x004*/     ULONG32      ThermalConstant1;
/*0x008*/     ULONG32      ThermalConstant2;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     UINT64       Processors;
/*0x018*/     ULONG32      SamplingPeriod;
/*0x01C*/     ULONG32      CurrentTemperature;
/*0x020*/     ULONG32      PassiveTripPoint;
/*0x024*/     ULONG32      CriticalTripPoint;
/*0x028*/     UINT8        ActiveTripPointCount;
/*0x029*/     UINT8        _PADDING1_[0x3];
/*0x02C*/     ULONG32      ActiveTripPoint[10];
/*0x054*/     UINT8        _PADDING2_[0x4];
          }THERMAL_INFORMATION, *PTHERMAL_INFORMATION;

          typedef struct _THERMAL_INFORMATION_EX  // 11 elements, 0x98 bytes (sizeof)
          {
/*0x000*/     ULONG32      ThermalStamp;
/*0x004*/     ULONG32      ThermalConstant1;
/*0x008*/     ULONG32      ThermalConstant2;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     struct _KAFFINITY_EX Processors;    // 4 elements, 0x48 bytes (sizeof)
/*0x058*/     ULONG32      SamplingPeriod;
/*0x05C*/     ULONG32      CurrentTemperature;
/*0x060*/     ULONG32      PassiveTripPoint;
/*0x064*/     ULONG32      CriticalTripPoint;
/*0x068*/     UINT8        ActiveTripPointCount;
/*0x069*/     UINT8        _PADDING1_[0x3];
/*0x06C*/     ULONG32      ActiveTripPoint[10];
/*0x094*/     ULONG32      S4TransitionTripPoint;
          }THERMAL_INFORMATION_EX, *PTHERMAL_INFORMATION_EX;

          typedef struct _BATTERY_REPORTING_SCALE // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Granularity;
/*0x004*/     ULONG32      Capacity;
          }BATTERY_REPORTING_SCALE, *PBATTERY_REPORTING_SCALE;

          typedef struct _PROCESSOR_IDLESTATE_INFO // 4 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      TimeCheck;
/*0x004*/     UINT8        DemotePercent;
/*0x005*/     UINT8        PromotePercent;
/*0x006*/     UINT8        Spare[2];
          }PROCESSOR_IDLESTATE_INFO, *PPROCESSOR_IDLESTATE_INFO;

          typedef struct _PROCESSOR_IDLESTATE_POLICY      // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT16       Revision;
              union                                       // 4 elements, 0x2 bytes (sizeof)
              {
/*0x002*/         UINT16       AsUSHORT;
                  struct                                  // 3 elements, 0x2 bytes (sizeof)
                  {
/*0x002*/             UINT16       AllowScaling : 1;      // 0 BitPosition
/*0x002*/             UINT16       Disabled : 1;          // 1 BitPosition
/*0x002*/             UINT16       Reserved : 14;         // 2 BitPosition
                  };
              }Flags;
/*0x004*/     ULONG32      PolicyCount;
/*0x008*/     struct _PROCESSOR_IDLESTATE_INFO Policy[3];
          }PROCESSOR_IDLESTATE_POLICY, *PPROCESSOR_IDLESTATE_POLICY;

          typedef struct _PROCESSOR_PERFSTATE_POLICY           // 11 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      Revision;
/*0x004*/     UINT8        MaxThrottle;
/*0x005*/     UINT8        MinThrottle;
/*0x006*/     UINT8        BusyAdjThreshold;
              union                                            // 2 elements, 0x1 bytes (sizeof)
              {
/*0x007*/         UINT8        Spare;
                  union                                        // 5 elements, 0x1 bytes (sizeof)
                  {
/*0x007*/             UINT8        AsUCHAR;
                      struct                                   // 4 elements, 0x1 bytes (sizeof)
                      {
/*0x007*/                 UINT8        NoDomainAccounting : 1; // 0 BitPosition
/*0x007*/                 UINT8        IncreasePolicy : 2;     // 1 BitPosition
/*0x007*/                 UINT8        DecreasePolicy : 2;     // 3 BitPosition
/*0x007*/                 UINT8        Reserved : 3;           // 5 BitPosition
                      };
                  }Flags;
              };
/*0x008*/     ULONG32      TimeCheck;
/*0x00C*/     ULONG32      IncreaseTime;
/*0x010*/     ULONG32      DecreaseTime;
/*0x014*/     ULONG32      IncreasePercent;
/*0x018*/     ULONG32      DecreasePercent;
          }PROCESSOR_PERFSTATE_POLICY, *PPROCESSOR_PERFSTATE_POLICY;

typedef enum _SYSTEM_POWER_STATE  // 8 elements, 0x4 bytes
{
    PowerSystemUnspecified = 0 /*0x0*/,
    PowerSystemWorking     = 1 /*0x1*/,
    PowerSystemSleeping1   = 2 /*0x2*/,
    PowerSystemSleeping2   = 3 /*0x3*/,
    PowerSystemSleeping3   = 4 /*0x4*/,
    PowerSystemHibernate   = 5 /*0x5*/,
    PowerSystemShutdown    = 6 /*0x6*/,
    PowerSystemMaximum     = 7 /*0x7*/
}SYSTEM_POWER_STATE, *PSYSTEM_POWER_STATE;

typedef enum _POWER_ACTION  // 8 elements, 0x4 bytes
{
    PowerActionNone          = 0 /*0x0*/,
    PowerActionReserved      = 1 /*0x1*/,
    PowerActionSleep         = 2 /*0x2*/,
    PowerActionHibernate     = 3 /*0x3*/,
    PowerActionShutdown      = 4 /*0x4*/,
    PowerActionShutdownReset = 5 /*0x5*/,
    PowerActionShutdownOff   = 6 /*0x6*/,
    PowerActionWarmEject     = 7 /*0x7*/
}POWER_ACTION, *PPOWER_ACTION;

typedef enum _POWER_POLICY_DEVICE_TYPE  // 10 elements, 0x4 bytes
{
    PolicyDeviceSystemButton     = 0 /*0x0*/,
    PolicyDeviceThermalZone      = 1 /*0x1*/,
    PolicyDeviceBattery          = 2 /*0x2*/,
    PolicyDeviceMemory           = 3 /*0x3*/,
    PolicyInitiatePowerActionAPI = 4 /*0x4*/,
    PolicySetPowerStateAPI       = 5 /*0x5*/,
    PolicyImmediateDozeS4        = 6 /*0x6*/,
    PolicySystemIdle             = 7 /*0x7*/,
    PolicyDeviceWakeAlarm        = 8 /*0x8*/,
    PolicyDeviceMax              = 9 /*0x9*/
}POWER_POLICY_DEVICE_TYPE, *PPOWER_POLICY_DEVICE_TYPE;

