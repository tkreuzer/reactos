/*
 * PROJECT:     ReactOS CRT library
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Portable implementation of ceil
 * COPYRIGHT:   Copyright 2021 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits.h>

#ifdef _MSC_VER
#pragma warning(disable: 4164)
#pragma function(ceil)
#endif

double
__cdecl
ceil(double x)
{
    /* Check if x is positive */
    if ((*(unsigned long long*)&x & (1ULL << 63)) == 0)
    {
        /* Check if it fits into an int64 */
        if (x < (double)_I64_MAX)
        {
            long long ll = (long long)x;
            return (x > (double)ll) ? (double)ll + 1 : (double)ll;
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
        /* Check if it is up to 1. */
        if (x > -1.)
        {
            return -0.;
        }
        /* Check if it fits into an int64 */
        if (x > (double)_I64_MIN)
        {
            /* Just cast to int64, which will truncate towards 0,
               which is what we want here .*/
            x = (double)(long long)x;
            return (x == 0.) ? -0.0 : x;
        }
        else
        {
            /* The exponent is larger than the fraction bits.
            This means the number is already an integer. */
            return x;
        }
    }
}
