/*
* PROJECT:     ReactOS Win32k subsystem
* LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
* FILE:        win32ss/gdi/eng/multidisp.c
* PURPOSE:     Muldi-Display driver
* PROGRAMMERS: Copyright 2021 Timo Kreuzer (timo.kreuzer@reactos.org)
*/

/* INCLUDES *******************************************************************/

#include <win32k.h>
#define NDEBUG
#include <debug.h>

VOID
APIENTRY
CLIPOBJ_vSetOffset(
    _Inout_ CLIPOBJ* pco,
    _In_ const POINTL pptOffset);

typedef struct _DISPLAY
{
    RECT rcDisplay;
    SURFOBJ* pso;
} DISPLAY, *PDISPLAY;

typedef struct _MULTI_PDEV
{
    HSURF hsurf;
    SURFOBJ* pso;
    ULONG cDisplays;
    PDISPLAY pDisplays;
} MULTI_PDEV, *PMULTI_PDEV;


typedef struct _MULTISURF
{
    ULONG cSurf;
    SURFOBJ** ppso;
    RECTL rcTrgFull;
    RECTL rcTrgClipped;
    POINTL ptSrcFull;
    ULONG cTrgEnumerated;
    ULONG cSrcEnumerated;
} MULTISURF, *PMULTISURF;

typedef struct _MULTISURF_ENUM
{
    SURFOBJ* psoTrg;
    SURFOBJ* psoSrc;
    RECTL rcTrg;
    POINTL ptSrc;
    POINTL ptOffset;
} MULTISURF_ENUM, *PMULTISURF_ENUM;


VOID
MULTISURF_vInit(
    _Out_ PMULTISURF pms,
    _In_ ULONG cSurf,
    _In_ SURFOBJ **ppso,
    _In_ PRECTL prcTrg,
    _In_ PPOINTL pptSrc
    )
{
    pms->cSurf = cSurf;
    pms->ppso = ppso;
    pms->rcTrgFull = *prcTrg;
    //pms->rcTrgClipped;
    pms->ptSrcFull = *pptSrc;
    pms->cTrgEnumerated = 0;
    pms->cSrcEnumerated = 0;

}

BOOL
MULTISURF_bEnumTrg(
    PMULTISURF pms,
    PRECTL prcTrg,
    PMULTISURF_ENUM pmsenum
    )
{
    SURFOBJ *psoTrg;
    PPDEVOBJ ppdev;
    RECTL rcTrgSurf;

    /* Loop the target displays */
    for (; pms->cTrgEnumerated < pms->cSurf; pms->cTrgEnumerated++)
    {
        /* Get the target surface */
        psoTrg = pms->ppso[pms->cTrgEnumerated];
        ppdev = (PPDEVOBJ)psoTrg->hdev;

        /* Calculate the target surface rect */
        rcTrgSurf.left = ppdev->ptlOrigion.x;
        rcTrgSurf.top = ppdev->ptlOrigion.y;
        rcTrgSurf.right = rcTrgSurf.left + psoTrg->sizlBitmap.cx;
        rcTrgSurf.bottom = rcTrgSurf.top + psoTrg->sizlBitmap.cy;

        /* Intersect the target rect with the target surface rect */
        if (RECTL_bIntersectRect(&pms->rcTrgClipped, prcTrg, &rcTrgSurf))
        {
            /* We found an overlap, return the data */
            pmsenum->psoTrg = psoTrg;
            pmsenum->rcTrg.left = pms->rcTrgClipped.left - ppdev->ptlOrigion.x;
            pmsenum->rcTrg.top = pms->rcTrgClipped.top - ppdev->ptlOrigion.y;
            pmsenum->rcTrg.right = pms->rcTrgClipped.right - ppdev->ptlOrigion.x;
            pmsenum->rcTrg.bottom = pms->rcTrgClipped.bottom - ppdev->ptlOrigion.y;
            pmsenum->ptOffset.x = - ppdev->ptlOrigion.x;
            pmsenum->ptOffset.y = - ppdev->ptlOrigion.y;
            pms->cTrgEnumerated++;
            return TRUE;
        }
    }

    /* Nothing left to enumerate */
    return FALSE;
}


