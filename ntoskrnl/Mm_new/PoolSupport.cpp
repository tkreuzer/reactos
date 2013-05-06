
#include "ntosbase.h"
#include "KernelVad.hpp"
#include "Mapping.hpp"
#include "VadTable.hpp"
#include "AddressSpace.hpp"
#include "amd64/MachineDependent.hpp"

namespace Mm {

extern "C"
VOID
NTAPI
InitializePool(IN POOL_TYPE PoolType,
               IN ULONG Threshold);

extern SIZE_T MmSizeOfPfnDatabase;

#define NP_POOL_SIZE_IN_PAGES_LOW (40 * 1024 * 1024 / PAGE_SIZE)

#ifdef _WIN64
#define POOL_SIZE_IN_PAGES_MAX (128ULL * 1024 * 1024 * 1024 / PAGE_SIZE)
#else
#define POOL_SIZE_IN_PAGES_MAX  (2 * 1024 * 1024 * 1024 / PAGE_SIZE)
#endif

extern "C" PVOID MmPfnDatabase;
extern "C" PFN_NUMBER MmNumberOfPhysicalPages;
extern "C" PVOID MmNonPagedPoolStart;
extern "C" SIZE_T MmSizeOfNonPagedPoolInBytes;
extern "C" SIZE_T MmMaximumNonPagedPoolInBytes;
extern "C" PVOID MmPagedPoolStart;
extern "C" SIZE_T MmSizeOfPagedPoolInBytes;

KERNEL_VAD PoolVad[2];
RTL_BITMAP PoolBitmap[2];
RTL_BITMAP EndOfAllocationBitmap[2];
ULONG PoolHintIndex[2];
KSPIN_LOCK PoolPageSpinlock[2];

#ifndef _WIN64
/* On 32 bit systems we track each large page sized VA block used for np pool */
#define MI_MAXIMUM_SIZE_OF_SYSTEM_SPACE (2 * 1024 * 1024 * 1024)
ULONG NonPagedPoolVaBitmap[MI_MAXIMUM_SIZE_OF_SYSTEM_SPACE /  LARGE_PAGE_SIZE / 32];
ULONG InitialPoolSizeInPages[2];
PVOID* PoolExpansionArray[2];
#endif

/*!
 * MmSizeOfNonPagedPoolInBytes, MmMaximumNonPagedPoolInBytes,
 * MmSizeOfPagedPoolInBytes
*/
static
VOID
INIT_FUNCTION
CalculatePoolDimensions (
    VOID)
{
    PFN_NUMBER SizeOfNonPagedPoolInPages, MaximumNonPagedPoolInPages;
    PVOID EndAddress;

    /* Windows Internals: For non-paged pool, the initial size is 3 percent of
       system RAM. */
    SizeOfNonPagedPoolInPages = MmNumberOfPhysicalPages * 3 / 100;

    /* If this is less than 40 MB,  ... */
    if (SizeOfNonPagedPoolInPages < NP_POOL_SIZE_IN_PAGES_LOW)
    {
        /* ... the system will instead use 40 MB as long as 10 percent of RAM
           results in more than 40 MB; */
        if ((MmNumberOfPhysicalPages / 10) > NP_POOL_SIZE_IN_PAGES_LOW)
        {
            SizeOfNonPagedPoolInPages = NP_POOL_SIZE_IN_PAGES_LOW;
        }
        else
        {
            /* otherwise 10 percent of RAM is chosen as a minimum.  */
            SizeOfNonPagedPoolInPages = (MmNumberOfPhysicalPages / 10);
        }
    }

    /* Maximum is 75% of physical memory or 2/128 GB, whichever is smaller */
    MaximumNonPagedPoolInPages = min(MmNumberOfPhysicalPages * 3 / 4,
                                     POOL_SIZE_IN_PAGES_MAX);

    MmSizeOfNonPagedPoolInBytes = SizeOfNonPagedPoolInPages * PAGE_SIZE;
    MmMaximumNonPagedPoolInBytes = MaximumNonPagedPoolInPages * PAGE_SIZE;

    /* Non-paged pool starts after the PFN Database */
    MmNonPagedPoolStart = AddToPointer(MmPfnDatabase, MmSizeOfPfnDatabase);
    MmNonPagedPoolStart = ALIGN_UP_POINTER_BY(MmNonPagedPoolStart, PAGE_SIZE);

    /* Get the end address and align it up to the next large page boundary */
    EndAddress = AddToPointer(MmNonPagedPoolStart, MmSizeOfNonPagedPoolInBytes);
    EndAddress = ALIGN_UP_POINTER_BY(EndAddress, LARGE_PAGE_SIZE);

    /* Recalculate non-paged pool size */
    MmSizeOfNonPagedPoolInBytes = reinterpret_cast<PUCHAR>(EndAddress) -
                                  reinterpret_cast<PUCHAR>(MmNonPagedPoolStart);

    /// \todo improve this
    MmSizeOfPagedPoolInBytes = 32 * 1024 * 1024;
    MmPagedPoolStart = AddToPointer(MmNonPagedPoolStart, MmMaximumNonPagedPoolInBytes);
    MmPagedPoolStart = ALIGN_UP_POINTER_BY(MmPagedPoolStart, LARGE_PAGE_SIZE);

#ifndef _WIN64
    InitialPoolSizeInPages[NonPagedPool] = SizeOfNonPagedPoolInPages;
    InitialPoolSizeInPages[PagedPool] = 0; /// \todo
#endif



}

VOID
INIT_FUNCTION
InitializePoolSupportSingle (
    _In_ POOL_TYPE PoolType,
    _In_ PVOID PoolStart,
    _In_ SIZE_T InitialSize,
    _In_ SIZE_T MaximumSize,
    _In_ ULONG Protect)
{
    NTSTATUS Status;
    ULONG_PTR NumberOfPages, MaximumNumberOfPages;
    ULONG_PTR BitmapSize, AllocatedSize, StartingVpn;
    PULONG BitmapBuffer;

    /* Only these 2 types are allowed */
    NT_ASSERT((PoolType == NonPagedPool) || (PoolType == PagedPool));

    /* Initialize the static pool VAD object */
    PoolVad[PoolType].Initialize();

    /* Calculate the range of the pool */
    StartingVpn = AddressToVpn(PoolStart);
    NumberOfPages = InitialSize / PAGE_SIZE;
    MaximumNumberOfPages = MaximumSize / PAGE_SIZE;

#ifdef _WIN64
    /* On 64 bit systems we reserve the maximum pool size */
    Status = g_KernelVadTable.InsertVadObjectAtVpn(PoolVad[PoolType].GetVadObject(),
                                                   StartingVpn,
                                                   MaximumNumberOfPages);
#else
    /* On 32 bit systems we only reserve the actual pool size */
    Status = g_KernelVadTable.InsertVadObjectAtVpn(PoolVad[PoolType].GetVadObject(),
                                                   StartingVpn,
                                                   NumberOfPages);
#endif
    NT_ASSERT(NT_SUCCESS(Status));

    /* Check for large page mapping */ /// \todo Maybe we can get rid of this
    if (Protect & MM_LARGEPAGE)
    {
        /* Align to large page boundary */
        StartingVpn = ALIGN_UP_BY(StartingVpn, LARGE_PAGE_SIZE / PAGE_SIZE);
        NumberOfPages = ALIGN_DOWN_BY(NumberOfPages, LARGE_PAGE_SIZE / PAGE_SIZE);
    }

    /// \todo this if (...) is all pretty hacky, maybe we can improve this later

    /* Check if we shall map the pages */
    if (Protect & MM_MAPPED)
    {
        /* Map the pages */
        Status = CreateMapping(StartingVpn, NumberOfPages, Protect, NULL, NULL);
        NT_ASSERT(NT_SUCCESS(Status));
    }

    /* The bitmap is already allocated pool */
    BitmapSize = ((MaximumNumberOfPages + 31) / 32) * sizeof(ULONG);

    /* Initialize the pool bitmap */
    BitmapBuffer = static_cast<PULONG>(PoolStart);
    RtlInitializeBitMap(&PoolBitmap[PoolType], BitmapBuffer, (ULONG)NumberOfPages);

    /* Initialize the end-of-allocation bitmap */
    BitmapBuffer = static_cast<PULONG>(AddToPointer(BitmapBuffer, BitmapSize));
    RtlInitializeBitMap(&EndOfAllocationBitmap[PoolType], BitmapBuffer, (ULONG)NumberOfPages);

    /* The bitmaps are already allocated pool */
    AllocatedSize = 2 * BitmapSize;

#ifndef _WIN64
    /* On 32 bit systems, we add an array of expansion pointers */
    PoolExpansionArray[NonPagedPool] = AddToPointer(BitmapBuffer, AllocatedSize);
    NonPagedPoolExpansionCount =
        (MaximumNumberOfPages - NumberOfPages + LARGE_PAGE_SIZE - 1) / LARGE_PAGE_SIZE;

    /* Add the expansion array to the allocated size */
    AllocatedSize += NonPagedPoolExpansionCount * sizeof(PVOID);

    /// \todo set bits in NonPagedPoolVaBitmap
#endif

    /* Calculate how many pages we used up already */
    NumberOfPages = BYTES_TO_PAGES(AllocatedSize);

    /* Check if we did not map the pages */
    if (!(Protect & MM_MAPPED))
    {
        /* We still need to map the pages */
        Protect |= MM_MAPPED;
        Status = CreateMapping(StartingVpn, NumberOfPages, Protect, NULL, NULL);
        NT_ASSERT(NT_SUCCESS(Status));
    }

    /* Mark the pages we used */
    RtlSetBits(&PoolBitmap[PoolType], 0, (ULONG)NumberOfPages);

    /* Initialize the rest of the pool */
    InitializePool(PoolType, 0);
}

VOID
ScanPageTables (
    _In_ PFN_NUMBER PageFrameNumber);

VOID
INIT_FUNCTION
InitializePoolSupport (
    VOID)
{
    ULONG Protect;

    /* Calculate pool sizes */
    CalculatePoolDimensions();

    Protect = MM_READWRITE | MM_GLOBAL | MM_MAPPED | MM_NONPAGED | MM_LARGEPAGE;
    InitializePoolSupportSingle(NonPagedPool,
                                MmNonPagedPoolStart,
                                MmSizeOfNonPagedPoolInBytes,
                                MmMaximumNonPagedPoolInBytes,
                                Protect);

    Protect = MM_READWRITE | MM_GLOBAL;
    InitializePoolSupportSingle(PagedPool,
                                MmPagedPoolStart,
                                MmSizeOfPagedPoolInBytes,
                                POOL_SIZE_IN_PAGES_MAX,
                                Protect);


}

NTSTATUS
ExpandPool (
    _In_ ULONG BasePoolType,
    _In_ ULONG Index)
{

    //BitmapBuffer = static_cast<PULONG>(PoolStart);
    //RtlInitializeBitMap(&PoolBitmap[PoolType], BitmapBuffer, (ULONG)NumberOfPages);

    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

extern "C" {

POOL_TYPE
NTAPI
MmDeterminePoolType (
    IN PVOID VirtualAddress)
{
#ifdef _WIN64
    PVOID PoolEnd;

    /* The whole non-paged pool is in a contiguous VA region */
    PoolEnd = AddToPointer(MmNonPagedPoolStart, MmSizeOfNonPagedPoolInBytes);
    if ((VirtualAddress >= MmNonPagedPoolStart) &&
        (VirtualAddress < PoolEnd))
    {
        return NonPagedPool;
    }

    PoolEnd = AddToPointer(MmPagedPoolStart, MmSizeOfPagedPoolInBytes);
    if ((VirtualAddress >= MmPagedPoolStart) &&
        (VirtualAddress < PoolEnd))
    {
        return PagedPool;
    }
#else
    /* Check the pool VA bitmap */
    Index = PointerDiff(VirtualAddress, MmSystemRangeStart) / LARGE_PAGE_SIZE;
    if ((NonPagedPoolVaBitmap[Index / 32] >> (Index & 31)) & 1)
    {
        return NonPagedPool;
    }

    /// \todo check paged pool bitmap
    return PagedPool;
#endif
    KeBugCheck(0);
}

PVOID
NTAPI
MiAllocatePoolPages (
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T SizeInBytes)
{
    PRTL_BITMAP Bitmap;
    ULONG BasePoolType, PageCount, Index;
    KLOCK_QUEUE_HANDLE LockHandle;
    PVOID BaseAddress;
    SIZE_T PoolSizeInBytes;
    NTSTATUS Status;

    /* Get the base pool type */
    BasePoolType = PoolType & 1;

    if (BasePoolType == NonPagedPool)
    {
        BaseAddress = MmNonPagedPoolStart;
        PoolSizeInBytes = MmSizeOfNonPagedPoolInBytes;
    }
    else
    {
        BaseAddress = MmPagedPoolStart;
        PoolSizeInBytes = MmSizeOfPagedPoolInBytes;
    }

    /* Calculate page count */
    PageCount = static_cast<ULONG>(BYTES_TO_PAGES(SizeInBytes));

    /* First try to find clear bits without holding the lock */
    Bitmap = &PoolBitmap[BasePoolType];

    for (;;)
    {
        /* First try to find clear bits without holding the lock */
        Index = RtlFindClearBits(Bitmap, PageCount, PoolHintIndex[BasePoolType]);
        if (Index != -1)
        {
            /* Acquire the lock */
            KeAcquireInStackQueuedSpinLock(&PoolPageSpinlock[BasePoolType],
                                           &LockHandle);

            /* Set the bits */
            Index = RtlFindClearBitsAndSet(Bitmap, PageCount, Index);

            /* Release the lock */
            KeReleaseInStackQueuedSpinLock(&LockHandle);

            /* Check if that succeeded */
            if (Index != -1)
            {
                /* Stop looping */
                break;
            }
        }

        /* Expand the pool */
        Status = ExpandPool(BasePoolType, Index);
        if (!NT_SUCCESS(Status))
        {
            return NULL;
        }

        /* Start over */
    }

    /* Set the bit in the end-of-allocation bitmap */
    RtlSetBit(&EndOfAllocationBitmap[PoolType], Index + PageCount - 1);

    /* Update the hint index */
    PoolHintIndex[BasePoolType] = Index + PageCount;

#ifndef _WIN64
    /* On 32 bit systems we need to find the expansion base address */
    if (Index >= InitialPoolSizeInPages[BasePoolType])
    {
        /* Calculate the expansion index */
        ULONG ExpansionIndex = (Index - InitialPoolSizeInPages[BasePoolType]) /
            LARGE_PAGE_SIZE;

        /* Get the base address of the pool expansion */
        BaseAddress = PoolExpansionArray[BasePoolType][ExpansionIndex];
        NT_ASSERT(BaseAddress != NULL);
    }
#endif

    if (PoolType == PagedPool)
    {
        /* We need to map the pages */
        ULONG Protect = MM_READWRITE | MM_GLOBAL | MM_MAPPED;
        ULONG_PTR StartingVpn;

        StartingVpn = AddressToVpn(BaseAddress) + Index;
        Status = CreateMapping(StartingVpn, PageCount, Protect, NULL, NULL);
        if (!NT_SUCCESS(Status))
        {
            /// \todo handle failure
            ASSERT(FALSE);
        }
    }

    /* Return the address of the page */
    return AddToPointer(BaseAddress, Index * PAGE_SIZE);
}

ULONG
NTAPI
MiFreePoolPages (
    IN PVOID BaseAddress)
{
    ULONG_PTR StartingVpn;
    ULONG StartIndex, EndIndex, NumberOfPages;
    KLOCK_QUEUE_HANDLE LockHandle;
    POOL_TYPE PoolType;

    /* First determine the pool type */
    PoolType = MmDeterminePoolType(BaseAddress);

    if (PoolType == NonPagedPool)
        StartingVpn = AddressToVpn(MmNonPagedPoolStart);
    else
        StartingVpn = AddressToVpn(MmPagedPoolStart);

    /* Calculate the start index */
    StartIndex = static_cast<ULONG>(AddressToVpn(BaseAddress) - StartingVpn);

    /* Search for the next set bit in the end-of-allocation bitmap */
    EndIndex = RtlFindSetBits(&EndOfAllocationBitmap[PoolType], 1, StartIndex);

    /* Calculate the number of pages we have */
    NumberOfPages = EndIndex - StartIndex + 1;

    // if paged pool
        // decommit the page

    /* Acquire the lock */
    KeAcquireInStackQueuedSpinLock(&PoolPageSpinlock[PoolType], &LockHandle);

    /* Clear the end-of-allocation bit */
    RtlClearBit(&EndOfAllocationBitmap[PoolType], EndIndex);

    /* Clear the allocation bits */
    RtlClearBits(&EndOfAllocationBitmap[PoolType], StartIndex, NumberOfPages);

    /* Release the lock */
    KeReleaseInStackQueuedSpinLock(&LockHandle);

    return NumberOfPages;
}

BOOLEAN
NTAPI
MmUseSpecialPool (
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag)
{
    UNIMPLEMENTED;
    return 0;
}

BOOLEAN
NTAPI
MmIsSpecialPoolAddress (
    IN PVOID P)
{
    UNIMPLEMENTED;
    return 0;
}

PVOID
NTAPI
MmAllocateSpecialPool (
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag,
    IN POOL_TYPE PoolType,
    IN ULONG SpecialType)
{
    UNIMPLEMENTED;
    return NULL;
}

VOID
NTAPI
MmFreeSpecialPool (
    IN PVOID P)
{
    UNIMPLEMENTED;
}



}; // extern "C"
}; // namespace Mm
