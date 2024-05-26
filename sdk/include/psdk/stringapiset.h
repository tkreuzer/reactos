
#pragma once

#include <winnls.h>

WINBASEAPI
int
WINAPI
CompareStringEx(
    _In_opt_ LPCWSTR lpLocaleName,
    _In_ DWORD dwCmpFlags,
    _In_NLS_string_(cchCount1) LPCWCH lpString1,
    _In_ int cchCount1,
    _In_NLS_string_(cchCount2) LPCWCH lpString2,
    _In_ int cchCount2,
    _Reserved_ LPNLSVERSIONINFO lpVersionInformation,
    _Reserved_ LPVOID lpReserved,
    _Reserved_ LPARAM lParam
    );

