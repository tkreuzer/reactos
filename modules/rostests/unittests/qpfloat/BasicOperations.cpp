/*
 * PROJECT:     ReactOS Unit Tests
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later)
 * PURPOSE:     Unit Tests for QPFloat library
 * COPYRIGHT:   Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#define _USE_MATH_DEFINES
#include <apitest.h>
#include <__float128.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <exception>

void Test_Compare(void)
{
    ok(__float128(0.) == __float128(0.), "");
    ok(__float128(-0.) == __float128(0.), "");
    ok(-__float128(0.) == __float128(0.), "");
    ok(__float128(1.) > __float128(0.), "");
    ok(__float128(-1.) < __float128(0.), "");
    ok(-__float128(1.) == __float128(-1.), "");
    ok(__float128(DBL_MIN) > __float128(DBL_TRUE_MIN), "");
    ok(__float128(DBL_TRUE_MIN) > __float128(0.), "");
    ok(__float128(DBL_TRUE_MIN) / __float128(1000.) > __float128(0.), "");
}

void Test_Add(void)
{
    ok(__float128(1.) + __float128(2.) == __float128(3.), "");
    ok(__float128(1000.) + __float128(DBL_EPSILON) > __float128(1000.), "");
    ok(__float128(1.) + (__float128(DBL_EPSILON) / __float128(65536.)) > __float128(1.), "");

    ok(__float128(1.) + __float128(1.93E-34) > __float128(1.), "");
    ok(__float128(1.) + __float128(1.92E-34) == __float128(1.), "");

}

void Test_MulDiv(void)
{
    ok(__float128(0.) * __float128(0.) == __float128(0.), "");
    ok(__float128(1.) * __float128(0.) == __float128(0.), "");
    ok(__float128(-1.) * __float128(0.) == __float128(0.), "");
    ok(__float128(0.) * __float128(123.) == __float128(0.), "");
    ok(__float128(1.) * __float128(1.) == __float128(1.), "");
    ok(__float128(-1.) * __float128(1.) == -__float128(1.), "");

    //ok(__float128(1.E5) * __float128(1.E-5) == __float128(1.), "result: %e\n", __float128::ToDouble((__float128(1.E5) * __float128(1.E-5))));
    ok(__float128(1.E10) * __float128(1.E10) == __float128(1.E20), "");

    ok(__float128(2.) * (__float128(DBL_MIN) / __float128(2.)) == __float128(DBL_MIN), "");
    ok(__float128(2.) * (__float128(DBL_TRUE_MIN) / __float128(2.)) == __float128(DBL_TRUE_MIN), "");
}

void print_flt128(__float128 &x)
{
    double dbl;
    __float128::ToDouble(x, dbl);
    printf("%e", dbl);
}

__float128
pownq(__float128 x, uint32_t n)
{
    __float128 result = 1.;
    for (uint32_t i = 0; i < n; i++)
    {
        result = result * x;
    }

    return result;
}

// faster, but less accurate
__float128
pownq2(__float128 x, uint32_t exp)
{
    if ((x == 0) && (exp < 0))
    {
        throw exception("negative exponent for zero");
    }

    if (exp == 0)
        return 1;

    bool positive = true;
    if (exp < 0)
    {
        positive = false;
        exp *= -1;
    }

    __float128 result = 1.;
    while (exp >= 1)
    {
        if (exp % 2 != 0)
        {
            result = result * x;
        }
        x = x * x;
        exp >>= 1;
    }

    return positive ? result : __float128(1.) / result;
}

__float128
facultyq(uint32_t n)
{
    __float128 result = 1.;
    for (uint32_t i = n; i > 1; i--)
    {
        result = result * __float128((double)i);
    }

    return result;
}

__float128
cosq(__float128 &x)
{
    __float128 result = 0.;
    for (uint32_t i = 0; i < 500; i++)
    {
        __float128 old = result;
        __float128 term = pownq(x, 2 * i) / facultyq(2 * i);
        if (i & 1) __float128::Negate(term);
        result = result + term;
        if (result == old) break;
    }

    return result;
}

__float128
sinq(__float128 &x)
{
    __float128 result = 0.;
    for (uint32_t i = 0; i < 500; i++)
    {
        __float128 old = result;
        __float128 term = pownq(x, 2 * i + 1) / facultyq(2 * i + 1);
        if (i & 1) __float128::Negate(term);
        result = result + term;
        if (result == old) break;
    }

    return result;
}

#define SINCOS_COUNT 313
void Test_sincos()
{
    __float128 delta = __float128(2. * M_PI) / __float128(SINCOS_COUNT);
    __float128 maxerr = 0.;
    __float128 errorsqare = 0.;

    uint64_t startTime = __rdtsc();

    for (uint32_t i = 0; i < SINCOS_COUNT; i++)
    {
        __float128 x = delta * __float128((double)i);
        __float128 cos_x = cosq(x);
        __float128 sin_x = sinq(x);
        __float128 one = cos_x * cos_x + sin_x * sin_x;
        __float128 err = one - __float128(1.0);
#if 0
        printf("x = "); print_flt128(x); printf(" / ");
        printf("sin(x) = "); print_flt128(sin_x); printf(" / ");
        printf("cos(x) = "); print_flt128(cos_x); printf(" / ");
        printf("one = "); print_flt128(one); printf(" / ");
        printf("err = "); print_flt128(err); printf("\n");
#endif
        if (err < __float128(0.)) err = -err;
        if (err > maxerr) maxerr = err;
        errorsqare = errorsqare + err * err;

    }

    uint64_t endTime = __rdtsc();


    double dbl_maxerr;
    __float128::ToDouble(maxerr, dbl_maxerr);
    printf("maxerr = %e\n", dbl_maxerr);

    double dbl_errorsqare;
    __float128::ToDouble(errorsqare, dbl_errorsqare);
    printf("errorsqare = %e\n", dbl_errorsqare);

    printf("time = %llu\n", endTime - startTime);

    ok(__float128::Cos(__float128(0.)) == __float128(1.), "\n");

}

START_TEST(BasicOperations)
{
    Test_Compare();
    Test_Add();
    Test_MulDiv();
    Test_sincos();
}
