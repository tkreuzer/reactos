
#include "Rtl.hpp"

extern "C" {

typedef struct _CONTEXT *PCONTEXT;
typedef struct _EXCEPTION_RECORD *PEXCEPTION_RECORD;

// https://msdn.microsoft.com/ms680591
VOID
NTAPI
RtlCaptureContext (
    _Out_ PCONTEXT ContextRecord)
{
    __debugbreak();
}

// https://msdn.microsoft.com/ms680605
VOID
NTAPI
RtlRestoreContext (
    _In_ PCONTEXT ContextRecord,
    _In_ PEXCEPTION_RECORD ExceptionRecord)
{
    __debugbreak();
}

} // extern "C"
