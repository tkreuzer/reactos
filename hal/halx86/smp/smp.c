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

extern PVOID HalpLowStub;
extern PHYSICAL_ADDRESS HalpLowStubPhysicalAddress;
extern PVOID APBoot;
extern PVOID APEnd;
extern PVOID APProtectedModeEnd;
extern PVOID APProtectedMode;
//extern PVOID KiApplicationProcessorSpinupLoc;
/* Tiny bit of a hack to limit the cpu count until we progress further */
ULONG MAXAPCount = 2;
ULONG APCountStarted = 1;
ULONG_PTR EcxValue;
ULONG_PTR EipValue;
ULONG_PTR PageTable;
PLOADER_PARAMETER_BLOCK APLoaderBlock;
PKPROCESSOR_STATE ProcessorState;
PVOID HalpAPProtected;
PVOID HalpAfterProtected;

USHORT BSPGDTLimit;
PVOID BSPGDTBase;
PVOID KiApplicationProcessorSpinupLoc;
USHORT SegSS;
USHORT SegDS;
USHORT SegES;
USHORT SegGS;
USHORT SegFS;
/* Private Functions **********************************************************/

BOOLEAN
HalpStartNextProcessor(PLOADER_PARAMETER_BLOCK APLoaderBlock, PKPROCESSOR_STATE APProcessorState)
{   

    
    if(MAXAPCount > APCountStarted)
    {       
        APLoaderBlock = (PLOADER_PARAMETER_BLOCK)APLoaderBlock;
        ProcessorState = (PKPROCESSOR_STATE)APProcessorState;

    #ifdef _M_AMD64
        /* AMD64 Processor Setup */
    #else
        /* x86 Processor Setup */
        EcxValue = ProcessorState->ContextFrame.Ecx;
        EipValue = ProcessorState->ContextFrame.Eip;
        PageTable = ProcessorState->SpecialRegisters.Cr3;
        BSPGDTLimit = ProcessorState->SpecialRegisters.Gdtr.Limit;
        BSPGDTBase = (PVOID)ProcessorState->SpecialRegisters.Gdtr.Base;
        SegSS = ProcessorState->ContextFrame.SegSs;
        SegDS = ProcessorState->ContextFrame.SegDs;
        SegES = ProcessorState->ContextFrame.SegEs;
        SegGS = ProcessorState->ContextFrame.SegGs;
        SegFS = ProcessorState->ContextFrame.SegFs;
    #endif
        DPRINT1("the value of segment SegSS %X\n",SegSS);
        DPRINT1("the value of segment SegDS %X\n",SegDS);
        DPRINT1("the value of segment SegES %X\n",SegES);
        DPRINT1("the value of segment SegGS %X\n",SegGS);
        DPRINT1("the value of segment SegFS %X\n",SegFS);

        /* Copy the APBoot files to proper location */
        HalpAPProtected = (PVOID)((ULONG_PTR)HalpLowStub + ((ULONG_PTR)&APEnd - (ULONG_PTR)&APBoot));
        RtlCopyMemory(HalpLowStub, &APBoot,  ((ULONG_PTR)&APEnd - (ULONG_PTR)&APBoot));
        RtlCopyMemory(HalpAPProtected, &APProtectedMode,  ((ULONG_PTR)&APProtectedModeEnd - (ULONG_PTR)&APProtectedMode));
        #if 0
        KiApplicationProcessorSpinupLoc = (PVOID)0x8054F230;
        HalpAfterProtected = (PVOID)((ULONG_PTR)HalpLowStub + ((ULONG_PTR)&APEnd - (ULONG_PTR)&APBoot) + ((ULONG_PTR)&APProtectedModeEnd - (ULONG_PTR)&APProtectedMode));
        RtlCopyMemory(HalpAfterProtected, &HaliAPBootSpinup, 0x2000 + 0x500);
#endif
        if(!HaliStartApplicationProcessor(APCountStarted))
        {
            return FALSE;
        }

        /* A small delay to give time for AP to bootup before resetting Loaderblock with a new value */
        for (ULONG i = 0; i < 10000; i++) 
        {
           KeStallExecutionProcessor(10);
        }
        /* Start was sucessful update and continue. */
        APCountStarted++;   
        return TRUE;
    }else{
        return FALSE;   
    }
}

VOID __cdecl HaliAPBootSpinup(VOID)
{   
 //  PLOADER_PARAMETER_BLOCK KeLoaderBlock = APLoaderBlock;
    USHORT dstest = 0x30;
   // ULONG_PTR EcxTest = ProcessorState->ContextFrame.Ecx;
 #if defined(__GNUC__) && (defined(__i386__))
     __asm__ volatile ("hlt");
 #elif defined(_MSC_VER) && defined(__i386__)
    __asm
    {
        sti
        cli
          
        mov   ds, dstest
        //mov   gs, 0
    
        mov ecx, 0xB8ED4000
        hlt
    }
 #else
    /* This should be impossible */
    for(;;){}
 #endif
   // KiSystemStartup(KeLoaderBlock);
    for(;;){}
}
VOID __cdecl HaliAPBootSpinupEnd(VOID){/* Mostly a dummmy function */}

BOOLEAN
HaliStartApplicationProcessor(ULONG NTProcessorCount)
{
  ULONG tmp, i, flags;

  /* save flags and disable interrupts */
  flags = __readeflags();
  _disable();

  for (i = 0; i < 10000; i++)
  {
      tmp = ApicRead(APIC_ICR0);
         /* Check Delivery Status */
        if ((tmp & APIC_ICR0_DS) == 0)
            break;
        KeStallExecutionProcessor(10);
  }

  ApicWrite(APIC_ICR1,(NTProcessorCount << 24));
  ApicWrite(APIC_ICR0, APIC_DM_INIT);
  
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
     DPRINT1("HaliStartApplicationProcessor: Could not start IPI.. \n");
     __writeeflags(flags);
     return FALSE;
  }

  ApicWrite(APIC_ICR1, (NTProcessorCount << 24));
  ApicWrite(APIC_ICR0, APIC_DM_STARTUP | ((HalpLowStubPhysicalAddress.LowPart) >> 12));

    /* Wait up to 100ms for the APIC to become ready */
  for (i = 0; i < 10000; i++) 
  {
      tmp = ApicRead(APIC_ICR0);
      /* Check Delivery Status */
      if ((tmp & APIC_ICR0_DS) == 0)
          break;
      KeStallExecutionProcessor(10);
  }
  if(i == 10000)
  {
      DPRINT1("HaliStartApplicationProcessor: Could not start IPI.. \n");
      __writeeflags(flags);
      return FALSE;
  }

  __writeeflags(flags);
  return TRUE;
}