BOOL
MULTISURF_bEnum(
    PMULTISURF pms,
    PRECTL prcTrg,
    PPOINTL pptSrc,
    PMULTISURF_ENUM pmsenum
    )
{
    SURFOBJ *psoSrc;
    PPDEVOBJ ppdev;
    RECTL rcSrc, rcSrcSurf, rcIntersect;

    do
    {
        /* Check if we have started enumerating sources */
        if (pms->cSrcEnumerated == 0)
        {
            /* Enumerate the next target display */
            if (!MULTISURF_bEnumTrg(pms, prcTrg, pmsenum))
            {
                return FALSE;
            }
        }

        /* Loop the target displays */
        for (; pms->cSrcEnumerated < pms->cSurf; pms->cSrcEnumerated++)
        {
            /* Get the target surface */
            psoSrc = pms->ppso[pms->cSrcEnumerated];
            ppdev = (PPDEVOBJ)psoSrc->hdev;

            /* Calculate the source rect */
            rcSrc.left = pptSrc->x;
            rcSrc.top = pptSrc->y;
            rcSrc.right = rcSrc.left + (pms->rcTrgClipped.right - pms->rcTrgClipped.left);
            rcSrc.bottom = rcSrc.top + (pms->rcTrgClipped.bottom - pms->rcTrgClipped.top);

            /* Calculate the source surface rect */
            rcSrcSurf.left = ppdev->ptlOrigion.x;
            rcSrcSurf.top = ppdev->ptlOrigion.y;
            rcSrcSurf.right = rcSrcSurf.left + psoSrc->sizlBitmap.cx;
            rcSrcSurf.bottom = rcSrcSurf.top + psoSrc->sizlBitmap.cy;

            /* Intersect the source rect with the source surface rect */
            if (RECTL_bIntersectRect(&rcIntersect, &rcSrc, &rcSrcSurf))
            {
                RECTL rcClip;

                /* Calculate the clipping of the source rect */
                rcClip.left = (pms->rcTrgClipped.left - rcSrc.left);
                rcClip.top = (pms->rcTrgClipped.top - rcSrc.top);
                rcClip.right = (rcSrc.top - pms->rcTrgClipped.top);
                rcClip.bottom = (rcSrc.bottom - pms->rcTrgClipped.bottom);

                /* Clip the target rect accordingly */
                pmsenum->rcTrg.left = pms->rcTrgClipped.left + rcClip.left + pmsenum->ptOffset.x;
                pmsenum->rcTrg.top = pms->rcTrgClipped.top + rcClip.top + pmsenum->ptOffset.y;
                pmsenum->rcTrg.right = pms->rcTrgClipped.right - rcClip.right + pmsenum->ptOffset.x;
                pmsenum->rcTrg.bottom = pms->rcTrgClipped.bottom - rcClip.bottom + pmsenum->ptOffset.y;

                /* We found an overlap, return the data */
                pmsenum->psoSrc = psoSrc;
                pmsenum->ptSrc.x = pms->ptSrcFull.x + rcClip.left;
                pmsenum->ptSrc.y = pms->ptSrcFull.y + rcClip.top;

                pms->cSrcEnumerated++;
                pms->cSrcEnumerated %= pms->cSurf;
                return TRUE;
            }
        }

        pms->cSrcEnumerated = 0;

    } while (pms->cTrgEnumerated < pms->cSurf);

    return FALSE;
}

#if 0
typedef struct _MULTICLIP
{
    CLIPOBJ* pco;
    const DISPLAY *pDisplays;
    ULONG cDisplays;
    RECT_ENUM rectenum;
    ULONG cEnumerated;

    RECTL rcTrg;
    RECTL rcSrc;
    BOOL bHasSrc;
    ULONG iTrgDisplay;
    ULONG iSrcDisplay;
} MULTICLIP, *PMULTICLIP;

typedef struct _MULTICLIP_ENUM
{
    SURFOBJ* psoTrg;
    SURFOBJ* psoSrc;
    RECTL rcEnumTrg;
    POINTL ptEnumSrc;
} MULTICLIP_ENUM, *PMULTICLIP_ENUM;

VOID
MULTICLIP_vInit(
    _Out_ PMULTICLIP pmc,
    _In_ CLIPOBJ *pco
    )
{
    RtlZeroMemory(pmc, sizeof(*pmc));
    pmc->pco = pco;

    CLIPOBJ_cEnumStart(pmc->pco, FALSE, CT_RECTANGLES, CD_RIGHTDOWN, 0);
}

