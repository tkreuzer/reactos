/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            ntoskrnl/mm/i386/page.c
 * PURPOSE:         Low level memory managment manipulation
 *
 * PROGRAMMERS:     David Welch (welch@cwcom.net)
 */

/* INCLUDES ***************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

#include <mm/ARM3/miarm.h>

#define ADDR_TO_PDE_OFFSET MiAddressToPdeOffset
#define ADDR_TO_PAGE_TABLE(v)  (((ULONG)(v)) / (1024 * PAGE_SIZE))

/* GLOBALS *****************************************************************/

#define PA_BIT_PRESENT   (0)
#define PA_BIT_READWRITE (1)
#define PA_BIT_USER      (2)
#define PA_BIT_WT        (3)
#define PA_BIT_CD        (4)
#define PA_BIT_ACCESSED  (5)
#define PA_BIT_DIRTY     (6)
#define PA_BIT_GLOBAL    (8)

#define PA_PRESENT   (1 << PA_BIT_PRESENT)
#define PA_READWRITE (1 << PA_BIT_READWRITE)
#define PA_USER      (1 << PA_BIT_USER)
#define PA_DIRTY     (1 << PA_BIT_DIRTY)
#define PA_WT        (1 << PA_BIT_WT)
#define PA_CD        (1 << PA_BIT_CD)
#define PA_ACCESSED  (1 << PA_BIT_ACCESSED)
#define PA_GLOBAL    (1 << PA_BIT_GLOBAL)

#define IS_HYPERSPACE(v)    (((ULONG)(v) >= HYPER_SPACE && (ULONG)(v) <= HYPER_SPACE_END))

#define PTE_TO_PFN(X)  ((X) >> PAGE_SHIFT)
#define PFN_TO_PTE(X)  ((X) << PAGE_SHIFT)

#define MiPteToAddress(x) \
    ((PVOID)(((ULONG)(x) - PAGETABLE_MAP) << 10))

typedef struct _MMPTE_LISTHEAD
{
    MMPTE_LIST *Base;
    MMPTE_LIST *FirstEntry;
} MMPTE_LISTHEAD, *PMMPTE_LISTHEAD;

MMPTE_LIST *MmHyperspaceFreeListHead;

const
ULONG
MmProtectToPteMask[32] =
{
    //
    // These are the base MM_ protection flags
    //
    0,
    PTE_READONLY            | PTE_ENABLE_CACHE,
    PTE_EXECUTE             | PTE_ENABLE_CACHE,
    PTE_EXECUTE_READ        | PTE_ENABLE_CACHE,
    PTE_READWRITE           | PTE_ENABLE_CACHE,
    PTE_WRITECOPY           | PTE_ENABLE_CACHE,
    PTE_EXECUTE_READWRITE   | PTE_ENABLE_CACHE,
    PTE_EXECUTE_WRITECOPY   | PTE_ENABLE_CACHE,
    //
    // These OR in the MM_NOCACHE flag
    //
    0,
    PTE_READONLY            | PTE_DISABLE_CACHE,
    PTE_EXECUTE             | PTE_DISABLE_CACHE,
    PTE_EXECUTE_READ        | PTE_DISABLE_CACHE,
    PTE_READWRITE           | PTE_DISABLE_CACHE,
    PTE_WRITECOPY           | PTE_DISABLE_CACHE,
    PTE_EXECUTE_READWRITE   | PTE_DISABLE_CACHE,
    PTE_EXECUTE_WRITECOPY   | PTE_DISABLE_CACHE,
    //
    // These OR in the MM_DECOMMIT flag, which doesn't seem supported on x86/64/ARM
    //
    0,
    PTE_READONLY            | PTE_ENABLE_CACHE,
    PTE_EXECUTE             | PTE_ENABLE_CACHE,
    PTE_EXECUTE_READ        | PTE_ENABLE_CACHE,
    PTE_READWRITE           | PTE_ENABLE_CACHE,
    PTE_WRITECOPY           | PTE_ENABLE_CACHE,
    PTE_EXECUTE_READWRITE   | PTE_ENABLE_CACHE,
    PTE_EXECUTE_WRITECOPY   | PTE_ENABLE_CACHE,
    //
    // These OR in the MM_NOACCESS flag, which seems to enable WriteCombining?
    //
    0,
    PTE_READONLY            | PTE_WRITECOMBINED_CACHE,
    PTE_EXECUTE             | PTE_WRITECOMBINED_CACHE,
    PTE_EXECUTE_READ        | PTE_WRITECOMBINED_CACHE,
    PTE_READWRITE           | PTE_WRITECOMBINED_CACHE,
    PTE_WRITECOPY           | PTE_WRITECOMBINED_CACHE,
    PTE_EXECUTE_READWRITE   | PTE_WRITECOMBINED_CACHE,
    PTE_EXECUTE_WRITECOPY   | PTE_WRITECOMBINED_CACHE,
};

