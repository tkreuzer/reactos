
#include "Kep.hpp"

extern "C" {

//#if defined(_M_IX86) || defined(_M_AMD64)

typedef enum _BOUND_CALLBACK_STATUS {
    BoundExceptionContinueSearch = 0,
    BoundExceptionHandled,
    BoundExceptionError,
    BoundExceptionMaximum
} BOUND_CALLBACK_STATUS, *PBOUND_CALLBACK_STATUS;

typedef
_IRQL_requires_same_
BOUND_CALLBACK_STATUS
NTAPI
BOUND_CALLBACK(
    VOID);
typedef BOUND_CALLBACK *PBOUND_CALLBACK;

// wdm.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
KeRegisterBoundCallback (
    _In_ PBOUND_CALLBACK CallbackRoutine)
{
    __debugbreak();
    return NULL;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeDeregisterBoundCallback (
    _In_ PVOID Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//#endif

}; // extern "C"
