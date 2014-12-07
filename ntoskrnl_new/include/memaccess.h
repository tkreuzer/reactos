
#pragma once

#include <intrin.h>

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

#ifdef _M_IX86
FORCEINLINE
VOID
MemoryBarrier (
    VOID)
{
    LONG Barrier;
    _InterlockedOr(&Barrier, 0);
}
#define PreFetchCacheLine(l, a)  _mm_prefetch((CHAR CONST *) a, l)
#define PrefetchForWrite(p)
#define ReadForWriteAccess(p) (*(p))
#elif defined(_M_AMD64)
#define MemoryBarrier __faststorefence
#define PreFetchCacheLine(l, a)  _mm_prefetch((CHAR CONST *) a, l)
#define PrefetchForWrite(p) _m_prefetchw(p)
#define ReadForWriteAccess(p) (_m_prefetchw(p), *(p))
#elif defined(_M_ARM)
# define MemoryBarrier()             __dmb(_ARM_BARRIER_SY)
# define PreFetchCacheLine(l,a)      __prefetch((const void *) (a))
# define PrefetchForWrite(p)         __prefetch((const void *) (p))
# define ReadForWriteAccess(p)       (*(p))
# define _DataSynchronizationBarrier()        __dsb(_ARM_BARRIER_SY)
# define _InstructionSynchronizationBarrier() __isb(_ARM_BARRIER_SY)
#elif defined(_M_ARM64)
# define MemoryBarrier()             __dmb(_ARM64_BARRIER_SY)
# define PreFetchCacheLine(l,a)      __prefetch((const void *) (a))
# define PrefetchForWrite(p)         __prefetch((const void *) (p))
# define ReadForWriteAccess(p)       (*(p))
# define _DataSynchronizationBarrier()        __dsb(_ARM64_BARRIER_SY)
# define _InstructionSynchronizationBarrier() __isb(_ARM64_BARRIER_SY)
#endif /* _M_ARM */

#if defined(_M_IX86) || defined(_M_AMD64)

FORCEINLINE
CHAR
ReadAcquire8 (
    _In_ _Interlocked_operand_ CHAR const volatile *Source)
{
    return *Source;
}

FORCEINLINE
CHAR
ReadNoFence8 (
    _In_ _Interlocked_operand_ CHAR const volatile *Source)
{
    return *Source;
}

FORCEINLINE
VOID
WriteRelease8 (
    _Out_ _Interlocked_operand_ CHAR volatile *Destination,
    _In_ CHAR Value)
{
    *Destination = Value;
}

FORCEINLINE
VOID
WriteNoFence8 (
    _Out_ _Interlocked_operand_ CHAR volatile *Destination,
    _In_ CHAR Value)
{
    *Destination = Value;
}

FORCEINLINE
SHORT
ReadAcquire16 (
    _In_ _Interlocked_operand_ SHORT const volatile *Source)
{
    return *Source;
}

FORCEINLINE
SHORT
ReadNoFence16 (
    _In_ _Interlocked_operand_ SHORT const volatile *Source)
{
    return *Source;
}

FORCEINLINE
VOID
WriteRelease16 (
    _Out_ _Interlocked_operand_ SHORT volatile *Destination,
    _In_ SHORT Value)
{
    *Destination = Value;
}

FORCEINLINE
VOID
WriteNoFence16 (
    _Out_ _Interlocked_operand_ SHORT volatile *Destination,
    _In_ SHORT Value)
{
    *Destination = Value;
}

FORCEINLINE
LONG
ReadAcquire (
    _In_ _Interlocked_operand_ LONG const volatile *Source)
{
    return *Source;
}

FORCEINLINE
LONG
ReadNoFence (
    _In_ _Interlocked_operand_ LONG const volatile *Source)
{
    return *Source;
}

FORCEINLINE
VOID
WriteRelease (
    _Out_ _Interlocked_operand_ LONG volatile *Destination,
    _In_ LONG Value)
{
    *Destination = Value;
}

FORCEINLINE
VOID
WriteNoFence (
    _Out_ _Interlocked_operand_ LONG volatile *Destination,
    _In_ LONG Value)
{
    *Destination = Value;
}

