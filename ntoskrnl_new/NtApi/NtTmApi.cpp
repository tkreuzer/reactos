
#include <ntoskrnl.h>
#include <Tm/Tm.hpp>

extern "C" {

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCreateTransactionManager (
    _Out_ PHANDLE TmHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PUNICODE_STRING LogFileName,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ ULONG CommitStrength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtOpenTransactionManager (
    _Out_ PHANDLE TmHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PUNICODE_STRING LogFileName,
    _In_opt_ LPGUID TmIdentity,
    _In_opt_ ULONG OpenOptions)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRenameTransactionManager (
    _In_ PUNICODE_STRING LogFileName,
    _In_ LPGUID ExistingTransactionManagerGuid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCreateResourceManager (
    _Out_ PHANDLE ResourceManagerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE TmHandle,
    _In_ LPGUID RmGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ PUNICODE_STRING Description)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtOpenResourceManager (
    _Out_ PHANDLE ResourceManagerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE TmHandle,
    _In_opt_ LPGUID ResourceManagerGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtGetNotificationResourceManager (
    _In_ HANDLE ResourceManagerHandle,
    _Out_ PTRANSACTION_NOTIFICATION TransactionNotification,
    _In_ ULONG NotificationLength,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_opt_ PULONG ReturnLength,
    _In_ ULONG Asynchronous,
    _In_opt_ ULONG_PTR AsynchronousContext)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCreateTransaction (
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ LPGUID Uow,
    _In_opt_ HANDLE TmHandle,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ ULONG IsolationLevel,
    _In_opt_ ULONG IsolationFlags,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_opt_ PUNICODE_STRING Description)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtOpenTransaction (
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ LPGUID Uow,
    _In_opt_ HANDLE TmHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NtCreateKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _In_ HANDLE TransactionHandle,
    _Out_opt_ PULONG Disposition)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCommitTransaction (
    _In_ HANDLE TransactionHandle,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCreateEnlistment (
    _Out_ PHANDLE EnlistmentHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE ResourceManagerHandle,
    _In_ HANDLE TransactionHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG CreateOptions,
    _In_ NOTIFICATION_MASK NotificationMask,
    _In_opt_ PVOID EnlistmentKey)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtOpenEnlistment (
    _Out_ PHANDLE EnlistmentHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE ResourceManagerHandle,
    _In_ LPGUID EnlistmentGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCommitEnlistment (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtPrePrepareComplete (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtCommitComplete (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtEnumerateTransactionObject (
    _In_opt_ HANDLE RootObjectHandle,
    _In_ KTMOBJECT_TYPE QueryType,
    _Inout_updates_bytes_(ObjectCursorLength) PKTMOBJECT_CURSOR ObjectCursor,
    _In_ ULONG ObjectCursorLength,
    _Out_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtOpenKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE TransactionHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtPrePrepareEnlistment (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtPrepareComplete (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtPrepareEnlistment (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtPropagationComplete(
    _In_ HANDLE ResourceManagerHandle,
    _In_ ULONG RequestCookie,
    _In_ ULONG BufferLength,
    _In_ PVOID Buffer)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtPropagationFailed(
    _In_ HANDLE ResourceManagerHandle,
    _In_ ULONG RequestCookie,
    _In_ NTSTATUS PropStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationEnlistment (
    _In_ HANDLE EnlistmentHandle,
    _In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
    _Out_writes_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
    _In_ ULONG EnlistmentInformationLength,
    _Out_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationResourceManager (
    _In_ HANDLE ResourceManagerHandle,
    _In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
    _Out_writes_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
    _In_ ULONG ResourceManagerInformationLength,
    _Out_opt_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationTransaction (
    _In_ HANDLE TransactionHandle,
    _In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
    _Out_writes_bytes_(TransactionInformationLength) PVOID TransactionInformation,
    _In_ ULONG TransactionInformationLength,
    _Out_opt_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationTransactionManager (
    _In_ HANDLE TransactionManagerHandle,
    _In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
    _Out_writes_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
    _In_ ULONG TransactionManagerInformationLength,
    _Out_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtReadOnlyEnlistment (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRecoverEnlistment (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PVOID EnlistmentKey)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRecoverResourceManager (
    _In_ HANDLE ResourceManagerHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRecoverTransactionManager (
    _In_ HANDLE TransactionManagerHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRollbackComplete (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRollbackEnlistment (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRollbackTransaction (
    _In_ HANDLE TransactionHandle,
    _In_ BOOLEAN Wait)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtRollforwardTransactionManager (
    _In_ HANDLE TransactionManagerHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSetInformationEnlistment (
    _In_opt_ HANDLE EnlistmentHandle,
    _In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
    _In_reads_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
    _In_ ULONG EnlistmentInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSetInformationResourceManager (
    _In_ HANDLE ResourceManagerHandle,
    _In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
    _In_reads_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
    _In_ ULONG ResourceManagerInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSetInformationTransaction (
    _In_ HANDLE TransactionHandle,
    _In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
    _In_reads_bytes_(TransactionInformationLength) PVOID TransactionInformation,
    _In_ ULONG TransactionInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSetInformationTransactionManager (
    _In_opt_ HANDLE TmHandle,
    _In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
    _In_reads_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
    _In_ ULONG TransactionManagerInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtFreezeTransactions (
    _In_ PLARGE_INTEGER FreezeTimeout,
    _In_ PLARGE_INTEGER ThawTimeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtThawTransactions (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSinglePhaseReject (
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
