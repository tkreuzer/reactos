/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     Header for x86 / x64 CPU-level support
 * COPYRIGHT:   Copyright 2023 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#pragma once
#define __NTOSKRNL_INCLUDE_INTERNAL_X86X64_KE_H

VOID
NTAPI
KiGetCpuVendorString(
    _Out_writes_z_(13) PCHAR VendorString);

CPU_VENDORS
NTAPI
KiIdentifyCpuVendor(
    _In_ PCHAR VendorString);

CPU_VENDORS
NTAPI
KiGetCpuVendor(VOID);
