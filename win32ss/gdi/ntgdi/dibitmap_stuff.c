typedef struct _BITMAPV5INFO
{
    BITMAPV5HEADER bmiHeader;
    union
    {
        RGBQUAD argbColors[1];
        WORD awColorIndices[1];
    };
} BITMAPV5INFO, *PBITMAPV5INFO;

typedef struct _BITMAPV5INFO
{
    BITMAPV5HEADER bmiHeader;
    union
    {
        RGBQUAD bmiColors[1];
        WORD bmiPalColors[1];
    };
} BITMAPV5INFO, *PBITMAPV5INFO;

PBITMAPV5INFO
ProbeAndConvertBitmapInfo(
    _In_ const BITMAPINFO *pbmi,
)
{

    _SEH2_TRY
    {
        ProbeForRead(&pbmi->bmiHeader.biSize, sizeof(DWORD), 1);
        cjHeaderSize = pbmi->bmiHeader.biSize;
        pvColorTable = (PCHAR)pbmi + cjHeaderSize;

        ProbeForRead(pbmi, cjHeaderSize, 1);

        if (cjHeaderSize < sizeof(BITMAPCOREHEADER))
        {
            // ???
        }
        else if (cjHeaderSize < sizeof(BITMAPINFOHEADER))
        {
            PBITMAPCOREHEADER pbch = (PBITMAPCOREHEADER)pbmi;

            cBitsPixel = pbch->chBitCount;
            cColors = 1 << cBitsPixel;
        }
        else
        {
            cBitsPixel = pbmi->bmiHeader.biBitCount;
            cColors = pbmi->bmiHeader.biClrUsed;
        }
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
    }
    _SEH2_END;

    /* Check if this is an indexed palette */
    if (cBitsPixel <= 8)
    {
        if ((cColors == 0) || (cColors > 1 << cBitsPixel))
        {
            cColors = 1 << cBitsPixel;
        }
    }
    else
    {
        /* Otherwise we have no color table */
        cColors = 0;
    }


    /* Calculate the size of the new bitmapinfo */
    if (iUsage == BI_RGB)
        cjV5Size = sizeof(BITMAPV5HEADER) + cColors * sizeof(RGBQUAD);
    else
        cjV5Size = sizeof(BITMAPV5HEADER) + cColors * sizeof(WORD);


    pbv5i = ExAllocatePoolWithTag(PagedPool, cjV5Size, 'imbG');
    if (!pbv5i)
    {
        return NULL;
    }

    RtlZeroMemory(pbv5i, sizeof(BITMAPV5INFO));

    _SEH2_TRY
    {
        ProbeForRead(pvColorTable, cjColorTableSize, 1);

        if (cjHeaderSize < sizeof(BITMAPINFOHEADER))
        {
            PBITMAPCOREHEADER pbch = (PBITMAPCOREHEADER)pbmi;

            pbv5i->bmiHeader.bV5Width = pbch->bcWidth;
            pbv5i->bmiHeader.bV5Height = pbch->bcHeight;
            pbv5i->bmiHeader.bV5Planes = pbch->bcPlanes;
            pbv5i->bmiHeader.bV5BitCount = pbch->bcBitCount;
            pbv5i->bmiHeader.bV5Compression = BI_RGB;

            if (cBitsPixel > 8)
            {
                RGBTRIPLE *prgbColors = (RGBTRIPLE*)pvColorTable;

                pbv5i->bmiHeader.bV5RedMask = RGB(prgbColors[0].rgbRed,
                                                  prgbColors[0].rgbGreen,
                                                  prgbColors[0].rgbBlue);
                pbv5i->bmiHeader.bV5GreenMask = RGB(prgbColors[1].rgbRed,
                                                    prgbColors[1].rgbGreen,
                                                    prgbColors[1].rgbBlue);
                pbv5i->bmiHeader.bV5BlueMask = RGB(prgbColors[2].rgbRed,
                                                   prgbColors[2].rgbGreen,
                                                   prgbColors[2].rgbBlue);
            }
            else if (iUsage == BI_RGB)
            {
                RGBTRIPLE *prgbColors = (RGBTRIPLE*)pvColorTable;

                for (i = 0; i < cColors; i++)
                {
                    pbv5i->argbColors[i].rgbRed = prgbColors[i].rgbRed;
                    pbv5i->argbColors[i].rgbGreen = prgbColors[i].rgbGreen;
                    pbv5i->argbColors[i].rgbBlue = prgbColors[i].rgbBlue;
                }
            }
            else
            {
                PWORD pwIndices = (PWORD)pvColorTable;

                for (i = 0; i < cColors; i++)
                {
                    pbv5i->awColorIndices[i] = pwIndices[i];
                }
            }
        }
        else
        {

            pbv5i->bmiHeader.bV5Width = pbmi->bmiHeader.biWidth;
            pbv5i->bmiHeader.bV5Height = pbmi->bmiHeader.biHeight;
            pbv5i->bmiHeader.bV5Planes = pbmi->bmiHeader.biPlanes;
            pbv5i->bmiHeader.bV5BitCount = pbmi->bmiHeader.biBitCount;
            pbv5i->bmiHeader.bV5Compression = pbmi->bmiHeader.biCompression;
            pbv5i->bmiHeader.bV5SizeImage = pbmi->bmiHeader.biSizeImage;
            pbv5i->bmiHeader.bV5XPelsPerMeter = pbmi->bmiHeader.biXPelsPerMeter;
            pbv5i->bmiHeader.bV5YPelsPerMeter = pbmi->bmiHeader.biYPelsPerMeter;
            pbv5i->bmiHeader.bV5ClrUsed = pbmi->bmiHeader.biClrUsed;
            pbv5i->bmiHeader.bV5ClrImportant = pbmi->bmiHeader.biClrImportant;

            if (cjHeaderSize >= sizeof(BITMAPV4HEADER))
            {
                pbv4h = (PBITMAPV4HEADER)pbmi;

                pbv5i->bmiHeader.bV5RedMask = pbv4h->bV4RedMask;
                pbv5i->bmiHeader.bV5GreenMask = pbv4h->bV4GreenMask;
                pbv5i->bmiHeader.bV5BlueMask = pbv4h->bV4BlueMask;
                pbv5i->bmiHeader.bV5AlphaMask = pbv4h->bV4AlphaMask;
                pbv5i->bmiHeader.bV5CSType = pbv4h->bV4CSType;
                pbv5i->bmiHeader.bV5Endpoints = pbv4h->bV4Endpoints;
                pbv5i->bmiHeader.bV5GammaRed = pbv4h->bV4GammaRed;
                pbv5i->bmiHeader.bV5GammaGreen = pbv4h->bV4GammaGreen;
                pbv5i->bmiHeader.bV5GammaBlue = pbv4h->bV4GammaBlue;
            }
            else if (cBitsPixel > 8)
            {
                RGBQUAD *prgbColors = (RGBQUAD*)pvColorTable;

                pbv5i->bmiHeader.bV5RedMask = prgbColors[0];
                pbv5i->bmiHeader.bV5GreenMask = prgbColors[1];
                pbv5i->bmiHeader.bV5BlueMask = prgbColors[2];
            }

        }
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
    }
    _SEH2_END;



}

