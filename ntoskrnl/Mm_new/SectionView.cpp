/*!

    \file SectionView.cpp

    \brief Implements the SECTION_VIEW class

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "SectionView.hpp"
#include "PhysicalSection.hpp"
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

/*! \fn IsSectionVad
 *
 *  \brief ...
 *
 *  \param [in] VadObject -
 *
 *  \return ...
 */
bool
IsSectionVad(VAD_OBJECT* VadObject)
{
    return VadObject->GetVadType() == SectionViewVadType;
}


/*! \fn SECTION_VIEW::~SECTION_VIEW
 *
 *  \brief SECTION_VIEW virtual destructor
 *
 */
SECTION_VIEW::~SECTION_VIEW (
    VOID)
{
    NT_ASSERT(m_Section != NULL);
    m_Section->Release();
}


/*! \fn SECTION_VIEW::GetVadType
 *
 *  \brief ...
 *
 *  \return ...
 */
const char*
SECTION_VIEW::GetVadType () const
{
    return SectionViewVadType;
}

/*! \fn SECTION_VIEW::CreateInstance
 *
 *  \brief ...
 *
 *  \param [out] OutSectionView -
 *
 *  \param [in] Section -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
NTSTATUS
SECTION_VIEW::CreateInstance (
    _Out_ SECTION_VIEW** OutSectionView,
    _In_ PPHYSICAL_SECTION Section,
    _In_ ULONG_PTR SectionPageOffset,
    _In_ ULONG Protect)
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
    SectionView->m_SectionPageOffset = SectionPageOffset;
    SectionView->m_Protect = Protect;

    *OutSectionView = SectionView;
    return STATUS_SUCCESS;
}

/*! \fn SECTION_VIEW::GetMemoryType
 *
 *  \brief ...
 *
 *  \return ...
 */
ULONG
SECTION_VIEW::GetMemoryType (
    VOID)
{
    SECTION_FLAGS SectionFlags;

    SectionFlags = m_Section->GetSectionFlags();
    if (SectionFlags.Image)
        return MEM_IMAGE;
    else
        return MEM_MAPPED;
}

/*! \fn SECTION_VIEW::CommitPages
 *
 *  \brief ...
 *
 *  \param [in] StartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
NTSTATUS
SECTION_VIEW::CommitPages (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    NTSTATUS Status;
    //PVOID BaseAddress;
    ULONG_PTR EndingVpn, SectionStartingVpn;

    /// \todo check the range

    /* Check parameter */
    EndingVpn = StartingVpn + NumberOfPages - 1;
    if ((NumberOfPages == 0) || (EndingVpn < StartingVpn))
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Check the range */
    if ((StartingVpn < GetStartingVpn()) || (EndingVpn > GetEndingVpn()))
    {
        return STATUS_UNSUCCESSFUL;
    }

    SectionStartingVpn = StartingVpn - GetStartingVpn() + GetSectionPageOffset();

    /* Commit the requested size of the backing section memory */
    Status = m_Section->CommitPages(SectionStartingVpn, NumberOfPages, Protect);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to commit pages for section: 0x%lx\n", Status);
        __debugbreak(); // we need to make sure that the memory gets unmapped!
        return Status;
    }

    Status = m_Section->CreateMapping(VpnToAddress(StartingVpn),
                                      SectionStartingVpn,
                                      NumberOfPages,
                                      Protect);

    return Status;
}

/*! \fn SECTION_VIEW::CreateMapping
 *
 *  \brief ...
 *
 *  \param [in] RelativeStartingVpn -
 *
 *  \param [in] NumberOfPages -
 *
 *  \param [in] CommitSizeInPages -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
NTSTATUS
SECTION_VIEW::CreateMapping (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG_PTR CommitSizeInPages,
    _In_ ULONG Protect)
{
    NTSTATUS Status;

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

    /* Forward the mapping request to the section */
    Status = m_Section->CreateMapping(GetBaseAddress(),
                                      GetSectionPageOffset(),
                                      NumberOfPages,
                                      Protect);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to create prototype PTE mapping: 0x%lx\n", Status);
        return Status;
    }

    return STATUS_SUCCESS;
}

