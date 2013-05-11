
#pragma once

namespace Mm {

static const ULONG_PTR LARGE_PAGE_SIZE = (4 * 1024 * 1024);
static const ULONG_PTR LARGE_PAGE_MASK = (~0x3FF);

/* Memory layout base addresses */
static const ULONG LOWEST_VAD_ADDRESS         = 0x00010000;
static const ULONG HIGHEST_USER_ADDRESS       = 0x7FFEFFFF;
static const ULONG USER_PROBE_ADDRESS         = 0x7FFF0000;
static const ULONG SYSTEM_RANGE_START         = 0x80000000;
static const ULONG PAGE_TABLE_BASE            = 0xC0000000;
static const ULONG HYPER_SPACE_START          = 0xC0400000;
static const ULONG HYPER_SPACE_END            = 0xC07FFFFF;
static const ULONG SHARED_SYSTEM_PAGE         = 0xFFC00000;
static const ULONG SYSTEM_CACHE_WS_START      = 0xC0C00000;
static const ULONG LOADER_MAPPINGS_START      = 0x80000000;
//static const ULONG64 PAGED_SYSTEM_START         = 0xFFFFF88000000000ULL;
static const ULONG PAGED_POOL_START           = 0xE1000000;
//static const ULONG64 PAGED_POOL_END             = 0xFFFFF8BFFFFFFFFFULL;
static const ULONG SESSION_SPACE_START        = 0xBD000000;
static const ULONG SESSION_VIEW_START         = 0xBE000000;
static const ULONG SESSION_VIEW_END           = 0xBF3FFFFF;
//static const ULONG64 SESSION_SPACE_END          = 0xFFFFF97FFFFFFFFFULL;
//static const ULONG64 SYSTEM_SPACE_START         = 0xFFFFF98000000000ULL;
static const ULONG PFN_DATABASE_ADDRESS       = 0xB0000000;
static const ULONG SYSTEM_RANGE_END           = 0xFFFFFFFF;
//static const ULONG64 HIGHEST_SYSTEM_ADDRESS     = 0xFFFFFFFFFFFFFFFFULL;

// HACK, we probably need to use defines for all!
#define SYSTEM_RANGE_START         0x80000000
#define HIGHEST_USER_ADDRESS       0x7FFEFFFF
#define USER_PROBE_ADDRESS         0x7FFF0000

static const PVOID MmHighestSystemAddress = (PVOID)SYSTEM_RANGE_END;

}; // namespace Mm