HBITMAP
NTAPI
GreCreateOriginalDIBitmap(
    _In_ const BITMAPINFO *pbmi,
    _In_ PVOID pvBits)
{
    LONG lWidth, lHeight;
    ULONG iCompression;

    if (pbmi->bmiHeader.biSize < sizeof(BITMAPINFOHEADER))
    {
        PBITMAPCOREHEADER pbch = (PBITMAPCOREHEADER)pbmi;

        iCompression = BI_RGB;
        lWidth = pbch->bcWidth;
        lHeight = abs(pbch->bcHeight);
        cBitsPixel = pbch->bcPlanes * pbch->bcBitCount;
    }
    else
    {
        iCompression = pbmi->bmiHeader.biCompression;
        lWidth = pbmi->bmiHeader.biWidth;
        lHeight = pbmi->bmiHeader.biHeight;
        cBitsPixel = pbmi->bmiHeader.biPlanes * pbmi->bmiHeader.biBitCount;
    }

    hbmp = GreCreateBitmapEx(lWidth,
                             abs(lHeight),
                             0,
                             BitmapFormat(cBitsPixel, iCompression),
                             (lHeight > 0) ? BMF_TOPDOWN : 0,
                             cjSizeImage,
                             pvBits,
                             flags);


}




VOID
DibConvertBitmapInfo(
    _Out_ PBITMAPV5INFO pbmiDest,
    _In_ PBITMAPINFO pbmiUser,
    _In_ ULONG iColorUsage)
{

}


