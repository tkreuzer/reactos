/*
 * PROJECT:     ReactOS api tests
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Tests for CRT math functions
 * COPYRIGHT:   Copyright 2021 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#include <apitest.h>
#include <stdio.h>
#include "math_helpers.h"

#ifdef _MSC_VER
#pragma function(abs)
#pragma function(acos)
#pragma function(asin)
#pragma function(atan)
#pragma function(atan2)
#pragma function(ceil)
#pragma function(cos)
#pragma function(exp)
#pragma function(floor)
//#pragma function(ldexp)
#pragma function(log)
#pragma function(log10)
#pragma function(pow)
#pragma function(sin)
#pragma function(sqrt)
#pragma function(tan)
#ifdef _M_AMD64
#pragma function(acosf)
#pragma function(asinf)
#pragma function(atanf)
#pragma function(ceilf)
#pragma function(cosf)
#pragma function(expf)
#pragma function(floorf)
#pragma function(log10f)
#pragma function(logf)
#pragma function(powf)
#pragma function(sinf)
#pragma function(sqrtf)
#pragma function(tanf)
#endif
#endif

const ULONG64 U64_DOUBLE_0          = 0x0000000000000000ULL;
const ULONG64 U64_DOUBLE_MINUS_0    = 0x8000000000000000ULL;
const ULONG64 U64_DOUBLE_INF        = 0x7FF0000000000000ULL;
const ULONG64 U64_DOUBLE_MINUS_INF  = 0xFFF0000000000000ULL;
const ULONG64 U64_DOUBLE_QNAN       = 0x7FF8000000000000ULL; // 1.#QNAN0
const ULONG64 U64_DOUBLE_IND        = 0xFFF8000000000000ULL; // -1.#IND
const ULONG64 U64_DOUBLE_SNAN       = 0x7FF0000000000001ULL; // 1.#SNAN0
const ULONG64 U64_DOUBLE_MINUS_SNAN = 0xFFF0000000000001ULL; // 1.#SNAN0
const ULONG64 U64_DOUBLE_MIN        = 0xC1E0000000000000ULL; // 1.060998e-314


float fnull = 0.;

#define print_u32(x) printf(#x " = %e [0x%0x]\n", u32_to_flt(x), x)

#if 0
// Taken from https://referencesource.microsoft.com/#windowsbase/Shared/MS/Internal/DoubleUtil.cs
static BOOL AreClose(double value1, double value2)
{
    //in case they are Infinities (then epsilon check does not work)
    if(value1 == value2) return TRUE;
    // This computes (|value1-value2| / (|value1| + |value2| + 10.0)) < DBL_EPSILON
    double eps = (abs(value1) + abs(value2) + 10.0) * DBL_EPSILON;
    double delta = value1 - value2;
    return(-eps < delta) && (eps > delta);
}
#endif

#define DBL_MAX_ERROR DBL_EPSILON
#define FLT_MAX_ERROR FLT_EPSILON

static BOOL almost_equal(double d1, double d2, int  use_float)
{
    double margin = use_float ? FLT_MAX_ERROR : DBL_MAX_ERROR;
    double error = d1 - d2;
    double rel_error;

    if (error == 0)
        return TRUE;

    /* Normalize the sign */
    if (error < 0)
        error = -error;
    if (d2 < 0)
        d2 = -d2;

    /* If d2 is 0, we can't calculate the relative error */
    if (d2 == 0.)
    {
        /* Use the error directly */
        rel_error = error;
        //margin = margin / 2;
        //d2 = use_float ? FLT_MIN : DBL_MIN;
    }

    /* Check for very small/large values and adjust both exponents */
    else if (d2 < 1e-10)
    {
        rel_error = (error * 1e10) / (d2 * 1e10);
    }
    else if (d2 > 1e10)
    {
        rel_error = (error * 1e-10) / (d2 * 1e-10);
    }
    else
    {
        rel_error = error / d2;
    }

    if (rel_error < margin)
        return TRUE;

    printf("d1=%e, d2=%e, rel_error = %*e, margin=%e\n", d1, d2, DBL_DECIMAL_DIG, rel_error, margin);

    return FALSE;
}

static BOOL almost_equal2(double d1, double d2, int  use_float)
{
    double margin = use_float ? FLT_MAX_ERROR : DBL_MAX_ERROR;
    double quotient;
    double rel_error;

    if (d2 == 0.)
    {
        quotient = d1 / (use_float ? FLT_MIN : DBL_MIN);
    }
    else
    {
        quotient = d1 / d2;
    }

    rel_error = quotient - 1;

    if (rel_error < margin)
        return TRUE;

    printf("d1=%e, d2=%e, rel_error = %*e, margin=%e\n", d1, d2, DBL_DECIMAL_DIG, rel_error, margin);
    return FALSE;
}

#define ok_eq_dbl(x, y) ok(dbl_to_u64(x) == dbl_to_u64(y), #x " = %.*e [0x%016llX], expected %.*e [0x%016llX]\n", DBL_DECIMAL_DIG, x, dbl_to_u64(x), DBL_DECIMAL_DIG, y, dbl_to_u64(y));
#define ok_eq_dbl_u64(x, y) ok(dbl_to_u64(x) == y, #x " = %e [0x%016llX], expected %e [0x%016llX]\n", x, dbl_to_u64(x), u64_to_dbl(y), y);
#define ok_near_dbl(x, y) ok(almost_equal(x, y, 0), #x " = %.*e, expected %.*e\n", DBL_DECIMAL_DIG, x, DBL_DECIMAL_DIG, y);

