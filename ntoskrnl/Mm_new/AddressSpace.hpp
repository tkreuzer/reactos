
#pragma once

#include "ntosbase.h"
#include "ndk/pstypes.h"

namespace Mm {


class ADDRESS_SPACE
{
private:
    MMSUPPORT m_Support;

    VOID
    Initialize (
        VOID)
    {
    }

    inline
    class VAD_TABLE*
    GetVadRoot ()
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
        return reinterpret_cast<class VAD_TABLE*>(&Process->VadRoot);
    }

    friend class MEMORY_MANAGER;

public:


};

typedef ADDRESS_SPACE* PADDRESS_SPACE;

extern PADDRESS_SPACE g_KernelAddressSpace;

inline
PADDRESS_SPACE
GetProcessAddressSpace (
    PEPROCESS Process)
{
    return reinterpret_cast<PADDRESS_SPACE>(&Process->Vm);
}



}; // namespace Mm
