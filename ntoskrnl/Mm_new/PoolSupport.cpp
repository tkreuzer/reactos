
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

extern "C" ULONG_PTR MmNumberOfPhysicalPages;
extern "C" ULONG_PTR MmSizeOfNonPagedPoolInBytes;
extern "C" ULONG_PTR MmMaximumNonPagedPoolInBytes;
extern "C" PVOID MmNonPagedPoolStart;
extern "C" PVOID MmPfnDatabase;

KERNEL_VAD NonPagedPoolVad;
KERNEL_VAD PagedPoolVad;
RTL_BITMAP NonPagedPoolBitmap;
RTL_BITMAP PagedPoolBitmap;
ULONG NonPagedPoolHintIndex;
ULONG PagedPoolHintIndex;

/*!
 * MmSizeOfNonPagedPoolInBytes, MmMaximumNonPagedPoolInBytes,
 * MmSizeOfPagedPoolInBytes
*/
static
VOID
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

}

VOID
InitializePoolSupport (
    VOID)
{
    ULONG Protect = 2; // MM_READ | MM_WRITE | MM_GLOBAL |
    NTSTATUS Status;
    ULONG_PTR NumberOfPages;
    ULONG_PTR BitmapSize, StartingVpn, EndingVpn;
    PULONG BitmapBuffer;

__debugbreak();

    /* Calculate pool sizes */
    CalculatePoolDimensions();

    /* Initialize the static pool VAD objects */
    NonPagedPoolVad.Initialize();
    PagedPoolVad.Initialize();

    /* Calculate the range of the non-paged pool */
    StartingVpn = AddressToVpn(MmNonPagedPoolStart);
    NumberOfPages = MmMaximumNonPagedPoolInBytes / PAGE_SIZE;

    /* Reserve the address space for the whole non-paged pool */
    Status = g_KernelVadTable.InsertVadObjectAtVpn(NonPagedPoolVad.GetVadObject(),
                                                   StartingVpn,
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Commit large pages for the initial non-paged pool */
    Protect = 2; // MM_READ | MM_WRITE | MM_GLOBAL | MM_NONPAGED | MM_LARGEPAGE
    EndingVpn = StartingVpn + (MmSizeOfNonPagedPoolInBytes / PAGE_SIZE) - 1;
    NonPagedPoolVad.CommitPages(StartingVpn, EndingVpn, Protect);

    /* Initialize the non-paged pool bitmap */
    BitmapBuffer = static_cast<PULONG>(MmNonPagedPoolStart);
    RtlInitializeBitMap(&NonPagedPoolBitmap, BitmapBuffer, (ULONG)NumberOfPages);

    BitmapSize = ((NumberOfPages + 31) / 32) * sizeof(ULONG);
    RtlSetBits(&NonPagedPoolBitmap, 0, (ULONG)BYTES_TO_PAGES(BitmapSize));

    // calculate pool addresses
    // commit pages for pool bitmap
    // initialize pool page bitmap
    // initialize pool descriptors

    /* Initialize the nonpaged pool */
    InitializePool(NonPagedPool, 0);
}


extern "C" {

POOL_TYPE
NTAPI
MmDeterminePoolType (
    IN PVOID VirtualAddress)
{
    UNIMPLEMENTED;
    return PagedPool;
}


PVOID
NTAPI
MiAllocatePoolPages (
    IN POOL_TYPE PoolType,
    IN SIZE_T SizeInBytes)
{
    PRTL_BITMAP Bitmap;
    ULONG PageCount, Index;
    PULONG HintIndex;

    if (PoolType == NonPagedPool)
    {
        Bitmap = &NonPagedPoolBitmap;
        HintIndex = &NonPagedPoolHintIndex;
    }
    else
    {
        Bitmap = &PagedPoolBitmap;
        HintIndex = &PagedPoolHintIndex;
    }

    PageCount = static_cast<ULONG>(BYTES_TO_PAGES(SizeInBytes));

    Index = RtlFindClearBitsAndSet(Bitmap, PageCount, *HintIndex);
    if (Index == -1)
    {
        return NULL;
    }

    *HintIndex = Index + PageCount;

    //FirstExpansionIndex = BYTES_TO_PAGES(MmSizeOfNonPagedPoolInBytes);


    /* Check if the page is already mapped */
    //if ((PoolType != NonPagedPool) || (Index >= FirstExpandionIndex))
    {
    }

    return NULL;
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
