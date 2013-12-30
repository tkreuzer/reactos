/*!

    \file ContiguousMemory.cpp

    \brief Implements functions to manage contiguous physical memory

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include "PfnDatabase.hpp"
#include "Mapping.hpp"
#include "AddressSpace.hpp"

namespace Mm {

static const PHYSICAL_ADDRESS c_PhysicalAddress0 = {{0,0}};

/*! \fn AllocateContiguousMemory
 *
 *  \brief Allocates contiguous physical memory and maps it into the system
 *      address space.
 *
 *  \param [in] NumberOfBytes - Size of the contiguous chunk of physical memory
 *      in bytes.
 *
 *  \param [in] LowestAcceptableAddress - Lowest acceptable start address.
 *
 *  \param [in] HighestAcceptableAddress - Highest acceptable end address.
 *
 *  \param [in] BoundaryAddressMultiple - Page alignment.
 *
 *  \param [in] Protect - Protection to be used to map the memory.
 *
 *  \param [in] PreferredNode - Preferred NUMA node to allocate the memory from.
 *
 *  \return Pointer to the start of the mapped memory.
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
_When_(return != NULL, _Post_writable_byte_size_(NumberOfBytes))
PVOID
AllocateContiguousMemory (
    _In_ SIZE_T NumberOfBytes,
    _In_ PHYSICAL_ADDRESS LowestAcceptableAddress,
    _In_ PHYSICAL_ADDRESS HighestAcceptableAddress,
    _In_opt_ PHYSICAL_ADDRESS BoundaryAddressMultiple,
    _In_ ULONG Protect,
    _In_ NODE_REQUIREMENT PreferredNode)
{
    PFN_NUMBER LowestAcceptablePfn, HighestAcceptablePfn, BoundaryPageMultiple;
    PFN_COUNT NumberOfPages;
    PFN_NUMBER BasePageFrameNumber;
    PVOID BaseAddress;
    NTSTATUS Status;

    /* Check parameter */
    if ((BoundaryAddressMultiple.QuadPart & (PAGE_SIZE - 1)) != 0)
    {
        return NULL;
    }

    /* Convert to pages */
    NumberOfPages = (PFN_COUNT)BYTES_TO_PAGES(NumberOfBytes);
    LowestAcceptablePfn = (PFN_NUMBER)((LowestAcceptableAddress.QuadPart + PAGE_SIZE - 1) >> PAGE_SHIFT);
    HighestAcceptablePfn = (PFN_NUMBER)(HighestAcceptableAddress.QuadPart >> PAGE_SHIFT);
    BoundaryPageMultiple = (PFN_NUMBER)(BoundaryAddressMultiple.QuadPart >> PAGE_SHIFT);

    /* Check for overflow and if the ranges are OK */
    if (((LowestAcceptablePfn + NumberOfPages - 1) > HighestAcceptablePfn) ||
        ((LowestAcceptablePfn + NumberOfPages - 1) < LowestAcceptablePfn))
    {
        return NULL;
    }

    /* Allocate a range of contiguous physical pages */
    Status = g_PfnDatabase.AllocateContiguousPages(&BasePageFrameNumber,
                                                   NumberOfPages,
                                                   LowestAcceptablePfn,
                                                   HighestAcceptablePfn,
                                                   BoundaryPageMultiple,
                                                   PreferredNode);
    if (!NT_SUCCESS(Status))
    {
        return NULL;
    }

    /* Reserve a mapping range */
    BaseAddress = ReserveSystemMappingRange(NumberOfPages);
    if (BaseAddress == NULL)
    {
        g_PfnDatabase.FreeContiguousPages(BasePageFrameNumber);
        return NULL;
    }

    /* Map the physical pages */
    MapPhysicalMemory(AddressToVpn(BaseAddress),
                      NumberOfPages,
                      Protect,
                      BasePageFrameNumber);

    return BaseAddress;
}

extern "C" {

/*! \fn MmAllocateContiguousMemory
 *
 *  \brief Allocates contiguous physical memory and maps it into the system
 *      address space.
 *
 *  \param [in] NumberOfBytes - Size of the contiguous chunk of physical memory
 *      in bytes.
 *
 *  \param [in] HighestAcceptableAddress - Highest acceptable end address.
 *
 *  \return Pointer to the start of the mapped memory.
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateContiguousMemory (
  _In_ SIZE_T NumberOfBytes,
  _In_ PHYSICAL_ADDRESS HighestAcceptableAddress)
{
    return AllocateContiguousMemory(NumberOfBytes,
                                    c_PhysicalAddress0,
                                    HighestAcceptableAddress,
                                    c_PhysicalAddress0,
                                    MM_EXECUTE_READWRITE,
                                    MM_ANY_NODE_OK);
}

/*! \fn MmAllocateContiguousMemorySpecifyCache
 *
 *  \brief Allocates contiguous physical memory and maps it into the system
 *      address space.
 *
 *  \param [in] NumberOfBytes - Size of the contiguous chunk of physical memory
 *      in bytes.
 *
 *  \param [in] LowestAcceptableAddress - Lowest acceptable start address.
 *
 *  \param [in] HighestAcceptableAddress - Highest acceptable end address.
 *
 *  \param [in] BoundaryAddressMultiple - Page alignment.
 *
 *  \param [in] CachingType -
 *
 *  \return Pointer to the start of the mapped memory.
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateContiguousMemorySpecifyCache (
  _In_ SIZE_T NumberOfBytes,
  _In_ PHYSICAL_ADDRESS LowestAcceptableAddress,
  _In_ PHYSICAL_ADDRESS HighestAcceptableAddress,
  _In_opt_ PHYSICAL_ADDRESS BoundaryAddressMultiple,
  _In_ MEMORY_CACHING_TYPE CachingType)
{
    ULONG Protect;

    /* Convert protection */
    Protect = ConvertProtectAndCaching(PAGE_EXECUTE_READWRITE, CachingType);

    return AllocateContiguousMemory(NumberOfBytes,
                                    LowestAcceptableAddress,
                                    HighestAcceptableAddress,
                                    BoundaryAddressMultiple,
                                    Protect,
                                    MM_ANY_NODE_OK);
}

