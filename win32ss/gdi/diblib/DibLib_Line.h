
#define _DibFunction __DIB_FUNCTION_NAME(__FUNCTIONNAME, _SOURCE_BPP, _DEST_BPP)

VOID
FASTCALL
_DibFunction(
    PLINEDATA pli)
{
#if 0
    LONG x, y, xMax, cx, dy;
    ULONG iRun, iStyle;
    LONG lGamma;

    /* Outer loop to handle multiple runs */
    iRun = 0;
    do
    {
        /* Get the start and end position of this run */
        x = pli->cl.arun[iRun].iStart;
        xMax = pli->cl.arun[iRun].iStop;

        /* Get the y start coordinate */
        y = pli->runOtherCoordinate.iStart;

        /* Set y advance */
        dy = (pli->runOtherCoordinate.iStop > y) ? 1 : -1;

        /* Check if we have styles */
        if (pli->cStyles > 0)
        {
            /* Style count must be even and max 16! */
            NT_ASSERT((pli->cStyles & 1) == 0);
            NT_ASSERT(pli->cStyles <= 16);

            /* Get the current style index */
            iStyle = pli->iStyle;
            NT_ASSERT(iStyle < pli->cStyles);

            /* Calculate the remaining pixels */
            cx = pli->acxyStyle[iStyle] - pli->xyStylePos;

            /* Check if this is a space style step */
            if (iStyle & 1)
            {
                /* Skip this style index and continue with the next one */
                SkipPixels(cx, pli, &x, &y, dy, &lGamma);

                iStyle = (iStyle + 1) % pli->cStyles;

                /* Get new cx */
                cx = pli->acxyStyle[iStyle];
            }

            xMax = min(xMax, x + cx);
        }

        /* Get the gamma value */
        lGamma = pli->lGamma;

        /* 2nd loop for styles */
        while (TRUE)
        {
            /* 3rd loop for the pixels */
            while (x < xMax)
            {
                /* Draw this pixel */
                _PutPixel(pli, x, y);

                /* Advance one pixel in x direction */
                x++;

                lGamma -= pli->lDelta; // lDelta = (ptfxB.y - prfxA.y)
                if (lGamma < 0)
                {
                    y += dy;
                    lGamma += pli->lGamma0;
                }
            }

            /* If there are no styles, we are done */
            if (pli->cStyles == 0)
            {
                break;
            }

            /* Skip the next (odd, i.e. NULL) style index */
            cx = pli->acxyStyle[iStyle + 1];

            /* Check if that's still within the current run */
            if (x + cx > pli->cl.arun[iRun].iStop)
            {
                break;
            }

            /*  */
            SkipPixels(cx, pli, &x, &y, dy, &lGamma);

            /* Advance by 2 styles */
            iStyle = (iStyle + 2) % pli->cStyles;

            /* Recalculate xMax */
            xMax = min(pli->cl.arun[iRun].iStop, x + pli->acxyStyle[iStyle]);
        }

        iRun++;

    } while (iRun < pli->cl.c);
#endif
}

