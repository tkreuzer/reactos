/*!

    \file SysLoader.hpp

    \brief Header file for SysLoader.cpp

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"

namespace Mm {

extern "C" {

NTSTATUS
NTAPI
MmLoadSystemImage (
    _In_ PUNICODE_STRING FileName,
    _Reserved_ PUNICODE_STRING NamePrefix,
    _In_opt_ PUNICODE_STRING LoadedName,
    _In_ ULONG Flags,
    _Out_ PVOID *ModuleObject,
    _Out_ PVOID *ImageBaseAddress);

NTSTATUS
NTAPI
MmUnloadSystemImage (
    _In_ PVOID ImageHandle);


}; // extern "C"
}; // namespace Mm

