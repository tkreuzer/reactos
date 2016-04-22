
#pragma once

#include <ntoskrnl.h>
#include "Memory.hpp"

namespace Rtl {

extern const UCHAR BitCountTable[256];

#undef PopulationCount

FORCEINLINE
ULONG
PopulationCount (
    ULONG Value)
{
#if defined(_M_IX86) || defined(_M_AMD64)
    return __popcnt(Value);
#else
    return BitCountTable[(Value >> 00) & 0xFF] +
           BitCountTable[(Value >> 08) & 0xFF] +
           BitCountTable[(Value >> 16) & 0xFF] +
           BitCountTable[(Value >> 24) & 0xFF] +
#endif // defined
}

FORCEINLINE
ULONG
PopulationCount64 (
    ULONG64 Value)
{
#ifdef _M_AMD64
    return __popcnt64(Value);
#elif defined(_M_IX86)
    return __popcnt((ULONG)(Value >> 32)) + __popcnt((ULONG)Value);
#else
    return PopulationCount((ULONG)(Value >> 32)) +
           PopulationCount((ULONG)Value);
#endif // _M_AMD64
}

FORCEINLINE
ULONG
PopulationCount (
    ULONG64 Value)
{
    return PopulationCount64(Value);
}

FORCEINLINE
VOID
RtlFillMemoryAligned (
    _Out_writes_bytes_(Length) ULONG *Destination,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern)
{
    RtlFillMemoryUlong(Destination, Length, Pattern);
}

#ifdef _WIN64
FORCEINLINE
VOID
RtlFillMemoryAligned (
    _Out_writes_bytes_(Length) ULONG64 *Destination,
    _In_ SIZE_T Length,
    _In_ ULONG64 Pattern)
{
    RtlFillMemoryUlonglong(Destination, Length, Pattern);
}
#endif // _WIN64

template<typename _ULONG>
struct TBITMAP_RUN
{
    _ULONG StartingIndex;
    _ULONG NumberOfBits;
};

template<typename _ULONG>
class TBITMAP
{
    _ULONG _SizeOfBitMap;
    _ULONG *_Buffer;

    static const ULONG _BITCOUNT = sizeof(_ULONG) * 8;

public:

    inline
    TBITMAP (
        VOID)
    {
        _SizeOfBitMap = 0;
        _Buffer = NULL;
    }

    inline
    TBITMAP (
        _In_opt_ __drv_aliasesMem _ULONG *BitMapBuffer,
        _In_opt_ _ULONG SizeOfBitMap)
    {
        _SizeOfBitMap = SizeOfBitMap;
        _Buffer = BitMapBuffer;
    }

    _Must_inspect_result_
    inline
    BOOLEAN
    CheckBit (
        _In_range_(<, _SizeOfBitMap) _ULONG BitNumber)
    {
    #if defined(_M_IX86)
        return BitTest((LONG const *)_Buffer, (LONG)BitNumber);
    #elif defined(_M_AMD64)
        return BitTest64((LONG64 const *)_Buffer, (LONG64)BitNumber);
    #else
        return ((_Buffer[BitNumber / 32] >> (BitNumber % 32)) & 0x1);
    #endif // _M_AMD64
    }

    inline
    VOID
    ClearBit (
        _In_range_(<, _SizeOfBitMap) _ULONG BitNumber)
    {
        NT_ASSERT(BitNumber < _SizeOfBitMap);
    #if defined(_M_IX86)
        BitTestAndReset((LONG *)_Buffer, (LONG)BitNumber);
    #elif defined(_M_AMD64)
        BitTestAndReset64((LONG64 *)_Buffer, (LONG64)BitNumber);
    #else
        _Buffer[BitNumber / 32] &= ~(1u << (BitNumber % 32));
    #endif // _M_AMD64
    }

    inline
    VOID
    SetBit (
        _In_range_(<, _SizeOfBitMap) _ULONG BitNumber)
    {
        NT_ASSERT(BitNumber < _SizeOfBitMap);
    #if defined(_M_IX86)
        BitTestAndSet((LONG *)_Buffer, (LONG)BitNumber);
    #elif defined(_M_AMD64)
        BitTestAndSet64((LONG64 *)_Buffer, (LONG64)BitNumber);
    #else
        _Buffer[BitNumber / 32] |= (1u << (BitNumber % 32));
    #endif // _M_AMD64
    }

    inline
    VOID
    ClearAllBits (
        VOID)
    {
        _ULONG LengthInUlongs;
        LengthInUlongs = (_SizeOfBitMap + _BITCOUNT - 1) / _BITCOUNT;
        RtlFillMemoryAligned(_Buffer, LengthInUlongs * sizeof(_ULONG), 0);
    }

    inline
    VOID
    SetAllBits (
        VOID)
    {
        _ULONG LengthInUlongs;
        LengthInUlongs = (_SizeOfBitMap + _BITCOUNT - 1) / _BITCOUNT;
        RtlFillMemoryAligned(_Buffer, LengthInUlongs * sizeof(_ULONG), ~((_ULONG)0));
    }

    inline
    VOID
    ClearBits (
        _In_range_(0, _SizeOfBitMap - NumberToClear) _ULONG StartingIndex,
        _In_range_(0, _SizeOfBitMap - StartingIndex) _ULONG NumberToClear)
    {
        NT_ASSERT(StartingIndex < (_SizeOfBitMap - NumberToClear));
        NT_ASSERT(NumberToClear < (_SizeOfBitMap - StartingIndex));
        __debugbreak();
    }

