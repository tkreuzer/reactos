/*!

    \file Mdl.cpp

    \brief Implements MDL related functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/


#include "Mdl.hpp"
#include "AddressSpace.hpp"
#include "PfnDatabase.hpp"
#include _ARCH_RELATIVE_(PageTables.hpp)
#include <ndk/ketypes.h>
#include <ndk/rtlfuncs.h>

extern "C"
NTSTATUS
NTAPI
MmAccessFault (
    _In_ UCHAR AccessFlags,
    _In_ PVOID Address,
    _In_ KPROCESSOR_MODE Mode,
    _In_ PVOID TrapInformation);

namespace Mm {
extern "C" {

/*! \fn MmSizeOfMdl
 *
 *  \brief ...
 *
 *  \param [in] Base -
 *
 *  \param [in] Length -
 *
 *  \return ...
 */
SIZE_T
NTAPI
MmSizeOfMdl (
    _In_reads_bytes_opt_ (Length) PVOID Base,
    _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return 0;
}

/*! \fn MmAdvanceMdl
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 *
 *  \param [in] NumberOfBytes -
 *
 *  \return ...
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmAdvanceMdl (
    _Inout_ PMDLX Mdl,
    _In_ ULONG NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmAdvanceMdl
 *
 *  \brief ...
 *
 *  \param [in] LowAddress -
 *
 *  \param [in] HighAddress -
 *
 *  \param [in] SkipBytes -
 *
 *  \param [in] TotalBytes -
 *
 *  \param [in] CacheType -
 *
 *  \param [in] Flags -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_ (DISPATCH_LEVEL)
PMDL
NTAPI
MmAllocatePagesForMdlEx (
  _In_ PHYSICAL_ADDRESS LowAddress,
  _In_ PHYSICAL_ADDRESS HighAddress,
  _In_ PHYSICAL_ADDRESS SkipBytes,
  _In_ SIZE_T TotalBytes,
  _In_ MEMORY_CACHING_TYPE CacheType,
  _In_ ULONG Flags)
{
    UNIMPLEMENTED;
    return NULL;
}

/*! \fn MmAllocatePagesForMdl
 *
 *  \brief ...
 *
 *  \param [in] LowAddress -
 *
 *  \param [in] HighAddress -
 *
 *  \param [in] SkipBytes -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PMDL
NTAPI
MmAllocatePagesForMdl (
    _In_ PHYSICAL_ADDRESS LowAddress,
    _In_ PHYSICAL_ADDRESS HighAddress,
    _In_ PHYSICAL_ADDRESS SkipBytes,
    _In_ SIZE_T TotalBytes)
{
    UNIMPLEMENTED;
    return NULL;
}

/*! \fn MmFreePagesFromMdl
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 *
 *  \return ...
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreePagesFromMdl (
    _Inout_ PMDLX Mdl)
{
    if (Mdl->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA)
    {
        MmUnmapLockedPages(Mdl->MappedSystemVa, Mdl);
    }
    UNIMPLEMENTED;
}


/*! \fn MmBuildMdlForNonPagedPool
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmBuildMdlForNonPagedPool (
    _Inout_ PMDLX Mdl)
{
    PPFN_NUMBER CurrentPfn;
    ULONG_PTR NumberOfPages;
    PVOID BaseAddress;
    PPTE CurrentPte;
    PPDE CurrentPde;

    NT_ASSERT(!(Mdl->MdlFlags & (MDL_MAPPED_TO_SYSTEM_VA | MDL_PAGES_LOCKED |
                                 MDL_SOURCE_IS_NONPAGED_POOL | MDL_PARTIAL)));
    NT_ASSERT(Mdl->StartVa != NULL);
    NT_ASSERT(Mdl->ByteCount != 0);
    //NT_ASSERT(MmDeterminePoolType(Mdl->StartVa) == NonPagedPool);

    BaseAddress = AddToPointer(Mdl->StartVa, Mdl->ByteOffset);

    /* Calculate the size in pages */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseAddress, Mdl->ByteCount);

    CurrentPfn = MmGetMdlPfnArray(Mdl);
    CurrentPte = AddressToPte(Mdl->StartVa);

    do
    {
        /* Get the PDE */
        CurrentPde = PteToPde(CurrentPte);

        /* Check if this is a large page allocation */
        if (CurrentPde->IsLargePage())
        {
            /* Get the relative PFN from the large page PDE */
            *CurrentPfn = CurrentPde->GetPageFrameNumber();
            *CurrentPfn += CurrentPte - PdeToPte(CurrentPde);
        }
        else
        {
            /* Get the PFN from the PTE */
            *CurrentPfn = CurrentPte->GetPageFrameNumber();
        }

        /* Next PTE and PFN */
        CurrentPte++;
        CurrentPfn++;
    }
    while (--NumberOfPages > 0);

    Mdl->Process = 0;
    Mdl->MappedSystemVa = BaseAddress;
    Mdl->MdlFlags |= MDL_SOURCE_IS_NONPAGED_POOL;

}