FORCEINLINE
LONG64
ReadAcquire64 (
    _In_ _Interlocked_operand_ LONG64 const volatile *Source)
{
    return *Source;
}

FORCEINLINE
LONG64
ReadNoFence64 (
    _In_ _Interlocked_operand_ LONG64 const volatile *Source)
{
    return *Source;
}

FORCEINLINE
VOID
WriteRelease64 (
    _Out_ _Interlocked_operand_ LONG64 volatile *Destination,
    _In_ LONG64 Value)
{
    *Destination = Value;
}

FORCEINLINE
VOID
WriteNoFence64 (
    _Out_ _Interlocked_operand_ LONG64 volatile *Destination,
    _In_ LONG64 Value)
{
    *Destination = Value;
}

#elif defined(_M_ARM) || defined(_M_ARM64)

typedef enum _tag_ARM3264INTR_BARRIER_TYPE
{
    _ARM3264_BARRIER_SY    = 0xF,
    _ARM3264_BARRIER_ST    = 0xE,
    _ARM3264_BARRIER_ISH   = 0xB,
    _ARM3264_BARRIER_ISHST = 0xA,
    _ARM3264_BARRIER_NSH   = 0x7,
    _ARM3264_BARRIER_NSHST = 0x6,
    _ARM3264_BARRIER_OSH   = 0x3,
    _ARM3264_BARRIER_OSHST = 0x2
} _ARM6432INTR_BARRIER_TYPE;

FORCEINLINE
CHAR
ReadAcquire8 (
    _In_ _Interlocked_operand_ CHAR const volatile *Source)
{
    CHAR Value = __iso_volatile_load8(Source);
    __dmb(_ARM3264_BARRIER_ISH);
    return Value;
}

FORCEINLINE
CHAR
ReadNoFence8 (
    _In_ _Interlocked_operand_ CHAR const volatile *Source)
{
    return __iso_volatile_load8(Source);
}

FORCEINLINE
VOID
WriteRelease8 (
    _Out_ _Interlocked_operand_ CHAR volatile *Destination,
    _In_ CHAR Value)
{
    __dmb(_ARM3264_BARRIER_ISH);
    __iso_volatile_store8(Destination, Value);
}

FORCEINLINE
VOID
WriteNoFence8 (
    _Out_ _Interlocked_operand_ CHAR volatile *Destination,
    _In_ CHAR Value)
{
    __iso_volatile_store8(Destination, Value);
}

FORCEINLINE
SHORT
ReadAcquire16 (
    _In_ _Interlocked_operand_ SHORT const volatile *Source)
{
    SHORT Value = __iso_volatile_load16(Source);
    __dmb(_ARM3264_BARRIER_ISH);
    return Value;
}

FORCEINLINE
SHORT
ReadNoFence16 (
    _In_ _Interlocked_operand_ SHORT const volatile *Source)
{
    return __iso_volatile_load16(Source);
}

FORCEINLINE
VOID
WriteRelease16 (
    _Out_ _Interlocked_operand_ SHORT volatile *Destination,
    _In_ SHORT Value)
{
    __dmb(_ARM3264_BARRIER_ISH);
    __iso_volatile_store16(Destination, Value);
}

FORCEINLINE
VOID
WriteNoFence16 (
    _Out_ _Interlocked_operand_ SHORT volatile *Destination,
    _In_ SHORT Value)
{
    __iso_volatile_store16(Destination, Value);
}

FORCEINLINE
LONG
ReadAcquire (
    _In_ _Interlocked_operand_ LONG const volatile *Source)
{
    LONG Value = __iso_volatile_load32((int *)Source);
    __dmb(_ARM3264_BARRIER_ISH);
    return Value;
}

FORCEINLINE
LONG
ReadNoFence (
    _In_ _Interlocked_operand_ LONG const volatile *Source)
{
    return __iso_volatile_load32((int *)Source);
}

CFORCEINLINE
VOID
WriteRelease (
    _Out_ _Interlocked_operand_ LONG volatile *Destination,
    _In_ LONG Value)
{
    __dmb(_ARM3264_BARRIER_ISH);
    __iso_volatile_store32((int *)Destination, Value);
}

