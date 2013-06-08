
#include "ntosbase.h"

extern "C" {


MM_SYSTEMSIZE
NTAPI
MmQuerySystemSize (
    VOID)
{
    /* Seriously, nobody has less than 64 MB RAM these days.
       That shouldn't even be legal! */
    return MmLargeSystem;
}

BOOLEAN
NTAPI
MmIsThisAnNtAsSystem (
    VOID)
{
    UNIMPLEMENTED;
    return FALSE;
}


_IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
NTAPI
MmPrefetchPages (
  _In_ ULONG NumberOfLists,
  _In_reads_ (NumberOfLists) PREAD_LIST *ReadLists)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS
NTAPI
MmAdjustWorkingSetSize (
    _In_ SIZE_T WorkingSetMinimumInBytes,
    _In_ SIZE_T WorkingSetMaximumInBytes,
    _In_ ULONG SystemCache,
    _In_ BOOLEAN IncreaseOkay)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

PVOID
NTAPI
MmLockPageableDataSection (
    IN PVOID AddressWithinSection)
{
    //
    // We should just find the section and call MmLockPageableSectionByHandle
    //
    static BOOLEAN Warn; if (!Warn++) UNIMPLEMENTED;
    return AddressWithinSection;
}

VOID
NTAPI
MmLockPageableSectionByHandle (
    IN PVOID ImageSectionHandle)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
MmUnlockPageableImageSection (
    IN PVOID ImageSectionHandle)
{
    UNIMPLEMENTED;
}

NTSTATUS
NTAPI
MmSetBankedSection (
    IN HANDLE ProcessHandle,
    IN PVOID VirtualAddress,
    IN ULONG BankLength,
    IN BOOLEAN ReadWriteBank,
    IN PVOID BankRoutine,
    IN PVOID Context)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtGetWriteWatch (
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _In_ PVOID *UserAddressArray,
    _Out_ PULONG_PTR EntriesInUserAddressArray,
    _Out_ PULONG Granularity)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtResetWriteWatch (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


////////////////////////////////////////////////////////////////////////////////


VOID
NTAPI
MmZeroPageThread(
     VOID)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
MmDumpArmPfnDatabase(
    IN BOOLEAN StatusOnly)
{
    UNIMPLEMENTED;
}

}; // extern "C"
