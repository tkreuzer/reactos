/*
* PROJECT:     ReactOS SDK
* LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
* FILE:        skd/include/reactos/cpuid.h
* PURPOSE:     CPUID definitions
* PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
*/

// See Intel®_64_and_IA-32_Architectures_Software_Developer_Manuals/325462-sdm-vol-1-2abcd-3abcd.pdf, chapter 3-210
// See AMD CPUID Specification: https://www.amd.com/en/support/tech-docs/cpuid-specification

#pragma once

typedef struct _CPUID_REGISTERS
{
    unsigned int Eax;
    unsigned int Ebx;
    unsigned int Ecx;
    unsigned int Edx;
} CPUID_REGISTERS;

/* Basic CPUID Information */
typedef union _CPUID_00
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        unsigned int LFuncStd;
        char Vendor[12]; // Shuffled! Proper order is EBX,EDX,ECX
    };
} CPUID_00;

#define CPUID_VENDOR_OLDAMD       "AMDisbetter!" // Early engineering samples of AMD K5 processor
#define CPUID_VENDOR_AMD          "AuthenticAMD" // AMD
#define CPUID_VENDOR_CENTAUR      "CentaurHauls" // IDT WinChip/Centaur (Including some VIA CPU)
#define CPUID_VENDOR_CYRIX        "CyrixInstead" // Cyrix/early STMicroelectronics and IBM
#define CPUID_VENDOR_INTEL        "GenuineIntel" // Intel
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86" // Transmeta
#define CPUID_VENDOR_NEXGEN       "NexGenDriven" // NexGen
#define CPUID_VENDOR_UMC          "UMC UMC UMC " // UMC
#define CPUID_VENDOR_SIS          "SiS SiS SiS " // SiS
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU" // Transmeta
#define CPUID_VENDOR_NSC          "Geode by NSC" // National Semiconductor
#define CPUID_VENDOR_RISE         "RiseRiseRise" // Rise
#define CPUID_VENDOR_VORTEX       "Vortex86 SoC" // DM&P Vortex
#define CPUID_VENDOR_VIA          "VIA VIA VIA " // VIA
#define CPUID_VENDOR_ZHAOXIN      "  Shanghai  " // Zhaoxin
#define CPUID_VENDOR_HYGON        "HygonGenuine" // Hygon
#define CPUID_VENDOR_ELBRUS       "E2K MACHINE"  // MCST Elbrus

// The following are ID strings used by open source soft CPU cores:
#define CPUID_VENDOR_AO486        "GenuineAO486" // ao486 CPU
#define CPUID_VENDOR_V586         CPUID_VENDOR_INTEL // v586 core (this is identical to the Intel ID string)

/* Vendor-strings from Virtual Machines */
#define CPUID_VENDOR_VMWARE       "VMwareVMware" // VMware
#define CPUID_VENDOR_XENHVM       "XenVMMXenVMM" // Xen HVM
#define CPUID_VENDOR_MICROSOFT_HV "Microsoft Hv" // Microsoft Hyper-V or Windows Virtual PC
#define CPUID_VENDOR_PARALLELS    " lrpepyh  vr" // Parallels (becomes "prl hyperv  " when changing endianness)
#define CPUID_VENDOR_BHYVE        "bhyve bhyve " // bhyve
#define CPUID_VENDOR_KVM          " KVMKVMKVM  " // KVM
#define CPUID_VENDOR_QEMU         "TCGTCGTCGTCG" // QEMU
#define CPUID_VENDOR_ACRN         "ACRNACRNACRN" // Project ACRN
#define CPUID_VENDOR_QNX          " QNXQVMBSQG " // QNX Hypervisor
#define CPUID_VENDOR_ROSETTA      CPUID_VENDOR_INTEL // Apple Rosetta 2[7]

