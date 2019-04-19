


typedef struct _SECTION_IMAGE_INFORMATION
{
    PVOID TransferAddress;
    ULONG ZeroBits;
    UINT64 MaximumStackSize;
    UINT64 CommittedStackSize;
    ULONG SubSystemType;
    union
    {
        struct
        {
            UINT16 SubSystemMinorVersion;
            UINT16 SubSystemMajorVersion;
        };
        ULONG SubSystemVersion;
    };
    ULONG GpValue;
    UINT16 ImageCharacteristics;
    UINT16 DllCharacteristics;
    UINT16 Machine;
    BOOLEAN ImageContainsCode;
    union
    {
        UCHAR        ImageFlags;
        struct
        {
            UCHAR ComPlusNativeReady : 1;
            UCHAR ComPlusILOnly : 1;
            UCHAR ImageDynamicallyRelocated : 1;
            UCHAR ImageMappedFlat : 1;
            UCHAR BaseBelow4gb : 1;
            UCHAR Reserved : 3;
        };
    };
    ULONG LoaderFlags;
    ULONG ImageFileSize;
    ULONG CheckSum;
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _MI_EXTRA_IMAGE_INFORMATION
{
    ULONG SizeOfHeaders;
    ULONG SizeOfImage;
} MI_EXTRA_IMAGE_INFORMATION, *PMI_EXTRA_IMAGE_INFORMATION;

typedef struct _MI_SECTION_IMAGE_INFORMATION
{
    SECTION_IMAGE_INFORMATION ExportedImageInformation;
    MI_EXTRA_IMAGE_INFORMATION InternalImageInformation;
} MI_SECTION_IMAGE_INFORMATION, *PMI_SECTION_IMAGE_INFORMATION;

typedef struct _IMAGE_SECURITY_CONTEXT
{
    union
    {
        PVOID PageHashes;
        UINT64 Value;
        struct
        {
            UINT64 SecurityBeingCreated : 1;
            UINT64 SecurityMandatory : 1;
            UINT64 Unused : 1;
            UINT64 PageHashPointer : 61;
        };
    };
} IMAGE_SECURITY_CONTEXT, *PIMAGE_SECURITY_CONTEXT;

typedef struct _MI_IMAGE_SECURITY_REFERENCE
{
    IMAGE_SECURITY_CONTEXT SecurityContext;
    PVOID DynamicRelocations;
    LONG ReferenceCount;
} MI_IMAGE_SECURITY_REFERENCE, *PMI_IMAGE_SECURITY_REFERENCE;

typedef struct _MMSECTION_FLAGS
{
    UINT BeingDeleted : 1;
    UINT BeingCreated : 1;
    UINT BeingPurged : 1;
    UINT NoModifiedWriting : 1;
    UINT FailAllIo : 1;
    UINT Image : 1;
    UINT Based : 1;
    UINT File : 1;
    UINT AttemptingDelete : 1;
    UINT PrefetchCreated : 1;
    UINT PhysicalMemory : 1;
    UINT CopyOnWrite : 1;
    UINT Reserve : 1;
    UINT Commit : 1;
    UINT NoChange : 1;
    UINT WasPurged : 1;
    UINT UserReference : 1;
    UINT GlobalMemory : 1;
    UINT DeleteOnClose : 1;
    UINT FilePointerNull : 1;
    UINT PreferredNode : 6;
    UINT GlobalOnlyPerSession : 1;
    UINT UserWritable : 1;
    UINT Spare : 4;
} MMSECTION_FLAGS, *PMMSECTION_FLAGS;

typedef struct _MMSUBSECTION_FLAGS
{
    struct
    {
        USHORT SubsectionAccessed : 1;
        USHORT Protection : 5;
        USHORT StartingSector4132 : 10;
    };
    struct
    {
        USHORT SubsectionStatic : 1;
        USHORT GlobalMemory : 1;
        USHORT DirtyPages : 1;
        USHORT Spare : 1;
        USHORT SectorEndOffset : 12;
    };
} MMSUBSECTION_FLAGS, *PMMSUBSECTION_FLAGS;

typedef struct _SEGMENT_FLAGS
{
    struct
    {
        USHORT TotalNumberOfPtes4132 : 10;
        USHORT Spare0 : 1;
        USHORT LargePages : 1;
        USHORT Spare1 : 1;
        USHORT DebugSymbolsLoaded : 1;
        USHORT WriteCombined : 1;
        USHORT NoCache : 1;
    };
    struct
    {
        UCHAR FloppyMedia : 1;
        UCHAR DefaultProtectionMask : 5;
        UCHAR Binary32 : 1;
        UCHAR ContainsDebug : 1;
    };
    struct
    {
        UCHAR ILOnly : 1;
        UCHAR ImageSigningLevel : 3;
        UCHAR Spare : 4;
    };
} SEGMENT_FLAGS, *PSEGMENT_FLAGS;

typedef struct _MI_CONTROL_AREA_WAIT_BLOCK
{
    struct _MI_CONTROL_AREA_WAIT_BLOCK* Next;
    ULONG WaitReason;
    ULONG WaitResponse;
    KGATE Gate;
} MI_CONTROL_AREA_WAIT_BLOCK, *PMI_CONTROL_AREA_WAIT_BLOCK;

typedef struct _CONTROL_AREA
{
    PSEGMENT Segment;
    LIST_ENTRY ListHead;
    UINT64 NumberOfSectionReferences;
    UINT64 NumberOfPfnReferences;
    UINT64 NumberOfMappedViews;
    UINT64 NumberOfUserReferences;
    union
    {
        ULONG LongFlags;
        MMSECTION_FLAGS Flags;
    } u;
    ULONG FlushInProgressCount;
    EX_FAST_REF FilePointer;
    LONG ControlAreaLock;
    ULONG ModifiedWriteCount;
    PMI_CONTROL_AREA_WAIT_BLOCK WaitList;
    union
    {
        struct
        {
            union
            {
                ULONG NumberOfSystemCacheViews;
                ULONG ImageRelocationStartBit;
            };
            union
            {
                LONG WritableUserReferences;
                struct
                {
                    ULONG ImageRelocationSizeIn64k : 16;
                    ULONG Unused : 13;
                    ULONG BitMap : 2;
                    ULONG ImageActive : 1;
                };
            };
            union
            {
                PMM_AVL_TABLE SubsectionRoot;
                PMI_IMAGE_SECURITY_REFERENCE SeImageStub;
            };
        } e2;
    } u2;
    INT64        LockedPages;
} CONTROL_AREA, *PCONTROL_AREA;

typedef struct _SEGMENT
{
    PCONTROL_AREA ControlArea;
    ULONG TotalNumberOfPtes;
    SEGMENT_FLAGS SegmentFlags;
    ULONG64  NumberOfCommittedPages;
    ULONG64 SizeOfSegment;
    union
    {
        struct _MMEXTEND_INFO* ExtendInfo;
        PVOID BasedAddress;
    };
    EX_PUSH_LOCK SegmentLock;
    union
    {
        UINT64 ImageCommitment;
        PEPROCESS CreatingProcess;
    } u1;
    union
    {
        PMI_SECTION_IMAGE_INFORMATION ImageInformation;
        PVOID FirstMappedVa;
    } u2;
    PMMPTE PrototypePte;
} SEGMENT, *PSEGMENT;

typedef struct _SUBSECTION
{
    PCONTROL_AREA ControlArea;
    PMMPTE SubsectionBase;
    struct _SUBSECTION* NextSubsection;
    ULONG PtesInSubsection;
    union
    {
        ULONG UnusedPtes;
        PMM_AVL_TABLE GlobalPerSessionHead;
    };
    union
    {
        ULONG LongFlags;
        MMSUBSECTION_FLAGS SubsectionFlags;
    } u;
    ULONG StartingSector;
    ULONG NumberOfFullSectors;
} SUBSECTION, *PSUBSECTION;

typedef struct _MSUBSECTION
{
    PCONTROL_AREA ControlArea;
    PMMPTE SubsectionBase;
    union
    {
        struct _SUBSECTION* NextSubsection;
        struct _MSUBSECTION* NextMappedSubsection;
    };
    ULONG PtesInSubsection;
    union
    {
        ULONG UnusedPtes;
        PMM_AVL_TABLE GlobalPerSessionHead;
    };
    union
    {
        ULONG LongFlags;
        MMSUBSECTION_FLAGS SubsectionFlags;
    } u;
    ULONG StartingSector;
    ULONG NumberOfFullSectors;
    // extended area
    MM_AVL_NODE SubsectionNode;
    LIST_ENTRY DereferenceList;
    UINT64 NumberOfMappedViews;
    UINT64 NumberOfPfnReferences;
} MSUBSECTION, *PMSUBSECTION;

typedef struct _SEGMENT_OBJECT
{
    PVOID BaseAddress;
    ULONG TotalNumberOfPtes;
    LARGE_INTEGER SizeOfSegment;
    ULONG NonExtendedPtes;
    ULONG ImageCommitment;
    PCONTROL_AREA ControlArea;
    PSUBSECTION Subsection;
    PMMSECTION_FLAGS MmSectionFlags;
    PMMSUBSECTION_FLAGS MmSubSectionFlags;
} SEGMENT_OBJECT, *PSEGMENT_OBJECT;

typedef struct _SECTION_OBJECT
{
    PVOID StartingVa;
    PVOID EndingVa;
    PVOID Parent;
    PVOID LeftChild;
    PVOID RightChild;
    PSEGMENT_OBJECT Segment;
} SECTION_OBJECT, *PSECTION_OBJECT;

typedef struct _SECTION_OBJECT_POINTERS
{
    PVOID DataSectionObject;
    PVOID SharedCacheMap;
    PVOID ImageSectionObject;
} SECTION_OBJECT_POINTERS, *PSECTION_OBJECT_POINTERS;



typedef struct _MAPPED_FILE_SEGMENT        // 8 elements, 0x30 bytes (sizeof)
{
    struct _CONTROL_AREA* ControlArea;
    ULONG32      TotalNumberOfPtes;
    struct _SEGMENT_FLAGS SegmentFlags;    // 14 elements, 0x4 bytes (sizeof)
    UINT64       NumberOfCommittedPages;
    UINT64       SizeOfSegment;
    union                                  // 2 elements, 0x8 bytes (sizeof)
    {
        struct _MMEXTEND_INFO* ExtendInfo;
        VOID*        BasedAddress;
    };
    struct _EX_PUSH_LOCK SegmentLock;      // 7 elements, 0x8 bytes (sizeof)
} MAPPED_FILE_SEGMENT, *PMAPPED_FILE_SEGMENT;
