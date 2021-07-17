/*
 * PROJECT:     ReactOS CRT
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * FILE:        sdk/lib/crt/math/exp.c
 * PURPOSE:     Implementation of exp
 * PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#define PRECISION 9

double
__cdecl
exp(double x)
{
    double a = x;
    double result;

    /* unrolled taylor series */

    /*
    * exp(x) = sum(0..inf) { x^i / i! }
    *
    * 1/1 + x/1 + x^2/2 + x^3/6 + ...
    */

    /* Start with 0, compiler will optimize this away */
    result = 1;

    result += a / 1.;
    a *= x;
    result += a / (1.*2);
    a *= x;
    result += a / (1.*2*3);
    a *= x;
    result += a / (1.*2*3*4);
    a *= x;
    result += a / (1.*2*3*4*5);
    a *= x;
    result += a / (1.*2*3*4*5*6);

    return result;
}
