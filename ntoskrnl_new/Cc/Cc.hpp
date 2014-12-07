
#pragma once

#include <ntoskrnl.h>
#include <Io/Io.hpp>

extern "C" {

// ntifs.h
typedef struct _CC_FILE_SIZES
{
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER FileSize;
    LARGE_INTEGER ValidDataLength;
} CC_FILE_SIZES, *PCC_FILE_SIZES;

typedef
BOOLEAN
(*PACQUIRE_FOR_LAZY_WRITE) (
    _In_ PVOID Context,
    _In_ BOOLEAN Wait);

typedef
VOID
(*PRELEASE_FROM_LAZY_WRITE) (
    _In_ PVOID Context);

typedef
BOOLEAN
(*PACQUIRE_FOR_READ_AHEAD) (
    _In_ PVOID Context,
    _In_ BOOLEAN Wait);

typedef
VOID
(*PRELEASE_FROM_READ_AHEAD) (
    _In_ PVOID Context);

typedef struct _CACHE_MANAGER_CALLBACKS
{
    PACQUIRE_FOR_LAZY_WRITE AcquireForLazyWrite;
    PRELEASE_FROM_LAZY_WRITE ReleaseFromLazyWrite;
    PACQUIRE_FOR_READ_AHEAD AcquireForReadAhead;
    PRELEASE_FROM_READ_AHEAD ReleaseFromReadAhead;
} CACHE_MANAGER_CALLBACKS, *PCACHE_MANAGER_CALLBACKS;

typedef struct _CACHE_UNINITIALIZE_EVENT
{
    struct _CACHE_UNINITIALIZE_EVENT *Next;
    KEVENT Event;
} CACHE_UNINITIALIZE_EVENT, *PCACHE_UNINITIALIZE_EVENT;

/* SharedCacheMap.cpp */

VOID
NTAPI
CcInitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ BOOLEAN PinAccess,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext);

BOOLEAN
NTAPI
CcUninitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_opt_ PLARGE_INTEGER TruncateSize,
    _In_opt_ PCACHE_UNINITIALIZE_EVENT UninitializeCompleteEvent);




} // extern "C"

