
#include "Exp.hpp"

extern "C" {

__drv_preferredFunction("lookaside lists instead", "Obsolete")
DECLSPEC_DEPRECATED_DDK
NTSTATUS
NTAPI
ExInitializeZone (
    _Out_ PZONE_HEADER Zone,
    _In_ ULONG BlockSize,
    _Inout_ PVOID InitialSegment,
    _In_ ULONG InitialSegmentSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__drv_preferredFunction("lookaside lists instead", "Obsolete")
DECLSPEC_DEPRECATED_DDK
NTSTATUS
NTAPI
ExExtendZone (
    _Inout_ PZONE_HEADER Zone,
    _Inout_ PVOID Segment,
    _In_ ULONG SegmentSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