#define ok_eq_flt(x, y) ok(flt_to_u32(x) == flt_to_u32(y), #x " = %.*e [0x%08X], expected %.*e [0x%08X]\n", FLT_DECIMAL_DIG, x, flt_to_u32(x), FLT_DECIMAL_DIG, y, flt_to_u32(y));
#define ok_eq_flt_u32(x, y) ok(flt_to_u32(x) == y, #x " = %e [0x%08X], expected %e [0x%08X]\n", x, flt_to_u32(x), u32_to_flt(y), y);
#define ok_near_flt(x, y) ok(almost_equal((double)(x), (double)(y), 1), #x " = %.*e, expected %.*e\n", FLT_DECIMAL_DIG, (double)(x), FLT_DECIMAL_DIG, (double)(y));


#ifdef _M_AMD64
#define on_x86 if (0)
#define on_x64 if (1)
#else
#define on_x86 if (1)
#define on_x64 if (0)
#endif

#ifdef _M_IX86
#define FLT_MAX_INT 10000
void Test__ftol()
{
    int i;
    struct { double d; long long l; }
    tests[] =
    {
        { 0.0, 0 },
        { 0.8, 0 },
        { 42.5, 42 },
        { (double)INT_MAX, INT_MAX },
        { (double)LLONG_MAX, 0x8000000000000000ll },
    };

    for (i = 0; i < _countof(tests); i++)
    {
        ok_int64(tests[i].d, tests[i].l);
    }
}
#endif

void Test_abs()
{
    ok_int(abs(0), 0);
    ok_int(abs(1), 1);
    ok_int(abs(-1), 1);
    ok_int(abs(-INT_MAX), INT_MAX);
    ok_int(abs(INT_MIN), INT_MIN);
}

