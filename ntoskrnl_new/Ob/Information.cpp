
#include "Obp.hpp"

extern "C"
struct _OBJECT_HEADER_NAME_INFO*
NTAPI
ObQueryNameInfo (
    PVOID Object)
{
    __debugbreak();
    return NULL;
}

extern "C"
NTSTATUS
NTAPI
ObQueryNameString (
    _In_ PVOID Object,
    _Out_writes_bytes_opt_(Length) POBJECT_NAME_INFORMATION ObjectNameInfo,
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

