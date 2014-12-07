
#include "Semaphore.hpp"

extern "C" {

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
KeInitializeSemaphore (
    _Out_ PRKSEMAPHORE Semaphore,
    _In_ LONG Count,
    _In_ LONG Limit)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
LONG
NTAPI
KeReadStateSemaphore (
    _In_ PRKSEMAPHORE Semaphore)
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
KeReleaseSemaphore (
    _Inout_ PRKSEMAPHORE Semaphore,
    _In_ KPRIORITY Increment,
    _In_ LONG Adjustment,
    _In_ _Literal_ BOOLEAN Wait)
{
    __debugbreak();
    return 0;
}

}; // extern "C"
