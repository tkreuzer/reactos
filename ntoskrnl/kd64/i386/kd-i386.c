/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            ntoskrnl/kd64/i386/kdapi-i386.c
 * PURPOSE:         KD64 i386 Support
 * PROGRAMMERS:     Alex Ionescu (alex.ionescu@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* PRIVATE FUNCTIONS *********************************************************/

VOID
NTAPI
KdpSysGetVersion(IN PDBGKD_GET_VERSION64 Version)
{
    /* Copy the version block */
    RtlCopyMemory(Version, &KdVersionBlock, sizeof(DBGKD_GET_VERSION64));
}

VOID
NTAPI
KdpSetContextState(IN PDBGKD_WAIT_STATE_CHANGE64 WaitStateChange,
                   IN PCONTEXT Context)
{
    PKPRCB Prcb = KeGetCurrentPrcb();

    /* Copy i386 specific debug registers */
    WaitStateChange->ControlReport.Dr6 = Prcb->ProcessorState.SpecialRegisters.
                                         KernelDr6;
    WaitStateChange->ControlReport.Dr7 = Prcb->ProcessorState.SpecialRegisters.
                                         KernelDr7;

    /* Copy i386 specific segments */
    WaitStateChange->ControlReport.SegCs = (USHORT)Context->SegCs;
    WaitStateChange->ControlReport.SegDs = (USHORT)Context->SegDs;
    WaitStateChange->ControlReport.SegEs = (USHORT)Context->SegEs;
    WaitStateChange->ControlReport.SegFs = (USHORT)Context->SegFs;

    /* Copy EFlags */
    WaitStateChange->ControlReport.EFlags = Context->EFlags;

    /* Set Report Flags */
    WaitStateChange->ControlReport.ReportFlags = REPORT_INCLUDES_SEGS;
    if (WaitStateChange->ControlReport.SegCs == KGDT_R0_CODE)
    {
        WaitStateChange->ControlReport.ReportFlags = REPORT_INCLUDES_CS;
    }
}

BOOLEAN
NTAPI
KdpTrap(IN PKTRAP_FRAME TrapFrame,
        IN PKEXCEPTION_FRAME ExceptionFrame,
        IN PEXCEPTION_RECORD ExceptionRecord,
        IN PCONTEXT ContextRecord,
        IN KPROCESSOR_MODE PreviousMode,
        IN BOOLEAN SecondChanceException)
{
    BOOLEAN Unload = FALSE;
    ULONG Eip, Eax;
    BOOLEAN Status = FALSE;

    /*
     * Check if we got a STATUS_BREAKPOINT with a SubID for Print, Prompt or
     * Load/Unload symbols.
     */
    if ((ExceptionRecord->ExceptionCode == STATUS_BREAKPOINT) &&
        (ExceptionRecord->ExceptionInformation[0] != BREAKPOINT_BREAK))
    {
        /* Save EIP */
        Eip = ContextRecord->Eip;

        /* Check what kind of operation was requested from us */
        switch (ExceptionRecord->ExceptionInformation[0])
        {
            /* DbgPrint */
            case BREAKPOINT_PRINT:

                /* Call the worker routine */
                Eax = KdpPrint(ContextRecord->Ebx,
                               ContextRecord->Edi,
                               (LPSTR)ExceptionRecord->ExceptionInformation[1],
                               (ULONG)ExceptionRecord->ExceptionInformation[2],
                               PreviousMode,
                               TrapFrame,
                               ExceptionFrame,
                               &Status);

                /* Update the return value for the caller */
                ContextRecord->Eax = Eax;
                break;

            /* DbgPrompt */
            case BREAKPOINT_PROMPT:

                /* Call the worker routine */
                while (TRUE);
                Eax = 0;
                Status = TRUE;

                /* Update the return value for the caller */
                ContextRecord->Eax = Eax;
                break;

            /* DbgUnloadSymbols */
            case BREAKPOINT_UNLOAD_SYMBOLS:

                /* Drop into the load case below, with the unload parameter */
                Unload = TRUE;

            /* DbgLoadSymbols */
            case BREAKPOINT_LOAD_SYMBOLS:

                /* Call the worker routine */
                KdpSymbol((PVOID)ExceptionRecord->ExceptionInformation[1],
                          (PVOID)ExceptionRecord->ExceptionInformation[2],
                          Unload,
                          PreviousMode,
                          ContextRecord,
                          TrapFrame,
                          ExceptionFrame);
                Status = TRUE;
                break;

            /* DbgCommandString*/
            case BREAKPOINT_COMMAND_STRING:

                /* Call the worker routine */
                while (TRUE);
                Status = TRUE;

            /* Anything else, do nothing */
            default:

                /* Get out */
                break;
        }

        /*
         * If EIP was not updated, we'll increment it ourselves so execution
         * continues past the breakpoint.
         */
        if (ContextRecord->Eip == Eip) ContextRecord->Eip++;
    }
    else
    {
        /* Call the worker routine */
        Status = KdpReport(TrapFrame,
                           ExceptionFrame,
                           ExceptionRecord,
                           ContextRecord,
                           PreviousMode,
                           SecondChanceException);
    }

    /* Return TRUE or FALSE to caller */
    return Status;
}