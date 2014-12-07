
#include <Rtl.hpp>

extern "C" {

// ntosifs.h
ULONG
NTAPI
RtlComputeCrc32 (
    _In_ ULONG PartialCrc,
    _In_ PVOID Buffer,
    _In_ ULONG Length)
{
    __debugbreak();
    return 0;
}

ULONG
NTAPI
RtlCrc32 (
    _In_reads_bytes_(Size) const void *Buffer,
    _In_ size_t Size,
    _In_ ULONG InitialCrc)
{
    __debugbreak();
    return 0;
}

ULONGLONG
NTAPI
RtlCrc64 (
    _In_reads_bytes_(Size) const void *Buffer,
    _In_ size_t Size,
    _In_ ULONGLONG InitialCrc)
{
    __debugbreak();
    return 0;
}

}; // extern "C"
