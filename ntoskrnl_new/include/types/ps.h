typedef enum _PS_ATTRIBUTE_NUM  // 19 elements, 0x4 bytes
{
    PsAttributeParentProcess        = 0 /*0x0*/,
    PsAttributeDebugObject          = 1 /*0x1*/,
    PsAttributeToken                = 2 /*0x2*/,
    PsAttributeClientId             = 3 /*0x3*/,
    PsAttributeTebAddress           = 4 /*0x4*/,
    PsAttributeImageName            = 5 /*0x5*/,
    PsAttributeImageInfo            = 6 /*0x6*/,
    PsAttributeMemoryReserve        = 7 /*0x7*/,
    PsAttributePriorityClass        = 8 /*0x8*/,
    PsAttributeErrorMode            = 9 /*0x9*/,
    PsAttributeStdHandleInfo        = 10 /*0xA*/,
    PsAttributeHandleList           = 11 /*0xB*/,
    PsAttributeGroupAffinity        = 12 /*0xC*/,
    PsAttributePreferredNode        = 13 /*0xD*/,
    PsAttributeIdealProcessor       = 14 /*0xE*/,
    PsAttributeUmsThread            = 15 /*0xF*/,
    PsAttributeMitigationOptions    = 16 /*0x10*/,
    PsAttributeSecurityCapabilities = 17 /*0x11*/,
    PsAttributeMax                  = 18 /*0x12*/
}PS_ATTRIBUTE_NUM, *PPS_ATTRIBUTE_NUM;

typedef enum _PS_RESOURCE_TYPE  // 6 elements, 0x4 bytes
{
    PsResourceNonPagedPool = 0 /*0x0*/,
    PsResourcePagedPool    = 1 /*0x1*/,
    PsResourcePageFile     = 2 /*0x2*/,
    PsResourceWorkingSet   = 3 /*0x3*/,
    PsResourceCpuRate      = 4 /*0x4*/,
    PsResourceMax          = 5 /*0x5*/
}PS_RESOURCE_TYPE, *PPS_RESOURCE_TYPE;

typedef enum _PS_STD_HANDLE_STATE  // 4 elements, 0x4 bytes
{
    PsNeverDuplicate     = 0 /*0x0*/,
    PsRequestDuplicate   = 1 /*0x1*/,
    PsAlwaysDuplicate    = 2 /*0x2*/,
    PsMaxStdHandleStates = 3 /*0x3*/
}PS_STD_HANDLE_STATE, *PPS_STD_HANDLE_STATE;

typedef enum _PS_WAKE_REASON  // 5 elements, 0x4 bytes
{
    PsWakeReasonUser   = 0 /*0x0*/,
    PsWakeReasonDevice = 1 /*0x1*/,
    PsWakeReasonKernel = 2 /*0x2*/,
    PsWakeReasonPower  = 3 /*0x3*/,
    PsMaxWakeReasons   = 4 /*0x4*/
}PS_WAKE_REASON, *PPS_WAKE_REASON;

typedef enum _PS_CREATE_STATE  // 8 elements, 0x4 bytes
{
    PsCreateInitialState        = 0 /*0x0*/,
    PsCreateFailOnFileOpen      = 1 /*0x1*/,
    PsCreateFailOnSectionCreate = 2 /*0x2*/,
    PsCreateFailExeFormat       = 3 /*0x3*/,
    PsCreateFailMachineMismatch = 4 /*0x4*/,
    PsCreateFailExeName         = 5 /*0x5*/,
    PsCreateSuccess             = 6 /*0x6*/,
    PsCreateMaximumStates       = 7 /*0x7*/
}PS_CREATE_STATE, *PPS_CREATE_STATE;

          typedef struct _CLIENT_ID       // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        UniqueProcess;
/*0x008*/     VOID*        UniqueThread;
          }CLIENT_ID, *PCLIENT_ID;

          typedef struct _CLIENT_ID32     // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      UniqueProcess;
/*0x004*/     ULONG32      UniqueThread;
          }CLIENT_ID32, *PCLIENT_ID32;

          typedef struct _CLIENT_ID64     // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       UniqueProcess;
