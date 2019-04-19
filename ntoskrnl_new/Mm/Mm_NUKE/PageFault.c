
#include <ntoskrnl.h>
#include "Mm_internal.h"

/* Private types **************************************************************/

typedef struct _MI_TRANSITION_WAITBLOCK
{
    struct _MI_TRANSITION_WAITBLOCK *Next;
    KEVENT Event;
} MI_TRANSITION_WAITBLOCK, *PMI_TRANSITION_WAITBLOCK;

#define KiTrapFrameInterruptsOn(TrapFrame) 1
    // ((TrapFrame)->Eflags & EFLAGS_IF)

#define __endtry
#define MiDereferencePage(page)

static
NTSTATUS
MiPageFaultHandler(
    PVOID FaultAddress,
    struct _KTRAP_FRAME *TrapFrame,
    volatile PFN_NUMBER *CleanupPage)
{
    MXPTE TransitionPte, PteValue, PrevPteValue, NewPteValue = {0};
    PMXPTE PtePointer = MxAddressToPte(FaultAddress);
    PMXPDE PdePointer = MxAddressToPde(FaultAddress);
#if (_MI_PAGING_LEVELS >= 3)
    PMXPDE PpePointer = MxAddressToPpe(FaultAddress);
#endif
#if (_MI_PAGING_LEVELS == 4)
    PMXPDE PxePointer = MxAddressToPxe(FaultAddress);
#endif
    PFN_NUMBER PageFrameNumber;
    NTSTATUS Status;
    ASSERT(*CleanupPage == 0);

#if (_MI_PAGING_LEVELS == 4)
    /* Check if the PXE is valid */
    if (!PxePointer->Hard.Valid)
    {
        /* Recursively make the PDPT resident */
        Status = MiPageFaultHandler(PpePointer, TrapFrame, CleanupPage);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }
#endif

#if (_MI_PAGING_LEVELS >= 3)
    /* Check if the PPE is valid */
    if (!PpePointer->Hard.Valid)
    {
        /* Recursively make the PD resident */
        Status = MiPageFaultHandler(PdePointer, TrapFrame, CleanupPage);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }
#endif

    /* Check if the PDE is valid */
    if (!PdePointer->Hard.Valid)
    {
        /* Recursively make the PT resident */
        Status = MiPageFaultHandler(PtePointer, TrapFrame, CleanupPage);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }

    /* Read the PTE */
    PteValue = *PtePointer;

    /* Check if the PTE is already valid */
    if (PteValue.Hard.Valid)
    {
        BOOLEAN WriteOperation = 0; // FIXME
        PVOID InstructionPointer = 0; // FIXME

        /* Check the page protection */
        if ((WriteOperation && !PteValue.Hard.Write) ||
            ((InstructionPointer == FaultAddress) && PteValue.Hard.NoExecute))
        {
            return STATUS_ACCESS_VIOLATION;
        }

        /* Page must have been paged in by someone else already */
        return STATUS_SUCCESS;
    }

    /* Check if this is a VAD based PTE */
    if (PteValue.Soft.VadBased)
    {
        PMI_TRANSITION_WAITBLOCK WaitBlock;

        /* Create a transition PTE */
        MXPTE_CreateTransitionPte(&TransitionPte, NULL);

        while (TRUE)
        {
            /* Try to atomically exchange the PTE */
            PrevPteValue = MxInterlockedCompareExchangePte(PtePointer,
                                                           TransitionPte,
                                                           PteValue);

            /* Bail out, if that succeeded */
            if (PrevPteValue.Long == PteValue.Long) break;

            /* Restart with the value we got */
            PteValue = PrevPteValue;

            /* Check if it's not a VAD based PTE anymore */
            if (!PteValue.Soft.VadBased)
            {
                /* Check if it is a transition PTE now */
                if (PteValue.Soft.Transition)
                {
                    /* Continue with the transition PTE path */
                    goto TransitionFault;
                }

                /* It's not, whatever happened, assume it's fixed */
                return STATUS_SUCCESS;
            }
        }

        /*  */
        // Vad = ...
        // Vad->VadType->
        Status = 0;// Callback()
        __debugbreak();

        /* Atomically exchange the PTE */
        PteValue = MxInterlockedExchangePte(PtePointer, NewPteValue);

        /* Loop all enqueued wait blocks */
        WaitBlock = MXPTE_GetTransitionQueue(&PteValue);
        while (WaitBlock)
        {
            /* Get the address of the event and already go to the next wait
               block, because it will be invalid after we set the event */
            PKEVENT Event = &WaitBlock->Event;
            WaitBlock = WaitBlock->Next;
            KeMemoryBarrierWithoutFence();

            /* Signal the event */
            KeSetEvent(Event, 0, FALSE);
        }

        return Status;
    }

    /* Check if this is a transition PTE */
    if (PteValue.Soft.Transition)
    {
        MI_TRANSITION_WAITBLOCK WaitBlock;
TransitionFault:

        /* Initialize the event in the wait block */
        KeInitializeEvent(&WaitBlock.Event, NotificationEvent, FALSE);

        /* Create a new transition PTE */
        MXPTE_CreateTransitionPte(&TransitionPte, &WaitBlock);

        do
        {
            /* Set the next pointer to the current list head */
            WaitBlock.Next = MXPTE_GetTransitionQueue(&PteValue);

            /* Try to atomically exchange the PTE (push the wait block) */
            PrevPteValue = MxInterlockedCompareExchangePte(PtePointer,
                                                           TransitionPte,
                                                           PteValue);

            /* Check if that succeeded */
            if (PteValue.Long == PteValue.Long)
            {
                /* Wait for the event to be signaled */
                KeWaitForSingleObject(&WaitBlock.Event,
                                      PageIn,
                                      KeGetPreviousMode(),
                                      FALSE, // Alterable?
                                      NULL);
                break;
            }

            /* Restart with the value we got */
            PteValue = PrevPteValue;

        /* Retry as long as we have a transition PTE */
        } while (PteValue.Soft.Transition);

        /* We're done */
        return STATUS_PAGE_FAULT_TRANSITION;
    }
    else
    {
        /* Allocate a page (zero or dirty) */
        PageFrameNumber = MiAllocatePage(!PteValue.Demand.Dirty);
        *CleanupPage = PageFrameNumber;
        ASSERT(PageFrameNumber);

        NewPteValue = MxDemandPteToValidPte(PteValue, PageFrameNumber);

        /* Try to atomically exchange the PTE */
        PrevPteValue = MxInterlockedCompareExchangePte(PtePointer,
                                                       NewPteValue,
                                                       PteValue);

        /* Check if that succeeded */
        if (PrevPteValue.Long == PteValue.Long)
        {
            /* Reset the page frame number, so we don't do cleanup */
            *CleanupPage = 0;

            // FIXME: increment ValidPteCount
        }

        /* This is a demand-(zero-)fault */
        return STATUS_PAGE_FAULT_DEMAND_ZERO;
    }

}

