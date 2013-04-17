
#include "ntosbase.h"
#include "KernelVad.hpp"
#include "VadTable.hpp"
#include "AddressSpace.hpp"
#include "amd64/MmConstants.hpp"

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

    MmSizeOfNonPagedPoolInBytes = PointerDiff(EndAddress, MmNonPagedPoolStart);

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
    _In_ SIZE_T MaximumSize)
{
    ULONG Protect = 2; // MM_READ | MM_WRITE | MM_GLOBAL |
    NTSTATUS Status;
    ULONG_PTR NumberOfPages, MaximumNumberOfPages, ReserveSizeInPages;
    ULONG_PTR AllocatedSize, StartingVpn, EndingVpn;
    PULONG BitmapBuffer;

    NT_ASSERT((PoolType == NonPagedPool) || (PoolType == PagedPool));

__debugbreak();

    /* Initialize the static pool VAD object */
    PoolVad[PoolType].Initialize();

    /* Calculate the range of the non-paged pool */
    StartingVpn = AddressToVpn(PoolStart);
    NumberOfPages = InitialSize / PAGE_SIZE;
    MaximumNumberOfPages = MaximumSize / PAGE_SIZE;

#ifdef _WIN64
    /* On 64 bit systems we reserve the maximum pool size */
    ReserveSizeInPages = MaximumNumberOfPages;
#else
    /* On 32 bit systems we only reserve the actual pool size */
    ReserveSizeInPages = NumberOfPages;
#endif

    /* Reserve the address space for the pool */
    Status = g_KernelVadTable.InsertVadObjectAtVpn(PoolVad[PoolType].GetVadObject(),
                                                   StartingVpn,
                                                   ReserveSizeInPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Commit large pages for the initial pool */
    Protect = 2; // MM_READ | MM_WRITE | MM_GLOBAL | MM_NONPAGED | MM_LARGEPAGE
    EndingVpn = StartingVpn + NumberOfPages - 1;
    PoolVad[PoolType].CommitPages(StartingVpn, EndingVpn, Protect);

    /* Initialize the pool bitmap */
    BitmapBuffer = static_cast<PULONG>(PoolStart);
    RtlInitializeBitMap(&PoolBitmap[PoolType], BitmapBuffer, (ULONG)MaximumNumberOfPages);

    /* The bitmap is already allocated pool */
    AllocatedSize = ((MaximumNumberOfPages + 31) / 32) * sizeof(ULONG);

#ifndef _WIN64
    /* On 32 bit systems, we add an array of expansion pointers */
    PoolExpansionArray[NonPagedPool] = BitmapBuffer + AllocatedSize;
    NonPagedPoolExpansionCount =
        (MaximumNumberOfPages - NumberOfPages + LARGE_PAGE_SIZE - 1) / LARGE_PAGE_SIZE;

    /* Add the expansion array to the allocated size */
    AllocatedSize += NonPagedPoolExpansionCount * sizeof(PVOID);
#endif

    RtlSetBits(&PoolBitmap[PoolType], 0, (ULONG)BYTES_TO_PAGES(AllocatedSize));

    /* Initialize the rest of the pool */
    InitializePool(NonPagedPool, 0);
}

VOID
INIT_FUNCTION
InitializePoolSupport (
    VOID)
{
    /* Calculate pool sizes */
    CalculatePoolDimensions();

    InitializePoolSupportSingle(NonPagedPool,
                                MmNonPagedPoolStart,
                                MmSizeOfNonPagedPoolInBytes,
                                MmMaximumNonPagedPoolInBytes);


}

NTSTATUS
ExpandPool (
    _In_ ULONG BasePoolType,
    _In_ ULONG Index)
{
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
    Index = RtlFindClearBits(Bitmap, PageCount, PoolHintIndex[BasePoolType]);
    if (Index == -1)
    {
        /* There is nothing free */
        return NULL;
    }

    /* Acquire the lock */
    KeAcquireInStackQueuedSpinLock(&PoolPageSpinlock[BasePoolType],
                                   &LockHandle);

    /* Set the bits */
    Index = RtlFindClearBitsAndSet(Bitmap, PageCount, Index);

    /* Release the lock */
    KeReleaseInStackQueuedSpinLock(&LockHandle);

    /* Check for failure */
    if (Index == -1)
    {
        /* There is nothing free */
        return NULL;
    }

    /* Check if the index is larger than the current pool size */
    if ((Index * PAGE_SIZE) > PoolSizeInBytes)
    {
        /* Expand the pool */
        Status = ExpandPool(BasePoolType, Index);
        if (!NT_SUCCESS(Status))
        {
            /* Acquire the lock */
            KeAcquireInStackQueuedSpinLock(&PoolPageSpinlock[BasePoolType],
                                           &LockHandle);

            /* Clear the bits again */
            RtlClearBits(Bitmap, Index, PageCount);

            /* Release the lock */
            KeReleaseInStackQueuedSpinLock(&LockHandle);

            return NULL;
        }
    }

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

    /* Return the address of the page */
    return AddToPointer(BaseAddress, Index * PAGE_SIZE);
}

ULONG
NTAPI
MiFreePoolPages (
    IN PVOID StartingAddress)
{
    UNIMPLEMENTED;
    return 0;
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
