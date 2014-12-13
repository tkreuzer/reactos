
#pragma once

#include <ntoskrnl.h>

#include <Ex/Ex.hpp>
#include <Se/Se.hpp>

#include "Ob.hpp"
#include "Object.hpp"
#include "ObjectType.hpp"

FORCEINLINE
VOID
_ExInitializePushLock(
    _Out_ PEX_PUSH_LOCK Lock)
{
    *(PULONG_PTR)Lock = 0;
}
#define ExInitializePushLock _ExInitializePushLock

