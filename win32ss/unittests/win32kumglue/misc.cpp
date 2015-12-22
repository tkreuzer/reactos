
#include <win32k.h>

int _SEH2_Volatile0 = 0;
int _SEH2_VolatileExceptionCode = 0xC0000005;

extern "C" {

XCLIPOBJ gxcoTrivial =
{
    /* CLIPOBJ */
    {
        {
            0, /* iUniq */
            {LONG_MIN, LONG_MIN, LONG_MAX, LONG_MAX}, /* rclBounds */
            DC_TRIVIAL,    /* idCOmplexity */
            FC_RECT,       /* iFComplexity */
            TC_RECTANGLES, /* iMode */
            0              /* fjOptions */
        },
    },
    0, 0, 0
};

SHORT gusLanguageID;
struct _SERVERINFO *gpsi;

NTSTATUS
NTAPI
DriverEntry(
    PDRIVER_OBJECT DriverObject,
    PUNICODE_STRING RegistryPath)
{
    return STATUS_SUCCESS;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
_MmCopyFromCaller(
    _Out_writes_bytes_all_(Bytes) PVOID Target,
    _In_reads_bytes_(Bytes) PVOID Source,
    _In_ UINT Bytes)
{
    memcpy(Target, Source, Bytes);
    return STATUS_SUCCESS;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
_MmCopyToCaller(
    _Out_writes_bytes_all_(Bytes) PVOID Target,
    _In_reads_bytes_(Bytes) PVOID Source,
    _In_ UINT Bytes)
{
    memcpy(Target, Source, Bytes);
    return STATUS_SUCCESS;
}

BOOL
APIENTRY
IntEngMaskBlt(
    _Inout_ SURFOBJ *psoDest,
    _In_ SURFOBJ *psoMask,
    _In_ CLIPOBJ *pco,
    _In_ XLATEOBJ *pxloDest,
    _In_ XLATEOBJ *pxloSource,
    _In_ RECTL *prclDest,
    _In_ POINTL *pptlMask,
    _In_ BRUSHOBJ *pbo,
    _In_ POINTL *pptlBrushOrg)
{
    __debugbreak();
    return FALSE;
}

INT
FASTCALL
UserReleaseDC(struct _WND *Window, HDC hdc, BOOL EndPaint)
{
    __debugbreak();
    return 0;
}

VOID FASTCALL UserReferenceObject(PVOID obj)
{
    __debugbreak();
}

BOOL FASTCALL UserDereferenceObject(PVOID obj)
{
    return FALSE;
}

VOID FASTCALL UserEnterExclusive(VOID)
{
    __debugbreak();
}

VOID FASTCALL UserLeave(VOID)
{
}

BOOL FASTCALL UserIsEntered(VOID)
{
    __debugbreak();
    return FALSE;
}

HWND FASTCALL IntWindowFromDC(HDC hDc)
{
    __debugbreak();
    return NULL;
}

struct _WND* FASTCALL UserGetWindowObject(HWND hWnd)
{
    __debugbreak();
    return NULL;
}

struct _WND*
FASTCALL
UserGetDesktopWindow(VOID)
{
    __debugbreak();
    return (struct _WND*)GetDesktopWindow();
}

HDC FASTCALL UserGetWindowDC(struct _WND* Wnd)
{
    __debugbreak();
    return GetDC((HWND)Wnd);
}

HDC
FASTCALL
IntGetScreenDC(VOID)
{
    __debugbreak();
    return GetDC(NULL);
}

BOOL FASTCALL co_UserRedrawWindow(struct _WND *Wnd, const RECTL* UpdateRect, PREGION UpdateRgn, ULONG Flags)
{
    __debugbreak();
    return FALSE;
}

} // extern "C"
