
#include <asm.inc>

PUBLIC _APProtectedMode
PUBLIC _APProtectedModeEnd
EXTERN _PageTable:DWORD
EXTERN _HaliAPBootSpinup:DWORD
EXTERN _BSPGDTLimit:DWORD
EXTERN _BSPGDTBase:DWORD
.code32
_APProtectedMode:
     mov   ax, HEX(10)
     mov   ds, ax
     mov   es, ax
     mov   fs, ax
     mov   ss, ax

    /* TODO: Replace the hardcoded value with the _PageTable extern value from BSP. */
    xor eax, eax
    mov eax, HEX(80010000)
    mov cr3, eax

    /*Paging expects to be 8 in out case, but seems to only get to that number by adding 4 into cr0 instead TODO: Find out why. */
    mov   eax, cr0
    or    eax, HEX(40000000)
    mov   cr0, eax

    /* ESP points to the 0x500 that is saved just for the temporary stack after the stub is copied. */
    mov   esp, HEX(6010) + _APProtectedModeEnd - _APProtectedMode
    mov   ebp, 0
    hlt
_APProtectedModeEnd:
END

