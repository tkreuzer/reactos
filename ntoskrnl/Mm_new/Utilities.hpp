/*!

    \file Utilities.hpp

    \brief Header for Utilities.cpp

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"

/// HACK HACK HACK HACK
VOID
KeFlushMultipleTb (
    _In_ PVOID* AddressArray,
    _In_ ULONG AddressCount);

VOID
KeFlushRangeTb (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR NumberOfPages);

VOID
KeFlushProcessTb ();

namespace Mm {

ULONG
ConvertProtect (
    _In_ ULONG Win32Protect);

ULONG
ConvertProtectAndCaching (
    _In_ ULONG Win32Protect,
    _In_ MEMORY_CACHING_TYPE CachingType);

ULONG
ConvertProtectToWin32 (
    _In_ ULONG Protect);

}; // namespace Mm
