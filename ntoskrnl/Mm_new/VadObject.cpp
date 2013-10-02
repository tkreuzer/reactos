/*!

    \file VadObject.cpp

    \brief Implements the VAD_OBJECT class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "VadObject.hpp"
#include "Mapping.hpp"

namespace Mm {

const char VadObjectVadType[] = "VadObject";

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] OutVadObject -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
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

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 */
inline
VOID
VAD_OBJECT::AcquireLock (
    VOID)
{
    KeEnterCriticalRegion();
    //ExAcquirePushLockExclusive(&m_Lock);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 */
inline
VOID
VAD_OBJECT::ReleaseLock (
    VOID)
{
    KeLeaveCriticalRegion();
    //ExReleasePushLock(&m_Lock);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \return ...
 */
ULONG
VAD_OBJECT::GetMemoryType (
    VOID)
{
    return MEM_PRIVATE;
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \return ...
 */
const char*
VAD_OBJECT::GetVadType (
    VOID) const
{
    return VadObjectVadType;
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \return ...
 */
NTSTATUS
VAD_OBJECT::CommitPages (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    ULONG_PTR EndingVpn;
    NTSTATUS Status;

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

    AcquireLock();

    /* Check if the VAD object is inserted */
    if (!m_Flags.Inserted)
    {
        ReleaseLock();
        return STATUS_NOT_COMMITTED;
    }

    /* Map the pages */
    Status = MapVirtualMemory(StartingVpn, NumberOfPages, Protect);

    ReleaseLock();

    return Status;
}

}; // namespace Mm

