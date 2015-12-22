/*!

    \file DriverSupport.cpp

    \brief Implements driver management functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include <ldrtypes.h>

extern "C" LIST_ENTRY PsLoadedModuleList;

extern "C" {

/* Internal functions ********************************************************/


/*! \fn MmCheckSystemImage
 *
 *  \brief ...
 *
 *  \param [in] ImageHandle -
 *
 *  \param [in] PurgeSection -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmCheckSystemImage (
    _In_ HANDLE ImageHandle,
    _In_ BOOLEAN PurgeSection)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


/*! \fn MmCallDllInitialize
 *
 *  \brief ...
 *
 *  \param [in] LdrEntry -
 *
 *  \param [in] ListHead -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmCallDllInitialize (
    _In_ struct _LDR_DATA_TABLE_ENTRY* LdrEntry,
    _In_ PLIST_ENTRY ListHead)
{
    UNIMPLEMENTED_DBGBREAK;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmFreeDriverInitialization
 *
 *  \brief ...
 *
 *  \param [in] LdrEntry -
 *
 *  \return ...
 */
VOID
NTAPI
MmFreeDriverInitialization (
    _In_ struct _LDR_DATA_TABLE_ENTRY* LdrEntry)
{
    // find NtHeader
    // loop all sections
        // is section discardable?
            // decommit all pages of that section
    DbgPrint("MmFreeDriverInitialization stub\n");
}

/* Exported functions ********************************************************/

/*! \fn MmAddVerifierThunks
 *
 *  \brief ...
 *
 *  \param [in] ThunkBuffer -
 *
 *  \param [in] ThunkBufferSize -
 *
 *  \return ...
 */
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmAddVerifierThunks (
    _In_reads_bytes_ (ThunkBufferSize) PVOID ThunkBuffer,
    _In_ ULONG ThunkBufferSize)
{
    UNIMPLEMENTED;
    return STATUS_SUCCESS;
}

/*! \fn MmIsDriverVerifying
 *
 *  \brief ...
 *
 *  \param [in] DriverObject -
 *
 *  \return ...
 */
LOGICAL
NTAPI
MmIsDriverVerifying (
    _In_ struct _DRIVER_OBJECT *DriverObject)
{
    UNIMPLEMENTED_DBGBREAK;
    return 0;
}

/*! \fn MmIsVerifierEnabled
 *
 *  \brief ...
 *
 *  \param [in] VerifierFlags -
 *
 *  \return ...
 */
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmIsVerifierEnabled (
    _Out_ PULONG VerifierFlags)
{
    UNIMPLEMENTED;
    return STATUS_SUCCESS;
}

/*! \fn MmPageEntireDriver
 *
 *  \brief ...
 *
 *  \param [in] AddressWithinSection -
 *
 *  \return ...
 */
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
MmPageEntireDriver (
    _In_ PVOID AddressWithinSection)
{
    PLIST_ENTRY ListEntry;
    PLDR_DATA_TABLE_ENTRY LdrEntry;
    PVOID ImageBase = NULL;

    /* Loop the modules on the module list */
    for (ListEntry = PsLoadedModuleList.Flink;
         ListEntry != &PsLoadedModuleList;
         ListEntry = ListEntry->Flink)
    {
        /* Get the loader entry */
        LdrEntry = CONTAINING_RECORD(ListEntry,
                                     LDR_DATA_TABLE_ENTRY,
                                     InLoadOrderLinks);
        if ((AddressWithinSection >= LdrEntry->DllBase) &&
            (AddressWithinSection <= AddToPointer(LdrEntry->DllBase, LdrEntry->SizeOfImage)))
        {
            ImageBase = LdrEntry->DllBase;
            break;
        }
    }

    return ImageBase;
}

/*! \fn MmResetDriverPaging
 *
 *  \brief ...
 *
 *  \param [in] AddressWithinSection -
 *
 *  \return ...
 */
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmResetDriverPaging (
    _In_ PVOID AddressWithinSection)
{
    UNIMPLEMENTED_DBGBREAK;
}


}; // extern "C"
