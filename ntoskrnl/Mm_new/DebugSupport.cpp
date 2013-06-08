
#include "ntosbase.h"
#include "PfnDatabase.hpp"
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

static const
USHORT ProtectToWin32Protect[32] =
{
    PAGE_NOACCESS, // MM_INVALID
    PAGE_READONLY, // MM_READONLY
    PAGE_EXECUTE_READ, // MM_EXECUTE
    PAGE_EXECUTE_READ, // MM_EXECUTE_READ
    PAGE_READWRITE, // MM_READWRITE
    PAGE_WRITECOPY, // MM_WRITECOPY
    PAGE_EXECUTE_READWRITE, // MM_EXECUTE_READWRITE
    PAGE_EXECUTE_WRITECOPY, // MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_UNCACHED | MM_INVALID
    PAGE_NOCACHE | PAGE_READONLY, // MM_UNCACHED | MM_READONLY
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE_READ
    PAGE_NOCACHE | PAGE_READWRITE, // MM_UNCACHED | MM_READWRITE
    PAGE_NOCACHE | PAGE_WRITECOPY, // MM_UNCACHED | MM_WRITECOPY
    PAGE_NOCACHE | PAGE_EXECUTE_READWRITE, // MM_UNCACHED | MM_EXECUTE_READWRITE
    PAGE_NOCACHE | PAGE_EXECUTE_WRITECOPY, // MM_UNCACHED | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_GUARDPAGE | MM_INVALID
    PAGE_GUARD | PAGE_READONLY, // MM_GUARDPAGE | MM_READONLY
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE_READ
    PAGE_GUARD | PAGE_READWRITE, // MM_GUARDPAGE | MM_READWRITE
    PAGE_GUARD | PAGE_WRITECOPY, // MM_GUARDPAGE | MM_WRITECOPY
    PAGE_GUARD | PAGE_EXECUTE_READWRITE, // MM_GUARDPAGE | MM_EXECUTE_READWRITE
    PAGE_GUARD | PAGE_EXECUTE_WRITECOPY, // MM_GUARDPAGE | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_WRITECOMBINE | MM_INVALID
    PAGE_WRITECOMBINE | PAGE_READONLY, // MM_WRITECOMBINE | MM_READONLY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE_READ
    PAGE_WRITECOMBINE | PAGE_READWRITE, // MM_WRITECOMBINE | MM_READWRITE
    PAGE_WRITECOMBINE | PAGE_WRITECOPY, // MM_WRITECOMBINE | MM_WRITECOPY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READWRITE, // MM_WRITECOMBINE | MM_EXECUTE_READWRITE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_WRITECOPY, // MM_WRITECOMBINE | MM_EXECUTE_WRITECOPY
};


ULONG
NTAPI
MmGetPageProtect (
    _In_ PEPROCESS Process,
    _In_ PVOID Address)
{
    ULONG Protect;

    /* First check if the address is valid */
    if (!MmIsAddressValid(Address))
    {
        return PAGE_NOACCESS;
    }

    /* Get the page protection */
    Protect = AddressToPte(Address)->GetProtection();

    /* Convert it to the win32 format */
    return ProtectToWin32Protect[Protect & MM_PROTECTION_MASK];
}

// for GCC, invoked when a pure virtual function is called
void
__cxa_pure_virtual ()
{
    KeBugCheck(0);
}

// for GCC, invoked when static initialization fails
void
atexit()
{
    KeBugCheck(0);
}

}; // extern "C"
}; // namespace Mm
