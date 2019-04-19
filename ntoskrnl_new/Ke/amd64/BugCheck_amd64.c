
#include <ntoskrnl.h>
#include "../Ke_internal.h"

VOID
NTAPI
KxDumpProcessorState(
    PKPROCESSOR_STATE ProcessorState)
{
    PCONTEXT Ctx = &ProcessorState->ContextFrame;
    PKSPECIAL_REGISTERS SpReg = &ProcessorState->SpecialRegisters;

    VidPrint("  RAX: %p   R8:  %p   R12: %p\n", Ctx->Rax, Ctx->R8, Ctx->R12);
    VidPrint("  RBX: %p   R9:  %p   R13: %p\n", Ctx->Rbx, Ctx->R9, Ctx->R13);
    VidPrint("  RCX: %p   R10: %p   R14: %p\n", Ctx->Rcx, Ctx->R10, Ctx->R14);
    VidPrint("  RDX: %p   R11: %p   R15: %p\n", Ctx->Rdx, Ctx->R11, Ctx->R15);
    VidPrint("  RSI: %p   RDI: %p   RBP: %p\n", Ctx->Rsi, Ctx->Rdi, Ctx->Rbp);
    VidPrint("\n");
    VidPrint("  RIP: %p   RSP: %p   EFLAGS: %.8lx\n", Ctx->Rip, Ctx->EFlags);
    VidPrint("\n");
    VidPrint("  CS: %.4x    DS: %.4x    ES: %.4x    FS: %.4x    GS: %.4x    SS: %.4x\n",
             Ctx->SegCs, Ctx->SegDs, Ctx->SegEs, Ctx->SegFs, Ctx->SegGs, Ctx->SegSs);
    VidPrint("\n");
    VidPrint("  DR0: %p   DR2: %p   DR6: %p\n", Ctx->Dr0, Ctx->Dr2, Ctx->Dr6);
    VidPrint("  DR1: %p   DR3: %p   DR7: %p\n", Ctx->Dr1, Ctx->Dr3, Ctx->Dr7);
    VidPrint("\n");
    VidPrint("  DebugControl:    %p MxCsr: %.8lx\n", Ctx->DebugControl, Ctx->MxCsr);
    VidPrint("  LastBranchToRip: %p LastBranchFromRip: %p\n", Ctx->LastBranchToRip, Ctx->LastBranchFromRip);
    VidPrint("  LastExceptToRip: %p LastExceptFromRip: %p\n", Ctx->LastExceptionToRip, Ctx->LastExceptionFromRip);
    VidPrint("\n");

    VidPrint("  CR0: %p   CR2: %p   CR3: %p\n", SpReg->Cr0, SpReg->Cr2, SpReg->Cr3);
    VidPrint("  CR4: %p   CR8: %p\n", SpReg->Cr4, SpReg->Cr8);
    VidPrint("  MsrGsBase: %p  MsrGsSwap: %p\n", SpReg->MsrGsBase);
    VidPrint("  MsrStar:   %p  MsrLStar:  %p\n", SpReg->MsrStar, SpReg->MsrLStar);
    VidPrint("  MsrCStar:  %p  MsrSyscallMask: %p\n", SpReg->MsrCStar, SpReg->MsrSyscallMask);
    VidPrint("  Gdtr: %p  Idtr: %p  Tr: %.4x  Ldtr: %.4x\n",
              SpReg->Gdtr, SpReg->Idtr, SpReg->Tr, SpReg->Ldtr);
}

