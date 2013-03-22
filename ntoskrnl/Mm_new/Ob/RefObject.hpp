/*!

    \file Ob/RefObject.hpp

    \brief Implements the REF_OBJECT base class template

    \copyright Released under the terms of the GNU GPL v2

    \author Timo Kreuzer (timo.kreuzer@reactos.org)

    The purpose of this class is to provide a uniform way of handling object
    references, without the requirement of using virtual members.

    Derived classes must either make their destructor (if any) public (this
    will still not allow public use of delete for this object) or declare
    this class as a friend (for convenience the class "super" is declared,
    so you can use "friend super;").

*/

#pragma once

#include "ntosbase.h"

class REF_OBJECT_CORE
{
protected:
    LONG m_RefCount;

    inline
    REF_OBJECT_CORE (
        VOID) : m_RefCount(1)
    {
    }

    inline
    ~REF_OBJECT_CORE (
        VOID)
    {
        NT_ASSERT(m_RefCount == 0);
    }
};

template<class _DerivedClass, ULONG _PoolTag>
class REF_OBJECT : private REF_OBJECT_CORE
{
protected:

    typedef class REF_OBJECT super;

    inline
    void*
    operator new(size_t Size)
    {
        return ExAllocatePoolWithTag(PagedPool, Size, _PoolTag);
    }

    inline
    void
    operator delete(void* P)
    {
        return ExFreePoolWithTag(P, _PoolTag);
    }

public:

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
        LONG RefCount = InterlockedDecrement(&m_RefCount);
        if (RefCount == 0)
        {
            _DerivedClass* This = static_cast<_DerivedClass*>(this);
            delete This;
        }

        return RefCount;
    }

};

