
#define MX_PAGING_LEVELS 4

#define MX_HIGHEST_USER_ADDRESS         0x000007FFFFFFFFFFLL

#define MX_SYSTEM_RANGE_START           0xFFFF800000000000LL
#define MX_LOWEST_SYSTEM_VA             0xFFFFF00000000000LL
#define MX_PAGETABLE_MAP_START          0xFFFFF68000000000LL // vpn F68000000
#define MX_HYPERSPACE_START             0xFFFFF70000000000LL // vpn F70000000
#define MX_VPNLIST_USER_START           0xFFFFF70000000000LL
#define MX_VPNLIST_USER_END             0xFFFFF703FFFFFFFFLL // + 0x400000000
#define MX_VADLIST_USER_START           0xFFFFF70400000000LL // MAX 13 GB
#define MX_VADLIST_USER_END             0xFFFFF7073FFFFFFFLL
#define MX_VPNLIST_PAGE_TABLES          0xFFFFF77B40000000LL // + 0x740000000 7B40000000
#define MX_VPNLIST_HYPERSPACE           0xFFFFF77B80000000LL // + 0x780000000
#define MX_VPNLIST_HYPERSPACE_END       0xFFFFF77BBFFFFFFFLL // + 0x780000000
#define MX_HYPERSPACE_END               0xFFFFF77FFFFFFFFFLL
#define MX_DEBUG_MAPPING                0xFFFFF80000000000LL // checkme
#define MX_PFN_DATABASE                 0xFFFFFA8000000000LL
#define MX_HAL_RESERVED                 0xFFFFFFFFFFC00000LL
#define MX_APIC_BASE                    0xFFFFFFFFFFFE0000LL
#define MX_IOAPIC_BASE                  0xFFFFFFFFFFFE1000LL // checkme + aync with hal
#define MX_HIGHEST_SYSTEM_ADDRESS       0xFFFFFFFFFFFFFFFFLL

#define MX_HIGHEST_USER_PDE             (((MX_HIGHEST_USER_ADDRESS >> PDE_SHIFT) & PDE_MASK) + PDE_BASE)

#define MmSystemRangeEnd ((PVOID)MX_HIGHEST_SYSTEM_ADDRESS)
#define MxHighestUserPde ((PMXPDE)MX_HIGHEST_USER_PDE)

#define MxVadListUser    ((struct _MIVAD*)MX_VADLIST_USER_START)

// ssssssssssssssssxxxxxxxxxpppppppppdddddddddtttttttttoooooooooooo
typedef union _AMD64_POINTER_FIELDS
{
    PVOID Pointer;
    LONG64 Long;
    struct
    {
        ULONG64 Offset:12;
        ULONG64 Pti:9;
        ULONG64 Pdi:9;
        ULONG64 Ppi:9;
        ULONG64 Pxi:9;
        LONG64 SignExtend:16;
    } PageTable;
    struct
    {
        ULONG64 Offset:12;
        ULONG64 Vpn:36;
        LONG64 SignExtend:16;
    } Virtual;
} AMD64_POINTER_FIELDS;

typedef struct _MXPTE_HARDWARE
{
    ULONG64 Valid : 1;
    ULONG64 Write : 1;
    ULONG64 User : 1;
    ULONG64 WriteThrough : 1;
    ULONG64 CacheDisable : 1;
    ULONG64 Accessed : 1;
    ULONG64 Dirty : 1;
    ULONG64 LargePage : 1;
    ULONG64 Global : 1;
    ULONG64 Available1 : 3;
    ULONG64 PageFrameNumber : 40;
    ULONG64 Available2 : 11;
    ULONG64 NoExecute : 1;
} MXPTE_HARDWARE, *PMXPTE_HARDWARE;

typedef struct _MXPTE_ACTIVE
{
    ULONG64 Valid : 1;
    ULONG64 Write : 1;
    ULONG64 User : 1;
    ULONG64 WriteThrough : 1;
    ULONG64 CacheDisable : 1;
    ULONG64 Accessed : 1;
    ULONG64 Dirty : 1;
    ULONG64 LargePage : 1;
    ULONG64 Global : 1;
    ULONG64 CopyOnWrite : 1;
    ULONG64 Reserved0 : 2;
    ULONG64 PageFrameNumber : 40;
    ULONG64 UnusedYet : 11; /* Incremented whenever a new page is mapped */
    ULONG64 NoExecute : 1;
} MXPTE_ACTIVE, *PMXPTE_ACTIVE;

