
#include "Rtl.hpp"

extern "C" {

typedef struct _EXCEPTION_RECORD *PEXCEPTION_RECORD;

// https://msdn.microsoft.com/hh829883
VOID
NTAPI
RtlRaiseException (
    _In_ PEXCEPTION_RECORD ExceptionRecord)
{
    __debugbreak();
}

// http://filelog.net/func/RtlPcToFileHeader
PVOID
NTAPI
RtlPcToFileHeader (
    _In_ PVOID PcValue,
    _Out_ PVOID* BaseOfImage)
{
    __debugbreak();
    return NULL;
}

#ifdef _M_AMD64
typedef struct _RUNTIME_FUNCTION *PRUNTIME_FUNCTION;
typedef struct _CONTEXT *PCONTEXT;
typedef struct _KNONVOLATILE_CONTEXT_POINTERS *PKNONVOLATILE_CONTEXT_POINTERS;
typedef struct _RAME_POINTERS *FRAME_POINTERS;
typedef struct _UNWIND_HISTORY_TABLE *PUNWIND_HISTORY_TABLE;

// http://filelog.net/func/RtlLookupFunctionEntry
PVOID
NTAPI
RtlLookupFunctionEntry (
    ULONGLONG ControlPC,
    PULONGLONG ImageBase,
    PULONGLONG TargetGp)
{
    __debugbreak();
    return NULL;
}

// https://msdn.microsoft.com/ms680617
PEXCEPTION_ROUTINE
NTAPI
RtlVirtualUnwind (
    _In_ ULONG HandlerType,
    _In_ ULONG64 ImageBase,
    _In_ ULONG64 ControlPc,
    _In_ PRUNTIME_FUNCTION FunctionEntry,
    _Inout_ PCONTEXT ContextRecord,
    _Out_ PVOID *HandlerData,
    _Out_ PULONG64 EstablisherFrame,
    _Inout_opt_ PKNONVOLATILE_CONTEXT_POINTERS ContextPointers)
{
    __debugbreak();
    return NULL;
}

// https://msdn.microsoft.com/ms680615
VOID
NTAPI
RtlUnwindEx (
    _In_opt_ FRAME_POINTERS TargetFrame,
    _In_opt_ PVOID TargetIp,
    _In_opt_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PVOID ReturnValue,
    _In_ PCONTEXT OriginalContext,
    _In_opt_ PUNWIND_HISTORY_TABLE HistoryTable)
{
    __debugbreak();
}

#endif // _M_AMD64

VOID
NTAPI
RtlGetCallersAddress (
    _Out_ PVOID *CallersAddress,
    _Out_ PVOID *CallersCaller)
{
    __debugbreak();
}

// ntddk.h
ULONG
NTAPI
RtlWalkFrameChain (
    _Out_writes_(Count - (Flags >> RTL_STACK_WALKING_MODE_FRAMES_TO_SKIP_SHIFT))
        PVOID *Callers,
    _In_ ULONG Count,
    _In_ ULONG Flags)
{
    __debugbreak();
    return 0;
}

// https://msdn.microsoft.com/ff552119
_Success_(return != 0)
USHORT
NTAPI
RtlCaptureStackBackTrace (
    _In_ ULONG FramesToSkip,
    _In_ ULONG FramesToCapture,
    _Out_writes_to_(FramesToCapture, return) PVOID * BackTrace,
    _Out_opt_ PULONG BackTraceHash)
{
    __debugbreak();
    return 0;
}

// https://msdn.microsoft.com/ms680609
VOID
NTAPI
RtlUnwind (
    _In_opt_ PVOID TargetFrame,
    _In_opt_ PVOID TargetIp,
    _In_opt_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PVOID ReturnValue)
{
    __debugbreak();
}

} // extern "C"
