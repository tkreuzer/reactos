/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _INC_TIMEB
#define _INC_TIMEB
#pragma once

#include <corecrt.h>

#ifndef _WIN32
#error Only Win32 target is supported!
#endif

#ifdef __cplusplus
extern "C" {
#endif


  struct __timeb32 {
    __time32_t time;
    unsigned short millitm;
    short timezone;
    short dstflag;
};

  struct __timeb64 {
    __time64_t time;
    unsigned short millitm;
    short timezone;
    short dstflag;
};

#if defined(_CRT_INTERNAL_NONSTDC_NAMES) && _CRT_INTERNAL_NONSTDC_NAMES  && !defined _CRT_NO_TIME_T
  struct timeb {
  time_t time;
  unsigned short millitm;
  short timezone;
  short dstflag;
  };
#endif

#ifdef _USE_32BIT_TIME_T
    #define _timeb      __timeb32
    #define _ftime      _ftime32
    #define _ftime_s    _ftime32_s
#else
    #define _timeb      __timeb64
    #define _ftime      _ftime64
    #define _ftime_s    _ftime64_s
#endif



  _CRT_INSECURE_DEPRECATE(_ftime32_s)
  _ACRTIMP
  void
  __cdecl
  _ftime32(
    _Out_ struct __timeb32* _Time);

  _ACRTIMP
  errno_t
  __cdecl
  _ftime32_s(
    _Out_ struct __timeb32* _Time);

  _CRT_INSECURE_DEPRECATE(_ftime64_s)
  _ACRTIMP
  void
  __cdecl
  _ftime64(
    _Out_ struct __timeb64* _Time);

  _ACRTIMP
  errno_t
  __cdecl
  _ftime64_s(
    _Out_ struct __timeb64* _Time);



#if !defined RC_INVOKED && !defined __midl && defined(_CRT_INTERNAL_NONSTDC_NAMES) && _CRT_INTERNAL_NONSTDC_NAMES && !defined _CRT_NO_TIME_T

#pragma warning(push)
#pragma warning(disable:4996)

#ifdef _USE_32BIT_TIME_T
  static __inline void __CRTDECL ftime(struct timeb* const _Tmb)
  {
    _STATIC_ASSERT(sizeof(struct timeb) == sizeof(struct __timeb32));
    _ftime32((struct __timeb32*)_Tmb);
  }
#else
  static __inline void __CRTDECL ftime(struct timeb* const _Tmb)
  {
    _STATIC_ASSERT(sizeof(struct timeb) == sizeof(struct __timeb64));
    _ftime64((struct __timeb64*)_Tmb);
  }
#endif
#pragma warning(pop)
#endif

#ifdef __cplusplus
}
#endif
#endif /* !_INC_TIMEB */
