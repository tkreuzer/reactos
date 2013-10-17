/*!

    \file VadTable.cpp

    \brief Implements the VAD_TABLE class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "VadTable.hpp"
#include "VadObject.hpp"

namespace Mm {

ULONG_PTR g_LowestSystemVpn;
VAD_TABLE g_KernelVadTable;

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
VOID
VAD_TABLE::AcquireTableLock (
    PKLOCK_QUEUE_HANDLE LockHandle)
{
    KeAcquireInStackQueuedSpinLock(&m_ListLock, LockHandle);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
VOID
VAD_TABLE::ReleaseTableLock (
    PKLOCK_QUEUE_HANDLE LockHandle)
{
    KeReleaseInStackQueuedSpinLock(LockHandle);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
VOID
VAD_TABLE::Initialize (
    BOOLEAN KernelMode)
{
    InitializeListHead(&m_ListHead);
    KeInitializeSpinLock(&m_ListLock);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
PVAD_NODE
VAD_TABLE::GetLowestNodeWithEndingVpnNotBelow (
    ULONG_PTR MinimumEndingVpn)
{
    PLIST_ENTRY ListEntry;
    PVAD_NODE CurrentNode;

    for (ListEntry = m_ListHead.Flink;
         ListEntry != &m_ListHead;
         ListEntry = ListEntry->Flink)
    {
        CurrentNode = CONTAINING_RECORD(ListEntry, VAD_NODE, ListEntry);

        if (CurrentNode->EndingVpn >= MinimumEndingVpn)
        {
            return CurrentNode;
        }
    }

    return NULL;
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
PVAD_NODE
VAD_TABLE::GetHighestNodeWithStartingVpnNotAbove (
    ULONG_PTR MaximumStartingVpn)
{
    PLIST_ENTRY ListEntry;
    PVAD_NODE CurrentNode;

    for (ListEntry = m_ListHead.Blink;
         ListEntry != &m_ListHead;
         ListEntry = ListEntry->Blink)
    {
        CurrentNode = CONTAINING_RECORD(ListEntry, VAD_NODE, ListEntry);

        if (CurrentNode->StartingVpn <= MaximumStartingVpn)
        {
            return CurrentNode;
        }
    }

    return NULL;
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
PVAD_NODE
VAD_TABLE::GetNextHigherNode (
    PVAD_NODE Node)
{
    if (Node->ListEntry.Flink == &m_ListHead)
    {
        return NULL;
    }

    return CONTAINING_RECORD(Node->ListEntry.Flink, VAD_NODE, ListEntry);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
PVAD_NODE
VAD_TABLE::GetNextLowerNode (
    PVAD_NODE Node)
{
    if (Node->ListEntry.Blink == &m_ListHead)
    {
        return NULL;
    }

    return CONTAINING_RECORD(Node->ListEntry.Blink, VAD_NODE, ListEntry);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
VOID
VAD_TABLE::InsertBefore (
    PVAD_NODE ReferenceNode,
    PVAD_NODE NewNode)
{
    if (ReferenceNode == NULL)
    {
        InsertTailList(&m_ListHead, &NewNode->ListEntry);
    }
    else
    {
        InsertTailList(&ReferenceNode->ListEntry, &NewNode->ListEntry);
    }
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
inline
VOID
VAD_TABLE::InsertAfter (
    PVAD_NODE ReferenceNode,
    PVAD_NODE NewNode)
{
    if (ReferenceNode == NULL)
    {
        InsertHeadList(&m_ListHead, &NewNode->ListEntry);
    }
    else
    {
        InsertHeadList(&ReferenceNode->ListEntry, &NewNode->ListEntry);
    }
}


/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
_Must_inspect_result_
NTSTATUS
VAD_TABLE::InsertVadObject (
    _Inout_ PVAD_OBJECT VadObject,
    _In_ ULONG_PTR PageCount,
    _In_ ULONG_PTR LowestStartingVpn,
    _In_ ULONG_PTR HighestEndingVpn,
    _In_opt_ ULONG_PTR BoundaryPageMultiple,
    _In_ BOOLEAN TopDown)
{
    ULONG_PTR GapStartingVpn, PostGapStartingVpn;
    PVAD_NODE CurrentNode;
    NTSTATUS Status;
    KLOCK_QUEUE_HANDLE LockHandle;
    NT_ASSERT(PageCount != 0);

    /* Make sure the VAD was not already inserted */
    NT_ASSERT(IsListEmpty(&VadObject->ListEntry));
    NT_ASSERT(VadObject->m_Flags.Inserted == FALSE);

    /* Check parameter */
    if (PageCount > MAXLONG_PTR)
    {
        return STATUS_INVALID_PARAMETER;
    }

    if (BoundaryPageMultiple == 0)
        BoundaryPageMultiple = 1;

    /* Default to failure */
    Status = STATUS_INSUFFICIENT_RESOURCES;

    GapStartingVpn = ALIGN_UP_BY(LowestStartingVpn, BoundaryPageMultiple);
    PostGapStartingVpn = HighestEndingVpn + 1;

    /* Lock the table */
    AcquireTableLock(&LockHandle);

    /* Check direction */
    if (TopDown)
    {
        /* Find the highest node that starts below our upper limit */
        CurrentNode = GetHighestNodeWithStartingVpnNotAbove(HighestEndingVpn);

        /* Walk the nodes, until we find one completely below our low limit */
        while (CurrentNode && (CurrentNode->EndingVpn >= LowestStartingVpn))
        {
            GapStartingVpn = ALIGN_UP_BY(CurrentNode->EndingVpn + 1,
                                         BoundaryPageMultiple);

            /* Calculate the gap size (this might be negative) */
            LONG_PTR GapSize = PostGapStartingVpn - GapStartingVpn;

            /* Check if this gap is large enough */
            if (GapSize >= static_cast<LONG_PTR>(PageCount))
            {
                /* Set the starting VPN and break out of the loop */
                GapStartingVpn = ALIGN_DOWN_BY(PostGapStartingVpn - PageCount,
                                               BoundaryPageMultiple);
                break;
            }

            /* Otherwise update the upper limit and go to the next node */
            PostGapStartingVpn = CurrentNode->StartingVpn;
            CurrentNode = GetNextLowerNode(CurrentNode);
        }

        /* Check if we have a gap and it is large enough */
        if ((PostGapStartingVpn > GapStartingVpn) &&
            (PostGapStartingVpn - GapStartingVpn) >= PageCount)
        {
            /* Set the starting and ending VPN in the node */
            VadObject->StartingVpn = PostGapStartingVpn - PageCount;
            VadObject->EndingVpn = PostGapStartingVpn - 1;

            /* Insert the VAD *after* the current node, or at the lowest end */
            InsertAfter(CurrentNode, VadObject);
            Status = STATUS_SUCCESS;
        }
    }
    else
    {
        /* Find the lowest node that ends above our lower limit */
        CurrentNode = GetLowestNodeWithEndingVpnNotBelow(LowestStartingVpn);

        /* Walk the nodes, until we find one completely above our high limit */
        while (CurrentNode && (CurrentNode->StartingVpn <= HighestEndingVpn))
        {
            /* Calculate the gap size (this might be negative) */
            LONG_PTR GapSize = CurrentNode->StartingVpn - GapStartingVpn;

            /* Check if this gap is large enough */
            if (GapSize >= static_cast<LONG_PTR>(PageCount))
            {
                /* Set the post-gap starting VPN and break out of the loop */
                PostGapStartingVpn = GapStartingVpn + PageCount;
                break;
            }

            /* Otherwise update the lower limit and go to the next node */
            GapStartingVpn = ALIGN_UP_BY(CurrentNode->EndingVpn + 1,
                                         BoundaryPageMultiple);
            CurrentNode = GetNextHigherNode(CurrentNode);
        }

        /* Check if we have a gap and it is large enough */
        if ((PostGapStartingVpn > GapStartingVpn) &&
            (PostGapStartingVpn - GapStartingVpn) >= PageCount)
        {
            /* Set the starting and ending VPN in the node */
            VadObject->StartingVpn = GapStartingVpn;
            VadObject->EndingVpn = GapStartingVpn + PageCount - 1;

            /* Insert the VAD *before* the current node, or at the lowest end */
            InsertBefore(CurrentNode, VadObject);
            Status = STATUS_SUCCESS;
         }
    }

    /* Unlock the table */
    ReleaseTableLock(&LockHandle);

    if (NT_SUCCESS(Status))
    {
        /* Add a reference to the VAD object */
        VadObject->AddRef();
        VadObject->m_Flags.Inserted = TRUE;
    }

    return Status;
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
_Must_inspect_result_
NTSTATUS
VAD_TABLE::InsertVadObjectAtVpn (
    _Inout_ PVAD_OBJECT VadObject,
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR PageCount)
{
    PVAD_NODE VadNode;
    ULONG_PTR EndingVpn;
    NTSTATUS Status;
    KLOCK_QUEUE_HANDLE LockHandle;
    NT_ASSERT(StartingVpn != 0);
    NT_ASSERT(PageCount != 0);

    //DbgPrint("! %lx - %lx\n", StartingVpn, StartingVpn + PageCount);

    /* Make sure the VAD was not already inserted */
    NT_ASSERT(IsListEmpty(&VadObject->ListEntry));
    NT_ASSERT(VadObject->m_Flags.Inserted == FALSE);

    /* Calculate ending VPN */
    EndingVpn = StartingVpn + PageCount - 1;
    VadObject->StartingVpn = StartingVpn;
    VadObject->EndingVpn = EndingVpn;

    /* Default to failure */
    Status = STATUS_CONFLICTING_ADDRESSES;

    /* Lock the table */
    AcquireTableLock(&LockHandle);

    /* Get the lowest VAD that ends at or above the requested VPN */
    VadNode = GetLowestNodeWithEndingVpnNotBelow(StartingVpn);

    /* Check if there is enough free space */
    if ((VadNode == NULL) || (VadNode->StartingVpn > EndingVpn))
    {
        InsertBefore(VadNode, VadObject);
        Status = STATUS_SUCCESS;

        /* Add a reference to the VAD object */
        VadObject->AddRef();
        VadObject->m_Flags.Inserted = TRUE;
    }

    /* Unlock the table */
    ReleaseTableLock(&LockHandle);

    return Status;
}

