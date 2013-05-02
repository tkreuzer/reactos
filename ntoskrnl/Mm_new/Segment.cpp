

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
    Size = FIELD_OFFSET(SEGMENT, m_ThePrototypes[NumberOfPages]);

    /* Allocate the segment */
    Segment = new(Size) SEGMENT;
    if (Segment == NULL)
    {
        ERR("Could not allocate a segment\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory(Segment, Size);
    Segment->m_NumberOfPages = NumberOfPages;

    *OutSegment = Segment;
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
                     &m_ThePrototypes[RelativeStartingVpn],
                     Protect);
}


}; // namespace Mm
