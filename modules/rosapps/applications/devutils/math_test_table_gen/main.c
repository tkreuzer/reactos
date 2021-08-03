
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <MathLib.h>

#ifdef _MSC_VER
#pragma function(floor)
#ifdef _M_AMD64
#pragma function(floorf)
#endif
#endif

static unsigned long long s_special_values_u64[] =
{
    /* Special values */
    0x0000000000000000ull /* 0.0        */,
    0x8000000000000000ull /* -0.0       */,
    0x7FF0000000000000ull /* INF        */,
    0x7FF0000000000001ull /* NAN(SNAN)  */,
    0x7FF7FFFFFFFFFFFFull /* NAN(SNAN)  */,
    0x7FF8000000000000ull /* NAN        */,
    0x7FF8000000000001ull /* NAN        */,
    0x7FFFFFFFFFFFFFFFull /* NAN        */,
    0xFFF0000000000000ull /* -INF       */,
    0xFFF0000000000001ull /* -NAN(SNAN) */,
    0xFFF7FFFFFFFFFFFFull /* -NAN(SNAN) */,
    0xFFF8000000000000ull /* -NAN(IND)  */,
    0xFFF8000000000001ull /* -NAN       */,
    0xFFFFFFFFFFFFFFFFull /* -NAN       */,
};

static unsigned long long s_special_values_u32[] =
{
    /* Special values */
    0x00000000 /* 0.0        */,
    0x80000000 /* -0.0       */,
    0x7F800000 /* INF        */,
    0x7F800001 /* NAN(SNAN)  */,
    0x7FBFFFFF /* NAN(SNAN)  */,
    0x7FC00000 /* NAN        */,
    0x7FC00001 /* NAN        */,
    0x7FFFFFFF /* NAN        */,
    0xFF800000 /* -INF       */,
    0xFF800001 /* -NAN(SNAN) */,
    0xFFBFFFFF /* -NAN(SNAN) */,
    0xFFC00000 /* -NAN(IND)  */,
    0xFFC00001 /* -NAN       */,
    0xFFFFFFFF /* -NAN       */,
};

typedef double (*func_dbl_1arg_t)(double);
typedef float (*func_flt_1arg_t)(float);

void
print_line(double x, double z)
{
    printf("    { 0x%016llx /* %.15e */, 0x%016llx /* %.15e */ }\n",
        *(long long*)&x,
        x,
        *(long long *)&z,
        z);
}

void
print_line_u64(unsigned long long x, unsigned long long z)
{
    printf("    { 0x%016llx /* %.15e */, 0x%016llx /* %.15e */ },\n",
           x,
           *(double*)&x,
           z,
           *(double*)&z);
}

void
print_line_u32(unsigned int x, unsigned int z)
{
    printf("    { 0x%08x /* %.6e */, 0x%08x /* %.6e */ },\n",
           x,
           *(float*)&x,
           z,
           *(float*)&z);
}

void
Gen_special_values_u64(func_dbl_1arg_t func)
{
    for (int i = 0; i < _countof(s_special_values_u64); i++)
    {
        double x = *(double*)&s_special_values_u64[i];
        double z = func(x);
        print_line_u64(s_special_values_u64[i],
                       *(unsigned long long*)&z);
    }
}

void
Gen_special_values_u32(func_flt_1arg_t func)
{
    for (int i = 0; i < _countof(s_special_values_u64); i++)
    {
        float x = *(float*)&s_special_values_u64[i];
        float z = func(x);
        print_line_u32(s_special_values_u64[i],
                       *(unsigned int*)&z);
    }
}

unsigned int
Rnd32()
{
    unsigned int x;
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;
    return x;
}

unsigned int
Get_Random_u32(void)
{
    unsigned int x;
    do
    {
        x = (unsigned int)Rnd32();
    } while ((x & 0x7F800000) == 0x7F800000);
    return x;
}

unsigned long long
Get_Random_u64(void)
{
    unsigned long long x;
    do
    {
        x = ((unsigned long long)Rnd32() << 32) | Rnd32();
    } while ((x & 0x7FF0000000000000ull) == 0x7FF0000000000000ull);
    return x;
}

void
Gen_Random_u64(func_dbl_1arg_t func, int count)
{
    for (int i = 0; i < count; i++)
    {
        unsigned long long ullx = Get_Random_u64();
        double x = *(double*)&ullx;
        double z = func(x);
        print_line_u64(ullx, *(unsigned long long*)&z);
    }
}

