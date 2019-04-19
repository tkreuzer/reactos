
#pragma once

#include <intrin.h>

#ifndef CFORCEINLINE
#define CFORCEINLINE __forceinline
#endif // CFORCEINLINE

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

#ifdef _M_IX86
__forceinline
void
MemoryBarrier (
    void)
{
    long Barrier;
    _InterlockedOr(&Barrier, 0);
}
#define _AcquireBarrier()
#define _ReleaseBarrier()
#define PreFetchCacheLine(l, a)               _mm_prefetch((char const *) a, l)
#define PrefetchForWrite(p)
#define ReadForWriteAccess(p)                 (*(p))
#elif defined(_M_AMD64)
#define MemoryBarrier                         __faststorefence
#define _AcquireBarrier()
#define _ReleaseBarrier()
#define PreFetchCacheLine(l, a)               _mm_prefetch((char const *) a, l)
#define PrefetchForWrite(p)                   _m_prefetchw(p)
#define ReadForWriteAccess(p)                 (_m_prefetchw(p), *(p))
#elif defined(_M_ARM)
# define MemoryBarrier()                      __dmb(_ARM_BARRIER_SY)
# define _AcquireBarrier()                    __dmb(_ARM_BARRIER_ISH);
# define _ReleaseBarrier()                    __dmb(_ARM_BARRIER_ISH);
# define _DataSynchronizationBarrier()        __dsb(_ARM_BARRIER_SY)
# define _InstructionSynchronizationBarrier() __isb(_ARM_BARRIER_SY)
# define PreFetchCacheLine(l,a)               __prefetch((const void *) (a))
# define PrefetchForWrite(p)                  __prefetch((const void *) (p))
# define ReadForWriteAccess(p)                (*(p))
#elif defined(_M_ARM64)
# define MemoryBarrier()                      __dmb(_ARM64_BARRIER_SY)
# define _AcquireBarrier()                    __dmb(_ARM64_BARRIER_ISH);
# define _ReleaseBarrier()                    __dmb(_ARM64_BARRIER_ISH);
# define _DataSynchronizationBarrier()        __dsb(_ARM64_BARRIER_SY)
# define _InstructionSynchronizationBarrier() __isb(_ARM64_BARRIER_SY)
# define PreFetchCacheLine(l,a)               __prefetch((const void *) (a))
# define PrefetchForWrite(p)                  __prefetch((const void *) (p))
# define ReadForWriteAccess(p)                (*(p))
#endif /* _M_ARM */

__forceinline
char
ReadRaw8 (
    _In_ _Interlocked_operand_ char const volatile *Source)
{
    return *(char *)Source;
}

__forceinline
void
WriteRaw8 (
    _Out_ _Interlocked_operand_ char volatile *Destination,
    _In_ char Value)
{
    *(char *)Destination = Value;
}

__forceinline
short
ReadRaw16 (
    _In_ _Interlocked_operand_ short const volatile *Source)
{
    return *(short *)Source;
}

__forceinline
void
WriteRaw16 (
    _Out_ _Interlocked_operand_ short volatile *Destination,
    _In_ short Value)
{
    *(short *)Destination = Value;
}

__forceinline
long
ReadRaw (
    _In_ _Interlocked_operand_ long const volatile *Source)
{
    return *(long *)Source;
}

__forceinline
void
WriteRaw (
    _Out_ _Interlocked_operand_ long volatile *Destination,
    _In_ long Value)
{
    *(long *)Destination = Value;
}

__forceinline
__int64
ReadRaw64 (
    _In_ _Interlocked_operand_ __int64 const volatile *Source)
{
    return *(__int64 *)Source;
}

__forceinline
void
WriteRaw64 (
    _Out_ _Interlocked_operand_ __int64 volatile *Destination,
    _In_ __int64 Value)
{
    *(__int64 *)Destination = Value;
}

#if defined(_M_IX86) || defined(_M_AMD64)

__forceinline
char
ReadNoFence8 (
    _In_ _Interlocked_operand_ char const volatile *Source)
{
    return *Source;
}

__forceinline
void
WriteNoFence8 (
    _Out_ _Interlocked_operand_ char volatile *Destination,
    _In_ char Value)
{
    *Destination = Value;
}

