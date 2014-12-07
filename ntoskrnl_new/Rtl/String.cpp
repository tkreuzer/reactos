
#include "Rtl.hpp"

extern "C" {

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
RtlInitString (
    _Out_ PSTRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString)
{
    __debugbreak();
}

// use RtlInitString
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
RtlInitAnsiString (
    _Out_ PANSI_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(DestinationString->Buffer, _Post_equal_to_(SourceString))
_At_(DestinationString->Length, _Post_equal_to_(_String_length_(SourceString) * sizeof(WCHAR)))
_At_(DestinationString->MaximumLength, _Post_equal_to_((_String_length_(SourceString)+1) * sizeof(WCHAR)))
VOID
NTAPI
RtlInitUnicodeString (
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCWSTR SourceString)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
RtlInitStringEx (
    _Out_ PSTRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
RtlInitAnsiStringEx (
    _Out_ PANSI_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
RtlInitUnicodeStringEx (
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCWSTR SourceString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
LONG
NTAPI
RtlCompareString (
    _In_ const STRING * String1,
    _In_ const STRING * String2,
    _In_ BOOLEAN CaseInSensitive)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
LONG
NTAPI
RtlCompareUnicodeString (
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
LONG
NTAPI
RtlCompareUnicodeStrings (
    _In_reads_(String1Length) PCWCH String1,
    _In_ SIZE_T String1Length,
    _In_reads_(String2Length) PCWCH String2,
    _In_ SIZE_T String2Length,
    _In_ BOOLEAN CaseInSensitive)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlEqualString (
    _In_ const STRING * String1,
    _In_ const STRING * String2,
    _In_ BOOLEAN CaseInSensitive)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlEqualUnicodeString (
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlPrefixString (
    _In_ const STRING * String1,
    _In_ const STRING * String2,
    _In_ BOOLEAN CaseInSensitive)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlPrefixUnicodeString (
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlCopyString (
    _Out_ PSTRING DestinationString,
    _In_opt_ const STRING * SourceString)
{
    __debugbreak();
}

_Unchanged_(DestinationString->Buffer)
_Unchanged_(DestinationString->MaximumLength)
_At_(DestinationString->Length,
    _When_(SourceString->Length > DestinationString->MaximumLength,
        _Post_equal_to_(DestinationString->MaximumLength))
    _When_(SourceString->Length <= DestinationString->MaximumLength,
        _Post_equal_to_(SourceString->Length)))
VOID
NTAPI
RtlCopyUnicodeString (
    _Inout_ PUNICODE_STRING DestinationString,
    _In_opt_ PCUNICODE_STRING SourceString)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlDuplicateUnicodeString (
    _In_ ULONG Flags,
    _In_ PCUNICODE_STRING StringIn,
    _Out_ _At_(StringOut->Buffer, __drv_allocatesMem(Mem))
        PUNICODE_STRING StringOut)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
_Success_(return != 0)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlCreateUnicodeString (
    _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem))
        PUNICODE_STRING DestinationString,
    _In_z_ PCWSTR SourceString)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlAppendAsciizToString
NTSTATUS
NTAPI
RtlAppendAsciizToString (
    PSTRING Destination,
    PSTR Source)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
RtlUpperString (
    _Inout_ PSTRING DestinationString,
    _In_ const STRING * SourceString)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
NTSTATUS
NTAPI
RtlUpcaseUnicodeString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PUNICODE_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
NTSTATUS
NTAPI
RtlDowncaseUnicodeString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PUNICODE_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
NTSTATUS
NTAPI
RtlValidateUnicodeString (
    _Reserved_ ULONG Flags,
    _In_ PCUNICODE_STRING String)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
RtlFreeAnsiString (
    _Inout_ _At_(AnsiString->Buffer, _Frees_ptr_opt_)
        PANSI_STRING AnsiString)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
RtlFreeOemString (
    _Inout_ _At_(OemString->Buffer, _Frees_ptr_opt_)
        POEM_STRING OemString)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
RtlFreeUnicodeString (
    _Inout_ _At_(UnicodeString->Buffer, _Frees_ptr_opt_)
        PUNICODE_STRING UnicodeString)
{
    __debugbreak();
}

// ntifs.h
// export?
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
RtlAppendStringToString (
    _Inout_ PSTRING Destination,
    _In_ const STRING * Source)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Success_(1)
_Unchanged_(Destination->MaximumLength)
_Unchanged_(Destination->Buffer)
_When_(_Old_(Destination->Length) + Source->Length <= Destination->MaximumLength,
    _At_(Destination->Length,
         _Post_equal_to_(_Old_(Destination->Length) + Source->Length))
    _At_(return, _Out_range_(==, 0)))
_When_(_Old_(Destination->Length) + Source->Length > Destination->MaximumLength,
    _Unchanged_(Destination->Length)
    _At_(return, _Out_range_(<, 0)))
NTSTATUS
NTAPI
RtlAppendUnicodeStringToString (
    _Inout_ PUNICODE_STRING Destination,
    _In_ PCUNICODE_STRING Source)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Success_(1)
_Unchanged_(Destination->MaximumLength)
_Unchanged_(Destination->Buffer)
_When_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(WCHAR) <= Destination->MaximumLength,
    _At_(Destination->Length,
         _Post_equal_to_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(WCHAR)))
    _At_(return, _Out_range_(==, 0)))
_When_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(WCHAR) > Destination->MaximumLength,
    _Unchanged_(Destination->Length)
    _At_(return, _Out_range_(<, 0)))
NTSTATUS
NTAPI
RtlAppendUnicodeToString (
    _Inout_ PUNICODE_STRING Destination,
    _In_opt_z_ PCWSTR Source)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
RtlIsNormalizedString (
    _In_ ULONG NormForm,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_ PBOOLEAN Normalized)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
NTSTATUS
NTAPI
RtlNormalizeString (
    _In_ ULONG NormForm,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


#if 0
_At_(AnsiString->Buffer, _Post_equal_to_(Buffer))
_At_(AnsiString->Length, _Post_equal_to_(0))
_At_(AnsiString->MaximumLength, _Post_equal_to_(BufferSize))
FORCEINLINE
VOID
RtlInitEmptyAnsiString(
    _Out_ PANSI_STRING AnsiString,
    _Pre_maybenull_ _Pre_readable_size_(BufferSize) __drv_aliasesMem PCHAR Buffer,
    _In_ USHORT BufferSize)
{
    AnsiString->Length = 0;
    AnsiString->MaximumLength = BufferSize;
    AnsiString->Buffer = Buffer;
}

_At_(UnicodeString->Buffer, _Post_equal_to_(Buffer))
_At_(UnicodeString->Length, _Post_equal_to_(0))
_At_(UnicodeString->MaximumLength, _Post_equal_to_(BufferSize))
FORCEINLINE
VOID
RtlInitEmptyUnicodeString (
    _Out_ PUNICODE_STRING UnicodeString,
    _Writable_bytes_(BufferSize)
    _When_(BufferSize != 0, _Notnull_)
    __drv_aliasesMem PWCHAR Buffer,
    _In_ USHORT BufferSize)
{
    UnicodeString->Length = 0;
    UnicodeString->MaximumLength = BufferSize;
    UnicodeString->Buffer = Buffer;
}
#endif // 0


} // extern "C"