/* CPU model and features */
typedef union _CPUID_01
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int Stepping : 4;          // EAX[3:0]
        unsigned int Model : 4;             // EAX[7:4] BaseModel
        unsigned int Family : 4;            // EAX[11:8] BaseFamily
        unsigned int ProcessorType : 2;     // EAX[13:12]
        unsigned int Reserved1 : 2;         // EAX[15:14]
        unsigned int ExtendedModel : 4;     // EAX[19:16]
        unsigned int ExtendedFamily : 8;    // EAX[27:20
        unsigned int Reserved2 : 4;         // EAX[31:28]

        /* EBX */
        unsigned int BrandIndex : 8;            // EBX[7:0]
        unsigned int CLFlush : 8;               // EBX[15:8]
        unsigned int LogicalProcessorCount : 8; // EBX[23:16]
        unsigned int InitialApicId : 8;         // EBX[32:24] //  (LocalApicId)

        /* ECX */
        unsigned int SSE3 : 1;              // ECX[0] Streaming SIMD Extensions 3 (SSE3)
        unsigned int PCLMULQDQ : 1;         // ECX[1] PCLMULQDQ instruction
        unsigned int DTES64 : 1;            // ECX[2] Intel: 64-bit DS Area
        unsigned int MONITOR : 1;           // ECX[3] MONITOR/MWAIT instructions
        unsigned int DS_CPL : 1;            // ECX[4] Intel: CPL Qualified Debug Store
        unsigned int VMX : 5;               // ECX[5] Intel: Virtual Machine Extensions
        unsigned int SMX : 1;               // ECX[6] Intel: Safer Mode Extensions
        unsigned int EIST : 1;              // ECX[7] Intel: Enhanced Intel SpeedStep® technology
        unsigned int TM2 : 1;               // ECX[8] Intel: Thermal Monitor 2
        unsigned int SSSE3 : 1;             // ECX[9] 
        unsigned int CNXT_ID : 1;           // ECX[10] Intel: L1 Context ID.
        unsigned int SDBG : 1;              // ECX[11] Intel: 
        unsigned int FMA : 1;               // ECX[12]
        unsigned int CMPXCHG16B : 1;        // ECX[13] CMPXCHG16B Available
        unsigned int xTPRUpdateControl : 1; // ECX[14] Intel: xTPR Update Control
        unsigned int PDCM : 1;              // ECX[15] Intel: Perfmon and Debug Capability
        unsigned int Reserved3 : 1;         // ECX[16] 
        unsigned int PCID : 1;              // ECX[17] Intel: Process-context identifiers
        unsigned int DCA : 1;               // ECX[18] Intel: RDSEED?
        unsigned int SSE4_1 : 1;            // ECX[19]
        unsigned int SSE4_2 : 1;            // ECX[20]
        unsigned int x2APIC : 1;            // ECX[21]
        unsigned int MOVBE : 1;             // ECX[22]
        unsigned int POPCNT : 1;            // ECX[23]
        unsigned int TSCDeadline : 1;       // ECX[24] Intel: APIC timer supports one-shot operation using a TSC deadline value.
        unsigned int AESNI : 1;             // ECX[25] CPU Supports the AESNI instruction extensions (aka AES)
        unsigned int XSAVE : 1;             // ECX[26] CPU supports the XSAVE/XRSTOR, XSETBV/XGETBV, and XCR0
        unsigned int OSXSAVE : 1;           // ECX[27] The OS has set CR4.OSXSAVE[bit 18] to enable XSETBV/XGETBV instructions
        unsigned int AVX : 1;               // ECX[28] AVX instruction extensions
        unsigned int F16C : 1;              // ECX[29] CPU supports 16-bit floating-point conversion instructions
        unsigned int RDRAND : 1;            // ECX[30] CPU supports RDRAND instruction
        unsigned int Reserved4 : 1;         // ECX[31]

        /* EDX */
        unsigned int FPU : 1;               // EDX[0] Floating Point Unit On-Chip
        unsigned int VME : 1;               // EDX[1] Virtual 8086 Mode Enhancements
        unsigned int DE : 1;                // EDX[2] Debugging Extensions
        unsigned int PSE : 1;               // EDX[3] Page Size Extension
        unsigned int TSC : 1;               // EDX[4] Time Stamp Counter
        unsigned int MSR : 1;               // EDX[5] Model Specific Registers RDMSR and WRMSR Instructions
        unsigned int PAE : 1;               // EDX[6] Physical Address Extension
        unsigned int MCE : 1;               // EDX[7] Machine Check Exception
        unsigned int CX8 : 1;               // EDX[8] CMPXCHG8B Instruction
        unsigned int APIC : 1;              // EDX[9] APIC On - Chip
        unsigned int Reserved5 : 1;         // EDX[10]
        unsigned int SEP : 1;               // EDX[11] SYSENTER and SYSEXIT Instructions
        unsigned int MTRR : 1;              // EDX[12] Memory Type Range Registers
        unsigned int PGE : 1;               // EDX[13] Page Global Bit
        unsigned int MCA : 1;               // EDX[14] Machine Check Architecture
        unsigned int CMOV : 1;              // EDX[15] Conditional Move Instructions
        unsigned int PAT : 1;               // EDX[16] Page Attribute Table
        unsigned int PSE_36 : 1;            // EDX[17] 36 - Bit Page Size Extension
        unsigned int PSN : 1;               // EDX[18] Processor Serial Number
        unsigned int CLFSH : 1;             // EDX[19] CLFLUSH Instruction
        unsigned int Reserved6 : 1;         // EDX[20]
        unsigned int DS : 1;                // EDX[21] Debug Store
        unsigned int ACPI : 1;              // EDX[22] Thermal Monitorand Software Controlled Clock Facilities
        unsigned int MMX : 1;               // EDX[23] MMX Technology
        unsigned int FXSR : 1;              // EDX[24] FXSAVE and FXRSTOR Instructions
        unsigned int SSE : 1;               // EDX[25] SSE
        unsigned int SSE2 : 1;              // EDX[26] SSE 2
        unsigned int SS : 1;                // EDX[27] Self Snoop
        unsigned int HTT : 1;               // EDX[28] Max APIC IDs reserved field is Valid
        unsigned int TM : 1;                // EDX[29] Thermal Monitor
        unsigned int Reserved7 : 1;         // EDX[30]
        unsigned int PBE : 1;               // EDX[31] Pending Break Enable
    };
} CPUID_01;

