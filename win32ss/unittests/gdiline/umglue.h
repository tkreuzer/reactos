

typedef struct _DC_INFO
{
    HBITMAP hbmp;
    HBRUSH hbr;
    HPEN hpen;
    HFONT hfont;
    HPALETTE hpal;
} DC_INFO, *PDC_INFO;

BOOL
GetDcInfo(
    _In_ HDC hdc,
    _Out_ PDC_INFO pdcinfo);

typedef struct _SURFACE_INFO
{
    ULONG iFormat;
    PVOID pvBits;
    PVOID pvScan0;
} SURFACE_INFO, *PSURFACE_INFO;

BOOL
GetSurfaceInfo(
    _In_ HBITMAP hsurf,
    _Out_ PSURFACE_INFO psurfinfo);

