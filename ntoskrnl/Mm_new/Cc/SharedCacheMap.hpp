

#pragma once

#include "..\ntosbase.h"
#include "PrivateCacheMap.hpp"

namespace Cc {

typedef class SHARED_CACHE_MAP
{
    CSHORT m_NodeTypeCode;
    CSHORT m_NodeByteSize;

    /* This field counts the number of file objects that refer to the cache map.
       Access to it is synchronized using the FCB resource */
    ULONG m_OpenCount;

    LARGE_INTEGER m_FileSize;
    LIST_ENTRY m_BcbList;
    LARGE_INTEGER m_SectionSize;
    LARGE_INTEGER m_ValidDataLength;
    LARGE_INTEGER m_ValidDataGoal;
    class VACB* m_InitialVacbs[4];
    class VACD_ARRAY* m_Vacbs;
    EX_FAST_REF m_FileObjectFastRef;
    EX_PUSH_LOCK m_VacbLock;
    ULONG m_DirtyPages;
    LIST_ENTRY m_LoggedStreamLinks;
    LIST_ENTRY m_SharedCacheMapLinks;
    ULONG m_Flags;
    NTSTATUS m_Status;
    MBCB* m_Mbcb;
    PVOID m_Section;
    PKEVENT m_CreateEvent;
    PKEVENT m_WaitOnActiveCount;
    ULONG m_PagesToWrite;
    INT64 m_BeyondLastFlush;
    CACHE_MANAGER_CALLBACKS* m_Callbacks;
    PVOID m_LazyWriteContext;
    LIST_ENTRY m_PrivateList;
//    union
//    {
//        LOGGED_STREAM_CALLBACK_V1 m_V1;
//        LOGGED_STREAM_CALLBACK_V2 m_V2;
//    };
    LARGE_INTEGER m_LargestLSN;
    ULONG m_DirtyPageThreshold;
    ULONG m_LazyWritePassCount;
    CACHE_UNINITIALIZE_EVENT* m_UninitializeEvent;
    FAST_MUTEX m_BcbLock;
    LARGE_INTEGER m_LastUnmapBehindOffset;
    KEVENT m_Event;
    LARGE_INTEGER m_HighWaterMappingOffset;
    PRIVATE_CACHE_MAP m_PrivateCacheMap;
    PVOID m_WriteBehindWorkQueueEntry;
    class VOLUME_CACHE_MAP* m_VolumeCacheMap;
    ULONG m_ProcImagePathHash;
    ULONG m_WritesInProgress;

    inline
    void*
    operator new(size_t Size)
    {
        return ExAllocatePoolWithTag(NonPagedPool, Size, 'cScC');
    }


    NTSTATUS
    Initialize (
        _In_ PFILE_OBJECT FileObject,
        _In_ PCC_FILE_SIZES FileSizes,
        _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
        _In_ PVOID LazyWriteContext);

public:

    ~SHARED_CACHE_MAP();

    static
    NTSTATUS
    CreateInstance (
        _Out_ class SHARED_CACHE_MAP** OutSharedCacheMap,
        _In_ PFILE_OBJECT FileObject,
        _In_ PCC_FILE_SIZES FileSizes,
        _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
        _In_ PVOID LazyWriteContext);

    inline
    ULONG
    ModifyOpenCount (
        _In_ LONG Addend)
    {
        m_OpenCount += Addend;
        return m_OpenCount;
    }

    PPRIVATE_CACHE_MAP
    GetPrivateCacheMap (
        VOID);

    VOID
    AddPrivateCacheMap (
        _Inout_ PPRIVATE_CACHE_MAP PrivateCacheMap);

    VOID
    SetFileSizes (
        _In_ PCC_FILE_SIZES FileSizes);

    inline
    VOID
    AcquireMutex (
        VOID)
    {
        ExAcquireFastMutex(&m_BcbLock);
    }

    inline
    VOID
    ReleaseMutex (
        VOID)
    {
        ExReleaseFastMutex(&m_BcbLock);
    }

} *PSHARED_CACHE_MAP;

}; // namespace Cc

