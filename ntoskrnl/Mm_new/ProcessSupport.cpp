/*!

    \file ProcessSupport.cpp

    \brief Implements process related functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include <ndk/pstypes.h>
#include "AddressSpace.hpp"
#include "SectionObject.hpp"
#include "VirtualMemory.hpp"
#include "VadTable.hpp"
#ifdef __linux__
#include "eal.h"
#endif
#include <ndk/mmfuncs.h>
#include <ndk/rtlfuncs.h>

extern "C" {
extern PVOID ExpNlsSectionPointer;
extern ULONG ExpAnsiCodePageDataOffset;
extern ULONG ExpOemCodePageDataOffset;
extern ULONG ExpUnicodeCaseTableDataOffset;
extern ULONG NtMajorVersion;
extern ULONG NtMinorVersion;
extern ULONG NtGlobalFlag;
extern ULONG CmNtCSDVersion;
extern ULONG PsDefaultThreadLocaleId;
LARGE_INTEGER MmCriticalSectionTimeout;
};

namespace Mm {

extern ULONG MappingRecordTimeStamp;

extern "C" {

/* Number of processes, the initial process is already there */
ULONG NumberOfProcesses = 1;

// private

/*! \fn MmSetExecuteOptions
 *
 *  \brief ...
 *
 *  \param [in] ExecuteOptions -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmSetExecuteOptions (
    IN ULONG ExecuteOptions)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmGetExecuteOptions
 *
 *  \brief ...
 *
 *  \param [out] ExecuteOptions -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmGetExecuteOptions (
    _Out_ PULONG ExecuteOptions)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmCreatePeb
 *
 *  \brief Creates a PEB in the virtual address space of a given process
 *
 *  \param [in] Process - The process for which to allocate the PEB
 *
 *  \param [in] InitialPeb - Pointer to an INITIAL_PEB that contains information
 *              about the new PEB.
 *
 *  \param [out] BasePeb - Pointer to a variable that receives the base address
 *               of the newly created PEB.
 *
 *  \return STATUS_SUCCESS on success, an appropriate error code on failure.
 */
