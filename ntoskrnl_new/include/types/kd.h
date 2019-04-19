          typedef struct _X86_DBGKD_CONTROL_SET // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      TraceFlag;
/*0x004*/     ULONG32      Dr7;
/*0x008*/     ULONG32      CurrentSymbolStart;
/*0x00C*/     ULONG32      CurrentSymbolEnd;
          }X86_DBGKD_CONTROL_SET, *PX86_DBGKD_CONTROL_SET;

           typedef struct _AMD64_DBGKD_CONTROL_SET // 4 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      TraceFlag;
/*0x004*/     UINT64       Dr7;
/*0x00C*/     UINT64       CurrentSymbolStart;
/*0x014*/     UINT64       CurrentSymbolEnd;
          }AMD64_DBGKD_CONTROL_SET, *PAMD64_DBGKD_CONTROL_SET;

          typedef struct _ARM_DBGKD_CONTROL_SET // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      Continue;
/*0x004*/     ULONG32      CurrentSymbolStart;
/*0x008*/     ULONG32      CurrentSymbolEnd;
          }ARM_DBGKD_CONTROL_SET, *PARM_DBGKD_CONTROL_SET;

          typedef struct _ARMCE_DBGKD_CONTROL_SET // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      Continue;
/*0x004*/     ULONG32      CurrentSymbolStart;
/*0x008*/     ULONG32      CurrentSymbolEnd;
          }ARMCE_DBGKD_CONTROL_SET, *PARMCE_DBGKD_CONTROL_SET;

          typedef struct _IA64_DBGKD_CONTROL_SET // 3 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     ULONG32      Continue;
/*0x004*/     UINT64       CurrentSymbolStart;
/*0x00C*/     UINT64       CurrentSymbolEnd;
          }IA64_DBGKD_CONTROL_SET, *PIA64_DBGKD_CONTROL_SET;

          typedef struct _PPC_DBGKD_CONTROL_SET // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      Continue;
/*0x004*/     ULONG32      CurrentSymbolStart;
/*0x008*/     ULONG32      CurrentSymbolEnd;
          }PPC_DBGKD_CONTROL_SET, *PPPC_DBGKD_CONTROL_SET;


          typedef struct _DBGKD_ANY_CONTROL_SET                    // 7 elements, 0x1C bytes (sizeof)
          {
              union                                                // 7 elements, 0x1C bytes (sizeof)
              {
/*0x000*/         struct _X86_DBGKD_CONTROL_SET X86ControlSet;     // 4 elements, 0x10 bytes (sizeof)
/*0x000*/         ULONG32      AlphaControlSet;
/*0x000*/         struct _IA64_DBGKD_CONTROL_SET IA64ControlSet;   // 3 elements, 0x14 bytes (sizeof)
/*0x000*/         struct _AMD64_DBGKD_CONTROL_SET Amd64ControlSet; // 4 elements, 0x1C bytes (sizeof)
/*0x000*/         struct _ARM_DBGKD_CONTROL_SET ArmControlSet;     // 3 elements, 0xC bytes (sizeof)
/*0x000*/         struct _ARMCE_DBGKD_CONTROL_SET ArmCeControlSet; // 3 elements, 0xC bytes (sizeof)
/*0x000*/         struct _PPC_DBGKD_CONTROL_SET PpcControlSet;     // 3 elements, 0xC bytes (sizeof)
              };
          }DBGKD_ANY_CONTROL_SET, *PDBGKD_ANY_CONTROL_SET;

          typedef struct _DBGKD_BREAKPOINTEX // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      BreakPointCount;
/*0x004*/     LONG32       ContinueStatus;
          }DBGKD_BREAKPOINTEX, *PDBGKD_BREAKPOINTEX;

          typedef struct _DBGKD_CONTINUE   // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     LONG32       ContinueStatus;
          }DBGKD_CONTINUE, *PDBGKD_CONTINUE;

          typedef struct _DBGKD_CONTINUE2                      // 3 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     LONG32       ContinueStatus;
              union                                            // 2 elements, 0x1C bytes (sizeof)
              {
/*0x004*/         struct _AMD64_DBGKD_CONTROL_SET ControlSet;  // 4 elements, 0x1C bytes (sizeof)
/*0x004*/         struct _DBGKD_ANY_CONTROL_SET AnyControlSet; // 7 elements, 0x1C bytes (sizeof)
              };
          }DBGKD_CONTINUE2, *PDBGKD_CONTINUE2;

          typedef struct _DBGKD_FILL_MEMORY // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Address;
