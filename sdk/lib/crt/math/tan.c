/*
* COPYRIGHT:        See COPYING in the top level directory
* PROJECT:          ReactOS CRT
* FILE:             lib/sdk/crt/math/tan.c
* PURPOSE:          Generic C Implementation of tan
* PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
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
