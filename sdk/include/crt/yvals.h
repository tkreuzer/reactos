/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#ifndef _YVALS
#define _YVALS

#include <_mingw.h>
/* TODO, don't include crtdef.h.  */
#include <crtdefs.h>
#include <crtdbg.h>

#pragma pack(push,_CRT_PACKING)

#define __PURE_APPDOMAIN_GLOBAL

#ifndef __CRTDECL
#define __CRTDECL __cdecl
#endif

#define _WIN32_C_LIB 1

#define _MULTI_THREAD 1
#define _IOSTREAM_OP_LOCKS 1
#define _GLOBAL_LOCALE 0

#define _COMPILER_TLS 1
#define _TLS_QUAL __declspec(thread)

#ifndef _HAS_EXCEPTIONS
#define _HAS_EXCEPTIONS 1
#endif

#ifndef _HAS_NAMESPACE
#define _HAS_NAMESPACE 1
#endif

#ifndef _HAS_IMMUTABLE_SETS
#define _HAS_IMMUTABLE_SETS 0
#endif

#ifndef _HAS_STRICT_CONFORMANCE
#define _HAS_STRICT_CONFORMANCE 0
#endif

#define _GLOBAL_USING 1
#define _HAS_ITERATOR_DEBUGGING 0

#define __STR2WSTR(str) L##str
#define _STR2WSTR(str) __STR2WSTR(str)

#define __FILEW__ _STR2WSTR(__FILE__)
#define __FUNCTIONW__ _STR2WSTR(__FUNCTION__)

#define _SCL_SECURE_INVALID_PARAMETER(expr) ::_invalid_parameter_noinfo()

#define _SCL_SECURE_INVALID_ARGUMENT_NO_ASSERT _SCL_SECURE_INVALID_PARAMETER("invalid argument")
#define _SCL_SECURE_OUT_OF_RANGE_NO_ASSERT _SCL_SECURE_INVALID_PARAMETER("out of range")
#define _SCL_SECURE_ALWAYS_VALIDATE(cond) { if (!(cond)) { _ASSERTE((#cond,0)); _SCL_SECURE_INVALID_ARGUMENT_NO_ASSERT; } }

#define _SCL_SECURE_ALWAYS_VALIDATE_RANGE(cond) { if (!(cond)) { _ASSERTE((#cond,0)); _SCL_SECURE_OUT_OF_RANGE_NO_ASSERT; } }

#define _SCL_SECURE_CRT_VALIDATE(cond,retvalue) { if (!(cond)) { _ASSERTE((#cond,0)); _SCL_SECURE_INVALID_PARAMETER(cond); return (retvalue); } }

#define _SCL_SECURE_VALIDATE(cond)
#define _SCL_SECURE_VALIDATE_RANGE(cond)

#define _SCL_SECURE_INVALID_ARGUMENT
#define _SCL_SECURE_OUT_OF_RANGE

#define _SCL_SECURE_MOVE(func,dst,size,src,count) func((dst),(src),(count))
#define _SCL_SECURE_COPY(func,dst,size,src,count) func((dst),(src),(count))

#define _SECURE_VALIDATION _Secure_validation

#define _SECURE_VALIDATION_DEFAULT false

#define _SCL_SECURE_TRAITS_VALIDATE(cond)
#define _SCL_SECURE_TRAITS_VALIDATE_RANGE(cond)

#define _SCL_SECURE_TRAITS_INVALID_ARGUMENT
#define _SCL_SECURE_TRAITS_OUT_OF_RANGE

#define _CRT_SECURE_MEMCPY(dest,destsize,source,count) ::memcpy((dest),(source),(count))
#define _CRT_SECURE_MEMMOVE(dest,destsize,source,count) ::memmove((dest),(source),(count))
#define _CRT_SECURE_WMEMCPY(dest,destsize,source,count) ::wmemcpy((dest),(source),(count))
#define _CRT_SECURE_WMEMMOVE(dest,destsize,source,count) ::wmemmove((dest),(source),(count))

#ifndef _VC6SP2
#define _VC6SP2 0
#endif

#ifndef _CRTIMP2_NCEEPURE
#define _CRTIMP2_NCEEPURE _CRTIMP
#endif

#ifndef _MRTIMP2_NPURE
#define _MRTIMP2_NPURE
#endif

