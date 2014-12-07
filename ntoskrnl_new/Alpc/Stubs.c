#include <ntifs.h>

POBJECT_TYPE LpcPortObjectType;

// ntosp.h
NTSTATUS
NTAPI
LpcReplyWaitReplyPort (
    _In_ PVOID PortAddress,
    _In_ KPROCESSOR_MODE WaitMode,
    _Inout_ PPORT_MESSAGE ReplyMessage)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
LpcRequestPort(
    _In_ PVOID PortAddress,
    _In_ PPORT_MESSAGE RequestMessage)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
LpcRequestWaitReplyPort(
    _In_ PVOID PortAddress,
    _In_ PPORT_MESSAGE RequestMessage,
    _Out_ PPORT_MESSAGE ReplyMessage)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
NTSTATUS
NTAPI
LpcRequestWaitReplyPortEx (
    _In_ PVOID PortAddress,
    _In_ PPORT_MESSAGE RequestMessage,
    _Out_ PPORT_MESSAGE ReplyMessage)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


// ntosp.h
NTSTATUS
NTAPI
LpcSendWaitReceivePort(
    _In_ PVOID PortObject,
    _In_ PPORT_MESSAGE SendMessage,
    _Out_ PPORT_MESSAGE ReceiveMessage,
    _Inout_opt_ PSIZE_T BufferLength,
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}