/*0x008*/     UINT64       UniqueThread;
          }CLIENT_ID64, *PCLIENT_ID64;

          typedef struct _EJOB                                            // 99 elements, 0x3C8 bytes (sizeof)
          {
/*0x000*/     struct _KEVENT Event;                                       // 1 elements, 0x18 bytes (sizeof)
/*0x018*/     struct _LIST_ENTRY JobLinks;                                // 2 elements, 0x10 bytes (sizeof)
/*0x028*/     struct _LIST_ENTRY ProcessListHead;                         // 2 elements, 0x10 bytes (sizeof)
/*0x038*/     struct _ERESOURCE JobLock;                                  // 17 elements, 0x68 bytes (sizeof)
/*0x0A0*/     union _LARGE_INTEGER TotalUserTime;                         // 4 elements, 0x8 bytes (sizeof)
/*0x0A8*/     union _LARGE_INTEGER TotalKernelTime;                       // 4 elements, 0x8 bytes (sizeof)
/*0x0B0*/     union _LARGE_INTEGER TotalCycleTime;                        // 4 elements, 0x8 bytes (sizeof)
/*0x0B8*/     union _LARGE_INTEGER ThisPeriodTotalUserTime;               // 4 elements, 0x8 bytes (sizeof)
/*0x0C0*/     union _LARGE_INTEGER ThisPeriodTotalKernelTime;             // 4 elements, 0x8 bytes (sizeof)
/*0x0C8*/     UINT64       TotalContextSwitches;
/*0x0D0*/     ULONG32      TotalPageFaultCount;
/*0x0D4*/     ULONG32      TotalProcesses;
/*0x0D8*/     ULONG32      ActiveProcesses;
/*0x0DC*/     ULONG32      TotalTerminatedProcesses;
/*0x0E0*/     union _LARGE_INTEGER PerProcessUserTimeLimit;               // 4 elements, 0x8 bytes (sizeof)
/*0x0E8*/     union _LARGE_INTEGER PerJobUserTimeLimit;                   // 4 elements, 0x8 bytes (sizeof)
/*0x0F0*/     UINT64       MinimumWorkingSetSize;
/*0x0F8*/     UINT64       MaximumWorkingSetSize;
/*0x100*/     ULONG32      LimitFlags;
/*0x104*/     ULONG32      ActiveProcessLimit;
/*0x108*/     struct _KAFFINITY_EX Affinity;                              // 4 elements, 0x48 bytes (sizeof)
/*0x150*/     UINT8        PriorityClass;
/*0x151*/     UINT8        _PADDING0_[0x7];
/*0x158*/     struct _JOB_ACCESS_STATE* AccessState;
/*0x160*/     VOID*        AccessStateQuotaReference;
/*0x168*/     ULONG32      UIRestrictionsClass;
/*0x16C*/     ULONG32      EndOfJobTimeAction;
/*0x170*/     VOID*        CompletionPort;
/*0x178*/     VOID*        CompletionKey;
/*0x180*/     UINT64       CompletionCount;
/*0x188*/     ULONG32      SessionId;
/*0x18C*/     ULONG32      SchedulingClass;
/*0x190*/     UINT64       ReadOperationCount;
/*0x198*/     UINT64       WriteOperationCount;
/*0x1A0*/     UINT64       OtherOperationCount;
/*0x1A8*/     UINT64       ReadTransferCount;
/*0x1B0*/     UINT64       WriteTransferCount;
/*0x1B8*/     UINT64       OtherTransferCount;
/*0x1C0*/     struct _PROCESS_DISK_COUNTERS DiskIoInfo;                   // 5 elements, 0x28 bytes (sizeof)
/*0x1E8*/     UINT64       ProcessMemoryLimit;
/*0x1F0*/     UINT64       JobMemoryLimit;
/*0x1F8*/     UINT64       PeakProcessMemoryUsed;
/*0x200*/     UINT64       PeakJobMemoryUsed;
/*0x208*/     struct _KAFFINITY_EX EffectiveAffinity;                     // 4 elements, 0x48 bytes (sizeof)
/*0x250*/     union _LARGE_INTEGER EffectivePerProcessUserTimeLimit;      // 4 elements, 0x8 bytes (sizeof)
/*0x258*/     UINT64       EffectiveMinimumWorkingSetSize;
/*0x260*/     UINT64       EffectiveMaximumWorkingSetSize;
/*0x268*/     UINT64       EffectiveProcessMemoryLimit;
/*0x270*/     struct _EJOB* EffectiveProcessMemoryLimitJob;
/*0x278*/     struct _EJOB* EffectivePerProcessUserTimeLimitJob;
/*0x280*/     ULONG32      EffectiveLimitFlags;
/*0x284*/     ULONG32      EffectiveSchedulingClass;
/*0x288*/     ULONG32      EffectiveFreezeCount;
/*0x28C*/     ULONG32      EffectiveIdleAwareCount;
/*0x290*/     UINT8        EffectivePriorityClass;
/*0x291*/     UINT8        Reserved[3];
/*0x294*/     ULONG32      CompletionFilter;
              union                                                       // 2 elements, 0x28 bytes (sizeof)
              {
/*0x298*/         struct _WNF_STATE_NAME WakeChannel;                     // 1 elements, 0x8 bytes (sizeof)
/*0x298*/         struct _JOBOBJECT_WAKE_INFORMATION WakeInfo;            // 2 elements, 0x28 bytes (sizeof)
              };
/*0x2C0*/     struct _JOBOBJECT_WAKE_FILTER WakeFilter;                   // 2 elements, 0x8 bytes (sizeof)
/*0x2C8*/     struct _EJOB* NotificationLink;
/*0x2D0*/     struct _JOB_NOTIFICATION_LIMITS* NotificationLimits;
/*0x2D8*/     VOID*        NotificationLimitsQuotaReference;
/*0x2E0*/     struct _IO_MINI_COMPLETION_PACKET_USER* NotificationPacket;
/*0x2E8*/     ULONG32      NotificationLimitFlags;
/*0x2EC*/     ULONG32      ViolationLimitFlags;
/*0x2F0*/     struct _JOB_CPU_RATE_CONTROL* CpuRateControl;
/*0x2F8*/     VOID*        EffectiveSchedulingGroup;
/*0x300*/     ULONG32      ProcessListCount;
/*0x304*/     UINT8        _PADDING1_[0x4];
/*0x308*/     UINT64       CurrentJobMemoryUsed;
/*0x310*/     struct _EX_PUSH_LOCK MemoryLimitsLock;                      // 7 elements, 0x8 bytes (sizeof)
/*0x318*/     struct _LIST_ENTRY SiblingJobLinks;                         // 2 elements, 0x10 bytes (sizeof)
/*0x328*/     struct _LIST_ENTRY ChildJobListHead;                        // 2 elements, 0x10 bytes (sizeof)
/*0x338*/     struct _EJOB* ParentJob;
/*0x340*/     struct _EJOB* RootJob;
/*0x348*/     struct _LIST_ENTRY IteratorListHead;                        // 2 elements, 0x10 bytes (sizeof)
/*0x358*/     struct _KPROCESS_VALUES Accounting;                         // 10 elements, 0x50 bytes (sizeof)
/*0x3A8*/     UINT64       TimerListLock;
/*0x3B0*/     struct _LIST_ENTRY TimerListHead;                           // 2 elements, 0x10 bytes (sizeof)
              union                                                       // 2 elements, 0x4 bytes (sizeof)
              {
/*0x3C0*/         ULONG32      JobFlags;
                  struct                                                  // 20 elements, 0x4 bytes (sizeof)
                  {
/*0x3C0*/             ULONG32      CloseDone : 1;                         // 0 BitPosition
/*0x3C0*/             ULONG32      MultiGroup : 1;                        // 1 BitPosition
/*0x3C0*/             ULONG32      OutstandingNotification : 1;           // 2 BitPosition
/*0x3C0*/             ULONG32      NotificationInProgress : 1;            // 3 BitPosition
/*0x3C0*/             ULONG32      UILimits : 1;                          // 4 BitPosition
/*0x3C0*/             ULONG32      CpuRateControlActive : 1;              // 5 BitPosition
/*0x3C0*/             ULONG32      OwnCpuRateControl : 1;                 // 6 BitPosition
/*0x3C0*/             ULONG32      Terminating : 1;                       // 7 BitPosition
/*0x3C0*/             ULONG32      WorkingSetLock : 1;                    // 8 BitPosition
/*0x3C0*/             ULONG32      JobFrozen : 1;                         // 9 BitPosition
/*0x3C0*/             ULONG32      IdleAware : 1;                         // 10 BitPosition
/*0x3C0*/             ULONG32      WakeNotificationAllocated : 1;         // 11 BitPosition
/*0x3C0*/             ULONG32      WakeNotificationEnabled : 1;           // 12 BitPosition
/*0x3C0*/             ULONG32      WakeNotificationPending : 1;           // 13 BitPosition
/*0x3C0*/             ULONG32      LimitNotificationRequired : 1;         // 14 BitPosition
/*0x3C0*/             ULONG32      ZeroCountNotificationRequired : 1;     // 15 BitPosition
/*0x3C0*/             ULONG32      CycleTimeNotificationRequired : 1;     // 16 BitPosition
/*0x3C0*/             ULONG32      CycleTimeNotificationPending : 1;      // 17 BitPosition
/*0x3C0*/             ULONG32      TimersVirtualized : 1;                 // 18 BitPosition
/*0x3C0*/             ULONG32      SpareJobFlags : 13;                    // 19 BitPosition
                  };
              };
          }EJOB, *PEJOB;

          typedef struct _EPROCESS                                               // 150 elements, 0x530 bytes (sizeof)
          {
/*0x000*/     struct _KPROCESS Pcb;                                              // 40 elements, 0x1B8 bytes (sizeof)
/*0x1B8*/     struct _EX_PUSH_LOCK ProcessLock;                                  // 7 elements, 0x8 bytes (sizeof)
/*0x1C0*/     union _LARGE_INTEGER CreateTime;                                   // 4 elements, 0x8 bytes (sizeof)
/*0x1C8*/     struct _EX_RUNDOWN_REF RundownProtect;                             // 2 elements, 0x8 bytes (sizeof)
/*0x1D0*/     VOID*        UniqueProcessId;
/*0x1D8*/     struct _LIST_ENTRY ActiveProcessLinks;                             // 2 elements, 0x10 bytes (sizeof)
/*0x1E8*/     UINT64       ProcessQuotaUsage[2];
/*0x1F8*/     UINT64       ProcessQuotaPeak[2];
/*0x208*/     UINT64       PeakVirtualSize;
/*0x210*/     UINT64       VirtualSize;
/*0x218*/     struct _LIST_ENTRY SessionProcessLinks;                            // 2 elements, 0x10 bytes (sizeof)
              union                                                              // 3 elements, 0x8 bytes (sizeof)
              {
/*0x228*/         VOID*        ExceptionPortData;
/*0x228*/         UINT64       ExceptionPortValue;
/*0x228*/         UINT64       ExceptionPortState : 3;                           // 0 BitPosition
              };
/*0x230*/     struct _EX_FAST_REF Token;                                         // 3 elements, 0x8 bytes (sizeof)
/*0x238*/     UINT64       WorkingSetPage;
/*0x240*/     struct _EX_PUSH_LOCK AddressCreationLock;                          // 7 elements, 0x8 bytes (sizeof)
/*0x248*/     struct _ETHREAD* RotateInProgress;
/*0x250*/     struct _ETHREAD* ForkInProgress;
/*0x258*/     UINT64       HardwareTrigger;
/*0x260*/     struct _EJOB* CommitChargeJob;
/*0x268*/     struct _MM_AVL_TABLE* CloneRoot;
/*0x270*/     UINT64       NumberOfPrivatePages;
/*0x278*/     UINT64       NumberOfLockedPages;
/*0x280*/     VOID*        Win32Process;
/*0x288*/     struct _EJOB* Job;
/*0x290*/     VOID*        SectionObject;
/*0x298*/     VOID*        SectionBaseAddress;
/*0x2A0*/     ULONG32      Cookie;
/*0x2A4*/     UINT8        _PADDING0_[0x4];
/*0x2A8*/     struct _PAGEFAULT_HISTORY* WorkingSetWatch;
/*0x2B0*/     VOID*        Win32WindowStation;
/*0x2B8*/     VOID*        InheritedFromUniqueProcessId;
/*0x2C0*/     VOID*        LdtInformation;
              union                                                              // 2 elements, 0x8 bytes (sizeof)
              {
/*0x2C8*/         struct _EPROCESS* CreatorProcess;
/*0x2C8*/         UINT64       ConsoleHostProcess;
              };
/*0x2D0*/     struct _PEB* Peb;
/*0x2D8*/     VOID*        Session;
/*0x2E0*/     VOID*        AweInfo;
/*0x2E8*/     struct _EPROCESS_QUOTA_BLOCK* QuotaBlock;
/*0x2F0*/     struct _HANDLE_TABLE* ObjectTable;
/*0x2F8*/     VOID*        DebugPort;
/*0x300*/     VOID*        Wow64Process;
/*0x308*/     VOID*        DeviceMap;
/*0x310*/     VOID*        EtwDataSource;
              union                                                              // 2 elements, 0x8 bytes (sizeof)
              {
/*0x318*/         struct _HARDWARE_PTE PageDirectoryPte;                         // 16 elements, 0x8 bytes (sizeof)
/*0x318*/         UINT64       Filler;
              };
/*0x320*/     UINT8        ImageFileName[15];
/*0x32F*/     UINT8        PriorityClass;
/*0x330*/     VOID*        SecurityPort;
/*0x338*/     struct _SE_AUDIT_PROCESS_CREATION_INFO SeAuditProcessCreationInfo; // 1 elements, 0x8 bytes (sizeof)
/*0x340*/     struct _LIST_ENTRY JobLinks;                                       // 2 elements, 0x10 bytes (sizeof)
/*0x350*/     VOID*        HighestUserAddress;
/*0x358*/     struct _LIST_ENTRY ThreadListHead;                                 // 2 elements, 0x10 bytes (sizeof)
/*0x368*/     ULONG32      ActiveThreads;
/*0x36C*/     ULONG32      ImagePathHash;
/*0x370*/     ULONG32      DefaultHardErrorProcessing;
/*0x374*/     LONG32       LastThreadExitStatus;
/*0x378*/     struct _EX_FAST_REF PrefetchTrace;                                 // 3 elements, 0x8 bytes (sizeof)
/*0x380*/     struct _MM_AVL_TABLE* LockedPagesList;
/*0x388*/     union _LARGE_INTEGER ReadOperationCount;                           // 4 elements, 0x8 bytes (sizeof)
/*0x390*/     union _LARGE_INTEGER WriteOperationCount;                          // 4 elements, 0x8 bytes (sizeof)
/*0x398*/     union _LARGE_INTEGER OtherOperationCount;                          // 4 elements, 0x8 bytes (sizeof)
/*0x3A0*/     union _LARGE_INTEGER ReadTransferCount;                            // 4 elements, 0x8 bytes (sizeof)
/*0x3A8*/     union _LARGE_INTEGER WriteTransferCount;                           // 4 elements, 0x8 bytes (sizeof)
/*0x3B0*/     union _LARGE_INTEGER OtherTransferCount;                           // 4 elements, 0x8 bytes (sizeof)
/*0x3B8*/     UINT64       CommitChargeLimit;
/*0x3C0*/     UINT64       CommitCharge;
/*0x3C8*/     UINT64       CommitChargePeak;
/*0x3D0*/     struct _MMSUPPORT Vm;                                              // 22 elements, 0x88 bytes (sizeof)
/*0x458*/     struct _LIST_ENTRY MmProcessLinks;                                 // 2 elements, 0x10 bytes (sizeof)
/*0x468*/     ULONG32      ModifiedPageCount;
              union                                                              // 2 elements, 0x4 bytes (sizeof)
              {
/*0x46C*/         ULONG32      Flags2;
                  struct                                                         // 30 elements, 0x4 bytes (sizeof)
                  {
/*0x46C*/             ULONG32      JobNotReallyActive : 1;                       // 0 BitPosition
/*0x46C*/             ULONG32      AccountingFolded : 1;                         // 1 BitPosition
/*0x46C*/             ULONG32      NewProcessReported : 1;                       // 2 BitPosition
/*0x46C*/             ULONG32      ExitProcessReported : 1;                      // 3 BitPosition
/*0x46C*/             ULONG32      ReportCommitChanges : 1;                      // 4 BitPosition
/*0x46C*/             ULONG32      LastReportMemory : 1;                         // 5 BitPosition
/*0x46C*/             ULONG32      Spare1 : 1;                                   // 6 BitPosition
/*0x46C*/             ULONG32      HandleTableRundown : 1;                       // 7 BitPosition
/*0x46C*/             ULONG32      NeedsHandleRundown : 1;                       // 8 BitPosition
/*0x46C*/             ULONG32      RefTraceEnabled : 1;                          // 9 BitPosition
/*0x46C*/             ULONG32      NumaAware : 1;                                // 10 BitPosition
/*0x46C*/             ULONG32      Spare2 : 1;                                   // 11 BitPosition
/*0x46C*/             ULONG32      DefaultPagePriority : 3;                      // 12 BitPosition
/*0x46C*/             ULONG32      PrimaryTokenFrozen : 1;                       // 15 BitPosition
/*0x46C*/             ULONG32      ProcessVerifierTarget : 1;                    // 16 BitPosition
/*0x46C*/             ULONG32      StackRandomizationDisabled : 1;               // 17 BitPosition
/*0x46C*/             ULONG32      AffinityPermanent : 1;                        // 18 BitPosition
/*0x46C*/             ULONG32      AffinityUpdateEnable : 1;                     // 19 BitPosition
/*0x46C*/             ULONG32      PropagateNode : 1;                            // 20 BitPosition
/*0x46C*/             ULONG32      ExplicitAffinity : 1;                         // 21 BitPosition
/*0x46C*/             ULONG32      LowVaAccessible : 1;                          // 22 BitPosition
/*0x46C*/             ULONG32      ForceRelocateImages : 1;                      // 23 BitPosition
/*0x46C*/             ULONG32      DisallowStrippedImages : 1;                   // 24 BitPosition
/*0x46C*/             ULONG32      HighEntropyASLREnabled : 1;                   // 25 BitPosition
/*0x46C*/             ULONG32      ForceStackCheck : 1;                          // 26 BitPosition
/*0x46C*/             ULONG32      ProcessDeepFrozen : 1;                        // 27 BitPosition
/*0x46C*/             ULONG32      ProcessDeepFreezeRequest : 1;                 // 28 BitPosition
/*0x46C*/             ULONG32      ProcessDeepFreezeInProgress : 1;              // 29 BitPosition
/*0x46C*/             ULONG32      DisallowWin32kSystemCalls : 1;                // 30 BitPosition
/*0x46C*/             ULONG32      SpareBits : 1;                                // 31 BitPosition
                  };
              };
              union                                                              // 2 elements, 0x4 bytes (sizeof)
              {
/*0x470*/         ULONG32      Flags;
                  struct                                                         // 29 elements, 0x4 bytes (sizeof)
                  {
/*0x470*/             ULONG32      CreateReported : 1;                           // 0 BitPosition
/*0x470*/             ULONG32      NoDebugInherit : 1;                           // 1 BitPosition
/*0x470*/             ULONG32      ProcessExiting : 1;                           // 2 BitPosition
/*0x470*/             ULONG32      ProcessDelete : 1;                            // 3 BitPosition
/*0x470*/             ULONG32      Wow64SplitPages : 1;                          // 4 BitPosition
/*0x470*/             ULONG32      VmDeleted : 1;                                // 5 BitPosition
/*0x470*/             ULONG32      OutswapEnabled : 1;                           // 6 BitPosition
/*0x470*/             ULONG32      Outswapped : 1;                               // 7 BitPosition
/*0x470*/             ULONG32      ForkFailed : 1;                               // 8 BitPosition
/*0x470*/             ULONG32      Wow64VaSpace4Gb : 1;                          // 9 BitPosition
/*0x470*/             ULONG32      AddressSpaceInitialized : 2;                  // 10 BitPosition
/*0x470*/             ULONG32      SetTimerResolution : 1;                       // 12 BitPosition
/*0x470*/             ULONG32      BreakOnTermination : 1;                       // 13 BitPosition
/*0x470*/             ULONG32      DeprioritizeViews : 1;                        // 14 BitPosition
/*0x470*/             ULONG32      WriteWatch : 1;                               // 15 BitPosition
/*0x470*/             ULONG32      ProcessInSession : 1;                         // 16 BitPosition
/*0x470*/             ULONG32      OverrideAddressSpace : 1;                     // 17 BitPosition
/*0x470*/             ULONG32      HasAddressSpace : 1;                          // 18 BitPosition
/*0x470*/             ULONG32      LaunchPrefetched : 1;                         // 19 BitPosition
/*0x470*/             ULONG32      InjectInpageErrors : 1;                       // 20 BitPosition
/*0x470*/             ULONG32      VmTopDown : 1;                                // 21 BitPosition
/*0x470*/             ULONG32      ImageNotifyDone : 1;                          // 22 BitPosition
/*0x470*/             ULONG32      PdeUpdateNeeded : 1;                          // 23 BitPosition
/*0x470*/             ULONG32      VdmAllowed : 1;                               // 24 BitPosition
/*0x470*/             ULONG32      CrossSessionCreate : 1;                       // 25 BitPosition
/*0x470*/             ULONG32      ProcessInserted : 1;                          // 26 BitPosition
/*0x470*/             ULONG32      DefaultIoPriority : 3;                        // 27 BitPosition
/*0x470*/             ULONG32      ProcessSelfDelete : 1;                        // 30 BitPosition
/*0x470*/             ULONG32      SetTimerResolutionLink : 1;                   // 31 BitPosition
                  };
              };
/*0x474*/     LONG32       ExitStatus;
/*0x478*/     struct _MM_AVL_TABLE VadRoot;                                      // 6 elements, 0x30 bytes (sizeof)
/*0x4A8*/     UINT64       VadPhysicalPages;
/*0x4B0*/     UINT64       VadPhysicalPagesLimit;
/*0x4B8*/     struct _ALPC_PROCESS_CONTEXT AlpcContext;                          // 3 elements, 0x20 bytes (sizeof)
/*0x4D8*/     struct _LIST_ENTRY TimerResolutionLink;                            // 2 elements, 0x10 bytes (sizeof)
/*0x4E8*/     struct _PO_DIAG_STACK_RECORD* TimerResolutionStackRecord;
/*0x4F0*/     ULONG32      RequestedTimerResolution;
/*0x4F4*/     ULONG32      SmallestTimerResolution;
/*0x4F8*/     union _LARGE_INTEGER ExitTime;                                     // 4 elements, 0x8 bytes (sizeof)
/*0x500*/     struct _INVERTED_FUNCTION_TABLE* InvertedFunctionTable;
/*0x508*/     struct _EX_PUSH_LOCK InvertedFunctionTableLock;                    // 7 elements, 0x8 bytes (sizeof)
/*0x510*/     ULONG32      ActiveThreadsHighWatermark;
/*0x514*/     ULONG32      LargePrivateVadCount;
/*0x518*/     VOID*        WnfContext;
/*0x520*/     enum _SE_SIGNING_LEVEL SignatureLevel;
/*0x524*/     ULONG32      KeepAliveCounter;
/*0x528*/     struct _PROCESS_DISK_COUNTERS* DiskCounters;
          }EPROCESS, *PEPROCESS;

