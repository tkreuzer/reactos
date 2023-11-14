/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     Routines for x86 / x64 CPU-level support
 * COPYRIGHT:   Copyright 2006 Alex Ionescu <alex.ionescu@reactos.org>
 *              Copyright 2010-2023 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

/* INCLUDES *****************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* GLOBALS *******************************************************************/

/* CPU Signatures */
static const CHAR KiIntelID[]       = "GenuineIntel";
static const CHAR KiAmdID[]         = "AuthenticAMD";
static const CHAR KiCentaurID[]     = "CentaurHauls";
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
    if (!strcmp(VendorString, KiIntelID))
    {
        return CPU_INTEL;
    }
    else if (!strcmp(VendorString, KiAmdID))
    {
        return CPU_AMD;
    }
    else if (!strcmp(VendorString, KiCentaurID))
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
