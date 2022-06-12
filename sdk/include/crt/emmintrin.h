/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#pragma once
#ifndef _INCLUDED_EMM
#define _INCLUDED_EMM

#include <crtdefs.h>
#include <xmmintrin.h>

#if defined(_MSC_VER) && !defined(__clang__)

typedef union _DECLSPEC_INTRIN_TYPE _CRT_ALIGN(16) __m128i
{
    __int8  m128i_i8[16];
    __int16 m128i_i16[8];
    __int32 m128i_i32[4];
    __int64 m128i_i64[2];
    unsigned __int8  m128i_u8[16];
    unsigned __int16 m128i_u16[8];
    unsigned __int32 m128i_u32[4];
    unsigned __int64 m128i_u64[2];
} __m128i;
_STATIC_ASSERT(sizeof(__m128i) == 16);

typedef struct _DECLSPEC_INTRIN_TYPE _CRT_ALIGN(16) __m128d
{
    double m128d_f64[2];
} __m128d;

#define aTTRIBUTE_SSE2__

#else /* _MSC_VER */

typedef double __m128d attribute__((__vector_size__(16), aligned__(16)));
typedef long long __m128i attribute__((__vector_size__(16), aligned__(16)));

typedef double __m128d_u attribute__((__vector_size__(16), aligned__(1)));
typedef long long __m128i_u attribute__((__vector_size__(16), aligned__(1)));

/* Type defines.  */
typedef double __v2df attribute__((__vector_size__(16)));
typedef long long __v2di attribute__((__vector_size__(16)));
typedef short __v8hi attribute__((__vector_size__(16)));
typedef char __v16qi attribute__((__vector_size__(16)));

/* Unsigned types */
typedef unsigned long long __v2du attribute__((__vector_size__(16)));
typedef unsigned short __v8hu attribute__((__vector_size__(16)));
typedef unsigned char __v16qu attribute__((__vector_size__(16)));

/* We need an explicitly signed variant for char. Note that this shouldn't
 * appear in the interface though. */
typedef signed char __v16qs attribute__((__vector_size__(16)));

#ifdef __clang__
#define aTTRIBUTE_SSE2__ attribute__((__target__("sse2"),__min_vector_width__(128)))
#else
#define aTTRIBUTE_SSE2__ attribute__((__target__("sse2")))
#endif
#define __INTRIN_INLINE_SSE2 __INTRIN_INLINE aTTRIBUTE_SSE2__

#endif /* _MSC_VER */


