
#include "SectionView.hpp"
#include "Section.hpp"
#include "SectionObject.hpp"
#include "AddressSpace.hpp"
#include "VadTable.hpp"
#include "amd64/MachineDependent.hpp"
#include <ndk/ketypes.h>
#include <ndk/pstypes.h>

extern "C" struct _OBJECT_TYPE *MmSectionObjectType;


namespace Mm {

const char SectionViewVadType[] = "SectionView";

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
    return VadObject->GetVadType() == SectionViewVadType;
}

const char*
SECTION_VIEW::GetVadType () const
{
    return SectionViewVadType;
}

NTSTATUS
SECTION_VIEW::CreateInstance (
    _Out_ SECTION_VIEW** OutSectionView,
    _In_ PSECTION_OBJECT SectionObject)
{
    PSECTION_VIEW SectionView;

    /// \todo Evaluate if we can use paged pool for user VADs, when the VAD
    ///       table doesn't use a spinlock
    SectionView = static_cast<PSECTION_VIEW>(
        ExAllocatePoolWithTag(NonPagedPool, sizeof(SECTION_VIEW), 'wVmM'));
    if (SectionView == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    new(SectionView) SECTION_VIEW;

    SectionView->m_Section = SectionObject->ReferenceSection();
    NT_ASSERT(SectionView->m_Section != NULL);

    *OutSectionView = SectionView;
    return STATUS_SUCCESS;
}

NTSTATUS
SECTION_VIEW::CommitPages (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    NTSTATUS Status;
    PVOID BaseAddress;

    /// \todo check the range

    BaseAddress = AddToPointer(GetBaseAddress(), RelativeStartingVpn * PAGE_SIZE);

    Status = m_Section->CreateMapping(BaseAddress,
                                      RelativeStartingVpn,
                                      NumberOfPages,
                                      Protect);

    // get the SECTION
    UNIMPLEMENTED;
    return 0;
}

NTSTATUS
NTAPI
MapViewOfSection (
    _In_ PSECTION_OBJECT SectionObject,
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
    PADDRESS_SPACE AddressSpace;
    ULONG_PTR StartingVpn, LowestStartingVpn, HighestEndingVpn;
    ULONG_PTR BoundaryPageMultiple, ViewSizeInPages;
    SECTION_VIEW* SectionView;
    NTSTATUS Status;
    PVAD_TABLE VadTable;

    ViewSizeInPages = BYTES_TO_PAGES(*ViewSize);
    StartingVpn = AddressToVpn(*BaseAddress);

    if (VaType == VaProcessSpace)
    {
        AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
        LowestStartingVpn = 0;
        HighestEndingVpn = AddressToVpn(MmHighestUserAddress);
        BoundaryPageMultiple = 16;
        Protect |= MM_USER;

        /* Check if the caller did not pass a base address */
        if (StartingVpn == 0)
        {
            /* Get the starting VPN from the section object */
            //StartingVpn = AddressToVpn(SectionObject->GetBaseAddress());
            __debugbreak();
        }
    }
    else if (VaType == VaSystemSpace)
    {
        AddressSpace = &g_KernelAddressSpace;
        LowestStartingVpn = AddressToVpn(MmSystemRangeStart);
        HighestEndingVpn = AddressToVpn(SYSTEM_RANGE_END);
        BoundaryPageMultiple = 1;
    }
    else if (VaType == VaSessionSpace)
    {
        AddressSpace = 0;
        LowestStartingVpn = AddressToVpn(SESSION_SPACE_START);
        HighestEndingVpn = AddressToVpn(SESSION_VIEW_END);
        BoundaryPageMultiple = 1;
        Protect |= MM_GLOBAL;
    }

#if 0
    // maybe move it to NtMapViewOfSection / MmMapViewOfSection
    if ((*BaseAddress != NULL) &&
        (*BaseAddress != ALIGN_DOWN_POINTER_BY(AllocationGranularity)))
    {
        return STATUS_MAPPED_ALIGNMENT;
    }
#endif

    VadTable = AddressSpace->GetVadTable();


    // create a section view VAD (locked)
    Status = SECTION_VIEW::CreateInstance(&SectionView, SectionObject);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }


    if (StartingVpn != 0)
    {

        /* Check if the range is OK */
        if ((StartingVpn < LowestStartingVpn) ||
            ((StartingVpn + ViewSizeInPages) > HighestEndingVpn) ||
            ((StartingVpn + ViewSizeInPages) < StartingVpn))
        {
            //SectionView->Release();
            delete SectionView;
            return STATUS_INVALID_PARAMETER;
        }

        Status = VadTable->InsertVadObjectAtVpn(SectionView,
                                                StartingVpn,
                                                ViewSizeInPages);

    }
    else
    {
        // insert the VAD into the address space / VAD table
        Status = VadTable->InsertVadObject(SectionView,
                                           ViewSizeInPages,
                                           LowestStartingVpn,
                                           HighestEndingVpn,
                                           BoundaryPageMultiple,
                                           (AllocationType & MEM_TOP_DOWN) != 0);

    }

    if (!NT_SUCCESS(Status))
    {
        //SectionView->Release();
        delete SectionView;
        return Status;
    }

    /* Now commit the pages of the section view */
    Status = SectionView->CommitPages(0, BYTES_TO_PAGES(CommitSize), Protect);
    NT_ASSERT(NT_SUCCESS(Status));

    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
UnmapViewOfSection (
    _In_ VA_TYPE VaType,
    _In_ PVOID BaseAddress)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

extern "C" {
/** Internal API **************************************************************/

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
    return MapViewOfSection(static_cast<PSECTION_OBJECT>(SectionObject),
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
    return UnmapViewOfSection(VaSystemSpace, BaseAddress);
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
    return MapViewOfSection(static_cast<PSECTION_OBJECT>(SectionObject),
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
    return UnmapViewOfSection(VaSessionSpace, BaseAddress);
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
    Status = MapViewOfSection(static_cast<PSECTION_OBJECT>(SectionObject),
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
    Status = UnmapViewOfSection(VaProcessSpace, BaseAddress);

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
    Status = MapViewOfSection(static_cast<PSECTION_OBJECT>(SectionObject),
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
    Status = UnmapViewOfSection(VaProcessSpace, BaseAddress);

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
