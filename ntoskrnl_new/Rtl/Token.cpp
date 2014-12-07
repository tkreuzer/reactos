
#include "Rtl.hpp"

extern "C" {

typedef struct _TOKEN *PTOKEN;

VOID
NTAPI
RtlCheckTokenCapability (
    PTOKEN Token,
    ULONG P2,
    ULONG P3)
{
    __debugbreak();
}

VOID
NTAPI
RtlCheckTokenMembership (
    PTOKEN Token,
    ULONG P2,
    ULONG P3)
{
    __debugbreak();
}

VOID
NTAPI
RtlCheckTokenMembershipEx (
    PTOKEN Token,
    ULONG P2,
    ULONG P3,
    ULONG P4)
{
    __debugbreak();
}

} // extern "C"
