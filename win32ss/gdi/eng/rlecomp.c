/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS kernel
 * PURPOSE:           RLE compression
 * FILE:              subsystems/win32k/eng/rlecomp.c
 * PROGRAMER:         Jason Filby
 */

#include <win32k.h>

#define NDEBUG
#include <debug.h>

enum Rle_EscapeCodes
{
    RLE_EOL   = 0, /* End of line */
    RLE_END   = 1, /* End of bitmap */
    RLE_DELTA = 2  /* Delta */
};

BOOL
NTAPI
RleDecompressBitmap(
    _In_ PSIZEL psizel,
    _In_bytecount_(cjCompressedSize) PBYTE pjCompressedBits,
    _In_ ULONG cjCompressedSize,
    _Out_bytecap_(cjUncompressedSize) PBYTE pjUncompressedBits,
    _In_ ULONG cjUncompressedSize,
    _In_ LONG lDelta,
    _In_ ULONG iFormat)
{
    UCHAR jShift;
    PBYTE pjCurrent;

    /* Check the format */
    if ((Format == BMF_4RLE) || (Format == BMF_4BPP))
    {
        jShift = 1;
    }
    else if ((Format == BMF_8RLE) || (Format == BMF_8BPP))
    {
        jShift = 0;
    }
    else
    {
        ERR("Invalid format for RLE: %lu\n", iFormat);
        return FALSE;
    }

    /* Check if the output buffer is large enough */

    cjWidth = ((Size.cx + jShift) >> jShift);

    do
    {
        /* A command consists of at least 2 bytes */
        if (pjSource > (pjSourceEnd - 2))
        {
            ERR("Error while decompressing RLE. Unexpected end of data\n");
            return FALSE;
        }

        /* Get the first byte and check if it's 0 */
        jCode = *pjSource++;
        if (jCode != 0)
        {
            /* Second byte is the color */
            jColor = *pjSource++;


            if (bIs16Bit)
            {

            }


            /* We have the number of pixels, convert it to bytes */
            jLength = jCode >> jShift;

            /* Limit the length to not overflow the bitmap size */
            jLength = min(jLength, cjWidth - x);

            /* Not 0, the next byte gives us the fill byte */
            jPattern = *pjSource++;
            while (jLength--)
            {
                temp = UncompressedBits + (((height - y) * Delta) + x);
                x++;
                *temp = c;
            }

        }


    }
}

BOOL
NTAPI
DecompressBitmap(
    _In_ SIZEL Size,
    _In_bytecount_(CompressedSize) PBYTE CompressedBits,
    _In_ ULONG CompressedSize,
    _Out_bytecap_(UncompressedSize) PBYTE UncompressedBits,
    _In_ ULONG UncompressedSize,
    _In_ LONG Delta,
    _In_ ULONG Format)
{
    INT x = 0;
    INT y = Size.cy - 1;
    INT c;
    INT length;
    INT width;
    INT height = Size.cy - 1;
    PBYTE begin = CompressedBits;
    PBYTE bits = CompressedBits;
    PBYTE CompressedBitsEnd = CompressedBits + CompressedSize;
    PBYTE temp;
    INT shift = 0;

    if ((Format == BMF_4RLE) || (Format == BMF_4BPP))
        shift = 1;
    else if ((Format != BMF_8RLE) && (Format != BMF_8BPP))
        return FALSE;

    width = ((Size.cx + shift) >> shift);

    /* Check the output size */
    if ((Size.cy * Delta) > UncompressedSize)
        return FALSE;

    _SEH2_TRY
    {

        do
        {

        }


        while (y >= 0)
        {
            /* Need at least 2 bytes */
            if (bits >= CompressedBitsEnd - 1)
                return FALSE;

            length = (*bits++) >> shift;
            if (length)
            {
                c = *bits++;
                while (length--)
                {
                    if (x >= width) break;
                    temp = UncompressedBits + (((height - y) * Delta) + x);
                    x++;
                    *temp = c;
                }
            }
            else
            {
                length = *bits++;
                switch (length)
                {
                case RLE_EOL:
                    x = 0;
                    y--;
                    break;

                case RLE_END:
                    return TRUE;

                case RLE_DELTA:

                    /* Need 2 bytes */
                    if (bits >= CompressedBitsEnd - 1)
                        return;
                    x += (*bits++) >> shift;
                    y -= (*bits++) >> shift;
                    break;

                default:
                    length = length >> shift;

                    /* Need length bytes */
                    if (bits > CompressedBitsEnd - length)
                        return FALSE;

                    while (length--)
                    {
                        c = *bits++;
                        if (x < width)
                        {
                            temp = UncompressedBits + (((height - y) * Delta) + x);
                            x++;
                            *temp = c;
                        }
                    }
                    if ((bits - begin) & 1)
                    {
                        bits++;
                    }
                }
            }
        }
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        DPRINT1("Decoding error\n");
        return FALSE;
    }
    _SEH2_END;

    return TRUE;
}
