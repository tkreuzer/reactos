
#pragma once

#include "Kep.hpp"

typedef enum _KSTACK_TYPE
{
    ReserveStackNormal = 0,
    ReserveStackLarge,
    MaximumReserveStacks
} KSTACK_TYPE;

typedef
_IRQL_requires_same_
_Function_class_(EXPAND_STACK_CALLOUT)
VOID
NTAPI
EXPAND_STACK_CALLOUT (
    _In_opt_ PVOID Parameter);
typedef EXPAND_STACK_CALLOUT *PEXPAND_STACK_CALLOUT;

