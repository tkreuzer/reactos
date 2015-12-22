
#include <win32k.h>
#include "dc.hpp"
#include "surface.hpp"

extern "C" {

PGDI_HANDLE_TABLE GdiHandleTable;

POBJ
NTAPI
GDIOBJ_AllocateObject(UCHAR objt, ULONG cjSize, FLONG fl)
{
    __debugbreak();
    return NULL;
}

POBJ NTAPI
GDIOBJ_AllocObjWithHandle(ULONG ObjectType, ULONG cjSize)
{
    __debugbreak();
    return NULL;
}

HGDIOBJ
NTAPI
GDIOBJ_hInsertObject(POBJ pobj, ULONG ulOwner)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
GDIOBJ_vFreeObject(POBJ pobj)
{
    __debugbreak();

}

PVOID
NTAPI
GDIOBJ_LockObject(
    HGDIOBJ hobj,
    UCHAR objt)
{
    //ULONG ulObjectType;


    //ulObjectType = GDI_HANDLE_GET_TYPE(hobj);

    switch (objt)
    {
    case GDIObjType_DC_TYPE:
        return GetDc((HDC)hobj);

    default:
        __debugbreak();
    }

    return NULL;
}

BOOL
NTAPI
GDIOBJ_bLockMultipleObjects(ULONG ulCount, HGDIOBJ *ahObj, PGDIOBJ * apObj, UCHAR objt)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
GDIOBJ_vUnlockObject(POBJ pobj)
{
    switch (GDI_HANDLE_GET_TYPE(pobj->hHmgr))
    {
        case GDILoObjType_LO_DC_TYPE:
            DC_vDeleteDc((PDC)pobj);
            break;

    }
}

POBJ
NTAPI
GDIOBJ_ReferenceObjectByHandle(HGDIOBJ hobj, UCHAR objt)
{
    switch (objt)
    {
    case GDIObjType_SURF_TYPE:
        return (POBJ)GetSurface((HSURF)hobj);

    default:
        __debugbreak();
    }

    return NULL;
}

VOID
NTAPI
GDIOBJ_vReferenceObjectByPointer(POBJ pobj)
{
    __debugbreak();
}

PVOID
NTAPI
GDIOBJ_ShareLockObj(HGDIOBJ hobj, DWORD ExpectedType)
{
    switch (ExpectedType)
    {
    case GDILoObjType_LO_BITMAP_TYPE:
        return GetSurface((HSURF)hobj);

    default:
        __debugbreak();
    }

    return NULL;
}

VOID
NTAPI
GDIOBJ_vDeleteObject(POBJ pobj)
{
    __debugbreak();
}

VOID
NTAPI
GDIOBJ_vDereferenceObject(POBJ pobj)
{
    __debugbreak();
}

VOID
NTAPI
GDIOBJ_vSetObjectAttr(POBJ pobj, PVOID pvObjAttr)
{
    __debugbreak();
}

BOOL
NTAPI
GDIOBJ_ConvertToStockObj(HGDIOBJ *hObj)
{
    __debugbreak();
    return FALSE;
}

BOOL
NTAPI
GreSetObjectOwner(HGDIOBJ hobj, ULONG ulOwner)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
GDIOBJ_vSetObjectOwner(POBJ pobj, ULONG ulOwner)
{
    __debugbreak();
}

BOOL
NTAPI
GreIsHandleValid(HGDIOBJ hobj)
{
    __debugbreak();
    return FALSE;
}

BOOL
NTAPI
GreDeleteObject(HGDIOBJ hobj)
{
    __debugbreak();
    return FALSE;
}

ULONG
NTAPI
GreGetObjectOwner(HGDIOBJ hobj)
{
    __debugbreak();
    return 0;
}

INT
NTAPI
GreGetObject(HGDIOBJ hobj, INT cbCount, PVOID pvBuffer)
{
    __debugbreak();
    return 0;
}

} // extern "C"
