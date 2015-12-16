/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS win32 subsystem
 * PURPOSE:           EngLineTo implementation
 * PROGRAMER:         Timo Kreuzer (timo.kreuzer@reactos.org)
 *
 * REFERENCES:
 */

#include <win32k.h>
#include "../diblib/DibLib_interface.h"

DBG_DEFAULT_CHANNEL(EngLine);

// FIXME: move to header
extern "C"
BOOL
NTAPI
CLIPOBJ_bEnumClipLines(
    _Inout_ CLIPOBJ *pco,
    _In_ const POINTFIX pptfx[2],
    _In_ ULONG cj,
    _Out_ CLIPLINE *pcl);

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
    LINEATTRS lineattrs = { 0 };
    BOOL bResult;

    /// setup a 1 line EPATHOBJ


    lineattrs.fl = 0;
    lineattrs.iJoin = 0;
    lineattrs.iEndCap = 0;
    lineattrs.elWidth.l = 1;
    //lineattrs.eMiterLimit = 0;
    lineattrs.cstyle = 0;
    lineattrs.pstyle = 0;
    lineattrs.elStyleState.l = 0;

    pfnStrokePath = GDIDEVFUNCS(pso).StrokePath;
    bResult = pfnStrokePath(pso,
                            &epo.po,
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
    _Out_ PLINEINFO pli,
    _In_ SURFOBJ *pso,
    _In_ BRUSHOBJ *pbo
    )
{
    PPDEVOBJ ppdev;

    ppdev = (PPDEVOBJ)pso->hdev;

    // HACK!
    ppdev->gdiinfo.xStyleStep = 3;
    ppdev->gdiinfo.yStyleStep = 3;

    pli->ulColor = pbo->iSolidColor;

}

extern "C" {

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
    ULONG i;

    /// FIXME: need to test this
    if (pso->iType != STYPE_BITMAP)
    {
        NT_ASSERT(FALSE);
        return FALSE;
    }

    InitializeLineInfo(&li, pso, pbo);

    /* Setup the point array for enumeration */
    aptfx[0].x = x1;
    aptfx[0].y = y1;
    aptfx[1].x = x2;
    aptfx[1].y = y2;

    /* If no clip object is given, use trivial one */
    if (!pco) pco = (CLIPOBJ*)&gxcoTrivial;

    CLIPOBJ_cEnumStart(pco, FALSE, CT_RECTANGLES, CD_RIGHTDOWN, 0);

    do
    {
        /* Enumerate clip lines */
        bEnumMore = CLIPOBJ_bEnumClipLines(pco, aptfx, sizeof(li.aj), &li.cl);

        /* Loop all runs we got */
        for (i = 0; i < li.cl.c; i++)
        {
            li.runOtherCoordinate.iStart = y1;
            li.runOtherCoordinate.iStop = y2;


            //InitializeLineInfo(&li, &pfnLineTo, &ppdev->gdiinfo, pso, pbo, NULL);
            pfnLineTo = 0;

            pfnLineTo(&li);
        }

    } while (bEnumMore);

    return FALSE;
}

BOOL
NTAPI
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
    if (SURFOBJ_flags(pso) & HOOK_LINETO)
    {
        pfnLineTo = GDIDEVFUNCS(pso).LineTo;
        bResult = pfnLineTo(pso, pco, pbo, x1, y1, x2, y2, prclBounds, mix);
        if (bResult)
        {
            return TRUE;
        }
    }

    /* Check if DrvStrokePath function is hooked or we don't have a bitmap */
    if ((SURFOBJ_flags(pso) & HOOK_STROKEPATH) ||
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

BOOL
NTAPI
IntEngPolyline(
    _Inout_ SURFOBJ *pso,
    _In_ CLIPOBJ *pco,
    _In_ BRUSHOBJ *pbo,
    _In_ const POINT *pt,
    _In_ LONG cpt,
    _In_ MIX mix)
{
    BOOL bResult = FALSE;
    ULONG i;
    RECTL rcBounds;

    for (i = 1; i < cpt; i++)
    {
        rcBounds.left = min(pt[i-1].x, pt[i].x);
        rcBounds.top = min(pt[i-1].y, pt[i].y);
        rcBounds.right = max(pt[i-1].x, pt[i].x);
        rcBounds.bottom = max(pt[i-1].y, pt[i].y);

        bResult = IntEngLineTo(pso,
                               pco,
                               pbo,
                               pt[i-1].x,
                               pt[i-1].y,
                               pt[i].x,
                               pt[i].y,
                               &rcBounds,
                               mix);
        if (!bResult)
        {
            break;
        }
    }

    return bResult;
}


} // extern "C"
