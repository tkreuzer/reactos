
#include "Rtl.hpp"

extern "C" {

ULONG NlsAnsiCodePage;
ULONG NlsMbCodePageTag;
ULONG NlsMbOemCodePageTag;
ULONG NlsOemCodePage;
ULONG NlsOemLeadByteInfo;

// undocumented
NTSTATUS
NTAPI
RtlGetThreadLangIdByIndex (
    PVOID P1,
    PVOID P2,
    PVOID P3,
    PVOID P4)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlCultureNameToLCID
BOOLEAN
NTAPI
RtlCultureNameToLCID (
    PUNICODE_STRING String,
    PLCID Lcid)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlLCIDToCultureName
BOOLEAN
NTAPI
RtlLCIDToCultureName (
    LCID Lcid,
    PUNICODE_STRING String)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlGetDefaultCodePage
VOID
NTAPI
RtlGetDefaultCodePage (
    PUSHORT AnsiCodePage,
    PUSHORT OemCodePage)
{
    __debugbreak();
}

// ntifs.h
// see https://msdn.microsoft.com/dd318149.aspx
NTSTATUS
NTAPI
RtlIdnToAscii (
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
RtlIdnToNameprepUnicode (
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
RtlIdnToUnicode (
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