typedef struct _MXPTE_PAGETABLE
{
    ULONG64 Valid : 1;
    ULONG64 WriteMB1 : 1;
    ULONG64 User : 1;
    ULONG64 WriteThrough : 1;
    ULONG64 CacheDisable : 1;
    ULONG64 Accessed : 1;
    ULONG64 Dirty : 1;
    ULONG64 LargePage : 1;
    ULONG64 Global : 1;
    ULONG64 CopyOnWrite : 1;
    ULONG64 reserved0 : 2;
    ULONG64 PageFrameNumber : 40;
    ULONG64 UnusedYet : 11;
    ULONG64 NoExecute : 1;
} MXPTE_PAGETABLE, *PMXPTE_PAGETABLE;

typedef struct _MXPTE_SOFTWARE
{
    ULONG64 ValidMBZ : 1;
    ULONG64 Write : 1;
    ULONG64 User : 1;
    ULONG64 WriteThrough : 1;
    ULONG64 CacheDisable : 1;
    ULONG64 Accessed : 1;
    ULONG64 Dirty : 1;
    ULONG64 LargePage : 1;
    ULONG64 Global : 1;
    ULONG64 CopyOnWrite : 1;
    ULONG64 Transition : 1;
    ULONG64 VadBased : 1;
    ULONG64 PageFrameNumber : 40;
    ULONG64 UnusedYet : 11;
    ULONG64 NoExecute : 1;
} MXPTE_SOFTWARE; *PMXPTE_SOFTWARE;

typedef struct _MXPTE_DEMAND
{
    ULONG64 ValidMBZ : 1;
    ULONG64 Write : 1;
    ULONG64 User : 1;
    ULONG64 WriteThrough : 1;
    ULONG64 CacheDisable : 1;
    ULONG64 Accessed : 1;
    ULONG64 Dirty : 1;
    ULONG64 LargePage : 1;
    ULONG64 Global : 1;
    ULONG64 CopyOnWrite : 1;
    ULONG64 reserved0 : 2;
    ULONG64 PageFrameNumberMBZ : 36;
    ULONG64 Type : 4;
    ULONG64 Sequence : 11;
    ULONG64 NoExecute : 1;
} MXPTE_DEMAND, *PMXPTE_DEMAND;

typedef struct _MXPTE_VAD
{
    LONG64 ValidMBZ : 1;
    LONG64 VadIndexHigh : 10;
    LONG64 VadBasedMB1 : 1;
    LONG64 VadIndexLow : 16;
    LONG64 PteContext : 36;
} MXPTE_VAD; *PMXPTE_VAD;

typedef struct _MXPTE_TRANSITION
{
    LONG64 ValidMBZ : 1;
    LONG64 Unused : 9;
    LONG64 Transition : 1;
    LONG64 VadBased : 1;
    LONG64 QueueAddress : 52;
} MXPTE_TRANSITION; *PMXPTE_TRANSITION;

typedef struct _MXPTE_PAGEFILE
{
    ULONG64 ValidMBZ : 1;
    ULONG64 VadIndex : 26;
    ULONG64 PageFileIndex : 34;
    ULONG64 Type : 3;
} MXPTE_PAGEFILE; *PMXPTE_PAGEFILE;


typedef struct _MXPTE
{
    union
    {
        LONG64 Long;
        MXPTE_HARDWARE Hard;
        MXPTE_ACTIVE Active;
        MXPTE_SOFTWARE Soft;
        MXPTE_PAGETABLE PageTable;
        MXPTE_DEMAND Demand;
        MXPTE_PAGEFILE PageFile;
        MXPTE_TRANSITION Trans;
        MXPTE_VAD Vad;
    };


} MXPTE, *PMXPTE;

typedef MXPTE MXPDE, *PMXPDE;
typedef MXPTE MXPPE, *PMXPPE;
typedef MXPTE MXPXE, *PMXPXE;

extern MXPTE MxValidKernelPte;
extern MXPDE MxValidKernelPde;
extern MXPDE MxValidUserPde;

