
#include "pdev.hpp"

PDEVOBJ gpdevPrimary;

extern "C" {

PPDEVOBJ gppdevPrimary = &gpdevPrimary;

PPDEVOBJ
NTAPI
EngpGetPDEV(PUNICODE_STRING pustrDevice)
{
    __debugbreak();
    return NULL;
}

PSURFACE
NTAPI
PDEVOBJ_pSurface(PPDEVOBJ ppdev)
{
    __debugbreak();
    return NULL;
}

PSIZEL
FASTCALL
PDEVOBJ_sizl(PPDEVOBJ ppdev, PSIZEL psizl)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
PDEVOBJ_vRelease(PPDEVOBJ ppdev)
{
    __debugbreak();
}

INT
NTAPI
NtGdiGetDeviceCaps(HDC hdc, INT Index)
{
    __debugbreak();
    return GetDeviceCaps(hdc, Index);
}

} // extern "C"
