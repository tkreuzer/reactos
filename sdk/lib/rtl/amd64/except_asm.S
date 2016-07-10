/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Runtime Library (RTL)
 * FILE:            lib/rtl/amd64/except_asm.S
 * PURPOSE:         Exception support for AMD64
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <asm.inc>
#include <ksamd64.inc>

/* FUNCTIONS *****************************************************************/

.code64

/*
 * VOID NTAPI
 * RtlCaptureContext(
 *     PCONTEXT ContextRecord); <rcx>
 */
PUBLIC RtlCaptureContext
.PROC RtlCaptureContext

    /* Push rflags */
    pushfq
    .ALLOCSTACK 8
    .ENDPROLOG

    /* Save the basic register context */
    mov [rcx + CONTEXT.Rax], rax
    mov [rcx + CONTEXT.Rcx], rcx
    mov [rcx + CONTEXT.Rdx], rdx

    /* Load rflags into rax */
    mov rax, [rsp]

    mov [rcx + CONTEXT.Rbx], rbx
    mov [rcx + CONTEXT.Rsi], rsi
    mov [rcx + CONTEXT.Rdi], rdi

    /* Store eflags */
    mov [rcx + CONTEXT.EFlags], eax

    mov [rcx + CONTEXT.Rbp], rbp
    mov [rcx + CONTEXT.R8], r8
    mov [rcx + CONTEXT.R9], r9

    /* Load former stack pointer in rax */
    lea rax, [rsp + 16]

    mov [rcx + CONTEXT.R10], r10
    mov [rcx + CONTEXT.R11], r11
    mov [rcx + CONTEXT.R12], r12

    /* Store stack pointer */
    mov [rcx + CONTEXT.Rsp], rax

    mov [rcx + CONTEXT.R13], r13
    mov [rcx + CONTEXT.R14], r14
    mov [rcx + CONTEXT.R15], r15

    /* Load return address in rax */
    mov rax, [rsp + 8]

    /* Safe segment selectors */
    mov [rcx + CONTEXT.SegCs], cs
    mov [rcx + CONTEXT.SegDs], ds
    mov [rcx + CONTEXT.SegEs], es
    mov [rcx + CONTEXT.SegFs], fs
    mov [rcx + CONTEXT.SegGs], gs
    mov [rcx + CONTEXT.SegSs], ss

    /* Store return address */
    mov [rcx + CONTEXT.Rip], rax

    /* Safe xmm registers */
    movdqa [rcx + CONTEXT.Xmm0], xmm0
    movdqa [rcx + CONTEXT.Xmm1], xmm1
    movdqa [rcx + CONTEXT.Xmm2], xmm2
    movdqa [rcx + CONTEXT.Xmm3], xmm3
    movdqa [rcx + CONTEXT.Xmm4], xmm4
    movdqa [rcx + CONTEXT.Xmm5], xmm5
    movdqa [rcx + CONTEXT.Xmm6], xmm6
    movdqa [rcx + CONTEXT.Xmm7], xmm7
    movdqa [rcx + CONTEXT.Xmm8], xmm8
    movdqa [rcx + CONTEXT.Xmm9], xmm9
    movdqa [rcx + CONTEXT.Xmm10], xmm10
    movdqa [rcx + CONTEXT.Xmm11], xmm11
    movdqa [rcx + CONTEXT.Xmm12], xmm12
    movdqa [rcx + CONTEXT.Xmm13], xmm13
    movdqa [rcx + CONTEXT.Xmm14], xmm14
    movdqa [rcx + CONTEXT.Xmm15], xmm15

    /* Cleanup stack and return */
    add rsp, 8
    ret
.ENDP

END


