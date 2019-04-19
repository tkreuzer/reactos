

#include <ntoskrnl.h>
#include "..\Ke_internal.h"

// FIXME!!!
void MmAccessFault(void) { }
void KiDeliverApc(void) { }
void KiDispatchInterrupt(void) { }

extern KI_INTERRUPT_DISPATCH_ENTRY KiUnexpectedRange[256];

VOID KiDivideErrorFault(VOID);
VOID KiDebugTrapOrFault(VOID);
VOID KiNmiInterrupt(VOID);
VOID KiBreakpointTrap(VOID);
VOID KiOverflowTrap(VOID);
VOID KiBoundFault(VOID);
VOID KiInvalidOpcodeFault(VOID);
VOID KiNpxNotAvailableFault(VOID);
VOID KiDoubleFaultAbort(VOID);
VOID KiNpxSegmentOverrunAbort(VOID);
VOID KiInvalidTssFault(VOID);
VOID KiSegmentNotPresentFault(VOID);
VOID KiStackFault(VOID);
VOID KiGeneralProtectionFault(VOID);
VOID KiPageFault(VOID);
VOID KiFloatingErrorFault(VOID);
VOID KiAlignmentFault(VOID);
VOID KiMcheckAbort(VOID);
VOID KiXmmException(VOID);
VOID KiApcInterrupt(VOID);
VOID KiRaiseAssertion(VOID);
VOID KiDebugServiceTrap(VOID);
VOID KiDpcInterrupt(VOID);
VOID KiIpiInterrupt(VOID);

static KIDTENTRY64 Amd64Idt[256];
KDESCRIPTOR Amd64IdtDescriptor = {{0}, sizeof(Amd64Idt) - 1, Amd64Idt};

static KIDT_INIT
Amd64InterruptInitTable[] =
{
  /* Id,   Dpl,  IST,  ServiceRoutine */
    {0x00, 0x00, 0x00, KiDivideErrorFault},
    {0x01, 0x00, 0x00, KiDebugTrapOrFault},
    {0x02, 0x00, 0x03, KiNmiInterrupt},
    {0x03, 0x03, 0x00, KiBreakpointTrap},
    {0x04, 0x03, 0x00, KiOverflowTrap},
    {0x05, 0x00, 0x00, KiBoundFault},
    {0x06, 0x00, 0x00, KiInvalidOpcodeFault},
    {0x07, 0x00, 0x00, KiNpxNotAvailableFault},
    {0x08, 0x00, 0x01, KiDoubleFaultAbort},
    {0x09, 0x00, 0x00, KiNpxSegmentOverrunAbort},
    {0x0A, 0x00, 0x00, KiInvalidTssFault},
    {0x0B, 0x00, 0x00, KiSegmentNotPresentFault},
    {0x0C, 0x00, 0x00, KiStackFault},
    {0x0D, 0x00, 0x00, KiGeneralProtectionFault},
    {0x0E, 0x00, 0x00, KiPageFault},
    {0x10, 0x00, 0x00, KiFloatingErrorFault},
    {0x11, 0x00, 0x00, KiAlignmentFault},
    {0x12, 0x00, 0x02, KiMcheckAbort},
    {0x13, 0x00, 0x00, KiXmmException},
    {0x1F, 0x00, 0x00, KiApcInterrupt},
    {0x2C, 0x03, 0x00, KiRaiseAssertion},
    {0x2D, 0x03, 0x00, KiDebugServiceTrap},
    {0x2F, 0x00, 0x00, KiDpcInterrupt},
    {0xE1, 0x00, 0x00, KiIpiInterrupt},
    {0, 0, 0, 0}
};

