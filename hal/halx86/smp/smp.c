/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * FILE:        hal/halx86/smp/smp.c
 * PURPOSE:     Source File for SMP
 * PROGRAMMERS:  Copyright 2021 Justin Miller <justinmiller100@gmail.com>
 */

/* INCLUDES *******************************************************************/

#include <hal.h>
#include <apic.h>
#include <smp.h>
#define NDEBUG
#include <debug.h>

/* GLOBALS ********************************************************************/

/* Tiny bit of a hack to limit the cpu count until we progress further */
ULONG MAXAPCount = 1;

/* Private Functions **********************************************************/

BOOLEAN
HalpStartNextProcessor(PLOADER_PARAMETER_BLOCK APLoaderBlock, PKPROCESSOR_STATE APProcessorState)
{
    //@unimplemented
    return FALSE;
}