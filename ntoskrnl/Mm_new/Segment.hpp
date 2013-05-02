
#pragma once

#include "Ob/RefObject.hpp"

namespace Mm {

typedef class SEGMENT* PSEGMENT;


class SEGMENT : public REF_OBJECT<SEGMENT, PagedPool, 'OSmM'>
{
    struct _SECTION_IMAGE_INFORMATION_EX* ImageInformation;
    ULONG_PTR m_NumberOfPages;
    PROTOTYPE m_ThePrototypes[1];

public:

    static
    NTSTATUS
    CreateInstance (
        _Out_ PSEGMENT* OutSegmentObject,
        _In_ ULONG_PTR NumberOfPages);

    VOID
    MapPages (
        ULONG_PTR MappingVpn,
        ULONG_PTR RelativeStartingVpn,
        ULONG_PTR NumberOfPages,
        ULONG Protect);

};

}; // namespace Mm
