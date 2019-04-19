          typedef union _WHEA_ERROR_PACKET_FLAGS            // 8 elements, 0x4 bytes (sizeof)
          {
              struct                                        // 7 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      PreviousError : 1;           // 0 BitPosition
/*0x000*/         ULONG32      Reserved1 : 1;               // 1 BitPosition
/*0x000*/         ULONG32      HypervisorError : 1;         // 2 BitPosition
/*0x000*/         ULONG32      Simulated : 1;               // 3 BitPosition
/*0x000*/         ULONG32      PlatformPfaControl : 1;      // 4 BitPosition
/*0x000*/         ULONG32      PlatformDirectedOffline : 1; // 5 BitPosition
/*0x000*/         ULONG32      Reserved2 : 26;              // 6 BitPosition
              };
/*0x000*/     ULONG32      AsULONG;
          }WHEA_ERROR_PACKET_FLAGS, *PWHEA_ERROR_PACKET_FLAGS;

          typedef struct _WHEA_ERROR_PACKET_V2                // 16 elements, 0x50 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     ULONG32      Version;
/*0x008*/     ULONG32      Length;
/*0x00C*/     union _WHEA_ERROR_PACKET_FLAGS Flags;           // 8 elements, 0x4 bytes (sizeof)
/*0x010*/     enum _WHEA_ERROR_TYPE ErrorType;
/*0x014*/     enum _WHEA_ERROR_SEVERITY ErrorSeverity;
/*0x018*/     ULONG32      ErrorSourceId;
/*0x01C*/     enum _WHEA_ERROR_SOURCE_TYPE ErrorSourceType;
/*0x020*/     struct _GUID NotifyType;                        // 4 elements, 0x10 bytes (sizeof)
/*0x030*/     UINT64       Context;
/*0x038*/     enum _WHEA_ERROR_PACKET_DATA_FORMAT DataFormat;
/*0x03C*/     ULONG32      Reserved1;
/*0x040*/     ULONG32      DataOffset;
/*0x044*/     ULONG32      DataLength;
/*0x048*/     ULONG32      PshedDataOffset;
/*0x04C*/     ULONG32      PshedDataLength;
          }WHEA_ERROR_PACKET_V2, *PWHEA_ERROR_PACKET_V2;

          typedef struct _WHEA_ERROR_RECORD                                      // 2 elements, 0xC8 bytes (sizeof)
          {
/*0x000*/     struct _WHEA_ERROR_RECORD_HEADER Header;                           // 16 elements, 0x80 bytes (sizeof)
/*0x080*/     struct _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR SectionDescriptor[1];
          }WHEA_ERROR_RECORD, *PWHEA_ERROR_RECORD;

          typedef struct _WHEA_ERROR_RECORD_HEADER                 // 16 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     union _WHEA_REVISION Revision;                       // 3 elements, 0x2 bytes (sizeof)
/*0x006*/     ULONG32      SignatureEnd;
/*0x00A*/     UINT16       SectionCount;
/*0x00C*/     enum _WHEA_ERROR_SEVERITY Severity;
/*0x010*/     union _WHEA_ERROR_RECORD_HEADER_VALIDBITS ValidBits; // 5 elements, 0x4 bytes (sizeof)
/*0x014*/     ULONG32      Length;
/*0x018*/     union _WHEA_TIMESTAMP Timestamp;                     // 10 elements, 0x8 bytes (sizeof)
/*0x020*/     struct _GUID PlatformId;                             // 4 elements, 0x10 bytes (sizeof)
/*0x030*/     struct _GUID PartitionId;                            // 4 elements, 0x10 bytes (sizeof)
/*0x040*/     struct _GUID CreatorId;                              // 4 elements, 0x10 bytes (sizeof)
/*0x050*/     struct _GUID NotifyType;                             // 4 elements, 0x10 bytes (sizeof)
/*0x060*/     UINT64       RecordId;
/*0x068*/     union _WHEA_ERROR_RECORD_HEADER_FLAGS Flags;         // 5 elements, 0x4 bytes (sizeof)
/*0x06C*/     union _WHEA_PERSISTENCE_INFO PersistenceInfo;        // 7 elements, 0x8 bytes (sizeof)
/*0x074*/     UINT8        Reserved[12];
          }WHEA_ERROR_RECORD_HEADER, *PWHEA_ERROR_RECORD_HEADER;

          typedef union _WHEA_ERROR_RECORD_HEADER_FLAGS // 5 elements, 0x4 bytes (sizeof)
          {
              struct                                    // 4 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      Recovered : 1;           // 0 BitPosition
/*0x000*/         ULONG32      PreviousError : 1;       // 1 BitPosition
/*0x000*/         ULONG32      Simulated : 1;           // 2 BitPosition
/*0x000*/         ULONG32      Reserved : 29;           // 3 BitPosition
              };
