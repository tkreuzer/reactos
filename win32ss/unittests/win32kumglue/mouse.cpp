
#include <win32k.h>


__drv_preferredFunction("(see documentation)", "Obsolete, always returns false. ")
BOOL
APIENTRY
EngSetPointerTag(
    _In_ HDEV hdev,
    _In_opt_ SURFOBJ *psoMask,
    _In_opt_ SURFOBJ *psoColor,
    _Reserved_ XLATEOBJ *pxlo,
    _In_ FLONG fl)
{
    __debugbreak();
    return FALSE;
}

_Requires_lock_held_(*ppdev->hsemDevLock)
BOOL
NTAPI
MouseSafetyOnDrawStart(
    _Inout_ PPDEVOBJ ppdev,
    _In_ LONG HazardX1,
    _In_ LONG HazardY1,
    _In_ LONG HazardX2,
    _In_ LONG HazardY2)
{
    __debugbreak();
    return TRUE;
}

_Requires_lock_held_(*ppdev->hsemDevLock)
BOOL
NTAPI
MouseSafetyOnDrawEnd(
    _Inout_ PPDEVOBJ ppdev)
{
    __debugbreak();
    return TRUE;
}

VOID
NTAPI
IntHideMousePointer(
    _Inout_ PDEVOBJ *ppdev,
    _Inout_ SURFOBJ *psoDest)
{
    __debugbreak();
}

VOID
NTAPI
IntShowMousePointer(
    _Inout_ PDEVOBJ *ppdev,
    _Inout_ SURFOBJ *psoDest)
{
    __debugbreak();
}

ULONG
APIENTRY
EngSetPointerShape(
    _In_ SURFOBJ *pso,
    _In_opt_ SURFOBJ *psoMask,
    _In_opt_ SURFOBJ *psoColor,
    _In_opt_ XLATEOBJ *pxlo,
    _In_ LONG xHot,
    _In_ LONG yHot,
    _In_ LONG x,
    _In_ LONG y,
    _In_ RECTL *prcl,
    _In_ FLONG fl)
{
    __debugbreak();
    return SPS_ACCEPT_NOEXCLUDE;
}

VOID
APIENTRY
EngMovePointer(
    _In_ SURFOBJ *pso,
    _In_ LONG x,
    _In_ LONG y,
    _In_ RECTL *prcl)
{
    __debugbreak();
}

ULONG
NTAPI
IntEngSetPointerShape(
    _In_ SURFOBJ *pso,
    _In_opt_ SURFOBJ *psoMask,
    _In_opt_ SURFOBJ *psoColor,
    _In_opt_ XLATEOBJ *pxlo,
    _In_ LONG xHot,
    _In_ LONG yHot,
    _In_ LONG x,
    _In_ LONG y,
    _In_ RECTL *prcl,
    _In_ FLONG fl)
{
    __debugbreak();
    return SPS_ACCEPT_NOEXCLUDE;
}

ULONG
NTAPI
GreSetPointerShape(
    _In_ HDC hdc,
    _In_opt_ HBITMAP hbmMask,
    _In_opt_ HBITMAP hbmColor,
    _In_ LONG xHot,
    _In_ LONG yHot,
    _In_ LONG x,
    _In_ LONG y,
    _In_ FLONG fl)
{
    __debugbreak();
    return SPS_ACCEPT_NOEXCLUDE;
}

VOID
NTAPI
GreMovePointer(
    _In_ HDC hdc,
    _In_ LONG x,
    _In_ LONG y)
{
    __debugbreak();

}


/* EOF */

