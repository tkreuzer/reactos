
#pragma once

typedef enum _MEMORY_CACHING_TYPE_ORIG
{
    MmFrameBufferCached = 2
} MEMORY_CACHING_TYPE_ORIG;

typedef enum _MEMORY_CACHING_TYPE
{
    MmNonCached = FALSE,
    MmCached = TRUE,
    MmWriteCombined = MmFrameBufferCached,
    MmHardwareCoherentCached,
    MmNonCachedUnordered,
    MmUSWCCached,
    MmMaximumCacheType,
    MmNotMapped = -1
} MEMORY_CACHING_TYPE;

