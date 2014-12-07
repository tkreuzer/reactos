
#include "Rtl.hpp"

extern "C" {

#define RTL_GUID_STRING_SIZE 38

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlGenerateClass5Guid (
    _In_ REFGUID NamespaceGuid,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_ GUID* Guid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlStringFromGUID (
    _In_ REFGUID Guid,
    _Out_ _At_(GuidString->Buffer, __drv_allocatesMem(Mem))
        PUNICODE_STRING GuidString)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
NTAPI
RtlGUIDFromString (
    _In_ PCUNICODE_STRING GuidString,
    _Out_ GUID* Guid)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#if 0
__drv_maxIRQL(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlStringFromGUIDEx (
    _In_ REFGUID Guid,
    _Inout_ PUNICODE_STRING GuidString,
    _In_ BOOLEAN Allocate)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

#endif // 0

} // extern "C"
