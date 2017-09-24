
#pragma once

#define MI_PAGING_LEVELS 4

namespace Mm {

extern PFN_NUMBER GlobalZeroPfn;

enum PTE_TYPE
{
    /* Active states */
    PteValid = 0,      // 0b00
    PtePageTable = 1,  // 0b01
    PteShared = 2,     // 0b10
    PteDemandZero = 3, // 0b11

    PtePageFile = 4,   // 0b00
    PtePrototype = 5,  // 0b01
    PteTransition = 6, // 0b10
    PteVad = 7,        // 0b11

    PteCopyOnWrite,
    PteDemandAny,
    PteEmpty,
    PteNoAccess,
    PteGuardPage,
};

typedef struct _HARDWARE_PTE
{
    UINT64 Valid : 1;
    UINT64 Write : 1;
    UINT64 Owner : 1;
    UINT64 WriteCombining : 1;
    UINT64 CacheDisable : 1;
    UINT64 Accessed : 1;
    UINT64 Dirty : 1;
    UINT64 LargePage : 1;
    UINT64 Global : 1;
    UINT64 CopyOnWrite : 1;
    UINT64 Reserved0 : 2;
    UINT64 PageFrameNumber : 36;
    UINT64 Reserved1 : 4;
    UINT64 SoftwareWsIndex : 11;
    UINT64 NoExecute : 1;
} HARDWARE_PTE, *PHARDWARE_PTE;

typedef struct _SOFTWARE_PTE
{
    UINT64 MustBeZero : 1;
    UINT64 HardwareState : 8;
    UINT64 CopyOnWrite : 1;
    UINT64 Prototype : 1;
    UINT64 Transition : 1;
    UINT64 Reserved : 46;
    UINT64 Protection : 5;
    UINT64 NoExecuteOverlay : 1;
} SOFTWARE_PTE, *PSOFTWARE_PTE;

typedef struct _TRANSITION_PTE
{
    UINT64 MustBeZero : 1;
    UINT64 HardwareState : 8;
    UINT64 CopyOnWrite : 1;
    UINT64 Reserved0 : 1;
    UINT64 Transition : 1;
    UINT64 PageFrameNumber : 36;
    UINT64 Reserved1 : 15;
    UINT64 NoExecute : 1;
} TRANSITION_PTE, *PTRANSITION_PTE;

typedef struct _PAGEFILE_PTE
{
    UINT64 MustBeZero : 1;
    UINT64 HardwareState : 8;
    UINT64 CopyOnWrite : 1;
    UINT64 Reserved0 : 2;
    UINT64 PageFileNumber : 4;
    UINT64 PageFileIndex : 32;
    UINT64 PageFileReserved : 1;
    UINT64 PageFileAllocated : 1;
    UINT64 DbgCrc : 7;
    UINT64 Reserved : 1;
    UINT64 Protection : 5;
    UINT64 InStore : 1;
} PAGEFILE_PTE, *PPAGEFILE_PTE;

typedef struct _PROTOTYPE_PTE
{
    UINT64 MustBeZero : 1;
    UINT64 DemandFillProto : 1;
    UINT64 HiberVerifyConverted : 1;
    UINT64 Unused1 : 5;
    UINT64 ReadOnly : 1;
    UINT64 Combined : 1;
    UINT64 Prototype : 1;
    UINT64 Protection : 5;
    INT64 ProtoAddress : 48;
} PROTOTYPE_PTE, *PPROTOTYPE_PTE;

static const PROTOTYPE_PTE PrototypePte = {0, 0, 0, 0, 0, 0, 1, 0, 0};

typedef struct _VAD_PTE
{
    UINT64 MustBeZero : 1;
    UINT64 DemandFillProto : 1;
    UINT64 HiberVerifyConverted : 1;
    UINT64 Unused1 : 5;
    UINT64 ReadOnly : 1;
    UINT64 Combined : 1;
    UINT64 Prototype : 1;
    UINT64 Protection : 5;
    INT64 VadAddress : 48;
} VAD_PTE, *PVAD_PTE;

typedef union
{
    HARDWARE_PTE Hard;
    SOFTWARE_PTE Soft;
    PROTOTYPE_PTE Proto;
    ULONG64 Long;
} UNION_PTE, *PUNION_PTE;

extern const HARDWARE_PTE ProtectToPteBase[8];
extern const HARDWARE_PTE ProtectToPteFlags[32];

#define ProtectToPteMask(Protect) \
    (*(PULONG64)&ProtectToPteBase[(Protect) & 0x7] | *(PULONG64)&ProtectToPteFlags[((Protect) & 0xF8) >> 3])

//                                                         W C         C
//                                                   V W O T D A D L G W
static const HARDWARE_PTE ValidPte                = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const HARDWARE_PTE ValidPde                = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const HARDWARE_PTE ValidLargePagePde       = {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0};
static const SOFTWARE_PTE NoAccessPte             = {0,0,0,0,0,0,MM_NOACCESS,0};

class PTE_COMMON
{
protected:
    union
    {
        HARDWARE_PTE Hard;
        PROTOTYPE_PTE Proto;
        SOFTWARE_PTE Soft;
        PAGEFILE_PTE PageFile;
        LONG64 Long;
    };

#if 1 || DBG
protected:
    /* Disable direct write */
    PTE_COMMON (PTE_COMMON& NewPte);
    inline PTE_COMMON () {}
#endif

public:

