/*
* COPYRIGHT:        See COPYING in the top level directory
* PROJECT:          ReactOS CRT
* FILE:             lib/sdk/crt/math/remainder.c
* PURPOSE:          Generic C Implementation of remainder
* PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
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
