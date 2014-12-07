
#include "Rtl.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<=, MAXLONG)
ULONG
NTAPI
RtlRandom (
    _Inout_ PULONG Seed)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<=, MAXLONG)
ULONG
NTAPI
RtlRandomEx (
    _Inout_ PULONG Seed)
{
    __debugbreak();
    return 0;
}

} // extern "C"