BOOL
MULTICLIP_bEnum(
    _In_ PMULTICLIP pmc,
    _Out_ PMULTICLIP_ENUM pmcenum
    )
{
    /* Check if we need to enumerate */
    if (pmc->cEnumerated == pmc->rectenum.c)
    {
        /* Enumerate a set of rectangles */
        if (!CLIPOBJ_bEnum(pmc->pco, sizeof(pmc->rectenum), (PULONG)&pmc->rectenum))
        {
            /* There are no more rects, we are done */
            return FALSE;
        }
    }

    /* Check if we need to handle the source */
    if (pmc->psoSrc == pmc->psoTrg)
    {
        // do src target enumeration
    }
    else
    {

    }

    return FALSE;
}

VOID
MULTICLIP_vEnumStart(
    _Out_ PMULTICLIP pmc,
    _In_ ULONG cDisplays,
    _In_reads_(cDisplays) const DISPLAY *pDisplays,
    _In_ PRECTL prcTrg,
    _In_ PPOINTL pptSrc
    )
{
    pmc->cDisplays = cDisplays;
    pmc->pDisplays = pDisplays;

    pmc->rcTrg = *prcTrg;

    if (pptSrc != NULL)
    {
        pmc->bHasSrc = TRUE;
        pmc->rcSrc.left = pptSrc->x;
        pmc->rcSrc.top = pptSrc->y;
        pmc->rcSrc.right = rcSrc.left + (prcTrg->right - prcTrg->left);
        pmc->rcSrc.bottom = rcSrc.top + (prcTrg->bottom - prcTrg->top);
    }

    pmc->iTrgDisplay = 0;
    pmc->iSrcDisplay = 0;
}

BOOL
MULTICLIP_bEnum(
    _Inout_ PMULTICLIP pmc,
    _Out_ SURFOBJ **ppsoTrg,
    _Out_opt_ SURFOBJ **ppsoSrc
    )
{
    RECTL rcSrc, rcSrcClipped, rcTrgClipped;
    PRECTL prclDisplay;

    if (pmc->bHasSrc)
    {
        ASSERT(ppsoSrc != NULL);

        /* Check if we are already in enumerating sources */
        if (pmc->iSrcDisplay != 0)
        {
            goto Bypass;
        }
    }

    /* Loop the target displays */
    for (; pmc->iTrgDisplay < pmc->cDisplays; pmc->iTrgDisplay++)
    {
        /* Get the target display */
        prclDisplay = &pmc->pDisplays[pmc->iTrgDisplay].rcDisplay;

        /* Intersect the target rect with the target display */
        if (!RECTL_bIntersectRect(&rcTrgClipped, prcTrg, prclDisplay))
        {
            /* No overlap, continue with next target display */
            pmc->iSrcDisplay = 0;
            continue;
        }

Bypass:
        /* We have a target display */
        *ppsoTrg = &pmc->pDisplays[pmc->iTrgDisplay].pso;

        /* Check if we have a source */
        if (pptSrc)
        {
            /* Loop the source displays */
            for (; pmc->iSrcDisplay < pmc->cDisplays; pmc->iSrcDisplay++)
            {
                /* Get the source display */
                prclDisplay = &pmc->pDisplays[pmc->iSrcDisplay].rcDisplay;

                /* Intersect with the */
                if (RECTL_bIntersectRect(&rcSrcClipped, &rcSrc, prclDisplay))
                {
                    break;
                }
            }

            /* Check if we went past the last source display */
            if (pmc->iSrcDisplay == pmc->cDisplays)
            {
                /* Continue with the next target display */
                pmc->iSrcDisplay = 0;
                continue;
            }

            /* We have a source */
            *ppsoSrc = &pmc->pDisplays[pmc->iSrcDisplay].pso;
            pmc->iSrcDisplay++;
            break;
        }
    }

    /* Check if we went past the last target display */
    if (pmc->iTrgDisplay == pmc->cDisplays)
    {
        return FALSE;
    }


}
#endif

/* Required functions           */


DHPDEV
APIENTRY
MultiEnablePDEV(
    _In_ DEVMODEW* pdm,
    _In_ LPWSTR pwszLogAddress,
    _In_ ULONG cPat,
    _In_reads_opt_(cPat) HSURF* phsurfPatterns,
    _In_ ULONG cjCaps,
    _Out_writes_bytes_(cjCaps) ULONG* pdevcaps,
    _In_ ULONG cjDevInfo,
    _Out_writes_bytes_(cjDevInfo) DEVINFO* pdi,
    _In_ HDEV hdev,
    _In_ LPWSTR pwszDeviceName,
    _In_ HANDLE hDriver)
{
    // Allocate MULTIPDEV
    // Fill out DEVINFO
    // enumerate existing displays
    // alloate array of DISPLAY entries and fill them out
    __debugbreak();
    return NULL;
}

