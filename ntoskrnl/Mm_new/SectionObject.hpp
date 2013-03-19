/*!
 * \file SectionObject.hpp
 * ...
 */

#pragma once

#include "ntosbase.h"
#include "Ob/Object.hpp"

extern POBJECT_TYPE MmSectionObjectType;

namespace Mm {

class SECTION : public Ob::OBJECT
{
private:

    friend class MEMORY_MANAGER;

    static
    VOID
    InitializeClass (
        VOID);

public:

    _Must_inspect_result_
    static
    NTSTATUS
    CreateObject (
        _Out_ SECTION** OutSection,
        _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG64 MaximumSize,
        _In_ ULONG SectionPageProtection,
        _In_ ULONG AllocationAttributes,
        _In_opt_ PFILE_OBJECT FileObject);

};

}; // namespace Mm
