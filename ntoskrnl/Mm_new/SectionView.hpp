#pragma once

#include "ntosbase.h"
#include "VadObject.hpp"

namespace Mm {

class SECTION_VIEW : public VAD_OBJECT
{
    class SECTION* m_Section;

public:

    virtual
    const char*
    GetVadType () const;

    static
    NTSTATUS
    CreateInstance (
        _Out_ SECTION_VIEW** OutSectionView,
        _In_ class SECTION_OBJECT* SectionObject);

    virtual
    NTSTATUS
    CommitPages (
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG Protect);

};

typedef class SECTION_VIEW* PSECTION_VIEW;

}; // namespace Mm
