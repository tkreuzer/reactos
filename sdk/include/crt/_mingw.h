/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#ifndef _INC_MINGW
#define _INC_MINGW

#ifndef _INTEGRAL_MAX_BITS
#define _INTEGRAL_MAX_BITS 64
#endif

#ifndef _WIN64
 #ifndef _USE_32BIT_TIME_T
  #define _USE_32BIT_TIME_T
 #endif
#endif

#ifndef MINGW64
#define MINGW64
#define MINGW64_VERSION	1.0
#define MINGW64_VERSION_MAJOR	1
#define MINGW64_VERSION_MINOR	0
#define MINGW64_VERSION_STATE	"alpha"
#endif

#ifdef __GNUC__
 /* These compilers do support __declspec */
# if !defined(__MINGW32__) && !defined(__MINGW64__) && !defined(__CYGWIN32__)
#  define __declspec(x) __attribute__((x))
# endif
# define __DECLSPEC_SUPPORTED
# define __attribute__(x) /* nothing */
# define __restrict__ /* nothing */
#elif defined(__GNUC__)
# ifdef __declspec
#  ifndef __MINGW_IMPORT
#   ifdef _DLL
/* Note the extern. This is needed to work around GCC's
limitations in handling dllimport attribute.  */
#    define __MINGW_IMPORT  extern __attribute__ ((__dllimport__))
#   else
#    define __MINGW_IMPORT extern
#   endif
#  endif
#  ifndef _CRTIMP
#   ifdef __USE_CRTIMP
#    ifdef _DLL
#     define _CRTIMP  __attribute__ ((dllimport))
#    else
#     define _CRTIMP
#    endif
#   else
#    define _CRTIMP
#   endif
#  endif
#  define __DECLSPEC_SUPPORTED
# else /* __declspec */
#  undef __DECLSPEC_SUPPORTED
#  undef __MINGW_IMPORT
#  ifndef _CRTIMP
#   define _CRTIMP
#  endif
# endif /* __declspec */

#ifdef _MSC_VER
#define __restrict__ /* nothing */
#endif

/*
   The next two defines can cause problems if user code adds the __cdecl attribute
   like so:
   void __attribute__ ((__cdecl)) foo(void);
*/
# ifndef __cdecl
#  define __cdecl  __attribute__ ((__cdecl__))
# endif
# ifndef __stdcall
#  define __stdcall __attribute__ ((__stdcall__))
# endif

