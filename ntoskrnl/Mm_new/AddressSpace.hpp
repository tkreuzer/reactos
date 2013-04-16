
#pragma once

#include "ntosbase.h"
#include "ndk/pstypes.h"

namespace Mm {

enum ADDRESS_SPACE_TYPE;

class ADDRESS_SPACE
{
private:
    MMSUPPORT m_Support;
    /// alternatively we can add additional parts from EPROCESS here and address
    /// the vad table directly and include it into the system / session address space


    VOID
    Initialize (
        VOID)
    {
    }

    inline
    ADDRESS_SPACE_TYPE
    GetAddressSpaceType ();

    inline
    class VAD_TABLE*
    GetVadTable ();

    friend class MEMORY_MANAGER;

public:


};

typedef ADDRESS_SPACE* PADDRESS_SPACE;

extern VAD_TABLE g_KernelVadTable;
extern PADDRESS_SPACE g_KernelAddressSpace;
extern ADDRESS_SPACE g_GlobalSystemAddressSpace;

inline
PADDRESS_SPACE
GetProcessAddressSpace (
    PEPROCESS Process)
{
    return reinterpret_cast<PADDRESS_SPACE>(&Process->Vm);
}

inline
PADDRESS_SPACE
GetProcessSessionAddressSpace (
    PEPROCESS Process)
{
    //PMM_SESSION_SPACE SessionSpace = Process->Session;
    //return reinterpret_cast<PADDRESS_SPACE>(&SessionSpace->Vm);
    return 0;
}

}; // namespace Mm
