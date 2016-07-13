

enum
{
    StretchMode_XS_YS = 0, /* x: shrink, y shrink */
    StretchMode_XE_YS = 1, /* x: expand, y shrink */
    StretchMode_XS_YE = 2, /* x: shrink, y expand */
    StretchMode_XE_YE = 3  /* x: expand, y expand */
};

{

    jStretchMode = ((cyDst > cySrc) ? 2 : 0) | ((cxDst > cxSrc) ? 1 : 0);

    if (jStretchMode == StretchMode_XS_YS)
    {
        for (yDst = yDstStart; yDst < yDstEnd; yDst++, vySrc += vdySrc)
        {

            for (xDst = xDstStart; xDst < xDstEnd; xDst++, vxSrcX += vdxSrc)
            {

                ulSource = _ReadPixel(_SOURCE_BPP, pjSource, jSrcShift);

            }

        }
    }

}

StretchBlt_DELETESCANS
{

    if (cyDst > cySrc)
    {
        if (cxDst > cxSrc)
        {
        }
    }
    else
    {
        if (cxDst > cxSrc)
        {
        }
        else
        {
            /* This is case 4: compressing in x and y direction */
            for (yDst = yDstStart; yDst < yDstEnd; yDst++, vySrc += vdySrc)
            {

                for (xDst = xDstStart; xDst < xDstEnd; xDst++, vxSrcX += vdxSrc)
                {

                    ulSource = _ReadPixel(_SOURCE_BPP, pjSource, jSrcShift);

                }

            }
        }
    }

}
