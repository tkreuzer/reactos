
#define _DibLine __DIB_FUNCTION_NAME(__FUNCTIONNAME, _SOURCE_BPP, _DEST_BPP)
#define _SkipPixels __DIB_FUNCTION_NAME(__PASTE(__FUNCTIONNAME, _SkipPixels) , _SOURCE_BPP, _DEST_BPP)

#define _WritePixel(pj, jShift, c) __PASTE(_WritePixel_, _DEST_BPP)(pj, jShift, c)
#define _SHIFT(bpp, x) __PASTE(_SHIFT_, bpp)(x)

#ifdef __INVERTED_COORDINATES
#define _CalcDest(psi, x, y) ((PUCHAR)((psi)->pvScan0) + (x * (psi)->lDelta) + (_DEST_BPP * y / 8))
#define _NextPixelY(bpp, ppj, pjShift) __PASTE(_NextPixel_, bpp)(ppj, pjShift)
#define _NextPixelX(bpp, ppj, pjShift)  *(ppj) += pld->siDst.cjAdvanceY
#define _CALCSHIFT(bpp, pshift, x, y) __PASTE(_CALCSHIFT_, bpp)(pshift, y)
#else
#define _CalcDest(psi, x, y) ((PUCHAR)((psi)->pvScan0) + (y * (psi)->lDelta) + (_DEST_BPP * x / 8))
#define _NextPixelX(bpp, ppj, pjShift) __PASTE(_NextPixel_, bpp)(ppj, pjShift)
#define _NextPixelY(bpp, ppj, pjShift)  *(ppj) += pld->siDst.cjAdvanceY
#define _CALCSHIFT(bpp, pshift, x, y) __PASTE(_CALCSHIFT_, bpp)(pshift, x)
#endif

#if 0 && DBG
#define NT_ASSERT(exp) ((VOID)((!(exp)) ? (__int2c(), FALSE) : TRUE))
#else
#define NT_ASSERT(exp)
#endif

#define _AdvanceX(ppj, pjShift, cx) (*(ppj) += (_DEST_BPP * cx / 8)), (*(pjShift) += cx),

#define _NextPixel_4(ppj, pjShift)    (void)((*(pjShift)) ^= 4, (*(ppj) += (*(pjShift) != 0)))
#define _NextPixelR2L_4(ppj, pjShift) (void)((*(pjShift)) ^= 4, (*(ppj) -= (*(pjShift) == 0)))

#define _AdvanceX_1(ppj, pjShift, cx)    (void)(((*(pjShift)) -= ((cx & 1) << 2)), (*(ppj) += (cx/2) + (*(pjShift) > 4)), (*(pjShift) &= 7))
#define _AdvanceXR2L_1(ppj, pjShift, cx) (void)(((*(pjShift)) += ((cx & 1) << 2)), (*(ppj) -= (cx/2) + (*(pjShift) > 4)), (*(pjShift) &= 7))

FORCEINLINE
VOID
_SkipPixels(
    LONG cx,
    PLINEDATA pld,
    PBYTE *ppjDest,
    LONG *px,
    LONG *plRemainder)
{
    LONG lDiv, lMod;

    *px += cx;
    *ppjDest += (8 * cx / _DEST_BPP);

    lDiv = MulDivMod(cx, pld->lNumerator, pld->lDenominator, &lMod);

    *ppjDest += lDiv * pld->siDst.cjAdvanceY;

    *plRemainder -= lMod;
    if (*plRemainder < 0)
    {
        /* We need to go 1 pixel down (or up) */
        _NextPixelY(_DEST_BPP, ppjDest, pjDstShift);

        /* Account for this in the remainder */
        *plRemainder += pld->lDenominator;
    }

}

