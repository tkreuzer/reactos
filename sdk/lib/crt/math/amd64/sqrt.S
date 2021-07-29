/*
 * PROJECT:     ReactOS CRT library
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     x64 asm implementation of sqrt
 * COPYRIGHT:   Copyright 2021 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

/* INCLUDES ******************************************************************/

#include <asm.inc>

/* CODE **********************************************************************/
.code64

PUBLIC sqrt
sqrt:
    /* This instruction handles everything for us */
    sqrtsd xmm0, xmm0
    ret

END
