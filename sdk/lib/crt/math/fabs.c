/*
* COPYRIGHT:        See COPYING in the top level directory
* PROJECT:          ReactOS CRT
* FILE:             lib/sdk/crt/math/fabs.c
* PURPOSE:          Generic C Implementation of fabs
* PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
*/

#ifdef _MSC_VER
#pragma warning(disable: 4164)
#pragma function(fabs)
#endif

int
__cdecl
fabs(double x)
{
    return x < 0 ? -x : x;
}
