/*!

    \file AddressSpace.hpp

    \brief Contains the definition of the SEGMENT class

    \author Timo Kreuzer

*/

#pragma once

#include "Ob/RefObject.hpp"
#include _ARCH_RELATIVE_(PageTables.hpp)

namespace Mm {

typedef class SEGMENT* PSEGMENT;


class SEGMENT : public REF_OBJECT<SEGMENT, PagedPool, 'OSmM'>
{
    struct _SECTION_IMAGE_INFORMATION_EX* ImageInformation;
    ULONG_PTR m_NumberOfPages;
    //PROTOTYPE m_ThePrototypes[1];
    PTE m_ThePtes[1];

public:

    static
    NTSTATUS
    CreateInstance (
        _Out_ PSEGMENT* OutSegmentObject,
        _In_ ULONG_PTR NumberOfPages);

    NTSTATUS
    CommitDemandZeroPages (
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG Protect);

    NTSTATUS
    MapPages (
        _In_ PVOID BaseAddress,
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG Protect);

    VOID
    MapPages (
        ULONG_PTR MappingVpn,
        ULONG_PTR RelativeStartingVpn,
        ULONG_PTR NumberOfPages,
        ULONG Protect);

};

}; // namespace Mm
