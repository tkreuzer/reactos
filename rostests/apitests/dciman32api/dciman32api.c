#include "dciman32api.h"

HINSTANCE g_hInstance;

BOOL
IsFunctionPresent(LPWSTR lpszFunction)
{
    return TRUE;
}

int APIENTRY
WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR     lpCmdLine,
        int       nCmdShow)
{
    g_hInstance = hInstance;
    return TestMain(L"dciman32api", L"dciman32.dll");
}