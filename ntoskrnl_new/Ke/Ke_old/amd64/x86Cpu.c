

#include <ntoskrnl.h>
#include "..\Ke_Internal.h"

typedef struct
{
    UCHAR Associativity;
    USHORT NumberEntries;
} X86_TLB;

typedef struct
{
    ULONG Size;
    ULONG LineSize;
    UCHAR LinesPerSector;
    UCHAR Associativity;
} X86_CACHE;

typedef struct _CPU_CACHE_INFORMATION
{
    X86_TLB InstructionTlb;
    X86_TLB InstructionTlbLargePage;
    X86_TLB DataTlb;
    X86_TLB DataTlbLargePage;
    X86_CACHE L1InstructionCache;
    X86_CACHE L1DataCache;
    X86_CACHE L2Cache;
    X86_CACHE L3Cache;
    X86_CACHE TraceCache;
    UCHAR Prefetching;
} CPU_CACHE_INFORMATION, *PCPU_CACHE_INFORMATION;

VOID
NTAPI
x86GetIntelCacheInformation(PCPU_CACHE_INFORMATION Info)
{
    ULONG CpuidCount, i, Register;
    ULONG Buffer[4];
    UCHAR Byte;

    __cpuid(Buffer, 4);

    CpuidCount = Buffer[0] & 0xFF;

    /* Set the first byte to 0 so the loop works correctly */
    Buffer[0] &= ~0xFF;

    while (CpuidCount--)
    {
        /* Loop all 4 registers */
        for (i = 0; i < 4; i++)
        {
            Register = Buffer[i];

            /* If the highest bit is set, the register doesn't contain
               valid information */
            if (Register * 0x80000000) continue;

            /* Loop all bytes in the register */
            while (Register)
            {
                /* Get the current lowest byte and shift the register */
                Byte = (UCHAR)(Register & 0xFF);
                Register >>= 8;

                switch (Byte)
                {
                    case 0x01:
                        Info->InstructionTlb.Associativity = 4;
                        Info->InstructionTlb.NumberEntries = 32;
                        break;

                    case 0x02:
                        Info->InstructionTlbLargePage.Associativity = 4;
                        Info->InstructionTlbLargePage.NumberEntries = 2;
                        break;

                    case 0x03:
                        Info->DataTlb.Associativity = 4;
                        Info->DataTlb.NumberEntries = 64;
                        break;

                    case 0x04:
                        Info->DataTlbLargePage.Associativity = 4;
                        Info->DataTlbLargePage.NumberEntries = 8;
                        break;

                    case 0x05:
                        Info->DataTlbLargePage.Associativity = 4;
                        Info->DataTlbLargePage.NumberEntries = 32;
                        break;

                    case 0x06:
                        Info->L1InstructionCache.Associativity = 4;
                        Info->L1InstructionCache.Size = 8;
                        Info->L1InstructionCache.LineSize = 32;
                        break;

                    case 0x08:
                        Info->L1InstructionCache.Associativity = 4;
                        Info->L1InstructionCache.Size = 16;
                        Info->L1InstructionCache.LineSize = 32;
                        break;

                    case 0x0A:
                        Info->L1DataCache.Associativity = 2;
                        Info->L1DataCache.Size = 8;
                        Info->L1DataCache.LineSize = 32;
                        break;

                    case 0x0B:
                        Info->InstructionTlbLargePage.Associativity = 4;
                        Info->InstructionTlbLargePage.NumberEntries = 4;
                        break;

                    case 0x0C:
                        Info->L1DataCache.Associativity = 4;
                        Info->L1DataCache.Size = 16;
                        Info->L1DataCache.LineSize = 32;
                        break;

                    case 0x22:
                        Info->L3Cache.Associativity = 4;
                        Info->L3Cache.Size = 512;
                        Info->L3Cache.LineSize = 64;
                        Info->L3Cache.LinesPerSector = 2;
                        break;

                    case 0x23:
                        Info->L3Cache.Associativity = 8;
                        Info->L3Cache.Size = 1024;
                        Info->L3Cache.LineSize = 64;
                        Info->L3Cache.LinesPerSector = 2;
                        break;

                    case 0x25:
                        Info->L3Cache.Associativity = 8;
                        Info->L3Cache.Size = 2048;
                        Info->L3Cache.LineSize = 64;
                        Info->L3Cache.LinesPerSector = 2;
                        break;

                    case 0x29:
                        Info->L3Cache.Associativity = 8;
                        Info->L3Cache.Size = 4096;
                        Info->L3Cache.LineSize = 64;
                        Info->L3Cache.LinesPerSector = 2;
                        break;

                    case 0x2C:
                        Info->L1DataCache.Associativity = 8;
                        Info->L1DataCache.Size = 32;
                        Info->L1DataCache.LineSize = 64;
                        break;

                    case 0x30:
                        Info->L1InstructionCache.Associativity = 8;
                        Info->L1InstructionCache.Size = 32;
                        Info->L1InstructionCache.LineSize = 64;
                        Info->L1InstructionCache.LinesPerSector = 0; // ??
                        break;

                    case 0x40: // FIXME: handle this

                    case 0x41:
                        Info->L2Cache.Associativity = 4;
                        Info->L2Cache.Size = 128;
                        Info->L2Cache.LineSize = 32;
                        Info->L2Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x42:
                        Info->L2Cache.Associativity = 4;
                        Info->L2Cache.Size = 256;
                        Info->L2Cache.LineSize = 32;
                        Info->L2Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x43:
                        Info->L2Cache.Associativity = 4;
                        Info->L2Cache.Size = 512;
                        Info->L2Cache.LineSize = 32;
                        Info->L2Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x44:
                        Info->L2Cache.Associativity = 4;
                        Info->L2Cache.Size = 1024;
                        Info->L2Cache.LineSize = 32;
                        Info->L2Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x45:
                        Info->L2Cache.Associativity = 4;
                        Info->L2Cache.Size = 2048;
                        Info->L2Cache.LineSize = 32;
                        Info->L2Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x46:
                        Info->L3Cache.Associativity = 4;
                        Info->L3Cache.Size = 4096;
                        Info->L3Cache.LineSize = 64;
                        Info->L3Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x47:
                        Info->L3Cache.Associativity = 8;
                        Info->L3Cache.Size = 8192;
                        Info->L3Cache.LineSize = 64;
                        Info->L3Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x49:
                        Info->L2Cache.Associativity = 16;
                        Info->L2Cache.Size = 4096;
                        Info->L2Cache.LineSize = 64;
                        Info->L2Cache.LinesPerSector = 0; // ??
                        break;

                    case 0x50:
                        Info->InstructionTlb.Associativity = 1;
                        Info->InstructionTlb.NumberEntries = 64;
                        //Info->InstructionTlbLargePage.Associativity = 4; both
                        //Info->InstructionTlbLargePage.NumberEntries = 64;
                        break;

                    case 0x51:
                        Info->InstructionTlb.Associativity = 1;
                        Info->InstructionTlb.NumberEntries = 128;
                        // both
                        break;

                    case 0x52:
                        Info->InstructionTlb.Associativity = 1;
                        Info->InstructionTlb.NumberEntries = 256;
                        // both
                        break;

                    case 0x56:
                        // Data TLB0
                        Info->DataTlbLargePage.Associativity = 4;
                        Info->DataTlbLargePage.NumberEntries = 16;
                        break;

                    case 0x57:
                        // Data TLB0
                        Info->DataTlb.Associativity = 4;
                        Info->DataTlb.NumberEntries = 16;
                        break;

                    case 0x5B:
                        // both
                        Info->DataTlb.Associativity = 1;
                        Info->DataTlb.NumberEntries = 64;
                        break;

                    case 0x5C:
                        // both
                        Info->DataTlb.Associativity = 1;
                        Info->DataTlb.NumberEntries = 128;
                        break;

                    case 0x5D:
                        // both
                        Info->DataTlb.Associativity = 1;
                        Info->DataTlb.NumberEntries = 256;
                        break;

                    case 0x60:
                        Info->L1DataCache.Associativity = 8;
                        Info->L1DataCache.Size = 16;
                        Info->L1DataCache.LineSize = 64;
                        break;

                    case 0x66:
                        Info->L1DataCache.Associativity = 4;
                        Info->L1DataCache.Size = 8;
                        Info->L1DataCache.LineSize = 64;
                        break;

                    case 0x67:
                        Info->L1DataCache.Associativity = 4;
                        Info->L1DataCache.Size = 16;
                        Info->L1DataCache.LineSize = 64;
                        break;

                    case 0x68:
                        Info->L1DataCache.Associativity = 4;
                        Info->L1DataCache.Size = 32;
                        Info->L1DataCache.LineSize = 64;
                        break;

                    case 0x70:
                        Info->TraceCache.Associativity = 8;
                        Info->TraceCache.Size = 12;
                        break;

                    case 0x71:
                        Info->TraceCache.Associativity = 8;
                        Info->TraceCache.Size = 16;
                        break;

                    case 0x72:
                        Info->TraceCache.Associativity = 8;
                        Info->TraceCache.Size = 32;
                        break;

                    case 0x78:
                        Info->L2Cache.Associativity = 4;
                        Info->L2Cache.Size = 1024;
                        Info->L2Cache.LineSize = 64;
                        break;

                    case 0x79:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 128;
                        Info->L2Cache.LineSize = 64;
                        Info->L2Cache.LinesPerSector = 2;
                        break;

                    case 0x7A:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 256;
                        Info->L2Cache.LineSize = 64;
                        Info->L2Cache.LinesPerSector = 2;
                        break;

                    case 0x7B:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 512;
                        Info->L2Cache.LineSize = 64;
                        Info->L2Cache.LinesPerSector = 2;
                        break;

                    case 0x7C:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 1024;
                        Info->L2Cache.LineSize = 64;
                        Info->L2Cache.LinesPerSector = 2;
                        break;

                    case 0x7D:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 2048;
                        Info->L2Cache.LineSize = 64;
                        break;

                    case 0x7F:
                        Info->L2Cache.Associativity = 2;
                        Info->L2Cache.Size = 512;
                        Info->L2Cache.LineSize = 64;
                        break;

                    case 0x82:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 256;
                        Info->L2Cache.LineSize = 32;
                        break;

                    case 0x83:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 512;
                        Info->L2Cache.LineSize = 32;
                        break;

                    case 0x84:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 1024;
                        Info->L2Cache.LineSize = 32;
                        break;

                    case 0x85:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 2048;
                        Info->L2Cache.LineSize = 32;
                        break;

                    case 0x86:
                        Info->L2Cache.Associativity = 4;
                        Info->L2Cache.Size = 512;
                        Info->L2Cache.LineSize = 64;
                        break;

                    case 0x87:
                        Info->L2Cache.Associativity = 8;
                        Info->L2Cache.Size = 1024;
                        Info->L2Cache.LineSize = 64;
                        break;

                    case 0xB0:
                        Info->InstructionTlb.Associativity = 4;
                        Info->InstructionTlb.NumberEntries = 128;
                        break;

                    case 0xB3:
                        Info->DataTlb.Associativity = 4;
                        Info->DataTlb.NumberEntries = 128;
                        break;

                    case 0xB4:
                        Info->DataTlb.Associativity = 4;
                        Info->DataTlb.NumberEntries = 256;
                        break;

                    case 0xF0:
                        Info->Prefetching = 64;
                        break;

                    case 0xF1:
                        Info->Prefetching = 128;
                        break;

                    default:
                        __debugbreak();
                }

            }
        }

        /* Do the next cpuid round */
        if (CpuidCount) __cpuid(Buffer, 4);
    }
}

