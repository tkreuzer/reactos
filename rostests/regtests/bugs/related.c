/*
 * PROJECT:         ReactOS CRT regression tests
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            rostests/regtests/crt/time.c
 * PURPOSE:         Test for 
 * PROGRAMMERS:     Timo Kreuzer
 */

#include <stdio.h>
#include <wine/test.h>
#include <windows.h>

#define COUNT 26

void Test_related()
{
    const char text[COUNT] = "abcdefghijklmnopqrstuvmxyz";
    WORD agi[COUNT];
    INT iWidth, aiWidthIndex[COUNT];
    ABC aabc1[COUNT], aabc2[COUNT];
    DWORD result;
    HDC hdc;
    INT i;

    /* Create a DC */
    hdc = CreateCompatibleDC(NULL);

    SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));

    /* Convert the charcaters into glyph indices */
    result = GetGlyphIndicesA(hdc, text, COUNT, agi, 0);
    ok(result != 0, "result=%ld, GetLastError()=%ld\n", result, GetLastError());

    /* Get ABC widths from range of characters */
    result = GetCharABCWidthsA(hdc, 'a', 'z', aabc1);
    ok(result != 0, "result=%ld, GetLastError()=%ld\n", result, GetLastError());

    /* Get ABC widths from range of glyph indices. */
    result = GetCharABCWidthsI(hdc, 0, COUNT, agi, aabc2);
    ok(result != 0, "result=%ld, GetLastError()=%ld\n", result, GetLastError());

    /* Get full widths from range of glyph indices. */
    result = GetCharWidthI(hdc, 0, COUNT, agi, aiWidthIndex);
    ok(result != 0, "result=%ld, GetLastError()=%ld\n", result, GetLastError());

    /* Loop all characters */
    for (i = 0; i < COUNT; i++)
    {
        /* Check if we got identical spacing values */
        ok(aabc1[i].abcA == aabc2[i].abcA, "wrong A-spacing, i=%d, char:%d, index:%d\n", i, aabc1[i].abcA, aabc2[i].abcA);
        ok(aabc1[i].abcB == aabc2[i].abcB, "wrong B-spacing, i=%d, char:%d, index:%d\n", i, aabc1[i].abcB, aabc2[i].abcB);
        ok(aabc1[i].abcC == aabc2[i].abcC, "wrong A-spacing, i=%d, char:%d, index:%d\n", i, aabc1[i].abcC, aabc2[i].abcC);

        /* Add these together */
        iWidth = aabc1[i].abcA + aabc1[i].abcB + aabc1[i].abcC;
        ok(iWidth == aiWidthIndex[i], "wrong spacing, i=%d, char:%d, index:%d\n", i, iWidth, aiWidthIndex[i]);

        printf("i=%d, char=%d, index=%d, spacing=%d\n", i, text[i], agi[i], iWidth);
    }

    /* Cleanup */
    DeleteDC(hdc);
}

START_TEST(bug3481)
{
    Test_related();
}

