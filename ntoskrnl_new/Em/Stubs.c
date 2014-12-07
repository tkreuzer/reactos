
#include <ntifs.h>

typedef enum
{
    STATE_FALSE,
    STATE_UNKNOWN,
    STATE_TRUE
} EM_RULE_STATE, *PEM_RULE_STATE;

typedef struct _EM_ENTRY_DATA
{
    PVOID Data;
    ULONG DataLength;
} EM_ENTRY_DATA, *PEM_ENTRY_DATA;
typedef const EM_ENTRY_DATA *PCEM_ENTRY_DATA;

_Function_class_(EM_RULE_STATE_NOTIFY_ROUTINE)
_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_same_
typedef
VOID
(EM_RULE_STATE_NOTIFY_ROUTINE) (
    _In_ EM_RULE_STATE State,
    _In_ LPCGUID RuleId,
    _In_opt_ PVOID Context
    );

typedef EM_RULE_STATE_NOTIFY_ROUTINE *PEM_RULE_STATE_NOTIFY_ROUTINE;
typedef PEM_RULE_STATE_NOTIFY_ROUTINE EM_RULE_STATE_NOTIFY;

typedef struct _EM_CLIENT_NOTIFICATION_REGISTRATION
{
    LPCGUID RuleId;
    EM_RULE_STATE_NOTIFY RuleNotifyCallback;
    PVOID Context;
} EM_CLIENT_NOTIFICATION_REGISTRATION, *PEM_CLIENT_NOTIFICATION_REGISTRATION;

_Function_class_(EM_LAZYENTRY_CALLBACK_ROUTINE)
_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_same_
typedef
VOID
(EM_LAZYENTRY_CALLBACK_ROUTINE) (
    _In_ LPCGUID EntryGuid,
    _In_opt_ PVOID Context
    );

typedef EM_LAZYENTRY_CALLBACK_ROUTINE *PEM_LAZYENTRY_CALLBACK_ROUTINE;
typedef PEM_LAZYENTRY_CALLBACK_ROUTINE EM_LAZYENTRY_CALLBACK;

typedef struct _EM_ENTRY_REGISTRATION {
    LPCGUID EntryGuid;
    EM_LAZYENTRY_CALLBACK LazyEntryCallback;
    PVOID LazyCallbackContext;
} EM_ENTRY_REGISTRATION, *PEM_ENTRY_REGISTRATION;
typedef const EM_ENTRY_REGISTRATION *PCEM_ENTRY_REGISTRATION;

_Function_class_(EM_CALLBACK_ROUTINE)
_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_same_
typedef
EM_RULE_STATE
(EM_CALLBACK_ROUTINE) (
    _In_reads_opt_(NumberofEntries) EM_ENTRY_DATA **InputEntries,
    _In_ ULONG NumberofEntries,
    _In_reads_opt_(NumberofStrings) LPCSTR *InputStrings,
    _In_ ULONG NumberofStrings,
    _In_reads_opt_(NumberofNumerics) PULONG InputNumerics,
    _In_ ULONG NumberofNumerics,
    _In_opt_ PVOID Context
    );

typedef EM_CALLBACK_ROUTINE *PEM_CALLBACK_ROUTINE;
typedef PEM_CALLBACK_ROUTINE EM_CALLBACK_FUNC;

typedef struct _EM_CALLBACK_REGISTRATION {
    LPCGUID CallbackGuid;
    EM_CALLBACK_FUNC CallbackFunction;
    PVOID Context;
} EM_CALLBACK_REGISTRATION, *PEM_CALLBACK_REGISTRATION;

typedef const EM_CALLBACK_REGISTRATION *PCEM_CALLBACK_REGISTRATION;

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
EmClientQueryRuleState(
    _In_ LPCGUID RuleId,
    _Out_ PEM_RULE_STATE State)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
EmClientRuleDeregisterNotification(
    _In_ PVOID NotificationHandle)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
EmClientRuleEvaluate(
    _In_ LPCGUID RuleId,
    _In_reads_(NumberOfEntries) EM_ENTRY_DATA **InputEntries,
    _In_ ULONG NumberOfEntries,
    _Out_ PEM_RULE_STATE State)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
EmClientRuleRegisterNotification(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_reads_(NumberOfNotificatoinRegistration) PEM_CLIENT_NOTIFICATION_REGISTRATION RuleNotificationsRegistration,
    _In_ ULONG NumberOfNotificatoinRegistration,
    _Out_ PVOID *NotificationHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
EmProviderDeregister(
    _In_ PVOID ProviderHandle)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
EmProviderDeregisterEntry(
    _In_ PVOID EntryHandle)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
EmProviderRegister(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_reads_opt_(NumberOfEntry) PCEM_ENTRY_REGISTRATION EntryRegistration,
    _In_ ULONG NumberOfEntry,
    _In_reads_opt_(NumberOfCallback) PCEM_CALLBACK_REGISTRATION CallbackRegistration,
    _In_ ULONG NumberOfCallback,
    _Out_ PVOID *ProviderHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
EmProviderRegisterEntry(
    _In_ PVOID ProviderHandle,
    _In_ LPCGUID EntryId,
    _In_ PCEM_ENTRY_DATA EntryData,
    _Out_ PVOID *EntryHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
EmpProviderRegister(
    _In_opt_ PDRIVER_OBJECT DriverObject,
    _In_reads_opt_(NumberOfEntryRegistration) PCEM_ENTRY_REGISTRATION EntryRegistration,
    _In_ ULONG NumberOfEntryRegistration,
    _In_reads_opt_(NumberOfCallbackRegistration) PCEM_CALLBACK_REGISTRATION CallbackRegistration,
    _In_ ULONG NumberOfCallbackRegistration,
    _Out_ PVOID *ProviderHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}
