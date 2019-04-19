
#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* Hardware Lock Elision (HLE) */
long _InterlockedCompareExchange_HLEAcquire(long volatile *,long,long);
long _InterlockedCompareExchange_HLERelease(long volatile *,long,long);
__int64 _InterlockedCompareExchange64_HLEAcquire(__int64 volatile *,__int64,__int64);
__int64 _InterlockedCompareExchange64_HLERelease(__int64 volatile *,__int64,__int64);
void *_InterlockedCompareExchangePointer_HLEAcquire(void *volatile *,void *,void *);
void *_InterlockedCompareExchangePointer_HLERelease(void *volatile *,void *,void *);
long _InterlockedExchangeAdd_HLEAcquire(long volatile *,long);
long _InterlockedExchangeAdd_HLERelease(long volatile *,long);
__int64 _InterlockedExchangeAdd64_HLEAcquire(__int64 volatile *,__int64);
__int64 _InterlockedExchangeAdd64_HLERelease(__int64 volatile *,__int64);
void _Store_HLERelease(long volatile *,long);
void _Store64_HLERelease(__int64 volatile *,__int64);
void _StorePointer_HLERelease(void * volatile *,void *);

/*  Restricted Transactional Memory (RTM) */
unsigned __int32 _xbegin(void);
void _xend(void);
void _xabort(const unsigned int imm);
#define _XBEGIN_STARTED   (~0u)
#define _XABORT_EXPLICIT  (1 << 0)
#define _XABORT_RETRY     (1 << 1)
#define _XABORT_CONFLICT  (1 << 2)
#define _XABORT_CAPACITY  (1 << 3)
#define _XABORT_DEBUG     (1 << 4)
#define _XABORT_NESTED    (1 << 5)
#define _XABORT_CODE(x)   ((uint8_t)(((x) >> 24) & 0xFF))

#ifdef _MSC_VER
#pragma intrinsic(_xbegin)
#pragma intrinsic(_xend)
#pragma intrinsic(_xabort)
#else
#endif

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus
