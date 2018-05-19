
#include "Exception.hpp"

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
