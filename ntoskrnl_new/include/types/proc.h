
          typedef struct _PROC_FEEDBACK                          // 10 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     struct _PROC_FEEDBACK_COUNTER* FrequencyCounter;
/*0x008*/     struct _PROC_FEEDBACK_COUNTER* PerformanceCounter;
/*0x010*/     INT64        PerformanceScaledTime;
/*0x018*/     INT64        PerformanceScaledKernelTime;
/*0x020*/     INT64        UnaccountedTime;
/*0x028*/     UINT64       LastUpdateTime;
/*0x030*/     UINT64       CyclesLast;
/*0x038*/     UINT64       CyclesActive;
/*0x040*/     ULONG32      UserTimeLast;
/*0x044*/     ULONG32      KernelTimeLast;
          }PROC_FEEDBACK, *PPROC_FEEDBACK;

          typedef struct _PROC_FEEDBACK_COUNTER                         // 9 elements, 0x30 bytes (sizeof)
          {
              union                                                     // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         FUNCT_00AE_080A_InstantaneousRead* InstantaneousRead;
/*0x000*/         FUNCT_00AE_080E_DifferentialRead* DifferentialRead;
              };
/*0x008*/     UINT64       LastActualCount;
/*0x010*/     UINT64       LastReferenceCount;
/*0x018*/     ULONG32      CachedValue;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     UINT8        Affinitized;
/*0x021*/     UINT8        Differential;
/*0x022*/     UINT8        DisableInterrupts;
/*0x023*/     UINT8        _PADDING1_[0x5];
/*0x028*/     UINT64       Context;
          }PROC_FEEDBACK_COUNTER, *PPROC_FEEDBACK_COUNTER;

          typedef struct _PROC_IDLE_ACCOUNTING             // 7 elements, 0x2C8 bytes (sizeof)
          {
/*0x000*/     ULONG32      StateCount;
/*0x004*/     ULONG32      TotalTransitions;
/*0x008*/     ULONG32      ResetCount;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     UINT64       AbortCount;
/*0x018*/     UINT64       StartTime;
/*0x020*/     UINT64       BucketLimits[16];
/*0x0A0*/     struct _PROC_IDLE_STATE_ACCOUNTING State[1];
          }PROC_IDLE_ACCOUNTING, *PPROC_IDLE_ACCOUNTING;

          typedef struct _PROC_IDLE_SNAP // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Time;
/*0x008*/     UINT64       Idle;
          }PROC_IDLE_SNAP, *PPROC_IDLE_SNAP;

          typedef struct _PROC_IDLE_STATE_ACCOUNTING              // 7 elements, 0x228 bytes (sizeof)
          {
/*0x000*/     UINT64       TotalTime;
/*0x008*/     ULONG32      IdleTransitions;
/*0x00C*/     ULONG32      FailedTransitions;
/*0x010*/     ULONG32      InvalidBucketIndex;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     UINT64       MinTime;
/*0x020*/     UINT64       MaxTime;
/*0x028*/     struct _PROC_IDLE_STATE_BUCKET IdleTimeBuckets[16];
          }PROC_IDLE_STATE_ACCOUNTING, *PPROC_IDLE_STATE_ACCOUNTING;

          typedef struct _PROC_IDLE_STATE_BUCKET // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT64       TotalTime;
/*0x008*/     UINT64       MinTime;
/*0x010*/     UINT64       MaxTime;
/*0x018*/     ULONG32      Count;
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }PROC_IDLE_STATE_BUCKET, *PPROC_IDLE_STATE_BUCKET;

          typedef struct _PROC_PERF_CONSTRAINT      // 8 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _KPRCB* Prcb;
/*0x008*/     UINT64       PerfContext;
/*0x010*/     ULONG32      PercentageCap;
/*0x014*/     ULONG32      ThermalCap;
/*0x018*/     ULONG32      TargetFrequency;
/*0x01C*/     ULONG32      AcumulatedFullFrequency;
/*0x020*/     ULONG32      AcumulatedZeroFrequency;
/*0x024*/     ULONG32      FrequencySensitivity;
          }PROC_PERF_CONSTRAINT, *PPROC_PERF_CONSTRAINT;

          typedef struct _PROC_PERF_DOMAIN                                         // 27 elements, 0xD8 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY Link;                                             // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _KPRCB* Master;
