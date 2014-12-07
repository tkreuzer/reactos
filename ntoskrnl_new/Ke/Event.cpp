
#include "Event.hpp"

extern "C" {

// wdm.h / ntosp.h
VOID
NTAPI
KeInitializeEvent (
    _Out_ PRKEVENT Event,
    _In_ EVENT_TYPE Type,
    _In_ BOOLEAN State)
{
    __debugbreak();
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeReadStateEvent (
    _In_ PRKEVENT Event)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
KeClearEvent (
    _Inout_ PRKEVENT Event)
{
    __debugbreak();
}

// ntddk.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KePulseEvent (
    _Inout_ PRKEVENT Event,
    _In_ KPRIORITY Increment,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeResetEvent (
    _Inout_ PRKEVENT Event)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
LONG
NTAPI
KeSetEvent (
    _Inout_ PRKEVENT Event,
    _In_ KPRIORITY Increment,
    _In_ _Literal_ BOOLEAN Wait)
{
    __debugbreak();
    return 0;
}

// prototype from reactos
LONG
NTAPI
KeSetEventBoostPriority (
    _Inout_ PRKEVENT Event,
    _Out_ PKTHREAD *WaitingThread)
{
    __debugbreak();
    return 0;
}

}; // extern "C"
