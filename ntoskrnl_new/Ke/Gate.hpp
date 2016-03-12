
#pragma once

#include "DispatcherObject.hpp"

namespace Ke {

typedef class GATE *PGATE;

class GATE : public DISPATCHER_OBJECT
{
public:

    inline
    void*
    operator new (
        _In_ size_t Size) throw()
    {
        return ExAllocatePoolWithTag(NonPagedPool, Size, 'aGeK');
    }

    inline
    void
    operator delete (
        _In_ void *Object) throw()
    {
        return ExFreePoolWithTag(Object, 'aGeK');
    }

    inline
    GATE (
        _In_ BOOLEAN State)
        : DISPATCHER_OBJECT(GateObject, sizeof(GATE), FALSE, State)
    {
    }

    VOID
    Wait (
        VOID);

    VOID
    Signal (
        VOID);

};


}; // namespace Ke
