/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Bootsector
 * FILE:            boot/freeldr/bootsect/bootsector.inc
 * PURPOSE:         Provide useful macros to be shared between bootsectors
 * PROGRAMMERS:     Timo Kreuzer
 */

#if 0
MACRO(resb_once, name, size)
    ifndef __is_reserved_&name
        __is_reserved_&name = 1
        resb name, size
    endif
ENDM
#endif

#if 0
/******************************************************************************
 *                        Check for INT 13h extensions                        *
 ******************************************************************************/
MACRO(CheckForINT13hExtensions)

    /* Call INT 13h, AH = 41h - INT 13 extensions installation check
        AH = 41h
        BX = 55AAh
        DL = drive */
    mov  ah, HEX(41)
    mov  bx, HEX(55AA)
    int  HEX(13)

    /* Return from INT 13h:
        CF set on error
            AH = 01h (invalid function)
        CF clear if successful
            AH = major version of extensions
            BX = AA55h if installed
            AL = internal use
            CX = API subset support bitmap
                Bit 0, extended disk access functions
            DH = extension version */

    /* Use CHS if extensions are not supported */
    jc NoInt13Ext
    cmp bx, HEX(0aa55)
    jne NoInt13Ext

    /* Save API support bits */
    mov byte ptr [Int13APISupportBits], cl

NoInt13Ext:
ENDM
#endif
