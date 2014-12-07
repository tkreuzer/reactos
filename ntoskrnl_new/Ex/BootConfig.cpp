#include "Exp.hpp"

extern "C" {

DECLARE_HANDLE(EX_BOOT_DEVICE_HANDLE);

#define EX_BOOT_DEVICE_REGISTRATION_VERSION_1 1
#define EX_BOOT_DEVICE_REGISTRATION_VERSION EX_BOOT_DEVICE_REGISTRATION_VERSION_1

typedef
BOOLEAN
(NTAPI *PEX_IS_BOOT_DEVICE_READY) (
    _In_ struct _DEVICE_OBJECT *PhysicalDeviceObject,
    _In_opt_ PVOID Context);

typedef struct _EX_BOOT_DEVICE_REGISTRATION
{
    ULONG Version;
    ULONG Flags; //reserved; must be 0
    struct _DRIVER_OBJECT *DriverObject; //mandatory
    struct _DEVICE_OBJECT *DeviceObject; //optional
    PEX_IS_BOOT_DEVICE_READY IsBootDeviceReady; //mandatory
    PVOID Context; //optional
} EX_BOOT_DEVICE_REGISTRATION, *PEX_BOOT_DEVICE_REGISTRATION;

NTSTATUS
NTAPI
ExGetFirmwareEnvironmentVariable (
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _Out_writes_bytes_opt_(*ValueLength) PVOID Value,
    _Inout_ PULONG ValueLength,
    _Out_opt_ PULONG Attributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
ExSetFirmwareEnvironmentVariable (
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _In_reads_bytes_opt_(ValueLength) PVOID Value,
    _In_ ULONG ValueLength,
    _In_ ULONG Attributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
ExNotifyBootDeviceRemoval (
    _In_ EX_BOOT_DEVICE_HANDLE Handle)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
ExRegisterBootDevice (
    _In_ PEX_BOOT_DEVICE_REGISTRATION Registration,
    _Out_ EX_BOOT_DEVICE_HANDLE *Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef struct _EX_EXTENSION *PEX_EXTENSION;

NTSTATUS
NTAPI
ExRegisterExtension (
    _Outptr_ PEX_EXTENSION *Extension,
    _In_ ULONG RegistrationVersion,
    _In_ PVOID RegistrationInfo)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
ExUnregisterExtension (
    _Inout_ PEX_EXTENSION Extension)
{
    __debugbreak();
}

// wdm.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
ExIsManufacturingModeEnabled (
    VOID)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"