void Test_acos()
{
    const double test_constants[] = {
        0., 1., 2., 1.0000001, 0.0000001,
        M_E, M_LOG2E, M_LOG10E, M_LN2, M_LN10, M_PI, M_PI_2, M_PI_4, M_1_PI, M_2_PI, M_2_SQRTPI, M_SQRT2, M_SQRT1_2
    };
    int i;

    /* Special values */
    ok_eq_dbl_u64(acos(u64_to_dbl(0x7FF0000000000000ull)), 0xFFF8000000000000ull); // INF -> INF
    ok_eq_dbl_u64(acos(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(acos(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(acos(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(acos(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    ok_near_dbl(acos(cos(0)), 0.);
    ok_near_dbl(acos(cos(M_PI)), M_PI);
    ok_near_dbl(acos(cos(-M_PI)), M_PI);

    ok_near_dbl(acos(0.), M_PI_2);
    ok_near_dbl(acos(u64_to_dbl(U64_DOUBLE_MINUS_0)), M_PI_2);
    ok_near_dbl(acos(1.), 0.);
    ok_near_dbl(acos(-1.), M_PI);
    ok_near_dbl(acos(0.5), 1.0471975511965977461542144610932);
    ok_near_dbl(acos(-0.5), 2.0943951023931954923084289221863);
    ok_near_dbl(acos(cos(-1)), 1.);

    ok_eq_dbl_u64(acos(1. + DBL_EPSILON), U64_DOUBLE_IND);
    ok_eq_dbl_u64(acos(-1. - DBL_EPSILON), U64_DOUBLE_IND);
    ok_eq_dbl_u64(acos(123.456789), U64_DOUBLE_IND);
    ok_eq_dbl_u64(acos(DBL_MAX), U64_DOUBLE_IND);

    for (i = 0; i < sizeof(test_constants) / sizeof(test_constants[0]); i++)
    {
        double check = acos(cos(test_constants[i]));
        double error = check - test_constants[i];
        ok(((error >= 0) && (error < 1e-9)) || ((error < 0) && (error > -1e-9)),
           "i = %u, value = %e, error = %e\n",
           i, test_constants[i], error);
    }

}

#if 0
void Test_acosf()
{
    /* Special values */
    ok_eq_flt_u32(acosf(u32_to_flt(0x7F800000)), 0xFFC00000); // INF -> -NAN(IND)
    ok_eq_flt_u32(acosf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(acosf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(acosf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    ok_near_flt(acosf(0.), M_PI_2);
    ok_near_flt(acosf(u64_to_dbl(U64_DOUBLE_MINUS_0)), M_PI_2);
    ok_near_flt(acosf(1.), 0.);
    ok_near_flt(acosf(-1.), M_PI);
    ok_near_flt(acosf(0.5), 1.04719755119659790);
    ok_near_flt(acosf(-0.5), 2.09439510239319570);
    ok_near_flt(acosf(cos(-1)), 1.);
}

void Test_asin()
{
    /* Special values */
    ok_eq_dbl_u64(asin(u64_to_dbl(0x7FF0000000000000ull)), 0xFFF8000000000000ull); // INF -> -NAN(IND)
    ok_eq_dbl_u64(asin(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(asin(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(asin(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(asin(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    ok_eq_dbl(asin(-2.), u64_to_dbl(U64_DOUBLE_IND));
    ok_near_dbl(asin(-1.), -M_PI/2);
    ok_near_dbl(asin(-0.5), -M_PI/6);
    ok_near_dbl(asin(-DBL_MIN), 0.);
    ok_near_dbl(asin(0.), 0.);
    ok_near_dbl(asin(DBL_MIN), 0.);
    ok_near_dbl(asin(0.5), M_PI/6);
    ok_near_dbl(asin(1.), M_PI/2);
    ok_eq_dbl(asin(2.), u64_to_dbl(U64_DOUBLE_IND));

}

void Test_asinf()
{
    /* Special values */
    ok_eq_flt_u32(asinf(u32_to_flt(0x7F800000)), 0xFFC00000); // INF -> -NAN(IND)
    ok_eq_flt_u32(asinf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(asinf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(asinf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    ok_eq_flt_u32(asinf(-2.f), 0xFFC00000); // -> -NAN(IND)
    ok_near_flt(asinf(-1.f), -M_PI/2);
    ok_near_flt(asinf(-0.5f), -M_PI/6);
    ok_near_flt(asinf(-FLT_MIN), 0.);
    ok_near_flt(asinf(0.f), 0.);
    ok_near_flt(asinf(FLT_MIN), 0.);
    ok_near_flt(asinf(0.5f), M_PI/6);
    ok_near_flt(asinf(1.f), M_PI/2);
    ok_eq_flt_u32(asinf(2.f), 0xFFC00000); // -> -NAN(IND)

}

void Test_atan()
{
    /* Special values */
    ok_eq_dbl_u64(atan(u64_to_dbl(0x7FF0000000000000ull)), 0x3FF921FB54442D18ull); // INF -> 1.570796e+000
    ok_eq_dbl_u64(atan(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0xFFF0000000000000ull)), 0xBFF921FB54442D18ull); // -INF -> -1.570796e+000
    ok_eq_dbl_u64(atan(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(atan(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(atan(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    ok_near_dbl(atan(-DBL_MAX), -M_PI_2);
    ok_near_dbl(atan(-100), -1.56079666010823150);
    ok_near_dbl(atan(-10), -1.47112767430373470);
    ok_near_dbl(atan(-2), -1.10714871779409040);
    ok_near_dbl(atan(-1), -M_PI_4);
    ok_near_dbl(atan(0.), 0.);
    ok_near_dbl(atan(1), M_PI_4);
    ok_near_dbl(atan(3), 1.24904577239825440);
    ok_near_dbl(atan(15), 1.50422816301907280);
    ok_near_dbl(atan(100), 1.56079666010823150);
    ok_near_dbl(atan(1000), 1.56979632712822980);
    ok_near_dbl(atan(1e10), 1.57079632669489650);
    ok_near_dbl(atan(1e15), 1.57079632679489570);
    ok_near_dbl(atan(1e16), M_PI_2);
    ok_near_dbl(atan(DBL_MAX), M_PI_2);
}

void Test_atanf()
{
    /* Special values */
    ok_eq_flt_u32(atanf(u32_to_flt(0x7F800000)), 0x3FC90FDB); // INF -> 1.570796e+000
    ok_eq_flt_u32(atanf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0xFF800000)), 0xBFC90FDB); // -INF -> -1.570796e+000
    ok_eq_flt_u32(atanf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(atanf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    ok_near_flt(atanf(-FLT_MAX), -M_PI_2);
    ok_near_flt(atanf(-100), -1.56079666010823150);
    ok_near_flt(atanf(-10), -1.47112767430373470);
    ok_near_flt(atanf(-2), -1.10714871779409040);
    ok_near_flt(atanf(-1), -M_PI_4);
    ok_near_flt(atanf(0.), 0.);
    ok_near_flt(atanf(1), M_PI_4);
    ok_near_flt(atanf(3), 1.24904577239825440);
    ok_near_flt(atanf(15), 1.50422816301907280);
    ok_near_flt(atanf(100), 1.56079666010823150);
    ok_near_flt(atanf(1000), 1.56979632712822980);
    ok_near_flt(atanf(1e10), 1.57079632669489650);
    ok_near_flt(atanf(FLT_MAX), M_PI_2);
}

void Test_atan2()
{
    /* Special values */
#if 0
    ok_eq_dbl_u64(atan2(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(atan2(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(atan2(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(atan2(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(atan2(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN
#endif

    ok_near_dbl(atan2(-DBL_MAX, -DBL_MAX), -2.35619449019234480);
    ok_near_dbl(atan2(-DBL_MAX, -1000.), -1.57079632679489660);
    ok_near_dbl(atan2(-DBL_MAX, -1.), -1.57079632679489660);
    ok_near_dbl(atan2(-DBL_MAX, -0.), -1.57079632679489660);
    ok_near_dbl(atan2(0., -DBL_MAX), M_PI);
    ok_near_dbl(atan2(0., -1000.), M_PI);
    ok_near_dbl(atan2(0., -1.), M_PI);
    ok_near_dbl(atan2(0., -DBL_MIN), M_PI);
    ok_near_dbl(atan2(0., u64_to_dbl(U64_DOUBLE_MINUS_0)), M_PI);
    ok_near_dbl(atan2(0., 0.), 0.);
    ok_near_dbl(atan2(0., 0.001), 0.);
    ok_near_dbl(atan2(0., 10.), 0.);
    ok_near_dbl(atan2(0., 1000.), 0.);
    ok_near_dbl(atan2(0., DBL_MAX), 0.);
}

void Test_ceil()
{
    /* Special values */
    ok_eq_dbl_u64(ceil(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(ceil(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF0000000000000ull); // -INF -> -INF
    ok_eq_dbl_u64(ceil(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(ceil(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(ceil(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    ok_eq_dbl(ceil(-DBL_MAX), -DBL_MAX);
    ok_eq_dbl(ceil(-1000.0000001), -1000.);
    ok_eq_dbl(ceil(-1.00000001), -1.);
    ok_eq_dbl(ceil(-1. - DBL_MIN), -1.);
    ok_eq_dbl(ceil(-1. + DBL_MIN), -1.);
    ok_eq_dbl(ceil(-DBL_MIN), -0.);
    ok_eq_dbl(ceil(-DBL_TRUE_MIN), -0.);
    ok_eq_dbl(ceil(0.), 0.);
    ok_eq_dbl(ceil(DBL_TRUE_MIN), 1.);
    ok_eq_dbl(ceil(DBL_MIN), 1.);
    ok_eq_dbl(ceil(1. + DBL_TRUE_MIN), 1.);
    ok_eq_dbl(ceil(1. + DBL_MIN), 1.);
    ok_eq_dbl(ceil(1. + DBL_EPSILON / 2), 1.);
    ok_eq_dbl(ceil(1. + DBL_EPSILON), 2.);
    ok_eq_dbl(ceil(1.00000001), 2.);
    ok_eq_dbl(ceil(1000.0000001), 1001.);
    ok_eq_dbl(ceil(DBL_MAX), DBL_MAX);
    ok_eq_dbl(ceil(DBL_MAX + DBL_TRUE_MIN), DBL_MAX);
    ok_eq_dbl(ceil(DBL_MAX + DBL_MIN), DBL_MAX);
}

void Test_ceilf()
{
    /* Special values */
    ok_eq_flt_u32(ceilf(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF
    ok_eq_flt_u32(ceilf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0xFF800000)), 0xFF800000); // -INF -> -INF
    ok_eq_flt_u32(ceilf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(ceilf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    ok_eq_flt(ceilf(-FLT_MAX), -FLT_MAX);
    ok_eq_flt(ceilf(-1000.0000001f), -1000.f);
    ok_eq_flt(ceilf(-1.00000001f), -1.f);
    ok_eq_flt(ceilf(-1.f - FLT_MIN), -1.f);
    ok_eq_flt(ceilf(-1.f + FLT_MIN), -1.f);
    ok_eq_flt(ceilf(-FLT_MIN), -0.f);
    ok_eq_flt(ceilf(-FLT_TRUE_MIN), -0.f);
    ok_eq_flt(ceilf(0.f), 0.f);
    ok_eq_flt(ceilf(FLT_TRUE_MIN), 1.f);
    ok_eq_flt(ceilf(FLT_MIN), 1.f);
    ok_eq_flt(ceilf(1.f + FLT_TRUE_MIN), 1.f);
    ok_eq_flt(ceilf(1.f + FLT_MIN), 1.f);
    ok_eq_flt(ceilf(1.f + FLT_EPSILON / 2), 1.f);
    ok_eq_flt(ceilf(1.f + FLT_EPSILON), 2.f);
    ok_eq_flt(ceilf(1.0000000596f), 1.f);
    ok_eq_flt(ceilf(1.0000000597f), 2.f);
    ok_eq_flt(ceilf(1.00000001f), 1.f);
    ok_eq_flt(ceilf(1000.0000305f), 1000.f);
    ok_eq_flt(ceilf(1000.0000306f), 1001.f);
    ok_eq_flt(ceilf(FLT_MAX), FLT_MAX);
    ok_eq_flt(ceilf(FLT_MAX + FLT_TRUE_MIN), FLT_MAX);
    ok_eq_flt(ceilf(FLT_MAX + FLT_MIN), FLT_MAX);
}

void Test_cos()
{
    /* Special values */
    ok_eq_dbl_u64(cos(u64_to_dbl(0x7FF0000000000000ull)), 0xFFF8000000000000ull); // INF -> -NAN(IND)
    ok_eq_dbl_u64(cos(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(cos(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(cos(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(cos(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    /* Range between -2PI and 2PI */
    ok_eq_dbl(cos(-2 * M_PI), 1.);
    ok_near_dbl(cos(-M_PI - M_PI_2), 0.);
    ok_eq_dbl(cos(-M_PI), -1.);
    ok_near_dbl(cos(-M_PI_2), 0.);
    ok_eq_dbl(cos(0.), 1.);
    ok_near_dbl(cos(DBL_MIN), 1.);
    ok_near_dbl(cos(M_PI_2), 0.);
    ok_eq_dbl(cos(M_PI), -1.);
    ok_near_dbl(cos(M_PI + M_PI_2), 0.);
    ok_eq_dbl(cos(2 * M_PI), 1.);


}

void Test_cosf()
{
    /* Special values */
    ok_eq_flt_u32(cosf(u32_to_flt(0x7F800000)), 0xFFC00000); // INF -> -NAN(IND)
    ok_eq_flt_u32(cosf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(cosf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(cosf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    //on_x64 ok_near_flt(cosf(-FLT_MAX), 8.530210257e-001F);
    //on_x86 ok_near_flt(cosf(-FLT_MAX), -2.293052077e-001);

}

void Test_exp()
{
    /* Special values */
    ok_eq_dbl_u64(exp(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(exp(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0xFFF0000000000000ull)), 0x0000000000000000ull); // -INF -> 0.
    ok_eq_dbl_u64(exp(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(exp(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(exp(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    ok_eq_dbl(exp(-DBL_MAX), 0.);
    ok_eq_dbl(exp(-DBL_MAX_EXP), 0.);
    ok_eq_dbl(exp(-745.2), 0.);
    on_x86 ok_eq_dbl(exp(-745.1), 0.);
    on_x64 ok_eq_dbl(exp(-745.1), 4.94065645841246540e-324);
    ok_eq_dbl(exp(-744.4), 4.94065645841246540e-324);
    on_x64 ok_eq_dbl(exp(-DBL_MAX_10_EXP), 1.72702877557863010e-134);
    ok_near_dbl(exp(-DBL_MAX_10_EXP), 1.72702877557863010e-134);
    ok_near_dbl(exp(-10.), 4.53999297624848540e-005);
    ok_near_dbl(exp(-1.), 3.67879441171442330e-001);
    ok_near_dbl(exp(-5.6E-17), 9.99999999999999890e-001);
    ok_near_dbl(exp(-5.5E-17), 1.);
    ok_eq_dbl(exp(-DBL_MIN), 1.);
    ok_eq_dbl(exp(u64_to_dbl(U64_DOUBLE_MINUS_0)), 1.);
    ok_eq_dbl(exp(0.), 1.);
    ok_eq_dbl(exp(DBL_MIN), 1.);
    ok_near_dbl(exp(1.11e-16), 1.);
    ok_near_dbl(exp(1.12e-16), 1.0000000000000002);
    ok_near_dbl(exp(M_PI), 2.31406926327792670e+001);
    ok_near_dbl(exp(709.7), 1.65498402768026440e+308);
    ok_eq_dbl_u64(exp(709.8), U64_DOUBLE_INF);
    ok_eq_dbl_u64(exp(DBL_MAX), U64_DOUBLE_INF);
}

void Test_expf()
{
    /* Special values */
    ok_eq_flt_u32(expf(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF
    ok_eq_flt_u32(expf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(expf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(expf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(expf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(expf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(expf(u32_to_flt(0xFF800000)), 0x00000000); // -INF -> 0.
    ok_eq_flt_u32(expf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(expf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(expf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(expf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(expf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    ok_eq_flt(expf(-FLT_MAX), 0.F);
   // ok_eq_flt(expf(-FLT_MAX_EXP), 2.57220937264241480e-056F);
    ok_eq_flt(expf(-745.2F), 0.F);
   // ok_eq_flt(expf(-745.1F), 4.94065645841246540e-324F);
    ok_eq_flt(expf(-FLT_MAX_10_EXP), 3.13913288840975390e-017F);
    ok_eq_flt(expf(-10.F), 4.53999297624848540e-005F);
    ok_eq_flt(expf(-1.), 3.67879441171442330e-001F);
    ok_eq_flt(expf(-5.7E-10F), 9.99999999999999890e-001F);
    ok_eq_flt(expf(-5.6E-10F), 1.F);
    ok_eq_flt(expf(-FLT_MIN), 1.F);
    //ok_eq_flt(expf(u64_to_dbl(U64_DOUBLE_MINUS_0)), 1.F);
    ok_eq_flt(expf(0.F), 1.F);
    ok_eq_flt(expf(FLT_MIN), 1.F);
    ok_eq_flt(expf(1.11e-10F), 1.F);
    ok_eq_flt(expf(1.12e-10F), 1.0000000000000002F);
    ok_eq_flt(expf((float)M_PI), 2.31406955718994140e+001F);
    ok_eq_flt(expf(88.7F), 3.32597686440668500e+038F);
    //ok_eq_dbl_u64(expf(88.8F), U64_DOUBLE_INF);
    //ok_eq_dbl_u64(expf(FLT_MAX), U64_DOUBLE_INF);
}

double
__cdecl
fabs2(
    _In_ double x);

#pragma function(fabs)
static void Test_fabs()
{
    //printf("fabs = %p, fabs2 = %p\n", fabs, fabs2);
    //ok_eq_dbl_u64(fabs2(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF

    /* Special values */
    ok_eq_dbl_u64(fabs(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(fabs(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF0000000000001ull); // NAN(SNAN) -> NAN(SNAN)
    ok_eq_dbl_u64(fabs(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FF7FFFFFFFFFFFFull); // NAN(SNAN) -> NAN(SNAN)
    ok_eq_dbl_u64(fabs(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(fabs(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(fabs(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(fabs(u64_to_dbl(0xFFF0000000000000ull)), 0x7FF0000000000000ull); // -INF -> INF
    ok_eq_dbl_u64(fabs(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF0000000000001ull); // -NAN(SNAN) -> -NAN(SNAN)
    ok_eq_dbl_u64(fabs(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFF7FFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN(SNAN)
    ok_eq_dbl_u64(fabs(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(fabs(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(fabs(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    ok_eq_dbl(fabs(-DBL_MAX), DBL_MAX);
    ok_eq_dbl(fabs(-1000.0000001), 1000.0000001);
    ok_eq_dbl(fabs(-1.00000001), 1.00000001);
    ok_eq_dbl(fabs(-1. - DBL_MIN), 1. + DBL_MIN);
    ok_eq_dbl(fabs(-1. + DBL_MIN), 1. - DBL_MIN);
    ok_eq_dbl(fabs(-DBL_MIN), DBL_MIN);
    ok_eq_dbl(fabs(-DBL_TRUE_MIN), DBL_TRUE_MIN);
    ok_eq_dbl(fabs(-0.), 0.);
    ok_eq_dbl(fabs(0.), 0.);
    ok_eq_dbl(fabs(DBL_TRUE_MIN), DBL_TRUE_MIN);
    ok_eq_dbl(fabs(DBL_MIN), DBL_MIN);
    ok_eq_dbl(fabs(1. + DBL_TRUE_MIN), 1. + DBL_TRUE_MIN);
    ok_eq_dbl(fabs(1. + DBL_MIN), 1. + DBL_MIN);
    ok_eq_dbl(fabs(1.00000001), 1.00000001);
    ok_eq_dbl(fabs(1000.0000001), 1000.0000001);
    ok_eq_dbl(fabs(DBL_MAX), DBL_MAX);
    ok_eq_dbl(fabs(DBL_MAX + DBL_TRUE_MIN), DBL_MAX + DBL_TRUE_MIN);
    ok_eq_dbl(fabs(DBL_MAX + DBL_MIN), DBL_MAX + DBL_MIN);
}

_Check_return_
float
__cdecl
fabsf2(
    _In_ float x);

static void Test_fabsf()
{
    //printf("fabsf = %p, fabsf2 = %p\n", fabsf, fabsf2);
    //ok_eq_flt_u32(fabsf2(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF

    /* Special values */
    ok_eq_flt_u32(fabsf(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF
    ok_eq_flt_u32(fabsf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0xFF800000)), 0x7F800000); // -INF -> INF
    ok_eq_flt_u32(fabsf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(fabsf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    ok_eq_flt(fabsf(-FLT_MAX), FLT_MAX);
    ok_eq_flt(fabsf(-1000.0000001f), 1000.0000001f);
    ok_eq_flt(fabsf(-1.00000001f), 1.00000001f);
    ok_eq_flt(fabsf(-1.f - FLT_MIN), 1.f + FLT_MIN);
    ok_eq_flt(fabsf(-1.f + FLT_MIN), 1.f - FLT_MIN);
    ok_eq_flt(fabsf(-FLT_MIN), FLT_MIN);
    ok_eq_flt(fabsf(-FLT_TRUE_MIN), FLT_TRUE_MIN);
    ok_eq_flt(fabsf(-0.f), 0.);
    ok_eq_flt(fabsf(0.f), 0.);
    ok_eq_flt(fabsf(FLT_TRUE_MIN), FLT_TRUE_MIN);
    ok_eq_flt(fabsf(FLT_MIN), FLT_MIN);
    ok_eq_flt(fabsf(1.f + FLT_TRUE_MIN), 1. + FLT_TRUE_MIN);
    ok_eq_flt(fabsf(1.f + FLT_MIN), 1. + FLT_MIN);
    ok_eq_flt(fabsf(1.00000001f), 1.00000001f);
    ok_eq_flt(fabsf(1000.0000001f), 1000.0000001f);
    ok_eq_flt(fabsf(FLT_MAX), FLT_MAX);
    ok_eq_flt(fabsf(FLT_MAX + FLT_TRUE_MIN), FLT_MAX + FLT_TRUE_MIN);
    ok_eq_flt(fabsf(FLT_MAX + FLT_MIN), FLT_MAX + FLT_MIN);
}

void Test_floor()
{
    /* Special values */
    ok_eq_dbl_u64(floor(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(floor(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF0000000000000ull); // -INF -> -INF
    ok_eq_dbl_u64(floor(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(floor(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(floor(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

    ok_eq_dbl(floor(-DBL_MAX), -DBL_MAX);
    ok_eq_dbl(floor(-1000.0000001), -1001.);
    ok_eq_dbl(floor(-1.00000001), -2.);
    ok_eq_dbl(floor(-1. - DBL_MIN), -1.);
    ok_eq_dbl(floor(-1. + DBL_MIN), -1.);
    ok_eq_dbl(floor(-DBL_MIN), -1.);
    ok_eq_dbl(floor(-DBL_TRUE_MIN), -1.);
    ok_eq_dbl(floor(-0.), -0.);
    ok_eq_dbl(floor(0.), 0.);
    ok_eq_dbl(floor(DBL_TRUE_MIN), 0.);
    ok_eq_dbl(floor(DBL_MIN), 0.);
    ok_eq_dbl(floor(1. + DBL_TRUE_MIN), 1.);
    ok_eq_dbl(floor(1. + DBL_MIN), 1.);
    ok_eq_dbl(floor(1. + DBL_EPSILON / 2), 1.);
    ok_eq_dbl(floor(1. + DBL_EPSILON), 1.);
    ok_eq_dbl(floor(1.00000001), 1.);
    ok_eq_dbl(floor(1000.0000001), 1000.);
    ok_eq_dbl(floor(DBL_MAX), DBL_MAX);
    ok_eq_dbl(floor(DBL_MAX + DBL_TRUE_MIN), DBL_MAX);
    ok_eq_dbl(floor(DBL_MAX + DBL_MIN), DBL_MAX);
}

void Test_floorf()
{
    /* Special values */
    ok_eq_flt_u32(floorf(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF
    ok_eq_flt_u32(floorf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0xFF800000)), 0xFF800000); // -INF -> -INF
    ok_eq_flt_u32(floorf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(floorf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

    ok_eq_flt(floorf(-FLT_MAX), -FLT_MAX);
    ok_eq_flt(floorf(-1000.0000001f), -1000.f);
    ok_eq_flt(floorf(-1.00000001f), -1.f);
    ok_eq_flt(floorf(-1.f - FLT_MIN), -1.f);
    ok_eq_flt(floorf(-1.f + FLT_MIN), -1.f);
    ok_eq_flt(floorf(-FLT_MIN), -1.f);
    ok_eq_flt(floorf(-FLT_TRUE_MIN), -1.f);
    ok_eq_flt(floorf(-0.f), -0.f);
    ok_eq_flt(floorf(0.f), 0.f);
    ok_eq_flt(floorf(FLT_TRUE_MIN), 0.f);
    ok_eq_flt(floorf(FLT_MIN), 0.f);
    ok_eq_flt(floorf(1.f + FLT_TRUE_MIN), 1.f);
    ok_eq_flt(floorf(1.f + FLT_MIN), 1.f);
    ok_eq_flt(floorf(1.f + FLT_EPSILON / 2), 1.f);
    ok_eq_flt(floorf(1.f + FLT_EPSILON), 1.f);
    ok_eq_flt(floorf(1.0000000596f), 1.f);
    ok_eq_flt(floorf(1.0000000597f), 1.f);
    ok_eq_flt(floorf(1.00000001f), 1.f);
    ok_eq_flt(floorf(1000.0000305f), 1000.f);
    ok_eq_flt(floorf(1000.0000306f), 1000.f);
    ok_eq_flt(floorf(FLT_MAX), FLT_MAX);
    ok_eq_flt(floorf(FLT_MAX + FLT_TRUE_MIN), FLT_MAX);
    ok_eq_flt(floorf(FLT_MAX + FLT_MIN), FLT_MAX);
}

void Test_ldexp()
{
#if 0
    /* Special values */
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(ldexp(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN
#endif
}

void Test_log()
{
    /* Special values */
    ok_eq_dbl_u64(log(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(log(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(log(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(log(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(log(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

}

void Test_logf()
{
    /* Special values */
    ok_eq_flt_u32(logf(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF
    ok_eq_flt_u32(logf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(logf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(logf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(logf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(logf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(logf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(logf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(logf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(logf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(logf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(logf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

}

void Test_log10()
{
    /* Special values */
    ok_eq_dbl_u64(log10(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(log10(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(log10(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(log10(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(log10(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

}

void Test_log10f()
{
    /* Special values */
    ok_eq_flt_u32(log10f(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF
    ok_eq_flt_u32(log10f(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(log10f(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(log10f(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

}

void Test_pow()
{
#if 0
    /* Special values */
    ok_eq_dbl_u64(pow(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(pow(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(pow(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(pow(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(pow(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN
#endif
}

void Test_powf()
{
#if 0
    /* Special values */
    ok_eq_flt_u32(powf(u32_to_flt(0x7F800000)), 0xFFC00000); // INF -> -NAN(IND)
    ok_eq_flt_u32(powf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(powf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(powf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(powf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(powf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(powf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(powf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(powf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(powf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(powf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(powf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN
#endif
}

void Test_sin()
{
    /* Special values */
    ok_eq_dbl_u64(sin(u64_to_dbl(0x7FF0000000000000ull)), 0xFFF8000000000000ull); // INF -> -NAN(IND)
    ok_eq_dbl_u64(sin(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(sin(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(sin(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(sin(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN

}

void Test_sinf()
{
    /* Special values */
    ok_eq_flt_u32(sinf(u32_to_flt(0x7F800000)), 0xFFC00000); // INF -> -NAN(IND)
    ok_eq_flt_u32(sinf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(sinf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(sinf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

}

void Test_sqrt()
{
    const double test_constants[] = {
        M_PI, 1., 2., 1.0000001, 0.0000001, 10000.00001, 123.456789
    };
    int i;

    /* Special values */
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0x7FF0000000000000ull)), 0x7FF0000000000000ull); // INF -> INF
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(sqrt(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN
    //fprintf(stderr, "%f", u64_to_dbl(0xFFF8000000000000ull));

    /* Test exact matches */
    ok_eq_dbl(sqrt(0.), 0.);
    ok_eq_dbl(sqrt(1.), 1.);
    ok_eq_dbl(sqrt(4.), 2.);
    ok_eq_dbl(sqrt(4503599493152769.), 67108863.);

    /* Close matches here */
    ok_near_dbl(sqrt(0.00000000000000000004), 0.0000000002);
    ok_near_dbl(sqrt(2),       1.41421356237309504880);
    ok_near_dbl(sqrt(M_PI),    1.77245385090551590);
    ok_near_dbl(sqrt(DBL_MAX), 1.34078079299425960e+154);
    ok_near_dbl(sqrt(DBL_MIN), 1.49166814624004130e-154);
    ok_near_dbl(sqrt(DBL_MIN / 2), 1.05476866148629989527e-154);
    ok_near_dbl(sqrt(DBL_TRUE_MIN), 2.22275874948507750e-162);



    for (i = 0; i < sizeof(test_constants) / sizeof(test_constants[0]); i++)
    {
        double square = test_constants[i] * test_constants[i];
        ok_eq_dbl(sqrt(square), test_constants[i]);
    }
}

void Test_sqrtf()
{
    /* Special values */
    ok_eq_flt_u32(sqrtf(u32_to_flt(0x7F800000)), 0x7F800000); // INF -> INF
    ok_eq_flt_u32(sqrtf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(sqrtf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(sqrtf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

}

void Test_tan()
{
    /* Special values */
    ok_eq_dbl_u64(tan(u64_to_dbl(0x7FF0000000000000ull)), 0xFFF8000000000000ull); // INF -> -NAN(IND)
    ok_eq_dbl_u64(tan(u64_to_dbl(0x7FF0000000000001ull)), 0x7FF8000000000001ull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0x7FF7FFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN(SNAN) -> NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0x7FF8000000000000ull)), 0x7FF8000000000000ull); // NAN -> NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0x7FF8000000000001ull)), 0x7FF8000000000001ull); // NAN -> NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0x7FFFFFFFFFFFFFFFull)), 0x7FFFFFFFFFFFFFFFull); // NAN -> NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0xFFF0000000000000ull)), 0xFFF8000000000000ull); // -INF -> -NAN(IND)
    ok_eq_dbl_u64(tan(u64_to_dbl(0xFFF0000000000001ull)), 0xFFF8000000000001ull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0xFFF7FFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN(SNAN) -> -NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0xFFF8000000000000ull)), 0xFFF8000000000000ull); // -NAN(IND) -> -NAN(IND)
    ok_eq_dbl_u64(tan(u64_to_dbl(0xFFF8000000000001ull)), 0xFFF8000000000001ull); // -NAN -> -NAN
    ok_eq_dbl_u64(tan(u64_to_dbl(0xFFFFFFFFFFFFFFFFull)), 0xFFFFFFFFFFFFFFFFull); // -NAN -> -NAN


}

void Test_tanf()
{
    /* Special values */
    ok_eq_flt_u32(tanf(u32_to_flt(0x7F800000)), 0xFFC00000); // INF -> -NAN(IND)
    ok_eq_flt_u32(tanf(u32_to_flt(0x7F800001)), 0x7FC00001); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0x7FBFFFFF)), 0x7FFFFFFF); // NAN(SNAN) -> NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0x7FC00000)), 0x7FC00000); // NAN -> NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0x7FC00001)), 0x7FC00001); // NAN -> NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0x7FCFFFFF)), 0x7FCFFFFF); // NAN -> NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0xFF800000)), 0xFFC00000); // -INF -> -NAN(IND)
    ok_eq_flt_u32(tanf(u32_to_flt(0xFF800001)), 0xFFC00001); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0xFFBFFFFF)), 0xFFFFFFFF); // -NAN(SNAN) -> -NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0xFFC00000)), 0xFFC00000); // -NAN(IND) -> -NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0xFFC00001)), 0xFFC00001); // -NAN -> -NAN
    ok_eq_flt_u32(tanf(u32_to_flt(0xFFCFFFFF)), 0xFFCFFFFF); // -NAN -> -NAN

}

// shamelessly stolen from https://github.com/mstorsjo/llvm-mingw/blob/f061215ebf5a2871a5e1939a397f1cb101f51026/test/crt-test.c
void Test_divmod()
{
    //...
}
#endif


START_TEST(math_functions)
{
#ifdef _M_IX86
    Test__ftol();
#endif
#if 0
    Test_abs();
    Test_acos();
#if 0
    Test_acosf();
    Test_asin();
    Test_asinf();
    Test_atan();
    Test_atanf();
    Test_atan2();
#endif
    Test_ceil();
    Test_ceilf();
#if 0
    Test_cos();
    Test_cosf();
    Test_exp();
    Test_expf();
#endif
    Test_fabs();
    Test_fabsf();
#if 0
    Test_floor();
    Test_floorf();
#endif
#if 0
    Test_ldexp();
    Test_log();
    Test_logf();
    Test_log10();
    Test_log10f();
    Test_pow();
    Test_powf();
    Test_sin();
    Test_sinf();
#endif
    Test_sqrt();
#if 0
    Test_sqrtf();
    Test_tan();
    Test_tanf();
#endif
}
