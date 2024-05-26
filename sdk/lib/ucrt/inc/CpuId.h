//
// CpuId.h
//
//      Copyright (c) 2024 Timo Kreuzer
//
// CPUID structure definitions for x86/x64 processors
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include <stdint.h>

#if !defined(_M_X64) && !defined(_M_IX86)
#error "Unsupported architecture"
#endif

#define CPUID_SIGNATURE 0x00
typedef union _CPUID_SIGNATURE_REGS
{
    int AsInt32[4];
    struct
    {
        uint32_t Eax;
        uint32_t Ebx;
        uint32_t Ecx;
        uint32_t Edx;
    };
    struct
    {
        uint32_t MaxLeaf; ///< [Bits 31:0] Maximum input value for CPUID instruction
        char Signature[12]; ///< [Bits 63:32] Processor signature (unordered)
    };
} CPUID_SIGNATURE_REGS;

#define CPUID_VERSION_INFO 0x01
typedef union _CPUID_VERSION_INFO_REGS
{
    int AsInt32[4];
    struct
    {
        uint32_t Eax;
        uint32_t Ebx;
        uint32_t Ecx;
        uint32_t Edx;
    };
    struct
    {
        // EAX:
        struct
        {
            uint32_t SteppingId       : 4; ///< [Bits   3:0] Stepping ID
            uint32_t Model            : 4; ///< [Bits   7:4] Model
            uint32_t FamilyId         : 4; ///< [Bits  11:8] Family
            uint32_t ProcessorType    : 2; ///< [Bits 13:12] Processor Type
            uint32_t Reserved1        : 2; ///< [Bits 15:14] Reserved
            uint32_t ExtendedModelId  : 4; ///< [Bits 19:16] Extended Model ID
            uint32_t ExtendedFamilyId : 8; ///< [Bits 27:20] Extended Family ID
            uint32_t Reserved2        : 4; ///< Reserved
        };

        // EBX:
        struct
        {
            uint32_t BrandIndex       : 8; ///< [Bits  7:0] Brand Index
            uint32_t CLFLUSHLineSize  : 8; ///< [Bits 15:8] CLFLUSH line size
            uint32_t MaxLogicalProcessors : 8; ///< [Bits 23:16] Maximum number of addressable IDs for logical processors in this physical package
            uint32_t InitialAPICId    : 8; ///< [Bits 31:24] Initial APIC ID
        };

        // ECX:
        struct
        {
            uint32_t SSE3             : 1; ///< [Bits   0:0] SSE3 instructions
            uint32_t PCLMULQDQ        : 1; ///< [Bits   1:1] PCLMULQDQ instruction
            uint32_t DTES64           : 1; ///< [Bits   2:2] 64-bit DS area
            uint32_t MONITOR          : 1; ///< [Bits   3:3] MONITOR/MWAIT instructions
            uint32_t DS_CPL           : 1; ///< [Bits   4:4] CPL qualified debug store
            uint32_t VMX              : 1; ///< [Bits   5:5] Virtual Machine eXtensions
            uint32_t SMX              : 1; ///< [Bits   6:6] Safer Mode Extensions
            uint32_t EIST             : 1; ///< [Bits   7:7] Enhanced Intel SpeedStep technology
            uint32_t TM2              : 1; ///< [Bits   8:8] Thermal Monitor 2
            uint32_t SSSE3            : 1; ///< [Bits   9:9] Supplemental SSE3 instructions
            uint32_t CNXT_ID          : 1; ///< [Bits  10:10] L1 Context ID
            uint32_t SDBG             : 1; ///< [Bits  11:11] Silicon Debug interface
            uint32_t FMA              : 1; ///< [Bits  12:12] Fused Multiply Add
            uint32_t CMPXCHG16B       : 1; ///< [Bits  13:13] CMPXCHG16B instruction
            uint32_t xTPR             : 1; ///< [Bits  14:14] Send Task Priority messages
            uint32_t PDCM             : 1; ///< [Bits  15:15] Perfmon and Debug Capability
            uint32_t Reserved3        : 1; ///< Reserved
            uint32_t PCID             : 1; ///< [Bits  17:17] Process-context identifiers
            uint32_t DCA              : 1; ///< [Bits  18:18] Direct Cache Access
            uint32_t SSE41            : 1; ///< [Bits  19:19] SSE4.1 instructions
            uint32_t SSE42            : 1; ///< [Bits  20:20] SSE4.2 instructions
            uint32_t x2APIC           : 1; ///< [Bits  21:21] x2APIC
            uint32_t MOVBE            : 1; ///< [Bits  22:22] MOVBE instruction
            uint32_t POPCNT           : 1; ///< [Bits  23:23] POPCNT instruction
            uint32_t TSC_DEADLINE     : 1; ///< [Bits  24:24] APIC supports one-shot operation using a TSC deadline value
            uint32_t AESNI            : 1; ///< [Bits  25:25] AESNI instruction extension
            uint32_t XSAVE            : 1; ///< [Bits  26:26] XSAVE/XRSTOR instructions
            uint32_t OSXSAVE          : 1; ///< [Bits  27:27] OS has set CR4.OSXSAVE
            uint32_t AVX              : 1; ///< [Bits  28:28] AVX instructions
            uint32_t F16C             : 1; ///< [Bits  29:29] 16-bit floating-point conversion instructions
            uint32_t RDRAND           : 1; ///< [Bits  30:30] RDRAND instruction
            uint32_t ParaVirtualized  : 1; ///< [Bits  31:31] Processor is Para-Virtualized
        };

        // EDX:
        struct
        {
            uint32_t FPU              : 1; ///< [Bits   0:0] Floating Point Unit on-chip
            uint32_t VME              : 1; ///< [Bits   1:1] Virtual 8086 Mode Enhancements
            uint32_t DE               : 1; ///< [Bits   2:2] Debugging Extensions
            uint32_t PSE              : 1; ///< [Bits   3:3] Page Size Extension
            uint32_t TSC              : 1; ///< [Bits   4:4] Time Stamp Counter
            uint32_t MSR              : 1; ///< [Bits   5:5] Model Specific Registers
            uint32_t PAE              : 1; ///< [Bits   6:6] Physical Address Extension
            uint32_t MCE              : 1; ///< [Bits   7:7] Machine Check Exception
            uint32_t CX8              : 1; ///< [Bits   8:8] CMPXCHG8 instruction
            uint32_t APIC             : 1; ///< [Bits   9:9] On-chip APIC hardware
            uint32_t Reserved4        : 1; ///< Reserved
            uint32_t SEP              : 1; ///< [Bits  11:11] SYSENTER/SYSEXIT instructions
            uint32_t MTRR             : 1; ///< [Bits  12:12] Memory Type Range Registers
            uint32_t PGE              : 1; ///< [Bits  13:13] Page Global Enable
            uint32_t MCA              : 1; ///< [Bits  14:14] Machine Check Architecture
            uint32_t CMOV             : 1; ///< [Bits  15:15] Conditional Move instructions
            uint32_t PAT              : 1; ///< [Bits  16:16] Page Attribute Table
            uint32_t PSE36            : 1; ///< [Bits  17:17] 36-bit Page Size Extension
            uint32_t PSN              : 1; ///< [Bits  18:18] Processor Serial Number
            uint32_t CLFSH            : 1; ///< [Bits  19:19] CLFL
            uint32_t Reserved5        : 1; ///< Reserved
            uint32_t DS               : 1; ///< [Bits  21:21] Debug Store
            uint32_t ACPI             : 1; ///< [Bits  22:22] Thermal Monitor and Software Controlled Clock Facilities
            uint32_t MMX              : 1; ///< [Bits  23:23] MMX instructions
            uint32_t FXSR             : 1; ///< [Bits  24:24] FXSAVE and FXRSTOR instructions
            uint32_t SSE              : 1; ///< [Bits  25:25] SSE instructions
            uint32_t SSE2             : 1; ///< [Bits  26:26] SSE2 instructions
            uint32_t SS               : 1; ///< [Bits  27:27] Self Snoop
            uint32_t HTT              : 1; ///< [Bits  28:28] Hyper-Threading Technology
            uint32_t TM               : 1; ///< [Bits  29:29] Thermal Monitor
            uint32_t Reserved6        : 1; ///< Reserved
            uint32_t PBE              : 1; ///< [Bits  31:31] Pending Break Enable
        };
    };
} CPUID_VERSION_INFO_REGS;

