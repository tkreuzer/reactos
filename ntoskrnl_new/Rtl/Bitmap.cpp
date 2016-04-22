
#include "Bitmap.hpp"

namespace Rtl {

/* Number of set bits per byte value */
const UCHAR BitCountTable[256] =
{
    /* x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC xD xE xF */
       0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, /* 0x */
       1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, /* 1x */
       1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, /* 2x */
       2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, /* 3x */
       1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, /* 4x */
       2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, /* 5x */
       2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, /* 6c */
       3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, /* 7x */
       1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, /* 8x */
       2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, /* 9x */
       2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, /* Ax */
       3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, /* Bx */
       2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, /* Cx */
       3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, /* Dx */
       3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, /* Ex */
       4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8  /* Fx */
};

template<typename _ULONG>
_ULONG
TBITMAP<_ULONG>::NumberOfSetBits (
    VOID)
{
    _ULONG BitCount = 0;
    ULONG Remaining, Shift;
#ifdef _WIN64
    ULONG64 *Current, *MaxBuffer;

    /* Handle bitmaps up to 64 bits */
    if (_SizeOfBitMap <= 64)
    {
        Shift = 64 - _SizeOfBitMap;
        return PopulationCount64(*(PULONG64)_Buffer << Shift);
    }

    /* Get the start and size of the buffer */
    Current = (PULONG64)_Buffer;
    Remaining = _SizeOfBitMap;

    /* Check for unaligned buffer */
    if ((ULONG_PTR)_Buffer & 7)
    {
        BitCount += PopulationCount(*_Buffer);
        Remaining -= 32;
        Current = (PULONG64)((ULONG_PTR)Current + sizeof(ULONG));
    }

    /* Loop all full ULONG64 */
    MaxBuffer = Current + (Remaining / sizeof(ULONG64));
    while (Current < MaxBuffer)
    {
        BitCount += PopulationCount64(*Current++);
    }

    /* Calculate the remaining number of bits */
    Remaining = Remaining % (8 * sizeof(ULONG64));
    if (Remaining > 0)
    {
        Shift = (8 * sizeof(ULONG64)) - Remaining;
        BitCount += PopulationCount64(*Current << Shift);
    }
#else // _WIN64
    _ULONG *Current, *MaxBuffer;

    /* Get the start and end of the buffer */
    Current = _Buffer;
    MaxBuffer = _Buffer + (_SizeOfBitMap / sizeof(_ULONG));

    /* Loop all full _ULONG's */
    while (Current < MaxBuffer)
    {
        BitCount += PopulationCount(*Current++);
    }

    /* Calculate the remaining number of bits */
    Remaining = _SizeOfBitMap % (8 * sizeof(_ULONG));
    if (Remaining > 0)
    {
        Shift = (8 * sizeof(_ULONG)) - Remaining;
        BitCount += PopulationCount(*Current << Shift);
    }
#endif // _WIN64

    return BitCount;
}

/* Explicitly instantiate the class */
template class TBITMAP<ULONG>;
#ifdef _WIN64
template class TBITMAP<ULONG64>;
#endif // _WIN64

}; // namespace Rtl

using namespace Rtl;

extern "C" {

_Success_(return != -1)
_Must_inspect_result_
CCHAR
NTAPI
RtlFindLeastSignificantBit (
    _In_ ULONGLONG Value)
{
    ULONG Position;

#ifdef _WIN64
    if (BitScanForward64(&Position, Value))
    {
        return (CCHAR)Position;
    }
#else
    if (BitScanForward(&Position, (ULONG)Value))
    {
        return (CCHAR)Position;
    }
    else if (BitScanForward(&Position, Value >> 32))
    {
        return (CCHAR)(Position + 32);
    }
#endif
    return -1;
}

_Success_(return != -1)
_Must_inspect_result_
CCHAR
NTAPI
RtlFindMostSignificantBit (
    _In_ ULONGLONG Value)
{
    ULONG Position;

#ifdef _WIN64
    if (BitScanReverse64(&Position, Value))
    {
        return (CCHAR)Position;
    }
#else
    if (BitScanReverse(&Position, Value >> 32))
    {
        return (CCHAR)(Position + 32);
    }
    else if (BitScanReverse(&Position, (ULONG)Value))
    {
        return (CCHAR)Position;
    }
#endif
    return -1;
}

ULONG
NTAPI
RtlNumberOfSetBitsUlongPtr (
    _In_ ULONG_PTR Target)
{
    return PopulationCount(Target);
}

VOID
NTAPI
RtlInitializeBitMap (
    _Out_ PRTL_BITMAP BitMapHeader,
    _In_opt_ __drv_aliasesMem PULONG BitMapBuffer,
    _In_opt_ ULONG SizeOfBitMap)
{
    new (BitMapHeader) BITMAP;
}

VOID
NTAPI
RtlClearBit (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    BitMapHeader->ClearBit(BitNumber);
}

VOID
NTAPI
RtlSetBit (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    BitMapHeader->SetBit(BitNumber);
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlTestBit (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    return BitMapHeader->CheckBit(BitNumber);
}

VOID
NTAPI
RtlClearAllBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    BitMapHeader->ClearAllBits();
}

VOID
NTAPI
RtlSetAllBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    BitMapHeader->SetAllBits();
}

