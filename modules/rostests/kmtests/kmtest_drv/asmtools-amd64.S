

#include <asm.inc>
#include <ksamd64.inc>

.code

EXTERN ExRaiseStatus:PROC
STATUS_BAD_STACK = HEX(C0000028)

STACK_COOKIE = HEX(1337babec01db338)

.PROC GetRFlags
    pushfq
    .ENDPROLOG
    pop rax
    ret
.ENDP

.PROC InternalGetContext
    .ENDPROLOG
    mov qword ptr [rcx + CxContextFlags], CONTEXT_FULL
    mov qword ptr [rcx + CxRdi], rdi
    mov qword ptr [rcx + CxRsi], rsi
    mov qword ptr [rcx + CxRbx], rbx
    mov qword ptr [rcx + CxRdx], rdx
    mov qword ptr [rcx + CxRcx], rcx
    mov qword ptr [rcx + CxRax], rax
    mov qword ptr [rcx + CxRbp], rbp

    mov qword ptr [rcx + CxR8], r8
    mov qword ptr [rcx + CxR9], r9
    mov qword ptr [rcx + CxR10], r10
    mov qword ptr [rcx + CxR11], r11
    mov qword ptr [rcx + CxR12], r12
    mov qword ptr [rcx + CxR13], r13
    mov qword ptr [rcx + CxR14], r14
    mov qword ptr [rcx + CxR15], r15
#if 0
    mov xmmword ptr [rcx + CxXmm0], xmm0
    mov xmmword ptr [rcx + CxXmm1], xmm1
    mov xmmword ptr [rcx + CxXmm2], xmm2
    mov xmmword ptr [rcx + CxXmm3], xmm3
    mov xmmword ptr [rcx + CxXmm4], xmm4
    mov xmmword ptr [rcx + CxXmm5], xmm5
    mov xmmword ptr [rcx + CxXmm6], xmm6
    mov xmmword ptr [rcx + CxXmm7], xmm7
    mov xmmword ptr [rcx + CxXmm8], xmm8
    mov xmmword ptr [rcx + CxXmm9], xmm9
    mov xmmword ptr [rcx + CxXmm10], xmm10
    mov xmmword ptr [rcx + CxXmm11], xmm11
    mov xmmword ptr [rcx + CxXmm12], xmm12
    mov xmmword ptr [rcx + CxXmm13], xmm13
    mov xmmword ptr [rcx + CxXmm14], xmm14
    mov xmmword ptr [rcx + CxXmm15], xmm15
#endif

#if 0
    mov qword ptr [rcx + CxRsp], rsp
    mov rax, [rsp]
    mov qword ptr [rcx + CxRip], rax
    call GetRFlags
    mov dword ptr [rcx + CxEFlags], eax
    mov ax, ds
    mov word ptr [rcx + CxSegDs], ax
    and ax, 3
    or ax, KGDT64_R0_DATA
    mov word ptr [rcx + CxSegSs], ax
    and ax, 3
    or ax, KGDT64_R0_CODE
    mov word ptr [rcx + CxSegCs], ax
    mov ax, es
    mov word ptr [rcx + CxSegEs], ax
    mov ax, fs
    mov word ptr [rcx + CxSegFs], ax
    mov ax, gs
    mov qword ptr [rcx + CxSegGs], ax
#endif
/*
    CxMxCsr equ 034h
    CxDr0 equ 048h
    CxDr1 equ 050h
    CxDr2 equ 058h
    CxDr3 equ 060h
    CxDr6 equ 068h
    CxDr7 equ 070h
    CxFltSave equ 0100h
    CxDebugControl equ 04a8h
    CxLastBranchToRip equ 04b0h
    CxLastBranchFromRip equ 04b8h
    CxLastExceptionToRip equ 04c0h
    CxLastExceptionFromRip equ 04c8h
    CxVectorControl equ 04a0h
    CxVectorRegister equ 0300h
*/

    /* Restore rax */
    mov rax, qword ptr [rcx + CxRax]
    ret
.ENDP

/*
ULONGLONG
__cdecl
KmtCallWrapper(
    PCONTEXT PreState,
    PCONTEXT PostState,
    PVOID Function,
    BOOLEAN FastCall,
    ULONG NumberParameters,
    ...);
*/
P_PreState = 8
P_PostState = 12
P_Function = 16
P_FastCall = 20
P_NumberParameters = 24
P_Parameters = 28

PUBLIC KmtCallWrapper
.PROC KmtCallWrapper

    /* Save registers */
    push rsi
    .pushreg rsi
    push rdi
    .pushreg rdi

    /* Push a "stack cookie" */
    //push STACK_COOKIE

    .ENDPROLOG

    /* Save the PreState */
    call InternalGetContext
#if 0
    /* Make room for the parameters on the stack */
    mov ecx, dword ptr [ebp + P_NumberParameters]
    shl ecx, 2
    sub esp, ecx

    /* Copy the parameters to the the stack */
    lea rsi, qword ptr [ebp + P_Parameters]
    lea edi, [esp]
    mov ecx, dword ptr [ebp + P_NumberParameters]
    rep movsd

    /* Check if this is a fastcall function */
    cmp byte ptr [ebp + P_FastCall], 0
    je DoTheCall

    /* Check if we have 0 parameters */
    cmp dword ptr [ebp + P_NumberParameters], 0
    je DoTheCall

    /* Pop the first argument from the stack */
    pop ecx

    /* Check if we have only 1 parameter */
    cmp dword ptr [ebp + P_NumberParameters], 1
    je DoTheCall

    /* Pop the second argument from the stack */
    pop edx

DoTheCall:

    /* Call the function */
    call dword ptr [ebp + P_Function]

    /* Check if we still have the stack cookie where it should be (rel to ebp) */
    cmp dword ptr [ebp - 4], STACK_COOKIE
    jne stackfailure

    /* Save the PostState */
    mov ecx, dword ptr [ebp + P_PostState]
    call InternalGetContext

    /* Cleanup stack and return */
    pop edi
    pop esi
    mov esp, ebp
    pop ebp
    ret

stackfailure:
    /* This is bad */
    push STATUS_BAD_STACK
    call _ExRaiseStatus@4
#endif
.ENDP


END