#ifndef _MRTIMP2_NCEE
#define _MRTIMP2_NCEE _CRTIMP
#endif

#ifndef _MRTIMP2_NCEEPURE
#define _MRTIMP2_NCEEPURE _CRTIMP
#endif

#ifndef _MRTIMP2_NPURE_NCEEPURE
#define _MRTIMP2_NPURE_NCEEPURE
#endif

#define _DLL_CPPLIB

#ifndef _CRTIMP2_PURE
#define _CRTIMP2_PURE _CRTIMP
#endif

#ifndef _CRTIMP2_IMPORT
#if defined(CRTDLL2) && defined(_CRTBLD)
#define _CRTIMP2_IMPORT __declspec(dllexport)
#elif defined(_DLL) && !defined(_STATIC_CPPLIB)
#define _CRTIMP2_IMPORT __declspec(dllimport)
#else
#define _CRTIMP2_IMPORT
#endif
#endif // _CRTIMP2_IMPORT

#ifndef _CRTIMP2_PURE_IMPORT
#ifdef _M_CEE_PURE
#define _CRTIMP2_PURE_IMPORT
#else
#define _CRTIMP2_PURE_IMPORT _CRTIMP2_IMPORT
#endif
#endif // _CRTIMP2_PURE_IMPORT

#ifndef _CRTDATA2
#define _CRTDATA2 _CRTIMP
#endif

#define _DEPRECATED

#ifdef _ITERATOR_DEBUG_LEVEL // A. _ITERATOR_DEBUG_LEVEL is already defined.

// A1. Validate _ITERATOR_DEBUG_LEVEL.
#if _ITERATOR_DEBUG_LEVEL > 2 && defined(_DEBUG)
#error _ITERATOR_DEBUG_LEVEL > 2 is not supported in debug mode.
#elif _ITERATOR_DEBUG_LEVEL > 1 && !defined(_DEBUG)
#error _ITERATOR_DEBUG_LEVEL > 1 is not supported in release mode.
#endif

// A2. Inspect _HAS_ITERATOR_DEBUGGING.
#ifdef _HAS_ITERATOR_DEBUGGING // A2i. _HAS_ITERATOR_DEBUGGING is already defined, validate it.
#if _ITERATOR_DEBUG_LEVEL == 2 && _HAS_ITERATOR_DEBUGGING != 1
#error _ITERATOR_DEBUG_LEVEL == 2 must imply _HAS_ITERATOR_DEBUGGING == 1.
#elif _ITERATOR_DEBUG_LEVEL < 2 && _HAS_ITERATOR_DEBUGGING != 0
#error _ITERATOR_DEBUG_LEVEL < 2 must imply _HAS_ITERATOR_DEBUGGING == 0.
#endif
#else // A2ii. _HAS_ITERATOR_DEBUGGING is not yet defined, derive it.
#if _ITERATOR_DEBUG_LEVEL == 2
#define _HAS_ITERATOR_DEBUGGING 1
#else
#define _HAS_ITERATOR_DEBUGGING 0
#endif
#endif // _HAS_ITERATOR_DEBUGGING

// A3. Inspect _SECURE_SCL.
#ifdef _SECURE_SCL // A3i. _SECURE_SCL is already defined, validate it.
#if _ITERATOR_DEBUG_LEVEL > 0 && _SECURE_SCL != 1
#error _ITERATOR_DEBUG_LEVEL > 0 must imply _SECURE_SCL == 1.
#elif _ITERATOR_DEBUG_LEVEL == 0 && _SECURE_SCL != 0
#error _ITERATOR_DEBUG_LEVEL == 0 must imply _SECURE_SCL == 0.
#endif
#else // A3ii. _SECURE_SCL is not yet defined, derive it.
#if _ITERATOR_DEBUG_LEVEL > 0
#define _SECURE_SCL 1
#else
#define _SECURE_SCL 0
#endif
#endif // _SECURE_SCL

#else // B. _ITERATOR_DEBUG_LEVEL is not yet defined.

