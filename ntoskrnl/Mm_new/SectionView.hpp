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
        _In_ class SECTION* Section);

    NTSTATUS
    CreateMapping (
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG_PTR CommitSizeInPages,
        _In_ ULONG Protect);

    virtual
    NTSTATUS
    CommitPages (
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG Protect);

};

typedef class SECTION_VIEW* PSECTION_VIEW;

}; // namespace Mm
