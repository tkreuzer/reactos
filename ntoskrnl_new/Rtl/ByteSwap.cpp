
#include "Rtl.hpp"

extern "C" {

USHORT
FASTCALL
RtlUshortByteSwap (
    _In_ USHORT Source)
{
#if defined(_M_IX86) || (defined(_M_AMD64) || defined(_M_IA64)) || defined(_M_ARM) || defined(_M_ARM64)
    return _byteswap_ushort(Source);
#else
    return (Source >> 8) | (Source << 8);
#endif // _M_IX86
}

ULONG
FASTCALL
RtlUlongByteSwap (
    _In_ ULONG Source)
{
#if defined(_M_IX86) || (defined(_M_AMD64) || defined(_M_IA64)) || defined(_M_ARM) || defined(_M_ARM64)
    return _byteswap_ulong(Source);
#else
    return ((Source & 0x000000FF) << 24) |
           ((Source & 0x0000FF00) << 8) |
           ((Source & 0x00FF0000) >> 8) |
           ((Source & 0xFF000000) >> 24);
#endif // _M_IX86
}

ULONGLONG
FASTCALL
RtlUlonglongByteSwap (
    _In_ ULONGLONG Source)
{
#if defined(_M_IX86) || (defined(_M_AMD64) || defined(_M_IA64)) || defined(_M_ARM) || defined(_M_ARM64)
    return _byteswap_uint64(Source);
#else
    return RtlUlongByteSwap(Source >> 32) | RtlUlonglongByteSwap(Source & 0xFFFFFFFF) << 32;
#endif // _M_IX86
}

} // extern "C"
