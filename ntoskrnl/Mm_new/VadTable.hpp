
#pragma once

#include "VadObject.hpp"

namespace Mm {

class VAD_TABLE
{
private:
    LIST_ENTRY m_ListHead;
    KGUARDED_MUTEX m_ListLock;

    /* We can use ULONG + a bit that says, if this is kernel or user space,
       since the address space on win64 is only  */
    ULONG_PTR m_RangeStartingVpn;
    ULONG_PTR m_RangeEndingVpn;

    VOID
    AcquireTableLock (
        VOID);

    VOID
    ReleaseTableLock (
        VOID);

    PVAD_NODE
    GetLowestNodeWithEndingVpnNotBelow (
        ULONG_PTR MinimumEndingVpn);

    PVAD_NODE
    GetHighestNodeWithStartingVpnNotAbove (
        ULONG_PTR MaximumStartingVpn);

    PVAD_NODE
    GetNextHigherNode (
        PVAD_NODE Node);

    PVAD_NODE
    GetNextLowerNode (
        PVAD_NODE Node);

    VOID
    InsertBefore (
        PVAD_NODE ReferenceNode,
        PVAD_NODE NewNode);

    VOID
    InsertAfter (
        PVAD_NODE ReferenceNode,
        PVAD_NODE NewNode);

public:

    VOID
    Initialize (
        BOOLEAN KernelMode);

    _Must_inspect_result_
    NTSTATUS
    InsertVadObject (
        _Inout_ PVAD_OBJECT VadObject,
        _In_ ULONG PageCount,
        _In_ ULONG_PTR LowestStartingVpn,
        _In_ ULONG_PTR HighestEndingVpn,
        _In_ BOOLEAN TopDown);

    _Must_inspect_result_
    NTSTATUS
    InsertVadObjectAtVpn (
        _Inout_ PVAD_OBJECT VadObject,
        _In_ ULONG_PTR StartingVpn,
        _In_ ULONG PageCount);

    VOID
    RemoveVadObject (
        _Inout_ PVAD_OBJECT VadObject);

    _Must_inspect_result_
    PVAD_OBJECT
    ReferenceVadObjectByAddress (
        PVOID Address);


};

} // namespace Mm
