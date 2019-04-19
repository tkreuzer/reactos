
#include <asm.inc>
#include <asmdef.inc>

#define LOOP_COUNT 10000
#define UNROLLED_COUNT 100

//#define PROFILE_INSTRUCTION mov eax, dword ptr [APIC_TCCR] // 30 cycles
//#define PROFILE_INSTRUCTION int HEX(2F)
//#define PROFILE_INSTRUCTION lock cmpxchg [rsp - 8], r8
#define PROFILE_INSTRUCTION lock cmpxchg [GlobalVariable], r8

.data

GlobalVariable:
    .quad 0


.code

APIC_TCCR = HEX(0FFFFFFFFFFFE0390)

PUBLIC Amd64ProfileDummy
Amd64ProfileDummy:
    rdtsc
    mov r8, rdx
    shl r8, 32
    or r8, rax
    mov rcx, LOOP_COUNT
    jmp looper1

.align 16
looper1:
    //mov eax, dword ptr gs:[0]

    dec rcx
    jnz looper1

    rdtsc
    shl rdx, 32
    or rax, rdx
    sub rax, r8
    ret

PUBLIC Amd64ProfileFunction
Amd64ProfileFunction:
    rdtsc
    mov r8, rdx
    shl r8, 32
    or r8, rax
    mov rcx, LOOP_COUNT
    jmp looper2

.align 16
looper2:

REPEAT UNROLLED_COUNT
    PROFILE_INSTRUCTION
ENDR

    dec rcx
    jnz looper2

    rdtsc
    shl rdx, 32
    or rax, rdx
    sub rax, r8
    ret


END
