
#include "KernelVad.hpp"
#include "CommitCharge.hpp"

namespace Mm {

const char KernelVadType[] = "KernelVad";

VOID
KERNEL_VAD::Initialize (
    VOID)
{
    new(this) KERNEL_VAD;
}

NTSTATUS
KERNEL_VAD::CreateInstance (
    _Out_ KERNEL_VAD** OutKernelVad)
{
    KERNEL_VAD* NewVad;

    /* Allocate a new VAD from non-paged pool */
    NewVad = reinterpret_cast<KERNEL_VAD*>(
                ExAllocatePoolWithTag(NonPagedPool, sizeof(KERNEL_VAD), 'daVM'));
    if (NewVad == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Initialize it */
    NewVad->Initialize();

    *OutKernelVad = NewVad;
    return STATUS_SUCCESS;
}


const char*
KERNEL_VAD::GetVadType () const
{
    return KernelVadType;
}

NTSTATUS
KERNEL_VAD::OnPageFault (
    PVOID FaultAddress,
    ULONG_PTR PteContext)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


/// \todo We can probably add a generic routine and a CommitPagesImpl()
/// virtual implementation. The generic one can do the checks, etc.
NTSTATUS
KERNEL_VAD::CommitPages (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn,
    _In_ ULONG Protect)
{
#if 0
    ULONG_PTR EndingVpn;

    // Check range
    if ((StartingVpn < GetStartingVpn()) || (EndingVpn > GetEndingVpn()) ||
        (StartingVpn > EndingVpn))
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Check protection */
    // ignore for now and use read/write/execute

    /* Charge system commit */
    Status = ChargeSystemCommit(NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Lock the VAD */
    AcquireLock();

    /* Reserve PTEs and get the actual number of pages we are committing */
    ReservePtes(StartingVpn, EndingVpn, &NumberOfUncomittedPages);

    /* We want global pages for the kernel! */
    Protect |= PAGE_GLOBAL;

    /* Check if this is non-paged */
    if (m_Flags.NonPaged)
    {

    }

    SetPageMapping(StartingVpn, EndingVpn, Protect, &CommitCharge);

Cleanup:
    ReleaseLock();
#endif
    return STATUS_NOT_IMPLEMENTED;
}

#if 0
NTSTATUS
KERNEL_VAD::DecommitPages (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR EndingVpn)
{

    /* We need to cleanup what we allocated */
    for (PtePointer = StartingPte; NumberOfPages-- > 0; PtePointer++)
    {
        /* Get the page frame number */
        PageFrameNumber = PtePointer->GetPageFrameNumber();

        /* Zero out the PTE and invalidate the TLB */
        *PtePointer = PTE::EmptyPte;
        KeInvalidateTlbEntry(PteToAddress(PtePointer));

        /* Release the page */
        g_PfnDatabase.ReleasePage(PageFrameNumber);
    }


}

MapPages()
{
    // allocate pages and write PTEs
    for (PtePointer = StartingPte; NumberOfPages-- > 0; PtePointer++)
    {
        /* Allocate a physical page */
        PageFrameNumber = g_PfnDatabase.AllocateReservedZeroedPage();
        if (PageFrameNumber == 0)
        {
            /* Calculate the last VPN that we committed */
            EndingVpn -= (NumberOfPages + 1);
            if (EndingVpn >= StaringVpn)
            {
                /* Decommit the pages we already committed */
                DecommitPages(StartingVpn, EndingVpn);
            }

            Status = STATUS_NO_MEMORY;
        }

        /* Map the page */
        NT_ASSERT(!PtePointer->IsValid());
        *PtePointer = PTE::CreateValidKernelPte(PageFrameNumber);
    }
}

MapDemandZeroPtes()
{

    for (PtePointer = StartingPte; NumberOfPages-- > 0; PtePointer++)
    {
        /* Map a demand zero PTE */
        *PtePointer = PTE::CreateDemandZeroPte();
    }

}

#endif

}; // namespace Mm
