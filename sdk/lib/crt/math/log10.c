/*
 * PROJECT:     ReactOS CRT
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * FILE:        sdk/lib/crt/math/log10.c
 * PURPOSE:     Implementation of log10
 * PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include <math.h>

#ifdef _MSC_VER
#pragma warning(suppress:4164) /* intrinsic not declared */
#pragma function(log10)
#endif /* _MSC_VER */

double __cdecl log(double x);

#define LOG10 2.3025850929940456840179914546844

double
__cdecl
log10(double x)
{
    return log(x) / LOG10;
}
