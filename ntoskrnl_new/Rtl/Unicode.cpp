
#include "Rtl.hpp"

extern "C" {

typedef struct _CPTABLEINFO *PCPTABLEINFO;

// ntddk.h
_IRQL_requires_max_(PASSIVE_LEVEL)
CHAR
NTAPI
RtlUpperChar (
    _In_ CHAR Character)
{
    __debugbreak();
    return 0;
}

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlIsValidOemCharacter (
    _Inout_ PWCHAR Char)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
NTAPI
RtlInitCodePageTable (
    _In_ PUSHORT TableBase,
    _Inout_ PCPTABLEINFO CodePageTable)
{
    __debugbreak();
}

// wdm.h
_IRQL_requires_max_(PASSIVE_LEVEL)
WCHAR
NTAPI
RtlUpcaseUnicodeChar (
    _In_ WCHAR SourceCharacter)
{
    __debugbreak();
    return 0;
}

// wdm.h
_IRQL_requires_max_(PASSIVE_LEVEL)
WCHAR
NTAPI
RtlDowncaseUnicodeChar (
    _In_ WCHAR SourceCharacter)
{
    __debugbreak();
    return 0;
}

// http://filelog.net/func/RtlAnsiCharToUnicodeChar
WCHAR
NTAPI
RtlAnsiCharToUnicodeChar (
    PUCHAR* SourceCharacter)
{
    __debugbreak();
    return 0;
}

// http://filelog.net/func/RtlUpcaseUnicodeStringToAnsiString
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToAnsiString (
    PANSI_STRING DestinationString,
    PUNICODE_STRING SourceString,
    BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlAnsiStringToUnicodeString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PUNICODE_STRING DestinationString,
    _In_ PCANSI_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_When_(AllocateDestinationString,
       _At_(DestinationString->MaximumLength,
            _Out_range_(<=, (SourceString->MaximumLength / sizeof(WCHAR)))))
_When_(!AllocateDestinationString,
       _At_(DestinationString->Buffer, _Const_)
       _At_(DestinationString->MaximumLength, _Const_))
_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
NTSTATUS
NTAPI
RtlUnicodeStringToAnsiString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PANSI_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlxAnsiStringToUnicodeSize (
    _In_ PCANSI_STRING AnsiString)
{
    __debugbreak();
    return 0;
}

//#define RtlAnsiStringToUnicodeSize(STRING) (                 \
//    NLS_MB_CODE_PAGE_TAG ?                                   \
//    RtlxAnsiStringToUnicodeSize(STRING) :                    \
//    ((STRING)->Length + sizeof(ANSI_NULL)) * sizeof(WCHAR) \
//)
_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlAnsiStringToUnicodeSize (
    _In_ PCANSI_STRING AnsiString)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlxUnicodeStringToAnsiSize (
    _In_ PCUNICODE_STRING UnicodeString)
{
    __debugbreak();
    return 0;
}

//#define RtlUnicodeStringToAnsiSize(STRING) (                  \
//    NLS_MB_CODE_PAGE_TAG ?                                    \
//    RtlxUnicodeStringToAnsiSize(STRING) :                     \
//    ((STRING)->Length + sizeof(UNICODE_NULL)) / sizeof(WCHAR) \
//)

_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlUnicodeStringToAnsiSize (
    _In_ PCUNICODE_STRING UnicodeString)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlUnicodeToUTF8N (
    _Out_writes_bytes_to_(UTF8StringMaxByteCount, *UTF8StringActualByteCount) PCHAR UTF8StringDestination,
    _In_ ULONG  UTF8StringMaxByteCount,
    _Out_ PULONG UTF8StringActualByteCount,
    _In_reads_bytes_(UnicodeStringByteCount) PCWCH UnicodeStringSource,
    _In_ ULONG  UnicodeStringByteCount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlUTF8ToUnicodeN (
    _Out_writes_bytes_to_(UnicodeStringMaxByteCount, *UnicodeStringActualByteCount) PWSTR UnicodeStringDestination,
    _In_ ULONG  UnicodeStringMaxByteCount,
    _Out_ PULONG UnicodeStringActualByteCount,
    _In_reads_bytes_(UTF8StringByteCount) PCCH UTF8StringSource,
    _In_ ULONG  UTF8StringByteCount)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlOemStringToUnicodeString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PUNICODE_STRING DestinationString,
    _In_ PCOEM_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
_When_(AllocateDestinationString, _At_(DestinationString->Buffer, _Post_notnull_ __drv_allocatesMem(Mem)))
NTSTATUS
NTAPI
RtlUnicodeStringToOemString (
    _When_(AllocateDestinationString, _Out_)
    _When_(!AllocateDestinationString, _Inout_)
        POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToOemString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlOemStringToCountedUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        PUNICODE_STRING DestinationString,
    _In_ PCOEM_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlUnicodeStringToCountedOemString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToCountedOemString (
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
        POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlxUnicodeStringToOemSize (
    _In_ PCUNICODE_STRING UnicodeString)
{
    __debugbreak();
    return 0;
}

//#define RtlUnicodeStringToOemSize(STRING) (                   \
//    NLS_MB_OEM_CODE_PAGE_TAG ?                                \
//    RtlxUnicodeStringToOemSize(STRING) :                      \
//    ((STRING)->Length + sizeof(UNICODE_NULL)) / sizeof(WCHAR) \
//)

_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlUnicodeStringToOemSize (
    _In_ PCUNICODE_STRING UnicodeString)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlxOemStringToUnicodeSize (
    _In_ PCOEM_STRING OemString)
{
    __debugbreak();
    return 0;
}

//#define RtlOemStringToUnicodeSize(STRING) (                  \
//    NLS_MB_OEM_CODE_PAGE_TAG ?                               \
//    RtlxOemStringToUnicodeSize(STRING) :                     \
//    ((STRING)->Length + sizeof(ANSI_NULL)) * sizeof(WCHAR) \
//)

_IRQL_requires_max_(PASSIVE_LEVEL)
ULONG
NTAPI
RtlOemStringToUnicodeSize (
    _In_ PCOEM_STRING OemString)
{
    __debugbreak();
    return 0;
}

// export?
#define RtlOemStringToCountedUnicodeSize(STRING) (                    \
    (ULONG)(RtlOemStringToUnicodeSize(STRING) - sizeof(UNICODE_NULL)) \
    )

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlMultiByteToUnicodeN (
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) const CHAR *MultiByteString,
    _In_ ULONG BytesInMultiByteString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlMultiByteToUnicodeSize (
    _Out_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) const CHAR *MultiByteString,
    _In_ ULONG BytesInMultiByteString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUnicodeToMultiByteSize (
    _Out_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUnicodeToMultiByteN (
    _Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
    _In_ ULONG MaxBytesInMultiByteString,
    _Out_opt_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUpcaseUnicodeToMultiByteN (
    _Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
    _In_ ULONG MaxBytesInMultiByteString,
    _Out_opt_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlOemToUnicodeN (
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInOemString) PCCH OemString,
    _In_ ULONG BytesInOemString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUnicodeToOemN (
    _Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
    _In_ ULONG MaxBytesInOemString,
    _Out_opt_ PULONG BytesInOemString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUpcaseUnicodeToOemN (
    _Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
    _In_ ULONG MaxBytesInOemString,
    _Out_opt_ PULONG BytesInOemString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlCustomCPToUnicodeN (
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG BytesInCustomCPString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUnicodeToCustomCPN (
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG MaxBytesInCustomCPString,
    _Out_opt_ PULONG BytesInCustomCPString,
    _In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlUpcaseUnicodeToCustomCPN (
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG MaxBytesInCustomCPString,
    _Out_opt_ PULONG BytesInCustomCPString,
    _In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
