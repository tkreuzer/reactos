
#include <ntifs.h>

#define UNIMPLEMENTED_DBGBREAK __debugbreak()

ULONG CcFastMdlReadWait;
ULONG CcFastReadNotPossible;
ULONG CcFastReadWait;
ULONG CcFastReadResourceMiss;
ULONG CcFastReadNoWait;
ULONG CcFastMdlReadNotPossible;

struct _CC_ASYNC_READ_CONTEXT;

VOID
NTAPI
CcAddDirtyPagesToExternalCache (
    _In_ PVOID ExternalCacheContext,
    _In_ PFN_NUMBER Pages)
{
    UNIMPLEMENTED_DBGBREAK;
}

BOOLEAN
NTAPI
CcAsyncCopyRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ PETHREAD IoIssuerThread,
    _In_ struct _CC_ASYNC_READ_CONTEXT *AsyncReadContext
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

/*!
    \ref NT file system internals p. 301
*/
BOOLEAN
NTAPI
CcCanIWrite (
    _In_opt_ PFILE_OBJECT FileObject,
    _In_ ULONG BytesToWrite,
    _In_ BOOLEAN Wait,
    _In_ UCHAR Retrying)
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

VOID
NTAPI
CcCoherencyFlushAndPurgeCache (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_opt_ ULONG Flags
    )
{
    UNIMPLEMENTED_DBGBREAK;
}


BOOLEAN
NTAPI
CcCopyReadEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ PETHREAD IoIssuerThread)
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
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
    /* Pass on to the extended version */
    return CcCopyReadEx(FileObject,
                        FileOffset,
                        Length,
                        Wait,
                        Buffer,
                        IoStatus,
                        NULL);
}

BOOLEAN
NTAPI
CcCopyWriteEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ PETHREAD IoIssuerThread
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
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
    /* Pass on to the extended version */
    return CcCopyWriteEx(FileObject,
                         FileOffset,
                         Length,
                         Wait,
                         Buffer,
                         NULL);
}

#undef CcCopyWriteWontFlush
BOOLEAN
NTAPI
CcCopyWriteWontFlush (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length)
{
    return (Length <= 0x10000);
}

// ntosifs.h
VOID
NTAPI
CcDeductDirtyPagesFromExternalCache (
    _In_ PVOID ExternalCacheContext,
    _In_ PFN_NUMBER Pages
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcDeferWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_POST_DEFERRED_WRITE PostRoutine,
    _In_ PVOID Context1,
    _In_ PVOID Context2,
    _In_ ULONG BytesToWrite,
    _In_ BOOLEAN Retrying
    )
{
    UNIMPLEMENTED_DBGBREAK;
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
    LARGE_INTEGER LargeFileOffset;

    /* Pass on to the extended version */
    LargeFileOffset.QuadPart = FileOffset;
    CcCopyReadEx(FileObject,
                 &LargeFileOffset,
                 Length,
                 TRUE,
                 Buffer,
                 IoStatus,
                 NULL);
}