typedef struct _EPROCESS_QUOTA_BLOCK // 0 elements, 0x0 bytes (sizeof)
{
}EPROCESS_QUOTA_BLOCK, *PEPROCESS_QUOTA_BLOCK;

          typedef struct _ETHREAD                                              // 92 elements, 0x4A8 bytes (sizeof)
          {
/*0x000*/     struct _KTHREAD Tcb;                                             // 144 elements, 0x340 bytes (sizeof)
/*0x340*/     union _LARGE_INTEGER CreateTime;                                 // 4 elements, 0x8 bytes (sizeof)
              union                                                            // 2 elements, 0x10 bytes (sizeof)
              {
/*0x348*/         union _LARGE_INTEGER ExitTime;                               // 4 elements, 0x8 bytes (sizeof)
/*0x348*/         struct _LIST_ENTRY KeyedWaitChain;                           // 2 elements, 0x10 bytes (sizeof)
              };
/*0x358*/     VOID*        ChargeOnlySession;
              union                                                            // 2 elements, 0x10 bytes (sizeof)
              {
/*0x360*/         struct _LIST_ENTRY PostBlockList;                            // 2 elements, 0x10 bytes (sizeof)
                  struct                                                       // 2 elements, 0x10 bytes (sizeof)
                  {
/*0x360*/             VOID*        ForwardLinkShadow;
/*0x368*/             VOID*        StartAddress;
                  };
              };
              union                                                            // 3 elements, 0x8 bytes (sizeof)
              {
/*0x370*/         struct _TERMINATION_PORT* TerminationPort;
/*0x370*/         struct _ETHREAD* ReaperLink;
/*0x370*/         VOID*        KeyedWaitValue;
              };
/*0x378*/     UINT64       ActiveTimerListLock;
/*0x380*/     struct _LIST_ENTRY ActiveTimerListHead;                          // 2 elements, 0x10 bytes (sizeof)
/*0x390*/     struct _CLIENT_ID Cid;                                           // 2 elements, 0x10 bytes (sizeof)
              union                                                            // 2 elements, 0x20 bytes (sizeof)
              {
/*0x3A0*/         struct _KSEMAPHORE KeyedWaitSemaphore;                       // 2 elements, 0x20 bytes (sizeof)
/*0x3A0*/         struct _KSEMAPHORE AlpcWaitSemaphore;                        // 2 elements, 0x20 bytes (sizeof)
              };
/*0x3C0*/     union _PS_CLIENT_SECURITY_CONTEXT ClientSecurity;                // 4 elements, 0x8 bytes (sizeof)
/*0x3C8*/     struct _LIST_ENTRY IrpList;                                      // 2 elements, 0x10 bytes (sizeof)
/*0x3D8*/     UINT64       TopLevelIrp;
/*0x3E0*/     struct _DEVICE_OBJECT* DeviceToVerify;
/*0x3E8*/     VOID*        SparePointer;
/*0x3F0*/     VOID*        Win32StartAddress;
/*0x3F8*/     VOID*        LegacyPowerObject;
/*0x400*/     struct _LIST_ENTRY ThreadListEntry;                              // 2 elements, 0x10 bytes (sizeof)
/*0x410*/     struct _EX_RUNDOWN_REF RundownProtect;                           // 2 elements, 0x8 bytes (sizeof)
/*0x418*/     struct _EX_PUSH_LOCK ThreadLock;                                 // 7 elements, 0x8 bytes (sizeof)
/*0x420*/     ULONG32      ReadClusterSize;
/*0x424*/     LONG32       MmLockOrdering;
/*0x428*/     LONG32       CmLockOrdering;
              union                                                            // 2 elements, 0x4 bytes (sizeof)
              {
/*0x42C*/         ULONG32      CrossThreadFlags;
                  struct                                                       // 14 elements, 0x4 bytes (sizeof)
                  {
/*0x42C*/             ULONG32      Terminated : 1;                             // 0 BitPosition
/*0x42C*/             ULONG32      ThreadInserted : 1;                         // 1 BitPosition
/*0x42C*/             ULONG32      HideFromDebugger : 1;                       // 2 BitPosition
/*0x42C*/             ULONG32      ActiveImpersonationInfo : 1;                // 3 BitPosition
/*0x42C*/             ULONG32      HardErrorsAreDisabled : 1;                  // 4 BitPosition
/*0x42C*/             ULONG32      BreakOnTermination : 1;                     // 5 BitPosition
/*0x42C*/             ULONG32      SkipCreationMsg : 1;                        // 6 BitPosition
/*0x42C*/             ULONG32      SkipTerminationMsg : 1;                     // 7 BitPosition
/*0x42C*/             ULONG32      CopyTokenOnOpen : 1;                        // 8 BitPosition
/*0x42C*/             ULONG32      ThreadIoPriority : 3;                       // 9 BitPosition
/*0x42C*/             ULONG32      ThreadPagePriority : 3;                     // 12 BitPosition
/*0x42C*/             ULONG32      RundownFail : 1;                            // 15 BitPosition
/*0x42C*/             ULONG32      UmsForceQueueTermination : 1;               // 16 BitPosition
/*0x42C*/             ULONG32      ReservedCrossThreadFlags : 15;              // 17 BitPosition
                  };
              };
              union                                                            // 2 elements, 0x4 bytes (sizeof)
              {
/*0x430*/         ULONG32      SameThreadPassiveFlags;
                  struct                                                       // 5 elements, 0x4 bytes (sizeof)
                  {
/*0x430*/             ULONG32      ActiveExWorker : 1;                         // 0 BitPosition
/*0x430*/             ULONG32      MemoryMaker : 1;                            // 1 BitPosition
/*0x430*/             ULONG32      ClonedThread : 1;                           // 2 BitPosition
/*0x430*/             ULONG32      KeyedEventInUse : 1;                        // 3 BitPosition
/*0x430*/             ULONG32      SelfTerminate : 1;                          // 4 BitPosition
                  };
              };
              union                                                            // 2 elements, 0x4 bytes (sizeof)
              {
/*0x434*/         ULONG32      SameThreadApcFlags;
                  struct                                                       // 4 elements, 0x4 bytes (sizeof)
                  {
                      struct                                                   // 8 elements, 0x1 bytes (sizeof)
                      {
/*0x434*/                 UINT8        Spare : 1;                              // 0 BitPosition
/*0x434*/                 UINT8        StartAddressInvalid : 1;                // 1 BitPosition
/*0x434*/                 UINT8        EtwCalloutActive : 1;                   // 2 BitPosition
/*0x434*/                 UINT8        OwnsProcessWorkingSetExclusive : 1;     // 3 BitPosition
/*0x434*/                 UINT8        OwnsProcessWorkingSetShared : 1;        // 4 BitPosition
/*0x434*/                 UINT8        OwnsSystemCacheWorkingSetExclusive : 1; // 5 BitPosition
/*0x434*/                 UINT8        OwnsSystemCacheWorkingSetShared : 1;    // 6 BitPosition
/*0x434*/                 UINT8        OwnsSessionWorkingSetExclusive : 1;     // 7 BitPosition
                      };
                      struct                                                   // 8 elements, 0x1 bytes (sizeof)
                      {
/*0x435*/                 UINT8        OwnsSessionWorkingSetShared : 1;        // 0 BitPosition
/*0x435*/                 UINT8        OwnsProcessAddressSpaceExclusive : 1;   // 1 BitPosition
/*0x435*/                 UINT8        OwnsProcessAddressSpaceShared : 1;      // 2 BitPosition
/*0x435*/                 UINT8        SuppressSymbolLoad : 1;                 // 3 BitPosition
/*0x435*/                 UINT8        Prefetching : 1;                        // 4 BitPosition
/*0x435*/                 UINT8        OwnsVadExclusive : 1;                   // 5 BitPosition
/*0x435*/                 UINT8        OwnsChangeControlAreaExclusive : 1;     // 6 BitPosition
/*0x435*/                 UINT8        OwnsChangeControlAreaShared : 1;        // 7 BitPosition
                      };
                      struct                                                   // 6 elements, 0x1 bytes (sizeof)
                      {
/*0x436*/                 UINT8        OwnsPagedPoolWorkingSetExclusive : 1;   // 0 BitPosition
/*0x436*/                 UINT8        OwnsPagedPoolWorkingSetShared : 1;      // 1 BitPosition
/*0x436*/                 UINT8        OwnsSystemPtesWorkingSetExclusive : 1;  // 2 BitPosition
/*0x436*/                 UINT8        OwnsSystemPtesWorkingSetShared : 1;     // 3 BitPosition
/*0x436*/                 UINT8        TrimTrigger : 2;                        // 4 BitPosition
/*0x436*/                 UINT8        Spare2 : 2;                             // 6 BitPosition
                      };
/*0x437*/             UINT8        PriorityRegionActive;
                  };
              };
/*0x438*/     UINT8        CacheManagerActive;
/*0x439*/     UINT8        DisablePageFaultClustering;
/*0x43A*/     UINT8        ActiveFaultCount;
/*0x43B*/     UINT8        LockOrderState;
/*0x43C*/     UINT8        _PADDING0_[0x4];
/*0x440*/     UINT64       AlpcMessageId;
              union                                                            // 2 elements, 0x8 bytes (sizeof)
              {
/*0x448*/         VOID*        AlpcMessage;
/*0x448*/         ULONG32      AlpcReceiveAttributeSet;
              };
/*0x450*/     LONG32       ExitStatus;
/*0x454*/     UINT8        _PADDING1_[0x4];
/*0x458*/     struct _LIST_ENTRY AlpcWaitListEntry;                            // 2 elements, 0x10 bytes (sizeof)
/*0x468*/     ULONG32      CacheManagerCount;
/*0x46C*/     ULONG32      IoBoostCount;
/*0x470*/     UINT64       IrpListLock;
/*0x478*/     VOID*        ReservedForSynchTracking;
/*0x480*/     struct _SINGLE_LIST_ENTRY CmCallbackListHead;                    // 1 elements, 0x8 bytes (sizeof)
/*0x488*/     struct _GUID* ActivityId;
/*0x490*/     VOID*        WnfContext;
/*0x498*/     struct _SINGLE_LIST_ENTRY SeLearningModeListHead;                // 1 elements, 0x8 bytes (sizeof)
/*0x4A0*/     UINT64       RelativeTimerBias;
          }ETHREAD, *PETHREAD;

