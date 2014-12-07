
#include "Rtl.hpp"

extern "C" {

// http://filelog.net/func/RtlFormatCurrentUserKeyPath
NTSTATUS
NTAPI
RtlFormatCurrentUserKeyPath (
    PUNICODE_STRING KeyPath)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlOpenCurrentUser
NTSTATUS
NTAPI
RtlOpenCurrentUser (
    ACCESS_MASK DesiredAccess,
    PHANDLE KeyHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef
_Function_class_(RTL_QUERY_REGISTRY_ROUTINE)
_IRQL_requires_max_(PASSIVE_LEVEL)
_IRQL_requires_same_
NTSTATUS
NTAPI
RTL_QUERY_REGISTRY_ROUTINE (
    _In_z_ PWSTR ValueName,
    _In_ ULONG ValueType,
    _In_reads_bytes_opt_(ValueLength) PVOID ValueData,
    _In_ ULONG ValueLength,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID EntryContext
    );
typedef RTL_QUERY_REGISTRY_ROUTINE *PRTL_QUERY_REGISTRY_ROUTINE;

typedef struct _RTL_QUERY_REGISTRY_TABLE
{
    PRTL_QUERY_REGISTRY_ROUTINE QueryRoutine;
    ULONG Flags;
    PWSTR Name;
    PVOID EntryContext;
    ULONG DefaultType;
    PVOID DefaultData;
    ULONG DefaultLength;
} RTL_QUERY_REGISTRY_TABLE, *PRTL_QUERY_REGISTRY_TABLE;

#define RTL_QUERY_REGISTRY_SUBKEY    0x00000001
#define RTL_QUERY_REGISTRY_TOPKEY    0x00000002
#define RTL_QUERY_REGISTRY_REQUIRED  0x00000004
#define RTL_QUERY_REGISTRY_NOVALUE   0x00000008
#define RTL_QUERY_REGISTRY_NOEXPAND  0x00000010
#define RTL_QUERY_REGISTRY_DIRECT    0x00000020
#define RTL_QUERY_REGISTRY_DELETE    0x00000040
#define RTL_QUERY_REGISTRY_NOSTRING  0x00000080
#define RTL_QUERY_REGISTRY_TYPECHECK 0x00000100

#define RTL_QUERY_REGISTRY_TYPECHECK_SHIFT  24
#define RTL_QUERY_REGISTRY_TYPECHECK_MASK  (0xff << RTL_QUERY_REGISTRY_TYPECHECK_SHIFT)

#define RTL_REGISTRY_ABSOLUTE     0   // Path is a full path
#define RTL_REGISTRY_SERVICES     1   // \Registry\Machine\System\CurrentControlSet\Services
#define RTL_REGISTRY_CONTROL      2   // \Registry\Machine\System\CurrentControlSet\Control
#define RTL_REGISTRY_WINDOWS_NT   3   // \Registry\Machine\Software\Microsoft\Windows NT\CurrentVersion
#define RTL_REGISTRY_DEVICEMAP    4   // \Registry\Machine\Hardware\DeviceMap
#define RTL_REGISTRY_USER         5   // \Registry\User\CurrentUser
#define RTL_REGISTRY_MAXIMUM      6
#define RTL_REGISTRY_HANDLE       0x40000000    // Low order bits are registry handle
#define RTL_REGISTRY_OPTIONAL     0x80000000    // Indicates the key node is optional

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlCheckRegistryKey(
    _In_ ULONG RelativeTo,
    _In_ PWSTR Path)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlCreateRegistryKey(
    _In_ ULONG RelativeTo,
    _In_ PWSTR Path)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlDeleteRegistryValue(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_z_ PCWSTR ValueName)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlQueryRegistryValues(
    _In_     ULONG RelativeTo,
    _In_     PCWSTR Path,
    _Inout_ _At_(*(*QueryTable).EntryContext, _Pre_unknown_)
        PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID Environment)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlWriteRegistryValue(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_z_ PCWSTR ValueName,
    _In_ ULONG ValueType,
    _In_reads_bytes_opt_(ValueLength) PVOID ValueData,
    _In_ ULONG ValueLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// see RtlxQueryRegistryValues
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlQueryRegistryValuesEx (
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _Inout_ _At_(*(*QueryTable).EntryContext, _Pre_unknown_)
        PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID Environment)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#if (NTDDI_VERSION >= NTDDI_WIN8) && !defined(MIDL_PASS)
#undef RtlQueryRegistryValues
#define RtlQueryRegistryValues RtlxQueryRegistryValues
#endif

#if 0 // not exported
_IRQL_requires_max_(PASSIVE_LEVEL)
FORCEINLINE
NTSTATUS
RtlxQueryRegistryValues (
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _Inout_ _At_(*(*QueryTable).EntryContext, _Pre_unknown_)
        PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID Environment)
{
    typedef NTSTATUS NTAPI QUERYFN(
        ULONG, PCWSTR, PRTL_QUERY_REGISTRY_TABLE, PVOID, PVOID);

    UNICODE_STRING FunctionName;
    QUERYFN* QueryRoutine;

    RtlInitUnicodeString(&FunctionName, L"RtlQueryRegistryValuesEx");

    #pragma warning(suppress: 4055)
    QueryRoutine = (QUERYFN*)MmGetSystemRoutineAddress(&FunctionName);

    if (QueryRoutine == NULL)
    {
        QueryRoutine = &RtlQueryRegistryValues;
    }
    return QueryRoutine(RelativeTo,
                        Path,
                        QueryTable,
                        Context,
                        Environment);
}
#endif // 0

} // extern "C"
