
#pragma once

#include "Rtl.hpp"

#if defined(_DBG_MEMCPY_INLINE_) && !defined(_MEMCPY_INLINE_) && !defined(_CRTBLD)
#define _MEMCPY_INLINE_
FORCEINLINE
PVOID
__cdecl
memcpy_inline (
    _Out_writes_bytes_all_(size) void *dst,
    _In_reads_bytes_(size) const void *src,
    _In_ size_t size
    )
{
    if (((char *)dst > (char *)src) &&
        ((char *)dst < ((char *)src + size)))
    {
        __debugbreak();
    }
    return memcpy(dst, src, size);
}
#define memcpy memcpy_inline
#endif

//#define RtlEqualMemory(Destination,Source,Length) (!memcmp((Destination),(Source),(Length)))
//#define RtlCopyMemory(Destination,Source,Length) memcpy((Destination),(Source),(Length))
//#define RtlMoveMemory(Destination,Source,Length) memmove((Destination),(Source),(Length))
//#define RtlFillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))
//#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))

FORCEINLINE
PVOID
RtlSecureZeroMemory(
    _Out_writes_bytes_all_(cnt) PVOID Pointer,
    _In_ SIZE_T Length)
{
    volatile char *vptr = (volatile char *)Pointer;

#if defined(_M_IX86) || defined(_M_AMD64)
    __stosb((PUCHAR)((ULONG64)vptr), 0, Length);
#else
    while (Length--)
    {
        WriteNoFence8(vptr++, 0);
    }
#endif // _M_AMD64

    return Pointer;
}

FORCEINLINE
VOID
RtlFillMemoryUlong (
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern)
{
    PULONG Address = (PULONG)Destination;
    NT_ASSERT((((ULONG_PTR)Destination & 3) == 0) && ((Length & 3) == 0));
#if defined(_M_IX86)
    __stosd(Address, Pattern, Length / sizeof(ULONG));
#elif defined(_M_AMD64)
    if (Length != 0)
    {
        if (((ULONG_PTR)Address & 7) != 0)
        {
            *Address++ = Pattern;
            Length -= sizeof(ULONG);
        }

         __stosq((PULONG64)Address,
                 ((ULONG64)Pattern << 32) | Pattern,
                 Length / sizeof(ULONG64));

        if ((Length % sizeof(ULONG64)) != 0)
        {
            Address[Length / sizeof(ULONG) - 1] = Pattern;
        }
    }
#else
    RtlFillMemory(Destination, Length, Pattern);
#endif // _M_IX86
}

FORCEINLINE
VOID
NTAPI
RtlFillMemoryUlonglong (
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONG64 Pattern)
{
    NT_ASSERT((((ULONG_PTR)Destination & 7) == 0) && ((Length & 7) == 0));
#ifdef _M_AMD64
    __stosq((PULONG64)Destination, Pattern, Length / sizeof(ULONG64));
#else
    RtlFillMemoryUlong(Destination, Length, Pattern);
#endif // _M_AMD64
}

