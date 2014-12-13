
#include "Obp.hpp"

namespace Ob {

extern "C"
BOOLEAN
NTAPI
ObInitSystem(
    VOID)
{
    /* Initialize the OBJECT class */
    OBJECT::InitializeClass();

    /* Initialize the OBJECT_TYPE class */
    OBJECT_TYPE::InitializeClass();

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

// HACK!
extern "C"
NTSTATUS
NTAPI
SeDefaultObjectMethodEx (
    _In_ PVOID Object,
    _In_ SECURITY_OPERATION_CODE OperationType,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _In_ PVOID SecurityDescriptor, // PSECURITY_DESCRIPTOR
    _Inout_ PULONG CapturedLength,
    _Inout_ PVOID *ObjectSecurityDescriptor, // PSECURITY_DESCRIPTOR
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode)
{
    return SeDefaultObjectMethod(Object,
                                 OperationType,
                                 SecurityInformation,
                                 SecurityDescriptor,
                                 CapturedLength,
                                 ObjectSecurityDescriptor,
                                 PoolType,
                                 GenericMapping);
}

}; // namespace Ob
