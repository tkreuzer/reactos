/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     Routines for x86 / x64 CPU-level support
 * COPYRIGHT:   Copyright 2006 Alex Ionescu <alex.ionescu@reactos.org>
 *              Copyright 2010-2023 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

/* INCLUDES *****************************************************************/

#include <ntoskrnl.h>
#include <x86x64/Cpuid.h>
#define NDEBUG
#include <debug.h>

/* GLOBALS *******************************************************************/

/* CPU Signatures */
static const CHAR KiIntelID[]       = "GenuineIntel";
static const CHAR KiIotelID[]       = "GenuineIotel"; // Intel Xeon E3-1231 v3
static const CHAR KiAmdID[]         = "AuthenticAMD";
static const CHAR KiHygonID[]       = "HygonGenuine";
static const CHAR KiCentaurID[]     = "CentaurHauls";
static const CHAR KiZhaoxinID[]     = "  Shanghai  ";
#ifdef _M_I386
static const CHAR KiCyrixID[]       = "CyrixInstead";
static const CHAR KiTransmetaID[]   = "GenuineTMx86";
static const CHAR KiRiseID[]        = "RiseRiseRise";
#endif // _M_I386

/* FUNCTIONS *****************************************************************/

/*!
 * \brief Get the CPUID information for a given CPU
 *
 * \param[out] VendorString - Pointer to a buffer to receive the vendor string
 */
CODE_SEG("INIT")
VOID
NTAPI
KiGetCpuVendorString(
    _Out_writes_z_(13) PCHAR VendorString)
{
    CPU_INFO CpuInfo;

    /* Get the Vendor string */
    KiCpuId(&CpuInfo, 0);

    /* Copy and null-terminate it */
    *(ULONG*)&VendorString[0] = CpuInfo.Ebx;
    *(ULONG*)&VendorString[4] = CpuInfo.Edx;
    *(ULONG*)&VendorString[8] = CpuInfo.Ecx;
    VendorString[12] = 0;
}

/*!
 * \brief Identify the CPU vendor by the vendor string
 *
 * \param[in] VendorString - Pointer to a buffer containing the vendor string
 *
 * \return The CPU_VENDOR enum value that corresponds to the vendor string
 *
 * \see
 * - https://en.wikipedia.org/wiki/CPUID
 * - https://github.com/InstLatx64/InstLatx64
 * 
 * \remark This function is called very early during the boot process, before
 *         the kernel debugger is initialized, so it must not do any debug prints.
 */
CODE_SEG("INIT")
CPU_VENDORS
NTAPI
KiIdentifyCpuVendor(
    _In_reads_z_(13) PCHAR VendorString)
{
    /* Identify the CPU Type */
    if (!strcmp(VendorString, KiIntelID) ||
        !strcmp(VendorString, KiIotelID))
    {
        return CPU_INTEL;
    }
    else if (!strcmp(VendorString, KiAmdID) ||
             !strcmp(VendorString, KiHygonID))
    {
        return CPU_AMD;
    }
    else if (!strcmp(VendorString, KiCentaurID) ||
             !strcmp(VendorString, KiZhaoxinID))
    {
        return CPU_VIA;
    }
#ifdef _M_I386
    else if (!strcmp(VendorString, KiCyrixID))
    {
        return CPU_CYRIX;
    }
    else if (!strcmp(VendorString, KiTransmetaID))
    {
        return CPU_TRANSMETA;
    }
    else if (!strcmp(VendorString, KiRiseID))
    {
        return CPU_RISE;
    }
#endif // _M_I386

    return CPU_UNKNOWN;
}

/*!
 * \brief Get the CPU vendor
 *
 * \return The CPU_VENDOR enum value that corresponds to the vendor string
 */
CODE_SEG("INIT")
CPU_VENDORS
NTAPI
KiGetCpuVendor(VOID)
{
    CHAR VendorString[13];

    /* Get the vendor string */
    KiGetCpuVendorString(VendorString);

    /* Identify the CPU Type */
    return KiIdentifyCpuVendor(VendorString);
}

