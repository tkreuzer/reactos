/*
* COPYRIGHT:        See COPYING in the top level directory
* PROJECT:          ReactOS CRT
* FILE:             lib/sdk/crt/math/log10.c
* PURPOSE:          Generic C Implementation of log10
* PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
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
