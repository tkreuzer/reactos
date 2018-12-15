/*
 * profiles.h
 *
 * Definitions for bootloader profile information
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

#ifndef _PROFILES_H_
#define _PROFILES_H_

#define HW_PROFILE_STATUS_SUCCESS           0x0000
#define HW_PROFILE_STATUS_ALIAS_MATCH       0x0001
#define HW_PROFILE_STATUS_TRUE_MATCH        0x0002
#define HW_PROFILE_STATUS_PRISTINE_MATCH    0x0003
#define HW_PROFILE_STATUS_FAILURE           0xC001

#define HW_PROFILE_DOCKSTATE_UNSUPPORTED    (0x0)
#define HW_PROFILE_DOCKSTATE_UNDOCKED       (0x1)
#define HW_PROFILE_DOCKSTATE_DOCKED         (0x2)
#define HW_PROFILE_DOCKSTATE_UNKNOWN        (0x3)
#define HW_PROFILE_DOCKSTATE_USER_SUPPLIED  (0x4)
#define HW_PROFILE_DOCKSTATE_USER_UNDOCKED \
    (HW_PROFILE_DOCKSTATE_USER_SUPPLIED | HW_PROFILE_DOCKSTATE_UNDOCKED)
#define HW_PROFILE_DOCKSTATE_USER_DOCKED \
    (HW_PROFILE_DOCKSTATE_USER_SUPPLIED | HW_PROFILE_DOCKSTATE_DOCKED)

#define HW_PROFILE_CAPS_VCR                 0x0001
#define HW_PROFILE_CAPS_DOCKING_WARM        0x0002
#define HW_PROFILE_CAPS_DOCKING_HOT         0x0004
#define HW_PROFILE_CAPS_RESERVED            0xFFF8

typedef struct _PROFILE_PARAMETER_BLOCK
{
    USHORT Status;
    USHORT Reserved;
    USHORT DockingState;
    USHORT Capabilities;
    ULONG DockID;
    ULONG SerialNumber;
} PROFILE_PARAMETER_BLOCK, *PPROFILE_PARAMETER_BLOCK;

typedef struct _PROFILE_ACPI_DOCKING_STATE
{
    USHORT DockingState;
    USHORT SerialLength;
    WCHAR SerialNumber[1];
} PROFILE_ACPI_DOCKING_STATE, *PPROFILE_ACPI_DOCKING_STATE;

// #define DOCKINFO_VERBOSE TRUE

#endif // _PROFILES_H_
