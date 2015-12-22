
#include <windows.h>
#include "umglue.h"

BOOL
GetDcInfo(
    _In_ HDC hdc,
    _Out_ PDC_INFO pdcinfo)
{
    pdcinfo->hbr = GetCurrentObject(hdc, OBJ_BRUSH);
    if (pdcinfo->hbr == NULL)
    {
        return FALSE;
    }

    pdcinfo->hbmp = GetCurrentObject(hdc, OBJ_BITMAP);


    return TRUE;
}

