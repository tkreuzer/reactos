
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
    PfnFree,
    PfnZeroed,
    PfnPrivate,
    PfnShared,
    PfnContiguous,
    PfnPageTable,
    PfnTransition,
    PfnRom,
    PfnBad,
};

enum PFN_CACHE_ATTRIBUTE
{
    PfnNotMapped     = 0,
    PfnNonCached     = 1,
    PfnCached        = 2,
    PfnWriteCombined = 3,
};


struct PFN_ENTRY
{
    struct
    {
        PFN_STATE State : 4;
        PFN_CACHE_ATTRIBUTE CacheAttribute : 2;
        ULONG ReferenceCount : 27;
    };

    union
    {
        struct
        {
            ULONG_PTR Next;
        } Free;
    };


    union
    {
        ULONG ProcessId; // For private PFNs
        struct /* For shared PFNs */
        {
            ULONG ShareCount;
        };
        struct /* For page-table PFNs */
        {
            ULONG UsedPteCount : 9;
            ULONG ValidPteCount : 9;
        };
        ULONG NumberOfContiguousPages; // For contiguous allocations
    } u1;

    union
    {
        ULONG_PTR Next;
        struct _KEVENT* Event;
    } u2;

    union
    {
        ULONG_PTR Previous;
    } u3;

    ULONG_PTR PteAddressAndLock;

};

struct __PFN_LIST
{
    KSPIN_LOCK SpinLock;
    ULONG_PTR FirstPfn;
};

class PFN_LIST
{
    PFN_NUMBER m_ListHead;
    KSPIN_LOCK m_SpinLock;

    // for now
    friend class PFN_DATABASE;

public:

    PFN_NUMBER
    InterlockedPopEntry (
        VOID);

    VOID
    InterlockedPushEntry (
        PFN_NUMBER PageFrameNumber);

    PFN_NUMBER
    UnsafePopEntry (
        VOID);

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
    static PRTL_BITMAP m_PhysicalMemoryBitmap;
    static PFN_ENTRY* m_PfnArray;
    static PULONG m_PhysicalBitmapBuffer;
    static KSPIN_LOCK m_ContiguousMemoryLock;

    static
    VOID
    InitializePfnEntries (
        _In_ PFN_NUMBER BasePage,
        _In_ PFN_NUMBER PageCount,
        _In_ enum _TYPE_OF_MEMORY MemoryType);


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

}; // namespace Mm
