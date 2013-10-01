/*!

    \file Paging.cpp

    \brief Implements paging related functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"

extern "C" {

/*! \fn MmTrimAllSystemPageableMemory
 *
 *  \brief ...
 *
 *  \param [in] PurgeTransitionList -
 *
 *  \return ...
 */
ULONG
NTAPI
MmTrimAllSystemPageableMemory (
    _In_ ULONG PurgeTransitionList)
{
    UNIMPLEMENTED;
    return 0;
}

/*! \fn MmTrimAllSystemPageableMemory
 *
 *  \brief ...
 *
 *  \param [in] FileObject -
 *
 *  \return ...
 */
BOOLEAN
NTAPI
MmIsFileObjectAPagingFile (
    _In_ PFILE_OBJECT FileObject)
{
    UNIMPLEMENTED;
    return 0;
}

/*! \fn NtCreatePagingFile
 *
 *  \brief ...
 *
 *  \param [in] FileName -
 *
 *  \param [in] InitialSize -
 *
 *  \param [in] MaxiumSize -
 *
 *  \param [in] Reserved -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
NtCreatePagingFile (
    _In_ PUNICODE_STRING FileName,
    _In_ PLARGE_INTEGER InitialSize,
    _In_ PLARGE_INTEGER MaxiumSize,
    _In_ ULONG Reserved)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