typedef struct _JOB_ACCESS_STATE // 0 elements, 0x0 bytes (sizeof)
{
}JOB_ACCESS_STATE, *PJOB_ACCESS_STATE;

typedef struct _JOB_CPU_RATE_CONTROL // 0 elements, 0x0 bytes (sizeof)
{
}JOB_CPU_RATE_CONTROL, *PJOB_CPU_RATE_CONTROL;

typedef struct _JOB_NOTIFICATION_LIMITS // 0 elements, 0x0 bytes (sizeof)
{
}JOB_NOTIFICATION_LIMITS, *PJOB_NOTIFICATION_LIMITS;

          typedef struct _JOBOBJECT_WAKE_FILTER // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      HighEdgeFilter;
/*0x004*/     ULONG32      LowEdgeFilter;
          }JOBOBJECT_WAKE_FILTER, *PJOBOBJECT_WAKE_FILTER;

          typedef struct _JOBOBJECT_WAKE_INFORMATION // 2 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       NotificationChannel;
/*0x008*/     UINT64       WakeCounters[4];
          }JOBOBJECT_WAKE_INFORMATION, *PJOBOBJECT_WAKE_INFORMATION;

         typedef union _PS_CLIENT_SECURITY_CONTEXT    // 4 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       ImpersonationData;
