
#pragma once

#include "Ob/RefObject.hpp"

namespace Mm {

typedef class SEGMENT_OBJECT* PSEGMENT_OBJECT;

class SEGMENT_OBJECT : public REF_OBJECT<SEGMENT_OBJECT, PagedPool, 'OSmM'>
{

public:

    static
    NTSTATUS
    CreateInstance (
        _Out_ PSEGMENT_OBJECT* OutSegmentObject);

};

}; // namespace Mm
