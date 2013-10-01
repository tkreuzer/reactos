/*!

    \file SectionView.hpp

    \brief Contains the definition of the SECTION_VIEW class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"
#include "VadObject.hpp"

namespace Mm {

class SECTION_VIEW : public VAD_OBJECT
{
    class PHYSICAL_SECTION* m_Section;

public:

    /// FIXME: why can't this shit be protected???
    virtual
    ~SECTION_VIEW (
        VOID)
    {
    }

    virtual
    const char*
    GetVadType () const;

    virtual
    ULONG
    GetMemoryType (
        VOID);

    static
    NTSTATUS
    CreateInstance (
        _Out_ SECTION_VIEW** OutSectionView,
        _In_ class PHYSICAL_SECTION* Section,
        _In_ ULONG Protect);

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
