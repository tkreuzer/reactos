
#include "Queue.hpp"

extern "C" {

// ntifs.h / ntosp.h
VOID
NTAPI
KeInitializeQueue (
    _Out_ PRKQUEUE Queue,
    _In_ ULONG Count)
{
    __debugbreak();
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeReadStateQueue (
    _In_ PRKQUEUE Queue)
{
    __debugbreak();
    return 0;
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeInsertQueue (
    _Inout_ PRKQUEUE Queue,
    _Inout_ PLIST_ENTRY Entry)
{
    __debugbreak();
    return 0;
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeInsertHeadQueue (
    _Inout_ PRKQUEUE Queue,
    _Inout_ PLIST_ENTRY Entry)
{
    __debugbreak();
    return 0;
}

// ntifs.h / ntosp.h
_When_((Timeout==NULL || Timeout->QuadPart!=0), _IRQL_requires_max_(APC_LEVEL))
_When_((Timeout!=NULL && Timeout->QuadPart==0), _IRQL_requires_max_(DISPATCH_LEVEL))
PLIST_ENTRY
NTAPI
KeRemoveQueue (
    _Inout_ PRKQUEUE Queue,
    _In_ KPROCESSOR_MODE WaitMode,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    __debugbreak();
    return NULL;
}

// ntifs.h / ntosp.h
_When_((Timeout==NULL || Timeout->QuadPart!=0), _IRQL_requires_max_(APC_LEVEL))
_When_((Timeout!=NULL && Timeout->QuadPart==0), _IRQL_requires_max_(DISPATCH_LEVEL))
ULONG
NTAPI
KeRemoveQueueEx (
    _Inout_ PKQUEUE Queue,
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_writes_to_(Count, return) PLIST_ENTRY *EntryArray,
    _In_ ULONG Count)
{
    __debugbreak();
    return 0;
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
PLIST_ENTRY
NTAPI
KeRundownQueue (
    _Inout_ PRKQUEUE Queue)
{
    __debugbreak();
    return NULL;
}


}; // extern "C"
