

#include "VadTable.hpp"

namespace Mm {

ULONG_PTR g_LowestSystemVpn;

inline
VOID
VAD_TABLE::AcquireTableLock (
    VOID)
{
    NT_ASSERT(KeGetCurrentIrql() < DISPATCH_LEVEL);
    KeAcquireGuardedMutex(&m_ListLock);
}

inline
VOID
VAD_TABLE::ReleaseTableLock (
    VOID)
{
    NT_ASSERT(KeGetCurrentIrql() < DISPATCH_LEVEL);
    KeReleaseGuardedMutex(&m_ListLock);
}

VOID
VAD_TABLE::Initialize (
    BOOLEAN KernelMode)
{
    PVOID LowestAddress, HighestAddress;

    InitializeListHead(&m_ListHead);
    KeInitializeGuardedMutex(&m_ListLock);
    if (KernelMode)
    {
        LowestAddress = MmSystemRangeStart;
        HighestAddress = (PVOID)(LONG_PTR)-1;
    }
    else
    {
        LowestAddress = MmLowestUserAddress;
        HighestAddress = MmHighestUserAddress;
    }

    m_RangeStartingVpn = reinterpret_cast<ULONG_PTR>(LowestAddress) >> PAGE_SHIFT;
    m_RangeEndingVpn = (reinterpret_cast<ULONG_PTR>(HighestAddress) >> PAGE_SHIFT) + 1;
}

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
        CurrentNode = CONTAINING_RECORD(m_ListHead.Blink, VAD_NODE, ListEntry);

        if (CurrentNode->EndingVpn >= MinimumEndingVpn)
        {
            return CurrentNode;
        }
    }

    return NULL;
}

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
        CurrentNode = CONTAINING_RECORD(m_ListHead.Blink, VAD_NODE, ListEntry);

        if (CurrentNode->StartingVpn <= MaximumStartingVpn)
        {
            return CurrentNode;
        }
    }

    return NULL;
}

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


