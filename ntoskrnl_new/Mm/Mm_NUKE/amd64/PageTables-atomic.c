#define PDE_REFCOUNT_SHIFT 52

ULONG
FORCEINLINE
MxInterlockedAddPteCount(
    _Inout_ PMXPTE PdePointer,
    _In_ ULONG Addend)
{
    MXPTE OldPdeValue;
    OldPdeValue.Long = InterlockedAdd64(&PdePointer->Long,
                                        (Addend << PDE_REFCOUNT_SHIFT));

    return (ULONG)OldPdeValue.PageTable.UsedPageTableEntries;
}

VOID
NTAPI
MxReservePtes(
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount)
{
    PMXPTE PxePointer, EndPxe;
    PMXPTE PpePointer, EndPpe, MarginPpe;
    PMXPTE PdePointer, EndPde, MarginPde;
    PMXPTE PtePointer, EndPte, MarginPte;
    ULONG PpeCount, PdeCount, PteCount;
    MXPTE PdeValue;

    // for paged memory IRQL < DISPATCH_LEVEL!
    // must own the WS lock

    PxePointer = MxVpnToPxe(StartingVpn);
    PpePointer = MxVpnToPpe(StartingVpn);
    PdePointer = MxVpnToPde(StartingVpn);

    EndPxe = MxVpnToPxe(StartingVpn + PageCount - 1) + 1;
    EndPpe = MxVpnToPpe(StartingVpn + PageCount - 1) + 1;
    EndPde = MxVpnToPde(StartingVpn + PageCount - 1) + 1;

    do
    {
        /* Read the PXE and check if it's empty */
        if (PxePointer->Long == 0)
        {
            // map the pxe
            MxMapPageTable(PpePointer);
        }

        PpeCount = 0;
        MarginPpe = MinPtr(MxPteToAddress(PxePointer + 1), EndPpe);
        do
        {
            /* Read the PPE and check if it's empty */
            if (PpePointer->Long == 0)
            {
                // map the ppe
                MxMapPageTable(PpePointer);

                /* Count this PPE */
                PpeCount++;
            }

            PdeCount = 0;
            MarginPde = MinPtr(MxPteToAddress(PpePointer + 1), EndPde);
            do
            {
                /* Read the PDE and check if it's empty */
                if (PdePointer->Long == 0)
                {
                    // map the pde
                    PdeValue = ...

                    /* Count this PDE */
                    PdeCount++;
                }

                PteCount = 0;
                MarginPte = MinPtr(MxPteToAddress(PdePointer + 1), EndPte);
                do
                {
                    if (PtePointer->Long == 0)
                    {
                        /* Count this PTE */
                        PteCount++;
                    }

                    /* Go to the next PTE */
                    PtePointer++;
                } while (PtePointer < MarginPte);

                /* Update the PTE count in the PDE */
                if (PteCount) MxInterlockedAddPteCount(PdePointer, PteCount);

                /* Go to the next PDE */
                PdePointer++;
            } while (PdePointer < MarginPde);

            /* Update the PDE count in the PPE */
            if (PdeCount) MxInterlockedAddPteCount(PpePointer, PdeCount);

            /* Go to the next PPE */
            PpePointer++;
        } while (PpePointer < MarginPpe);

        /* Update the PPE count in the PXE */
        if (PpeCount) MxInterlockedAddPteCount(PxePointer, PpeCount);

        /* Go to the next PXE */
        PxePointer++;
    } while (PxePointer < EndPxe);

}



#include <ntoskrnl.h>
#include "../Mm_internal.h"


VOID
NTAPI
MxReleasePtes(
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount)
{
    MXPTE PxeValue, *PxePointer, *EndPxe;
    MXPTE PpeValue, *PpePointer, *EndPpe, *MarginPpe;
    MXPTE PdeValue, *PdePointer, *EndPde, *MarginPde;
    MXPTE PteValue, *PtePointer, *EndPte, *MarginPte;

    // for paged memory IRQL < DISPATCH_LEVEL!
    // must own the WS lock

    PxePointer = MxVpnToPxe(StartingVpn);
    PpePointer = MxVpnToPpe(StartingVpn);
    PdePointer = MxVpnToPde(StartingVpn);

    EndPxe = MxVpnToPxe(StartingVpn + PageCount - 1) + 1;
    EndPpe = MxVpnToPpe(StartingVpn + PageCount - 1) + 1;
    EndPde = MxVpnToPde(StartingVpn + PageCount - 1) + 1;

    do
    {
        MarginPpe = MinPtr(MxPteToAddress(PxePointer + 1), EndPpe);
        do
        {
            MarginPde = MinPtr(MxPteToAddress(PpePointer + 1), EndPde);
            do
            {
                MarginPte = MinPtr(MxPteToAddress(PdePointer + 1), EndPte);
                do
                {
                    if (PtePointer->Long == 0)
                    {
                        /* Increase count of used entries in the PT */
                        PdeValue.PageTable.UsedPageTableEntries++;
                    }

                    /* Go to the next PTE */
                    PtePointer++;
                } while (PtePointer < MarginPte);

                /* Write the updated PDE */
                *PdePointer = PdeValue;

                /* Go to the next PDE */
                PdePointer++;
            } while (PdePointer < MarginPde);

            /* Write the updated PPE */
            *PpePointer = PpeValue;

            /* Go to the next PPE */
            PpePointer++;
        } while (PpePointer < MarginPpe);

        /* Write the updated PXE */
        *PxePointer = PxeValue;

        /* Go to the next PXE */
        PxePointer++;
    } while (PxePointer < EndPxe);

}

