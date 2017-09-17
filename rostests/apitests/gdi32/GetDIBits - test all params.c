/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPL - See COPYING in the top level directory
 * PURPOSE:         Test for GetDIBits
 * PROGRAMMERS:     Timo Kreuzer
 */

#include <apitest.h>

#include <wingdi.h>
#include <winuser.h>

#include "init.h"

#define RETURN(x) *pdwLine = __LINE__; return x
UINT
MyGetDIBits (
    HDC hdc,
    HBITMAP hbm,
    UINT uStart,
    UINT cLines,
    PVOID pvBits,
    PBITMAPINFO pbmi,
    UINT uUsage,
    DWORD *pdwExpectedError,
    DWORD *pdwLine)
{
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        RGBQUAD bmiColors[256];
    } bmiBuffer;

    if ((hdc == NULL) || (hdc == (HDC)-1))
    {
        *pdwExpectedError = ERROR_INVALID_PARAMETER;
        RETURN(0);
    }

    if ((ULONG)pbmi->bmiHeader.biSize == sizeof(BITMAPCOREHEADER))
    {
        PBITMAPCOREINFO pbci = (PBITMAPCOREINFO)pbmi;

        memset(&bmiBuffer, 0, sizeof(bmiBuffer));
        pbmi = (PBITMAPINFO)&bmiBuffer;
        pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        pbmi->bmiHeader.biBitCount = pbci->bmciHeader.bcBitCount;
        pbmi->bmiHeader.biWidth = (ULONG)pbci->bmciHeader.bcWidth;
        pbmi->bmiHeader.biHeight = (LONG)pbci->bmciHeader.bcHeight;
        pbmi->bmiHeader.biPlanes = pbci->bmciHeader.bcPlanes;
    }
    else if ((ULONG)pbmi->bmiHeader.biSize < sizeof(BITMAPINFOHEADER))
    {
        RETURN(0);
    }

    if ((hbm == NULL) || (hbm == (HBITMAP)-1))
    {
        RETURN(0);
    }

    if (uUsage > 2)
    {
        RETURN(0);
    }

    if ((pbmi->bmiHeader.biBitCount != 0) &&
        (pbmi->bmiHeader.biBitCount != 1) &&
        (pbmi->bmiHeader.biBitCount != 4) &&
        (pbmi->bmiHeader.biBitCount != 8) &&
        (pbmi->bmiHeader.biBitCount != 16) &&
        (pbmi->bmiHeader.biBitCount != 24) &&
        (pbmi->bmiHeader.biBitCount != 32))
    {
        RETURN(0);
    }


    if (pvBits == NULL)
    {
        if (pbmi->bmiHeader.biBitCount != 0)
        {
            if (pbmi->bmiHeader.biPlanes == 0)
            {
                if ((pbmi->bmiHeader.biWidth <= 0) || (pbmi->bmiHeader.biHeight == 0))
                {
                    *pdwExpectedError = ERROR_INVALID_PARAMETER;
                    RETURN(0);
                }


                if (cLines > 0)
                {
                    if (uStart == 0)
                    {
                        RETURN(0);
                    }

                    if (uStart == 1)
                    {
                        //RETURN(-3);
                    }

                    if (((LONG)uStart >= 0) && ((LONG)uStart < abs(pbmi->bmiHeader.biHeight)))
                    {
                        if ((abs(pbmi->bmiHeader.biHeight) > 20))
                        {
                            RETURN(0);
                        }
                    }
                }
            }
            else
            {
                if ((pbmi->bmiHeader.biBitCount == 32) &&
                    (pbmi->bmiHeader.biWidth < 0) &&
                    (cLines > 20))
                {
                    RETURN(0);
                }

                if (pbmi->bmiHeader.biWidth <= 0)
                {
                    *pdwExpectedError = ERROR_INVALID_PARAMETER;
                    RETURN(0);
                }

                if ((LONG)cLines < 0)
                {
                    RETURN(0);
                }

                if (pbmi->bmiHeader.biHeight == 0)
                {
                    *pdwExpectedError = ERROR_INVALID_PARAMETER;
                    RETURN(0);
                }

                if (cLines > 0)
                {
                    if (((LONG)uStart >= 0) && ((LONG)uStart < abs(pbmi->bmiHeader.biHeight)))
                    {
                        if ((abs(pbmi->bmiHeader.biHeight) > 20))
                        {
                            RETURN(1);
                        }
                    }
                }
            }
        }

        RETURN(1);
    }
    else
    {
        if (cLines > 0)
        {
            RETURN(0);
        }

        if (pbmi->bmiHeader.biBitCount == 0)
        {
            // this should be complete */
        }
        else
        {
            {
                if ((pbmi->bmiHeader.biWidth <= 0) || (pbmi->bmiHeader.biHeight == 0))
                {
                    *pdwExpectedError = ERROR_INVALID_PARAMETER;
                    RETURN(0);
                }
            }

        }

        (void)*(BYTE*)pvBits;

        RETURN(cLines ? cLines : 1);
    }

    RETURN(1);
}

