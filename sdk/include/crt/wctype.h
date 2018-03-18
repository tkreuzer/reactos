/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _INC_WCTYPE
#define _INC_WCTYPE

#ifndef _WIN32
#error Only Win32 target is supported!
#endif

#include <crtdefs.h>

#pragma pack(push,_CRT_PACKING)

#ifdef __cplusplus
extern "C" {
#endif

/* Wide character equivalents - also in ctype.h */
_CRTIMP int __cdecl __MINGW_NOTHROW	iswctype(wint_t, wctype_t);
_CRTIMP int __cdecl __MINGW_NOTHROW	is_wctype(wint_t, wctype_t);	/* Obsolete! */

#if (defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
     || !defined __STRICT_ANSI__ || defined __cplusplus
int __cdecl __MINGW_NOTHROW iswblank (wint_t);
#endif

#ifndef _CRT_CTYPEDATA_DEFINED
#define _CRT_CTYPEDATA_DEFINED
#ifndef _CTYPE_DISABLE_MACROS

#ifndef __PCTYPE_FUNC
#define __PCTYPE_FUNC __pctype_func()
#ifdef _MSVCRT_
#define __pctype_func() (_pctype)
#else
#define __pctype_func() (*_imp___pctype)
#endif
#endif

#ifndef _pctype
#ifdef _MSVCRT_
  extern unsigned short *_pctype;
#else
  extern unsigned short **_imp___pctype;
#define _pctype (*_imp___pctype)
#endif
#endif

#ifndef _CTYPE_H_
#ifdef __DECLSPEC_SUPPORTED
# if __MSVCRT_VERSION__ <= 0x0700
  __MINGW_IMPORT unsigned short _ctype[];
# endif
# ifdef __MSVCRT__
  __MINGW_IMPORT const unsigned short* _pctype;
# else	/* CRTDLL */
  __MINGW_IMPORT const unsigned short* _pctype_dll;
# define  _pctype _pctype_dll
# endif

#ifndef _CRT_WCTYPEDATA_DEFINED
#define _CRT_WCTYPEDATA_DEFINED
#ifndef _CTYPE_DISABLE_MACROS
#ifndef _wctype
#ifdef _MSVCRT_
  extern unsigned short *_wctype;
#else
  extern unsigned short **_imp___wctype;
#define _wctype (*_imp___wctype)
#endif
#endif

#ifndef _pwctype
#ifdef _MSVCRT_
  extern unsigned short *_pwctype;
#else
  extern unsigned short **_imp___pwctype;
#define _pwctype (*_imp___pwctype)
#define __pwctype_func() (*_imp___pwctype)
#endif
#endif
#endif
#endif

#define _UPPER 0x1
#define _LOWER 0x2
#define _DIGIT 0x4
#define _SPACE 0x8

#ifndef __WCTYPE_INLINES_DEFINED
_CRTIMP int __cdecl __MINGW_NOTHROW iswalnum(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswalpha(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswascii(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswcntrl(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswdigit(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswgraph(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswlower(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswprint(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswpunct(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswspace(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswupper(wint_t);
_CRTIMP int __cdecl __MINGW_NOTHROW iswxdigit(wint_t);
#endif

typedef wchar_t wctrans_t;

#define _LEADBYTE 0x8000
#define _ALPHA (0x0100|_UPPER|_LOWER)

#ifndef _WCTYPE_DEFINED
#define _WCTYPE_DEFINED

  int __cdecl iswalpha(wint_t);
  int __cdecl iswupper(wint_t);
  int __cdecl iswlower(wint_t);
  int __cdecl iswdigit(wint_t);
  int __cdecl iswxdigit(wint_t);
  int __cdecl iswspace(wint_t);
  int __cdecl iswpunct(wint_t);
  int __cdecl iswalnum(wint_t);
  int __cdecl iswprint(wint_t);
  int __cdecl iswgraph(wint_t);
  int __cdecl iswcntrl(wint_t);
  int __cdecl iswascii(wint_t);
  int __cdecl isleadbyte(int);
  wint_t __cdecl towupper(wint_t);
  wint_t __cdecl towlower(wint_t);
  int __cdecl iswctype(wint_t,wctype_t);
  _CRTIMP int __cdecl __iswcsymf(wint_t);
  _CRTIMP int __cdecl __iswcsym(wint_t);
  int __cdecl is_wctype(wint_t,wctype_t);
#if (defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || !defined (NO_OLDNAMES)
 _CRTIMP int __cdecl iswblank(wint_t _C);
#endif
#endif

#ifndef _WCTYPE_INLINE_DEFINED
#define _WCTYPE_INLINE_DEFINED
#ifndef __cplusplus
#define iswalpha(_c) (iswctype(_c,_ALPHA))
#define iswupper(_c) (iswctype(_c,_UPPER))
#define iswlower(_c) (iswctype(_c,_LOWER))
#define iswdigit(_c) (iswctype(_c,_DIGIT))
#define iswxdigit(_c) (iswctype(_c,_HEX))
#define iswspace(_c) (iswctype(_c,_SPACE))
#define iswpunct(_c) (iswctype(_c,_PUNCT))
#define iswalnum(_c) (iswctype(_c,_ALPHA|_DIGIT))
#define iswprint(_c) (iswctype(_c,_BLANK|_PUNCT|_ALPHA|_DIGIT))
#define iswgraph(_c) (iswctype(_c,_PUNCT|_ALPHA|_DIGIT))
#define iswcntrl(_c) (iswctype(_c,_CONTROL))
#define iswascii(_c) ((unsigned)(_c) < 0x80)
#define isleadbyte(c) (__pctype_func()[(unsigned char)(c)] & _LEADBYTE)
#else
  __CRT_INLINE int __cdecl iswalpha(wint_t _C) {return (iswctype(_C,_ALPHA)); }
  __CRT_INLINE int __cdecl iswupper(wint_t _C) {return (iswctype(_C,_UPPER)); }
  __CRT_INLINE int __cdecl iswlower(wint_t _C) {return (iswctype(_C,_LOWER)); }
  __CRT_INLINE int __cdecl iswdigit(wint_t _C) {return (iswctype(_C,_DIGIT)); }
  __CRT_INLINE int __cdecl iswxdigit(wint_t _C) {return (iswctype(_C,_HEX)); }
  __CRT_INLINE int __cdecl iswspace(wint_t _C) {return (iswctype(_C,_SPACE)); }
  __CRT_INLINE int __cdecl iswpunct(wint_t _C) {return (iswctype(_C,_PUNCT)); }
  __CRT_INLINE int __cdecl iswalnum(wint_t _C) {return (iswctype(_C,_ALPHA|_DIGIT)); }
  __CRT_INLINE int __cdecl iswprint(wint_t _C) {return (iswctype(_C,_BLANK|_PUNCT|_ALPHA|_DIGIT)); }
  __CRT_INLINE int __cdecl iswgraph(wint_t _C) {return (iswctype(_C,_PUNCT|_ALPHA|_DIGIT)); }
  __CRT_INLINE int __cdecl iswcntrl(wint_t _C) {return (iswctype(_C,_CONTROL)); }
  __CRT_INLINE int __cdecl iswascii(wint_t _C) {return ((unsigned)(_C) < 0x80); }
  __CRT_INLINE int __cdecl isleadbyte(int _C) {return (__pctype_func()[(unsigned char)(_C)] & _LEADBYTE); }
#endif
#endif

  typedef wchar_t wctrans_t;
  wint_t __cdecl towctrans(wint_t,wctrans_t);
  wctrans_t __cdecl wctrans(const char *);
  wctype_t __cdecl wctype(const char *);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif
