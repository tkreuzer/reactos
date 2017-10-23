/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPL - See COPYING in the top level directory
 * PURPOSE:         Test for NtGdiGetDCObject
 * PROGRAMMERS:
 */

#include <win32nt.h>

/*
#define GDI_OBJECT_TYPE_DC            0x00010000
#define GDI_OBJECT_TYPE_DD_SURFACE    0x00030000
#define GDI_OBJECT_TYPE_REGION        0x00040000
#define GDI_OBJECT_TYPE_BITMAP        0x00050000
#define GDI_OBJECT_TYPE_CLIOBJ        0x00060000
#define GDI_OBJECT_TYPE_PATH          0x00070000
#define GDI_OBJECT_TYPE_PALETTE       0x00080000
#define GDI_OBJECT_TYPE_COLORSPACE    0x00090000
#define GDI_OBJECT_TYPE_FONT          0x000a0000
#define GDI_OBJECT_TYPE_BRUSH         0x00100000
#define GDI_OBJECT_TYPE_DD_VIDEOPORT  0x00120000
#define GDI_OBJECT_TYPE_DD_MOTIONCOMP 0x00140000
#define GDI_OBJECT_TYPE_ENUMFONT      0x00160000
#define GDI_OBJECT_TYPE_DRIVEROBJ     0x001C0000
#define GDI_OBJECT_TYPE_DIRECTDRAW    0x00200000
#define GDI_OBJECT_TYPE_EMF           0x00210000
#define GDI_OBJECT_TYPE_METAFILE      0x00260000
#define GDI_OBJECT_TYPE_ENHMETAFILE   0x00460000
#define GDI_OBJECT_TYPE_PEN           0x00300000
#define GDI_OBJECT_TYPE_EXTPEN        0x00500000
#define GDI_OBJECT_TYPE_METADC        0x00660000
#define GDI_OBJECT_TYPE_DD_PALETTE    0x00630000
#define GDI_OBJECT_TYPE_DD_CLIPPER    0x00640000
*/

#define ok_objtype(hobj, type) \
    ok(GetObjectType(hobj) == (type), \
       "Wrong object type for " #hobj " (0x%p): expected " #type " got %u\n", \
       hobj, (unsigned)GetObjectType(hobj))

START_TEST(NtGdiGetDCObject)
{
	HGDIOBJ hobj;
    HDC hdc;
    HPEN hpen1, hpen2;
    HBITMAP hbmp;
    HRGN hrgn;

    hdc = CreateCompatibleDC(NULL);
    ok(hdc != NULL, "Failed to create a DC");
    if (hdc == NULL)
    {
        return;
    }

    SetLastError(0xdeadbeef);

	hobj = NtGdiGetDCObject(NULL, 0);
    ok_hdl(hobj, NULL);

	hobj = NtGdiGetDCObject(NULL, -12345);
    ok_hdl(hobj, NULL);

	hobj = NtGdiGetDCObject(hdc, -12345);
    ok_hdl(hobj, NULL);
    ok_err(0xdeadbeef);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_REGION);
    ok_hdl(hobj, NULL);

    hrgn = CreateRectRgn(0, 0, 10, 10);
    ok(hrgn != NULL, "CreateRectRgn() failed\n");
    ok(SelectObject(hdc, hrgn) != NULL, "SelectObject() failed\n");;
	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_REGION);
    ok_hdl(hobj, NULL);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_BITMAP);
    ok(hobj != NULL, "NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_BITMAP) failed\n");
    ok_objtype(hobj, OBJ_BITMAP);
    ok_hdl(hobj, GetStockObject(DEFAULT_BITMAP));

    hbmp = CreateBitmap(1, 1, 1, 1, NULL);
    SelectObject(hdc, hbmp);
	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_BITMAP);
    ok_hdl(hobj, hbmp);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_CLIOBJ);
    ok_hdl(hobj, NULL);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_PATH);
    ok_hdl(hobj, NULL);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_PALETTE);
    ok(hobj != NULL, "NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_PALETTE) failed\n");
    ok_objtype(hobj, OBJ_PAL);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_COLORSPACE);
    ok_hdl(hobj, NULL);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_FONT);
    ok(hobj != NULL, "NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_FONT) failed\n");
    ok_objtype(hobj, OBJ_FONT);

	hobj = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_BRUSH);
    ok(hobj != NULL, "NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_BRUSH) failed\n");
    ok_objtype(hobj, OBJ_BRUSH);

	hpen1 = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_PEN);
    ok(hpen1 != NULL, "NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_PEN) failed\n");
	hpen2 = NtGdiGetDCObject(hdc, GDI_OBJECT_TYPE_EXTPEN);
    ok_hdl(hpen2, hpen1);
    ok_objtype(hpen1, OBJ_PEN);


    ok_err(0xdeadbeef);

}