__forceinline
short
ReadNoFence16 (
    _In_ _Interlocked_operand_ short const volatile *Source)
{
    return *Source;
}

__forceinline
void
WriteNoFence16 (
    _Out_ _Interlocked_operand_ short volatile *Destination,
    _In_ short Value)
{
    *Destination = Value;
}

__forceinline
long
ReadNoFence (
    _In_ _Interlocked_operand_ long const volatile *Source)
{
    return *Source;
}

__forceinline
void
WriteNoFence (
    _Out_ _Interlocked_operand_ long volatile *Destination,
    _In_ long Value)
{
    *Destination = Value;
}

__forceinline
__int64
ReadNoFence64 (
    _In_ _Interlocked_operand_ __int64 const volatile *Source)
{
    return *Source;
}

__forceinline
void
WriteNoFence64 (
    _Out_ _Interlocked_operand_ __int64 volatile *Destination,
    _In_ __int64 Value)
{
    *Destination = Value;
}

#elif defined(_M_ARM) || defined(_M_ARM64)

__forceinline
char
ReadNoFence8 (
    _In_ _Interlocked_operand_ char const volatile *Source)
{
    return __iso_volatile_load8(Source);
}

__forceinline
void
WriteNoFence8 (
    _Out_ _Interlocked_operand_ char volatile *Destination,
    _In_ char Value)
{
    __iso_volatile_store8(Destination, Value);
}

__forceinline
short
ReadNoFence16 (
    _In_ _Interlocked_operand_ short const volatile *Source)
{
    return __iso_volatile_load16(Source);
}

__forceinline
void
WriteNoFence16 (
    _Out_ _Interlocked_operand_ short volatile *Destination,
    _In_ short Value)
{
    __iso_volatile_store16(Destination, Value);
}

__forceinline
long
ReadNoFence (
    _In_ _Interlocked_operand_ long const volatile *Source)
{
    return __iso_volatile_load32((int *)Source);
}

__forceinline
void
WriteNoFence (
    _Out_ _Interlocked_operand_ long volatile *Destination,
    _In_ long Value)
{
    __iso_volatile_store32((int *)Destination, Value);
}

__forceinline
__int64
ReadNoFence64 (
    _In_ _Interlocked_operand_ __int64 const volatile *Source)
{
    return __iso_volatile_load64(Source);
}

__forceinline
void
WriteNoFence64 (
    _Out_ _Interlocked_operand_ __int64 volatile *Destination,
    _In_ __int64 Value)
{
    __iso_volatile_store64(Destination, Value);
}

#else
#error Unknown architecture
#endif // defined

/////////////////////////////////

__forceinline
char
ReadAcquire8 (
    _In_ _Interlocked_operand_ char const volatile *Source)
{
    char Value = ReadNoFence8(Source);
    _AcquireBarrier();
    return Value;
}

__forceinline
void
WriteRelease8 (
    _Out_ _Interlocked_operand_ char volatile *Destination,
    _In_ char Value)
{
    _ReleaseBarrier();
    WriteNoFence8(Destination, Value);
}

__forceinline
short
ReadAcquire16 (
    _In_ _Interlocked_operand_ short const volatile *Source)
{
    short Value = ReadNoFence16(Source);
    _AcquireBarrier();
    return Value;
}

__forceinline
void
WriteRelease16 (
    _Out_ _Interlocked_operand_ short volatile *Destination,
    _In_ short Value)
{
    _ReleaseBarrier();
    WriteNoFence16(Destination, Value);
}

__forceinline
long
ReadAcquire (
    _In_ _Interlocked_operand_ long const volatile *Source)
{
    long Value = ReadNoFence(Source);
    _AcquireBarrier();
    return Value;
}

CFORCEINLINE // C__forceinline
void
WriteRelease (
    _Out_ _Interlocked_operand_ long volatile *Destination,
    _In_ long Value)
{
    _ReleaseBarrier();
    WriteNoFence(Destination, Value);
}

__forceinline
__int64
ReadAcquire64 (
    _In_ _Interlocked_operand_ __int64 const volatile *Source)
{
    __int64 Value = ReadNoFence64(Source);
    _AcquireBarrier();
    return Value;
}

