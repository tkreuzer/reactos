/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _INC_UTIME
#define _INC_UTIME
#pragma once

#ifndef _WIN32
#error Only Win32 target is supported!
#endif

#include <corecrt.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _CRT_NO_TIME_T
  struct _utimbuf {
        time_t actime;
        time_t modtime;
    };
#endif

  struct __utimbuf32 {
    __time32_t actime;
    __time32_t modtime;
};

  struct __utimbuf64 {
    __time64_t actime;
    __time64_t modtime;
};

#if defined(_CRT_INTERNAL_NONSTDC_NAMES) && _CRT_INTERNAL_NONSTDC_NAMES && !defined _CRT_NO_TIME_T
  struct utimbuf {
        time_t actime;
        time_t modtime;
    };

  struct utimbuf32 {
        __time32_t actime;
        __time32_t modtime;
    };
#endif




  _ACRTIMP
  int
  __cdecl
  _utime32(
    _In_z_   char const*         _FileName,
    _In_opt_ struct __utimbuf32* _Time);

  _ACRTIMP
  int
  __cdecl
  _futime32(
    _In_     int                 _FileHandle,
    _In_opt_ struct __utimbuf32* _Time);

  _ACRTIMP
  int
  __cdecl
  _wutime32(
    _In_z_   wchar_t const*      _FileName,
    _In_opt_ struct __utimbuf32* _Time);

  _ACRTIMP
  int
  __cdecl
  _utime64(
    _In_z_   char const*         _FileName,
    _In_opt_ struct __utimbuf64* _Time);

  _ACRTIMP
  int
  __cdecl
  _futime64(
    _In_ int _FileHandle,
    _In_opt_ struct __utimbuf64* _Time);

  _ACRTIMP
  int
  __cdecl
  _wutime64(
    _In_z_   wchar_t const*      _FileName,
    _In_opt_ struct __utimbuf64* _Time);


#if !defined RC_INVOKED && !defined __midl && !defined _CRT_NO_TIME_T
#ifdef _USE_32BIT_TIME_T
  static __inline int __CRTDECL _utime(char const* const _FileName, struct _utimbuf* const _Time) {
    _STATIC_ASSERT(sizeof(struct _utimbuf) == sizeof(struct __utimbuf32));
    return _utime32(_FileName, (struct __utimbuf32*)_Time);
  }

  static __inline int __CRTDECL _futime(int const _FileHandle, struct _utimbuf* const _Time) {
    _STATIC_ASSERT(sizeof(struct _utimbuf) == sizeof(struct __utimbuf32));
    return _futime32(_FileHandle, (struct __utimbuf32*)_Time);
  }

  static __inline int __CRTDECL _wutime(wchar_t const* const _FileName, struct _utimbuf* const _Time) {
    _STATIC_ASSERT(sizeof(struct _utimbuf) == sizeof(struct __utimbuf32));
    return _wutime32(_FileName, (struct __utimbuf32*)_Time);
  }

#else
        static __inline int __CRTDECL _utime(char const* const _FileName, struct _utimbuf* const _Time)
        {
            _STATIC_ASSERT(sizeof(struct _utimbuf) == sizeof(struct __utimbuf64));
            return _utime64(_FileName, (struct __utimbuf64*)_Time);
        }

        static __inline int __CRTDECL _futime(int const _FileHandle, struct _utimbuf* const _Time)
        {
            _STATIC_ASSERT(sizeof(struct _utimbuf) == sizeof(struct __utimbuf64));
            return _futime64(_FileHandle, (struct __utimbuf64*)_Time);
        }

        static __inline int __CRTDECL _wutime(wchar_t const* const _FileName, struct _utimbuf* const _Time)
        {
            _STATIC_ASSERT(sizeof(struct _utimbuf) == sizeof(struct __utimbuf64));
            return _wutime64(_FileName, (struct __utimbuf64*)_Time);
        }

#endif

#if defined(_CRT_INTERNAL_NONSTDC_NAMES) && _CRT_INTERNAL_NONSTDC_NAMES
#ifdef _USE_32BIT_TIME_T
            static __inline int __CRTDECL utime(char const* const _FileName, struct utimbuf* const _Time)
            {
                _STATIC_ASSERT(sizeof(struct utimbuf) == sizeof(struct __utimbuf32));
                return _utime32(_FileName, (struct __utimbuf32*)_Time);
            }
#else
            static __inline int __CRTDECL utime(char const* const _FileName, struct utimbuf* const _Time)
            {
                _STATIC_ASSERT(sizeof(struct utimbuf) == sizeof(struct __utimbuf64));
                return _utime64(_FileName, (struct __utimbuf64*)_Time);
            }
#endif
#endif
#endif

#ifdef __cplusplus
}
#endif
