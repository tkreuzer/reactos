/*
* COPYRIGHT:        See COPYING in the top level directory
* PROJECT:          ReactOS CRT
* FILE:             lib/sdk/crt/math/floor.c
* PURPOSE:          Generic C Implementation of floor
* PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits.h>

#ifdef _MSC_VER
#pragma warning(disable: 4164)
#pragma function(floor)
#endif

double
__cdecl
floor(double x)
{
    /* Check if x is positive */
    if (x >= 0)
    {
        /* Check if it fits into an int64 */
        if (x <= (double)_I64_MAX)
        {
            /* Just cast to int64, which will truncate towards 0,
               which is what we want here .*/
            return (double)(long long)x;
        }
        else
        {
            /* The exponent is larger than the fraction bits.
               This means the number is already an integer. */
            return x;
        }
    }
    else
    {
        /* Check if it fits into an int64 */
        if (x >= (double)_I64_MIN)
        {
            /* Here we need to first offset the value into the positive
               range, so that we truncate down towards 0. Then we offset
               the result back accordingly. */
            return (double)((long long)(x - _I64_MIN)) + _I64_MIN);
        }
        else
        {
            /* The exponent is larger than the fraction bits.
               This means the number is already an integer. */
            return x;
        }
    }
}
