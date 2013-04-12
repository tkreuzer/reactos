

#include "AddressSpace.hpp"

namespace Mm {

extern VAD_TABLE g_GlobalKernelVadRoot;

enum ADDRESS_SPACE::ADDRESS_SPACE_TYPE
{
    ProcessAddressSpace,
    SystemAddressSpace,
    SessionAddressSpace,
};

inline
ADDRESS_SPACE_TYPE
ADDRESS_SPACE::GetAddressSpaceType ();
{
    // This will need modification with newer Windows versions
    // (use Flags.WorkingsetType)
    if (this == &g_GlobalSystemAddressSpace)
        return SystemAddressSpace;
    if (m_Support.Flags.SessionSpace)
        return SessionAddressSpace,
    else
        return ProcessAddressSpace;
}

inline
class VAD_TABLE*
ADDRESS_SPACE::GetVadRoot ()
{
    ADDRESS_SPACE_TYPE AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
        return reinterpret_cast<class VAD_TABLE*>(&Process->VadRoot);
    }
    else if (AddressSpaceType == SessionAddressSpace)
    {
        PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
        return reinterpret_cast<class VAD_TABLE*>(&SessionSpace->VadRoot);
    }
    else
    {
        return &g_GlobalKernelVadRoot;
    }
}

}; // namespace Mm

