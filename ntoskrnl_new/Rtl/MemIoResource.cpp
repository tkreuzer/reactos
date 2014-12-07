
#include "Rtl.hpp"

extern "C" {

typedef struct _IO_RESOURCE_DESCRIPTOR *PIO_RESOURCE_DESCRIPTOR;
typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR *PCM_PARTIAL_RESOURCE_DESCRIPTOR;

NTSTATUS
NTAPI
RtlIoEncodeMemIoResource (
    _In_ PIO_RESOURCE_DESCRIPTOR Descriptor,
    _In_ UCHAR Type,
    _In_ ULONGLONG Length,
    _In_ ULONGLONG Alignment,
    _In_ ULONGLONG MinimumAddress,
    _In_ ULONGLONG MaximumAddress)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlCmEncodeMemIoResource (
    _In_ PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor,
    _In_ UCHAR Type,
    _In_ ULONGLONG Length,
    _In_ ULONGLONG Start)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

ULONGLONG
NTAPI
RtlIoDecodeMemIoResource (
    _In_ PIO_RESOURCE_DESCRIPTOR Descriptor,
    _Out_opt_ PULONGLONG Alignment,
    _Out_opt_ PULONGLONG MinimumAddress,
    _Out_opt_ PULONGLONG MaximumAddress)
{
    __debugbreak();
    return 0;
}

ULONGLONG
NTAPI
RtlCmDecodeMemIoResource (
    _In_ PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor,
    _Out_opt_ PULONGLONG Start)
{
    __debugbreak();
    return 0;
}

} // extern "C"
