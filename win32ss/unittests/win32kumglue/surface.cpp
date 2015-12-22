
#include <win32k.h>
#include "pdev.hpp"

typedef struct _SURFACE_INFO
{
    ULONG iFormat;
    PVOID pvBits;
    PVOID pvScan0;
} SURFACE_INFO, *PSURFACE_INFO;

BOOL
GetSurfaceInfo(
    _In_ HBITMAP hsurf,
    _Out_ PSURFACE_INFO psurfinfo)
{
    return FALSE;
}

ULONG
GetBitmapFormat(
    PDIBSECTION pds)
{
    return BMF_32BPP;
}

PSURFACE
GetSurface(
    _In_ HSURF hsurf)
{
    SURFACE_INFO surfinfo;
    DIBSECTION ds;
    PSURFACE ps;

    if (!GetSurfaceInfo((HBITMAP)hsurf, &surfinfo))
    {
        return NULL;
    }

    GetObject((HGDIOBJ)hsurf, sizeof(ds), &ds);

    ps = (PSURFACE)EngAllocMem(FL_ZERO_MEMORY, sizeof(SURFACE), 'US');
    if (ps == NULL)
    {
        return NULL;
    }

    ps->BaseObject.hHmgr = hsurf;

    ps->SurfObj.dhsurf = NULL;
    ps->SurfObj.hsurf = hsurf;
    ps->SurfObj.dhpdev = NULL;
    ps->SurfObj.hdev = (HDEV)gppdevPrimary;
    ps->SurfObj.sizlBitmap.cx = ds.dsBm.bmWidth;
    ps->SurfObj.sizlBitmap.cy = ds.dsBm.bmHeight;
    ps->SurfObj.cjBits = ds.dsBmih.biSizeImage;
    ps->SurfObj.pvBits = ds.dsBm.bmBits;
    ps->SurfObj.pvScan0 = ds.dsBm.bmBits;;
    ps->SurfObj.lDelta = ds.dsBm.bmWidthBytes;
    ps->SurfObj.iUniq = 0;
    ps->SurfObj.iBitmapFormat = GetBitmapFormat(&ds);
    ps->SurfObj.iType = STYPE_BITMAP;
    ps->SurfObj.fjBitmap = 0;
    ps->flags = 0;
    //ps->ppal = CreateDibPalette(%ds.dsBmih);

    ps->hSecureUMPD = NULL;
    ps->sizlDim = ps->SurfObj.sizlBitmap;
    ps->hdc = NULL;
    ps->cRef = 1;
    ps->hpalHint = NULL;

    /* For device-independent bitmaps: */
    ps->hDIBSection = ds.dshSection;
    ps->hSecure = (HANDLE)-1;
    ps->dwOffset = ds.dsOffset;
    ps->biClrImportant = ds.dsBmih.biClrImportant;

    return NULL;
}

