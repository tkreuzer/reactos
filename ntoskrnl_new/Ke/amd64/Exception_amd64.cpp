


PVOID KeLastBranchMSR;

VOID
KxGetExceptionContext (
    _Out_ PCONTEXT Context,
    _In_ PKTRAP_FRAME TrapFrame,
    _In_ PKEXCEPTION_FRAME ExceptionFrame)
{
    ASSERT(ExceptionFrame != NULL);

    Context->ContextFlags = CONTEXT_ALL | CONTEXT_AMD64;

    Context->MxCsr = TrapFrame->MxCsr;
    Context->SegCs = TrapFrame->SegCs;
    Context->SegDs = TrapFrame->SegDs;
    Context->SegEs = TrapFrame->SegEs;
    Context->SegFs = TrapFrame->SegFs;
    Context->SegGs = TrapFrame->SegGs;
    Context->SegSs = TrapFrame->SegSs;
    Context->EFlags = TrapFrame->EFlags;
    Context->Dr0 = TrapFrame->Dr0;
    Context->Dr1 = TrapFrame->Dr1;
    Context->Dr2 = TrapFrame->Dr2;
    Context->Dr3 = TrapFrame->Dr3;
    Context->Dr6 = TrapFrame->Dr6;
    Context->Dr7 = TrapFrame->Dr7;
    Context->Rax = TrapFrame->Rax;
    Context->Rcx = TrapFrame->Rcx;
    Context->Rdx = TrapFrame->Rdx;
    Context->Rbx = TrapFrame->Rbx;
    Context->Rsp = TrapFrame->Rsp;
    Context->Rbp = TrapFrame->Rbp;
    Context->Rsi = TrapFrame->Rsi;
    Context->Rdi = TrapFrame->Rdi;
    Context->R8 = TrapFrame->R8;
    Context->R9 = TrapFrame->R9;
    Context->R10 = TrapFrame->R10;
    Context->R11 = TrapFrame->R11;
    Context->R12 = ExceptionFrame->R12;
    Context->R13 = ExceptionFrame->R13;
    Context->R14 = ExceptionFrame->R14;
    Context->R15 = ExceptionFrame->R15;
    Context->Rip = TrapFrame->Rip;
    Context->Xmm0 = TrapFrame->Xmm0;
    Context->Xmm1 = TrapFrame->Xmm1;
    Context->Xmm2 = TrapFrame->Xmm2;
    Context->Xmm3 = TrapFrame->Xmm3;
    Context->Xmm4 = TrapFrame->Xmm4;
    Context->Xmm5 = TrapFrame->Xmm5;
    Context->Xmm6 = ExceptionFrame->Xmm6;
    Context->Xmm7 = ExceptionFrame->Xmm7;
    Context->Xmm8 = ExceptionFrame->Xmm8;
    Context->Xmm9 = ExceptionFrame->Xmm9;
    Context->Xmm10 = ExceptionFrame->Xmm10;
    Context->Xmm11 = ExceptionFrame->Xmm11;
    Context->Xmm12 = ExceptionFrame->Xmm12;
    Context->Xmm13 = ExceptionFrame->Xmm13;
    Context->Xmm14 = ExceptionFrame->Xmm14;
    Context->Xmm15 = ExceptionFrame->Xmm15;
    Context->DebugControl = TrapFrame->DebugControl;
    Context->LastBranchToRip = TrapFrame->LastBranchToRip;
    Context->LastBranchFromRip = TrapFrame->LastBranchFromRip;
    Context->LastExceptionToRip = TrapFrame->LastExceptionToRip;
    Context->LastExceptionFromRip = TrapFrame->LastExceptionFromRip;
}

VOID
KxSetExceptionContext(
    _In_ PCONTEXT Context,
    _out_ PKTRAP_FRAME TrapFrame,
    _Out_ PKEXCEPTION_FRAME ExceptionFrame)
{
    ULONG ContextFlags = Context->ContextFlags & ~CONTEXT_AMD64;
    ASSERT(ExceptionFrame != NULL);

    Context->ContextFlags = CONTEXT_ALL | CONTEXT_AMD64;

    if (ContextFlags & CONTEXT_INTEGER)
    {
        TrapFrame->Rax = Context->Rax;
        TrapFrame->Rbx = Context->Rbx;
        TrapFrame->Rcx = Context->Rcx;
        TrapFrame->Rdx = Context->Rdx;
        TrapFrame->Rsi = Context->Rsi;
        TrapFrame->Rdi = Context->Rdi;
        TrapFrame->Rbp = Context->Rbp;
        TrapFrame->R8 = Context->R8;
        TrapFrame->R9 = Context->R9;
        TrapFrame->R10 = Context->R10;
        TrapFrame->R11 = Context->R11;
        ExceptionFrame->R12 = Context->R12;
        ExceptionFrame->R13 = Context->R13;
        ExceptionFrame->R14 = Context->R14;
        ExceptionFrame->R15 = Context->R15;
    }

    if (ContextFlags & CONTEXT_CONTROL)
    {
        TrapFrame->SegSs = Context->SegSs;
        TrapFrame->Rsp = Context->Rsp;
        TrapFrame->SegCs = Context->SegCs;
        TrapFrame->Rip = Context->Rip;
        TrapFrame->EFlags = Context->EFlags;
    }

    if (ContextFlags & CONTEXT_SEGMENTS)
    {
        TrapFrame->SegDs = Context->SegDs;
        TrapFrame->SegEs = Context->SegEs;
        TrapFrame->SegFs = Context->SegFs;
        TrapFrame->SegGs = Context->SegGs;
    }

    if (ContextFlags & CONTEXT_FLOATING_POINT)
    {
        TrapFrame->Xmm0 = Context->Xmm0;
        TrapFrame->Xmm1 = Context->Xmm1;
        TrapFrame->Xmm2 = Context->Xmm2;
        TrapFrame->Xmm3 = Context->Xmm3;
        TrapFrame->Xmm4 = Context->Xmm4;
        TrapFrame->Xmm5 = Context->Xmm5;
        ExceptionFrame->Xmm6 = Context->Xmm6;
        ExceptionFrame->Xmm7 = Context->Xmm7;
        ExceptionFrame->Xmm8 = Context->Xmm8;
        ExceptionFrame->Xmm9 = Context->Xmm9;
        ExceptionFrame->Xmm10 = Context->Xmm10;
        ExceptionFrame->Xmm11 = Context->Xmm11;
        ExceptionFrame->Xmm12 = Context->Xmm12;
        ExceptionFrame->Xmm13 = Context->Xmm13;
        ExceptionFrame->Xmm14 = Context->Xmm14;
        ExceptionFrame->Xmm15 = Context->Xmm15;
    }

    if (ContextFlags & CONTEXT_DEBUG_REGISTERS)
    {
        TrapFrame->Dr0 = Context->Dr0;
        TrapFrame->Dr1 = Context->Dr1;
        TrapFrame->Dr2 = Context->Dr2;
        TrapFrame->Dr3 = Context->Dr3;
        TrapFrame->Dr6 = Context->Dr6;
        TrapFrame->Dr7 = Context->Dr7;
    }

    TrapFrame->MxCsr = Context->MxCsr;
}