#define CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS 0x07
typedef union _CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_REGS
{
    int AsInt32[4];
    struct
    {
        uint32_t Eax;
        uint32_t Ebx;
        uint32_t Ecx;
        uint32_t Edx;
    };
    struct
    {
        // EAX:
        uint32_t MaxSubLeaf; ///< [Bits 31:0] Maximum sub-leaf supported in the processor

        // EBX:
        struct
        {
            uint32_t FSGSBASE         : 1; ///< [Bits   0:0] Access to base of %fs and %gs
            uint32_t IA32_TSC_ADJUST  : 1; ///< [Bits   1:1] IA32_TSC_ADJUST MSR
            uint32_t SGX              : 1; ///< [Bits   2:2] Software Guard Extensions
            uint32_t BMI1             : 1; ///< [Bits   3:3] Bit Manipulation Instruction Set 1
            uint32_t HLE              : 1; ///< [Bits   4:4] Hardware Lock Elision
            uint32_t AVX2             : 1; ///< [Bits   5:5] AVX2 instructions
            uint32_t FDP_EXCPTN_ONLY  : 1; ///< [Bits   6:6] x87 FPU Data Pointer updated only on x87 exceptions
            uint32_t SMEP             : 1; ///< [Bits   7:7] Supervisor Mode Execution Protection
            uint32_t BMI2             : 1; ///< [Bits   8:8] Bit Manipulation Instruction Set 2
            uint32_t EnhancedRepMovsb : 1; ///< [Bits   9:9] Fast REP MOVSB/STOSB
            uint32_t INVPCID          : 1; ///< [Bits  10:10] INVPCID instruction
            uint32_t RTM              : 1; ///< [Bits  11:11] Restricted Transactional Memory
            uint32_t RDT_M            : 1; ///< [Bits  12:12] Resource Director Technology Monitoring
            uint32_t DEPR_FPU_CS_DS   : 1; ///< [Bits  13:13] Deprecates FPU CS and FPU DS
            uint32_t MPX              : 1; ///< [Bits  14:14] Memory Protection Extensions
            uint32_t RDT_A            : 1; ///< [Bits  15:15] Resource Director Technology Allocation
            uint32_t AVX512F          : 1; ///< [Bits  16:16] AVX-
            uint32_t AVX512DQ         : 1; ///< [Bits  17:17] AVX-
            uint32_t RDSEED           : 1; ///< [Bits  18:18] RDSEED instruction
            uint32_t ADX              : 1; ///< [Bits  19:19] ADCX and ADOX instructions
            uint32_t SMAP             : 1; ///< [Bits  20:20] Supervisor Mode Access Prevention
            uint32_t AVX512IFMA       : 1; ///< [Bits  21:21] AVX-
            uint32_t Reserved         : 1; ///< Reserved
            uint32_t CLFLUSHOPT       : 1; ///< [Bits  23:23] CLFLUSHOPT instruction
            uint32_t CLWB             : 1; ///< [Bits  24:24] CLWB instruction
            uint32_t IntelPT          : 1; ///< [Bits  25:25] Intel Processor Trace
            uint32_t AVX512PF         : 1; ///< [Bits  26:26] AVX-
            uint32_t AVX512ER         : 1; ///< [Bits  27:27] AVX-
            uint32_t AVX512CD         : 1; ///< [Bits  28:28] AVX-
            uint32_t SHA              : 1; ///< [Bits  29:29] SHA instructions
            uint32_t AVX512BW         : 1; ///< [Bits  30:30] AVX-
            uint32_t AVX512VL         : 1; ///< [Bits  31:31] AVX-
        };

        // ECX:
        struct
        {
            uint32_t PREFETCHWT1      : 1; ///< [Bits   0:0] PREFETCHWT1 instruction
            uint32_t AVX512VBMI       : 1; ///< [Bits   1:1] AVX-
            uint32_t UMIP             : 1; ///< [Bits   2:2] User-Mode Instruction Prevention
            uint32_t PKU              : 1; ///< [Bits   3:3] Protection Keys for User-mode pages
            uint32_t OSPKE            : 1; ///< [Bits   4:4] OS Protection Keys Enable
            uint32_t Reserved8        : 8; ///< Reserved
            uint32_t TME_EN           : 1;
            uint32_t AVX512_VPOPCNTDQ : 1;
            uint32_t Reserved7        : 1;
            uint32_t FiveLevelPage    : 1;
            uint32_t MAWAU            : 5;
            uint32_t RDPID            : 1;
            uint32_t Reserved3        : 7;
            uint32_t SGX_LC           : 1;
            uint32_t Reserved4        : 1;
        };
    };
} CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_REGS;
