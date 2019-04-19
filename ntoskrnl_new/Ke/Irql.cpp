
#include "Irql.hpp"

extern "C" {

KIRQL
NTAPI
KeGetEffectiveIrql (
    VOID)
{
    __debugbreak();
    return 0;
}

//@ stdcall -arch=x86_64 KeGetCurrentIrql()


//@ stdcall -stub KeSetProfileIrql(long)
// from Ke_NUKE
VOID
NTAPI
KeSetProfileIrql(IN KIRQL ProfileIrql)
{
    __debugbreak();
}

}; // extern "C"