VOID
NTAPI
CcFastCopyWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG FileOffset,
    _In_ ULONG Length,
    _In_reads_bytes_(Length) PVOID Buffer
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcFlushCache (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _Out_opt_ PIO_STATUS_BLOCK IoStatus
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

// ntosifs.h
VOID
NTAPI
CcFlushCacheToLsn (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER LargestLsn,
    _Out_opt_ PIO_STATUS_BLOCK IoStatus
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

LARGE_INTEGER
NTAPI
CcGetDirtyPages (
    _In_ PVOID LogHandle,
    _In_ PDIRTY_PAGE_ROUTINE DirtyPageRoutine,
    _In_ PVOID Context1,
    _In_ PVOID Context2
    )
{
    LARGE_INTEGER Result = {{0,0}};
    UNIMPLEMENTED_DBGBREAK;
    return Result;
}

PFILE_OBJECT
NTAPI
CcGetFileObjectFromBcb (
    _In_ PVOID Bcb
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return NULL;
}

PFILE_OBJECT
NTAPI
CcGetFileObjectFromSectionPtrs (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer)
{
    UNIMPLEMENTED_DBGBREAK;
    return NULL;
}

PFILE_OBJECT
NTAPI
CcGetFileObjectFromSectionPtrsRef (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return NULL;
}

LARGE_INTEGER
NTAPI
CcGetFlushedValidData (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ BOOLEAN BcbListHeld
    )
{
    LARGE_INTEGER Result = {{0,0}};
    UNIMPLEMENTED_DBGBREAK;
    return Result;
}

LARGE_INTEGER
NTAPI
CcGetLsnForFileObject (
    _In_ PFILE_OBJECT FileObject,
    _Out_opt_ PLARGE_INTEGER OldestLsn)
{
    LARGE_INTEGER Result = {{0,0}};
    UNIMPLEMENTED_DBGBREAK;
    return Result;
}

BOOLEAN
NTAPI
CcIsThereDirtyData (
    _In_ PVPB Vpb
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

BOOLEAN
NTAPI
CcIsThereDirtyDataEx (
    _In_ PVPB Vpb,
    _In_opt_ PULONG NumberOfDirtyPages
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

// ntosifs.h
BOOLEAN
NTAPI
CcIsThereDirtyLoggedPages (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Out_opt_ PULONG NumberOfDirtyPages
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

//_Success_(return!=FALSE)
BOOLEAN
NTAPI
CcMapData (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _Outptr_ PVOID *Bcb,
    _Outptr_result_bytebuffer_(Length) PVOID *Buffer
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
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
    PMDL Mdl;

    UNIMPLEMENTED_DBGBREAK;

    // reference and lock the FCB
    Mdl = 0;//MmProbeAndLockSectionPages(Section, StartingPage, PageCount);
    if (Mdl == NULL)
    {
        //RtlRaiseStatus(STATUS_INSUFFICIENT_RESOURCES);
    }

}

VOID
NTAPI
CcMdlReadComplete (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MdlChain)
{
    UNIMPLEMENTED_DBGBREAK;
    //MmUnlockPages(MdlChain);
    //MmFreeMdl(MdlChain);
}

VOID
NTAPI
CcMdlWriteAbort (
    _In_ PFILE_OBJECT FileObject,
    _In_ PMDL MdlChain
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcMdlWriteComplete (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PMDL MdlChain)
{
    PDEVICE_OBJECT FsDeviceObject;
    PFAST_IO_DISPATCH FastIoDispatch;

    UNIMPLEMENTED_DBGBREAK;

    FsDeviceObject = IoGetRelatedDeviceObject(FileObject);
    FastIoDispatch = FsDeviceObject->DriverObject->FastIoDispatch;

    if ((FastIoDispatch != NULL) &&
        (FastIoDispatch->SizeOfFastIoDispatch > 0x4C) &&
        (FastIoDispatch->MdlWriteComplete != NULL))
    {
        if (FastIoDispatch->MdlWriteComplete(FileObject,
                                             FileOffset,
                                             MdlChain,
                                             FsDeviceObject))
        {
            return;
        }
    }

    //CcMdlWriteComplete2(FileObject, FileOffset, MdlChain);
}

BOOLEAN
NTAPI
CcPinMappedData (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _Inout_ PVOID *Bcb
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

BOOLEAN
NTAPI
CcPinRead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _Outptr_ PVOID *Bcb,
    _Outptr_result_bytebuffer_(Length) PVOID *Buffer
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

VOID
NTAPI
CcPrepareMdlWrite (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _Out_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus
    )
{
    UNIMPLEMENTED_DBGBREAK;
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
    _Outptr_result_bytebuffer_(Length) PVOID *Buffer
    )
{
    UNIMPLEMENTED_DBGBREAK;
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
    (void)Flags;
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

typedef
VOID
NTAPI
EXTERNAL_CACHE_CALLBACK (
    _In_ PVOID ExternalCacheContext,
    _In_ PFN_NUMBER PagesToWrite,
    _In_ ULONG Reserved);
typedef EXTERNAL_CACHE_CALLBACK *PEXTERNAL_CACHE_CALLBACK;

NTSTATUS
NTAPI
CcRegisterExternalCache(
    _In_ PEXTERNAL_CACHE_CALLBACK Callback,
    _Out_ PVOID *ExternalCacheContext
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return STATUS_NOT_IMPLEMENTED;
}

PVOID
NTAPI
CcRemapBcb (
    _In_ PVOID Bcb
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return NULL;
}

VOID
NTAPI
CcRepinBcb (
    _In_ PVOID Bcb
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcScheduleReadAhead (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcScheduleReadAheadEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ PETHREAD IoIssuerThread
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcSetAdditionalCacheAttributes (
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN DisableReadAhead,
    _In_ BOOLEAN DisableWriteBehind
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcSetAdditionalCacheAttributesEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG Flags
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcSetBcbOwnerPointer (
    _In_ PVOID Bcb,
    _In_ PVOID OwnerPointer
    )
{
    UNIMPLEMENTED_DBGBREAK;
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
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcSetDirtyPinnedData (
    _In_ PVOID BcbVoid,
    _In_opt_ PLARGE_INTEGER Lsn
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcSetFileSizes (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

NTSTATUS
NTAPI
CcSetFileSizesEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
CcSetLogHandleForFile (
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID LogHandle,
    _In_ PFLUSH_TO_LSN FlushToLsnRoutine
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

// ntosifs.h
typedef struct _QUERY_LOG_USAGE *PQUERY_LOG_USAGE;
VOID
NTAPI
CcSetLogHandleForFileEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ PVOID LogHandle,
    _In_ PFLUSH_TO_LSN FlushToLsnRoutine,
    _In_ PQUERY_LOG_USAGE QueryLogUsageRoutine,
    _In_opt_ PFILE_OBJECT RelatedLogHandleFileObject
    )
{
    UNIMPLEMENTED_DBGBREAK;
}


// ntosifs.h
VOID
NTAPI
CcSetLoggedDataThreshold (
    _In_ PVOID LogHandle,
    _In_ ULONG NumberOfPages
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcSetParallelFlushFile (
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN EnableParallelFlush
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcSetReadAheadGranularity (
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG Granularity
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

// ntosifs.h
struct _READ_AHEAD_PARAMETERS;
VOID
NTAPI
CcSetReadAheadGranularityEx (
    _In_ PFILE_OBJECT FileObject,
    _In_ struct _READ_AHEAD_PARAMETERS *ReadAheadParameters
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

//@ stub CcTestControl

// ntosifs.h
VOID
NTAPI
CcUnmapFileOffsetFromSystemCache (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG Flags
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcUnpinData (
    _In_ PVOID Bcb
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcUnpinDataForThread (
    _In_ PVOID Bcb,
    _In_ ERESOURCE_THREAD ResourceThreadId
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

VOID
NTAPI
CcUnpinRepinnedBcb (
    _In_ PVOID Bcb,
    _In_ BOOLEAN WriteThrough,
    _Out_ PIO_STATUS_BLOCK IoStatus
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

// ntosifs.h
VOID
NTAPI
CcUnregisterExternalCache (
    _In_ PVOID ExternalCacheContext
    )
{
    UNIMPLEMENTED_DBGBREAK;
}

NTSTATUS
NTAPI
CcWaitForCurrentLazyWriterActivity (
    VOID
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
CcZeroData (
    _In_ PFILE_OBJECT FileObject,
    _In_ PLARGE_INTEGER StartOffset,
    _In_ PLARGE_INTEGER EndOffset,
    _In_ BOOLEAN Wait
    )
{
    UNIMPLEMENTED_DBGBREAK;
    return FALSE;
}

//@ stub CcZeroDataOnDisk

/*! Internal Stuff ************************************************************/


BOOLEAN
NTAPI
CcInitializeCacheManager (
    VOID)
{
    UNIMPLEMENTED_DBGBREAK;
    return TRUE;
}

VOID
NTAPI
CcPfInitializePrefetcher (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
CcMdlReadComplete2 (
    IN PMDL MemoryDescriptorList,
    IN PFILE_OBJECT FileObject)
{
    UNIMPLEMENTED_DBGBREAK;
}


VOID
NTAPI
CcShutdownSystem (
    VOID)
{
    UNIMPLEMENTED_DBGBREAK;
}

