
#include "SectionView.hpp"
#include <ndk/ketypes.h>
#include <ndk/pstypes.h>

extern "C" struct _OBJECT_TYPE *MmSectionObjectType;


namespace Mm {

const char SectionVadType[] = "SectionView";

enum VA_TYPE
{
    VaUnused = 0,
    VaProcessSpace,
    VaSystemSpace,
    VaSessionSpace,

    VaBootLoaded,
    VaPfnDatabase,
    VaNonPagedPool,
    VaPagedPool,
    VaSpecialPoolPaged,
    VaSystemCache,
    VaSystemPtes,
    VaHal,
    VaSessionGlobalSpace,
    VaDriverImages,
    VaSpecialPoolNonPaged,
    VaMaximumType,
};

bool
IsSectionVad(VAD_OBJECT* VadObject)
{
    return VadObject->GetVadType() == SectionVadType;
}


extern "C" {

/** Internal API **************************************************************/

NTSTATUS
NTAPI
MiMapViewOfSection (
    _In_ PVOID SectionObject,
    _In_ VA_TYPE VaType,
    _Inout_ PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    // create a section VAD (locked)
    // insert the VAD into the address space / VAD table
    // get the "SEGMENT"
    // Segment->GetSectionView(offset, size)
    //
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MiUnmapViewOfSection (
    _In_ VA_TYPE VaType,
    _In_ PVOID BaseAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmGetFileNameForAddress (
    _In_ PVOID Address,
    _Out_ PUNICODE_STRING ModuleName)
{
    // Process = PsGetCurrentProcess();
    // AddressSpace = GetProcessAddressSpace(Process);
    // AddressSpace->FindVadByAddress(Address)
    // if (VadObject->GetType() == SectionVadType)
    // SectionVad
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


/** Exported API **************************************************************/

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSystemSpace (
    _In_ PVOID SectionObject,
    _Outptr_result_bytebuffer_(*ViewSize) PVOID *BaseAddress,
    _Inout_ PSIZE_T ViewSize)
{
    /* Call the internal function */
    return MiMapViewOfSection(SectionObject,
                              VaSystemSpace,
                              BaseAddress,
                              0,
                              *ViewSize,
                              NULL,
                              ViewSize,
                              ViewUnmap,
                              0,
                              PAGE_EXECUTE_READWRITE);
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSystemSpace (
    _In_ PVOID BaseAddress)
{
    /* Call the internal function */
    return MiUnmapViewOfSection(VaSystemSpace, BaseAddress);
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSessionSpace (
    _In_ PVOID SectionObject,
    _Outptr_result_bytebuffer_(*ViewSize) PVOID *BaseAddress,
    _Inout_ PSIZE_T ViewSize)
{
    /* Call the internal function */
    return MiMapViewOfSection(SectionObject,
                              VaSessionSpace,
                              BaseAddress,
                              0,
                              *ViewSize,
                              NULL,
                              ViewSize,
                              ViewUnmap,
                              0,
                              PAGE_EXECUTE_READWRITE);
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSessionSpace (
    _In_ PVOID BaseAddress)
{
    /* Call the internal function */
    return MiUnmapViewOfSection(VaSessionSpace, BaseAddress);
}

NTSTATUS
NTAPI
MmMapViewOfSection (
    _In_ PVOID SectionObject,
    _In_ PEPROCESS Process,
    _Inout_ PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    KAPC_STATE SavedApcState;
    BOOLEAN Attached = FALSE;
    NTSTATUS Status;

    /* Check if this the current process is requested */
    if ((PKPROCESS)Process != KeGetCurrentThread()->ApcState.Process)
    {
        /* Foreign process, attach to it */
        KeStackAttachProcess((PKPROCESS)Process, &SavedApcState);
        Attached = TRUE;
    }

    /* Call the internal function */
    Status = MiMapViewOfSection(SectionObject,
                                VaProcessSpace,
                                BaseAddress,
                                ZeroBits,
                                CommitSize,
                                SectionOffset,
                                ViewSize,
                                InheritDisposition,
                                AllocationType,
                                Protect);

    /* Detach if required */
    if (Attached)
    {
        KeUnstackDetachProcess(&SavedApcState);
    }

    return Status;
}

NTSTATUS
NTAPI
MmUnmapViewOfSection (
    _In_ struct _EPROCESS* Process,
    _In_ PVOID BaseAddress)
{
    KAPC_STATE SavedApcState;
    BOOLEAN Attached = FALSE;
    NTSTATUS Status;

    /* Check if this the current process is requested */
    if ((PKPROCESS)Process != KeGetCurrentThread()->ApcState.Process)
    {
        /* Foreign process, attach to it */
        KeStackAttachProcess((PKPROCESS)Process, &SavedApcState);
        Attached = TRUE;
    }

    /* Call the internal function */
    Status = MiUnmapViewOfSection(VaProcessSpace, BaseAddress);

    /* Detach if required */
    if (Attached)
    {
        KeUnstackDetachProcess(&SavedApcState);
    }

    return Status;
}


/** Syscall API ***************************************************************/

NTSTATUS
NTAPI
NtMapViewOfSection (
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect)
{
    KPROCESSOR_MODE PreviousMode;
    PVOID SafeBaseAddress, *BaseAddressPointer;
    LARGE_INTEGER SafeSectionOffset, *SectionOffsetPointer;
    SIZE_T SafeViewSize, *ViewSizePointer;
    PVOID SectionObject;
    ACCESS_MASK DesiredAccess;
    KAPC_STATE SavedApcState;
    PEPROCESS Process;
    NTSTATUS Status;

    /* Check if this call comes from user mode */
    PreviousMode = ExGetPreviousMode();
    if (PreviousMode != KernelMode)
    {
        /* Use SEH to copy the buffers */
        _SEH2_TRY
        {
            ProbeForWrite(BaseAddress, sizeof(*BaseAddress), 1);
            SafeBaseAddress = *BaseAddress;

            ProbeForWrite(SectionOffset, sizeof(*SectionOffset), 1);
            SafeSectionOffset = *SectionOffset;

            ProbeForWrite(ViewSize, sizeof(*ViewSize), 1);
            SafeViewSize = *ViewSize;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            //ERR("Could not
            _SEH2_YIELD(return _SEH2_GetExceptionCode();)
        }
        _SEH2_END;

        /* Use the safe copies */
        BaseAddressPointer = &SafeBaseAddress;
        SectionOffsetPointer = &SafeSectionOffset;
        ViewSizePointer = &SafeViewSize;
    }
    else
    {
        /* Use the passed pointer directly */
        BaseAddressPointer = BaseAddress;
        SectionOffsetPointer = SectionOffset;
        ViewSizePointer = ViewSize;
    }

    /* Check if the current process is specified */
    if (ProcessHandle != NtCurrentProcess())
    {
        /* Reference the process object */
        Status = ObReferenceObjectByHandle(ProcessHandle,
                                           PROCESS_VM_OPERATION,
                                           PsProcessType,
                                           PreviousMode,
                                           reinterpret_cast<PVOID*>(&Process),
                                           NULL);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        /* Attach to it */
        KeStackAttachProcess(&Process->Pcb, &SavedApcState);
    }

    /* Get the required access mask from the page protection */
    DesiredAccess = SECTION_MAP_READ;
    if (Win32Protect & PAGE_ANY_WRITE)
    {
        DesiredAccess |= SECTION_MAP_WRITE;
    }
    if (Win32Protect & PAGE_ANY_EXECUTE)
    {
        DesiredAccess |= SECTION_MAP_EXECUTE;
    }

    /* Reference the section object */
    Status = ObReferenceObjectByHandle(SectionHandle,
                                       DesiredAccess,
                                       MmSectionObjectType,
                                       PreviousMode,
                                       reinterpret_cast<PVOID*>(&SectionObject),
                                       NULL);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Call the exported function */
    Status = MiMapViewOfSection(SectionObject,
                                VaProcessSpace,
                                BaseAddressPointer,
                                ZeroBits,
                                CommitSize,
                                SectionOffsetPointer,
                                ViewSizePointer,
                                InheritDisposition,
                                AllocationType,
                                Win32Protect);

    if (NT_SUCCESS(Status))
    {
        if (PreviousMode != KernelMode)
        {
            /* Use SEH to copy the data back (pointers are already probed) */
            _SEH2_TRY
            {
                *BaseAddress = SafeBaseAddress;
                *SectionOffset = SafeSectionOffset;
                *ViewSize = SafeViewSize;
            }
            _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
            {
                //ERR("Could not
                _SEH2_YIELD(return _SEH2_GetExceptionCode();)
            }
            _SEH2_END;
        }
    }

    /* Dereference the section object */
    ObDereferenceObject(SectionObject);

Cleanup:

    if (ProcessHandle != NtCurrentProcess())
    {
        /* Detach and dereference process */
        KeUnstackDetachProcess(&SavedApcState);
        ObDereferenceObject(Process);
    }

    return Status;
}

NTSTATUS
NTAPI
NtUnmapViewOfSection (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress)
{
    KAPC_STATE SavedApcState;
    PEPROCESS Process;
    NTSTATUS Status;

    /* Check if the current process is specified */
    if (ProcessHandle != NtCurrentProcess())
    {
        /* Reference the process object */
        Status = ObReferenceObjectByHandle(ProcessHandle,
                                           PROCESS_VM_OPERATION,
                                           PsProcessType,
                                           ExGetPreviousMode(),
                                           reinterpret_cast<PVOID*>(&Process),
                                           NULL);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        /* Attach to it */
        KeStackAttachProcess(&Process->Pcb, &SavedApcState);
    }

    /* Call the internal function */
    Status = MiUnmapViewOfSection(VaProcessSpace, BaseAddress);

    if (ProcessHandle != NtCurrentProcess())
    {
        /* Detach and dereference process */
        KeUnstackDetachProcess(&SavedApcState);
        ObDereferenceObject(Process);
    }

    return Status;
}

}; // extern "C"
}; // namespace Mm
