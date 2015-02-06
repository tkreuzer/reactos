
#pragma once

#include "Obp.hpp"

namespace Ob {

#ifdef _WIN64
#define FAST_REF_BITS 4
#define FAST_REF_MASK ((ULONG_PTR)0xF)
#else
#define FAST_REF_BITS 3
#define FAST_REF_MASK ((ULONG_PTR)0x7)
#endif

typedef class FAST_REF *PFAST_REF;

class FAST_REF
{
    union
    {
        PVOID _Pointer;
        ULONG_PTR _Value;
        LONG_PTR _RefCount : FAST_REF_BITS;
    };

    inline
    POBJECT
    GetObject (
        VOID)
    {
        return reinterpret_cast<POBJECT>(_Value & ~FAST_REF_MASK);
    }

public:

    inline
    FAST_REF (
        _In_opt_ POBJECT Object = NULL)
    {
        if (Object != NULL)
        {
            NT_ASSERT((reinterpret_cast<ULONG_PTR>(Object) & FAST_REF_MASK) == 0);
            _Value = reinterpret_cast<ULONG_PTR>(Object) | FAST_REF_MASK;
            Object->AddRef(FAST_REF_MASK);
        }
        else
        {
            _Pointer = NULL;
        }
    }

    POBJECT
    ReferenceObject (
        VOID);

    POBJECT
    ReferenceObjectLocked (
        VOID);

    VOID
    DereferenceObject (
        _In_ POBJECT NewObject);

    POBJECT
    ReplaceObject (
        _In_opt_ POBJECT NewObject);

};

}; // namespace Ob
