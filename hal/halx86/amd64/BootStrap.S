

#include <asm.inc>
#include <ksamd64.inc>

.code16

KxCpuStartup:
    /* jump over the data area */
    jmp RealStartup

/* Data area begins at offset 4 */
.org 4

    /* Offset of the entry point to be patched */
    .long offset LongModeEntryPoint

StartupCr3:
    .long 0


RealStartup:
	cli

	/* Setup real mode segment registers */
	xor ax, ax
	mov	ds, ax
	mov es, ax
	mov fs, ax
	mov	gs, ax
	mov ss, ax

	/* Setup a real mode stack */
    mov sp, offset StartupStack

    /* Enable A20 address line */
    call EnableA20

	/* Load the GDT */
	lgdt fword ptr [StartupGdtPtr]

    /* Set PAE and PGE: 10100000b */
	mov eax, HEX(00a0)
	mov cr4, eax

    /* Point cr3 at the PML4 */
	mov eax, dword ptr [StartupCr3]
	mov cr3, eax

    /* Enable long mode */
	mov ecx, MSR_EFER
	rdmsr
	or eax, HEX(00000100)
	wrmsr

    /* Activate long mode by enabling paging and protection simultaneously,
       skipping protected mode entirely */
	mov eax, cr0
	or eax, HEX(80000001)
	mov cr0, eax

    /* Clear prefetch queue & correct CS */
    ljmp16 KGDT64_R0_CODE, InLongMode
InLongMode:
	//DB 66h, 0B8h, 18h, 00h // mov ax, LMODE_DS
	//DB 66h, 8Eh, 0D8h // mov ds, ax
	//DB 66h, 66h, 0C7h, 04h, 25h, 00h, 80h, 0Bh, 00h, 31h, 0Eh
	//mov word ptr [HEX(b8000)], HEX(0e00) + '1'

    .byte HEX(0ff), HEX(25) // opcode of 64bit indirect jump
    .long 1 // relative address of LongModeEntryPoint
    nop
LongModeEntryPoint:
    .long 0, 0


Empty8042:
    .word HEX(00eb), HEX(00eb)		// jmp $+2, jmp $+2
    in al, HEX(64)
    cmp al, HEX(0ff)				// legacy-free machine without keyboard
    jz Empty8042_ret			// controllers on Intel Macs read back 0xFF
    test al, 2
    jnz Empty8042
Empty8042_ret:
	ret

EnableA20:
    pusha
    call Empty8042
    mov al, HEX(0D1)				// command write
    out HEX(064), al
    call Empty8042
    mov al, HEX(0DF)				// A20 on
    out HEX(060), al
    call Empty8042
    popa
    ret

.align 8
StartupGdt:
	.word HEX(0000), HEX(0000), HEX(0000), HEX(0000) /* 00: NULL descriptor */
	.word HEX(0000), HEX(0000), HEX(0000), HEX(0000) /* 08:  */
	.word HEX(0000), HEX(0000), HEX(9800), HEX(0020) /* 10: long mode cs */
	.word HEX(ffff), HEX(0000), HEX(f300), HEX(00cf) /* 18: long mode ds */

/* GDT table pointer */
StartupGdtPtr:
	.word 31 /* Limit */
	.long offset StartupGdt   /* Base Address */

    .fill 2000, 0
StartupStack:

.endcode16

END
