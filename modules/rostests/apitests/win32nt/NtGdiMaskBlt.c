
INT
Test_NtGdiMaskBlt(PTESTINFO pti)
{
    HDC hdcDst, hdcSrc;
    HBITMAP hbmDst, hbmSrc, hbmMask;
    BOOL ret;

    hdcDst = CreateCompatibleDC(0);
    hdcSrc = CreateCompatibleDC(0);
    ASSERT(hdcDst != 0 && hdcSrc != 0);

    hbmDst = CreateCompatibleBitmap(hdcDst, 4, 4);
    hbmSrc = CreateCompatibleBitmap(hdcDst, 2, 4);
    hbmMask = CreateBitmap(4, 2, 1, 1, NULL);
    ASSERT(hbmDst != 0 && hbmSrc != 0 && hbmMask != 0);

    SelectObject(hdcDst, hbmDst);
    SelectObject(hdcSrc, hbmSrc);

    /* Test SRCCOPY */
    ret = MaskBlt(hdcDst, 0, 0, 2, 2, hdcSrc, 0, 0, hbmMask, 0, 0, SRCCOPY);
    TEST(ret == 1);

    /* Test with too big sizes */
    ret = MaskBlt(hdcDst, 0, 0, 4, 4, hdcSrc, 0, 0, hbmMask, 0, 0, SRCCOPY);
    TEST(ret == 0);
    ret = MaskBlt(hdcDst, 0, 0, 2, 4, hdcSrc, 0, 0, hbmMask, 0, 0, SRCCOPY);
    TEST(ret == 0);
    ret = MaskBlt(hdcDst, 0, 0, 5, 2, hdcSrc, 0, 0, hbmMask, 0, 0, SRCCOPY);
    TEST(ret == 0);

    /* Exceeds the source size, yet works */
    ret = MaskBlt(hdcDst, 0, 0, 4, 2, hdcSrc, 0, 0, hbmMask, 0, 0, SRCCOPY);
    TEST(ret == 1);

    /* Mask position out of bounds */
    ret = MaskBlt(hdcDst, 0, 0, 2, 2, hdcSrc, 7, 5, hbmMask, 0, 0, SRCCOPY);
    TEST(ret == 1);

    /* ROP with pattern */
    ret = MaskBlt(hdcDst, 0, 0, 2, 2, hdcSrc, 0, 0, hbmMask, 0, 0, PATCOPY);
    TEST(ret == 1);

    /* Cleanup */
    DeleteDC(hdcDst);
    DeleteDC(hdcSrc);

    return APISTATUS_NORMAL;
}
