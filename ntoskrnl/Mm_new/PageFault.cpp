/*!

    \file PageFault.cpp

    \brief Implements the page fault handler

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include "PfnDatabase.hpp"
#include "AddressSpace.hpp"
#include _ARCH_RELATIVE_(PageTables.hpp)
#include <ndk/pstypes.h>

namespace Mm {

static
NTSTATUS
ResolveFaultForPte (
    _Inout_ PPTE PtePointer,
    _In_ PVOID Address,
    _In_ IN KPROCESSOR_MODE Mode,
    _In_ PVOID TrapInformation,
    _In_ UCHAR AccessFlags,
    _Inout_ volatile PFN_NUMBER* PageFrameNumber);

#define PAGE_GLOBAL 0x800


const ULONG MmProtectToWin32Protect[32] =
{
    PAGE_NOACCESS,
    PAGE_READONLY,
    PAGE_EXECUTE,
    PAGE_EXECUTE_READ,
    PAGE_READWRITE,
    PAGE_WRITECOPY,
    PAGE_EXECUTE_READWRITE,
    PAGE_EXECUTE_WRITECOPY,
    PAGE_NOACCESS,
    PAGE_NOCACHE | PAGE_READONLY,
    PAGE_NOCACHE | PAGE_EXECUTE,
    PAGE_NOCACHE | PAGE_EXECUTE_READ,
    PAGE_NOCACHE | PAGE_READWRITE,
    PAGE_NOCACHE | PAGE_WRITECOPY,
    PAGE_NOCACHE | PAGE_EXECUTE_READWRITE,
    PAGE_NOCACHE | PAGE_EXECUTE_WRITECOPY,
    PAGE_NOACCESS,
    PAGE_GUARD | PAGE_READONLY,
    PAGE_GUARD | PAGE_EXECUTE,
    PAGE_GUARD | PAGE_EXECUTE_READ,
    PAGE_GUARD | PAGE_READWRITE,
    PAGE_GUARD | PAGE_WRITECOPY,
    PAGE_GUARD | PAGE_EXECUTE_READWRITE,
    PAGE_GUARD | PAGE_EXECUTE_WRITECOPY,
    PAGE_NOACCESS,
    PAGE_WRITECOMBINE | PAGE_READONLY,
    PAGE_WRITECOMBINE | PAGE_EXECUTE,
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ,
    PAGE_WRITECOMBINE | PAGE_READWRITE,
    PAGE_WRITECOMBINE | PAGE_WRITECOPY,
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READWRITE,
    PAGE_WRITECOMBINE | PAGE_EXECUTE_WRITECOPY
};

inline
NTSTATUS
ResolveDemandZeroFault (
    _In_ PPTE CurrentPteValue,
    _Out_ PPTE NewPteValue,
    _Inout_ volatile PFN_NUMBER* PageFrameNumber)
{
    ULONG Protect;

    /// FIXME
    Protect = MM_READWRITE | MM_GLOBAL;//CurrentPteValue->GetSoftProtection();

    CurrentPteValue->MakeValidPte(*PageFrameNumber, Protect);
    *PageFrameNumber = 0;
    NewPteValue->Erase();

    return STATUS_PAGE_FAULT_DEMAND_ZERO;
}

inline
NTSTATUS
ResolvePrototypePteFault (
    _Inout_ PPTE PtePointer,
    _In_ PVOID Address,
    _In_ IN KPROCESSOR_MODE Mode,
    _In_ PVOID TrapInformation,
    _In_ UCHAR AccessFlags,
    _Inout_ volatile PFN_NUMBER* PageFrameNumber)
{
    PADDRESS_SPACE AddressSpace;
    PPTE PrototypeAddress;
    NTSTATUS Status;

    /* Get the address space (Process/Session/System) */
    AddressSpace = GetAddressSpaceForAddress(Address);

    /* Acquire the corresponding working set lock */
    AddressSpace->AcquireWorkingSetLock();

    /* Get the address of the prototype */
    PrototypeAddress = PtePointer->GetPrototypeAddress();
    if (PrototypeAddress == NULL)
    {
        /* This is not a prototype PTE anymore, unlock and retry */
        AddressSpace->ReleaseWorkingSetLock();
        return STATUS_RETRY;
    }

    /* Check if the prototype is invalid */
    while (!PrototypeAddress->IsValid())
    {
        // reference the VAD -> reference the section
        // AddressSpace->ReferenceVadByAddress(Address)

        /* Release the working set lock while resolving the prototype fault */
        AddressSpace->ReleaseWorkingSetLock();

        /* Recursively resolve the fault on the prototype */
        Status = ResolveFaultForPte(PrototypeAddress,
                                    Address,
                                    Mode,
                                    TrapInformation,
                                    AccessFlags,
                                    PageFrameNumber);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        /* Acquire working set lock again */
        AddressSpace->AcquireWorkingSetLock();

        // dereference the VAD

        /* Check if the original PTE has changed */
        if (PtePointer->GetPrototypeAddress() != PrototypeAddress)
        {
            /* This is not the original PTE anymore, unlock and retry */
            AddressSpace->ReleaseWorkingSetLock();
            return STATUS_RETRY;
        }
    }

    /* Now create a valid PTE from the prototype */
    PtePointer->MakeValidPte(PrototypeAddress->GetPageFrameNumber(),
                             MM_READWRITE | MM_GLOBAL); /// HACK!!!

    AddressSpace->ReleaseWorkingSetLock();

    return STATUS_SUCCESS;
}

