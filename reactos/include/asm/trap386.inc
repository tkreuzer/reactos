
TF_PUSH_FAKE_ERROR_CODE = HEX(0001)
TF_UNUSED               = HEX(0002)
TF_NONVOLATILES_ONLY    = HEX(0004)
TF_FAST_SYSTEM_CALL     = HEX(0008)
TF_SOFTWARE_TRAP        = HEX(0010)
TF_HARDWARE_INT         = HEX(0020)
TF_DONT_SAVE_SEGS       = HEX(0100)

TF_RESTORE_EAX          = HEX(001)
TF_RESTORE_ECX_EDX      = HEX(002)
TF_RESTORE_FS           = HEX(004)
TF_RESTORE_SEGMENTS     = HEX(008)
TF_RESTORE_EFLAGS       = HEX(010)
TF_RESTORE_VOLATILES    = (TF_RESTORE_EAX OR TF_RESTORE_ECX_EDX)

TF_EXIT_SYSCALL         = HEX(020)
TF_EXIT_JMP             = HEX(040)
TF_EXIT_RET             = HEX(080)
TF_EXIT_IRET            = HEX(100)
TF_EDITED_FRAME         = HEX(200)

MACRO(EnterTrap, Flags)
    LOCAL kernel_trap
    LOCAL not_v86_trap
    LOCAL set_sane_segs

    /* Check what kind of trap frame this trap requires */
    if (Flags AND TF_FAST_SYSTEM_CALL)

        /* SYSENTER requires us to build a complete ring transition trap frame */
        FrameSize = KTRAP_FRAME_V86_ES

        /* Fixup fs. cx is free to clobber */
        mov cx, KGDT_R0_PCR
        mov fs, cx

        /* Get pointer to the TSS */
        mov ecx, fs:[KPCR_TSS]

        /* Get a stack pointer */
        mov esp, [ecx + KTSS_ESP0]

        /* Set up a fake hardware trap frame */
        push KGDT_R3_DATA or RPL_MASK
        push edx
        pushfd
        push KGDT_R3_CODE or RPL_MASK
        push dword ptr ds:[KUSER_SHARED_SYSCALL_RET]

    elseif (Flags AND TF_SOFTWARE_TRAP)

        /* Software traps need a complete non-ring transition trap frame */
        FrameSize = KTRAP_FRAME_ESP

        /* Software traps need to get their EIP from the caller's frame */
        pop eax

    elseif (Flags AND TF_PUSH_FAKE_ERROR_CODE)

        /* If the trap doesn't have an error code, we'll make space for it */
        FrameSize = KTRAP_FRAME_EIP

    else

        /* The trap already has an error code, so just make space for the rest */
        FrameSize = KTRAP_FRAME_ERROR_CODE

    endif

    /* Make space for this frame */
    sub esp, FrameSize

    /* Save nonvolatile registers */
    mov [esp + KTRAP_FRAME_EBP], ebp
    mov [esp + KTRAP_FRAME_EBX], ebx
    mov [esp + KTRAP_FRAME_ESI], esi
    mov [esp + KTRAP_FRAME_EDI], edi

    /* Save eax for system calls, for use by the C handler */
    mov [esp + KTRAP_FRAME_EAX], eax

    /* Does the caller want nonvolatiles only? */
    if (NOT (Flags AND TF_NONVOLATILES_ONLY))
        /* Otherwise, save the volatiles as well */
        mov [esp + KTRAP_FRAME_ECX], ecx
        mov [esp + KTRAP_FRAME_EDX], edx
    endif

    /* Save segment registers? */
    if (Flags AND TF_DONT_SAVE_SEGS)

        /* Initialize TrapFrame segment registers with sane values */
        mov eax, KGDT_R3_DATA OR 3
        mov ecx, fs
        mov [esp + KTRAP_FRAME_DS], eax
        mov [esp + KTRAP_FRAME_ES], eax
        mov [esp + KTRAP_FRAME_FS], ecx
        mov dword ptr [esp + KTRAP_FRAME_GS], 0

    else

        /* Check for V86 mode */
        test byte ptr [esp + KTRAP_FRAME_EFLAGS + 2], (EFLAGS_V86_MASK / HEX(10000))
        jz not_v86_trap

            /* Restore V8086 segments into Protected Mode segments */
            mov eax, [esp + KTRAP_FRAME_V86_DS]
            mov ecx, [esp + KTRAP_FRAME_V86_ES]
            mov [esp + KTRAP_FRAME_DS], eax
            mov [esp + KTRAP_FRAME_ES], ecx
            mov eax, [esp + KTRAP_FRAME_V86_FS]
            mov ecx, [esp + KTRAP_FRAME_V86_GS]
            mov [esp + KTRAP_FRAME_FS], eax
            mov [esp + KTRAP_FRAME_GS], ecx
            jmp set_sane_segs

        not_v86_trap:

            /* Save segment selectors */
            mov eax, ds
            mov ecx, es
            mov [esp + KTRAP_FRAME_DS], eax
            mov [esp + KTRAP_FRAME_ES], ecx
            mov eax, fs
            mov ecx, gs
            mov [esp + KTRAP_FRAME_FS], eax
            mov [esp + KTRAP_FRAME_GS], ecx

    endif

set_sane_segs:
    /* Load correct data segments */
    mov ax, KGDT_R3_DATA OR RPL_MASK
    mov ds, ax
    mov es, ax

    /* Fast system calls have fs already fixed */
    if (Flags AND TF_FAST_SYSTEM_CALL)

        /* Enable interrupts and set a sane FS value */
        or dword ptr [esp + KTRAP_FRAME_EFLAGS], EFLAGS_INTERRUPT_MASK
        mov dword ptr [esp + KTRAP_FRAME_FS], KGDT_R3_TEB or RPL_MASK

        /* Set sane active EFLAGS */
        push 2
        popfd

        /* Point edx to the usermode parameters */
        add edx, 8
    else
        /* Otherwise fix fs now */
        mov ax, KGDT_R0_PCR
        mov fs, ax
    endif