NTSTATUS
NTAPI
MmPageFaultHandler(
    PVOID FaultAddress,
    struct _KTRAP_FRAME *TrapFrame)
{
    PFN_NUMBER PageFrameNumber = 0;
    NTSTATUS Status;

    /* Check if the IRQL is ok */
    if (KeGetCurrentIrql() > APC_LEVEL)
    {
        /* Bugcheck the system */
        KeBugCheck(DRIVER_IRQL_NOT_LESS_OR_EQUAL);
    }

    /* Check if the fault happened with interrupts off */
    if (!KiTrapFrameInterruptsOn(TrapFrame))
    {
        /* Bugcheck the system */
        KeBugCheck(PAGE_FAULT_WITH_INTERRUPTS_OFF);
    }

    /* Check for privilege violation */
    if ((FaultAddress > MmHighestUserAddress) &&
        (KeGetPreviousMode() != KernelMode)) // use TrapFrame->PreviousMode
    {
        /* This is an access violation */
        return STATUS_ACCESS_VIOLATION;
    }

    /* Protect the operation with SEH to avoid locking */
    __try
    {
        /* Call the internal handler */
        Status = MiPageFaultHandler(FaultAddress, TrapFrame, &PageFrameNumber);
    }
    __except(1)
    {
        /* An unhandled exception occurred while accessing a page table or a
           VAD. This means, a virtual address has been decommitted in the
           meanwhile. In that case, we fail! */
        Status = GetExceptionCode();
    }
    __endtry

    /* Check if we have a page that was not committed */
    if (PageFrameNumber)
    {
        /* The new PTE was already created, but it was not committed.
           Either the PTE changed in the meanwhile or we got an exception.
           In both cases we need to release the page. */
        MiDereferencePage(PageFrameNumber);
        return STATUS_SUCCESS;
    }

#if PDES_DONT_MAP_PTS
    if (NT_SUCCESS(Status))
    {
        /* Check if this was a PTE address */
        if (MiIsPageTableAddress(FaultAddress))
        {
            /* The page table has been paged in, now make the PDE valid */
            PdePointer = MiAddressToPde(MiPteToAddress(FaultAddress));
            MiMakePdeValid(PdePointer, NewPteValue.Hard.PageFrameNumber);
        }
    }
#endif

    return Status;
}