extern __m128d _mm_add_sd(__m128d a, __m128d b);
extern __m128d _mm_add_pd(__m128d a, __m128d b);
extern __m128d _mm_sub_sd(__m128d a, __m128d b);
extern __m128d _mm_sub_pd(__m128d a, __m128d b);
extern __m128d _mm_mul_sd(__m128d a, __m128d b);
extern __m128d _mm_mul_pd(__m128d a, __m128d b);
extern __m128d _mm_div_sd(__m128d a, __m128d b);
extern __m128d _mm_div_pd(__m128d a, __m128d b);
extern __m128d _mm_sqrt_sd(__m128d a, __m128d b);
extern __m128d _mm_sqrt_pd(__m128d a);
extern __m128d _mm_min_sd(__m128d a, __m128d b);
extern __m128d _mm_min_pd(__m128d a, __m128d b);
extern __m128d _mm_max_sd(__m128d a, __m128d b);
extern __m128d _mm_max_pd(__m128d a, __m128d b);
extern __m128d _mm_and_pd(__m128d a, __m128d b);
extern __m128d _mm_andnot_pd(__m128d a, __m128d b);
extern __m128d _mm_or_pd(__m128d a, __m128d b);
extern __m128d _mm_xor_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpeq_pd(__m128d a, __m128d b);
extern __m128d _mm_cmplt_pd(__m128d a, __m128d b);
extern __m128d _mm_cmple_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpgt_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpge_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpord_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpunord_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpneq_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpnlt_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpnle_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpngt_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpnge_pd(__m128d a, __m128d b);
extern __m128d _mm_cmpeq_sd(__m128d a, __m128d b);
extern __m128d _mm_cmplt_sd(__m128d a, __m128d b);
extern __m128d _mm_cmple_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpgt_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpge_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpord_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpunord_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpneq_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpnlt_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpnle_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpngt_sd(__m128d a, __m128d b);
extern __m128d _mm_cmpnge_sd(__m128d a, __m128d b);
extern int _mm_comieq_sd(__m128d a, __m128d b);
extern int _mm_comilt_sd(__m128d a, __m128d b);
extern int _mm_comile_sd(__m128d a, __m128d b);
extern int _mm_comigt_sd(__m128d a, __m128d b);
extern int _mm_comige_sd(__m128d a, __m128d b);
extern int _mm_comineq_sd(__m128d a, __m128d b);
extern int _mm_ucomieq_sd(__m128d a, __m128d b);
extern int _mm_ucomilt_sd(__m128d a, __m128d b);
extern int _mm_ucomile_sd(__m128d a, __m128d b);
extern int _mm_ucomigt_sd(__m128d a, __m128d b);
extern int _mm_ucomige_sd(__m128d a, __m128d b);
extern int _mm_ucomineq_sd(__m128d a, __m128d b);
extern __m128 _mm_cvtpd_ps(__m128d a);
extern __m128d _mm_cvtps_pd(__m128 a);
extern __m128d _mm_cvtepi32_pd(__m128i a);
extern __m128i _mm_cvtpd_epi32(__m128d a);
extern int _mm_cvtsd_si32(__m128d a);
extern __m128 _mm_cvtsd_ss(__m128 a, __m128d b);
extern __m128d _mm_cvtsi32_sd(__m128d a, int b);
extern __m128d _mm_cvtss_sd(__m128d a, __m128 b);
extern __m128i _mm_cvttpd_epi32(__m128d a);
extern int _mm_cvttsd_si32(__m128d a);
extern __m64 _mm_cvtpd_pi32(__m128d a);
extern __m64 _mm_cvttpd_pi32(__m128d a);
extern __m128d _mm_cvtpi32_pd(__m64 a);
extern double _mm_cvtsd_f64(__m128d a);
extern __m128d _mm_load_pd(double const *__dp);
extern __m128d _mm_load1_pd(double const *__dp);
//#define _mm_load_pd1(dp) _mm_load1_pd(dp)
extern __m128d _mm_loadr_pd(double const *__dp);
extern __m128d _mm_loadu_pd(double const *__dp);
extern __m128i _mm_loadu_si64(void const *a);
extern __m128i _mm_loadu_si32(void const *a);
extern __m128i _mm_loadu_si16(void const *a);
extern __m128d _mm_load_sd(double const *__dp);
extern __m128d _mm_loadh_pd(__m128d a, double const *__dp);
extern __m128d _mm_loadl_pd(__m128d a, double const *__dp);
extern __m128d _mm_undefined_pd(void);
extern __m128d _mm_set_sd(double __w);
extern __m128d _mm_set1_pd(double __w);
extern __m128d _mm_set_pd1(double __w);
extern __m128d _mm_set_pd(double __w, double __x);
extern __m128d _mm_setr_pd(double __w, double __x);
extern __m128d _mm_setzero_pd(void);
extern __m128d _mm_move_sd(__m128d a, __m128d b);
extern void _mm_store_sd(double *__dp, __m128d a);
extern void _mm_store_pd(double *__dp, __m128d a);
extern void _mm_store1_pd(double *__dp, __m128d a);
extern void _mm_store_pd1(double *__dp, __m128d a);
extern void _mm_storeu_pd(double *__dp, __m128d a);
extern void _mm_storer_pd(double *__dp, __m128d a);
extern void _mm_storeh_pd(double *__dp, __m128d a);
extern void _mm_storel_pd(double *__dp, __m128d a);
extern __m128i _mm_add_epi8(__m128i a, __m128i b);
extern __m128i _mm_add_epi16(__m128i a, __m128i b);
extern __m128i _mm_add_epi32(__m128i a, __m128i b);
extern __m64 _mm_add_si64(__m64 a, __m64 b);
extern __m128i _mm_add_epi64(__m128i a, __m128i b);
extern __m128i _mm_adds_epi8(__m128i a, __m128i b);
extern __m128i _mm_adds_epi16(__m128i a, __m128i b);
extern __m128i _mm_adds_epu8(__m128i a, __m128i b);
extern __m128i _mm_adds_epu16(__m128i a, __m128i b);
extern __m128i _mm_avg_epu8(__m128i a, __m128i b);
extern __m128i _mm_avg_epu16(__m128i a, __m128i b);
extern __m128i _mm_madd_epi16(__m128i a, __m128i b);
extern __m128i _mm_max_epi16(__m128i a, __m128i b);
extern __m128i _mm_max_epu8(__m128i a, __m128i b);
extern __m128i _mm_min_epi16(__m128i a, __m128i b);
extern __m128i _mm_min_epu8(__m128i a, __m128i b);
extern __m128i _mm_mulhi_epi16(__m128i a, __m128i b);
extern __m128i _mm_mulhi_epu16(__m128i a, __m128i b);
extern __m128i _mm_mullo_epi16(__m128i a, __m128i b);
extern __m64 _mm_mul_su32(__m64 a, __m64 b);
extern __m128i _mm_mul_epu32(__m128i a, __m128i b);
extern __m128i _mm_sad_epu8(__m128i a, __m128i b);
extern __m128i _mm_sub_epi8(__m128i a, __m128i b);
extern __m128i _mm_sub_epi16(__m128i a, __m128i b);
extern __m128i _mm_sub_epi32(__m128i a, __m128i b);
extern __m64 _mm_sub_si64(__m64 a, __m64 b);
extern __m128i _mm_sub_epi64(__m128i a, __m128i b);
extern __m128i _mm_subs_epi8(__m128i a, __m128i b);
extern __m128i _mm_subs_epi16(__m128i a, __m128i b);
extern __m128i _mm_subs_epu8(__m128i a, __m128i b);
extern __m128i _mm_subs_epu16(__m128i a, __m128i b);
extern __m128i _mm_and_si128(__m128i a, __m128i b);
extern __m128i _mm_andnot_si128(__m128i a, __m128i b);
extern __m128i _mm_or_si128(__m128i a, __m128i b);
extern __m128i _mm_xor_si128(__m128i a, __m128i b);
extern __m128i _mm_slli_si128(__m128i a, int i);
//#define _mm_bslli_si128(a, ((__m128i)builtin_ia32_pslldqi128_byteshift((__v2di)(__m128i)(a), (int)(imm)))
extern __m128i _mm_slli_epi16(__m128i a, int __count);
extern __m128i _mm_sll_epi16(__m128i a, __m128i __count);
extern __m128i _mm_slli_epi32(__m128i a, int __count);
extern __m128i _mm_sll_epi32(__m128i a, __m128i __count);
extern __m128i _mm_slli_epi64(__m128i a, int __count);
extern __m128i _mm_sll_epi64(__m128i a, __m128i __count);
extern __m128i _mm_srai_epi16(__m128i a, int __count);
extern __m128i _mm_sra_epi16(__m128i a, __m128i __count);
extern __m128i _mm_srai_epi32(__m128i a, int __count);
extern __m128i _mm_sra_epi32(__m128i a, __m128i __count);
extern __m128i _mm_srli_si128(__m128i a, int imm);
//#define _mm_bsrli_si128(a, ((__m128i)builtin_ia32_psrldqi128_byteshift((__v2di)(__m128i)(a), (int)(imm)))
extern __m128i _mm_srli_epi16(__m128i a, int __count);
extern __m128i _mm_srl_epi16(__m128i a, __m128i __count);
extern __m128i _mm_srli_epi32(__m128i a, int __count);
extern __m128i _mm_srl_epi32(__m128i a, __m128i __count);
extern __m128i _mm_srli_epi64(__m128i a, int __count);
extern __m128i _mm_srl_epi64(__m128i a, __m128i __count);
extern __m128i _mm_cmpeq_epi8(__m128i a, __m128i b);
extern __m128i _mm_cmpeq_epi16(__m128i a, __m128i b);
extern __m128i _mm_cmpeq_epi32(__m128i a, __m128i b);
extern __m128i _mm_cmpgt_epi8(__m128i a, __m128i b);
extern __m128i _mm_cmpgt_epi16(__m128i a, __m128i b);
extern __m128i _mm_cmpgt_epi32(__m128i a, __m128i b);
extern __m128i _mm_cmplt_epi8(__m128i a, __m128i b);
extern __m128i _mm_cmplt_epi16(__m128i a, __m128i b);
extern __m128i _mm_cmplt_epi32(__m128i a, __m128i b);
#ifdef _M_AMD64
extern __m128d _mm_cvtsi64_sd(__m128d a, long long b);
extern long long _mm_cvtsd_si64(__m128d a);
extern long long _mm_cvttsd_si64(__m128d a);
#endif
extern __m128 _mm_cvtepi32_ps(__m128i a);
extern __m128i _mm_cvtps_epi32(__m128 a);
extern __m128i _mm_cvttps_epi32(__m128 a);
extern __m128i _mm_cvtsi32_si128(int a);
extern __m128i _mm_cvtsi64_si128(long long a);
extern int _mm_cvtsi128_si32(__m128i a);
extern long long _mm_cvtsi128_si64(__m128i a);
extern __m128i _mm_load_si128(__m128i const *__p);
//extern __m128i _mm_loadu_si128(__m128i_u const *__p);
//extern __m128i _mm_loadl_epi64(__m128i_u const *__p);
extern __m128i _mm_undefined_si128(void);
extern __m128i _mm_set_epi64x(long long q1, long long q0);
extern __m128i _mm_set_epi64(__m64 q1, __m64 q0);
//extern __m128i _mm_set_epi32(int __i3, int __i1, int __i0);
extern __m128i _mm_set_epi32(int i3, int i2, int i1, int i0);
//extern __m128i _mm_set_epi16(short __w7, short __w2, short __w1, short __w0);
extern __m128i _mm_set_epi16(short w7, short w6, short w5, short w4, short w3, short w2, short w1, short w0);
//extern __m128i _mm_set_epi8(char b15, char b10, char b4, char b3, char b2, char b1, char b0);
extern __m128i _mm_set_epi8(char b15, char b14, char b13, char b12, char b11, char b10, char b9, char b8, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0);
extern __m128i _mm_set1_epi64x(long long __q);
extern __m128i _mm_set1_epi64(__m64 __q);
extern __m128i _mm_set1_epi32(int __i);
extern __m128i _mm_set1_epi16(short __w);
extern __m128i _mm_set1_epi8(char b);
extern __m128i _mm_setr_epi64(__m64 __q0, __m64 __q1);
//extern __m128i _mm_setr_epi32(int __i0, int __i2, int __i3);
extern __m128i _mm_setr_epi32(int i0, int i1, int i2, int i3);
//extern __m128i _mm_setr_epi16(short __w0, short __w5, short __w6, short __w7);
extern __m128i _mm_setr_epi16(short w0, short w1, short w2, short w3, short w4, short w5, short w6, short w7);
//extern __m128i _mm_setr_epi8(char b0, char b6, char b11, char b12, char b13, char b14, char b15);
extern __m128i _mm_setr_epi8(char b15, char b14, char b13, char b12, char b11, char b10, char b9, char b8, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0);
extern __m128i _mm_setzero_si128(void);
extern void _mm_store_si128(__m128i *__p, __m128i b);
//extern void _mm_storeu_si128(__m128i_u *__p, __m128i b);
extern void _mm_storeu_si64(void *__p, __m128i b);
extern void _mm_storeu_si32(void *__p, __m128i b);
extern void _mm_storeu_si16(void *__p, __m128i b);
extern void _mm_maskmoveu_si128(__m128i __d, __m128i __n, char *__p);
//extern void _mm_storel_epi64(__m128i_u *__p, __m128i a);
extern void _mm_stream_pd(double *__p, __m128d a);
extern void _mm_stream_si128(__m128i *__p, __m128i a);
extern void _mm_stream_si32(int *__p, int a);
#ifdef _M_AMD64
extern void _mm_stream_si64(long long *__p, long long a);
#endif
void _mm_clflush(void const *__p);
void _mm_lfence(void);
void _mm_mfence(void);
extern __m128i _mm_packs_epi16(__m128i a, __m128i b);
extern __m128i _mm_packs_epi32(__m128i a, __m128i b);
extern __m128i _mm_packus_epi16(__m128i a, __m128i b);
extern int _mm_extract_epi16(__m128i a, int imm);
extern __m128i _mm_insert_epi16(__m128i a, int b, int imm);
extern int _mm_movemask_epi8(__m128i a);
extern __m128i _mm_shuffle_epi32(__m128i a, int imm);
extern __m128i _mm_shufflelo_epi16(__m128i a, int imm);
extern __m128i _mm_shufflehi_epi16(__m128i a, int imm);
extern __m128i _mm_unpackhi_epi8(__m128i a, __m128i b);
extern __m128i _mm_unpackhi_epi16(__m128i a, __m128i b);
extern __m128i _mm_unpackhi_epi32(__m128i a, __m128i b);
extern __m128i _mm_unpackhi_epi64(__m128i a, __m128i b);
extern __m128i _mm_unpacklo_epi8(__m128i a, __m128i b);
extern __m128i _mm_unpacklo_epi16(__m128i a, __m128i b);
extern __m128i _mm_unpacklo_epi32(__m128i a, __m128i b);
extern __m128i _mm_unpacklo_epi64(__m128i a, __m128i b);
extern __m64 _mm_movepi64_pi64(__m128i a);
extern __m128i _mm_movpi64_epi64(__m64 a);
extern __m128i _mm_move_epi64(__m128i a);
extern __m128d _mm_unpackhi_pd(__m128d a, __m128d b);
extern __m128d _mm_unpacklo_pd(__m128d a, __m128d b);
extern int _mm_movemask_pd(__m128d a);
extern __m128d _mm_shuffle_pd(__m128d a, __m128d b, int imm);
extern __m128 _mm_castpd_ps(__m128d a);
extern __m128i _mm_castpd_si128(__m128d a);
extern __m128d _mm_castps_pd(__m128 a);
extern __m128i _mm_castps_si128(__m128 a);
extern __m128 _mm_castsi128_ps(__m128i a);
extern __m128d _mm_castsi128_pd(__m128i a);
void _mm_pause(void);