#if DBG
    /* Keep the frame chain intact */
    mov eax, [esp + KTRAP_FRAME_EIP]
    mov [esp + KTRAP_FRAME_DEBUGEIP], eax
    mov [esp + KTRAP_FRAME_DEBUGEBP], ebp
    mov ebp, esp
#endif

    /* Set parameter 1 (ECX) to point to the frame */
    mov ecx, esp

    /* Clear direction flag */
    cld

ENDM

MACRO(KiCallHandler, Handler)
#if DBG
    /* Use a call to get the return address for back traces */
    call Handler
#else
    /* Use the faster jmp */
    jmp Handler
#endif
    nop
ENDM


MACRO(KiTrapExitStub, Name, Flags)

PUBLIC @&Name&@4
@&Name&@4:

    if (Flags AND TF_EXIT_RET8) OR (Flags AND TF_EXIT_IRET)

        /* This is the IRET frame */
        OffsetEsp = KTRAP_FRAME_EIP

    elseif (Flags AND TF_RESTORE_EFLAGS)

        /* We will pop EFlags off the stack */
        OffsetEsp = KTRAP_FRAME_EFLAGS

    else

        OffsetEsp = 0

    endif

    if (Flags AND TF_EDITED_FRAME)

        /* Load the requested ESP */
        mov esp, [ecx + KTRAP_FRAME_TEMPESP]

        /* Put return address on the new stack */
        push [ecx + KTRAP_FRAME_EIP]

        /* Put EFLAGS on the new stack */
        push [ecx + KTRAP_FRAME_EFLAGS]

    else

        /* Point esp to an appropriate member of the frame */
        lea esp, [ecx + OffsetEsp]

    endif

    /* Restore non volatiles */
    mov ebx, [ecx + KTRAP_FRAME_EBX]
    mov esi, [ecx + KTRAP_FRAME_ESI]
    mov edi, [ecx + KTRAP_FRAME_EDI]
    mov ebp, [ecx + KTRAP_FRAME_EBP]

    if (Flags AND TF_RESTORE_EAX)

        /* Restore eax */
        mov eax, [ecx + KTRAP_FRAME_EAX]

    endif

    if (Flags AND TF_RESTORE_ECX_EDX)

        /* Restore volatiles */
        mov edx, [ecx + KTRAP_FRAME_EDX]
        mov ecx, [ecx + KTRAP_FRAME_ECX]

    elseif (Flags AND TF_EXIT_JMP)

        /* Load return address into edx */
        mov edx, [esp - OffsetEsp + KTRAP_FRAME_EIP]

    elseif (Flags AND TF_EXIT_SYSCALL)

        /* Set sysexit parameters */
        mov edx, [esp - OffsetEsp + KTRAP_FRAME_EIP]
        mov ecx, [esp - OffsetEsp + KTRAP_FRAME_ESP]

        /* Keep interrupts disabled until the sti / sysexit */
        and byte ptr [esp - OffsetEsp + KTRAP_FRAME_EFLAGS + 1], NOT (EFLAGS_INTERRUPT_MASK / HEX(100))

    endif

    if (Flags AND TF_RESTORE_SEGMENTS)

        /* Restore segments for user mode */
        mov ds, [esp - OffsetEsp + KTRAP_FRAME_DS]
        mov es, [esp - OffsetEsp + KTRAP_FRAME_ES]
        mov gs, [esp - OffsetEsp + KTRAP_FRAME_GS]

    endif

    if ((Flags AND TF_RESTORE_FS) OR (Flags AND TF_RESTORE_SEGMENTS))

        /* Restore user mode FS */
        mov fs, [esp - OffsetEsp + KTRAP_FRAME_FS]

    endif

    if (Flags AND TF_RESTORE_EFLAGS)

        if (Flags AND TF_EXIT_RET8)

            /* We are at the IRET frame, so push EFLAGS first */
            push dword ptr [esp + 8]

        endif

        /* Restore EFLAGS */
        popfd

    endif

    if (Flags AND TF_EXIT_SYSCALL)

        /* Enable interrupts and return to user mode.
           Both must follow directly after another to be "atomic". */
        sti
        sysexit

    elseif (Flags AND TF_EXIT_IRET)

        /* Return with iret */
        iretd

    elseif (Flags AND TF_EXIT_JMP)

        /* Return to kernel mode with a jmp */
        jmp edx

    elseif (Flags AND TF_EXIT_RET)

        /* Return to kernel mode with a ret 8 */
        ret 8

    elseif (Flags AND TF_EXIT_RET)

        /* Return to kernel mode with a ret */
        ret

    endif

ENDM


MACRO(CallHandler, Handler)
#if DBG
    /* Use a call to get the return address for back traces */
    call Handler
#else
    /* Use the faster jmp */
    jmp Handler
#endif
    nop
ENDM


MACRO(TRAP_ENTRY, Trap, Flags)
    EXTERN @&Trap&Handler@4 :PROC
    PUBLIC _&Trap
    .PROC &Trap
        /* Generate proper debugging symbols */
        FPO 0, 0, 0, 0, 1, FRAME_TRAP

        /* Common code to create the trap frame */
        EnterTrap Flags

        /* Call the C handler */
        CallHandler @&Trap&Handler@4
    .ENDP &Trap
ENDM

