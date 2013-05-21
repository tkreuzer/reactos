
#include "ntosbase.h"
#include _ARCH_RELATIVE_(PageTables.hpp)

namespace Mm {

static const ULONG MMDBG_COPY_WRITE          = 0x00000001;
static const ULONG MMDBG_COPY_PHYSICAL       = 0x00000002;
static const ULONG MMDBG_COPY_UNSAFE         = 0x00000004;
static const ULONG MMDBG_COPY_CACHED         = 0x00000008;
static const ULONG MMDBG_COPY_UNCACHED       = 0x00000010;
static const ULONG MMDBG_COPY_WRITE_COMBINED = 0x00000020;

extern "C" {

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
MmIsAddressValid (
    _In_ PVOID VirtualAddress)
{
    /* Check all present page table levels */
    return (
#if MI_PAGING_LEVELS >= 4
        AddressToPxe(VirtualAddress)->IsValid() &&
#endif
#if MI_PAGING_LEVELS >= 3
        AddressToPpe(VirtualAddress)->IsValid() &&
#endif
        AddressToPde(VirtualAddress)->IsValid() &&
        (AddressToPde(VirtualAddress)->IsLargePage() ||
         AddressToPte(VirtualAddress)->IsValid()));
}

NTSTATUS
NTAPI
MmDbgCopyMemory (
    IN ULONG64 Address,
    IN PVOID Buffer,
    IN ULONG Size,
    IN ULONG Flags)
{
    ULONG64 EndAddress;
    ULONG PageOffset;
    PVOID Pointer;
    BOOLEAN NeedMakeWritable;

    if (Flags & MMDBG_COPY_PHYSICAL)
    {
        //DbgPrint("MMDBG_COPY_PHYSICAL is not supported yet!\n");
        return STATUS_UNSUCCESSFUL;
    }

    /* Calculate the end of the copy area */
    EndAddress = Address + Size;

    do
    {
        /* Convert to a pointer */
        Pointer = reinterpret_cast<PVOID>(Address);

        /* Check if this address is accessible */
        if (!MmIsAddressValid(Pointer))
        {
            return STATUS_UNSUCCESSFUL;
        }

        /* Check if this we write to memory */
        if (Flags & MMDBG_COPY_WRITE)
        {
            /* Figure out, if the address is writable */
            NeedMakeWritable = !AddressToPte(Pointer)->IsWritable();
            if (NeedMakeWritable)
            {
                /* It's not writable, so make it writable */
                AddressToPte(Pointer)->SetWritable(TRUE);
            }

            /* Copy the maximum that is inside this page */
            PageOffset = Address & (PAGE_SIZE - 1);
            RtlCopyMemory(Pointer, Buffer, min(Size, PAGE_SIZE - PageOffset));

            if (NeedMakeWritable)
            {
                AddressToPte(Pointer)->SetWritable(FALSE);
            }
        }
        else
        {
            /* Copy the maximum that is inside this page */
            PageOffset = Address & (PAGE_SIZE - 1);
            RtlCopyMemory(Buffer, Pointer, min(Size, PAGE_SIZE - PageOffset));
        }

        /* Go to next page */
        Address += PAGE_SIZE;
        Size -= PAGE_SIZE;
    }
    while (Address < EndAddress);

    return STATUS_SUCCESS;
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
