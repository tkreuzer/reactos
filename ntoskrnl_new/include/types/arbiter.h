          typedef struct _ARBITER_ADD_RESERVED_PARAMETERS // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _DEVICE_OBJECT* ReserveDevice;
          }ARBITER_ADD_RESERVED_PARAMETERS, *PARBITER_ADD_RESERVED_PARAMETERS;

          typedef struct _ARBITER_ALLOCATION_STATE             // 12 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     UINT64       Start;
/*0x008*/     UINT64       End;
/*0x010*/     UINT64       CurrentMinimum;
/*0x018*/     UINT64       CurrentMaximum;
/*0x020*/     struct _ARBITER_LIST_ENTRY* Entry;
/*0x028*/     struct _ARBITER_ALTERNATIVE* CurrentAlternative;
/*0x030*/     ULONG32      AlternativeCount;
/*0x034*/     UINT8        _PADDING0_[0x4];
/*0x038*/     struct _ARBITER_ALTERNATIVE* Alternatives;
/*0x040*/     UINT16       Flags;
/*0x042*/     UINT8        RangeAttributes;
/*0x043*/     UINT8        RangeAvailableAttributes;
/*0x044*/     UINT8        _PADDING1_[0x4];
/*0x048*/     UINT64       WorkSpace;
          }ARBITER_ALLOCATION_STATE, *PARBITER_ALLOCATION_STATE;

          typedef struct _ARBITER_ALTERNATIVE             // 8 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     UINT64       Minimum;
/*0x008*/     UINT64       Maximum;
/*0x010*/     UINT64       Length;
/*0x018*/     UINT64       Alignment;
/*0x020*/     LONG32       Priority;
/*0x024*/     ULONG32      Flags;
/*0x028*/     struct _IO_RESOURCE_DESCRIPTOR* Descriptor;
/*0x030*/     ULONG32      Reserved[3];
/*0x03C*/     UINT8        _PADDING0_[0x4];
          }ARBITER_ALTERNATIVE, *PARBITER_ALTERNATIVE;

          typedef struct _ARBITER_BOOT_ALLOCATION_PARAMETERS // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY* ArbitrationList;
          }ARBITER_BOOT_ALLOCATION_PARAMETERS, *PARBITER_BOOT_ALLOCATION_PARAMETERS;

          typedef struct _ARBITER_CONFLICT_INFO    // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _DEVICE_OBJECT* OwningObject;
/*0x008*/     UINT64       Start;
/*0x010*/     UINT64       End;
          }ARBITER_CONFLICT_INFO, *PARBITER_CONFLICT_INFO;

          typedef struct _ARBITER_INSTANCE                                                                       // 43 elements, 0x698 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _KEVENT* MutexEvent;
