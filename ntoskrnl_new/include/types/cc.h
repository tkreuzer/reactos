          typedef struct _CACHE_DESCRIPTOR     // 5 elements, 0xC bytes (sizeof)
          {
/*0x000*/     UINT8        Level;
/*0x001*/     UINT8        Associativity;
/*0x002*/     UINT16       LineSize;
/*0x004*/     ULONG32      Size;
/*0x008*/     enum _PROCESSOR_CACHE_TYPE Type;
          }CACHE_DESCRIPTOR, *PCACHE_DESCRIPTOR;

          typedef struct _CACHE_MANAGER_CALLBACKS                                                                                                                                                                                                      // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     FUNCT_006E_198D_AcquireForLazyWrite_AcquireForReadAhead* AcquireForLazyWrite;
/*0x008*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* ReleaseFromLazyWrite;
/*0x010*/     FUNCT_006E_198D_AcquireForLazyWrite_AcquireForReadAhead* AcquireForReadAhead;
/*0x018*/     FUNCT_00AE_0744_Free_IdleExecute_IdleComplete_WorkerRoutine_InterfaceReference_InterfaceDereference_DeleteProcedure_DevicePowerRequired_DevicePowerNotRequired_Callback_ReleaseFromLazyWrite_ReleaseFromReadAhead* ReleaseFromReadAhead;
          }CACHE_MANAGER_CALLBACKS, *PCACHE_MANAGER_CALLBACKS;

          typedef struct _CACHE_UNINITIALIZE_EVENT    // 2 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     struct _CACHE_UNINITIALIZE_EVENT* Next;
/*0x008*/     struct _KEVENT Event;                   // 1 elements, 0x18 bytes (sizeof)
          }CACHE_UNINITIALIZE_EVENT, *PCACHE_UNINITIALIZE_EVENT;

          typedef struct _CACHED_CHILD_LIST              // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     ULONG32      Count;
/*0x004*/     UINT8        _PADDING0_[0x4];
              union                                      // 2 elements, 0x8 bytes (sizeof)
              {
/*0x008*/         UINT64       ValueList;
/*0x008*/         struct _CM_KEY_CONTROL_BLOCK* RealKcb;
              };
          }CACHED_CHILD_LIST, *PCACHED_CHILD_LIST;

         typedef struct _CC_EXTERNAL_CACHE_INFO                 // 3 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     FUNCT_00AE_19CE_Callback* Callback;
/*0x008*/     struct _DIRTY_PAGE_STATISTICS DirtyPageStatistics; // 3 elements, 0x18 bytes (sizeof)
/*0x020*/     struct _LIST_ENTRY Links;                          // 2 elements, 0x10 bytes (sizeof)
          }CC_EXTERNAL_CACHE_INFO, *PCC_EXTERNAL_CACHE_INFO;

