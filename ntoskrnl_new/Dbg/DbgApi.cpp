
/*!
 * \ref http://alter.org.ua/docs/nt_kernel/kdprint/
 */

#include <ntbase.h>
#include <ntstatus.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <debug.h>
#include <RtlString.hpp>

//extern IKernelDebugger* g_KernelDebugger;

#define __analysis_noreturn
#define DbgChannelMaximum 6
#define DPFLTR_ERROR_LEVEL 0

UCHAR DbgChannelConfig[DbgChannelMaximum];

extern "C" {

typedef
void
(__cdecl *PDEBUGPRINT_CALLBACK_FUNCTION) (
    _In_ PANSI_STRING String,
    _In_ ULONG ComponentId,
    _In_ ULONG Level);

#undef DbgBreakPoint
__analysis_noreturn
VOID
NTAPI
DbgBreakPoint (
    VOID)
{
    __debugbreak();
}

__analysis_noreturn
VOID
NTAPI
DbgBreakPointWithStatus (
    _In_ ULONG Status)
{
    /// \todo This needs to be asm and have a global label
    (void)Status;
    __debugbreak();
}

VOID
NTAPI
DbgCommandString(
    _In_ PCSTR Name,
    _In_ PCSTR Command)
{
    (void)Name;
    (void)Command;
}

VOID
NTAPI
DbgLoadImageSymbols(
    _In_ PSTRING Name,
    _In_ PVOID Base,
    _In_ ULONG_PTR ProcessId)
{
    (void)Name;
    (void)Base;
    (void)ProcessId;
}

NTSTATUS
NTAPI
vDbgPrintInternal (
    _In_z_ PCSTR Prefix,
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCSTR Format,
    _In_ va_list argptr)
{
    CHAR buffer[512];
    ANSI_STRING ansiString;
    INT cnt;
    NTSTATUS status;

    if ((ComponentId != -1) && (ComponentId > 9)) /// \todo fix this (dpfltr.h)
    {
        return STATUS_INVALID_PARAMETER;
    }

    if ((ComponentId != -1) && (DbgChannelConfig[ComponentId] < Level))
    {
        return STATUS_SUCCESS;
    }

    /* First put the prefix into the buffer */
    cnt = _snprintf(buffer, sizeof(buffer), "%s", Prefix);
    if (cnt < 0)
    {
        return STATUS_INVALID_PARAMETER;
    }

    ASSERT(cnt < sizeof(buffer));

    /* Append the actual debug string */
    cnt = _vsnprintf(buffer + cnt, sizeof(buffer) - cnt, Format, argptr);
    if (cnt < 0)
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Initialize an ANSI_STRING */
    ansiString.Initialize(buffer);

    /* Call the kernel debugger */
    status = STATUS_SUCCESS;//g_KernelDebugger->PrintString(&ansiString);
    if (!NT_SUCCESS(status))
    {
        //KdRefreshDebuggerNotPresent();
    }

    return status;
}

#define DBG_STATUS_CONTROL_C 1 /// \todo

NTSTATUS
NTAPI
vDbgPrintExWithPrefix (
    _In_z_ PCSTR Prefix,
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCSTR Format,
    _In_ va_list argptr)
{
    NTSTATUS status;

    /* Call the internal API */
    status = vDbgPrintInternal(Prefix, ComponentId, Level, Format, argptr);

    /* Check if a Ctrl-C was detected */
    if (status == STATUS_BREAKPOINT)
    {
        DbgBreakPointWithStatus(DBG_STATUS_CONTROL_C);
    }

    return status;
}

NTSTATUS
NTAPI
vDbgPrintEx (
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCSTR Format,
    _In_ va_list argptr)
{
    return vDbgPrintExWithPrefix("", ComponentId, Level, Format, argptr);
}

UINT
__cdecl
DbgPrint (
    _In_z_ _Printf_format_string_ const char* Format,
    ...)
{
    va_list argptr;
    NTSTATUS status;

    va_start(argptr, Format);
    status = vDbgPrintEx((ULONG)-1, DPFLTR_ERROR_LEVEL, Format, argptr);
    va_end(argptr);

    return status;
}

NTSTATUS
__cdecl
DbgPrintEx (
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...)
{
    va_list argptr;
    NTSTATUS status;

    va_start(argptr, Format);
    status = vDbgPrintEx(ComponentId, Level, Format, argptr);
    va_end(argptr);

    return status;
}

NTSTATUS
__cdecl
DbgPrintReturnControlC (
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...)
{
    va_list argptr;
    NTSTATUS status;

    va_start(argptr, Format);
    status = vDbgPrintInternal("", (ULONG)-1, DPFLTR_ERROR_LEVEL, Format, argptr);
    va_end(argptr);

    return status;
}


ULONG
NTAPI
DbgPrompt (
    _In_z_ PCSTR Prompt,
    _Out_writes_bytes_(MaximumResponseLength) PCH Response,
    _In_ ULONG MaximumResponseLength)
{
    (void)Prompt;
    (void)Response;
    (void)MaximumResponseLength;
    __debugbreak();
    return 0;
}


/*!
 * \ref http://msdn.microsoft.com/en-us/library/ff551519.aspx
 * \ref http://www.woodmann.com/forum/entry.php?140-NtSetDebugFilterState-as-Anti-Dbg-Trick
 */
NTSTATUS
NTAPI
DbgQueryDebugFilterState (
    _In_ ULONG ComponentId,
    _In_ ULONG Level)
{
    (void)ComponentId;
    (void)Level;
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
    (void)ComponentId;
    (void)Level;
    (void)State;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
DbgSetDebugPrintCallback (
    _In_ PDEBUGPRINT_CALLBACK_FUNCTION Function,
    _In_ BOOLEAN Mode)
{
    (void)Function;
    (void)Mode;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtQueryDebugFilterState (
    _In_ ULONG ComponentId,
    _In_ ULONG Level)
{
    return DbgQueryDebugFilterState(ComponentId, Level);
}

NTSTATUS
NTAPI
NtSetDebugFilterState (
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State)
{
    /// \todo privilege check
    return DbgSetDebugFilterState(ComponentId, Level, State);
}

} // extern "C"
