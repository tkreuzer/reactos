
#include "Luid.hpp"

extern "C" {

BOOLEAN
NTAPI
RtlEqualLuid (
    _In_ const LUID *Luid1,
    _In_ const LUID *Luid2)
{
    return ((Luid1->LowPart == Luid2->LowPart) &&
            (Luid1->HighPart == Luid2->HighPart));
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
RtlCopyLuid (
    _Out_ PLUID DestinationLuid,
    _In_ PLUID SourceLuid)
{
    __debugbreak();
}

// http://filelog.net/func/RtlCopyLuidAndAttributesArray
VOID
NTAPI
RtlCopyLuidAndAttributesArray (
    ULONG Count,
    PLUID_AND_ATTRIBUTES Src,
    PLUID_AND_ATTRIBUTES Dest)
{
    __debugbreak();
}

} // extern "C"
