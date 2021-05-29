/*
 * PROJECT:     ReactOS CRT
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * FILE:        sdk/lib/crt/math/atan2.c
 * PURPOSE:     Implementation of atan2
 * PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#define _USE_MATH_DEFINES
#include <math.h>

#define GET_SIGN_BIT(x) ((*(unsigned long long *)&(x)) & 0x8000000000000000ULL)

// See https://en.wikipedia.org/wiki/Atan2#Definition
double
__cdecl
atan2(double y, double x)
{
    if (x > 0.)
    {
        return atan(y / x);
    }
    else if (x < 0.)
    {
        if (y >= 0)
        {
            return atan(y / x) + M_PI;
        }
        else
        {
            return atan(y / x) - M_PI;
        }
    }
    else
    {
        if (y > 0.)
        {
            return M_PI / 2.;
        }
        else if (y < 0.)
        {
            return -M_PI / 2.;
        }
        else
        {
            /* Undefined case, this is what Windows returns */
            if (GET_SIGN_BIT(x) == 0)
            {
                return y;
            }
            else if (GET_SIGN_BIT(y) == 0)
            {
                return M_PI;
            }
            else
            {
                return -M_PI;
            }
        }
    }
}
