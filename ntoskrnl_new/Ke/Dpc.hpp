
#pragma once

#include "Kep.hpp"

typedef enum _KDPC_IMPORTANCE
{
    LowImportance,
    MediumImportance,
    HighImportance,
    MediumHighImportance
} KDPC_IMPORTANCE;

typedef struct _KDPC *PRKDPC;
typedef struct _KDPC_WATCHDOG_INFORMATION *PKDPC_WATCHDOG_INFORMATION;

_Function_class_(KDEFERRED_ROUTINE)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
VOID
NTAPI
KDEFERRED_ROUTINE (
    _In_ struct _KDPC *Dpc,
    _In_opt_ PVOID DeferredContext,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2);
typedef KDEFERRED_ROUTINE *PKDEFERRED_ROUTINE;

