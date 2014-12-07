
#include "Kep.hpp"

extern "C" {

VOID
KiSystemService (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
KiZwSystemService (
    VOID)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
KeAddSystemServiceTable (
    _In_ PULONG_PTR Base,
    _In_opt_ PULONG Count,
    _In_ ULONG Limit,
    _In_ PUCHAR Number,
    _In_ ULONG Index)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
KeRemoveSystemServiceTable (
    _In_ ULONG Index)
{
    __debugbreak();
    return FALSE;
}

//; ??? @ extern -arch=i386 KeServiceDescriptorTable

}; // extern "C"
