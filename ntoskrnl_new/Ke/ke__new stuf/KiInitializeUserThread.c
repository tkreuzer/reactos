
/*! \name KiInitializeUserThread
 *
 *  \brief Prepares a startup stack frame for user threads so that the thread
 *      will start at KiThreadStartup, call KiUserThreadStartup system routine
 *      and finally exit through KiServiceExit2 into usermode to the usermode
 *      entrypoint ntdll.LdInitializeThunk, passing the executable entrypoint
 *      in rcx. LdInitializeThunk will then create a context and call LdrpInit
 *      STATUS: experimental
 */
VOID
KiInitializeUserThread(
    IN PKTHREAD Thread,
    IN PVOID AddressOfEntryPoint)
{
    PKUINIT_FRAME InitFrame;

    /* Make sure we got the expected parameters */
    ASSERT(SystemRoutine == PspUserThreadStartup);
    ASSERT(StartRoutine == NULL);
    ASSERT(StartContext != 0);
    ASSERT(StartContext < MmHighestUserAddress);

    /* Set up the Initial Frame */
    InitFrame = ((PKUINIT_FRAME)Thread->InitialStack) - 1;
    Thread->KernelStack = (PVOID)InitFrame;


    StartFrame = &InitFrame->StartFrame;
    CtxSwitchFrame = &InitFrame->CtxSwitchFrame;


    /* Tell the thread it will run in User Mode */
    Thread->PreviousMode = UserMode;

    // FIXME Setup the Fx Area

    /* Set the Thread's NPX State */
    Thread->NpxState = 0xA;
    Thread->Header.NpxIrql = PASSIVE_LEVEL;

    /* Make sure, we have control registers, disable debug registers */
    ASSERT((Context->ContextFlags & CONTEXT_CONTROL) == CONTEXT_CONTROL);
    ContextFlags = Context->ContextFlags & ~CONTEXT_DEBUG_REGISTERS;

    /* Setup the Trap Frame */
    TrapFrame = &InitFrame->TrapFrame;

    /* Zero out the trap frame */
    RtlZeroMemory(TrapFrame, sizeof(KTRAP_FRAME));

    /* Set the user mode entrypoint to ntdll.LdrInitializeThunk */
    TrapFrame->Rip = (ULONG64)PspSystemDllEntryPoint;
    TrapFrame->SegCs = KGDT64_R3_CODE | RPL_MASK;

    /* Set SS, DS, ES's RPL Mask properly */
    TrapFrame->SegSs |= RPL_MASK;
    TrapFrame->SegDs |= RPL_MASK;
    TrapFrame->SegEs |= RPL_MASK;
    TrapFrame->Dr7 = 0;

    /* Set the previous mode as user */
    TrapFrame->PreviousMode = UserMode;

    /* Terminate the Exception Handler List */
    TrapFrame->ExceptionFrame = 0;

    /* We "return" to usermode through the trap exit code */
    InitFrame->StartFrame.Return = (ULONG64)KiServiceExit2;

    /* Set up the rest of the start frame */
    InitFrame->StartFrame.P1Home = 0;
    InitFrame->StartFrame.P2Home = 0;
    InitFrame->StartFrame.P3Home = 0;
    InitFrame->StartFrame.P4Home = (ULONG64)KiUserThreadStartup;
    InitFrame->StartFrame.P5Home = 0;

    /* Set up the Context Switch Frame */
    CtxSwitchFrame->Return = (ULONG64)KiThreadStartup;
    CtxSwitchFrame->ApcBypass = FALSE;
}