const
ULONG MmProtectToValue[32] =
{
    PAGE_NOACCESS,
    PAGE_READONLY,
    PAGE_EXECUTE,
    PAGE_EXECUTE_READ,
    PAGE_READWRITE,
    PAGE_WRITECOPY,
    PAGE_EXECUTE_READWRITE,
    PAGE_EXECUTE_WRITECOPY,
    PAGE_NOACCESS,
    PAGE_NOCACHE | PAGE_READONLY,
    PAGE_NOCACHE | PAGE_EXECUTE,
    PAGE_NOCACHE | PAGE_EXECUTE_READ,
    PAGE_NOCACHE | PAGE_READWRITE,
    PAGE_NOCACHE | PAGE_WRITECOPY,
    PAGE_NOCACHE | PAGE_EXECUTE_READWRITE,
    PAGE_NOCACHE | PAGE_EXECUTE_WRITECOPY,
    PAGE_NOACCESS,
    PAGE_GUARD | PAGE_READONLY,
    PAGE_GUARD | PAGE_EXECUTE,
    PAGE_GUARD | PAGE_EXECUTE_READ,
    PAGE_GUARD | PAGE_READWRITE,
    PAGE_GUARD | PAGE_WRITECOPY,
    PAGE_GUARD | PAGE_EXECUTE_READWRITE,
    PAGE_GUARD | PAGE_EXECUTE_WRITECOPY,
    PAGE_NOACCESS,
    PAGE_WRITECOMBINE | PAGE_READONLY,
    PAGE_WRITECOMBINE | PAGE_EXECUTE,
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ,
    PAGE_WRITECOMBINE | PAGE_READWRITE,
    PAGE_WRITECOMBINE | PAGE_WRITECOPY,
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READWRITE,
    PAGE_WRITECOMBINE | PAGE_EXECUTE_WRITECOPY
};

/* FUNCTIONS ***************************************************************/

static BOOLEAN MmUnmapPageTable(PULONG Pt, KIRQL OldIrql);
BOOLEAN HasDebug = 0;
#define DPRINT0 if(HasDebug) DbgPrint

#define USE_FREELIST 1

#if USE_FREELIST

BOOLEAN HyperspaceInitialized = 0;

ULONG BackTrace[30];
VOID NTAPI KeRosDumpStackFrames(PULONG, ULONG);

#define VALIDATE if (!MiValidateFreeList() && HasDebug) ASSERT(FALSE)
static
BOOLEAN
MiValidateFreeList()
{
    PULONG p;
    INT i;

if (HyperspaceInitialized)
{
    p = (PULONG)MiAddressToPte(HYPERSPACE);
    for (i = 0; i < 1024; i++)
    {
        if (p[i] == 0)
        {
            DPRINT1("Found 0 entry in index %d\n", i);
            return FALSE;
        }
    }
    return TRUE;
}
return TRUE;
}

#if 0
static
PMMPTE
MiInterlockedPopPteListEntry(MMPTE_LIST **ListHead)
{
    MMPTE_LIST *FirstEntry, *NextEntry, *PrevEntry;

    do
    {
        FirstEntry = *ListHead;
        if (!FirstEntry)
        {
            return NULL;
        }
        NextEntry = FirstEntry->NextEntry ?
            (PVOID)((ULONG_PTR)FirstEntry + (INT)FirstEntry->NextEntry) : NULL;

        PrevEntry = InterlockedCompareExchangePointer((PVOID*)ListHead,
                                                      (PVOID)NextEntry,
                                                      (PVOID)FirstEntry);
    }
    while (PrevEntry != FirstEntry);
//DPRINT0("MiInterlockedPopPteListEntry returns %p, NextEntry = %p\n", FirstEntry, NextEntry);
if (!MiValidateFreeList() && HasDebug)
{
    DPRINT1("we have a problem !\n");
    KeRosDumpStackFrames(BackTrace, 20);
    ASSERT(FALSE);
}

    return (PMMPTE)FirstEntry;
}
#else
static
PMMPTE
MiInterlockedPopPteListEntry(MMPTE_LIST *ListHead)
{
    MMPTE_LIST *FirstEntry, *NextEntry, *PrevEntry;

    do
    {
        FirstEntry = ListHead->NextEntry ?
            (PVOID)((ULONG_PTR)ListHead + (INT)ListHead->NextEntry) : NULL;
        if (!FirstEntry)
        {
            return NULL;
        }
        NextEntry = FirstEntry->NextEntry ?
            (PVOID)((ULONG_PTR)FirstEntry + (INT)FirstEntry->NextEntry) : NULL;

        PrevEntry = InterlockedCompareExchangePointer((PVOID*)ListHead,
                                                      (PVOID)*NextEntry,
                                                      (PVOID)*FirstEntry);
    }
    while (PrevEntry != *FirstEntry);

//DPRINT0("MiInterlockedPopPteListEntry returns %p, NextEntry = %p\n", FirstEntry, NextEntry);
if (!MiValidateFreeList() && HasDebug)
{
    DPRINT1("we have a problem !\n");
    KeRosDumpStackFrames(BackTrace, 20);
    ASSERT(FALSE);
}

    return (PMMPTE)FirstEntry;
}
#endif

static
void
MiInterlockedPushPteListEntry(MMPTE_LIST **ListHead, MMPTE *Entry)
{
    MMPTE_LIST *FirstEntry, *PrevEntry;
//VALIDATE;
    do
    {
        FirstEntry = *ListHead;
        Entry->u.List.NextEntry = FirstEntry ? 
            (LONG_PTR)FirstEntry - (LONG_PTR)Entry : 0;
        PrevEntry = InterlockedCompareExchangePointer((PVOID*)ListHead,
                                                      (PVOID)Entry,
                                                      (PVOID)FirstEntry);
    }
    while (PrevEntry != FirstEntry);
    RtlCaptureStackBackTrace(0, 20, (PVOID*)BackTrace, NULL);
//DPRINT0("MiInterlockedPushPteListEntry pushed %p\n", Entry);
}
#endif

VOID
MmInitHyperSpaceFreeList(MMPTE *Pte)
{
    INT i;

//DPRINT1("Enter MmInitHyperSpaceFreeList\n");

//    Pte = MiAddressToPte(HYPERSPACE);
    MmHyperspaceFreeListHead = &Pte->u.List;
    for (i = 0; i < 1024; i++)
    {
        Pte[i].u.Long = 0;
        Pte[i].u.List.NextEntry = 4;
    }
//DPRINT1("Leave MmInitHyperSpaceFreeList\n");
    HyperspaceInitialized = 1;

}