/*0x008*/     ULONG32      Length;
/*0x00C*/     UINT16       Flags;
/*0x00E*/     UINT16       PatternLength;
          }DBGKD_FILL_MEMORY, *PDBGKD_FILL_MEMORY;

          typedef struct _DBGKD_GET_CONTEXT // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      Unused;
          }DBGKD_GET_CONTEXT, *PDBGKD_GET_CONTEXT;

          typedef struct _DBGKD_GET_CONTEXT_EX // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      Offset;
/*0x004*/     ULONG32      ByteCount;
/*0x008*/     ULONG32      BytesCopied;
          }DBGKD_GET_CONTEXT_EX, *PDBGKD_GET_CONTEXT_EX;

          typedef struct _DBGKD_GET_INTERNAL_BREAKPOINT32 // 7 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      BreakpointAddress;
/*0x004*/     ULONG32      Flags;
/*0x008*/     ULONG32      Calls;
/*0x00C*/     ULONG32      MaxCallsPerPeriod;
/*0x010*/     ULONG32      MinInstructions;
/*0x014*/     ULONG32      MaxInstructions;
/*0x018*/     ULONG32      TotalInstructions;
          }DBGKD_GET_INTERNAL_BREAKPOINT32, *PDBGKD_GET_INTERNAL_BREAKPOINT32;

          typedef struct _DBGKD_GET_INTERNAL_BREAKPOINT64 // 7 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     UINT64       BreakpointAddress;
/*0x008*/     ULONG32      Flags;
/*0x00C*/     ULONG32      Calls;
/*0x010*/     ULONG32      MaxCallsPerPeriod;
/*0x014*/     ULONG32      MinInstructions;
/*0x018*/     ULONG32      MaxInstructions;
/*0x01C*/     ULONG32      TotalInstructions;
          }DBGKD_GET_INTERNAL_BREAKPOINT64, *PDBGKD_GET_INTERNAL_BREAKPOINT64;

          typedef struct _DBGKD_GET_SET_BUS_DATA // 5 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     ULONG32      BusDataType;
/*0x004*/     ULONG32      BusNumber;
/*0x008*/     ULONG32      SlotNumber;
/*0x00C*/     ULONG32      Offset;
/*0x010*/     ULONG32      Length;
          }DBGKD_GET_SET_BUS_DATA, *PDBGKD_GET_SET_BUS_DATA;

          typedef struct _DBGKD_GET_VERSION32        // 14 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT16       MajorVersion;
/*0x002*/     UINT16       MinorVersion;
/*0x004*/     UINT16       ProtocolVersion;
/*0x006*/     UINT16       Flags;
/*0x008*/     ULONG32      KernBase;
/*0x00C*/     ULONG32      PsLoadedModuleList;
/*0x010*/     UINT16       MachineType;
/*0x012*/     UINT16       ThCallbackStack;
/*0x014*/     UINT16       NextCallback;
/*0x016*/     UINT16       FramePointer;
/*0x018*/     ULONG32      KiCallUserMode;
/*0x01C*/     ULONG32      KeUserCallbackDispatcher;
/*0x020*/     ULONG32      BreakpointWithStatus;
/*0x024*/     ULONG32      DebuggerDataList;
          }DBGKD_GET_VERSION32, *PDBGKD_GET_VERSION32;

          typedef struct _DBGKD_GET_VERSION64  // 14 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT16       MajorVersion;
/*0x002*/     UINT16       MinorVersion;
/*0x004*/     UINT8        ProtocolVersion;
/*0x005*/     UINT8        KdSecondaryVersion;
/*0x006*/     UINT16       Flags;
/*0x008*/     UINT16       MachineType;
/*0x00A*/     UINT8        MaxPacketType;
/*0x00B*/     UINT8        MaxStateChange;
/*0x00C*/     UINT8        MaxManipulate;
/*0x00D*/     UINT8        Simulation;
/*0x00E*/     UINT16       Unused[1];
/*0x010*/     UINT64       KernBase;
/*0x018*/     UINT64       PsLoadedModuleList;
/*0x020*/     UINT64       DebuggerDataList;
          }DBGKD_GET_VERSION64, *PDBGKD_GET_VERSION64;

          typedef struct _DBGKD_LOAD_SYMBOLS32 // 6 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      PathNameLength;
