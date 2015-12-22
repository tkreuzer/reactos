
#include "eng.h"
#include "DibLine.h"
#include "pathobj.hpp"

static
BOOL
IntStrokeTo(
    _Inout_ SURFOBJ *pso,
    _In_ CLIPOBJ *pco,
    _In_ BRUSHOBJ *pbo,
    _In_ LONG x1,
    _In_ LONG y1,
    _In_ LONG x2,
    _In_ LONG y2,
    _In_opt_ RECTL *prclBounds,
    _In_ MIX mix)
{
    PFN_DrvStrokePath pfnStrokePath;
    EPATHOBJ epo;
    LINEATTRS lineattrs;
    BOOL bResult;


    pfnStrokePath = GDIDEVFUNCS(pso).StrokePath;
    bResult = pfnStrokePath(pso,
                            &epo,
                            pco,
                            NULL, // pxo
                            pbo,
                            NULL, // pptlBrushOrg
                            &lineattrs,
                            mix);

    return bResult;
}


VOID
InitializeLineInfo(
    _Inout_ PLINEINFO pli,
    _Out_ PFN_DIB_LINETO *ppfnLineTo,
    _In_ PGDIINFO pgdiinfo,
    _In_ SURFOBJ *pso,
    _In_ BRUSHOBJ *pbo,
    _In_ POINTL *pptlBrushOrg)
{
    LONG cx, cy, lBrushOrg, yxStyleStep, cxyStyleSize;
    ULONG xyStyle;

    pli->dx = 1;
    pli->dy = 1;

    cx = abs(pli->cl.ptfxB.x - pli->cl.ptfxA.x);
    cy = abs(pli->cl.ptfxB.y - pli->cl.ptfxA.y);

    /// FIXME: we need to check whether rounding takes place before direction decision!
    if (cx > cy)
    {
        if (pli->cl.ptfxB.x < pli->cl.ptfxA.x)
        {
            SwapLongs(&pli->cl.ptfxA.x, &pli->cl.ptfxB.x);
            SwapLongs(&pli->cl.ptfxA.y, &pli->cl.ptfxB.y);
        }

        /// \todo FIXME: calculate y start
        pli->runOtherCoordinate.iStart = pli->cl.ptfxA.y / 16;
        pli->runOtherCoordinate.iStop = pli->cl.ptfxB.y / 16;

        if (pli->runOtherCoordinate.iStart >
            pli->runOtherCoordinate.iStop)
        {
            pli->runOtherCoordinate.iStart++;
            pli->runOtherCoordinate.iStop++;
            pli->dy = -1;
        }

        *ppfnLineTo = DibLineMajorX;

        pli->lNumerator = FIX2LONG(cy);
        pli->lDenominator = FIX2LONG(cx);

        lBrushOrg = pptlBrushOrg ? pptlBrushOrg->x : 0;
        yxStyleStep = pgdiinfo->xStyleStep;
    }
    else
    {
        if (pli->cl.ptfxB.x < pli->cl.ptfxA.x)
        {
            SwapLongs(&pli->cl.ptfxA.x, &pli->cl.ptfxB.x);
            SwapLongs(&pli->cl.ptfxA.y, &pli->cl.ptfxB.y);
            //SwapLongs(&pli->cl.arun[0].iStart, &pli->cl.arun[0].iStop); // HACK

            /// \todo FIXME: calculate y start
            pli->runOtherCoordinate.iStart = pli->cl.ptfxA.x / 16;
            pli->runOtherCoordinate.iStop = pli->cl.ptfxB.x / 16;
        }
        else
        {
            /// \todo FIXME: calculate y start
            pli->runOtherCoordinate.iStart = pli->cl.ptfxA.x / 16;
            pli->runOtherCoordinate.iStop = pli->cl.ptfxB.x / 16;
        }



        *ppfnLineTo = DibLineMajorY;

        pli->lNumerator = FIX2LONG(cx);
        pli->lDenominator = FIX2LONG(cy);

        lBrushOrg = pptlBrushOrg ? pptlBrushOrg->y : 0;
        yxStyleStep = pgdiinfo->yStyleStep;
    }

    pli->lRemainder = pli->lDenominator / 2;


    PEBRUSHOBJ pebo = (PEBRUSHOBJ)pbo;
    pli->cStyles = pebo->cStyles;

    if (pli->cStyles > 0)
    {
        cxyStyleSize = 0;
        for (ULONG i = 0; i < pli->cStyles; i++)
        {
            pli->acxyStyle[i] = pebo->pulStyles[i] * yxStyleStep;
            cxyStyleSize += pli->acxyStyle[i];
        }

        pli->cxyStyleSize = cxyStyleSize;

        xyStyle = (pli->cl.arun[0].iStart + lBrushOrg) % cxyStyleSize;

        for (ULONG i = 0; i < pli->cStyles; i++)
        {

            if (xyStyle < pli->acxyStyle[i])
            {
                pli->iStyle = i;
                break;
            }

            xyStyle -= pli->acxyStyle[i];
        }

        pli->xyStylePos = xyStyle;
    }

    PSURFACE ps = CONTAINING_RECORD(pso, SURFACE, so);
    pli->hdc = ps->hdc;
}

