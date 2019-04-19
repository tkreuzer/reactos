

#include <asm.inc>

.align 16
PUBLIC MxZeroPage
.PROC MxZeroPage
    .endprolog

    pxor xmm0, xmm0

.repeat:
    movaps [rcx + 0 * 16], xmm0
    movaps [rcx + 1 * 16], xmm0
    movaps [rcx + 2 * 16], xmm0
    movaps [rcx + 3 * 16], xmm0
    movaps [rcx + 4 * 16], xmm0
    movaps [rcx + 5 * 16], xmm0
    movaps [rcx + 6 * 16], xmm0
    movaps [rcx + 7 * 16], xmm0
    movaps [rcx + 8 * 16], xmm0
    movaps [rcx + 9 * 16], xmm0
    movaps [rcx + 10 * 16], xmm0
    movaps [rcx + 11 * 16], xmm0
    movaps [rcx + 12 * 16], xmm0
    movaps [rcx + 13 * 16], xmm0
    movaps [rcx + 14 * 16], xmm0
    movaps [rcx + 15 * 16], xmm0

    add rcx, 256
    test rcx, HEX(FFF)
    jnz .repeat

    ret
.ENDP

END