/* Cache and TLB Information */
typedef union _CPUID_02
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int EaxFields : 31; // EAX[30:0]
        unsigned int EaxInvalid : 1; // EAX[31]

        /* EBX */
        unsigned int EbxFields : 31; // EBX[30:0]
        unsigned int EbxInvalid : 1; // EBX[31]

        /* ECX */
        unsigned int EcxFields : 31; // ECX[30:0]
        unsigned int EcxInvalid : 1; // ECX[31]

        /* EDX */
        unsigned int EdxFields : 31; // EDX[30:0]
        unsigned int EdxInvalid : 1; // EDX[31]
    };
    struct
    {
        unsigned char CacheDescriptors[16]; // First one always returns 1
    };
    struct
    {
        unsigned char EaxCacheDescriptors[4]; // First one always returns 1
        unsigned char EbxCacheDescriptors[4];
        unsigned char EcxCacheDescriptors[4];
        unsigned char EdxCacheDescriptors[4];
    };
} CPUID_02;

/* Processor serial number (PSN)
 * Not supported in the Pentium 4 processor or later.
 * On all models, use the PSN flag (returned using CPUID) to check for PSN support before accessing the feature.
 */
typedef union _CPUID_03
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int Reserved1;

        /* EBX */
        unsigned int Reserved2;

        /* ECX */
        unsigned long ProcessorSerialNumber_00_31;

        /* EDX */
        unsigned long ProcessorSerialNumber_32_63;
    };
} CPUID_03;

/* Intel: Deterministic Cache Parameters Leaf for aach level.
 * Leaf 04H output depends on the initial value in ECX. 
 */
typedef union _CPUID_04
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int CacheType : 5; // EAX[4:0] Cache Type Field. (0 = No more caches, 1 = Data Cache, 2 = Instruction Cache, 3 = Unified Cache, 4-31 = Reserved)
        unsigned int CacheLevel : 3; // EAX[7:5] Cache Level(starts at 1).
        unsigned int SelfInitCacheLevel : 1; // EAX[8] Self Initializing cache level(does not need SW initialization).
        unsigned int FullyAssociativeCache : 1; // EAX[9] Fully Associative cache.
        unsigned int Reserved : 4; // EAX[13:10] Reserved.
        unsigned int MaxAddressableIds : 12; // EAX[25:14] Maximum number of addressable IDs for logical processors sharing this cache
        unsigned int MaxAddressableIds : 6; // EAX[31:26] Maximum number of addressable IDs for processor cores in the physical package

        /* EBX */
        unsigned int L : 12; // EBX[11:00] System Coherency Line Size
        unsigned int P : 10; // EBX[21:12] Physical Line partitions
        unsigned int W : 10; // EBX[31:22] Ways of associativity

        /* ECX */
        unsigned int S; // ECX[31:0] Number of Sets

        /* EDX */
        unsigned int WriteBackInvalidate : 1; // EDX[0] Write - Back Invalidate / Invalidate.
            // 0 = WBINVD/INVD from threads sharing this cache acts upon lower level caches for threads sharing this cache.
            // 1 = WBINVD/INVD is not guaranteed to act upon lower level caches of non-originating threads sharing this cache.
        unsigned int CacheInclusiveness : 1; // EDX[1] Cache Inclusiveness.
            // 0 = Cache is not inclusive of lower cache levels.
            // 1 = Cache is inclusive of lower cache levels.
        unsigned int ComplexCacheIndexing : 1; // EDX[2] Complex Cache Indexing.
            // 0 = Direct mapped cache.
            // 1 = A complex function is used to index the cache, potentially using all address bits.
        unsigned int Reserved : 29; // EDX[31:3] Reserved = 0.
    };
} CPUID_04;

