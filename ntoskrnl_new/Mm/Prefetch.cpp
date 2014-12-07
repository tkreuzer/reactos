
#include "Mmp.hpp"

extern "C" {

// wdm.h
typedef union _FILE_SEGMENT_ELEMENT
{
    PVOID64 Buffer;
    ULONGLONG Alignment;
}FILE_SEGMENT_ELEMENT, *PFILE_SEGMENT_ELEMENT;

// ntifs.h
typedef struct _READ_LIST
{
    struct _FILE_OBJECT *FileObject;
    ULONG NumberOfEntries;
    LOGICAL IsImage;
    FILE_SEGMENT_ELEMENT List[ANYSIZE_ARRAY];
} READ_LIST, *PREAD_LIST;

typedef struct _PREFETCH_VIRTUAL_ADDRESS_ENTRY
{
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} PREFETCH_VIRTUAL_ADDRESS_ENTRY, *PPREFETCH_VIRTUAL_ADDRESS_ENTRY;

typedef enum _PREFETCH_VIRTUAL_ADDRESS_PRIORITY_TYPE
{
    PrefetchPagePriorityDefault,
    PrefetchPagePriorityLow,
    PrefetchPagePriorityUseThreadDefault,
    PrefetchPagePriorityReserved
} PREFETCH_VIRTUAL_ADDRESS_PRIORITY_TYPE, *PPREFETCH_VIRTUAL_ADDRESS_PRIORITY_TYPE;

typedef union _PREFETCH_VIRTUAL_ADDRESS_FLAGS
{
    struct
    {
        ULONG ConsumeOnlySamePriorityOrLowerPages : 1;
        ULONG PagePriority : 2;
        ULONG MustBeZero : 29;
    } Flags;
    ULONG AllFlags;
} PREFETCH_VIRTUAL_ADDRESS_FLAGS, *PPREFETCH_VIRTUAL_ADDRESS_FLAGS;

typedef struct _PREFETCH_VIRTUAL_ADDRESS_LIST
{
    ULONG Version;
    PREFETCH_VIRTUAL_ADDRESS_FLAGS u1;
    HANDLE AddressSpaceHandle;
    ULONG_PTR NumberOfEntries;
    PPREFETCH_VIRTUAL_ADDRESS_ENTRY VirtualAddresses;        // NumberOfEntries entries here
} PREFETCH_VIRTUAL_ADDRESS_LIST, *PPREFETCH_VIRTUAL_ADDRESS_LIST;

// ntifs.h
_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmPrefetchPages (
    _In_ ULONG NumberOfLists,
    _In_reads_ (NumberOfLists) PREAD_LIST *ReadLists)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmPrefetchVirtualAddresses (
    _In_ PPREFETCH_VIRTUAL_ADDRESS_LIST ParameterBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"