VOID
MiFlushTlb(PULONG Pt, PVOID Address, KIRQL OldIrql)
{
    if ((Pt && MmUnmapPageTable(Pt, OldIrql)) || Address >= MmSystemRangeStart)
    {
        KeInvalidateTlbEntry(Address);
    }
}

static ULONG
ProtectToPTE(ULONG flProtect)
{
    ULONG Attributes = 0;

    if (flProtect & (PAGE_NOACCESS|PAGE_GUARD))
    {
        Attributes = 0;
    }
    else if (flProtect & PAGE_IS_WRITABLE)
    {
        Attributes = PA_PRESENT | PA_READWRITE;
    }
    else if (flProtect & (PAGE_IS_READABLE | PAGE_IS_EXECUTABLE))
    {
        Attributes = PA_PRESENT;
    }
    else
    {
        DPRINT1("Unknown main protection type.\n");
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    if (flProtect & PAGE_SYSTEM)
    {
    }
    else
    {
        Attributes = Attributes | PA_USER;
    }
    if (flProtect & PAGE_NOCACHE)
    {
        Attributes = Attributes | PA_CD;
    }
    if (flProtect & PAGE_WRITETHROUGH)
    {
        Attributes = Attributes | PA_WT;
    }
    return(Attributes);
}

NTSTATUS
NTAPI
MiDispatchFault(IN ULONG FaultCode,
                IN PVOID Address,
                IN PMMPTE PointerPte,
                IN PMMPTE PointerProtoPte,
                IN BOOLEAN Recursive,
                IN PEPROCESS Process,
                IN PVOID TrapInformation,
                IN PVOID Vad);

NTSTATUS
NTAPI
MiFillSystemPageDirectory(IN PVOID Base,
                          IN SIZE_T NumberOfBytes);

NTSTATUS
NTAPI
Mmi386ReleaseMmInfo(PEPROCESS Process)
{
    PUSHORT LdtDescriptor;
    ULONG LdtBase;
    PULONG PageDir;
    ULONG i;
    
    DPRINT("Mmi386ReleaseMmInfo(Process %x)\n",Process);
    
    LdtDescriptor = (PUSHORT) &Process->Pcb.LdtDescriptor;
    LdtBase = LdtDescriptor[1] |
    ((LdtDescriptor[2] & 0xff) << 16) |
    ((LdtDescriptor[3] & ~0xff) << 16);
    
    DPRINT("LdtBase: %x\n", LdtBase);
    
    if (LdtBase)
    {
        ExFreePool((PVOID) LdtBase);
    }
    
    PageDir = MmCreateHyperspaceMapping(PTE_TO_PFN(Process->Pcb.DirectoryTableBase[0]));
    for (i = 0; i < ADDR_TO_PDE_OFFSET(MmSystemRangeStart); i++)
    {
        if (PageDir[i] != 0)
        {
            MiZeroPage(PTE_TO_PFN(PageDir[i]));
            MmReleasePageMemoryConsumer(MC_NPPOOL, PTE_TO_PFN(PageDir[i]));
        }
    }
    MmReleasePageMemoryConsumer(MC_NPPOOL, PTE_TO_PFN(PageDir[ADDR_TO_PDE_OFFSET(HYPERSPACE)]));
    MmDeleteHyperspaceMapping(PageDir);
    MmReleasePageMemoryConsumer(MC_NPPOOL, PTE_TO_PFN(Process->Pcb.DirectoryTableBase[0]));

    Process->Pcb.DirectoryTableBase[0] = 0;
    Process->Pcb.DirectoryTableBase[1] = 0;

    DPRINT("Finished Mmi386ReleaseMmInfo()\n");
    return(STATUS_SUCCESS);
}

NTSTATUS
NTAPI
MmInitializeHandBuiltProcess(IN PEPROCESS Process,
                             IN PULONG DirectoryTableBase)
{
    /* Share the directory base with the idle process */
    DirectoryTableBase[0] = PsGetCurrentProcess()->Pcb.DirectoryTableBase[0];
    DirectoryTableBase[1] = PsGetCurrentProcess()->Pcb.DirectoryTableBase[1];

    /* Initialize the Addresss Space */
    KeInitializeGuardedMutex(&Process->AddressCreationLock);
    Process->Vm.WorkingSetExpansionLinks.Flink = NULL;
    ASSERT(Process->VadRoot.NumberGenericTableElements == 0);
    Process->VadRoot.BalancedRoot.u1.Parent = &Process->VadRoot.BalancedRoot;

    /* The process now has an address space */
    Process->HasAddressSpace = TRUE;
    return STATUS_SUCCESS;
}

BOOLEAN
NTAPI
MmCreateProcessAddressSpace(IN ULONG MinWs,
                            IN PEPROCESS Process,
                            IN PULONG DirectoryTableBase)
{
    NTSTATUS Status;
    ULONG i, j;
    PFN_TYPE Pfn[2];
    PULONG PageDirectory, Hyperspace;
    
    DPRINT("MmCopyMmInfo(Src %x, Dest %x)\n", MinWs, Process);
    
    for (i = 0; i < 2; i++)
    {
        Status = MmRequestPageMemoryConsumer(MC_NPPOOL, FALSE, &Pfn[i]);
        if (!NT_SUCCESS(Status))
        {
            for (j = 0; j < i; j++)
            {
                MmReleasePageMemoryConsumer(MC_NPPOOL, Pfn[j]);
            }
            
            return FALSE;
        }
    }
    
    PageDirectory = MmCreateHyperspaceMapping(Pfn[0]);
    
    memcpy(PageDirectory + ADDR_TO_PDE_OFFSET(MmSystemRangeStart),
           MmGlobalKernelPageDirectory + ADDR_TO_PDE_OFFSET(MmSystemRangeStart),
           (1024 - ADDR_TO_PDE_OFFSET(MmSystemRangeStart)) * sizeof(ULONG));
    
    DPRINT("Addr %x\n",ADDR_TO_PDE_OFFSET(PAGETABLE_MAP));
    PageDirectory[ADDR_TO_PDE_OFFSET(PAGETABLE_MAP)] = PFN_TO_PTE(Pfn[0]) | PA_PRESENT | PA_READWRITE;
    PageDirectory[ADDR_TO_PDE_OFFSET(HYPERSPACE)] = PFN_TO_PTE(Pfn[1]) | PA_PRESENT | PA_READWRITE;
    
    MmDeleteHyperspaceMapping(PageDirectory);

    Hyperspace = MmCreateHyperspaceMapping(Pfn[1]);
    MmInitHyperSpaceFreeList((MMPTE*)Hyperspace);
    MmDeleteHyperspaceMapping(Hyperspace);

    DirectoryTableBase[0] = PFN_TO_PTE(Pfn[0]);
    DirectoryTableBase[1] = 0;
    DPRINT("Finished MmCopyMmInfo(): 0x%x\n", DirectoryTableBase[0]);
    return TRUE;
}

static PULONG
MmGetPageTableForProcess(PEPROCESS Process, PVOID Address, BOOLEAN Create, PKIRQL OldIrql)
{
    PFN_NUMBER Pfn;
    PULONG Pt;
    PMMPDE PointerPde;

    if (Address < MmSystemRangeStart)
    {
        /* We should have a process for user land addresses */
        ASSERT(Process != NULL);

        if(Process != PsGetCurrentProcess())
        {
            PMMPDE PdeBase;
            ULONG PdeOffset = MiGetPdeOffset(Address);

            PdeBase = MiMapPageInHyperSpace(PsGetCurrentProcess(),
                                            PTE_TO_PFN(Process->Pcb.DirectoryTableBase[0]),
                                            OldIrql);
            if (PdeBase == NULL)
            {
                KeBugCheck(MEMORY_MANAGEMENT);
            }
            PointerPde = PdeBase + PdeOffset;
            if (PointerPde->u.Hard.Valid == 0)
            {
                KAPC_STATE ApcState;
                NTSTATUS Status;

                if (!Create)
                {
                    MiUnmapPageInHyperSpace(PsGetCurrentProcess(), PdeBase, *OldIrql);
                    return NULL;
                }

                KeStackAttachProcess(&Process->Pcb, &ApcState);

                Status = MiDispatchFault(0x1,
                                     MiAddressToPte(Address),
                                     MiAddressToPde(Address),
                                     NULL,
                                     FALSE,
                                     Process,
                                     NULL,
                                     NULL);

                KeUnstackDetachProcess(&ApcState);
                if (!NT_SUCCESS(Status))
                    return NULL;
            }

            Pfn = PointerPde->u.Hard.PageFrameNumber;
            MiUnmapPageInHyperSpace(PsGetCurrentProcess(), PdeBase, *OldIrql);
            Pt = MiMapPageInHyperSpace(PsGetCurrentProcess(), Pfn, OldIrql);
            if (Pt == NULL)
            {
                KeBugCheck(MEMORY_MANAGEMENT);
            }
            return Pt + MiAddressToPteOffset(Address);
        }
        /* This is for our process */
        PointerPde = MiAddressToPde(Address);
        Pt = (PULONG)MiAddressToPte(Address);
        if (PointerPde->u.Hard.Valid == 0)
        {
            NTSTATUS Status;
            if (Create == FALSE)
            {
                return NULL;
            }
            ASSERT(PointerPde->u.Long == 0);

            MI_WRITE_INVALID_PTE(PointerPde, DemandZeroPde);
            // Tiny HACK: Parameter 1 is the architecture specific FaultCode for an access violation (i.e. page is present)
            Status = MiDispatchFault(0x1,
                                     Pt,
                                     PointerPde,
                                     NULL,
                                     FALSE,
                                     PsGetCurrentProcess(),
                                     NULL,
                                     NULL);
            DBG_UNREFERENCED_LOCAL_VARIABLE(Status);
            ASSERT(KeAreAllApcsDisabled() == TRUE);
            ASSERT(PointerPde->u.Hard.Valid == 1);
        }
        return (PULONG)MiAddressToPte(Address);
    }

    /* This is for kernel land address */
    ASSERT(Process == NULL);
    PointerPde = MiAddressToPde(Address);
    Pt = (PULONG)MiAddressToPte(Address);
    if (PointerPde->u.Hard.Valid == 0)
    {
        /* Let ARM3 synchronize the PDE */
        if(!MiSynchronizeSystemPde(PointerPde))
        {
            /* PDE (still) not valid, let ARM3 allocate one if asked */
            if(Create == FALSE)
                return NULL;
            MiFillSystemPageDirectory(Address, PAGE_SIZE);
        }
    }
    return Pt;
}

static BOOLEAN MmUnmapPageTable(PULONG Pt, KIRQL OldIrql)
{
    if (!IS_HYPERSPACE(Pt))
    {
        return TRUE;
    }

    MiUnmapPageInHyperSpace(PsGetCurrentProcess(), Pt, OldIrql);

    return FALSE;
}

static ULONG MmGetPageEntryForProcess(PEPROCESS Process, PVOID Address)
{
    ULONG Pte;
    PULONG Pt;
    KIRQL OldIrql;

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);
    if (Pt)
    {
        Pte = *Pt;
        MmUnmapPageTable(Pt, OldIrql);
        return Pte;
    }
    return 0;
}

