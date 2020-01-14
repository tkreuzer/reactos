
#include <asm.inc>

.code64

PUBLIC KdbpStackSwitchAndCall
KdbpStackSwitchAndCall:
    push rbp
    mov rbp, rsp    /* Old stack - frame */

    /* Save old stack */
    mov rax, rsp
cli
hlt
    /* Set new stack */
    mov rsp, rcx

    /* Call function */
    call rdx

    /* Switch back to old stack */
    pop rsp

    ret 8

END
