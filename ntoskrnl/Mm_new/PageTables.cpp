/*!

    \file PageTables.cpp

    \brief Implements page table related functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include _ARCH_RELATIVE_(PageTables.hpp)
#include _ARCH_RELATIVE_(MachineDependent.hpp)
#include "PfnDatabase.hpp"
#include "CommitCharge.hpp"

#undef MI_PAGING_LEVELS
#define MI_PAGING_LEVELS 4

namespace Mm {



}; // namespace Mm
