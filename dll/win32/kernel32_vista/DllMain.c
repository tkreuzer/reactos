
#include "k32_vista.h"

char __roscompat_descriptor__;
char* p__roscompat_descriptor__ = &__roscompat_descriptor__;

BOOL
WINAPI
DllMain(HANDLE hDll,
        DWORD dwReason,
        LPVOID lpReserved)
{
    /* For now, there isn't much to do */
    if (dwReason == DLL_PROCESS_ATTACH)
        DisableThreadLibraryCalls(hDll);
    return TRUE;
}
