/*
 * PROJECT:         ReactOS kernel-mode tests
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         Kernel-Mode Test Suite Interlocked function test
 * PROGRAMMER:      Thomas Faber <thomas.faber@reactos.org>
 *                  Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#include <stddef.h>
#include <kmt_test.h>

/* We do not want to test the macros/intrinsics, but the exported functions */
#undef InterlockedCompareExchange
#undef ExInterlockedCompareExchange64
#undef ExfInterlockedCompareExchange64
#undef InterlockedExchange
#undef ExInterlockedExchangeUlong
#undef InterlockedExchangeAdd
#undef ExInterlockedAddUlong
#undef Exi386InterlockedExchangeUlong
#undef InterlockedIncrement
#undef InterlockedDecrement
#undef ExInterlockedIncrementLong
#undef ExInterlockedDecrementLong
#undef Exi386InterlockedIncrementLong
#undef Exi386InterlockedDecrementLong
#undef InterlockedXor
#undef ExInterlockedAddLargeStatistic

/* missing prototypes >:| */
#ifdef _X86_
__declspec(dllimport)   long            __fastcall  InterlockedCompareExchange(volatile long *, long, long);
__declspec(dllimport)   __int64         __fastcall  ExInterlockedCompareExchange64(volatile __int64 *, __int64 *, __int64 *, void *);
__declspec(dllimport)   __int64         __fastcall  ExfInterlockedCompareExchange64(volatile __int64 *, __int64 *, __int64 *);
__declspec(dllimport)   long            __fastcall  InterlockedExchange(volatile long *, long);
__declspec(dllimport)   unsigned long   __stdcall   ExInterlockedExchangeUlong(unsigned long *, unsigned long, void *);
__declspec(dllimport)   long            __fastcall  InterlockedExchangeAdd(volatile long *, long);
__declspec(dllimport)   unsigned long   __stdcall   ExInterlockedAddUlong(unsigned long *, unsigned long, unsigned long *);
__declspec(dllimport)   unsigned long   __stdcall   Exi386InterlockedExchangeUlong(unsigned long *, unsigned long);
__declspec(dllimport)   long            __fastcall  InterlockedIncrement(long *);
__declspec(dllimport)   long            __fastcall  InterlockedDecrement(long *);
__declspec(dllimport)   int             __stdcall   ExInterlockedIncrementLong(long *, void *);
__declspec(dllimport)   int             __stdcall   ExInterlockedDecrementLong(long *, void *);
__declspec(dllimport)   int             __stdcall   Exi386InterlockedIncrementLong(long *);
__declspec(dllimport)   int             __stdcall   Exi386InterlockedDecrementLong(long *);
__declspec(dllimport)   void            __fastcall  ExInterlockedAddLargeStatistic(LARGE_INTEGER *, ULONG);
#endif


/* TODO: stress-testing */

static KSPIN_LOCK SpinLock;