    inline
    VOID
    SetBits (
        _In_range_(0, _SizeOfBitMap - NumberToSet) _ULONG StartingIndex,
        _In_range_(0, _SizeOfBitMap - StartingIndex) _ULONG NumberToSet)
    {
        NT_ASSERT(StartingIndex < (_SizeOfBitMap - NumberToSet));
        NT_ASSERT(NumberToSet < (_SizeOfBitMap - StartingIndex));
        __debugbreak();
    }

    _Must_inspect_result_
    inline
    BOOLEAN
    AreBitsClear (
        _In_ _ULONG StartingIndex,
        _In_ _ULONG Length)
    {
        __debugbreak();
        return FALSE;
    }

    _Must_inspect_result_
    inline
    BOOLEAN
    AreBitsSet (
        _In_ _ULONG StartingIndex,
        _In_ _ULONG Length)
    {
        __debugbreak();
        return FALSE;
    }

    inline
    _ULONG
    NumberOfClearBits (
        VOID)
    {
        return _SizeOfBitMap - NumberOfSetBits();
    }

    _ULONG
    NumberOfSetBits (
        VOID);

    inline
    _ULONG
    NumberOfClearBitsInRange (
        _In_ _ULONG StartingIndex,
        _In_ _ULONG Length)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    NumberOfSetBitsInRange (
        _In_ _ULONG StartingIndex,
        _In_ _ULONG Length)
    {
        __debugbreak();
        return -1;
    }

    _Success_(return != -1)
    _Must_inspect_result_
    inline
    _ULONG
    FindClearBits (
        _In_ _ULONG NumberToFind,
        _In_ _ULONG HintIndex)
    {
        __debugbreak();
        return -1;
    }

    _Success_(return != -1)
    _Must_inspect_result_
    inline
    _ULONG
    FindSetBits (
        _In_ _ULONG NumberToFind,
        _In_ _ULONG HintIndex)
    {
        __debugbreak();
        return -1;
    }

    _Success_(return != -1)
    inline
    _ULONG
    FindClearBitsAndSet (
        _In_ _ULONG NumberToFind,
        _In_ _ULONG HintIndex)
    {
        __debugbreak();
        return -1;
    }

    _Success_(return != -1)
    inline
    _ULONG
    FindSetBitsAndClear (
        _In_ _ULONG NumberToFind,
        _In_ _ULONG HintIndex)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    FindClearRuns (
        _Out_writes_to_(SizeOfRunArray, return) TBITMAP_RUN<_ULONG> *RunArray,
        _In_range_(>, 0) _ULONG SizeOfRunArray,
        _In_ BOOLEAN LocateLongestRuns)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    FindSetRuns (
        _Out_writes_to_(SizeOfRunArray, return) TBITMAP_RUN<_ULONG> *RunArray,
        _In_range_(>, 0) _ULONG SizeOfRunArray,
        _In_ BOOLEAN LocateLongestRuns)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    FindLongestRunClear (
        _Out_ PULONG StartingIndex)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    FindLongestRunSet (
        _Out_ PULONG StartingIndex)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    FindFirstRunClear (
        _Out_ PULONG StartingIndex)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    FindNextForwardRunClear (
        _In_ _ULONG FromIndex,
        _Out_ PULONG StartingRunIndex)
    {
        __debugbreak();
        return -1;
    }

    inline
    _ULONG
    FindLastBackwardRunClear (
        _In_ _ULONG FromIndex,
        _Out_ PULONG StartingRunIndex)
    {
        __debugbreak();
        return -1;
    }

    inline
    VOID
    CopyBitMapFrom (
        _In_ TBITMAP *Source,
        _In_range_(0, Destination->SizeOfBitMap - 1) _ULONG TargetBit)
    {
        __debugbreak();
    }

    inline
    VOID
    ExtractBitMapFrom (
        _In_ TBITMAP *Source,
        _In_range_(0, Source->SizeOfBitMap - 1) _ULONG TargetBit,
        _In_range_(0, Source->SizeOfBitMap) _ULONG NumberOfBits)
    {
        __debugbreak();
    }

};

//struct BITMAP_RUN : TBITMAP_RUN<ULONG> {};
class BITMAP
    : public TBITMAP<ULONG>
{
};
typedef TBITMAP_RUN<ULONG> BITMAP_RUN;

#ifdef _WIN64
struct BITMAP_RUN64 : TBITMAP_RUN<ULONG64> {};
class BITMAP64
    : public TBITMAP<ULONG64>
{
};
#endif // _WIN64

}; // namespace Rtl

typedef Rtl::BITMAP RTL_BITMAP, *PRTL_BITMAP;
typedef Rtl::BITMAP_RUN RTL_BITMAP_RUN, *PRTL_BITMAP_RUN;
#ifdef _WIN64
typedef Rtl::BITMAP64 RTL_BITMAP64, *PRTL_BITMAP64;
typedef Rtl::BITMAP64 RTL_BITMAP_EX, *PRTL_BITMAP_EX;
typedef Rtl::BITMAP_RUN64 RTL_BITMAP_RUN64, *PRTL_BITMAP_RUN64;
typedef Rtl::BITMAP_RUN64 RTL_BITMAP_RUN_EX, *PRTL_BITMAP_RUN_EX;
#else
typedef Rtl::BITMAP RTL_BITMAP_EX, *PRTL_BITMAP_EX;
typedef Rtl::BITMAP_RUN RTL_BITMAP_RUN_EX, *PRTL_BITMAP_RUN_EX;
#endif // _WIN64
