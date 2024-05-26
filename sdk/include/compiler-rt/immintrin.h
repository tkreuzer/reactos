
#pragma once

//#include <wmmintrin.h>
#include <emmintrin.h>

typedef union _DECLSPEC_INTRIN_TYPE  _CRT_ALIGN(32) __m256i
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

#ifdef __cplusplus
extern "C" {
#endif

extern void __cdecl _mm256_zeroupper(void);
extern __m256i __cdecl _mm256_setzero_si256(void);
extern int __cdecl _mm256_movemask_epi8(__m256i);
extern __m256i __cdecl _mm256_cmpeq_epi8(__m256i, __m256i);
extern __m256i __cdecl _mm256_cmpeq_epi16(__m256i, __m256i);


#ifdef __cplusplus
} // extern "C"
#endif
