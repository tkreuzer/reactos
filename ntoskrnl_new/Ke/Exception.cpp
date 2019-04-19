
#include "Exception.hpp"

VOID
EXCEPTION::GetContext(
    _Out_ PCONTEXT OutContext);

VOID
EXCEPTION::Dispatch(
    VOID);


VOID
NTAPI
KiDispatchException(
    IN PEXCEPTION_RECORD ExceptionRecord,
    IN PKEXCEPTION_FRAME ExceptionFrame,
    IN OUT PKTRAP_FRAME TrapFrame,
    IN KPROCESSOR_MODE PreviousMode)
{
    CONTEXT Context;
    NTSTATUS Status;

    RawDbgPrint("KiDispatchException, Rip = %p\n", TrapFrame->Rip);

    /* Evil hack around vbox brokenness! */
    if (ExceptionRecord->ExceptionCode == STATUS_BREAKPOINT)
    {
        if ((*(UCHAR*)TrapFrame->Rip != 0xCC) &&
            (*((UCHAR*)TrapFrame->Rip + 1) == 0xCC))
        {
            TrapFrame->Rip++;
        }
    }

    /* Get a context */
    KxGetExceptionContext(&Context, TrapFrame, ExceptionFrame);

    /* Check if a debugger is present */
    if (!KdDebuggerNotPresent)
    {
        /* Call the kernel debugger (first chance) */
        Status = KdExceptionStateChange(ExceptionRecord, &Context, TRUE);
        if (NT_SUCCESS(Status))
        {
            goto Handled;
        }
    }

    if (RtlDispatchException(ExceptionRecord, &Context))
    {
        goto Handled;
    }

    /* Check if a debugger is present */
    if (!KdDebuggerNotPresent)
    {
        /* Call the kernel debugger (second chance) */
        Status = KdExceptionStateChange(ExceptionRecord, &Context, FALSE);
        if (NT_SUCCESS(Status))
        {
            goto Handled;
        }
    }

    /* Bugcheck the system */
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED,
                 ExceptionRecord->ExceptionCode,
                 (ULONG_PTR)ExceptionRecord->ExceptionAddress,
                 (ULONG_PTR)TrapFrame,
                 0);

Handled:
    /* Get the new context */
    KxSetExceptionContext(&Context, TrapFrame, ExceptionFrame);
}



DECLSPEC_NORETURN
VOID
NTAPI
KiSystemFatalException(
    _In_ ULONG ExceptionCode,
    _In_ PKTRAP_FRAME TrapFrame)
{
    /* Bugcheck the system */
    KeBugCheckWithTf(UNEXPECTED_KERNEL_MODE_TRAP,
                     ExceptionCode,
                     0,
                     0,
                     0,
                     TrapFrame);
}


extern "C" {

//; ??? @ stdcall -stub -arch=??? KiCoprocessorError()
//@ stdcall -stub KeEnterKernelDebugger()

NTSTATUS
NTAPI
NtRaiseException (
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN FirstChance)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//@ stdcall -stub KeRaiseUserException(long)
// from Ke_NUKE
NTSTATUS
NTAPI
KeRaiseUserException(
    IN NTSTATUS ExceptionCode)
{
    __debugbreak();
    return 0;
}

}; // extern "C"
