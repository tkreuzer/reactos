
#pragma once

#include "CcPrivate.hpp"

namespace Cc {

class CACHE_MANAGER
{
private:
    static LIST_ENTRY m_VacbFreeList;
    static LIST_ENTRY m_VacbInUseList;

    VOID
    Initialize (
        VOID);


};




}; // namespace Cc

