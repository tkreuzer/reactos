/*!

    \file VirtualMemory.hpp

    \brief Header for VirtualMemory.cpp

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"

namespace Mm {

_Must_inspect_result_
_At_(*BaseAddress, __drv_allocatesMem(Mem))
__kernel_entry
NTSTATUS
AllocateVirtualMemory (
    _Inout_ _Outptr_result_buffer_(*RegionSize) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect);

}; // namespace Mm

