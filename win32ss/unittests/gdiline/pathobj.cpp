
/*!

    \References

    - http://ideone.com/D0eX7F
    - https://gist.github.com/hunt978/6648097
    - https://www.exploit-db.com/exploits/25611/


*/


#include <windows.h>
#include "eng.h"
#include "pathobj.hpp"

// HACK
ULONG
APIENTRY
CLIPOBJ_cEnumStart(
    _Inout_ CLIPOBJ *pco,
    _In_ BOOL bAll,
    _In_ ULONG iType,
    _In_ ULONG iDirection,
    _In_ ULONG cMaxRects)
{
    return 1;
}

FORCEINLINE
BOOL
ClipLineToRect(
    _In_ PPOINTFIX pptfxA,
    _In_ PPOINTFIX pptfxB,
    _In_ PRECTFX prcfxClip,
    _Out_ PRUN prunX,
    _Out_ PRUN prunY)
{
    LONG x1, y1, x2, y2, cx, cy;
    LONG xMin, xMax, yMin, yMax;

    xMin = prcfxClip->xLeft;
    xMax = prcfxClip->xRight;
    yMin = prcfxClip->yTop;
    yMax = prcfxClip->yBottom;

    x1 = pptfxA->x;
    x2 = pptfxB->x;
    if (x2 < x1)
    {
        x1 = pptfxB->x;
        x2 = pptfxA->x;
    }

    /* Check if everything is clipped away */
    if ((x2 < xMin) || (x1 > xMax))
    {
        return FALSE;
    }

    y1 = pptfxA->y;
    y2 = pptfxB->y;
    if (x2 < x1)
    {
        SwapLongs(&y1, &y2);
    }

    /* Check if everything is clipped away */
    if ((y2 < yMin) || (y1 > yMax))
    {
        return FALSE;
    }

    cx = x2 - x1;
    cy = y2 - y1;

    /* Check if we need to clip on the left side */
    if (x1 < xMin)
    {
        /* Calculate the related y adjustment */
        LONG cyClip = MulDiv(xMin - x1, cy, cx);

        y1 += cyClip;

        x1 = xMin;
    }

    /* Check if we need to clip on the top side */
    if (y1 < yMin)
    {
        /* Calculate the related x adjustment */
        LONG cxClip = MulDiv(yMin - y1, cx, cy);

        x1 += cxClip;

        y1 = yMin;
    }

    /* Check if we need to clip on the right side */
    if (x2 > xMax)
    {
        /* Calculate the related new y extent */
        LONG cyNew = MulDiv(xMax - x1, cy, cx);

        y2 = y1 + cyNew;

        x2 = xMax;
    }


    /* Check if we need to clip on the bottom side */
    if (y2 > yMax)
    {
        /* Calculate the related new x extent */
        LONG cxNew = MulDiv(yMax - y1, cx, cy);

        x2 = x1 + cxNew;

        y2 = yMax;
    }

    /* Now everything should be clipped */
    NT_ASSERT(x1 >= xMin);
    NT_ASSERT(x2 < xMax);
    NT_ASSERT(y1 >= yMin);
    NT_ASSERT(y2 < yMax);

    NT_ASSERT(x1 < x2);
    NT_ASSERT(y1 < y2);

    return TRUE;
}


/*
           #######
        ++
      #   +**
      #      **
      #        **
                 +++
                    ++

*/

BOOL
NTAPI
CLIPOBJ_bEnumClipLines(
    _Inout_ CLIPOBJ *pco,
    _In_ const POINTFIX *pptfx,
    _In_ ULONG cj,
    _Out_ CLIPLINE *pcl)
{
#if 1
    LONG cx, cy, iStart, iStop;

    /* Copy the coordinates */
    pcl->ptfxA = pptfx[0];
    pcl->ptfxB = pptfx[1];

    pcl->c = 1;

    cx = abs(pcl->ptfxB.x - pcl->ptfxA.x);
    cy = abs(pcl->ptfxB.y - pcl->ptfxA.y);

    if (cx > cy)
    {
        iStart = FIX2LONG(pcl->ptfxA.x);
        iStop = FIX2LONG(pcl->ptfxB.x);
    }
    else
    {
        iStart = FIX2LONG(pcl->ptfxA.y);
        iStop = FIX2LONG(pcl->ptfxB.y);
    }

    if (iStop < iStart)
    {
        SwapLongs(&pcl->ptfxA.x, &pcl->ptfxB.x);
        SwapLongs(&pcl->ptfxA.y, &pcl->ptfxB.y);
        SwapLongs(&iStart, &iStop);
    }

    pcl->arun[0].iStart = iStart;
    pcl->arun[0].iStop = iStop;

    return FALSE;
#else
    RECTFX rcfxClip;
    RUN runX, runY;

    if (Clip->EnumPos >= pco->EnumMax)
    {
        return FALSE;
    }


    do
    {

        src = &Clip->Rects[Clip->EnumPos];

        rcfxClip.xLeft =

        ClipLineToRect(&pptfx[0],
                       &pptfx[1],
                       &rcfxClip,
                       &runX,
                       &runY);
    } while ();

#endif
}

EPATHOBJ::EPATHOBJ(
    VOID)
{
    fl = 0;
    cCurves = 1;
}

EPATHOBJ::~EPATHOBJ(
    VOID)
{

    if (_ppath != NULL)
    {

    }

}

BOOL
EPATHOBJ::bAllocatePath(
    VOID)
{
    return FALSE;
}

VOID
EPATHOBJ::vEnumStart(
    VOID)
{
}

