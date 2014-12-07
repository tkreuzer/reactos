
#include "Exp.hpp"

typedef struct _CALLBACK_OBJECT *PCALLBACK_OBJECT;

_IRQL_requires_same_
_Function_class_(CALLBACK_FUNCTION)
typedef
VOID
NTAPI
CALLBACK_FUNCTION (
    _In_opt_ PVOID CallbackContext,
    _In_opt_ PVOID Argument1,
    _In_opt_ PVOID Argument2);
typedef CALLBACK_FUNCTION *PCALLBACK_FUNCTION;

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
ExCreateCallback (
    _Outptr_ PCALLBACK_OBJECT *CallbackObject,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN Create,
    _In_ BOOLEAN AllowMultipleCallbacks)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
ExRegisterCallback (
    _Inout_ PCALLBACK_OBJECT CallbackObject,
    _In_ PCALLBACK_FUNCTION CallbackFunction,
    _In_opt_ PVOID CallbackContext)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ExUnregisterCallback (
    _Inout_ PVOID CallbackRegistration)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
ExNotifyCallback (
    _In_ PCALLBACK_OBJECT CallbackObject,
    _In_opt_ PVOID Argument1,
    _In_opt_ PVOID Argument2)
{
    __debugbreak();
}

}; // extern "C"
