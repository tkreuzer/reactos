/*!

    \file AddressSpace.cpp

    \brief Implements the ADDRESS_SPACE class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "AddressSpace.hpp"
#include "VadObject.hpp"
#include "VadTable.hpp"
#include "KernelVad.hpp"
#include _ARCH_RELATIVE_(MachineDependent.hpp)
#include <ndk/exfuncs.h>

/*

- After return from a function releasing virtual memory, the region must be available again
- A releasing function must remove the VAD object AND unmap all pages from it,
  Dereferencing alone is not sufficient!
-

*/

namespace Mm {

PADDRESS_SPACE g_SystemProcessAddressSpace;
ADDRESS_SPACE g_KernelAddressSpace;


/*! \fn ADDRESS_SPACE::GetAddressSpaceType
 *
 *  \brief Returns the type of address space
 *
 *  \return One of ProcessAddressSpace, SessionAddressSpace, KernelAddressSpace
 *
 *  \todo This will need modification with newer Windows versions
 *        (use Flags.WorkingsetType)
 */
inline
ADDRESS_SPACE::ADDRESS_SPACE_TYPE
ADDRESS_SPACE::GetAddressSpaceType ()
{
    /* Check if this is the kernel address space */
    if (this == &g_KernelAddressSpace)
        return SystemAddressSpace;

    /* Check if it's session address space */
    if (m_Support.Flags.SessionSpace)
        return SessionAddressSpace;

    /* Must be process address space */
    return ProcessAddressSpace;
}

/*! \fn ADDRESS_SPACE::GetVadTable
 *
 *  \brief Returns a pointer to the VAD table belonging to this address space.
 *
 *  \return Pointer to the VAD_TABLE object belonging to this address space.
 */
PVAD_TABLE
ADDRESS_SPACE::GetVadTable ()
{
    ADDRESS_SPACE_TYPE AddressSpaceType;

    /* Get the address space type and check if it's process address space */
    AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        /* The VAD table is in the containing EPROCESS structure */
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
        return reinterpret_cast<class VAD_TABLE*>(&Process->VadRoot);
    }

    /* Otherwise check if it's session address space */
    if (AddressSpaceType == SessionAddressSpace)
    {
        //PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
        //return reinterpret_cast<class VAD_TABLE*>(&SessionSpace->VadRoot);
        UNIMPLEMENTED;
        return NULL;
    }

    /* Must be the kernel address space */
    NT_ASSERT(this == &g_KernelAddressSpace);
    return &g_KernelVadTable;
}

/*! \fn ADDRESS_SPACE::Initialize
 *
 *  \brief Initializes the address space
 */
VOID
ADDRESS_SPACE::Initialize (
    VOID)
{
    ADDRESS_SPACE_TYPE AddressSpaceType;
    BOOLEAN KernelMode;

    /* Get the address space type and check if it's process address space */
    AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);

        /* Initialize some fields in the containing EPROCESS */
        KeInitializeGuardedMutex(&Process->AddressCreationLock);
        KeInitializeSpinLock(&Process->HyperSpaceLock);
        Process->Vm.WorkingSetExpansionLinks.Flink = NULL;
        Process->HasAddressSpace = TRUE;
        KernelMode = FALSE;
    }

    /* Otherwise check if it's session address space */
    else if (AddressSpaceType == SessionAddressSpace)
    {
        //PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
        UNIMPLEMENTED_DBGBREAK;
        KernelMode = TRUE;
    }
    else
    {
        //
        KernelMode = TRUE;
    }

    /* Initialize the VAD table */
    GetVadTable()->Initialize(KernelMode);
}

/*! \fn ADDRESS_SPACE::AcquireWorkingSetLock
 *
 *  \brief Acquires the workingset lock
 */
VOID
ADDRESS_SPACE::AcquireWorkingSetLock (
    VOID)
{
    //KeEnterGuardedRegion();
    //ExAcquirePushLockExclusive(&m_Support.WorkingSetMutex);
}

/*! \fn ADDRESS_SPACE::ReleaseWorkingSetLock
 *
 *  \brief Releases the workingset lock
 */
VOID
ADDRESS_SPACE::ReleaseWorkingSetLock (
    VOID)
{
    //ExReleasePushLock(&m_Support.WorkingSetMutex);
    //KeLeaveGuardedRegion();
}

