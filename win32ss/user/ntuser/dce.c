/*
 * PROJECT:         ReactOS Win32k subsystem
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            subsystems/win32/win32k/ntuser/dce.c
 * PURPOSE:         Window DC management
 * COPYRIGHT:       Copyright 2007 ReactOS Team
 */

#include <win32k.h>
DBG_DEFAULT_CHANNEL(UserDce);

LIST_ENTRY liUsedDceListHead;
LIST_ENTRY liCachedDceListHead;

INIT_FUNCTION
NTSTATUS
NTAPI
InitDCEImpl(VOID)
{
    InitializeListHead(&liUsedDceListHead);
    InitializeListHead(&liCachedDceListHead);
    return STATUS_SUCCESS;
}

PDCE
FASTCALL
DceAllocDCE(
    _In_opt_ PWND pwnd,
    DCE_TYPE dceType)
{
    __debugbreak();
    return 0;
}

VOID
FASTCALL
DceFreeThreadDCE(
    _Inout_ PTHREADINFO pti)
{
    __debugbreak();
}

VOID
FASTCALL
DceFreeClassDCE(
    _In_ HDC hdc)
{
    __debugbreak();
}

VOID
FASTCALL
DceFreeWindowDCE(
    PWND pwnd)
{
    __debugbreak();
}

VOID
FASTCALL
DceResetActiveDCEs(
    PWND pwnd)
{
    __debugbreak();
}

HWND
FASTCALL
UserGethWnd(
    HDC hdc,
    PWNDOBJ *pwndo)
{
    __debugbreak();
    return 0;
}

HDC
FASTCALL
UserGetDCEx(
    _In_opt_ PWND pwnd,
    _In_ HANDLE prgnClip,
    ULONG fl)
{
    __debugbreak();
    return 0;
}

HDC
FASTCALL
UserGetWindowDC(
    _In_ PWND pwnd)
{
    return UserGetDCEx(pwnd, 0, DCX_USESTYLE | DCX_WINDOW);
}

INT
FASTCALL
UserReleaseDC(
    _Inout_ PWND pwnd,
    _In_ HDC hdc,
    _In_ BOOL bEndPaint)
{
    __debugbreak();
    return -1;
}


HWND
FASTCALL
IntWindowFromDC(
    _In_ HDC hdc)
{
    __debugbreak();
    return 0;
}

HDC
APIENTRY
NtUserGetDCEx(
    _In_opt_ HWND hWnd OPTIONAL,
    _In_ HANDLE hrgnClip,
    _In_ ULONG flags)
{
    __debugbreak();
    return 0;
}

HDC
APIENTRY
NtUserGetDC(
    _In_ HWND hwnd)
{
    ULONG flags;

    flags = (hwnd == NULL) ? DCX_CACHE | DCX_WINDOW : DCX_USESTYLE;
    return NtUserGetDCEx(hwnd, NULL, flags);
}

HDC
APIENTRY
NtUserGetWindowDC(
    HWND hwnd)
{
    __debugbreak();
    return 0;
}



/*!
 * Select logical palette into device context.
 * \param	hDC 				handle to the device context
 * \param	hpal				handle to the palette
 * \param	ForceBackground 	If this value is FALSE the logical palette will be copied to the device palette only when the applicatioon
 * 								is in the foreground. If this value is TRUE then map the colors in the logical palette to the device
 * 								palette colors in the best way.
 * \return	old palette
 *
 * \todo	implement ForceBackground == TRUE
*/
HPALETTE
APIENTRY
NtUserSelectPalette(HDC  hDC,
              HPALETTE  hpal,
       BOOL  ForceBackground)
{
    HPALETTE oldPal;
    UserEnterExclusive();
    // Implement window checks
    oldPal = GdiSelectPalette( hDC, hpal, ForceBackground);
    UserLeave();
    return oldPal;
}
