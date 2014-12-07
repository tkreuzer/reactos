
#include "Obp.hpp"

extern "C"
BOOLEAN
NTAPI
ObInitSystem(
    VOID)
{
    __debugbreak();
    return FALSE;
}


extern "C"
NTSTATUS
NTAPI
ObRegisterCallbacks(
    _In_ POB_CALLBACK_REGISTRATION CallBackRegistration,
    _Outptr_ PVOID *RegistrationHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
VOID
NTAPI
ObUnRegisterCallbacks (
    _In_ PVOID RegistrationHandle)
{
    __debugbreak();
}

extern "C"
USHORT
NTAPI
ObGetFilterVersion (
    VOID)
{
    __debugbreak();
    return 0;
}

