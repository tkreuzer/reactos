/*!

    \file DebugSupport.cpp

    \brief Implements debugging support functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include "PfnDatabase.hpp"
#include <ndk/pstypes.h>
#include _ARCH_RELATIVE_(PageTables.hpp)

/// HACK!
#define KeInvalidateTlbEntry(Address) __invlpg(Address)

namespace Mm {

static const ULONG MMDBG_COPY_WRITE          = 0x00000001;
static const ULONG MMDBG_COPY_PHYSICAL       = 0x00000002;
static const ULONG MMDBG_COPY_UNSAFE         = 0x00000004;
static const ULONG MMDBG_COPY_CACHED         = 0x00000008;
static const ULONG MMDBG_COPY_UNCACHED       = 0x00000010;
static const ULONG MMDBG_COPY_WRITE_COMBINED = 0x00000020;
extern PPTE DebugPte;

ULONG
ConvertProtectToWin32 (
    _In_ ULONG Protect);


/*! \fn DbgCopyMapPhysicalMemory
 *
 *  \brief ...
 *
 *  \param [in] PhysicalAddress -
 *
 *  \param [in] Flags -
 *
 *  \return ...
 */
static
PVOID
DbgCopyMapPhysicalMemory (
    _In_ ULONG64 PhysicalAddress,
    _In_ ULONG Flags)
{
    PFN_NUMBER PageFrameNumber;
    ULONG Protect;
    PFN_CACHE_ATTRIBUTE CacheAttribute;

    /* We must have a debug PTE, otherwise we cannot do anything */
    if (DebugPte == NULL)
    {
        return NULL;
    }

    /* Calculate the page frame number and check if it's valid */
    PageFrameNumber = static_cast<PFN_NUMBER>(PhysicalAddress >> PAGE_SHIFT);
    if (!g_PfnDatabase.IsValidPageFrameNumber(PageFrameNumber))
    {
        return NULL;
    }

    /* Check if the debug PTE already has the correct page frame number */
    if (DebugPte->GetPageFrameNumber() != PageFrameNumber)
    {
        /* Set the protection */
        Protect = MM_READWRITE;

        /* Check for requested cache attributes */
        if (Flags & MMDBG_COPY_UNCACHED)
        {
            Protect |= MM_UNCACHED;
        }
        else if (Flags & MMDBG_COPY_WRITE_COMBINED)
        {
            Protect |= MM_WRITECOMBINE;
        }
        else if ((Flags & MMDBG_COPY_CACHED) == 0)
        {
            /* No flag was set, get the caching from the PFN database */
            CacheAttribute = g_PfnDatabase.GetPfnCacheAttribute(PageFrameNumber);
            if (CacheAttribute == PfnNonCached)
                Protect |= MM_UNCACHED;
            else if (CacheAttribute == PfnWriteCombined)
                Protect |= MM_WRITECOMBINE;
        }

        /* Now write a new PTE and invalidate the TLB entry */
        DebugPte->MakeValidPte(PageFrameNumber, MM_READWRITE);
        KeInvalidateTlbEntry(PteToAddress(DebugPte));
    }

    return AddToPointer(PteToAddress(DebugPte), PhysicalAddress & (PAGE_SIZE - 1));
}