/*! \fn ADDRESS_SPACE::AcquireAddressCreationLock
 *
 *  \brief Acqires the address-creation lock
 *
 *  \return The previous IRQL (Only used for KernelAddressSpace) or 0.
 */
KIRQL
ADDRESS_SPACE::AcquireAddressCreationLock (
    VOID)
{
    ADDRESS_SPACE_TYPE AddressSpaceType;

    /* Get the address space type and check if it's process address space */
    AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
        KeEnterGuardedRegion();
        ExAcquirePushLockExclusive(&Process->AddressCreationLock);
#else
        KeAcquireGuardedMutex(&Process->AddressCreationLock);
#endif
        return 0;
    }

    /* Otherwise check if it's session address space */
    if (AddressSpaceType == SessionAddressSpace)
    {
        //PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
        UNIMPLEMENTED_DBGBREAK;
        return 0;
    }

    /* Must be the kernel address space */
    NT_ASSERT(this == &g_KernelAddressSpace);
    return KeAcquireQueuedSpinLock(LockQueueSystemSpaceLock);
}

/*! \fn ADDRESS_SPACE::ReleaseAddressCreationLock
 *
 *  \brief Releases the address-creation lock
 *
 *  \param [in] OldIrql - The IRQL value returned by AcquireAddressCreationLock
 */
VOID
ADDRESS_SPACE::ReleaseAddressCreationLock (
    KIRQL OldIrql)
{
    ADDRESS_SPACE_TYPE AddressSpaceType;

    /* Get the address space type and check if it's process address space */
    AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
        ExReleasePushLock(&Process->AddressCreationLock);
        KeLeaveGuardedRegion();
#else
        KeReleaseGuardedMutex(&Process->AddressCreationLock);
#endif
    }

    /* Otherwise check if it's session address space */
    else if (AddressSpaceType == SessionAddressSpace)
    {
        UNIMPLEMENTED_DBGBREAK;
    }
    else
    {
        /* Must be the kernel address space */
        NT_ASSERT(this == &g_KernelAddressSpace);
        KeReleaseQueuedSpinLock(LockQueueSystemSpaceLock, OldIrql);
    }
}

/*! \fn ADDRESS_SPACE::InsertVadObject
 *
 *  \brief Inserts a VAD object into the address space's VAD table, reserving
 *      a region of virtual memory.
 *
 *  \param [inout] VadObject - Pointer to the VAD object to insert.
 *
 *  \param [inout] BaseAddress - Pointer to a variable that contains the base
 *      address of the reserved memory region, or NULL to have the function
 *      select a base address.
 *
 *  \param [in] SizeInPages - The size of the memory to reserve.
 *
 *  \param [in] ZeroBits - The number of high bits that need to be 0 in the
 *      base address.
 *
 *  \param [in] AllocationType - Can be a combination of: MEM_TOP_DOWN
 *
 *  \return STATUS_SUCCESS on success, STATUS_INVALID_PARAMETER if the provided
 *      base address and size don't fit into the address space,
 *      STATUS_CONFLICTING_ADDRESSES when the desired range overlaps with an
 *      already reserved range.
 */