FORCEINLINE
VOID
WriteNoFence (
    _Out_ _Interlocked_operand_ LONG volatile *Destination,
    _In_ LONG Value)
{
    __iso_volatile_store32((int *)Destination, Value);
}

FORCEINLINE
LONG64
ReadAcquire64 (
    _In_ _Interlocked_operand_ LONG64 const volatile *Source)
{
    LONG64 Value = __iso_volatile_load64(Source);
    __dmb(_ARM3264_BARRIER_ISH);
    return Value;
}

FORCEINLINE
LONG64
ReadNoFence64 (
    _In_ _Interlocked_operand_ LONG64 const volatile *Source)
{
    return __iso_volatile_load64(Source);
}

CFORCEINLINE
VOID
WriteRelease64 (
    _Out_ _Interlocked_operand_ LONG64 volatile *Destination,
    _In_ LONG64 Value)
{
    __dmb(_ARM3264_BARRIER_ISH);
    __iso_volatile_store64(Destination, Value);
}

FORCEINLINE
VOID
WriteNoFence64 (
    _Out_ _Interlocked_operand_ LONG64 volatile *Destination,
    _In_ LONG64 Value)
{
    __iso_volatile_store64(Destination, Value);
}

#else
#error Unknown architecture
#endif // defined

FORCEINLINE
CHAR
ReadRaw8 (
    _In_ _Interlocked_operand_ CHAR const volatile *Source)
{
    return *(CHAR *)Source;
}

FORCEINLINE
VOID
WriteRaw8 (
    _Out_ _Interlocked_operand_ CHAR volatile *Destination,
    _In_ CHAR Value)
{
    *(CHAR *)Destination = Value;
}

FORCEINLINE
SHORT
ReadRaw16 (
    _In_ _Interlocked_operand_ SHORT const volatile *Source)
{
    return *(SHORT *)Source;
}

FORCEINLINE
VOID
WriteRaw16 (
    _Out_ _Interlocked_operand_ SHORT volatile *Destination,
    _In_ SHORT Value)
{
    *(SHORT *)Destination = Value;
}

FORCEINLINE
LONG
ReadRaw (
    _In_ _Interlocked_operand_ LONG const volatile *Source)
{
    return *(LONG *)Source;
}

FORCEINLINE
VOID
WriteRaw (
    _Out_ _Interlocked_operand_ LONG volatile *Destination,
    _In_ LONG Value)
{
    *(LONG *)Destination = Value;
}

FORCEINLINE
LONG64
ReadRaw64 (
    _In_ _Interlocked_operand_ LONG64 const volatile *Source)
{
    return *(LONG64 *)Source;
}

FORCEINLINE
VOID
WriteRaw64 (
    _Out_ _Interlocked_operand_ LONG64 volatile *Destination,
    _In_ LONG64 Value)
{
    *(LONG64 *)Destination = Value;
}

///

FORCEINLINE
UCHAR
ReadUCharAcquire (
    _In_ _Interlocked_operand_ UCHAR const volatile *Source)
{
    return (UCHAR)ReadAcquire8((PCHAR)Source);
}

FORCEINLINE
UCHAR
ReadUCharNoFence (
    _In_ _Interlocked_operand_ UCHAR const volatile *Source)
{
    return (UCHAR)ReadNoFence8((PCHAR)Source);
}

FORCEINLINE
UCHAR
ReadUCharRaw (
    _In_ _Interlocked_operand_ UCHAR const volatile *Source)
{
    return (UCHAR)ReadRaw8((PCHAR)Source);
}

FORCEINLINE
VOID
WriteUCharRelease (
    _Out_ _Interlocked_operand_ UCHAR volatile *Destination,
    _In_ UCHAR Value)
{
    WriteRelease8((PCHAR)Destination, (CHAR)Value);
}

FORCEINLINE
VOID
WriteUCharNoFence (
    _Out_ _Interlocked_operand_ UCHAR volatile *Destination,
    _In_ UCHAR Value)
{
    WriteNoFence8((PCHAR)Destination, (CHAR)Value);
}

