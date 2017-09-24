

#include "Segment.hpp"
#include "../Mapping.hpp"
#include <eal.h>

namespace Mm {

NTSTATUS
SEGMENT::CreateInstance (
    _Out_ PSEGMENT* OutSegment,
    _In_ ULONG_PTR NumberOfPages)
{
    PSEGMENT Segment;
    SIZE_T Size;

    /* Calculate the size of the segment including the PFN array */
    Size = sizeof(SEGMENT) + NumberOfPages * sizeof(UCHAR);

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
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    for (ULONG i = 0; i < NumberOfPages; i++)
    {
        m_ProtectArray[RelativeStartingVpn + i] = static_cast<UCHAR>(Protect);
    }

    return STATUS_SUCCESS;
}

NTSTATUS
SEGMENT::MapPages (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
//    return EalMapSharedMemory(BaseAddress,
//                              RelativeStartingVpn * PAGE_SIZE,
//                              NumberOfPages * PAGE_SIZE,
//                               Protect);
    UNIMPLEMENTED;
    return 0;
}


}; // namespace Mm