PFN_NUMBER
NTAPI
MmGetPfnForProcess(PEPROCESS Process,
                   PVOID Address)
{
    ULONG Entry;
    Entry = MmGetPageEntryForProcess(Process, Address);
    if (!(Entry & PA_PRESENT))
    {
        return 0;
    }
    return(PTE_TO_PFN(Entry));
}

VOID
NTAPI
MmDeleteVirtualMapping(PEPROCESS Process, PVOID Address,
                       BOOLEAN* WasDirty, PPFN_NUMBER Page)
/*
 * FUNCTION: Delete a virtual mapping
 */
{
    BOOLEAN WasValid = FALSE;
    PFN_NUMBER Pfn;
    ULONG Pte;
    PULONG Pt;
    KIRQL OldIrql;

    DPRINT("MmDeleteVirtualMapping(%p, %p, %p, %p)\n",
           Process, Address, WasDirty, Page);

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);

    if (Pt == NULL)
    {
        if (WasDirty != NULL)
        {
            *WasDirty = FALSE;
        }
        if (Page != NULL)
        {
            *Page = 0;
        }
        return;
    }

    /*
     * Atomically set the entry to zero and get the old value.
     */
    Pte = InterlockedExchangePte(Pt, 0);

    /* We count a mapping as valid if it's a present page, or it's a nonzero pfn with
     * the swap bit unset, indicating a valid page protected to PAGE_NOACCESS. */
    WasValid = (Pte & PA_PRESENT) || ((Pte >> PAGE_SHIFT) && !(Pte & 0x800));
    if (WasValid)
    {
        /* Flush the TLB since we transitioned this PTE
         * from valid to invalid so any stale translations
         * are removed from the cache */
        MiFlushTlb(Pt, Address, OldIrql);

		if (Address < MmSystemRangeStart)
		{
			/* Remove PDE reference */
			Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)]--;
			ASSERT(Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)] < PTE_PER_PAGE);
		}

        Pfn = PTE_TO_PFN(Pte);
    }
    else
    {
        MmUnmapPageTable(Pt, OldIrql);
        Pfn = 0;
    }

    /*
     * Return some information to the caller
     */
    if (WasDirty != NULL)
    {
        *WasDirty = ((Pte & PA_DIRTY) && (Pte & PA_PRESENT)) ? TRUE : FALSE;
    }
    if (Page != NULL)
    {
        *Page = Pfn;
    }
}

