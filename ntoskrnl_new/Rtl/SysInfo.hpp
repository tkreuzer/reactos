
#pragma once

#include "Rtl.hpp"

typedef union _RTL_ELEVATION_FLAGS
{
    ULONG Flags;
    struct
    {
        ULONG ElevationEnabled          : 1;
        ULONG VirtualizationEnabled     : 1;
        ULONG InstallerDetectEnabled    : 1;
        ULONG ReservedBits              : 29;
    };
} RTL_ELEVATION_FLAGS, *PRTL_ELEVATION_FLAGS;

typedef struct _PS_PKG_CLAIM *PPS_PKG_CLAIM;

#if !defined(VRL_GLOBAL_LEVEL)
#define VRL_GLOBAL_LEVEL (SharedUserData->GlobalValidationRunlevel)
#endif // !defined(VRL_GLOBAL_LEVEL)

#if !defined(IS_VALIDATION_ENABLED)
#define IS_VALIDATION_ENABLED(C,L) ((L) & (C))
#define VRL_PREDEFINED_CLASS_BEGIN  (1 << 0)
#define VRL_CUSTOM_CLASS_BEGIN      (1 << 8)
#define VRL_CLASS_CONSISTENCY       (VRL_PREDEFINED_CLASS_BEGIN << 0)
#define VRL_ENABLE_KERNEL_BREAKS    (1 << 31)
#endif // !defined(IS_VALIDATION_ENABLED)

