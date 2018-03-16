/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     ReactOS AMD64 user mode callback helper
 * COPYRIGHT:   Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include <ksamd64.inc>

/*
 * NTSTATUS
 * KiUserModeCallout (
 *     _Inout_ PKCALLOUT_FRAME CalloutFrame);
 */
EXTERN KiUserModeCallout:PROC

.code64

;
; NTSTATUS
; KiCallUserMode (
;     _In_ ULONG RoutineIndex@<rcx>,
;     _In_ PVOID Argument@<rdx>,
;     _In_ ULONG ArgumentLength@<r8>,
;     _In_ PVOID *OutputBuffer@<r9>,
;     _In_ PULONG OutputLength);
;
PUBLIC KiCallUserMode
.PROC KiCallUserMode

    /* Generate a KEXCEPTION_FRAME on the stack */
    /* This is identical to a KCALLOUT_FRAME */
    GENERATE_EXCEPTION_FRAME

    /* Save OutputBuffer and OutputLength */
    mov [rsp + ExOutputBuffer], r9
    mov rax, [rsp + ExReturn + 5 * 8]
    mov [rsp + ExOutputLength], rax
    mov [rsp + ExP5], rax

    /* Call the C function */
    call KiUserModeCallout

    /* Restore the registers from the KEXCEPTION_FRAME */
    RESTORE_EXCEPTION_STATE

    /* Return */
    ret

.ENDP

/*
 * DECLSPEC_NORETURN
 * VOID
 * KiCallbackReturn (
 *     _In_ PVOID Stack,
 *     _In_ NTSTATUS Status);
 */
PUBLIC KiCallbackReturn
.PROC KiCallbackReturn

    .ENDPROLOG

    /* Restore the stack */
    mov rsp, rcx

    /* Set return status */
    mov eax, edx

    /* Restore the registers from the KEXCEPTION_FRAME */
    RESTORE_EXCEPTION_STATE

    /* Return */
    ret

.ENDP


END
