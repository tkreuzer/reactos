
#pragma once

#include <intrin.h> // for __fastfail

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

ULONG
__cdecl
DbgPrint (
    _In_ PCCH Format,
    ...);

#ifdef __cplusplus
}; // extern "C"
#endif /* __cplusplus */

#define FAST_FAIL_LEGACY_GS_VIOLATION         0
#define FAST_FAIL_VTGUARD_CHECK_FAILURE       1
#define FAST_FAIL_STACK_COOKIE_CHECK_FAILURE  2
#define FAST_FAIL_CORRUPT_LIST_ENTRY          3
#define FAST_FAIL_INCORRECT_STACK             4
#define FAST_FAIL_INVALID_ARG                 5
#define FAST_FAIL_GS_COOKIE_INIT              6
#define FAST_FAIL_FATAL_APP_EXIT              7
#define FAST_FAIL_RANGE_CHECK_FAILURE         8
#define FAST_FAIL_UNSAFE_REGISTRY_ACCESS      9
#define FAST_FAIL_GUARD_ICALL_CHECK_FAILURE   10
#define FAST_FAIL_GUARD_WRITE_CHECK_FAILURE   11
#define FAST_FAIL_INVALID_FIBER_SWITCH        12
#define FAST_FAIL_INVALID_SET_OF_CONTEXT      13
#define FAST_FAIL_INVALID_REFERENCE_COUNT     14
#define FAST_FAIL_INVALID_JUMP_BUFFER         18
#define FAST_FAIL_MRDATA_MODIFIED             19
#define FAST_FAIL_CERTIFICATION_FAILURE       20
#define FAST_FAIL_INVALID_EXCEPTION_CHAIN     21
#define FAST_FAIL_CRYPTO_LIBRARY              22
#define FAST_FAIL_INVALID_CALL_IN_DLL_CALLOUT 23
#define FAST_FAIL_INVALID_IMAGE_BASE          24
#define FAST_FAIL_DLOAD_PROTECTION_FAILURE    25
#define FAST_FAIL_UNSAFE_EXTENSION_CALL       26
#define FAST_FAIL_DEPRECATED_SERVICE_INVOKED  27
#define FAST_FAIL_INVALID_BUFFER_ACCESS       28
#define FAST_FAIL_INVALID_BALANCED_TREE       29
#define FAST_FAIL_INVALID_FAST_FAIL_CODE      0xFFFFFFFF

#if defined(_M_IX86)
# define DbgRaiseAssertionFailure() __int2c()
#elif defined(_M_AMD64)
# define DbgRaiseAssertionFailure() __int2c()
#elif defined(_M_IA64)
# define BREAK_DEBUG_BASE 0x080000
# define ASSERT_BREAKPOINT (BREAK_DEBUG_BASE + 3)
# define DbgRaiseAssertionFailure() __break(ASSERT_BREAKPOINT)
#elif defined(_M_ARM)
# define DbgRaiseAssertionFailure() __emit(0xdefc)
#elif defined(_M_ARM64)
# define DbgRaiseAssertionFailure() __break(0xf001)
#endif

#if defined(_MSC_VER)
# define __assert_annotationA(msg) __annotation(L"Debug", L"AssertFail", L ## msg)
# define __assert_annotationW(msg) __annotation(L"Debug", L"AssertFail", msg)
#else
# define __assert_annotationA(msg) \
    DbgPrint("Assertion failed at %s(%d): %s\n", __FILE__, __LINE__, msg)
# define __assert_annotationW(msg) \
    DbgPrint("Assertion failed at %s(%d): %S\n", __FILE__, __LINE__, msg)
#endif

#ifdef _PREFAST_
# define NT_ANALYSIS_ASSUME(_exp) _Analysis_assume_(_exp)
#elif DBG
# define NT_ANALYSIS_ASSUME(_exp) ((void)0)
#else
# define NT_ANALYSIS_ASSUME(_exp) __noop(_exp)
#endif

