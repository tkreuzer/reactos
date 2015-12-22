
#include "DibLine.h"

VOID
SetPixel2(
    HDC hdc,
    LONG x,
    LONG y,
    COLORREF cr)
{
    COLORREF crOld = GetPixel(hdc, x, y);

    if (crOld == 0x00FF00)
    {
        SetPixel(hdc, x, y, cr);
    }
    else
    {
        SetPixel(hdc, x, y, 0x0000FF);
    }
}

FORCEINLINE
VOID
SkipPixels(
    LONG cx,
    PLINEINFO pli,
    LONG *px,
    LONG *py,
    LONG dy,
    LONG *plGamma)
{
    LONGLONG llDelta;

    *px += cx;

    llDelta = Int32x32To64(cx, pli->lNumerator);

    *py += dy * (LONG)(llDelta / pli->lDenominator);

    *plGamma -= (LONG)(llDelta % pli->lDenominator);

    if (*plGamma < 0)
    {
        *py += dy;
        *plGamma += pli->lDenominator;
    }
}

#define DibLine DibLineMajorX
#define _PutPixel(pli, x, y) SetPixel2(pli->hdc, x, y, pli->ulColor)
#include "DibLine.c"

#undef DibLine
#undef _PutPixel

#define DibLine DibLineMajorY
#define _PutPixel(pli, x, y) SetPixel2(pli->hdc, y, x, pli->ulColor)
#include "DibLine.c"

