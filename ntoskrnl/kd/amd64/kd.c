/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            ntoskrnl/kd/amd64/kd.c
 * PURPOSE:         Routines for CPU-level support
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* FUNCTIONS *****************************************************************/

VOID
NTAPI
KdpGdbStubInit(PKD_DISPATCH_TABLE WrapperTable,
               ULONG BootPhase)
{
    UNIMPLEMENTED;
}

VOID
STDCALL
KdbpGetCommandLineSettings(PCHAR p1)
{
    PCHAR p2;

    while (p1 && (p2 = strchr(p1, ' ')))
    {
        p2++;

        if (!_strnicmp(p2, "KDSERIAL", 8))
        {
            p2 += 8;
            KdbDebugState |= KD_DEBUG_KDSERIAL;
            KdpDebugMode.Serial = TRUE;
        }
        else if (!_strnicmp(p2, "KDNOECHO", 8))
        {
            p2 += 8;
            KdbDebugState |= KD_DEBUG_KDNOECHO;
        }

        p1 = p2;
    }
}
