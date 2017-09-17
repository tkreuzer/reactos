// MinGW options:
//   g++ -O3 -Wall -c -o MetricsTest.o MetricsTest.cpp
//   g++ -Wl,-subsystem,windows -static-libstdc++ -static-libgcc -o MetricsTest.exe MetricsTest.o -lgdi32

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#include <windows.h>

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
    wc.lpszClassName  = "abcdefgh";
    wc.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
        return -1;

    HWND hMainWnd = CreateWindow(
		"abcdefgh", "ReactOS Tests: MetricsTest", WS_OVERLAPPEDWINDOW,
        10, 10, 640, 480, (HWND)NULL, (HMENU)NULL,
        wc.hInstance, NULL
    );

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

void SetScale(HDC hDC, int scale)
{
    XFORM xf;
    xf.eM11 = 1.0f;
    xf.eM22 = 1.0f;
    xf.eM12 = 0.0f;
    xf.eM21 = 0.0f;
    xf.eDx = 0.0f;
    xf.eDy = 0.0f;
	if (scale != 1)
	{
		xf.eM11 *= scale;
		xf.eM22 *= scale;
	}
    SetGraphicsMode(hDC, GM_ADVANCED);
	SetWorldTransform(hDC, &xf);
	if (scale == 1)
	{
		SetGraphicsMode(hDC, GM_COMPATIBLE);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
__debugbreak();
            const int hello_string_len = 15;
            const wchar_t* hello_string = L"Hello, ReactOS!";

            HFONT hFont = CreateFontA(24, 0, 0, 0, FW_DONTCARE,
                    FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                    CLIP_DEFAULT_PRECIS, 0, DEFAULT_PITCH, "Tahoma");
			HBRUSH hBrush = CreateSolidBrush(0x00FFF8F0);
			HPEN hPen = CreatePen(PS_SOLID, 1, 0x00FF7060);
			SelectObject(hDC, hPen);
			SelectObject(hDC, hBrush);
            SelectObject(hDC, hFont);

			for (int scale = 1; scale < 4; scale++)
			{
				SetScale(hDC, scale);
				GLYPHMETRICS metrics[hello_string_len];
				for (int i = 0; i < hello_string_len; i++)
				{
					MAT2 matrix = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
					if (GetGlyphOutlineW(hDC, hello_string[i], GGO_METRICS,
							&metrics[i], 0, NULL, &matrix) == GDI_ERROR)
					{
						MessageBoxA(0, "GetGlyphOutlineW failed", "Error", MB_OK | MB_ICONERROR);
						ExitProcess(-1);
					}
				}

				SetScale(hDC, 1);

				int startX = 20;
				int startY = 20 + 30 * scale * scale;

				int curX = startX;
				int curY = startY;
				for (int i = 0; i < hello_string_len; i++)
				{
					int left = curX + metrics[i].gmptGlyphOrigin.x;
					int top = curY - metrics[i].gmptGlyphOrigin.y;
					int right = left + metrics[i].gmBlackBoxX;
					int bottom = top + metrics[i].gmBlackBoxY;
					Rectangle(hDC, left, top, right, bottom);
					curX += metrics[i].gmCellIncX;
				}

				SetScale(hDC, scale);

				SetBkMode(hDC, TRANSPARENT);
				ExtTextOutW(hDC, startX / scale, startY / scale,
					0, NULL, hello_string, hello_string_len, NULL);
			}

			DeleteObject(hFont);
			DeleteObject(hBrush);
			DeleteObject(hPen);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        default:
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}