/*! \fn MmCreateMdl
 *
 *  \brief ...
 *
 *  \param [out] Mdl -
 *
 *  \param [in] Base -
 *
 *  \param [in] Length -
 *
 *  \return ...
 */
PMDL
NTAPI
MmCreateMdl (
    _Out_writes_bytes_opt_ (sizeof (MDL) + (sizeof (PFN_NUMBER) * ADDRESS_AND_SIZE_TO_SPAN_PAGES (Base, Length)))
        PMDL Mdl,
    _In_reads_bytes_opt_ (Length) PVOID Base,
    _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return NULL;
}

/*! \fn MmProtectMdlSystemAddress
 *
 *  \brief ...
 *
 *  \param [in] Mdl -
 *
 *  \param [in] NewProtect -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmProtectMdlSystemAddress (
    _In_ PMDLX Mdl,
    _In_ ULONG NewProtect)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmProbeAndLockProcessPages
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 *
 *  \param [in] Process -
 *
 *  \param [in] AccessMode -
 *
 *  \param [in] Operation -
 */
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmProbeAndLockProcessPages (
    _Inout_ PMDL Mdl,
    _In_ PEPROCESS Process,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    KAPC_STATE SavedApcState;
    BOOLEAN Attached = FALSE;

    /* Check if this the current process is requested */
    if ((PKPROCESS)Process != KeGetCurrentThread()->ApcState.Process)
    {
        /* Foreign process, attach to it */
        KeStackAttachProcess((PKPROCESS)Process, &SavedApcState);
        Attached = TRUE;
    }

    /* Use SEH, so we can detach, in case the callee throws an exception */
    _SEH2_TRY
    {
        /* Call the function for the current process */
        MmProbeAndLockPages(Mdl, AccessMode, Operation);
    }
    _SEH2_FINALLY
    {
        /* Detach if required */
        if (Attached)
        {
            KeUnstackDetachProcess(&SavedApcState);
        }
    }
    _SEH2_END;
}