GDIINFO g_gdiinfo;

BOOL
APIENTRY
EngLineTo(
    _Inout_ SURFOBJ *pso,
    _In_ CLIPOBJ *pco,
    _In_ BRUSHOBJ *pbo,
    _In_ LONG x1,
    _In_ LONG y1,
    _In_ LONG x2,
    _In_ LONG y2,
    _In_opt_ RECTL *prclBounds,
    _In_ MIX mix)
{
    LINEINFO li;
    PFN_DIB_LINETO pfnLineTo;
    BOOL bEnumMore;
    POINTFIX aptfx[2];

    /* Setup the point array for enumeration */
    aptfx[0].x = x1;
    aptfx[0].y = y1;
    aptfx[1].x = x2;
    aptfx[1].y = y2;

    CLIPOBJ_cEnumStart(pco, FALSE, CT_RECTANGLES, CD_RIGHTDOWN, 0);

    do
    {
        /* Enumerate clip lines */
        bEnumMore = CLIPOBJ_bEnumClipLines(pco, aptfx, sizeof(li.aj), &li.cl);

        li.runOtherCoordinate.iStart = y1;
        li.runOtherCoordinate.iStop = y2;
        li.ulColor = 0;

        g_gdiinfo.xStyleStep = 3;
        g_gdiinfo.yStyleStep = 3;

        InitializeLineInfo(&li, &pfnLineTo, &g_gdiinfo, pso, pbo, NULL);

        if (pso->iType != STYPE_BITMAP)
        {
            NT_ASSERT(FALSE);
        }

        pfnLineTo(&li);

    } while (bEnumMore);

    return FALSE;
}

BOOL
APIENTRY
IntEngLineTo(
    _Inout_ SURFOBJ *pso,
    _In_ CLIPOBJ *pco,
    _In_ BRUSHOBJ *pbo,
    _In_ LONG x1,
    _In_ LONG y1,
    _In_ LONG x2,
    _In_ LONG y2,
    _In_opt_ RECTL *prclBounds,
    _In_ MIX mix)
{
    PFN_DrvLineTo pfnLineTo;
    BOOL bResult;

    /* Check if DrvLineTo function is hooked */
    if (SURFOBJ_flags(psoTrg) & HOOK_LINETO)
    {
        pfnLineTo = GDIDEVFUNCS(pso).LineTo;
        bResult = pfnLineTo(pso, pco, pbo, x1, y1, x2, y2, prclBounds, mix);
        if (bResult)
        {
            return TRUE;
        }
    }

    /* Check if DrvStrokePath function is hooked or we don't have a bitmap */
    if ((SURFOBJ_flags(psoTrg) & HOOK_STROKEPATH) ||
        (pso->iType != STYPE_BITMAP))
    {
        bResult = IntStrokeTo(pso, pco, pbo, x1, y1, x2, y2, prclBounds, mix);
    }
    else
    {
        bResult = EngLineTo(pso, pco, pbo, x1, y1, x2, y2, prclBounds, mix);
    }

    return FALSE;
}
