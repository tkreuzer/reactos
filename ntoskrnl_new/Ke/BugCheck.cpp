
#include "BugCheck.hpp"

DECLSPEC_NORETURN
VOID
NTAPI
KiBugCheckInternal(
    _In_ ULONG BugCheckCode,
    _In_ ULONG_PTR BugCheckParameter1,
    _In_ ULONG_PTR BugCheckParameter2,
    _In_ ULONG_PTR BugCheckParameter3,
    _In_ ULONG_PTR BugCheckParameter4,
    PKPROCESSOR_STATE ProcessorState)
{
    /* Set screen colors and clear the screen */
    VidSetColors(VID_COLOR_MAGENTA, VID_COLOR_BRIGHTWHITE);
    VidClearScreen();

    /* Print bugcheck information on the screen */
    VidPrint("\n*** HALT: 0x%08lx\n"
             "  (0x%p,0x%p,0x%p,0x%p)\n\n",
             BugCheckCode,
             BugCheckParameter1,
             BugCheckParameter2,
             BugCheckParameter3,
             BugCheckParameter4);

    /* Dump the processor state information */
    KxDumpProcessorState(ProcessorState);

    /* Enter the debugger */
    DbgBreakPointWithStatus(DBG_STATUS_BUGCHECK_FIRST);

    for (;;);
}


DECLSPEC_NORETURN
VOID
NTAPI
KeBugCheckWithTf(
    _In_ ULONG BugCheckCode,
    _In_ ULONG_PTR BugCheckParameter1,
    _In_ ULONG_PTR BugCheckParameter2,
    _In_ ULONG_PTR BugCheckParameter3,
    _In_ ULONG_PTR BugCheckParameter4,
    _In_ PKTRAP_FRAME TrapFrame)
{
    PKPRCB Prcb = KxGetCurrentPrcb();

    /* Get the context from the trap frame */
    KxGetExceptionContext(&Prcb->ProcessorState.ContextFrame,
                          TrapFrame,
                          (PVOID)TrapFrame->ExceptionFrame);

    /* Call the internal function */
    KiBugCheckInternal(BugCheckCode,
                       BugCheckParameter1,
                       BugCheckParameter2,
                       BugCheckParameter3,
                       BugCheckParameter4,
                       &Prcb->ProcessorState);
}

extern "C" {

ULONG_PTR KiBugCheckData[5];
KBUGCHECK_REASON_CALLBACK_ROUTINE BugCheckSecondaryMultiPartDumpDataCallback;


// ntddk.h / ntosp.h
__drv_preferredFunction("error logging or driver shutdown",
    "Whenever possible, all kernel-mode components should log an error and "
    "continue to run, rather than calling KeBugCheck")
NTKERNELAPI
DECLSPEC_NORETURN
VOID
NTAPI
KeBugCheck (
    _In_ ULONG BugCheckCode)
{
    /* Call the extended version */
    KeBugCheckEx(BugCheckCode, 0, 0, 0, 0);
}

// wdm.h / ntosp.h
__drv_preferredFunction("error logging or driver shutdown",
    "Whenever possible, all kernel-mode components should log an error and "
    "continue to run, rather than calling KeBugCheckEx")
DECLSPEC_NORETURN
VOID
NTAPI
KeBugCheckEx (
    _In_ ULONG BugCheckCode,
    _In_ ULONG_PTR BugCheckParameter1,
    _In_ ULONG_PTR BugCheckParameter2,
    _In_ ULONG_PTR BugCheckParameter3,
    _In_ ULONG_PTR BugCheckParameter4)
{
    PKPRCB Prcb = KxGetCurrentPrcb();

    /* Capture the full context in the PRCB */
    Prcb->ProcessorState.ContextFrame.ContextFlags |= CONTEXT_FULL;
    RtlCaptureContext(&Prcb->ProcessorState.ContextFrame);

    /* Call the internal function */
    KiBugCheckInternal(BugCheckCode,
                       BugCheckParameter1,
                       BugCheckParameter2,
                       BugCheckParameter3,
                       BugCheckParameter4,
                       &Prcb->ProcessorState);
}

// wdm.h / ntosp.h
_Must_inspect_result_
BOOLEAN
NTAPI
KeRegisterBugCheckCallback (
    _Out_ PKBUGCHECK_CALLBACK_RECORD CallbackRecord,
    _In_ PKBUGCHECK_CALLBACK_ROUTINE CallbackRoutine,
    _In_reads_bytes_opt_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ PUCHAR Component)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_Must_inspect_result_
BOOLEAN
NTAPI
KeDeregisterBugCheckCallback (
    _Inout_ PKBUGCHECK_CALLBACK_RECORD CallbackRecord)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_Must_inspect_result_
BOOLEAN
NTAPI
KeRegisterBugCheckReasonCallback (
    _Out_ PKBUGCHECK_REASON_CALLBACK_RECORD CallbackRecord,
    _In_ PKBUGCHECK_REASON_CALLBACK_ROUTINE CallbackRoutine,
    _In_ KBUGCHECK_CALLBACK_REASON Reason,
    _In_ PUCHAR Component)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_Must_inspect_result_
BOOLEAN
NTAPI
KeDeregisterBugCheckReasonCallback (
    _Inout_ PKBUGCHECK_REASON_CALLBACK_RECORD CallbackRecord)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"