NTSTATUS
NTAPI
MmCreatePeb (
    _In_ PEPROCESS Process,
    _In_ struct _INITIAL_PEB* InitialPeb,
    _Out_ struct _PEB** BasePeb)
{
    SIZE_T Size;
    PVOID TableBase;
    LARGE_INTEGER SectionOffset = {{0}};
    NTSTATUS Status;
    PPEB Peb;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_LOAD_CONFIG_DIRECTORY ImageConfigData;
    ULONG ConfigDataSize;

    /* Attach to the Process */
    KeAttachProcess(&Process->Pcb);

    /* Map the NLS tables */
    TableBase = NULL;
    Size = 0;
    Status = MmMapViewOfSection(ExpNlsSectionPointer,
                                Process,
                                &TableBase,
                                0,
                                0,
                                &SectionOffset,
                                &Size,
                                ViewShare,
                                MEM_TOP_DOWN,
                                PAGE_READONLY);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Allocate virtual memory for the PEB */ /// FIXME: make it secured! (MEM_SECURED)
    Peb = NULL;
    Size = sizeof(PEB);
    Status = AllocateVirtualMemory((PVOID*)&Peb,
                                   0,
                                   &Size,
                                   MEM_RESERVE | MEM_COMMIT,
                                   MM_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    // Initialize the PEB
    Peb->ImageBaseAddress = Process->SectionBaseAddress;
    Peb->InheritedAddressSpace = InitialPeb->InheritedAddressSpace;
    Peb->Mutant = InitialPeb->Mutant;
    Peb->ImageUsesLargePages = InitialPeb->ImageUsesLargePages;
    Peb->AnsiCodePageData = (PCHAR)TableBase + ExpAnsiCodePageDataOffset;
    Peb->OemCodePageData = (PCHAR)TableBase + ExpOemCodePageDataOffset;
    Peb->UnicodeCaseTableData = (PCHAR)TableBase + ExpUnicodeCaseTableDataOffset;
    Peb->OSMajorVersion = NtMajorVersion;
    Peb->OSMinorVersion = NtMinorVersion;
    Peb->OSBuildNumber = (USHORT)(NtBuildNumber & 0x3FFF);
    Peb->OSPlatformId = VER_PLATFORM_WIN32_NT;
    Peb->OSCSDVersion = (USHORT)CmNtCSDVersion;
    Peb->NumberOfProcessors = KeNumberProcessors;
    Peb->BeingDebugged = (BOOLEAN)(Process->DebugPort != NULL);
    Peb->NtGlobalFlag = NtGlobalFlag;
    /*Peb->HeapSegmentReserve = MmHeapSegmentReserve;
     Peb->HeapSegmentCommit = MmHeapSegmentCommit;
     Peb->HeapDeCommitTotalFreeThreshold = MmHeapDeCommitTotalFreeThreshold;
     Peb->HeapDeCommitFreeBlockThreshold = MmHeapDeCommitFreeBlockThreshold;*/
    Peb->CriticalSectionTimeout = MmCriticalSectionTimeout;
    /*Peb->MinimumStackCommit = MmMinimumStackCommitInBytes;
     */
    Peb->MaximumNumberOfHeaps = (PAGE_SIZE - sizeof(PEB)) / sizeof(PVOID);
    Peb->ProcessHeaps = (PVOID*)(Peb + 1);

    //MmGetSessionId(Process);

    /* Use SEH to protect access to image headers */
    _SEH2_TRY
    {
        /* Get the NT headers (32 and 64 bit version are equal for all we need) */
        NtHeaders = RtlImageNtHeader(Peb->ImageBaseAddress);

        // Get the Image Config Data too
        ImageConfigData = (PIMAGE_LOAD_CONFIG_DIRECTORY)
            RtlImageDirectoryEntryToData(Peb->ImageBaseAddress,
                                                       TRUE,
                                                       IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG,
                                                       &ConfigDataSize);
        if (ImageConfigData)
        {
            //
            // Probe it
            //
            ProbeForRead(ImageConfigData,
                         sizeof(IMAGE_LOAD_CONFIG_DIRECTORY),
                         sizeof(ULONG));
        }

        // Write subsystem data
        Peb->ImageSubsystem = NtHeaders->OptionalHeader.Subsystem;
        Peb->ImageSubsystemMajorVersion = NtHeaders->OptionalHeader.MajorSubsystemVersion;
        Peb->ImageSubsystemMinorVersion = NtHeaders->OptionalHeader.MinorSubsystemVersion;

        // Check for version data
        if (NtHeaders->OptionalHeader.Win32VersionValue)
        {
            // Extract values and write them
            Peb->OSMajorVersion = NtHeaders->OptionalHeader.Win32VersionValue & 0xFF;
            Peb->OSMinorVersion = (NtHeaders->OptionalHeader.Win32VersionValue >> 8) & 0xFF;
            Peb->OSBuildNumber = (NtHeaders->OptionalHeader.Win32VersionValue >> 16) & 0x3FFF;
            Peb->OSPlatformId = (NtHeaders->OptionalHeader.Win32VersionValue >> 30) ^ 2;

            /* Process CSD version override */
            if ((ImageConfigData) && (ImageConfigData->CSDVersion))
            {
                /* Take the value from the image configuration directory */
                Peb->OSCSDVersion = ImageConfigData->CSDVersion;
            }
        }

        /* Check if we have an affinity mask and this is not a UP image */
        if ((ImageConfigData) && (ImageConfigData->ProcessAffinityMask) &&
            !(NtHeaders->FileHeader.Characteristics & IMAGE_FILE_UP_SYSTEM_ONLY))
        {
            /* Take the value from the image configuration directory */
            Peb->ImageProcessAffinityMask = ImageConfigData->ProcessAffinityMask;
        }
        else
        {
            /* Use CPU 0 */
            Peb->ImageProcessAffinityMask = 0;
        }
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = STATUS_INVALID_IMAGE_PROTECT;
        _SEH2_YIELD(goto Cleanup);
    }
    _SEH2_END;

    *BasePeb = Peb;
    Status = STATUS_SUCCESS;

Cleanup:

    /* Detach from process */
    KeDetachProcess();

    return Status;
}

/*! \fn MmCreateTeb
 *
 *  \brief Creates a TEB in the virtual address space of a given process
 *
 *  \param [in] Process - The process for which to allocate the TEB
 *
 *  \param [in] ClientId - The client id of the process
 *
 *  \param [in] InitialPeb - Pointer to an INITIAL_TEB that contains information
 *              about the new TEB.
 *
 *  \param [out] BaseTeb - Pointer to a variable that receives the base address
 *               of the newly created TEB.
 *
 *  \return STATUS_SUCCESS on success, an appropriate error code on failure.
 */
NTSTATUS
NTAPI
MmCreateTeb (
    _In_ PEPROCESS Process,
    _In_ PCLIENT_ID ClientId,
    _In_ struct _INITIAL_TEB* InitialTeb,
    _Out_ struct _TEB** BaseTeb)
{
    NTSTATUS Status;
    PTEB Teb;
    SIZE_T Size;

    /* Attach to the Process */
    KeAttachProcess(&Process->Pcb);

    /* Allocate virtual memory for the TEB */ /// FIXME: make it secured! (MEM_SECURED)
    Teb = NULL;
    Size = sizeof(TEB);
    Status = AllocateVirtualMemory((PVOID*)&Teb,
                                   0,
                                   &Size,
                                   MEM_RESERVE | MEM_COMMIT,
                                   MM_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    // Initialize the PEB
    RtlZeroMemory(Teb, sizeof(TEB));
#ifdef _M_AMD64
    Teb->NtTib.ExceptionList = NULL;
#else
    Teb->NtTib.ExceptionList = EXCEPTION_CHAIN_END;
#endif
    Teb->NtTib.Self = (PNT_TIB)Teb;

    // Identify this as an OS/2 V3.0 ("Cruiser") TIB
    Teb->NtTib.Version = 30 << 8;

    // Set TEB Data
    Teb->ClientId = *ClientId;
    Teb->RealClientId = *ClientId;
    Teb->ProcessEnvironmentBlock = Process->Peb;
    Teb->CurrentLocale = PsDefaultThreadLocaleId;

    // Check if we have a grandparent TEB
    if ((InitialTeb->PreviousStackBase == NULL) &&
        (InitialTeb->PreviousStackLimit == NULL))
    {
        // Use initial TEB values
        Teb->NtTib.StackBase = InitialTeb->StackBase;
        Teb->NtTib.StackLimit = InitialTeb->StackLimit;
        Teb->DeallocationStack = InitialTeb->AllocatedStackBase;
    }
    else
    {
        // Use grandparent TEB values
        Teb->NtTib.StackBase = InitialTeb->PreviousStackBase;
        Teb->NtTib.StackLimit = InitialTeb->PreviousStackLimit;
    }

    // Initialize the static unicode string
    Teb->StaticUnicodeString.MaximumLength = sizeof(Teb->StaticUnicodeBuffer);
    Teb->StaticUnicodeString.Buffer = Teb->StaticUnicodeBuffer;

    *BaseTeb = Teb;
    Status = STATUS_SUCCESS;

Cleanup:

    /* Detach from process */
    KeDetachProcess();

    return Status;
}

/*! \fn MmDeleteTeb
 *
 *  \brief Deletes a TEB for a given process.
 *
 *  \param [in] Process - The process for which to delete the TEB
 *
 *  \param [in] Teb - Base address of the TEB to delete.
 *
 *  \return ...
 */
VOID
NTAPI
MmDeleteTeb (
    _In_ struct _EPROCESS *Process,
    _In_ struct _TEB* Teb)
{
    UNIMPLEMENTED;
}

/*! \fn MmInitializeHandBuiltProcess
 *
 *  \brief ...
 *
 *  \param [in] Process -
 *
 *  \param [in] DirectoryTableBase -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmInitializeHandBuiltProcess (
    _In_ PEPROCESS Process,
    _In_ PULONG_PTR DirectoryTableBase)
{
    /* Share the directory base with the idle process */
    DirectoryTableBase[0] = PsGetCurrentProcess()->Pcb.DirectoryTableBase[0];
    DirectoryTableBase[1] = PsGetCurrentProcess()->Pcb.DirectoryTableBase[1];

    /* Initialize the Addresss Space */
    KeInitializeGuardedMutex(&Process->AddressCreationLock);
    KeInitializeSpinLock(&Process->HyperSpaceLock);
    Process->Vm.WorkingSetExpansionLinks.Flink = NULL;
    ASSERT(Process->VadRoot.NumberGenericTableElements == 0);
    Process->VadRoot.BalancedRoot.u1.Parent = &Process->VadRoot.BalancedRoot;

    /* Use idle process Working set */
    Process->Vm.VmWorkingSetList = PsGetCurrentProcess()->Vm.VmWorkingSetList;

    GetProcessAddressSpace(Process)->GetVadTable()->Initialize(FALSE);

    /* Done */
    Process->HasAddressSpace = TRUE;//??
    return STATUS_SUCCESS;
}

/*! \fn MmInitializeHandBuiltProcess2
 *
 *  \brief ...
 *
 *  \param [in] Process -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmInitializeHandBuiltProcess2 (
    _In_ PEPROCESS Process)
{
    /* Nothing to do */
    return STATUS_SUCCESS;
}

