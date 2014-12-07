
#include "Rtl.hpp"

extern "C" {

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlCharToInteger (
    _In_z_ PCSZ String,
    _In_opt_ ULONG Base,
    _Out_ PULONG Value)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlIntegerToChar
NTSTATUS
NTAPI
RtlIntegerToChar (
    _In_ ULONG Value,
    _In_ ULONG Base,
    _In_ ULONG Length,
    PCHAR String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlIntegerToUnicode
NTSTATUS
NTAPI
RtlIntegerToUnicode (
    _In_ ULONG Value,
    _In_ ULONG Base,
    _In_ ULONG Length,
    _Out_ LPWSTR String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_At_(String->MaximumLength, _Const_)
NTSTATUS
NTAPI
RtlIntegerToUnicodeString (
    _In_ ULONG Value,
    _In_opt_ ULONG Base,
    _Inout_ PUNICODE_STRING String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_At_(String->MaximumLength, _Const_)
NTSTATUS
NTAPI
RtlInt64ToUnicodeString (
    _In_ ULONGLONG Value,
    _In_opt_ ULONG Base,
    _Inout_ PUNICODE_STRING String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUnicodeStringToInteger (
    _In_ PCUNICODE_STRING String,
    _In_opt_ ULONG Base,
    _Out_ PULONG Value)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlUnicodeStringToInt64 (
    _In_ PCUNICODE_STRING String,
    _In_opt_ ULONG Base,
    _Out_ PLONG64 Number,
    _Out_opt_ PWSTR *EndPointer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