void
Gen_Random_u32(func_flt_1arg_t func, int count)
{
    for (int i = 0; i < count; i++)
    {
        unsigned int ux = Get_Random_u32();
        float x = *(float*)&ux;
        float z = func(x);
        print_line_u32(ux, *(unsigned int*)&z);
    }
}

void
Gen_Range(func_dbl_1arg_t func, double start, double end, unsigned int count)
{
    double delta = (end - start) / count;
    double x, z;
    unsigned i;

    for (i = 0; i < count; i++)
    {
        x = start + (i * delta);
        z = func(x);
        print_line(x, z);
#if 0
        double rz = cos(x);
        double err = rz - z;
        if (err != 0.)
        {
            double rel_err = (z != 0) ? err / z : err;
            double ulp = rel_err / DBL_EPSILON;
            printf("fail: cos(x) = %e, (err=%e, rel_err=%e, ulp=%.2f)\n", rz, err, rel_err, ulp);
        }
#endif
    }
}

void
Gen_exact_dbl(func_dbl_1arg_t func)
{
    Gen_special_values_u64(func);
    Gen_Random_u64(func, 10);
}

void
Gen_exact_flt(func_flt_1arg_t func)
{
    Gen_special_values_u32(func);
    Gen_Random_u32(func, 10);
}

void
Gen_ceil(void)
{
    srand('ceil');
    printf("struct{unsigned long long x; unsigned long long y;} ceil_table[] = \n{\n");
    Gen_exact_dbl(ceil);
    printf("}\n\n");
}

void
Gen_ceilf(void)
{
    srand('ceil');
    printf("struct { unsigned int x; unsigned int y; } ceilf_table[] =\n{\n");
    Gen_exact_flt(ceilf);
    printf("}\n\n");
}

void
Gen_cos(void)
{
    printf("struct { unsigned long long x; unsigned long long y; } cos_table[] =\n{\n");

    /* 2 values from 0 to DBL_MIN */
    Gen_Range(ucos, 0., 0., 1);
    Gen_Range(ucos, DBL_MIN, DBL_MIN, 1);
    Gen_Range(ucos, DBL_EPSILON, DBL_EPSILON, 1);

    /* 7 values from DBL_MIN to DBL_EPSILON */
    Gen_Range(ucos, 1E-8, 1E-7, 7);

    /* 97 values from 0 to 0.5 pi */
    Gen_Range(ucos, 2E-7, M_PI_2, 97);

    /* 53 values from 0.5 pi to pi */
    Gen_Range(ucos, M_PI_2, M_PI, 53);

    /* 37 values from pi to 1.5  pi */
    Gen_Range(ucos, M_PI, 1.5 * M_PI, 37);

    /* 13 values from 1.5  pi to 2 pi */
    Gen_Range(ucos, 1.5 * M_PI, 2 * M_PI, 13);

    /* 13 values from 2 pi to 100 */
    Gen_Range(ucos, 2 * M_PI, 100., 13);

    printf("}\n\n");
}

void
Gen_fabs(void)
{
    srand('fabs');
    printf("struct { unsigned long long x; unsigned long long y; } fabs_table[] =\n{\n");
    Gen_exact_dbl(fabs);
    printf("}\n\n");
}

void
Gen_fabsf(void)
{
    srand('fabs');
    printf("struct { unsigned int x; unsigned int y; } fabsf_table[] =\n{\n");
    Gen_exact_flt(fabsf);
    printf("}\n\n");
}

void
Gen_floor(void)
{
    srand('floo');
    printf("struct { unsigned long long x; unsigned long long y; } floor_table[] =\n{\n");
    Gen_exact_dbl(floor);
    printf("}\n\n");
}

void
Gen_floorf(void)
{
    srand('floo');
    printf("struct { unsigned int x; unsigned int y; } floorf_table[] =\n{\n");
    Gen_exact_flt(floorf);
    printf("}\n\n");
}

int main(int argc, const char* argv[])
{
    Gen_ceil();
    Gen_ceilf();
    //Gen_cos();
    //Gen_fabs();
    //Gen_fabsf();
    Gen_floor();
    Gen_floorf();
     return 0;
}