/*0x000*/     ULONG32      AsULONG;
          }WHEA_ERROR_RECORD_HEADER_FLAGS, *PWHEA_ERROR_RECORD_HEADER_FLAGS;

          typedef union _WHEA_ERROR_RECORD_HEADER_VALIDBITS // 5 elements, 0x4 bytes (sizeof)
          {
              struct                                        // 4 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      PlatformId : 1;              // 0 BitPosition
/*0x000*/         ULONG32      Timestamp : 1;               // 1 BitPosition
/*0x000*/         ULONG32      PartitionId : 1;             // 2 BitPosition
/*0x000*/         ULONG32      Reserved : 29;               // 3 BitPosition
              };
/*0x000*/     ULONG32      AsULONG;
          }WHEA_ERROR_RECORD_HEADER_VALIDBITS, *PWHEA_ERROR_RECORD_HEADER_VALIDBITS;

          typedef struct _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR                 // 10 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     ULONG32      SectionOffset;
/*0x004*/     ULONG32      SectionLength;
/*0x008*/     union _WHEA_REVISION Revision;                                   // 3 elements, 0x2 bytes (sizeof)
/*0x00A*/     union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS ValidBits; // 4 elements, 0x1 bytes (sizeof)
/*0x00B*/     UINT8        Reserved;
/*0x00C*/     union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS Flags;         // 8 elements, 0x4 bytes (sizeof)
/*0x010*/     struct _GUID SectionType;                                        // 4 elements, 0x10 bytes (sizeof)
/*0x020*/     struct _GUID FRUId;                                              // 4 elements, 0x10 bytes (sizeof)
/*0x030*/     enum _WHEA_ERROR_SEVERITY SectionSeverity;
/*0x034*/     CHAR         FRUText[20];
          }WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, *PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR;

          typedef union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS // 8 elements, 0x4 bytes (sizeof)
          {
              struct                                                // 7 elements, 0x4 bytes (sizeof)
              {
/*0x000*/         ULONG32      Primary : 1;                         // 0 BitPosition
/*0x000*/         ULONG32      ContainmentWarning : 1;              // 1 BitPosition
/*0x000*/         ULONG32      Reset : 1;                           // 2 BitPosition
/*0x000*/         ULONG32      ThresholdExceeded : 1;               // 3 BitPosition
/*0x000*/         ULONG32      ResourceNotAvailable : 1;            // 4 BitPosition
/*0x000*/         ULONG32      LatentError : 1;                     // 5 BitPosition
/*0x000*/         ULONG32      Reserved : 26;                       // 6 BitPosition
              };
/*0x000*/     ULONG32      AsULONG;
          }WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS, *PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS;

          typedef union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS // 4 elements, 0x1 bytes (sizeof)
          {
              struct                                                    // 3 elements, 0x1 bytes (sizeof)
              {
/*0x000*/         UINT8        FRUId : 1;                               // 0 BitPosition
/*0x000*/         UINT8        FRUText : 1;                             // 1 BitPosition
/*0x000*/         UINT8        Reserved : 6;                            // 2 BitPosition
              };
/*0x000*/     UINT8        AsUCHAR;
          }WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS, *PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS;

          typedef union _WHEA_ERROR_STATUS     // 11 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT64       ErrorStatus;
              struct                           // 10 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       Reserved1 : 8;  // 0 BitPosition
