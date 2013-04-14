
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
};

typedef struct _HARDWARE_PTE
{
    UINT64 Valid : 1;
    UINT64 Write : 1;
    UINT64 Owner : 1;
    UINT64 WriteThrough : 1;
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

//                                                         W C         W
//                                                   V W O T D A D L G C
static const HARDWARE_PTE ValidKernelPte          = {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0};
static const HARDWARE_PTE ValidKernelPde          = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const HARDWARE_PTE ValidLargePageKernelPde = {1,1,0,0,0,0,0,1,1,0,0,0,0,0,0};

class PTE
{
    union
    {
        HARDWARE_PTE Hard;
        SOFTWARE_PTE Soft;
        PROTOTYPE_PTE Proto;
    };

public:

#if 1 || DBG
    /* Copy constructor, for debugging */
    PTE (PTE& NewPte)
    {
        /* Check only real PTEs */
        if (this->IsRealPte())
        {
            if (NewPte.Hard.Valid)
            {
                /* Never overwrite a valid PTE */
                NT_ASSERT(this->Hard.Valid == FALSE);

                /* PPEs and PXEs (which are also PPEs) must not be global */
                NT_ASSERT(!IsRealPpe() || !NewPte.Hard.Global);
            }
        }

        this->Hard = NewPte.Hard;
    }

    /* We also need a default constructor now */
    inline PTE() {}
#endif

    inline
    bool
    IsRealPte ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PTE_BASE;
        return Offset < (PTE_TOP + 1 - PTE_BASE);
    }

    inline
    bool
    IsRealPde ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PDE_BASE;
        return Offset < (PDE_TOP + 1 - PDE_BASE);
    }

    inline
    bool
    IsRealPpe ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PPE_BASE;
        return Offset < (PPE_TOP + 1 - PPE_BASE);
    }

    inline
    bool
    IsRealPxe ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PXE_BASE;
        return Offset < (PXE_TOP + 1 - PXE_BASE);
    }

    inline
    bool
    IsValid ()
    {
        return Hard.Valid;
    }

    inline
    bool
    IsExecutable ()
    {
        return !Hard.NoExecute;
    }

    inline
    bool
    IsLargePage ()
    {
        return Hard.LargePage;
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
        Hard.Write = Writable;
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

    static inline
    PTE
    CreateValidKernelPte (
        _In_ PFN_NUMBER PageFrameNumber)
    {
        PTE Pte;
        Pte.Hard = ValidKernelPte;
        Pte.Hard.PageFrameNumber = PageFrameNumber;
        return Pte;
    }

    static inline
    PTE
    CreateValidKernelPde (
        _In_ PFN_NUMBER PageFrameNumber)
    {
        PTE Pte;
        Pte.Hard = ValidKernelPde;
        Pte.Hard.PageFrameNumber = PageFrameNumber;
        return Pte;
    }

    static inline
    PTE
    CreateValidKernelPpe (
        _In_ PFN_NUMBER PageFrameNumber)
    {
        return CreateValidKernelPde(PageFrameNumber);
    }

    static inline
    PTE
    CreateValidKernelPxe (
        _In_ PFN_NUMBER PageFrameNumber)
    {
        return CreateValidKernelPde(PageFrameNumber);
    }

    static inline
    PTE
    CreateValidLargePageKernelPde (
        _In_ PFN_NUMBER PageFrameNumber)
    {
        PTE Pte;
        NT_ASSERT((PageFrameNumber & 0x1ff) == 0);
        // The lowest PFN bit (Bit 12) is in fact PAT, but we ignore it for now
        Pte.Hard = ValidLargePageKernelPde;
        Pte.Hard.PageFrameNumber = PageFrameNumber;
        return Pte;
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
            if (Proto.Prototype)
                return PtePrototype;

        }
    }


};

typedef PTE PDE, PPE, PXE;
typedef PTE *PPTE, *PPDE, *PPPE, *PPXE;

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

PPTE
FORCEINLINE
AddressToPde(PVOID Address)
{
    ULONG64 Offset = (ULONG64)Address >> (PDI_SHIFT - 3);
    Offset &= 0x7FFFFFF << 3;
    return (PPDE)(PDE_BASE + Offset);
}

PPTE
FORCEINLINE
AddressToPpe(PVOID Address)
{
    ULONG64 Offset = (ULONG64)Address >> (PPI_SHIFT - 3);
    Offset &= 0x3FFFF << 3;
    return (PPPE)(PPE_BASE + Offset);
}

PPTE
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


}; // namespace Mm
