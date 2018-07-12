/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            ntoskrnl/ke/amd64/thrdini.c
 * PURPOSE:         amd64 Thread Context Creation
 * PROGRAMMER:      Timo Kreuzer (timo.kreuzer@reactos.org)
 *                  Alex Ionescu (alex@relsoft.net)
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>
#if 0
typedef struct _KSWITCH_FRAME
{
    PVOID ExceptionList;
    BOOLEAN ApcBypassDisable;
    PVOID RetAddr;
} KSWITCH_FRAME, *PKSWITCH_FRAME;

typedef struct _KSTART_FRAME
{
    PKSYSTEM_ROUTINE SystemRoutine;
    PKSTART_ROUTINE StartRoutine;
    PVOID StartContext;
    BOOLEAN UserThread;
} KSTART_FRAME, *PKSTART_FRAME;

extern void KiInvalidSystemThreadStartupExit(void);
extern void KiUserThreadStartupExit(void);
extern void KiServiceExit3(void);

typedef struct _KUINIT_FRAME
{
    KSWITCH_FRAME CtxSwitchFrame;
    KSTART_FRAME StartFrame;
    KTRAP_FRAME TrapFrame;
    FX_SAVE_AREA FxSaveArea;
} KUINIT_FRAME, *PKUINIT_FRAME;

typedef struct _KKINIT_FRAME
{
    KSWITCH_FRAME CtxSwitchFrame;
    KSTART_FRAME StartFrame;
    FX_SAVE_AREA FxSaveArea;
} KKINIT_FRAME, *PKKINIT_FRAME;
#endif

/* FUNCTIONS *****************************************************************/

VOID
NTAPI
KiInitializeContextThread(IN PKTHREAD Thread,
                           IN PKSYSTEM_ROUTINE SystemRoutine,
                           IN PKSTART_ROUTINE StartRoutine,
                           IN PVOID StartContext,
                           IN PCONTEXT Context)
{
    //PFXSAVE_FORMAT FxSaveFormat;
    PKSTART_FRAME StartFrame;
    PKSWITCH_FRAME CtxSwitchFrame;
    PKTRAP_FRAME TrapFrame;
    ULONG ContextFlags;

    /* Check if this is a With-Context Thread */
    if (Context)
    {
        PKUINIT_FRAME InitFrame;

        /* Set up the Initial Frame */
        InitFrame = ((PKUINIT_FRAME)Thread->InitialStack) - 1;
        StartFrame = &InitFrame->StartFrame;
        CtxSwitchFrame = &InitFrame->CtxSwitchFrame;

        /* Zero out the trap frame and save area */
        RtlZeroMemory(&InitFrame->TrapFrame,
                      KTRAP_FRAME_LENGTH + sizeof(FX_SAVE_AREA));

        /* Setup the Fx Area */
        FxSaveArea = &InitFrame->FxSaveArea;

            /* Get the FX Save Format Area */
            FxSaveFormat = (PFXSAVE_FORMAT)Context->ExtendedRegisters;

            /* Set an initial state */
            FxSaveFormat->ControlWord = 0x27F;
            FxSaveFormat->StatusWord = 0;
            FxSaveFormat->TagWord = 0;
            FxSaveFormat->ErrorOffset = 0;
            FxSaveFormat->ErrorSelector = 0;
            FxSaveFormat->DataOffset = 0;
            FxSaveFormat->DataSelector = 0;
            FxSaveFormat->MXCsr = 0x1F80;


        /* Set an intial NPX State */
        Context->FloatSave.Cr0NpxState = 0;
        FxSaveArea->Cr0NpxState = 0;
        FxSaveArea->NpxSavedCpu = 0;

        /* Now set the context flags depending on XMM support */
        ContextFlags |= (KeI386FxsrPresent) ? CONTEXT_EXTENDED_REGISTERS :
                                              CONTEXT_FLOATING_POINT;

        /* Set the Thread's NPX State */
        Thread->NpxState = NPX_STATE_NOT_LOADED;
        Thread->Header.NpxIrql = PASSIVE_LEVEL;

        /* Make sure, we have control registers, disable debug registers */
        ASSERT((Context->ContextFlags & CONTEXT_CONTROL) == CONTEXT_CONTROL);
        ContextFlags = Context->ContextFlags & ~CONTEXT_DEBUG_REGISTERS;

        /* Setup the Trap Frame */
        TrapFrame = &InitFrame->TrapFrame;

        /* Zero out the trap frame */
        RtlZeroMemory(TrapFrame, sizeof(KTRAP_FRAME));

        /* Set up a trap frame from the context. */
        KeContextToTrapFrame(Context,
                             &InitFrame->ExceptionFrame,
                             TrapFrame,
                             CONTEXT_AMD64 | ContextFlags,
                             UserMode);

        /* Set SS, DS, ES's RPL Mask properly */
        TrapFrame->HardwareSegSs |= RPL_MASK;
        TrapFrame->SegDs |= RPL_MASK;
        TrapFrame->SegEs |= RPL_MASK;
        TrapFrame->Dr7 = 0;

        /* Set the debug mark */
        TrapFrame->DbgArgMark = 0xBADB0D00;

        /* Set the previous mode as user */
        TrapFrame->PreviousPreviousMode = UserMode;

        /* Terminate the Exception Handler List */
        TrapFrame->ExceptionList = EXCEPTION_CHAIN_END;

        /* We return to ... */
        StartFrame->Return = (ULONG64)KiServiceExit2;
    }
    else
    {
        PKKINIT_FRAME InitFrame;

        /* Setup the Fx Area */
        FxSaveArea = &InitFrame->FxSaveArea;
        RtlZeroMemory(FxSaveArea, sizeof(FX_SAVE_AREA));

        /* Set the stub FX area */
        FxSaveArea->U.FxArea.ControlWord = 0x27F;
        FxSaveArea->U.FxArea.MXCsr = 0x1F80;

        /* Tell the thread it will run in Kernel Mode */
        Thread->PreviousMode = KernelMode;

        /* No NPX State */
        Thread->NpxState = NPX_STATE_NOT_LOADED;

        /* We have no return address! */
        StartFrame->Return = 0;
    }

    /* Set up the Context Switch Frame */
    CtxSwitchFrame->Return = (ULONG64)KiThreadStartup;
    CtxSwitchFrame->ApcBypass = FALSE;

    StartFrame->P1Home = (ULONG64)StartRoutine;
    StartFrame->P2Home = (ULONG64)StartContext;
    StartFrame->P3Home = 0;
    StartFrame->P4Home = (ULONG64)SystemRoutine;
    StartFrame->Reserved = 0;

    /* Now setup the remaining data for KiThreadStartup */
    StartFrame->StartContext = StartContext;
    StartFrame->StartRoutine = StartRoutine;
    StartFrame->SystemRoutine = SystemRoutine;
}