/*0x018*/     struct _KAFFINITY_EX Members;                                        // 4 elements, 0x48 bytes (sizeof)
/*0x060*/     FUNCT_00AE_0846_FeedbackLazyRead* FeedbackLazyRead;
/*0x068*/     FUNCT_00AE_084C_GetFFHThrottleState* GetFFHThrottleState;
/*0x070*/     FUNCT_00AE_084F_BoostPolicyHandler_StallRoutine* BoostPolicyHandler;
/*0x078*/     FUNCT_0009_0852_PerfSelectionHandler* PerfSelectionHandler;
/*0x080*/     FUNCT_00AE_085B_PerfHandler* PerfHandler;
/*0x088*/     struct _PROC_PERF_CONSTRAINT* Processors;
/*0x090*/     UINT64       PerfChangeTime;
/*0x098*/     ULONG32      ProcessorCount;
/*0x09C*/     ULONG32      PreviousFrequencyMhz;
/*0x0A0*/     ULONG32      CurrentFrequencyMhz;
/*0x0A4*/     ULONG32      PreviousFrequency;
/*0x0A8*/     ULONG32      CurrentFrequency;
/*0x0AC*/     ULONG32      CurrentPerfContext;
/*0x0B0*/     ULONG32      DesiredFrequency;
/*0x0B4*/     ULONG32      MaxFrequency;
/*0x0B8*/     ULONG32      MinPerfPercent;
/*0x0BC*/     ULONG32      MinThrottlePercent;
/*0x0C0*/     ULONG32      MaxPercent;
/*0x0C4*/     ULONG32      MinPercent;
/*0x0C8*/     ULONG32      ConstrainedMaxPercent;
/*0x0CC*/     ULONG32      ConstrainedMinPercent;
/*0x0D0*/     UINT8        Coordination;
/*0x0D1*/     UINT8        Force;
/*0x0D2*/     UINT8        _PADDING0_[0x2];
/*0x0D4*/     LONG32       PerfChangeIntervalCount;
          }PROC_PERF_DOMAIN, *PPROC_PERF_DOMAIN;

          typedef struct _PROC_PERF_HISTORY                   // 6 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     ULONG32      Slot;
/*0x008*/     ULONG32      UtilityTotal;
/*0x00C*/     ULONG32      AffinitizedUtilityTotal;
/*0x010*/     ULONG32      FrequencyTotal;
/*0x014*/     struct _PROC_PERF_HISTORY_ENTRY HistoryList[1];
/*0x01A*/     UINT8        _PADDING0_[0x2];
          }PROC_PERF_HISTORY, *PPROC_PERF_HISTORY;

          typedef struct _PROC_PERF_HISTORY_ENTRY // 4 elements, 0x6 bytes (sizeof)
          {
/*0x000*/     UINT16       Utility;
/*0x002*/     UINT16       AffinitizedUtility;
/*0x004*/     UINT8        Frequency;
/*0x005*/     UINT8        Reserved;
          }PROC_PERF_HISTORY_ENTRY, *PPROC_PERF_HISTORY_ENTRY;

          typedef struct _PROC_PERF_LOAD        // 2 elements, 0x2 bytes (sizeof)
          {
/*0x000*/     UINT8        BusyPercentage;
/*0x001*/     UINT8        FrequencyPercentage;
          }PROC_PERF_LOAD, *PPROC_PERF_LOAD;

          typedef struct _PROC_PERF_SNAP      // 7 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     UINT64       Time;
/*0x008*/     UINT64       LastTime;
/*0x010*/     UINT64       Active;
/*0x018*/     UINT64       LastActive;
/*0x020*/     UINT64       ScaledActive;
/*0x028*/     UINT64       CyclesActive;
/*0x030*/     UINT64       CyclesAffinitized;
          }PROC_PERF_SNAP, *PPROC_PERF_SNAP;

