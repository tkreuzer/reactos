
#include "Bitmap.hpp"

extern "C" {

_Success_(return != -1)
_Must_inspect_result_
CCHAR
NTAPI
RtlFindLeastSignificantBit (
    _In_ ULONGLONG Set)
{
    __debugbreak();
    return -1;
}

_Success_(return != -1)
_Must_inspect_result_
CCHAR
NTAPI
RtlFindMostSignificantBit (
    _In_ ULONGLONG Set)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlNumberOfSetBitsUlongPtr (
    _In_ ULONG_PTR Target)
{
    __debugbreak();
    return -1;
}

VOID
NTAPI
RtlInitializeBitMap (
    _Out_ PRTL_BITMAP BitMapHeader,
    _In_opt_ __drv_aliasesMem PULONG BitMapBuffer,
    _In_opt_ ULONG SizeOfBitMap)
{
    __debugbreak();
}

VOID
NTAPI
RtlClearBit (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    __debugbreak();
}

VOID
NTAPI
RtlSetBit (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    __debugbreak();
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlTestBit (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlClearAllBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    __debugbreak();
}

VOID
NTAPI
RtlSetAllBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    __debugbreak();
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
    __debugbreak();
    return -1;
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
    __debugbreak();
    return -1;
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindClearBitsAndSet (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    __debugbreak();
    return -1;
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindSetBitsAndClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    __debugbreak();
    return -1;
}

VOID
NTAPI
RtlClearBits (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear)
{
    __debugbreak();
}

VOID
NTAPI
RtlSetBits (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet)
{
    __debugbreak();
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsSet (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return FALSE;
}

ULONG
NTAPI
RtlNumberOfClearBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlNumberOfSetBits (
    _In_ PRTL_BITMAP BitMapHeader)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlNumberOfClearBitsInRange (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlNumberOfSetBitsInRange (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindClearRuns (
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_writes_to_(SizeOfRunArray, return) PRTL_BITMAP_RUN RunArray,
    _In_range_(>, 0) ULONG SizeOfRunArray,
    _In_ BOOLEAN LocateLongestRuns)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindLongestRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindFirstRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindNextForwardRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindLastBackwardRunClear (
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    __debugbreak();
    return -1;
}

VOID
NTAPI
RtlCopyBitMap (
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Destination->SizeOfBitMap - 1) ULONG TargetBit)
{
    __debugbreak();
}

VOID
NTAPI
RtlExtractBitMap (
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Source->SizeOfBitMap - 1) ULONG TargetBit,
    _In_range_(0, Source->SizeOfBitMap) ULONG NumberOfBits)
{
    __debugbreak();
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
