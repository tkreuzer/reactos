
#pragma once

#define _ENGINE_EXPORT_

#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winddi.h>

#define abs(x) ((x) < 0 ? (-(x)) : (x))

#define SURFOBJ_flags(pso) 0

#define GDIDEVFUNCS(pso) ((PDEVOBJ *)((pso)->hdev))->DriverFunctions

typedef struct _DRIVER_FUNCTIONS
{
    PFN_DrvLineTo LineTo;
    PFN_DrvStrokePath StrokePath;
} DRIVER_FUNCTIONS;

typedef struct _PDEVOBJ
{
    DRIVER_FUNCTIONS DriverFunctions;
} PDEVOBJ, *PPDEVOBJ;

typedef struct _SURFACE
{
    //BASEOBJECT BaseObject;
    SURFOBJ so;
    ULONG flags;
    HDEV hdev;

    // GDI32 hack
    HDC hdc;
} SURFACE, *PSURFACE;

typedef struct _EBRUSHOBJ
{
    BRUSHOBJ bo;

    ULONG cStyles;
    PULONG pulStyles;
} EBRUSHOBJ, *PEBRUSHOBJ;

typedef struct _CLIPGDI {
    union
    {
        CLIPOBJ ClipObj;
        WNDOBJ WndObj;
    };
    /* WNDOBJ part */
    HWND              Hwnd;
    WNDOBJCHANGEPROC  ChangeProc;
    FLONG             Flags;
    int               PixelFormat;
    /* CLIPOBJ part */
    ULONG EnumPos;
    ULONG EnumOrder;
    ULONG EnumMax;
    ULONG RectCount;
    RECTL* Rects;
} CLIPGDI, *PCLIPGDI;
C_ASSERT(FIELD_OFFSET(CLIPGDI, ClipObj) == FIELD_OFFSET(CLIPGDI, WndObj.coClient));
#define XCLIPOBJ CLIPGDI

#define FIX LONG

#define FIX2LONG(x) (((x) + 8) >> 4)

#define ENUM_RECT_LIMIT 32

typedef struct _RECT_ENUM
{
    ULONG c;
    RECTL arcl[ENUM_RECT_LIMIT];
} RECT_ENUM;

FORCEINLINE
VOID
SwapLongs(
    PLONG pl1,
    PLONG pl2)
{
    LONG lTemp;
    lTemp = *pl1;
    *pl1 = *pl2;
    *pl2 = lTemp;
}

BOOL
NTAPI
CLIPOBJ_bEnumClipLines(
    _Inout_ CLIPOBJ *pco,
    _In_ const POINTFIX *pptfx,
    _In_ ULONG cj,
    _Out_ CLIPLINE *pcl);

#define UNIMPLEMENTED __debugbreak()
#define NT_ASSERT(x) if (!(x)) __debugbreak()
