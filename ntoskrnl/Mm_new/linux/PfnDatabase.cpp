/*!

    \file PfnDatabase.cpp

    \brief Implements the PFN_DATABASE class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "../PfnDatabase.hpp"
#include "../VadTable.hpp"
#include "../KernelVad.hpp"
#include "../MmData.hpp"
//#include _ARCH_RELATIVE_(PageTables.hpp)
//#include _ARCH_RELATIVE_(MachineDependent.hpp)
#include <arc/arc.h>
#include <limits.h>
#include <ndk/ketypes.h>
#include <ndk/pstypes.h>

#define PFN_DATABASE_ADDRESS 0x82000000

/*

Concurrency between interlocked page removal and contiguous page allocation:
- Contiguous allocator
    - Lock global contiguous memory spinlock
    - trigger an IPI for all CPUs
        - All CPUs wait, except this one
        - This CPU performs the allocation (non-interlocked)
        -


*/

extern "C" {

extern "C" PFN_NUMBER MmNumberOfPhysicalPages;
extern "C" PFN_NUMBER MmAvailablePages;
extern "C" UCHAR KeNumberNodes;

};

namespace Mm {

PFN_DATABASE g_PfnDatabase;
ULONG PFN_DATABASE::m_CacheColorBits;
ULONG PFN_DATABASE::m_CacheColorMask;
PPFN_LIST PFN_DATABASE::m_FreeLists;
PPFN_LIST PFN_DATABASE::m_ZeroedLists;
PPHYSICAL_MEMORY_DESCRIPTOR PFN_DATABASE::m_PhysicalMemoryDescriptor;
PRTL_BITMAP_EX PFN_DATABASE::m_PhysicalMemoryBitmap;
PFN_ENTRY* PFN_DATABASE::m_PfnArray;
PULONG_PTR PFN_DATABASE::m_PhysicalBitmapBuffer;
static KERNEL_VAD g_PfnDatabaseVad;
static KERNEL_VAD g_MappingPtesVad;
static KEVENT PagesAvailableEvent;
#define NUMBER_OF_MAPPING_PTES 128
ULONG NodeShift;
ULONG NodeMask;

SIZE_T MmSizeOfPfnDatabase;

PFN_NUMBER EarlyAllocPageBase;
PFN_NUMBER EarlyAllocPageCount;
#ifdef MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
PFN_NUMBER EarlyAllocLargePageBase;
#endif // MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
ULONG NumberOfPhysicalMemoryRuns;
ULONG NumberOfMemoryDescriptors;
PMEMORY_ALLOCATION_DESCRIPTOR LargestFreeDescriptor;


/*! \name ScanMemoryDescriptors
 *
 * \brief Collects information from the loader blocks's memory descriptors
 *
 * \param [in] LoaderBlock
 *       Pointer to the loader block.
 *
 * \remarks This function sets up MmLowestPhysicalPage, MmHighestPhysicalPage,
 *      MmNumberOfPhysicalPages, MmBadPagesDetected, MmAvailablePages,
 *      NumberOfPhysicalMemoryRuns, NumberOfMemoryDescriptors and
 *      LargestFreeDescriptor
 */
VOID
INIT_FUNCTION
ScanMemoryDescriptors (
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock)
{

    /* Initialize the physical page range */
    MmNumberOfPhysicalPages = 0xfffff;
    MmLowestPhysicalPage = 0;
    MmHighestPhysicalPage = MmNumberOfPhysicalPages;
    MmAvailablePages = MmNumberOfPhysicalPages;
    NumberOfMemoryDescriptors = 0;
    NumberOfPhysicalMemoryRuns = 1;
    MmBadPagesDetected = 0;
}

PHYSICAL_MEMORY_DESCRIPTOR g_PhysicalMemoryDescriptor;

VOID
INIT_FUNCTION
PFN_DATABASE::Initialize (
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock)
{


    /* Calculate location of the page lists and physical memory descriptor */
    m_PfnArray = (PFN_ENTRY*)PFN_DATABASE_ADDRESS;

    /* Initialize the physical memory descriptor */
    m_PhysicalMemoryDescriptor = &g_PhysicalMemoryDescriptor;
    m_PhysicalMemoryDescriptor->NumberOfRuns = NumberOfPhysicalMemoryRuns;
    m_PhysicalMemoryDescriptor->NumberOfPages = MmNumberOfPhysicalPages;
    m_PhysicalMemoryDescriptor->Run[0].BasePage = MmLowestPhysicalPage;
    m_PhysicalMemoryDescriptor->Run[0].PageCount = MmNumberOfPhysicalPages;

    /* Set global variables */
    MmPfnDatabase = m_PfnArray;
    MmSizeOfPfnDatabase = 0;

}


/* FUNCTIONS ******************************************************************/

VOID
ZeroPage (
    _In_ PFN_NUMBER PageFrameNumber)
{

}

BOOLEAN
PFN_DATABASE::IsValidPageFrameNumber (
    _In_ PFN_NUMBER PageFrameNumber)
{
    /* Return, whether the PFN is valid */
    return 0;
}


VOID
PFN_DATABASE::MakeActivePfn (
    _Inout_ PFN_NUMBER PageFrameNumber,
    _In_ PVOID PteAddress,
    _In_ ULONG Protect)
{

}


VOID
PFN_DATABASE::MakeLargePagePfn (
    _Inout_ PFN_NUMBER PageFrameNumber,
    _In_ PVOID PteAddress,
    _In_ ULONG Protect)
{
    //UNIMPLEMENTED;
}

VOID
PFN_DATABASE::MakePageTablePfn (
    _Inout_ PFN_NUMBER PageFrameNumber,
    _In_ PVOID PteAddress,
    _In_ ULONG Protect)
{
}

ULONG
PFN_DATABASE::ModifyEntryCount (
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ LONG Addend)
{
    return 0;
}

ULONG
PFN_DATABASE::ModifyUsedCount (
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ LONG Addend)
{
    return 0;
}

ULONG
PFN_DATABASE::ModifyValidCount (
    _In_ PFN_NUMBER PageFrameNumber,
    _In_ LONG Addend)
{
    return 0;
}

PFN_NUMBER
PFN_DATABASE::AllocatePageLocked (
    _In_ ULONG DesiredPageColor,
    _Inout_ PBOOLEAN Zeroed)
{
    return 0;
}

PFN_NUMBER
PFN_DATABASE::AllocatePage (
    _In_ BOOLEAN Zeroed)
{
    /* Return the new page */
    return 0;
}

VOID
PFN_DATABASE::FreePageLocked (
    _Inout_ PFN_NUMBER PageFrameNumber)
{

}

VOID
PFN_DATABASE::ReleasePage (
    _Inout_ PFN_NUMBER PageFrameNumber)
{

}

NTSTATUS
PFN_DATABASE::AllocateMultiplePages (
    _Out_ PFN_LIST* PageList,
    _In_ ULONG_PTR NumberOfPages,
    _In_ BOOLEAN Zeroed)
{

    return STATUS_SUCCESS;
}


VOID
PFN_DATABASE::ReleaseMultiplePages (
    _Inout_ PFN_LIST* PageList)
{

}

NTSTATUS
PFN_DATABASE::AllocateLargePages (
    _Out_ PFN_LIST* LargePageList,
    _In_ ULONG_PTR NumberOfLargePages,
    _In_ BOOLEAN Zeroed)
{

    return STATUS_SUCCESS;
}

VOID
PFN_DATABASE::ReleaseLargePages (
    _Inout_ PFN_LIST* PageList)
{
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
PFN_DATABASE::AllocateContiguousPages (
    _Out_ PPFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ PFN_NUMBER LowestAcceptablePfn,
    _In_ PFN_NUMBER HighestAcceptablePfn,
    _In_opt_ PFN_NUMBER BoundaryPageMultiple,
    _In_ NODE_REQUIREMENT PreferredNode)
{

    return 0;
}

VOID
PFN_DATABASE::FreeContiguousPages (
    _In_ PFN_NUMBER BasePageFrameNumber)
{
}


VOID
PFN_DATABASE::LockPage (
    _In_ PFN_NUMBER PageFrameNumber)
{

}

VOID
PFN_DATABASE::UnlockPage (
    _In_ PFN_NUMBER PageFrameNumber)
{

}

VOID
PFN_DATABASE::SetPageMapping (
    _In_ PFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    UNIMPLEMENTED;
}


}; // namespace Mm
