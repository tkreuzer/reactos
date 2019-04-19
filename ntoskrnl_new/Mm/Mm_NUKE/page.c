

#include <ntoskrnl.h>
#include "Mm_internal.h"

BOOLEAN
NTAPI
MmIsAddressValidForRead(
    IN PVOID Address)
{
#if (MI_PAGING_LEVELS == 4)
    if (!MxAddressToPxe(Address)->Hard.Valid) return FALSE;
#endif
#if (MI_PAGING_LEVELS >= 3)
    if (!MxAddressToPpe(Address)->Hard.Valid) return FALSE;
#endif
    if (!MxAddressToPde(Address)->Hard.Valid) return FALSE;
    if (!MxAddressToPte(Address)->Hard.Valid) return FALSE;

    return TRUE;
}

BOOLEAN
NTAPI
MmIsAddressValidForWrite(
    IN PVOID Address)
{
#if (MI_PAGING_LEVELS == 4)
    if (!MxAddressToPxe(Address)->Hard.Valid) return FALSE;
    if (!MxAddressToPxe(Address)->Hard.Write) return FALSE;
#endif
#if (MI_PAGING_LEVELS >= 3)
    if (!MxAddressToPpe(Address)->Hard.Valid) return FALSE;
    if (!MxAddressToPpe(Address)->Hard.Write) return FALSE;
#endif
    if (!MxAddressToPde(Address)->Hard.Valid) return FALSE;
    if (!MxAddressToPde(Address)->Hard.Write) return FALSE;
    if (!MxAddressToPte(Address)->Hard.Valid) return FALSE;
    if (!MxAddressToPte(Address)->Hard.Write) return FALSE;

    return FALSE;
}

NTSTATUS
NTAPI
MmDebugCopyMemory(
    IN PVOID Destination,
    IN PVOID Source,
    IN PULONG ByteCount,
    IN MM_COPY_TYPE CopyType)
{
    PUCHAR CurrentDestination, CurrentSource, ProtectedAddress;
    MXPTE BackupPte, *PointerPte;
    ULONG CurrentSize, BytesRemaining = *ByteCount;
    NTSTATUS Status = STATUS_SUCCESS;

    /* Get start address */
    CurrentDestination = Destination;
    CurrentSource = Source;

    /* Get the address to be protected */
    ProtectedAddress = (CopyType == MmDebugCopyRead) ? Source : Destination;

    /* Loop all pages */
    while (BytesRemaining)
    {
        /* Break out, if the page is not present */
        if (!MmIsAddressValidForRead(ProtectedAddress)) break;

        /* Check if writing on read only pages is requested */
        if (CopyType == MmDebugCopyWriteReadOnly)
        {
            /* Get the PTE and safe a backup */
            PointerPte = MxAddressToPte(ProtectedAddress);
            BackupPte = *PointerPte;

            /* Make the page writable */
            PointerPte->Hard.Write = 1;
        }
        else if (CopyType == MmDebugCopyWrite)
        {
            /* Break out, if the page is not writable */
            if (!PointerPte->Hard.Write) break;
        }

        /* Calculate the size for this page */
        CurrentSize = ((ULONG_PTR)ProtectedAddress & (PAGE_SIZE - 1));
        CurrentSize = PAGE_SIZE - CurrentSize;
        if (CurrentSize > BytesRemaining) CurrentSize = BytesRemaining;

        /* Copy this page */
        RtlCopyMemory(CurrentDestination, CurrentSource, CurrentSize);

        /* Check if the PTE was modified */
        if (CopyType == MmDebugCopyWriteReadOnly)
        {
            /* Restore the original pte */
            *PointerPte = BackupPte;
        }

        /* Go to the next page */
        CurrentDestination += CurrentSize;
        CurrentSource += CurrentSize;
        ProtectedAddress += CurrentSize;
        BytesRemaining -= CurrentSize;
    }

    *ByteCount -= BytesRemaining;

    /* Return the number of bytes copied */
    return BytesRemaining > 0 ? STATUS_UNSUCCESSFUL : STATUS_SUCCESS;
}