_Must_inspect_result_
NTSTATUS
VAD_TABLE::InsertVadObject (
    _Inout_ PVAD_OBJECT VadObject,
    _In_ ULONG PageCount,
    _In_ ULONG_PTR LowestStartingVpn,
    _In_ ULONG_PTR HighestEndingVpn,
    _In_ BOOLEAN TopDown)
{
    ULONG_PTR GapStartingVpn, PostGapStartingVpn;
    PVAD_NODE CurrentNode;
    NTSTATUS Status;

    /* Check if this is a kernel VAD table */
    //if (m_Flags.KernelMode)
    {
        /* Switch to relative VPNs */
        LowestStartingVpn -= g_LowestSystemVpn;
        HighestEndingVpn -= g_LowestSystemVpn;
    }

    /* Default to failure */
    Status = STATUS_INSUFFICIENT_RESOURCES;

    GapStartingVpn = LowestStartingVpn;
    PostGapStartingVpn = HighestEndingVpn + 1;

    /* Lock the table */
    AcquireTableLock();

    /* Check direction */
    if (TopDown)
    {
        /* Find the highest node that starts below our upper limit */
        CurrentNode = GetHighestNodeWithStartingVpnNotAbove(HighestEndingVpn);

        /* Walk the nodes, until we find one completely below our low limit */
        while (CurrentNode && (CurrentNode->EndingVpn >= LowestStartingVpn))
        {
            /* Calculate the gap size (this might be negative) */
            LONG_PTR GapSize = PostGapStartingVpn - CurrentNode->EndingVpn;

            /* Check if this gap is large enough (>, since we are off by 1) */
            if (GapSize > static_cast<LONG_PTR>(PageCount))
            {
                /* Set the starting VPN and break out of the loop */
                GapStartingVpn = PostGapStartingVpn - PageCount;
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
            VadObject->m_Node.StartingVpn = GapStartingVpn;
            VadObject->m_Node.EndingVpn = PostGapStartingVpn - 1;

            /* Insert the VAD *after* the current node, or at the lowest end */
            InsertAfter(CurrentNode, &VadObject->m_Node);
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
            LONG_PTR GapSize = static_cast<ULONG_PTR>(CurrentNode->StartingVpn)
                               - GapStartingVpn;

            /* Check if this gap is large enough */
            if (GapSize >= static_cast<LONG_PTR>(PageCount))
            {
                /* Set the post-gap starting VPN and break out of the loop */
                PostGapStartingVpn = GapStartingVpn + PageCount;
                break;
            }

            /* Otherwise update the lower limit and go to the next node */
            GapStartingVpn = (ULONG_PTR)CurrentNode->EndingVpn + 1;
            CurrentNode = GetNextHigherNode(CurrentNode);
        }

        /* Check if we have a gap and it is large enough */
        if ((PostGapStartingVpn > GapStartingVpn) &&
            (PostGapStartingVpn - GapStartingVpn) >= PageCount)
        {
            /* Set the starting and ending VPN in the node */
            VadObject->m_Node.StartingVpn = GapStartingVpn;
            VadObject->m_Node.EndingVpn = PostGapStartingVpn - 1;

            /* Insert the VAD *before* the current node, or at the lowest end */
            InsertBefore(CurrentNode, &VadObject->m_Node);
            Status = STATUS_SUCCESS;
        }
    }

    /* Unlock the table */
    ReleaseTableLock();

    return Status;
}

_Must_inspect_result_
NTSTATUS
VAD_TABLE::InsertVadObjectAtVpn (
    _Inout_ PVAD_OBJECT VadObject,
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount)
{
    PVAD_NODE VadNode;
    ULONG_PTR EndingVpn;
    NTSTATUS Status;

    /* Check if this is a kernel VAD table */
    //if (m_Flags.KernelMode)
    {
        /* Switch to relative VPNs */
        StartingVpn -= g_LowestSystemVpn;
    }

    /* Calculate ending VPN */
    EndingVpn = StartingVpn + PageCount + 1;

    /* Default to failure */
    Status = STATUS_CONFLICTING_ADDRESSES;

    /* Lock the table */
    AcquireTableLock();

    /* Get the lowest VAD that ends at or above the requested VPN */
    VadNode = GetLowestNodeWithEndingVpnNotBelow(StartingVpn);

    /* Check if there is enough free space */
    if (VadNode->StartingVpn > EndingVpn)
    {
        InsertBefore(VadNode, &VadObject->m_Node);
        Status = STATUS_SUCCESS;
    }

    /* Unlock the table */
    ReleaseTableLock();

    return Status;
}

VOID
VAD_TABLE::RemoveVadObject (
    _Inout_ PVAD_OBJECT VadObject)
{
    /* Lock the table */
    AcquireTableLock();

    /* Remove the list entry */
    RemoveEntryList(&VadObject->m_Node.ListEntry);

    /* Unlock the table */
    ReleaseTableLock();
}

_Must_inspect_result_
PVAD_OBJECT
VAD_TABLE::ReferenceVadObjectByAddress (
    PVOID Address)
{
    ULONG_PTR RequestedVpn;
    PVAD_NODE VadNode;
    VAD_OBJECT* VadObject;

    /* Calculate the VPN for the address */
    RequestedVpn = reinterpret_cast<ULONG_PTR>(Address) >> PAGE_SHIFT;

    /* Default to not found */
    VadObject = NULL;

    /* Lock the table */
    AcquireTableLock();

    /* Get the lowest VAD that ends at or above the requested address */
    VadNode = GetLowestNodeWithEndingVpnNotBelow(RequestedVpn);

    /* Check if the node also begins before our address */
    if (VadNode->StartingVpn <= RequestedVpn)
    {
        /* Get the VAD object and reference it */
        VadObject = CONTAINING_RECORD(VadNode, VAD_OBJECT, m_Node);
        VadObject->AddRef();
    }

    /* Unlock the table */
    ReleaseTableLock();

    return VadObject;
}


} // namespace Mm
