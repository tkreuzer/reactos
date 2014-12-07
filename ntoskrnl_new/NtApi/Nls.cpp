
#include <ntoskrnl.h>
#include <Ex/Ex.hpp>

extern "C" {

__kernel_entry
NTSTATUS
NTAPI
NtInitializeNlsFiles (
    _Outptr_result_bytebuffer_(sizeof(NLS_MAIN_TABLE_OFFSET)) PVOID *BaseAddress,
    _Out_ PLCID DefaultLocaleId,
    _Out_ PLARGE_INTEGER DefaultCasingTableSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtGetNlsSectionPtr (
    _In_ ULONG SectionType,
    _In_ ULONG SectionData,
    _In_opt_ PVOID ContextData,
    _Out_ PVOID *SectionPointer,
    _Out_ PSIZE_T SectionSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtGetMUIRegistryInfo (
    _In_ ULONG Flags,
    _Inout_opt_ ULONG *DataSize,
    _Inout_updates_bytes_opt_(*DataSize) PVOID Data)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetDefaultLocale (
    _In_ BOOLEAN UserProfile,
    _In_ LCID DefaultLocaleId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetDefaultUILanguage (
    _In_ LANGID DefaultUILanguageId)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"
