

#include <asm.inc>
#include <ks386.inc>

.code

EXTERN _ExRaiseStatus@4:PROC
STATUS_BAD_STACK = HEX(C0000028)

STACK_COOKIE = HEX(1337babe)

InternalGetContext:
    mov dword ptr [ecx + CONTEXT_FLAGS], CONTEXT_FULL
    mov dword ptr [ecx + CONTEXT_EDI], edi
    mov dword ptr [ecx + CONTEXT_ESI], esi
    mov dword ptr [ecx + CONTEXT_EBX], ebx
    mov dword ptr [ecx + CONTEXT_EDX], edx
    mov dword ptr [ecx + CONTEXT_ECX], ecx
    mov dword ptr [ecx + CONTEXT_EAX], eax
    mov dword ptr [ecx + CONTEXT_EBP], ebp
    mov eax, [esp]
    mov dword ptr [ecx + CONTEXT_EIP], eax
    mov dword ptr [ecx + CONTEXT_SEGCS], KGDT_R0_CODE
    pushfd
    pop eax
    mov dword ptr [ecx + CONTEXT_EFLAGS], eax
    mov dword ptr [ecx + CONTEXT_ESP], esp
    mov dword ptr [ecx + CONTEXT_SEGSS], KGDT_R0_DATA
    mov eax, ds
    mov dword ptr [ecx + CONTEXT_SEGDS], eax
    mov eax, es
    mov dword ptr [ecx + CONTEXT_SEGES], eax
    mov eax, fs
    mov dword ptr [ecx + CONTEXT_SEGFS], eax
    mov eax, gs
    mov dword ptr [ecx + CONTEXT_SEGGS], eax

    /* Restore eax */
    mov eax, dword ptr [ecx + CONTEXT_EAX]
    ret

/*
ULONGLONG
__cdecl
KmtCallWrapper(
    PCONTEXT PreState,
    PCONTEXT PostState,
    PVOID Function,
    BOOLEAN FastCall,
    ULONG NumberParameters,
    ...);
*/
P_PreState = 8
P_PostState = 12
P_Function = 16
P_FastCall = 20
P_NumberParameters = 24
P_Parameters = 28

PUBLIC _KmtCallWrapper
_KmtCallWrapper:

    push ebp
    mov ebp, esp
    push esi
    push edi

    /* Push a "stack cookie" */
    push STACK_COOKIE

    /* Save the PreState */
    mov ecx, dword ptr [ebp + P_PreState]
    call InternalGetContext

    /* Make room for the parameters on the stack */
    mov ecx, dword ptr [ebp + P_NumberParameters]
    shl ecx, 2
    sub esp, ecx

    /* Copy the parameters to the the stack */
    lea esi, dword ptr [ebp + P_Parameters]
    lea edi, [esp]
    mov ecx, dword ptr [ebp + P_NumberParameters]
    rep movsd

    /* Check if this is a fastcall function */
    cmp byte ptr [ebp + P_FastCall], 0
    je DoTheCall

    /* Check if we have 0 parameters */
    cmp dword ptr [ebp + P_NumberParameters], 0
    je DoTheCall

    /* Pop the first argument from the stack */
    pop ecx

    /* Check if we have only 1 parameter */
    cmp dword ptr [ebp + P_NumberParameters], 1
    je DoTheCall

    /* Pop the second argument from the stack */
    pop edx

DoTheCall:

    /* Call the function */
    call dword ptr [ebp + P_Function]

    /* Check if we still have the stack cookie where it should be (rel to ebp) */
    cmp dword ptr [ebp - 4], STACK_COOKIE
    jne stackfailure

    /* Save the PostState */
    mov ecx, dword ptr [ebp + P_PostState]
    call InternalGetContext

    /* Cleanup stack and return */
    pop edi
    pop esi
    mov esp, ebp
    pop ebp
    ret

stackfailure:
    /* This is bad */
    push STATUS_BAD_STACK
    call _ExRaiseStatus@4

END
