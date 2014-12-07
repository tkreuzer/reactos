
#include <ntifs.h>

_IRQL_requires_same_
typedef
VOID
(NTAPI *PETW_CLASSIC_CALLBACK) (
    _In_ LPCGUID Guid,
    _In_ UCHAR ControlCode,
    _In_ PVOID EnableContext,
    _In_opt_ PVOID CallbackContext);

_IRQL_requires_same_
typedef
VOID
(NTAPI *PETW_BUFFER_COMPLETION_ROUTINE) (
    _In_ NTSTATUS Status,
    _In_ PVOID Buffer,
    _In_opt_ PVOID Context);

_When_(ControlCode==EVENT_ACTIVITY_CTRL_CREATE_ID, _IRQL_requires_max_(HIGH_LEVEL) _At_(ActivityId, _Out_))
_When_(ControlCode==EVENT_ACTIVITY_CTRL_GET_ID, _IRQL_requires_max_(APC_LEVEL) _At_(ActivityId, _Out_))
_When_(ControlCode==EVENT_ACTIVITY_CTRL_SET_ID, _IRQL_requires_max_(APC_LEVEL) _At_(ActivityId, _In_))
_When_(ControlCode==EVENT_ACTIVITY_CTRL_GET_SET_ID, _IRQL_requires_max_(APC_LEVEL) _At_(ActivityId, _Inout_))
_When_(ControlCode==EVENT_ACTIVITY_CTRL_CREATE_SET_ID, _IRQL_requires_max_(APC_LEVEL) _At_(ActivityId, _Out_))
NTSTATUS
NTAPI
EtwActivityIdControl (
    _In_ ULONG ControlCode,
    _Inout_updates_bytes_(sizeof(GUID)) LPGUID ActivityId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
EtwEnableTrace (
    _In_ LPCGUID ProviderId,
    _In_opt_ LPCGUID SourceId,
    _In_ TRACEHANDLE TraceHandle,
    _In_ ULONG ControlCode,
    _In_ UCHAR Level,
    _In_ ULONGLONG MatchAnyKeyword,
    _In_ ULONGLONG MatchAllKeyword,
    _In_ ULONG EnableProperty)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
BOOLEAN
NTAPI
EtwEventEnabled (
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(HIGH_LEVEL)
BOOLEAN
NTAPI
EtwProviderEnabled (
    _In_ REGHANDLE RegHandle,
    _In_ UCHAR Level,
    _In_ ULONGLONG Keyword)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
EtwRegister (
    _In_ LPCGUID ProviderId,
    _In_opt_ PETWENABLECALLBACK EnableCallback,
    _In_opt_ PVOID CallbackContext,
    _Out_ PREGHANDLE RegHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
EtwRegisterClassicProvider (
    _In_ LPCGUID ProviderId,
    _In_ ULONG Type,
    _In_ PETW_CLASSIC_CALLBACK EnableCallback,
    _In_opt_ PVOID CallbackContext,
    _Out_ PREGHANDLE RegHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
EtwSendTraceBuffer (
    _In_ ULONGLONG LoggerHandle,
    _In_ PVOID Buffer,
    _In_ ULONG EventsLost,
    _In_ PETW_BUFFER_COMPLETION_ROUTINE CompletionRoutine,
    _In_opt_ PVOID CompletionContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

enum _EVENT_INFO_CLASS
{
    Unknown,
};

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
EtwSetInformation(
    _In_ REGHANDLE RegHandle,
    _In_ enum _EVENT_INFO_CLASS InformationClass,
    _In_reads_bytes_opt_(InformationLength) PVOID EventInformation,
    _In_ ULONG InformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
EtwUnregister (
    _In_ REGHANDLE RegHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
EtwWrite (
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_opt_ LPCGUID ActivityId,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR  UserData)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
EtwWriteEx (
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ ULONG64 Filter,
    _In_ ULONG Flags,
    _In_opt_ LPCGUID ActivityId,
    _In_opt_ LPCGUID RelatedActivityId,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
EtwWriteString (
    _In_ REGHANDLE RegHandle,
    _In_ UCHAR Level,
    _In_ ULONGLONG Keyword,
    _In_opt_ LPCGUID ActivityId,
    _In_ PCWSTR String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
EtwWriteTransfer (
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_opt_ LPCGUID ActivityId,
    _In_opt_ LPCGUID RelatedActivityId,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

