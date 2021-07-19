
#pragma once

#ifndef _ZMMINTRIN_H_INCLUDED
#define _ZMMINTRIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char       __mmask8;
typedef unsigned short      __mmask16;
typedef unsigned int        __mmask32;
typedef unsigned __int64    __mmask64;

#ifdef _MSC_VER

typedef union __declspec(intrin_type) __declspec(align(64)) __m512
{
    float m512_f32[16];
} __m512;

typedef struct __declspec(intrin_type) __declspec(align(64)) __m512d
{
    double m512d_f64[8];
} __m512d;

typedef union  __declspec(intrin_type) __declspec(align(64)) __m512i
{
    __int8 m512i_i8[64];
    __int16 m512i_i16[32];
    __int32 m512i_i32[16];
    __int64 m512i_i64[8];
    unsigned __int8 m512i_u8[64];
    unsigned __int16 m512i_u16[32];
    unsigned __int32 m512i_u32[16];
    unsigned __int64 m512i_u64[8];
} __m512i;

#else

typedef float __m512 __attribute__ ((__vector_size__ (64), __may_alias__));

typedef double __m512d __attribute__ ((__vector_size__ (64), __may_alias__));

typedef long long __m512i __attribute__ ((__vector_size__ (64), __may_alias__));

#endif

#ifdef __cplusplus
}
#endif

#endif // _ZMMINTRIN_H_INCLUDED