VOID
NTAPI
MmGetPageFileMapping(PEPROCESS Process, PVOID Address,
                     SWAPENTRY* SwapEntry)
/*
 * FUNCTION: Get a page file mapping
 */
{
    ULONG Entry = MmGetPageEntryForProcess(Process, Address);
    *SwapEntry = Entry >> 1;
}

VOID
NTAPI
MmDeletePageFileMapping(PEPROCESS Process, PVOID Address,
                        SWAPENTRY* SwapEntry)
/*
 * FUNCTION: Delete a virtual mapping
 */
{
    ULONG Pte;
    PULONG Pt;
    KIRQL OldIrql;

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);

    if (Pt == NULL)
    {
        *SwapEntry = 0;
        return;
    }

    /*
     * Atomically set the entry to zero and get the old value.
     */
    Pte = InterlockedExchangePte(Pt, 0);

	if (Address < MmSystemRangeStart)
	{
		/* Remove PDE reference */
		Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)]--;
		ASSERT(Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)] < PTE_PER_PAGE);
	}

    /* We don't need to flush here because page file entries
     * are invalid translations, so the processor won't cache them */
    MmUnmapPageTable(Pt, OldIrql);

    if ((Pte & PA_PRESENT) || !(Pte & 0x800))
    {
        DPRINT1("Pte %x (want not 1 and 0x800)\n", Pte);
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    /*
     * Return some information to the caller
     */
    *SwapEntry = Pte >> 1;
}

BOOLEAN
Mmi386MakeKernelPageTableGlobal(PVOID Address)
{
    PMMPDE PointerPde = MiAddressToPde(Address);
    PMMPTE PointerPte = MiAddressToPte(Address);

    if (PointerPde->u.Hard.Valid == 0)
    {
        if(!MiSynchronizeSystemPde(PointerPde))
            return FALSE;
        return PointerPte->u.Hard.Valid != 0;
    }
    return FALSE;
}

BOOLEAN
NTAPI
MmIsDirtyPage(PEPROCESS Process, PVOID Address)
{
    return MmGetPageEntryForProcess(Process, Address) & PA_DIRTY ? TRUE : FALSE;
}

VOID
NTAPI
MmSetCleanPage(PEPROCESS Process, PVOID Address)
{
    PULONG Pt;
    ULONG Pte;
    KIRQL OldIrql;

    if (Address < MmSystemRangeStart && Process == NULL)
    {
        DPRINT1("MmSetCleanPage is called for user space without a process.\n");
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);
    if (Pt == NULL)
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    do
    {
        Pte = *Pt;
    } while (Pte != InterlockedCompareExchangePte(Pt, Pte & ~PA_DIRTY, Pte));

    if (!(Pte & PA_PRESENT))
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }
    else if (Pte & PA_DIRTY)
    {
        MiFlushTlb(Pt, Address, OldIrql);
    }
    else
    {
        MmUnmapPageTable(Pt, OldIrql);
    }
}

