
#include "dc.hpp"
#include "pdev.hpp"
#include "surface.hpp"

#define DIRTY_DEFAULT DIRTY_CHARSET|DIRTY_BACKGROUND|DIRTY_TEXT|DIRTY_LINE|DIRTY_FILL

PDC defaultDCstate;

typedef struct _DC_INFO
{
    HSURF hsurf;
    HBRUSH hbr;
    HPEN hpen;
    HFONT hfont;
    HPALETTE hpal;
    ULONG iMapMode;
    XFORM xformWorldToPage;
} DC_INFO, *PDC_INFO;

BOOL
GetDcInfo(
    _In_ HDC hdc,
    _Out_ PDC_INFO pdcinfo)
{

    pdcinfo->hsurf = (HSURF)GetCurrentObject(hdc, OBJ_BITMAP);
    pdcinfo->hbr = (HBRUSH)GetCurrentObject(hdc, OBJ_BRUSH);
    pdcinfo->hpen = (HPEN)GetCurrentObject(hdc, OBJ_PEN);
    pdcinfo->hfont = (HFONT)GetCurrentObject(hdc, OBJ_FONT);
    pdcinfo->hpal = (HPALETTE)GetCurrentObject(hdc, OBJ_PAL);
    pdcinfo->iMapMode = GetMapMode(hdc);


    if ((pdcinfo->hsurf == NULL) ||
        (pdcinfo->hbr == NULL) ||
        (pdcinfo->hpen == NULL) ||
        (pdcinfo->hfont == NULL) ||
        (pdcinfo->hpal == NULL) ||
        (pdcinfo->iMapMode == 0)
        )
    {
        return FALSE;
    }

    if (!GetWorldTransform(hdc, &pdcinfo->xformWorldToPage))
    {
        return FALSE;
    }

    return TRUE;
}