    inline
    bool
    IsEmpty ()
    {
        return (this->Long == 0);
    }

    inline
    void
    Erase ()
    {
        this->Long = 0;
    }

    inline
    bool
    IsValid ()
    {
        return this->Hard.Valid;
    }

    inline
    PFN_NUMBER
    GetPageFrameNumber (
        VOID)
    {
        return this->Hard.PageFrameNumber;
    }

    inline
    VOID
    SetPageFrameNumber (
        _In_ PFN_NUMBER PageFrameNumber)
    {
        NT_ASSERT(!Proto.Prototype);
        this->Hard.PageFrameNumber = PageFrameNumber;
    }

    inline
    ULONG
    GetProtection ()
    {
        ULONG Protect = 0;
        if (this->Hard.Valid) Protect |= MM_READONLY;
        if (this->Hard.Write) Protect |= MM_READWRITE;
        if (!this->Hard.NoExecute) Protect |= MM_EXECUTE;
        if (this->Hard.Global) Protect |= MM_GLOBAL;
        if (this->Hard.LargePage) Protect |= MM_LARGEPAGE;
        return Protect;
    }

    VOID
    ReadValue (PTE_COMMON* TargetPte)
    {
        TargetPte->Long = this->Long;
    }

    inline
    bool
    IsRealPte ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PTE_BASE;
        return Offset < (PTE_TOP + 1 - PTE_BASE);
    }

    inline
    ULONG
    GetTableIndex ()
    {
        return ((ULONG64)this & (PAGE_SIZE - 1)) / sizeof(*this);
    }

};

class PTE : public PTE_COMMON
{
public:

    inline
    bool
    IsPdeBoundary ()
    {
        return (((ULONG64)this & (PAGE_SIZE - 1)) == 0);
    }

    inline
    bool
    IsNoAccess ()
    {
        return (this->Long == *(ULONG64*)&NoAccessPte);
    }

    inline
    bool
    IsExecutable ()
    {
        return !this->Hard.NoExecute;
    }

    inline
    bool
    IsWritable ()
    {
        return this->Hard.Write;
    }

    inline
    void
    SetWritable (
        bool Writable)
    {
        this->Hard.Write = Writable;
    }

    inline
    bool
    IsCopyOnWrite ()
    {
        return this->Hard.CopyOnWrite;
    }

    inline
    VOID
    MakeValidPte (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ ULONG Protect)
    {
        UNION_PTE PteValue;
        NT_ASSERT(!(Protect & MM_LARGEPAGE));
        PteValue.Long = ProtectToPteMask(Protect);
        NT_ASSERT(PteValue.Hard.Valid);
        PteValue.Hard.PageFrameNumber = PageFrameNumber;
        this->Long = PteValue.Long;
    }

    inline
    VOID
    MakeDemandZeroPte (
        _In_ ULONG Protect)
    {
        NT_ASSERT(!(Protect & (MM_MAPPED|MM_LARGEPAGE)));
        NT_ASSERT((Protect & MM_PROTECTION_MASK) != MM_INVALID);
        UNION_PTE PteValue = { 0 };
        PteValue.Soft.Protection = Protect & MM_PROTECTION_MASK;
        this->Long = PteValue.Long;
    }