/*! \fn MmCreateProcessAddressSpace
 *
 *  \brief ...
 *
 *  \param [in] MinWs -
 *
 *  \param [in] NewProcess -
 *
 *  \param [in] DirectoryTableBase -
 *
 *  \return ...
 */
BOOLEAN
NTAPI
MmCreateProcessAddressSpace (
    _In_ ULONG MinWs,
    _In_ PEPROCESS NewProcess,
    _In_ PULONG_PTR DirectoryTableBase)
{
#ifdef __linux__
    NTSTATUS Status;

    /* Register the process with EAL */
    Status = EalCreateProcessAddressSpace((PSWITCH_BLOCK)NewProcess->Pcb.DirectoryTableBase);
    if (!NT_SUCCESS(Status))
    {
        return FALSE;
    }

    /* Return the table base from the process, KeInitializeProcess, will copy that back */
    DirectoryTableBase[0] = NewProcess->Pcb.DirectoryTableBase[0];
    DirectoryTableBase[1] = NewProcess->Pcb.DirectoryTableBase[1];

    /* Count this process */
    InterlockedIncrement((LONG*)&NumberOfProcesses);

    /* Initialize the process mapping time stamp */
    NewProcess->Spare0[0] = (PVOID)MappingRecordTimeStamp;
    DbgPrint("MmCreateProcessAddressSpace: set time stamp for proc %lx to 0x%x\n",
            PsGetCurrentProcessId(), MappingRecordTimeStamp);

    return TRUE;
#else
    UNIMPLEMENTED;
    return FALSE;
#endif
}