/*0x004*/     ULONG32      BaseOfDll;
/*0x008*/     ULONG32      ProcessId;
/*0x00C*/     ULONG32      CheckSum;
/*0x010*/     ULONG32      SizeOfImage;
/*0x014*/     UINT8        UnloadSymbols;
/*0x015*/     UINT8        _PADDING0_[0x3];
          }DBGKD_LOAD_SYMBOLS32, *PDBGKD_LOAD_SYMBOLS32;

          typedef struct _DBGKD_LOAD_SYMBOLS64 // 6 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     ULONG32      PathNameLength;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT64       BaseOfDll;
/*0x010*/     UINT64       ProcessId;
/*0x018*/     ULONG32      CheckSum;
/*0x01C*/     ULONG32      SizeOfImage;
/*0x020*/     UINT8        UnloadSymbols;
/*0x021*/     UINT8        _PADDING1_[0x7];
          }DBGKD_LOAD_SYMBOLS64, *PDBGKD_LOAD_SYMBOLS64;

          typedef struct _DBGKD_MANIPULATE_STATE32                               // 5 elements, 0x34 bytes (sizeof)
          {
/*0x000*/     ULONG32      ApiNumber;
/*0x004*/     UINT16       ProcessorLevel;
/*0x006*/     UINT16       Processor;
/*0x008*/     LONG32       ReturnStatus;
              union                                                              // 22 elements, 0x28 bytes (sizeof)
              {
/*0x00C*/         struct _DBGKD_READ_MEMORY32 ReadMemory;                        // 3 elements, 0xC bytes (sizeof)
/*0x00C*/         struct _DBGKD_WRITE_MEMORY32 WriteMemory;                      // 3 elements, 0xC bytes (sizeof)
/*0x00C*/         struct _DBGKD_READ_MEMORY64 ReadMemory64;                      // 3 elements, 0x10 bytes (sizeof)
/*0x00C*/         struct _DBGKD_WRITE_MEMORY64 WriteMemory64;                    // 3 elements, 0x10 bytes (sizeof)
/*0x00C*/         struct _DBGKD_GET_CONTEXT GetContext;                          // 1 elements, 0x4 bytes (sizeof)
/*0x00C*/         struct _DBGKD_SET_CONTEXT SetContext;                          // 1 elements, 0x4 bytes (sizeof)
/*0x00C*/         struct _DBGKD_WRITE_BREAKPOINT32 WriteBreakPoint;              // 2 elements, 0x8 bytes (sizeof)
/*0x00C*/         struct _DBGKD_RESTORE_BREAKPOINT RestoreBreakPoint;            // 1 elements, 0x4 bytes (sizeof)
/*0x00C*/         struct _DBGKD_CONTINUE Continue;                               // 1 elements, 0x4 bytes (sizeof)
/*0x00C*/         struct _DBGKD_CONTINUE2 Continue2;                             // 3 elements, 0x20 bytes (sizeof)
/*0x00C*/         struct _DBGKD_READ_WRITE_IO32 ReadWriteIo;                     // 3 elements, 0xC bytes (sizeof)
/*0x00C*/         struct _DBGKD_READ_WRITE_IO_EXTENDED32 ReadWriteIoExtended;    // 6 elements, 0x18 bytes (sizeof)
/*0x00C*/         struct _DBGKD_QUERY_SPECIAL_CALLS QuerySpecialCalls;           // 1 elements, 0x4 bytes (sizeof)
/*0x00C*/         struct _DBGKD_SET_SPECIAL_CALL32 SetSpecialCall;               // 1 elements, 0x4 bytes (sizeof)
/*0x00C*/         struct _DBGKD_SET_INTERNAL_BREAKPOINT32 SetInternalBreakpoint; // 2 elements, 0x8 bytes (sizeof)
/*0x00C*/         struct _DBGKD_GET_INTERNAL_BREAKPOINT32 GetInternalBreakpoint; // 7 elements, 0x1C bytes (sizeof)
/*0x00C*/         struct _DBGKD_GET_VERSION32 GetVersion32;                      // 14 elements, 0x28 bytes (sizeof)
/*0x00C*/         struct _DBGKD_BREAKPOINTEX BreakPointEx;                       // 2 elements, 0x8 bytes (sizeof)
/*0x00C*/         struct _DBGKD_READ_WRITE_MSR ReadWriteMsr;                     // 3 elements, 0xC bytes (sizeof)
/*0x00C*/         struct _DBGKD_SEARCH_MEMORY SearchMemory;                      // 4 elements, 0x18 bytes (sizeof)
/*0x00C*/         struct _DBGKD_GET_CONTEXT_EX GetContextEx;                     // 3 elements, 0xC bytes (sizeof)
/*0x00C*/         struct _DBGKD_SET_CONTEXT_EX SetContextEx;                     // 4 elements, 0x10 bytes (sizeof)
              }u;
          }DBGKD_MANIPULATE_STATE32, *PDBGKD_MANIPULATE_STATE32;

          typedef struct _DBGKD_MANIPULATE_STATE64                               // 5 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     ULONG32      ApiNumber;
