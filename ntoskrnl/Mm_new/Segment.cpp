

#include "Segment.hpp"
#include "Mapping.hpp"

namespace Mm {

NTSTATUS
SEGMENT::CreateInstance (
    _Out_ PSEGMENT* OutSegment,
    _In_ ULONG_PTR NumberOfPages)
{
    PSEGMENT Segment;
    SIZE_T Size;

    /* Calculate the size of the segment including the PFN array */
    Size = FIELD_OFFSET(SEGMENT, m_ThePtes[NumberOfPages]);

    /* Allocate the segment */
    Segment = new(Size) SEGMENT;
    if (Segment == NULL)
    {
        ERR("Could not allocate a segment\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Initialize the segment */
    RtlZeroMemory(Segment, Size);
    Segment->m_NumberOfPages = NumberOfPages;

    *OutSegment = Segment;
    return STATUS_SUCCESS;
}

NTSTATUS
SEGMENT::CommitDemandZeroPages (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages)
{
    PPTE PtePointer;

    PtePointer = m_ThePtes + RelativeStartingVpn;
    while (NumberOfPages--)
    {
        PtePointer->MakeDemandZeroPte(MM_READWRITE); /// \todo protection!
        PtePointer++;
    }

    return STATUS_SUCCESS;
}


VOID
SEGMENT::MapPages (
    ULONG_PTR StartingVpn,
    ULONG_PTR RelativeStartingVpn,
    ULONG_PTR NumberOfPages,
    ULONG Protect)
{
    NT_ASSERT((RelativeStartingVpn + NumberOfPages) <= m_NumberOfPages);
    MapPrototypePtes(StartingVpn,
                     NumberOfPages,
                     &m_ThePtes[RelativeStartingVpn],
                     Protect);
}


}; // namespace Mm
