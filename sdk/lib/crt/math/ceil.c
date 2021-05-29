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
    /* Load the value as uint64 */
    unsigned long long u64 = *(unsigned long long*)&x;

    /* Check for NAN */
    if ((u64 & ~(1ULL << 63)) > 0x7FF0000000000000ull)
    {
        /* Set error bit */
        u64 |= 0x0008000000000000ull;
        return *(double*)&u64;
    }

    /* Check if x is positive */
    if ((u64 & (1ULL << 63)) == 0)
    {
        /* Check if it fits into an int64 */
        if (x <= (double)_I64_MAX)
        {
            /* Here we need to first offset the value into the negative
               range, so that we truncate down towards 0. Then we offset
               the result back accordingly. */
            return (double)((long long)(x - _I64_MAX)) + _I64_MAX);
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
        if (x >= (double)_I64_MIN)
        {
            /* Cast to int64 to truncate towards 0. */
            return (double)(long long)x;
        }
        else
        {
            /* The exponent is larger than the fraction bits.
               This means the number is already an integer. */
            return x;
        }
    }
}
