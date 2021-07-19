
#pragma once

#ifndef _INCLUDED_NMM
#define _INCLUDED_NMM

#include <smmintrin.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _SIDD_UBYTE_OPS                0x00
#define _SIDD_UWORD_OPS                0x01
#define _SIDD_SBYTE_OPS                0x02
#define _SIDD_SWORD_OPS                0x03

#define _SIDD_CMP_EQUAL_ANY            0x00
#define _SIDD_CMP_RANGES               0x04
#define _SIDD_CMP_EQUAL_EACH           0x08
#define _SIDD_CMP_EQUAL_ORDERED        0x0C

#define _SIDD_POSITIVE_POLARITY        0x00
#define _SIDD_NEGATIVE_POLARITY        0x10
#define _SIDD_MASKED_POSITIVE_POLARITY 0x20
#define _SIDD_MASKED_NEGATIVE_POLARITY 0x30

#define _SIDD_LEAST_SIGNIFICANT        0x00
#define _SIDD_MOST_SIGNIFICANT         0x40

#define _SIDD_BIT_MASK                 0x00
#define _SIDD_UNIT_MASK                0x40

__m128i _mm_cmpistrm (__m128i a, __m128i b, const int mode);
int _mm_cmpistri (__m128i a, __m128i b, const int mode);
__m128i _mm_cmpestrm (__m128i a, int la, __m128i b, int lb, const int mode);
extern int _mm_cmpestri (__m128i a, int la, __m128i b, int lb, const int mode);
int _mm_cmpistrz (__m128i a, __m128i b, const int mode);
int _mm_cmpistrc (__m128i a, __m128i b, const int mode);
int _mm_cmpistrs (__m128i a, __m128i b, const int mode);
int _mm_cmpistro (__m128i a, __m128i b, const int mode);
int _mm_cmpistra (__m128i a, __m128i b, const int mode);
int _mm_cmpestrz (__m128i a, int la, __m128i b, int lb, const int mode);
int _mm_cmpestrc (__m128i a, int la, __m128i b, int lb, const int mode);
int _mm_cmpestrs (__m128i a, int la, __m128i b, int lb, const int mode);
int _mm_cmpestro (__m128i a, int la, __m128i b, int lb, const int mode);
int _mm_cmpestra (__m128i a, int la, __m128i b, int lb, const int mode);
__m128i _mm_cmpgt_epi64(__m128i val1, __m128i val2);
int _mm_popcnt_u32(unsigned int v);
unsigned int _mm_crc32_u8 (unsigned int crc, unsigned char v);
unsigned int _mm_crc32_u16(unsigned int crc, unsigned short v);
unsigned int _mm_crc32_u32(unsigned int crc, unsigned int v);

#ifdef _M_AMD64
__int64 _mm_popcnt_u64(unsigned __int64 v);
unsigned __int64 _mm_crc32_u64(unsigned __int64 crc, unsigned __int64 v);
#endif

#ifdef __cplusplus
};
#endif

#endif // _INCLUDED_NMM
