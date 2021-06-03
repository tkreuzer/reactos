/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * FILE:        hal/halx86/acpi/madt.c
 * PURPOSE:     Source File for SMP
 * PROGRAMMERS:  Copyright 2021 Justin Miller <justinmiller100@gmail.com>
 */

/* INCLUDES *******************************************************************/

#include <hal.h>
//#include <acpi.h>
#define NDEBUG
#include <debug.h>

/* GLOBALS ********************************************************************/

/* FUNCTIONS ******************************************************************/

PVOID
NTAPI
HalAcpiParseMadt(IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    return NULL;
}
