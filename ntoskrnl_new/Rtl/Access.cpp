
#include "Rtl.hpp"

typedef struct _GENERIC_MAPPING *PGENERIC_MAPPING;

extern "C" {

// wine: https://source.winehq.org/WineAPI/RtlAreAllAccessesGranted.html
// http://filelog.net/func/RtlAreAllAccessesGranted
BOOLEAN
NTAPI
RtlAreAllAccessesGranted (
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ACCESS_MASK DesiredAccess)
{
    __debugbreak();
    return FALSE;
}

// wine
// http://filelog.net/func/RtlAreAnyAccessesGranted
BOOLEAN
NTAPI
RtlAreAnyAccessesGranted (
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ACCESS_MASK DesiredAccess)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
RtlMapGenericMask(
    _Inout_ PACCESS_MASK AccessMask,
    _In_ PGENERIC_MAPPING GenericMapping)
{
    __debugbreak();
}

} // extern "C"
