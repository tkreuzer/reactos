/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPL - See COPYING in the top level directory
 * PURPOSE:         Test for CreateDC
 * PROGRAMMERS:     Timo Kreuzer
 */

#include <stdio.h>
#include <wine/test.h>
#include <windows.h>

#define DEFAULT_BITMAP 21

void Test_CreateDC()
{
    HDC hdc1, hdc2;
__debugbreak();
    hdc1 = CreateDCW(NULL, NULL, NULL, NULL);
    ok(hdc1 == NULL, "CreateDCW() should fail\n");

    hdc1 = CreateDCW(L"DISPLAY", NULL, NULL, NULL);
    ok(hdc1 != NULL, "CreateDCW() failed\n");
    ok(DeleteDC(hdc1) == TRUE, "Failed to delete DC\n");

    hdc1 = CreateDCW(L"DISPLAY", L"FOOBAR", NULL, NULL);
    ok(hdc1 != NULL, "CreateDCW() failed\n");
    ok(DeleteDC(hdc1) == TRUE, "Failed to delete DC\n");

#if 0
    hdc1 = CreateDCW(L"\\\\.\\DISPLAY", NULL, NULL, NULL);
    ok(hdc1 != NULL, "CreateDCW() failed\n");
    ok(DeleteDC(hdc1) == TRUE, "Failed to delete DC\n");

    hdc1 = CreateDCW(NULL, L"\\\\.\\DISPLAY", NULL, NULL);
    ok(hdc1 != NULL, "CreateDCW() failed\n");
    ok(DeleteDC(hdc1) == TRUE, "Failed to delete DC\n");
#endif
    hdc1 = CreateDCW(L"DISPLAY", NULL, NULL, NULL);
    ok(hdc1 != NULL, "CreateDCW() failed\n");
    ok(ReleaseDC(NULL, hdc1) == TRUE, "ReleaseDC() should succeed\n");
    ok(DeleteDC(hdc1) == FALSE, "DeleteDC() should fail\n");

    hdc2 = CreateDCW(L"DISPLAY", NULL, NULL, NULL);
    ok(hdc2 != NULL, "CreateDCW() failed\n");
    ok(hdc1 != hdc2, "HDCs should not be identical\n");

    hdc1 = CreateDCW(L"DISPLAY", NULL, NULL, NULL);
    ok(SelectObject(hdc1, GetStockObject(BLACK_PEN)) != 0, "SelectObject(BLACK_PEN) should succeed\n");
    ok(SelectObject(hdc1, GetStockObject(DEFAULT_BITMAP)) == 0, "SelectObject(DEFAULT_BITMAP) should fail\n");

}

START_TEST(CreateDC)
{
    Test_CreateDC();
}

