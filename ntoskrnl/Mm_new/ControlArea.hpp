/*!

    \file Mm/ControlArea.hpp

    \brief Defines the CONTROL_AREA class for use by section objects

    \copyright Released under the terms of the GNU GPL v2

    \author Timo Kreuzer (timo.kreuzer@reactos.org)

    ...

*/

#pragma once

#include "ntosbase.h"
#include "Ob/RefObject.hpp"

namespace Mm {

typedef class CONTROL_AREA* PCONTROL_AREA;

class CONTROL_AREA : public REF_OBJECT<CONTROL_AREA, NonPagedPool, 'ACmM'>
{
private:
    EX_PUSH_LOCK m_Lock;
    PFILE_OBJECT m_FileObject;
    class SEGMENT* m_Segment;

    CONTROL_AREA (
        VOID);

public:

    ~CONTROL_AREA (
        VOID);

    static
    NTSTATUS
    CreateInstance (
        _Out_ PCONTROL_AREA* OutControlArea);

    static
    NTSTATUS
    ReferenceOrCreateControlArea (
        _Out_ PCONTROL_AREA* OutControlArea,
        _In_ PFILE_OBJECT FileObject,
        _In_ BOOLEAN AsImage);

};

typedef class CONTROL_AREA* PCONTROL_AREA;

}; // namespace Mm