typedef union _X86_AMD_CPUID_80000005
{
    ULONG Regs[4];
    struct
    {
        UCHAR L1ITlb2and4MSize;
        UCHAR L1ITlb2and4MAssoc;
        UCHAR L1DTlb2and4MSize;
        UCHAR L1DTlb2and4MAssoc;
        UCHAR L1ITlb4KSize;
        UCHAR L1ITlb4KAssoc;
        UCHAR L1DTlb4KSize;
        UCHAR L1DTlb4KAssoc;
        UCHAR L1DcLineSize;
        UCHAR L1DcLinesPerTag;
        UCHAR L1DcAssoc;
        UCHAR L1DcSize;
        UCHAR L1IcLineSize;
        UCHAR L1IcLinesPerTag;
        UCHAR L1IcAssoc;
        UCHAR L1IcSize;
    };
} X86_AMD_CPUID_80000005, *PX86_AMD_CPUID_80000005;

typedef union _X86_AMD_CPUID_80000006
{
    ULONG Regs[4];
    struct
    {
        USHORT L2ITlb2and4MSize : 12;
        USHORT L2ITlb2and4MAssoc : 4;
        USHORT L2DTlb2and4MSize : 12;
        USHORT L2DTlb2and4MAssoc : 4;
        USHORT L2ITlb4KSize : 12;
        USHORT L2ITlb4KAssoc : 4;
        USHORT L2DTlb4KSize : 12;
        USHORT L2DTlb4KAssoc : 4;
        USHORT L2LineSize : 8;
        USHORT L2LinesPerTag : 4;
        USHORT L2Assoc : 4;
        USHORT L2Size : 16;
        USHORT L3LineSize : 8;
        USHORT L3LinesPerTag : 4;
        USHORT L3Assoc : 4;
        USHORT Reserved : 2;
        USHORT L3Size : 14;
    };
} X86_AMD_CPUID_80000006, *PX86_AMD_CPUID_80000006;

