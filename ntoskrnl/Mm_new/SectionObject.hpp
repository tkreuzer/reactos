/*!

    \file Mm/SectionObject.hpp

    \brief Defines the SECTION_OBJECT class

    \copyright Released under the terms of the GNU GPL v2

    \author Timo Kreuzer (timo.kreuzer@reactos.org)

    ...

*/

#pragma once

#include "ntosbase.h"
#include "Ob/Object.hpp"

namespace Mm {

class SECTION_OBJECT : public Ob::OBJECT
{
private:

    ULONG64 m_SectionSize;
    ULONG m_SectionFlags;
    ULONG m_PageProtection;

    friend class MEMORY_MANAGER;

    static
    VOID
    InitializeClass (
        VOID);

    static
    VOID
    NTAPI
    ObDeleteProcedure (
        _In_ PVOID Object);

    static
    VOID
    NTAPI
    ObCloseProcedure (
        _In_opt_ PEPROCESS Process,
        _In_ PVOID Object,
        _In_ ACCESS_MASK GrantedAccess,
        _In_ ULONG ProcessHandleCount,
        _In_ ULONG SystemHandleCount);

public:

    _Must_inspect_result_
    static
    NTSTATUS
    CreateInstance (
        _Out_ SECTION_OBJECT** OutSection,
        _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG64 MaximumSize,
        _In_ ULONG SectionPageProtection,
        _In_ ULONG AllocationAttributes,
        _In_opt_ PFILE_OBJECT FileObject);

    PFILE_OBJECT
    GetFileObject (
        VOID);

};

}; // namespace Mm