/*! \fn MapViewOfSection
 *
 *  \brief ...
 *
 *  \param [in] SectionObject -
 *
 *  \param [in] VaType -
 *
 *  \param [in,out] BaseAddress -
 *
 *  \param [in] ZeroBits -
 *
 *  \param [in] CommitSize -
 *
 *  \param [in,out] SectionOffset -
 *
 *  \param [in,out] ViewSize -
 *
 *  \param [in] InheritDisposition -
 *
 *  \param [in] AllocationType -
 *
 *  \param [in] Win32Protect -
 *
 *  \return ...
 */
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
    ULONG_PTR StartingVpn, SectionPageOffset;
    ULONG_PTR BoundaryPageMultiple, SectionSizeInPages, ViewSizeInPages;
    SECTION_VIEW* SectionView;
    NTSTATUS Status;
    PPHYSICAL_SECTION Section;
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
            __debugbreak();
            return STATUS_INVALID_PARAMETER;
        }

        SectionPageOffset = (ULONG_PTR)BYTES_TO_PAGES(SectionOffset->QuadPart);
    }
    else
    {
        SectionPageOffset = 0;
    }

    /* Convert protection mask */
    Protect = ConvertProtect(Win32Protect);

    if (VaType == VaProcessSpace)
    {
        AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
        LowestStartingVpn = 0;
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
        AddressSpace = 0;
        LowestStartingVpn = AddressToVpn(SESSION_SPACE_START);
        HighestEndingVpn = AddressToVpn(SESSION_VIEW_END);
        BoundaryPageMultiple = 1;
        Protect |= MM_GLOBAL;
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

    /* Get the section size */
    SectionSizeInPages = Section->GetSizeInPages();

    /// \todo check if == is ok
    /* Check if we start outside of the section */
    if (SectionPageOffset >= SectionSizeInPages)
    {
        Section->Release();
        return STATUS_INVALID_PARAMETER;
    }

    /* Check if the caller specified the view size */
    if (*ViewSize != 0)
    {
        /* Convert to pages and check if it's valid */
        ViewSizeInPages = BYTES_TO_PAGES(*ViewSize);
        if (ViewSizeInPages > SectionSizeInPages - SectionPageOffset)
        {
            Section->Release();
            return STATUS_INVALID_PARAMETER;
        }
    }
    else
    {
        /* Otherwise use the full section size minus the section offset */
        ViewSizeInPages = SectionSizeInPages - SectionPageOffset;
        NT_ASSERT(ViewSizeInPages != 0);
    }

    /* Update the view size */
    *ViewSize = ViewSizeInPages * PAGE_SIZE;

    /* Check if the commit size is larger than the view size */
    if (CommitSize > *ViewSize)
    {
        ERR("Invalid CommitSize (0x%lx), ViewSize 0x%lx\n", CommitSize, *ViewSize);
        Section->Release();
        return STATUS_INVALID_PARAMETER_5;
    }

    /* Create a section view VAD */
    Status = SECTION_VIEW::CreateInstance(&SectionView,
                                          Section,
                                          SectionPageOffset,
                                          Protect);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to create section view VAD: 0x%lx\n", Status);
        Section->Release();
        return Status;
    }

    /* Check if the caller specified a base address */
    if (*BaseAddress != NULL)
    {
        /* Use the base address for the starting VPN */
        StartingVpn = AddressToVpn(*BaseAddress);

        /* Check if the range is OK */
        if (((StartingVpn < LowestStartingVpn)) ||
            ((StartingVpn + ViewSizeInPages) > HighestEndingVpn) ||
            ((StartingVpn + ViewSizeInPages) < StartingVpn))
        {
            ERR("Invalid parameters: StartingVpn = 0x%lx\n", StartingVpn);
            Section->Release();
            return STATUS_INVALID_PARAMETER;
        }
    }
    else
    {
        /* Get the image start address */
        StartingVpn = AddressToVpn(Section->GetBaseAddress());

        /* Check if the range is OK */
        if (((StartingVpn < LowestStartingVpn)) ||
            ((StartingVpn + ViewSizeInPages) > HighestEndingVpn) ||
            ((StartingVpn + ViewSizeInPages) < StartingVpn))
        {
            /* Range is not ok, fall back to auto-base */
            StartingVpn = 0;
        }
    }

    /* Check if we didn't succeed yet */
    if (!NT_SUCCESS(Status))
    {
        /* Insert the VAD object into the address space */
        Status = AddressSpace->InsertVadObjectEx(SectionView,
                                                 BaseAddress,
                                                 ViewSizeInPages,
                                                 ZeroBits,
                                                 AllocationType);
    }


    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to insert section view into address space: %x\n", Status);
        SectionView->Release();
        return Status;
    }

    /* Now create the prototype PTE mapping */
    Status = SectionView->CreateMapping(SectionPageOffset,
                                        ViewSizeInPages,
                                        BYTES_TO_PAGES(CommitSize),
                                        Protect);
    if (!NT_SUCCESS(Status))
    {
        //AddressSpace->RemoveVadObject(SectionView);
        SectionView->Release();
        return Status;
    }

    /* Return the base address to the caller */
    *BaseAddress = SectionView->GetBaseAddress();
    return STATUS_SUCCESS;
}

/*! \fn UnmapViewOfSection
 *
 *  \brief ...
 *
 *  \param [in] VaType -
 *
 *  \param [in] BaseAddress -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
UnmapViewOfSection (
    _In_ VA_TYPE VaType,
    _In_ PVOID BaseAddress)
{
    PADDRESS_SPACE AddressSpace;
    PVAD_TABLE VadTable;
    PVAD_OBJECT VadObject;

    if (VaType == VaProcessSpace)
    {
        AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
    }
    else if (VaType == VaSystemSpace)
    {
        AddressSpace = &g_KernelAddressSpace;
    }
    else if (VaType == VaSessionSpace)
    {
        AddressSpace = &g_KernelAddressSpace; /// HACK
    }
    else
    {
        __debugbreak();
        return STATUS_INVALID_PARAMETER;
    }

    /* Get the VAD table */
    VadTable = AddressSpace->GetVadTable();

    /// should lock the address space or something

    VadObject = VadTable->GetVadObjectByAddress(BaseAddress);
    if (VadObject == NULL)
    {
        return STATUS_NOT_COMMITTED;
    }

    if (VadObject->GetVadType() != SectionViewVadType)
    {
        return STATUS_NOT_COMMITTED;
    }

    // VadObject->Unmap()
    VadTable->RemoveVadObject(VadObject);
    VadObject->Release();

    return STATUS_SUCCESS;
}

