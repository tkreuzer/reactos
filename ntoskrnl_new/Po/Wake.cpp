
#include "Po.hpp"

extern "C" {

//@ stub PoInitiateProcessorWake

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
PoGetSystemWake (
    _In_ PIRP Irp)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoSetSystemWake (
    _Inout_ PIRP Irp)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
PoSetFixedWakeSource (
    _In_ ULONG WakeMask)
{
    __debugbreak();
}

} // extern "C"