NTSTATUS
NTAPI
MmDebugCopyPhysicalMemory(
    PVOID VirtualAddress,
    ULONG64 PhysicalAddress,
    ULONG Size,
    BOOLEAN WriteToPhysical)
{
    MXPTE TemplatePte, *MappingPte;
    PUCHAR CurrentVirtual = VirtualAddress;
    ULONG Offset, CurrentSize, BytesRemaining = Size;

    /* Get the address of the debug mapping PTE */
    MappingPte = MxAddressToPte((PVOID)MX_DEBUG_MAPPING);

    /* Setup a template PTE */
    TemplatePte = MxValidKernelPte;

    /* Loop until everything is copied */
    while (BytesRemaining)
    {
        /* Get the page frame number from the current physical address */
        TemplatePte.Hard.PageFrameNumber = PhysicalAddress >> PAGE_SHIFT;

        /* Map the physical page */
        *MappingPte = TemplatePte;

        /* Get the current offset within the page */
        Offset = PhysicalAddress & (PAGE_SIZE - 1);

        /* Calculate the maximum that can be copied on this page */
        CurrentSize = min(BytesRemaining, (PAGE_SIZE - Offset));

        /* Copy from or to physical? */
        if (WriteToPhysical)
        {
            RtlCopyMemory((PVOID)(MX_DEBUG_MAPPING + Offset),
                          CurrentVirtual,
                          CurrentSize);
        }
        else
        {
            RtlCopyMemory(CurrentVirtual,
                          (PVOID)(MX_DEBUG_MAPPING + Offset),
                          CurrentSize);
        }

        /* Go to the next page */
        PhysicalAddress += CurrentSize;
        CurrentVirtual += CurrentSize;
        BytesRemaining -= CurrentSize;
    }

    /* Unmap the debug mapping PTE */
    TemplatePte.Long = 0;
    *MappingPte = TemplatePte;

    return STATUS_SUCCESS;
}



static ULONG HalpPteBitmapBuffer[HAL_VA_PAGECOUNT / sizeof(ULONG)];
static RTL_BITMAP HalpPteBitmap = {HAL_VA_PAGECOUNT, HalpPteBitmapBuffer};
static KSPIN_LOCK HalpPteBitmapLock;
static ULONG HalpPteHint;


PMXPTE
NTAPI
MiAllocatePtesForHal(
    ULONG PageCount,
    PVOID Address)
{
    ULONG Index;
    KIRQL OldIrql;

    /* Acquire the bitmap lock */
    KeAcquireSpinLock(&HalpPteBitmapLock, &OldIrql);

    /* Chack if an address was given */
    if (Address)
    {
        /* Calculate the bitmap index */
        Index = (ULONG)(MxAddressToPte(Address) -
                        MxAddressToPte((PVOID)MM_HAL_VA_START));

        /* Check if the pages are available */
        if (RtlAreBitsClear(&HalpPteBitmap, Index, PageCount))
        {
            /* Pages are available, so set the bits */
            RtlSetBits(&HalpPteBitmap, Index, PageCount);
        }
        else
        {
            /* Not all pages are available, report failure */
            Index = 0xFFFFFFFF;
        }
    }
    else
    {
        /* Find and set bits */
        Index = RtlFindClearBitsAndSet(&HalpPteBitmap, PageCount, HalpPteHint);

        /* Update the hint */
        if (Index != 0xFFFFFFFF) HalpPteHint = Index + PageCount;
    }

    /* Release the bitmap lock */
    KeReleaseSpinLock(&HalpPteBitmapLock, OldIrql);

    /* Check for failure */
    if (Index == 0xFFFFFFFF) return NULL;

    /* Return the address of the first PTE */
    return MxAddressToPte((PVOID)MM_HAL_VA_START) + Index;
}


NTSTATUS
NTAPI
MmMapPhysicalMemoryForHal(
    IN PHYSICAL_ADDRESS PhysicalAddress,
    IN SIZE_T Size,
    IN OUT PVOID *VirtualAddress)
{
    ULONG_PTR PageOffset;
    ULONG PageCount;
    MXPTE PteValue, *PointerPte;

    /* Calculate the offset in the first page */
    PageOffset = (PhysicalAddress.LowPart & (PAGE_SIZE - 1));

    /* Calculate the size in pages */
    PageCount = ADDRESS_AND_SIZE_TO_SPAN_PAGES((PVOID)PageOffset, Size);

    /* Allocate PTEs */
    PointerPte = MiAllocatePtesForHal(PageCount, *VirtualAddress);

    /* Check for failure */
    if (!PointerPte) return STATUS_INSUFFICIENT_RESOURCES;

    /* Return the virtual address */
    *VirtualAddress = MxPteToAddress(PointerPte);

    /* Prepare the PTE value */
    PteValue.Long = 0;
    PteValue.Hard.Valid = 1;
    PteValue.Hard.Write = 1;
    PteValue.Hard.Global = 1;
    PteValue.Hard.PageFrameNumber = PhysicalAddress.QuadPart / PAGE_SIZE;

    /* Loop the pages */
    while (PageCount)
    {
        /* Make sure this one isn't yet mapped */
        ASSERT(PointerPte->Hard.Valid == 0);

        /* Map the page */
        *PointerPte = PteValue;

        /* Next page */
        PointerPte++;
        PteValue.Hard.PageFrameNumber++;
        PageCount--;
    }

    return STATUS_SUCCESS;
}

