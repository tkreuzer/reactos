
#pragma once

#include <ntoskrnl.h>

#include <Ex/Ex.hpp>
#include <Se/Se.hpp>

#include "Ob.hpp"
#include "Object.hpp"
#include "ObjectType.hpp"
#include "Directory.hpp"
#include "FastRef.hpp"

extern "C"
ULONG
NTAPI
MmGetSessionId (
    _In_ PEPROCESS Process);

