#pragma once

#include "ntosbase.h"
#include "VadObject.hpp"

namespace Mm {

extern const char SectionViewVadType[];

class SECTION_VIEW : public VAD_OBJECT
{

public:

    virtual
    const char*
    GetVadType ()
    {
        return SectionViewVadType;
    }

};


}; // namespace Mm
