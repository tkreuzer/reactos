VOID
NTAPI
KiUserThreadStartup(IN PKSTART_ROUTINE StartRoutine,
                     IN PVOID StartContext)
{
    PETHREAD Thread;
    PTEB Teb;
    BOOLEAN DeadThread = FALSE;
    KIRQL OldIrql;
    PAGED_CODE();

    /* Go to Passive Level */
    KeLowerIrql(PASSIVE_LEVEL);
    Thread = PsGetCurrentThread();

    /* Check if the thread is dead */
    if (Thread->DeadThread)
    {
        /* Terminate it */
        PspTerminateThreadByPointer(Thread,
                                    STATUS_THREAD_IS_TERMINATING,
                                    TRUE);
        ASSERT(FALSE);
    }

    /* Get the Locale ID and save Preferred Proc */
    Teb = NtCurrentTeb();
    Teb->CurrentLocale = MmGetSessionLocaleId();
    Teb->IdealProcessor = Thread->Tcb.IdealProcessor;

    /* Check if this is a dead thread, or if we're hiding */
    if (!Thread->HideFromDebugger)
    {
        /* We're not, so notify the debugger */
        DbgkCreateThread(Thread, StartContext);
    }

    /* Check if the Prefetcher is enabled */
    //if (CcPfEnablePrefetcher)
    {
        /* FIXME: Prepare to prefetch this process */
    }

    /* Raise to APC */
    KeRaiseIrql(APC_LEVEL, &OldIrql);

    // initialize the APC

    /* Lower it back to passive */
    KeLowerIrql(PASSIVE_LEVEL);


    /* Do we have a cookie set yet? */
    while (!SharedUserData->Cookie)
    {
        LARGE_INTEGER SystemTime;
        ULONG NewCookie;
        PKPRCB Prcb;

        /* Generate a new cookie */
        KeQuerySystemTime(&SystemTime);
        Prcb = KeGetCurrentPrcb();
        NewCookie = (Prcb->MmPageFaultCount ^ Prcb->InterruptTime ^
                    SystemTime.u.LowPart ^ SystemTime.u.HighPart ^
                    (ULONG)(ULONG_PTR)&SystemTime);

        /* Set the new cookie*/
        InterlockedCompareExchange((LONG*)&SharedUserData->Cookie,
                                   NewCookie,
                                   0);
    }
}

