

#include "bltobj.hpp"


BOOL
bTransformPoints(
    _In_ PDC pdc,
    _In_ PPOINT ppt,
    _In_ ULONG cpt,
    _In_ ULONG iMode)
{
    XFORMOBJ xo;
    ULONG i;

    /* Transform coordinates */
    XFORMOBJ_vInit(&xo, DC_pmxWorldToDevice(pdc));
    if (!XFORMOBJ_bApplyXform(&xo, iMode, cpt, ppt, ppt))
    {
        return FALSE;
    }

    /* Account for the DC origin */
    for (i = 0; i < cpt; i++)
    {
        if (iMode == XF_LTOFX)
        {
            ppt[i].x += LONG2FIX(pdc->ptlDCOrig.x);
            ppt[i].y += LONG2FIX(pdc->ptlDCOrig.y);
        }
        else
        {
            ppt[i].x += pdc->ptlDCOrig.x;
            ppt[i].y += pdc->ptlDCOrig.y;
        }
    }

    return TRUE;
}

BLTOBJ::~BLTOBJ (
    VOID)
{
    /* Check if we acquired PDEV locks */
    if (_fDevicesLocked)
    {
        vUnlockDevices();
    }

    /* Check if we locked a DC */
    if (_fDCsLocked)
    {
        NT_ASSERT(_pdcTrg != NULL);
        DC_UnlockDc(_pdcTrg);
        if (_pdcSrc != NULL)
        {
            DC_UnlockDc(_pdcSrc);
        }
    }

    /* Check if we initialized an EXLATEOBJ */
    if (_fXlateNeedsCleanup)
    {
        EXLATEOBJ_vCleanup(&_exlo);
    }

    /* Check if the current position should be updated */
    if (_UpdateCurrentPos)
    {
        /// FIXME: should we check for success of the drawing operation?
        _pdcTrg->pdcattr->ptfxCurrent = _ptfxTrg;
        _pdcTrg->pdcattr->ptlCurrent.x = FIX2LONG(_ptfxTrg.x); /// FIXME: needs to be in world coordinates
        _pdcTrg->pdcattr->ptlCurrent.y = FIX2LONG(_ptfxTrg.y);
    }

}

BOOL
BLTOBJ::bInit (
    _In_ HDC hdcTrg,
    _In_opt_ HDC hdcSrc,
    _In_ PPOINT pptTrg,
    _In_ ULONG cptTrg,
    _In_opt_ PPOINT pptSrc,
    _In_ ULONG cptSrc,
    _In_ ULONG fl)
{
    HGDIOBJ ahobj[2];
    PVOID apvObj[2];
    ULONG iXformMode;
    BOOL bResult;

    /* We need at least a target DC */
    if (hdcTrg == NULL)
    {
        bResult = FALSE;
        goto Exit;
    }

    /* Check if we have a source DC */
    if (hdcSrc != NULL)
    {
        /* Check if a source is needed */
        if (fl & BLT_NEED_SRC)
        {
            bResult = FALSE;
            goto Exit;
        }

        /* Lock both DCs */
        ahobj[0] = hdcTrg;
        ahobj[1] = hdcSrc ;
        if (!GDIOBJ_bLockMultipleObjects(2, ahobj, apvObj, GDIObjType_DC_TYPE))
        {
            WARN("Invalid dc handle (hdcSrc=0x%p, hdcSrc=0x%p)\n", hdcTrg, hdcSrc);
            _pdcTrg = NULL;
            _pdcSrc = NULL;
            bResult = FALSE;
            goto Exit;
        }

        _pdcTrg = (PDC)apvObj[0];
        _pdcSrc = (PDC)apvObj[1];
    }
    else
    {
        _pdcTrg = NULL;
        _pdcSrc = DC_LockDc(hdcSrc);
        if (_pdcSrc == NULL)
        {
            bResult = FALSE;
            goto Exit;
        }

        /* There is no XLATEOBJ for a single surface! */
        _pxlo = &gexloTrivial.xlo;
        _fXlateInitialized = 1;
    }

    /* Set the target transform mode */
    iXformMode = (fl & BLT_TRG_FIXPOINTS) ? XF_LTOFX : XF_LTOL;

    /* Transform the target coordinates */
    if (!bTransformPoints(_pdcTrg, pptTrg, cptTrg, iXformMode))
    {
        bResult = FALSE;
        goto Exit;
    }

    /* Check if we have a source */
    if (_pdcSrc != NULL)
    {
        /* Set the source transform mode */
        iXformMode = (fl & BLT_SRC_FIXPOINTS) ? XF_LTOFX : XF_LTOL;

        /* Transform the source coordinates */
        if (!bTransformPoints(_pdcSrc, pptSrc, cptSrc, iXformMode))
        {
            bResult = FALSE;
            goto Exit;
        }
    }

    NT_ASSERT(_pdcTrg != NULL);
    NT_ASSERT((hdcSrc == NULL) || (_pdcSrc != NULL));

    _fDCsLocked = TRUE;
    bResult = TRUE;

Exit:

    /* Check for failure */
    if (!bResult)
    {
        /* We clean up right here, since callers might expect that */
        if (_pdcTrg != NULL)
        {
            DC_UnlockDc(_pdcTrg);
        }
        if (_pdcSrc != NULL)
        {
            DC_UnlockDc(_pdcSrc);
        }
        _fDCsLocked = FALSE;
    }

    return bResult;
}

