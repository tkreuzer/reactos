
#include <ntoskrnl.h>

struct _EPROCESS;
ULONG
NTAPI
MmGetSessionId (
    _In_ struct _EPROCESS *Process);

PVOID pMmGetSessionId = (PVOID)MmGetSessionId;

BOOLEAN Mm64BitPhysicalAddress;
PVOID MmHighestUserAddress;
PVOID MmSystemRangeStart;
ULONG_PTR MmUserProbeAddress;
PVOID MmBadPointer;

typedef enum _MM_SYSTEM_SIZE
{
    MmSmallSystem,
    MmMediumSystem,
    MmLargeSystem
} MM_SYSTEMSIZE;

MM_SYSTEMSIZE
NTAPI
MmQuerySystemSize (
    VOID)
{
    __debugbreak();
    return MmLargeSystem;
}

BOOLEAN
NTAPI
MmIsThisAnNtAsSystem (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmSetAddressRangeModified (
    _In_reads_bytes_ (Length) PVOID Address,
    _In_ SIZE_T Length)
{
    __debugbreak();
    return FALSE;
}

// ntddk.h
_Must_inspect_result_
_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmCreateMirror (
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtMapCMFModule (
    _In_ ULONG What,
    _In_ ULONG Index,
    _Out_opt_ ULONG *CacheIndexOut,
    _Out_opt_ ULONG *CacheFlagsOut,
    _Out_opt_ ULONG *ViewSizeOut,
    _Out_opt_ PVOID *BaseAddress)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

