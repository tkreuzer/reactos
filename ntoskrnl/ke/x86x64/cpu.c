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
        /* For Family 6 ExtendedModelId is only non-0 for Intel/VIA */
        *Model |= VersionInfo.Eax.Bits.ExtendedModelId << 4;
    }

    /* Get the stepping */
    *Stepping = VersionInfo.Eax.Bits.SteppingId;
}
