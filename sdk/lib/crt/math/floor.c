/*
 * PROJECT:     ReactOS CRT library
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * FILE:        sdk/lib/crt/math/floor.c
 * PURPOSE:     Implementation of floor
 * PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
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
            return (double)((long long)(x - _I64_MIN)) + _I64_MIN;
        }
        else
        {
            /* The exponent is larger than the fraction bits.
               This means the number is already an integer. */
            return x;
        }
    }
}
