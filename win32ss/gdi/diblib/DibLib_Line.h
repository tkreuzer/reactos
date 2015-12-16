
#define _DibLine __DIB_FUNCTION_NAME(__FUNCTIONNAME, _SOURCE_BPP, _DEST_BPP)
#define _SkipPixels __DIB_FUNCTION_NAME(__PASTE(__FUNCTIONNAME, _SkipPixels) , _SOURCE_BPP, _DEST_BPP)

#define _WritePixel(pj, jShift, c) __PASTE(_WritePixel_, _DEST_BPP)(pj, jShift, c)
#define _SHIFT(bpp, x) __PASTE(_SHIFT_, bpp)(x)

#ifdef __INVERTED_COORDINATES
#define _CalcDest(psi, x, y) ((PUCHAR)((psi)->pvScan0) + (x * (psi)->lDelta) + (_DEST_BPP * y / 8))
#define _NextPixelY(bpp, ppj, pjShift, dy) __PASTE(_NextPixel_, bpp)(ppj, pjShift)
#define _NextPixelX(bpp, ppj, pjShift)  *(ppj) += pld->siDst.cjAdvanceY
#define _CALCSHIFT(bpp, pshift, x, y) __PASTE(_CALCSHIFT_, bpp)(pshift, y)
#else
#define _CalcDest(psi, x, y) ((PUCHAR)((psi)->pvScan0) + (y * (psi)->lDelta) + (_DEST_BPP * x / 8))
#define _NextPixelX(bpp, ppj, pjShift) __PASTE(_NextPixel_, bpp)(ppj, pjShift)
#define _NextPixelY(bpp, ppj, pjShift, dy)  *(ppj) += (dy) * pld->siDst.cjAdvanceY
#define _CALCSHIFT(bpp, pshift, x, y) __PASTE(_CALCSHIFT_, bpp)(pshift, x)
#endif

#if 0 && DBG
#define NT_ASSERT(exp) ((VOID)((!(exp)) ? (__int2c(), FALSE) : TRUE))
#else
#define NT_ASSERT(exp)
#endif

FORCEINLINE
VOID
_SkipPixels(
    LONG cx,
    PLINEDATA pld,
    LONG *px,
    LONG *py,
    LONG dy,
    LONG *plRemainder)
{
    LONG lDiv, lMod;

    *px += cx;

    lDiv = MulDivMod(cx, pld->lDelta, pld->lRemainder0, &lMod);

    *py += dy * lDiv;

    *plRemainder -= lMod;

    if (*plRemainder < 0)
    {
        *py += dy;
        *plRemainder += pld->lRemainder0;
    }
}

VOID
FASTCALL
_DibLine(
    PLINEDATA pld)
{
    LONG x, y, xMax, cx, dy;
    ULONG iRun, iStyle;
    LONG lRemainder;
    PBYTE pjDest, pjDestBase;
    _SHIFT(_DEST_BPP, BYTE jDstShift;)

    pjDestBase = pld->siDst.pjBase;

    /* Get the y start coordinate */
    y = pld->runOtherCoordinate.iStart;

    /* Set y advance */
    dy = (pld->runOtherCoordinate.iStop > y) ? 1 : -1;

    /* Get the initial remainder value */
    lRemainder = pld->lRemainder;

    /* Outer loop to handle multiple runs */
    iRun = 0;
    do
    {
        /* Get the start and end position of this run */
        x = pld->cl.arun[iRun].iStart;
        xMax = pld->cl.arun[iRun].iStop;

        /* Check if we have styles */
        if (pld->cStyles > 0)
        {
            /* Style count must be even and max 16! */
            NT_ASSERT((pld->cStyles & 1) == 0);
            NT_ASSERT(pld->cStyles <= 16);

            /* Get the current style index */
            iStyle = pld->iStyle;
            NT_ASSERT(iStyle < pld->cStyles);

            /* Calculate the remaining pixels */
            cx = pld->acxyStyle[iStyle] - pld->xyStylePos;

            /* Check if this is a space style step */
            if (iStyle & 1)
            {
                /* Skip this style index and continue with the next one */
                _SkipPixels(cx, pld, &x, &y, dy, &lRemainder);

                iStyle = (iStyle + 1) % pld->cStyles;

                /* Get new cx */
                cx = pld->acxyStyle[iStyle];
            }

            xMax = min(xMax, x + cx);
        }

        /* 2nd loop for styles */
        while (TRUE)
        {
            pjDest = _CalcDest(&pld->siDst, x, y);
            _CALCSHIFT(_DEST_BPP, &jDstShift, x, y);

            /* 3rd loop for the pixels */
            while (x < xMax)
            {
                /* Write the pixel and go to the next dest pixel */
                _WritePixel(pjDest, jDstShift, pld->ulColor);
                _NextPixelX(_DEST_BPP, &pjDest, &jDstShift);

                /* Update the remainder and check if went below 0 */
                lRemainder -= pld->lDelta;
                if (lRemainder < 0)
                {
                    /* We need to go 1 pixel down (or up) */
                    y += dy;
                    _NextPixelY(_DEST_BPP, &pjDest, &jDstShift, dy);

                    /* Account for this in the remainder */
                    lRemainder += pld->lRemainder0;
                }
            }

            x = xMax;

            /* If there are no styles, we are done */
            if (pld->cStyles == 0)
            {
                break;
            }

            /* Skip the next (odd, i.e. NULL) style index */
            cx = pld->acxyStyle[iStyle + 1];

            /* Check if that's still within the current run */
            if (x + cx > pld->cl.arun[iRun].iStop)
            {
                break;
            }

            /*  */
            _SkipPixels(cx, pld, &x, &y, dy, &lRemainder);

            /* Advance by 2 styles */
            iStyle = (iStyle + 2) % pld->cStyles;

            /* Recalculate xMax */
            xMax = min(pld->cl.arun[iRun].iStop, x + pld->acxyStyle[iStyle]);
        }

        iRun++;

    } while (iRun < pld->cl.c);
}

#undef _DibLine
#undef _CalcDest
#undef _NextPixelX
#undef _NextPixelY
#undef _CALCSHIFT
#undef __FUNCTIONNAME2
