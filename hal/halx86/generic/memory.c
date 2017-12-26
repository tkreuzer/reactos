/*
 * PROJECT:         ReactOS HAL
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            hal/halx86/generic/memory.c
 * PURPOSE:         HAL memory management routines
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <hal.h>
#define NDEBUG
#include <debug.h>

static ULONG HalpPteBitmapBuffer[HAL_VA_PAGECOUNT / sizeof(ULONG)];
static RTL_BITMAP HalpPteBitmap = {HAL_VA_PAGECOUNT, HalpPteBitmapBuffer};
static KSPIN_LOCK HalpPteBitmapLock;
static ULONG HalpPteHint;

VOID
NTAPI
HalpAllocatePteForAddress(
    IN PVOID Address)
{
    ULONG_PTR Index;
    KIRQL OldIrql;
    ASSERT((ULONG_PTR)Address >= MM_HAL_VA_START);

    /* Calculate the bitmap index */
    Index = HalAddressToPte(Address) - HalAddressToPte((PVOID)MM_HAL_VA_START);

    /* Acquire the bitmap lock */
    KeAcquireSpinLock(&HalpPteBitmapLock, &OldIrql);

    /* Set the bit */
    RtlSetBit(&HalpPteBitmap, (ULONG)Index);

    /* Release the bitmap lock */
    KeReleaseSpinLock(&HalpPteBitmapLock, OldIrql);
}

PHARDWARE_PTE
NTAPI
HalpAllocatePtes(
    ULONG PageCount)
{
    ULONG Position;
    KIRQL OldIrql;

    /* Acquire the bitmap lock */
    KeAcquireSpinLock(&HalpPteBitmapLock, &OldIrql);

    /* Find and set bits */
    Position = RtlFindClearBitsAndSet(&HalpPteBitmap, PageCount, HalpPteHint);

    /* Release the bitmap lock */
    KeReleaseSpinLock(&HalpPteBitmapLock, OldIrql);

    /* Check for failure */
    if (Position == 0xFFFFFFFF) return NULL;

    /* Update the hint (no lock needed) */
    HalpPteHint = Position + PageCount;

    /* Return the address of the first PTE */
    return HalAddressToPte(MM_HAL_VA_START) + Position;
}

