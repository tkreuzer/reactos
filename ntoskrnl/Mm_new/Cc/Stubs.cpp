
#include "..\ntosbase.h"

#define UNIMPLEMENTED __debugbreak()

extern "C" {

ULONG CcFastMdlReadWait;
ULONG CcFastReadNotPossible;
ULONG CcFastReadWait;
ULONG CcFastReadResourceMiss;
ULONG CcFastReadNoWait;
ULONG CcFastMdlReadNotPossible;

LARGE_INTEGER
NTAPI
CcGetLsnForFileObject (
    _In_ PFILE_OBJECT FileObject,
    _Out_opt_ PLARGE_INTEGER OldestLsn)
{
    LARGE_INTEGER Result = {0};
    UNIMPLEMENTED;
    return Result;
}


VOID
NTAPI
CcInitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ BOOLEAN PinAccess,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext)
{
    UNIMPLEMENTED;
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



VOID
NTAPI
CcSetFileSizes (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes)
{
    //LARGE_INTEGER AllocationSize;
    //LARGE_INTEGER FileSize;
    //LARGE_INTEGER ValidDataLength;

    UNIMPLEMENTED;
}


VOID
NTAPI
CcSetDirtyPageThreshold (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG DirtyPageThreshold)
{
#if 0
    PFSRTL_ADVANCED_FCB_HEADER FcbHeader;
    PSECTION_OBJECT_POINTERS SectionObjectPointers;
    PSHARED_CACHE_MAP SharedCacheMap;

    /* Get the shared cache map */
    SharedCacheMap = FileObject->SectionObjectPointer->SharedCacheMap;

    /* If we have a shared cache map, set the value */
    if (SharedCacheMap != NULL)
    {
        // SharedCacheMap->SetDirtyPageThreshold(DirtyPageThreshold);
        SharedCacheMap->DirtyPageThreshold = DirtyPageThreshold;
    }

    /* Get the FCB header */
    FcbHeader = FileObject->FsContext;
    if ((FcbHeader->Flags & FSRTL_FLAG_LIMIT_MODIFIED_PAGES) == 0)
    {
        FcbHeader->Flags |= FSRTL_FLAG_LIMIT_MODIFIED_PAGES;
    }
#endif
    UNIMPLEMENTED;
}


VOID
NTAPI
CcFlushCache (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _Out_opt_ PIO_STATUS_BLOCK IoStatus)
{
    UNIMPLEMENTED;
}


LARGE_INTEGER
NTAPI
CcGetFlushedValidData (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ BOOLEAN BcbListHeld)
{
    LARGE_INTEGER Result = {0};
    UNIMPLEMENTED;
    return Result;
}


BOOLEAN
NTAPI
CcZeroData (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER StartOffset,
    _In_ PLARGE_INTEGER EndOffset,
    _In_ BOOLEAN Wait)
{
    UNIMPLEMENTED;
    return FALSE;
}


PVOID
NTAPI
CcRemapBcb (
    _In_ PVOID Bcb)
{
    UNIMPLEMENTED;
    return NULL;
}


VOID
NTAPI
CcRepinBcb (
    _In_ PVOID Bcb)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcUnpinRepinnedBcb (
    _In_ PVOID Bcb,
    _In_ BOOLEAN WriteThrough,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    UNIMPLEMENTED;
}


PFILE_OBJECT
NTAPI
CcGetFileObjectFromSectionPtrs (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer)
{
    UNIMPLEMENTED;
    return NULL;
}


PFILE_OBJECT
NTAPI
CcGetFileObjectFromBcb (
    _In_ PVOID Bcb)
{
    UNIMPLEMENTED;
    return NULL;
}


BOOLEAN
NTAPI
CcCanIWrite (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_ ULONG BytesToWrite,
    _In_ BOOLEAN Wait,
    _In_ BOOLEAN Retrying)
{
    UNIMPLEMENTED;
    return FALSE;
}


VOID
NTAPI
CcDeferWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_POST_DEFERRED_WRITE PostRoutine,
    _In_ PVOID Context1,
    _In_ PVOID Context2,
    _In_ ULONG BytesToWrite,
    _In_ BOOLEAN Retrying)
{
    // Create a "workitem"
    // if that failed, call PostRoutine directly
    // queue the workitem (Retrying to head)
        // Workerthread waits for event that signals that writing is ok
        // Workerthread walks the list
            // if (CcCanIWrite(FileObject, BytesToWrite, TRUE, Retrying))
            //     PostRoutine(Context1, Context2);
    UNIMPLEMENTED;
}


BOOLEAN
NTAPI
CcCopyRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    // Get shared cache map
    // for each block in the file
        // find VACB
        // Create VACB if not existing
    // prefetch the pages we need MmPrefetchPages
    // for each block in the file
        // find VACB
        // Copy the block

    UNIMPLEMENTED;
    return FALSE;
}


VOID
NTAPI
CcFastCopyRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG FileOffset,
    _In_ ULONG Length,
    _In_ ULONG PageCount,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    UNIMPLEMENTED;
}