/*0x000*/         UINT64       ErrorType : 8;  // 8 BitPosition
/*0x000*/         UINT64       Address : 1;    // 16 BitPosition
/*0x000*/         UINT64       Control : 1;    // 17 BitPosition
/*0x000*/         UINT64       Data : 1;       // 18 BitPosition
/*0x000*/         UINT64       Responder : 1;  // 19 BitPosition
/*0x000*/         UINT64       Requester : 1;  // 20 BitPosition
/*0x000*/         UINT64       FirstError : 1; // 21 BitPosition
/*0x000*/         UINT64       Overflow : 1;   // 22 BitPosition
/*0x000*/         UINT64       Reserved2 : 41; // 23 BitPosition
              };
          }WHEA_ERROR_STATUS, *PWHEA_ERROR_STATUS;

          typedef struct _WHEA_MEMORY_ERROR_SECTION                 // 16 elements, 0x49 bytes (sizeof)
          {
/*0x000*/     union _WHEA_MEMORY_ERROR_SECTION_VALIDBITS ValidBits; // 17 elements, 0x8 bytes (sizeof)
/*0x008*/     union _WHEA_ERROR_STATUS ErrorStatus;                 // 11 elements, 0x8 bytes (sizeof)
/*0x010*/     UINT64       PhysicalAddress;
/*0x018*/     UINT64       PhysicalAddressMask;
/*0x020*/     UINT16       Node;
/*0x022*/     UINT16       Card;
/*0x024*/     UINT16       Module;
/*0x026*/     UINT16       Bank;
/*0x028*/     UINT16       Device;
/*0x02A*/     UINT16       Row;
/*0x02C*/     UINT16       Column;
/*0x02E*/     UINT16       BitPosition;
/*0x030*/     UINT64       RequesterId;
/*0x038*/     UINT64       ResponderId;
/*0x040*/     UINT64       TargetId;
/*0x048*/     UINT8        ErrorType;
          }WHEA_MEMORY_ERROR_SECTION, *PWHEA_MEMORY_ERROR_SECTION;

          typedef union _WHEA_MEMORY_ERROR_SECTION_VALIDBITS // 17 elements, 0x8 bytes (sizeof)
          {
              struct                                         // 16 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       ErrorStatus : 1;              // 0 BitPosition
/*0x000*/         UINT64       PhysicalAddress : 1;          // 1 BitPosition
/*0x000*/         UINT64       PhysicalAddressMask : 1;      // 2 BitPosition
/*0x000*/         UINT64       Node : 1;                     // 3 BitPosition
/*0x000*/         UINT64       Card : 1;                     // 4 BitPosition
/*0x000*/         UINT64       Module : 1;                   // 5 BitPosition
/*0x000*/         UINT64       Bank : 1;                     // 6 BitPosition
/*0x000*/         UINT64       Device : 1;                   // 7 BitPosition
/*0x000*/         UINT64       Row : 1;                      // 8 BitPosition
/*0x000*/         UINT64       Column : 1;                   // 9 BitPosition
/*0x000*/         UINT64       BitPosition : 1;              // 10 BitPosition
/*0x000*/         UINT64       RequesterId : 1;              // 11 BitPosition
/*0x000*/         UINT64       ResponderId : 1;              // 12 BitPosition
/*0x000*/         UINT64       TargetId : 1;                 // 13 BitPosition
/*0x000*/         UINT64       ErrorType : 1;                // 14 BitPosition
/*0x000*/         UINT64       Reserved : 49;                // 15 BitPosition
              };
/*0x000*/     UINT64       ValidBits;
          }WHEA_MEMORY_ERROR_SECTION_VALIDBITS, *PWHEA_MEMORY_ERROR_SECTION_VALIDBITS;

          typedef union _WHEA_PERSISTENCE_INFO  // 7 elements, 0x8 bytes (sizeof)
          {
              struct                            // 6 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       Signature : 16;  // 0 BitPosition
/*0x000*/         UINT64       Length : 24;     // 16 BitPosition
/*0x000*/         UINT64       Identifier : 16; // 40 BitPosition
/*0x000*/         UINT64       Attributes : 2;  // 56 BitPosition
/*0x000*/         UINT64       DoNotLog : 1;    // 58 BitPosition
/*0x000*/         UINT64       Reserved : 5;    // 59 BitPosition
              };
