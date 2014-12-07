
#include "Version.hpp"

extern "C" {

// undocumented
NTSTATUS
NTAPI
RtlCheckPortableOperatingSystem (
    PVOID PortableOperatingSystem)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
RtlSetPortableOperatingSystem (
    PVOID PortableOperatingSystem)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlGetVersion (
    _Out_
    _At_(lpVersionInformation->dwOSVersionInfoSize, _Pre_ _Valid_)
    _When_(lpVersionInformation->dwOSVersionInfoSize == sizeof(RTL_OSVERSIONINFOEXW),
        _At_((PRTL_OSVERSIONINFOEXW)lpVersionInformation, _Out_))
        PRTL_OSVERSIONINFOW lpVersionInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlVerifyVersionInfo (
    _In_ PRTL_OSVERSIONINFOEXW VersionInfo,
    _In_ ULONG TypeMask,
    _In_ ULONGLONG ConditionMask)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
RtlGetProductInfo (
    _In_ ULONG OSMajorVersion,
    _In_ ULONG OSMinorVersion,
    _In_ ULONG SpMajorVersion,
    _In_ ULONG SpMinorVersion,
    _Out_ PULONG ReturnedProductType)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
RtlIsNtDdiVersionAvailable (
    _In_ ULONG Version)
{
    __debugbreak();
    return FALSE;
}

BOOLEAN
NTAPI
RtlIsServicePackVersionInstalled (
    _In_ ULONG Version)
{
    __debugbreak();
    return FALSE;
}

ULONGLONG
NTAPI
VerSetConditionMask(
    _In_ ULONGLONG ConditionMask,
    _In_ ULONG TypeMask,
    _In_ UCHAR Condition)
{
    __debugbreak();
    return 0;
}

#if 0

OS_DEPLOYEMENT_STATE_VALUES
NTAPI
RtlOsDeploymentState(
    _In_ ULONG Flags)
{
    __debugbreak();
    return OS_DEPLOYMENT_STANDARD;
}

#endif // 0

} // extern "C"