/* MONITOR and MWAIT Features
 * NOTE: The definition of C0 through C7 states for MWAIT extension are processor-specific C-states, not ACPI Cstates
*/
typedef union _CPUID_05
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int MonLineSizeMin : 16; // EAX[15:0] Smallest monitor-line size in bytes (default is processor's monitor granularity).
        unsigned int Reserved1 : 16; // EAX[31:16] Reserved = 0.

        /* EBX */
        unsigned int MonLineSizeMax : 16; // EBX[15:0] Largest monitor-line size in bytes (default is processor's monitor granularity).
        unsigned int Reserved2 : 16; // EBX[31:16] Reserved = 0.

        /* ECX */
        unsigned int EMX : 1; // ECX[0] Enumeration of Monitor-Mwait extensions (beyond EAX and EBX registers) supported.
        unsigned int IBE : 1; // ECX[1] Supports treating interrupts as break-event for MWAIT, even when interrupts disabled.
        unsigned int Reserved3 : 30; // ECX[31:2] Reserved. 

        /* EDX */
        unsigned int NumC0SubStates : 4; // EDX[3:0] Number of C0* sub C-states supported using MWAIT.
        unsigned int NumC1SubStates : 4; // EDX[7:4] Number of C1* sub C-states supported using MWAIT.
        unsigned int NumC2SubStates : 4; // EDX[11:8] Number of C2* sub C-states supported using MWAIT.
        unsigned int NumC3SubStates : 4; // EDX[15:12] Number of C3* sub C-states supported using MWAIT.
        unsigned int NumC4SubStates : 4; // EDX[19:16] Number of C4* sub C-states supported using MWAIT.
        unsigned int NumC5SubStates : 4; // EDX[23:20] Number of C5* sub C-states supported using MWAIT.
        unsigned int NumC6SubStates : 4; // EDX[27:24] Number of C6* sub C-states supported using MWAIT.
        unsigned int NumC7SubStates : 4; // EDX[31:28] Number of C7* sub C-states supported using MWAIT.
    };
} CPUID_05;

// Thermal and Power Management Features
typedef union _CPUID_06
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int SigitalTemperatureSensor : 1; // EAX[0] Digital temperature sensor is supported if set.
        unsigned int TurboBoot : 1; // EAX[1] Intel Turbo Boost Technology Available (see description of IA32_MISC_ENABLE[38]).
        unsigned int ARAT : 1; // EAX[2] APIC-Timer-always-running feature is supported if set.
        unsigned int Reserved1 : 1; // EAX[3] Reserved.
        unsigned int PLN : 1; // EAX[4] Power limit notification controls are supported if set.
        unsigned int ECMD : 1; // EAX[5] Clock modulation duty cycle extension is supported if set.
        unsigned int PTM : 1; // EAX[6] Package thermal management is supported if set.
        unsigned int HWP : 1; // EAX[7] HWP base registers (IA32_PM_ENABLE[bit 0], IA32_HWP_CAPABILITIES, IA32_HWP_REQUEST, IA32_HWP_STATUS) are supported if set.
        unsigned int HWP_Notification : 1; // EAX[8] IA32_HWP_INTERRUPT MSR is supported if set.
        unsigned int HWP_ActivityWindow : 1; // EAX[9] IA32_HWP_REQUEST[bits 41:32] is supported if set.
        unsigned int HWP_EnergyPerformancePreference : 1; // EAX[10] IA32_HWP_REQUEST[bits 31:24] is supported if set.
        unsigned int HWP_PackageLevelRequest : 1; // EAX[11] IA32_HWP_REQUEST_PKG MSR is supported if set.
        unsigned int Reserved : 1; // EAX[12] Reserved.
        unsigned int HDC : 1; // EAX[13] HDC base registers IA32_PKG_HDC_CTL, IA32_PM_CTL1, IA32_THREAD_STALL MSRs are supported if set.
        unsigned int Reserved2 : 17; // EAX[31:15] Reserved.

        /* EBX */
        unsigned int NIT : 4; // EBX[3:0] Number of Interrupt Thresholds in Digital Thermal Sensor.
        unsigned int Reserved3 : 28; // EBX[31:4] Reserved.

        /* ECX */
        unsigned int HCFC : 1; // ECX[0] Hardware Coordination Feedback Capability (Presence of IA32_MPERF and IA32_APERF).
        unsigned int Reserved4 : 2; // ECX[2:1] Reserved = 0.
        unsigned int PEBP : 1; // ECX[3] The processor supports performance-energy bias preference if CPUID.06H:ECX.SETBH[bit 3] is set
            // and it also implies the presence of a new architectural MSR called IA32_ENERGY_PERF_BIAS (1B0H).
        unsigned int Reserved5 : 28; // ECX[31:4] Reserved = 0.

        /* EDX */
        unsigned int Reserved6; // EDX[31:0] Reserved = 0
    };
} CPUID_06;

