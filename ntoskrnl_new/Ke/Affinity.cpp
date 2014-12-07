
#include "Affinity.hpp"

extern "C" {

/*!

    \ref WDK 10 / ntosp.h
*/

// ntosp.h
VOID
NTAPI
KeInitializeAffinityEx (
    _Out_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
}

// ntosp.h
ULONG
NTAPI
KeQueryActiveProcessorAffinity  (
    _Out_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeIsEmptyAffinityEx (
    _In_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeIsEqualAffinityEx (
    _In_ PKAFFINITY_EX Affinity1,
    _In_ PKAFFINITY_EX Affinity2)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeIsSubsetAffinityEx (
    _In_ PKAFFINITY_EX Affinity1,
    _In_ PKAFFINITY_EX Affinity2)
{
    __debugbreak();
    return 0;
}

// ntosp.h
ULONG
NTAPI
KeCountSetBitsAffinityEx (
    _In_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
    return 0;
}

// ntosp.h
ULONG
NTAPI
KeFindFirstSetLeftAffinityEx (
    _In_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
    return 0;
}

// ntosp.h
ULONG
NTAPI
KeFindFirstSetRightAffinityEx (
    _In_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeCheckProcessorAffinityEx (
    _In_ PKAFFINITY_EX Affinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
    return 0;
}

// ntosp.h
VOID
NTAPI
KeAddProcessorAffinityEx (
    _Inout_ PKAFFINITY_EX Affinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
KeRemoveProcessorAffinityEx (
    _Inout_ PKAFFINITY_EX Affinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
}

// ntosp.h
LOGICAL
NTAPI
KeInterlockedSetProcessorAffinityEx (
    _Inout_ PKAFFINITY_EX Affinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeInterlockedClearProcessorAffinityEx (
    _Inout_ PKAFFINITY_EX Affinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
    return 0;
}

// ntosp.h
VOID
NTAPI
KeCopyAffinityEx (
    _Out_ PKAFFINITY_EX Dest,
    _In_ PKAFFINITY_EX Source)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
KeComplementAffinityEx (
    _Out_ PKAFFINITY_EX Result,
    _In_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
}

// ntosp.h
LOGICAL
NTAPI
KeAndAffinityEx (
    _In_ PKAFFINITY_EX Affinity1,
    _In_ PKAFFINITY_EX Affinity2,
    _Out_opt_ PKAFFINITY_EX Result)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeOrAffinityEx (
    _In_ PKAFFINITY_EX Affinity1,
    _In_ PKAFFINITY_EX Affinity2,
    _Out_opt_ PKAFFINITY_EX Result)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeSubtractAffinityEx (
    _In_ PKAFFINITY_EX Affinity1,
    _In_ PKAFFINITY_EX Affinity2,
    _Out_opt_ PKAFFINITY_EX Result)
{
    __debugbreak();
    return 0;
}


/// Group Affinity

// ntosp.h
VOID
NTAPI
KeProcessorGroupAffinity (
    _Out_ PGROUP_AFFINITY GroupAffinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
}

// ntosp.h
KAFFINITY
NTAPI
KeQueryGroupAffinityEx (
    _In_ PKAFFINITY_EX Affinity,
    _In_ USHORT GroupNumber)
{
    __debugbreak();
    return 0;
}

// ntosp.h
ULONG
NTAPI
KeCountSetBitsGroupAffinity (
    _In_ PGROUP_AFFINITY GroupAffinity)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeIsSingleGroupAffinityEx (
    _In_ PKAFFINITY_EX Affinity,
    _Out_opt_ PUSHORT Group)
{
    __debugbreak();
    return 0;
}

// ntosp.h
LOGICAL
NTAPI
KeCheckProcessorGroupAffinity (
    _In_ PGROUP_AFFINITY GroupAffinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
    return 0;
}

// ntosp.h
NTSTATUS
NTAPI
KeFirstGroupAffinityEx (
    _Out_ PGROUP_AFFINITY GroupAffinity,
    _In_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
ULONG
NTAPI
KeFindFirstSetLeftGroupAffinity (
    _In_ PGROUP_AFFINITY GroupAffinity)
{
    __debugbreak();
    return 0;
}

// ntosp.h
ULONG
NTAPI
KeFindFirstSetRightGroupAffinity (
    _In_ PGROUP_AFFINITY GroupAffinity)
{
    __debugbreak();
    return 0;
}



// ntosp.h
VOID
NTAPI
KeAddProcessorGroupAffinity (
    _Inout_ PGROUP_AFFINITY GroupAffinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
KeRemoveProcessorGroupAffinity (
    _Inout_ PGROUP_AFFINITY GroupAffinity,
    _In_ ULONG ProcIndex)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
KeAddGroupAffinityEx (
    _Inout_ PKAFFINITY_EX Affinity,
    _In_ USHORT GroupNumber,
    _In_ KAFFINITY ProcessorMask)
{
    __debugbreak();
}

// ntosp.h
VOID
NTAPI
KeRemoveGroupAffinityEx (
    _Inout_ PKAFFINITY_EX Affinity,
    _In_ USHORT GroupNumber,
    _In_ KAFFINITY ProcessorMask)
{
    __debugbreak();
}

// ntosp.h
LOGICAL
NTAPI
KeAndGroupAffinityEx (
    _In_ PKAFFINITY_EX Affinity,
    _In_ PGROUP_AFFINITY GroupAffinity,
    _Out_opt_ PGROUP_AFFINITY Result)
{
    __debugbreak();
    return 0;
}

// ntosp.h
VOID
NTAPI
KeInitializeEnumerationContext (
    _Out_ PKAFFINITY_ENUMERATION_CONTEXT Context,
    _In_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
}

//@ stub KeInitializeEnumerationContextFromAffinity

// ntosp.h
VOID
NTAPI
KeInitializeEnumerationContextFromGroup (
    _Out_ PKAFFINITY_ENUMERATION_CONTEXT Context,
    _In_ PGROUP_AFFINITY GroupAffinity)
{
    __debugbreak();
}

}; // extern "C"
