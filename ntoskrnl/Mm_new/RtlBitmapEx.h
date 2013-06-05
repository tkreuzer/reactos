

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN64

typedef struct _RTL_BITMAP64
{
    ULONG64 SizeOfBitMap;
    PULONG64 Buffer;
} RTL_BITMAP64, *PRTL_BITMAP64;

VOID
NTAPI
RtlInitializeBitMap64 (
    _Out_ PRTL_BITMAP64 BitMapHeader,
    _In_ PULONG64 BitMapBuffer,
    _In_ ULONG64 SizeOfBitMap);

BOOLEAN
NTAPI
RtlTestBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 BitNumber);

VOID
NTAPI
RtlClearBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 BitNumber);

VOID
NTAPI
RtlClearBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 StartingIndex,
    _In_ ULONG64 NumberToClear);

VOID
NTAPI
RtlSetBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 BitNumber);

VOID
NTAPI
RtlSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 StartingIndex,
    _In_ ULONG64 NumberToClear);

BOOLEAN
NTAPI
RtlAreBitsSet64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 StartingIndex,
    _In_ ULONG64 Length);

ULONG64
NTAPI
RtlFindSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 NumberToFind,
    _In_ ULONG64 HintIndex);

#define RtlInitializeBitMapEx RtlInitializeBitMap64
#define RtlTestBitEx RtlTestBit64
#define RtlClearBitEx RtlClearBit64
#define RtlClearBitsEx RtlClearBits64
#define RtlSetBitEx RtlSetBit64
#define RtlSetBitsEx RtlSetBits64
#define RtlAreBitsSetEx RtlAreBitsSet64
#define RtlFindSetBitsEx RtlFindSetBits64
#define RTL_BITMAP_EX RTL_BITMAP64
#define PRTL_BITMAP_EX PRTL_BITMAP64
#else
#define RtlInitializeBitMapEx RtlInitializeBitMap
#define RtlTestBitEx RtlTestBit
#define RtlClearBitEx RtlClearBit
#define RtlClearBitsEx RtlClearBits
#define RtlSetBitEx RtlSetBit
#define RtlSetBitsEx RtlSetBits
#define RtlAreBitsSetEx RtlAreBitsSet
#define RtlFindSetBitsEx RtlFindSetBits
#define RTL_BITMAP_EX RTL_BITMAP
#define PRTL_BITMAP_EX PRTL_BITMAP
#endif

#ifdef __cplusplus
};
#endif
