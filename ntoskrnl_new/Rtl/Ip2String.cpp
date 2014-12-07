
#include "Rtl.hpp"

extern "C" {

// ip2string.h
struct in_addr;
struct in6_addr;
union _DL_EUI48;
typedef union _DL_EUI48 DL_EUI48, *PDL_EUI48;

// ip2string.h
PSTR
NTAPI
RtlEthernetAddressToStringA (
    _In_ const DL_EUI48 *Addr,
    _Out_writes_(18) PSTR AddressString)
{
    __debugbreak();
    return NULL;
}

// ip2string.h
PWSTR
NTAPI
RtlEthernetAddressToStringW (
    _In_ const DL_EUI48 *Addr,
    _Out_writes_(18) PWSTR AddressString)
{
    __debugbreak();
    return NULL;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlEthernetStringToAddressA (
    _In_ PCSTR AddressString,
    _Out_ PCSTR *Terminator,
    _Out_ DL_EUI48 *Addr)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlEthernetStringToAddressW (
    _In_ PCWSTR AddressString,
    _Out_ LPCWSTR *Terminator,
    _Out_ DL_EUI48 *Addr)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
PSTR
NTAPI
RtlIpv4AddressToStringA (
    _In_ const struct in_addr *Addr,
    _Out_writes_(16) PSTR AddressString)
{
    __debugbreak();
    return NULL;
}

// ip2string.h
PWSTR
NTAPI
RtlIpv4AddressToStringW (
    _In_ const struct in_addr *Addr,
    _Out_writes_(16) PWSTR AddressString)
{
    __debugbreak();
    return NULL;
}

// ip2string.h
NTSTATUS
NTAPI
RtlIpv4AddressToStringExA(
    _In_ const struct in_addr *Address,
    _In_ USHORT Port,
    _Out_writes_to_(*AddressStringLength, *AddressStringLength) PSTR AddressString,
    _Inout_ PULONG AddressStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
NTSTATUS
NTAPI
RtlIpv4AddressToStringExW(
    _In_ const struct in_addr *Address,
    _In_ USHORT Port,
    _Out_writes_to_(*AddressStringLength, *AddressStringLength) PWSTR AddressString,
    _Inout_ PULONG AddressStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlIpv4StringToAddressA (
    _In_ PCSTR AddressString,
    _In_ BOOLEAN Strict,
    _Out_ PCSTR *Terminator,
    _Out_ struct in_addr *Addr)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlIpv4StringToAddressW (
    _In_ PCWSTR AddressString,
    _In_ BOOLEAN Strict,
    _Out_ LPCWSTR *Terminator,
    _Out_ struct in_addr *Addr)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlIpv4StringToAddressExA (
    _In_ PCSTR AddressString,
    _In_ BOOLEAN Strict,
    _Out_ struct in_addr *Address,
    _Out_ PUSHORT Port)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlIpv4StringToAddressExW (
    _In_ PCWSTR AddressString,
    _In_ BOOLEAN Strict,
    _Out_ struct in_addr *Address,
    _Out_ PUSHORT Port)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
PSTR
NTAPI
RtlIpv6AddressToStringA (
    _In_ const struct in6_addr *Addr,
    _Out_writes_(46) PSTR AddressString)
{
    __debugbreak();
    return NULL;
}

// ip2string.h
PWSTR
NTAPI
RtlIpv6AddressToStringW (
    _In_ const struct in6_addr *Addr,
    _Out_writes_(46) PWSTR AddressString)
{
    __debugbreak();
    return NULL;
}

// ip2string.h
NTSTATUS
NTAPI
RtlIpv6AddressToStringExA (
    _In_ const struct in6_addr *Address,
    _In_ ULONG ScopeId,
    _In_ USHORT Port,
    _Out_writes_to_(*AddressStringLength, *AddressStringLength) PSTR AddressString,
    _Inout_ PULONG AddressStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
NTSTATUS
NTAPI
RtlIpv6AddressToStringExW (
    _In_ const struct in6_addr *Address,
    _In_ ULONG ScopeId,
    _In_ USHORT Port,
    _Out_writes_to_(*AddressStringLength, *AddressStringLength) PWSTR AddressString,
    _Inout_ PULONG AddressStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlIpv6StringToAddressA (
    _In_ PCSTR AddressString,
    _Out_ PCSTR *Terminator,
    _Out_ struct in6_addr *Addr)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlIpv6StringToAddressW (
    _In_ PCWSTR AddressString,
    _Out_ PCWSTR *Terminator,
    _Out_ struct in6_addr *Addr)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSTATUS
NTAPI
RtlIpv6StringToAddressExA (
    _In_ PCSTR AddressString,
    _Out_ struct in6_addr *Address,
    _Out_ PULONG ScopeId,
    _Out_ PUSHORT Port)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ip2string.h
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlIpv6StringToAddressExW (
    _In_ PCWSTR AddressString,
    _Out_ struct in6_addr *Address,
    _Out_ PULONG ScopeId,
    _Out_ PUSHORT Port)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