NTSTATUS
ADDRESS_SPACE::InsertVadObject (
    _Inout_ PVAD_OBJECT VadObject,
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR SizeInPages,
    _In_ ULONG_PTR ZeroBits,
    _In_ ULONG AllocationType)
{
    ADDRESS_SPACE_TYPE AddressSpaceType;
    PVAD_TABLE VadTable;
    ULONG_PTR StartingVpn, LowestStartingVpn, HighestEndingVpn, BoundaryPageMultiple;
    NTSTATUS Status;
    KIRQL OldIrql;

    NT_ASSERT(ZeroBits <= 20);

    /* Get the address space type and check if it's process address space */
    AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        /* Get the VAD table from the EPROCESS */
        PEPROCESS Process = CONTAINING_RECORD(&m_Support, EPROCESS, Vm);
        VadTable = reinterpret_cast<class VAD_TABLE*>(&Process->VadRoot);

        /* Calculate allowed VPN range based on ZeroBits */
        LowestStartingVpn = 0x10;
        StartingVpn = (MAXULONG_PTR >> (ZeroBits + PAGE_SHIFT));
        HighestEndingVpn = min(StartingVpn + SizeInPages,
                               AddressToVpn(MmHighestUserAddress));
        BoundaryPageMultiple = 16;
    }
    else if (AddressSpaceType == SessionAddressSpace)
    {
        //PSESSION_SPACE SessionSpace = CONTAINING_RECORD(&m_Support, SESSION_SPACE, Vm);
        VadTable = 0; //reinterpret_cast<class VAD_TABLE*>(&SessionSpace->VadRoot);
        LowestStartingVpn = 0;//AddressToVpn(MmSessionSpaceStart);
        HighestEndingVpn = 0;//AddressToVpn(MmSessionSpaceEnd);
        BoundaryPageMultiple = 1;
        UNIMPLEMENTED_DBGBREAK;
    }
    else
    {
        /* Use the kernel VAD table */
        VadTable = &g_KernelVadTable;

        /* Calculate allowed VPN range */
        LowestStartingVpn = AddressToVpn(MmSystemRangeStart);
        HighestEndingVpn = AddressToVpn(MmHighestSystemAddress);
        BoundaryPageMultiple = 1;
    }

    /* Check if a base address was specified */
    if (*BaseAddress != NULL)
    {
        /* Use the specified base address */
        StartingVpn = AddressToVpn(*BaseAddress);

        /* Check if the range is OK */
        if (((StartingVpn < LowestStartingVpn)) ||
            ((StartingVpn + SizeInPages) > HighestEndingVpn) ||
            ((StartingVpn + SizeInPages) < StartingVpn))
        {
            ERR("Invalid parameters: StartingVpn\n");
            return STATUS_INVALID_PARAMETER;
        }

        /* Acquire address creation lock */
        OldIrql = AcquireAddressCreationLock();

        /* Try to insert the VAD at the corresponding VPN */
        Status = VadTable->InsertVadObjectAtVpn(VadObject,
                                                StartingVpn,
                                                SizeInPages);
    }
    else
    {
        /* Acquire address creation lock */
        OldIrql = AcquireAddressCreationLock();

        /* Insert the VAD into the VAD table */
        Status = VadTable->InsertVadObject(VadObject,
                                           SizeInPages,
                                           LowestStartingVpn,
                                           HighestEndingVpn,
                                           BoundaryPageMultiple,
                                           (AllocationType & MEM_TOP_DOWN) != 0);
    }

    /* Release address creation lock */
    ReleaseAddressCreationLock(OldIrql);

    if (!NT_SUCCESS(Status))
    {
        ERR("Could not insert VAD object: 0x%lx\n", Status);
        return Status;
    }

    /* Return the actual base address */
    NT_ASSERT((*BaseAddress == NULL) || (*BaseAddress == VadObject->GetBaseAddress()));
    *BaseAddress = VadObject->GetBaseAddress();

    return STATUS_SUCCESS;
}

/*! \fn ADDRESS_SPACE::ReserveVirtualMemory
 *
 *  \brief ...
 *
 *  \return STATUS_SUCCESS on success, STATUS_INSUFFICIENT_RESOURCES, when
 *      there was not enough free pool memory, STATUS_CONFLICTING_ADDRESSES
 *      when the virtual memory range overlapped with an already reserved
 *      range.
 */
NTSTATUS
ADDRESS_SPACE::ReserveVirtualMemory (
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    ADDRESS_SPACE_TYPE AddressSpaceType;
    PVAD_OBJECT VadObject;
    NTSTATUS Status;

    /* Get the address space type and check if it's process address space */
    AddressSpaceType = GetAddressSpaceType();
    if (AddressSpaceType == ProcessAddressSpace)
    {
        Status = VAD_OBJECT::CreateInstance(&VadObject, Protect);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }
    else
    {
        Status = KERNEL_VAD::CreateInstance((KERNEL_VAD**)&VadObject);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }

    Status = InsertVadObject(VadObject, BaseAddress, NumberOfPages, 0, 0);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to insert VAD object into address space: %x\n", Status);
        VadObject->Release();
        return Status;
    }

    /* Release the VAD object */
    VadObject->Release();

    return STATUS_SUCCESS;
}

/*! \fn ADDRESS_SPACE::ReleaseVirtualMemory
 *
 *  \brief Release a range of reserved virtual memory, that was previously
 *      reserved through a call to ADDRESS_SPACE::ReserveVirtualMemory.
 *
 *  \param [in] BaseAddress - Pointer to the beginning of the reserved range.
 */