VOID
APIENTRY
MultiCompletePDEV(
    _In_ DHPDEV dhpdev,
    _In_ HDEV hdev)
{

}

VOID
APIENTRY
MultiDisablePDEV(
    _In_ DHPDEV dhpdev)
{

}

HSURF
APIENTRY
DrvEnableSurface(
    _In_ DHPDEV dhpdev)
{
    // Allocate DrvSurface
    // 
    return NULL;
}

VOID
APIENTRY
DrvDisableSurface(
    _In_ DHPDEV dhpdev)
{

}

#if 0

/* Other functions              */

/*
#define INDEX_DrvAssertMode                      5L
#define INDEX_DrvOffset                          6L     // Obsolete
#define INDEX_DrvResetPDEV                       7L
#define INDEX_DrvDisableDriver                   8L
#define INDEX_DrvCreateDeviceBitmap             10L
#define INDEX_DrvDeleteDeviceBitmap             11L
#define INDEX_DrvRealizeBrush                   12L
#define INDEX_DrvDitherColor                    13L
*/

BOOL
APIENTRY
MultiStrokePath(
    _Inout_ SURFOBJ* pso,
    _In_ PATHOBJ* ppo,
    _In_ CLIPOBJ* pco,
    _In_opt_ XFORMOBJ* pxo,
    _In_ BRUSHOBJ* pbo,
    _In_ POINTL* pptlBrushOrg,
    _In_ LINEATTRS* plineattrs,
    _In_ MIX mix)
{
    PMULTI_PDEV pmpdev = (PMULTI_PDEV)pso->hdev;
    PFN_DrvStrokePath pfnStrokePath;
    SURFOBJ* psoTrgDisplay;
    ULONG iTrgDisplay;

    for (iTrgDisplay = 0; iTrgDisplay < pmpdev->cDisplays; iTrgDisplay++)
    {
        psoTrgDisplay = pmpdev->pDisplays[iTrgDisplay].pso;
        pfnStrokePath = GDIDEVFUNCS(psoTrgDisplay).StrokePath;

        pfnStrokePath(psoTrgDisplay,
                      ppo,
                      pco,
                      pxo,
                      pbo,
                      pptlBrushOrg,
                      plineattrs,
                      mix);
    }

    return FALSE;
}


#define INDEX_DrvFillPath                       15L
#define INDEX_DrvStrokeAndFillPath              16L
#define INDEX_DrvPaint                          17L
#define INDEX_DrvBitBlt                         18L
#define INDEX_DrvCopyBits                       19L
#define INDEX_DrvStretchBlt                     20L
#define INDEX_DrvSetPalette                     22L
#define INDEX_DrvTextOut                        23L
#define INDEX_DrvEscape                         24L
#define INDEX_DrvDrawEscape                     25L
#define INDEX_DrvQueryFont                      26L
#define INDEX_DrvQueryFontTree                  27L
#define INDEX_DrvQueryFontData                  28L
#define INDEX_DrvSetPointerShape                29L
#define INDEX_DrvMovePointer                    30L
#define INDEX_DrvLineTo                         31L
#define INDEX_DrvSendPage                       32L
#define INDEX_DrvStartPage                      33L
#define INDEX_DrvEndDoc                         34L
#define INDEX_DrvStartDoc                       35L
#define INDEX_DrvGetGlyphMode                   37L
#define INDEX_DrvSynchronize                    38L
#define INDEX_DrvSaveScreenBits                 40L
#define INDEX_DrvGetModes                       41L
#define INDEX_DrvFree                           42L
#define INDEX_DrvDestroyFont                    43L
#define INDEX_DrvQueryFontCaps                  44L
#define INDEX_DrvLoadFontFile                   45L
#define INDEX_DrvUnloadFontFile                 46L
#define INDEX_DrvFontManagement                 47L
#define INDEX_DrvQueryTrueTypeTable             48L
#define INDEX_DrvQueryTrueTypeOutline           49L
#define INDEX_DrvGetTrueTypeFile                50L
#define INDEX_DrvQueryFontFile                  51L
#define INDEX_DrvMovePanning                    52L
#define INDEX_DrvQueryAdvanceWidths             53L
#define INDEX_DrvSetPixelFormat                 54L
#define INDEX_DrvDescribePixelFormat            55L
#define INDEX_DrvSwapBuffers                    56L
#define INDEX_DrvStartBanding                   57L
#define INDEX_DrvNextBand                       58L
#define INDEX_DrvGetDirectDrawInfo              59L
#define INDEX_DrvEnableDirectDraw               60L
#define INDEX_DrvDisableDirectDraw              61L
#define INDEX_DrvQuerySpoolType                 62L
#define INDEX_DrvIcmCreateColorTransform        64L
#define INDEX_DrvIcmDeleteColorTransform        65L
#define INDEX_DrvIcmCheckBitmapBits             66L
#define INDEX_DrvIcmSetDeviceGammaRamp          67L
#define INDEX_DrvGradientFill                   68L
#define INDEX_DrvStretchBltROP                  69L
#define INDEX_DrvPlgBlt                         70L
#define INDEX_DrvAlphaBlend                     71L
#define INDEX_DrvSynthesizeFont                 72L
#define INDEX_DrvGetSynthesizedFontFiles        73L
#define INDEX_DrvTransparentBlt                 74L
#define INDEX_DrvQueryPerBandInfo               75L
#define INDEX_DrvQueryDeviceSupport             76L

