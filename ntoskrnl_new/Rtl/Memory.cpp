
#include "Rtl.hpp"

extern "C" {

#if defined(_M_AMD64)
VOID
NTAPI
RtlCopyMemoryNonTemporal (
   _Out_writes_bytes_all_(Length) VOID UNALIGNED *Destination,
   _In_reads_bytes_(Length) CONST VOID UNALIGNED *Source,
   _In_ SIZE_T Length)
{
    __debugbreak();
}
#endif

#ifndef _WIN64
VOID
NTAPI
_RtlFillMemoryUlong (
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern)
{
    __debugbreak();
}

VOID
NTAPI
_RtlFillMemoryUlonglong (
   _Out_writes_bytes_all_(Length) PVOID Destination,
   _In_ SIZE_T Length,
   _In_ ULONGLONG Pattern)
{
    __debugbreak();
}
#endif

_Check_return_
SIZE_T
NTAPI
RtlCompareMemory (
    _In_ const VOID * Source1,
    _In_ const VOID * Source2,
    _In_ SIZE_T Length)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
SIZE_T
NTAPI
RtlCompareMemoryUlong (
    _In_reads_bytes_(Length) PVOID Source,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern)
{
    __debugbreak();
    return 0;
}

VOID
FASTCALL
RtlPrefetchMemoryNonTemporal(
    _In_ PVOID Source,
    _In_ SIZE_T Length)
{
    __debugbreak();
}


} // extern "C"