VOID
ADDRESS_SPACE::ReleaseVirtualMemory (
    _In_ PVOID BaseAddress)
{
    PVAD_TABLE VadTable;
    PVAD_OBJECT VadObject;
    KIRQL OldIrql;

    /* Get the VAD table */
    VadTable = GetVadTable();

    /* Acquire address creation lock */
    OldIrql = AcquireAddressCreationLock();

    /* Get the VAD object for this allocation */
    VadObject = VadTable->GetVadObjectByAddress(BaseAddress);
    NT_ASSERT(VadObject && VadObject->GetBaseAddress() == BaseAddress);

    /* Remove the VAD object from the table */
    VadTable->RemoveVadObject(VadObject);

    /* Release address creation lock */
    ReleaseAddressCreationLock(OldIrql);

    /* Release the VAD object */
    VadObject->Release();
}

/*! \fn ADDRESS_SPACE::ReferenceVadObjectByAddress
 *
 *  \brief Searches for a VAD object in the VAD tree of the address space that
 *      corresponds to a given address and references it.
 *
 *  \param [in] Address - Address inside the range represented by the VAD object
 *
 *  \param [in] AllowHigherVads - Specifies, whether the next higher VAD object
 *      with an address above the given address should be returned, if no VAD
 *      object corresponds to the given address itself.
 *
 *  \return A Pointer to the referenced VAD object, or NULL, if none was found.
 */
PVAD_OBJECT
ADDRESS_SPACE::ReferenceVadObjectByAddress (
    _In_ PVOID Address,
    _In_ BOOLEAN AllowHigherVads)
{
    PVAD_TABLE VadTable;
    PVAD_OBJECT VadObject;
    KIRQL OldIrql;

    /* Get the VAD table */
    VadTable = GetVadTable();

    /* Acquire address creation lock */
    OldIrql = AcquireAddressCreationLock();

    /* Get the VAD object for this allocation */
    VadObject = VadTable->GetVadObjectByAddress(Address);
    if (VadObject != NULL)
    {
        /* Check if this VAD is what we want */
        if (AllowHigherVads || (VadObject->GetBaseAddress() <= Address))
        {
            VadObject->AddRef();
        }
        else
        {
            VadObject = NULL;
        }
    }

    /* Release address creation lock */
    ReleaseAddressCreationLock(OldIrql);

    return VadObject;
}

/*! \fn ReserveKernelMemory
 *
 *  \brief ...
 *
 *  \return ...
 */
PVOID
ReserveKernelMemory (
    SIZE_T Size)
{
    KERNEL_VAD* VadObject;
    NTSTATUS Status;

    /* Allocate a new kernel VAD */
    Status = KERNEL_VAD::CreateInstance(&VadObject);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to allocate a KERNEL_VAD\n");
        return NULL;
    }

    /* Insert the kernel VAD */
    Status = g_KernelVadTable.InsertVadObject(VadObject,
                                              BYTES_TO_PAGES(Size),
                                              AddressToVpn(MmSystemRangeStart),
                                              AddressToVpn(MmHighestSystemAddress),
                                              1,
                                              TRUE);

    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to insert VAD object into VAD table: %x\n", Status);
        __debugbreak();
        VadObject->Release();
        return NULL;
    }

    /* Return the base address */
    return VadObject->GetBaseAddress();
}

/*! \fn ReleaseKernelMemory
 *
 *  \brief ...
 *
 *  \return ...
 */
VOID
ReleaseKernelMemory (
    PVOID BaseAddress)
{
    PVAD_OBJECT VadObject;
    KIRQL OldIrql;

    /* Acquire the kernel address creation lock */
    OldIrql = g_KernelAddressSpace.AcquireAddressCreationLock();

    /* Reference the VAD object */
    VadObject = g_KernelAddressSpace.ReferenceVadObjectByAddress(BaseAddress, FALSE);
    NT_ASSERT(VadObject != NULL);
    NT_ASSERT(VadObject->GetBaseAddress() == BaseAddress);

    /* Remove the VAD object from the table */
    g_KernelVadTable.RemoveVadObject(VadObject);

    /* Release address creation lock */
    g_KernelAddressSpace.ReleaseAddressCreationLock(OldIrql);

    VadObject->Release();
}

}; // namespace Mm