    inline
    VOID
    MakeSoftwarePte (
        _In_ ULONG Protect)
    {
        SOFTWARE_PTE SoftPte = { 0 };;
        NT_ASSERT(!(Protect & (MM_MAPPED|MM_LARGEPAGE)));
        SoftPte.Protection = Protect & MM_PROTECTION_MASK;
        this->Soft = SoftPte;
    }

    inline
    VOID
    MakePrototypePte (
        _In_ PTE* Prototype,
        _In_ ULONG Protect)
    {
        PROTOTYPE_PTE ProtoPte = {0};
        ProtoPte.Prototype = 1;
        ProtoPte.Protection = Protect;
        ProtoPte.ProtoAddress = reinterpret_cast<ULONG64>(Prototype) & 0xFFFFFFFFFFFFULL;
        this->Proto = ProtoPte;
    }

    inline
    PTE*
    GetPrototypeAddress ()
    {
        if (this->Soft.Prototype == 0)
            return NULL;
        ULONG64 Address = this->Proto.ProtoAddress | 0xFFFF800000000000ULL;
        return reinterpret_cast<PTE*>(Address);
    }

    inline
    VOID
    WriteValidPte (
        _In_ PTE &NewPte)
    {
        NT_ASSERT(NewPte.Hard.Valid != 0);
        this->Hard = NewPte.Hard;
    }

    inline
    VOID
    WriteSoftwarePte (
        _In_ PTE &NewPte)
    {
        NT_ASSERT(NewPte.Hard.Valid == 0);
        this->Soft = NewPte.Soft;
    }

    inline
    VOID
    MakeValidPteFromPrototype (
        VOID)
    {
        //UNION_PTE PteValue;
        //PteValue.Long = ProtectToPteMask(this->Proto.Protection);
        //NT_ASSERT(PteValue.Hard.Valid);
        //PteValue.Hard.PageFrameNumber = PageFrameNumber;
        //this->Long = PteValue.Long;
    }

    inline
    VOID
    UpdateProtection (
        _In_ ULONG Protect)
    {
        NT_ASSERT(FALSE);
    }

    inline
    BOOLEAN
    InterlockedCompareExchange (
        _In_ PTE& ExchangePte,
        _Inout_ PTE* CurrentPte)
    {
        PTE OldPteValue;

        OldPteValue.Long = InterlockedCompareExchange64(&this->Long,
                                                        ExchangePte.Long,
                                                        CurrentPte->Long);
        if (OldPteValue.Long != CurrentPte->Long)
        {
            CurrentPte->Long = OldPteValue.Long;
            return FALSE;
        }
        return TRUE;
    }

    inline
    PTE_TYPE
    GetPteType (
        VOID)
    {
        if (this->Hard.Valid)
        {
            return PteValid;
        }
        else if (this->Soft.Prototype)
        {
            return PtePrototype;
        }
        else if (this->Soft.Transition)
        {
            return PteTransition;
        }
        else if (this->PageFile.PageFileIndex != 0)
        {
            return PtePageFile;
        }
        else if (this->Soft.Protection == MM_NOACCESS)
        {
             return PteNoAccess;
        }
        else if (this->Soft.Protection & MM_GUARDPAGE)
        {
             // FIXME: yould also be MM_DECOMMIT, but we ignore this for now
             return PteGuardPage;
        }
        else if (this->Soft.Protection != MM_INVALID)
        {
            return PteDemandZero;
        }
        else //if (this->Long == 0)
        {
            return PteEmpty;
        }

    }

};

class PDE : public PTE_COMMON
{
public:

    inline
    bool
    IsLargePage ()
    {
        return this->Hard.LargePage;
    }

    inline
    VOID
    MakeValidPde (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ ULONG Protect)
    {
        HARDWARE_PTE HardPde = ValidPde;
        if (Protect & MM_GLOBAL) HardPde.Global = 1;
        HardPde.PageFrameNumber = PageFrameNumber;
        this->Hard = HardPde;
    }

    inline
    VOID
    MakeValidLargePagePde (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ ULONG Protect)
    {
        HARDWARE_PTE HardPde = ValidLargePagePde;
        NT_ASSERT((PageFrameNumber & 0x1FFULL) == 0);
        if (Protect & MM_READWRITE) HardPde.Write = 1;
        if (Protect & MM_GLOBAL) HardPde.Global = 1;
        HardPde.PageFrameNumber = PageFrameNumber;
        this->Hard = HardPde;
    }

};

class PPE : public PTE_COMMON
{
public:

