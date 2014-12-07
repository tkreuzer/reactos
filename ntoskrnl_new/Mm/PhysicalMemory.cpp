
#include "Mmp.hpp"
#include "Mdl.hpp"
#include <Ke/Ke.hpp>

extern "C" {

//@ extern Mm64BitPhysicalAddress

typedef struct _EPROCES *PEPROCESS;

// ntddk.h
typedef struct _PHYSICAL_MEMORY_RANGE
{
    PHYSICAL_ADDRESS BaseAddress;
    LARGE_INTEGER NumberOfBytes;
} PHYSICAL_MEMORY_RANGE, *PPHYSICAL_MEMORY_RANGE;

// wdm.h
typedef union _FILE_SEGMENT_ELEMENT
{
    PVOID64 Buffer;
    ULONGLONG Alignment;
}FILE_SEGMENT_ELEMENT, *PFILE_SEGMENT_ELEMENT;

typedef enum _LOCK_OPERATION
{
    IoReadAccess,
    IoWriteAccess,
    IoModifyAccess
} LOCK_OPERATION;

PHYSICAL_ADDRESS
NTAPI
MmGetPhysicalAddress (
    _In_ PVOID BaseAddress)
{
    PHYSICAL_ADDRESS PhysicalAddress = {{ 0 }};
    __debugbreak();
    return PhysicalAddress;
}

PVOID
NTAPI
MmGetVirtualForPhysical (
    _In_ PHYSICAL_ADDRESS PhysicalAddress)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
PPHYSICAL_MEMORY_RANGE
NTAPI
MmGetPhysicalMemoryRanges (
    VOID)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmAddPhysicalMemory (
    _In_ PPHYSICAL_ADDRESS StartAddress,
    _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmRemovePhysicalMemory (
    _In_ PPHYSICAL_ADDRESS StartAddress,
    _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmMarkPhysicalMemoryAsGood (
    _In_ PPHYSICAL_ADDRESS StartAddress,
    _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmMarkPhysicalMemoryAsBad (
    _In_ PPHYSICAL_ADDRESS StartAddress,
    _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Out_writes_bytes_opt_ (NumberOfBytes)
PVOID
NTAPI
MmAllocateNonCachedMemory (
    _In_ SIZE_T NumberOfBytes)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeNonCachedMemory (
    _In_reads_bytes_ (NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes)
{
    __debugbreak();
}

_IRQL_requires_max_ (DISPATCH_LEVEL)
NTSTATUS
NTAPI
MmGetCacheAttribute (
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _Out_ MEMORY_CACHING_TYPE *CacheType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}



_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(MemoryDescriptorList->StartVa + MemoryDescriptorList->ByteOffset,
    _Field_size_bytes_opt_(MemoryDescriptorList->ByteCount))
VOID
NTAPI
MmProbeAndLockPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    __debugbreak();
}

_IRQL_requires_max_ (APC_LEVEL)
VOID
NTAPI
MmProbeAndLockProcessPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ PEPROCESS Process,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    __debugbreak();
}

_IRQL_requires_max_ (APC_LEVEL)
VOID
NTAPI
MmProbeAndLockSelectedPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnlockPages (
    _Inout_ PMDL MemoryDescriptorList)
{
    __debugbreak();
}

}; // extern "C"
