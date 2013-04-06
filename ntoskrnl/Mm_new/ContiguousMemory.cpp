
#include "ntosbase.h"
#include "PfnDatabase.hpp"
#include "Mapping.hpp"

namespace Mm {

static const PHYSICAL_ADDRESS c_PhysicalAddress0 = {0,0};

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
MiAllocateContiguousMemory (
    _In_ SIZE_T NumberOfBytes,
    _In_ PHYSICAL_ADDRESS LowestAcceptableAddress,
    _In_ PHYSICAL_ADDRESS HighestAcceptableAddress,
    _In_opt_ PHYSICAL_ADDRESS BoundaryAddressMultiple,
    _In_ ULONG Protect,
    _In_ MEMORY_CACHING_TYPE CachingType,
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
    LowestAcceptablePfn = (LowestAcceptableAddress.QuadPart + PAGE_SIZE - 1) >> PAGE_SHIFT;
    HighestAcceptablePfn = HighestAcceptableAddress.QuadPart >> PAGE_SHIFT;
    BoundaryPageMultiple = BoundaryAddressMultiple.QuadPart >> PAGE_SHIFT;

    /* Check for overflow and if the ranges are ok */
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

    /* Map the physical pages */
    BaseAddress = MiMapPhysicalMemory(BasePageFrameNumber,
                                      NumberOfPages,
                                      Protect,
                                      CachingType);
    if (BaseAddress == NULL)
    {
        g_PfnDatabase.FreeContiguousPages(BasePageFrameNumber);
    }

    return BaseAddress;
}

extern "C" {

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_ (return != NULL, _Post_writable_byte_size_ (NumberOfBytes))
PVOID
NTAPI
MmAllocateContiguousMemory (
  _In_ SIZE_T NumberOfBytes,
  _In_ PHYSICAL_ADDRESS HighestAcceptableAddress)
{
    return MiAllocateContiguousMemory(NumberOfBytes,
                                      c_PhysicalAddress0,
                                      HighestAcceptableAddress,
                                      c_PhysicalAddress0,
                                      PAGE_EXECUTE_READWRITE,
                                      MmCached,
                                      MM_ANY_NODE_OK);
}

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
    return MiAllocateContiguousMemory(NumberOfBytes,
                                      LowestAcceptableAddress,
                                      HighestAcceptableAddress,
                                      BoundaryAddressMultiple,
                                      PAGE_EXECUTE_READWRITE,
                                      CachingType,
                                      MM_ANY_NODE_OK);
}

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
    _In_ ULONG Protect,
    _In_ NODE_REQUIREMENT PreferredNode)
{
    MEMORY_CACHING_TYPE CachingType;

    if (Protect & PAGE_WRITECOMBINE)
        CachingType = MmWriteCombined;
    else if (Protect & PAGE_NOCACHE)
        CachingType = MmNonCached;
    else
        CachingType = MmCached;

    return MiAllocateContiguousMemory(NumberOfBytes,
                                      LowestAcceptableAddress,
                                      HighestAcceptableAddress,
                                      BoundaryAddressMultiple,
                                      Protect,
                                      CachingType,
                                      PreferredNode);
}

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
    return MiAllocateContiguousMemory(NumberOfBytes,
                                      LowestAcceptableAddress,
                                      HighestAcceptableAddress,
                                      BoundaryAddressMultiple,
                                      PAGE_EXECUTE_READWRITE,
                                      CachingType,
                                      PreferredNode);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmFreeContiguousMemory (
    _In_ PVOID BaseAddress)
{
#if 0
    NON_PAGED_KERNEL_VAD* Vad;
    NTSTATUS Status;
    PMDL Mdl;

    Vad = g_KernelAddressSpace.VadTable.FindVadByAddress(BaseAddress);
    NT_ASSERT(Vad != NULL);

    Status = g_KernelAddressSpace.VadTable.RemoveVad(Vad);
    NT_ASSERT(NT_SUCCESS(Status));

    Mdl = Vad->GetMdl();
    NT_ASSERT(Mdl != NULL);

    g_PfnDatabase.FreeContiguousPages(Mdl);

    Vad->Release();
#endif
    UNIMPLEMENTED;
}

_IRQL_requires_max_ (DISPATCH_LEVEL)
VOID
NTAPI
MmFreeContiguousMemorySpecifyCache (
    _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    MmFreeContiguousMemory(BaseAddress);
}

}; // extern "C"
}; // namespace Mm
