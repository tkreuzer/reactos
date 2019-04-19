

#include "SharedCacheMap.hpp"

const OBJECT_ATTRIBUTES g_DefaultKernelObjectAttributes =
{
    sizeof(OBJECT_ATTRIBUTES),
    NULL,
    NULL,
    OBJ_KERNEL_HANDLE,
    NULL,
    NULL
};

namespace Cc {

#if 0
CalculateSectionSize (
    ULONG64 FileSize)
{

    if (FileSize < SMALL_FILE_SIZE)
    {
        SectionSize = 4 * VACB_MAPPING_SIZE;
    }

}


SHARED_CACHE_MAP::ShrinkSection

SHARED_CACHE_MAP::ExpandSection
#endif

SHARED_CACHE_MAP::~SHARED_CACHE_MAP;
{
    ObFastReplaceObject(&m_FileObjectFastRef, NULL);
}

NTSTATUS
SHARED_CACHE_MAP::Initialize (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext)
{
    NTSTATUS Status;

    m_NodeTypeCode = NODE_TYPE_CODE;
    m_NodeByteSize = 504;
    m_OpenCount = 0;

    InitializeListHead(&m_BcbList);
    InitializeListHead(&m_PrivateList);

    KeInitializeEvent(&m_Event, SynchronisationEvent, FALSE);
    KeInitializeEvent(&m_CreateEvent, NotificationEvent, FALSE);
    KeInitializeEvent(&m_WaitOnActiveCount, SynchronisationEvent, FALSE);

    ObInitializeFastReference(&m_FileObjectFastRef, FileObject);
    ExInitializePushLock(&m_VacbLock);
    ExInitializeFastMutex(&m_BcbLock);

    m_FileSize = FileSizes->FileSize;
    m_ValidDataLength = FileSizes->ValidDataLength;
    m_ValidDataGoal = FileSizes->ValidDataLength;
    m_SectionSize = FileSizes->AllocationSize;

    m_Callbacks = Callbacks;
    m_LazyWriteContext = LazyWriteContext;

    /* Get volume cache map (find existing or create new) */
    m_VolumeCacheMap = g_CacheManager.GetVolumeCacheMap(FileObject);

    /* Create the section */
    m_Status = MmCreateSection(&m_Section,
                               SECTION_ALL_ACCESS,
                               &g_DefaultKernelObjectAttributes,
                               &m_SectionSize,
                               PAGE_READWRITE,
                               0,
                               NULL,
                               FileObject);
    if (!NT_SUCCESS(m_Status))
    {
        return m_Status;
    }


#if 0
/*0x030*/     struct _VACB* InitialVacbs[4];
/*0x040*/     struct _VACB** Vacbs;
/*0x04C*/     ULONG32      DirtyPages;

/*0x058*/     struct _LIST_ENTRY SharedCacheMapLinks;
    m_Flags = 0;
    m_Status = 0;
/*0x078*/     ULONG32      PagesToWrite;
/*0x07C*/     UINT8        _PADDING0_[0x4];
/*0x080*/     INT64        BeyondLastFlush;

              union                                                // 2 elements, 0x8 bytes (sizeof)
              {
/*0x098*/         struct _LOGGED_STREAM_CALLBACK_V1 V1;            // 2 elements, 0x8 bytes (sizeof)
/*0x098*/         struct _LOGGED_STREAM_CALLBACK_V2 V2;            // 1 elements, 0x4 bytes (sizeof)
              };
/*0x0A0*/     union _LARGE_INTEGER LargestLSN;                     // 4 elements, 0x8 bytes (sizeof)
/*0x0A8*/     ULONG32      DirtyPageThreshold;
/*0x0AC*/     ULONG32      LazyWritePassCount;
/*0x0B0*/     struct _CACHE_UNINITIALIZE_EVENT* UninitializeEvent;
/*0x0D8*/     union _LARGE_INTEGER LastUnmapBehindOffset;          // 4 elements, 0x8 bytes (sizeof)
/*0x068*/     struct _MBCB* Mbcb;
/*0x0F0*/     union _LARGE_INTEGER HighWaterMappingOffset;         // 4 elements, 0x8 bytes (sizeof)
/*0x0F8*/     struct _PRIVATE_CACHE_MAP PrivateCacheMap;           // 18 elements, 0x68 bytes (sizeof)
/*0x160*/     VOID*        WriteBehindWorkQueueEntry;
/*0x164*/     struct _VOLUME_CACHE_MAP* VolumeCacheMap;
/*0x168*/     ULONG32      ProcImagePathHash;
/*0x16C*/     ULONG32      WritesInProgress;
#endif

    return STATUS_SUCCESS;
}

NTSTATUS
SHARED_CACHE_MAP::CreateInstance (
    _Out_ PSHARED_CACHE_MAP OutSharedCacheMap,
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext)
{
    PSHARED_CACHE_MAP SharedCacheMap;

    /* Allocate a new shared cache map from non-paged pool */
    SharedCacheMap = ExAllocatePoolWithTag(NonPagedPool,
                                           sizeof(PSHARED_CACHE_MAP),
                                           'cScC');
    if (SharedCacheMap == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = SharedCacheMap->Initialize(FileObject,
                                        FileSizes,
                                        Callbacks,
                                        LazyWriteContext);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    *OutSharedCacheMap = SharedCacheMap;
    return STATUS_SUCCESS;
}

inline
VOID
SHARED_CACHE_MAP::AcquireExclusiveLock (
    VOID)
{
    ExAcquirePushLockExclusive(&m_Lock);
}


extern "C" {

VOID
NTAPI
CcInitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ BOOLEAN PinAccess,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext)
{
    PSECTION_OBJECT_POINTERS SectionObjectPointers;
    PFSRTL_ADVANCED_FCB_HEADER FcbHeader;
    PSHARED_CACHE_MAP SharedCacheMap, NewSharedChacheMap;

    /* Get section object pointers */
    SectionObjectPointers = FileObject->SectionObjectPointer;
    if (SectionObjectPointers == NULL)
    {
        RtlRaiseStatus(STATUS_INVALID_PARAMETER);
    }

Retry:

    NewSharedCacheMap = NULL;
    NewPrivateCacheMap = NULL;

    /* Check if we have a shared cache map */
    if (SectionObjectPointers->SharedCacheMap == NULL)
    {
        /* Create a new instance of a shared cache map */
        Status = SHARED_CACHE_MAP::CreateInstance(&NewSharedCacheMap,
                                                  FileObject,
                                                  FileSizes,
                                                  Callbacks,
                                                  LazyWriteContext);
        if (!NT_SUCCESS(Status))
        {
            /* Raise failure status */
            RtlRaiseStatus(Status);
        }
    }

    /* Check if the file object has a private cache map */
    if (FileObject->PrivateCacheMap == NULL)
    {
        /* Check if the instance in the shared cache map is unused */
        if (NewSharedCacheMap == NULL)
        {
            /* Create a new private cache map */
            Status = PRIVATE_CACHE_MAP::CreateInstance(&NewPrivateCacheMap,
                                                       FileObject);
            if (!NT_SUCCESS(Status))
            {
                /* Raise failure status */
                RtlRaiseStatus(Status);
            }
        }
    }

    AcquireCacheMapLock();

    /* Check again if we still have the cache map */
    SharedCacheMap = SectionObjectPointers->SharedCacheMap;
    if (SharedCacheMap != NULL)
    {
        /* Reference it */
        SharedCacheMap->m_OpenCount++;
    }
    else
    {
        /* Check if we created a new shared cache map */
        if (NewSharedChacheMap == NULL)
        {
            ReleaseCacheMapLock();
            goto Retry;
        }

        SectionObjectPointers->SharedCacheMap = NewSharedChacheMap;
        SharedCacheMap = NewSharedChacheMap;
        NewSharedChacheMap = NULL;
    }

    /* Check if the file object has a private cache map */
    if (FileObject->PrivateCacheMap == NULL)
    {
        /* Check if the instance in the shared cache map is unused */
        if (SharedCacheMap->PrivateCacheMap.m_NodeTypeCode == 0)
        {
            /* Use the instance from the shared cache map */
            PrivateCacheMap = &SharedCacheMap->PrivateCacheMap;
            PrivateCacheMap->Initialize(FileObject);
            FileObject->PrivateCacheMap = PrivateCacheMap;
        }
        else
        {
            if (NewPrivateCacheMap == NULL)
            {
                ReleaseCacheMapLock();
                goto Retry;
            }

            FileObject->PrivateCacheMap = NewPrivateCacheMap;
            PrivateCacheMap = NewPrivateCacheMap;
            NewPrivateCacheMap = NULL;
        }
    }

    /* Insert the private cache map into the shared cache map's list */
    InsertTailList(&SharedCacheMap->m_PrivateList, &PrivateCacheMap->m_PrivateLinks);

    /* Release CacheMap lock */
    ReleaseCacheMapLock();

    /* If we still have NewSharedCacheMap, we need to delete it */
    if (NewSharedCacheMap != NULL)
    {
        /* Delete the shared cache map we created */
        delete NewSharedCacheMap;
    }

    if (NewPrivateCacheMap != NULL)
    {
        /* Delete the shared cache map we created */
        delete NewPrivateCacheMap;
    }

    /// CHeck if mapping section is large enough, otherwise extend it


}

BOOLEAN
NTAPI
CcUninitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_opt_ PLARGE_INTEGER TruncateSize,
    _In_opt_ PCACHE_UNINITIALIZE_EVENT UninitializeCompleteEvent)
{
    // call CcPurgeCacheSection to purge any cached data that is no longer part of the file.
    // Enqueue the Event in the SharedCacheMap
    UNIMPLEMENTED;
    return FALSE;
}

}; // extern "C"
}; // namespace Cc
