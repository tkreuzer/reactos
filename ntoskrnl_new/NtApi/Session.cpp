#include <ntoskrnl.h>

extern "C" {

typedef struct _EPROCESS *PEPROCESS;

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtOpenSession (
    _Out_ PHANDLE SessionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
