/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * FILE:        ntoskrnl/ke/i386/mp.c
 * PURPOSE:     processor specific file to hold multiprocessor functions
 * PROGRAMMERS:  Copyright 2021 Justin Miller <justinmiller100@gmail.com>
 */

/* INCLUDES *****************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* GLOBALS *******************************************************************/
/* FUNCTIONS *****************************************************************/
VOID
NTAPI
KeStartAllProcessors()
{
    //@unimplemented
}