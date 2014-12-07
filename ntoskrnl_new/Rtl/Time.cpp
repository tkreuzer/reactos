
#include "Rtl.hpp"

extern "C" {

typedef struct _TIME_FIELDS
{
    CSHORT Year;
    CSHORT Month;
    CSHORT Day;
    CSHORT Hour;
    CSHORT Minute;
    CSHORT Second;
    CSHORT Milliseconds;
    CSHORT Weekday;
} TIME_FIELDS, *PTIME_FIELDS;

// ntosifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlSystemTimeToLocalTime (
    _In_ PLARGE_INTEGER SystemTime,
    _Out_ PLARGE_INTEGER LocalTime)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlLocalTimeToSystemTime (
    _In_ PLARGE_INTEGER LocalTime,
    _Out_ PLARGE_INTEGER SystemTime)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Success_(return != 0)
BOOLEAN
NTAPI
RtlTimeFieldsToTime (
    _In_ PTIME_FIELDS TimeFields,
    _Out_ PLARGE_INTEGER Time)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlTimeToTimeFields (
    _In_ PLARGE_INTEGER Time,
    _Out_ PTIME_FIELDS TimeFields)
{
    __debugbreak();
}

_Success_(return != 0)
BOOLEAN
NTAPI
RtlTimeToSecondsSince1980 (
    _In_ PLARGE_INTEGER Time,
    _Out_ PULONG ElapsedSeconds)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlSecondsSince1980ToTime (
    _In_ ULONG ElapsedSeconds,
    _Out_ PLARGE_INTEGER Time)
{
    __debugbreak();
}

_Success_(return != 0)
BOOLEAN
NTAPI
RtlTimeToSecondsSince1970 (
    _In_ PLARGE_INTEGER Time,
    _Out_ PULONG ElapsedSeconds)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlSecondsSince1970ToTime (
    _In_ ULONG ElapsedSeconds,
    _Out_ PLARGE_INTEGER Time)
{
    __debugbreak();
}

// ntosifs.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
RtlTimeToElapsedTimeFields (
    _In_ PLARGE_INTEGER Time,
    _Out_ PTIME_FIELDS TimeFields)
{
    __debugbreak();
}

#if 0 // not exported
// ntosifs.h
_IRQL_requires_max_(APC_LEVEL)
_Success_(return != 0)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlCutoverTimeToSystemTime (
    _In_ PTIME_FIELDS CutoverTime,
    _Out_ PLARGE_INTEGER SystemTime,
    _In_ PLARGE_INTEGER CurrentSystemTime,
    _In_ BOOLEAN ThisYear
    );
{
    __debugbreak();
    return FALSE;
}
#endif // 0

typedef struct _RTL_TIME_ZONE_INFORMATION *PRTL_TIME_ZONE_INFORMATION;

// http://filelog.net/func/RtlQueryTimeZoneInformation
NTSTATUS
NTAPI
RtlQueryTimeZoneInformation (
    PRTL_TIME_ZONE_INFORMATION TimeZoneInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlSetTimeZoneInformation
NTSTATUS
NTAPI
RtlSetTimeZoneInformation (
    PRTL_TIME_ZONE_INFORMATION TimeZoneInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
RtlQueryDynamicTimeZoneInformation (
    PVOID TimeZoneInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
RtlSetDynamicTimeZoneInformation (
    PVOID TimeZoneInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
