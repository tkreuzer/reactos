
#include <ntoskrnl.h>
#include <Ke/Ke.hpp>
#include <Tm.hpp>

extern "C" {

typedef struct _GUID *PGUID;
typedef struct _KTRANSACTION *PKTRANSACTION;

// prototypes from wdm.h

#if 0
@ stub TmCancelPropagationRequest
@ stub TmCurrentTransaction
@ stub TmEndPropagationRequest
@ stub TmEnlistmentObjectType
@ stub TmFreezeTransactions
@ stub TmInitSystem
@ stub TmInitSystemPhase2
@ stub TmIsKTMCommitCoordinator
@ stub TmResourceManagerObjectType
@ stub TmSetCurrentTransaction
@ stub TmThawTransactions
@ stub TmTransactionManagerObjectType
@ stub TmTransactionObjectType
#endif

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmInitializeTransactionManager (
    _In_ PRKTM TransactionManager,
    _In_opt_ PCUNICODE_STRING LogFileName,
    _In_opt_ PGUID TmId,
    _In_ ULONG CreateOptions)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRenameTransactionManager (
    _In_ PUNICODE_STRING LogFileName,
    _In_ LPGUID ExistingTransactionManagerGuid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRecoverTransactionManager (
    _In_ PKTM Tm,
    _In_ PLARGE_INTEGER TargetVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
TmCommitTransaction (
    _In_ PKTRANSACTION Transaction,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRollbackTransaction (
    _In_ PKTRANSACTION Transaction,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmCreateEnlistment (
    _Out_ PHANDLE EnlistmentHandle,
    _In_ KPROCESSOR_MODE PreviousMode,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PRKRESOURCEMANAGER ResourceManager,
    _In_ PKTRANSACTION Transaction,
    _In_opt_ ULONG CreateOptions,
    _In_ NOTIFICATION_MASK  NotificationMask,
    _In_opt_ PVOID EnlistmentKey)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRecoverEnlistment (
    _In_ PKENLISTMENT Enlistment,
    _In_ PVOID        EnlistmentKey)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmPrePrepareEnlistment (
    _In_ PKENLISTMENT Enlistment,
    _In_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmPrepareEnlistment (
    _In_ PKENLISTMENT Enlistment,
    _In_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmCommitEnlistment (
    _In_ PKENLISTMENT Enlistment,
    _In_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRollbackEnlistment (
    _In_ PKENLISTMENT Enlistment,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmPrePrepareComplete (
    _In_ PKENLISTMENT Enlistment,
    _In_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmPrepareComplete (
    _In_ PKENLISTMENT Enlistment,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmReadOnlyEnlistment (
    _In_ PKENLISTMENT Enlistment,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmCommitComplete (
    _In_ PKENLISTMENT Enlistment,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRollbackComplete (
    _In_ PKENLISTMENT Enlistment,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmReferenceEnlistmentKey (
    _In_ PKENLISTMENT Enlistment,
    _Out_ PVOID *Key)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmDereferenceEnlistmentKey (
    _In_ PKENLISTMENT Enlistment,
    _Out_opt_ PBOOLEAN LastReference)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmSinglePhaseReject (
    _In_ PKENLISTMENT Enlistment,
    _In_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRequestOutcomeEnlistment (
    _In_ PKENLISTMENT Enlistment,
    _In_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmEnableCallbacks (
    _In_ PKRESOURCEMANAGER ResourceManager,
    _In_ PTM_RM_NOTIFICATION CallbackRoutine,
    _In_opt_ PVOID RMKey)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmRecoverResourceManager (
    _In_ PKRESOURCEMANAGER ResourceManager)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmPropagationComplete (
    _In_  PKRESOURCEMANAGER ResourceManager,
    _In_  ULONG RequestCookie,
    _In_  ULONG BufferLength,
    _In_  PVOID Buffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
TmPropagationFailed (
    _In_  PKRESOURCEMANAGER ResourceManager,
    _In_  ULONG RequestCookie,
    _In_  NTSTATUS Status)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
VOID
NTAPI
TmGetTransactionId (
    _In_ PKTRANSACTION Transaction,
    _Out_ PUOW TransactionId)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
TmIsTransactionActive (
    _In_ PKTRANSACTION Transaction)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"

