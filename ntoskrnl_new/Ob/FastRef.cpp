
#include "Obp.hpp"

namespace Ob {

POBJECT
FAST_REF::ReferenceObject (
    VOID)
{
    FAST_REF OldValue, NewValue, Compare;
    POBJECT Object;

    /* Get the current value and start the exchange loop */
    OldValue = *this;
    do
    {
        /* Check if the object is NULL or in an intermediate state */
        if (OldValue._RefCount == 0)
        {
            return NULL;
        }

        /* Setup the new value, by decrementing the reference count */
        NewValue._Value = OldValue._Value - 1;

        /* Try to atomically exchange the value with the new value */
        Compare = OldValue;
        OldValue._Pointer = InterlockedCompareExchangePointer(&_Pointer,
                                                              NewValue._Pointer,
                                                              Compare._Pointer);

        /* Repeat until we succeeded */
    } while (OldValue._Value != Compare._Value);

    /* Get the object */
    Object = NewValue.GetObject();

    /* Check if the reference count is still above 0 */
    if (NewValue._RefCount > 0)
    {
        /* We are done, return the object */
        return Object;
    }

    /* We consumed all fast references, move references to the object */
    Object->AddRef(FAST_REF_MASK);

    /* The new value is now the old value */
    OldValue = NewValue;

    /* Setup a fully referenced new value and start the exchange loop */
    NewValue._Value = OldValue._Value | FAST_REF_MASK;

    /* Try to atomically exchange the value with the new value */
    Compare = OldValue;
    OldValue._Pointer = InterlockedCompareExchangePointer(&_Pointer,
                                                          NewValue._Pointer,
                                                          Compare._Pointer);

    /* Check if that failed */
    if (OldValue._Value != Compare._Value)
    {
        /* We have 2 scenarios here: 1. The object is still the same, but it got
           dereferenced. This means _RefCount is now > 0 and we are in a "good"
           state again, so we don't need the additional references anymore,
           and we still expect another dereference operation next.
           2. The object got exchanged. Whether it was exchanged while _RefCount
           was 0 or has been dereferenced already is not relevant. The number
           of references on the fast reference have been removed from the
           object. The additional references we acquired here were not taken
           into account. So we simply drop all the references again. */
        Object->Release(FAST_REF_MASK);
    }

    /* Return the object. In case that the object got replaced, we still
       return the previous object, which we already own a reference on.
       This is legitimate, since we cannot prevent the object from being
       replaced after this point anyway, so it doesn't make a difference. */
    return Object;
}

POBJECT
FAST_REF::ReferenceObjectLocked (
    VOID)
{
    POBJECT Object;

    /* The caller must own a shared or exclusive lock that prevents the object
       from being finally dereferenced and deleted (the same lock must be
       acquired exclusively before the object gets dereferenced, but after the
       fast reference has been dereferenced). So it's safe to just get the
       object and add a reference. */
    Object = GetObject();
    Object->AddRef();
    return Object;
}

VOID
FAST_REF::DereferenceObject (
    _In_ POBJECT Object)
{
    FAST_REF OldValue, NewValue, Compare;

    /* Get the current value and start the exchange loop */
    OldValue = *this;
    do
    {
        /* Check, if the object has been replaced or the reference count
           wrapped when referencing the object */
        if ((OldValue.GetObject() != Object) ||
            (OldValue._RefCount == FAST_REF_MASK))
        {
            /* If the object was replaced, all it's references, except the ones
               taken from the fast reference have already been released. So
               we release our reference as well. If the reference count on the
               fast reference wrapped, we got a full number of additional
               references on the object, so we just keep releasing them. The
               additional references will get removed, once the object is
               replaced. */
            Object->Release();
            return;
        }

        /* Setup the new value, by incrementing the reference count */
        NewValue._Value = OldValue._Value + 1;

        /* Try to atomically exchange the value with the new value */
        Compare = OldValue;
        OldValue._Pointer = InterlockedCompareExchangePointer(&_Pointer,
                                                              NewValue._Pointer,
                                                              Compare._Pointer);

        /* Repeat until we succeeded */
    } while (OldValue._Value != Compare._Value);
}

POBJECT
FAST_REF::ReplaceObject (
    _In_opt_ POBJECT NewObject)
{
    FAST_REF OldValue;
    POBJECT OldObject;

    /* Set up a new value. This will add references to the object */
    FAST_REF NewValue(NewObject);

    /* Exchange the fast reference with the new value */
    OldValue._Pointer = InterlockedExchangePointer(&_Pointer, NewValue._Pointer);

    /* Get the old object */
    OldObject = OldValue.GetObject();

    /* Check if there were references on the old object */
    if (OldValue._RefCount > 0)
    {
        /* Release the references from the object */
        NT_ASSERT(OldObject != NULL);
        OldObject->Release(OldValue._RefCount);
    }

    return OldObject;
}

extern "C" {

/*! \name ObInitializeFastReference
 *
 *  \brief Initialized a fast reference.
 *
 *  \param [out] FastRef
 *      Pointer to an EX_FAST_REF union, that is to be initialized.
 *
 *  \param [in] Object
 *      Pointer to an arbitrary object, that the fast reference should track.
 *
 *  \remarks
 *      The function sets the Object member to point to the given objects and
 *      initialized the RefCnt field to binary all 1's (-1). The object must be
 *      aligned to 8 bytes on x86 and to 16 bytes on x64.
 */
VOID
FASTCALL
ObInitializeFastReference (
    _Out_ PFAST_REF FastRef,
    _In_opt_ POBJECT Object)
{
    NT_ASSERT(FastRef != NULL);
    *FastRef = FAST_REF(Object);
}

/*! \name ObFastReferenceObject
 *
 *  \brief
 *
 *  \param [out] FastRef
 *      Pointer to an EX_FAST_REF that is to be used to reference the related
 *      object.
 *
 *  \return
 *      Pointer to the referenced object on success. NULL on failire (when the
 *      number of references exceeds the possible maximum).
 */
PVOID
FASTCALL
ObFastReferenceObject (
    _Inout_ PFAST_REF FastRef)
{
    NT_ASSERT(FastRef != NULL);
    return FastRef->ReferenceObject();
}

PVOID
FASTCALL
ObFastReferenceObjectLocked (
    _Inout_ PFAST_REF FastRef)
{
    NT_ASSERT(FastRef != NULL);
    return FastRef->ReferenceObjectLocked();
}

/*! \name ObFastDereferenceObject
 *
 *  \brief
 *
 *  \param [out] FastRef
 *      Pointer to an EX_FAST_REF that is to be used to dereference the related
 *      object.
 *
 *  \param [in] Object
 *
 *  \return
 *      Pointer to the referenced object on success. NULL on failire (when the
 *      number of references exceeds the possible maximum).
 */
VOID
FASTCALL
ObFastDereferenceObject (
    _Inout_ PFAST_REF FastRef,
    _In_ POBJECT Object)
{
    NT_ASSERT(FastRef != NULL);
    FastRef->DereferenceObject(Object);
}

PVOID
FASTCALL
ObFastReplaceObject (
    _Inout_ PFAST_REF FastRef,
    _In_opt_ POBJECT NewObject)
{
    NT_ASSERT(FastRef != NULL);
    return FastRef->ReplaceObject(NewObject);
}

} // extern "C"

}; // namespace Ob
