

#include "AddressSpace.hpp"
#include "VadTable.hpp"

namespace Mm {

PADDRESS_SPACE g_SystemProcessAddressSpace;
ADDRESS_SPACE g_KernelAddressSpace;
VAD_TABLE g_KernelVadTable;

enum ADDRESS_SPACE_TYPE
{
    ProcessAddressSpace,
    SystemAddressSpace,
    SessionAddressSpace,
};

inline
ADDRESS_SPACE_TYPE
ADDRESS_SPACE::GetAddressSpaceType ()
{
    // This will need modification with newer Windows versions
    // (use Flags.WorkingsetType)
    if (this == &g_KernelAddressSpace)
        return SystemAddressSpace;
    if (m_Support.Flags.SessionSpace)
        return SessionAddressSpace;
    else
        return ProcessAddressSpace;
}

PVAD_TABLE
ADDRESS_SPACE::GetVadTable ()
{
    ADDRESS_SPACE_TYPE AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
        return reinterpret_cast<class VAD_TABLE*>(&Process->VadRoot);
    }
    else if (AddressSpaceType == SessionAddressSpace)
    {
        //PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
        //return reinterpret_cast<class VAD_TABLE*>(&SessionSpace->VadRoot);
        UNIMPLEMENTED;
        return NULL;
    }
    else
    {
        return &g_KernelVadTable;
    }
}

VOID
ADDRESS_SPACE::Initialize (
    VOID)
{
#if 0
    ADDRESS_SPACE_TYPE AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
        KeInitializeGuardedMutex(&Process->AddressCreationLock);
        KeInitializeSpinLock(&Process->HyperSpaceLock);
        Process->Vm.WorkingSetExpansionLinks.Flink = NULL;
        Process->HasAddressSpace = TRUE;
    }
    else if (AddressSpaceType == SessionAddressSpace)
    {
        //PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
    }
    else
    {
        //
    }

    /* Initialize the Addresss Space */
    GetVadTable()->Initialize();
#endif
}

VOID
ADDRESS_SPACE::AcquireWorkingSetLock (
    VOID)
{
    //KeEnterGuardedRegion();
    //ExAcquirePushLockExclusive(&m_Support.WorkingSetMutex);
}

VOID
ADDRESS_SPACE::ReleaseWorkingSetLock (
    VOID)
{
    //ExReleasePushLock(&m_Support.WorkingSetMutex);
    //KeLeaveGuardedRegion();
}


}; // namespace Mm

