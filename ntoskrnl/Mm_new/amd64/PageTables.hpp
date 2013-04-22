
#pragma once

namespace Mm {

#define MI_PAGING_LEVELS 4

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
    UINT64 ActiveType : 2;
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
    UINT64 SoftType : 2;
    UINT64 Reserved : 46;
    UINT64 Protection : 5;
    UINT64 NoExecuteOverlay : 1;
} SOFTWARE_PTE, *PSOFTWARE_PTE;

typedef struct _PAGEFILE_PTE
{
    UINT64 MustBeZero : 1;
    UINT64 HardwareState : 8;
    UINT64 CopyOnWrite : 1;
    UINT64 Prototype : 1;
    UINT64 Transition : 1;
    UINT64 PageFileIndex : 36;
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

//                                                         W C         C
//                                                   V W O T D A D L G W
static const HARDWARE_PTE ValidPte                = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const HARDWARE_PTE ValidPde                = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const HARDWARE_PTE ValidLargePagePde       = {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0};

extern const HARDWARE_PTE ProtectToPte[32] ;

class PTE_COMMON
{
protected:
    union
    {
        HARDWARE_PTE Hard;
        SOFTWARE_PTE Soft;
        PROTOTYPE_PTE Proto;
        ULONG64 Long;
    };

#if 1 || DBG
    /* Disable direct write */
    PTE_COMMON (PTE_COMMON& NewPte);
    inline PTE_COMMON () {}
#endif

public:

    inline
    bool
    IsEmpty ()
    {
        return (Long == 0);
    }

    inline
    bool
    IsValid ()
    {
        return Hard.Valid;
    }

    inline
    PFN_NUMBER
    GetPageFrameNumber (
        VOID)
    {
        return Hard.PageFrameNumber;
    }

    inline
    VOID
    SetPageFrameNumber (
        _In_ PFN_NUMBER PageFrameNumber)
    {
        NT_ASSERT(!Proto.Prototype);
        Hard.PageFrameNumber = PageFrameNumber;
    }

    inline
    ULONG
    GetProtection ()
    {
        ULONG Protect = MM_NOACCESS;
        if (Hard.Valid) Protect |= MM_READONLY;
        if (Hard.Write) Protect |= MM_READWRITE;
        if (!Hard.NoExecute) Protect |= MM_EXECUTE;
        if (Hard.Global) Protect |= MM_GLOBAL;
        if (Hard.LargePage) Protect |= MM_LARGEPAGE;
        return Protect;
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
    IsExecutable ()
    {
        return !Hard.NoExecute;
    }

    inline
    bool
    IsWritable ()
    {
        return Hard.Write;
    }

    inline
    void
    SetWritable (
        bool Writable)
    {
        this->Hard.Write = Writable;
    }

    inline
    VOID
    MakeValidPte (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ ULONG Protect)
    {
        HARDWARE_PTE HardPte = ValidPte;
        NT_ASSERT(!(Protect & MM_LARGEPAGE));
        if (Protect & MM_READWRITE) HardPte.Write = 1;
        if (!(Protect & MM_EXECUTE)) HardPte.NoExecute = 1;
        if (Protect & MM_GLOBAL) HardPte.Global = 1;
        if (Protect & MM_USER) HardPte.Owner = 1;
        HardPte.PageFrameNumber = PageFrameNumber;
        this->Hard = HardPte;
    }

    inline
    VOID
    MakeDemandZeroPte (
        _In_ ULONG Protect)
    {
        HARDWARE_PTE HardPte = ValidPte;
        NT_ASSERT(Protect & MM_READWRITE);
        NT_ASSERT(!(Protect & MM_MAPPED));
        NT_ASSERT(!(Protect & MM_LARGEPAGE));
        if (Protect & MM_READWRITE) HardPte.CopyOnWrite = 1;
        if (!(Protect & MM_EXECUTE)) HardPte.NoExecute = 1;
        if (Protect & MM_GLOBAL) HardPte.Global = 1;
        if (Protect & MM_USER) HardPte.Owner = 1;
        HardPte.PageFrameNumber = GlobalZeroPfn;
        this->Hard = HardPte;
    }

    inline
    VOID
    MakeProtoPte (
        _In_ PPROTOTYPE Prototype)
    {
        /// \todo IMPLEMENT ME
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
    UpdateProtection (
        _In_ ULONG Protect)
    {
        NT_ASSERT(FALSE);
    }

    inline
    PTE_TYPE
    GetPteType (
        VOID)
    {
        if (Hard.Valid)
        {
            if (Hard.CopyOnWrite)
            {
                if (Hard.PageFrameNumber == GlobalZeroPfn)
                    return PteDemandZero;
                else
                    return PteCopyOnWrite;
            }
            else
                return PteValid;
        }
        else
        {
            if (Long == 0)
                return PteEmpty;
            if (Proto.Prototype)
                return PtePrototype;

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
        return Hard.LargePage;
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
        Hard = HardPde;
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
        Hard = HardPde;
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
        Hard = HardPpe;
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
        Hard = HardPxe;
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

enum FAULT_REASON
{
    FaultReasonPrivilegeViolation,
    FaultReasonNoExecute,
    FaultReasonProtectionViolation,
};

inline
FAULT_REASON
GetFaultReason (
    PVOID Address,
    PAGE_FAULT_ERROR_CODE ErrorCode)
{
    /* First check for a privilege violation */
    if ((ErrorCode & PFEC_USER) && (Address > MmHighestUserAddress))
    {
        return FaultReasonPrivilegeViolation;
    }

    if (ErrorCode & PFEC_PROTECT)
    {
        if (ErrorCode & PFEC_INSTRUCTION_FETCH)
        {
            return FaultReasonNoExecute;
        }
        else
        {
            /* This must be a write operation */
            NT_ASSERT(ErrorCode & PFEC_WRITE);
            return FaultReasonProtectionViolation;
        }
    }
    else
    {
        //if (
    }
}

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

#define VpnToPxe(Vpn) AddressToPxe(VpnToAddress(Vpn))
#define VpnToPpe(Vpn) AddressToPpe(VpnToAddress(Vpn))
#define VpnToPde(Vpn) AddressToPde(VpnToAddress(Vpn))
#define VpnToPte(Vpn) AddressToPte(VpnToAddress(Vpn))

}; // namespace Mm
