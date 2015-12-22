
#include <win32k.h>

extern "C" {

PVOID
NTAPI
GdiPoolAllocate(
    PGDI_POOL pPool)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
GdiPoolFree(
    PGDI_POOL pPool,
    PVOID pvAlloc)
{
    __debugbreak();
}

PGDI_POOL
NTAPI
GdiPoolCreate(
    ULONG cjAllocSize,
    ULONG ulTag)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
GdiPoolDestroy(PGDI_POOL pPool)
{
    __debugbreak();
}

PGDI_POOL
GetBrushAttrPool(VOID)
{
    __debugbreak();
    return NULL;
}

} // extern "C"