inline
NTSTATUS
ResolveCopyOnWriteFault (
    _In_ PPTE PtePointer,
    _In_ PVOID Address,
    _In_ IN KPROCESSOR_MODE Mode,
    _In_ UCHAR AccessFlags)
{
    UNIMPLEMENTED;
    return STATUS_PAGE_FAULT_COPY_ON_WRITE;
}

/*! \fn ResolveFaultForPte
 *
 *  \brief ...
 *
 *  \param [inout] PtePointer -
 *
 *  \param [in] Mode -
 *
 *  \param [in] TrapInformation -
 *
 *  \param [in] AccessFlags -
 *
 *  \param [in] PageFrameNumber -
 *
 *  \return ...
 */
static
NTSTATUS
ResolveFaultForPte (
    _Inout_ PPTE PtePointer,
    _In_ PVOID Address,
    _In_ IN KPROCESSOR_MODE Mode,
    _In_ PVOID TrapInformation,
    _In_ UCHAR AccessFlags,
    _Inout_ volatile PFN_NUMBER* PageFrameNumber)
{
    PTE CurrentPteValue, NewPteValue;
    NTSTATUS Status;

    /* Read the PTE value */
    PtePointer->ReadValue(&CurrentPteValue);

    switch (PtePointer->GetPteType())
    {
    case PteValid:

        /* Check if this was a write instruction */
        if (AccessFlags & PFEC_WRITE)
        {
            /* Check if this is a Copy-On-Write page */
            if (PtePointer->IsCopyOnWrite())
            {
                return ResolveCopyOnWriteFault(PtePointer,
                                               Address,
                                               Mode,
                                               AccessFlags);
            }

            /* Check if the PTE is already writable now */
            if (PtePointer->IsWritable())
            {
                /* The PTE must have been made writable by another thread */
                return STATUS_SUCCESS;
            }

            /* On non-debug versions, we bug-check for kernel mode access */
            if (!DBG && (Mode == KernelMode))
            {
                KeBugCheckEx(ATTEMPTED_WRITE_TO_READONLY_MEMORY,
                             (ULONG_PTR)Address,
                             *(ULONG_PTR*)PtePointer,
                             0,
                             0);
            }

            /* User mode or debug build: dispatch the fault */
            return STATUS_ACCESS_VIOLATION;
        }

        /* Check if this was due to instruction execution */
        if (AccessFlags & PFEC_INSTRUCTION_FETCH)
        {
            /* Check if the PTE is executable */
            if (PtePointer->IsExecutable())
            {
                /* The page fault has been resolved by another thread */
                return STATUS_SUCCESS;
            }

            /* On non-debug versions, we bug-check for kernel mode access */
            if (!DBG && (Mode == KernelMode))
            {
                KeBugCheckEx(ATTEMPTED_EXECUTE_OF_NOEXECUTE_MEMORY,
                             (ULONG_PTR)Address,
                             *(ULONG_PTR*)PtePointer,
                             0,
                             0);
            }

            /* User mode or debug build: dispatch the fault */
            return STATUS_ACCESS_VIOLATION;
        }

        /* A read instruction accessed memory, which is now valid, so the fault
           must have been resolved by a concurrent thread already. */
        return STATUS_SUCCESS;

    case PteDemandZero:

        return ResolveDemandZeroFault(PtePointer,
                                      &NewPteValue,
                                      PageFrameNumber);
        break;

    case PtePrototype:

        return ResolvePrototypePteFault(PtePointer,
                                        Address,
                                        Mode,
                                        TrapInformation,
                                        AccessFlags,
                                        PageFrameNumber);

    case PteTransition:
        Status = STATUS_PAGE_FAULT_TRANSITION;
    case PtePageFile:
        Status = STATUS_PAGE_FAULT_PAGING_FILE;
    // case PteGuardPage:
        Status = STATUS_PAGE_FAULT_GUARD_PAGE;
        __debugbreak();

    case PteNoAccess:
    case PteEmpty:

        /* Both of these are invalid */
        return STATUS_ACCESS_VIOLATION;

    DEFAULT_UNREACHABLE;
    }

    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /// FIXME: this is not safe, we need to lock something
    /// possibly: use a shared lock on the WorkingSetLock + interlocked exchange

    /* Try to exchange the PTE with the new PTE, if it did not change */
    if (!PtePointer->InterlockedCompareExchange(NewPteValue, &CurrentPteValue))
    {
        /* No success, signal the caller that we need to retry */
        return STATUS_RETRY;
    }

    /* The page frame number is in use now */
    *PageFrameNumber = 0;

    return STATUS_SUCCESS;
}

