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

#define PHYSICAL_ADDRESS  LARGE_INTEGER
PHYSICAL_ADDRESS HighestPhysicalAddress;
PLOADER_PARAMETER_BLOCK KeLoaderBlock;
 /* Prep some values for SMP mode */
KPROCESSOR_STATE ProcessorState;

/* FUNCTIONS *****************************************************************/

VOID
NTAPI
KeStartAllProcessors()
{
    BOOLEAN ProcessorsStarted = FALSE;
    ULONG ProcessorCount = 0;
    BOOLEAN Success = FALSE;
    KDESCRIPTOR GdtDesc, IdtDesc;
    __sgdt(&GdtDesc.Limit);
    __sidt(&IdtDesc.Limit);

    while(ProcessorsStarted == FALSE)
    {
        ProcessorCount++;
        SIZE_T APInfo = sizeof(KPCR) + sizeof(KTSS) + sizeof(ETHREAD) + GdtDesc.Limit + 1 + IdtDesc.Limit + 1; 
        HighestPhysicalAddress.QuadPart = UINT64_MAX;
        PVOID PAPInfo = MmAllocateContiguousMemory(APInfo, HighestPhysicalAddress);
        if(!PAPInfo)
        {
            DPRINT1("KeStartAllProcessors: Memory Allocation has failed");
        }

        RtlCopyMemory((PVOID)((ULONG_PTR)PAPInfo + sizeof(KPCR) + sizeof(KTSS)), (PVOID)GdtDesc.Base, GdtDesc.Limit + 1);
        RtlCopyMemory((PVOID)((ULONG_PTR)PAPInfo + sizeof(KPCR) + sizeof(KTSS) + GdtDesc.Limit + 1), (PVOID)IdtDesc.Base, IdtDesc.Limit + 1);


        PKPCR pKPcr = (PKPCR)PAPInfo;
        PKTSS pKTss = (PKTSS)((ULONG_PTR)PAPInfo + sizeof(KPCR));
        PKGDTENTRY pGdt = (PKGDTENTRY)((ULONG_PTR)PAPInfo + sizeof(KPCR) + sizeof(KTSS));
        PKIDTENTRY pIdt = (PKIDTENTRY)((ULONG_PTR)PAPInfo + sizeof(KPCR) + sizeof(KTSS) + GdtDesc.Limit + 1);
        PKTHREAD InitialThread = (PKTHREAD)((ULONG_PTR) PAPInfo + sizeof(KPCR) + sizeof(KTSS));

        ProcessorState.SpecialRegisters.Gdtr.Limit = GdtDesc.Limit;
        ProcessorState.SpecialRegisters.Gdtr.Base = (ULONG)((ULONG_PTR)PAPInfo + sizeof(KPCR) + sizeof(KTSS));
        ProcessorState.SpecialRegisters.Idtr.Limit = IdtDesc.Limit;
        ProcessorState.SpecialRegisters.Idtr.Base = (ULONG)((ULONG_PTR)PAPInfo + sizeof(KPCR) + sizeof(KTSS) + GdtDesc.Limit + 1);

        /* Prep Cr Regsters */
        ProcessorState.SpecialRegisters.Cr0 = __readcr0();
        ProcessorState.SpecialRegisters.Cr2 = __readcr2();
        ProcessorState.SpecialRegisters.Cr3 = __readcr3();
        ProcessorState.SpecialRegisters.Cr4 = __readcr4();
        PVOID KernelStack;
        PVOID DPCStack;

        KernelStack = MmCreateKernelStack(FALSE, 0);
        if (!KernelStack)
        {
            DPRINT1("KeStartAllProcessors: MmCreateKernelStack has failed for an AP");
        }

        DPCStack = MmCreateKernelStack(FALSE, 0);
        if (!DPCStack)
        {
            MmDeleteKernelStack(KernelStack, FALSE);
        }



        KiInitializePcr(ProcessorCount,
                     (PKIPCR)pKPcr,
                     pIdt, 
                     pGdt, 
                     pKTss,
                     InitialThread,
                     (PVOID)DPCStack);

        
        KeLoaderBlock->KernelStack = (ULONG_PTR)KernelStack;
        KeLoaderBlock->Prcb = (ULONG_PTR)pKPcr;
        KeLoaderBlock->Thread = (ULONG_PTR)InitialThread;

        ProcessorState.ContextFrame.SegCs = KGDT_R0_CODE;

        /* Set SS selector */
        ProcessorState.ContextFrame.SegSs = KGDT_R0_DATA;

        /* Set DS and ES selectors */
        ProcessorState.ContextFrame.SegDs = KGDT_R0_DATA;
        ProcessorState.ContextFrame.SegEs = KGDT_R0_DATA; // This is vital for rep stosd.

        /* LDT = not used ever, is set to 0 */

        /* Load TSR */
        ProcessorState.SpecialRegisters.Tr = KGDT_TSS;

        /* Clear GS */
        ProcessorState.ContextFrame.SegGs = 0;

        /* Set FS to PCR */
        ProcessorState.ContextFrame.SegFs = KGDT_R0_PCR;
        ProcessorState.ContextFrame.Ecx = (ULONG_PTR)PAPInfo;
        ProcessorState.ContextFrame.Eip = (ULONG_PTR)KiSystemStartup;
        DPRINT1("The value of EIP is %X\n", ProcessorState.ContextFrame.Eip);
        DPRINT1("The value of ECX is %X\n", ProcessorState.ContextFrame.Ecx);
        Ki386InitializeTss(pKTss, pIdt, pGdt);

        /* Actually Start the AP */
        Success = HalStartNextProcessor(KeLoaderBlock, &ProcessorState);
        if(!Success)
        {
            DPRINT1("NTOS: Ntkrnlmp has sucessfully started the APs");
            MmFreeContiguousMemory(PAPInfo);
            MmDeleteKernelStack(KernelStack, FALSE);
            MmDeleteKernelStack(DPCStack, FALSE);
            ProcessorsStarted = TRUE;
            break;
        }
    }
}
