
#include <asm.inc>
#include <asmdef.inc>

EXTERN KiServiceExit2:PROC

.code

PUBLIC KxUserThreadEntryPoint
KxUserThreadEntryPoint:
    // CHECKME: do we need to initialize something?
    mov rcx, rsp
    jmp KiServiceExit2

PUBLIC KxSystemThreadEntryPoint
KxSystemThreadEntryPoint:
    mov rcx, [rsp + KSTART_FRAME.StartContext]
    jmp [rsp + KSTART_FRAME.StartRoutine]


KxSwapContextStack:
    /* Save the current thread's stack pointer */
    mov [rcx + KTHREAD.KernelStack], rsp

    /* Switch to the new thread's stack */
    mov rsp, [rdx + KTHREAD.KernelStack]

    /* Return on the new thread's stack */
    ret




PUBLIC KxSwapContext
KxSwapContext:

    sub rsp, sizeof(KNONVOLATILES)

    /* Save non-volatiles */
    mov [rsp + KNONVOLATILES.Rbp], rbp
    mov [rsp + KNONVOLATILES.Rbx], rbx
    mov [rsp + KNONVOLATILES.Rdi], rdi
    mov [rsp + KNONVOLATILES.Rsi], rsi
    mov [rsp + KNONVOLATILES.R12], r12
    mov [rsp + KNONVOLATILES.R13], r13
    mov [rsp + KNONVOLATILES.R14], r14
    mov [rsp + KNONVOLATILES.R15], r15

    movaps [rsp + KNONVOLATILES.Xmm6], xmm6
    movaps [rsp + KNONVOLATILES.Xmm7], xmm7
    movaps [rsp + KNONVOLATILES.Xmm8], xmm8
    movaps [rsp + KNONVOLATILES.Xmm9], xmm9
    movaps [rsp + KNONVOLATILES.Xmm10], xmm10
    movaps [rsp + KNONVOLATILES.Xmm11], xmm11
    movaps [rsp + KNONVOLATILES.Xmm12], xmm12
    movaps [rsp + KNONVOLATILES.Xmm13], xmm13
    movaps [rsp + KNONVOLATILES.Xmm14], xmm14
    movaps [rsp + KNONVOLATILES.Xmm15], xmm15

    call KxSwapContextStack

    movaps xmm6, [rsp + KNONVOLATILES.Xmm6]
    movaps xmm7, [rsp + KNONVOLATILES.Xmm7]
    movaps xmm8, [rsp + KNONVOLATILES.Xmm8]
    movaps xmm9, [rsp + KNONVOLATILES.Xmm9]
    movaps xmm10, [rsp + KNONVOLATILES.Xmm10]
    movaps xmm11, [rsp + KNONVOLATILES.Xmm11]
    movaps xmm12, [rsp + KNONVOLATILES.Xmm12]
    movaps xmm13, [rsp + KNONVOLATILES.Xmm13]
    movaps xmm14, [rsp + KNONVOLATILES.Xmm14]
    movaps xmm15, [rsp + KNONVOLATILES.Xmm15]

    /* Save non-volatiles */
    mov rbp, [rsp + KNONVOLATILES.Rbp]
    mov rbx, [rsp + KNONVOLATILES.Rbx]
    mov rdi, [rsp + KNONVOLATILES.Rdi]
    mov rsi, [rsp + KNONVOLATILES.Rsi]
    mov r12, [rsp + KNONVOLATILES.R12]
    mov r13, [rsp + KNONVOLATILES.R13]
    mov r14, [rsp + KNONVOLATILES.R14]
    mov r15, [rsp + KNONVOLATILES.R15]

    add rsp, sizeof(KNONVOLATILES)
    ret





END
