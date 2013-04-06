
#include "ntosbase.h"
#include "amd64/PageTables.hpp"

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
        AddressToPte(VirtualAddress)->IsValid());
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

}; // extern "C"
}; // namespace Mm
