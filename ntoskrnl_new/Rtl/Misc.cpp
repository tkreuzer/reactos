
#include "Rtl.hpp"
#include "SecurityDescriptor.hpp"
#include <Se/Se.hpp>

extern "C" {

typedef struct _CPTABLEINFO *PCPTABLEINFO;

typedef
ULONG
NTAPI
THREAD_START_ROUTINE (
    PVOID lpThreadParameter);
typedef THREAD_START_ROUTINE *PTHREAD_START_ROUTINE, *LPTHREAD_START_ROUTINE;

// http://filelog.net/func/RtlCreateUserThread
NTSTATUS
NTAPI
RtlCreateUserThread (
    HANDLE /* [ProcessHandle] */ ProcessHandle,
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    BOOLEAN CreateSuspended,
    ULONG StackZeroBits,
    SIZE_T StackReserve,
    SIZE_T StackCommit,
    PTHREAD_START_ROUTINE StartAddress,
    PVOID Parameter,
    PHANDLE ThreadHandle,
    PCLIENT_ID ClientId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//@ stub RtlEqualWnfChangeStamps

// http://filelog.net/func/RtlSidHashInitialize
NTSTATUS
NTAPI
RtlSidHashInitialize (
    PSID_AND_ATTRIBUTES SidAttr,
    ULONG SidCount,
    PSID_AND_ATTRIBUTES_HASH SidAttrHash)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlSidHashLookup
// On success return NotEqual 0
PSID_AND_ATTRIBUTES
NTAPI
RtlSidHashLookup (
    PSID_AND_ATTRIBUTES_HASH SidAttrHash,
    PSID Sid)
{
    __debugbreak();
    return NULL;
}

// wdm.h
__analysis_noreturn
VOID
NTAPI
RtlAssert (
    _In_ PVOID VoidFailedAssertion,
    _In_ PVOID VoidFileName,
    _In_ ULONG LineNumber,
    _In_opt_ PSTR MutableMessage)
{
    __debugbreak();
}

// ntifs.h
LONG
NTAPI
RtlCompareAltitudes (
    _In_ PCUNICODE_STRING Altitude1,
    _In_ PCUNICODE_STRING Altitude2)
{
    __debugbreak();
    return 0;
}

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlCreateSystemVolumeInformationFolder (
    _In_ PCUNICODE_STRING VolumeRootPath)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef struct _GENERATE_NAME_CONTEXT
{
    USHORT Checksum;
    BOOLEAN ChecksumInserted;
    _Field_range_(<=, 8) UCHAR NameLength;
    WCHAR NameBuffer[8];
    _Field_range_(<=, 4) ULONG ExtensionLength;
    WCHAR ExtensionBuffer[4];
    ULONG LastIndexValue;
} GENERATE_NAME_CONTEXT, *PGENERATE_NAME_CONTEXT;

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
BOOLEAN
NTAPI
RtlIsNameLegalDOS8Dot3 (
    _In_ PCUNICODE_STRING Name,
    _Inout_opt_ POEM_STRING OemName,
    _Out_opt_ PBOOLEAN NameContainsSpaces)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlGenerate8dot3Name (
    _In_    PCUNICODE_STRING Name,
    _In_    BOOLEAN AllowExtendedCharacters,
    _Inout_ PGENERATE_NAME_CONTEXT Context,
    _Inout_ PUNICODE_STRING Name8dot3)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntddk.h
__drv_preferredFunction("IoVolumeDeviceToDosName",
    "Obsolete on WINXP and above")
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlVolumeDeviceToDosName (
    _In_ PVOID VolumeDeviceObject,
    _Out_ PUNICODE_STRING DosName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h
NTSTATUS
NTAPI
RtlFindClosestEncodableLength (
    _In_ ULONGLONG SourceLength,
    _Out_ PULONGLONG TargetLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// wdm.h
NTSTATUS
NTAPI
RtlIsUntrustedObject (
    _In_opt_ HANDLE Handle,
    _In_opt_ PVOID Object,
    _Out_ PBOOLEAN UntrustedObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// rtlsupportapi.h
__analysis_noreturn
VOID
NTAPI
RtlRaiseException (
    _In_ PEXCEPTION_RECORD ExceptionRecord);

__analysis_noreturn
VOID
NTAPI
RtlRaiseStatus (
    _In_ NTSTATUS Status)
{
    __debugbreak();
}

#undef RtlFillMemory
VOID
NTAPI
RtlFillMemory (
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ UCHAR Fill)
{
    __debugbreak();
}

#undef RtlZeroMemory
VOID
NTAPI
RtlZeroMemory (
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length)
{
    __debugbreak();
}

// wdm.h
ULONG
NTAPI
vDbgPrintEx (
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list ArgList)
{
    __debugbreak();
    return 0;
}

// wdm.h
ULONG
NTAPI
vDbgPrintExWithPrefix (
    _In_z_ PCCH Prefix,
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list ArgList)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
RtlGetSetBootStatusData (
    PVOID P1,
    ULONG P2,
    ULONG P3,
    PVOID P4,
    ULONG P5,
    ULONG P6)
{
    __debugbreak();
}

VOID
NTAPI
RtlLockBootStatusData (
    PVOID P1)
{
    __debugbreak();
}

VOID
NTAPI
RtlUnlockBootStatusData (
    PVOID P1)
{
    __debugbreak();
}

} // extern "C"
