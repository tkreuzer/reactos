
#include <asm.inc>
#include <asmdef.inc>

.code

EXTERN P0BootStack:QWORD
EXTERN KiSystemStartup:PROC

PUBLIC KxKernelEntryPoint
.PROC KxKernelEntryPoint
    /* Terminate the frame chain */
    xor rbp, rbp
    .setframe rbp, 0
    .endprolog

    /* Initialize segment selectors */
    mov ax, KGDT64_R3_DATA or RPL_MASK
    mov ds, ax
    mov es, ax
    mov gs, ax
    swapgs
    mov gs, ax
    mov ax, KGDT64_R3_CMTEB or RPL_MASK
    mov fs, ax
    mov ax, KGDT64_R0_DATA
    mov ss, ax

    /* Get stack from loader block */
    mov rsp, [rcx + LOADER_PARAMETER_BLOCK.KernelStack]

    /* If we have no stack it's CPU0 */
    test rsp, rsp
    jz BootCpu

//    call KiProcessorStartup
    int 3

BootCpu:
    /* Setup a proper stack */
    mov rsp, qword ptr [P0BootStack]

    /* Jump to kernel startup code */
    call KiSystemStartup

    int 3
.ENDP


PUBLIC KiSystemService
KiSystemService:
    int 3

#ifdef _MSC_VER
#undef lgdt
#undef lidt

//void __lgdt(void *Source);
PUBLIC __lgdt
__lgdt:
    lgdt fword ptr [rcx]
    ret

//void __sgdt(void *Destination);
PUBLIC __sgdt
__sgdt:
    sgdt fword ptr [rcx]
    ret

// void __lldt(unsigned short Value)
PUBLIC __lldt
__lldt:
    lldt cx
    ret

//void __sldt(void *Destination);
PUBLIC __sldt
__sldt:
    sldt word ptr [rcx]
    ret

//void __ltr(unsigned short Source);
PUBLIC __ltr
__ltr:
    ltr cx
    ret

//void __str(unsigned short *Destination);
PUBLIC __str
__str:
    str word ptr [rcx]
    ret

// void __stmxcsr(unsigned int *Destination);
PUBLIC __stmxcsr
__stmxcsr:
    stmxcsr dword ptr [rcx]
    ret

// void __fxsave(void *SaveArea);
PUBLIC __fxsave
__fxsave:
    fxsave [rcx]
    ret

// void __fxrstor(void *SaveArea);
PUBLIC __fxrstor
__fxrstor:
    fxrstor [rcx]
    ret

#endif

END