/*0x010*/     UINT16*      Name;
/*0x018*/     UINT16*      OrderingName;
/*0x020*/     INT32        ResourceType;
/*0x024*/     UINT8        _PADDING1_[0x4];
/*0x028*/     struct _RTL_RANGE_LIST* Allocation;
/*0x030*/     struct _RTL_RANGE_LIST* PossibleAllocation;
/*0x038*/     struct _ARBITER_ORDERING_LIST OrderingList;                                                        // 3 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _ARBITER_ORDERING_LIST ReservedList;                                                        // 3 elements, 0x10 bytes (sizeof)
/*0x058*/     LONG32       ReferenceCount;
/*0x05C*/     UINT8        _PADDING2_[0x4];
/*0x060*/     struct _ARBITER_INTERFACE* Interface;
/*0x068*/     ULONG32      AllocationStackMaxSize;
/*0x06C*/     UINT8        _PADDING3_[0x4];
/*0x070*/     struct _ARBITER_ALLOCATION_STATE* AllocationStack;
/*0x078*/     FUNCT_0064_25F5_UnpackRequirement* UnpackRequirement;
/*0x080*/     FUNCT_0064_25FC_PackResource* PackResource;
/*0x088*/     FUNCT_0064_2601_UnpackResource* UnpackResource;
/*0x090*/     FUNCT_0064_2606_ScoreRequirement* ScoreRequirement;
/*0x098*/     FUNCT_0064_2609_TestAllocation* TestAllocation;
/*0x0A0*/     FUNCT_0064_260F_RetestAllocation* RetestAllocation;
/*0x0A8*/     FUNCT_0064_2614_CommitAllocation_RollbackAllocation* CommitAllocation;
/*0x0B0*/     FUNCT_0064_2614_CommitAllocation_RollbackAllocation* RollbackAllocation;
/*0x0B8*/     FUNCT_0064_2617_BootAllocation* BootAllocation;
/*0x0C0*/     FUNCT_0064_261C_QueryArbitrate* QueryArbitrate;
/*0x0C8*/     FUNCT_0064_2621_QueryConflict* QueryConflict;
/*0x0D0*/     FUNCT_0064_2626_AddReserved* AddReserved;
/*0x0D8*/     FUNCT_0064_262B_StartArbiter* StartArbiter;
/*0x0E0*/     FUNCT_0064_262F_PreprocessEntry_AllocateEntry* PreprocessEntry;
/*0x0E8*/     FUNCT_0064_262F_PreprocessEntry_AllocateEntry* AllocateEntry;
/*0x0F0*/     FUNCT_006E_2633_GetNextAllocationRange_FindSuitableRange_OverrideConflict* GetNextAllocationRange;
/*0x0F8*/     FUNCT_006E_2633_GetNextAllocationRange_FindSuitableRange_OverrideConflict* FindSuitableRange;
/*0x100*/     FUNCT_00AE_2635_AddAllocation_BacktrackAllocation* AddAllocation;
/*0x108*/     FUNCT_00AE_2635_AddAllocation_BacktrackAllocation* BacktrackAllocation;
/*0x110*/     FUNCT_006E_2633_GetNextAllocationRange_FindSuitableRange_OverrideConflict* OverrideConflict;
/*0x118*/     FUNCT_0064_2637_InitializeRangeList* InitializeRangeList;
/*0x120*/     UINT8        TransactionInProgress;
/*0x121*/     UINT8        _PADDING4_[0x7];
/*0x128*/     struct _KEVENT* TransactionEvent;
/*0x130*/     VOID*        Extension;
/*0x138*/     struct _DEVICE_OBJECT* BusDeviceObject;
/*0x140*/     VOID*        ConflictCallbackContext;
/*0x148*/     FUNCT_006E_263D_ConflictCallback* ConflictCallback;
/*0x150*/     WCHAR        PdoDescriptionString[336];
/*0x3F0*/     CHAR         PdoSymbolicNameString[672];
/*0x690*/     WCHAR        PdoAddressString[1];
/*0x692*/     UINT8        _PADDING5_[0x6];
          }ARBITER_INSTANCE, *PARBITER_INSTANCE;

          typedef struct _ARBITER_INTERFACE                                                                                                                                                                                                            // 7 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     UINT16       Size;
/*0x002*/     UINT16       Version;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        Context;
/*0x010*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* InterfaceReference;
/*0x018*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* InterfaceDereference;
/*0x020*/     FUNCT_0064_2593_ArbiterHandler* ArbiterHandler;
/*0x028*/     ULONG32      Flags;
/*0x02C*/     UINT8        _PADDING1_[0x4];
          }ARBITER_INTERFACE, *PARBITER_INTERFACE;

          typedef struct _ARBITER_LIST_ENTRY                       // 13 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY ListEntry;                        // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     ULONG32      AlternativeCount;
/*0x014*/     UINT8        _PADDING0_[0x4];
/*0x018*/     struct _IO_RESOURCE_DESCRIPTOR* Alternatives;
/*0x020*/     struct _DEVICE_OBJECT* PhysicalDeviceObject;
/*0x028*/     enum _ARBITER_REQUEST_SOURCE RequestSource;
/*0x02C*/     ULONG32      Flags;
/*0x030*/     INT64        WorkSpace;
/*0x038*/     enum _INTERFACE_TYPE InterfaceType;
/*0x03C*/     ULONG32      SlotNumber;
/*0x040*/     ULONG32      BusNumber;
/*0x044*/     UINT8        _PADDING1_[0x4];
/*0x048*/     struct _CM_PARTIAL_RESOURCE_DESCRIPTOR* Assignment;
/*0x050*/     struct _IO_RESOURCE_DESCRIPTOR* SelectedAlternative;
/*0x058*/     enum _ARBITER_RESULT Result;
/*0x05C*/     UINT8        _PADDING2_[0x4];
          }ARBITER_LIST_ENTRY, *PARBITER_LIST_ENTRY;

          typedef struct _ARBITER_ORDERING // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Start;
/*0x008*/     UINT64       End;
          }ARBITER_ORDERING, *PARBITER_ORDERING;

          typedef struct _ARBITER_ORDERING_LIST    // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Count;
