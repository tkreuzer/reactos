

#include "AddressSpace.hpp"
#include "VadObject.hpp"
#include "VadTable.hpp"
#include "KernelVad.hpp"
//#include "amd64/MachineDependent.hpp"
#include _ARCH_RELATIVE_(MachineDependent.hpp)
#include <ndk/exfuncs.h>

namespace Mm {

PADDRESS_SPACE g_SystemProcessAddressSpace;
ADDRESS_SPACE g_KernelAddressSpace;
VAD_TABLE g_KernelVadTable;

inline
ADDRESS_SPACE::ADDRESS_SPACE_TYPE
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

    /* Initialize the VAD table */
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

KIRQL
ADDRESS_SPACE::AcquireAddressCreationLock (
    VOID)
{
    ADDRESS_SPACE_TYPE AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        KeEnterGuardedRegion();
        ExAcquirePushLockExclusive(&m_Support.WorkingSetMutex);
        return 0;
    }
    else if (AddressSpaceType == SessionAddressSpace)
    {
        __debugbreak();
        return 0;
    }
    else
    {
        return KeAcquireQueuedSpinLock(LockQueueSystemSpaceLock);
    }
}

VOID
ADDRESS_SPACE::ReleaseAddressCreationLock (
    KIRQL OldIrql)
{
    ADDRESS_SPACE_TYPE AddressSpaceType = GetAddressSpaceType();

    if (AddressSpaceType == ProcessAddressSpace)
    {
        ExReleasePushLock(&m_Support.WorkingSetMutex);
        KeLeaveGuardedRegion();
    }
    else if (AddressSpaceType == SessionAddressSpace)
    {
        __debugbreak();
    }
    else
    {
        KeReleaseQueuedSpinLock(LockQueueSystemSpaceLock, OldIrql);
    }
}

NTSTATUS
ADDRESS_SPACE::ReserveVirtualMemory (
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR NumberOfPages)
{
    ADDRESS_SPACE_TYPE AddressSpaceType = GetAddressSpaceType();
    ULONG_PTR LowestStartingVpn, HighestEndingVpn;
    PVAD_TABLE VadTable;
    PVAD_OBJECT VadObject;
    NTSTATUS Status;

    if (AddressSpaceType == ProcessAddressSpace)
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
        VadTable = reinterpret_cast<class VAD_TABLE*>(&Process->VadRoot);
        LowestStartingVpn = AddressToVpn(MmSystemRangeStart);
        HighestEndingVpn = AddressToVpn(MmHighestSystemAddress);
        UNIMPLEMENTED;
    }
    else if (AddressSpaceType == SessionAddressSpace)
    {
        //PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
        VadTable = 0; //reinterpret_cast<class VAD_TABLE*>(&SessionSpace->VadRoot);
        LowestStartingVpn = 0;//AddressToVpn(MmSessionSpaceStart);
        HighestEndingVpn = 0;//AddressToVpn(MmSessionSpaceEnd);
        UNIMPLEMENTED;
    }
    else
    {
        VadTable = &g_KernelVadTable;
        LowestStartingVpn = AddressToVpn(MmSystemRangeStart);
        HighestEndingVpn = AddressToVpn(MmHighestSystemAddress);

        Status = KERNEL_VAD::CreateInstance((KERNEL_VAD**)&VadObject);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }

    if (*BaseAddress != NULL)
    {
        UNIMPLEMENTED;
    }
    else
    {
        Status = VadTable->InsertVadObject(VadObject,
                                           NumberOfPages,
                                           LowestStartingVpn,
                                           HighestEndingVpn,
                                           1,
                                           FALSE);
    }

    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to insert VAD object into VAD table: %x\n", Status);
        VadObject->Release();
        return Status;
    }

    *BaseAddress = VadObject->GetBaseAddress();

    return STATUS_SUCCESS;
}

}; // namespace Mm