extern "C" {
/** Internal API **************************************************************/

/*! \fn MmGetFileNameForAddress
 *
 *  \brief ...
 *
 *  \param [in] Address -
 *
 *  \param [out] ModuleName -
 *
 *  \return ...
 */
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

/*! \fn MmMapViewInSystemSpace
 *
 *  \brief ...
 *
 *  \param [in] SectionObject -
 *
 *  \param [out] BaseAddress -
 *
 *  \param [in,out] ViewSize -
 *
 *  \return ...
 */
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

/*! \fn MmUnmapViewInSystemSpace
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \return ...
 */
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSystemSpace (
    _In_ PVOID BaseAddress)
{
    /* Call the internal function */
    return UnmapViewOfSection(VaSystemSpace, BaseAddress);
}

/*! \fn MmMapViewInSessionSpace
 *
 *  \brief ...
 *
 *  \param [in] SectionObject -
 *
 *  \param [out] BaseAddress -
 *
 *  \param [in,out] ViewSize -
 *
 *  \return ...
 */
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

/*! \fn MmUnmapViewInSessionSpace
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \return ...
 */
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSessionSpace (
    _In_ PVOID BaseAddress)
{
    /* Call the internal function */
    return UnmapViewOfSection(VaSessionSpace, BaseAddress);
}

//MmMapViewInSystemCache
//MmUnmapViewInSystemCache

/*! \fn MmMapViewOfSection
 *
 *  \brief ...
 *
 *  \param [in] SectionObject -
 *
 *  \param [in] Process -
 *
 *  \param [in,out] BaseAddress -
 *
 *  \param [in] ZeroBits -
 *
 *  \param [in] CommitSize -
 *
 *  \param [in,out] SectionOffset -
 *
 *  \param [in,out] ViewSize -
 *
 *  \param [in] InheritDisposition -
 *
 *  \param [in] AllocationType -
 *
 *  \param [in] Win32Protect -
 *
 *  \return ...
 */
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

    /* Check if the current process is requested */
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
        /* Detach from the target process */
        KeUnstackDetachProcess(&SavedApcState);
    }

    return Status;
}

/*! \fn MmUnmapViewOfSection
 *
 *  \brief ...
 *
 *  \param [in] Process -
 *
 *  \param [in] BaseAddress -
 *
 *  \return ...
 */
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

/*! \fn NtMapViewOfSection
 *
 *  \brief ...
 *
 *  \param [in] SectionHandle -
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [in,out] BaseAddress -
 *
 *  \param [in] ZeroBits -
 *
 *  \param [in] CommitSize -
 *
 *  \param [in,out] SectionOffset -
 *
 *  \param [in,out] ViewSize -
 *
 *  \param [in] InheritDisposition -
 *
 *  \param [in] AllocationType -
 *
 *  \param [in] Win32Protect -
 *
 *  \return ...
 */
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

    Process = NULL;

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
    {
        return STATUS_INVALID_PARAMETER_3;
    }

    /* Check the ZeroBits parameter */
    if (((ULONG_PTR)SafeBaseAddress + SafeViewSize) > (MAXULONG_PTR >> ZeroBits))
    {
        return STATUS_INVALID_PARAMETER_4;
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
    }

    /* Get the required access mask from the page protection */
    DesiredAccess = 0;
    if (Win32Protect & PAGE_IS_READABLE)
    {
        DesiredAccess |= SECTION_MAP_READ;
    }
    if (Win32Protect & PAGE_IS_WRITABLE)
    {
        DesiredAccess |= SECTION_MAP_WRITE;
    }
    if (Win32Protect & PAGE_IS_EXECUTABLE)
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
        if (Process != NULL)
        {
            /* Dereference process */
            ObDereferenceObject(Process);
        }
        return Status;
    }

    /* Check if we have a process */
    if (Process != NULL)
    {
        /* Attach to it */
        KeStackAttachProcess(&Process->Pcb, &SavedApcState);
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

    /* Check if we attached to a process */
    if (Process != NULL)
    {
        /* Detach and dereference the process */
        KeUnstackDetachProcess(&SavedApcState);
        ObDereferenceObject(Process);
    }

    /* Dereference the section object */
    ObDereferenceObject(SectionObject);

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

    return Status;
}

/*! \fn NtUnmapViewOfSection
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [in] BaseAddress -
 *
 *  \return ...
 */
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
