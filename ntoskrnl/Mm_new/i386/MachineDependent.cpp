
#include "../ntosbase.h"
#include "PageTables.hpp"
#include "MachineDependent.hpp"
#include "../KernelVad.hpp"
#include "../VadTable.hpp"
#include <ndk/pstypes.h>
#include <ndk/ketypes.h>
#include <ndk/kefuncs.h>
#include <arc/arc.h>

extern "C"
VOID
NTAPI
KeFlushCurrentTb(VOID);

namespace Mm {

PFN_NUMBER
EarlyAllocPage (
    VOID);


const HARDWARE_PTE ProtectToPteBase[8] =
{
//         W C         C
//   V W O C D A D L G W
    {0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_INVALID
    {1,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_READONLY
    {1,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE
    {1,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE_READ
    {1,1,0,0,0,0,0,0,0,0,0,0,0}, // MM_READWRITE
    {1,0,0,0,0,0,0,0,0,1,0,0,0}, // MM_WRITECOPY
    {1,1,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE_READWRITE
    {1,0,0,0,0,0,0,0,0,1,0,0,0}, // MM_EXECUTE_WRITECOPY
};

const HARDWARE_PTE ProtectToPteFlags[32] =
{
//         W C         C
//   V W O C D A D L G W
    {0,0,0,0,0,0,0,0,0,0,0,0,0}, // -
    {0,0,0,0,1,0,0,0,0,0,0,0,0}, // MM_UNCACHED
    {0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_GUARDPAGE
    {0,0,0,1,0,0,0,0,0,0,0,0,0}, // MM_WRITECOMBINE
    {0,0,0,0,0,0,0,0,1,0,0,0,0}, // MM_GLOBAL
    {0,0,0,0,1,0,0,0,1,0,0,0,0}, // MM_GLOBAL|MM_UNCACHED
    {0,0,0,0,0,0,0,0,1,0,0,0,0}, // MM_GLOBAL|MM_GUARDPAGE
    {0,0,0,1,0,0,0,0,1,0,0,0,0}, // MM_GLOBAL|MM_WRITECOMBINE

    {0,0,1,0,0,0,0,0,0,0,0,0,0}, // MM_USER
    {0,0,1,0,1,0,0,0,0,0,0,0,0}, // MM_USER|MM_UNCACHED
    {0,0,1,0,0,0,0,0,0,0,0,0,0}, // MM_USER|MM_GUARDPAGE
    {0,0,1,1,0,0,0,0,0,0,0,0,0}, // MM_USER|MM_WRITECOMBINE
    {0,0,1,0,0,0,0,0,1,0,0,0,0}, // MM_USER|MM_GLOBAL
    {0,0,1,0,1,0,0,0,1,0,0,0,0}, // MM_USER|MM_GLOBAL|MM_UNCACHED
    {0,0,1,0,0,0,0,0,1,0,0,0,0}, // MM_USER|MM_GLOBAL|MM_GUARDPAGE
    {0,0,1,1,0,0,0,0,1,0,0,0,0}, // MM_USER|MM_GLOBAL|MM_WRITECOMBINE
};

#if 0
const ULONG64 ProtectToPteMask[8] =
{
    /* Base values */
    0,                                         // MM_INVALID
    PTE_VALID | PTE_NOEXECUTE,                 // MM_READONLY
    PTE_VALID,                                 // MM_EXECUTE
    PTE_VALID,                                 // MM_EXECUTE_READ
    PTE_VALID | PTE_WRITE | PTE_NOEXECUTE,     // MM_READWRITE
    PTE_VALID | PTE_WRITECOPY | PTE_NOEXECUTE, // MM_WRITECOPY
    PTE_VALID | PTE_WRITE,                     // MM_EXECUTE_READWRITE
    PTE_VALID | PTE_WRITECOPY,                 // MM_EXECUTE_WRITECOPY

    /* | MM_UNCACHED */
    0,                                         // MM_INVALID
    PTE_VALID | PTE_NOEXECUTE,                 // MM_UNCACHED | MM_READONLY
    PTE_VALID,                                 // MM_UNCACHED | MM_EXECUTE
    PTE_VALID,                                 // MM_UNCACHED | MM_EXECUTE_READ
    PTE_VALID | PTE_WRITE | PTE_NOEXECUTE,     // MM_READWRITE
    PTE_VALID | PTE_WRITECOPY | PTE_NOEXECUTE, // MM_WRITECOPY
    PTE_VALID | PTE_WRITE,                     // MM_EXECUTE_READWRITE
    PTE_VALID | PTE_WRITECOPY,                 // MM_EXECUTE_WRITECOPY

};
#endif

static KERNEL_VAD PageTableVad;
static KERNEL_VAD HyperSpaceVad;

VOID
INIT_FUNCTION
InitializePageTable ()
{
    ULONG PdPhysicalAddress;
    PPTE PdPte;
    PFN_NUMBER PdPfn;
    PPDE CurrentPde;
    ULONG_PTR NumberOfPages;
    NTSTATUS Status;

    /* Reserve the address space for the page tables */
    PageTableVad.Initialize();
    NumberOfPages = AddressToVpn(PTE_TOP) - AddressToVpn(PTE_BASE) + 1;
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&PageTableVad,
                                                   AddressToVpn(PTE_BASE),
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Reserve the address space for hyper space (same size as page tables) */
    HyperSpaceVad.Initialize();
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&HyperSpaceVad,
                                                   AddressToVpn(PTE_TOP) + 1,
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Make sure this is not PAE */
    if (__readcr4() & CR4_PAE)
    {
        ERR("Non-PAE kernel loaded with PAE enabled!\n");
        KeBugCheckEx(MEMORY_MANAGEMENT, 0x03030303, 0, 0, 0);
    }

    /* Get current directory base */
    PdPte = (PPTE)PDE_SELFMAP;
    PdPfn = PdPte->GetPageFrameNumber();

    PdPhysicalAddress = PdPfn << PAGE_SHIFT;
    NT_ASSERT(PdPhysicalAddress == __readcr3());

    /* Set directory base for the system process */
    PsGetCurrentProcess()->Pcb.DirectoryTableBase[0] = PdPhysicalAddress;

    /* Enable global pages */
    __writecr4(__readcr4() | CR4_PGE);
    ASSERT(__readcr4() & CR4_PGE);

    /* Enable page size extension */
    __writecr4(__readcr4() | CR4_PSE);
    ASSERT(__readcr4() & CR4_PSE);

    /* Loop the user mode PDEs */
    for (CurrentPde = AddressToPde(0);
         CurrentPde <= AddressToPde(MmHighestUserAddress);
         CurrentPde++)
    {
        /* Zero the PDE, clear all mappings */
        CurrentPde->Erase();
    }

    /* Flush the TLB */
    KeFlushCurrentTb();

    __writecr4(__readcr4());

    /* Setup 1 PPE for hyper space */
    //MiMapPPEs((PVOID)HYPER_SPACE_START, (PVOID)HYPER_SPACE_END);

    /* Setup PPEs for system space view */
    //MiMapPPEs(MiSystemViewStart, (PCHAR)MiSystemViewStart + MmSystemViewSize);

    /* Setup the mapping PDEs */
    //MiMapPDEs((PVOID)MI_MAPPING_RANGE_START, (PVOID)MAPPING_RANGE_END);

    /* Setup the mapping PTEs */
    //MmFirstReservedMappingPte = AddressToPte((PVOID)MAPPING_RANGE_START);
    //MmLastReservedMappingPte = AddressToPte((PVOID)MAPPING_RANGE_END);
    //MmFirstReservedMappingPte->u.Hard.PageFrameNumber = HYPERSPACE_PTES;

#if 0 //def _WINKD_
    /* Setup debug mapping PTE */
    MiMapPPEs((PVOID)MI_DEBUG_MAPPING, (PVOID)MI_DEBUG_MAPPING);
    MiMapPDEs((PVOID)MI_DEBUG_MAPPING, (PVOID)MI_DEBUG_MAPPING);
    MmDebugPte = MiAddressToPte((PVOID)MI_DEBUG_MAPPING);
#endif

    /* Setup PDE and PTEs for VAD bitmap and working set list */
    //MiMapPDEs((PVOID)MI_VAD_BITMAP, (PVOID)(MI_WORKING_SET_LIST + PAGE_SIZE - 1));
    //MiMapPTEs((PVOID)MI_VAD_BITMAP, (PVOID)(MI_WORKING_SET_LIST + PAGE_SIZE - 1));
}

VOID
InitializeMachineDependent (
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock)
{

    InitializePageTable();

}

extern "C"
VOID
NTAPI
MmSetPageProtect (
    struct _EPROCESS* Process,
    PVOID Address,
    ULONG flProtect)
{
    UNIMPLEMENTED;
}


enum VA_SPACES
{
    UserModeVaSpace,
    ProcessVaSpace,
    PageTableVaSpace,

    NumberVaSpaces,
};

class VA_SPACE
{
    ULONG_PTR StartingVpn;
};

VA_SPACE g_VaSpaces[NumberVaSpaces];

static const VA_SPACE* g_UserModeVaSpace = &g_VaSpaces[UserModeVaSpace];

static const ULONG SYSTEM_RANGE_X = 0xFF00FF00;
PVOID BlablaConstant = (PVOID)SYSTEM_RANGE_X;

PVOID MmLoaderMappingsStart;
ULONG_PTR MmHyperSpaceStart;
ULONG_PTR MmHyperSpaceEnd;
//ULONG_PTR MmHalVaStart;

VOID
ConfigureVaSpaces (
    PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    (void)g_UserModeVaSpace;


    MmSystemViewSize = 16 * 1024 * 1024;

    /* Calculate HyperSpace range */
    MmHyperSpaceStart = PTE_TOP + 1;
    //MmHyperSpaceEnd = MmHyperSpaceStart + HYPERSPACE_SIZE - 1;

    /* Put session space right after hyper space */
    MmSessionBase = MmHyperSpaceEnd + 1;



    /* Check if the /3GB switch was passed */
    if (strstr(LoaderBlock->LoadOptions, "3GB") != NULL)
    {
        MmSystemRangeStart = (PVOID)SYSTEM_RANGE_START_3GB;
        MmLoaderMappingsStart = (PVOID)LOADER_MAPPINGS_START_3GB;

        MmSessionSize = 48 * 1024 * 1024;

        MmSystemCacheStart =
    }
    else
    {
        MmSystemRangeStart = (PVOID)SYSTEM_RANGE_START;
        MmLoaderMappingsStart = (PVOID)LOADER_MAPPINGS_START;

        MmSessionSize = 64 * 1024 * 1024;
    }

    /* Calculate the user mode address range */
    MmHighestUserAddress = AddToPointer(MmSystemRangeStart, -1);
    MmUserProbeAddress = (ULONG_PTR)MmSystemRangeStart - PAGE_SIZE;


    MmSystemCacheStart = MmHyperSpaceEnd + 1;
    MmSystemCacheEnd =


    //MmHalVaStart = HAL_VA_START;

#if 0
    g_UserModeVaSpace =

    g_AddressSpaces[UserModeVaSpace].Initialize(0,
                                                MmHigestUserAddress,
                                                MEMORY_ALLOCATION_GRANULARITY,
                                                AcquireProcessLock);

    g_AddressSpaces[PageTableVaSpace].Initialize(PTE_BASE,
                                                 PTE_TOP,
                                                 PAGE_SIZE,
                                                 AcquireProcessLock);

    g_AddressSpaces[ProcessVaSpace].Initialize(MmHyperSpaceStart,
                                               MmHyperSpaceEnd,
                                               PAGE_SIZE,
                                               AcquireProcessLock);

    g_AddressSpaces[LoaderMappingVaSpace].Initialize(MmLoaderMappingsStart,
                                                     MmLoaderMappingsEnd,
                                                     PAGE_SIZE,
                                                     AcquireProcessLock);
#endif

}


}; // namespace Mm
