// MinGW options:
//   g++ -O3 -Wall -c -o MetricsTest.o MetricsTest.cpp
//   g++ -Wl,-subsystem,windows -static-libstdc++ -static-libgcc -o MetricsTest.exe MetricsTest.o -lgdi32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "eng.h"

#define FIX LONG

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main()
{
    WNDCLASSEX wc;
    wc.cbSize         = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc    = WndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.hInstance      = GetModuleHandle(NULL);
    wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = "LineTestWndClass";
    wc.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
        return -1;

    HWND hMainWnd = CreateWindow("LineTestWndClass",
                                 "ReactOS Tests: LinesTest",
                                 WS_OVERLAPPEDWINDOW,
                                 10,
                                 10,
                                 640,
                                 480,
                                 (HWND)NULL,
                                 (HMENU)NULL,
                                 wc.hInstance,
                                 NULL);
    if (!hMainWnd)
        return -1;

    ShowWindow(hMainWnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

BOOL
APIENTRY
GreLineTo(
    _In_ HDC hdc,
    _In_ INT x,
    _In_ INT y);

VOID
MyDrawLine(
    HDC hdc,
    FIX x1,
    FIX y1,
    FIX x2,
    FIX y2,
    COLORREF cr,
    ULONG cStyles,
    PULONG pulStyles)
{
    SURFACE surface;
    EBRUSHOBJ ebo;

    SetWindowExtEx(hdc, 1, 1, NULL);
    SetViewportExtEx(hdc, 1, 1, NULL);

    surface.so.iType = STYPE_BITMAP;
    surface.flags = 0;
    surface.hdc = hdc;

    ebo.bo.iSolidColor = cr;
    ebo.bo.pvRbrush = NULL;
    ebo.bo.flColorType = 0;
    ebo.cStyles = cStyles;
    ebo.pulStyles = pulStyles;

    EngLineTo(&surface.so,
              NULL, // pco,
              &ebo.bo,
              x1,
              y1,
              x2,
              y2,
              NULL, // prclBounds,
              0); // mix

}


VOID
GdiDrawLine(
    HDC hdc,
    FIX x0,
    FIX y0,
    FIX x1,
    FIX y1,
    COLORREF cr,
    ULONG cStyles,
    PULONG pulStyles)
{
    LOGBRUSH lb = {0};
    HPEN hpen, hpenOld;

    // set GM_ADVANCED
    SetMapMode(hdc, MM_ISOTROPIC);
    SetWindowExtEx(hdc, 16, 16, NULL);
    SetViewportExtEx(hdc, 1, 1, NULL);

    if (cStyles)
    {
        lb.lbStyle = BS_SOLID;
        lb.lbColor = cr;
        hpen = ExtCreatePen(PS_USERSTYLE,
                            1, &lb, cStyles, pulStyles);
    }
    else
    {
        hpen = CreatePen(PS_SOLID, 0, cr);
    }

    hpenOld = (HPEN)SelectObject(hdc, hpen);
    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x1, y1);
    SelectObject(hdc, (HGDIOBJ)hpenOld);

    DeleteObject(hpen);
}

typedef struct
{
    POINT ptA;
    POINT ptB;
    ULONG cStyles;
    ULONG aulStyles[16];
} LINESPEC, *PLINESPEC;

VOID
GdiDrawLine2(HDC hdc, LINESPEC *pls)
{
    GdiDrawLine(hdc,
                pls->ptA.x,
                pls->ptA.y,
                pls->ptB.x,
                pls->ptB.y,
                0x00FF00,
                pls->cStyles,
                pls->aulStyles);
#if 1
    MyDrawLine(hdc,
                pls->ptA.x,
                pls->ptA.y,
                pls->ptB.x,
                pls->ptB.y,
                0x000000,
                pls->cStyles,
                pls->aulStyles);
#endif
}

VOID
LinesTest(
    HDC hdc)
{
    static LINESPEC aLines[] =
    {
        {{0,0},{3200,2000},0,{0}},
        {{0,0},{3200,2000},2,{10,10}},
        {{0,0},{3275,1234},6,{10,2,4,6,1,9}},
        {{0,0},{2000,3200},0,{0}},
        {{3200,0},{1000,200},0,{0}},
        {{1200,0},{1000,800},0,{0}},
    };

    GdiDrawLine2(hdc, &aLines[5]);
}

LRESULT
CALLBACK
WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            LinesTest(hdc);

            EndPaint(hwnd, &ps);
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        default:
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}