    inline
    bool
    IsRealPpe ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PPE_BASE;
        return Offset < (PPE_TOP + 1 - PPE_BASE);
    }

    inline
    VOID
    MakeValidPpe (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ ULONG Protect)
    {
        HARDWARE_PTE HardPpe = ValidPde;
        HardPpe.PageFrameNumber = PageFrameNumber;
        this->Hard = HardPpe;
    }

};

class PXE : public PTE_COMMON
{
public:

    inline
    bool
    IsRealPxe ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PXE_BASE;
        return Offset < (PXE_TOP + 1 - PXE_BASE);
    }

    inline
    VOID
    MakeValidPxe (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ ULONG Protect)
    {
        HARDWARE_PTE HardPxe = ValidPde;
        HardPxe.PageFrameNumber = PageFrameNumber;
        this->Hard = HardPxe;
    }

};

typedef PTE *PPTE;
typedef PDE *PPDE;
typedef PPE *PPPE;
typedef PXE *PPXE;

enum PAGE_FAULT_ERROR_CODE
{
    PFEC_PROTECT = 0x01,
    PFEC_WRITE = 0x02,
    PFEC_USER = 0x04,
    PFEC_RESERVED = 0x08,
    PFEC_INSTRUCTION_FETCH = 0x10
};

PPTE
FORCEINLINE
AddressToPte(PVOID Address)
{
    ULONG64 Offset = (ULONG64)Address >> (PTI_SHIFT - 3);
    Offset &= 0xFFFFFFFFFULL << 3;
    return (PPTE)(PTE_BASE + Offset);
}

PPDE
FORCEINLINE
AddressToPde(PVOID Address)
{
    ULONG64 Offset = (ULONG64)Address >> (PDI_SHIFT - 3);
    Offset &= 0x7FFFFFF << 3;
    return (PPDE)(PDE_BASE + Offset);
}

PPPE
FORCEINLINE
AddressToPpe(PVOID Address)
{
    ULONG64 Offset = (ULONG64)Address >> (PPI_SHIFT - 3);
    Offset &= 0x3FFFF << 3;
    return (PPPE)(PPE_BASE + Offset);
}

PPXE
FORCEINLINE
AddressToPxe(PVOID Address)
{
    ULONG64 Offset = (ULONG64)Address >> (PXI_SHIFT - 3);
    Offset &= PXI_MASK << 3;
    return (PPXE)(PXE_BASE + Offset);
}

PVOID
FORCEINLINE
PteToAddress(PPTE PtePointer)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PtePointer << 25) >> 16);
}

PVOID
FORCEINLINE
PdeToAddress(PPDE PdePointer)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PdePointer << 34) >> 16);
}

PVOID
FORCEINLINE
PpeToAddress(PPPE PpePointer)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PpePointer << 43) >> 16);
}

PVOID
FORCEINLINE
PxeToAddress(PPXE PxePointer)
{
    /* Use signed math */
    return (PVOID)(((LONG64)PxePointer << 52) >> 16);
}

bool
FORCEINLINE
IsPageTableAddress (
    PVOID Address)
{
    return ((Address >= (PVOID)PTE_BASE) && (Address <= (PVOID)PTE_TOP));
}

VOID
FORCEINLINE
InvalidateTlbEntry (
    _In_ PVOID Address)
{
    __invlpg(Address);
}

/* Generic:
#define PxeToPpe(PxePointer) AddressToPpe(PxeToAddress(PxePointer))
#define PpeToPde(PpePointer) AddressToPde(PpeToAddress(PpePointer))
#define PdeToPte(PdePointer) AddressToPte(PdeToAddress(PdePointer))
*/

/* For amd64: */
#define PxeToPpe(Pxe) ((PPPE)PteToAddress((PPTE)Pxe))
#define PpeToPde(Ppe) ((PPDE)PteToAddress((PPTE)Ppe))
#define PdeToPte(Pde) ((PPTE)PteToAddress((PPTE)Pde))
#define LargePagePdeToAddress(Pde) PdeToAddress(Pde)
#define PteToPde(Pte) ((PPDE)AddressToPte(Pte))

#define VpnToPxe(Vpn) AddressToPxe(VpnToAddress(Vpn))
#define VpnToPpe(Vpn) AddressToPpe(VpnToAddress(Vpn))
#define VpnToPde(Vpn) AddressToPde(VpnToAddress(Vpn))
#define VpnToPte(Vpn) AddressToPte(VpnToAddress(Vpn))

}; // namespace Mm
