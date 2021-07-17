#ifndef _LIBM_H
#define _LIBM_H

/* Support non-nearest rounding mode.  */
#define WANT_ROUNDING 1

#define issignaling_inline(x) 0

/* Helps static branch prediction so hot path can be better optimized.  */
#ifdef __GNUC__
#define predict_true(x) __builtin_expect(!!(x), 1)
#define predict_false(x) __builtin_expect(x, 0)
#else
#define predict_true(x) (x)
#define predict_false(x) (x)
#endif

static inline double eval_as_double(double x)
{
    double y = x;
    return y;
}

static inline double fp_barrier(double x)
{
    volatile double y = x;
    return y;
}

static inline void fp_force_eval(double x)
{
    volatile double y;
    y = x;
}

static __inline uint32_t asuint(float f) { union { float _f; uint32_t _i; } u; u._f = f; return u._i; }
static __inline float asfloat(uint32_t i) { union { float _f; uint32_t _i; } u; u._i = i; return u._f; }
static __inline uint64_t asuint64(float f) { union { double _f; uint64_t _i; } u; u._f = f; return u._i; }
static __inline double asdouble(uint32_t i) { union { double _f; uint64_t _i; } u; u._i = i; return u._f; }

/* error handling functions */
static inline double __math_divzero(uint32_t i) { return 0.; }
static inline double __math_invalid(double f) { return 0.; }
static inline double __math_oflow(uint32_t i) { return 0.; }
static inline double __math_uflow(uint32_t i) { return 0.; }

#endif