BOOLEAN
KiSwapContextResume(
    IN PKTHREAD NewThread,
    IN PKTHREAD OldThread,
    IN BOOLEAN ApcBypass)
{
    PKIPCR Pcr = (PKIPCR)KeGetPcr();
    PKPROCESS OldProcess, NewProcess;

    /* Setup ring 0 stack pointer */
    Pcr->TssBase->Rsp0 = (ULONG64)NewThread->InitialStack; // FIXME: NPX save area?
    Pcr->Prcb.RspBase = Pcr->TssBase->Rsp0;

    /* Now we are the new thread. Check if it's in a new process */
    OldProcess = OldThread->ApcState.Process;
    NewProcess = NewThread->ApcState.Process;
    if (OldProcess != NewProcess)
    {
        /* Switch address space and flush TLB */
        __writecr3(NewProcess->DirectoryTableBase[0]);

        /* Set new TSS fields */
        //Pcr->TssBase->IoMapBase = NewProcess->IopmOffset;
    }

    /* Set TEB pointer and GS base */
    Pcr->NtTib.Self = (PVOID)NewThread->Teb;
    if (NewThread->Teb)
    {
       /* This will switch the usermode gs */
       __writemsr(MSR_GS_SWAP, (ULONG64)NewThread->Teb);
    }

    /* Increase context switch count */
    Pcr->ContextSwitches++;
    NewThread->ContextSwitches++;

    /* DPCs shouldn't be active */
    if (Pcr->Prcb.DpcRoutineActive)
    {
        /* Crash the machine */
        KeBugCheckEx(ATTEMPTED_SWITCH_FROM_DPC,
                     (ULONG_PTR)OldThread,
                     (ULONG_PTR)NewThread,
                     (ULONG_PTR)OldThread->InitialStack,
                     0);
    }

    /* Kernel APCs may be pending */
    if (NewThread->ApcState.KernelApcPending)
    {
        /* Are APCs enabled? */
        if (!NewThread->SpecialApcDisable)
        {
            /* Request APC delivery */
            if (!ApcBypass)
                HalRequestSoftwareInterrupt(APC_LEVEL);
            else
                return TRUE;
        }
    }

    /* Return stating that no kernel APCs are pending*/
    return FALSE;
}

/* EOF */


