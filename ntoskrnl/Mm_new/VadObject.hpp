/*!

    \file VadObject.hpp

    \brief Contains the definition of the VAD_OBJECT class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"

namespace Mm {

typedef struct VAD_NODE
{
    /* For now use a simple LIST_ENTRY */
    LIST_ENTRY ListEntry;

    /* Starting and ending VPN (EndingVpn = StartingVpn + PageCount - 1) */
    ULONG_PTR StartingVpn;
    ULONG_PTR EndingVpn;
} VAD_NODE, *PVAD_NODE;

typedef struct _VAD_FLAGS
{
    BOOLEAN Inserted : 1;
} VAD_FLAGS;

/* The VAD_OBJECT base class */
class VAD_OBJECT : private VAD_NODE
{
private:
    /* Reference count */
    LONG m_RefCount;

    EX_PUSH_LOCK m_Lock;
    VAD_FLAGS m_Flags;

    /* The type of VAD */
    static const UCHAR m_Dummy;

    inline
    VOID
    AcquireLock (
        VOID);

    inline
    VOID
    ReleaseLock (
        VOID);

    /* The VAD table needs to access the VAD_NODE */
    friend class VAD_TABLE;

protected:
    ULONG m_Protect;

protected:

    inline
    VAD_OBJECT (
        VOID)
    {
        m_RefCount = 1;
        InitializeListHead(&ListEntry);
    }

    virtual
    ~VAD_OBJECT (
        VOID)
    {
    }

public:

    static
    NTSTATUS
    CreateInstance (
        _Out_ VAD_OBJECT** OutVadObject,
        _In_ ULONG Protect);

    inline
    ULONG_PTR
    GetStartingVpn (
        VOID)
    {
        return StartingVpn;
    }

    inline
    ULONG_PTR
    GetEndingVpn (
        VOID)
    {
        return EndingVpn;
    }

    inline
    PVOID
    GetBaseAddress (
        VOID)
    {
        return reinterpret_cast<PVOID>(StartingVpn << PAGE_SHIFT);
    }

    inline
    ULONG
    GetProtect (
        VOID)
    {
        return m_Protect;
    }

    inline
    LONG
    AddRef (
        VOID)
    {
        return InterlockedIncrement(&m_RefCount);
    }

    inline
    LONG
    Release (
        VOID)
    {
        LONG NewRefCount = InterlockedDecrement(&m_RefCount);
        if (NewRefCount == 0)
        {
            delete this;
        }
        return NewRefCount;
    }

    virtual
    ULONG
    GetMemoryType (
        VOID);

    virtual
    const char*
    GetVadType (
        VOID) const;

    virtual
    NTSTATUS
    CommitPages (
        _In_ ULONG_PTR StartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG Protect);


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