VOID
NTAPI
x86GetAmdCacheInformation(PCPU_CACHE_INFORMATION Info)
{
    static const UCHAR Assoc[] = {0, 1, 2, 0, 4, 0, 8, 0,
                                  16, 0, 32, 48, 64, 96, 128, 0xFF};
    X86_AMD_CPUID_80000005 CpuId_L1;
    X86_AMD_CPUID_80000006 CpuId_L23;


    __cpuid(CpuId_L1.Regs, 0x80000005);
    __cpuid(CpuId_L23.Regs, 0x80000006);


    Info->InstructionTlb.Associativity = Assoc[CpuId_L1.L1ITlb4KAssoc];
    Info->InstructionTlb.NumberEntries = CpuId_L1.L1ITlb4KSize;
    Info->InstructionTlbLargePage.Associativity = Assoc[CpuId_L1.L1ITlb2and4MAssoc];
    Info->InstructionTlbLargePage.NumberEntries = CpuId_L1.L1ITlb2and4MSize / 2;
    Info->DataTlb.Associativity = Assoc[CpuId_L1.L1DTlb4KAssoc];
    Info->DataTlb.NumberEntries = CpuId_L1.L1DTlb4KSize;
    Info->DataTlbLargePage.Associativity = Assoc[CpuId_L1.L1DTlb2and4MAssoc];
    Info->DataTlbLargePage.NumberEntries = CpuId_L1.L1DTlb2and4MSize / 2;
    Info->L1InstructionCache.Size = CpuId_L1.L1IcSize;
    Info->L1InstructionCache.LineSize = CpuId_L1.L1IcLineSize;
    Info->L1InstructionCache.LinesPerSector = CpuId_L1.L1IcLinesPerTag;
    Info->L1InstructionCache.Associativity = Assoc[CpuId_L1.L1IcAssoc];
    Info->L1DataCache.Size = CpuId_L1.L1DcSize;
    Info->L1DataCache.LineSize = CpuId_L1.L1DcLineSize;
    Info->L1DataCache.LinesPerSector = CpuId_L1.L1DcLinesPerTag;
    Info->L1DataCache.Associativity = Assoc[CpuId_L1.L1DcAssoc];
    Info->L2Cache.Size = CpuId_L23.L2Size;
    Info->L2Cache.LineSize = CpuId_L23.L2LineSize;
    Info->L2Cache.LinesPerSector = (UCHAR)CpuId_L23.L2LinesPerTag;
    Info->L2Cache.Associativity = Assoc[CpuId_L23.L2Assoc];
    Info->L3Cache.Size = CpuId_L23.L3Size;
    Info->L3Cache.LineSize = CpuId_L23.L3LineSize;
    Info->L3Cache.LinesPerSector = (UCHAR)CpuId_L23.L3LinesPerTag;
    Info->L3Cache.Associativity = Assoc[CpuId_L23.L3Assoc];
    Info->TraceCache.Size = 0;
    Info->TraceCache.LineSize = 0;
    Info->TraceCache.LinesPerSector = 0;
    Info->TraceCache.Associativity = 0;
    Info->Prefetching = 0;

}

