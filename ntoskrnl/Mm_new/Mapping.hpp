

#pragma once

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
NTAPI
MiMapPhysicalMemory (
    _In_ PFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ ULONG Protect,
    _In_ MEMORY_CACHING_TYPE CacheType);