/*!
 * \brief Get the CPU signature
 *
 * \param[out] Family - Pointer to a USHORT to receive the family
 * \param[out] Model - Pointer to a USHORT to receive the model
 * \param[out] Stepping - Pointer to a USHORT to receive the stepping
 * 
 * \See
 * - https://www.sandpile.org/x86/cpuid.htm#level_0000_0001h
 * - https://github.com/InstLatx64/InstLatx64
 * 
 * - Intel:
 *   - https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-2a-manual.pdf#G5.876260
 *   - https://www.scss.tcd.ie/Jeremy.Jones/CS4021/processor-identification-cpuid-instruction-note.pdf
 *   - https://en.wikichip.org/wiki/intel/cpuid
 * - AMD:
 *   - https://www.amd.com/content/dam/amd/en/documents/processor-tech-docs/programmer-references/24594.pdf#G15.998445
 *   - https://kib.kiev.ua/x86docs/AMD/AMD-CPUID-Spec/20734-r3.13.pdf
 *   - https://en.wikichip.org/wiki/amd/cpuid
 *
 */
CODE_SEG("INIT")
VOID
NTAPI
KiGetCpuSignature(
    _Out_ PUSHORT Family,
    _Out_ PUSHORT Model,
    _Out_ PUSHORT Stepping)
{
    CPUID_VERSION_INFO_REGS VersionInfo;

    /* Get the CPUID */
    __cpuid(VersionInfo.AsInt32, 1);

    /* Get the family */
    *Family = VersionInfo.Eax.Bits.FamilyId;
    if (VersionInfo.Eax.Bits.FamilyId == 15)
    {
        *Family += VersionInfo.Eax.Bits.ExtendedFamilyId;
    }

    /* Get the model */
    *Model = VersionInfo.Eax.Bits.Model;
    if ((VersionInfo.Eax.Bits.FamilyId == 6) ||
        (VersionInfo.Eax.Bits.FamilyId == 15))
    {
        /* For Family 6 of AMD and Centaur ExtendedModelId is always 0 */
        *Model |= VersionInfo.Eax.Bits.ExtendedModelId << 4;
    }

    /* Get the stepping */
    *Stepping = VersionInfo.Eax.Bits.SteppingId;
}

ULONG
KiGetMaxCpuid(VOID)
{
    CPUID_SIGNATURE_REGS Signature;

    /* Read CPUID_SIGNATURE and return the maximum function */
    __cpuid(Signature.AsInt32, CPUID_SIGNATURE);
    return Signature.MaxLeaf;
}

ULONG
KiGetMaxExtendedCpuid(VOID)
{
    CPU_INFO CpuInfo;

    /* Get the CPUID */
    KiCpuId(&CpuInfo, 0x80000000);

    /* Return the max function */
    return CpuInfo.Eax;
}

BOOLEAN
KiGetBrandString(
    _Out_writes_z_(49) PCHAR BrandString)
{
    if (KiGetMaxExtendedCpuid() < 0x80000004)
    {
        return FALSE;
    }

    /* Get the brand string */
    KiCpuId((PCPU_INFO)BrandString, 0x80000002);
    KiCpuId((PCPU_INFO)(BrandString + 16), 0x80000003);
    KiCpuId((PCPU_INFO)(BrandString + 32), 0x80000004);

    /* Null-terminate it */
    BrandString[48] = 0;

    /* Return success */
    return TRUE;
}

ULONG
KiGetClockFrequencyFromBrandString()
{
    CHAR BrandString[49];
    PCHAR p;
    ULONG Multiplier;
    ULONG Divisor;
    ULONG DigitMultiplier;
    ULONG Frequency;

    /* Get the brand string */
    if (!KiGetBrandString(BrandString))
    {
        return 0;
    }

    /* Search for "MHz" */
    p = strstr(BrandString, "MHz");
    if (p != NULL)
    {
        Multiplier = 1000000;
    }
    else
    {
        /* Search for "GHz" */
        p = strstr(BrandString, "GHz");
        if (p != NULL)
        {
            Multiplier = 1000000000;
        }
        else
        {
            /* Not found */
            return 0;
        }
    }

    /* Skip optional white space */
    p--;
    if (*p == ' ')
    {
        p--;
    }

    /* Get the frequency */
    Frequency = 0;
    Divisor = 1;
    DigitMultiplier = 1;
    while (p > BrandString)
    {
        if ((*p >= '0') && (*p <= '9'))
        {
            Frequency += (*p - '0') * DigitMultiplier;
            DigitMultiplier *= 10;
        }
        else if (*p == '.')
        {
            if (Divisor != 1)
            {
                /* Already found a dot */
                return 0;
            }
            Divisor = DigitMultiplier;
        }
        else
        {
            /* Not a digit */
            break;
        }
        p--;
    }

    /* Return the frequency */
    return (ULONG)((ULONG64)Frequency * Multiplier / Divisor);
}

