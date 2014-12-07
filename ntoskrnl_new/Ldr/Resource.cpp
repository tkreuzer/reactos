
#include "Ldr.hpp"

extern "C" {

// wine
NTSTATUS
NTAPI
LdrAccessResource (
    PVOID ImageBase,
    const struct _IMAGE_RESOURCE_DATA_ENTRY *DataEntry,
    PVOID *Pointer,
    PULONG Size)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// reactos
NTSTATUS
NTAPI
LdrEnumResources (
    _In_ PVOID ImageBase,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Inout_ ULONG *ResourceCount,
    _Out_opt_ PLDR_ENUM_RESOURCE_INFO Resources)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// reactos
NTSTATUS
NTAPI
LdrFindResourceDirectory_U (
    _In_ PVOID BaseAddress,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Out_ PIMAGE_RESOURCE_DIRECTORY *ResourceDirectory)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// reactos
NTSTATUS
NTAPI
LdrFindResource_U (
    _In_ PVOID BaseAddress,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Out_ PIMAGE_RESOURCE_DATA_ENTRY *ResourceDataEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
LdrFindResourceEx_U (
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Out_ PIMAGE_RESOURCE_DATA_ENTRY *ResourceDataEntry)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