/* Structured Extended Feature Enumeration Information Sub-leaf 0 (Input ECX = 0) */
typedef union _CPUID_07_00
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int MaxSubLeaf;    // EAX[31:0] Reports the maximum input value for supported leaf 7 sub-leaves.

        /* EBX */
        unsigned int FSGSBASE : 1;  // EBX[0] Supports RDFSBASE / RDGSBASE / WRFSBASE / WRGSBASE if 1.
        unsigned int TSC_ADJUST : 1;// EBX[1] IA32_TSC_ADJUST MSR is supported if 1.
        unsigned int SGX : 1;       // EBX[2] Supports Intel® Software Guard Extensions(Intel® SGX Extensions) if 1.
        unsigned int BMI1 : 1;      // EBX[3] BMI1. Bit manipulation instruction support.
        unsigned int HLE : 1;       // EBX[4] HLE.
        unsigned int AVX2 : 1;      // EBX[5] AVX2.
        unsigned int FDP_EXCPTN_ONLY : 1; // EBX[6] x87 FPU Data Pointer updated only on x87 exceptions if 1.
        unsigned int SMEP : 1;      // EBX[7] SMEP. Supports Supervisor-Mode Execution Prevention if 1.
        unsigned int BMI2 : 1;      // EBX[8] BMI2.
        unsigned int EREPMOVSB : 1; // EBX[9] Supports Enhanced REP MOVSB/STOSB if 1.
        unsigned int INVPCID : 1;   // EBX[10] INVPCID. If 1, supports INVPCID instruction for system software that manages process-context identifiers.
        unsigned int RTM : 1;       // EBX[11]: RTM.
        unsigned int RDT_M : 1;     // EBX[12] Supports Intel® Resource Director Technology (Intel® RDT) Monitoring capability if 1.
        unsigned int DepFPUCSDS : 1;// EBX[13] Deprecates FPU CS and FPU DS values if 1.
        unsigned int MPX : 1;       // EBX[14] Supports Intel® Memory Protection Extensions if 1.
        unsigned int RDT_A : 1;     // EBX[15] Supports Intel® Resource Director Technology (Intel® RDT) Allocation capability if 1.
        unsigned int Reserved1 : 2; // EBX[17:16] Reserved.
        unsigned int RDSEED : 1;    // EBX[18] RDSEED.
        unsigned int ADX : 1;       // EBX[19] ADX.
        unsigned int SMAP : 1;      // EBX[20] Supports Supervisor-Mode Access Prevention (and the CLAC/STAC instructions) if 1.
        unsigned int Reserved2 : 2; // EBX[[22:21] Reserved.
        unsigned int CLFLUSHOPT : 1;// EBX[23] CLFLUSHOPT.
        unsigned int CLWB : 1;      // EBX[24] CLWB.
        unsigned int PT : 1;        // EBX[25] Intel Processor Trace.
        unsigned int Reserved3 : 3; // EBX[28:26] Reserved.
        unsigned int SHA : 1;       // EBX[29] Supports Intel® Secure Hash Algorithm Extensions (Intel® SHA Extensions) if 1.
        unsigned int Reserved4 : 2; // EBX[31:30] Reserved.

        /* ECX */
        unsigned int PREFETCHWT1 : 1; // ECX[0] PREFETCHWT1.
        unsigned int Reserved5 : 1; // ECX[1] Reserved.
        unsigned int UMIP : 1;      // ECX[2] UMIP. Supports user-mode instruction prevention if 1.
        unsigned int PKU : 1;       // ECX[3] PKU. Supports protection keys for user-mode pages if 1.
        unsigned int OSPKE : 1;     // ECX[4] OSPKE. If 1, OS has set CR4.PKE to enable protection keys (and the RDPKRU/WRPKRU instructions).
        unsigned int Reserved6 : 12;// ECX[16:5] Reserved.
        unsigned int MAWAU : 5;     // ECX[21:17] The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode.
        unsigned int RDPID : 1;     // ECX[22] RDPID. Supports Read Processor ID if 1.
        unsigned int Reserved7 : 1; // ECX[29:23] Reserved.
        unsigned int SGX_LC : 1;    // ECX[30] SGX_LC. Supports SGX Launch Configuration if 1.
        unsigned int Reserved8 : 1; // ECX[31] Reserved.

        /* EDX */
        unsigned int Reserved9;     // EDX[31:0] Reserved.
    };
} CPUID_07_00;