/*! \fn MmProbeAndLockPages
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 *
 *  \param [in] AccessMode -
 *
 *  \param [in] Operation -
 *
 *  \todo Check how Windows behaves when accessing pageable or not mapped memory
 *      while at DISPATCH_LEVEL.
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(Mdl->StartVa + Mdl->ByteOffset,
  _Field_size_bytes_opt_(Mdl->ByteCount))
VOID
NTAPI
MmProbeAndLockPages (
    _Inout_ PMDLX Mdl,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    PPFN_NUMBER CurrentPfn, NextPfnToLock;
    PFN_COUNT PfnCount;
    PVOID StartVa, EndVa, CurrentVa;
    PADDRESS_SPACE AddressSpace;
    PPTE CurrentPte;
    PPDE CurrentPde;
    UCHAR AccessFlags;
    KIRQL CurrentIrql;
    NTSTATUS Status;

    /// \todo charge system commit

    /* Get start and end of the VA range */
    StartVa = AddToPointer(Mdl->StartVa, Mdl->ByteOffset);
    EndVa = AddToPointer(StartVa, Mdl->ByteCount);

    /* Check for invalid VA range */
    if ((EndVa < StartVa) ||
        ((StartVa <= MmHighestUserAddress) && (EndVa > MmHighestUserAddress)) ||
        ((StartVa > MmHighestUserAddress) && (AccessMode != KernelMode)))
    {
        /* This is not allowed, raise access violation */
        RtlRaiseStatus(STATUS_ACCESS_VIOLATION);
    }

    /* Check for user mode addresses */
    if (StartVa < MmHighestUserAddress)
    {
        /* Set the MDL process */
        Mdl->Process = PsGetCurrentProcess();
    }
    else
    {
        /* Set MDL process to NULL */
        Mdl->Process = NULL;
    }

    /* Calculate the access flags based on the operation type */
    AccessFlags = (Operation != IoReadAccess) ? PFEC_WRITE : 0;

    /* First loop to make the pages resident */
    CurrentVa = ALIGN_DOWN_POINTER_BY(StartVa, PAGE_SIZE);
    do
    {
#if 1
        /* Access the page to make it resident */
        *(volatile CHAR*)CurrentVa;

        /* Check if this is write access */
        if (Operation != IoReadAccess)
        {
            /* Do a write as well */
            *(volatile CHAR*)CurrentVa = *(volatile CHAR*)CurrentVa;
        }
#else
        /// This code is problematic, since it requires checking the PDE and PTE
        /// without holding the WS lock. possible solution: lock the WS here, too
        /* Invoke the fault handler to page in the page */
        Status = MmAccessFault(AccessFlags, CurrentVa, AccessMode, NULL);
        if (!NT_SUCCESS(Status))
        {
            RtlRaiseStatus(Status);
            // RaiseAccessViolation(CurrentVa, Operation);
        }
#endif
        /* Go to the next page */
        CurrentVa = AddToPointer(CurrentVa, PAGE_SIZE);
    }
    while (CurrentVa < EndVa);

    CurrentPfn = MmGetMdlPfnArray(Mdl);
    NextPfnToLock = CurrentPfn;
    *CurrentPfn = MAXULONG_PTR;

    /* Check if we are below DISPATCH_LEVEL */
    CurrentIrql = KeGetCurrentIrql();
    NT_ASSERT(CurrentIrql <= DISPATCH_LEVEL);
    if (CurrentIrql < DISPATCH_LEVEL)
    {
        /* Get the address space */
        AddressSpace = GetAddressSpaceForAddress(StartVa);

        /* Lock the working set to prevent paging out */
        AddressSpace->AcquireWorkingSetLock();
    }

    /* Note that we don't use SEH, since if we are below DISPATCH_LEVEL, we own
       the WS lock preventing paging out, so that no exception can happen.
       If we are at DISPATCH_LEVEL accessing pageable memory is illegal. */

    /* Start looping */
    CurrentVa = ALIGN_DOWN_POINTER_BY(StartVa, PAGE_SIZE);
    CurrentPte = AddressToPte(CurrentVa);
    do
    {
        /* Get the current PDE */
        CurrentPde = AddressToPde(CurrentVa);

        /* Check if any paging level is invalid. For pageable addresses
           we must be below DISPATCH_LEVEL and own the WS lock. */
        if (
#if (MI_PAGING_LEVELS == 4)
            (!AddressToPxe(Address)->IsValid()) ||
#endif
#if (MI_PAGING_LEVELS >= 3)
            (!AddressToPpe(Address)->IsValid()) ||
#endif
            (!CurrentPde->IsValid()) ||
///           We probably don't need this
//            (CurrentPde->IsLargePage() &&
//                (Operation != IoReadAccess) && !CurrentPde->IsWritable()) ||
            (!CurrentPde->IsLargePage() &&
                (!CurrentPte->IsValid() ||
                ((Operation != IoReadAccess) && !CurrentPte->IsWritable()))))
        {
            /* Check if we are below DISPATCH_LEVEL */
            if (CurrentIrql < DISPATCH_LEVEL)
            {
                /* Lock all pages we gathered so far */
                PfnCount = CurrentPfn - NextPfnToLock;
                PFN_DATABASE::LockMultiplePages(NextPfnToLock, PfnCount);
                NextPfnToLock = CurrentPfn;

                /* Unlock the working set */
                AddressSpace->ReleaseWorkingSetLock();

                /* Invoke the fault handler to page in the page */
                Status = MmAccessFault(AccessFlags, CurrentVa, AccessMode, NULL);
            }
            else
            {
                /* We are at DISPATCH_LEVEL, this is not allowed */
                Status = STATUS_ACCESS_VIOLATION;
            }

            if (!NT_SUCCESS(Status))
            {
                NT_ASSERT(FALSE); /// Do we need to do anything else with the MDL?

                /* Mark the end of the PFN array */
                *NextPfnToLock = MAXULONG_PTR;

                /* Unlock the pages processed so far and raise status */
                MmUnlockPages(Mdl);
                RtlRaiseStatus(Status);
            }

            /* Lock the working set again */
            AddressSpace->AcquireWorkingSetLock();

            /* Try again */
            continue;
        }

        /* Check if this is a large page PDE */
        if (CurrentPde->IsLargePage())
        {
            /* Calculate the PFN from the base page and relative page */
            ULONG_PTR RelativePage = CurrentPte - PdeToPte(CurrentPde);
            *CurrentPfn = CurrentPde->GetPageFrameNumber() + RelativePage;
        }
        else
        {
            /* Normal page, get the page frame number from the PTE */
            *CurrentPfn = CurrentPte->GetPageFrameNumber();

            /* Sanity check */
//            NT_ASSERT((CurrentIrql < DISPATCH_LEVEL) ||
//                      !g_PfnDatabase.IsPageable(*CurrentPfn));
        }

        /* Go to the next page */
        CurrentVa = AddToPointer(CurrentVa, PAGE_SIZE);
        CurrentPte++;
        CurrentPfn++;
    }
    while (CurrentVa < EndVa);

    /* Lock all remaining PFNs */
    PfnCount = CurrentPfn - NextPfnToLock;
    PFN_DATABASE::LockMultiplePages(NextPfnToLock, PfnCount);

    /* Unlock the working set */
    AddressSpace->ReleaseWorkingSetLock();

    /* Update the MDL flags */
    Mdl->MdlFlags |= MDL_PAGES_LOCKED;
    if (Operation != IoReadAccess)
    {
        Mdl->MdlFlags |= MDL_WRITE_OPERATION;
    }
    else
    {
        Mdl->MdlFlags &= ~(MDL_WRITE_OPERATION);
    }


}