#define MxValidKernelPpe MxValidKernelPde
#define MxValidKernelPxe MxValidKernelPde

enum
{
    PteInvalid,
    PteDemandAny,
    PteDemandZero,
    PtePrototype,
    PtePageFile,
    PteSection
};

extern PVOID Amd64IdentityMappingStart;

MXPTE
FORCEINLINE
MxInterlockedCompareExchangePte(
        _Inout_ PMXPTE TargetPte,
        _In_ MXPTE NewPte,
        _In_ MXPTE ComparandPte)
{
    MXPTE OldPte;
    ASSERT(ComparandPte.Hard.Valid == 0);
    ASSERT(NewPte.Hard.Valid == 1); // currently only invalid -> valid
    //ASSERT(NewPte.Active.Sequence == ComparandPte.Soft.Sequence);
    //ASSERT(NewPte.Active.Sequence == MmPfnDatabase[NewPte.Active.PageFrameNumber].Sequence);

    OldPte.Long = InterlockedCompareExchange64(&TargetPte->Long,
                                               NewPte.Long,
                                               ComparandPte.Long);
    return OldPte;
}

MXPTE
FORCEINLINE
MxInterlockedExchangePte(
        _Inout_ PMXPTE TargetPte,
        _In_ MXPTE NewPte)
{
    MXPTE OldPte;
    OldPte.Long = InterlockedExchange64(&TargetPte->Long, NewPte.Long);
    return OldPte;
}

#define MXPTE_Valid(Pte) (Pte->Hard.Valid)
#define MXPTE_Write(Pte) (Pte->Hard.Write)
#define MXPTE_Execute(Pte) (!Pte->Hard.NoExecute()

VOID
FORCEINLINE
MXPTE_CreateTransitionPte(
    _Out_ PMXPTE TransPte,
    _In_ struct _MI_TRANSITION_WAITBLOCK *WaitBlock)
{
    TransPte->Long = ((ULONG64)WaitBlock) << 12;
    TransPte->Soft.Transition = 1;
}

PVOID
FORCEINLINE
MXPTE_GetTransitionQueue(
    _In_ PMXPTE TransPte)
{
    ASSERT(TransPte->Soft.Transition == 1);
    ASSERT(TransPte->Soft.VadBased == 0);
    return (PVOID)TransPte->Trans.QueueAddress;
}

ULONG
FORCEINLINE
MXPTE_GetVadIndex(
    _In_ PMXPTE VadPte)
{
    ASSERT(VadPte->Soft.Transition == 0);
    ASSERT(VadPte->Soft.VadBased == 1);
    return (ULONG)((VadPte->Vad.VadIndexHigh << 16) + VadPte->Vad.VadIndexLow);
}

MXPTE
FORCEINLINE
MxDemandPteToValidPte(
    _In_ MXPTE DemandPte,
    _In_ PFN_NUMBER PageFrameNumber)
{
    MXPTE ValidPte = DemandPte;
    ASSERT(DemandPte.Demand.ValidMBZ == 0);
    ASSERT(DemandPte.Soft.Transition == 0);
    ASSERT(DemandPte.Soft.VadBased == 0);

    ValidPte.Active.Valid = 1;
    ValidPte.Active.Dirty = 0;
    ValidPte.Active.Accessed = 0;
    ValidPte.Active.PageFrameNumber = PageFrameNumber;
    return ValidPte;
}


ULONG64
FORCEINLINE
MxAddressToVpn(PVOID Address)
{
    return (((ULONG_PTR)Address) >> PAGE_SHIFT) & 0xFFFFFFFFFULL;
}

ULONG64
FORCEINLINE
MxAddressToVpn2(PVOID Address)
{
    AMD64_POINTER_FIELDS Fields;
    Fields.Pointer = Address;
    return Fields.Virtual.Vpn;
}

PMXPTE
FORCEINLINE
MxVpnToPte(ULONG64 Vpn)
{
    return ((PMXPTE)PTE_BASE) + Vpn;
}

PMXPTE
FORCEINLINE
MxVpnToPde(ULONG64 Vpn)
{
    return ((PMXPTE)PDE_BASE) + (Vpn / PTE_PER_PAGE);
}