/* Direct Cache Access Information */
typedef union _CPUID_09
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int PLATFORM_DCA_CAP;  // EAX[31:0] Value of bits [31:0] of IA32_PLATFORM_DCA_CAP MSR (address 1F8H).

        /* EBX */
        unsigned int Reserved1;         // EBX[31:0] Reserved.

        /* ECX */
        unsigned int Reserved2;         // ECX[31:0] Reserved.

        /* EDX */
        unsigned int Reserved3;         // EDX[31:0] Reserved. 
    };
} CPUID_09;

/* Architectural Performance Monitoring Features */
typedef union _CPUID_0A
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int VersionID : 8;     // EAX[7:0] Version ID of architectural performance monitoring.
        unsigned int NGPPMC : 8;        // EAX[15:8] Number of general-purpose performance monitoring counter per logical processor.
        unsigned int BWGPPME : 8;       // EAX[23:16] Bit width of general-purpose, performance monitoring counter.
        unsigned int VectorLength : 8;  // EAX[31:24] Length of EBX bit vector to enumerate architectural performance monitoring events.

        /* EBX */
        unsigned int NoCCE : 1;         // EBX[0] Core cycle event not available if 1.
        unsigned int NoIRE : 1;         // EBX[1] Instruction retired event not available if 1.
        unsigned int NoRCE : 1;         // EBX[2] Reference cycles event not available if 1.
        unsigned int NoLLCRE : 1;       // EBX[3] Last-level cache reference event not available if 1.
        unsigned int NoLLCME : 1;       // EBX[4] Last-level cache misses event not available if 1.
        unsigned int NoBIRE : 1;        // EBX[5] Branch instruction retired event not available if 1.
        unsigned int NoBMPE : 1;        // EBX[6] Branch mispredict retired event not available if 1.
        unsigned int Reserved1 : 25;    // EBX[31:7] Reserved = 0.

        /* ECX */
        unsigned int Reserved2;         // ECX[31:0] Reserved = 0.

        /* EDX */
        unsigned int NumFixedPC : 5;    // EDX[4:0] Number of fixed-function performance counters (if Version ID > 1).
        unsigned int WidthFixedPC : 8;  // EDX[12:5] Bit width of fixed-function performance counters (if Version ID > 1).
        unsigned int Reserved3 : 19;    // EDX[31:13] Reserved = 0.
    };
} CPUID_0A;

/* Extended Topology Information
 * NOTES:
 * Most of Leaf 0BH output depends on the initial value in ECX. 
 * The EDX output of leaf 0BH is always valid and does not vary with input value in ECX.
 * Output value in ECX[7:0] always equals input value in ECX[7:0].
 * For sub-leaves that return an invalid level-type of 0 in ECX[15:8]; EAX and EBX will return 0.
 * If an input value n in ECX returns the invalid level-type of 0 in ECX[15:8], other input values
 * with ECX > n also return 0 in ECX[15:8
*/
typedef union _CPUID_0B
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int TopologyShift : 5; // EAX[4:0] Number of bits to shift right on x2APIC ID to get a unique topology ID of the next level type*.
            // All logical processors with the same next level ID share current level.
        unsigned int Reserved1 : 27; // EAX[31:5] Reserved.

        /* EBX */
        unsigned int ProcessorCount : 16; // EBX[15:0] Number of logical processors at this level type. The number reflects configuration as shipped by Intel**.
        unsigned int Reserved2 : 16; // EBX[31:16] Reserved.

        /* ECX */
        unsigned int LevelNumber : 8; // ECX[7:0] Level number. Same value in ECX input.
        unsigned int LevelType : 8; // ECX[15:8] Level type.
        unsigned int Reserved3 : 16; // ECX[31:16] Reserved.

        /* EDX */
        unsigned int x2ApicID; // EDX[31:0] x2APIC ID of the current logical processor
    };
} CPUID_0B;

