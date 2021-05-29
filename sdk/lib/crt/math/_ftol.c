/*
 * PROJECT:     ReactOS CRT
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * FILE:        sdk/lib/crt/math/_ftol.c
 * PURPOSE:     Implementation of _ftol
 * PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits.h>

long long
__cdecl
_ftol(double x)
{
    return (long long)x;
}
