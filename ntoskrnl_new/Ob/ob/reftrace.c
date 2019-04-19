/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            ntoskrnl/ob/reftrace.c
 * PURPOSE:         Ob reference tracing functions
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#include "ob_internal.h"

#define MAXIMUM_TRACE_TAGS 16

static ULONG ObpNumberOfTraceTags;
static ULONG ObpTraceTags[MAXIMUM_TRACE_TAGS];

VOID
NTAPI
ObpTraceReference (
    PVOID Object,
    ULONG Tag)
{
    POBJECT_HEADER ObjectHeader = CONTAINING_RECORD(Object, OBJECT_HEADER, Body);

    /* Check if we have a process */
    if (Obp

    for (i = 0; i < ObpNumberOfTraceTags; i++)
    {
        if (ObpTraceTags[i] == Tag)
        {
            .
        }
    }

}

