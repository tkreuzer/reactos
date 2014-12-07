
#include "Mdl.hpp"

extern "C" {

DECLSPEC_DEPRECATED_DDK                 // Use IoAllocateMdl
__drv_preferredFunction("IoAllocateMdl","Obsolete")
PMDL
NTAPI
MmCreateMdl (
    _Out_writes_bytes_opt_ (sizeof (MDL) + (sizeof (PFN_NUMBER) * ADDRESS_AND_SIZE_TO_SPAN_PAGES (Base, Length)))
        PMDL MemoryDescriptorList,
    _In_reads_bytes_opt_ (Length) PVOID Base,
    _In_ SIZE_T Length)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmBuildMdlForNonPagedPool (
    _Inout_ PMDL MemoryDescriptorList)
{
    __debugbreak();
}

SIZE_T
NTAPI
MmSizeOfMdl (
    _In_reads_bytes_opt_ (Length) PVOID Base,
    _In_ SIZE_T Length)
{
    __debugbreak();
    return 0;
}

_IRQL_requires_max_ (DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmAllocateMdlForIoSpace (
    _In_reads_ (NumberOfEntries) PMM_PHYSICAL_ADDRESS_LIST PhysicalAddressList,
    _In_ SIZE_T NumberOfEntries,
    _Out_ PMDL *NewMdl)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmAdvanceMdl (
    _Inout_ PMDL Mdl,
    _In_ ULONG NumberOfBytes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PMDL
NTAPI
MmAllocatePagesForMdl (
    _In_ PHYSICAL_ADDRESS LowAddress,
    _In_ PHYSICAL_ADDRESS HighAddress,
    _In_ PHYSICAL_ADDRESS SkipBytes,
    _In_ SIZE_T TotalBytes)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_ (DISPATCH_LEVEL)
PMDL
NTAPI
MmAllocatePagesForMdlEx (
    _In_ PHYSICAL_ADDRESS LowAddress,
    _In_ PHYSICAL_ADDRESS HighAddress,
    _In_ PHYSICAL_ADDRESS SkipBytes,
    _In_ SIZE_T TotalBytes,
    _In_ MEMORY_CACHING_TYPE CacheType,
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
_IRQL_requires_max_ (DISPATCH_LEVEL)
PMDL
NTAPI
MmAllocateNodePagesForMdlEx (
    _In_ PHYSICAL_ADDRESS LowAddress,
    _In_ PHYSICAL_ADDRESS HighAddress,
    _In_ PHYSICAL_ADDRESS SkipBytes,
    _In_ SIZE_T TotalBytes,
    _In_ MEMORY_CACHING_TYPE CacheType,
    _In_ ULONG IdealNode,
    _In_ ULONG Flags)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreePagesFromMdl (
    _Inout_ PMDL MemoryDescriptorList)
{
    __debugbreak();
}

VOID
NTAPI
MmMapMemoryDumpMdl (
    _Inout_ PMDL MemoryDumpMdl)
{
    __debugbreak();
}

_IRQL_requires_max_ (DISPATCH_LEVEL)
LOGICAL
NTAPI
MmAreMdlPagesCached (
    _In_ PMDL MemoryDescriptorList)
{
    __debugbreak();
    return FALSE;
}

typedef enum _MM_MDL_PAGE_CONTENTS_STATE
{
    MmMdlPageContentsDynamic,
    MmMdlPageContentsInvariant,
    MmMdlPageContentsQuery
} MM_MDL_PAGE_CONTENTS_STATE, PMM_MDL_PAGE_CONTENTS_STATE;

_IRQL_requires_max_(DISPATCH_LEVEL)
MM_MDL_PAGE_CONTENTS_STATE
NTAPI
MmMdlPageContentsState (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ MM_MDL_PAGE_CONTENTS_STATE State)
{
    __debugbreak();
    return MmMdlPageContentsDynamic;
}

// ntifs.h
_IRQL_requires_max_ (APC_LEVEL)
LOGICAL
NTAPI
MmMdlPagesAreZero (
    _In_ PMDL Mdl)
{
    __debugbreak();
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmProtectMdlSystemAddress (
    _In_ PMDL MemoryDescriptorList,
    _In_ ULONG NewProtect)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"
