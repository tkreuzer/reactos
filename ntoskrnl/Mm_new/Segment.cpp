/*!

    \file Segment.cpp

    \brief Implements the SEGMENT class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/


#include "Segment.hpp"
#include "Mapping.hpp"

namespace Mm {

/*! \fn SEGMENT::CreateInstance
 *
 *  \brief ...
 *
 *  \param [out] OutSegment -
 *
 *  \param [in] NumberOfPages -
 *
 *  \return ...
 */
NTSTATUS
SEGMENT::CreateInstance (
    _Out_ PSEGMENT* OutSegment,
    _In_ ULONG_PTR NumberOfPages)
{
    PSEGMENT Segment;
    SIZE_T Size;

    /* Calculate the size of the segment including the PFN array */
    //Size = FIELD_OFFSET(SEGMENT, m_ThePtes[NumberOfPages]);
    Size = sizeof(SEGMENT) + NumberOfPages * sizeof(PTE);

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

/*! \fn SEGMENT::CommitDemandZeroPages
 *
 *  \brief ...
 *
 *  \param [in] RelativeStartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
NTSTATUS
SEGMENT::CommitDemandZeroPages (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    PPTE PtePointer;

    PtePointer = m_ThePtes + RelativeStartingVpn;
    while (NumberOfPages--)
    {
        PtePointer->MakeDemandZeroPte(Protect);
        PtePointer++;
    }

    return STATUS_SUCCESS;
}

#if 0
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
#endif

/*! \fn SEGMENT::MapPages
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] RelativeStartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
NTSTATUS
SEGMENT::MapPages (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    NT_ASSERT((RelativeStartingVpn + NumberOfPages) <= m_NumberOfPages);
    return MapPrototypePtes(AddressToVpn(BaseAddress),
                            NumberOfPages,
                            Protect,
                            &m_ThePtes[RelativeStartingVpn]);
}


}; // namespace Mm
