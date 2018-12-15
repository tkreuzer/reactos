/*
 * hdlsblk.h
 *
 * Definitions for the headless loader block
 *
 * This file is part of the reactos sdk package.
 *
 * Contributors:
 *   Created by Timo Kreuzer <timo.kreuzer@reactos.org>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#pragma once

#ifndef _HDLSBLK_
#define _HDLSBLK_

typedef struct _HEADLESS_LOADER_BLOCK
{
    UCHAR UsedBiosSettings;
    UCHAR DataBits;
    UCHAR StopBits;
    UCHAR Parity;
    ULONG BaudRate;
    ULONG PortNumber;
    PUCHAR PortAddress;
    USHORT PciDeviceId;
    USHORT PciVendorId;
    UCHAR PciBusNumber;
    UCHAR PciSlotNumber;
    UCHAR PciFunctionNumber;
    ULONG PciFlags;
    GUID SystemGUID;
    UCHAR IsMMIODevice;
    UCHAR TerminalType;
} HEADLESS_LOADER_BLOCK, *PHEADLESS_LOADER_BLOCK;

#endif // _HDLSBLK_
