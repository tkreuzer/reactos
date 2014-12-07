
#include "Obp.hpp"

extern "C"
NTSTATUS
NTAPI
ObWaitForSingleObject (
    _In_ HANDLE Object,
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Time)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObWaitForMultipleObjects (
    _In_ ULONG Count,
    _In_count_(Count) HANDLE Objects[],
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Time)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

