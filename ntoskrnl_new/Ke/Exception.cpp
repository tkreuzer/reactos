
#include "Exception.hpp"

extern "C" {

//; ??? @ stdcall -stub -arch=??? KiCoprocessorError()
//@ stdcall -stub KeEnterKernelDebugger()
//@ stdcall -stub KeRaiseUserException(long)

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


}; // extern "C"
