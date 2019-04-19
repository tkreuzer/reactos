/**
 *  This file is part of the "fancykrnl" project.
 *
 *  Purpose:
 *      This file contains the amd64 specific kernel startup routines.
 *
 *  License:
 *      The software in this file is released under the terms of the
 *      GNU General Public License v2.
 *
 *  Copyright (c) 2011 Timo Kreuzer <timo.kreuzer@reactos.org>
 *
 */


#include <ntoskrnl.h>
#include "..\ke_internal.h"



VOID
KiSystemStartup(VOID)
{


    /* Initialized the CPU */
    //KiInitializeCpu();

    /* Architecture specific PCR initialization */
    //KiInitializePcr();



    /* Switch to the boot stack and run the portable init code */
    //KiSwitchToBootStack();
}

