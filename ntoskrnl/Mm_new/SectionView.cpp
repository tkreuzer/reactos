
#include "SectionView.hpp"
#include "Section.hpp"
#include "SectionObject.hpp"
#include "Mapping.hpp"
#include "AddressSpace.hpp"
#include "VadTable.hpp"
#include _ARCH_RELATIVE_(MachineDependent.hpp)
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
    _In_ PSECTION Section)
{
    PSECTION_VIEW SectionView;
    NT_ASSERT(Section != NULL);

    /// \todo Evaluate if we can use paged pool for user VADs, when the VAD
    ///       table doesn't use a spinlock
    /* Allocate a new VAD from non-paged pool */
    SectionView = new(NonPagedPool, sizeof(SECTION_VIEW), 'wVmM') SECTION_VIEW;
    if (SectionView == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    SectionView->m_Section = Section;

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
    return Status;
}

NTSTATUS
SECTION_VIEW::CreateMapping (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG_PTR CommitSizeInPages,
    _In_ ULONG Protect)
{
    NTSTATUS Status;

    /* Forward the mapping request to the section */
    Status = m_Section->CreateMapping(GetBaseAddress(),
                                      RelativeStartingVpn,
                                      NumberOfPages,
                                      Protect);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to create prototype PTE mapping: 0x%lx\n", Status);
        return Status;
    }

    /* Check if we shall commit pages */
    if (CommitSizeInPages != 0)
    {
        /* Commit the requested size of the backing section memory */
        Status = m_Section->CommitPages(0, CommitSizeInPages, Protect);
        if (!NT_SUCCESS(Status))
        {
            ERR("Failed to commit pages for section: 0x%lx\n", Status);
            __debugbreak(); // we need to make sure that the memory gets unmapped!
            return Status;
        }
    }

    return STATUS_SUCCESS;
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
    _In_ ULONG Win32Protect)
{
    PADDRESS_SPACE AddressSpace;
    ULONG_PTR StartingVpn, LowestStartingVpn, HighestEndingVpn, RelativeStartingVpn;
    ULONG_PTR BoundaryPageMultiple, ViewSizeInPages;
    SECTION_VIEW* SectionView;
    NTSTATUS Status;
    PVAD_TABLE VadTable;
    PSECTION Section;
    ULONG Protect;

//__debugbreak();

    // Check ViewSize

    if (CommitSize > *ViewSize)
    {
        return STATUS_INVALID_PARAMETER_5;
    }

    /* Check if the caller specified a section offset */
    if (SectionOffset != NULL)
    {
        /* Check if it's valid */
        if (SectionOffset->QuadPart >= (LONG64)(ULONG64)MAXULONG * PAGE_SIZE)
        {
            return STATUS_INVALID_PARAMETER;
        }

        RelativeStartingVpn = (ULONG_PTR)BYTES_TO_PAGES(SectionOffset->QuadPart);
    }
    else
    {
        RelativeStartingVpn = 0;
    }

    /* Convert protection mask */
    Protect = ConvertProtect(Win32Protect);

    if (VaType == VaProcessSpace)
    {
        AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
        LowestStartingVpn = 1;
        HighestEndingVpn = AddressToVpn(MmHighestUserAddress);
        BoundaryPageMultiple = 16;
        Protect |= MM_USER;
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
        AddressSpace = &g_KernelAddressSpace; /// HACK
        LowestStartingVpn = AddressToVpn(SESSION_SPACE_START);
        HighestEndingVpn = AddressToVpn(SESSION_VIEW_END);
        BoundaryPageMultiple = 1;
        Protect |= MM_GLOBAL;
    }
    else
    {
        return STATUS_INVALID_PARAMETER;
    }

#if 0
    // maybe move it to NtMapViewOfSection / MmMapViewOfSection
    if ((*BaseAddress != NULL) &&
        (*BaseAddress != ALIGN_DOWN_POINTER_BY(BoundaryPageMultiple * PAGE_SIZE)))
    {
        return STATUS_MAPPED_ALIGNMENT;
    }
#endif

    /* Reference the section */
    Section = SectionObject->ReferenceSection();
    NT_ASSERT(Section != NULL);

    /* Create a section view VAD */
    Status = SECTION_VIEW::CreateInstance(&SectionView, Section);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to create section view VAD: 0x%lx\n", Status);
        Section->Release();
        return Status;
    }

    /* Check if the caller did not specify the size */
    ViewSizeInPages = BYTES_TO_PAGES(*ViewSize);
    if (ViewSizeInPages == 0)
    {
        /* Use the full section size */
        ViewSizeInPages = Section->GetSizeInPages();
        NT_ASSERT(ViewSizeInPages != 0);
    }

    /* Get the VAD table */
    VadTable = AddressSpace->GetVadTable();

    /* Check if a base address was specified */
    if (*BaseAddress != NULL)
    {
        /* Use the specified base address */
        StartingVpn = AddressToVpn(*BaseAddress);

        /* Check if the range is OK */
        if (((StartingVpn < LowestStartingVpn)) ||
            ((StartingVpn + ViewSizeInPages) > HighestEndingVpn) ||
            ((StartingVpn + ViewSizeInPages) < StartingVpn))
        {
            ERR("Invalid parameters: StartingVpn\n");
            SectionView->Release();
            return STATUS_INVALID_PARAMETER;
        }

        /* Try to insert the VAD at the corresponding VPN */
        Status = VadTable->InsertVadObjectAtVpn(SectionView,
                                                StartingVpn,
                                                ViewSizeInPages);
    }
    else
    {
        /* Use the image base address */
        StartingVpn = AddressToVpn(Section->GetBaseAddress());

        /* Check if the range is OK */
        if ((StartingVpn != 0) && ((StartingVpn >= LowestStartingVpn)) &&
            ((StartingVpn + ViewSizeInPages) <= HighestEndingVpn) &&
            ((StartingVpn + ViewSizeInPages) > StartingVpn))
        {
            /* Try to insert the VAD at the image base address */
            Status = VadTable->InsertVadObjectAtVpn(SectionView,
                                                    StartingVpn,
                                                    ViewSizeInPages);
        }
        else
        {
            /* Range is invalid, no success yet */
            Status = STATUS_UNSUCCESSFUL;
        }

        /* Check if we did not succeed yet */
        if (!NT_SUCCESS(Status))
        {
            /* Insert the VAD into the VAD table */
            Status = VadTable->InsertVadObject(SectionView,
                                               ViewSizeInPages,
                                               LowestStartingVpn,
                                               HighestEndingVpn,
                                               BoundaryPageMultiple,
                                               (AllocationType & MEM_TOP_DOWN) != 0);
        }
    }

    if (!NT_SUCCESS(Status))
    {
        SectionView->Release();
        return Status;
    }

    /* Now create the prototype PTE mapping */
    Status = SectionView->CreateMapping(RelativeStartingVpn,
                                        ViewSizeInPages,
                                        BYTES_TO_PAGES(CommitSize),
                                        Protect);
    if (!NT_SUCCESS(Status))
    {
        VadTable->RemoveVadObject(SectionView);
        SectionView->Release();
        return Status;
    }

    /* Return the base address to the caller */
    *BaseAddress = SectionView->GetBaseAddress();
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
    *BaseAddress = NULL;
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
    *BaseAddress = NULL;
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
    _In_ ULONG Win32Protect)
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
                              Win32Protect);

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
    PVOID SafeBaseAddress;
    LARGE_INTEGER SafeSectionOffset;
    SIZE_T SafeViewSize;
    PVOID SectionObject;
    ACCESS_MASK DesiredAccess;
    KAPC_STATE SavedApcState;
    PEPROCESS Process;
    NTSTATUS Status;

    /* Check ZeroBits parameter */
    if (ZeroBits > 21)
        return STATUS_INVALID_PARAMETER_4;

    /* Check InheritDisposition parameter */
    if ((InheritDisposition != ViewShare) && (InheritDisposition != ViewUnmap))
        return STATUS_INVALID_PARAMETER_8;

    /* Check Allocation type flags */
    if (AllocationType & 0x9FAFDF80)
        return STATUS_INVALID_PARAMETER_9;

    // convert protection / return STATUS_INVALID_PAGE_PROTECTION;


    /* Check if this call comes from user mode */
    PreviousMode = ExGetPreviousMode();
    if (PreviousMode != KernelMode)
    {
        /* Use SEH to copy the buffers */
        _SEH2_TRY
        {
            ProbeForWrite(BaseAddress, sizeof(*BaseAddress), 1);
            SafeBaseAddress = *BaseAddress;

            ProbeForWrite(ViewSize, sizeof(*ViewSize), 1);
            SafeViewSize = *ViewSize;

            if (SectionOffset != NULL)
            {
                ProbeForWrite(SectionOffset, sizeof(*SectionOffset), 1);
                SafeSectionOffset = *SectionOffset;
            }
            else
            {
                SafeSectionOffset.QuadPart = 0;
            }
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            ERR("Exception while copying parameters\n");
            _SEH2_YIELD(return _SEH2_GetExceptionCode();)
        }
        _SEH2_END;
    }
    else
    {
        SafeBaseAddress = *BaseAddress;
        SafeSectionOffset.QuadPart = SectionOffset ? SectionOffset->QuadPart : 0;
        SafeViewSize = *ViewSize;
    }

    /* Check the BaseAddress parameter */
    if ((SafeBaseAddress > MmHighestUserAddress) ||
        (AddToPointer(SafeBaseAddress, SafeViewSize) > MmHighestUserAddress) ||
        (AddToPointer(SafeBaseAddress, SafeViewSize) < SafeBaseAddress))
        return STATUS_INVALID_PARAMETER_3;

    /* Check the ZeroBits parameter */
    if (((ULONG_PTR)SafeBaseAddress + SafeViewSize) > (MAXULONG_PTR >> ZeroBits))
        return STATUS_INVALID_PARAMETER_4;

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
                                       &SectionObject,
                                       NULL);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Call the internal function */
    Status = MapViewOfSection(static_cast<PSECTION_OBJECT>(SectionObject),
                              VaProcessSpace,
                              &SafeBaseAddress,
                              ZeroBits,
                              CommitSize,
                              &SafeSectionOffset,
                              &SafeViewSize,
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
                *ViewSize = SafeViewSize;
                if (SectionOffset != NULL)
                    *SectionOffset = SafeSectionOffset;
            }
            _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
            {
                //ERR("Could not
                _SEH2_YIELD(return _SEH2_GetExceptionCode();)
            }
            _SEH2_END;
        }
        else
        {
            *BaseAddress = SafeBaseAddress;
            *ViewSize = SafeViewSize;
            if (SectionOffset != NULL)
                *SectionOffset = SafeSectionOffset;
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