#define CheckInterlockedCmpXchg(Function, Type, Fc, Print, Val, Cmp, Xchg,  \
                                ExpectedValue, ExpectedRet) do              \
{                                                                           \
    Type Ret##Type = 0;                                                     \
    Type Value##Type = Val;                                                 \
    CALL_WRAPPER(&Ret##Type, Type, Fc, Function, &Value##Type, Xchg, Cmp);  \
    ok_eq_print(Ret##Type, ExpectedRet, Print);                             \
    ok_eq_print(Value##Type, ExpectedValue, Print);                         \
} while (0)

#define CheckInterlockedCmpXchgI(Function, Type, Fc, Print, Val, Cmp, Xchg, \
                                ExpectedValue, ExpectedRet, ...) do         \
{                                                                           \
    Type Ret##Type = 0;                                                     \
    Type Value##Type = Val;                                                 \
    Type Compare##Type = Cmp;                                               \
    Type Exchange##Type = Xchg;                                             \
    CALL_WRAPPER(&Ret##Type, Type, Fc, Function, &Value##Type,              \
                 &Exchange##Type, &Compare##Type, ##__VA_ARGS__);           \
    ok_eq_print(Ret##Type, ExpectedRet, Print);                             \
    ok_eq_print(Value##Type, ExpectedValue, Print);                         \
    ok_eq_print(Exchange##Type, Xchg, Print);                               \
    ok_eq_print(Compare##Type, Cmp, Print);                                 \
} while(0)

#define CheckInterlockedOp(Function, Type, Fc, Print, Val, Op,              \
                                ExpectedValue, ExpectedRet, ...) do         \
{                                                                           \
    Type Ret##Type = 0;                                                     \
    Type Value##Type = Val;                                                 \
    CALL_WRAPPER(&Ret##Type, Type, Fc, Function,                            \
                 &Value##Type, Op, ##__VA_ARGS__);                          \
    ok_eq_print(Ret##Type, ExpectedRet, Print);                             \
    ok_eq_print(Value##Type, ExpectedValue, Print);                         \
} while (0)

#define CheckInterlockedOpNoArg(Function, Type, Fc, Print, Val,             \
                                ExpectedValue, ExpectedRet, ...) do         \
{                                                                           \
    Type Ret##Type = 0;                                                     \
    Type Value##Type = Val;                                                 \
    CALL_WRAPPER(&Ret##Type, Type, Fc, Function,                            \
                 &Value##Type, ##__VA_ARGS__);                              \
    ok_eq_print(Ret##Type, ExpectedRet, Print);                             \
    ok_eq_print(Value##Type, ExpectedValue, Print);                         \
} while (0)

#define CheckInterlockedOpLarge(Function, Type, Fc, Print, Val, Op,         \
                                ExpectedValue, ExpectedRet, ...) do         \
{                                                                           \
    Type Ret##Type = Large(0);                                              \
    Type Value##Type = Val;                                                 \
    CALL_WRAPPER(&Ret##Type, Type, Fc, Function,                            \
                 &Value##Type, Op, ##__VA_ARGS__);                          \
    ok_eq_print(Ret##Type.QuadPart, ExpectedRet, Print);                    \
    ok_eq_print(Value##Type.QuadPart, ExpectedValue, Print);                \
} while (0)

#define CheckInterlockedOpLargeNoRet(Function, Type, Fc, Print, Val, Op,    \
                                ExpectedValue) do                           \
{                                                                           \
    Type Ret##Type;                                                         \
    Type Value##Type = Val;                                                 \
    CALL_WRAPPER(&Ret##Type, Type, Fc, Function,                            \
                 &Value##Type, Op);                                         \
    ok_eq_print(Value##Type.QuadPart, ExpectedValue, Print);                \
} while (0)

static
VOID
TestInterlockedFunctional(VOID)
{
    PKSPIN_LOCK pSpinLock = &SpinLock;
    CONTEXT PreContext, PostContext;

    /* on x86, most of these are supported intrinsically and don't need a spinlock! */
#if defined _M_IX86 || defined _M_AMD64
    pSpinLock = NULL;
#endif

    /* CompareExchange */
#ifdef _M_IX86
    CheckInterlockedCmpXchg(InterlockedCompareExchange, LONG, 1, "%ld", 5, 6, 8, 5L, 5L);
    CheckInterlockedCmpXchg(InterlockedCompareExchange, LONG, 1, "%ld", 5, 5, 9, 9L, 5L);
    /* exported function */
    CheckInterlockedCmpXchgI((ExInterlockedCompareExchange64), LONGLONG, 1, "%I64d", 17, 4LL, 20LL, 17LL, 17LL, pSpinLock);
    CheckInterlockedCmpXchgI((ExInterlockedCompareExchange64), LONGLONG, 1, "%I64d", 17, 17LL, 21LL, 21LL, 17LL, pSpinLock);
    /* fastcall version */
    CheckInterlockedCmpXchgI(ExfInterlockedCompareExchange64, LONGLONG, 1, "%I64d", 17, 4LL, 20LL, 17LL, 17LL);
    CheckInterlockedCmpXchgI(ExfInterlockedCompareExchange64, LONGLONG, 1, "%I64d", 17, 17LL, 21LL, 21LL, 17LL);
#endif

    /* Exchange */
#ifdef _M_IX86
    CheckInterlockedOp(InterlockedExchange, LONG, 1, "%ld", 5, 8, 8L, 5L);
    CheckInterlockedOp(ExInterlockedExchangeUlong, ULONG, 0, "%lu", 212, 121, 121LU, 212LU, pSpinLock);
    CheckInterlockedOp((ExInterlockedExchangeUlong), ULONG, 0, "%lu", 212, 121, 121LU, 212LU, pSpinLock);
    CheckInterlockedOp(Exi386InterlockedExchangeUlong, ULONG, 0, "%lu", 212, 121, 121LU, 212LU);
    CheckInterlockedOp(Exfi386InterlockedExchangeUlong, ULONG, 1, "%lu", 212, 121, 121LU, 212LU);
#endif

    /* ExchangeAdd */
#ifdef _M_IX86
    CheckInterlockedOp(InterlockedExchangeAdd, LONG, 1, "%ld", 312, 7, 319L, 312L);
#endif

    /* Add */
    /* these DO need a valid spinlock even on x86 */
    /* Note the "trick", passing one additional parameter to the macro.
       This is because we have a LARGE_INTEGER, which is 2 parameters on x86 */
    CheckInterlockedOpLarge(ExInterlockedAddLargeInteger, LARGE_INTEGER, 0, "%I64d", Large(23), Large(7), 30LL, 23LL, &SpinLock, 0);
#ifdef _M_IX86
    CheckInterlockedOpLargeNoRet(ExInterlockedAddLargeStatistic, LARGE_INTEGER, 1, "%I64d", Large(15), 17LL, 32LL);
    CheckInterlockedOp(ExfInterlockedAddUlong, ULONG, 0, "%lu", 239, 44, 283LU, 239LU, &SpinLock);
#endif
    CheckInterlockedOp(ExInterlockedAddUlong, ULONG, 0, "%lu", 239, 44, 283LU, 239LU, &SpinLock);

    /* Increment */
#if 0
    CheckInterlockedOpNoArg(InterlockedIncrementAcquire, LONG, 0, "%ld", 2341L, 2342L, 2342L);
    CheckInterlockedOpNoArg(InterlockedIncrementRelease, LONG, 0, "%ld", 2341L, 2342L, 2342L);
#endif
#ifdef _M_IX86
    CheckInterlockedOpNoArg(InterlockedIncrement, LONG, 1, "%ld", 2341L, 2342L, 2342L);
    CheckInterlockedOpNoArg(InterlockedIncrement, LONG, 1, "%ld", (LONG)MAXLONG, (LONG)MINLONG, (LONG)MINLONG);
    CheckInterlockedOpNoArg(ExInterlockedIncrementLong, LONG, 0, "%ld", -2L, -1L, (LONG)ResultNegative, pSpinLock);
    CheckInterlockedOpNoArg(ExInterlockedIncrementLong, LONG, 0, "%ld", -1L, 0L, (LONG)ResultZero, pSpinLock);
    CheckInterlockedOpNoArg(ExInterlockedIncrementLong, LONG, 0, "%ld", 0L, 1L, (LONG)ResultPositive, pSpinLock);
    CheckInterlockedOpNoArg(ExInterlockedIncrementLong, LONG, 0, "%ld", (LONG)MAXLONG, (LONG)MINLONG, (LONG)ResultNegative, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedIncrementLong), LONG, 0, "%ld", -2L, -1L, (LONG)ResultNegative, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedIncrementLong), LONG, 0, "%ld", -1L, 0L, (LONG)ResultZero, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedIncrementLong), LONG, 0, "%ld", 0L, 1L, (LONG)ResultPositive, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedIncrementLong), LONG, 0, "%ld", (LONG)MAXLONG, (LONG)MINLONG, (LONG)ResultNegative, pSpinLock);
    CheckInterlockedOpNoArg(Exi386InterlockedIncrementLong, LONG, 0, "%ld", -2L, -1L, (LONG)ResultNegative);
    CheckInterlockedOpNoArg(Exi386InterlockedIncrementLong, LONG, 0, "%ld", -1L, 0L, (LONG)ResultZero);
    CheckInterlockedOpNoArg(Exi386InterlockedIncrementLong, LONG, 0, "%ld", 0L, 1L, (LONG)ResultPositive);
    CheckInterlockedOpNoArg(Exi386InterlockedIncrementLong, LONG, 0, "%ld", (LONG)MAXLONG, (LONG)MINLONG, (LONG)ResultNegative);
    CheckInterlockedOpNoArg(Exfi386InterlockedIncrementLong, LONG, 0, "%ld", -2L, -1L, (LONG)ResultNegative);
    CheckInterlockedOpNoArg(Exfi386InterlockedIncrementLong, LONG, 0, "%ld", -1L, 0L, (LONG)ResultZero);
    CheckInterlockedOpNoArg(Exfi386InterlockedIncrementLong, LONG, 0, "%ld", 0L, 1L, (LONG)ResultPositive);
    CheckInterlockedOpNoArg(Exfi386InterlockedIncrementLong, LONG, 0, "%ld", (LONG)MAXLONG, (LONG)MINLONG, (LONG)ResultNegative);
#endif

    /* Decrement */
#if 0 // Who implements these?
    CheckInterlockedOpNoArg(InterlockedDecrementAcquire, LONG, 0, "%ld", 1745L, 1744L, 1744L);
    CheckInterlockedOpNoArg(InterlockedDecrementRelease, LONG, 0, "%ld", 1745L, 1744L, 1744L);
#endif
#ifdef _M_IX86
    CheckInterlockedOpNoArg(InterlockedDecrement, LONG, 1, "%ld", 1745L, 1744L, 1744L);
    CheckInterlockedOpNoArg(InterlockedDecrement, LONG, 1, "%ld", (LONG)MINLONG, (LONG)MAXLONG, (LONG)MAXLONG);
    CheckInterlockedOpNoArg(ExInterlockedDecrementLong, LONG, 0, "%ld", (LONG)MINLONG, (LONG)MAXLONG, (LONG)ResultPositive, pSpinLock);
    CheckInterlockedOpNoArg(ExInterlockedDecrementLong, LONG, 0, "%ld", 0L, -1L, (LONG)ResultNegative, pSpinLock);
    CheckInterlockedOpNoArg(ExInterlockedDecrementLong, LONG, 0, "%ld", 1L, 0L, (LONG)ResultZero, pSpinLock);
    CheckInterlockedOpNoArg(ExInterlockedDecrementLong, LONG, 0, "%ld", 2L, 1L, (LONG)ResultPositive, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedDecrementLong), LONG, 0, "%ld", (LONG)MINLONG, (LONG)MAXLONG, (LONG)ResultPositive, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedDecrementLong), LONG, 0, "%ld", 0L, -1L, (LONG)ResultNegative, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedDecrementLong), LONG, 0, "%ld", 1L, 0L, (LONG)ResultZero, pSpinLock);
    CheckInterlockedOpNoArg((ExInterlockedDecrementLong), LONG, 0, "%ld", 2L, 1L, (LONG)ResultPositive, pSpinLock);
    CheckInterlockedOpNoArg(Exi386InterlockedDecrementLong, LONG, 0, "%ld", (LONG)MINLONG, (LONG)MAXLONG, (LONG)ResultPositive);
    CheckInterlockedOpNoArg(Exi386InterlockedDecrementLong, LONG, 0, "%ld", 0L, -1L, (LONG)ResultNegative);
    CheckInterlockedOpNoArg(Exi386InterlockedDecrementLong, LONG, 0, "%ld", 1L, 0L, (LONG)ResultZero);
    CheckInterlockedOpNoArg(Exi386InterlockedDecrementLong, LONG, 0, "%ld", 2L, 1L, (LONG)ResultPositive);
    CheckInterlockedOpNoArg(Exfi386InterlockedDecrementLong, LONG, 0, "%ld", (LONG)MINLONG, (LONG)MAXLONG, (LONG)ResultPositive, pSpinLock);
    CheckInterlockedOpNoArg(Exfi386InterlockedDecrementLong, LONG, 0, "%ld", 0L, -1L, (LONG)ResultNegative);
    CheckInterlockedOpNoArg(Exfi386InterlockedDecrementLong, LONG, 0, "%ld", 1L, 0L, (LONG)ResultZero);
    CheckInterlockedOpNoArg(Exfi386InterlockedDecrementLong, LONG, 0, "%ld", 2L, 1L, (LONG)ResultPositive);
#endif
}

START_TEST(ExInterlocked)
{
    KIRQL Irql;
    KeInitializeSpinLock(&SpinLock);

    /* functional testing */
    TestInterlockedFunctional();
    KeRaiseIrql(HIGH_LEVEL, &Irql);
    TestInterlockedFunctional();
    KeLowerIrql(Irql);
}