PBITMAPV5INFO
NTAPI
DibProbeAndConvertBitmapInfo(
    _In_ PBITMAPINFO pbmiUser,
    _In_ ULONG cjHeader,
    _In_ ULONG iColorUsage)
{
    ULONG cColors, cjColorTableSize, cjFullSize;
    PBITMAPV5INFO pbmi;


    _SEH2_TRY
    {
        ProbeForRead(pbmiUser, cjHeader, 1);

        cjHeader = pbmiUser->bmiHeader.biSize;
        ProbeForRead(pbmiUser, cjHeader, 1);

        cColors = pbmiUser->bmiHeader.biClrUsed;
        if (!cColors) cColors = (1 << pbmiUser->bmiHeader.biBitCount);

    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        _SEH2_YIELD(return NULL);
    }
    _SEH2_END;

    /* Check what kind of color table we have */
    if (iColorUsage == DIB_PAL_COLORS)
    {
        /* The color table is an array of DWORD sized palette indices */
        cjColorTableSize = cColors * sizeof(WORD);
    }
    else
    {
        /* The color table is an array of RGBQUADs */
        cjColorTableSize = cColors * sizeof(RGBQUAD);
    }

    cjFullSize = sizeof(BITMAPV5INFO) + cjColorTableSize;
    pbmi = ExAllocatePoolWithTag(PagedPool, cjFullSize, GDITAG_BITMAPINFO);

    _SEH2_TRY
    {
        DibConvertBitmapInfo(pbmi, pbmiUser, iColorUsage);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        ExFreePoolWithTag(pbmi, GDITAG_BITMAPINFO);
        _SEH2_YIELD(return NULL);
    }
    _SEH2_END;


    return NULL;
}

