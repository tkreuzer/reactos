

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

SIZE_T
NTAPI
MmSizeOfMdl (
  _In_reads_bytes_opt_ (Length) PVOID Base,
  _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return 0;
}

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

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreePagesFromMdl (
  _Inout_ PMDLX MemoryDescriptorList)
{
    if (MemoryDescriptorList->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA)
    {
        MmUnmapLockedPages(MemoryDescriptorList->MappedSystemVa,
                           MemoryDescriptorList);
    }
    UNIMPLEMENTED;
}


_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmBuildMdlForNonPagedPool (
    _Inout_ PMDLX Mdl)
{
    PPFN_NUMBER CurrentPfnNumber;
    ULONG_PTR NumberOfPages;
    PVOID BaseAddress;
    PPTE CurrentPte;
    PPDE CurrentPde;

    NT_ASSERT(Mdl->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA);
    NT_ASSERT(Mdl->StartVa != NULL);
    //NT_ASSERT(MmDeterminePoolType(Mdl->StartVa) == NonPagedPool);

    BaseAddress = AddToPointer(Mdl->StartVa, Mdl->ByteOffset);

    /* Calculate the size in pages */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseAddress, Mdl->ByteCount);

    CurrentPfnNumber = MmGetMdlPfnArray(Mdl);
    CurrentPte = AddressToPte(Mdl->StartVa);
    CurrentPde = AddressToPde(Mdl->StartVa);

    do
    {
        /* Get the PDE */
        CurrentPde = PteToPde(CurrentPte);

        /* Check if this is a large page allocation */
        if (CurrentPde->IsLargePage())
        {
            /* Get the relative PFN from the large page PDE */
            *CurrentPfnNumber = CurrentPde->GetPageFrameNumber();
            *CurrentPfnNumber += CurrentPte - PdeToPte(CurrentPde);
        }
        else
        {
            /* Get the PFN from the PTE */
            *CurrentPfnNumber = CurrentPte->GetPageFrameNumber();
        }

        /* Next PTE */
        CurrentPte++;
    }
    while (--NumberOfPages > 0);

    Mdl->Process = 0;
    Mdl->MappedSystemVa = BaseAddress;
    Mdl->MdlFlags |= MDL_SOURCE_IS_NONPAGED_POOL;

}

