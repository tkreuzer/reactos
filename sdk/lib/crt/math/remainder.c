/*
 * PROJECT:     ReactOS CRT
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * FILE:        sdk/lib/crt/math/remainder.c
 * PURPOSE:     Implementation of remainder
 * PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include <math.h>

#ifdef _MSC_VER
#pragma warning(suppress:4164) /* intrinsic not declared */
#pragma function(remainder)
#endif /* _MSC_VER */

double __cdecl floor(double x);

// See https://en.cppreference.com/w/c/numeric/math/remainder
double
__cdecl
remainder(double x, double y)
{
    double result, n;

    result = x / y;
    if (result >= 0)
    {
        n = floor(result + 0.5);
    }
    else
    {
        n = floor(result - 0.5);
    }

    return x - n * y;
}
