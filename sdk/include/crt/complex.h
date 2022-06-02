/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
/*
 * complex.h
 *
 * This file is part of the Mingw32 package.
 *
 * Contributors:
 *  Created by Danny Smith <dannysmith@users.sourceforge.net>
 *
 *  THIS SOFTWARE IS NOT COPYRIGHTED
 *
 *  This source code is offered for use in the public domain. You may
 *  use, modify or distribute it freely.
 *
 *  This code is distributed in the hope that it will be useful but
 *  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAIMED. This includes but is not limited to warranties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef _COMPLEX
#define _COMPLEX

#include <crtdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RC_INVOKED

#ifndef _C_COMPLEX_T
#define _C_COMPLEX_T
typedef struct _C_double_complex
{
    double _Val[2];
} _C_double_complex;

typedef struct _C_float_complex
{
    float _Val[2];
} _C_float_complex;

typedef struct _C_ldouble_complex
{
    long double _Val[2];
} _C_ldouble_complex;
#endif

typedef _C_double_complex  _Dcomplex;
typedef _C_float_complex   _Fcomplex;
typedef _C_ldouble_complex _Lcomplex;

#define _DCOMPLEX_(re, im)  _Cbuild(re, im)
#define _FCOMPLEX_(re, im)  _FCbuild(re, im)
#define _LCOMPLEX_(re, im)  _LCbuild(re, im)

#define _Complex_I _FCbuild(0.0F, 1.0F)
#define I          _Complex_I

#ifdef _MSC_VER2

double creal(_Dcomplex z);
double cimag(_Dcomplex z);
double carg(_Dcomplex z);
_Dcomplex conj(_Dcomplex z);
_Dcomplex cacos(_Dcomplex z);
_Dcomplex casin(_Dcomplex z);
_Dcomplex catan(_Dcomplex z);
_Dcomplex ccos(_Dcomplex z);
_Dcomplex csin(_Dcomplex z);
_Dcomplex ctan(_Dcomplex z);
_Dcomplex cacosh(_Dcomplex z);
_Dcomplex casinh(_Dcomplex z);
_Dcomplex catanh(_Dcomplex z);
_Dcomplex ccosh(_Dcomplex z);
_Dcomplex csinh(_Dcomplex z);
_Dcomplex ctanh(_Dcomplex z);
_Dcomplex cexp(_Dcomplex z);
_Dcomplex clog(_Dcomplex z);
_Dcomplex cpow(_Dcomplex x, _Dcomplex y);
_Dcomplex csqrt(_Dcomplex z);
_Dcomplex cproj(_Dcomplex z);

float crealf(_Fcomplex z);
float cimagf(_Fcomplex z);
float cargf(_Fcomplex z);
float cabsf(_Fcomplex z);
_Fcomplex conjf(_Fcomplex z);
_Fcomplex cacosf(_Fcomplex z);
_Fcomplex casinf(_Fcomplex z);
_Fcomplex catanf(_Fcomplex z);
_Fcomplex ccosf(_Fcomplex z);
_Fcomplex csinf(_Fcomplex z);
_Fcomplex ctanf(_Fcomplex z);
_Fcomplex cacoshf(_Fcomplex z);
_Fcomplex casinhf(_Fcomplex z);
_Fcomplex catanhf(_Fcomplex z);
_Fcomplex ccoshf(_Fcomplex z);
_Fcomplex csinhf(_Fcomplex z);
_Fcomplex ctanhf(_Fcomplex z);
_Fcomplex cexpf(_Fcomplex z);
_Fcomplex clogf(_Fcomplex z);
_Fcomplex cpowf(_Fcomplex x, _Fcomplex y);
_Fcomplex csqrtf(_Fcomplex z);
_Fcomplex cprojf(_Fcomplex z);

long double creall(_Lcomplex z);
long double cimagl(_Lcomplex z);
long double cargl(_Lcomplex z);
long double cabsl(_Lcomplex z);
_Lcomplex conjl(_Lcomplex z);
_Lcomplex  cacosl(_Lcomplex z);
_Lcomplex  casinl(_Lcomplex z);
_Lcomplex  catanl(_Lcomplex z);
_Lcomplex  ccosl(_Lcomplex z);
_Lcomplex  csinl(_Lcomplex z);
_Lcomplex  ctanl(_Lcomplex z);
_Lcomplex  cacoshl(_Lcomplex z);
_Lcomplex  casinhl(_Lcomplex z);
_Lcomplex  catanhl(_Lcomplex z);
_Lcomplex  ccoshl(_Lcomplex z);
_Lcomplex  csinhl(_Lcomplex z);
_Lcomplex  ctanhl(_Lcomplex z);
_Lcomplex  cexpl(_Lcomplex z);
_Lcomplex  clogl(_Lcomplex z);
_Lcomplex  cpowl(_Lcomplex x, _Lcomplex y);
_Lcomplex  csqrtl(_Lcomplex z);
_Lcomplex cprojl(_Lcomplex z);

#endif

#ifdef __GNUC__

/* double */
__CRT_INLINE double creal (double _Complex _Z)
{
  return __real__ _Z;
}

__CRT_INLINE double cimag (double _Complex _Z)
{
  return __imag__ _Z;
}

__CRT_INLINE double _Complex conj (double _Complex _Z)
{
  return __extension__ ~_Z;
}

__CRT_INLINE  double carg (double _Complex _Z)
{
  double res;
  __asm__  ("fpatan;"
	   : "=t" (res) : "0" (__real__ _Z), "u" (__imag__ _Z) : "st(1)");
  return res;
}


/* float */
__CRT_INLINE float crealf (float _Complex _Z)
{
  return __real__ _Z;
}

__CRT_INLINE float cimagf (float _Complex _Z)
{
  return __imag__ _Z;
}

__CRT_INLINE float _Complex conjf (float _Complex _Z)
{
  return __extension__ ~_Z;
}

__CRT_INLINE  float cargf (float _Complex _Z)
{
  float res;
  __asm__  ("fpatan;"
	   : "=t" (res) : "0" (__real__ _Z), "u" (__imag__ _Z) : "st(1)");
  return res;
}

/* long double */
__CRT_INLINE long double creall (long double _Complex _Z)
{
  return __real__ _Z;
}

__CRT_INLINE long double cimagl (long double _Complex _Z)
{
  return __imag__ _Z;
}

__CRT_INLINE long double _Complex conjl (long double _Complex _Z)
{
  return __extension__ ~_Z;
}

__CRT_INLINE  long double cargl (long double _Complex _Z)
{
  long double res;
  __asm__  ("fpatan;"
	   : "=t" (res) : "0" (__real__ _Z), "u" (__imag__ _Z) : "st(1)");
  return res;
}

#endif /* __GNUC__ */


#endif /* RC_INVOKED */

#ifdef __cplusplus
}
#endif

#endif /* _COMPLEX */
