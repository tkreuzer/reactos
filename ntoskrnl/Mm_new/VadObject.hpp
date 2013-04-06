
#pragma once

#include "ntosbase.h"

namespace Mm {

typedef struct VAD_NODE
{
    /* For now use a simple LIST_ENTRY */
    LIST_ENTRY ListEntry;

    /* Starting and ending VPN - EndingVpn = StartingVpn + PageCount - 1 */
    ULONG StartingVpn;
    ULONG EndingVpn;
} VAD_NODE, *PVAD_NODE;

/* The abstract VAD_OBJECT base class */
class VAD_OBJECT
{
private:

    /* The node in the VAD table */
    VAD_NODE m_Node;

    /* Reference count tracing */
    LONG m_RefCount;

    /* The VAD table needs to access the VAD_NODE */
    friend class VAD_TABLE;

protected:

    inline
    VAD_OBJECT (
        VOID)
    {
        m_RefCount = 1;
    }

    inline
    PVOID
    GetBaseAddress (
        VOID)
    {
        return reinterpret_cast<PVOID>(m_Node.StartingVpn << PAGE_SHIFT);
    }

    inline
    LONG
    AddRef (
        VOID)
    {
        return InterlockedIncrement(&m_RefCount);
    }

public:

    virtual
    NTSTATUS
    OnPageFault (
        PVOID FaultAddress,
        ULONG_PTR PteContext) = 0;


};

typedef class VAD_OBJECT* PVAD_OBJECT;


}; // namespace Mm
