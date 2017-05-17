/*
 * COPYRIGHT:         GNU GPL - See COPYING in the top level directory
 * PROJECT:           ReactOS Run-Time Library
 * PURPOSE:           Memory functions
 * FILE:              lib/rtl/i386/rtlmem.s
 * PROGRAMER:         Alex Ionescu (alex.ionescu@reactos.org)
 */

#include <asm.inc>

/* GLOBALS *******************************************************************/

PUBLIC _RtlCompareMemory@12
PUBLIC _RtlCompareMemoryUlong@12
PUBLIC _RtlFillMemory@12
PUBLIC _RtlFillMemoryUlong@12
PUBLIC _RtlFillMemoryUlonglong@16
PUBLIC _RtlMoveMemory@12
PUBLIC _RtlZeroMemory@8
PUBLIC @RtlPrefetchMemoryNonTemporal@8

/* FUNCTIONS *****************************************************************/
.code

_RtlCompareMemory@12:

    /* Save volatiles */
    push esi
    push edi

    /* Clear direction flag and load pointers and size in ULONGs */
    cld
    mov ecx, [esp+20]
    mov esi, [esp+12]
    mov edi, [esp+16]
    shr ecx, 2
    jz NoUlongs

    /* Compare the ULONGs */
    repe cmpsd
    jnz NotEqual

NoUlongs:

    /* Compare what's left */
    mov ecx, [esp+20]
    and ecx, 3
    jz NoneLeft
    repe cmpsb
    jnz NotEqual2

NoneLeft:

    /* We're done, return full count */
    mov eax, [esp+20]
    pop edi
    pop esi
    ret 12

NotEqual:
    /* Compare the last ULONG */
    sub esi, 4
    sub edi, 4
    mov ecx, 5
    repe cmpsb

NotEqual2:

    /* Remember how many matched */
    sub esi, [esp+12]

    /* Return count */
    mov eax, esi
    pop edi
    pop esi
    dec eax
    ret 12


_RtlCompareMemoryUlong@12:

    /* Get pointers and size in ULONGs */
    push edi
    mov edi, [esp+8]
    mov ecx, [esp+12]
    mov eax, [esp+16]
    shr ecx, 2

    /* Do the compare and check result */
    repe scasd
    jz Done
    sub edi, 4

    /* Return count */
Done:
    mov eax, edi
    pop edi
    sub eax, [esp+8]
    ret 12


_RtlFillMemory@12:

    /* Get pointers and size  */
    push edi
    mov edi, [esp+8]
    mov ecx, [esp+12]

    /* Get pattern */
    mov al, [esp+16]
    mov ah, al
    shl eax, 16
    mov al, [esp+16]
    mov ah, al

    /* Clear direction flag and set ULONG size and UCHAR remainder */
    mov edx, ecx
    cld
    shr ecx, 2
    and edx, 3

    /* Do the fill */
    rep stosd
    or ecx, edx
    jnz ByteFill

    /* Return */
    pop edi
    ret 12

ByteFill:
    /* Fill what's left */
    rep stosb
    /* Return */
    pop edi
    ret 12


_RtlFillMemoryUlong@12:

    /* Get pointer, size and pattern */
    push edi
    mov edi, [esp+8]
    mov ecx, [esp+12]
    mov eax, [esp+16]
    shr ecx, 2

    /* Do the fill and return */
    rep stosd
    pop edi
    ret 12


_RtlFillMemoryUlonglong@16:

    /* Save volatiles */
    push edi
    push esi

    /* Get pointer, size and pattern */
    mov esi, [esp+12]
    mov ecx, [esp+16]
    mov eax, [esp+20]
    shr ecx, 2

    /* Save the first part */
    mov [esi], eax
    sub ecx, 2

    /* Read second part */
    mov eax, [esp+24]
    lea edi, [esi+8]
    mov [esi+4], eax

    /* Do the fill and return */
    rep movsd
    pop esi
    pop edi
    ret 16


_RtlZeroMemory@8:

    /* Get pointers and size  */
    push edi
    mov edi, [esp+8]
    mov ecx, [esp+12]

    /* Get pattern */
    xor eax, eax

    /* Clear direction flag and set ULONG size and UCHAR remainder */
    mov edx, ecx
    cld
    shr ecx, 2
    and edx, 3

    /* Do the fill */
    rep stosd
    or ecx, edx
    jnz ByteZero

    /* Return */
    pop edi
    ret 8

ByteZero:
    /* Fill what's left */
    rep stosb
    pop edi
    ret 8


_RtlMoveMemory@12:
	push ebp
	mov ebp, esp

    /* Save non-volatiles */
    push esi
    push edi

    /* Get pointers and size  */
	mov	edi, [ebp + 8]
	mov	esi, [ebp + 12]
	mov	ecx, [ebp + 16]

    /* Save original size and prepare ecx for moving dwords */
    mov edx, ecx
    shr ecx, 2

    /* Check if the source is higher */
    cmp esi, edi
    ja DoMove

    /* Do move backwards to not overwrite our source */
    std
    add esi, edx
    add edi, edx
    jcxz ByteMoveBackward

    sub si,4
    sub di,4

DoMove:

    /* Do the move */
    rep movsd
    and edx, 3
    jnz ByteMove

    /* Return */
    cld
    pop edi
    pop esi
    ret 12

ByteMoveBackward:
    dec esi
    dec edi
    and edx, 3

ByteMove:
    /* Move what's left */
    mov ecx, edx
    rep movsb

    /* Return */
    cld
    pop edi
    pop esi
    ret 12


    /* Make the destination dword aligned */
	mov ecx, edi
	and ecx, 3
	sub edx, ecx
	dec esi
	dec edi
	rep movsb
	mov ecx, edx
	sub esi, 3
	sub edi, 3

.CopyDownDwords:
	shr ecx, 2
	rep movsd
	mov ecx, edx
	and ecx, 3
	je .CopyDownEnd
	add esi, 3
	add edi, 3

.CopyDownBytes:
	rep movsb

.CopyDownEnd:
	cld
	mov eax, [ebp + 8]
	pop edi
	pop esi
	pop ebp
	ret 12

.CopyDownAligned:
	sub edi, 4
	sub esi, 4
	jmp .CopyDownDwords

.CopyDownSmall:
	test ecx, ecx
	je .CopyDownEnd
	dec esi
	dec edi
	jmp .CopyDownBytes



@RtlPrefetchMemoryNonTemporal@8:

    /*
     * Overwritten by ntoskrnl/ke/i386/kernel.c if SSE is supported
     * (see Ki386SetProcessorFeatures())
     */
    ret

    /* Get granularity */
    mov eax, [_Ke386CacheAlignment]

FetchLine:

    /* Prefetch this line */
    prefetchnta byte ptr [ecx]

    /* Update address and count */
    add ecx, eax
    sub edx, eax

    /* Keep looping for the next line, or return if done */
    ja FetchLine
    ret


/* FIXME: HACK */
_Ke386CacheAlignment:
    .long   64

END
