
#include "Obp.hpp"

typedef ULONG_PTR EX_FAST_REF, *PEX_FAST_REF;

extern "C"
VOID
FASTCALL
ObInitializeFastReference (
    _Out_ PEX_FAST_REF FastRef,
    _In_ PVOID Object)
{
    __debugbreak();
}

extern "C"
PVOID
FASTCALL
ObFastReferenceObject (
    _Inout_ PEX_FAST_REF FastRef)
{
    __debugbreak();
    return NULL;
}

extern "C"
PVOID
FASTCALL
ObFastReferenceObjectLocked(
    _Inout_ PEX_FAST_REF FastRef)
{
    __debugbreak();
    return NULL;
}

extern "C"
VOID
FASTCALL
ObFastDereferenceObject (
    _Inout_ PEX_FAST_REF FastRef,
    _In_ PVOID Object)
{
    __debugbreak();
}

extern "C"
PVOID
FASTCALL
ObFastReplaceObject (
    _Inout_ PEX_FAST_REF FastRef,
    _In_ PVOID Object)
{
    __debugbreak();
    return NULL;
}
