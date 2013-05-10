
#pragma once

#include "ntosbase.h"

extern "C" ULONG KeNodeMask;
enum _TYPE_OF_MEMORY;

namespace Mm {

static const ULONG TAG_MEMORY_RANGES = 'hPmM';
static const ULONG TAG_MM = '  mM';

static const ULONG MAXIMUM_NUMA_NODES = 16;

/// \todo use enum class, once GCC is fixed.
/// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=51242
enum PFN_STATE : ULONG
{
    PfnNotPresent = 0,
    PfnKernelReserved,
    PfnZeroed,
    PfnPrivate,
    PfnShared,
    PfnContiguous,
    PfnPageTable,
    PfnTransition,
    PfnRom,
    PfnFree,
    PfnBad,
};

enum PFN_CACHE_ATTRIBUTE
{
    PfnNotMapped     = 0,
    PfnWriteCombined = 1,
    PfnCached        = 2,
    PfnNonCached     = 3,
};

#define ProtectToCacheAttribute(Protect) ((PFN_CACHE_ATTRIBUTE)((((Protect) >> 3) - 2) & 3))
static_assert(ProtectToCacheAttribute(MM_READONLY) == PfnCached, "");
static_assert(ProtectToCacheAttribute(MM_UNCACHED) == PfnNonCached, "");
static_assert(ProtectToCacheAttribute(MM_WRITECOMBINE) == PfnWriteCombined, "");


typedef struct PFN_ENTRY
{
    struct
    {
        PFN_STATE State : 4;
        PFN_CACHE_ATTRIBUTE CacheAttribute : 2;
        ULONG Dirty : 1;
        ULONG ReferenceCount : 25;
    };

    union
    {
        struct
        {
            ULONG_PTR Next;
        } Free;
        struct
        {
            ULONG UsedPteCount : 10;
            ULONG ValidPteCount : 10;
        } PageTable;
        struct
        {
            ULONG ShareCount;
            ULONG ProcessId;
        } Active;
        struct
        {
            ULONG_PTR Next;
            ULONG NumberOfPages;
        } Contiguous;
    };

    PVOID PteAddress;

} PFN_ENTRY, *PPFN_ENTRY;

class PFN_LIST
{
    PFN_NUMBER m_ListHead;
    PFN_NUMBER m_ListTail;
    KSPIN_LOCK m_SpinLock;

    // for now
    friend class PFN_DATABASE;

public:

    VOID
    Initialize (
        VOID);

    PFN_NUMBER
    InterlockedPopEntry (
        VOID);

    VOID
    InterlockedPushEntry (
        PFN_NUMBER PageFrameNumber);

    PFN_NUMBER
    RemovePage (
        VOID);

    VOID
    AddPage (
        PFN_NUMBER PageFrameNumber);

    VOID
    PushPage (
        _In_ PFN_NUMBER PageFrameNumber);

    VOID
    PushMultiplePfns (
        PFN_NUMBER FirstPfn);

    VOID
    AcquireSpinLock (
        _Out_ PKLOCK_QUEUE_HANDLE LockHandle)
    {
        KeAcquireInStackQueuedSpinLock(&m_SpinLock, LockHandle);
    }

    VOID
    ReleaseSpinLock (
        _In_ PKLOCK_QUEUE_HANDLE LockHandle)
    {
        KeReleaseInStackQueuedSpinLock(LockHandle);
    }

};

typedef class PFN_LIST* PPFN_LIST;

typedef struct _PHYSICAL_MEMORY_RUN
{
    PFN_NUMBER BasePage;
    PFN_NUMBER PageCount;
} PHYSICAL_MEMORY_RUN, *PPHYSICAL_MEMORY_RUN;

typedef struct _PHYSICAL_MEMORY_DESCRIPTOR
{
    ULONG NumberOfRuns;
    PFN_NUMBER NumberOfPages;
    PHYSICAL_MEMORY_RUN Run[1];
} PHYSICAL_MEMORY_DESCRIPTOR, *PPHYSICAL_MEMORY_DESCRIPTOR;

class PFN_DATABASE
{
    static ULONG m_CacheColorBits;
    static ULONG m_CacheColorMask;
    static PPFN_LIST m_FreeLists;
    static PPFN_LIST m_ZeroedLists;
    static PPHYSICAL_MEMORY_DESCRIPTOR m_PhysicalMemoryDescriptor;
    static PRTL_BITMAP_EX m_PhysicalMemoryBitmap;
    static PFN_ENTRY* m_PfnArray;
    static PULONG_PTR m_PhysicalBitmapBuffer;