/*! \fn MmInitializeProcessAddressSpace
 *
 *  \brief ...
 *
 *  \param [in] Process -
 *
 *  \param [in] Clone -
 *
 *  \param [in] Section -
 *
 *  \param [in] Flags -
 *
 *  \param [in] AuditName -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmInitializeProcessAddressSpace (
    _In_ PEPROCESS Process,
    _In_opt_ PEPROCESS Clone,
    _In_opt_ PVOID Section,
    _Inout_ PULONG Flags,
    _In_opt_ POBJECT_NAME_INFORMATION *AuditName)
{
    NTSTATUS Status;
    SIZE_T ViewSize = 0;
    PVOID ImageBase = 0;
    PSECTION_OBJECT SectionObject = (PSECTION_OBJECT)Section;
    //PMMPTE PointerPte;
    //KIRQL OldIrql;
    //PFN_NUMBER PageFrameNumber;
    //UNICODE_STRING FileName;
    //PWCHAR Source;
    //PCHAR Destination;
    //USHORT Length = 0;
    PVOID SharedUserPage = (PVOID)MM_SHARED_USER_DATA_VA;

#ifdef __linux__
    /* We should have an initialized SwitchBlock */
    ASSERT(Process->Pcb.DirectoryTableBase[0] == (ULONG)&Process->Pcb.DirectoryTableBase[0]);
#endif

    /* Attach to the process */
    KeAttachProcess(&Process->Pcb);

    /* The address space should now been in phase 1 or 0 */
    ASSERT(Process->AddressSpaceInitialized <= 1);
    Process->AddressSpaceInitialized = 2;

    /* Initialize the Addresss Space lock */
    KeInitializeGuardedMutex(&Process->AddressCreationLock);
    Process->Vm.WorkingSetExpansionLinks.Flink = NULL;

    /* Initialize AVL tree */
    //ASSERT(Process->VadRoot.NumberGenericTableElements == 0);
    //Process->VadRoot.BalancedRoot.u1.Parent = &Process->VadRoot.BalancedRoot;
    GetProcessAddressSpace(Process)->GetVadTable()->Initialize(FALSE);