extern "C" {

/*! \fn MmDbgCopyMemoryEx
 *
 *  \brief ...
 *
 *  \param [in] Address -
 *
 *  \param [in] Buffer -
 *
 *  \param [in] Size -
 *
 *  \param [in] Flags -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmDbgCopyMemoryEx (
    _In_ ULONG64 Address,
    _In_ PVOID Buffer,
    _In_ ULONG Size,
    _In_ ULONG Flags)
{
    ULONG64 EndAddress;
    ULONG PageOffset, CopySize;
    PVOID Pointer;
    BOOLEAN NeedMakeWritable;

    /* Calculate the end of the copy area */
    EndAddress = Address + Size;

    do
    {
        /* Check if this is a physical memory copy */
        if (Flags & MMDBG_COPY_PHYSICAL)
        {
            /* Map the physical memory and get the pointer to the VA */
            Pointer = DbgCopyMapPhysicalMemory(Address, Flags);
            if (Pointer == NULL)
            {
                return STATUS_UNSUCCESSFUL;
            }
        }
        else
        {
            /* Convert current virtual address to a pointer */
            Pointer = reinterpret_cast<PVOID>(Address);

            /* Check if this address is accessible */
            if (!MmIsAddressValid(Pointer))
            {
                return STATUS_UNSUCCESSFUL;
            }

            /* Check if we write to memory */
            if (Flags & MMDBG_COPY_WRITE)
            {
                /* Check if the address is writable */
                NeedMakeWritable = !AddressToPte(Pointer)->IsWritable();
                if (NeedMakeWritable)
                {
                    /* It's not writable, so make it writable */
                    AddressToPte(Pointer)->SetWritable(TRUE);
                }
            }
        }

        /* Calculate the offset and the size we can copy */
        PageOffset = Address & (PAGE_SIZE - 1);
        CopySize = min(Size, PAGE_SIZE - PageOffset);

        /* Check if we read or write */
        if (Flags & MMDBG_COPY_WRITE)
        {
            /* Copy the maximum that is inside this page */
            RtlCopyMemory(Pointer, Buffer, CopySize);

            /* Check if we modified a PTE */
            if (!(Flags & MMDBG_COPY_PHYSICAL) && NeedMakeWritable)
            {
                /* Reset back to read-only */
                AddressToPte(Pointer)->SetWritable(FALSE);
            }
        }
        else
        {
            /* Copy the maximum that is inside this page */
            RtlCopyMemory(Buffer, Pointer, CopySize);
        }

        /* Go to next page */
        Address += CopySize;
        Size -= CopySize;
    }
    while (Address < EndAddress);

    return STATUS_SUCCESS;
}

/*! \fn MmDbgCopyMemory
 *
 *  \brief ...
 *
 *  \param [in] Address -
 *
 *  \param [in] Buffer -
 *
 *  \param [in] Size -
 *
 *  \param [in] Flags -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmDbgCopyMemory (
    _In_ ULONG64 Address,
    _In_ PVOID Buffer,
    _In_ ULONG Size,
    _In_ ULONG Flags)
{
    /* Verify the requested size is ok */
    if ((Size != 1) && (Size != 2) && (Size != 4) && (Size != 8))
    {
        return STATUS_INVALID_PARAMETER_3;
    }

    /* Verify that the Address is sufficiently aligned */
    if ((Address & (Size - 1)) != 0)
    {
        return STATUS_INVALID_PARAMETER_1;
    }

    /* Use the extended function */
    return MmDbgCopyMemoryEx(Address, Buffer, Size, Flags);
}

/*! \fn MmGetPageProtect
 *
 *  \brief Returns the win32 protection value for the page at the given
 *      address. Can only be used by the debugger, because the function is
 *      NOT thread safe.
 *
 *  \param [in] Process - The process for which the mapping should be evaluated.
 *
 *  \param [in] Address - An address inside the page that is to be checked.
 *
 *  \return One of the PAGE_* protection constants or a combination.
 */
ULONG
NTAPI
MmGetPageProtect (
    _In_ PEPROCESS Process,
    _In_ PVOID Address)
{
    KAPC_STATE SavedApcState;
    ULONG Protect;
    BOOLEAN Attached = FALSE;

    /* Check if a different process is requested */
    if (Process != PsGetCurrentProcess())
    {
        /* Attach to the target process */
        KeStackAttachProcess(&Process->Pcb, &SavedApcState);
        Attached = TRUE;
    }

    /* First check if the address is valid */
    if (!MmIsAddressValid(Address))
    {
        return PAGE_NOACCESS;
    }

    /* Get the page protection */
    Protect = AddressToPte(Address)->GetProtection();

    /* Did we attach? */
    if (Attached)
    {
        /* Detach from process */
        KeUnstackDetachProcess(&SavedApcState);
    }

    /* Convert it to the win32 format */
    return ConvertProtectToWin32(Protect);
}

/*! \fn atexit
 *
 *  \brief Invoked when static initialization fails
 */
void
atexit ()
{
    KeBugCheck(0);
}

#ifdef __GNUC__

/*! \fn __cxa_pure_virtual
 *
 *  \brief For GCC, invoked when a pure virtual function is called
 */
void
__cxa_pure_virtual ()
{
    KeBugCheck(0);
}

#endif // __GNUC__

}; // extern "C"
}; // namespace Mm
