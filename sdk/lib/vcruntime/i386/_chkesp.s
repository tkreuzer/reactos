


#include <asm.inc>

.code

#define FAST_FAIL_INCORRECT_STACK 4

PUBLIC __chkesp
__chkesp:
    jnz __chkesp_failed
    ret

__chkesp_failed:
    mov ecx, FAST_FAIL_INCORRECT_STACK
    int HEX(29)

END
