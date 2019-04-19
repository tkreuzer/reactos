

#include "SharedCacheMap.hpp"
#include <ndk/obfuncs.h>
#include <ndk/rtlfuncs.h>
#include <ndk/mmfuncs.h>

OBJECT_ATTRIBUTES g_DefaultKernelObjectAttributes =
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

SHARED_CACHE_MAP::~SHARED_CACHE_MAP()
{
    //ObFastReplaceObject(&m_FileObjectFastRef, NULL);
    if (m_Section != NULL)
    {
        ObCloseHandle(m_Section, KernelMode);
    }
}

NTSTATUS
SHARED_CACHE_MAP::Initialize (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext)
{
    //NTSTATUS Status;

    m_NodeTypeCode = 1;//NODE_TYPE_CODE;
    m_NodeByteSize = 504;
    m_OpenCount = 1;

    InitializeListHead(&m_BcbList);
    InitializeListHead(&m_PrivateList);

    KeInitializeEvent(&m_Event, SynchronizationEvent, FALSE);
    //KeInitializeEvent(&m_CreateEvent, NotificationEvent, FALSE);
    //KeInitializeEvent(&m_WaitOnActiveCount, SynchronizationEvent, FALSE);

    //ObInitializeFastReference(&m_FileObjectFastRef, FileObject);
    //ExInitializePushLock(&m_VacbLock);
    ExInitializeFastMutex(&m_BcbLock);

    m_FileSize = FileSizes->FileSize;
    m_ValidDataLength = FileSizes->ValidDataLength;
    m_ValidDataGoal = FileSizes->ValidDataLength;
    m_SectionSize = FileSizes->AllocationSize;

    m_Callbacks = Callbacks;
    m_LazyWriteContext = LazyWriteContext;

    /* Get volume cache map (find existing or create new) */
    //m_VolumeCacheMap = g_CacheManager.GetVolumeCacheMap(FileObject);



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
/*0x160*/     VOID*        WriteBehindWorkQueueEntry;
/*0x164*/     struct _VOLUME_CACHE_MAP* VolumeCacheMap;
/*0x168*/     ULONG32      ProcImagePathHash;
/*0x16C*/     ULONG32      WritesInProgress;
#endif

    return STATUS_SUCCESS;
}

NTSTATUS
SHARED_CACHE_MAP::CreateInstance (
    _Out_ PSHARED_CACHE_MAP* OutSharedCacheMap,
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext)
{
    PSHARED_CACHE_MAP SharedCacheMap;
    NTSTATUS Status;

    /* Allocate a new shared cache map from non-paged pool */
    SharedCacheMap = new SHARED_CACHE_MAP;
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
        delete SharedCacheMap;
        return Status;
    }

    *OutSharedCacheMap = SharedCacheMap;
    return STATUS_SUCCESS;
}

PPRIVATE_CACHE_MAP
SHARED_CACHE_MAP::GetPrivateCacheMap (
    VOID)
{
    if (m_PrivateCacheMap.GetFileObject() != NULL)
    {
        return NULL;
    }

    return &m_PrivateCacheMap;
}

VOID
SHARED_CACHE_MAP::AddPrivateCacheMap (
    _Inout_ PPRIVATE_CACHE_MAP PrivateCacheMap)
{
    InsertTailList(&m_PrivateList, &PrivateCacheMap->m_PrivateLinks);
}

VOID
SHARED_CACHE_MAP::SetFileSizes (
    _In_ PCC_FILE_SIZES FileSizes)
{
#if 0
    if (m_Section == NULL)
    {
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
    }
#endif
}

#if 0
inline
VOID
SHARED_CACHE_MAP::AcquireExclusiveLock (
    VOID)
{
    ExAcquirePushLockExclusive(&m_Lock);
}
#endif

BOOLEAN
IsFcbAcquiredShared (
    PFILE_OBJECT FileObject)
{
    PFSRTL_COMMON_FCB_HEADER FcbHeader;

    FcbHeader = static_cast<PFSRTL_COMMON_FCB_HEADER>(FileObject->FsContext);

    return ExIsResourceAcquiredSharedLite(FcbHeader->Resource) != 0;
}

BOOLEAN
IsFcbAcquiredExclusive (
    PFILE_OBJECT FileObject)
{
    PFSRTL_COMMON_FCB_HEADER FcbHeader;

    FcbHeader = static_cast<PFSRTL_COMMON_FCB_HEADER>(FileObject->FsContext);

    return ExIsResourceAcquiredExclusiveLite(FcbHeader->Resource);
}