PMDL
NTAPI
MmCreateMdl(
    _Out_writes_bytes_opt_ (sizeof (MDL) + (sizeof (PFN_NUMBER) * ADDRESS_AND_SIZE_TO_SPAN_PAGES (Base, Length)))
        PMDL MemoryDescriptorList,
    _In_reads_bytes_opt_ (Length) PVOID Base,
    _In_ SIZE_T Length)
{
    UNIMPLEMENTED;
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmProtectMdlSystemAddress (
    _In_ PMDLX MemoryDescriptorList,
    _In_ ULONG NewProtect)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmProbeAndLockProcessPages (
    _Inout_ PMDL MemoryDescriptorList,
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
        MmProbeAndLockPages(MemoryDescriptorList, AccessMode, Operation);
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
    PPFN_NUMBER CurrentPfnNumber;
    PVOID StartVa, EndVa, CurrentVa;
    PADDRESS_SPACE AddressSpace;
    PPTE CurrentPte;
    PPDE CurrentPde;

//__debugbreak();

    CurrentPfnNumber = MmGetMdlPfnArray(Mdl);
    *CurrentPfnNumber = MAXULONG_PTR;
    Mdl->Process = NULL;

    /* Get start and end of the VA range */
    StartVa = Mdl->StartVa;
    EndVa = AddToPointer(StartVa, Mdl->ByteCount);

    /* Check for invalid VA range */
    if ((EndVa < StartVa) ||
        ((StartVa <= MmHighestUserAddress) && (EndVa > MmHighestUserAddress)) ||
        ((StartVa > MmHighestUserAddress) && (AccessMode != KernelMode)))
    {
        /* This is not allowed, raise access violation */
        RtlRaiseStatus(STATUS_ACCESS_VIOLATION);
    }

    /* First loop to make the pages resident */
    CurrentVa = ALIGN_DOWN_POINTER_BY(StartVa, PAGE_SIZE);
    do
    {
        /* Access the page to make it resident */
        *(volatile CHAR*)CurrentVa;
        //Status = MmAccessFault(0, CurrentVa, AccessMode, NULL);

        /* Check if this is write access */
        if (Operation != IoReadAccess)
        {
            /* Do a write as well */
            *(volatile CHAR*)CurrentVa = *(volatile CHAR*)CurrentVa;
        }

        /* Go to the next page */
        CurrentVa = AddToPointer(CurrentVa, PAGE_SIZE);
    }
    while (CurrentVa < EndVa);

    /* Get the address space */
    AddressSpace = GetAddressSpaceForAddress(StartVa);

    /* Lock the working set */
    AddressSpace->AcquireWorkingSetLock();

    /* Loop again. This time we can't throw an exception, since we check
       if the PTE is valid before accessing anything */
    CurrentVa = ALIGN_DOWN_POINTER_BY(StartVa, PAGE_SIZE);
    CurrentPte = AddressToPte(CurrentVa);
    do
    {
        /* Get the PDE */
        CurrentPde = AddressToPde(CurrentVa);

        /* Check if this is a large page PDE */
        /// FIXME: not safe
        if (CurrentPde->IsValid() && CurrentPde->IsLargePage())
        {

            ULONG_PTR RelativePage = CurrentPte - PdeToPte(CurrentPde);

            *CurrentPfnNumber = CurrentPde->GetPageFrameNumber() + RelativePage;
        }
        else
        {
            /* If the page got paged out, we need to make it resident again */
            while (!MmIsAddressValid(CurrentVa) ||
                   ((Operation != IoReadAccess) && !CurrentPte->IsWritable()))
            {
                UCHAR AccessFlags;
                NTSTATUS Status;

                /* Unlock the working set */
                AddressSpace->ReleaseWorkingSetLock();

                AccessFlags = (Operation != IoReadAccess) ? PFEC_WRITE : 0;
                Status = MmAccessFault(AccessFlags, CurrentVa, AccessMode, NULL);
                if (!NT_SUCCESS(Status))
                {
                    NT_ASSERT(FALSE); /// Do we need to do anything else with the MDL?

                    /* Mark The end of the PFN array */
                    *CurrentPfnNumber = MAXULONG_PTR;

                    MmUnlockPages(Mdl);
                    RtlRaiseStatus(Status);
                }

                /* Lock the working set again */
                AddressSpace->AcquireWorkingSetLock();
            }

            /* Get the page frame number from the PTE */
            *CurrentPfnNumber = CurrentPte->GetPageFrameNumber();

            //g_PfnDatabase.LockPage(*CurrentPfnNumber);
        }

        /* Go to the next page */
        CurrentVa = AddToPointer(CurrentVa, PAGE_SIZE);
        CurrentPte++;
        CurrentPfnNumber++;
    }
    while (CurrentVa < EndVa);

    /* Unlock the working set */
    AddressSpace->ReleaseWorkingSetLock();

    Mdl->MdlFlags |= MDL_PAGES_LOCKED;
    if (Operation != IoReadAccess)
    {
        Mdl->MdlFlags |= MDL_WRITE_OPERATION;
    }
    else
    {
        Mdl->MdlFlags &= ~(MDL_WRITE_OPERATION);
    }

    if (StartVa <= MmHighestUserAddress)
    {
        Mdl->Process = PsGetCurrentProcess();
    }
    else
    {
        Mdl->Process = NULL;
    }

}

VOID
NTAPI
MmProbeAndLockSelectedPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
}


_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnlockPages (
    _Inout_ PMDLX MemoryDescriptorList)
{
    DbgPrint("MmUnlockPages does nothing\n");
    //UNIMPLEMENTED;
}

}; // extern "C"
}; // namespace Mm
