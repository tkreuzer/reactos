
#pragma once

#include "ntosbase.h"

namespace Mm {

typedef struct VAD_NODE
{
    /* For now use a simple LIST_ENTRY */
    LIST_ENTRY ListEntry;

    /* Starting and ending VPN - EndingVpn = StartingVpn + PageCount - 1 */
    ULONG_PTR StartingVpn;
    ULONG_PTR EndingVpn;
} VAD_NODE, *PVAD_NODE;

/* The abstract VAD_OBJECT base class */
class VAD_OBJECT
{
private:

    /* The node in the VAD table */
    VAD_NODE m_Node;

    /* Reference count */
    LONG m_RefCount;

    /* The type of VAD */
    static const UCHAR m_Dummy;

    /* The VAD table needs to access the VAD_NODE */
    friend class VAD_TABLE;

protected:

    inline
    VAD_OBJECT (
        VOID)
    {
        m_RefCount = 1;
        InitializeListHead(&m_Node.ListEntry);
    }

public:

    inline
    ULONG_PTR
    GetStartingVpn (
        VOID)
    {
        return m_Node.StartingVpn;
    }

    inline
    ULONG_PTR
    GetEndingVpn (
        VOID)
    {
        return m_Node.EndingVpn;
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

    inline
    VAD_OBJECT*
    GetVadObject ()
    {
        return this;
    }

    virtual
    const char*
    GetVadType () const = 0;

#if 0
    virtual
    NTSTATUS
    OnPageFault (
        PVOID FaultAddress,
        ULONG_PTR PteContext) = 0;
#endif
};

typedef class VAD_OBJECT* PVAD_OBJECT;


}; // namespace Mm