CPU_CACHE_INFORMATION x86CpuCacheInformation;

VOID
INITAPI
x86GetCacheInformation(PKPCR Pcr)
{
    switch (KxGetCurrentPrcb()->CpuVendor)
    {
        case CPU_INTEL:
            x86GetIntelCacheInformation(&x86CpuCacheInformation);
            break;

        case CPU_AMD:
            x86GetAmdCacheInformation(&x86CpuCacheInformation);
            break;

        default:
            __debugbreak();
            break;
    }

    Pcr->SecondLevelCacheAssociativity = x86CpuCacheInformation.L2Cache.Associativity;
    Pcr->SecondLevelCacheSize = x86CpuCacheInformation.L2Cache.Size * 1024;

    if (Pcr->SecondLevelCacheAssociativity == 0)
        Pcr->SecondLevelCacheAssociativity = 1;

}

VOID
INITAPI
x86GetCpuInfo(PKPRCB Prcb)
{
    X86_CPUID_0001 CpuId1;
    ULONG Regs[4];

    /* CPUID 0 to get vendor name */
    __cpuid(Regs, 0);
    memcpy(&Prcb->VendorString[0], &Regs[1], 4);
    memcpy(&Prcb->VendorString[4], &Regs[3], 4);
    memcpy(&Prcb->VendorString[8], &Regs[2], 4);

    /* Now check the CPU Type */
    if (!strcmp(Prcb->VendorString, VENDOR_STRING_INTEL))
    {
        Prcb->CpuVendor = CPU_INTEL;
    }
    else if (!strcmp(Prcb->VendorString, VENDOR_STRING_AMD))
    {
        Prcb->CpuVendor = CPU_AMD;
    }
    else
    {
        // WARN("Unsupported CPU vendor: \n", Prcb->VendorString);
        Prcb->CpuVendor = CPU_UNKNOWN;
    }

    /* CPUID 1 to get cpu type and stepping */
    __cpuid(CpuId1.Regs, 1);
    Prcb->CpuType = CpuId1.BaseFamily;
    Prcb->CpuStepping = CpuId1.Stepping;
    Prcb->CpuModel = CpuId1.BaseModel;
    Prcb->InitialApicId = CpuId1.LocalApicId;
}

