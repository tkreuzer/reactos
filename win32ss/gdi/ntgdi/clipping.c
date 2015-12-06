/*
 * COPYRIGHT:        GNU GPL, See COPYING in the top level directory
 * PROJECT:          ReactOS Win32k subsystem
 * PURPOSE:          Clip region functions
 * FILE:             subsystems/win32/win32k/objects/cliprgn.c
 * PROGRAMER:        Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include <win32k.h>

#define NDEBUG
#include <debug.h>

#define REGION_iOffsetRgn IntGdiOffsetRgn
#define REGION_iCombine IntGdiCombineRgn
#define REGION_CreateEmptyRgn() IntSysCreateRectpRgn(0, 0, 0, 0)


/*! \name NtGdiGetRandomRgn
 *
 * \brief Retrieves a copy of one of the DCs regions.
 *
 * \param hdc
 *     Handle of the DC whose region is to be retrieved.
 *
 * \param hrgnDest
 *     Handle of a region, that will receive a copy of the requested dc region.
 *
 * \param iMode
 *     Specifies, which DC region to retrieve. Can be one of
 *         CLIPRGN (1) - The clip region as set by SelectClipRgn
 *         METARGN (2) - The meta region as set by SetMetaRgn
 *         APIRGN  (3) - The intersection of the clip and meta region.
 *         SYSRGN  (4) - The system or visible region.
 *                 (5) - Unknown
 *
 * \return 0 if the region is null, 1 if the region is not null, -1 on error.
 *
 * \note http://www.codeproject.com/gdi/cliprgnguide.asp is wrong!
 *
 * \see WINE, MSDN, OSR and
 *     "Feng Yuan - Windows Graphics Programming Win32 GDI and DirectDraw"
 */
INT
APIENTRY
NtGdiGetRandomRgn(
    _In_ HDC hdc,
    _In_ HRGN hrgnDest,
    _In_ INT iCode)
{
    INT iComplexity;
    PDC pdc;
    PRGN prgnSrc, prgnDest;

    if (iCode == 0)
        return ERROR;

    /* Lock the DC */
    pdc = DC_LockDc(hdc);
    if (!pdc)
    {
        return ERROR;
    }

    /* Lock the destination region */
    prgnDest = REGION_LockRegion(hrgnDest);
    if (!prgnDest)
    {
        DC_UnlockDc(pdc);
        return ERROR;
    }

    /* Check what kind of region was requested */
    switch (iCode)
    {
        case CLIPRGN:
            prgnSrc = pdc->dclevel.prgnClip;
            break;

        case METARGN:
            prgnSrc = pdc->dclevel.prgnMeta;
            break;

        case APIRGN:
            prgnSrc = pdc->prgnAPI;
            break;

        case SYSRGN:
            prgnSrc = pdc->prgnVis;
            break;

        case 5:
            // unknown
            prgnSrc = NULL;
            break;

        default:
            prgnSrc = NULL;
            break;
    }

    /* Check if we got a non-null region */
    if (prgnSrc)
    {
        /* Copy the region and get it's complexity */
        REGION_CopyRegion(prgnDest, prgnSrc);
        iComplexity = REGION_Complexity(prgnDest);

        /// WTF is this???
        if (iCode == SYSRGN)
            REGION_iOffsetRgn(prgnDest, pdc->ptlDCOrig.x, pdc->ptlDCOrig.y);
    }
    else
        iComplexity = NULLREGION;

    /* Unlock destination region and DC */
    REGION_UnlockRegion(prgnDest);
    DC_UnlockDc(pdc);

    /* Return the complexity */
    return iComplexity;
}


/*! \name NtGdiGetAppClipBox
 *
 * \brief Retrieves the bounding box of the DC's visible region.
 *
 * \param [in] hdc
 *     Handle of the DC whose clip box is to be retrieved.
 *
 * \param [out] prc
 *     Pointer to a RECT structure that will receive the bounding box of the
 *     visible region in logical coordinates.
 *
 * \return 0 if the region is null, 1 if the region is not null, -1 on error.
 *
 * \note
 *
 * \see WINE, MSDN, OSR and
 *     "Feng Yuan - Windows Graphics Programming Win32 GDI and DirectDraw"
 */


INT
APIENTRY
NtGdiExtSelectClipRgn(
    _In_ HDC hdc,
    _In_ HRGN hrgn,
    _In_ INT iMode)
{
    INT iComplexity;
    PDC pdc;
    PRGN prgn;

    if ((iMode < RGN_AND) || (iMode > RGN_COPY))
        return ERROR;

    /* Lock the DC */
    pdc = DC_LockDc(hdc);
    if (!pdc)
    {
        return ERROR;
    }

    /* Check if a null region was passed */
    if (hrgn == NULL)
    {
        /* Check if the caller wants to set a null region */
        if (iMode == RGN_COPY)
        {
            /* Check if there was is clip region */
            if (pdc->dclevel.prgnClip)
            {
                /* Delete the current clip region */
                REGION_DeleteRgn(pdc->dclevel.prgnClip);
                pdc->dclevel.prgnClip = NULL;
            }
            iComplexity = NULLREGION;
        }
        else
        {
            /* Other operations are not allowed */
            iComplexity = ERROR;
        }
    }
    else
    {
        /* Lock the destination region */
        prgn = REGION_LockRegion(hrgn);
        if (prgn == NULL)
        {
            DC_UnlockDc(pdc);
            return ERROR;
        }

        /* Check if there is no region */
        if (pdc->dclevel.prgnClip == NULL)
        {
            /* Create a new empty region */
            pdc->dclevel.prgnClip = REGION_CreateEmptyRgn();
            if (pdc->dclevel.prgnClip == NULL)
            {
                REGION_UnlockRegion(prgn);
                DC_UnlockDc(pdc);
                return ERROR;
            }
        }

        /* Check if the caller wants to copy the region */
        if (iMode == RGN_COPY)
        {
            /* Copy the region to the clip region and get it's complexity */
            REGION_CopyRegion(pdc->dclevel.prgnClip, prgn);
            iComplexity = REGION_Complexity(prgn);
        }
        else
        {
            /* Combine the given region with the clip region */
            iComplexity = REGION_iCombine(pdc->dclevel.prgnClip,
                                          pdc->dclevel.prgnClip,
                                          prgn,
                                          iMode);
        }

        /* Unlock the region */
        REGION_UnlockRegion(prgn);
    }

    /* Unlock the DC */
    DC_UnlockDc(pdc);

    /* Return the complexity */
    return iComplexity;
}

INT
APIENTRY
NtGdiOffsetClipRgn(
    _In_ HDC hdc,
    _In_ INT x,
    _In_ INT y)
{
}


BOOL
APIENTRY
NtGdiSelectClipPath(
    _In_ HDC hdc,
    _In_ INT iMode)
{
}


INT
APIENTRY
NtGdiSetMetaRgn(
    _In_ HDC hdc)
{
}