C__forceinline
void
WriteRelease64 (
    _Out_ _Interlocked_operand_ __int64 volatile *Destination,
    _In_ __int64 Value)
{
    _ReleaseBarrier();
    WriteNoFence64(Destination, Value);
}

//////////////////////

__forceinline
unsigned char
ReadUCharAcquire (
    _In_ _Interlocked_operand_ unsigned char const volatile *Source)
{
    return (unsigned char)ReadAcquire8((Pchar)Source);
}

__forceinline
unsigned char
ReadUCharNoFence (
    _In_ _Interlocked_operand_ unsigned char const volatile *Source)
{
    return (unsigned char)ReadNoFence8((Pchar)Source);
}

__forceinline
unsigned char
ReadUCharRaw (
    _In_ _Interlocked_operand_ unsigned char const volatile *Source)
{
    return (unsigned char)ReadRaw8((Pchar)Source);
}

__forceinline
void
WriteUCharRelease (
    _Out_ _Interlocked_operand_ unsigned char volatile *Destination,
    _In_ unsigned char Value)
{
    WriteRelease8((Pchar)Destination, (char)Value);
}

__forceinline
void
WriteUCharNoFence (
    _Out_ _Interlocked_operand_ unsigned char volatile *Destination,
    _In_ unsigned char Value)
{
    WriteNoFence8((Pchar)Destination, (char)Value);
}

__forceinline
void
WriteUCharRaw (
    _Out_ _Interlocked_operand_ unsigned char volatile *Destination,
    _In_ unsigned char Value)
{
    WriteRaw8((Pchar)Destination, (char)Value);
}

__forceinline
unsigned char
ReadBooleanAcquire (
    _In_ _Interlocked_operand_ BOOLEAN const volatile *Source)
{
    return (BOOLEAN)ReadAcquire8((Pchar)Source);
}

__forceinline
unsigned char
ReadBooleanNoFence (
    _In_ _Interlocked_operand_ BOOLEAN const volatile *Source)
{
    return (BOOLEAN)ReadNoFence8((Pchar)Source);
}

__forceinline
void
WriteBooleanRelease (
    _Out_ _Interlocked_operand_ BOOLEAN volatile *Destination,
    _In_ BOOLEAN Value)
{
    WriteRelease8((Pchar)Destination, (char)Value);
}

__forceinline
void
WriteBooleanNoFence (
    _Out_ _Interlocked_operand_ BOOLEAN volatile *Destination,
    _In_ BOOLEAN Value)
{
    WriteNoFence8((Pchar)Destination, (char)Value);
}

__forceinline
unsigned short
ReadUShortAcquire (
    _In_ _Interlocked_operand_ unsigned short const volatile *Source)
{
    return (unsigned short)ReadAcquire16((Pshort)Source);
}

__forceinline
unsigned short
ReadUShortNoFence (
    _In_ _Interlocked_operand_ unsigned short const volatile *Source)
{
    return (unsigned short)ReadNoFence16((Pshort)Source);
}

__forceinline
unsigned short
ReadUShortRaw (
    _In_ _Interlocked_operand_ unsigned short const volatile *Source)
{
    return (unsigned short)ReadRaw16((Pshort)Source);
}

__forceinline
void
WriteUShortRelease (
    _Out_ _Interlocked_operand_ unsigned short volatile *Destination,
    _In_ unsigned short Value)
{
    WriteRelease16((Pshort)Destination, (short)Value);
}

__forceinline
void
WriteUShortNoFence (
    _Out_ _Interlocked_operand_ unsigned short volatile *Destination,
    _In_ unsigned short Value)
{
    WriteNoFence16((Pshort)Destination, (short)Value);
}

__forceinline
void
WriteUShortRaw (
    _Out_ _Interlocked_operand_ unsigned short volatile *Destination,
    _In_ unsigned short Value)
{
    WriteRaw16((Pshort)Destination, (short)Value);
}

__forceinline
unsigned long
ReadULongAcquire (
    _In_ _Interlocked_operand_ unsigned long const volatile *Source)
{
    return (unsigned long)ReadAcquire((Plong)Source);
}

