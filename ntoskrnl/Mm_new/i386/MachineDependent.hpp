
#pragma once

namespace Mm {

static const ULONG_PTR LARGE_PAGE_SIZE = (4 * 1024 * 1024);
static const ULONG_PTR LARGE_PAGE_MASK = (~0x3FF);

/*

x86-PAE
00000000 - 7FFFFFFF     2 GB    UserModeVaSpace
80000000 - 81000000     16 MB   LoaderMappingsVaSpace
81000000 - 817FFFFF      8 MB   NonPagedSystemVaSpace (PFN-DB, NPPool)
81800000 - BAFFFFFF     920 MB  ??? free
BB000000 - BBFFFFFF     16 MB   SystemViewVaSpace
BC000000 - BFFFFFFF     64 MB   SessionVaSpace
C0000000 - C07FFFFF     8 MB    PageTableVaSpace
C0800000 - C0DFFFFF     6 MB    ProcessVaSpace (HyperSpace)
C0E00000 - C1200000     4 MB    ???
C1200000 - E0FFFFFF     510 MB  SystemCacheVaSpace
e1000000 - ECDFFFFF     190 MB  Paged Pool
ECE00000 - FFBFFFFF     302 MB  NonPagedSystemVaSpace(SysPTEs, NPPool Exp)
FFC00000 - FFFFFFFF     4 MB    HalVaSpace

LoaderMappings:     -8 MB
SystemCache:        -84 MB
SessionSpace:       -16 MB
SystemView:         +8 MB
ProcessVaSpace:     +4 MB

x86-PAE/3GB
00000000 - BFFFFFFF     3 GB    UserModeVaSpace
C0000000 - C07FFFFF     8 MB    PageTableVaSpace
C0800000 - C11FFFFF     10 MB   ProcessVaSpace (HyperSpace)
C1200000 - C15FFFFF     4 MB    ???
C1600000 - DBFFFFFF     426 MB  SystemCacheVaSpace
DC000000 - DEFFFFFF     48 MB   SessionVaSpace
DF000000 - DFFFFFFF     16 MB   SystemViewVaSpace
E0000000 - E0FFFFFF     16 MB   LoaderMappingsVaSpace
E1000000 - ED1FFFFF     194 MB  PagedSystemVaSpace
ED200000 - FFBFFFFF     298 MB  NonPagedSystemVaSpace (SysPTEs, PFN-DB, NPPool)
FFC00000 - FFFFFFFF     4 MB    HalVaSpace

bei 4GB mem:
00000000 - BFFFFFFF     3 GB    UserModeVaSpace
C0000000 - C07FFFFF     8 MB    PageTableVaSpace
C0800000 - C11FFFFF     10 MB   ProcessVaSpace (HyperSpace)
C1200000 - C15FFFFF     4 MB    ???
C1600000 - DBDFFFFF     424 MB  SystemCacheVaSpace
DBE00000 - DEDFFFFF     48 MB   SessionVaSpace
DEE00000 - DFDFFFFF     16 MB   SystemViewVaSpace
DFE00000 - DFFFFFFF     2 MB    ???
E0000000 - E0FFFFFF     18 MB   LoaderMappingsVaSpace
E1200000 - F05FFFFF     244 MB  PagedSystemVaSpace
F0600000 - FFBFFFFF     246 MB  NonPagedSystemVaSpace (SysPTEs, PFN-DB, NPPool)
FFC00000 - FFFFFFFF     4 MB    HalVaSpace

----

1 GB
C0000000 - C07FFFFF     8 MB    PageTableVaSpace
C0800000 - C11FFFFF     10 MB   ProcessVaSpace (HyperSpace)
C1200000 - C41FFFFF     48 MB   SessionVaSpace
446 MB
E0000000 - E0FFFFFF     18 MB   LoaderMappingsVaSpace
490 MB
FFC00000 - FFFFFFFF     4 MB    HalVaSpace

----

00000000 - BFFFFFFF     3 GB    UserModeVaSpace
C0000000 - C07FFFFF     8 MB    PageTableVaSpace
C0800000 - C11FFFFF     10 MB   ProcessVaSpace (HyperSpace)
C1200000 - C41FFFFF     48 MB   SessionVaSpace

C4200000 - DFFFFFFF ???

E0000000 - E0FFFFFF     16 MB   LoaderMappingsVaSpace
E1000000 - ????????     256 MB  PagedSystemVaSpace
F1000000 - FFBFFFFF     240 MB  NonPagedSystemVaSpace
FFC00000 - FFFFFFFF     4 MB    HalVaSpace

2 GB userspace
1 GB ?


    if (Address < MmSystemRangeStart)
    {
        return UserModeVaSpace;
    }
    else if (Address < MiLoaderMappingsVaSpaceStart)
    {
        if (Address < MiSessionVaSpaceStart)
        {
            if (Address < MiPagedSystemVaSpaceStart)
            {
                return ProcessVaSpace;
            }
            else
            {
                return SystemCacheVaSpace;
            }
        }
        else
        {
            if (Address < MiSystemViewVaSpaceStart)
            {
                return SessionVaSpace;
            }
            else
            {
                return SystemViewVaSpace;
            }
        }
    }
    else
    {
        if (Address < MiNonPagedSystemVaSpaceStart)
        {
            if (Address < MiPagedSystemVaSpaceStart)
            {
                return LoaderMappingsVaSpace;
            }
            else
            {
                return PagedSystemVaSpace;
            }
        }
        else
        {
            if (Address < MiHalVaSpaceStart)
            {
                return NonPagedSystemVaSpace;
            }
            else
            {
                return HalVaSpace;
            }
        }
    }

*/

/* Memory layout base addresses */
enum _ADDRESS_SPACE
{
    LOWEST_VAD_ADDRESS         = 0x00010000,
    HIGHEST_USER_ADDRESS       = 0x7FFEFFFF,
    USER_PROBE_ADDRESS         = 0x7FFF0000,
    SYSTEM_RANGE_START         = 0x80000000,
    LOADER_MAPPINGS_START      = 0x80000000,
    PFN_DATABASE_ADDRESS       = 0xB0000000,
    SESSION_SPACE_START        = 0xBD000000,
    SESSION_VIEW_START         = 0xBE000000,
    SESSION_VIEW_END           = 0xBF3FFFFF,
    SYSTEM_RANGE_START_3GB     = 0xC0000000,
    PAGE_TABLE_BASE            = 0xC0000000,
    HYPER_SPACE_START          = 0xC0400000,
    HYPER_SPACE_END            = 0xC07FFFFF,
    SYSTEM_CACHE_WS_START      = 0xC0C00000,
    LOADER_MAPPINGS_START_3GB  = 0xE0000000,
//static const ULONG64 PAGED_SYSTEM_START         = 0xFFFFF88000000000ULL;
    PAGED_POOL_START           = 0xE1000000,
//static const ULONG64 PAGED_POOL_END             = 0xFFFFF8BFFFFFFFFFULL;
//static const ULONG64 SESSION_SPACE_END          = 0xFFFFF97FFFFFFFFFULL;
//static const ULONG64 SYSTEM_SPACE_START         = 0xFFFFF98000000000ULL;
    SHARED_SYSTEM_PAGE         = 0xFFC00000,
    HAL_VA_START               = 0xFFC00000,
#ifdef __linux__
    SYSTEM_RANGE_END           = 0xBFFFFFFF,
#else
    SYSTEM_RANGE_END           = 0xFFFFFFFF,
#endif
//static const ULONG64 HIGHEST_SYSTEM_ADDRESS     = 0xFFFFFFFFFFFFFFFFULL;
};

// HACK, we probably need to use defines for all!
#define SYSTEM_RANGE_START         0x80000000
#define HIGHEST_USER_ADDRESS       0x7FFEFFFF
#define USER_PROBE_ADDRESS         0x7FFF0000

static const PVOID MmHighestSystemAddress = (PVOID)SYSTEM_RANGE_END;

}; // namespace Mm
