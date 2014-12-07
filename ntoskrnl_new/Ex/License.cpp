
#include "Exp.hpp"

extern "C" {

// ntosp.h
typedef enum _LICENSING_TAMPER_STATE
{
    LicensingTamperNone,
    LicensingTamperTrustedStore,
    LicensingTamperServiceStopped,
    LicensingTamperModuleAuthentication,
    LicensingTamperCacheData,
    LicensingTamperOther
} LICENSING_TAMPER_STATE, *PLICENSING_TAMPER_STATE;

_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
ExQueryFastCacheDevLicense (
    VOID)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
ExGetLicenseTamperState (
    _Out_opt_ PLICENSING_TAMPER_STATE LicensingTamperState)
{
    /* Always return FALSE */
    return FALSE;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExSetLicenseTamperState (
    _In_ LICENSING_TAMPER_STATE LicensingTamperState)
{
    /* Don't do anything */
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
ExUpdateLicenseData (
    _In_ ULONG LicenseDataSize,
    _In_reads_bytes_(LicenseDataSize) PVOID LicenseData)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
ExFetchLicenseData (
    _Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
    _In_ ULONG DataSize,
    _Out_ PULONG ResultDataSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