__forceinline
unsigned long
ReadULongNoFence (
    _In_ _Interlocked_operand_ unsigned long const volatile *Source)
{
    return (unsigned long)ReadNoFence((Plong)Source);
}

__forceinline
unsigned long
ReadULongRaw (
    _In_ _Interlocked_operand_ unsigned long const volatile *Source)
{
    return (unsigned long)ReadRaw((Plong)Source);
}

__forceinline
void
WriteULongRelease (
    _Out_ _Interlocked_operand_ unsigned long volatile *Destination,
    _In_ unsigned long Value)
{
    WriteRelease((Plong)Destination, (long)Value);
}

__forceinline
void
WriteULongNoFence (
    _Out_ _Interlocked_operand_ unsigned long volatile *Destination,
    _In_ unsigned long Value)
{
    WriteNoFence((Plong)Destination, (long)Value);
}

__forceinline
void
WriteULongRaw (
    _Out_ _Interlocked_operand_ unsigned long volatile *Destination,
    _In_ unsigned long Value)
{
    WriteRaw((Plong)Destination, (long)Value);
}

__forceinline
unsigned __int64
ReadULong64Acquire (
    _In_ _Interlocked_operand_ unsigned __int64 const volatile *Source)
{
    return (unsigned __int64)ReadAcquire64((P__int64)Source);
}

__forceinline
unsigned __int64
ReadULong64NoFence (
    _In_ _Interlocked_operand_ unsigned __int64 const volatile *Source)
{
    return (unsigned __int64)ReadNoFence64((P__int64)Source);
}

__forceinline
unsigned __int64
ReadULong64Raw (
    _In_ _Interlocked_operand_ unsigned __int64 const volatile *Source)
{
    return (unsigned __int64)ReadRaw64((P__int64)Source);
}

__forceinline
void
WriteULong64Release (
    _Out_ _Interlocked_operand_ unsigned __int64 volatile *Destination,
    _In_ unsigned __int64 Value)
{
    WriteRelease64((P__int64)Destination, (__int64)Value);
}

__forceinline
void
WriteULong64NoFence (
    _Out_ _Interlocked_operand_ unsigned __int64 volatile *Destination,
    _In_ unsigned __int64 Value)
{
    WriteNoFence64((P__int64)Destination, (__int64)Value);
}

__forceinline
void
WriteULong64Raw (
    _Out_ _Interlocked_operand_ unsigned __int64 volatile *Destination,
    _In_ unsigned __int64 Value)
{
    WriteRaw64((P__int64)Destination, (__int64)Value);
}

#ifdef _WIN64

__forceinline
Pvoid
ReadPointerAcquire (
    _In_ _Interlocked_operand_ Pvoid const volatile *Source)
{
    return (Pvoid)ReadAcquire64((P__int64)Source);
}

__forceinline
Pvoid
ReadPointerNoFence (
    _In_ _Interlocked_operand_ Pvoid const volatile *Source)
{
    return (Pvoid)ReadNoFence64((P__int64)Source);
}

__forceinline
Pvoid
ReadPointerRaw (
    _In_ _Interlocked_operand_ Pvoid const volatile *Source)
{
    return (Pvoid)ReadRaw64((P__int64)Source);
}

__forceinline
void
WritePointerRelease (
    _Out_ _Interlocked_operand_ Pvoid volatile *Destination,
    _In_ Pvoid Value)
{
    WriteRelease64((P__int64)Destination, (__int64)Value);
}

__forceinline
void
WritePointerNoFence (
    _Out_ _Interlocked_operand_ Pvoid volatile *Destination,
    _In_ Pvoid Value)
{
    WriteNoFence64((P__int64)Destination, (__int64)Value);
}

__forceinline
void
WritePointerRaw (
    _Out_ _Interlocked_operand_ Pvoid volatile *Destination,
    _In_ Pvoid Value)
{
    WriteRaw64((P__int64)Destination, (__int64)Value);
}

