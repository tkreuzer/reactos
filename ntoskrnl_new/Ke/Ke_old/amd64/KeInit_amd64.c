
#include <ntoskrnl.h>
#include "..\Ke_internal.h"


/* FUNCTIONS *****************************************************************/

VOID
INIT_FUNCTION
Amd64InitializeCpu(
    IN PKPCREX Pcr)
{
    /* Set GS base */
    __writemsr(MSR_GS_BASE, (ULONG64)Pcr);
    __writemsr(MSR_GS_SWAP, (ULONG64)Pcr);

    /* Load the IDTR */
    __lidt(&Amd64IdtDescriptor.Limit);

    /* LDT is unused */
    //__lldt(0);

    /* Enable fx save restore support */
    __writecr4(__readcr4() | CR4_FXSR);

    /* Enable XMMI exceptions */
    __writecr4(__readcr4() | CR4_XMMEXCPT);

    /* Enable Write-Protection */
    __writecr0(__readcr0() | CR0_WP);

    /* Disable fpu monitoring */
    __writecr0(__readcr0() & ~CR0_MP);

    /* Disable x87 fpu exceptions */
    __writecr0(__readcr0() & ~CR0_NE);

    /* Set the systemcall entry points */
    __writemsr(MSR_LSTAR, (ULONG64)KiSystemCallEntry64);
    __writemsr(MSR_CSTAR, (ULONG64)KiSystemCallEntry32);

   __writemsr(MSR_STAR, ((ULONG64)KGDT64_R0_CODE << 32) |
                        ((ULONG64)(KGDT64_R3_CMCODE|RPL_MASK) << 48));

    /* Set the flags to be cleared when doing a syscall */
    __writemsr(MSR_SYSCALL_MASK, EFLAGS_IF_MASK | EFLAGS_TF | EFLAGS_DF);

    /* Enable syscall instruction and fast FXSAVE/FXRSTOR */
    __writemsr(MSR_EFER, __readmsr(MSR_EFER) | MSR_SCE | MSR_FFXSR);
}

VOID
Amd64CaptureSpecialRegisters(PKSPECIAL_REGISTERS SpecialRegisters)
{
    /* GDT, LDT, IDT and TR registers */
    __sgdt(&SpecialRegisters->Gdtr.Limit);
    __sldt(&SpecialRegisters->Ldtr);
    __sidt(&SpecialRegisters->Idtr.Limit);
    __str(&SpecialRegisters->Tr);

    /* MXCSR */
    __stmxcsr(&SpecialRegisters->MxCsr);

    /* Control registers */
    SpecialRegisters->Cr0 = __readcr0();
    SpecialRegisters->Cr2 = __readcr2();
    SpecialRegisters->Cr3 = __readcr3();
    SpecialRegisters->Cr4 = __readcr4();
    SpecialRegisters->Cr8 = __readcr8();

    /* Debug registers */
    SpecialRegisters->KernelDr0 = __readdr(0);
    SpecialRegisters->KernelDr1 = __readdr(1);
    SpecialRegisters->KernelDr2 = __readdr(2);
    SpecialRegisters->KernelDr3 = __readdr(3);
    SpecialRegisters->KernelDr6 = __readdr(6);
    SpecialRegisters->KernelDr7 = __readdr(7);

    /* Control transfer MSRs */
    SpecialRegisters->DebugControl = __readmsr(MSR_DEGUG_CTL);
    SpecialRegisters->LastBranchToRip = __readmsr(MSR_LAST_BRANCH_TO);
    SpecialRegisters->LastBranchFromRip = __readmsr(MSR_LAST_BRANCH_FROM);
    SpecialRegisters->LastExceptionToRip = __readmsr(MSR_LAST_EXCEPTION_TO);
    SpecialRegisters->LastExceptionFromRip = __readmsr(MSR_LAST_EXCEPTION_FROM);

    /* Other MSRs */
    SpecialRegisters->MsrGsBase = __readmsr(MSR_GS_BASE);
    SpecialRegisters->MsrGsSwap = __readmsr(MSR_GS_SWAP);
    SpecialRegisters->MsrStar = __readmsr(MSR_STAR);
    SpecialRegisters->MsrLStar = __readmsr(MSR_LSTAR);
    SpecialRegisters->MsrCStar = __readmsr(MSR_CSTAR);
    SpecialRegisters->MsrSyscallMask = __readmsr(MSR_SYSCALL_MASK);
}


VOID
INIT_FUNCTION
Amd64InitializeTss(
    IN PKTSS64 Tss,
    IN UINT64 Stack)
{
    PKPCR Pcr = KeGetPcr();
    PKGDTENTRY64 TssEntry;

    /* Get pointer to the GDT entry */
    TssEntry = Amd64GetGdtEntry(Pcr->GdtBase, KGDT64_SYS_TSS);

    /* Initialize the GDT entry */
    Amd64InitGdtEntry(TssEntry, (ULONG64)Tss, sizeof(KTSS64), AMD64_TSS, 0);

    /* Zero out the TSS */
    RtlZeroMemory(Tss, sizeof(KTSS64));

    /* FIXME: I/O Map? */
    Tss->IoMapBase = 0x68;

    /* Setup ring 0 stack pointer */
    Tss->Rsp0 = Stack;

    /* Setup a stack for Double Fault Traps */
    Tss->Ist[1] = (ULONG_PTR)KiDoubleFaultStack;

    /* Setup a stack for CheckAbort Traps */
    Tss->Ist[2] = (ULONG_PTR)KiDoubleFaultStack;

    /* Setup a stack for NMI Traps */
    Tss->Ist[3] = (ULONG_PTR)KiDoubleFaultStack;

    /* Load the task register */
    __ltr(KGDT64_SYS_TSS);
}

VOID
INIT_FUNCTION
Amd64InitializePcr(
    IN PKPCREX Pcr,
    IN ULONG ProcessorNumber,
    IN PVOID DpcStack)
{
    PKGDTENTRY64 TssEntry;

    /* Capture the special register state */
    Amd64CaptureSpecialRegisters(&Pcr->Prcb.ProcessorState.SpecialRegisters);

    /* Set GDT and IDT descriptors */
    Pcr->GdtBase = (PVOID)Pcr->Prcb.ProcessorState.SpecialRegisters.Gdtr.Base;
    Pcr->IdtBase = (PVOID)Pcr->Prcb.ProcessorState.SpecialRegisters.Idtr.Base;

    /* Get TSS Entry */
    TssEntry = KxGetGdtEntry(Pcr->GdtBase, KGDT64_SYS_TSS);

    /* Get the KTSS itself */
    Pcr->TssBase = KxGetGdtDescriptorBase(TssEntry);

    /* Set DPC Stack */
    Pcr->Prcb.DpcStack = DpcStack;

    /* set features */
    Pcr->Prcb.CpuID = TRUE;

    /* Get cpu and cache information */
    x86GetCpuInfo(&Pcr->Prcb);
    x86GetCacheInformation((PKPCR)Pcr);
}


VOID
INIT_FUNCTION
KxInitializeArchitectureSpecific(PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    /* Setup the IDT */
    Amd64InitializeIDT();

    /* Prepare the CPU */
    Amd64InitializeCpu(&KiBootstrapPcr);


    Amd64InitializePcr(&KiBootstrapPcr, 0, 0);

    /* Setup the TSS */
    Amd64InitializeTss(KiBootstrapPcr.TssBase, LoaderBlock->KernelStack);
}


