/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS system libraries
 * PURPOSE:           Implementation of _chkstk and _alloca_probe
 * FILE:              lib/sdk/crt/math/amd64/chkstk_asm.s
 * PROGRAMMER:        Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <ndk/amd64/asm.h>
#include <ndk/amd64/asmmacro.S>

.intel_syntax noprefix

.global _MsgUnimplemented
_MsgUnimplemented:
.asciz "WARNING:  %s at %s:%d is UNIMPLEMENTED!\n"


.proc _chkstk
    UNIMPLEMENTED chkstk
    ret
.endproc

.proc _alloca_probe
    UNIMPLEMENTED alloca_probe
    ret
.endproc

/* EOF */