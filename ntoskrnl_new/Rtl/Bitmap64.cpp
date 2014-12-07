
#include "Bitmap.hpp"

extern "C" {

VOID
NTAPI
RtlInitializeBitMap64 (
    _Out_ PRTL_BITMAP64 BitMapHeader,
    _In_opt_ __drv_aliasesMem PULONG BitMapBuffer,
    _In_opt_ ULONG SizeOfBitMap)
{
    __debugbreak();
}

VOID
NTAPI
RtlClearBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    __debugbreak();
}

VOID
NTAPI
RtlSetBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    __debugbreak();
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlTestBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlClearAllBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    __debugbreak();
}

VOID
NTAPI
RtlSetAllBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    __debugbreak();
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
    __debugbreak();
    return -1;
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
    __debugbreak();
    return -1;
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindClearBitsAndSet64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    __debugbreak();
    return -1;
}

_Success_(return != -1)
ULONG
NTAPI
RtlFindSetBitsAndClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex)
{
    __debugbreak();
    return -1;
}

VOID
NTAPI
RtlClearBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear)
{
    __debugbreak();
}

VOID
NTAPI
RtlSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet)
{
    __debugbreak();
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
BOOLEAN
NTAPI
RtlAreBitsSet64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return FALSE;
}

ULONG
NTAPI
RtlNumberOfClearBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlNumberOfSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader)
{
    __debugbreak();
    return -1;
}

#if 0 // not exported!

ULONG
NTAPI
RtlNumberOfClearBitsInRange64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlNumberOfSetBitsInRange64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindClearRuns64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _Out_writes_to_(SizeOfRunArray, return) PRTL_BITMAP_RUN64 RunArray,
    _In_range_(>, 0) ULONG SizeOfRunArray,
    _In_ BOOLEAN LocateLongestRuns)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindLongestRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    __debugbreak();
    return -1;
}

ULONG
NTAPI
RtlFindFirstRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _Out_ PULONG StartingIndex)
{
    __debugbreak();
    return -1;
}

#endif // 0

ULONG
NTAPI
RtlFindNextForwardRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    __debugbreak();
    return -1;
}

#if 0 // not exported!

ULONG
NTAPI
RtlFindLastBackwardRunClear64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex)
{
    __debugbreak();
    return -1;
}

VOID
NTAPI
RtlCopyBitMap64 (
    _In_ PRTL_BITMAP64 Source,
    _In_ PRTL_BITMAP64 Destination,
    _In_range_(0, Destination->SizeOfBitMap - 1) ULONG TargetBit)
{
    __debugbreak();
}

VOID
NTAPI
RtlExtractBitMap64 (
    _In_ PRTL_BITMAP64 Source,
    _In_ PRTL_BITMAP64 Destination,
    _In_range_(0, Source->SizeOfBitMap - 1) ULONG TargetBit,
    _In_range_(0, Source->SizeOfBitMap) ULONG NumberOfBits)
{
    __debugbreak();
}
#endif // 0

}; // extern "C"
