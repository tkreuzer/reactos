
#pragma once

#include "ntosbase.h"

namespace Mm {

/* Forward declaration */
struct VAD_NODE;
class VAD_OBJECT;

class VAD_TABLE
{
private:
    LIST_ENTRY m_ListHead;
    KSPIN_LOCK m_ListLock;

    /* We can use ULONG + a bit that says, if this is kernel or user space,
       since the address space on win64 is only  */
    ULONG_PTR m_RangeStartingVpn;
    ULONG_PTR m_RangeEndingVpn;

    VOID
    AcquireTableLock (
        PKLOCK_QUEUE_HANDLE LockHandle);

    VOID
    ReleaseTableLock (
        PKLOCK_QUEUE_HANDLE LockHandle);

    VAD_NODE*
    GetLowestNodeWithEndingVpnNotBelow (
        ULONG_PTR MinimumEndingVpn);

    VAD_NODE*
    GetHighestNodeWithStartingVpnNotAbove (
        ULONG_PTR MaximumStartingVpn);

    VAD_NODE*
    GetNextHigherNode (
        VAD_NODE* Node);

    VAD_NODE*
    GetNextLowerNode (
        VAD_NODE* Node);

    VOID
    InsertBefore (
        VAD_NODE* ReferenceNode,
        VAD_NODE* NewNode);

    VOID
    InsertAfter (
        VAD_NODE* ReferenceNode,
        VAD_NODE* NewNode);

public:

    VOID
    Initialize (
        BOOLEAN KernelMode);

    _Must_inspect_result_
    NTSTATUS
    InsertVadObject (
        _Inout_ VAD_OBJECT* VadObject,
        _In_ ULONG_PTR PageCount,
        _In_ ULONG_PTR LowestStartingVpn,
        _In_ ULONG_PTR HighestEndingVpn,
        _In_opt_ ULONG_PTR BoundaryPageMultiple,
        _In_ BOOLEAN TopDown);

    _Must_inspect_result_
    NTSTATUS
    InsertVadObjectAtVpn (
        _Inout_ VAD_OBJECT* VadObject,
        _In_ ULONG_PTR StartingVpn,
        _In_ ULONG_PTR PageCount);

    VOID
    RemoveVadObject (
        _Inout_ VAD_OBJECT* VadObject);

    _Must_inspect_result_
    VAD_OBJECT*
    ReferenceVadObjectByAddress (
        PVOID Address);


};

//static_assert(sizeof(VAD_TABLE) <= sizeof(MM_AVL_TABLE), "");

extern VAD_TABLE g_KernelVadTable;

} // namespace Mm