extern "C" {

/*! \name CcInitializeCacheMap
 *
 *  \param FileObject -
 *
 *  \param FileSizes -
 *
 *  \param PinAccess -
 *
 *  \param Callbacks -
 *
 *  \param LazyWriteContext -
 *
 *  \remarks
 *      This routine requires that the FCB for the file be acquired either
 *      shared or exclusive prior to invoking the routine.
 */
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
    PSHARED_CACHE_MAP SharedCacheMap;
    PPRIVATE_CACHE_MAP PrivateCacheMap;
    PVOID Previous;
    NTSTATUS Status;

__debugbreak();
    /* Make sure the FCB is locked properly */
    NT_ASSERT(IsFcbAcquiredShared(FileObject) ||
              IsFcbAcquiredExclusive(FileObject));

    /* Get section object pointers */
    SectionObjectPointers = FileObject->SectionObjectPointer;
    if (SectionObjectPointers == NULL)
    {
        RtlRaiseStatus(STATUS_INVALID_PARAMETER);
    }

    /* Check if we have a shared cache map */
    SharedCacheMap = static_cast<PSHARED_CACHE_MAP>(SectionObjectPointers->SharedCacheMap);
    if (SharedCacheMap == NULL)
    {
        /* Create a new instance of a shared cache map */
        Status = SHARED_CACHE_MAP::CreateInstance(&SharedCacheMap,
                                                  FileObject,
                                                  FileSizes,
                                                  Callbacks,
                                                  LazyWriteContext);
        if (!NT_SUCCESS(Status))
        {
            /* Raise failure status */
            RtlRaiseStatus(Status);
        }

        /* Since we might only own a shared FCB lock, we need to exchange atomically */
        Previous = InterlockedCompareExchangePointer(&SectionObjectPointers->SharedCacheMap,
                                                     NULL,
                                                     SharedCacheMap);
        if (Previous != NULL)
        {
            /* Another thread was faster, delete the cache map we created */
            delete SharedCacheMap;

            /* Use the one we found */
            SharedCacheMap = static_cast<PSHARED_CACHE_MAP>(Previous);
        }
    }

    /* Lock the shared cache map, so that we have exclusive access */
    SharedCacheMap->AcquireMutex();

    /* Reference it */
    SharedCacheMap->ModifyOpenCount(1);

    /// Check if mapping section is large enough, otherwise extend it
    // SharedCacheMap->ExtendSection(FileSizes);
    SharedCacheMap->SetFileSizes(FileSizes);

    /* Check if the file object has a private cache map */
    PrivateCacheMap = static_cast<PPRIVATE_CACHE_MAP>(FileObject->PrivateCacheMap);
    if (PrivateCacheMap == NULL)
    {
        /* Check if the instance in the shared cache map is unused */
        PrivateCacheMap = SharedCacheMap->GetPrivateCacheMap();
        if (PrivateCacheMap != NULL)
        {
            /* Use the instance from the shared cache map */
            PrivateCacheMap->Initialize(FileObject);
        }
        else
        {
            /* Create a new private cache map */
            Status = PRIVATE_CACHE_MAP::CreateInstance(&PrivateCacheMap,
                                                       FileObject);
            if (!NT_SUCCESS(Status))
            {
                /* Raise failure status */
                RtlRaiseStatus(Status);
            }
        }

        FileObject->PrivateCacheMap = PrivateCacheMap;

        /* Insert the private cache map into the shared cache map's list */
        SharedCacheMap->AddPrivateCacheMap(PrivateCacheMap);
    }

    /* We are done, release the mutex */
    SharedCacheMap->ReleaseMutex();
}

/*! \fn CcUninitializeCacheMap
 *
 *  \param FileObject -
 *
 *  \param TruncateSize -
 *
 *  \param UninitializeCompleteEvent -
 *
 *  \remarks
 *      The FCB for the file stream must be acquired exclusively before
 *      invoking this routine.
 */
BOOLEAN
NTAPI
CcUninitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_opt_ PLARGE_INTEGER TruncateSize,
    _In_opt_ PCACHE_UNINITIALIZE_EVENT UninitializeCompleteEvent)
{
    /* Make sure the FCB is locked properly */
    NT_ASSERT(IsFcbAcquiredExclusive(FileObject));

    // call CcPurgeCacheSection to purge any cached data that is no longer part of the file.
    // Enqueue the Event in the SharedCacheMap
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}


VOID
NTAPI
CcSetFileSizes (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes)
{
    PSECTION_OBJECT_POINTERS SectionObjectPointers;
    PSHARED_CACHE_MAP SharedCacheMap;

    /* Make sure the FCB is locked properly */
    NT_ASSERT(IsFcbAcquiredExclusive(FileObject));

    /* Get section object pointers */
    SectionObjectPointers = FileObject->SectionObjectPointer;
    if (SectionObjectPointers == NULL)
    {
        RtlRaiseStatus(STATUS_INVALID_PARAMETER);
    }

    /* Check if we have a shared cache map */
    SharedCacheMap = static_cast<PSHARED_CACHE_MAP>(SectionObjectPointers->SharedCacheMap);
    if (SharedCacheMap == NULL)
    {
        RtlRaiseStatus(STATUS_INVALID_PARAMETER);
    }

    SharedCacheMap->SetFileSizes(FileSizes);

    UNIMPLEMENTED;
}


}; // extern "C"
}; // namespace Cc
