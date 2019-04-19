#ifndef _M_AMD64

#define MI_MIN_PAGES_FOR_NONPAGED_POOL_TUNING   ((255 * _1MB) >> PAGE_SHIFT)
#define MI_MIN_PAGES_FOR_SYSPTE_TUNING          ((19 * _1MB) >> PAGE_SHIFT)
#define MI_MIN_PAGES_FOR_SYSPTE_BOOST           ((32 * _1MB) >> PAGE_SHIFT)
#define MI_MIN_PAGES_FOR_SYSPTE_BOOST_BOOST     ((256 * _1MB) >> PAGE_SHIFT)
#define MI_MAX_INIT_NONPAGED_POOL_SIZE          (128 * _1MB)
#define MI_MAX_NONPAGED_POOL_SIZE               (128 * _1MB)
#define MI_MAX_FREE_PAGE_LISTS                  4

#define MI_MIN_INIT_PAGED_POOLSIZE              (32 * _1MB)

#define MI_SESSION_VIEW_SIZE                    (20 * _1MB)
#define MI_SESSION_POOL_SIZE                    (16 * _1MB)
#define MI_SESSION_IMAGE_SIZE                   (8 * _1MB)
#define MI_SESSION_WORKING_SET_SIZE             (4 * _1MB)
#define MI_SESSION_SIZE                         (MI_SESSION_VIEW_SIZE + \
                                                 MI_SESSION_POOL_SIZE + \
                                                 MI_SESSION_IMAGE_SIZE + \
                                                 MI_SESSION_WORKING_SET_SIZE)

#define MI_SYSTEM_VIEW_SIZE                     (32 * _1MB)

#define MI_HIGHEST_USER_ADDRESS                 (PVOID)0x7FFEFFFF
#define MI_USER_PROBE_ADDRESS                   (PVOID)0x7FFF0000
#define MI_DEFAULT_SYSTEM_RANGE_START           (PVOID)0x80000000
#define MI_SYSTEM_CACHE_WS_START                (PVOID)0xC0C00000
#define MI_PAGED_POOL_START                     (PVOID)0xE1000000
#define MI_NONPAGED_POOL_END                    (PVOID)0xFFBE0000
#define MI_DEBUG_MAPPING                        (PVOID)0xFFBFF000

#define MI_SYSTEM_PTE_BASE                      (PVOID)MiAddressToPte(NULL)

#define MI_MIN_SECONDARY_COLORS                 8
#define MI_SECONDARY_COLORS                     64
#define MI_MAX_SECONDARY_COLORS                 1024

#define MI_MIN_ALLOCATION_FRAGMENT              (4 * _1KB)
#define MI_ALLOCATION_FRAGMENT                  (64 * _1KB)
#define MI_MAX_ALLOCATION_FRAGMENT              (2  * _1MB)

#define MM_HIGHEST_VAD_ADDRESS \
    (PVOID)((ULONG_PTR)MM_HIGHEST_USER_ADDRESS - (16 * PAGE_SIZE))
#define MI_LOWEST_VAD_ADDRESS                   (PVOID)MM_LOWEST_USER_ADDRESS

#define MI_DEFAULT_SYSTEM_PTE_COUNT             50000

#endif /* !_M_AMD64 */