#define INDEX_DrvReserved1                      77L
#define INDEX_DrvReserved2                      78L
#define INDEX_DrvReserved3                      79L
#define INDEX_DrvReserved4                      80L
#define INDEX_DrvReserved5                      81L
#define INDEX_DrvReserved6                      82L
#define INDEX_DrvReserved7                      83L
#define INDEX_DrvReserved8                      84L

#define INDEX_DrvDeriveSurface                  85L
#define INDEX_DrvQueryGlyphAttrs                86L
#define INDEX_DrvNotify                         87L
#define INDEX_DrvSynchronizeSurface             88L
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define INDEX_DrvResetDevice                    89L
#define INDEX_DrvReserved9                      90L
#define INDEX_DrvReserved10                     91L
#define INDEX_DrvReserved11                     92L
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define INDEX_DrvRenderHint                     93L
#if (NTDDI_VERSION >= NTDDI_WIN7)
#define INDEX_DrvCreateDeviceBitmapEx           94L
#define INDEX_DrvDeleteDeviceBitmapEx           95L
#define INDEX_DrvAssociateSharedSurface         96L
#define INDEX_DrvSynchronizeRedirectionBitmaps  97L
#define INDEX_DrvAccumulateD3DDirtyRect         98L
#define INDEX_DrvStartDxInterop                 99L
#define INDEX_DrvEndDxInterop                   100L
#define INDEX_DrvLockDisplayArea                101L
#define INDEX_DrvUnlockDisplayArea              102L
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1 )
#define INDEX_DrvSurfaceComplete                103L
#endif // (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#endif // (NTDDI_VERSION >= NTDDI_WIN7)
#endif // (NTDDI_VERSION >= NTDDI_VISTA)
#endif // (NTDDI_VERSION >= NTDDI_WINXP)
/* The total number of dispatched functions */
*/
#endif


static DRVFN gadrvfn[] =
{
    {   INDEX_DrvEnablePDEV,            (PFN) MultiEnablePDEV         },
    {   INDEX_DrvCompletePDEV,          (PFN) MultiCompletePDEV       },
    {   INDEX_DrvDisablePDEV,           (PFN) MultiDisablePDEV        },
//    {   INDEX_DrvEnableSurface,         (PFN) MultiEnableSurface      },
//    {   INDEX_DrvDisableSurface,        (PFN) MultiDisableSurface     },
//    {   INDEX_DrvAssertMode,            (PFN) MultiAssertMode         },
//    {   INDEX_DrvSetPalette,            (PFN) MultiSetPalette         },
//    {   INDEX_DrvMovePointer,           (PFN) MultiMovePointer        },
//    {   INDEX_DrvSetPointerShape,       (PFN) MultiSetPointerShape    },

};

BOOL
APIENTRY
MultiEnableDriver(
    _In_ ULONG iEngineVersion,
    _In_ ULONG cj,
    _Inout_bytecount_(cj) PDRVENABLEDATA pded)
{
    if (cj < sizeof(DRVENABLEDATA))
    {
        return FALSE;
    }

    pded->pdrvfn = gadrvfn;
    pded->c = sizeof(gadrvfn) / sizeof(DRVFN);
    pded->iDriverVersion = GDI_DRIVER_VERSION;

    return TRUE;
}
