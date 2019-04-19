
#pragma once


// http://www.masmforum.com/board/index.php?PHPSESSID=8d46cd4ecb1688be429ab49694ec53e6&topic=16842.0;wap2

#ifndef NTVIDAPI
#define NTVIDAPI DECLSPEC_DLLIMPORT
#endif // NTVIDAPI

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _BITMAPINFO *PBITMAPINFO;

#if (NTDDI_VERSION >= NTDDI_WIN10) // ???
NTVIDAPI
BOOLEAN
NTAPI
VidInitialize (
    _In_ LONG Operation,
    _In_ BOOLEAN SetMode);
#else
NTVIDAPI
BOOLEAN
NTAPI
VidInitialize (
    _In_ BOOLEAN SetMode);
#endif

NTVIDAPI
VOID
NTAPI
VidCleanUp (
    VOID);

NTVIDAPI
VOID
NTAPI
VidResetDisplay (
    VOID);

NTVIDAPI
VOID
NTAPI
VidSetScrollRegion (
    _In_ ULONG X1,
    _In_ ULONG Y1,
    _In_ ULONG X2,
    _In_ ULONG Y2);

NTVIDAPI
VOID
NTAPI
VidSolidColorFill (
    _In_ ULONG X1,
    _In_ ULONG Y1,
    _In_ ULONG X2,
    _In_ ULONG Y2,
    _In_ ULONG Color);

NTVIDAPI
VOID
NTAPI
VidBitBlt (
    _In_ PBITMAPINFO BitmapInfo,
    _In_ ULONG X,
    _In_ ULONG Y);

// `???
NTVIDAPI
VOID
NTAPI
VidBitBltEx (
    _In_ ULONG X,
    _In_ ULONG Y,
    _In_ ULONG Width,
    _In_ ULONG Height,
    _In_ PUCHAR Buffer);

NTVIDAPI
VOID
NTAPI
VidBufferToScreenBlt (
    _In_ PUCHAR Buffer,
    _In_ ULONG X,
    _In_ ULONG Y,
    _In_ ULONG Width,
    _In_ ULONG Height,
    _In_ LONG lDelta);

NTVIDAPI
VOID
NTAPI
VidScreenToBufferBlt (
    _Out_ PUCHAR Buffer,
    _In_ ULONG X,
    _In_ ULONG Y,
    _In_ ULONG Width,
    _In_ ULONG Height,
    _In_ LONG lDelta);

NTVIDAPI
ULONG
NTAPI
VidSetTextColor (
    _In_ ULONG Color);

NTVIDAPI
VOID
NTAPI
VidDisplayString (
    _In_ PUCHAR String);

NTVIDAPI
VOID
NTAPI
VidDisplayStringXY (
    _In_ PUCHAR String,
    _In_ ULONG X,
    _In_ ULONG Y,
    _In_ BOOLEAN Transparent);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

