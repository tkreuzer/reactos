
#include "Bitmap.hpp"

using namespace Rtl;

extern "C" {

VOID
NTAPI
RtlInitializeBitMap64 (
    _Out_ PRTL_BITMAP64 BitMapHeader,
    _In_opt_ __drv_aliasesMem PULONG BitMapBuffer,
    _In_opt_ ULONG SizeOfBitMap)
{
    new (BitMapHeader) BITMAP64;
}

VOID
NTAPI
RtlClearBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    BitMapHeader->ClearBit(BitNumber);
}

VOID
NTAPI
RtlSetBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    BitMapHeader->SetBit(BitNumber);
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlTestBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    return BitMapHeader->CheckBit(BitNumber);
}

VOID
NTAPI
RtlClearAllBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    BitMapHeader->ClearAllBits();
}

VOID
NTAPI
RtlSetAllBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    BitMapHeader->SetAllBits();
}

_Success_(return != -1)
_Must_inspect_result_
ULONG
NTAPI
RtlFindClearBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindClearBits(NumberToFind, HintIndex);
}

_Success_(return != -1)
_Must_inspect_result_
ULONG
NTAPI
RtlFindSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindSetBits(NumberToFind, HintIndex);
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindClearBitsAndSet64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindClearBitsAndSet(NumberToFind, HintIndex);
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindSetBitsAndClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    return BitMapHeader->FindSetBitsAndClear(NumberToFind, HintIndex);
}

VOID
NTAPI
RtlClearBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear)
{
    BitMapHeader->ClearBits(StartingIndex, NumberToClear);
}

VOID
NTAPI
RtlSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet)
{
    BitMapHeader->SetBits(StartingIndex, NumberToSet);
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->AreBitsClear(StartingIndex, Length);
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsSet64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->AreBitsSet(StartingIndex, Length);
}

ULONG
NTAPI
RtlNumberOfClearBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    return BitMapHeader->NumberOfClearBits();
}

ULONG
NTAPI
RtlNumberOfSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    return BitMapHeader->NumberOfSetBits();
}

#if 0 // not exported!

ULONG
NTAPI
RtlNumberOfClearBitsInRange64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->NumberOfClearBitsInRange(StartingIndex, Length);
}

ULONG
NTAPI
RtlNumberOfSetBitsInRange64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    return BitMapHeader->NumberOfSetBitsInRange(StartingIndex, Length);
}

ULONG
NTAPI
RtlFindClearRuns64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _Out_writes_to_(SizeOfRunArray, return) PRTL_BITMAP_RUN64 RunArray,
    _In_range_(>, 0) ULONG SizeOfRunArray,
    _In_ BOOLEAN LocateLongestRuns)
{
    return BitMapHeader->FindClearRuns(RunArray, SizeOfRunArray, LocateLongestRuns);
}

ULONG
NTAPI
RtlFindLongestRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    return BitMapHeader->FindLongestRunClear(StartingIndex);
}

ULONG
NTAPI
RtlFindFirstRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    return BitMapHeader->FindFirstRunClear(StartingIndex);
}

#endif // 0

ULONG
NTAPI
RtlFindNextForwardRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    return BitMapHeader->FindNextForwardRunClear(FromIndex, StartingRunIndex);
}

#if 0 // not exported!

ULONG
NTAPI
RtlFindLastBackwardRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    return BitMapHeader->FindLastBackwardRunClear(FromIndex, StartingRunIndex);
}

VOID
NTAPI
RtlCopyBitMap64 (
    _In_ PRTL_BITMAP64 Source,
    _In_ PRTL_BITMAP64 Destination,
    _In_range_(0, Destination->SizeOfBitMap - 1) ULONG TargetBit)
{
    Destination->CopyBitMapFrom(Source, TargetBit);
}

VOID
NTAPI
RtlExtractBitMap64 (
    _In_ PRTL_BITMAP64 Source,
    _In_ PRTL_BITMAP64 Destination,
    _In_range_(0, Source->SizeOfBitMap - 1) ULONG TargetBit,
    _In_range_(0, Source->SizeOfBitMap) ULONG NumberOfBits)
{
    Destination->ExtractBitMapFrom(Source, TargetBit, NumberOfBits);
}
#endif // 0

}; // extern "C"