#if defined (__GNUC__) && defined (__GNUC_MINOR__)
#define __MINGW_GNUC_PREREQ(major, minor) \
  (__GNUC__ > (major) \
   || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
#else
#define __MINGW_GNUC_PREREQ(major, minor)  0
#endif

#if defined (_MSC_VER)
#define __MINGW_MSC_PREREQ(major, minor) (_MSC_VER >= (major * 100 + minor * 10))
#else
#define __MINGW_MSC_PREREQ(major, minor) 0
#endif

#define USE___UUIDOF	0

#ifdef __cplusplus
# define __CRT_INLINE inline
#elif defined(_MSC_VER)
# define __CRT_INLINE __inline
#elif defined(__GNUC__)
# if defined(__clang__) || ( __MINGW_GNUC_PREREQ(4, 3)  &&  __STDC_VERSION__ >= 199901L)
#  define __CRT_INLINE extern inline __attribute__((__always_inline__,__gnu_inline__))
# else
#  define __CRT_INLINE extern __inline__ __attribute__((__always_inline__))
# endif
#endif

#ifdef __cplusplus
# define __UNUSED_PARAM(x)
#else
# ifdef __GNUC__
#  define __UNUSED_PARAM(x) x __attribute__ ((__unused__))
# else
#  define __UNUSED_PARAM(x) x
# endif
#endif

#ifdef __cplusplus
# define __unaligned
#else
# ifdef __GNUC__
#  define __unaligned
# elif defined(_MSC_VER) && !defined(_M_IA64) && !defined(_M_AMD64)
#  define __unaligned
# else
#  define __unaligned
# endif
#endif

#ifdef __GNUC__
#define __MINGW_ATTRIB_NORETURN __attribute__ ((__noreturn__))
#define __MINGW_ATTRIB_CONST __attribute__ ((__const__))
#elif __MINGW_MSC_PREREQ(12, 0)
#define __MINGW_ATTRIB_NORETURN __declspec(noreturn)
#define __MINGW_ATTRIB_CONST
#else
#define __MINGW_ATTRIB_NORETURN
#define __MINGW_ATTRIB_CONST
#endif

#if __MINGW_GNUC_PREREQ (3, 0)
#define __MINGW_ATTRIB_MALLOC __attribute__ ((__malloc__))
#define __MINGW_ATTRIB_PURE __attribute__ ((__pure__))
#elif __MINGW_MSC_PREREQ(14, 0)
#define __MINGW_ATTRIB_MALLOC __declspec(noalias) __declspec(restrict)
#define __MINGW_ATTRIB_PURE
#else
#define __MINGW_ATTRIB_MALLOC
#define __MINGW_ATTRIB_PURE
#endif

/* Attribute `nonnull' was valid as of gcc 3.3.  We don't use GCC's
   variadiac macro facility, because variadic macros cause syntax
   errors with  --traditional-cpp.  */
#if  __MINGW_GNUC_PREREQ (3, 3)
#define __MINGW_ATTRIB_NONNULL(arg) __attribute__ ((__nonnull__ (arg)))
#else
#define __MINGW_ATTRIB_NONNULL(arg)
#endif /* GNUC >= 3.3 */

#ifdef __GNUC__
#define __MINGW_ATTRIB_UNUSED __attribute__ ((__unused__))
#else
#define __MINGW_ATTRIB_UNUSED
#endif /* ATTRIBUTE_UNUSED */

#if  __MINGW_GNUC_PREREQ (3, 1)
#define __MINGW_ATTRIB_DEPRECATED __attribute__ ((__deprecated__))
#elif __MINGW_MSC_PREREQ(12, 0)
#define __MINGW_ATTRIB_DEPRECATED __declspec(deprecated)
#else
#define __MINGW_ATTRIB_DEPRECATED
#endif

#if  __MINGW_GNUC_PREREQ (3, 1)
#define __MINGW_ATTRIB_DEPRECATED_SEC_WARN //__attribute__ ((__deprecated__))
#elif __MINGW_MSC_PREREQ(12, 0)
#define __MINGW_ATTRIB_DEPRECATED_SEC_WARN //__declspec(deprecated)
#else
#define __MINGW_ATTRIB_DEPRECATED_SEC_WARN
#endif

#if  __MINGW_GNUC_PREREQ (3, 1)
#define __MINGW_ATTRIB_DEPRECATED_MSVC2005 //__attribute__ ((__deprecated__))
#elif __MINGW_MSC_PREREQ(12, 0)
#define __MINGW_ATTRIB_DEPRECATED_MSVC2005 //__declspec(deprecated)
#else
#define __MINGW_ATTRIB_DEPRECATED_MSVC2005
#endif

#if  __MINGW_GNUC_PREREQ (3, 3)
#define __MINGW_NOTHROW __attribute__ ((__nothrow__))
#elif __MINGW_MSC_PREREQ(12, 0) && defined (__cplusplus)
#define __MINGW_NOTHROW __declspec(nothrow)
#else
#define __MINGW_NOTHROW
#endif

/* TODO: Mark (almost) all CRT functions as __MINGW_NOTHROW.  This will
allow GCC to optimize away some EH unwind code, at least in DW2 case.  */

#ifndef __MINGW_EXTENSION
#if defined(__GNUC__) || defined(__GNUG__)
#define __MINGW_EXTENSION       __extension__
#else
#define __MINGW_EXTENSION
#endif
#endif

#ifndef __MSVCRT_VERSION__
/*  High byte is the major version, low byte is the minor. */
# define __MSVCRT_VERSION__ 0x0700
#endif

//#ifndef WINVER
//#define WINVER 0x0502
//#endif

#ifndef _UINTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED
#ifdef _WIN64
  typedef unsigned __int64 uintptr_t;
#else
  typedef unsigned int uintptr_t;
#endif
#endif

#include <mingw32/intrin.h>

#endif /* !_INC_MINGW */

#ifndef _WCTYPE_T_DEFINED
#define _WCTYPE_T_DEFINED
  typedef unsigned short wint_t;
  typedef unsigned short wctype_t;

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
  typedef __builtin_va_list __gnuc_va_list;
#endif

#ifndef _VA_LIST_DEFINED
#define _VA_LIST_DEFINED
  typedef __gnuc_va_list va_list;
#endif

# define __ptr32
# define __ptr64
# ifdef __cplusplus
#  define __forceinline inline __attribute__((__always_inline__))
# else
#  if (( __MINGW_GNUC_PREREQ(4, 3)  &&  __STDC_VERSION__ >= 199901L) || defined(__clang__))
#   define __forceinline extern inline __attribute__((__always_inline__,__gnu_inline__))
#  else
#   define __forceinline extern __inline__ __attribute__((__always_inline__))
#  endif
# endif
#ifdef _USE_32BIT_TIME_T
#error You cannot use 32-bit time_t (_USE_32BIT_TIME_T) with _WIN64
#undef _USE_32BIT_TIME_T
#endif
#endif
#else
#if _INTEGRAL_MAX_BITS < 64
#define _USE_32BIT_TIME_T
#endif
#endif

#ifndef _ERRCODE_DEFINED
#define _ERRCODE_DEFINED
  typedef int errcode;
  typedef int errno_t;
#endif

#ifndef _TIME32_T_DEFINED
#define _TIME32_T_DEFINED
  typedef long __time32_t;
#endif

#ifndef _TIME64_T_DEFINED
#define _TIME64_T_DEFINED
//#if _INTEGRAL_MAX_BITS >= 64
  typedef __int64 __time64_t;
#endif
//#endif

#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
#ifdef _USE_32BIT_TIME_T
  typedef __time32_t time_t;
#else
  typedef __time64_t time_t;
#endif
#endif

#ifndef _CONST_RETURN
#define _CONST_RETURN
#endif

#ifndef __CRT_UNALIGNED
#define __CRT_UNALIGNED
#endif

#ifndef UNALIGNED
#if defined(__ia64__) || defined(__x86_64)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif
#endif

#ifndef _CRT_ALIGN
#define _CRT_ALIGN(x) __attribute__ ((aligned(x)))
#endif

#ifndef _CRTNOALIAS
#define _CRTNOALIAS
#endif

#ifndef _CRTRESTRICT
#define _CRTRESTRICT
#endif

#ifndef __CRTDECL
#define __CRTDECL __cdecl
#endif

#define _ARGMAX 100

#ifndef _TRUNCATE
#define _TRUNCATE ((size_t)-1)
#endif
  struct threadlocaleinfostruct;
  struct threadmbcinfostruct;
  typedef struct threadlocaleinfostruct *pthreadlocinfo;
  typedef struct threadmbcinfostruct *pthreadmbcinfo;
  struct __lc_time_data;

  typedef struct localeinfo_struct {
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
  } _locale_tstruct,*_locale_t;

#ifndef _TAGLC_ID_DEFINED
#define _TAGLC_ID_DEFINED
  typedef struct tagLC_ID {
    unsigned short wLanguage;
    unsigned short wCountry;
    unsigned short wCodePage;
  } LC_ID,*LPLC_ID;
#endif

#ifndef _THREADLOCALEINFO
#define _THREADLOCALEINFO
  typedef struct threadlocaleinfostruct {
    int refcount;
    unsigned int lc_codepage;
    unsigned int lc_collate_cp;
    unsigned long lc_handle[6];
    LC_ID lc_id[6];
    struct {
      char *locale;
      wchar_t *wlocale;
      int *refcount;
      int *wrefcount;
    } lc_category[6];
    int lc_clike;
    int mb_cur_max;
    int *lconv_intl_refcount;
    int *lconv_num_refcount;
    int *lconv_mon_refcount;
    struct lconv *lconv;
    int *ctype1_refcount;
    unsigned short *ctype1;
    const unsigned short *pctype;
    const unsigned char *pclmap;
    const unsigned char *pcumap;
    struct __lc_time_data *lc_time_curr;
  } threadlocinfo;
#endif

#ifdef __cplusplus
}
#endif

