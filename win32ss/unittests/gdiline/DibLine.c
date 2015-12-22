
VOID
DibLine(
    PLINEINFO pli)
{
    LONG x, y, xMax, cx, dy;
    ULONG iRun, iStyle;
    LONG lRemainder;

    /* Style count must be even and max 16! */
    NT_ASSERT((pli->cStyles & 1) == 0);
    NT_ASSERT(pli->cStyles <= 16);

    /* Get the y start coordinate */
    y = pli->runOtherCoordinate.iStart;

    /* Set y advance */
    dy = pli->dy;//(pli->runOtherCoordinate.iStop > y) ? 1 : -1;

    /* Get the initial remainder value */
    lRemainder = pli->lRemainder;

    /* Outer loop to handle multiple runs */
    iRun = 0;
    do
    {
        /* Get the start and end position of this run */
        x = pli->cl.arun[iRun].iStart;
        xMax = pli->cl.arun[iRun].iStop;

        /* Check if we have styles */
        if (pli->cStyles > 0)
        {
            /* Get the current style index */
            iStyle = pli->iStyle;
            NT_ASSERT(iStyle < pli->cStyles);

            /* Calculate the remaining pixels */
            cx = pli->acxyStyle[iStyle] - pli->xyStylePos;

            /* Check if this is a space style step */
            if (iStyle & 1)
            {
                /* Skip this style index and continue with the next one */
                SkipPixels(cx, pli, &x, &y, dy, &lRemainder);

                iStyle = (iStyle + 1) % pli->cStyles;

                /* Get new cx */
                cx = pli->acxyStyle[iStyle];
            }

            xMax = min(xMax, x + cx);
        }

        /* 2nd loop for styles */
        while (TRUE)
        {
            /* 3rd loop for the pixels */
            while (x != xMax)
            {
                /* Draw this pixel */
                _PutPixel(pli, x, y);

                /* Advance one pixel in x direction */
                x += pli->dx;

                /* Update the remainder and check if went below 0 */
                lRemainder -= pli->lNumerator; // lNumerator = (y2 - y1)
                if (lRemainder < 0)
                {
                    /* We need to go 1 pixel down (or up) */
                    y += dy;

                    /* Account for this in the remainder */
                    lRemainder += pli->lDenominator;
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
            SkipPixels(cx, pli, &x, &y, dy, &lRemainder);

            /* Advance by 2 styles */
            iStyle = (iStyle + 2) % pli->cStyles;

            /* Recalculate xMax */
            xMax = min(pli->cl.arun[iRun].iStop, x + pli->acxyStyle[iStyle]);
        }

        iRun++;

    } while (iRun < pli->cl.c);

}