/* Processor Extended States Enumeration Information */
typedef union _CPUID_0D_00
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        union
        {
            unsigned int EnabledFeaturesLow;
            struct
            {
                unsigned int X87_State : 1; // EAX[0]
                unsigned int SSE_State : 1; // EAX[1]
                unsigned int AVX_State : 1; // EAX[2]
                unsigned int MPX_State : 2; // EAX[4:3]
                unsigned int AVX512_State : 2; // EAX[7:5]
                unsigned int IA32_XSS : 1; // EAX[8]
                unsigned int PKRU_State : 1; // EAX[9]
                unsigned int Reserved1 : 24; // EAX[31:10]
            };
        };

        /* EBX */
        unsigned int MaxEnabledFeatureSize; // EBX[31:0] Maximum size (bytes, from the beginning of the XSAVE/XRSTOR save area) required by
            // enabled features in XCR0. May be different than ECX if some features at the end of the XSAVE save area are not enabled.

        /* ECX */
        unsigned int MaxAllFeaturesSize; // ECX[31:0] Maximum size (bytes, from the beginning of the XSAVE/XRSTOR save area) of the 
            // XSAVE/XRSTOR save area required by all supported features in the processor, i.e., all the valid bit fields in XCR0.

        /* EDX */
        unsigned int EnabledFeaturesHigh; // EDX[31:0] Reports the supported bits of the upper 32 bits of XCR0. XCR0[n+32] can be set to 1 only if EDX[n] is 1.
            // Bits 31 - 00: Reserved
    };
} CPUID_0D_00;

/* Processor Extended State Enumeration Sub-leaf (EAX = 0DH, ECX = 1) */
typedef union _CPUID_0D_01
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int XSAVEOPT : 1; // EAX[0] XSAVEOPT is available.
        unsigned int XSAVEC : 1; // EAX[1] Supports XSAVEC and the compacted form of XRSTOR if set.
        unsigned int XGETBV1 : 1; // EAX[2] Supports XGETBV with ECX = 1 if set.
        unsigned int XSAVES : 1; // EAX[3] Supports XSAVES/XRSTORS and IA32_XSS if set.
        unsigned int Reserved1 : 28; // EAX[31:4] Reserved.

        /* EBX */
        unsigned int EnabledFeaturesSize; // EBX[31:0] The size in bytes of the XSAVE area containing all states enabled by XCRO | IA32_XSS.

        /* ECX */
        union
        {
            unsigned int EnabledSupervisorFeaturesLow;
            struct
            {
                unsigned int UsedForXCR0 : 8; // ECX[7:0] Used for XCR0.
                unsigned int PT_State : 1; // ECX[8] PT state.
                unsigned int UsedForXCR0_2 : 1; // ECX[9] Used for XCR0.
                unsigned int Reserved1 : 22; // ECX[31:10] Reserved.
            };
        }

        /* EDX */
        union
        {
            unsigned int EnabledSupervisorFeaturesHigh;
            struct
            {
                unsigned int Reserved2; // EDX[31:0] Reserved.
            };
        }
    };
} CPUID_0D_01;

/* Processor Extended State Enumeration Sub-leaves (EAX = 0DH, ECX = n, n > 1) */
typedef union _CPUID_0D_N
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int FeatureSize; // EAX[31:0] Size for XSAVE are for this component

        /* EBX */
        unsigned int StandardFormatOffset; // EBX[31:0] Only for user components, otherwise 0

        /* ECX */
        unsigned int IsSupervisorComponent : 1; // ECX[0]
        unsigned int Needs64ByteAlignment : 1; // ECX[1]
        unsigned int Reserved1 : 30; // ECX[31:2] Reserved

        /* EDX */
        unsigned int Reserved2; // EDX[31:0] Reserved
    };
} CPUID_0D_N;

/* Intel Resource Director Technology (Intel RDT) Monitoring Enumeration Sub-leaf (EAX = 0FH, ECX = 0) */
typedef union _CPUID_0F_00
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int Reserved1;         // EAX[31:0] Reserved.

        /* EBX */
        unsigned int MaxRMIDRange;      // EBX[31:0] Maximum range (zero-based) of RMID within this physical processor of all types.

        /* ECX */
        unsigned int Reserved2;         // ECX[31:0] Reserved.

        /* EDX */
        unsigned int Reserved3 : 1;     // EDX[0] Reserved.
        unsigned int RDTMonitoring : 1; // EDX[1] Supports L3 Cache Intel RDT Monitoring if 1.
        unsigned int Reserved4 : 30;    // EDX[31:2] Reserved.
    };
} CPUID_0F_00;

/* L3 Cache Intel RDT Monitoring Capability Enumeration Sub-leaf (EAX = 0FH, ECX = 1) */
typedef union _CPUID_0F_01
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        // EAX


        // EBX


        // ECX


        // EDX

    };
} CPUID_0F_01;

