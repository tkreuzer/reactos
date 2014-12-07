
#include "BugCheck.hpp"

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
    __debugbreak();
    for (;;);
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
    __debugbreak();
    for (;;);
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
