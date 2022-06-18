#include <fpieee.h>
#include <excpt.h>
#include <float.h>
#include <math.h>
#include <errno.h>

#include "libm_new.h"

#define FN_PROTOTYPE(x) x

static const unsigned __int64 L_piby4 = 0x3FE921FB54442D18ull;
static const unsigned __int64 L_two_to_neg_13 = 0x3F20000000000000ull;
static const unsigned __int64 L_two_to_neg_27 = 0x3E40000000000000ull;

//L_one           xmmword 3FF00000000000003FF0000000000000h
static const UT64 L_one = { .f64 = 1. };
static const UT64 L_int_one = { .u64 = 1 };

const UT64 __declspec(align(16)) _Lcosarray[] =
{
    { .u64 = 0x03fa5555555555555ull }, //                          ; 0.0416667           c1
#if 0
            DQ    0
            DQ    0bf56c16c16c16967h                          ; -0.00138889         c2
            DQ    0
            DQ    03EFA01A019F4EC91h                          ; 2.48016e-005        c3
            DQ    0
            DQ    0bE927E4FA17F667Bh                          ; -2.75573e-007       c4
            DQ    0
            DQ    03E21EEB690382EECh                          ; 2.08761e-009        c5
            DQ    0
            DQ    0bDA907DB47258AA7h                          ; -1.13826e-011       c6
            DQ    0
#endif
};


double FN_PROTOTYPE(cos)(double x)
{
    UT64 xm;
    unsigned __int64 aux;

    xm.f64 = x;
    aux = xm.u64 & ~SIGN_MASK_64;

    if (aux < L_piby4)
    {
        if (aux < L_two_to_neg_13)
        {
            if (aux < L_two_to_neg_27)
                return L_one.f64 + L_int_one.f64;
            else
                return L_one.f64 - x * x * 0.5;
        }
        else
        {
            double x_to_4 = x * x * x * x;
            return L_one.f64
                - (x * x * -0.5 + L_one.f64)
                + x * x * -0.5
                + (_Lcosarray[2].f64 * (x * x) + _Lcosarray[0].f64) * x_to_4
                + (_Lcosarray[6].f64 * (x * x) + _Lcosarray[4].f64) * (x_to_4 * x_to_4)
                + x_to_4 * (x_to_4 * x_to_4) * (_Lcosarray[10].f64 * (x * x) + _Lcosarray[8].f64)
                + x * x * -0.5
                + L_one.f64;
        }
    }

    x = aux.f64;

    if (v2 < L_small_arg_cw)
    {
#if 0
        v3.m128d_f64[1] = 0.0;
        v3.m128d_f64[0] = *(double *)&v2 * 0.6366197723675814 + 0.5;
        v4 = _mm_cvttpd_epi32(v3);
        v5 = _mm_cvtepi32_pd(v4).m128d_f64[0];
        v6 = *(double *)&v2 - 1.570796326734126 * v5;
        v7 = 6.077100506506192e-11 * v5;
        v8 = _mm_cvtsi128_si32(v4);
        X = v6 - 6.077100506506192e-11 * v5;
        if ( (__int64)((v2 >> 52) - ((unsigned __int64)(2i64 * *(_QWORD *)&X) >> 53)) > 15 )
        {
            v6 = v6 - 6.077100506303966e-11 * v5;
            v7 = 2.022266248795951e-21 * v5 - (*(double *)&v2 - 1.570796326734126 * v5 - v6 - 6.077100506303966e-11 * v5);
            X = v6 - v7;
        }
        v9 = v6 - X - v7;
#endif
    }
    else if (v2 < L__inf_mask_64)
    {
        v8 = _remainder_piby2_forAsm();
        v9 = *(double *)&_XMM1;
    }
    else
    {
        cos_special();
        return X;
    }

    v10 = X * X;
    if ( (v8 & 1) != 0 )
    {
        X = v9
            + X
            * v10
            * (((_Lsinarray[10] * v10 + _Lsinarray[8]) * v10 + _Lsinarray[6]) * (v10 * v10 * v10)
            + (_Lsinarray[4] * v10 + _Lsinarray[2]) * v10
            + _Lsinarray[0])
            - v10 * 0.5 * v9
            + X;
    }
    else
    {
        X = ((_Lcosarray[4] * v10 + _Lcosarray[2]) * v10
            + _Lcosarray[0]
            + ((_Lcosarray[10] * v10 + _Lcosarray[8]) * v10 + _Lcosarray[6]) * (v10 * v10 * v10))
            * (v10
            * v10)
            + 0.5 * v10
            - *(double *)&L_one
            + *(double *)&L_one
            - v10 * 0.5
            - v9 * X
            - (v10 * 0.5
            - *(double *)&L_one);
    }

    if ( ((v8 + 1) & 2) != 0 )
        return 0.0 - X;

    return X;

#endif

    return 0.;
}
