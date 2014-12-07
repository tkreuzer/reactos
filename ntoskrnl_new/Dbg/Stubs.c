
#include <ntifs.h>

#undef DbgBreakPoint
__analysis_noreturn
VOID
NTAPI
DbgBreakPoint (
    VOID)
{
    __debugbreak();
}

// wdm.h
__analysis_noreturn
VOID
NTAPI
DbgBreakPointWithStatus (
    _In_ ULONG Status)
{
    __debugbreak();
}

ULONG
__cdecl
DbgPrint (
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...)
{
    __debugbreak();
    return 0;
}

ULONG
__cdecl
DbgPrintEx (
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...)
{
    __debugbreak();
    return 0;
}

ULONG
NTAPI
DbgPrompt (
    _In_z_ PCCH Prompt,
    _Out_writes_bytes_(Length) PCH Response,
    _In_ ULONG Length)
{
    __debugbreak();
    return 0;
}

ULONG
__cdecl
DbgPrintReturnControlC (
    _In_z_ _Printf_format_string_ PCCH Format,
    ...)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
DbgQueryDebugFilterState (
    _In_ ULONG ComponentId,
    _In_ ULONG Level)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
DbgSetDebugFilterState (
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

typedef
VOID
(NTAPI *PDEBUG_PRINT_CALLBACK) (
    _In_ PSTRING Output,
    _In_ ULONG ComponentId,
    _In_ ULONG Level);

NTSTATUS
NTAPI
DbgSetDebugPrintCallback (
    _In_ PDEBUG_PRINT_CALLBACK DebugPrintCallback,
    _In_ BOOLEAN Enable)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
typedef
NTSTATUS
(NTAPI *PLKMD_SNAPDATA_ROUTINE) (
    _In_ PVOID CollectionContext,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length);

// ntosp.h
typedef
BOOLEAN
(NTAPI *PLKMD_ISMEMORYBLOCKPRESENT_ROUTINE) (
    _In_ PVOID CollectionContext,
    _In_ PVOID Address,
    _In_opt_ ULONG Length);

// ntosp.h
typedef
NTSTATUS
(NTAPI *PLKMD_CALLBACK_ROUTINE) (
    _In_ PLKMD_SNAPDATA_ROUTINE SnapDataRoutine,
    _In_ PLKMD_ISMEMORYBLOCKPRESENT_ROUTINE IsMemoryBlockPresentRoutine,
    _In_ PVOID CollectionContext,
    _In_opt_ PVOID CallbackContext,
    _In_ PVOID Object);

// ntosp.h
#define LKMD_PER_PROCESS    (0x00000001UL)
#define LKMD_PER_THREAD     (0x00000002UL)
#define LKMD_SAME_SESSION   (0x00000004UL)

// ntosp.h
NTSTATUS
NTAPI
DbgkLkmdRegisterCallback (
    _In_ PLKMD_CALLBACK_ROUTINE CallbackRoutine,
    _In_opt_ PVOID CallbackContext,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
DbgkLkmdUnregisterCallback (
    _In_ PLKMD_CALLBACK_ROUTINE CallbackRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
typedef union DBGK_LIVEDUMP_FLAGS
{
    struct
    {
        ULONG  UserPages:1;
        ULONG  Reserved:31;
    };
    ULONG AsUlong;
} DBGK_LIVEDUMP_FLAGS, *PDBGK_LIVEDUMP_FLAGS;

// ntosp.h
typedef
NTSTATUS
NTAPI
DBGK_LIVEDUMP_ADDSECONDARYDATA_ROUTINE (
    _In_ HANDLE ReportHandle,
    _In_reads_bytes_(sizeof(GUID)) LPCGUID Identifier,
    _In_reads_bytes_(Size) PVOID Data,
    _In_ ULONG Size);
typedef DBGK_LIVEDUMP_ADDSECONDARYDATA_ROUTINE *PDBGK_LIVEDUMP_ADDSECONDARYDATA_ROUTINE;

// ntosp.h
typedef
NTSTATUS
NTAPI
DBGK_LIVEDUMP_CALLBACK_ROUTINE (
    _In_ HANDLE ReportHandle,
    _In_ PDBGK_LIVEDUMP_ADDSECONDARYDATA_ROUTINE AddSecondaryDataRoutine,
    _In_ ULONG BugCheckCode,
    _In_opt_ ULONG_PTR P1,
    _In_opt_ ULONG_PTR P2,
    _In_opt_ ULONG_PTR P3,
    _In_opt_ ULONG_PTR P4,
    _In_opt_ PVOID CallbackContext);
typedef DBGK_LIVEDUMP_CALLBACK_ROUTINE *PDBGK_LIVEDUMP_CALLBACK_ROUTINE;

#define DBGKWER_COMPONENT_NAME_LENGTH 16

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
DbgkWerCaptureLiveKernelDump (
    _In_ LPCWSTR ComponentName,
    _In_ ULONG BugCheckCode,
    _In_opt_ ULONG_PTR P1,
    _In_opt_ ULONG_PTR P2,
    _In_opt_ ULONG_PTR P3,
    _In_opt_ ULONG_PTR P4,
    _In_opt_ PVOID CallbackContext,
    _In_opt_ PDBGK_LIVEDUMP_CALLBACK_ROUTINE CallbackFunction,
    _In_opt_ DBGK_LIVEDUMP_FLAGS Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#if 1

// ntosp.h
LOGICAL
NTAPI
DbgUnicodeStringToAnsiString (
    _Out_ PANSI_STRING AnsiFileName,
    _In_ PUNICODE_STRING UnicodeFileName)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
VOID
NTAPI
DbgLoadUserImageSymbols (
    _In_ PSTRING FileName,
    _In_ PVOID ImageBase,
    _In_ ULONG_PTR ProcessId,
    _In_ ULONG CapturedSizeOfImage,
    _In_ ULONG CapturedCheckSum)
{
    __debugbreak();
}

// derived from DbgLoadImageSymbolsUnicode
LOGICAL
NTAPI
DbgLoadImageSymbols (
    _In_ PSTRING UnicodeFileName,
    _In_ PVOID ImageBase,
    _In_ ULONG_PTR ProcessId)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
LOGICAL
NTAPI
DbgLoadImageSymbolsUnicode (
    _In_ PUNICODE_STRING UnicodeFileName,
    _In_ PVOID ImageBase,
    _In_ ULONG_PTR ProcessId)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
LOGICAL
NTAPI
DbgUnLoadImageSymbolsUnicode (
    _In_opt_ PUNICODE_STRING UnicodeFileName,
    _In_ PVOID ImageBase,
    _In_ ULONG_PTR ProcessId)
{
    __debugbreak();
    return FALSE;
}

// undocumented
VOID
NTAPI
DbgCommandString (
    PVOID P1,
    PVOID P2)
{
    __debugbreak();
}

//@ stdcall DbgLoadImageSymbols(ptr ptr long)

#endif // 0