#if 0
/// HACK
_Must_inspect_result_
NTSTATUS
VAD_TABLE::InsertVadObject (
    _Inout_ PVAD_OBJECT VadObject,
    _In_ ULONG_PTR PageCount,
    _In_ ULONG_PTR LowestStartingVpn,
    _In_ ULONG_PTR HighestEndingVpn,
    _In_opt_ ULONG_PTR BoundaryPageMultiple,
    _In_ BOOLEAN TopDown)
{
    PVOID BaseAddress;

    BaseAddress = EalReserveVirtualMemory(PageCount * PAGE_SIZE,
                                          LowestStartingVpn,
                                          HighestEndingVpn)
}
#endif

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
VOID
VAD_TABLE::RemoveVadObject (
    _Inout_ PVAD_OBJECT VadObject)
{
    KLOCK_QUEUE_HANDLE LockHandle;

    /* Lock the table */
    AcquireTableLock(&LockHandle);

    /* Remove the list entry */
    RemoveEntryList(&VadObject->ListEntry);

    /* Release the VAD object */
    VadObject->Release();
    VadObject->m_Flags.Inserted = FALSE;

    /* Unlock the table */
    ReleaseTableLock(&LockHandle);
}

/*! \fn xxxxxxxxxx
 *
 *  \brief ...
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \param [in] xxxxxx -
 *
 *  \return ...
 */
_Must_inspect_result_
PVAD_OBJECT
VAD_TABLE::GetVadObjectByAddress (
    PVOID Address)
{
    ULONG_PTR RequestedVpn;
    PVAD_NODE VadNode;
    VAD_OBJECT* VadObject;

    /* Calculate the VPN for the address */
    RequestedVpn = AddressToVpn(Address);

    /* Get the lowest VAD that ends at or above the requested address */
    VadNode = GetLowestNodeWithEndingVpnNotBelow(RequestedVpn);

    /* Check if we found anything */
    if (VadNode != NULL)
    {
        /* Get the VAD object */
        VadObject = static_cast<VAD_OBJECT*>(VadNode);
    }
    else
    {
        /* Not found */
        VadObject = NULL;
    }

    return VadObject;
}


} // namespace Mm