BOOL
EPATHOBJ::bEnum(
    _Out_ PATHDATA *ppd)
{
    return TRUE;
}

VOID
EPATHOBJ::vEnumStartClipLines(
    _Inout_ CLIPOBJ *pco,
    _In_ SURFOBJ *pso,
    _In_ LINEATTRS *pla)
{
    vEnumStart();

    _pco = pco;
    _pdEnum.count = 0;
    _bMorePaths = TRUE;
    _bMoreClips = FALSE;
}

BOOL
EPATHOBJ::bEnumClipLines(
    _In_ ULONG cj,
    _Out_ CLIPLINE *pcl)
{
    /* Check if we can enumerate more clip lines */
    if (!_bMoreClips)
    {
        /* We need at least 2 points (> since we check the old state) */
        if (_pdEnum.count > 2)
        {
            /* We have at least 2 more points, grab the next one */
            _pdEnum.pptfx++;
            _pdEnum.count--;
        }
        else
        {
            /* There are no more points left, we need to enumerate more */
            do
            {
                /* Check if there are more paths */
                if (!_bMorePaths)
                {
                    /* There is nothing more we can do! */
                    return FALSE;
                }

                /* Enumerate a path entry */
                _bMorePaths = this->bEnum(&_pdEnum);

            /* Repeat until we have at least 2 */
            } while (_pdEnum.count < 2);
        }

        /* Reset the clip object for the next path */
        CLIPOBJ_cEnumStart(_pco, FALSE, CT_RECTANGLES, CD_RIGHTDOWN, 0);
    }

    /* Do another enumeration */
    _bMoreClips = CLIPOBJ_bEnumClipLines(_pco, _pdEnum.pptfx, cj, pcl);
    return _bMoreClips;
}


__drv_allocatesMem(Mem)
PATHOBJ*
APIENTRY
EngCreatePath(
    VOID)
{
    EPATHOBJ *pepo;

    pepo = new EPATHOBJ;
    if (pepo == NULL)
    {
        return NULL;
    }

    if (!pepo->bAllocatePath())
    {
        delete pepo;
        return NULL;
    }

    return pepo;
}

VOID
APIENTRY
EngDeletePath(
    _Inout_ _Post_ptr_invalid_ PATHOBJ *ppo)
{
    EPATHOBJ *pepo = reinterpret_cast<EPATHOBJ*>(ppo);
    delete pepo;
}

BOOL
APIENTRY
PATHOBJ_bCloseFigure(
    _Inout_ PATHOBJ *ppo)
{
    // www.osr.com/ddk/graphics/gdifncs_5mhz.htm
    return reinterpret_cast<EPATHOBJ*>(ppo)->bCloseFigure();
}

BOOL
APIENTRY
PATHOBJ_bEnum(
    _Inout_ PATHOBJ *ppo,
    _Out_ PATHDATA *ppd)
{
    // www.osr.com/ddk/graphics/gdifncs_98o7.htm
    return reinterpret_cast<EPATHOBJ*>(ppo)->bEnum(ppd);
}

BOOL
APIENTRY
PATHOBJ_bEnumClipLines(
    _Inout_ PATHOBJ *ppo,
    _In_ ULONG cj,
    _Out_ CLIPLINE *pcl)
{
    // www.osr.com/ddk/graphics/gdifncs_4147.htm
    return reinterpret_cast<EPATHOBJ*>(ppo)->bEnumClipLines(cj, pcl);
}

BOOL
APIENTRY
PATHOBJ_bMoveTo(
    _Inout_ PATHOBJ *ppo,
    _In_ POINTFIX ptfx)
{
    // www.osr.com/ddk/graphics/gdifncs_70vb.htm
    return reinterpret_cast<EPATHOBJ*>(ppo)->bMoveTo(ptfx);
}

BOOL
APIENTRY
PATHOBJ_bPolyBezierTo(
    _Inout_ PATHOBJ *ppo,
    _In_ POINTFIX *pptfx,
    _In_ ULONG cptfx)
{
    // www.osr.com/ddk/graphics/gdifncs_2c9z.htm
    return reinterpret_cast<EPATHOBJ*>(ppo)->bPolyBezierTo(pptfx, cptfx);
}

BOOL
APIENTRY
PATHOBJ_bPolyLineTo(
    _Inout_ PATHOBJ *ppo,
    _In_ POINTFIX *pptfx,
    _In_ ULONG cptfx)
{
    // www.osr.com/ddk/graphics/gdifncs_0x47.htm
    return reinterpret_cast<EPATHOBJ*>(ppo)->bPolyLineTo(pptfx, cptfx);
}

VOID
APIENTRY
PATHOBJ_vEnumStart(
    _Inout_ PATHOBJ *ppo)
{
    // www.osr.com/ddk/graphics/gdifncs_74br.htm
    UNIMPLEMENTED;
}

VOID
APIENTRY
PATHOBJ_vEnumStartClipLines(
    _Inout_ PATHOBJ *ppo,
    _Inout_ CLIPOBJ *pco,
    _In_ SURFOBJ *pso,
    _In_ LINEATTRS *pla)
{
    // www.osr.com/ddk/graphics/gdifncs_5grr.htm
    UNIMPLEMENTED;
}

VOID
APIENTRY
PATHOBJ_vGetBounds(
    _In_ PATHOBJ *ppo,
    OUT PRECTFX prectfx)
{
    // www.osr.com/ddk/graphics/gdifncs_8qp3.htm
    UNIMPLEMENTED;
}

