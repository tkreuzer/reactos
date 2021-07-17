/*
 * PROJECT:     ReactOS CRT
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * FILE:        sdk/lib/crt/math/tan.c
 * PURPOSE:     Implementation of tan
 * PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include <math.h>

#ifdef _MSC_VER
#pragma warning(suppress:4164) /* intrinsic not declared */
#pragma function(tan)
#endif /* _MSC_VER */

double __cdecl sin(double x);
double __cdecl cos(double x);

double
__cdecl
tan(double x)
{
    // CHECKME: this might not be very accurate
    return sin(x) / cos(x);
}
