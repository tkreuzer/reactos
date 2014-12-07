
#include "Kep.hpp"

extern "C" {

VOID
NTAPI
KeFindConfigurationEntry (
    ULONG_PTR p1,
    ULONG_PTR p2,
    ULONG_PTR p3,
    ULONG_PTR p4)
{
    __debugbreak();
}

VOID
NTAPI
KeFindConfigurationNextEntry (
    ULONG_PTR p1,
    ULONG_PTR p2,
    ULONG_PTR p3,
    ULONG_PTR p4,
    ULONG_PTR p5)
{
    __debugbreak();
}

}; // extern "C"