VOID
NTAPI
MmSetDirtyPage(PEPROCESS Process, PVOID Address)
{
    PULONG Pt;
    ULONG Pte;
    KIRQL OldIrql;

    if (Address < MmSystemRangeStart && Process == NULL)
    {
        DPRINT1("MmSetDirtyPage is called for user space without a process.\n");
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);
    if (Pt == NULL)
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    do
    {
        Pte = *Pt;
    } while (Pte != InterlockedCompareExchangePte(Pt, Pte | PA_DIRTY, Pte));

    if (!(Pte & PA_PRESENT))
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }
    else
    {
        /* The processor will never clear this bit itself, therefore
         * we do not need to flush the TLB here when setting it */
        MmUnmapPageTable(Pt, OldIrql);
    }
}

VOID
NTAPI
MmClearPageAccessedBit(PEPROCESS Process, PVOID Address)
{
    PULONG Pt;
    LONG Pte;
    KIRQL OldIrql;

    if (Address < MmSystemRangeStart && Process == NULL)
    {
        DPRINT1("MmClearPageAccessedBit is called for user space without a process.\n");
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);
    if (Pt == NULL)
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    do
    {
        Pte = *Pt;
    } while (Pte != InterlockedCompareExchangePte(Pt, Pte & ~PA_ACCESSED, Pte));

    if (!(Pte & PA_PRESENT))
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    MiFlushTlb(Pt, Address, OldIrql);
}

BOOLEAN
NTAPI
MmIsPageAccessed(PEPROCESS Process, PVOID Address)
{
    return BooleanFlagOn(MmGetPageEntryForProcess(Process, Address), PA_ACCESSED);
}

BOOLEAN
NTAPI
MmIsPagePresent(PEPROCESS Process, PVOID Address)
{
    return MmGetPageEntryForProcess(Process, Address) & PA_PRESENT;
}

BOOLEAN
NTAPI
MmIsDisabledPage(PEPROCESS Process, PVOID Address)
{
    ULONG_PTR Entry = MmGetPageEntryForProcess(Process, Address);
    return !(Entry & PA_PRESENT) && !(Entry & 0x800) && (Entry >> PAGE_SHIFT);
}

BOOLEAN
NTAPI
MmIsPageSwapEntry(PEPROCESS Process, PVOID Address)
{
    ULONG Entry;
    Entry = MmGetPageEntryForProcess(Process, Address);
    return !(Entry & PA_PRESENT) && (Entry & 0x800);
}

NTSTATUS
NTAPI
MmCreatePageFileMapping(PEPROCESS Process,
                        PVOID Address,
                        SWAPENTRY SwapEntry)
{
    PULONG Pt;
    ULONG Pte;
    KIRQL OldIrql;

    if (Process == NULL && Address < MmSystemRangeStart)
    {
        DPRINT1("No process\n");
        KeBugCheck(MEMORY_MANAGEMENT);
    }
    if (Process != NULL && Address >= MmSystemRangeStart)
    {
        DPRINT1("Setting kernel address with process context\n");
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    if (SwapEntry & (1 << 31))
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);
    if (Pt == NULL)
    {
        /* Nobody should page out an address that hasn't even been mapped */
        /* But we might place a wait entry first, requiring the page table */
        if (SwapEntry != MM_WAIT_ENTRY)
        {
            KeBugCheck(MEMORY_MANAGEMENT);
        }
        Pt = MmGetPageTableForProcess(Process, Address, TRUE, &OldIrql);
    }
    Pte = InterlockedExchangePte(Pt, SwapEntry << 1);
    if (Pte != 0)
    {
        KeBugCheckEx(MEMORY_MANAGEMENT, SwapEntry, (ULONG_PTR)Process, (ULONG_PTR)Address, 0);
    }

	if (Address < MmSystemRangeStart)
	{
		/* Add PDE reference */
		Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)]++;
		ASSERT(Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Address)] <= PTE_PER_PAGE);
	}

    /* We don't need to flush the TLB here because it
     * only caches valid translations and a zero PTE
     * is not a valid translation */
    MmUnmapPageTable(Pt, OldIrql);

    return(STATUS_SUCCESS);
}


