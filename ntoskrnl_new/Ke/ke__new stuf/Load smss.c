
Phase1InitializationDiscard
{
    ...

    ExpLoadInitialProcess(InitBuffer, ProcessParameters, ProcessEnvironment)
    {
        RtlCreateUserProcess("...\smss.exe", ...)
        {
            ZwCreateProcess()
            ZwQuerySection() -> gives us the entry point in ImageInformation
            RtlCreateUserThread(...,
                                StartAddress = ProcessInfo->ImageInformation.TransferAddress,
                                ...)
            {
                RtlpCreateUserStack(..., &InitialTeb)
                RtlInitializeContext(&Context, StartAddress, InitialTeb.StackBase)
                ZwCreateThread(..., &Context, &InitialTeb)
                {
                    PspCreateThread(..., Context, &SafeInitialTeb)
                    {
                        MmCreateTeb(..., InitalTeb)
                        Thread->StartAddress = (PVOID)KeGetContextPc(Context);
                        KeInitThread(Thread,
                                     KernelStack = NULL,
                                     SystemRoutine = PspUserThreadStartup,
                                     StartRoutine = NULL,
                                     StartContext = Thread->StartAddress,
                                     Context,
                                     TebBase,
                                     Process)
                        {
                            KernelStack = MmCreateKernelStack(FALSE, 0);
                            KiInitializeContextThread(Thread, 0xfffffa80`04a0d1a0
                                                      SystemRoutine
                                                      StartRoutine,
                                                      StartContext,
                                                      Context) -> Rip=0x7901, Rsp=0xabfff8
                            {
                                KeContextToTrapFrame(TrapFrame = 0xfffff980`053bbe70)
                                StartFrame->StartContext = StartContext; (Thread->StartAddress)
                                StartFrame->StartRoutine = StartRoutine;
                                StartFrame->SystemRoutine = SystemRoutine;
                                CtxSwitchFrame->RetAddr = KiThreadStartup;
                            }
                            KeStartThread()

                        }
                    }
                }
            }
        }

        ZwResumeThread()
    }

    ZwWaitForSingleObject(ProcessInfo->ProcessHandle, FALSE, &Timeout);
        KeWaitForSingleObject()
            KiSwapThread
                KiSwapContext
                    KiSwapContextInternal
                    ->
                    KiThreadStartup
                    {
                        PspUserThreadStartup(StartRoutine, StartContext <= StartAddress)
                            KeRaiseIrql(APC_LEVEL, &OldIrql);
                            KiInitializeUserApc(KeGetExceptionFrame(&Thread->Tcb),
                                                KeGetTrapFrame(&Thread->Tcb),
                                                NormalRoutine = PspSystemDllEntryPoint,
                                                NormalContext = StartContext, //          new!
                                                SystemArgument1 = PspSystemDllBase,
                                                SystemArgument2 = NULL);
                            {
                                KeTrapFrameToContext(TrapFrame, ExceptionFrame, &Context);
                                TrapFrame->Rip = (ULONG64)KiUserApcDispatcher;
                                AlignedRsp = Context.Rsp & ~15;

                            }
                    }

}

KiServiceExit2:
    ...
    iret->
    ntdll.KiUserApcDispatcher(NormalRoutine, NormalContext, SystemArgument1, SystemArgument2)
    {
        NormalRoutine(NormalContext, SystemArgument1, SystemArgument2)
    }

    ntdll.LdrInitializeThunk(NormalContext, SystemArgument1, SystemArgument2)
    {

    }



HalpApcInterruptHandler
{
    // fake int stack
    TrapFrame->SegCs = KGDT_R0_CODE;
    TrapFrame->Eip = TrapFrame->Eax;

    KiDeliverApc(KernelMode, NULL, TrapFrame)
    {

    }

}

  if (((Segment->WriteCopy) &&
       (Region->Protect == PAGE_*_READWRITE))
