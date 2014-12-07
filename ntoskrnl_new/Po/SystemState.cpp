
#include "Po.hpp"

extern "C" {

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
PoRegisterSystemState (
    _Inout_opt_ PVOID StateHandle,
    _In_ EXECUTION_STATE Flags)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PoUnregisterSystemState (
    _Inout_ PVOID StateHandle)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
PoSetSystemState (
    _In_ EXECUTION_STATE Flags)
{
    __debugbreak();
}

} // extern "C"