// B1. Inspect _HAS_ITERATOR_DEBUGGING.
#ifdef _HAS_ITERATOR_DEBUGGING // B1i. _HAS_ITERATOR_DEBUGGING is already defined, validate it.
#if _HAS_ITERATOR_DEBUGGING > 1
#error _HAS_ITERATOR_DEBUGGING must be either 0 or 1.
#elif _HAS_ITERATOR_DEBUGGING == 1 && !defined(_DEBUG)
#error _HAS_ITERATOR_DEBUGGING == 1 is not supported in release mode.
#endif
#else // B1ii. _HAS_ITERATOR_DEBUGGING is not yet defined, default it.
#ifdef _DEBUG
#define _HAS_ITERATOR_DEBUGGING 1
#else
#define _HAS_ITERATOR_DEBUGGING 0
#endif
#endif // _HAS_ITERATOR_DEBUGGING

// B2. Inspect _SECURE_SCL.
#ifdef _SECURE_SCL // B2i. _SECURE_SCL is already defined, validate it.
#if _SECURE_SCL > 1
#error _SECURE_SCL must be either 0 or 1.
#endif
#else // B2ii. _SECURE_SCL is not yet defined, default it.
#if _HAS_ITERATOR_DEBUGGING == 1
#define _SECURE_SCL 1
#else
#define _SECURE_SCL 0
#endif
#endif // _SECURE_SCL

// B3. Derive _ITERATOR_DEBUG_LEVEL.
#if _HAS_ITERATOR_DEBUGGING
#define _ITERATOR_DEBUG_LEVEL 2
#elif _SECURE_SCL
#define _ITERATOR_DEBUG_LEVEL 1
#else
#define _ITERATOR_DEBUG_LEVEL 0
#endif

#endif // _ITERATOR_DEBUG_LEVEL

#ifdef __cplusplus
#define _STD_BEGIN namespace std {
#define _STD_END }
#define _STD ::std::

#define _STDEXT_BEGIN namespace stdext {
#define _STDEXT_END }
#define _STDEXT ::stdext::

#ifdef _STD_USING
#define _C_STD_BEGIN namespace std {
#define _C_STD_END }
#define _CSTD ::std::
#else

#define _C_STD_BEGIN
#define _C_STD_END
#define _CSTD ::
#endif

#define _C_LIB_DECL extern "C" {
#define _END_C_LIB_DECL }
#define _EXTERN_C extern "C" {
#define _END_EXTERN_C }
#else
#define _STD_BEGIN
#define _STD_END
#define _STD

#define _C_STD_BEGIN
#define _C_STD_END
#define _CSTD

#define _C_LIB_DECL
#define _END_C_LIB_DECL
#define _EXTERN_C
#define _END_EXTERN_C
#endif

#define _Restrict restrict

#ifdef __cplusplus
_STD_BEGIN
typedef bool _Bool;
_STD_END
#endif

#define _LONGLONG /* __MINGW_EXTENSION */ __int64
#define _ULONGLONG /* __MINGW_EXTENSION */ unsigned __int64
#define _LLONG_MAX 0x7fffffffffffffffLL
#define _ULLONG_MAX 0xffffffffffffffffULL

#define _C2 1

#define _MAX_EXP_DIG 8
#define _MAX_INT_DIG 32
#define _MAX_SIG_DIG 36

__MINGW_EXTENSION typedef _LONGLONG _Longlong;
__MINGW_EXTENSION typedef _ULONGLONG _ULonglong;

#define _Filet _iobuf

#ifndef _FPOS_T_DEFINED
//#define _FPOSOFF(fp) ((long)(fp))
#endif

#define _IOBASE _base
#define _IOPTR _ptr
#define _IOCNT _cnt

#define _LOCK_LOCALE 0
#define _LOCK_MALLOC 1
#define _LOCK_STREAM 2
#define _LOCK_DEBUG 3
#define _MAX_LOCK 4

#ifdef __cplusplus
_STD_BEGIN

class _CRTIMP _Lockit {
public:
  explicit __thiscall _Lockit();
  explicit __thiscall _Lockit(int);
  __thiscall ~_Lockit();
  static void __cdecl _Lockit_ctor(int);
  static void __cdecl _Lockit_dtor(int);
private:
  static void __cdecl _Lockit_ctor(_Lockit *);
  static void __cdecl _Lockit_ctor(_Lockit *,int);
  static void __cdecl _Lockit_dtor(_Lockit *);
  _Lockit(const _Lockit&);
  _Lockit& operator=(const _Lockit&);
  int _Locktype;
};

