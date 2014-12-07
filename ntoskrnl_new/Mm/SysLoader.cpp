
#include "Mmp.hpp"

extern "C" {

//@ stub MmLoadSystemImage
//@ stub MmUnloadSystemImage

_IRQL_requires_max_(PASSIVE_LEVEL)
PVOID
NTAPI
MmGetSystemRoutineAddress (
    _In_ PUNICODE_STRING SystemRoutineName)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
MmPageEntireDriver (
    _In_ PVOID AddressWithinSection)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmResetDriverPaging (
    _In_ PVOID AddressWithinSection)
{
    __debugbreak();
}


}; // extern "C"


