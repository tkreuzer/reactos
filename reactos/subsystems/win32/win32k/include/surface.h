#pragma once

#include "win32.h"
#include "gdiobj.h"

#define PDEV_SURFACE              0x80000000

/* GDI surface object */
typedef struct _SURFACE
{
  BASEOBJECT  BaseObject;

  SURFOBJ     SurfObj;
  FLONG	      flHooks;
  FLONG       flFlags;
  struct _PALETTE  *ppal;

  union
  {
    HANDLE    hSecureUMPD;  // if UMPD_SURFACE set
    HANDLE    hMirrorParent;// if MIRROR_SURFACE set
    HANDLE    hDDSurface;   // if DIRECTDRAW_SURFACE set
  };

  SIZEL       dimension;    /* For SetBitmapDimension(), do NOT use
                               to get width/height of bitmap, use
                               bitmap.bmWidth/bitmap.bmHeight for
                               that */
  
  HDC         hDC; // Doc in "Undocumented Windows", page 546, seems to be supported with XP.
  ULONG       cRef;         // 0x064
  HPALETTE    hpalHint;

  /* For device-independent bitmaps: */
  HANDLE      hDIBSection;
  HANDLE      hSecure;
  DWORD       dwOffset;

  /* reactos specific */
  PFAST_MUTEX BitsLock;     /* You need to hold this lock before you touch
                               the actual bits in the bitmap */
  HPALETTE hDIBPalette;
  DWORD dsBitfields[3]; // hack, should probably use palette instead
  DWORD biClrUsed;
  DWORD biClrImportant;
} SURFACE, *PSURFACE;

#define BITMAPOBJ_IS_APIBITMAP		0x1

/*  Internal interface  */

#define SURFACE_AllocSurface()    ((PSURFACE) GDIOBJ_AllocObj(GDIObjType_SURF_TYPE))
#define SURFACE_AllocSurfaceWithHandle()    ((PSURFACE) GDIOBJ_AllocObjWithHandle(GDI_OBJECT_TYPE_BITMAP))
#define SURFACE_FreeSurface(pBMObj) GDIOBJ_FreeObj((POBJ) pBMObj, GDIObjType_SURF_TYPE)
#define SURFACE_FreeSurfaceByHandle(hBMObj) GDIOBJ_FreeObjByHandle((HGDIOBJ) hBMObj, GDI_OBJECT_TYPE_BITMAP)

/* NOTE: Use shared locks! */
#define  SURFACE_LockSurface(hBMObj) \
  ((PSURFACE) GDIOBJ_LockObj ((HGDIOBJ) hBMObj, GDI_OBJECT_TYPE_BITMAP))
#define  SURFACE_ShareLockSurface(hBMObj) \
  ((PSURFACE) GDIOBJ_ShareLockObj ((HGDIOBJ) hBMObj, GDI_OBJECT_TYPE_BITMAP))
#define  SURFACE_UnlockSurface(pBMObj)  \
  GDIOBJ_UnlockObjByPtr ((POBJ)pBMObj)
#define  SURFACE_ShareUnlockSurface(pBMObj)  \
  GDIOBJ_ShareUnlockObjByPtr ((POBJ)pBMObj)

#define SURFACE_LockBitmapBits(pBMObj) ExEnterCriticalRegionAndAcquireFastMutexUnsafe((pBMObj)->BitsLock)
#define SURFACE_UnlockBitmapBits(pBMObj) ExReleaseFastMutexUnsafeAndLeaveCriticalRegion((pBMObj)->BitsLock)

BOOL INTERNAL_CALL SURFACE_Cleanup(PVOID ObjectBody);
BOOL INTERNAL_CALL SURFACE_InitBitsLock(SURFACE *pBMObj);
void INTERNAL_CALL SURFACE_CleanupBitsLock(SURFACE *pBMObj);

#define GDIDEV(SurfObj) ((PDEVOBJ *)((SurfObj)->hdev))
#define GDIDEVFUNCS(SurfObj) ((PDEVOBJ *)((SurfObj)->hdev))->DriverFunctions

INT   FASTCALL BitsPerFormat (ULONG Format);
ULONG FASTCALL BitmapFormat (WORD Bits, DWORD Compression);