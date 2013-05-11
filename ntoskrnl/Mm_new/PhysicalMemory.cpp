
#include "ntosbase.h"
#include "PfnDatabase.hpp"

namespace Mm {
extern "C" {

/*!

    \name  MmGetPhysicalMemoryRanges

    \brief Returns an array of PHYSICAL_MEMORY_RANGE, describing the systems
           physical memory.

    \return Pointer to the newly allocated array of PHYSICAL_MEMORY_RANGE
            structures. The pool-tag is 'hPmM'

    The array is allocated from non-paged pool and consists or n+1 elements,
    where n is the number of contiguous memory regions. The last element has
    the value 0 for both the BaseAddress and NumberOfBytes fields.

    Note that the function uses the PhysicalMemoryDescriptor from the PFN
    database which is constant after it has been initialized. Therefore we
    don't require any lock.

    \ref http://www.jungo.com/st/support/tech_docs/td129.html

*/
_IRQL_requires_max_ (PASSIVE_LEVEL)
PPHYSICAL_MEMORY_RANGE
NTAPI
MmGetPhysicalMemoryRanges (
    VOID)
{
    const PHYSICAL_MEMORY_DESCRIPTOR* PhysicalMemoryDescriptor;
    ULONG NumberOfRuns, ArraySize, i;
    PPHYSICAL_MEMORY_RANGE MemoryRanges;

    /* Get a pointer to the physical memory descriptor */
    PhysicalMemoryDescriptor = g_PfnDatabase.GetPhysicalMemoryDescriptor();

    /* Query the number of physical memory runs */
    NumberOfRuns = PhysicalMemoryDescriptor->NumberOfRuns;

    /* Calculate the array size (one additional terminating entry) */
    ArraySize = (NumberOfRuns + 1) * sizeof(*MemoryRanges);

    /* Allocate the array */
    MemoryRanges = static_cast<PPHYSICAL_MEMORY_RANGE>(
        ExAllocatePoolWithTag(NonPagedPool, ArraySize, TAG_MEMORY_RANGES));
    if (MemoryRanges == NULL)
    {
        return NULL;
    }

    /* Loop all memory runs */
    for (i = 0; i < NumberOfRuns; i++)
    {
        ULONG64 BasePage, PageCount;

        /* Fill in the data */
        BasePage = PhysicalMemoryDescriptor->Run[i].BasePage;
        MemoryRanges[i].BaseAddress.QuadPart = BasePage << PAGE_SHIFT;
        PageCount = PhysicalMemoryDescriptor->Run[i].PageCount;
        MemoryRanges[i].NumberOfBytes.QuadPart = PageCount << PAGE_SHIFT;
    }

    /* Zero the terminating entry */
    MemoryRanges[i].BaseAddress.QuadPart = 0;
    MemoryRanges[i].NumberOfBytes.QuadPart = 0;

    return MemoryRanges;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmAddPhysicalMemory (
  _In_ PPHYSICAL_ADDRESS StartAddress,
  _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_SUPPORTED;;
}

_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmRemovePhysicalMemory (
  _In_ PPHYSICAL_ADDRESS StartAddress,
  _Inout_ PLARGE_INTEGER NumberOfBytes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_SUPPORTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Out_writes_bytes_opt_(NumberOfBytes)
PVOID
NTAPI
MmAllocateNonCachedMemory (
  _In_ SIZE_T NumberOfBytes)
{
    UNIMPLEMENTED;
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmFreeNonCachedMemory (
  _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes)
{
    UNIMPLEMENTED;
}

PVOID
NTAPI
MmGetVirtualForPhysical (
  _In_ PHYSICAL_ADDRESS PhysicalAddress)
{
    UNIMPLEMENTED;
    return NULL;
}

NTSTATUS
NTAPI
MmMarkPhysicalMemoryAsBad (
    IN PPHYSICAL_ADDRESS StartAddress,
    IN OUT PLARGE_INTEGER NumberOfBytes)
{
#if 0
    PFN_NUMBER StartingPfn, NumberOfPages;

    StartingPfn = StartAddress->QuadPart >> PAGE_SHIFT;
    NumberOfPages = NumberOfBytes->QuadPart >> PAGE_SHIFT;
    return g_PfnDatabase.MarkPhysicalMemory(PfnBad, StartingPfn, NumberOfPages);
#endif
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmMarkPhysicalMemoryAsGood (
    IN PPHYSICAL_ADDRESS StartAddress,
    IN OUT PLARGE_INTEGER NumberOfBytes)
{
#if 0
    PFN_NUMBER StartingPfn, NumberOfPages;

    StartingPfn = StartAddress->QuadPart >> PAGE_SHIFT;
    NumberOfPages = NumberOfBytes->QuadPart >> PAGE_SHIFT;
    return g_PfnDatabase.MarkPhysicalMemory(PfnFree, StartingPfn, NumberOfPages);
#endif
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


/** Syscall API ***************************************************************/

NTSTATUS
NTAPI
NtAllocateUserPhysicalPages (
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtFreeUserPhysicalPages (
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtMapUserPhysicalPages (
    _In_ PVOID VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtMapUserPhysicalPagesScatter (
    _In_ PVOID *VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _Inout_ PULONG_PTR UserPfnArray)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"
}; // namespace Mm
