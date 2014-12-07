
#pragma once

#undef NTDDI_VERSION
#define NTDDI_VERSION NTDDI_WIN10
#include <excpt.h>
#include <ntdef.h>
#include <ntstatus.h>
#include <intrin.h>
#include <pseh/pseh2.h>

/* Use C++ types */
#ifdef __cplusplus
#undef TRUE
#define TRUE true
#undef FALSE
#define FALSE false
#define BOOLEAN bool
#undef NULL
#define NULL nullptr
#endif // __cplusplus

/* Fix inline on GCC */
#ifdef __GNUC__
#undef __forceinline
#define __forceinline inline __attribute__((always_inline))
#endif // __GNUC__

#define DECLSPEC_NORETURN __declspec(noreturn)

#define NTKERNELAPI
#define NTHALAPI
#define _DECL_HAL_KE_IMPORT DECLSPEC_IMPORT
#define INIT_FUNCTION

#include <debug.h>
#include <probe.h>
#include <list.h>
#include <interlocked.h>

// ntosp.h
#ifdef _PREFAST_
#define __string_type 0x1000
#define __guid_type 0x2000
#define __multiString_type 0x4000
#else
#define __string_type 0
#define __guid_type 0
#define __multiString_type 0
#endif

// FIXME: should go to specstrings.h
#define __volatile
#define _Frees_ptr_opt_

#if defined(_M_IX86)
# define ExInterlockedAddLargeStatistic(Addend, Increment) \
    (VOID)_InterlockedAddLargeStatistic((PLONGLONG)&(Addend)->QuadPart, Increment)
#else
# define ExInterlockedAddLargeStatistic(Addend, Increment) \
    (VOID)InterlockedAddNoFence64(&(Addend)->QuadPart, Increment)
#endif

#ifdef __cplusplus
//extern "C" {
#endif // __cplusplus

#define RtlEqualMemory(Destination,Source,Length) (!memcmp((Destination),(Source),(Length)))
#define RtlMoveMemory(Destination,Source,Length) memmove((Destination),(Source),(Length))
#define RtlCopyMemory(Destination,Source,Length) memcpy((Destination),(Source),(Length))
#define RtlFillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))

#undef GetExceptionCode
#define GetExceptionCode() ((NTSTATUS)_exception_code())

#ifndef _MSC_VER
#define __try _SEH3_TRY
#define __except _SEH3_EXCEPT
#define __finally _SEH3_FINALLY
#define __endtry _SEH3_END
#else
#define __endtry
#endif // _MSC_VER

#define _Enum_is_bitflag_

FORCEINLINE
struct _KPROCESS*
NTAPI
_KeGetCurrentProcess (
    VOID)
{
    return 0;
}
#define KeGetCurrentProcess _KeGetCurrentProcess

#ifdef __cplusplus
//}; // extern "C"
#endif // __cplusplus

#define PsGetCurrentProcess() ((PEPROCESS)KeGetCurrentProcess())

#define YieldProcessor()
#define PAGE_SIZE 0x1000

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef ULONG ACCESS_MASK, *PACCESS_MASK;

#ifdef __cplusplus

inline
void*
operator new (
    _In_ size_t Size) throw()
{
    __debugbreak();
    return 0;
}

inline
void*
operator new (
    _In_ size_t Size,
    _In_ void *Pointer) throw()
{
    return Pointer;
}

#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#ifdef __cplusplus
};
#endif // __cplusplus
