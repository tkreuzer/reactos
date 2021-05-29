/*
* COPYRIGHT:        See COPYING in the top level directory
* PROJECT:          ReactOS CRT
* FILE:             lib/sdk/crt/math/fmod.c
* PURPOSE:          Generic C Implementation of fmod
* PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
*/

#include <math.h>

#ifdef _MSC_VER
#pragma warning(suppress:4164) /* intrinsic not declared */
#pragma function(fmod)
#endif /* _MSC_VER */

// Taken from https://en.cppreference.com/w/c/numeric/math/fmod
double
__cdecl
fmod(double x, double y)
{
#ifdef __GNUC__
#pragma STDC FENV_ACCESS ON
#endif
    double result = remainder(fabs(x), (y = fabs(y)));
    if (signbit(result)) result += y;
    return copysign(result, x);
}