VOID
BLTOBJ::vLockDevices (
    VOID)
{
    /// FIXME: bounds might be bogus!
    /// need to calculate bounds for multi point invocation!
    /// might always calculate FIX coordinates and update them on demand
    /// update currenpos explicitly on success?
    DC_vPrepareDCsForBlit(_pdcTrg, &_rclTrg, _pdcSrc, &_rclSrc);
}

VOID
BLTOBJ::vUnlockDevices (
    VOID)
{
    DC_vFinishBlit(_pdcTrg, _pdcSrc);
}

VOID
BLTOBJ::vInitXlateObject (
    VOID)
{
    NT_ASSERT(_pdcSrc != NULL);

    EXLATEOBJ_vInitXlateFromDCs(&_exlo, _pdcSrc, _pdcTrg);
    _pxlo = &_exlo.xlo;
    _fXlateInitialized = 1;
    _fXlateNeedsCleanup = 1;
}

__kernel_entry
W32KAPI
BOOL
APIENTRY
GdiAlphaBlend(
    _In_ HDC hdcDst,
    _In_ LONG xDst,
    _In_ LONG yDst,
    _In_ LONG cxDst,
    _In_ LONG cyDst,
    _In_ HDC hdcSrc,
    _In_ LONG xSrc,
    _In_ LONG ySrc,
    _In_ LONG cxSrc,
    _In_ LONG cySrc,
    _In_ BLENDFUNCTION BlendFunction,
    _In_ HANDLE hcmXform)
{
    RECT rcDst, rcSrc;
    BLENDOBJ blendobj;
    BLTOBJ bltobj;

    /* Make sure we have 2 DCs */
    if ((hdcDst == NULL) || (hdcSrc == NULL))
    {
        EngSetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    /* Validate the sizes */
    if ((cxDst < 0) || (cyDst < 0) || (cxSrc < 0) || (cySrc < 0))
    {
        EngSetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    /* Set up the BLENDOBJ */
    blendobj.BlendFunction = BlendFunction;

    /* Set up the coordinates */
    rcDst.left = xDst;
    rcDst.top = yDst;
    rcDst.right = xDst + cxDst;
    rcDst.bottom = yDst + cyDst;
    rcSrc.left = xDst;
    rcSrc.top = yDst;
    rcSrc.right = xDst + cxDst;
    rcSrc.bottom = yDst + cyDst;

    /* Initialize the BLTOBJ */
    if (!bltobj.bInit(hdcDst, hdcSrc, &rcDst, &rcSrc, TRUE))
    {
        return FALSE;
    }

    /* Check for empty memory DCs */
    if (!bltobj.bTrgDcHasSurface() || !bltobj.bSrcDcHasSurface())
    {
        return TRUE;
    }

    /* Pass to the Drv / Eng function */
    return IntEngAlphaBlend(bltobj.psoTrg(),
                            bltobj.psoSrc(),
                            bltobj.pco(),
                            bltobj.pxlo(),
                            bltobj.prclTrg(),
                            bltobj.prclSrc(),
                            &blendobj);
}
