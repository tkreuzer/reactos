
#pragma once

#include <ntoskrnl.h>
#include <Ke/Ke.hpp>

#define PCW_VERSION_1 0x0100
#define PCW_CURRENT_VERSION PCW_VERSION_1

typedef struct _PCW_INSTANCE *PPCW_INSTANCE;
typedef struct _PCW_REGISTRATION *PPCW_REGISTRATION;
typedef struct _PCW_BUFFER *PPCW_BUFFER;

typedef struct _PCW_COUNTER_DESCRIPTOR
{
    USHORT Id;
    USHORT StructIndex;
    USHORT Offset;
    USHORT Size;
} PCW_COUNTER_DESCRIPTOR, *PPCW_COUNTER_DESCRIPTOR;

typedef struct _PCW_DATA
{
    _In_reads_bytes_(Size) const VOID *Data;
    _In_ ULONG Size;
} PCW_DATA, *PPCW_DATA;

typedef struct _PCW_COUNTER_INFORMATION
{
    ULONG64 CounterMask;
    PCUNICODE_STRING InstanceMask;
} PCW_COUNTER_INFORMATION, *PPCW_COUNTER_INFORMATION;

typedef struct _PCW_MASK_INFORMATION
{
    ULONG64 CounterMask;
    PCUNICODE_STRING InstanceMask;
    ULONG InstanceId;
    BOOLEAN CollectMultiple;
    PPCW_BUFFER Buffer;
    PKEVENT CancelEvent;
} PCW_MASK_INFORMATION, *PPCW_MASK_INFORMATION;

typedef union _PCW_CALLBACK_INFORMATION
{
    PCW_COUNTER_INFORMATION AddCounter;
    PCW_COUNTER_INFORMATION RemoveCounter;
    PCW_MASK_INFORMATION EnumerateInstances;
    PCW_MASK_INFORMATION CollectData;
} PCW_CALLBACK_INFORMATION, *PPCW_CALLBACK_INFORMATION;

typedef enum _PCW_CALLBACK_TYPE
{
    PcwCallbackAddCounter = 0,
    PcwCallbackRemoveCounter,
    PcwCallbackEnumerateInstances,
    PcwCallbackCollectData,
} PCW_CALLBACK_TYPE, *PPCW_CALLBACK_TYPE;

typedef
NTSTATUS
NTAPI
PCW_CALLBACK (
    _In_ PCW_CALLBACK_TYPE Type,
    _In_ PPCW_CALLBACK_INFORMATION Info,
    _In_opt_ PVOID Context);
typedef PCW_CALLBACK *PPCW_CALLBACK;

typedef struct _PCW_REGISTRATION_INFORMATION
{
    _In_ ULONG Version;
    _In_ PCUNICODE_STRING Name;
    _In_ ULONG CounterCount;
    _In_reads_(CounterCount) PPCW_COUNTER_DESCRIPTOR Counters;
    _In_opt_ PPCW_CALLBACK Callback;
    _In_opt_ PVOID CallbackContext;
} PCW_REGISTRATION_INFORMATION, *PPCW_REGISTRATION_INFORMATION;

typedef
NTSTATUS
NTAPI
PCW_REGISTER_PROC (
    _Outptr_ PPCW_REGISTRATION *Registration,
    _In_ PPCW_REGISTRATION_INFORMATION Info);

typedef
VOID
NTAPI
PCW_UNREGISTER_PROC (
    _In_ PPCW_REGISTRATION Registration);

typedef
NTSTATUS
NTAPI
PCW_CREATE_INSTANCE_PROC (
    _Outptr_ PPCW_INSTANCE *Instance,
    _In_ PPCW_REGISTRATION Registration,
    _In_ PCUNICODE_STRING Name,
    _In_ ULONG Count,
    _In_reads_(Count) PPCW_DATA Data);

typedef
VOID
NTAPI
PCW_CLOSE_INSTANCE_PROC (
    _In_ PPCW_INSTANCE Instance);

typedef
NTSTATUS
NTAPI
PCW_ADD_INSTANCE_PROC (
    _In_ PPCW_BUFFER Buffer,
    _In_ PCUNICODE_STRING Name,
    _In_ ULONG Id,
    _In_ ULONG Count,
    _In_reads_(Count) PPCW_DATA Data);

typedef struct _PCW_CALLBACK_TABLE {
    PCW_REGISTER_PROC *Register;
    PCW_UNREGISTER_PROC *Unregister;
    PCW_CREATE_INSTANCE_PROC *CreateInstance;
    PCW_CLOSE_INSTANCE_PROC *CloseInstance;
    PCW_ADD_INSTANCE_PROC *AddInstance;
} PCW_CALLBACK_TABLE, *PPCW_CALLBACK_TABLE;
