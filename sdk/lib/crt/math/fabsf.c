/*
 * PROJECT:     ReactOS CRT library
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Portable implementation of fabsf
 * COPYRIGHT:   Copyright 2021 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#include <math.h>

#include <stdio.h>

_Check_return_
float
__cdecl
fabsf2(
    _In_ float x)
{
    /* Load the value as uint */
    unsigned int u32 = *(unsigned int*)&x;

    /* Clear the sign bit */
    u32 &= ~(1 << 31);

    /* Check for NAN */
    if (u32 > 0x7F800000)
    {
        /* Set error bit */
        *(unsigned int*)&x |= 0x00400000;
        return x;
    }

    /* Convert back to float */
    return *(float*)&u32;
}

_Check_return_
float
__cdecl
fabsf(
    _In_ float x)
{
    union
    {
        float flt;
        unsigned int u32;
    } u;
    unsigned int u32b;

    u.flt = x;

    /* Clear the sign bit */
    u32b = u.u32 & ~(1 << 31);

    /* Check for NAN */
    if (u32b > 0x7F800000)
    {
        u.u32 |= 0x00400000;
    }
    else
    {
        u.u32 = u32b;
    }

    /* Convert back to float */
    return u.flt;
}
