
#include "Obp.hpp"

#include "Ke/Ke.hpp"

extern "C" {

typedef struct _DEVICE_MAP *PDEVICE_MAP;

KGUARDED_MUTEX ObpDeviceMapLock;
PDEVICE_MAP ObSystemDeviceMap;

} // extern "C"

extern "C"
VOID
NTAPI
ObDereferenceDeviceMap (
    _In_ PEPROCESS Process)
{
    __debugbreak();
}

extern "C"
VOID
NTAPI
ObInheritDeviceMap (
    _In_ PEPROCESS Parent,
    _In_ PEPROCESS Process)
{
    __debugbreak();
}

extern "C"
VOID
NTAPI
ObQueryDeviceMapInformation (
    _In_ PEPROCESS Process,
    _Out_ PPROCESS_DEVICEMAP_INFORMATION DeviceMapInfo)
{
    __debugbreak();
}

extern "C"
NTSTATUS
NTAPI
ObIsDosDeviceLocallyMapped(
    _In_ ULONG Index,
    _Out_ PUCHAR DosDeviceState)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