VOID
FASTCALL
_DibLine(
    PLINEDATA pld)
{
    LONG x, y, xMax, cx;
    ULONG iRun, iStyle;
    LONG lRemainder;
    PBYTE pjDest;
    _SHIFT(_DEST_BPP, BYTE jDstShift;)

    /* Style count must be even and max 16! */
    NT_ASSERT((pld->cStyles & 1) == 0);
    NT_ASSERT(pld->cStyles <= 16);

    /* Get the start coordinates */
    x = pld->cl.arun[0].iStart;
    y = pld->runOtherCoordinate.iStart;
    pjDest = _CalcDest(&pld->siDst, x, y);
    _CALCSHIFT(_DEST_BPP, &jDstShift, x, y);

    /* Get the initial remainder value */
    lRemainder = pld->lRemainder;

    /* Check if we have styles */
    if (pld->cStyles > 0)
    {
        /* Get the current style index */
        iStyle = pld->iStyle;
        NT_ASSERT(iStyle < pld->cStyles);

        /* Calculate the remaining pixels */
        cxStyle = pld->acxyStyle[iStyle] - pld->xyStylePos;
        xStyleMax = x + cxStyle;
    }

    /* Outer loop to handle multiple runs */
    iRun = 0;
    for (;;)
    {
        /* Get the end of this run */
        xMax = pld->cl.arun[iRun].iStop;

        /* Check if we have styles */
        if (pld->cStyles > 0)
        {
            /* First we need to recalculate the style position. We need to
               do this anyway within this function, whenever a new run starts,
               so we can do it right here, taking the effort of calculating it
               away from the caller */
            xStyle = (x + pld->cxyStyleOffset) % pld->cxyStyleSize;

            /* Now loop until we have found the style index */
            for (iStyle = 0; xStyle > pld->acxyStyle[iStyle]; iStyle++)
            {
                xStyle -= pld->acxyStyle[iStyle];
            }

            /* Calculate the remaining pixels for this style index */
            cxStyle = pld->acxyStyle[iStyle] - xStyle;

            /* Check if this style index is a gap */
            if (iStyle & 1)
            {
                /* Bail out, if it covers the whole run */
                if (x + cxStyle > xMax)
                {
                    /// FIXME
                    break;
                }

                /* Skip this style index and continue with the next one */
                _SkipPixels(cxStyle, pld, &pjDest, &x, &lRemainder);

                iStyle = (iStyle + 1) % pld->cStyles;

                /* Get new cx */
                cxStyle = pld->acxyStyle[iStyle];
            }

            if (x + cxStyle < xMax)
            {
                cx = cxStyle;
                bMoreStyles = TRUE;
            }
            else
            {
                bMoreStyles = TRUE;
            }
        }

        /* 2nd loop for styles */
        while (TRUE)
        {
            /* 3rd loop for the pixels */
            do
            {
                /* Write the pixel and go to the next dest pixel */
                _WritePixel(pjDest, jDstShift, pld->ulColor);
                _NextPixelX(_DEST_BPP, &pjDest, &jDstShift);

                /* Update the remainder and check if went below 0 */
                lRemainder -= pld->lNumerator;
                if (lRemainder < 0)
                {
                    /* We need to go 1 pixel down (or up) */
                    _NextPixelY(_DEST_BPP, &pjDest, &jDstShift);

                    /* Account for this in the remainder */
                    lRemainder += pld->lDenominator;
                }
            }
            while (++x < xMax);

            /* If there are no more styles, we are done with this run */
            if (!bMoreStyles)
            {
                break;
            }

            /* Get the length of the next (odd, i.e. gap) style index */
            cxStyle = pld->acxyStyle[iStyle + 1];

            /* Check if that's still within the current run */
            if (x + cxStyle >= pld->cl.arun[iRun].iStop)
            {
                break;
            }

            _SkipPixels(cxStyle, pld, &pjDest, &x, &lRemainder);

            /* Advance by 2 styles */
            iStyle = (iStyle + 2) % pld->cStyles;

            /* Recalculate xMax */
            xMax = min(pld->cl.arun[iRun].iStop, x + pld->acxyStyle[iStyle]);
        }

        iRun++;
        if (iRun >= pld->cl.c)
        {
            break;
        }

        /* Get the next start */
        cx = pld->cl.arun[iRun].iStart - x;
        _SkipPixels(cx, pld, &pjDest, &x, &lRemainder);
    }
}

#undef _DibLine
#undef _CalcDest
#undef _NextPixelX
#undef _NextPixelY
#undef _CALCSHIFT
#undef __FUNCTIONNAME2