#if defined(_MSC_VER) && !defined(__Clang__)

#pragma intrinsic(_mm_add_sd)
#pragma intrinsic(_mm_add_pd)
#pragma intrinsic(_mm_sub_sd)
#pragma intrinsic(_mm_sub_pd)
#pragma intrinsic(_mm_mul_sd)
#pragma intrinsic(_mm_mul_pd)
#pragma intrinsic(_mm_div_sd)
#pragma intrinsic(_mm_div_pd)
#pragma intrinsic(_mm_sqrt_sd)
#pragma intrinsic(_mm_sqrt_pd)
#pragma intrinsic(_mm_min_sd)
#pragma intrinsic(_mm_min_pd)
#pragma intrinsic(_mm_max_sd)
#pragma intrinsic(_mm_max_pd)
#pragma intrinsic(_mm_and_pd)
#pragma intrinsic(_mm_andnot_pd)
#pragma intrinsic(_mm_or_pd)
#pragma intrinsic(_mm_xor_pd)
#pragma intrinsic(_mm_cmpeq_pd)
#pragma intrinsic(_mm_cmplt_pd)
#pragma intrinsic(_mm_cmple_pd)
#pragma intrinsic(_mm_cmpgt_pd)
#pragma intrinsic(_mm_cmpge_pd)
#pragma intrinsic(_mm_cmpord_pd)
#pragma intrinsic(_mm_cmpunord_pd)
#pragma intrinsic(_mm_cmpneq_pd)
#pragma intrinsic(_mm_cmpnlt_pd)
#pragma intrinsic(_mm_cmpnle_pd)
#pragma intrinsic(_mm_cmpngt_pd)
#pragma intrinsic(_mm_cmpnge_pd)
#pragma intrinsic(_mm_cmpeq_sd)
#pragma intrinsic(_mm_cmplt_sd)
#pragma intrinsic(_mm_cmple_sd)
#pragma intrinsic(_mm_cmpgt_sd)
#pragma intrinsic(_mm_cmpge_sd)
#pragma intrinsic(_mm_cmpord_sd)
#pragma intrinsic(_mm_cmpunord_sd)
#pragma intrinsic(_mm_cmpneq_sd)
#pragma intrinsic(_mm_cmpnlt_sd)
#pragma intrinsic(_mm_cmpnle_sd)
#pragma intrinsic(_mm_cmpngt_sd)
#pragma intrinsic(_mm_cmpnge_sd)
#pragma intrinsic(_mm_comieq_sd)
#pragma intrinsic(_mm_comilt_sd)
#pragma intrinsic(_mm_comile_sd)
#pragma intrinsic(_mm_comigt_sd)
#pragma intrinsic(_mm_comige_sd)
#pragma intrinsic(_mm_comineq_sd)
#pragma intrinsic(_mm_ucomieq_sd)
#pragma intrinsic(_mm_ucomilt_sd)
#pragma intrinsic(_mm_ucomile_sd)
#pragma intrinsic(_mm_ucomigt_sd)
#pragma intrinsic(_mm_ucomige_sd)
#pragma intrinsic(_mm_ucomineq_sd)
#pragma intrinsic(_mm_cvtpd_ps)
#pragma intrinsic(_mm_cvtps_pd)
#pragma intrinsic(_mm_cvtepi32_pd)
#pragma intrinsic(_mm_cvtpd_epi32)
#pragma intrinsic(_mm_cvtsd_si32)
#pragma intrinsic(_mm_cvtsd_ss)
#pragma intrinsic(_mm_cvtsi32_sd)
#pragma intrinsic(_mm_cvtss_sd)
#pragma intrinsic(_mm_cvttpd_epi32)
#pragma intrinsic(_mm_cvttsd_si32)
//#pragma intrinsic(_mm_cvtpd_pi32)
//#pragma intrinsic(_mm_cvttpd_pi32)
//#pragma intrinsic(_mm_cvtpi32_pd)
#pragma intrinsic(_mm_cvtsd_f64)
#pragma intrinsic(_mm_load_pd)
#pragma intrinsic(_mm_load1_pd)
#pragma intrinsic(_mm_loadr_pd)
#pragma intrinsic(_mm_loadu_pd)
//#pragma intrinsic(_mm_loadu_si64)
//#pragma intrinsic(_mm_loadu_si32)
//#pragma intrinsic(_mm_loadu_si16)
#pragma intrinsic(_mm_load_sd)
#pragma intrinsic(_mm_loadh_pd)
#pragma intrinsic(_mm_loadl_pd)
//#pragma intrinsic(_mm_undefined_pd)
#pragma intrinsic(_mm_set_sd)
#pragma intrinsic(_mm_set1_pd)
//#pragma intrinsic(_mm_set_pd1)
#pragma intrinsic(_mm_set_pd)
#pragma intrinsic(_mm_setr_pd)
#pragma intrinsic(_mm_setzero_pd)
#pragma intrinsic(_mm_move_sd)
#pragma intrinsic(_mm_store_sd)
#pragma intrinsic(_mm_store_pd)
#pragma intrinsic(_mm_store1_pd)
//#pragma intrinsic(_mm_store_pd1)
#pragma intrinsic(_mm_storeu_pd)
#pragma intrinsic(_mm_storer_pd)
#pragma intrinsic(_mm_storeh_pd)
#pragma intrinsic(_mm_storel_pd)
#pragma intrinsic(_mm_add_epi8)
#pragma intrinsic(_mm_add_epi16)
#pragma intrinsic(_mm_add_epi32)
//#pragma intrinsic(_mm_add_si64)
#pragma intrinsic(_mm_add_epi64)
#pragma intrinsic(_mm_adds_epi8)
#pragma intrinsic(_mm_adds_epi16)
#pragma intrinsic(_mm_adds_epu8)
#pragma intrinsic(_mm_adds_epu16)
#pragma intrinsic(_mm_avg_epu8)
#pragma intrinsic(_mm_avg_epu16)
#pragma intrinsic(_mm_madd_epi16)
#pragma intrinsic(_mm_max_epi16)
#pragma intrinsic(_mm_max_epu8)
#pragma intrinsic(_mm_min_epi16)
#pragma intrinsic(_mm_min_epu8)
#pragma intrinsic(_mm_mulhi_epi16)
#pragma intrinsic(_mm_mulhi_epu16)
#pragma intrinsic(_mm_mullo_epi16)
//#pragma intrinsic(_mm_mul_su32)
#pragma intrinsic(_mm_mul_epu32)
#pragma intrinsic(_mm_sad_epu8)
#pragma intrinsic(_mm_sub_epi8)
#pragma intrinsic(_mm_sub_epi16)
#pragma intrinsic(_mm_sub_epi32)
//#pragma intrinsic(_mm_sub_si64)
#pragma intrinsic(_mm_sub_epi64)
#pragma intrinsic(_mm_subs_epi8)
#pragma intrinsic(_mm_subs_epi16)
#pragma intrinsic(_mm_subs_epu8)
#pragma intrinsic(_mm_subs_epu16)
#pragma intrinsic(_mm_and_si128)
#pragma intrinsic(_mm_andnot_si128)
#pragma intrinsic(_mm_or_si128)
#pragma intrinsic(_mm_xor_si128)
#pragma intrinsic(_mm_slli_si128)
#pragma intrinsic(_mm_slli_epi16)
#pragma intrinsic(_mm_sll_epi16)
#pragma intrinsic(_mm_slli_epi32)
#pragma intrinsic(_mm_sll_epi32)
#pragma intrinsic(_mm_slli_epi64)
#pragma intrinsic(_mm_sll_epi64)
#pragma intrinsic(_mm_srai_epi16)
#pragma intrinsic(_mm_sra_epi16)
#pragma intrinsic(_mm_srai_epi32)
#pragma intrinsic(_mm_sra_epi32)
#pragma intrinsic(_mm_srli_si128)
#pragma intrinsic(_mm_srli_epi16)
#pragma intrinsic(_mm_srl_epi16)
#pragma intrinsic(_mm_srli_epi32)
#pragma intrinsic(_mm_srl_epi32)
#pragma intrinsic(_mm_srli_epi64)
#pragma intrinsic(_mm_srl_epi64)
#pragma intrinsic(_mm_cmpeq_epi8)
#pragma intrinsic(_mm_cmpeq_epi16)
#pragma intrinsic(_mm_cmpeq_epi32)
#pragma intrinsic(_mm_cmpgt_epi8)
#pragma intrinsic(_mm_cmpgt_epi16)
#pragma intrinsic(_mm_cmpgt_epi32)
#pragma intrinsic(_mm_cmplt_epi8)
#pragma intrinsic(_mm_cmplt_epi16)
#pragma intrinsic(_mm_cmplt_epi32)
#ifdef _M_AMD64
#pragma intrinsic(_mm_cvtsi64_sd)
#pragma intrinsic(_mm_cvtsd_si64)
#pragma intrinsic(_mm_cvttsd_si64)
#endif
#pragma intrinsic(_mm_cvtepi32_ps)
#pragma intrinsic(_mm_cvtps_epi32)
#pragma intrinsic(_mm_cvttps_epi32)
#pragma intrinsic(_mm_cvtsi32_si128)
#pragma intrinsic(_mm_cvtsi64_si128)
#pragma intrinsic(_mm_cvtsi128_si32)
#pragma intrinsic(_mm_cvtsi128_si64)
#pragma intrinsic(_mm_load_si128)
#pragma intrinsic(_mm_loadu_si128)
#pragma intrinsic(_mm_loadl_epi64)
//#pragma intrinsic(_mm_undefined_si128)
#pragma intrinsic(_mm_set_epi64x)
//#pragma intrinsic(_mm_set_epi64)
#pragma intrinsic(_mm_set_epi32)
#pragma intrinsic(_mm_set_epi16)
#pragma intrinsic(_mm_set_epi8)
#pragma intrinsic(_mm_set1_epi64x)
//#pragma intrinsic(_mm_set1_epi64)
#pragma intrinsic(_mm_set1_epi32)
#pragma intrinsic(_mm_set1_epi16)
#pragma intrinsic(_mm_set1_epi8)
//#pragma intrinsic(_mm_setr_epi64)
#pragma intrinsic(_mm_setr_epi32)
#pragma intrinsic(_mm_setr_epi16)
#pragma intrinsic(_mm_setr_epi8)
#pragma intrinsic(_mm_setzero_si128)
#pragma intrinsic(_mm_store_si128)
#pragma intrinsic(_mm_storeu_si128)
//#pragma intrinsic(_mm_storeu_si64)
//#pragma intrinsic(_mm_storeu_si32)
//#pragma intrinsic(_mm_storeu_si16)
#pragma intrinsic(_mm_maskmoveu_si128)
#pragma intrinsic(_mm_storel_epi64)
#pragma intrinsic(_mm_stream_pd)
#pragma intrinsic(_mm_stream_si128)
#pragma intrinsic(_mm_stream_si32)
#ifdef _M_AMD64
//#pragma intrinsic(_mm_stream_si64)
#endif
#pragma intrinsic(_mm_clflush)
#pragma intrinsic(_mm_lfence)
#pragma intrinsic(_mm_mfence)
#pragma intrinsic(_mm_packs_epi16)
#pragma intrinsic(_mm_packs_epi32)
#pragma intrinsic(_mm_packus_epi16)
#pragma intrinsic(_mm_extract_epi16)
#pragma intrinsic(_mm_insert_epi16)
#pragma intrinsic(_mm_movemask_epi8)
#pragma intrinsic(_mm_shuffle_epi32)
#pragma intrinsic(_mm_shufflelo_epi16)
#pragma intrinsic(_mm_shufflehi_epi16)
#pragma intrinsic(_mm_unpackhi_epi8)
#pragma intrinsic(_mm_unpackhi_epi16)
#pragma intrinsic(_mm_unpackhi_epi32)
#pragma intrinsic(_mm_unpackhi_epi64)
#pragma intrinsic(_mm_unpacklo_epi8)
#pragma intrinsic(_mm_unpacklo_epi16)
#pragma intrinsic(_mm_unpacklo_epi32)
#pragma intrinsic(_mm_unpacklo_epi64)
//#pragma intrinsic(_mm_movepi64_pi64)
//#pragma intrinsic(_mm_movpi64_epi64)
#pragma intrinsic(_mm_move_epi64)
#pragma intrinsic(_mm_unpackhi_pd)
#pragma intrinsic(_mm_unpacklo_pd)
#pragma intrinsic(_mm_movemask_pd)
#pragma intrinsic(_mm_shuffle_pd)
#pragma intrinsic(_mm_castpd_ps)
#pragma intrinsic(_mm_castpd_si128)
#pragma intrinsic(_mm_castps_pd)
#pragma intrinsic(_mm_castps_si128)
#pragma intrinsic(_mm_castsi128_ps)
#pragma intrinsic(_mm_castsi128_pd)
#pragma intrinsic(_mm_pause)

#else /* _MSC_VER */


#endif /* _MSC_VER */



#endif /* _INCLUDED_EMM */
