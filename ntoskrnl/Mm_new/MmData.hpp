/*!

    \file MmData.hpp

    \brief Header for MmData.cpp

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"

extern "C" ULONG_PTR MmNumberOfPhysicalPages;
extern "C" ULONG_PTR MmAvailablePages;
extern "C" struct _MMPFN* MmPfnDatabase;
extern "C" SIZE_T MmSizeOfPfnDatabase;
extern "C" PFN_NUMBER MmNumberOfPhysicalPages;
extern "C" PVOID MmNonPagedPoolStart;
extern "C" SIZE_T MmSizeOfNonPagedPoolInBytes;
extern "C" PVOID MmPagedPoolStart;
extern "C" PVOID MmPagedPoolEnd;
extern "C" SIZE_T MmSizeOfPagedPoolInBytes;
extern "C" SIZE_T MmMaximumNonPagedPoolInBytes;
