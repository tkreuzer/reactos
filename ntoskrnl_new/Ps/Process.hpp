
#pragma once

#include <ntoskrnl.h>
#include "Ps.hpp"

typedef struct _EPROCESS *PEPROCESS;
typedef struct _PEB *PPEB;

typedef enum _PSPROCESSPRIORITYMODE
{
    PsProcessPriorityBackground,
    PsProcessPriorityForeground,
    PsProcessPrioritySpinning
} PSPROCESSPRIORITYMODE;

// ntosp.h
typedef
VOID
NTAPI
CREATE_PROCESS_NOTIFY_ROUTINE (
    _In_ HANDLE ParentId,
    _In_ HANDLE ProcessId,
    _In_ BOOLEAN Create);
typedef CREATE_PROCESS_NOTIFY_ROUTINE *PCREATE_PROCESS_NOTIFY_ROUTINE;

// ntosp.h
typedef struct _PS_CREATE_NOTIFY_INFO {
    _In_ SIZE_T Size;
    union
    {
        _In_ ULONG Flags;
        struct
        {
            _In_ ULONG FileOpenNameAvailable : 1;
            _In_ ULONG Reserved : 31;
        };
    };
    _In_ HANDLE ParentProcessId;
    _In_ CLIENT_ID CreatingThreadId;
    _Inout_ struct _FILE_OBJECT *FileObject;
    _In_ PCUNICODE_STRING ImageFileName;
    _In_opt_ PCUNICODE_STRING CommandLine;
    _Inout_ NTSTATUS CreationStatus;
} PS_CREATE_NOTIFY_INFO, *PPS_CREATE_NOTIFY_INFO;

// ntosp.h
typedef
VOID
NTAPI
CREATE_PROCESS_NOTIFY_ROUTINE_EX (
    _Inout_ PEPROCESS Process,
    _In_ HANDLE ProcessId,
    _Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo);
typedef CREATE_PROCESS_NOTIFY_ROUTINE_EX *PCREATE_PROCESS_NOTIFY_ROUTINE_EX;

// ntosp.h
typedef union _PS_EXCEPTION_FLAGS
{
    ULONG Flags;
    struct
    {
        ULONG ProcessUsingVEH : 1;
        ULONG ProcessUsingVCH : 1;
        ULONG Reserved : 30;
    };
} PS_EXCEPTION_FLAGS, *PPS_EXCEPTION_FLAGS;

// undocumented
typedef ULONG PS_WAKE_REASON;
