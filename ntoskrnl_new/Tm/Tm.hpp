
#pragma once

// wdm.h
typedef struct _GUID UOW, *PUOW;

// ktmtypes.h
typedef ULONG NOTIFICATION_MASK;
typedef GUID CRM_PROTOCOL_ID, *PCRM_PROTOCOL_ID;

// wdm.h
typedef struct _KTM KTM, *PKTM, *RESTRICTED_POINTER PRKTM;
typedef struct _KRESOURCEMANAGER KRESOURCEMANAGER, *PKRESOURCEMANAGER, *RESTRICTED_POINTER PRKRESOURCEMANAGER;
typedef struct _KENLISTMENT KENLISTMENT, *PKENLISTMENT, *RESTRICTED_POINTER PRKENLISTMENT;

// wdm.h
typedef enum _KTMOBJECT_TYPE
{
    KTMOBJECT_TRANSACTION,
    KTMOBJECT_TRANSACTION_MANAGER,
    KTMOBJECT_RESOURCE_MANAGER,
    KTMOBJECT_ENLISTMENT,
    KTMOBJECT_INVALID
} KTMOBJECT_TYPE, *PKTMOBJECT_TYPE;

// wdm.h
typedef enum _RESOURCEMANAGER_INFORMATION_CLASS
{
    ResourceManagerBasicInformation,
    ResourceManagerCompletionInformation,
} RESOURCEMANAGER_INFORMATION_CLASS;

// wdm.h
typedef enum _TRANSACTION_INFORMATION_CLASS
{
    TransactionBasicInformation,
    TransactionPropertiesInformation,
    TransactionEnlistmentInformation,
    TransactionSuperiorEnlistmentInformation
} TRANSACTION_INFORMATION_CLASS;

// wdm.h
typedef enum _TRANSACTIONMANAGER_INFORMATION_CLASS
{
    TransactionManagerBasicInformation,
    TransactionManagerLogInformation,
    TransactionManagerLogPathInformation,
    TransactionManagerRecoveryInformation = 4
} TRANSACTIONMANAGER_INFORMATION_CLASS;

// ktmtypes.h
typedef struct _TRANSACTION_NOTIFICATION
{
    PVOID         TransactionKey;
    ULONG         TransactionNotification;
    LARGE_INTEGER TmVirtualClock;
    ULONG         ArgumentLength;
} TRANSACTION_NOTIFICATION, *PTRANSACTION_NOTIFICATION;

// wdm.h
typedef enum _ENLISTMENT_INFORMATION_CLASS
{
    EnlistmentBasicInformation,
    EnlistmentRecoveryInformation,
    EnlistmentCrmInformation
} ENLISTMENT_INFORMATION_CLASS;

// wdm.h
typedef struct _KTMOBJECT_CURSOR
{
    GUID LastQuery;
    ULONG ObjectIdCount;
    GUID ObjectIds[1];
} KTMOBJECT_CURSOR, *PKTMOBJECT_CURSOR;

// wdm.h
typedef
NTSTATUS
(NTAPI *PTM_RM_NOTIFICATION) (
    _In_ PKENLISTMENT EnlistmentObject,
    _In_ PVOID RMContext,
    _In_ PVOID TransactionContext,
    _In_ ULONG TransactionNotification,
    _Inout_ PLARGE_INTEGER TmVirtualClock,
    _In_ ULONG ArgumentLength,
    _In_ PVOID Argument);

