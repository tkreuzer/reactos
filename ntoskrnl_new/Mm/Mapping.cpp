
#include "Mmp.hpp"
#include "Mdl.hpp"
#include <Ke/Ke.hpp>

extern "C" {

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_When_ (return != NULL, _Out_writes_bytes_opt_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateMappingAddress (
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG PoolTag)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeMappingAddress (
    _In_ PVOID BaseAddress,
    _In_ ULONG PoolTag)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapReservedMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDL MemoryDescriptorList)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
BOOLEAN
NTAPI
MmIsAddressValid (
    _In_ PVOID VirtualAddress)
{
    __debugbreak();
    return FALSE;
}

__drv_preferredFunction("(see documentation)", "Obsolete")
DECLSPEC_DEPRECATED_DDK
BOOLEAN
NTAPI
MmIsNonPagedSystemAddressValid (
    _In_ PVOID VirtualAddress)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_ (DISPATCH_LEVEL)
LOGICAL
NTAPI
MmIsIoSpaceActive (
    _In_ PHYSICAL_ADDRESS StartAddress,
    _In_ SIZE_T NumberOfBytes)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Out_writes_bytes_opt_ (NumberOfBytes)
PVOID
NTAPI
MmMapIoSpace (
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ MEMORY_CACHING_TYPE CacheType)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_ (DISPATCH_LEVEL)
_Out_writes_bytes_opt_ (NumberOfBytes)
PVOID
NTAPI
MmMapIoSpaceEx (
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Protect)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapIoSpace (
    _In_reads_bytes_ (NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
_Out_writes_bytes_opt_ (NumberOfBytes)
PVOID
NTAPI
MmMapVideoDisplay (
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ MEMORY_CACHING_TYPE CacheType)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_ (APC_LEVEL)
VOID
NTAPI
MmUnmapVideoDisplay (
    _In_reads_bytes_ (NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes)
{
    __debugbreak();
}

_Must_inspect_result_
__drv_preferredFunction("MmMapLockedPagesSpecifyCache",
    "Obsolete except on Windows 98.  Use MmGetSystemAddressForMdlSafe if this "
	"is a call to MmGetSystemAddressForMdl.")
_When_(AccessMode==0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==1, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL))
DECLSPEC_DEPRECATED_DDK
PVOID
NTAPI
MmMapLockedPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
    KPROCESSOR_MODE AccessMode)
{
    __debugbreak();
    return NULL;
}

_Post_writable_byte_size_(MemoryDescriptorList->ByteCount)
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL) _Post_notnull_)
_At_(MemoryDescriptorList->MappedSystemVa,
    _Post_writable_byte_size_(MemoryDescriptorList->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesSpecifyCache (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
        KPROCESSOR_MODE AccessMode,
    _In_ __drv_strictTypeMatch(__drv_typeCond) MEMORY_CACHING_TYPE CacheType,
    _In_opt_ PVOID RequestedAddress,
    _In_ ULONG BugCheckOnFailure,
    _In_ ULONG Priority)
{
    __debugbreak();
    return NULL;
}

_Post_writable_byte_size_(MemoryDescriptorList->ByteCount)
_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(MemoryDescriptorList->MappedSystemVa + MemoryDescriptorList->ByteOffset,
     _Post_writable_byte_size_(MemoryDescriptorList->ByteCount))
_Must_inspect_result_
_Success_(return != NULL)
PVOID
NTAPI
MmMapLockedPagesWithReservedMapping (
    _In_ PVOID MappingAddress,
    _In_ ULONG PoolTag,
    _Inout_ PMDL MemoryDescriptorList,
    _In_ __drv_strictTypeMatch(__drv_typeCond) MEMORY_CACHING_TYPE CacheType)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnmapLockedPages (
    _In_ PVOID BaseAddress,
    _Inout_ PMDL MemoryDescriptorList)
{
    __debugbreak();
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmMapUserAddressesToPage (
    _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ PVOID PageAddress)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"
