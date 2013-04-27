
#include "ntosbase.h"

extern "C" {

#include <ndk/ketypes.h>

_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(MemoryDescriptorList->StartVa + MemoryDescriptorList->ByteOffset,
  _Field_size_bytes_opt_(MemoryDescriptorList->ByteCount))
VOID
NTAPI
MmProbeAndLockPages (
  _Inout_ PMDLX MemoryDescriptorList,
  _In_ KPROCESSOR_MODE AccessMode,
  _In_ LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
MmProbeAndLockSelectedPages (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmProbeAndLockProcessPages (
  _Inout_ PMDL MemoryDescriptorList,
  _In_ PEPROCESS Process,
  _In_ KPROCESSOR_MODE AccessMode,
  _In_ LOCK_OPERATION Operation)
{
    KAPC_STATE SavedApcState;
    BOOLEAN Attached = FALSE;

    /* Check if this the current process is requested */
    if ((PKPROCESS)Process != KeGetCurrentThread()->ApcState.Process)
    {
        /* Foreign process, attach to it */
        KeStackAttachProcess((PKPROCESS)Process, &SavedApcState);
        Attached = TRUE;
    }

    /* Use SEH, so we can detach, in case the callee throws an exception */
    _SEH2_TRY
    {
        /* Call the function for the current process */
        MmProbeAndLockPages(MemoryDescriptorList, AccessMode, Operation);
    }
    _SEH2_FINALLY
    {
        /* Detach if required */
        if (Attached)
        {
            KeUnstackDetachProcess(&SavedApcState);
        }
    }
    _SEH2_END;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnlockPages (
  _Inout_ PMDLX MemoryDescriptorList)
{
    UNIMPLEMENTED;
}

MM_SYSTEMSIZE
NTAPI
MmQuerySystemSize (
    VOID)
{
    /* Seriously, nobody has less than 64 MB RAM these days.
       That shouldn't even be legal! */
    return MmLargeSystem;
}

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmFlushImageSection (
  _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
  _In_ MMFLUSH_TYPE FlushType)
{
    UNIMPLEMENTED;
    return FALSE;
}

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmForceSectionClosed (
  _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
  _In_ BOOLEAN DelayClose)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmIsNonPagedSystemAddressValid (
  _In_ PVOID VirtualAddress)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmIsThisAnNtAsSystem (
    VOID)
{
    UNIMPLEMENTED;
    return FALSE;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmMapUserAddressesToPage (
  _In_reads_bytes_(NumberOfBytes) PVOID BaseAddress,
  _In_ SIZE_T NumberOfBytes,
  _In_ PVOID PageAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
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

BOOLEAN
NTAPI
MmDisableModifiedWriteOfSection (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer)
{
    UNIMPLEMENTED;
    return FALSE;
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

VOID
NTAPI
MmUnlockPageableImageSection (
    IN PVOID ImageSectionHandle)
{
    UNIMPLEMENTED;
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
