
#include "ntosbase.h"
#include "amd64/PageTables.hpp"
#include "ndk/pstypes.h"

namespace Mm {

#define PAGE_GLOBAL 0x800

enum MM_PROTECT
{
    MM_NOACCESS           = 0,
    MM_READONLY           = 1,
    MM_EXECUTE            = 2,
    MM_EXECUTE_READ       = 3,
    MM_READWRITE          = 4,
    MM_WRITECOPY          = 5,
    MM_EXECUTE_READWRITE  = 6,
    MM_EXECUTE_WRITECOPY  = 7,

    MM_NOCACHE            = 0x08,
    MM_DECOMMIT           = 0x10,
    MM_WRITECOMBINE       = 0x18,

    MM_PROTECTION_MASK    = 0x1F,

    MM_GLOBAL             = 0x20,
    MM_MAPPED             = 0x40,
    MM_NONPAGED           = 0x80,

    MM_INVALID_PROTECTION = 0xFFFFFFFF
};

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

NTSTATUS
MiResolveFaultForPte (
    PPTE PtePointer,
    PVOID Address,
    IN KPROCESSOR_MODE Mode,
    BOOLEAN StoreInstruction)
{
    UNIMPLEMENTED;
    return STATUS_ACCESS_VIOLATION;
}

extern "C"
NTSTATUS
NTAPI
MmAccessFault(
    IN BOOLEAN StoreInstruction,
    IN PVOID Address,
    IN KPROCESSOR_MODE Mode,
    IN PVOID TrapInformation)
{
    PETHREAD Thread;
    NTSTATUS Status;

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
#if !DBG
        /* On non-debug versions, we bug-check, otherwise dispatch the fault */
        if (Mode == KernelMode)
        {
            KeBugCheckEx(PAGE_FAULT_IN_NONPAGED_AREA,
                         (ULONG_PTR)Address,
                         StoreInstruction,
                         (ULONG_PTR)TrapInformation,
                         0);
        }
#endif
        /* Dispatch the fault */
        return STATUS_ACCESS_VIOLATION;
    }
#endif

DbgPrint("Pagefault for Address %p, PdeAddress = %p (%d), PteAddress = %p\n",
         Address, AddressToPde(Address), AddressToPde(Address)->IsValid(),
         AddressToPte(Address));

    /* Get current thread and increment active fault count */
    Thread = PsGetCurrentThread();
    Thread->ActiveFaultCount++;

    /* Protect with SEH, since the internal function could cause a page fault
       while accessing a PTE, which might not be resolved. In that case the
       fault get's dispatched and we catch it here */
    _SEH2_TRY
    {
        Status = MiResolveFaultForPte(AddressToPte(Address),
                                      Address,
                                      Mode,
                                      StoreInstruction);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = _SEH2_GetExceptionCode();
    }
    _SEH2_END;

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