INT
APIENTRY
NtGdiStretchDIBitsInternal(
    _In_ HDC hdc,
    _In_ INT xDst,
    _In_ INT yDst,
    _In_ INT cxDst,
    _In_ INT cyDst,
    _In_ INT xSrc,
    _In_ INT ySrc,
    _In_ INT cxSrc,
    _In_ INT cySrc,
    _In_opt_ LPBYTE pjInit,
    _In_ LPBITMAPINFO pbmi,
    _In_ DWORD dwUsage,
    _In_ DWORD dwRop, // ms ntgdi.h says dwRop4(?)
    _In_ UINT cjMaxInfo,
    _In_ UINT cjMaxBits,
    _In_ HANDLE hcmXform)
{
    BOOL bResult = FALSE;
    SIZEL sizel;
    RECTL rcSrc, rcDst;
    PDC pdc;
    HBITMAP hbmTmp;
    PSURFACE psurfTmp, psurfDst;
    EXLATEOBJ exlo;

    /* Lock the destination DC */
    if (!(pdc = DC_LockDc(hdc)))
    {
        EngSetLastError(ERROR_INVALID_HANDLE);
        return 0;
    }

    /* Transform dest size */
    sizel.cx = cxDst;
    sizel.cy = cyDst;
    IntLPtoDP(pdc, (POINTL*)&sizel, 1);
    DC_UnlockDc(pdc);

    /* Check if we can use NtGdiSetDIBitsToDeviceInternal */
    if (sizel.cx == cxSrc && sizel.cy == cySrc && dwRop == SRCCOPY)
    {
        /* Yes, we can! */
        return NtGdiSetDIBitsToDeviceInternal(hdc,
                                              xDst,
                                              yDst,
                                              cxDst,
                                              cyDst,
                                              xSrc,
                                              ySrc,
                                              0,
                                              cySrc,
                                              pjInit,
                                              pbmi,
                                              dwUsage,
                                              cjMaxBits,
                                              cjMaxInfo,
                                              TRUE,
                                              hcmXform);
    }


    // Capture BITMAPINFO
    // Create a temp bitmap with secured user memory
    // psurfTmp = CreateSecuredDIBitmap(cx, cy, pbmi


    /* Create an intermediate bitmap from the DIB */
    hbmTmp = NtGdiCreateDIBitmapInternal(hdc,
                                         cxSrc,
                                         cySrc,
                                         CBM_INIT | CBM_CREATDIB,
                                         pjInit,
                                         pbmi,
                                         dwUsage,
                                         cjMaxInfo,
                                         cjMaxBits,
                                         0,
                                         hcmXform);
    if (!hbmTmp) return 0;

    /* FIXME: locking twice is cheesy, coord tranlation in UM will fix it */
    if (!(pdc = DC_LockDc(hdc)))
    {
        DPRINT1("Could not lock dc\n");
        EngSetLastError(ERROR_INVALID_HANDLE);
        GreDeleteObject(hbmTmp);
        return 0;
    }

    psurfTmp = SURFACE_ShareLockSurface(hbmTmp);
    if (!psurfTmp)
    {
        DPRINT1("Could not lock bitmap :-(\n");
        goto cleanup;
    }

    psurfDst = pdc->dclevel.pSurface;
    if (!psurfDst)
    {
        // CHECKME
        DPRINT1("nothing to do\n");
        bResult = TRUE;
        goto cleanup;
    }

    /* Calculate source and destination rect */
    rcSrc.left = xSrc;
    rcSrc.top = ySrc;
    rcSrc.right = xSrc + cxSrc;
    rcSrc.bottom = ySrc + cySrc;
    rcDst.left = xDst;
    rcDst.top = yDst;
    rcDst.right = rcDst.left + cxDst;
    rcDst.bottom = rcDst.top + cyDst;
    IntLPtoDP(pdc, (POINTL*)&rcDst, 2);
    RECTL_vOffsetRect(&rcDst, pdc->ptlDCOrig.x, pdc->ptlDCOrig.y);

    /* Initialize XLATEOBJ */
    EXLATEOBJ_vInitialize(&exlo,
                          psurfTmp->ppal,
                          psurfDst->ppal,
                          RGB(0xff, 0xff, 0xff),
                          pdc->pdcattr->crBackgroundClr,
                          pdc->pdcattr->crForegroundClr);

    /* Prepare DC for blit */
    DC_vPrepareDCsForBlit(pdc, rcDst, NULL, rcSrc);

    /* Perform the stretch operation */
    bResult = IntEngStretchBlt(&psurfDst->SurfObj,
                               &psurfTmp->SurfObj,
                               NULL,
                               pdc->rosdc.CombinedClip,
                               &exlo.xlo,
                               &rcDst,
                               &rcSrc,
                               NULL,
                               &pdc->eboFill.BrushObject,
                               NULL,
                               ROP_TO_ROP4(dwRop));

    /* Cleanup */
    DC_vFinishBlit(pdc, NULL);
    EXLATEOBJ_vCleanup(&exlo);
cleanup:
    if (psurfTmp) SURFACE_ShareUnlockSurface(psurfTmp);
    if (hbmTmp) GreDeleteObject(hbmTmp);
    if (pdc) DC_UnlockDc(pdc);

    return bResult;
}

