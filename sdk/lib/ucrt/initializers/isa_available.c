//
// isa_available.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of __isa_available_init.
//
// SPDX-License-Identifier: MIT
//

#include <isa_availability.h>
#include <intrin.h>
#include <CpuId.h>

int __isa_available = 0;

int
__cdecl
__isa_available_init(void)
{
#if defined(_M_IX86) || defined(_M_X64)
    CPUID_SIGNATURE_REGS signature = { 0 };
    CPUID_VERSION_INFO_REGS versionInfo = { 0 };
    CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_REGS featureFlags = { 0 };

    // We assume that CPUID is supported on x86 and x64.
    __cpuid(signature.AsInt32, CPUID_SIGNATURE);

    if (signature.MaxLeaf >= CPUID_VERSION_INFO)
    {
        __cpuid(versionInfo.AsInt32, CPUID_VERSION_INFO);
    }

    if (signature.MaxLeaf >= CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS)
    {
        __cpuid(featureFlags.AsInt32, CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS);
    }

    if (featureFlags.AVX512F)
    {
        __isa_available = __ISA_AVAILABLE_AVX512;
    }
    else if (featureFlags.AVX2)
    {
        __isa_available = __ISA_AVAILABLE_AVX2;
    }
    else if (versionInfo.AVX)
    {
        __isa_available = __ISA_AVAILABLE_AVX;
    }
    else if (versionInfo.SSE42)
    {
        __isa_available = __ISA_AVAILABLE_SSE42;
    }
    else if (versionInfo.SSE2)
    {
        __isa_available = __ISA_AVAILABLE_SSE2;
    }
    else
    {
        __isa_available = __ISA_AVAILABLE_X86;
    }
#elif defined(_M_ARM) || defined(_M_ARM64))
    // TODO:
    // - What to check to determine if NEON is available?
#endif

    return 0;
}
