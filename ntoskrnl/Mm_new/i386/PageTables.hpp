
#pragma once

#define MI_PAGING_LEVELS 2

#define PTE_BASE 0xC0000000
#define PDE_BASE 0xC0300000
#define PDE_TOP  0xC0300FFF
#define PTE_TOP  0xC03FFFFF
#define PTE_PER_PAGE 1024
#define PDE_PER_PAGE 1024

namespace Mm {

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
    ULONG Valid : 1;
    ULONG Write : 1;
    ULONG Owner : 1;
    ULONG WriteThrough : 1;
    ULONG CacheDisable : 1;
    ULONG Accessed : 1;
    ULONG Dirty : 1;
    ULONG LargePage : 1;
    ULONG Global : 1;
    ULONG CopyOnWrite : 1;
    ULONG Unused : 1;
    ULONG WriteSMP : 1;
    ULONG PageFrameNumber : 20;
} HARDWARE_PTE, *PHARDWARE_PTE;

typedef struct _SOFTWARE_PTE
{
    ULONG MustBeZero : 1;
    ULONG PageFileLow : 4;
    ULONG Protection : 5;
    ULONG Prototype : 1;
    ULONG Transition : 1;
    ULONG PageFileHigh : 20;
} SOFTWARE_PTE, *PSOFTWARE_PTE;

typedef struct _TRANSITION_PTE
{
    ULONG MustBeZero : 1;
    ULONG Write : 1;
    ULONG Spare : 1;
    ULONG WriteThrough : 1;
    ULONG CacheDisable : 1;
    ULONG Protection : 5;
    ULONG PrototypeMBZ : 1;
    ULONG Transition : 1;
    ULONG PageFrameNumber : 20;
} TRANSITION_PTE, *PTRANSITION_PTE;

typedef struct _PAGEFILE_PTE
{
    ULONG MustBeZero : 1;
    ULONG PageFileLow : 4;
    ULONG Protection : 5;
    ULONG PrototypeMBZ : 1;
    ULONG Transition : 1;
    ULONG PageFileHigh : 20;
} PAGEFILE_PTE, *PPAGEFILE_PTE;

typedef struct _PROTOTYPE_PTE
{
    ULONG MustBeZero : 1;
    ULONG ProtoAddressLow : 8;
    ULONG ReadOnly : 1;
    ULONG Prototype : 1;
    ULONG ProtoAddressHigh : 21;
} PROTOTYPE_PTE, *PPROTOTYPE_PTE;

static const PROTOTYPE_PTE PrototypePte = {0, 0, 0, 1, 0};

typedef struct _VAD_PTE
{
    ULONG MustBeZero : 1;
    ULONG Reserved : 31;
} VAD_PTE, *PVAD_PTE;

typedef union
{
    HARDWARE_PTE Hard;
    SOFTWARE_PTE Soft;
    PROTOTYPE_PTE Proto;
    ULONG Long;
} UNION_PTE, *PUNION_PTE;

extern const HARDWARE_PTE ProtectToPteBase[8];
extern const HARDWARE_PTE ProtectToPteFlags[32];

#define ProtectToPteMask(Protect) \
    (*(PULONG)&ProtectToPteBase[(Protect) & 0x7] | *(PULONG)&ProtectToPteFlags[((Protect) & 0xF8) >> 3])

//                                                         W C         C
//                                                   V W O T D A D L G W
//static const HARDWARE_PTE ValidPte              = {1,0,0,0,0,0,0,0,0,0,0,0};
static const HARDWARE_PTE ValidPde                = {1,1,0,0,0,0,0,0,0,0,0,0};
static const HARDWARE_PTE ValidLargePagePde       = {1,0,0,0,0,0,0,1,0,0,0,0};
static const SOFTWARE_PTE NoAccessPte             = {0,0,MM_NOACCESS,0,0,0};

class PTE_COMMON
{
protected:
    union
    {
        HARDWARE_PTE Hard;
        PROTOTYPE_PTE Proto;
        SOFTWARE_PTE Soft;
        PAGEFILE_PTE PageFile;
        LONG Long;
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
        ULONG Protect = MM_EXECUTE;
        if (this->Hard.Valid) Protect |= MM_READONLY;
        if (this->Hard.Write) Protect |= MM_READWRITE;
        if (this->Hard.Global) Protect |= MM_GLOBAL;
        if (this->Hard.LargePage) Protect |= MM_LARGEPAGE;
        return Protect;
    }

    VOID
    ReadValue (PTE_COMMON* TargetPte)
    {
        TargetPte->Long = this->Long;
    }
};

class PTE : public PTE_COMMON
{
public:

    inline
    bool
    IsRealPte ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PTE_BASE;
        return Offset < (PTE_TOP + 1 - PTE_BASE);
    }

    inline
    bool
    IsPdeBoundary ()
    {
         return (((ULONG)this & (PAGE_SIZE - 1)) == 0);
    }

    inline
    bool
    IsNoAccess ()
    {
        return (this->Long == *(ULONG*)&NoAccessPte);
    }

    inline
    bool
    IsExecutable ()
    {
        return true;
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
        ProtoPte.ReadOnly = !(Protect & MM_READWRITE);
        ProtoPte.ProtoAddressHigh = reinterpret_cast<ULONG>(Prototype) >> 10;
        ProtoPte.ProtoAddressLow  = reinterpret_cast<ULONG>(Prototype) >> 2;
        this->Proto = ProtoPte;
    }

    inline
    PTE*
    GetPrototypeAddress ()
    {
        if (this->Soft.Prototype == 0)
            return NULL;
        ULONG Address = (this->Proto.ProtoAddressHigh << 10) | 0x80000000 |
                        (this->Proto.ProtoAddressLow << 2);
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
        __debugbreak();
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

        OldPteValue.Long = ::InterlockedCompareExchange(&this->Long,
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
        else if ((this->PageFile.PageFileLow != 0) &&
                 (this->PageFile.PageFileHigh != 0))
        {
            return PtePageFile;
        }
        else if (this->Soft.Protection == MM_NOACCESS)
        {
             return PteNoAccess;
        }
        else if (this->Soft.Protection & MM_GUARDPAGE)
        {
             // FIXME: could also be MM_DECOMMIT, but we ignore this for now
             return PteGuardPage;
        }
        else if (this->Soft.Protection != MM_INVALID)
        {
            return PteDemandZero;
        }
        else //if (this->Long == 0)
        {
            NT_ASSERT(this->Long == 0);
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
        NT_ASSERT((PageFrameNumber & 0x2FFULL) == 0);
        if (Protect & MM_READWRITE) HardPde.Write = 1;
        if (Protect & MM_GLOBAL) HardPde.Global = 1;
        HardPde.PageFrameNumber = PageFrameNumber;
        this->Hard = HardPde;
    }

};

typedef PTE *PPTE;
typedef PDE *PPDE;

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
    return (PPTE)(((((ULONG)Address) >> 12) << 2) + PTE_BASE);
}

PPDE
FORCEINLINE
AddressToPde(PVOID Address)
{
    return (PPDE)(((((ULONG)Address) >> 22) << 2) + PTE_BASE);
}

PVOID
FORCEINLINE
PteToAddress(PPTE PtePointer)
{
    /* Use signed math */
    return (PVOID)((ULONG)PtePointer << 10);
}

PVOID
FORCEINLINE
PdeToAddress(PPDE PdePointer)
{
    /* Use signed math */
    return (PVOID)((ULONG)PdePointer << 20);
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

/* For i386: */
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
