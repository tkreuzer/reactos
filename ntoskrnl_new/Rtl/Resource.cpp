
#include "Rtl.hpp"

extern "C" {

typedef struct _RTL_MESSAGE_RESOURCE_ENTRY *PRTL_MESSAGE_RESOURCE_ENTRY;

// http://filelog.net/func/RtlFindMessage
NTSTATUS
NTAPI
RtlFindMessage (
    PVOID BaseAddress,
    ULONG Type,
    ULONG Language,
    ULONG MessageId,
    PRTL_MESSAGE_RESOURCE_ENTRY* MessageResourceEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlFormatMessage
NTSTATUS
NTAPI
RtlFormatMessage (
    PWSTR MessageFormat,
    ULONG MaximumWidth,
    BOOLEAN IgnoreInserts,
    BOOLEAN ArgumentsAreAnsi,
    BOOLEAN ArgumentsAreAnArray,
    va_list* Arguments,
    PWSTR Buffer,
    ULONG Length,
    PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// backtrace: http://www.hivmr.com/db/91a1cf3mcd1cscx1xfxaaxkp83j1acsa
// LoadString: https://msdn.microsoft.com/ms647486.aspx
NTSTATUS
NTAPI
RtlLoadString (
    _In_opt_ HINSTANCE hInstance,
    _In_ UINT uID,
    PVOID P3,
    PVOID P4,
    PVOID P5,
    PVOID P6,
    PVOID P7,
    PVOID P8)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
