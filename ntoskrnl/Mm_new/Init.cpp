

#include "ntosbase.h"

#define UNIMPLEMENTED __debugbreak()

extern "C" {

BOOLEAN
NTAPI
MmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmArmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
    return FALSE;
}

VOID
NTAPI
//INIT_FUNCTION
MmFreeLoaderBlock (
    struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
}


}; // extern "C"