#define _BEGIN_LOCK(_Kind) { _STD _Lockit _Lock(_Kind);
#define _END_LOCK() }
#define _BEGIN_LOCINFO(_VarName) { _Locinfo _VarName;
#define _END_LOCINFO() }
#define _RELIABILITY_CONTRACT

class _CRTIMP _Mutex {
public:
  __thiscall _Mutex();
  __thiscall ~_Mutex();
  void __thiscall _Lock();
  void __thiscall _Unlock();
private:
  static void __cdecl _Mutex_ctor(_Mutex *);
  static void __cdecl _Mutex_dtor(_Mutex *);
  static void __cdecl _Mutex_Lock(_Mutex *);
  static void __cdecl _Mutex_Unlock(_Mutex *);
  _Mutex(const _Mutex&);
  _Mutex& operator=(const _Mutex&);
  void *_Mtx;
};

class _CRTIMP _Init_locks {
public:
  __thiscall _Init_locks();
  __thiscall ~_Init_locks();
private:
  static void __cdecl _Init_locks_ctor(_Init_locks *);
  static void __cdecl _Init_locks_dtor(_Init_locks *);
};

#define _STL_REPORT_ERROR(mesg)              \
    do {                                     \
        _RPTF0(_CRT_ASSERT, mesg);           \
        _CRT_SECURE_INVALID_PARAMETER(mesg); \
    } while (false)

#define _STL_VERIFY(cond, mesg)                                     \
    do {                                                            \
        if (cond) { /* contextually convertible to bool paranoia */ \
        } else {                                                    \
            _STL_REPORT_ERROR(mesg);                                \
        }                                                           \
                                                                    \
        _Analysis_assume_(cond);                                    \
    } while (false)

#ifdef _DEBUG
#define _STL_ASSERT(cond, mesg) _STL_VERIFY(cond, mesg)
#else // ^^^ _DEBUG ^^^ // vvv !_DEBUG vvv
#define _STL_ASSERT(cond, mesg) _Analysis_assume_(cond)
#endif // _DEBUG

#ifdef _ENABLE_STL_INTERNAL_CHECK
#define _STL_INTERNAL_CHECK(cond) _STL_VERIFY(cond, "STL internal check: " _CRT_STRINGIZE(cond))
#else // ^^^ _ENABLE_STL_INTERNAL_CHECK ^^^ // vvv !_ENABLE_STL_INTERNAL_CHECK vvv
#define _STL_INTERNAL_CHECK(cond) _Analysis_assume_(cond)
#endif // _ENABLE_STL_INTERNAL_CHECK

// EXCEPTION MACROS
#if _HAS_EXCEPTIONS
#define _TRY_BEGIN try {
#define _CATCH(x) \
    }             \
    catch (x) {
#define _CATCH_ALL \
    }              \
    catch (...) {
#define _CATCH_END }

#define _RAISE(x) throw x
#define _RERAISE throw
#define _THROW(x) throw x

#else // _HAS_EXCEPTIONS
#define _TRY_BEGIN \
    {              \
        if (1) {
#define _CATCH(x) \
    }             \
    else if (0) {
#define _CATCH_ALL \
    }              \
    else if (0) {
#define _CATCH_END \
    }              \
    }

#ifdef _DEBUG
#define _RAISE(x) _invoke_watson(_CRT_WIDE(#x), __FUNCTIONW__, __FILEW__, __LINE__, 0)
#else // _DEBUG
#define _RAISE(x) _invoke_watson(nullptr, nullptr, nullptr, 0, 0)
#endif // _DEBUG

#define _RERAISE
#define _THROW(x) x._Raise()
#endif // _HAS_EXCEPTIONS

_STD_END
#endif

#ifndef _RELIABILITY_CONTRACT
#define _RELIABILITY_CONTRACT
#endif

_C_STD_BEGIN
_CRTIMP void __cdecl _Atexit(void (__cdecl *)(void));

typedef int _Mbstatet;

#define _ATEXIT_T void
#define _Mbstinit(x) mbstate_t x = {0}
_C_STD_END

#define _EXTERN_TEMPLATE template
#define _THROW_BAD_ALLOC _THROW1(...)

#define _THROW(x) throw x

#pragma pack(pop)
#endif
