
          typedef struct _FS_FILTER_CALLBACK_DATA      // 6 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     ULONG32      SizeOfFsFilterCallbackData;
/*0x004*/     UINT8        Operation;
/*0x005*/     UINT8        Reserved;
/*0x006*/     UINT8        _PADDING0_[0x2];
/*0x008*/     struct _DEVICE_OBJECT* DeviceObject;
/*0x010*/     struct _FILE_OBJECT* FileObject;
/*0x018*/     union _FS_FILTER_PARAMETERS Parameters;  // 5 elements, 0x28 bytes (sizeof)
          }FS_FILTER_CALLBACK_DATA, *PFS_FILTER_CALLBACK_DATA;

          typedef struct _FS_FILTER_CALLBACKS                                                                                                                                                                                                                // 14 elements, 0x68 bytes (sizeof)
          {
/*0x000*/     ULONG32      SizeOfFsFilterCallbacks;
/*0x004*/     ULONG32      Reserved;
/*0x008*/     FUNCT_0064_0A22_PreAcquireForSectionSynchronization_PreReleaseForSectionSynchronization_PreAcquireForCcFlush_PreReleaseForCcFlush_PreAcquireForModifiedPageWriter_PreReleaseForModifiedPageWriter* PreAcquireForSectionSynchronization;
/*0x010*/     FUNCT_00AE_0A9D_PostAcquireForSectionSynchronization_PostReleaseForSectionSynchronization_PostAcquireForCcFlush_PostReleaseForCcFlush_PostAcquireForModifiedPageWriter_PostReleaseForModifiedPageWriter* PostAcquireForSectionSynchronization;
/*0x018*/     FUNCT_0064_0A22_PreAcquireForSectionSynchronization_PreReleaseForSectionSynchronization_PreAcquireForCcFlush_PreReleaseForCcFlush_PreAcquireForModifiedPageWriter_PreReleaseForModifiedPageWriter* PreReleaseForSectionSynchronization;
/*0x020*/     FUNCT_00AE_0A9D_PostAcquireForSectionSynchronization_PostReleaseForSectionSynchronization_PostAcquireForCcFlush_PostReleaseForCcFlush_PostAcquireForModifiedPageWriter_PostReleaseForModifiedPageWriter* PostReleaseForSectionSynchronization;
/*0x028*/     FUNCT_0064_0A22_PreAcquireForSectionSynchronization_PreReleaseForSectionSynchronization_PreAcquireForCcFlush_PreReleaseForCcFlush_PreAcquireForModifiedPageWriter_PreReleaseForModifiedPageWriter* PreAcquireForCcFlush;
/*0x030*/     FUNCT_00AE_0A9D_PostAcquireForSectionSynchronization_PostReleaseForSectionSynchronization_PostAcquireForCcFlush_PostReleaseForCcFlush_PostAcquireForModifiedPageWriter_PostReleaseForModifiedPageWriter* PostAcquireForCcFlush;
/*0x038*/     FUNCT_0064_0A22_PreAcquireForSectionSynchronization_PreReleaseForSectionSynchronization_PreAcquireForCcFlush_PreReleaseForCcFlush_PreAcquireForModifiedPageWriter_PreReleaseForModifiedPageWriter* PreReleaseForCcFlush;
/*0x040*/     FUNCT_00AE_0A9D_PostAcquireForSectionSynchronization_PostReleaseForSectionSynchronization_PostAcquireForCcFlush_PostReleaseForCcFlush_PostAcquireForModifiedPageWriter_PostReleaseForModifiedPageWriter* PostReleaseForCcFlush;
/*0x048*/     FUNCT_0064_0A22_PreAcquireForSectionSynchronization_PreReleaseForSectionSynchronization_PreAcquireForCcFlush_PreReleaseForCcFlush_PreAcquireForModifiedPageWriter_PreReleaseForModifiedPageWriter* PreAcquireForModifiedPageWriter;
/*0x050*/     FUNCT_00AE_0A9D_PostAcquireForSectionSynchronization_PostReleaseForSectionSynchronization_PostAcquireForCcFlush_PostReleaseForCcFlush_PostAcquireForModifiedPageWriter_PostReleaseForModifiedPageWriter* PostAcquireForModifiedPageWriter;
/*0x058*/     FUNCT_0064_0A22_PreAcquireForSectionSynchronization_PreReleaseForSectionSynchronization_PreAcquireForCcFlush_PreReleaseForCcFlush_PreAcquireForModifiedPageWriter_PreReleaseForModifiedPageWriter* PreReleaseForModifiedPageWriter;
/*0x060*/     FUNCT_00AE_0A9D_PostAcquireForSectionSynchronization_PostReleaseForSectionSynchronization_PostAcquireForCcFlush_PostReleaseForCcFlush_PostAcquireForModifiedPageWriter_PostReleaseForModifiedPageWriter* PostReleaseForModifiedPageWriter;
          }FS_FILTER_CALLBACKS, *PFS_FILTER_CALLBACKS;

          typedef union _FS_FILTER_PARAMETERS                                   // 5 elements, 0x28 bytes (sizeof)
          {
              struct                                                            // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         union _LARGE_INTEGER* EndingOffset;
/*0x008*/         struct _ERESOURCE** ResourceToRelease;
              }AcquireForModifiedPageWriter;
              struct                                                            // 1 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         struct _ERESOURCE* ResourceToRelease;
              }ReleaseForModifiedPageWriter;
              struct                                                            // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         enum _FS_FILTER_SECTION_SYNC_TYPE SyncType;