FORCEINLINE
VOID
WriteUCharRaw (
    _Out_ _Interlocked_operand_ UCHAR volatile *Destination,
    _In_ UCHAR Value)
{
    WriteRaw8((PCHAR)Destination, (CHAR)Value);
}

FORCEINLINE
UCHAR
ReadBooleanAcquire (
    _In_ _Interlocked_operand_ BOOLEAN const volatile *Source)
{
    return (BOOLEAN)ReadAcquire8((PCHAR)Source);
}

FORCEINLINE
UCHAR
ReadBooleanNoFence (
    _In_ _Interlocked_operand_ BOOLEAN const volatile *Source)
{
    return (BOOLEAN)ReadNoFence8((PCHAR)Source);
}

FORCEINLINE
VOID
WriteBooleanRelease (
    _Out_ _Interlocked_operand_ BOOLEAN volatile *Destination,
    _In_ BOOLEAN Value)
{
    WriteRelease8((PCHAR)Destination, (CHAR)Value);
}

FORCEINLINE
VOID
WriteBooleanNoFence (
    _Out_ _Interlocked_operand_ BOOLEAN volatile *Destination,
    _In_ BOOLEAN Value)
{
    WriteNoFence8((PCHAR)Destination, (CHAR)Value);
}

FORCEINLINE
USHORT
ReadUShortAcquire (
    _In_ _Interlocked_operand_ USHORT const volatile *Source)
{
    return (USHORT)ReadAcquire16((PSHORT)Source);
}

FORCEINLINE
USHORT
ReadUShortNoFence (
    _In_ _Interlocked_operand_ USHORT const volatile *Source)
{
    return (USHORT)ReadNoFence16((PSHORT)Source);
}

FORCEINLINE
USHORT
ReadUShortRaw (
    _In_ _Interlocked_operand_ USHORT const volatile *Source)
{
    return (USHORT)ReadRaw16((PSHORT)Source);
}

FORCEINLINE
VOID
WriteUShortRelease (
    _Out_ _Interlocked_operand_ USHORT volatile *Destination,
    _In_ USHORT Value)
{
    WriteRelease16((PSHORT)Destination, (SHORT)Value);
}

FORCEINLINE
VOID
WriteUShortNoFence (
    _Out_ _Interlocked_operand_ USHORT volatile *Destination,
    _In_ USHORT Value)
{
    WriteNoFence16((PSHORT)Destination, (SHORT)Value);
}

FORCEINLINE
VOID
WriteUShortRaw (
    _Out_ _Interlocked_operand_ USHORT volatile *Destination,
    _In_ USHORT Value)
{
    WriteRaw16((PSHORT)Destination, (SHORT)Value);
}

FORCEINLINE
ULONG
ReadULongAcquire (
    _In_ _Interlocked_operand_ ULONG const volatile *Source)
{
    return (ULONG)ReadAcquire((PLONG)Source);
}

FORCEINLINE
ULONG
ReadULongNoFence (
    _In_ _Interlocked_operand_ ULONG const volatile *Source)
{
    return (ULONG)ReadNoFence((PLONG)Source);
}

FORCEINLINE
ULONG
ReadULongRaw (
    _In_ _Interlocked_operand_ ULONG const volatile *Source)
{
    return (ULONG)ReadRaw((PLONG)Source);
}

FORCEINLINE
VOID
WriteULongRelease (
    _Out_ _Interlocked_operand_ ULONG volatile *Destination,
    _In_ ULONG Value)
{
    WriteRelease((PLONG)Destination, (LONG)Value);
}

FORCEINLINE
VOID
WriteULongNoFence (
    _Out_ _Interlocked_operand_ ULONG volatile *Destination,
    _In_ ULONG Value)
{
    WriteNoFence((PLONG)Destination, (LONG)Value);
}

FORCEINLINE
VOID
WriteULongRaw (
    _Out_ _Interlocked_operand_ ULONG volatile *Destination,
    _In_ ULONG Value)
{
    WriteRaw((PLONG)Destination, (LONG)Value);
}

FORCEINLINE
ULONG64
ReadULong64Acquire (
    _In_ _Interlocked_operand_ ULONG64 const volatile *Source)
{
    return (ULONG64)ReadAcquire64((PLONG64)Source);
}

