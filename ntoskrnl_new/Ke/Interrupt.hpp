
#pragma once

#include "Kep.hpp"

typedef enum _KINTERRUPT_DISPATCH_STATUS
{
    IsrNotDispatched = 0,
    IsrDispatchDeferred = 1,
    IsrDispatched = 2
} KINTERRUPT_DISPATCH_STATUS, *PKINTERRUPT_DISPATCH_STATUS;

typedef
_Function_class_(NMI_CALLBACK)
_IRQL_requires_same_
BOOLEAN
NTAPI
NMI_CALLBACK(
    _In_opt_ PVOID Context,
    _In_ BOOLEAN Handled);
typedef NMI_CALLBACK *PNMI_CALLBACK;

typedef
_Function_class_(KSYNCHRONIZE_ROUTINE)
_IRQL_requires_(HIGH_LEVEL)
_IRQL_requires_same_
BOOLEAN
NTAPI
KSYNCHRONIZE_ROUTINE (
    _In_opt_ PVOID SynchronizeContext);
typedef KSYNCHRONIZE_ROUTINE *PKSYNCHRONIZE_ROUTINE;

