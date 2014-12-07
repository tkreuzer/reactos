
#include "SysInfo.hpp"

extern "C" {

//@ stdcall RtlGetSetBootStatusData(ptr long long ptr long long)
//@ stdcall RtlLockBootStatusData(ptr)
//@ stdcall RtlUnlockBootStatusData(ptr)

typedef struct _RTL_MODULE_INFO
{
    PVOID ModuleBaseAddress;
    SIZE_T ModuleSize;
    USHORT ModuleNameOffset;
    CHAR ModuleName[256];
} RTL_MODULE_INFO, *PRTL_MODULE_INFO;

// https://github.com/GPUOpen-Tools/CxlCommon/blob/master/Src/WinDriverStackWalker/Src/StackWalker.cpp
// Buffer is PRTL_MODULE_INFO or PPVOID (BaseAddress only)
NTSTATUS
NTAPI
RtlQueryModuleInformation (
    _Inout_ PULONG BufferSize,
    _In_ ULONG ElementSize,
    _Out_ PVOID Buffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlGetEnabledExtendedFeatures
ULONG64 // [XSTATE_MASK_ULONG64]
NTAPI
RtlGetEnabledExtendedFeatures (
    ULONG64 /* [XSTATE_MASK_ULONG64] */ FeatureMask)
{
    __debugbreak();
    return 0;
}

ULONG
NTAPI
RtlGetNtGlobalFlags (
    VOID)
{
    __debugbreak();
    return 0;//NtGlobalFlag;
}

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlQueryElevationFlags (
    _Out_ PRTL_ELEVATION_FLAGS Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlQueryPackageIdentity (
    _In_ PVOID TokenObject,
    _Out_writes_bytes_to_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ PBOOLEAN Packaged)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

ULONG
NTAPI
RtlQueryValidationRunlevel (
    _In_opt_ PCUNICODE_STRING ComponentName)
{
    __debugbreak();
    return 0;
}

#if 0 // not exported from ntoskrnl

NTSTATUS
NTAPI
RtlQueryPackageIdentityEx (
    _In_ PVOID TokenObject,
    _Out_writes_bytes_to_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ LPGUID DynamicId,
    _Out_opt_ PULONG64 Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlQueryPackageClaims (
    _In_ PVOID TokenObject,
    _Out_writes_bytes_to_opt_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_opt_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ LPGUID DynamicId,
    _Out_opt_ PPS_PKG_CLAIM PkgClaim)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#endif // 0

} // extern "C"
