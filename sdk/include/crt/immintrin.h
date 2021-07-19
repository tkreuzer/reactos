
#pragma once

#include <wmmintrin.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef _MSC_VER

typedef union __declspec(intrin_type) __declspec(align(32)) __m256
{
    float m256_f32[8];
} __m256;

typedef struct __declspec(intrin_type) __declspec(align(32)) __m256d
{
    double m256d_f64[4];
} __m256d;

typedef union  __declspec(intrin_type) __declspec(align(32)) __m256i
{
    __int8              m256i_i8[32];
    __int16             m256i_i16[16];
    __int32             m256i_i32[8];
    __int64             m256i_i64[4];
    unsigned __int8     m256i_u8[32];
    unsigned __int16    m256i_u16[16];
    unsigned __int32    m256i_u32[8];
    unsigned __int64    m256i_u64[4];
} __m256i;

#else

typedef float __m256 __attribute__ ((__vector_size__ (32), __may_alias__));

typedef double __m256d __attribute__ ((__vector_size__ (32), __may_alias__));

typedef long long __m256i __attribute__ ((__vector_size__ (32), __may_alias__));

#endif

#if defined __cplusplus
}; /* End "C" */
#endif  /* defined __cplusplus */

#include <zmmintrin.h>
