typedef struct _PCW_BUFFER // 0 elements, 0x0 bytes (sizeof)
{
}PCW_BUFFER, *PPCW_BUFFER;

          typedef union _PCW_CALLBACK_INFORMATION              // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _PCW_COUNTER_INFORMATION AddCounter;      // 2 elements, 0x10 bytes (sizeof)
/*0x000*/     struct _PCW_COUNTER_INFORMATION RemoveCounter;   // 2 elements, 0x10 bytes (sizeof)
/*0x000*/     struct _PCW_MASK_INFORMATION EnumerateInstances; // 6 elements, 0x28 bytes (sizeof)
/*0x000*/     struct _PCW_MASK_INFORMATION CollectData;        // 6 elements, 0x28 bytes (sizeof)
          }PCW_CALLBACK_INFORMATION, *PPCW_CALLBACK_INFORMATION;

          typedef struct _PCW_COUNTER_DESCRIPTOR // 4 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT16       Id;
/*0x002*/     UINT16       StructIndex;
/*0x004*/     UINT16       Offset;
/*0x006*/     UINT16       Size;
          }PCW_COUNTER_DESCRIPTOR, *PPCW_COUNTER_DESCRIPTOR;

          typedef struct _PCW_COUNTER_INFORMATION   // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       CounterMask;
/*0x008*/     struct _UNICODE_STRING* InstanceMask;
          }PCW_COUNTER_INFORMATION, *PPCW_COUNTER_INFORMATION;

          typedef struct _PCW_DATA          // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        Data;
/*0x008*/     ULONG32      Size;
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }PCW_DATA, *PPCW_DATA;

typedef struct _PCW_INSTANCE // 0 elements, 0x0 bytes (sizeof)
{
}PCW_INSTANCE, *PPCW_INSTANCE;

          typedef struct _PCW_MASK_INFORMATION      // 6 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT64       CounterMask;
/*0x008*/     struct _UNICODE_STRING* InstanceMask;
/*0x010*/     ULONG32      InstanceId;
/*0x014*/     UINT8        CollectMultiple;
/*0x015*/     UINT8        _PADDING0_[0x3];
/*0x018*/     struct _PCW_BUFFER* Buffer;
/*0x020*/     struct _KEVENT* CancelEvent;
          }PCW_MASK_INFORMATION, *PPCW_MASK_INFORMATION;

          typedef struct _PCW_PROCESSOR_INFO       // 26 elements, 0xB0 bytes (sizeof)
          {
/*0x000*/     UINT64       IdleTime;
/*0x008*/     UINT64       AvailableTime;
/*0x010*/     UINT64       UserTime;
/*0x018*/     UINT64       KernelTime;
/*0x020*/     ULONG32      Interrupts;
/*0x024*/     UINT8        _PADDING0_[0x4];
/*0x028*/     UINT64       DpcTime;
/*0x030*/     UINT64       InterruptTime;
/*0x038*/     ULONG32      ClockInterrupts;
/*0x03C*/     ULONG32      DpcCount;
/*0x040*/     ULONG32      DpcRate;
/*0x044*/     UINT8        _PADDING1_[0x4];
/*0x048*/     UINT64       C1Time;
/*0x050*/     UINT64       C2Time;
/*0x058*/     UINT64       C3Time;
/*0x060*/     UINT64       C1Transitions;
/*0x068*/     UINT64       C2Transitions;
/*0x070*/     UINT64       C3Transitions;
/*0x078*/     ULONG32      ParkingStatus;
/*0x07C*/     ULONG32      CurrentFrequency;
/*0x080*/     ULONG32      PercentMaxFrequency;
/*0x084*/     ULONG32      StateFlags;
/*0x088*/     ULONG32      NominalThroughput;
/*0x08C*/     ULONG32      ActiveThroughput;
/*0x090*/     UINT64       ScaledThroughput;
/*0x098*/     UINT64       ScaledKernelThroughput;
/*0x0A0*/     UINT64       AverageIdleTime;
/*0x0A8*/     UINT64       IdleBreakEvents;
          }PCW_PROCESSOR_INFO, *PPCW_PROCESSOR_INFO;

typedef struct _PCW_REGISTRATION // 0 elements, 0x0 bytes (sizeof)
{
}PCW_REGISTRATION, *PPCW_REGISTRATION;

          typedef struct _PCW_REGISTRATION_INFORMATION  // 6 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     ULONG32      Version;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _UNICODE_STRING* Name;
/*0x010*/     ULONG32      CounterCount;
/*0x014*/     UINT8        _PADDING1_[0x4];
/*0x018*/     struct _PCW_COUNTER_DESCRIPTOR* Counters;
/*0x020*/     FUNCT_0064_15CD_Callback* Callback;
/*0x028*/     VOID*        CallbackContext;
          }PCW_REGISTRATION_INFORMATION, *PPCW_REGISTRATION_INFORMATION;