/*0x000*/     VOID*        ImpersonationToken;
              struct                                   // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       ImpersonationLevel : 2; // 0 BitPosition
/*0x000*/         UINT64       EffectiveOnly : 1;      // 2 BitPosition
              };
          }PS_CLIENT_SECURITY_CONTEXT, *PPS_CLIENT_SECURITY_CONTEXT;

typedef enum _JOBOBJECTINFOCLASS  // 32 elements, 0x4 bytes
{
    JobObjectBasicAccountingInformation         = 1 /*0x1*/,
    JobObjectBasicLimitInformation              = 2 /*0x2*/,
    JobObjectBasicProcessIdList                 = 3 /*0x3*/,
    JobObjectBasicUIRestrictions                = 4 /*0x4*/,
    JobObjectSecurityLimitInformation           = 5 /*0x5*/,
    JobObjectEndOfJobTimeInformation            = 6 /*0x6*/,
    JobObjectAssociateCompletionPortInformation = 7 /*0x7*/,
    JobObjectBasicAndIoAccountingInformation    = 8 /*0x8*/,
    JobObjectExtendedLimitInformation           = 9 /*0x9*/,
    JobObjectJobSetInformation                  = 10 /*0xA*/,
    JobObjectGroupInformation                   = 11 /*0xB*/,
    JobObjectNotificationLimitInformation       = 12 /*0xC*/,
    JobObjectLimitViolationInformation          = 13 /*0xD*/,
    JobObjectGroupInformationEx                 = 14 /*0xE*/,
    JobObjectCpuRateControlInformation          = 15 /*0xF*/,
    JobObjectCompletionFilter                   = 16 /*0x10*/,
    JobObjectCompletionCounter                  = 17 /*0x11*/,
    JobObjectFreezeInformation                  = 18 /*0x12*/,
    JobObjectExtendedAccountingInformation      = 19 /*0x13*/,
    JobObjectWakeInformation                    = 20 /*0x14*/,
    JobObjectIdleAwareInformation               = 21 /*0x15*/,
    JobObjectSchedulingRankBiasInformation      = 22 /*0x16*/,
    JobObjectTimerVirtualizationInformation     = 23 /*0x17*/,
    JobObjectCycleTimeNotification              = 24 /*0x18*/,
    JobObjectReserved1Information               = 18 /*0x12*/,
    JobObjectReserved2Information               = 19 /*0x13*/,
    JobObjectReserved3Information               = 20 /*0x14*/,
    JobObjectReserved4Information               = 21 /*0x15*/,
    JobObjectReserved5Information               = 22 /*0x16*/,
    JobObjectReserved6Information               = 23 /*0x17*/,
    JobObjectReserved7Information               = 24 /*0x18*/,
    MaxJobObjectInfoClass                       = 25 /*0x19*/
}JOBOBJECTINFOCLASS, *PJOBOBJECTINFOCLASS;