#ifdef __linux__
    /* Clean out the private usermode address space from 0x10000 - 0x7FFE0000 */
    Status = EalMapVirtualMemory((PVOID)0x10000, 0x7FFE0000 - 0x10000, MM_NOACCESS);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Clean out the private usermode address space from 0x7FFE1000 - 0x7fff0000 */
    Status = EalMapVirtualMemory((PVOID)0x7FFE1000, 0x7fff0000 - 0x7FFE1000, MM_NOACCESS);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }
#endif
    /* Reserve the shared user data address range */
    Status = GetProcessAddressSpace(Process)->ReserveVirtualMemory(&SharedUserPage,
                                                                   1,
                                                                   MM_READONLY);
    NT_ASSERT(NT_SUCCESS(Status));


    /* Check if there's a Section Object */
    if (SectionObject)
    {
#if 0
        /* Determine the image file name and save it to EPROCESS */
        FileName = SectionObject->FileObject->FileName;
        Source = (PWCHAR)((PCHAR)FileName.Buffer + FileName.Length);
        if (FileName.Buffer)
        {
            /* Loop the file name*/
            while (Source > FileName.Buffer)
            {
                /* Make sure this isn't a backslash */
                if (*--Source == OBJ_NAME_PATH_SEPARATOR)
                {
                    /* If so, stop it here */
                    Source++;
                    break;
                }
                else
                {
                    /* Otherwise, keep going */
                    Length++;
                }
            }
        }

        /* Copy the to the process and truncate it to 15 characters if necessary */
        Destination = Process->ImageFileName;
        Length = min(Length, sizeof(Process->ImageFileName) - 1);
        while (Length--) *Destination++ = (UCHAR)*Source++;
        *Destination = ANSI_NULL;

        /* Check if caller wants an audit name */
        if (AuditName)
        {
            /* Setup the audit name */
            Status = SeInitializeProcessAuditName(SectionObject->GetFileObject(),
                                                  FALSE,
                                                  AuditName);
            if (!NT_SUCCESS(Status))
            {
                /* Fail */
                KeDetachProcess();
                return Status;
            }
        }
#endif
        /* Map the section */
        Status = MmMapViewOfSection(Section,
                                    Process,
                                    (PVOID*)&ImageBase,
                                    0,
                                    0,
                                    NULL,
                                    &ViewSize,
                                    ViewUnmap, /// ???
                                    MEM_COMMIT,
                                    PAGE_READWRITE);

        /* Save the pointer */
        Process->SectionBaseAddress = ImageBase;
    }

#ifdef __linux__
Cleanup:
#endif
    /* Detach from the process */
    KeDetachProcess();

    /* Return status to caller */
    return Status;
}

/*! \fn MmCleanProcessAddressSpace
 *
 *  \brief ...
 *
 *  \param [in] Process -
 */
VOID
NTAPI
MmCleanProcessAddressSpace (
    _In_ PEPROCESS Process)
{
    UNIMPLEMENTED;
}

/*! \fn MmDeleteProcessAddressSpace
 *
 *  \brief ...
 *
 *  \param [in] Process -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmDeleteProcessAddressSpace (
    _In_ PEPROCESS Process)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmSetMemoryPriorityProcess
 *
 *  \brief Sets the memory priority for a given process
 *
 *  \param [in] Process - The process for whch to set the memory priority
 *
 *  \param [in] MemoryPriority - The new memory priority
 *
 *  \return The process' previous memory priority
 */
UCHAR
NTAPI
MmSetMemoryPriorityProcess (
    _In_ PEPROCESS Process,
    _In_ UCHAR MemoryPriority)
{
    UCHAR OldPriority;

    /* Save the old priority and update it */
    OldPriority = Process->Vm.Flags.MemoryPriority;
    Process->Vm.Flags.MemoryPriority = MemoryPriority;

    /* Return the old priority */
    return OldPriority;
}

}; // extern "C"
}; // namespace Mm