/*0x004*/     UINT16       ProcessorLevel;
/*0x006*/     UINT16       Processor;
/*0x008*/     LONG32       ReturnStatus;
/*0x00C*/     UINT8        _PADDING0_[0x4];
              union                                                              // 24 elements, 0x28 bytes (sizeof)
              {
/*0x010*/         struct _DBGKD_READ_MEMORY64 ReadMemory;                        // 3 elements, 0x10 bytes (sizeof)
/*0x010*/         struct _DBGKD_WRITE_MEMORY64 WriteMemory;                      // 3 elements, 0x10 bytes (sizeof)
/*0x010*/         struct _DBGKD_GET_CONTEXT GetContext;                          // 1 elements, 0x4 bytes (sizeof)
/*0x010*/         struct _DBGKD_SET_CONTEXT SetContext;                          // 1 elements, 0x4 bytes (sizeof)
/*0x010*/         struct _DBGKD_WRITE_BREAKPOINT64 WriteBreakPoint;              // 2 elements, 0x10 bytes (sizeof)
/*0x010*/         struct _DBGKD_RESTORE_BREAKPOINT RestoreBreakPoint;            // 1 elements, 0x4 bytes (sizeof)
/*0x010*/         struct _DBGKD_CONTINUE Continue;                               // 1 elements, 0x4 bytes (sizeof)
/*0x010*/         struct _DBGKD_CONTINUE2 Continue2;                             // 3 elements, 0x20 bytes (sizeof)
/*0x010*/         struct _DBGKD_READ_WRITE_IO64 ReadWriteIo;                     // 3 elements, 0x10 bytes (sizeof)
/*0x010*/         struct _DBGKD_READ_WRITE_IO_EXTENDED64 ReadWriteIoExtended;    // 6 elements, 0x20 bytes (sizeof)
/*0x010*/         struct _DBGKD_QUERY_SPECIAL_CALLS QuerySpecialCalls;           // 1 elements, 0x4 bytes (sizeof)
/*0x010*/         struct _DBGKD_SET_SPECIAL_CALL64 SetSpecialCall;               // 1 elements, 0x8 bytes (sizeof)
/*0x010*/         struct _DBGKD_SET_INTERNAL_BREAKPOINT64 SetInternalBreakpoint; // 2 elements, 0x10 bytes (sizeof)
/*0x010*/         struct _DBGKD_GET_INTERNAL_BREAKPOINT64 GetInternalBreakpoint; // 7 elements, 0x20 bytes (sizeof)
/*0x010*/         struct _DBGKD_GET_VERSION64 GetVersion64;                      // 14 elements, 0x28 bytes (sizeof)
/*0x010*/         struct _DBGKD_BREAKPOINTEX BreakPointEx;                       // 2 elements, 0x8 bytes (sizeof)
/*0x010*/         struct _DBGKD_READ_WRITE_MSR ReadWriteMsr;                     // 3 elements, 0xC bytes (sizeof)
/*0x010*/         struct _DBGKD_SEARCH_MEMORY SearchMemory;                      // 4 elements, 0x18 bytes (sizeof)
/*0x010*/         struct _DBGKD_GET_SET_BUS_DATA GetSetBusData;                  // 5 elements, 0x14 bytes (sizeof)
/*0x010*/         struct _DBGKD_FILL_MEMORY FillMemory;                          // 4 elements, 0x10 bytes (sizeof)
/*0x010*/         struct _DBGKD_QUERY_MEMORY QueryMemory;                        // 4 elements, 0x18 bytes (sizeof)
/*0x010*/         struct _DBGKD_SWITCH_PARTITION SwitchPartition;                // 1 elements, 0x4 bytes (sizeof)
/*0x010*/         struct _DBGKD_GET_CONTEXT_EX GetContextEx;                     // 3 elements, 0xC bytes (sizeof)
/*0x010*/         struct _DBGKD_SET_CONTEXT_EX SetContextEx;                     // 4 elements, 0x10 bytes (sizeof)
              }u;
          }DBGKD_MANIPULATE_STATE64, *PDBGKD_MANIPULATE_STATE64;

          typedef struct _DBGKD_QUERY_MEMORY // 4 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT64       Address;
