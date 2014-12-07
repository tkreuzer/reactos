
#include "Process.hpp"

extern "C" {

// not exported, just in the same way as KeGetCurrentThread
#undef KeGetCurrentProcess
PKPROCESS
NTAPI
KeGetCurrentProcess (
    VOID)
{
    __debugbreak();
    return NULL;
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeAttachProcess (
    _Inout_ PRKPROCESS Process)
{
    __debugbreak();
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeDetachProcess (
    VOID)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
KeIsAttachedProcess (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeStackAttachProcess (
    _Inout_ PRKPROCESS PROCESS,
    _Out_ PRKAPC_STATE ApcState)
{
    __debugbreak();
}

// ntifs.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
KeUnstackDetachProcess (
    _In_ PRKAPC_STATE ApcState)
{
    __debugbreak();
}

// ntosp.h
BOOLEAN
NTAPI
Ke386IoSetAccessProcess (
    _In_ struct _KPROCESS *Process,
    _In_range_(<, IOPM_COUNT) ULONG MapNumber)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"
