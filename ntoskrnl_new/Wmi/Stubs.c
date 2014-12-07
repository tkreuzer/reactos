
#include <ntifs.h>

//@ stub WmiGetClock

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
WmiQueryTraceInformation (
    _In_ TRACE_INFORMATION_CLASS TraceInformationClass,
    _Out_writes_bytes_(TraceInformationLength) PVOID TraceInformation,
    _In_ ULONG TraceInformationLength,
    _Out_opt_ PULONG RequiredLength,
    _In_opt_ PVOID Buffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
WmiTraceMessageVa (
    _In_ TRACEHANDLE LoggerHandle,
    _In_ ULONG MessageFlags,
    _In_ LPGUID MessageGuid,
    _In_ USHORT MessageNumber,
    _In_ va_list MessageArgList)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
NTAPI
WmiTraceMessage (
    _In_ TRACEHANDLE LoggerHandle,
    _In_ ULONG MessageFlags,
    _In_ LPGUID MessageGuid,
    _In_ USHORT MessageNumber,
    ...)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

