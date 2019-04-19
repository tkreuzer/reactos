EXTERN KiZwSystemServiceProlog:PROC
EXTERN KiZwSystemServiceEpilog:PROC

MACRO(STUBCODE_K, Name, SyscallId, ArgCount)
    StackBytes = 8 * &ArgCount
    push rbp
    sub rsp, KTRAP_FRAME_LENGTH + StackBytes
    lea rbp, [rsp + StackBytes]
    .ENDPROLOG
    mov qword ptr [rsp + StackBytes + KTRAP_FRAME_Rax], SyscallId
    jmp KiZwSystemService
ENDM


KiZwSystemService:
    /* Save register parameters */
    mov [rbp + KTRAP_FRAME_Rcx], rcx
    mov [rbp + KTRAP_FRAME_Rdx], rdx
    mov [rbp + KTRAP_FRAME_R8], r8
    mov [rbp + KTRAP_FRAME_R9], r9

    /* Call the prolog handler (returns the service handler address) */
    mov rcx, rbp
    call KiZwSystemServiceProlog

    /* Restore register parameters */
    mov rcx, [rbp + KTRAP_FRAME_Rcx]
    mov rdx, [rbp + KTRAP_FRAME_Rdx]
    mov r8, [rbp + KTRAP_FRAME_R8]
    mov r9, [rbp + KTRAP_FRAME_R9]

    /* Call the service function */
    call rax

    /* Save the result */
    mov [rbp + KTRAP_FRAME_Rax], rax

    /* Call epilog handler */
    mov rcx, rbp
    call KiZwSystemServiceEpilog

    /* Restore the result */
    mov rax, [rbp + KTRAP_FRAME_Rax]

    /* Cleanup the stack and return */
    lea rsp, [rbp + KTRAP_FRAME_LENGTH]
    pop rbp
    ret
