
#include "../ntosbase.h"
#include "PageTables.hpp"
#include "MachineDependent.hpp"
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

VOID
INIT_FUNCTION
InitializePageTable ()
{
    ULONG PdPhysicalAddress;
    PPTE PdPte;
    PFN_NUMBER PdPfn;
    PPDE CurrentPde;

    /* Get current directory base */
    PdPte = (PPTE)AddressToPde((PVOID)PTE_BASE);
    PdPfn = PdPte->GetPageFrameNumber();

    PdPhysicalAddress = PdPfn << PAGE_SHIFT;
    ASSERT(PdPhysicalAddress == __readcr3());

    /* Set directory base for the system process */
    PsGetCurrentProcess()->Pcb.DirectoryTableBase[0] = PdPhysicalAddress;

    /* Enable global pages */
    __writecr4(__readcr4() | CR4_PGE);
    ASSERT(__readcr4() & CR4_PGE);

    /* Loop the user mode PDEs */
    for (CurrentPde = AddressToPde(0);
         CurrentPde <= AddressToPde(MmHighestUserAddress);
         CurrentPde++)
    {
        /* Zero the PXE, clear all mappings */
        CurrentPde->Erase();
    }

    /* Flush the TLB */
    KeFlushCurrentTb();


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

}; // namespace Mm

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
