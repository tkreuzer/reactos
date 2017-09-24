/*!

    \file Ob/RefObject.hpp

    \brief Implements the REF_OBJECT base template class

    \copyright Released under the terms of the GNU GPL v2

    \author Timo Kreuzer (timo.kreuzer@reactos.org)

    The purpose of this class is to provide a uniform way of handling object
    references, without the requirement of using virtual members.
    A set of Secure* methods provide means for secure pointer reference.

*/

#pragma once

#include "ntosbase.h"

class REF_OBJECT_CORE
{
private:
    /* Empiric data shows that 27 is a good number to minimize conflicts */
    static const ULONG LOCK_ARRAY_SIZE = 27;
    static EX_PUSH_LOCK s_SecureReferenceLock[LOCK_ARRAY_SIZE] = { 0 };

protected:

    LONG m_RefCount;

    static
    PVOID
    SecureReferenceObject (
        _In_ PVOID* ObjectPointer);

    _Success_(return!=FALSE)
    static
    BOOLEAN
    SecureSetObjectPointer (
        _Out_ PVOID* ObjectPointer,
        _In_ PVOID Object);

    static
    VOID
    SecureDeleteObjectPointer (
        _Out_ PVOID* ObjectPointer);

};

REF_OBJECT_CORE*
REF_OBJECT_CORE::SecureReferenceObject (
    _In_ PVOID* ObjectPointer)
{
    REF_OBJECT_CORE* RefObject;
    KIRQL OldIrql;
    ULONG LockIndex;

    /* Calculate the lock index */
    LockIndex = reinterpret_cast<ULONG_PTR>(ObjectPointer) % LOCK_ARRAY_SIZE;

    /* Quick check without lock first */
    if (*ObjectPointer == NULL)
    {
        /* Currently we cannot reference it */
        return NULL;
    }

    /* Acquire the lock. We only need a shared lock, since we don't modify
       the protected variable (the object pointer) and the only one who
       does this in a way that affects this function (setting the pointer to
       NULL) is done with an exclusive lock held. */
    OldIrql = ExAcquireSpinLockShared(&s_SecureReferenceLock[LockIndex]);

    /* Read the object pointer and check again */
    RefObject = reinterpret_cast<REF_OBJECT_CORE*>(*ObjectPointer);
    if (RefObject != NULL)
    {
        /* Reference the object */
        InterlockedIncrement(&RefObject->m_RefCount);
    }

    /* Release the spin lock */
    ExReleaseSpinLockShared(&s_SecureReferenceLock[LockIndex], OldIrql);

    return RefObject;
}

_Success_(return!=FALSE)
BOOLEAN
REF_OBJECT_CORE::SecureSetObjectPointer (
    _Out_ PVOID* ObjectPointer,
    _In_ PVOID Object)
{
    PVOID OldValue;

    /* Try to atomically update the pointer from NULL */
    OldValue = InterlockedCompareExchangePointer(ObjectPointer,
                                                 Object,
                                                 NULL);

    return (OldValue == NULL);
}

VOID
REF_OBJECT_CORE::SecureDeleteObjectPointer (
    _Out_ PVOID* ObjectPointer)
{
    KIRQL OldIrql;
    ULONG LockIndex;

    /* Calculate the lock index */
    LockIndex = reinterpret_cast<ULONG_PTR>(ObjectPointer) % LOCK_ARRAY_SIZE;

    /* Acquire the lock. This guarantees that no other thread can get a new
       reference on the object in the meanwhile */
    OldIrql = ExAcquireSpinLockExclusive(&s_SecureReferenceLock[LockIndex]);

    /* Delete the object pointer */
    *ObjectPointer = NUL;

    /* Release the spin lock */
    ExReleaseSpinLockShared(&s_SecureReferenceLock[LockIndex], OldIrql);
}

template<class _DerivedClass>
class REF_OBJECT : public REF_OBJECT_CORE
{
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
            _DerivedClass* that = static_cast<_DerivedClass*>(this);
            delete that;
        }

        return RefCount;
    }

    static inline
    _Class*
    SecureReferenceObject (
        _In_ PVOID* ObjectPointer);
    {
        REF_OBJECT_CORE* Object;

        Object = REF_OBJECT_CORE::SecureReferenceObject(ObjectPointer));
        return reinterpret_cast<_Class*>(Object);
    }

};

