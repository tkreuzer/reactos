/*
 * PROJECT:     ReactOS CRT library
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Dummy-implementation of _invoke_matherr
 * COPYRIGHT:   Copyright 2022 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

// DO NOT SYNC WITH WINE OR MINGW32

#include <math.h>

int
__cdecl
_invoke_matherr(
    int type,
    char* name,
    double arg1,
    double arg2,
    double retval)
{
    return 0;
}