FORCEINLINE
ULONG64
ReadULong64NoFence (
    _In_ _Interlocked_operand_ ULONG64 const volatile *Source)
{
    return (ULONG64)ReadNoFence64((PLONG64)Source);
}

FORCEINLINE
ULONG64
ReadULong64Raw (
    _In_ _Interlocked_operand_ ULONG64 const volatile *Source)
{
    return (ULONG64)ReadRaw64((PLONG64)Source);
}

FORCEINLINE
VOID
WriteULong64Release (
    _Out_ _Interlocked_operand_ ULONG64 volatile *Destination,
    _In_ ULONG64 Value)
{
    WriteRelease64((PLONG64)Destination, (LONG64)Value);
}

FORCEINLINE
VOID
WriteULong64NoFence (
    _Out_ _Interlocked_operand_ ULONG64 volatile *Destination,
    _In_ ULONG64 Value)
{
    WriteNoFence64((PLONG64)Destination, (LONG64)Value);
}

FORCEINLINE
VOID
WriteULong64Raw (
    _Out_ _Interlocked_operand_ ULONG64 volatile *Destination,
    _In_ ULONG64 Value)
{
    WriteRaw64((PLONG64)Destination, (LONG64)Value);
}

#ifdef _WIN64

FORCEINLINE
PVOID
ReadPointerAcquire (
    _In_ _Interlocked_operand_ PVOID const volatile *Source)
{
    return (PVOID)ReadAcquire64((PLONG64)Source);
}

FORCEINLINE
PVOID
ReadPointerNoFence (
    _In_ _Interlocked_operand_ PVOID const volatile *Source)
{
    return (PVOID)ReadNoFence64((PLONG64)Source);
}

FORCEINLINE
PVOID
ReadPointerRaw (
    _In_ _Interlocked_operand_ PVOID const volatile *Source)
{
    return (PVOID)ReadRaw64((PLONG64)Source);
}

FORCEINLINE
VOID
WritePointerRelease (
    _Out_ _Interlocked_operand_ PVOID volatile *Destination,
    _In_ PVOID Value)
{
    WriteRelease64((PLONG64)Destination, (LONG64)Value);
}

FORCEINLINE
VOID
WritePointerNoFence (
    _Out_ _Interlocked_operand_ PVOID volatile *Destination,
    _In_ PVOID Value)
{
    WriteNoFence64((PLONG64)Destination, (LONG64)Value);
}

FORCEINLINE
VOID
WritePointerRaw (
    _Out_ _Interlocked_operand_ PVOID volatile *Destination,
    _In_ PVOID Value)
{
    WriteRaw64((PLONG64)Destination, (LONG64)Value);
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

FORCEINLINE
PVOID
ReadPointerAcquire (
    _In_ _Interlocked_operand_ PVOID const volatile *Source)
{
    return (PVOID)ReadAcquire((PLONG)Source);
}

FORCEINLINE
PVOID
ReadPointerNoFence (
    _In_ _Interlocked_operand_ PVOID const volatile *Source)
{
    return (PVOID)ReadNoFence((PLONG)Source);
}

FORCEINLINE
PVOID
ReadPointerRaw (
    _In_ _Interlocked_operand_ PVOID const volatile *Source)
{
    return (PVOID)ReadRaw((PLONG)Source);
}

FORCEINLINE
VOID
WritePointerRelease (
    _Out_ _Interlocked_operand_ PVOID volatile *Destination,
    _In_ PVOID Value)
{
    WriteRelease((PLONG)Destination, (LONG)Value);
}

FORCEINLINE
VOID
WritePointerNoFence (
    _Out_ _Interlocked_operand_ PVOID volatile *Destination,
    _In_opt_ PVOID Value)
{
    WriteNoFence((PLONG)Destination, (LONG)Value);
}

FORCEINLINE
VOID
WritePointerRaw (
    _Out_ _Interlocked_operand_ PVOID volatile *Destination,
    _In_opt_ PVOID Value)
{
    WriteRaw((PLONG)Destination, (LONG)Value);
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