NTSTATUS
NTAPI
MmCreateVirtualMappingUnsafe(PEPROCESS Process,
                             PVOID Address,
                             ULONG flProtect,
                             PPFN_NUMBER Pages,
                             ULONG PageCount)
{
    ULONG Attributes;
    PVOID Addr;
    ULONG i;
    ULONG oldPdeOffset, PdeOffset;
    PULONG Pt = NULL;
    ULONG Pte;
    KIRQL OldIrql;

    DPRINT("MmCreateVirtualMappingUnsafe(%p, %p, %lu, %p (%x), %lu)\n",
           Process, Address, flProtect, Pages, *Pages, PageCount);

    ASSERT(((ULONG_PTR)Address % PAGE_SIZE) == 0);

    if (Process == NULL)
    {
        if (Address < MmSystemRangeStart)
        {
            DPRINT1("NULL process given for user-mode mapping at %p -- %lu pages starting at %Ix\n", Address, PageCount, *Pages);
            KeBugCheck(MEMORY_MANAGEMENT);
        }
        if (PageCount > 0x10000 ||
            (ULONG_PTR) Address / PAGE_SIZE + PageCount > 0x100000)
        {
            DPRINT1("Page count too large for kernel-mode mapping at %p -- %lu pages starting at %Ix\n", Address, PageCount, *Pages);
            KeBugCheck(MEMORY_MANAGEMENT);
        }
    }
    else
    {
        if (Address >= MmSystemRangeStart)
        {
            DPRINT1("Process %p given for kernel-mode mapping at %p -- %lu pages starting at %Ix\n", Process, Address, PageCount, *Pages);
            KeBugCheck(MEMORY_MANAGEMENT);
        }
        if (PageCount > (ULONG_PTR)MmSystemRangeStart / PAGE_SIZE ||
            (ULONG_PTR) Address / PAGE_SIZE + PageCount >
            (ULONG_PTR)MmSystemRangeStart / PAGE_SIZE)
        {
            DPRINT1("Page count too large for process %p user-mode mapping at %p -- %lu pages starting at %Ix\n", Process, Address, PageCount, *Pages);
            KeBugCheck(MEMORY_MANAGEMENT);
        }
    }

    Attributes = ProtectToPTE(flProtect);
    Attributes &= 0xfff;
    if (Address >= MmSystemRangeStart)
    {
        Attributes &= ~PA_USER;
        }
    else
    {
        Attributes |= PA_USER;
    }

    Addr = Address;
    /* MmGetPageTableForProcess should be called on the first run, so
     * let this trigger it */
    oldPdeOffset = ADDR_TO_PDE_OFFSET(Addr) + 1;
    for (i = 0; i < PageCount; i++, Addr = (PVOID)((ULONG_PTR)Addr + PAGE_SIZE))
    {
        if (!(Attributes & PA_PRESENT) && Pages[i] != 0)
        {
            DPRINT1("Setting physical address but not allowing access at address "
                    "0x%p with attributes %x/%x.\n",
                    Addr, Attributes, flProtect);
            KeBugCheck(MEMORY_MANAGEMENT);
        }
        PdeOffset = ADDR_TO_PDE_OFFSET(Addr);
        if (oldPdeOffset != PdeOffset)
        {
            if(Pt) MmUnmapPageTable(Pt, OldIrql);
            Pt = MmGetPageTableForProcess(Process, Addr, TRUE, &OldIrql);
            if (Pt == NULL)
            {
                KeBugCheck(MEMORY_MANAGEMENT);
            }
        }
        else
        {
            Pt++;
        }
        oldPdeOffset = PdeOffset;

        Pte = InterlockedExchangePte(Pt, PFN_TO_PTE(Pages[i]) | Attributes);

        /* There should not be anything valid here */
        if (Pte != 0)
        {
            DPRINT1("Bad PTE %lx at %p for %p + %lu\n", Pte, Pt, Address, i);
            KeBugCheck(MEMORY_MANAGEMENT);
        }

        /* We don't need to flush the TLB here because it only caches valid translations
         * and we're moving this PTE from invalid to valid so it can't be cached right now */

		if (Addr < MmSystemRangeStart)
		{
			/* Add PDE reference */
			Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Addr)]++;
			ASSERT(Process->Vm.VmWorkingSetList->UsedPageTableEntries[MiGetPdeOffset(Addr)] <= PTE_PER_PAGE);
		}
    }

    ASSERT(Addr > Address);
    MmUnmapPageTable(Pt, OldIrql);

    return(STATUS_SUCCESS);
}

NTSTATUS
NTAPI
MmCreateVirtualMapping(PEPROCESS Process,
                       PVOID Address,
                       ULONG flProtect,
                       PPFN_NUMBER Pages,
                       ULONG PageCount)
{
    ULONG i;

    ASSERT((ULONG_PTR)Address % PAGE_SIZE == 0);
    for (i = 0; i < PageCount; i++)
    {
        if (!MmIsPageInUse(Pages[i]))
        {
            DPRINT1("Page at address %x not in use\n", PFN_TO_PTE(Pages[i]));
            KeBugCheck(MEMORY_MANAGEMENT);
        }
    }

    return(MmCreateVirtualMappingUnsafe(Process,
                                        Address,
                                        flProtect,
                                        Pages,
                                        PageCount));
}

ULONG
NTAPI
MmGetPageProtect(PEPROCESS Process, PVOID Address)
{
    ULONG Entry;
    ULONG Protect;

    Entry = MmGetPageEntryForProcess(Process, Address);


    if (!(Entry & PA_PRESENT))
    {
        Protect = PAGE_NOACCESS;
    }
    else
    {
        if (Entry & PA_READWRITE)
        {
            Protect = PAGE_READWRITE;
        }
        else
        {
            Protect = PAGE_EXECUTE_READ;
        }
        if (Entry & PA_CD)
        {
            Protect |= PAGE_NOCACHE;
        }
        if (Entry & PA_WT)
        {
            Protect |= PAGE_WRITETHROUGH;
        }
        if (!(Entry & PA_USER))
        {
            Protect |= PAGE_SYSTEM;
        }

    }
    return(Protect);
}

VOID
NTAPI
MmSetPageProtect(PEPROCESS Process, PVOID Address, ULONG flProtect)
{
    ULONG Attributes = 0;
    PULONG Pt;
    ULONG Pte;
    KIRQL OldIrql;

    DPRINT("MmSetPageProtect(Process %p  Address %p  flProtect %x)\n",
           Process, Address, flProtect);

    Attributes = ProtectToPTE(flProtect);

    Attributes &= 0xfff;
    if (Address >= MmSystemRangeStart)
    {
        Attributes &= ~PA_USER;
        }
    else
    {
        Attributes |= PA_USER;
    }

    Pt = MmGetPageTableForProcess(Process, Address, FALSE, &OldIrql);
    if (Pt == NULL)
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }
    Pte = InterlockedExchangePte(Pt, PAGE_MASK(*Pt) | Attributes | (*Pt & (PA_ACCESSED|PA_DIRTY)));

    // We should be able to bring a page back from PAGE_NOACCESS
    if ((Pte & 0x800) || !(Pte >> PAGE_SHIFT))
    {
        DPRINT1("Invalid Pte %lx\n", Pte);
        KeBugCheck(MEMORY_MANAGEMENT);
    }

    if((Pte & Attributes) != Attributes)
        MiFlushTlb(Pt, Address, OldIrql);
    else
        MmUnmapPageTable(Pt, OldIrql);
}

