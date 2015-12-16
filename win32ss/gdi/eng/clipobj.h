/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS win32 subsystem
 * PURPOSE:           XCLIPOBJ class definition
 * PROGRAMER:         Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#pragma once

#ifdef __cplusplus
class XCLIPOBJ
#else
struct _XCLIPOBJ
#endif
{
    union
    {
        CLIPOBJ ClipObj;
        WNDOBJ WndObj;
        WNDOBJ _wndo;
        CLIPOBJ _co;
    };

    struct _REGION * _prgn;
    PRECTL _prc;
    ULONG _iEnumNext;
    ULONG _iRowStart;
    ULONG _iLastInRow;
    ULONG _iLast;

    ULONG _iDirection;
    ULONG _iType;
    BOOL _bAll;

    ULONG _cRects;
    ULONG _cEnumerated;

    /* WNDOBJ part (should move to EWNDOBJ) */
    HWND              Hwnd;
    WNDOBJCHANGEPROC  ChangeProc;
    FLONG             Flags;
    int               PixelFormat;

#ifdef __cplusplus

public:

    XCLIPOBJ(
        VOID);

    ~XCLIPOBJ(
        VOID);

    inline
    VOID
    vSetRgn(
        _In_ PREGION *prgn)
    {
        _prgn = prgn;
    }

    ULONG
    cEnumStart(
        _In_ BOOL bAll,
        _In_ ULONG iType,
        _In_ ULONG iDirection,
        _In_ ULONG cLimit);

    BOOL
    bEnum(
        _In_ ULONG cRects,
        _Out_ ENUMRECTS *per);

#endif
};

#ifdef __cplusplus
typedef class XCLIPOBJ *PXCLIPOBJ;
#else
typedef struct _XCLIPOBJ XCLIPOBJ, *PXCLIPOBJ;

VOID FASTCALL
IntEngUpdateClipRegion_(XCLIPOBJ* Clip,
                       ULONG count,
                       const RECTL* pRect,
                       const RECTL* rcBounds);

VOID FASTCALL
IntEngInitClipObj(XCLIPOBJ *Clip);

VOID FASTCALL
IntEngFreeClipResources(XCLIPOBJ *Clip);

#endif

