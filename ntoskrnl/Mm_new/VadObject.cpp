/*!

    @file VadObject.cpp

    @brief Implements the VAD_OBJECT class

    @author Timo Kreuzer

*/

#include "VadObject.hpp"
#include "Mapping.hpp"

namespace Mm {

const char VadObjectVadType[] = "VadObject";

NTSTATUS
VAD_OBJECT::CreateInstance (
    _Out_ VAD_OBJECT** OutVadObject,
    _In_ ULONG Protect)
{
    VAD_OBJECT* NewVad;

    /* Allocate a new VAD from non-paged pool */
    NewVad = new(NonPagedPool, sizeof(VAD_OBJECT), 'daVM') VAD_OBJECT;
    if (NewVad == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    NewVad->m_Protect = Protect;

    *OutVadObject = NewVad;
    return STATUS_SUCCESS;
}

ULONG
VAD_OBJECT::GetMemoryType (
    VOID)
{
    return MEM_PRIVATE;
}

const char*
VAD_OBJECT::GetVadType (
    VOID) const
{
    return VadObjectVadType;
}

NTSTATUS
VAD_OBJECT::CommitPages (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    ULONG_PTR EndingVpn;

    /* Check parameter */
    EndingVpn = StartingVpn + NumberOfPages - 1;
    if ((NumberOfPages == 0) || (EndingVpn < StartingVpn))
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Check the range */
    if ((StartingVpn < GetStartingVpn()) || (EndingVpn > GetEndingVpn()))
    {
        return STATUS_UNSUCCESSFUL;
    }

    /* Map the pages */
    return MapVirtualMemory(StartingVpn, NumberOfPages, Protect);
}

}; // namespace Mm