PVOID
NTAPI
MmCreateHyperspaceMapping(PFN_TYPE Page)
{
    PVOID Address;
    ULONG i;
    
    ULONG Entry;
    PULONG Pte;
    Entry = PFN_TO_PTE(Page) | PA_PRESENT | PA_READWRITE;

#if USE_FREELIST

if (!HyperspaceInitialized)
{
    MmInitHyperSpaceFreeList(MiAddressToPte(HYPERSPACE));
}

    Pte = (PULONG)MiInterlockedPopPteListEntry(&MmHyperspaceFreeListHead);
if (!Pte)
{
    PULONG p;
    DPRINT1("Pte == 0\n");

    p = (PULONG)MiAddressToPte(HYPERSPACE);
    for (i = 0; i < 1024; i++)
    {
        DbgPrint("%x ", p[i]);
    }
}
    *Pte = Entry;
    Address = MiPteToAddress(Pte);

#else

    Pte = (PULONG)MiAddressToPte(HYPERSPACE) + Page % 1024;
    if (Page & 1024)
    {
        for (i = Page % 1024; i < 1024; i++, Pte++)
        {
            if (0 == InterlockedCompareExchange((PLONG)Pte, (LONG)Entry, 0))
            {
                break;
            }
        }
        if (i >= 1024)
        {
            Pte = (PULONG)MiAddressToPte(HYPERSPACE);
            for (i = 0; i < Page % 1024; i++, Pte++)
            {
                if (0 == InterlockedCompareExchange((PLONG)Pte, (LONG)Entry, 0))
                {
                    break;
                }
            }
            if (i >= Page % 1024)
            {
                KeBugCheck(MEMORY_MANAGEMENT);
            }
        }
    }
    else
    {
        for (i = Page % 1024; (LONG)i >= 0; i--, Pte--)
        {
            if (0 == InterlockedCompareExchange((PLONG)Pte, (LONG)Entry, 0))
            {
                break;
            }
        }
        if ((LONG)i < 0)
        {
            Pte = (PULONG)MiAddressToPte(HYPERSPACE) + 1023;
            for (i = 1023; i > Page % 1024; i--, Pte--)
            {
                if (0 == InterlockedCompareExchange((PLONG)Pte, (LONG)Entry, 0))
                {
                    break;
                }
            }
            if (i <= Page % 1024)
            {
                KeBugCheck(MEMORY_MANAGEMENT);
            }
        }
    }
    Address = (PVOID)((ULONG_PTR)HYPERSPACE + i * PAGE_SIZE);
#endif
    __invlpg(Address);
    return Address;
}

PFN_TYPE
NTAPI
MmDeleteHyperspaceMapping(PVOID Address)
{
    PFN_TYPE Pfn;
    ULONG Entry;
    
    ASSERT (IS_HYPERSPACE(Address));
    
    Entry = InterlockedExchangePte(MiAddressToPte(Address), 0);
    Pfn = PTE_TO_PFN(Entry);
#if USE_FREELIST
    MiInterlockedPushPteListEntry(&MmHyperspaceFreeListHead,
                                  MiAddressToPte(Address));
#endif
    __invlpg(Address);
    return Pfn;
}

CODE_SEG("INIT")
VOID
NTAPI
MmInitGlobalKernelPageDirectory(VOID)
{
    /* Nothing to do here */
}

VOID
INIT_FUNCTION
NTAPI
MiInitPageDirectoryMap(VOID)
{
    MEMORY_AREA* kernel_map_desc = NULL;
    MEMORY_AREA* hyperspace_desc = NULL;
    PHYSICAL_ADDRESS BoundaryAddressMultiple;
    PVOID BaseAddress;
    NTSTATUS Status;
    
    DPRINT1("MiInitPageDirectoryMap()\n");
    
    BoundaryAddressMultiple.QuadPart = 0;
    BaseAddress = (PVOID)PAGETABLE_MAP;
    Status = MmCreateMemoryArea(MmGetKernelAddressSpace(),
                                MEMORY_AREA_SYSTEM | MEMORY_AREA_STATIC,
                                &BaseAddress,
                                0x400000,
                                PAGE_READWRITE,
                                &kernel_map_desc,
                                TRUE,
                                0,
                                BoundaryAddressMultiple);
    if (!NT_SUCCESS(Status))
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }
    BaseAddress = (PVOID)HYPERSPACE;
    Status = MmCreateMemoryArea(MmGetKernelAddressSpace(),
                                MEMORY_AREA_SYSTEM | MEMORY_AREA_STATIC,
                                &BaseAddress,
                                0x400000,
                                PAGE_READWRITE,
                                &hyperspace_desc,
                                TRUE,
                                0,
                                BoundaryAddressMultiple);
    if (!NT_SUCCESS(Status))
    {
        KeBugCheck(MEMORY_MANAGEMENT);
    }
    HasDebug = 1;

    DPRINT1("Leave MiInitPageDirectoryMap\n");
    if (!MiValidateFreeList()) DPRINT1("not valid!");
}

/* EOF */