#define __crt_typefix(ctype)

#ifndef _CRT_UNUSED
#define _CRT_UNUSED(x) (void)x
#endif

#pragma pack(pop)
#define _DECLSPEC_INTRIN_TYPE
#endif

/* Define to a function attribute for Microsoft hotpatch assembly prefix. */
#ifndef DECLSPEC_HOTPATCH
#if defined(_MSC_VER) || defined(__clang__)
/* FIXME: http://llvm.org/bugs/show_bug.cgi?id=20888 */
#define DECLSPEC_HOTPATCH
#else
#define DECLSPEC_HOTPATCH __attribute__((__ms_hook_prologue__))
#endif
#endif /* DECLSPEC_HOTPATCH */

#ifndef __INTRIN_INLINE
#  define __INTRIN_INLINE extern __inline__ __attribute__((__always_inline__,__gnu_inline__,artificial))
#endif

#ifndef HAS_BUILTIN
#  ifdef __clang__
#    define HAS_BUILTIN(x) __has_builtin(x)
#  else
#    define HAS_BUILTIN(x) 0
#  endif
#endif

#ifdef __cplusplus
#  define __mingw_ovr  inline __cdecl
#elif defined (__GNUC__)
#  define __mingw_ovr static \
      __attribute__ ((__unused__)) __inline__ __cdecl
#else
#  define __mingw_ovr static __cdecl
#endif /* __cplusplus */

#include "_mingw_mac.h"

#endif /* !_INC_MINGW */