PMXPTE
FORCEINLINE
MxVpnToPpe(ULONG64 Vpn)
{
    return ((PMXPTE)PPE_BASE) + (Vpn / PDE_PER_PAGE);
}

PMXPTE
FORCEINLINE
MxVpnToPxe(ULONG64 Vpn)
{
    return ((PMXPTE)PXE_BASE) + (Vpn / PPE_PER_PAGE);
}

ULONG
FORCEINLINE
MxAddressToPxi(PVOID Address)
{
    return ((((ULONG64)Address) >> PXI_SHIFT) & PXI_MASK);
}

ULONG
FORCEINLINE
MxAddressToPpi(PVOID Address)
{
    return ((((ULONG64)Address) >> PPI_SHIFT) & PPI_MASK);
}

ULONG
FORCEINLINE
MxAddressToPdi(PVOID Address)
{
    return ((((ULONG64)Address) >> PDI_SHIFT) & PDI_MASK_AMD64);
}

ULONG
FORCEINLINE
MxAddressToPti(PVOID Address)
{
    return ((((ULONG64)Address) >> PTI_SHIFT) & PTI_MASK_AMD64);
}

#define PTE_SHIFT (PTI_SHIFT - 3)
#define PDE_SHIFT (PDI_SHIFT - 3)
#define PPE_SHIFT (PPI_SHIFT - 3)
#define PXE_SHIFT (PXI_SHIFT - 3)

#define PTE_MASK (0xFFFFFFFFFULL << 3)
#define PDE_MASK (0x7FFFFFF << 3)
#define PPE_MASK (0x3FFFF << 3)
#define PXE_MASK (0x1FF << 3)

PMXPTE
FORCEINLINE
MxAddressToPte(PVOID Address)
{
    return (PMXPTE)((((ULONG64)Address >> PTE_SHIFT) & PTE_MASK) + PTE_BASE);
}

PMXPTE
FORCEINLINE
MxAddressToPde(PVOID Address)
{
    return (PMXPTE)((((ULONG64)Address >> PDE_SHIFT) & PDE_MASK) + PDE_BASE);
}

PMXPTE
FORCEINLINE
MxAddressToPpe(PVOID Address)
{
    return (PMXPTE)((((ULONG64)Address >> PPE_SHIFT) & PPE_MASK) + PPE_BASE);
}

PMXPTE
FORCEINLINE
MxAddressToPxe(PVOID Address)
{
    return (PMXPTE)((((ULONG64)Address >> PXE_SHIFT) & PXE_MASK) + PXE_BASE);
}


PVOID
FORCEINLINE
MxPteToAddress(PMXPTE PointerPte)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PointerPte << (PTE_SHIFT + 16)) >> 16);
}


PVOID
FORCEINLINE
MxPdeToAddress(PMXPTE PointerPde)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PointerPde << (PDE_SHIFT + 16)) >> 16);
}

PVOID
FORCEINLINE
MxPpeToAddress(PMXPTE PointerPpe)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PointerPpe << (PPE_SHIFT + 16)) >> 16);
}

PVOID
FORCEINLINE
MxPxeToAddress(PMXPTE PointerPxe)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PointerPxe << (PXE_SHIFT + 16)) >> 16);
}


BOOLEAN
FORCEINLINE
MxIsPageTableAddress(PVOID Address)
{
    return ((ULONG64)Address & 0xFFFFFF8000000000ULL) == 0xFFFFF68000000000ULL;
}

BOOLEAN
FORCEINLINE
MxIsHyperSpaceAddress(PVOID Address)
{
    return ((ULONG64)Address & 0xFFFFFF8000000000ULL) == 0xFFFFF70000000000ULL;
}

BOOLEAN
FORCEINLINE
MxIsPtOrHyperAddress(PVOID Address)
{
    return ((ULONG64)Address - 0xFFFFF68000000000ULL) <= 0xFFFFFFFFFFUL;
}

PVOID
FORCEINLINE
MxGetEphemeralMapping(
    PFN_NUMBER PageFrameNumber)
{
    return (PUCHAR)Amd64IdentityMappingStart + (PageFrameNumber * PAGE_SIZE);
}

VOID
FORCEINLINE
MxReleaseEphemeralMapping(
    PVOID Address)
{
    /* Nothing to do */
}

