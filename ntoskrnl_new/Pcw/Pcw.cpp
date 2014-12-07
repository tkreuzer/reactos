
#include "Pcw.hpp"

extern "C" {

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PcwRegister(
    _Outptr_ PPCW_REGISTRATION *Registration,
    _In_ PPCW_REGISTRATION_INFORMATION Info)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PcwUnregister(
    _In_ PPCW_REGISTRATION Registration)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PcwCreateInstance(
    _Outptr_ PPCW_INSTANCE *Instance,
    _In_ PPCW_REGISTRATION Registration,
    _In_ PCUNICODE_STRING Name,
    _In_ ULONG Count,
    _In_reads_(Count) PPCW_DATA Data)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PcwCloseInstance(
    _In_ PPCW_INSTANCE Instance)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PcwAddInstance(
    _In_ PPCW_BUFFER Buffer,
    _In_ PCUNICODE_STRING Name,
    _In_ ULONG Id,
    _In_ ULONG Count,
    _In_reads_(Count) PPCW_DATA Data)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
