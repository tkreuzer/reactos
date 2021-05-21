/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * FILE:        hal/halx86/smp/ipi.c
 * PURPOSE:     Source file for managing IPI functions
 * PROGRAMMERS:  Copyright 2021 Justin Miller <justinmiller100@gmail.com>
 */

/* INCLUDES *******************************************************************/

#include <hal.h>
#include <apic.h>
#include <smp.h>
#define NDEBUG
#include <debug.h>

VOID
HalpSendIPI(ULONG AP, ULONG Mode)
{
    ULONG tmp, i;

    /* Disable interrupts */
    _disable();

    /* Wait up to 100ms for the APIC to become ready */
    for (i = 0; i < 10000; i++) 
    {
        tmp = ApicRead(APIC_ICR0);
        /* Check Delivery Status */
        if ((tmp & APIC_ICR0_DS) == 0)
            break;
        KeStallExecutionProcessor(10);
    }

    ApicWrite(APIC_ICR1 , (AP << 24));
    ApicWrite(APIC_ICR0, Mode);

    /* Wait up to 100ms for the APIC to become ready */
   for (i = 0; i < 10000; i++) 
   {
      tmp = ApicRead(APIC_ICR0);
      /* Check Delivery Status */
      if ((tmp & APIC_ICR0_DS) == 0)
      {
        break;
      }
      KeStallExecutionProcessor(10);
   }

    if (i == 10000) 
   {
      DPRINT1("Current IPI was not delivered after 100ms.\n");
   }
}