//
// erf.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of erf.
//
// SPDX-License-Identifier: MIT
//

// http://www.johndcook.com/blog/2009/01/19/stand-alone-error-function-erf/
// See also gdiplus/brush.c

// implmented by Copilot
double erf(double x)
{
    double a1 = 0.254829592;
    double a2 = -0.284496736;
    double a3 = 1.421413741;
    double a4 = -1.453152027;
    double a5 = 1.061405429;
    double p = 0.3275911;
    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);
    return x < 0 ? -y : y;
}