/*0x000*/     UINT64       AsULONGLONG;
          }WHEA_PERSISTENCE_INFO, *PWHEA_PERSISTENCE_INFO;

          typedef union _WHEA_REVISION        // 3 elements, 0x2 bytes (sizeof)
          {
              struct                          // 2 elements, 0x2 bytes (sizeof)
              {
/*0x000*/         UINT8        MinorRevision;
/*0x001*/         UINT8        MajorRevision;
              };
/*0x000*/     UINT16       AsUSHORT;
          }WHEA_REVISION, *PWHEA_REVISION;

          typedef union _WHEA_TIMESTAMP             // 10 elements, 0x8 bytes (sizeof)
          {
              struct                                // 9 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         UINT64       Seconds : 8;         // 0 BitPosition
/*0x000*/         UINT64       Minutes : 8;         // 8 BitPosition
/*0x000*/         UINT64       Hours : 8;           // 16 BitPosition
/*0x000*/         UINT64       Precise : 1;         // 24 BitPosition
/*0x000*/         UINT64       Reserved : 7;        // 25 BitPosition
/*0x000*/         UINT64       Day : 8;             // 32 BitPosition
/*0x000*/         UINT64       Month : 8;           // 40 BitPosition
/*0x000*/         UINT64       Year : 8;            // 48 BitPosition
/*0x000*/         UINT64       Century : 8;         // 56 BitPosition
              };
/*0x000*/     union _LARGE_INTEGER AsLARGE_INTEGER; // 4 elements, 0x8 bytes (sizeof)
          }WHEA_TIMESTAMP, *PWHEA_TIMESTAMP;

typedef enum _WHEA_ERROR_PACKET_DATA_FORMAT  // 9 elements, 0x4 bytes
{
    WheaDataFormatIPFSalRecord = 0 /*0x0*/,
    WheaDataFormatXPFMCA       = 1 /*0x1*/,
    WheaDataFormatMemory       = 2 /*0x2*/,
    WheaDataFormatPCIExpress   = 3 /*0x3*/,
    WheaDataFormatNMIPort      = 4 /*0x4*/,
    WheaDataFormatPCIXBus      = 5 /*0x5*/,
    WheaDataFormatPCIXDevice   = 6 /*0x6*/,
    WheaDataFormatGeneric      = 7 /*0x7*/,
    WheaDataFormatMax          = 8 /*0x8*/
}WHEA_ERROR_PACKET_DATA_FORMAT, *PWHEA_ERROR_PACKET_DATA_FORMAT;

typedef enum _WHEA_ERROR_SEVERITY  // 4 elements, 0x4 bytes
{
    WheaErrSevRecoverable   = 0 /*0x0*/,
    WheaErrSevFatal         = 1 /*0x1*/,
    WheaErrSevCorrected     = 2 /*0x2*/,
    WheaErrSevInformational = 3 /*0x3*/
}WHEA_ERROR_SEVERITY, *PWHEA_ERROR_SEVERITY;

typedef enum _WHEA_ERROR_SOURCE_TYPE  // 13 elements, 0x4 bytes
{
    WheaErrSrcTypeMCE        = 0 /*0x0*/,
    WheaErrSrcTypeCMC        = 1 /*0x1*/,
    WheaErrSrcTypeCPE        = 2 /*0x2*/,
    WheaErrSrcTypeNMI        = 3 /*0x3*/,
    WheaErrSrcTypePCIe       = 4 /*0x4*/,
    WheaErrSrcTypeGeneric    = 5 /*0x5*/,
    WheaErrSrcTypeINIT       = 6 /*0x6*/,
    WheaErrSrcTypeBOOT       = 7 /*0x7*/,
    WheaErrSrcTypeSCIGeneric = 8 /*0x8*/,
    WheaErrSrcTypeIPFMCA     = 9 /*0x9*/,
    WheaErrSrcTypeIPFCMC     = 10 /*0xA*/,
    WheaErrSrcTypeIPFCPE     = 11 /*0xB*/,
    WheaErrSrcTypeMax        = 12 /*0xC*/
}WHEA_ERROR_SOURCE_TYPE, *PWHEA_ERROR_SOURCE_TYPE;

typedef enum _WHEA_ERROR_TYPE  // 7 elements, 0x4 bytes
{
    WheaErrTypeProcessor  = 0 /*0x0*/,
    WheaErrTypeMemory     = 1 /*0x1*/,
    WheaErrTypePCIExpress = 2 /*0x2*/,
    WheaErrTypeNMI        = 3 /*0x3*/,
    WheaErrTypePCIXBus    = 4 /*0x4*/,
    WheaErrTypePCIXDevice = 5 /*0x5*/,
    WheaErrTypeGeneric    = 6 /*0x6*/
}WHEA_ERROR_TYPE, *PWHEA_ERROR_TYPE;

