
#pragma once

#define _NO_DDRAWINT_NO_COM
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winddi.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef NT_ASSERT
#define NT_ASSERT(x) if (!(x)) __debugbreak()
#endif // NT_ASSERT

#define RUN_MAX 20

typedef struct _LINEINFO
{
    LONG dx;
    LONG dy;
    ULONG ulColor;
    LONG lRemainder;
    LONG lDenominator;
    LONG lNumerator;
    ULONG acxyStyle[16];    /* Style array, adjusted to pixel size */
    USHORT cStyles;
    USHORT cxyStyleSize;
    USHORT iStyle;          /* Current index into pulStyle */
    USHORT xyStylePos;      /* Pixel offset from the start of iStyle */
    //USHORT xStyleStep;      /* Width in pixels of one style unit */
    //USHORT yStyleStep;      /* Height in pixels of one style unit */
    RUN runOtherCoordinate;
    union
    {
        UCHAR aj[FIELD_OFFSET(CLIPLINE, arun) + RUN_MAX * sizeof(RUN)];
        CLIPLINE cl;
    };

    /* Test hack */
    HDC hdc;

} LINEINFO, *PLINEINFO;

VOID
DibLineMajorX(
    PLINEINFO pli);

VOID
DibLineMajorY(
    PLINEINFO pli);

typedef
VOID
(*PFN_DIB_LINETO)(
    PLINEINFO pli);

#ifdef __cplusplus
}
#endif // __cplusplus