#define NT_ASSERT_ACTION(exp) \
   (NT_ANALYSIS_ASSUME(exp), \
   ((!(exp)) ? \
      (__assert_annotationA(#exp), \
       DbgRaiseAssertionFailure(), FALSE) : TRUE))

#define NT_ASSERTMSG_ACTION(msg, exp) \
   (NT_ANALYSIS_ASSUME(exp), \
   ((!(exp)) ? \
      (__assert_annotationA(msg), \
       DbgRaiseAssertionFailure(), FALSE) : TRUE))

#define NT_ASSERTMSGW_ACTION(msg, exp) \
   (NT_ANALYSIS_ASSUME(exp), \
   ((!(exp)) ? \
      (__assert_annotationW(msg), \
       DbgRaiseAssertionFailure(), FALSE) : TRUE))

#if DBG

#define RTL_VERIFY(exp) \
  ((!(exp)) ? \
    RtlAssert( (PVOID)#exp, (PVOID)__FILE__, __LINE__, NULL ), FALSE : TRUE)

#define RTL_VERIFYMSG(msg, exp) \
  ((!(exp)) ? \
    RtlAssert( (PVOID)#exp, (PVOID)__FILE__, __LINE__, (PCHAR)msg ), FALSE : TRUE)

#define RTL_SOFT_VERIFY(exp) \
  ((!(exp)) ? \
    DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n", __FILE__, __LINE__, #exp), FALSE : TRUE)

#define RTL_SOFT_VERIFYMSG(msg, exp) \
  ((!(exp)) ? \
    DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n   Message: %s\n", __FILE__, __LINE__, #exp, (msg)), FALSE : TRUE)

/* The ASSERTs must be cast to void to avoid warnings about unused results. */
#define ASSERT                 (void)RTL_VERIFY
#define ASSERTMSG              (void)RTL_VERIFYMSG
#define RTL_SOFT_ASSERT        (void)RTL_SOFT_VERIFY
#define RTL_SOFT_ASSERTMSG     (void)RTL_SOFT_VERIFYMSG

#define NT_VERIFY              NT_ASSERT_ACTION
#define NT_VERIFYMSG           NT_ASSERTMSG_ACTION
#define NT_VERIFYMSGW          NT_ASSERTMSGW_ACTION

#define NT_ASSERT_ASSUME       (void)NT_ASSERT_ACTION
#define NT_ASSERTMSG_ASSUME    (void)NT_ASSERTMSG_ACTION
#define NT_ASSERTMSGW_ASSUME   (void)NT_ASSERTMSGW_ACTION

#define NT_ASSERT_NOASSUME     (void)NT_ASSERT_ACTION
#define NT_ASSERTMSG_NOASSUME  (void)NT_ASSERTMSG_ACTION
#define NT_ASSERTMSGW_NOASSUME (void)NT_ASSERTMSGW_ACTION

#else /* !DBG */

#define ASSERT(exp)                  ((void)0)
#define ASSERTMSG(msg, exp)          ((void)0)

#define RTL_SOFT_ASSERT(exp)         ((void)0)
#define RTL_SOFT_ASSERTMSG(msg, exp) ((void)0)

#define RTL_VERIFY(exp)              ((exp) ? TRUE : FALSE)
#define RTL_VERIFYMSG(msg, exp)      ((exp) ? TRUE : FALSE)

#define RTL_SOFT_VERIFY(exp)         ((exp) ? TRUE : FALSE)
#define RTL_SOFT_VERIFYMSG(msg, exp) ((exp) ? TRUE : FALSE)

#define NT_VERIFY(exp)          (NT_ANALYSIS_ASSUME(exp), ((exp) ? TRUE : FALSE))
#define NT_VERIFYMSG(msg, exp)  (NT_ANALYSIS_ASSUME(exp), ((exp) ? TRUE : FALSE))
#define NT_VERIFYMSGW(msg, exp) (NT_ANALYSIS_ASSUME(exp), ((exp) ? TRUE : FALSE))

#define NT_ASSERT_ASSUME(exp)          (NT_ANALYSIS_ASSUME(exp), (void)0)
#define NT_ASSERTMSG_ASSUME(msg, exp)  (NT_ANALYSIS_ASSUME(exp), (void)0)
#define NT_ASSERTMSGW_ASSUME(msg, exp) (NT_ANALYSIS_ASSUME(exp), (void)0)

#define NT_ASSERT_NOASSUME(exp)          ((void)0)
#define NT_ASSERTMSG_NOASSUME(msg, exp)  ((void)0)
#define NT_ASSERTMSGW_NOASSUME(msg, exp) ((void)0)

#endif /* DBG */

#define NT_FRE_ASSERT     (void)NT_ASSERT_ACTION
#define NT_FRE_ASSERTMSG  (void)NT_ASSERTMSG_ACTION
#define NT_FRE_ASSERTMSGW (void)NT_ASSERTMSGW_ACTION

#ifdef NT_ASSERT_ALWAYS_ASSUMES
# define NT_ASSERT NT_ASSERT_ASSUME
# define NT_ASSERTMSG NT_ASSERTMSG_ASSUME
# define NT_ASSERTMSGW NT_ASSERTMSGW_ASSUME
#else
# define NT_ASSERT NT_ASSERT_NOASSUME
# define NT_ASSERTMSG NT_ASSERTMSG_NOASSUME
# define NT_ASSERTMSGW NT_ASSERTMSGW_NOASSUME
#endif /* NT_ASSERT_ALWAYS_ASSUMES */

#if defined(_MSC_VER) && (defined(__REACTOS__) || defined(ASSERT_ALWAYS_NT_ASSERT))
#undef ASSERT
#define ASSERT NT_ASSERT
#undef ASSERTMSG
#define ASSERTMSG NT_ASSERT
#undef ASSERTMSGW
#define ASSERTMSGW NT_ASSERTMSGW
#undef RTL_VERIFY
#define RTL_VERIFY NT_VERIFY
#endif
