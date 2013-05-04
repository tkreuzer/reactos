
#include "ntosbase.h"
#include "PfnDatabase.hpp"
#include "amd64/PageTables.hpp"
#include "ndk/pstypes.h"

namespace Mm {

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
    _Out_ volatile PFN_NUMBER* PageFrameNumber)
{
    ULONG Protect;

    /// FIXME
    Protect = MM_READWRITE | MM_GLOBAL;//CurrentPteValue->GetSoftProtection();

    if (*PageFrameNumber == 0)
    {
        *PageFrameNumber = g_PfnDatabase.AllocatePage(TRUE); /// FIXME what about waiting?
        NT_ASSERT(*PageFrameNumber != 0);
    }

    NewPteValue->MakeValidPte(*PageFrameNumber, Protect);

    return STATUS_SUCCESS;
}

inline
NTSTATUS
ResolvePrototypePteFault (
    _In_ PPTE CurrentPteValue,
    _Out_ PPTE NewPteValue,
    _Out_ volatile PFN_NUMBER* PageFrameNumber)
{
    UNIMPLEMENTED;
    return STATUS_ACCESS_VIOLATION;
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
    return STATUS_ACCESS_VIOLATION;
}

inline
NTSTATUS
ResolveFaultForPte (
    _In_ PPTE PtePointer,
    _In_ PVOID Address,
    _In_ IN KPROCESSOR_MODE Mode,
    _In_ PVOID TrapInformation,
    _In_ UCHAR AccessFlags,
    _Out_ volatile PFN_NUMBER* PageFrameNumber)
{
    PTE CurrentPteValue, NewPteValue;
    NTSTATUS Status;

    /* Read the PTE value */
    PtePointer->ReadValue(&CurrentPteValue);

    switch (CurrentPteValue.GetPteType())
    {
    case PteValid:

        /* Check if this was a write instruction */
        if (AccessFlags & PFEC_WRITE)
        {
            if (CurrentPteValue.IsWritable())
                return STATUS_SUCCESS;

            if (CurrentPteValue.IsCopyOnWrite())
            {
                return ResolveCopyOnWriteFault(PtePointer,
                                               Address,
                                               Mode,
                                               AccessFlags);
            }

            /* On non-debug versions, we bug-check for kernel mode access */
            if (!DBG && (Mode == KernelMode))
            {
                KeBugCheckEx(ATTEMPTED_WRITE_TO_READONLY_MEMORY,
                             (ULONG_PTR)Address,
                             *(ULONG_PTR*)&CurrentPteValue,
                             0,
                             0);
            }

            /* User mode or debug build: dispatch the fault */
            return STATUS_ACCESS_VIOLATION;
        }

        /* Check if this was due to instruction execution */
        if (AccessFlags & PFEC_INSTRUCTION_FETCH)
        {
            if (CurrentPteValue.IsExecutable())
                return STATUS_SUCCESS;

            /* On non-debug versions, we bug-check for kernel mode access */
            if (!DBG && (Mode == KernelMode))
            {
                KeBugCheckEx(ATTEMPTED_EXECUTE_OF_NOEXECUTE_MEMORY,
                             (ULONG_PTR)Address,
                             *(ULONG_PTR*)&CurrentPteValue,
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

        Status = ResolveDemandZeroFault(&CurrentPteValue,
                                        &NewPteValue,
                                        PageFrameNumber);
        break;

    case PtePrototype:

        Status = ResolvePrototypePteFault(&CurrentPteValue,
                                          &NewPteValue,
                                          PageFrameNumber);
        break;

    case PteTransition:
    case PtePageFile:
        __debugbreak();


    case PteNoAccess:
    case PteEmpty:

        /* On non-debug versions, we bug-check for kernel mode access */
        if (!DBG && (Mode == KernelMode))
        {
            KeBugCheckEx(PAGE_FAULT_IN_NONPAGED_AREA,
                         (ULONG_PTR)Address,
                         (AccessFlags & PFEC_WRITE) ? 1 : 0,
                         (ULONG_PTR)TrapInformation,
                         0);
        }

        /* Both of these are not accessible / resolvable */
        return STATUS_ACCESS_VIOLATION;

    DEFAULT_UNREACHABLE;
    }

    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Try to exchange the PTE with the new PTE, if it did not change */
    if (!PtePointer->InterlockedCompareExchange(NewPteValue, &CurrentPteValue))
    {
        /* Signal the caller that we need to retry */
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

    PageFrameNumber = 0;

    /* Protect with SEH, since the internal function can cause a page fault
       while accessing a PTE, which might not be resolved. In that case the
       fault get's dispatched and we catch it here */
    _SEH2_TRY
    {
        do
        {
            Status = ResolveFaultForPte(AddressToPte(Address),
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

    /* Check if a page needs to be freed */
    if (PageFrameNumber != 0)
    {
        g_PfnDatabase.ReleasePage(PageFrameNumber);
    }

    /* Reset active fault count back to what it was before */
    Thread->ActiveFaultCount--;

    return Status;
}

extern "C"
BOOLEAN
MmIsRecursiveIoFault (
    VOID)
{
    return PsGetCurrentThread()->ActiveFaultCount > 0;
}

}; // namespace Mm