extern "C"
NTSTATUS
NTAPI
MmAccessFault (
    _In_ UCHAR AccessFlags,
    _In_ PVOID Address,
    _In_ KPROCESSOR_MODE Mode,
    _In_ PVOID TrapInformation)
{
    PETHREAD Thread;
    NTSTATUS Status;
    PTE CurrentPteValue, *PtePointer;
    volatile PFN_NUMBER PageFrameNumber;

    /* Quick check for privilege violation */
    if ((Mode != KernelMode) && (Address > MmHighestUserAddress))
    {
        /* Return exception code */
        return STATUS_ACCESS_VIOLATION;
    }

#if MI_PAGING_LEVELS >= 3
    /* Check higher levels of page tables, which are always mapped for all
       committed memory! */
    if (
#if MI_PAGING_LEVELS >= 4
        (!AddressToPxe(Address)->IsValid()) ||
#endif
        (!AddressToPpe(Address)->IsValid()))
    {
        /* On non-debug versions, we bug-check, otherwise dispatch the fault */
        if ((Mode == KernelMode) && !DBG)
        {
            KeBugCheckEx(PAGE_FAULT_IN_NONPAGED_AREA,
                         (ULONG_PTR)Address,
                         (AccessFlags & PFEC_WRITE) ? 1 : 0,
                         (ULONG_PTR)TrapInformation,
                         0);
        }

        /* User mode or debug build: dispatch the fault */
        return STATUS_ACCESS_VIOLATION;
    }
#endif

DbgPrint("Pagefault for Address %p, PdeAddress = %p (%d), PteAddress = %p\n",
         Address, AddressToPde(Address), AddressToPde(Address)->IsValid(),
         AddressToPte(Address));

    /* Get current thread and increment active fault count */
    Thread = PsGetCurrentThread();
    Thread->ActiveFaultCount++;

    /* Allocate a zeroed page. In the majority of cases we will need it */
    PageFrameNumber = g_PfnDatabase.AllocatePage(TRUE); /// FIXME what about waiting?
    NT_ASSERT(PageFrameNumber != 0);

    PtePointer = AddressToPte(Address);

    /* Protect with SEH, since accessing the PTE can cause a page fault, which
       might not get resolved. In that case the fault get's dispatched and we
       catch it here */
    _SEH2_TRY
    {
        do
        {
            /* Read the PTE value */
            PtePointer->ReadValue(&CurrentPteValue);

            Status = ResolveFaultForPte(PtePointer,
                                        Address,
                                        Mode,
                                        TrapInformation,
                                        AccessFlags,
                                        &PageFrameNumber);
        }
        while (Status == STATUS_RETRY);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = _SEH2_GetExceptionCode();
    }
    _SEH2_END;

    /* On non-debug versions, we bug-check for kernel mode access */
    if (!DBG && !NT_SUCCESS(Status) && (Mode == KernelMode))
    {
        KeBugCheckEx(PAGE_FAULT_IN_NONPAGED_AREA,
                     (ULONG_PTR)Address,
                     (AccessFlags & PFEC_WRITE) ? 1 : 0,
                     (ULONG_PTR)TrapInformation,
                     0);
    }

    /* Check if a page needs to be freed */
    if (PageFrameNumber != 0)
    {
        g_PfnDatabase.ReleasePage(PageFrameNumber);
    }

    /* Reset active fault count back to what it was before */
    Thread->ActiveFaultCount--;

    return Status;
}

extern "C" {

BOOLEAN
NTAPI
MmIsRecursiveIoFault (
    VOID)
{
    return PsGetCurrentThread()->ActiveFaultCount > 0;
}

}; // extern "C"
}; // namespace Mm