void
Compare(
    HDC hdc,
    HBITMAP hbm,
    UINT uStart,
    UINT cLines,
    PVOID pvBits,
    PBITMAPINFO pbmi,
    UINT uUsage,
    PBITMAPINFO pbmiValid,
    UINT biSize,
    UINT biPlanes,
    UINT biBitCount,
    INT biWidth,
    INT biHeight)
{
    UINT uResult, uExpected;
    DWORD dwExpectedError, dwLine;
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        RGBQUAD bmiColors[256];
    } bmiBufferOrgIn;
    PBITMAPINFO pbmiOrgIn = (PBITMAPINFO)&bmiBufferOrgIn;
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        RGBQUAD bmiColors[256];
    } bmiBuffer2;
    PBITMAPINFO pbmiSavedOut = (PBITMAPINFO)&bmiBuffer2;

    memset(pbmiValid, 0, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
    pbmiValid->bmiHeader.biSize = biSize;
    if (pbmiValid->bmiHeader.biSize < sizeof(BITMAPINFOHEADER))
    {
        PBITMAPCOREHEADER pbch = (PBITMAPCOREHEADER)pbmiValid;

        pbch->bcPlanes = biPlanes;
        pbch->bcBitCount = biBitCount;
        pbch->bcWidth = biWidth;
        pbch->bcHeight = biHeight;
    }
    else
    {
        pbmiValid->bmiHeader.biPlanes = biPlanes;
        pbmiValid->bmiHeader.biBitCount = biBitCount;
        pbmiValid->bmiHeader.biWidth = biWidth;
        pbmiValid->bmiHeader.biHeight = biHeight;
    }

    /* Save the original data */
    memcpy(pbmiOrgIn, pbmiValid, sizeof(bmiBufferOrgIn));

    dwExpectedError = 0x12345678;
    dwLine = 0;
    _SEH2_TRY
    {
        uExpected = MyGetDIBits(hdc,
                                hbm,
                                uStart,
                                cLines,
                                pvBits,
                                pbmi,
                                uUsage,
                                &dwExpectedError,
                                &dwLine);
    }
    _SEH2_EXCEPT(1)
    {
        dwExpectedError = 0xdeadbeef;
    }
    _SEH2_END;

    /* Save the result */
    memcpy(pbmiSavedOut, pbmiValid, sizeof(bmiBuffer2));

    /* Restore the original data */
    memcpy(pbmiValid, pbmiOrgIn, sizeof(bmiBufferOrgIn));

    SetLastError(0x12345678);
    _SEH2_TRY
    {
        uResult = GetDIBits(hdc,
                            hbm,
                            uStart,
                            cLines,
                            pvBits,
                            pbmi,
                            uUsage);
    }
    _SEH2_EXCEPT(1)
    {
        SetLastError(0xdeadbeef);
    }
    _SEH2_END;

    ok((uResult == uExpected) && (GetLastError() == dwExpectedError),
       "{hdc=%p,hbm=%p,uStart=%i,cLines=%i,pv=%p,pbmi=%p,Usage=%u,biSize=%u,biBitCount=%u,size=(%d,%d)}: uResult=%u (exp:%u), LastError=0x%lx (exp:0x%lx),line=%ld\n",
       hdc, hbm, uStart, cLines, pvBits, pbmi, uUsage, biSize, biBitCount, biWidth, biHeight,
       uResult, uExpected,
       GetLastError(), dwExpectedError, dwLine);
}

