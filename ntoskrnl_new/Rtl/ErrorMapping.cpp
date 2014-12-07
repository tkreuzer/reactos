
#include "Rtl.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
_When_(Status < 0, _Out_range_(>, 0))
_When_(Status >= 0, _Out_range_(==, 0))
ULONG
NTAPI
RtlNtStatusToDosError (
   _In_ NTSTATUS Status)
{
    __debugbreak();
    return 0;
}

_When_(Status < 0, _Out_range_(>, 0))
_When_(Status >= 0, _Out_range_(==, 0))
ULONG
NTAPI
RtlNtStatusToDosErrorNoTeb (
   _In_ NTSTATUS Status)
{
    __debugbreak();
    return 0;
}

// undocumented
NTSTATUS
NTAPI
RtlMapSecurityErrorToNtStatus (
   _In_ ULONG SecurityError)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