_Success_(return != -1)
_Must_inspect_result_
ULONG
NTAPI
RtlFindClearBits (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindClearBits(NumberToFind, HintIndex);
}

_Success_(return != -1)
_Must_inspect_result_
ULONG
NTAPI
RtlFindSetBits (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindSetBits(NumberToFind, HintIndex);
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindClearBitsAndSet (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindClearBitsAndSet(NumberToFind, HintIndex);
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindSetBitsAndClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindSetBitsAndClear(NumberToFind, HintIndex);
}

VOID
NTAPI
RtlClearBits (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear)
{
    BitMapHeader->ClearBits(StartingIndex, NumberToClear);
}

VOID
NTAPI
RtlSetBits (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet)
{
    BitMapHeader->SetBits(StartingIndex, NumberToSet);
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->AreBitsClear(StartingIndex, Length);
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsSet (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->AreBitsSet(StartingIndex, Length);
}

ULONG
NTAPI
RtlNumberOfClearBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    return BitMapHeader->NumberOfClearBits();
}

ULONG
NTAPI
RtlNumberOfSetBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    return BitMapHeader->NumberOfSetBits();
}

ULONG
NTAPI
RtlNumberOfClearBitsInRange (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->NumberOfClearBitsInRange(StartingIndex, Length);
}

ULONG
NTAPI
RtlNumberOfSetBitsInRange (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->NumberOfSetBitsInRange(StartingIndex, Length);
}

ULONG
NTAPI
RtlFindClearRuns (
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_writes_to_(SizeOfRunArray, return) PRTL_BITMAP_RUN RunArray,
    _In_range_(>, 0) ULONG SizeOfRunArray,
    _In_ BOOLEAN LocateLongestRuns)
{
    return BitMapHeader->FindClearRuns(RunArray, SizeOfRunArray, LocateLongestRuns);
}

ULONG
NTAPI
RtlFindLongestRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    return BitMapHeader->FindLongestRunClear(StartingIndex);
}

ULONG
NTAPI
RtlFindFirstRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    return BitMapHeader->FindFirstRunClear(StartingIndex);
}

ULONG
NTAPI
RtlFindNextForwardRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    return BitMapHeader->FindNextForwardRunClear(FromIndex, StartingRunIndex);
}

ULONG
NTAPI
RtlFindLastBackwardRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    return BitMapHeader->FindLastBackwardRunClear(FromIndex, StartingRunIndex);
}

VOID
NTAPI
RtlCopyBitMap (
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Destination->SizeOfBitMap - 1) ULONG TargetBit)
{
    Destination->CopyBitMapFrom(Source, TargetBit);
}

VOID
NTAPI
RtlExtractBitMap (
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Source->SizeOfBitMap - 1) ULONG TargetBit,
    _In_range_(0, Source->SizeOfBitMap) ULONG NumberOfBits)
{
    Destination->ExtractBitMapFrom(Source, TargetBit, NumberOfBits);
}

// prototype from RtlClearBits
VOID
NTAPI
RtlInterlockedClearBitRun (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear)
{
    __debugbreak();
}

// prototype from RtlClearBits
VOID
NTAPI
RtlInterlockedSetBitRun (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet)
{
    __debugbreak();
}

// prototype from RtlClearBits, but BOOLEAN return value
BOOLEAN
NTAPI
RtlInterlockedSetClearRun (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"