/*! \fn MmProbeAndLockSelectedPages
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 *
 *  \param [in] SegmentArray -
 *
 *  \param [in] AccessMode -
 *
 *  \param [in] Operation -
 */
VOID
NTAPI
MmProbeAndLockSelectedPages (
    _Inout_ PMDL Mdl,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
}


/*! \fn MmUnlockPages
 *
 *  \brief ...
 *
 *  \param [inout] Mdl -
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnlockPages (
    _Inout_ PMDLX Mdl)
{
    PADDRESS_SPACE AddressSpace;
    PPFN_NUMBER PageFrameNumber;
    ULONG PageCount;

    /* Check if the MDL is still mapped */
    if (Mdl->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA)
    {
        /* Unmap it */
        MmUnmapLockedPages(Mdl->MappedSystemVa, Mdl);
    }

    /* Check if the MDL has a process */
    if (Mdl->Process != NULL)
    {
        __debugbreak(); /// this won't work with the furure address space concept!
        /// we probably only need to hold the LockPagesMutex anyway
        /* Use the related process address space */
        AddressSpace = GetProcessAddressSpace(Mdl->Process);
    }
    else
    {
        /* Use the kernel address space */
        AddressSpace = &g_KernelAddressSpace;
    }

    /* Acquire the working set lock */
    AddressSpace->AcquireWorkingSetLock();

    /* Loop all pages in the MDL */
    PageCount = ALIGN_UP_BY(Mdl->ByteOffset + Mdl->ByteCount, PAGE_SIZE);
    PageFrameNumber = MmGetMdlPfnArray(Mdl);
    do
    {
        /* Check if the array was terminated */
        if (*PageFrameNumber == MAXULONG_PTR)
        {
            break;
        }

        /* Unlock this page */
        g_PfnDatabase.UnlockPage(*PageFrameNumber);
        PageFrameNumber++;
    }
    while (--PageCount);

    /* Unlock the working set */
    AddressSpace->ReleaseWorkingSetLock();
}

}; // extern "C"
}; // namespace Mm
