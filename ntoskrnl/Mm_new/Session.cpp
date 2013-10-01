/*!

    \file Session.cpp

    \brief Implements session related functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"

extern "C" {

// private

/*! \fn MmSessionCreate
 *
 *  \brief ...
 *
 *  \param [out] SessionId -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmSessionCreate (
    _Out_ PULONG SessionId)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmSessionDelete
 *
 *  \brief ...
 *
 *  \param [in] SessionId -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmSessionDelete (
    _In_ ULONG SessionId)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmGetSessionId
 *
 *  \brief ...
 *
 *  \param [in] Process -
 *
 *  \return ...
 */
ULONG
NTAPI
MmGetSessionId (
    _In_ PEPROCESS Process)
{
    UNIMPLEMENTED;
    return 0;
}

/*! \fn MmGetSessionLocaleId
 *
 *  \brief ...
 *
 *  \return ...
 */
ULONG
NTAPI
MmGetSessionLocaleId (
    VOID)
{
    UNIMPLEMENTED;
    return 0;
}

/*! \fn MmIsSessionAddress
 *
 *  \brief ...
 *
 *  \param [in] Address -
 *
 *  \return ...
 */
BOOLEAN
NTAPI
MmIsSessionAddress (
    _In_ PVOID Address)
{
    //UNIMPLEMENTED;
    return FALSE;
}

}; // extern "C"
