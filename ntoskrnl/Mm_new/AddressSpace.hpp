
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
        VOID);

    inline
    ADDRESS_SPACE_TYPE
    GetAddressSpaceType ();


    friend class MEMORY_MANAGER;

public:

    class VAD_TABLE*
    GetVadTable ();

    VOID
    AcquireWorkingSetLock (
        VOID);

    VOID
    ReleaseWorkingSetLock (
        VOID);

};

typedef ADDRESS_SPACE* PADDRESS_SPACE;

extern PADDRESS_SPACE g_SystemProcessAddressSpace;
extern ADDRESS_SPACE g_KernelAddressSpace;
extern VAD_TABLE g_KernelVadTable;

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

inline
PADDRESS_SPACE
GetAddressSpaceForAddress (
    _In_ PVOID Address)
{
    if (Address <= MmHighestUserAddress)
        return GetProcessAddressSpace(PsGetCurrentProcess());
    //else if ((Address >= MmSessionSpaceStart) && (Address <= MmSessionSpaceStart))
    //    return GetProcessSessionAddressSpace(PsGetCurrentProcess());
    else
        return &g_KernelAddressSpace;
}

}; // namespace Mm
