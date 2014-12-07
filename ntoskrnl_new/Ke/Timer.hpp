
#pragma once

#include "Kep.hpp"

typedef
VOID
(NTAPI *PTIMER_APC_ROUTINE) (
    _In_ PVOID TimerContext,
    _In_ ULONG TimerLowValue,
    _In_ LONG TimerHighValue);