/*! \fn MmAllocateContiguousNodeMemory
 *
 *  \brief Allocates contiguous physical memory and maps it into the system
 *      address space.
 *
 *  \param [in] NumberOfBytes - Size of the contiguous chunk of physical memory
 *      in bytes.
 *
 *  \param [in] LowestAcceptableAddress - Lowest acceptable start address.
 *
 *  \param [in] HighestAcceptableAddress - Highest acceptable end address.
 *
 *  \param [in] BoundaryAddressMultiple - Page alignment.
 *
 *  \param [in] Win32Protect - Protection to be used to map the memory. One of
 *      the PAGE_* constants.
 *
 *  \param [in] PreferredNode - Preferred NUMA node to allocate the memory from.
 *
 *  \return Pointer to the start of the mapped memory.
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateContiguousNodeMemory (
    _In_ SIZE_T NumberOfBytes,
    _In_ PHYSICAL_ADDRESS LowestAcceptableAddress,
    _In_ PHYSICAL_ADDRESS HighestAcceptableAddress,
    _In_opt_ PHYSICAL_ADDRESS BoundaryAddressMultiple,
    _In_ ULONG Win32Protect,
    _In_ NODE_REQUIREMENT PreferredNode)
{
    ULONG Protect;

    /* Convert protection */
    Protect = ConvertProtect(Win32Protect);

    return AllocateContiguousMemory(NumberOfBytes,
                                    LowestAcceptableAddress,
                                    HighestAcceptableAddress,
                                    BoundaryAddressMultiple,
                                    Protect,
                                    PreferredNode);
}

/*! \fn MmAllocateContiguousMemorySpecifyCacheNode
 *
 *  \brief Allocates contiguous physical memory and maps it into the system
 *      address space.
 *
 *  \param [in] NumberOfBytes - Size of the contiguous chunk of physical memory
 *      in bytes.
 *
 *  \param [in] LowestAcceptableAddress - Lowest acceptable start address.
 *
 *  \param [in] HighestAcceptableAddress - Highest acceptable end address.
 *
 *  \param [in] BoundaryAddressMultiple - Page alignment.
 *
 *  \param [in] CachingType -
 *
 *  \param [in] PreferredNode - Preferred NUMA node to allocate the memory from.
 *
 *  \return Pointer to the start of the mapped memory.
 */
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateContiguousMemorySpecifyCacheNode (
    _In_ SIZE_T NumberOfBytes,
    _In_ PHYSICAL_ADDRESS LowestAcceptableAddress,
    _In_ PHYSICAL_ADDRESS HighestAcceptableAddress,
    _In_opt_ PHYSICAL_ADDRESS BoundaryAddressMultiple,
    _In_ MEMORY_CACHING_TYPE CachingType,
    _In_ NODE_REQUIREMENT PreferredNode)
{
    ULONG Protect;

    /* Convert protection */
    Protect = ConvertProtectAndCaching(PAGE_EXECUTE_READWRITE, CachingType);

    return AllocateContiguousMemory(NumberOfBytes,
                                    LowestAcceptableAddress,
                                    HighestAcceptableAddress,
                                    BoundaryAddressMultiple,
                                    Protect,
                                    PreferredNode);
}

/*! \fn MmFreeContiguousMemory
 *
 *  \brief Frees a mapping of contiguous physical memory that was previously
 *      mapped using one of the MmAllocateContiguousMemory* functions.
 *
 *  \param [in] BaseAddress - Pointer to the start of the mapped memory that is
 *      to be unmapped.
 */
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreeContiguousMemory (
    _In_ PVOID BaseAddress)
{
    PHYSICAL_ADDRESS PhysicalAddress;
    PFN_NUMBER BasePageFrameNumber;

    /* Get the PFN of the first mapped page */
    PhysicalAddress = MmGetPhysicalAddress(BaseAddress);
    BasePageFrameNumber = (PFN_NUMBER)(PhysicalAddress.QuadPart >> PAGE_SHIFT);
    NT_ASSERT(BasePageFrameNumber != 0);

    //UnmapPages

    /* Release the contiguous physical pages */
    g_PfnDatabase.FreeContiguousPages(BasePageFrameNumber);

    if (KeGetCurrentIrql() >= DISPATCH_LEVEL)
    {
        /// \todo queue a workitem to release the mapping
        NT_ASSERT(FALSE);
    }
    else
    {
        ReleaseSystemMappingRange(BaseAddress);
    }

}

/*! \fn MmFreeContiguousMemorySpecifyCache
 *
 *  \brief Frees a mapping of contiguous physical memory that was previously
 *      mapped using one of the MmAllocateContiguousMemory* functions.
 *
 *  \param [in] BaseAddress - Pointer to the start of the mapped memory that is
 *      to be unmapped.
 *
 *  \param [in] NumberOfBytes - ignored.
 *
 *  \param [in] CachingType - ignored.
 *
 *  \remarks The function simply calls MmFreeContiguousMemory, which is the
 *      same that Windows does.
 */
_IRQL_requires_max_ (DISPATCH_LEVEL)
VOID
NTAPI
MmFreeContiguousMemorySpecifyCache (
    _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    /* Ignore NumberOfBytes and CachingType and call the basic function. */
    MmFreeContiguousMemory(BaseAddress);
}

}; // extern "C"
}; // namespace Mm
