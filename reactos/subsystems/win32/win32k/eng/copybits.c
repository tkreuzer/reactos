/*
 *  ReactOS W32 Subsystem
 *  Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003 ReactOS Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
/*
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * PURPOSE:          GDI EngCopyBits Function
 * FILE:             subsys/win32k/eng/copybits.c
 * PROGRAMER:        Jason Filby
 * REVISION HISTORY:
 *        8/18/1999: Created
 */

#include <win32k.h>

#define NDEBUG
#include <debug.h>

/*
 * @implemented
 */
BOOL APIENTRY
EngCopyBits(SURFOBJ *psoDest,
            SURFOBJ *psoSource,
            CLIPOBJ *Clip,
            XLATEOBJ *ColorTranslation,
            RECTL *DestRect,
            POINTL *SourcePoint)
{
    BOOL      ret;
    BYTE      clippingType;
    RECT_ENUM RectEnum;
    BOOL      EnumMore;
    BLTINFO   BltInfo;
    SURFACE *psurfDest;
    SURFACE *psurfSource;

    ASSERT(psoDest != NULL && psoSource != NULL && DestRect != NULL && SourcePoint != NULL);

    psurfSource = CONTAINING_RECORD(psoSource, SURFACE, SurfObj);
    SURFACE_LockBitmapBits(psurfSource);

    psurfDest = CONTAINING_RECORD(psoDest, SURFACE, SurfObj);
    if (psoDest != psoSource)
    {
        SURFACE_LockBitmapBits(psurfDest);
    }

    // FIXME: Don't punt to the driver's DrvCopyBits immediately. Instead,
    //        mark the copy block function to be DrvCopyBits instead of the
    //        GDI's copy bit function so as to remove clipping from the
    //        driver's responsibility

    // If one of the surfaces isn't managed by the GDI
    if ((psoDest->iType!=STYPE_BITMAP) || (psoSource->iType!=STYPE_BITMAP))
    {
        // Destination surface is device managed
        if (psoDest->iType!=STYPE_BITMAP)
        {
            /* FIXME: Eng* functions shouldn't call Drv* functions. ? */
            if (psurfDest->flHooks & HOOK_COPYBITS)
            {
                ret = GDIDEVFUNCS(psoDest).CopyBits(
                          psoDest, psoSource, Clip, ColorTranslation, DestRect, SourcePoint);

                goto cleanup;
            }
        }

        // Source surface is device managed
        if (psoSource->iType!=STYPE_BITMAP)
        {
            /* FIXME: Eng* functions shouldn't call Drv* functions. ? */
            if (psurfSource->flHooks & HOOK_COPYBITS)
            {
                ret = GDIDEVFUNCS(psoSource).CopyBits(
                          psoDest, psoSource, Clip, ColorTranslation, DestRect, SourcePoint);

                goto cleanup;
            }
        }

        // If CopyBits wasn't hooked, BitBlt must be
        ret = IntEngBitBlt(psoDest, psoSource,
                           NULL, Clip, ColorTranslation, DestRect, SourcePoint,
                           NULL, NULL, NULL, ROP3_TO_ROP4(SRCCOPY));

        goto cleanup;
    }

    // Determine clipping type
    if (!Clip)
    {
        clippingType = DC_TRIVIAL;
    }
    else
    {
        clippingType = Clip->iDComplexity;
    }

    BltInfo.DestSurface = psoDest;
    BltInfo.SourceSurface = psoSource;
    BltInfo.PatternSurface = NULL;
    BltInfo.XlateSourceToDest = ColorTranslation;
    BltInfo.Rop4 = SRCCOPY;

    switch (clippingType)
    {
        case DC_TRIVIAL:
            BltInfo.DestRect = *DestRect;
            BltInfo.SourcePoint = *SourcePoint;

            ret = DibFunctionsForBitmapFormat[psoDest->iBitmapFormat].DIB_BitBltSrcCopy(&BltInfo);
            break;

        case DC_RECT:
            // Clip the blt to the clip rectangle
            RECTL_bIntersectRect(&BltInfo.DestRect, DestRect, &Clip->rclBounds);

            BltInfo.SourcePoint.x = SourcePoint->x + BltInfo.DestRect.left - DestRect->left;
            BltInfo.SourcePoint.y = SourcePoint->y + BltInfo.DestRect.top  - DestRect->top;

            ret = DibFunctionsForBitmapFormat[psoDest->iBitmapFormat].DIB_BitBltSrcCopy(&BltInfo);
            break;

        case DC_COMPLEX:

            CLIPOBJ_cEnumStart(Clip, FALSE, CT_RECTANGLES, CD_ANY, 0);

            do
            {
                EnumMore = CLIPOBJ_bEnum(Clip,(ULONG) sizeof(RectEnum), (PVOID) &RectEnum);

                if (RectEnum.c > 0)
                {
                    RECTL* prclEnd = &RectEnum.arcl[RectEnum.c];
                    RECTL* prcl    = &RectEnum.arcl[0];

                    do
                    {
                        RECTL_bIntersectRect(&BltInfo.DestRect, prcl, DestRect);

                        BltInfo.SourcePoint.x = SourcePoint->x + prcl->left - DestRect->left;
                        BltInfo.SourcePoint.y = SourcePoint->y + prcl->top - DestRect->top;

                        if (!DibFunctionsForBitmapFormat[psoDest->iBitmapFormat].DIB_BitBltSrcCopy(&BltInfo))
                        {
                            ret = FALSE;
                            goto cleanup;
                        }

                        prcl++;

                    } while (prcl < prclEnd);
                }

            } while (EnumMore);
            ret = TRUE;
            break;

        default:
            ASSERT(FALSE);
            ret = FALSE;
            break;
    }

cleanup:
    if (psoDest != psoSource)
    {
        SURFACE_UnlockBitmapBits(psurfDest);
    }
    SURFACE_UnlockBitmapBits(psurfSource);

    return ret;
}

BOOL APIENTRY
IntEngCopyBits(
    SURFOBJ *psoDest,
    SURFOBJ *psoSource,
    CLIPOBJ *pco,
    XLATEOBJ *pxlo,
    RECTL *prclDest,
    POINTL *ptlSource)
{
    BOOL bResult;

    MouseSafetyOnDrawStart(psoSource, ptlSource->x, ptlSource->y,
                           (ptlSource->x + abs(prclDest->right - prclDest->left)),
                           (ptlSource->y + abs(prclDest->bottom - prclDest->top)));

    MouseSafetyOnDrawStart(psoDest, prclDest->left, prclDest->top, prclDest->right, prclDest->bottom);

    bResult = EngCopyBits(psoDest, psoSource, pco, pxlo, prclDest, ptlSource);

    MouseSafetyOnDrawEnd(psoDest);
    MouseSafetyOnDrawEnd(psoSource);

    return bResult;
}


/* EOF */