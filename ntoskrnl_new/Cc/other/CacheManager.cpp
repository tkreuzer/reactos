
#include "CacheManager.hpp"

namespace Cc {

CACHE_MANAGER g_CacheManager;

typedef struct _VACB_ARRAY
{
    ULONG VacbArrayIndex;
    ULONG MappingCount;
    ULONG HighestMappedIndex;
    ULONG Reserved;
    VACB Vacbs[];
} VACB_ARRAY, *PVACB_ARRAY;

VOID
CACHE_MANAGER::Initialize (
    VOID)
{
    ULONG i;

    InitializeListHead(&m_VacbFreeList);

    /* Allocate a VACB array */

    /* Loop all VACBs */
    for (i = 0; i < NUMBER_VACBS_PER_ARRAY; i++)
    {
        /* Insert the VACB into the free list */
        InsertTailList(&m_VacbFreeList, &VacbArray->Vacbs[i].Link);
    }


}

inline
KIRQL
CACHE_MANAGER::AcquireVacbListLock (
    VOID)
{
    return KeAcquireInstackQueuedSpinLock(LockQueueVacbLock);
}

inline
VOID
CACHE_MANAGER::ReleaseVacbListLock (
    KIRQL OldIrql)
{
    KeReleaseInStackQueuedSpinLock(LockQueueVacbLock, OldIrql);
}

PVACB
CACHE_MANAGER::AllocateVacb (
    VOID)
{
    KIRQL OldIrql;
    PVACB Vacb;

    /* Acquire VACB lock */
    OldIrql = AcquireVacbListLock();

    /* Remove a VACB from the free list */
    Vacb = RemoveHeadList(&m_VacbFreeList);
    if (Vacb == NULL)
    {
        UNIMPLEMENTED;
        NT_ASSERT(FALSE);
    }

    /* Insert the VACB into the In-use-list */
    InsertHeadList(&m_VacbInUseList, &Vacb->Link);

    /* Release VACB lock */
    ReleaseVacbListLock(OldIrql);

    return Vacb;
}



}; // namespace Cc