#define countof(x) (sizeof(x) / sizeof((x)[0]))

void
Test_AllParams()
{
    HDC hdcMem;
    PBITMAPINFO pbmi;
    ULONG iBpp, ihdc, ihbm, iStart, iLines, ipvBits, ipbmi, iUsage, ibiSize, iWidth, iHeight, iPlanes;
    USHORT abiBitCount[] = {0, 1, 2, 3, 4, 8, 16, 24, 32, 64};
    PVOID pvBits;

    hdcMem = CreateCompatibleDC(0);
    pbmi = malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
    pvBits = malloc(10000);
    ok(pvBits != NULL, "\n");

    for (iBpp = 1; iBpp < 2/*countof(abiBitCount)*/; iBpp++)
    {
        HDC ahdc[] = { NULL, (HDC)-1, hdcMem };

        for (ihdc = 2; ihdc < 3/*countof(ahdc)*/; ihdc++)
        {
            HBITMAP ahbm[] = { NULL, (HBITMAP)-1, ghbmp1, ghbmpDIB1 };

            for (ihbm = 2; ihbm < 4/*countof(ahbm)*/; ihbm++)
            {
                UINT aiStart[] = {0, 1, -1, -50, 50};

                for (iStart = 0; iStart < 5/*countof(aiStart)*/; iStart++)
                {
                    UINT acLines[] = {0, 3, -1, -50, 50};

                    for (iLines = 1; iLines < 2/*countof(acLines)*/; iLines++)
                    {
                        PVOID apvBits[] = {NULL, (PVOID)-1, pvBits};

                        for (ipvBits = 0; ipvBits < 1/*countof(acLines)*/; ipvBits++)
                        {
                            PBITMAPINFO apbmi[] = {NULL, (PBITMAPINFO)-1, pbmi};

                            for (ipbmi = 2; ipbmi < 3/*countof(acLines)*/; ipbmi++)
                            {
                                UINT abiSize[] = {0, sizeof(BITMAPCOREHEADER)-1, sizeof(BITMAPCOREHEADER), sizeof(BITMAPCOREHEADER)+1, sizeof(BITMAPINFOHEADER), sizeof(BITMAPINFOHEADER)+1};

                                for (ibiSize = 4; ibiSize < 5/*countof(acLines)*/; ibiSize++)
                                {
                                    UINT auUsage[] = {DIB_RGB_COLORS, DIB_PAL_COLORS, 3, 4, -1};

                                    for (iUsage = 0; iUsage < 5/*countof(acLines)*/; iUsage++)
                                    {
                                        LONG aiSize[] = {0, 1, 2, 1000000, -1, -1000};

                                        for (iWidth = 0; iWidth < 5/*countof(acLines)*/; iWidth++)
                                        {
                                            for (iHeight = 0; iHeight < 5/*countof(acLines)*/; iHeight++)
                                            {
                                                UINT abiPlanes[] = { 0, 1, 2, 3, 64 };

                                                for (iPlanes = 0; iPlanes < 1/*countof(acLines)*/; iPlanes++)
                                                {
                                                    Compare(ahdc[ihdc],
                                                            ahbm[ihbm],
                                                            aiStart[iStart],
                                                            acLines[iLines],
                                                            apvBits[ipvBits],
                                                            apbmi[ipbmi],
                                                            auUsage[iUsage],
                                                            pbmi,
                                                            abiSize[ibiSize],
                                                            abiPlanes[iPlanes],
                                                            abiBitCount[iBpp],
                                                            aiSize[iWidth],
                                                            aiSize[iHeight]);
                                                }
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }
    }


}

void
Test_GetDIBits_xBpp(
    ULONG cBitsPixel)
{
    UCHAR ajBuffer[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
    PBITMAPINFO pbmi = (PBITMAPINFO)ajBuffer;
    HBITMAP hbmp;
    ULONG cjSizeImage, cColors;
    HDC hdc;

    hdc = GetDC(0);
    hbmp = CreateBitmap(3, 3, 1, cBitsPixel, NULL);

    /* Fill in the size field */
    ZeroMemory(pbmi, sizeof(ajBuffer));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    /* Get info */
    ok_int(GetDIBits(hdc, hbmp, 0, 0, NULL, pbmi, DIB_RGB_COLORS), 1);
    cjSizeImage = (((pbmi->bmiHeader.biWidth * pbmi->bmiHeader.biBitCount) + 31) & ~31) * pbmi->bmiHeader.biHeight / 8;
    cColors = cBitsPixel <= 8 ? 1 << pbmi->bmiHeader.biBitCount : 0;

    ok_int(pbmi->bmiHeader.biSize, sizeof(BITMAPINFOHEADER));
    ok_int(pbmi->bmiHeader.biWidth, 3);
    ok_int(pbmi->bmiHeader.biHeight, 3);
    ok_int(pbmi->bmiHeader.biPlanes, 1);
    ok_int(pbmi->bmiHeader.biBitCount, cBitsPixel);
    ok_int(pbmi->bmiHeader.biCompression, (cBitsPixel == 16) || (cBitsPixel == 32) ? BI_BITFIELDS : BI_RGB);
    ok_int(pbmi->bmiHeader.biSizeImage, cjSizeImage);
    ok_int(pbmi->bmiHeader.biXPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biYPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biClrUsed, cColors);
    ok_int(pbmi->bmiHeader.biClrImportant, cColors);

//    pbmi->bmiHeader.biSizeImage = 0;
   //ok_int(GetDIBits(NULL, hbmp, 0, 0, NULL, pbmi, DIB_RGB_COLORS), 1);

    /* Test a bitmap with values partly set */
    ZeroMemory(pbmi, sizeof(ajBuffer));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = 12;
    pbmi->bmiHeader.biHeight = 14;
    pbmi->bmiHeader.biPlanes = 2;
    pbmi->bmiHeader.biBitCount = 0; // keep biBitCount == 0!
    pbmi->bmiHeader.biCompression = 7;
    pbmi->bmiHeader.biSizeImage = 123;
    ok_int(GetDIBits(hdc, hbmp, 0, 5, NULL, pbmi, DIB_RGB_COLORS), 1);
    ok_int(pbmi->bmiHeader.biWidth, 3);
    ok_int(pbmi->bmiHeader.biHeight, 3);
    ok_int(pbmi->bmiHeader.biPlanes, 1);
    ok_int(pbmi->bmiHeader.biBitCount, cBitsPixel);
    ok_int(pbmi->bmiHeader.biSizeImage, cjSizeImage);
    ok_int(pbmi->bmiHeader.biXPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biYPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biClrUsed, cColors);
    ok_int(pbmi->bmiHeader.biClrImportant, cColors);


#if 0
    /* Get info including the color table */
    ZeroMemory(pbmi, sizeof(ajBuffer));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biBitCount = 1;
    ok_int(GetDIBits(NULL, hbmp, 0, 0, NULL, pbmi, DIB_PAL_COLORS), 1);

    /* Check a different bit depth */
    pbmi->bmiHeader.biBitCount, cBitsPixel = (cBitsPixel == 1) ? 8 : 1;
    ok_int(GetDIBits(hdc, hbmp, 0, 0, NULL, pbmi, DIB_RGB_COLORS), 1);
    ok_int(pbmi->bmiHeader.biBitCount, (cBitsPixel == 1) ? 8 : 1);

    /* Get the bits */
    SetLastError(0);
    ok_int(GetDIBits(hdc, hbmp, 0, 4, pvBits, pbmi, DIB_PAL_COLORS), 3);
    ok_int(GetDIBits(hdc, hbmp, 3, 7, pvBits, pbmi, DIB_RGB_COLORS), 1);
    ok_err(0);

    pbmi->bmiHeader.biPlanes = 2;
    pbmi->bmiHeader.biClrUsed = 0;
    ok_int(GetDIBits(hdc, hbmp, 0, 4, pvBits, pbmi, DIB_RGB_COLORS), 3);
#endif

    DeleteObject(hbmp);
    ReleaseDC(NULL, hdc);
}

void Test_GetDIBits()
{
    HDC hdcScreen, hdcMem;
    HBITMAP hbmp;
    PBITMAPINFO pbi;
    DWORD bisize;
    PBITMAPCOREHEADER pbch;
    PBITMAPV5HEADER pbV5Header;
    INT ScreenBpp;
    DWORD ajBits[100] = {0xff, 0x00, 0xcc, 0xf0, 0x0f};
    PVOID pvBits;
    ULONG cjSizeImage;

    bisize = sizeof(BITMAPV5HEADER) + 256 * sizeof(DWORD);
    pbi = malloc(bisize);
    pbch = (PVOID)pbi;
    pbV5Header = (PVOID)pbi;

    hdcScreen = GetDC(NULL);
    ok(hdcScreen != 0, "GetDC failed, skipping tests\n");
    if (hdcScreen == NULL) return;

    hbmp = CreateCompatibleBitmap(hdcScreen, 16, 16);
    ok(hbmp != NULL, "CreateCompatibleBitmap failed\n");

    /* misc */
    SetLastError(ERROR_SUCCESS);
    ok(GetDIBits(0, 0, 0, 0, NULL, NULL, 0) == 0, "\n");
    ok_err(ERROR_INVALID_PARAMETER);

    SetLastError(ERROR_SUCCESS);
    ok(GetDIBits((HDC)2345, 0, 0, 0, NULL, NULL, 0) == 0, "\n");
    ok_err(ERROR_INVALID_PARAMETER);

    SetLastError(ERROR_SUCCESS);
    ok(GetDIBits((HDC)2345, hbmp, 0, 0, NULL, NULL, 0) == 0, "\n");
    ok_err(ERROR_INVALID_PARAMETER);

    SetLastError(ERROR_SUCCESS);
    ok(GetDIBits((HDC)2345, hbmp, 0, 15, NULL, pbi, 0) == 0, "\n");
    ok_err(ERROR_INVALID_PARAMETER);



    /* null hdc */
    SetLastError(ERROR_SUCCESS);
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok(GetDIBits(NULL, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS) == 0, "\n");
    ok_err(ERROR_INVALID_PARAMETER);

    /* null bitmap */
    SetLastError(ERROR_SUCCESS);
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok(GetDIBits(hdcScreen, NULL, 0, 15, NULL, pbi, DIB_RGB_COLORS) == 0, "\n");
    ok_err(ERROR_SUCCESS);

    /* 0 scan lines */
    SetLastError(ERROR_SUCCESS);
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS) > 0, "\n");
    ok_err(ERROR_SUCCESS);

    /* null bitmap info - crashes XP*/
    //SetLastError(ERROR_SUCCESS);
    //ok(GetDIBits(hdcScreen, NULL, 0, 15, NULL, NULL, DIB_RGB_COLORS) == 0);
    //ok(GetLastError() == ERROR_INVALID_PARAMETER);

    /* bad bmi colours (uUsage) */
    SetLastError(0);
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, 100) == 0, "\n");
    ok_err(ERROR_SUCCESS);
    ok(pbi->bmiHeader.biWidth == 0, "\n");
    ok(pbi->bmiHeader.biHeight == 0, "\n");
    ok(pbi->bmiHeader.biBitCount == 0, "\n");
    ok(pbi->bmiHeader.biSizeImage == 0, "\n");

    /* basic call */
    SetLastError(ERROR_SUCCESS);
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS) > 0, "\n");
    ok_err(ERROR_SUCCESS);
    ScreenBpp = GetDeviceCaps(hdcScreen, BITSPIXEL);
    ok(pbi->bmiHeader.biWidth == 16, "\n");
    ok(pbi->bmiHeader.biHeight == 16, "\n");
    ok(pbi->bmiHeader.biBitCount == ScreenBpp, "\n");
    ok(pbi->bmiHeader.biSizeImage == (16 * 16) * (ScreenBpp / 8), "\n");

    /* Test if COREHEADER is supported */
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPCOREHEADER);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biSize, sizeof(BITMAPCOREHEADER));
    ok_int(pbch->bcWidth, 16);
    ok_int(pbch->bcHeight, 16);
    ok_int(pbch->bcPlanes, 1);
    //ok_int(pbch->bcBitCount, ScreenBpp > 16 ? 24 : ScreenBpp); // fails on XP with screenbpp == 16

    /* Test different header sizes */
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPCOREHEADER) + 4;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS), 0);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER) + 4;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS), 1);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPV4HEADER);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS), 1);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPV4HEADER) + 4;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS), 1);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPV5HEADER);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS), 1);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPV5HEADER) + 4;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 15, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbV5Header->bV5RedMask, 0);
    ok_int(pbV5Header->bV5GreenMask, 0);
    ok_int(pbV5Header->bV5BlueMask, 0);
    ok_int(pbV5Header->bV5AlphaMask, 0);
    ok_int(pbV5Header->bV5CSType, 0);
    // CIEXYZTRIPLE bV5Endpoints;
    ok_int(pbV5Header->bV5GammaRed, 0);
    ok_int(pbV5Header->bV5GammaGreen, 0);
    ok_int(pbV5Header->bV5GammaBlue, 0);
    ok_int(pbV5Header->bV5Intent, 0);
    ok_int(pbV5Header->bV5ProfileData, 0);
    ok_int(pbV5Header->bV5ProfileSize, 0);
    ok_int(pbV5Header->bV5Reserved, 0);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok_int(GetDIBits(hdcScreen, hbmp, 234, 43, NULL, pbi, DIB_RGB_COLORS), 1);

    DeleteObject(hbmp);

    /* Test a mono bitmap */
    hbmp = CreateBitmap(13, 7, 1, 1, ajBits);
    ok(hbmp != 0, "failed to create bitmap\n");
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biWidth, 13);
    ok_int(pbi->bmiHeader.biHeight, 7);
    ok_int(pbi->bmiHeader.biBitCount, 1);
    ok_int(pbi->bmiHeader.biSizeImage, 28);

    /* Test with values set, except biSizeImage */
    pbi->bmiHeader.biSizeImage = 0;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biSizeImage, 28);

    /* Test with different biWidth set */
    pbi->bmiHeader.biWidth = 17;
    pbi->bmiHeader.biHeight = 3;
    pbi->bmiHeader.biSizeImage = 0;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biSizeImage, 12);
    ok_int(pbi->bmiHeader.biWidth, 17);
    ok_int(pbi->bmiHeader.biHeight, 3);

    /* Test with different biBitCount set */
    pbi->bmiHeader.biBitCount = 4;
    pbi->bmiHeader.biSizeImage = 1;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biSizeImage, 36);
    ok_int(pbi->bmiHeader.biBitCount, 4);

    /* Test with different biBitCount set */
    pbi->bmiHeader.biBitCount = 8;
    pbi->bmiHeader.biSizeImage = 1000;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biSizeImage, 60);
    ok_int(pbi->bmiHeader.biBitCount, 8);

    /* Test with invalid biBitCount set */
    pbi->bmiHeader.biBitCount = 123;
    pbi->bmiHeader.biSizeImage = -12;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 0);
    ok_int(pbi->bmiHeader.biSizeImage, -12);
    ok_int(pbi->bmiHeader.biBitCount, 123);

    /* Set bitmap dimensions */
    ok_int(SetBitmapDimensionEx(hbmp, 110, 220, NULL), 1);
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biXPelsPerMeter, 0);
    ok_int(pbi->bmiHeader.biYPelsPerMeter, 0);

    /* Set individual values */
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biWidth = 12;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biWidth, 13);
    ok_int(pbi->bmiHeader.biSizeImage, 28);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biSizeImage = 123;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);

    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biCompression = BI_RGB;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);

    /* Set only biBitCount */
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biBitCount = 5;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biBitCount = 1;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biBitCount = 8;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biBitCount = 32;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    ok_int(pbi->bmiHeader.biWidth, 0);
    ok_int(pbi->bmiHeader.biHeight, 0);
    ok_int(pbi->bmiHeader.biPlanes, 0);
    ok_int(pbi->bmiHeader.biBitCount, 32);
    ok_int(pbi->bmiHeader.biCompression, 0);
    ok_int(pbi->bmiHeader.biSizeImage, 0);

    /* Get the bitmap info */
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biWidth = 4;
    pbi->bmiHeader.biHeight = 4;
    pbi->bmiHeader.biPlanes = 3;
    pbi->bmiHeader.biBitCount = 32;
    pbi->bmiHeader.biCompression = BI_RGB;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biSizeImage, 64);
    ok_int(pbi->bmiHeader.biPlanes, 1);
    pbi->bmiHeader.biWidth = 0;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biWidth = 2;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biSizeImage, 32);
    pbi->bmiHeader.biWidth = -3;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biWidth = 4;
    pbi->bmiHeader.biHeight = 0;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biHeight = -4;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);
    pbi->bmiHeader.biBitCount = 31;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biBitCount = 16;
    pbi->bmiHeader.biPlanes = 23;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biPlanes, 1);
    SetLastError(0xdeadbabe);
    ok_int(GetDIBits((HDC)0xff00ff00, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    ok_err(0x57);
    SetLastError(0xdeadbabe);
    ok_int(GetDIBits(hdcScreen, (HBITMAP)0xff00ff00, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    ok_err(0xdeadbabe);
    SetLastError(0xdeadbabe);
    ok_int(GetDIBits((HDC)0xff00ff00, (HBITMAP)0xff00ff00, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    ok_err(0x57);
    SetLastError(0xdeadbabe);
    ok_int(GetDIBits(NULL, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    ok_err(0x57);

    pbi->bmiHeader.biCompression = BI_JPEG;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biCompression = BI_PNG;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 5, NULL, pbi, DIB_RGB_COLORS), 0);

    /* Get the bitmap bits */
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biWidth = 4;
    pbi->bmiHeader.biHeight = 4;
    pbi->bmiHeader.biPlanes = 1;
    pbi->bmiHeader.biBitCount = 32;
    pbi->bmiHeader.biCompression = BI_RGB;
    pbi->bmiHeader.biSizeImage = 0;
    pbi->bmiHeader.biXPelsPerMeter = 0;
    pbi->bmiHeader.biYPelsPerMeter = 0;
    pbi->bmiHeader.biClrUsed = 0;
    pbi->bmiHeader.biClrImportant = 0;
    cjSizeImage = ((pbi->bmiHeader.biWidth * pbi->bmiHeader.biBitCount + 31) / 32) * 4 * pbi->bmiHeader.biHeight;
    pvBits = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 512);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 4);
    ok_int(pbi->bmiHeader.biSize, sizeof(BITMAPINFOHEADER));
    ok_int(pbi->bmiHeader.biWidth, 4);
    ok_int(pbi->bmiHeader.biHeight, 4);
    ok_int(pbi->bmiHeader.biPlanes, 1);
    ok_int(pbi->bmiHeader.biBitCount, 32);
    ok_int(pbi->bmiHeader.biCompression, BI_RGB);
    ok_int(pbi->bmiHeader.biSizeImage, 64);
    ok_int(pbi->bmiHeader.biXPelsPerMeter, 0);
    ok_int(pbi->bmiHeader.biYPelsPerMeter, 0);
    ok_int(pbi->bmiHeader.biClrUsed, 0);
    ok_int(pbi->bmiHeader.biClrImportant, 0);

    /* Get the bitmap bits */
    pbi->bmiHeader.biPlanes = 0;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 0);
    pbi->bmiHeader.biPlanes = 1;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 4);

    Compare(hdcScreen,
            hbmp,
            0,
            4,
            pvBits,
            pbi,
            DIB_RGB_COLORS,
            pbi,
            sizeof(BITMAPINFOHEADER),
            0,
            4,
            3,
            5);

    /* Set biBitCount to 0 */
    pbi->bmiHeader.biBitCount = 0;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 0);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, (PVOID)(LONG_PTR)-1, pbi, DIB_RGB_COLORS), 0);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(GetDIBits(NULL, hbmp, 0, 4, NULL, pbi, DIB_RGB_COLORS), 0);

    /* Try different biBitCount and biWidth */
    pbi->bmiHeader.biBitCount = 24;
    pbi->bmiHeader.biWidth = 3;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 4);

    /* Try different biBitCount and biWidth */
    pbi->bmiHeader.biBitCount = 24;
    pbi->bmiHeader.biWidth = 3;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 4);

    /* Try invalid biBitCount */
    pbi->bmiHeader.biBitCount = 17;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 0);

    /* Set only biBitCount and pjInit */
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biBitCount = 5;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 0);

    /* Set only biBitCount and pjInit */
    pbi->bmiHeader.biBitCount = 4;
    pbi->bmiHeader.biWidth = 3;
    pbi->bmiHeader.biHeight = 3;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 0);

    DeleteObject(hbmp);
    HeapFree(GetProcessHeap(), 0, pvBits);

    /* Test a 4 bpp bitmap */
    hbmp = CreateBitmap(3, 5, 1, 4, NULL);
    ok(hbmp != 0, "failed to create bitmap\n");
    ZeroMemory(pbi, bisize);
    pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 1);
    ok_int(pbi->bmiHeader.biWidth, 3);
    ok_int(pbi->bmiHeader.biHeight, 5);
    ok_int(pbi->bmiHeader.biBitCount, 4);
    ok_int(pbi->bmiHeader.biSizeImage, 20);

    /* This does NOT work with incompatible bitmaps */
    pbi->bmiHeader.biSizeImage = 0;
    ok_int(GetDIBits(hdcScreen, hbmp, 0, 0, NULL, pbi, DIB_RGB_COLORS), 0);

    /* Calculate bitmap size and allocate a buffer */
    cjSizeImage = ((pbi->bmiHeader.biWidth * pbi->bmiHeader.biBitCount + 31) / 32) * 4 * pbi->bmiHeader.biHeight;
    ok_int(cjSizeImage, 20);
    pvBits = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cjSizeImage);

    ok_int(GetDIBits(ghdcDIB4, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 0);
    ok_int(GetDIBits(ghdcDIB4, ghbmpDIB4, 0, 7, pvBits, pbi, DIB_RGB_COLORS), 5);

    Compare(ghdcDIB4,
            ghbmpDIB4,
            0,
            7,
            pvBits,
            pbi,
            DIB_RGB_COLORS,
            pbi,
            sizeof(BITMAPINFOHEADER),
            0,
            4,
            3,
            5);

    /* Test using a compatible DC */
    hdcMem = CreateCompatibleDC(0);
    ok(hdcMem != 0, "CreateCompatibleDC failed, skipping tests\n");
    if (hdcMem == NULL) return;
    ok_int(GetDIBits(hdcMem, hbmp, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 0);
    ok_int(GetDIBits(hdcMem, ghbmpDIB4, 0, 4, pvBits, pbi, DIB_RGB_COLORS), 4);

    HeapFree(GetProcessHeap(), 0, pvBits);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
}

void Test_GetDIBits_BI_BITFIELDS()
{
}

START_TEST(GetDIBits)
{
    //getchar();
    InitStuff();
    //Test_GetDIBits_xBpp(1);
    //Test_GetDIBits_xBpp(4);
    //Test_GetDIBits_xBpp(8);
    //Test_GetDIBits_xBpp(16);
    //Test_GetDIBits_xBpp(24);
    //Test_GetDIBits_xBpp(32);
    //Test_GetDIBits();
    Test_AllParams();
}