/*0x004*/         ULONG32      PageProtection;
              }AcquireForSectionSynchronization;
              struct                                                            // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         enum _FS_FILTER_STREAM_FO_NOTIFICATION_TYPE NotificationType;
/*0x004*/         UINT8        _PADDING0_[0x4];
/*0x008*/         UINT8        SafeToRecurse;
/*0x009*/         UINT8        _PADDING1_[0x7];
              }NotifyStreamFileObject;
              struct                                                            // 5 elements, 0x28 bytes (sizeof)
              {
/*0x000*/         VOID*        Argument1;
/*0x008*/         VOID*        Argument2;
/*0x010*/         VOID*        Argument3;
/*0x018*/         VOID*        Argument4;
/*0x020*/         VOID*        Argument5;
              }Others;
          }FS_FILTER_PARAMETERS, *PFS_FILTER_PARAMETERS;

          typedef struct _FSRTL_ADVANCED_FCB_HEADER   // 18 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     INT16        NodeTypeCode;
/*0x002*/     INT16        NodeByteSize;
/*0x004*/     UINT8        Flags;
/*0x005*/     UINT8        IsFastIoPossible;
/*0x006*/     UINT8        Flags2;
              struct                                  // 2 elements, 0x1 bytes (sizeof)
              {
/*0x007*/         UINT8        Reserved : 4;          // 0 BitPosition
/*0x007*/         UINT8        Version : 4;           // 4 BitPosition
              };
/*0x008*/     struct _ERESOURCE* Resource;
/*0x010*/     struct _ERESOURCE* PagingIoResource;
/*0x018*/     union _LARGE_INTEGER AllocationSize;    // 4 elements, 0x8 bytes (sizeof)
/*0x020*/     union _LARGE_INTEGER FileSize;          // 4 elements, 0x8 bytes (sizeof)
/*0x028*/     union _LARGE_INTEGER ValidDataLength;   // 4 elements, 0x8 bytes (sizeof)
/*0x030*/     struct _FAST_MUTEX* FastMutex;
/*0x038*/     struct _LIST_ENTRY FilterContexts;      // 2 elements, 0x10 bytes (sizeof)
/*0x048*/     struct _EX_PUSH_LOCK PushLock;          // 7 elements, 0x8 bytes (sizeof)
/*0x050*/     VOID**       FileContextSupportPointer;
              union                                   // 2 elements, 0x8 bytes (sizeof)
              {
/*0x058*/         VOID*        Oplock;
/*0x058*/         VOID*        ReservedForRemote;
              };
          }FSRTL_ADVANCED_FCB_HEADER, *PFSRTL_ADVANCED_FCB_HEADER;

typedef enum _FS_FILTER_SECTION_SYNC_TYPE  // 2 elements, 0x4 bytes
{
    SyncTypeOther         = 0 /*0x0*/,
    SyncTypeCreateSection = 1 /*0x1*/
}FS_FILTER_SECTION_SYNC_TYPE, *PFS_FILTER_SECTION_SYNC_TYPE;

typedef enum _FS_FILTER_STREAM_FO_NOTIFICATION_TYPE  // 2 elements, 0x4 bytes
{
    NotifyTypeCreate  = 0 /*0x0*/,
    NotifyTypeRetired = 1 /*0x1*/
}FS_FILTER_STREAM_FO_NOTIFICATION_TYPE, *PFS_FILTER_STREAM_FO_NOTIFICATION_TYPE;

typedef enum _FSINFOCLASS  // 12 elements, 0x4 bytes
{
    FileFsVolumeInformation      = 1 /*0x1*/,
    FileFsLabelInformation       = 2 /*0x2*/,
    FileFsSizeInformation        = 3 /*0x3*/,
    FileFsDeviceInformation      = 4 /*0x4*/,
    FileFsAttributeInformation   = 5 /*0x5*/,
    FileFsControlInformation     = 6 /*0x6*/,
    FileFsFullSizeInformation    = 7 /*0x7*/,
    FileFsObjectIdInformation    = 8 /*0x8*/,
    FileFsDriverPathInformation  = 9 /*0x9*/,
    FileFsVolumeFlagsInformation = 10 /*0xA*/,
    FileFsSectorSizeInformation  = 11 /*0xB*/,
    FileFsMaximumInformation     = 12 /*0xC*/
}FSINFOCLASS, *PFSINFOCLASS;

