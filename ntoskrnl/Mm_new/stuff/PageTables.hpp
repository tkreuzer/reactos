
#if DBG
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
    inline PTE () {}

    inline
    bool
    IsRealPpe ()
    {
        ULONG_PTR Offset = reinterpret_cast<ULONG_PTR>(this) - PPE_BASE;
        return Offset < (PPE_TOP + 1 - PPE_BASE);
    }
#endif

enum FAULT_TYPE
{
    NoExecuteFault,
    CopyOnWriteFault,
    PrivilegeViolationFault,
    PageNotPresentFault,
    TransitionPteFault,
    DemandZeroFault,
};

#if 0
    inline
    FAULT_TYPE
    GetFaultType (
        _In_ UCHAR ErrorCode)
    {
        if (this->Hard.Valid)
        {
            NT_ASSERT((ErrorCode & PFEC_PROTECT) != 0);

            if (ErrorCode & PFEC_INSTRUCTION_FETCH)
            {
                return NoExecuteFault;
            }

            if (ErrorCode & PFEC_WRITE)
            {
                if (this->Hard.CopyOnWrite)
                    return CopyOnWriteFault;
                else
                    return AccessViolationFault;
            }
            else
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
        else if (this->Long == 0)
        {
            return PteEmpty;
        }
        else
        {
            if (this->PageFile.PageFileIndex != 0)
            {
                return PtePageFile;
            }
            else if (this->PageFile.CopyOnWrite)
            {
                return PteDemandZero;
            }
            else
            {
                NT_ASSERT(this->Hard.NoExecute == 1);
                return PteNoAccess;
            }
        }
    }

    inline
    FAULT_TYPE
    GetFaultType (
        _In_ UCHAR ErrorCode)
    {
        /* Check if the fault was a protection violation */
        if (ErrorCode & PFEC_PROTECT)
        {
            /* Only 3 possibilities here: 1) User mode code accessing kernel
               mode memory (this has already been checked), 2) Executing a
               no-execute page and 3) Writing a read-only page. */

            /* Check if it was due to an instruction fetch */
            if (ErrorCode & PFEC_INSTRUCTION_FETCH)
            {
                /* This can only be a no-execute fault */
                return NoExecuteFault;
            }
            else
            {
                /* This must be a write operation */
                NT_ASSERT(ErrorCode & PFEC_WRITE);

                /* Check if the PTE is writable now */
                if (this->Hard.Write)
                {
                    /* The fault was probably a CopyOnWrite fault and has been
                       resolved already by another thread */
                    return ResolvedFault;
                }

                /* Check if we have a CopyOnWrite PTE */
                if (this->Hard.CopyOnWrite)
                    return CopyOnWriteFault;

                /* Otherwise this must be an access violation */
                return AccessViolationFault;
            }
        }
        else
        {
            /* Check if the page is valid now */
            if (PteValue.IsValid())
                return ResolvedFault;

            if (this->Long == 0)
                return AccessViolationFault;

            if (this->Soft.Prototype)
                return PrototypePteFault;

            if (this->Soft.Transition)
                return TransitionPteFault;

            if (this->PageFile.PageFileIndex != 0)
                return PageFileFault;

            if (this->PageFile.CopyOnWrite)
                return DemandZeroFault;

            NT_ASSERT(this->Hard.NoExecute == 1);
            return PteNoAccess;
        }
    }
#endif

#if 0
enum FAULT_REASON
{
    FaultReasonPrivilegeViolation,
    FaultReasonNoExecute,
    FaultReasonProtectionViolation,
};

inline
FAULT_REASON
GetFaultReason (
    _In_ PVOID Address,
    _In_ PTE PteValue,
    _In_ UCHAR ErrorCode)
{
    /* First check for a privilege violation */
    if ((ErrorCode & PFEC_USER) && (Address > MmHighestUserAddress))
    {
        /* Should not happen, since this is checked earlier */
        NT_ASSERT(FALSE);
        return FaultReasonPrivilegeViolation;
    }

    /* Check if the fault was a protection violation */
    if (ErrorCode & PFEC_PROTECT)
    {
        /* Check if it was due to an instruction fetch */
        if (ErrorCode & PFEC_INSTRUCTION_FETCH)
        {
            return NoExecuteFault;
        }
        else
        {
            /* This must be a write operation */
            NT_ASSERT(ErrorCode & PFEC_WRITE);

            /* Check if we have a CopyOnWrite PTE */
            if (PteValue.IsCopyOnWrite())
                return CopyOnWriteFault;

            /* Check if the PTE is writable */
            if (PteValue.IsWritable())
                return ResolvedFault;

            /* Otherwise this must be an access violation */
            return AccessViolationFault;
        }
    }
    else
    {
        /* Check if the page is valid now */
        if (PteValue.IsValid())
            return ResolvedFault;

        if (PteValue.Is
    }
}
#endif

PTE
FORCEINLINE
InterlockedCompareExchangePte (
    _Inout_ PPTE DestinationPte,
    _In_ PTE ExchangePte,
    _In_ PTE ComparandPte)
{
    LONG64 Result;

    Result = InterlockedCompareExchange64(reinterpret_cast<PLONG64>(DestinationPte),
                                          *reinterpret_cast<PLONG64>(&ExchangePte),
                                          *reinterpret_cast<PLONG64>(&ComparandPte));
    return *reinterpret_cast<PPTE>(&Result);
}