VOID
INIT_FUNCTION
Amd64InitializeIDT(VOID)
{
    int i, j;

    /* Loop all IDT entries */
    for (j = i = 0; i < 256; i++)
    {
        ULONG64 Offset;

        /* Check if the current initializer is for this entry */
        if (Amd64InterruptInitTable[j].InterruptId == i)
        {
            /* It is, so use it's settings */
            Offset = (ULONG64)Amd64InterruptInitTable[j].ServiceRoutine;
            Amd64Idt[i].Dpl = Amd64InterruptInitTable[j].Dpl;
            Amd64Idt[i].IstIndex = Amd64InterruptInitTable[j].IstIndex;

            /* Go to the next initializer */
            j++;
        }
        else
        {
            /* This is an uninitialized entry */
            Offset = (ULONG64)&KiUnexpectedRange[i]._Op_push;
            Amd64Idt[i].Dpl = 0;
            Amd64Idt[i].IstIndex = 0;
        }

        /* Set the rest of the fields */
        Amd64Idt[i].OffsetLow = Offset & 0xffff;
        Amd64Idt[i].Selector = KGDT64_R0_CODE;
        Amd64Idt[i].Type = 0x0e;
        Amd64Idt[i].Reserved0 = 0;
        Amd64Idt[i].Present = 1;
        Amd64Idt[i].OffsetMiddle = (Offset >> 16) & 0xffff;
        Amd64Idt[i].OffsetHigh = (Offset >> 32);
        Amd64Idt[i].Reserved1 = 0;
    }
}

NTSTATUS
NTAPI
KiNpxNotAvailableFaultHandler(
    IN PKTRAP_FRAME TrapFrame)
{
    UNIMPLEMENTED;
    KeBugCheckWithTf(TRAP_CAUSE_UNKNOWN, 13, 0, 0, 1, TrapFrame);
    return -1;
}

NTSTATUS
NTAPI
KiGeneralProtectionFaultHandler(
    IN PKTRAP_FRAME TrapFrame)
{
    PUCHAR Instructions;

    /* Check for user-mode GPF */
    if (TrapFrame->SegCs & 3)
    {
        UNIMPLEMENTED;
        ASSERT(FALSE);
    }

    /* Check for lazy segment load */
    if (TrapFrame->SegDs != (KGDT64_R3_DATA | RPL_MASK))
    {
        /* Fix it */
        TrapFrame->SegDs = (KGDT64_R3_DATA | RPL_MASK);
        return STATUS_SUCCESS;
    }
    else if (TrapFrame->SegEs != (KGDT64_R3_DATA | RPL_MASK))
    {
        /* Fix it */
        TrapFrame->SegEs = (KGDT64_R3_DATA | RPL_MASK);
        return STATUS_SUCCESS;
    }

    /* Check for nested exception */
    if ((TrapFrame->Rip >= (ULONG64)KiGeneralProtectionFaultHandler) &&
        (TrapFrame->Rip < (ULONG64)KiGeneralProtectionFaultHandler))
    {
        /* Not implemented */
        UNIMPLEMENTED;
        ASSERT(FALSE);
    }

    /* Get Instruction Pointer */
    Instructions = (PUCHAR)TrapFrame->Rip;

    /* Check for IRET */
    if (Instructions[0] == 0x48 && Instructions[1] == 0xCF)
    {
        /* Not implemented */
        UNIMPLEMENTED;
        ASSERT(FALSE);
    }

    /* Check for RDMSR/WRMSR */
    if ((Instructions[0] == 0xF) &&            // 2-byte opcode
        ((Instructions[1] == 0x30) ||        // RDMSR
         (Instructions[1] == 0x32)))         // WRMSR
    {
        /* Unknown CPU MSR, so raise an access violation */
        return STATUS_ACCESS_VIOLATION;
    }

    ASSERT(FALSE);
    return STATUS_UNSUCCESSFUL;
}

NTSTATUS
NTAPI
KiXmmExceptionHandler(
    IN PKTRAP_FRAME TrapFrame)
{
    UNIMPLEMENTED;
    KeBugCheckWithTf(TRAP_CAUSE_UNKNOWN, 13, 0, 0, 1, TrapFrame);
    return -1;
}

