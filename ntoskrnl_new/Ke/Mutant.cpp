
#include "Mutant.hpp"

extern "C" {

VOID
NTAPI
KeInitializeMutex (
    _Out_ PRKMUTEX Mutex,
    _In_ ULONG Level)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeReadStateMutex (
    _In_ PRKMUTEX Mutex)
{
    __debugbreak();
    return 0;
}

/*!
    \note The Wait argument does not provide any synchronization guarantees,
          only a hint to the system that the thread will immediately issue
          a wait operation.
*/
_When_(Wait==0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(Wait==1, _IRQL_requires_max_(APC_LEVEL))
LONG
NTAPI
KeReleaseMutex (
    _Inout_ PRKMUTEX Mutex,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeInitializeMutant (
    _Out_ PRKMUTANT Mutant,
    _In_ BOOLEAN InitialOwner)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeReadStateMutant (
    _In_ PRKMUTANT Mutant)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
KeQueryOwnerMutant (
    _In_ PKMUTANT Mutant,
    _Out_ PCLIENT_ID ClientId)
{
    __debugbreak();
}

/*!
    \note The Wait argument does not provide any synchronization guarantees,
          only a hint to the system that the thread will immediately issue
          a wait operation.
*/
_When_(Wait==0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(Wait==1, _IRQL_requires_max_(APC_LEVEL))
LONG
NTAPI
KeReleaseMutant (
    _Inout_ PRKMUTANT Mutant,
    _In_ KPRIORITY Increment,
    _In_ BOOLEAN Abandoned,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return 0;
}

}; // extern "C"