VOID
KiGetClockInfo(
    _Out_ PULONG TscFrequencyInHz,
    _Out_ PUSHORT ClockSpeedInMHz,
    _Out_ PUSHORT MaxBoostSpeedInMHz,
    _Out_ PUSHORT BusSpeedInMHz,
    _Out_ PULONG FrequencyFromBrandStringInHz)
{
    CPUID_SIGNATURE_REGS Signature;
    CPUID_TIME_STAMP_COUNTER_REGS TscInfo;
    CPUID_PROCESSOR_FREQUENCY_REGS CpuClockInfo;

    /* Read signature for max lead */
    __cpuid(Signature.AsInt32, CPUID_SIGNATURE);

    /* Check if we support CPUID_TIME_STAMP_COUNTER (0x15) */
    if (Signature.MaxLeaf >= CPUID_TIME_STAMP_COUNTER)
    {
        /* Get the TSC speed */
        __cpuidex(TscInfo.AsInt32, CPUID_TIME_STAMP_COUNTER, 0);

        /* Return the TSC frequency */
        if (TscInfo.Denominator != 0)
        {
            *TscFrequencyInHz = (ULONG64)TscInfo.CoreFrequency *
                TscInfo.Numerator / TscInfo.Denominator;
        }
        else
        {
            *TscFrequencyInHz = 0;
        }
    }
    else
    {
        *TscFrequencyInHz = 0;
    }

    /* Check if we support CPUID_PROCESSOR_FREQUENCY (0x16) */
    if (Signature.MaxLeaf >= CPUID_PROCESSOR_FREQUENCY)
    {
        /* Get the CPU speed */
        __cpuidex(CpuClockInfo.AsInt32, CPUID_PROCESSOR_FREQUENCY, 0);
        *ClockSpeedInMHz = CpuClockInfo.Eax.Bits.ProcessorBaseFrequency;
        *MaxBoostSpeedInMHz = CpuClockInfo.Ebx.Bits.MaximumFrequency;
        *BusSpeedInMHz = CpuClockInfo.Ecx.Bits.BusFrequency;
    }
    else
    {
        *ClockSpeedInMHz = 0;
        *MaxBoostSpeedInMHz = 0;
        *BusSpeedInMHz = 0;
    }

    *FrequencyFromBrandStringInHz =
        KiGetClockFrequencyFromBrandString();
}

VOID
KiTestGetClockInfo()
{
    ULONG TscFrequencyInHz;
    USHORT ClockSpeedInMHz;
    USHORT MaxBoostSpeedInMHz;
    USHORT BusSpeedInMHz;
    ULONG FrequencyFromBrandStringInHz;

    __debugbreak();
    KiGetClockInfo(&TscFrequencyInHz,
        &ClockSpeedInMHz,
        &MaxBoostSpeedInMHz,
        &BusSpeedInMHz,
        &FrequencyFromBrandStringInHz);

    DPRINT1("TSC Frequency: %lu Hz\n", TscFrequencyInHz);
    DPRINT1("Clock Speed: %u MHz\n", ClockSpeedInMHz);
    DPRINT1("Max Boost Speed: %u MHz\n", MaxBoostSpeedInMHz);
    DPRINT1("Bus Speed: %u MHz\n", BusSpeedInMHz);
    DPRINT1("Frequency from Brand String: %lu Hz\n", FrequencyFromBrandStringInHz);
}
