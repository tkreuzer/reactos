
#pragma once

#include "Kep.hpp"

// Windows 10 symbols
typedef enum _KHETERO_CPU_POLICY
{
    KHeteroCpuPolicyAll         = 0 /*0x0*/,
    KHeteroCpuPolicyLarge       = 1 /*0x1*/,
    KHeteroCpuPolicyLargeOrIdle = 2 /*0x2*/,
    KHeteroCpuPolicySmall       = 3 /*0x3*/,
    KHeteroCpuPolicySmallOrIdle = 4 /*0x4*/,
    KHeteroCpuPolicyDynamic     = 5 /*0x5*/,
    KHeteroCpuPolicyStaticMax   = 5 /*0x5*/,
    KHeteroCpuPolicyBiasedSmall = 6 /*0x6*/,
    KHeteroCpuPolicyBiasedLarge = 7 /*0x7*/,
    KHeteroCpuPolicyDefault     = 8 /*0x8*/,
    KHeteroCpuPolicyMax         = 9 /*0x9*/
} KHETERO_CPU_POLICY, *PKHETERO_CPU_POLICY;

typedef enum _KTHREAD_TAG {
    KThreadTagNone = 0,
    KThreadTagMediaBuffering,
    KThreadTagMax,
} KTHREAD_TAG, *PKTHREAD_TAG;

