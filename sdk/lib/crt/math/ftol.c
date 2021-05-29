/*
* COPYRIGHT:        See COPYING in the top level directory
* PROJECT:          ReactOS CRT
* FILE:             lib/sdk/crt/math/_ftol.c
* PURPOSE:          Generic C Implementation of _ftol
* PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits.h>

#ifdef _MSC_VER
#pragma warning(disable: 4164)
#pragma function(_ftol)
#endif

long long
__cdecl
_ftol(double x)
{
    return (long long)x;
}