/* Intel Resource Director Technology (Intel RDT) Allocation Enumeration Information */
typedef union _CPUID_10
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        // EAX


        // EBX


        // ECX


        // EDX

    };
} CPUID_10;

/* Intel SGX Enumeration Information */
typedef union _CPUID_12
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        // EAX


        // EBX


        // ECX


        // EDX

    };
} CPUID_12;

/* Intel Processor Trace Enumeration Information */
typedef union _CPUID_14
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned long NumberOfAddressRanges : 3; // EAX[2:0] Number of configurable Address Ranges for filtering.
        unsigned long Reserved1 : 13; // EAX[15:3] Reserved.
        unsigned long MtcBitmap : 16; // EAX[31:16] Bitmap of supported MTC period encodings.

        /* EBX */
        unsigned long CycleThresholdBitmap : 16; // EBX[15:0] Bitmap of supported Cycle Threshold value encodings.
        unsigned long PsbBitmap : 16; // EBX[31:16] Bitmap of supported Configurable PSB frequency encodings.

        /* ECX */
        unsigned long Reserved2; // ECX[31:0] Reserved

        /* EDX */
        unsigned long Reserved3; // EDX[31:0] Reserved
    };
} CPUID_14;

/* Time Stamp Counter and Nominal Core Crystal Clock Information */
typedef union _CPUID_15
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned int Denominator;       // EAX[31:00] An unsigned integer which is the denominator of the TSC/”core crystal clock” ratio.

        /* EBX */
        unsigned int Numerator;         // EBX[31:00] An unsigned integer which is the numerator of the TSC / ”core crystal clock” ratio

        /* ECX */
        unsigned int NominalFrequency;  // ECX[31:00] An unsigned integer which is the nominal frequency of the core crystal clock in Hz

        /* EDX */
        unsigned int Reserved;          // EDX[31:00] Reserved = 0.
    };
} CPUID_15;

/* Intel: Processor Frequency Information */
typedef union _CPUID_16
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned short ProcessorBaseFrequency;  // EAX[15:0] Processor Base Frequency (in MHz).
        unsigned short Reserved1;               // EAX[31:16] Reserved =0

        /* EBX */
        unsigned short MaximumFrequency;        // EBX[15:0] Maximum Frequency (in MHz).
        unsigned short Reserved2;               // EBX[31:16] Reserved = 0.

        /* ECX */
        unsigned short BusFrequency;            // ECX[15:0] Bus (Reference) Frequency (in MHz).
        unsigned short Reserved3;               // ECX[31:16] Reserved = 0.

        /* EDX */
        unsigned int Reserved4;                 // EDX[31:0] Reserved.
    };
} CPUID_16;

/* System-On-Chip Information
 *
 * Leaf 17H main leaf (ECX = 0).
 * Leaf 17H output depends on the initial value in ECX.
 * Leaf 17H sub-leaves 1 through 3 reports SOC Vendor Brand String.
 * Leaf 17H is valid if MaxSOCID_Index >= 3.
 * Leaf 17H sub-leaves 4 and above are reserved
 */
typedef union _CPUID_17_00
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        /* EAX */
        unsigned long MaxSOCID_Index; // Reports the maximum input value of supported sub-leaf in leaf 17H.

        /* EBX */
        unsigned long SOC_VendorID : 16; // EBX[15:0]
        unsigned long IsVendorScheme : 1; // EBX[16] If 1, the SOC Vendor ID field is assigned via an industry standard enumeration
            // scheme. Otherwise, the SOC Vendor ID field is assigned by Intel.
        unsigned long Reserved : 15; // EBX[31:17] = 0

        /* ECX */
        unsigned long Project_ID; // ECX[31:0] A unique number an SOC vendor assigns to its SOC projects.
 
        /* EDX */
        unsigned long Stepping_ID; // EDX[31:0] A unique number within an SOC project that an SOC vendor assigns

    };
} CPUID_17_00;

/* Leaf 17H output depends on the initial value in ECX.
 * SOC Vendor Brand String is a UTF-8 encoded string padded with trailing bytes of 00H.
 * The complete SOC Vendor Brand String is constructed by concatenating in ascending order of
 * EAX:EBX:ECX:EDX and from the sub-leaf 1 fragment towards sub-leaf 3
*/
typedef union _CPUID_17_N
{
    int AsInt32[4];
    CPUID_REGISTERS AsRegs;
    struct
    {
        char SOC_VendorBrandString[16]; // UTF-8 encoded string.
    };
} CPUID_17_N;

