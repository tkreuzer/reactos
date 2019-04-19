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
    KLOCK_QUEUE_HANDLE LockHandle, *LockHandles;
    ULONG NumberPageColors, Index;
    PFN_NUMBER BasePage;

    /// \todo FIXME NUMA nodes!
    NumberPageColors = KeGetCurrentPrcb()->SecondaryColorMask + 1;

#if 0
    LockHandles = static_cast<PKLOCK_QUEUE_HANDLE>(
                  ExAllocatePoolWithTag(NonPagedPool,
                                        2 * NumberPageColors * sizeof(*LockHandles),
                                        TAG_MM));
    if (LockHandles == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }
#else
    KLOCK_QUEUE_HANDLE LockHandles[2 * NumberPageColors];
#endif

    // acquire the global lock
    KeAcquireInStackQueuedSpinLock(&m_ContiguousMemoryLock, &LockHandle);

    // lock the lists (free and zeroed for all page colors)
    for (ULONG i = 0; i < NumberPageColors; i++)
    {
        m_FreeLists[i].AcquireSpinLock(&LockHandles[i * 2]);
        m_ZeroedLists[i].AcquireSpinLock(&LockHandles[i * 2 + 1]);
    }

    for (ULONG i = 0; i < m_PhysicalMemoryDescriptor->NumberOfRuns; i++)
    {
        ULONG HintIndex = 0;

        // find free bits in the physical memory bitmap for this run
        /// \todo FIXME: currently we do sparse mapping of the bitmap.
        /// We can either map it fully, possibly wasting some memory
        /// or we use multiple bitmaps (one per run) and have each
        /// point to a ULONG(64) aligned range in the buffer.
        Index = RtlFindSetBitsAndClear(m_PhysicalMemoryBitmap,
                                       NumberOfPages,
                                       HintIndex);
        if (Index != 0xFFFFFFFF)
        {
            BasePage = m_PhysicalMemoryDescriptor->Run[i].BasePage + Index;
            break;
        }
    }


    // unlock the lists
    for (ULONG i = 0; i < NumberPageColors; i++)
    {
        m_FreeLists[i].ReleaseSpinLock(&LockHandles[i * 2]);
        m_ZeroedLists[i].ReleaseSpinLock(&LockHandles[i * 2 + 1]);
    }

    KeReleaseInStackQueuedSpinLock(&LockHandle);

    return 0;
}