/*0x008*/     UINT64       Reserved;
/*0x010*/     ULONG32      AddressSpace;
/*0x014*/     ULONG32      Flags;
          }DBGKD_QUERY_MEMORY, *PDBGKD_QUERY_MEMORY;

          typedef struct _DBGKD_QUERY_SPECIAL_CALLS // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      NumberOfSpecialCalls;
          }DBGKD_QUERY_SPECIAL_CALLS, *PDBGKD_QUERY_SPECIAL_CALLS;

          typedef struct _DBGKD_READ_MEMORY32 // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      TargetBaseAddress;
/*0x004*/     ULONG32      TransferCount;
/*0x008*/     ULONG32      ActualBytesRead;
          }DBGKD_READ_MEMORY32, *PDBGKD_READ_MEMORY32;

          typedef struct _DBGKD_READ_MEMORY64 // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       TargetBaseAddress;
/*0x008*/     ULONG32      TransferCount;
/*0x00C*/     ULONG32      ActualBytesRead;
          }DBGKD_READ_MEMORY64, *PDBGKD_READ_MEMORY64;

          typedef struct _DBGKD_READ_WRITE_IO_EXTENDED32 // 6 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     ULONG32      DataSize;
/*0x004*/     ULONG32      InterfaceType;
/*0x008*/     ULONG32      BusNumber;
/*0x00C*/     ULONG32      AddressSpace;
/*0x010*/     ULONG32      IoAddress;
/*0x014*/     ULONG32      DataValue;
          }DBGKD_READ_WRITE_IO_EXTENDED32, *PDBGKD_READ_WRITE_IO_EXTENDED32;

          typedef struct _DBGKD_READ_WRITE_IO_EXTENDED64 // 6 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     ULONG32      DataSize;
/*0x004*/     ULONG32      InterfaceType;
/*0x008*/     ULONG32      BusNumber;
/*0x00C*/     ULONG32      AddressSpace;
/*0x010*/     UINT64       IoAddress;
/*0x018*/     ULONG32      DataValue;
/*0x01C*/     UINT8        _PADDING0_[0x4];
          }DBGKD_READ_WRITE_IO_EXTENDED64, *PDBGKD_READ_WRITE_IO_EXTENDED64;

          typedef struct _DBGKD_READ_WRITE_IO32 // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      DataSize;
/*0x004*/     ULONG32      IoAddress;
/*0x008*/     ULONG32      DataValue;
          }DBGKD_READ_WRITE_IO32, *PDBGKD_READ_WRITE_IO32;

          typedef struct _DBGKD_READ_WRITE_IO64 // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       IoAddress;
/*0x008*/     ULONG32      DataSize;
/*0x00C*/     ULONG32      DataValue;
          }DBGKD_READ_WRITE_IO64, *PDBGKD_READ_WRITE_IO64;

          typedef struct _DBGKD_READ_WRITE_MSR // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      Msr;
/*0x004*/     ULONG32      DataValueLow;
/*0x008*/     ULONG32      DataValueHigh;
          }DBGKD_READ_WRITE_MSR, *PDBGKD_READ_WRITE_MSR;

          typedef struct _DBGKD_RESTORE_BREAKPOINT // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      BreakPointHandle;
          }DBGKD_RESTORE_BREAKPOINT, *PDBGKD_RESTORE_BREAKPOINT;

          typedef struct _DBGKD_SEARCH_MEMORY // 4 elements, 0x18 bytes (sizeof)
          {
              union                           // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       SearchAddress;
/*0x000*/         UINT64       FoundAddress;
              };
