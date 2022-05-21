/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef __ASSERT_H_
#define __ASSERT_H_

#if defined _VCRT_BUILD && !defined _ASSERT_OK
    #error assert.h not for CRT internal use
#endif

#include <corecrt.h>

#undef assert
#ifdef NDEBUG

#define assert(expression) ((void)0)

#else /* !NDEBUG */

#ifdef __cplusplus
extern "C" {
#endif

  _ACRTIMP
  void
  __cdecl
  _wassert(
    _In_z_ const wchar_t *_Message,
    _In_z_ const wchar_t *_File,
    _In_ unsigned _Line);

#ifdef __cplusplus
}
#endif


#define assert(_Expression) (void)((!!(_Expression)) || (_wassert(_CRT_WIDE(#_Expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) )

#endif

#endif