PDC
GetDc(
    _In_ HDC hdc)
{
    DC_INFO dcinfo;
    PDC pdc;
    PPDEVOBJ ppdev = gppdevPrimary;

    if (!GetDcInfo(hdc, &dcinfo))
    {
        return NULL;
    }

    pdc = (PDC)EngAllocMem(FL_ZERO_MEMORY, sizeof(DC), 'CD');
    if (pdc == NULL)
    {
        return NULL;
    }

    /* Setup some basic fields */
    pdc->dctype = DCTYPE_MEMORY;
    pdc->ppdev = ppdev;
    pdc->dhpdev = ppdev->dhpdev;
    pdc->hsem = ppdev->hsemDevLock;
    pdc->flGraphicsCaps = ppdev->devinfo.flGraphicsCaps;
    pdc->flGraphicsCaps2 = ppdev->devinfo.flGraphicsCaps2;
    pdc->fs = DC_DIRTY_RAO;

    /* Setup dc attribute */
    pdc->pdcattr = &pdc->dcattr;
    pdc->dcattr.pvLDC = NULL;
    pdc->dcattr.ulDirty_ = DIRTY_DEFAULT;

    /* Memory DCs have a 1 x 1 bitmap by default */
    pdc->dclevel.sizl.cx = 1;
    pdc->dclevel.sizl.cy = 1;

    /* Setup Window rect based on DC size */
    pdc->erclWindow.left = 0;
    pdc->erclWindow.top = 0;
    pdc->erclWindow.right = pdc->dclevel.sizl.cx;
    pdc->erclWindow.bottom = pdc->dclevel.sizl.cy;

    /* Non-direct DCs don't have a surface by default */
    pdc->dclevel.pSurface = SURFACE_ShareLockSurface(dcinfo.hsurf);
    pdc->erclBounds.left = 0;
    pdc->erclBounds.top = 0;
    pdc->erclBounds.right = 0;
    pdc->erclBounds.bottom = 0;
    pdc->erclBoundsApp = pdc->erclBounds;
    pdc->erclClip = pdc->erclWindow;
    //pdc->co = gxcoTrivial;

      //pdc->dcattr.VisRectRegion:

	EXFORMOBJ xo;

    /* Setup coordinate transformation data */
	//pdc->dclevel.mxWorldToDevice = gmxWorldToDeviceDefault;
	//pdc->dclevel.mxDeviceToWorld = gmxDeviceToWorldDefault;
	XFORMOBJ_vInit(&xo, &pdc->dclevel.mxWorldToPage);
	XFORMOBJ_iSetXform(&xo, (PXFORML)&dcinfo.xformWorldToPage);
	//pdc->dclevel.efM11PtoD = gef16;
	//pdc->dclevel.efM22PtoD = gef16;
	//pdc->dclevel.efDxPtoD = gef0;
	//pdc->dclevel.efDyPtoD = gef0;
	//pdc->dclevel.efM11_TWIPS = gef0;
	//pdc->dclevel.efM22_TWIPS = gef0;
	//pdc->dclevel.efPr11 = gef0;
	//pdc->dclevel.efPr22 = gef0;
	pdc->dcattr.mxWorldToDevice = pdc->dclevel.mxWorldToDevice;
	pdc->dcattr.mxDeviceToWorld = pdc->dclevel.mxDeviceToWorld;
	pdc->dcattr.mxWorldToPage = pdc->dclevel.mxWorldToPage;
	pdc->dcattr.efM11PtoD = pdc->dclevel.efM11PtoD;
	pdc->dcattr.efM22PtoD = pdc->dclevel.efM22PtoD;
	pdc->dcattr.efDxPtoD = pdc->dclevel.efDxPtoD;
	pdc->dcattr.efDyPtoD = pdc->dclevel.efDyPtoD;
	pdc->dcattr.iMapMode = dcinfo.iMapMode;
	pdc->dcattr.dwLayout = 0;
	pdc->dcattr.flXform = PAGE_TO_DEVICE_SCALE_IDENTITY |
	                      PAGE_TO_DEVICE_IDENTITY |
	                      WORLD_TO_PAGE_IDENTITY;

    /* Setup more coordinates */
    pdc->ptlDCOrig.x = 0;
    pdc->ptlDCOrig.y = 0;
	pdc->dcattr.lWindowOrgx = 0;
	pdc->dcattr.ptlWindowOrg.x = 0;
	pdc->dcattr.ptlWindowOrg.y = 0;
	pdc->dcattr.szlWindowExt.cx = 1;
	pdc->dcattr.szlWindowExt.cy = 1;
	pdc->dcattr.ptlViewportOrg.x = 0;
	pdc->dcattr.ptlViewportOrg.y = 0;
	pdc->dcattr.szlViewportExt.cx = 1;
	pdc->dcattr.szlViewportExt.cy = 1;
    pdc->dcattr.szlVirtualDevicePixel.cx = ppdev->gdiinfo.ulHorzRes;
    pdc->dcattr.szlVirtualDevicePixel.cy = ppdev->gdiinfo.ulVertRes;
    pdc->dcattr.szlVirtualDeviceMm.cx = ppdev->gdiinfo.ulHorzSize;
    pdc->dcattr.szlVirtualDeviceMm.cy = ppdev->gdiinfo.ulVertSize;
    pdc->dcattr.szlVirtualDeviceSize.cx = 0;
    pdc->dcattr.szlVirtualDeviceSize.cy = 0;

    /* Setup regions */
    pdc->prgnAPI = NULL;
	pdc->prgnRao = NULL;
	pdc->dclevel.prgnClip = NULL;
	pdc->dclevel.prgnMeta = NULL;
    /* Allocate a Vis region */
    //pdc->prgnVis = IntSysCreateRectpRgn(0, 0, pdc->dclevel.sizl.cx, pdc->dclevel.sizl.cy);
	ASSERT(pdc->prgnVis);

	/* Initialize Clip object */
	//IntEngInitClipObj(&pdc->co);

    /* Setup palette */
    pdc->dclevel.hpal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
    pdc->dclevel.ppal = PALETTE_ShareLockPalette(pdc->dclevel.hpal);

    /* Setup path */
	pdc->dclevel.hPath = NULL;
    pdc->dclevel.flPath = 0;
//	pdc->dclevel.lapath:

    /* Setup colors */
	pdc->dcattr.crBackgroundClr = RGB(0xff, 0xff, 0xff);
	pdc->dcattr.ulBackgroundClr = RGB(0xff, 0xff, 0xff);
	pdc->dcattr.crForegroundClr = RGB(0, 0, 0);
	pdc->dcattr.ulForegroundClr = RGB(0, 0, 0);
	pdc->dcattr.crBrushClr = RGB(0xff, 0xff, 0xff);
	pdc->dcattr.ulBrushClr = RGB(0xff, 0xff, 0xff);
	pdc->dcattr.crPenClr = RGB(0, 0, 0);
	pdc->dcattr.ulPenClr = RGB(0, 0, 0);

    /* Select the default fill and line brush */
	pdc->dcattr.hbrush = GetStockObject(WHITE_BRUSH);
	pdc->dcattr.hpen = GetStockObject(BLACK_PEN);
    pdc->dclevel.pbrFill = BRUSH_ShareLockBrush(pdc->pdcattr->hbrush);
    pdc->dclevel.pbrLine = PEN_ShareLockPen((HPEN)pdc->pdcattr->hpen);
	pdc->dclevel.ptlBrushOrigin.x = 0;
	pdc->dclevel.ptlBrushOrigin.y = 0;
	pdc->dcattr.ptlBrushOrigin = pdc->dclevel.ptlBrushOrigin;

    /* Initialize EBRUSHOBJs */
    //EBRUSHOBJ_vInitFromDC(&pdc->eboFill, pdc->dclevel.pbrFill, pdc);
    //EBRUSHOBJ_vInitFromDC(&pdc->eboLine, pdc->dclevel.pbrLine, pdc);
    //EBRUSHOBJ_vInitFromDC(&pdc->eboText, pbrDefaultBrush, pdc);
    //EBRUSHOBJ_vInitFromDC(&pdc->eboBackground, pbrDefaultBrush, pdc);

    /* Setup fill data */
	pdc->dcattr.jROP2 = R2_COPYPEN;
	pdc->dcattr.jBkMode = 2;
	pdc->dcattr.lBkMode = 2;
	pdc->dcattr.jFillMode = ALTERNATE;
	pdc->dcattr.lFillMode = 1;
	pdc->dcattr.jStretchBltMode = 1;
	pdc->dcattr.lStretchBltMode = 1;
    pdc->ptlFillOrigin.x = 0;
    pdc->ptlFillOrigin.y = 0;

    /* Setup drawing position */
    GetCurrentPositionEx(hdc, &pdc->dcattr.ptlCurrent);
	pdc->dcattr.ptfxCurrent.x = pdc->dcattr.ptlCurrent.x;
	pdc->dcattr.ptfxCurrent.y = pdc->dcattr.ptlCurrent.y;
    LPtoDP(hdc, (PPOINTL)&pdc->dcattr.ptfxCurrent, 1);

	/* Setup ICM data */
	pdc->dclevel.lIcmMode = 0;
	pdc->dcattr.lIcmMode = 0;
	pdc->dcattr.hcmXform = NULL;
	pdc->dcattr.flIcmFlags = 0;
	pdc->dcattr.IcmBrushColor = CLR_INVALID;
	pdc->dcattr.IcmPenColor = CLR_INVALID;
	pdc->dcattr.pvLIcm = NULL;
    pdc->dcattr.hColorSpace = NULL; // FIXME: 0189001f
	pdc->dclevel.pColorSpace = NULL; // FIXME
    pdc->pClrxFormLnk = NULL;
//	pdc->dclevel.ca =

	/* Setup font data */
    pdc->hlfntCur = NULL; // FIXME: 2f0a0cf8
    pdc->pPFFList = NULL;
    pdc->flSimulationFlags = 0;
    pdc->lEscapement = 0;
    pdc->prfnt = NULL;
	pdc->dcattr.flFontMapper = 0;
	pdc->dcattr.flTextAlign = 0;
	pdc->dcattr.lTextAlign = 0;
	pdc->dcattr.lTextExtra = 0;
	pdc->dcattr.lRelAbs = 1;
	pdc->dcattr.lBreakExtra = 0;
	pdc->dcattr.cBreak = 0;
    pdc->dcattr.hlfntNew = GetStockObject(SYSTEM_FONT);
    //pdc->dclevel.plfnt = LFONT_ShareLockFont(pdc->dcattr.hlfntNew);

    /* Other stuff */
    pdc->hdcNext = NULL;
    pdc->hdcPrev = NULL;
    pdc->ipfdDevMax = 0;
    pdc->ulCopyCount = -1;
    pdc->ptlDoBanding.x = 0;
    pdc->ptlDoBanding.y = 0;
	pdc->dclevel.lSaveDepth = 1;
	pdc->dclevel.hdcSave = NULL;
	pdc->dcattr.iGraphicsMode = GM_COMPATIBLE;
	pdc->dcattr.iCS_CP = 0;
    pdc->pSurfInfo = NULL;

    if (pdc->dclevel.pSurface != NULL)
    {
        pdc->dclevel.pSurface->hdc = hdc;
    }

    pdc->BaseObject.hHmgr = hdc;

    return pdc;
}

VOID
DC_vDeleteDc(
    PDC pdc)
{
}
