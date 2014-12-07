
#include "DeviceQueue.hpp"

extern "C" {

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
KeInitializeDeviceQueue (
    _Out_ PKDEVICE_QUEUE DeviceQueue)
{
    __debugbreak();
}

// wdm.h / ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeInsertByKeyDeviceQueue (
    _Inout_ PKDEVICE_QUEUE DeviceQueue,
    _Inout_ PKDEVICE_QUEUE_ENTRY DeviceQueueEntry,
    _In_ ULONG SortKey)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeInsertDeviceQueue (
    _Inout_ PKDEVICE_QUEUE DeviceQueue,
    _Inout_ PKDEVICE_QUEUE_ENTRY DeviceQueueEntry)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
PKDEVICE_QUEUE_ENTRY
NTAPI
KeRemoveByKeyDeviceQueue (
    _Inout_ PKDEVICE_QUEUE DeviceQueue,
    _In_ ULONG SortKey)
{
    __debugbreak();
    return NULL;
}

// wdm.h / ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
PKDEVICE_QUEUE_ENTRY
NTAPI
KeRemoveByKeyDeviceQueueIfBusy (
    _Inout_ PKDEVICE_QUEUE DeviceQueue,
    _In_ ULONG SortKey)
{
    __debugbreak();
    return NULL;
}

// wdm.h / ntosp.h
_IRQL_requires_(DISPATCH_LEVEL)
PKDEVICE_QUEUE_ENTRY
NTAPI
KeRemoveDeviceQueue (
    _Inout_ PKDEVICE_QUEUE DeviceQueue)
{
    __debugbreak();
    return NULL;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
KeRemoveEntryDeviceQueue (
    _Inout_ PKDEVICE_QUEUE DeviceQueue,
    _Inout_ PKDEVICE_QUEUE_ENTRY DeviceQueueEntry)
{
    __debugbreak();
    return FALSE;
}


}; // extern "C"