    static
    VOID
    InitializePfnEntries (
        _In_ PFN_NUMBER BasePage,
        _In_ PFN_NUMBER PageCount,
        _In_ enum _TYPE_OF_MEMORY MemoryType);

    static
    VOID
    InitializePageTablePfn (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ PFN_NUMBER ParendDirectoryPfn,
        _In_ PVOID MappedAddress,
        _In_ ULONG PageTableLevel);

    static
    VOID
    InitializePfnEntriesFromPageTables (
        VOID);

    static
    PFN_NUMBER
    AllocatePageLocked (
        _In_ ULONG DesiredPageColor,
        _Inout_ PBOOLEAN Zeroed);

    static
    VOID
    FreePageLocked (
        _Inout_ PFN_NUMBER PageFrameNumber);

    friend class PFN_LIST;

public:

    static
    VOID
    Initialize (
        _In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock);

    static inline
    const PHYSICAL_MEMORY_DESCRIPTOR*
    GetPhysicalMemoryDescriptor (
        VOID)
    {
        return m_PhysicalMemoryDescriptor;
    }

    static
    PFN_NUMBER
    AllocatePage (
        _In_ BOOLEAN Zeroed);

    static
    VOID
    ReleasePage (
        _Inout_ PFN_NUMBER PageFrameNumber);

    static
    NTSTATUS
    AllocateMultiplePages (
        _Out_ PFN_LIST* PageList,
        _In_ ULONG_PTR NumberOfPages,
        _In_ BOOLEAN Zeroed);

    static
    VOID
    ReleaseMultiplePages (
        _Inout_ PFN_LIST* PageList);

    static
    NTSTATUS
    AllocateLargePages (
        _Out_ PFN_LIST* LargePageList,
        _In_ ULONG_PTR NumberOfLargePages,
        _In_ BOOLEAN Zeroed);

    static
    VOID
    ReleaseLargePages (
        _Inout_ PFN_LIST* PageList);

    static
    VOID
    MakeActivePfn (
        _Inout_ PFN_NUMBER PageFrameNumber,
        _In_ PVOID PteAddress,
        _In_ ULONG Protect);

    static
    VOID
    MakeLargePagePfn (
        _Inout_ PFN_NUMBER PageFrameNumber,
        _In_ PVOID PteAddress,
        _In_ ULONG Protect);

    static
    VOID
    MakePageTablePfn (
        _Inout_ PFN_NUMBER PageFrameNumber,
        _In_ PVOID PteAddress,
        _In_ ULONG Protect);

    static
    ULONG
    ModifyEntryCount (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ LONG Addend);

    static
    ULONG
    ModifyUsedCount (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ LONG Addend);

    static
    ULONG
    ModifyValidCount (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ LONG Addend);

#if 0
    AllocatePageNuma (
        _In_ ULONG NodeNumber)
    {

    }

    inline
    PFN_NUMBER
    AllocatePageForCpu (
        _In_ ULONG CpuNumber)
    {

        return AllocatePageNuma(KiProcessorBlock[CpuNumber]->Node.NodeNumber);
    }
#endif

    static
    NTSTATUS
    MarkPhysicalMemory (
        _In_ PFN_NUMBER BasePageFrameNumber,
        _In_ PFN_COUNT NumberOfPages,
        _In_ PFN_STATE NewState);

    _Must_inspect_result_
    _IRQL_requires_max_(DISPATCH_LEVEL)
    static
    NTSTATUS
    AllocateContiguousPages (
        _Out_ PPFN_NUMBER BasePageFrameNumber,
        _In_ PFN_COUNT NumberOfPages,
        _In_ PFN_NUMBER LowestAcceptablePfn,
        _In_ PFN_NUMBER HighestAcceptablePfn,
        _In_opt_ PFN_NUMBER BoundaryPageMultiple,
        _In_ NODE_REQUIREMENT PreferredNode);

    static
    VOID
    FreeContiguousPages (
        _In_ PFN_NUMBER BasePageFrameNumber);

    static
    VOID
    SetPageMapping (
        _In_ PFN_NUMBER BasePageFrameNumber,
        _In_ PFN_COUNT NumberOfPages,
        _In_ MEMORY_CACHING_TYPE CachingType);

};

extern PFN_DATABASE g_PfnDatabase;

VOID
ZeroPage (
    _In_ PFN_NUMBER PageFrameNumber);

}; // namespace Mm