BOOLEAN
NTAPI
CcCopyWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _In_reads_bytes_(Length) PVOID Buffer)
{
    UNIMPLEMENTED;
    return FALSE;
}


VOID
NTAPI
CcFastCopyWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG FileOffset,
    _In_ ULONG Length,
    _In_reads_bytes_(Length) PVOID Buffer)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcMdlRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _Out_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcMdlReadComplete (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MdlChain)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcPrepareMdlWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _Out_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcMdlWriteComplete (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PMDL MdlChain)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcScheduleReadAhead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length)
{
    UNIMPLEMENTED;
}


NTSTATUS
NTAPI
CcWaitForCurrentLazyWriterActivity (
    VOID)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


VOID
NTAPI
CcSetReadAheadGranularity (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG Granularity)
{
    UNIMPLEMENTED;
}


BOOLEAN
NTAPI
CcPinRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _Outptr_ PVOID *Bcb,
    _Outptr_result_bytebuffer_(Length) PVOID *Buffer)
{
    UNIMPLEMENTED;
    return FALSE;
}


BOOLEAN
NTAPI
CcPinMappedData (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _Inout_ PVOID *Bcb)
{
    UNIMPLEMENTED;
    return FALSE;
}


BOOLEAN
NTAPI
CcPreparePinWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Zero,
    _In_ ULONG Flags,
    _Outptr_ PVOID *Bcb,
    _Outptr_result_bytebuffer_(Length) PVOID *Buffer)
{
    UNIMPLEMENTED;
    return FALSE;
}


VOID
NTAPI
CcSetDirtyPinnedData (
    _In_ PVOID BcbVoid,
    _In_opt_ PLARGE_INTEGER Lsn)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcUnpinData (
    _In_ PVOID Bcb)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcSetBcbOwnerPointer (
    _In_ PVOID Bcb,
    _In_ PVOID OwnerPointer)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcUnpinDataForThread (
    _In_ PVOID Bcb,
    _In_ ERESOURCE_THREAD ResourceThreadId)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcSetAdditionalCacheAttributes (
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN DisableReadAhead,
    _In_ BOOLEAN DisableWriteBehind)
{
    UNIMPLEMENTED;
}


BOOLEAN
NTAPI
CcIsThereDirtyData (
    _In_ PVPB Vpb)
{
    UNIMPLEMENTED;
    return FALSE;
}


VOID
NTAPI
CcMdlWriteAbort (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MdlChain)
{
    UNIMPLEMENTED;
}


VOID
NTAPI
CcSetLogHandleForFile (
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID LogHandle,
    _In_ PFLUSH_TO_LSN FlushToLsnRoutine)
{
    UNIMPLEMENTED;
}


LARGE_INTEGER
NTAPI
CcGetDirtyPages (
    _In_ PVOID LogHandle,
    _In_ PDIRTY_PAGE_ROUTINE DirtyPageRoutine,
    _In_ PVOID Context1,
    _In_ PVOID Context2)
{
    LARGE_INTEGER Result = {0};
    UNIMPLEMENTED;
    return Result;
}


_Success_(return!=FALSE)
BOOLEAN
NTAPI
CcMapData(
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _Outptr_ PVOID *Bcb,
    _Outptr_result_bytebuffer_(Length) PVOID *Buffer)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
CcPurgeCacheSection (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
#if (NTDDI_VERSION >= NTDDI_VISTA)
    _In_ ULONG Flags)
#else
    _In_ BOOLEAN UninitializeCacheMaps)
#endif
{
#if (NTDDI_VERSION < NTDDI_VISTA)
    ULONG Flags = UninitializeCacheMaps;
#endif
    UNIMPLEMENTED;
    return FALSE;
}


#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSTATUS
NTAPI
CcSetFileSizesEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes)


PFILE_OBJECT
NTAPI
CcGetFileObjectFromSectionPtrsRef (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer)


VOID
NTAPI
CcSetParallelFlushFile (
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN EnableParallelFlush)


BOOLEAN
CcIsThereDirtyDataEx (
    _In_ PVPB Vpb,
    _In_opt_ PULONG NumberOfDirtyPages)

#endif


#if (NTDDI_VERSION >= NTDDI_WIN7)
VOID
NTAPI
CcCoherencyFlushAndPurgeCache (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_opt_ ULONG Flags)

BOOLEAN
NTAPI
CcCopyWriteWontFlush (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length)
{
    return (Length <= 0x10000);
}
#endif


/*! Internal Stuff ************************************************************/


BOOLEAN
NTAPI
CcInitializeCacheManager (
    VOID)
{
    UNIMPLEMENTED;
    return FALSE;
}

VOID
NTAPI
CcPfInitializePrefetcher (
    VOID)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
CcMdlReadComplete2 (
    IN PMDL MemoryDescriptorList,
    IN PFILE_OBJECT FileObject)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
CcMdlWriteComplete2 (
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PMDL MdlChain)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
CcShutdownSystem (
    VOID)
{
    UNIMPLEMENTED;
}

}; // extern "C"
