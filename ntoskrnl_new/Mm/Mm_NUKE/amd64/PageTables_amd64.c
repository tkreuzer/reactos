
#include <ntoskrnl.h>
#include "../Mm_internal.h"


VOID
FORCEINLINE
MxCommitPageTable(
    _Out_ PMXPDE PdePointer)
{
    PFN_NUMBER ParentPageFrameNumber;
    MXPDE ValidPde;
    ASSERT(PdePointer->Long == 0);

    /* Get the right template PDE */
    ValidPde = (PdePointer < MxHighestUserPde) ?
                    MxValidUserPde : MxValidKernelPde;

    /* Allocate a physical page */
    ValidPde.Active.PageFrameNumber = MiAllocatePage(TRUE);

    // make the PFN a page table PFN

    /* Write the new PDE */
    *PdePointer = ValidPde;

    /* Increment count of used and valid entries in the parent's PFN entry */
    ParentPageFrameNumber = MxAddressToPte(PdePointer)->Hard.PageFrameNumber;
    MiIncrementUsedPteCount(ParentPageFrameNumber);
    MiIncrementValidPteCount(ParentPageFrameNumber);
}

PMXPTE
NTAPI
MxReservePtes(
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount)
{
    PMXPTE PxePointer, EndPxe;
    PMXPTE PpePointer, EndPpe, MarginPpe;
    PMXPTE PdePointer, EndPde, MarginPde;
    PMXPTE PtePointer, EndPte, MarginPte;
    ULONG_PTR EndingVpn = StartingVpn + PageCount - 1;

    ASSERT(PageCount > 0);
    // for paged memory IRQL < DISPATCH_LEVEL!
    // must own the WS lock
    // WS lock must prevent page tables from being paged out
    // caller MUST write something into the reserved PTEs

    PxePointer = MxVpnToPxe(StartingVpn);
    PpePointer = MxVpnToPpe(StartingVpn);
    PdePointer = MxVpnToPde(StartingVpn);
    PtePointer = MxVpnToPte(StartingVpn);

    EndPxe = MxVpnToPxe(EndingVpn);
    EndPpe = MxVpnToPpe(EndingVpn);
    EndPde = MxVpnToPde(EndingVpn);
    EndPte = MxVpnToPte(EndingVpn);

    do
    {
        /* Check if the PXE is empty */
        if (PxePointer->Long == 0)
        {
            /* Commit the PDPT */
            MxCommitPageTable(PxePointer);
        }

        /* Calculate the margin for PPEs in this PDPT */
        MarginPpe = MinPtr(MxPteToAddress(PxePointer + 1), EndPpe + 1);
        do
        {
            /* Check if the PPE is empty */
            if (PpePointer->Long == 0)
            {
                /* Commit the PD */
                MxCommitPageTable(PpePointer);
            }

            /* Calculate the margin for PDEs in this PD */
            MarginPde = MinPtr(MxPteToAddress(PpePointer + 1), EndPde + 1);
            do
            {
                /* Check if the PDE is empty */
                if (PdePointer->Long == 0)
                {
                    /* Commit the PT */
                    MxCommitPageTable(PdePointer);
                }

                /* Calculate the margin for PTEs in this PT */
                MarginPte = MinPtr(MxPteToAddress(PdePointer + 1), EndPte + 1);
                do
                {
                    /* Check if the PTE is empty */
                    if (PtePointer->Long == 0)
                    {
                        /* Increment count of used entries in the PT */
                        MiIncrementUsedPteCount(PdePointer->Hard.PageFrameNumber);
                    }

                    /* Go to the next PTE */
                    PtePointer++;
                } while (PtePointer < MarginPte);

                /* Go to the next PDE */
                PdePointer++;
            } while (PdePointer < MarginPde);

            /* Go to the next PPE */
            PpePointer++;
        } while (PpePointer < MarginPpe);

        /* Go to the next PXE */
        PxePointer++;
    } while (PxePointer < EndPxe);

    return MxVpnToPte(StartingVpn);
}

#if 0

VOID
MxDecommitPte(PMXPDE PdePointer)
{
}

VOID
NTAPI
MxReleasePtes(
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount)
{
    MXPTE PxeValue, *PxePointer, *EndPxe;
    MXPTE PpeValue, *PpePointer, *EndPpe, *MarginPpe;
    MXPTE PdeValue, *PdePointer, *EndPde, *MarginPde;
    MXPTE *PtePointer, *EndPte, *MarginPte;

    // for paged memory IRQL < DISPATCH_LEVEL!
    // must own the WS lock

    PxePointer = MxVpnToPxe(StartingVpn);
    PpePointer = MxVpnToPpe(StartingVpn);
    PdePointer = MxVpnToPde(StartingVpn);
    PtePointer = MxVpnToPte(StartingVpn);

    EndPxe = MxVpnToPxe(StartingVpn + PageCount - 1) + 1;
    EndPpe = MxVpnToPpe(StartingVpn + PageCount - 1) + 1;
    EndPde = MxVpnToPde(StartingVpn + PageCount - 1) + 1;
    EndPte = MxVpnToPte(StartingVpn + PageCount - 1) + 1;

    do
    {
        /* Calculate the margin for PPEs in this PDPT */
        MarginPpe = MinPtr(MxPteToAddress(PxePointer + 1), EndPpe);
        do
        {
            /* Calculate the margin for PDEs in this PD */
            MarginPde = MinPtr(MxPteToAddress(PpePointer + 1), EndPde);
            do
            {
                /* Calculate the margin for PTEs in this PT */
                MarginPte = MinPtr(MxPteToAddress(PdePointer + 1), EndPte);
                do
                {
                    if (PtePointer->Long != 0)
                    {
                        /* Decrement count of used entries in the PT */
                        MxDecommitPte(PdePointer);
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
#endif