/*0x002*/     UINT16       Maximum;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _ARBITER_ORDERING* Orderings;
          }ARBITER_ORDERING_LIST, *PARBITER_ORDERING_LIST;

          typedef struct _ARBITER_PARAMETERS                                                    // 1 elements, 0x20 bytes (sizeof)
          {
              union                                                                             // 7 elements, 0x20 bytes (sizeof)
              {
/*0x000*/         struct _ARBITER_TEST_ALLOCATION_PARAMETERS TestAllocation;                    // 3 elements, 0x18 bytes (sizeof)
/*0x000*/         struct _ARBITER_RETEST_ALLOCATION_PARAMETERS RetestAllocation;                // 3 elements, 0x18 bytes (sizeof)
/*0x000*/         struct _ARBITER_BOOT_ALLOCATION_PARAMETERS BootAllocation;                    // 1 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS QueryAllocatedResources; // 1 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _ARBITER_QUERY_CONFLICT_PARAMETERS QueryConflict;                      // 4 elements, 0x20 bytes (sizeof)
/*0x000*/         struct _ARBITER_QUERY_ARBITRATE_PARAMETERS QueryArbitrate;                    // 1 elements, 0x8 bytes (sizeof)
/*0x000*/         struct _ARBITER_ADD_RESERVED_PARAMETERS AddReserved;                          // 1 elements, 0x8 bytes (sizeof)
              }Parameters;
          }ARBITER_PARAMETERS, *PARBITER_PARAMETERS;

          typedef struct _ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _CM_PARTIAL_RESOURCE_LIST** AllocatedResources;
          }ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS, *PARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS;

          typedef struct _ARBITER_QUERY_ARBITRATE_PARAMETERS // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY* ArbitrationList;
          }ARBITER_QUERY_ARBITRATE_PARAMETERS, *PARBITER_QUERY_ARBITRATE_PARAMETERS;

          typedef struct _ARBITER_QUERY_CONFLICT_PARAMETERS        // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _DEVICE_OBJECT* PhysicalDeviceObject;
/*0x008*/     struct _IO_RESOURCE_DESCRIPTOR* ConflictingResource;
/*0x010*/     ULONG32*     ConflictCount;
/*0x018*/     struct _ARBITER_CONFLICT_INFO** Conflicts;
          }ARBITER_QUERY_CONFLICT_PARAMETERS, *PARBITER_QUERY_CONFLICT_PARAMETERS;

          typedef struct _ARBITER_RETEST_ALLOCATION_PARAMETERS      // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY* ArbitrationList;
/*0x008*/     ULONG32      AllocateFromCount;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     struct _CM_PARTIAL_RESOURCE_DESCRIPTOR* AllocateFrom;
          }ARBITER_RETEST_ALLOCATION_PARAMETERS, *PARBITER_RETEST_ALLOCATION_PARAMETERS;

          typedef struct _ARBITER_TEST_ALLOCATION_PARAMETERS        // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY* ArbitrationList;
/*0x008*/     ULONG32      AllocateFromCount;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     struct _CM_PARTIAL_RESOURCE_DESCRIPTOR* AllocateFrom;
          }ARBITER_TEST_ALLOCATION_PARAMETERS, *PARBITER_TEST_ALLOCATION_PARAMETERS;

typedef enum _ARBITER_ACTION  // 10 elements, 0x4 bytes
{
    ArbiterActionTestAllocation          = 0 /*0x0*/,
    ArbiterActionRetestAllocation        = 1 /*0x1*/,
    ArbiterActionCommitAllocation        = 2 /*0x2*/,
    ArbiterActionRollbackAllocation      = 3 /*0x3*/,
    ArbiterActionQueryAllocatedResources = 4 /*0x4*/,
    ArbiterActionWriteReservedResources  = 5 /*0x5*/,
    ArbiterActionQueryConflict           = 6 /*0x6*/,
    ArbiterActionQueryArbitrate          = 7 /*0x7*/,
    ArbiterActionAddReserved             = 8 /*0x8*/,
    ArbiterActionBootAllocation          = 9 /*0x9*/
}ARBITER_ACTION, *PARBITER_ACTION;

typedef enum _ARBITER_REQUEST_SOURCE  // 6 elements, 0x4 bytes
{
    ArbiterRequestUndefined      = -1 /*0xFF*/,
    ArbiterRequestLegacyReported = 0 /*0x0*/,
    ArbiterRequestHalReported    = 1 /*0x1*/,
    ArbiterRequestLegacyAssigned = 2 /*0x2*/,
    ArbiterRequestPnpDetected    = 3 /*0x3*/,
    ArbiterRequestPnpEnumerated  = 4 /*0x4*/
}ARBITER_REQUEST_SOURCE, *PARBITER_REQUEST_SOURCE;

typedef enum _ARBITER_RESULT  // 4 elements, 0x4 bytes
{
    ArbiterResultUndefined        = -1 /*0xFF*/,
    ArbiterResultSuccess          = 0 /*0x0*/,
    ArbiterResultExternalConflict = 1 /*0x1*/,
    ArbiterResultNullRequest      = 2 /*0x2*/
}ARBITER_RESULT, *PARBITER_RESULT;

