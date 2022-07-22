
#include <asm.inc>

.code64

PUBLIC __getfpcw87_
FUNC __getfpcw87_
    sub rsp, 8
    .ENDPROLOG
    stmxcsr [rsp]
    mov rax, [rsp]
    add rsp, 8
    ret
ENDFUNC

PUBLIC __setfpcw87_
FUNC __setfpcw87_
    mov qword ptr [rsp + 8], rcx
    .ENDPROLOG
    ldmxcsr [rsp + 8]
    ret
ENDFUNC

END
