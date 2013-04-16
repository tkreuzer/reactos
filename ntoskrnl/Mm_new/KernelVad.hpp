

#pragma once

#include "VadObject.hpp"

namespace Mm {

class KERNEL_VAD : public VAD_OBJECT
{
private:
    union
    {
        ULONG m_LongFlags;
        struct
        {
            ULONG NonPaged : 1;
        } m_Flags;
    };

public:

    VOID
    Initialize (
        VOID);

    NTSTATUS
    CreateInstance (
        _Out_ KERNEL_VAD** OutKernelVad);

    virtual
    const char*
    GetVadType() const;

    virtual
    NTSTATUS
    CommitPages (
        _In_ ULONG_PTR StartingVpn,
        _In_ ULONG_PTR EndingVpn,
        _In_ ULONG Protect);

    virtual
    NTSTATUS
    OnPageFault (
        PVOID FaultAddress,
        ULONG_PTR PteContext);


};

}; // namespace Mm
