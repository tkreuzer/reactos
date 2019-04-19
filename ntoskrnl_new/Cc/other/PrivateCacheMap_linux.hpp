

typedef struct _PRIVATE_CACHE_MAP
{
    USHORT m_NodeTypeCode;
    union
    {
        struct
        {
            USHORT ReadAheadActive  : 1;
            USHORT ReadAheadEnabled : 1;
            USHORT PagePriority : 3;
            USHORT PipelineReadAheads : 1;
        };
        USHORT Short;
    } m_Flags;
    ULONG m_ReadAheadMask;
    PFILE_OBJECT m_FileObject;
    LARGE_INTEGER m_FileOffset1;
    LARGE_INTEGER m_BeyondLastByte1;
    LARGE_INTEGER m_FileOffset2;
    LARGE_INTEGER m_BeyondLastByte2;
    ULONG m_SequentialReadCount;
    ULONG m_ReadAheadLength;
    LARGE_INTEGER m_ReadAheadOffset;
    LARGE_INTEGER m_ReadAheadBeyondLastByte;
    UINT64 m_PrevReadAheadBeyondLastByte;
    ULONG m_ReadAheadSpinLock;
    ULONG m_PipelinedReadAheadRequestSize;
    ULONG m_ReadAheadGrowth;
    LIST_ENTRY m_PrivateLinks;
    PVOID m_ReadAheadWorkItem;

    friend class SHARED_CACHE_MAP;


} PRIVATE_CACHE_MAP, *PPRIVATE_CACHE_MAP;



VOID
PRIVATE_CACHE_MAP::Initialize (
    _In_ PFILE_OBJECT FileObject)
{
    /* Zero out the structure */
    RtlZeroMemory(this, sizeof(*this));

    m_NodeTypeCode = CcNodeTypePrivateCacheMap;
    m_ReadAheadMask = 4095;
    KeInitializeSpinLock(&m_ReadAheadSpinLock);
    m_Flags.PagePriority = PsGetCurrentThread()->CrossThreadFlags.ThreadPagePriority;

    /* Reference the file object */
    ObReferenceObject(FileObject);
    m_FileObject = FileObject;
}

VOID
PRIVATE_CACHE_MAP::UnInitialize (
    VOID)
{
    ObDereferenceObject(m_FileObject);
}

NTSTATUS
PRIVATE_CACHE_MAP::CreateInstance (
    _Out_ PRIVATE_CACHE_MAP** OutPrivateCacheMap,
    _In_ PFILE_OBJECT FileObject)
{
    PRIVATE_CACHE_MAP* PrivateCacheMap
    NTSTATUS Status;

    /* Allocate a new private cache map from non-paged pool */
    PrivateCacheMap = ExAllocatePoolWithTag(NonPagedPool,
                                            sizeof(PRIVATE_CACHE_MAP),
                                            'cPcC');
    if (PrivateCacheMap == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    PrivateCacheMap->Initialize(FileObject);

    *OutPrivateCacheMap = PrivateCacheMap;
    return STATUS_SUCCESS;
}