/*0x008*/     UINT64       SearchLength;
/*0x010*/     ULONG32      PatternLength;
/*0x014*/     UINT8        _PADDING0_[0x4];
          }DBGKD_SEARCH_MEMORY, *PDBGKD_SEARCH_MEMORY;

          typedef struct _DBGKD_SET_CONTEXT // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      ContextFlags;
          }DBGKD_SET_CONTEXT, *PDBGKD_SET_CONTEXT;

          typedef struct _DBGKD_SET_CONTEXT_EX // 4 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      ContextFlags;
/*0x004*/     ULONG32      Offset;
/*0x008*/     ULONG32      ByteCount;
/*0x00C*/     ULONG32      BytesCopied;
          }DBGKD_SET_CONTEXT_EX, *PDBGKD_SET_CONTEXT_EX;

          typedef struct _DBGKD_SET_INTERNAL_BREAKPOINT32 // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      BreakpointAddress;
/*0x004*/     ULONG32      Flags;
          }DBGKD_SET_INTERNAL_BREAKPOINT32, *PDBGKD_SET_INTERNAL_BREAKPOINT32;

          typedef struct _DBGKD_SET_INTERNAL_BREAKPOINT64 // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       BreakpointAddress;
/*0x008*/     ULONG32      Flags;
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }DBGKD_SET_INTERNAL_BREAKPOINT64, *PDBGKD_SET_INTERNAL_BREAKPOINT64;

          typedef struct _DBGKD_SET_SPECIAL_CALL32 // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      SpecialCall;
          }DBGKD_SET_SPECIAL_CALL32, *PDBGKD_SET_SPECIAL_CALL32;

          typedef struct _DBGKD_SET_SPECIAL_CALL64 // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       SpecialCall;
          }DBGKD_SET_SPECIAL_CALL64, *PDBGKD_SET_SPECIAL_CALL64;

          typedef struct _DBGKD_SWITCH_PARTITION // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      Partition;
          }DBGKD_SWITCH_PARTITION, *PDBGKD_SWITCH_PARTITION;

          typedef struct _DBGKD_WRITE_BREAKPOINT32 // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      BreakPointAddress;
/*0x004*/     ULONG32      BreakPointHandle;
          }DBGKD_WRITE_BREAKPOINT32, *PDBGKD_WRITE_BREAKPOINT32;

          typedef struct _DBGKD_WRITE_BREAKPOINT64 // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       BreakPointAddress;
/*0x008*/     ULONG32      BreakPointHandle;
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }DBGKD_WRITE_BREAKPOINT64, *PDBGKD_WRITE_BREAKPOINT64;

          typedef struct _DBGKD_WRITE_MEMORY32 // 3 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      TargetBaseAddress;
/*0x004*/     ULONG32      TransferCount;
/*0x008*/     ULONG32      ActualBytesWritten;
          }DBGKD_WRITE_MEMORY32, *PDBGKD_WRITE_MEMORY32;

          typedef struct _DBGKD_WRITE_MEMORY64 // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       TargetBaseAddress;
/*0x008*/     ULONG32      TransferCount;
/*0x00C*/     ULONG32      ActualBytesWritten;
          }DBGKD_WRITE_MEMORY64, *PDBGKD_WRITE_MEMORY64;

          typedef struct _DBGKM_EXCEPTION32               // 2 elements, 0x54 bytes (sizeof)
          {
/*0x000*/     struct _EXCEPTION_RECORD32 ExceptionRecord; // 6 elements, 0x50 bytes (sizeof)
/*0x050*/     ULONG32      FirstChance;
          }DBGKM_EXCEPTION32, *PDBGKM_EXCEPTION32;

          typedef struct _DBGKM_EXCEPTION64               // 2 elements, 0xA0 bytes (sizeof)
          {
/*0x000*/     struct _EXCEPTION_RECORD64 ExceptionRecord; // 7 elements, 0x98 bytes (sizeof)
/*0x098*/     ULONG32      FirstChance;
/*0x09C*/     UINT8        _PADDING0_[0x4];
          }DBGKM_EXCEPTION64, *PDBGKM_EXCEPTION64;