#define ReadLongPtrAcquire ReadAcquire64
#define ReadLongPtrNoFence ReadNoFence64
#define ReadLongPtrRaw ReadRaw64
#define WriteLongPtrRelease WriteRelease64
#define WriteLongPtrNoFence WriteNoFence64
#define WriteLongPtrRaw WriteRaw64
#define ReadULongPtrAcquire ReadULong64Acquire
#define ReadULongPtrNoFence ReadULong64NoFence
#define ReadULongPtrRaw ReadULong64Raw
#define WriteULongPtrRelease WriteULong64Release
#define WriteULongPtrNoFence WriteULong64NoFence
#define WriteULongPtrRaw WriteULong64Raw

#else

__forceinline
void*
ReadPointerAcquire (
    _In_ _Interlocked_operand_ void* const volatile *Source)
{
    return (void*)ReadAcquire((long*)Source);
}

__forceinline
void*
ReadPointerNoFence (
    _In_ _Interlocked_operand_ void* const volatile *Source)
{
    return (void*)ReadNoFence((long*)Source);
}

__forceinline
void*
ReadPointerRaw (
    _In_ _Interlocked_operand_ void* const volatile *Source)
{
    return (void*)ReadRaw((long*)Source);
}

__forceinline
void
WritePointerRelease (
    _Out_ _Interlocked_operand_ void* volatile *Destination,
    _In_ Pvoid Value)
{
    WriteRelease((long*)Destination, (long)Value);
}

__forceinline
void
WritePointerNoFence (
    _Out_ _Interlocked_operand_ void* volatile *Destination,
    _In_opt_ Pvoid Value)
{
    WriteNoFence((long*)Destination, (long)Value);
}

__forceinline
void
WritePointerRaw (
    _Out_ _Interlocked_operand_ void* volatile *Destination,
    _In_opt_ Pvoid Value)
{
    WriteRaw((long*)Destination, (long)Value);
}

#define ReadLongPtrAcquire ReadAcquire
#define ReadLongPtrNoFence ReadNoFence
#define ReadLongPtrRaw ReadRaw
#define WriteLongPtrRelease WriteRelease
#define WriteLongPtrNoFence WriteNoFence
#define WriteLongPtrRaw WriteRaw
#define ReadULongPtrAcquire ReadULongAcquire
#define ReadULongPtrNoFence ReadULongNoFence
#define ReadULongPtrRaw ReadULongRaw
#define WriteULongPtrRelease WriteULongRelease
#define WriteULongPtrNoFence WriteULongNoFence
#define WriteULongPtrRaw WriteULongRaw

#endif

#define ReadSizeTAcquire ReadULongPtrAcquire
#define ReadSizeTNoFence ReadULongPtrNoFence
#define ReadSizeTRaw ReadULongPtrRaw
#define WriteSizeTRelease WriteULongPtrRelease
#define WriteSizeTNoFence WriteULongPtrNoFence
#define WriteSizeTRaw WriteULongPtrRaw

// Overloaded functions
#if defined(__cplusplus)
extern "C++" {

template<typename T>
__forceinline
T
ReadRaw (
    _In_ _Interlocked_operand_ T const volatile *Source)
{
    return *(T*)Source;
}

template<typename T>
__forceinline
void
WriteRaw (
    _Out_ _Interlocked_operand_ T volatile *Destination,
    _In_ T Value)
{
    *(T*)Destination = Value;
}

template<typename T>
__forceinline
T
ReadNoFence (
    _In_ _Interlocked_operand_ T const volatile *Source)
{
    switch (sizeof(T))
    {
        case 1: return (TYPE)ReadNoFence8((char const volatile *)Source);
        case 2: return (TYPE)ReadNoFence16((short const volatile *)Source);
        case 4: return (TYPE)ReadNoFence((long const volatile *)Source);
        case 8: return (TYPE)ReadNoFence64((__int64 const volatile *)Source);
    }
}

template<typename T>
__forceinline
void
WriteNoFence (
    _Out_ _Interlocked_operand_ T volatile *Destination,
    _In_ T Value)
{
    switch (sizeof(T))
    {
        case 1: WriteNoFence8((char const volatile *)Destination, (char)Value);
        case 2: WriteNoFence16((short const volatile *)Destination, (short)Value);
        case 4: WriteNoFence((long const volatile *)Destination, (long)Value);
        case 8: WriteNoFence64((__int64 const volatile *)Destination, (__int64)Value);
    }
}

} // extern "C++"
#endif // __cplusplus
