/*!

    \file VirtualMemory.cpp

    \brief Implements virtual memory related functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "VirtualMemory.hpp"
#include "AddressSpace.hpp"
#include "VadObject.hpp"
#include "Mapping.hpp"
#include <ndk/ketypes.h>
#include <ndk/pstypes.h>

#define VALID_ALLOCATION_FLAGS (MEM_COMMIT | MEM_RESERVE | MEM_RESET | MEM_PHYSICAL | MEM_TOP_DOWN | MEM_WRITE_WATCH)

namespace Mm {

/*! \fn AllocateVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] ZeroBits -
 *
 *  \param [inout] RegionSize -
 *
 *  \param [in] AllocationType -
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
_Must_inspect_result_
_At_(*BaseAddress, __drv_allocatesMem(Mem))
__kernel_entry
NTSTATUS
AllocateVirtualMemory (
    _Inout_ _Outptr_result_buffer_(*RegionSize) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    PADDRESS_SPACE AddressSpace;
    PVOID AlignedBaseAddress, EndAddress;
    ULONG_PTR Granularity;
    ULONG_PTR NumberOfPages;
    NTSTATUS Status;
    VAD_OBJECT* VadObject;

    /* Make sure we either reserve or commit */
    NT_ASSERT(AllocationType & (MEM_RESERVE | MEM_COMMIT));

    /* Calculate the end-address and align it to pages granularity */
    EndAddress = AddToPointer(*BaseAddress, *RegionSize);
    EndAddress = ALIGN_UP_POINTER_BY(EndAddress, PAGE_SIZE);

    /* Align down the base address to page/allocation granularity */
    Granularity = (AllocationType & MEM_RESERVE) ? 64 * 1024 : PAGE_SIZE;
    AlignedBaseAddress = ALIGN_DOWN_POINTER_BY(*BaseAddress, Granularity);

    /* We cannot allocate at address 0! */
    if ((*BaseAddress != NULL) && (AlignedBaseAddress == NULL))
    {
        ERR("Tried to allocate at address 0\n");
        return STATUS_INVALID_PARAMETER;
    }

    /* Save the aligned base address */
    *BaseAddress = AlignedBaseAddress;

    /* Calculate the size of the aligned region */
    *RegionSize = reinterpret_cast<ULONG_PTR>(EndAddress) -
                  reinterpret_cast<ULONG_PTR>(*BaseAddress);
    NumberOfPages = BYTES_TO_PAGES(*RegionSize);

    /* Get current process address space */
    AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());

    /* Check if we need to reserve memory */
    if (AllocationType & MEM_RESERVE)
    {
        /* Allocate a VAD object */
        Status = VAD_OBJECT::CreateInstance(&VadObject, Protect);
        if (!NT_SUCCESS(Status))
        {
            ERR("Failed to allocate VAD object: 0x%lx\n", Status);
            return Status;
        }

        /* Insert the VAD object into the address space */
        Status = AddressSpace->InsertVadObject(VadObject,
                                               BaseAddress,
                                               NumberOfPages,
                                               ZeroBits,
                                               AllocationType);
        if (!NT_SUCCESS(Status))
        {
            ERR("Failed to insert VAD object into address space: %x\n", Status);
            VadObject->Release();
            return Status;
        }
    }
    else
    {
        /* Reference the VAD object for the given address */
        VadObject = AddressSpace->ReferenceVadObjectByAddress(*BaseAddress, FALSE);
        if (VadObject == NULL)
        {
            ERR("Trying to commit memory that was not reserved!");
            return STATUS_NOT_COMMITTED;
        }
    }

    /* Check if we need to commit memory */
    if (AllocationType & MEM_COMMIT)
    {
        /* Commit the pages of the reserved region */
        Status = VadObject->CommitPages(AddressToVpn(*BaseAddress),
                                        NumberOfPages,
                                        Protect);
    }

    /* Release the VAD object */
    VadObject->Release();

    if (!NT_SUCCESS(Status))
    {
        /* Did we also reserve? */
        if (AllocationType & MEM_RESERVE)
        {
            /* Release the reserved memory as well */
            AddressSpace->ReleaseVirtualMemory(*BaseAddress);
        }
    }

    return STATUS_SUCCESS;
}

extern "C" {

/*! \fn MmSecureVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] Address -
 *
 *  \param [in] Size -
 *
 *  \param [in] ProbeMode -
 *
 *  \return ...
 */
_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
HANDLE
NTAPI
MmSecureVirtualMemory (
    __in_data_source(USER_MODE) _In_reads_bytes_ (Size) PVOID Address,
    _In_ __in_data_source(USER_MODE) SIZE_T Size,
    _In_ ULONG ProbeMode)
{
    UNIMPLEMENTED;
    return 0;
}

/*! \fn MmUnsecureVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] SecureHandle -
 *
 *  \return ...
 */
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmUnsecureVirtualMemory (
    _In_ HANDLE SecureHandle)
{
    UNIMPLEMENTED;
}


/*! \name NtAllocateVirtualMemory
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [inout] BaseAddress -
 *
 *  \param [in] ZeroBits -
 *
 *  \param [inout] RegionSize -
 *
 *  \param [in] AllocationType -
 *      The lowest 5 bits encode the NUMA node, if all 5 bits are 0, the ideal
 *      processor's NUMA node is used, otherwise the node number is calculated
 *      by masking the lowest 5 bits and subtracting 1.
 *
 *  \param [in] Win32Protect -
 *
 *  \return ...
 */
_Must_inspect_result_
_At_(*BaseAddress, __drv_allocatesMem(Mem))
__kernel_entry
NTSTATUS
NTAPI
NtAllocateVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ _Outptr_result_buffer_(*RegionSize) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect)
{
    KPROCESSOR_MODE PreviousMode;
    PVOID CapturedBaseAddress;
    SIZE_T CapturedRegionSize;
    KAPC_STATE SavedApcState;
    PEPROCESS Process;
    ULONG Protect;
    NTSTATUS Status;

    /* Check ZeroBits parameter */
    if (ZeroBits > 21)
    {
        ERR("ZeroBits is larger than 21.\n");
        return STATUS_INVALID_PARAMETER_3;
    }

    /* Check AllocationType parameter */
    if ((AllocationType & ~VALID_ALLOCATION_FLAGS) ||
        ((AllocationType & (MEM_COMMIT | MEM_RESERVE | MEM_RESET)) == 0))
    {
        ERR("Invalid AllocationType: 0x%lx\n", AllocationType);
        return STATUS_INVALID_PARAMETER_5;
    }

    /* MEM_RESET is an exclusive flag, make sure that is valid too */
    if ((AllocationType & MEM_RESET) && (AllocationType != MEM_RESET))
    {
        ERR("MEM_RESET not used exclusively.\n");
        return STATUS_INVALID_PARAMETER_5;
    }

    /* Check if large pages are being used */
    if (AllocationType & MEM_LARGE_PAGES)
    {
        /* Large page allocations MUST be committed */
        if (!(AllocationType & MEM_COMMIT))
        {
            ERR("Must supply MEM_COMMIT with MEM_LARGE_PAGES\n");
            return STATUS_INVALID_PARAMETER_5;
        }

        /* These flags are not allowed with large page allocations */
        if (AllocationType & (MEM_PHYSICAL | MEM_RESET | MEM_WRITE_WATCH))
        {
            ERR("Using illegal flags with MEM_LARGE_PAGES\n");
            return STATUS_INVALID_PARAMETER_5;
        }
    }

    /* MEM_WRITE_WATCH can only be used if MEM_RESERVE is also used */
    if ((AllocationType & MEM_WRITE_WATCH) && !(AllocationType & MEM_RESERVE))
    {
        ERR("MEM_WRITE_WATCH used without MEM_RESERVE\n");
        return STATUS_INVALID_PARAMETER_5;
    }

    /* MEM_PHYSICAL can only be used if MEM_RESERVE is also used */
    if ((AllocationType & MEM_PHYSICAL) && !(AllocationType & MEM_RESERVE))
    {
        ERR("MEM_WRITE_WATCH used without MEM_RESERVE\n");
        return STATUS_INVALID_PARAMETER_5;
    }

    /* Check for valid MEM_PHYSICAL usage */
    if (AllocationType & MEM_PHYSICAL)
    {
        /* Only these flags are allowed with MEM_PHYSIAL */
        if (AllocationType & ~(MEM_RESERVE | MEM_TOP_DOWN | MEM_PHYSICAL))
        {
            ERR("Using illegal flags with MEM_PHYSICAL\n");
            return STATUS_INVALID_PARAMETER_5;
        }

        /* Then make sure PAGE_READWRITE is used */
        if (Win32Protect != PAGE_READWRITE)
        {
            ERR("MEM_PHYSICAL used without PAGE_READWRITE\n");
            return STATUS_INVALID_PARAMETER_6;
        }
    }

    /* Convert the win32 protection */
    Protect = ConvertProtect(Win32Protect);
    if (Protect == -1)
    {
        ERR("Invalid page protection: 0x%lx\n", Win32Protect);
        return STATUS_INVALID_PAGE_PROTECTION;
    }

    /* Get the previous mode and check if this was user mode */
    PreviousMode = ExGetPreviousMode();
    if (PreviousMode != KernelMode)
    {
        /* Called from user mode, use SEH to access parameters */
        _SEH2_TRY
        {
            ProbeForWrite(BaseAddress, sizeof(*BaseAddress), sizeof(*BaseAddress));
            CapturedBaseAddress = *BaseAddress;
            ProbeForWrite(RegionSize, sizeof(*RegionSize), sizeof(*RegionSize));
            CapturedRegionSize = *RegionSize;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            /* Return the exception code */
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END;
    }
    else
    {
        /* Kernel mode, just copy the parameters */
        CapturedBaseAddress = *BaseAddress;
        CapturedRegionSize = *RegionSize;
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
            ERR("Invalid ProcessHandle.\n");
            return Status;
        }

        /* Attach to it */
        KeStackAttachProcess(&Process->Pcb, &SavedApcState);
    }

    /* Check if address should be chosen automatically */
    if (CapturedBaseAddress == NULL)
    {
        /* This means the caller wants to reserve memory */
        AllocationType |= MEM_RESERVE;
    }

    /* Call the internal function */
    Status = AllocateVirtualMemory(&CapturedBaseAddress,
                                   ZeroBits,
                                   &CapturedRegionSize,
                                   AllocationType,
                                   Win32Protect);

    /* Check if we attached to a process */
    if (ProcessHandle != NtCurrentProcess())
    {
        /* Detach and dereference process */
        KeUnstackDetachProcess(&SavedApcState);
        ObDereferenceObject(Process);
    }

    if (NT_SUCCESS(Status))
    {
        if (PreviousMode != KernelMode)
        {
            /* Use SEH to copy the data back (pointers are already probed) */
            _SEH2_TRY
            {
                *BaseAddress = CapturedBaseAddress;
                *RegionSize = CapturedRegionSize;
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
            *BaseAddress = CapturedBaseAddress;
            *RegionSize = CapturedRegionSize;
        }
    }

    return Status;
}

/*! \fn NtFreeVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [inout] BaseAddress -
 *
 *  \param [inout] RegionSize -
 *
 *  \param [in] FreeType -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtFreeVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn NtFlushVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [inout] BaseAddress -
 *
 *  \param [inout] RegionSize -
 *
 *  \param [out] IoStatus -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtFlushVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn NtProtectVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] NumberOfBytesToProtect -
 *
 *  \param [in] NewAccessProtection -
 *
 *  \param [out] OutOldAccessProtection -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtProtectVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID *BaseAddress,
    _In_ SIZE_T *NumberOfBytesToProtect,
    _In_ ULONG NewAccessProtection,
    _Out_ PULONG OutOldAccessProtection)
{
    PEPROCESS Process;
    ULONG OldAccessProtection;
    ULONG Protection;
    PVOID CapturedBaseAddress = NULL;
    SIZE_T NumberOfBytes = 0;
    KPROCESSOR_MODE PreviousMode = ExGetPreviousMode();
    NTSTATUS Status;
    BOOLEAN Attached = FALSE;
    KAPC_STATE ApcState;
    ULONG Protect;
    ULONG NumberOfPages;
    PAGED_CODE();

//__debugbreak();

    /* Check for valid protection flags */
    Protection = NewAccessProtection & ~(PAGE_GUARD|PAGE_NOCACHE);
    if (Protection != PAGE_NOACCESS &&
        Protection != PAGE_READONLY &&
        Protection != PAGE_READWRITE &&
        Protection != PAGE_WRITECOPY &&
        Protection != PAGE_EXECUTE &&
        Protection != PAGE_EXECUTE_READ &&
        Protection != PAGE_EXECUTE_READWRITE &&
        Protection != PAGE_EXECUTE_WRITECOPY)
    {
        return STATUS_INVALID_PAGE_PROTECTION;
    }

    /* Check if we came from user mode */
    if (PreviousMode != KernelMode)
    {
        // Enter SEH for probing
        _SEH2_TRY
        {
            // Validate all outputs
            ProbeForWrite(BaseAddress, sizeof(PVOID), sizeof(PVOID));
            ProbeForWrite(NumberOfBytesToProtect, sizeof(SIZE_T), sizeof(SIZE_T));
            ProbeForWrite(OutOldAccessProtection, sizeof(ULONG), sizeof(ULONG));

            // Capture them
            CapturedBaseAddress = *BaseAddress;
            NumberOfBytes = *NumberOfBytesToProtect;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END;
    }
    else
    {
        // Capture directly
        CapturedBaseAddress = *BaseAddress;
        NumberOfBytes = *NumberOfBytesToProtect;
    }

    // Catch illegal base address
    if (CapturedBaseAddress > MmHighestUserAddress)
    {
        return STATUS_INVALID_PARAMETER_2;
    }

    /* Check if the size is valid */
    if ((NumberOfBytes == 0) ||
        ((MmUserProbeAddress - (ULONG_PTR)CapturedBaseAddress) < NumberOfBytes))
    {
        return STATUS_INVALID_PARAMETER_3;
    }

    /* Check if we have a foreign process */
    if (ProcessHandle != NtCurrentProcess())
    {
        /* Reference the process */
        Status = ObReferenceObjectByHandle(ProcessHandle,
                                           PROCESS_VM_OPERATION,
                                           PsProcessType,
                                           PreviousMode,
                                           (PVOID*)(&Process),
                                           NULL);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        /* Attach to the process */
        KeStackAttachProcess(&Process->Pcb, &ApcState);
        Attached = TRUE;
    }

    Protect = ConvertProtect(NewAccessProtection);

    /* Calculate page aligned values */
    NumberOfPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(CapturedBaseAddress, NumberOfBytes);
    NumberOfBytes = NumberOfPages * PAGE_SIZE;
    CapturedBaseAddress = ALIGN_DOWN_POINTER_BY(CapturedBaseAddress, PAGE_SIZE);

    // Do the actual work
    Status = ProtectVirtualMemory(AddressToVpn(CapturedBaseAddress),
                                  NumberOfPages,
                                  Protect,
                                  &Protect);

    OldAccessProtection = ConvertProtectToWin32(Protect);

    /* Check if we need to detach from the process */
    if (ProcessHandle != NtCurrentProcess())
    {
        KeUnstackDetachProcess(&ApcState);
        ObDereferenceObject(Process);
    }

    /* Check if we came from user mode */
    if (PreviousMode != KernelMode)
    {
        // Enter SEH to return data
        _SEH2_TRY
        {
            // Return data to user
            *OutOldAccessProtection = OldAccessProtection;
            *BaseAddress = CapturedBaseAddress;
            *NumberOfBytesToProtect = NumberOfBytes;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
        }
        _SEH2_END;
    }
    else
    {
        *OutOldAccessProtection = OldAccessProtection;
        *BaseAddress = CapturedBaseAddress;
        *NumberOfBytesToProtect = NumberOfBytes;
    }

    // Return status
    return Status;
}

/*! \fn QueryMemoryBasicInformation
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [out] Information -
 *
 *  \param [in] BufferSize -
 *
 *  \return ...
 */
NTSTATUS
QueryMemoryBasicInformation (
    _In_ PVOID BaseAddress,
    _Out_ PMEMORY_BASIC_INFORMATION Information,
    _In_ SIZE_T BufferSize)
{
    PADDRESS_SPACE AddressSpace;
    PVAD_OBJECT VadObject;
    ULONG Protect;
    PVOID VadBaseAddress, EndAddress;

    /* Get current process address space */
    AddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());

    /// find VAD for address
    VadObject = AddressSpace->ReferenceVadObjectByAddress(BaseAddress, TRUE);

    if (VadObject != NULL)
    {
        /* Get the VAD's base address */
        VadBaseAddress = VadObject->GetBaseAddress();

        /* Check if the given address is within this VAD */
        if (VadBaseAddress <= BaseAddress)
        {
            /* We found the VAD, use it's information */
            Information->BaseAddress = ALIGN_DOWN_POINTER_BY(BaseAddress, PAGE_SIZE);
            Information->AllocationBase = VadBaseAddress;
            Information->AllocationProtect = ConvertProtectToWin32(VadObject->GetProtect());
            Information->Type = VadObject->GetMemoryType();

            /* Check the actual mappings */
            CheckVirtualMapping(Information->BaseAddress,
                                &Information->RegionSize,
                                &Protect);
            Information->Protect = ConvertProtectToWin32(Protect);
            Information->State = (Protect == MM_INVALID) ? MEM_FREE : MEM_PRIVATE;

            /* Release the VAD object */
            VadObject->Release();

            return STATUS_SUCCESS;
        }
        else
        {
            /* This is the hext higher VAD, the region ends at it's base address */
            EndAddress = VadBaseAddress;
        }

        /* Release the VAD object */
        VadObject->Release();
    }
    else
    {
        EndAddress = (PVOID)MmUserProbeAddress;
    }

    /* There is no VAD at the given address, so this memory is free */
    Information->BaseAddress = ALIGN_DOWN_POINTER_BY(BaseAddress, PAGE_SIZE);
    Information->AllocationBase = NULL;
    Information->AllocationProtect = 0;
    Information->RegionSize = (ULONG_PTR)EndAddress - (ULONG_PTR)Information->BaseAddress;
    Information->State = MEM_FREE;
    Information->Protect = PAGE_NOACCESS;
    Information->Type = 0;

    return STATUS_SUCCESS;
}

/*! \fn QueryMemorySectionName
 *
 *  \brief ...
 *
 *  \param [in] BaseAddress -
 *
 *  \param [out] MemorySectionName -
 *
 *  \param [in] BufferSize -
 *
 *  \param [out] ResultLength -
 *
 *  \return ...
 */
NTSTATUS
QueryMemorySectionName (
    _In_ PVOID BaseAddress,
    _Out_ PMEMORY_SECTION_NAME MemorySectionName,
    _In_ SIZE_T BufferSize,
    _Out_ PSIZE_T ResultLength)
{
    UNIMPLEMENTED;
    __debugbreak();
    return 0;
}

/*! \fn NtQueryVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] MemoryInformationClass -
 *
 *  \param [out] MemoryInformation -
 *
 *  \param [in] InfoBufferSize -
 *
 *  \param [out] ResultLength -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtQueryVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ enum _MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_ PVOID MemoryInformation,
    _In_ SIZE_T InfoBufferSize,
    _Out_opt_ PSIZE_T ResultLength)
{
    NTSTATUS Status = STATUS_SUCCESS;
    KPROCESSOR_MODE PreviousMode;
    SIZE_T InformationSize;
    PEPROCESS Process;
    KAPC_STATE ApcState;
    union
    {
        MEMORY_BASIC_INFORMATION BasicInformation;
        struct
        {
            MEMORY_SECTION_NAME SectionName;
            WCHAR SectionNameBuffer[MAX_PATH];
        };
    } StackBuffer;

    //DPRINT("Querying class %d about address: %p\n", MemoryInformationClass, BaseAddress);

    /* Check if the address is valid */
    if (BaseAddress > MmHighestUserAddress)
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Probe return buffer */
    PreviousMode =  ExGetPreviousMode();
    if (PreviousMode != KernelMode)
    {
        _SEH2_TRY
        {
            ProbeForWrite(MemoryInformation, InfoBufferSize, sizeof(ULONG_PTR));
            if (ResultLength != NULL)
                ProbeForWrite(ResultLength, sizeof(SIZE_T), sizeof(SIZE_T));
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END;
    }

    /* Check if we have a foreign process */
    if (ProcessHandle != NtCurrentProcess())
    {
        /* Reference the process */
        Status = ObReferenceObjectByHandle(ProcessHandle,
                                           PROCESS_VM_OPERATION,
                                           PsProcessType,
                                           PreviousMode,
                                           (PVOID*)(&Process),
                                           NULL);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        /* Attach to the process */
        KeStackAttachProcess(&Process->Pcb, &ApcState);
    }

    switch (MemoryInformationClass)
    {
        case MemoryBasicInformation:

            /* Validate the size information of the class */
            InformationSize = sizeof(MEMORY_BASIC_INFORMATION);
            if (InfoBufferSize < InformationSize)
            {
                /* The size is invalid */
                return STATUS_INFO_LENGTH_MISMATCH;
            }

            Status = QueryMemoryBasicInformation(BaseAddress,
                                                 &StackBuffer.BasicInformation,
                                                 InformationSize);
            break;

        case MemorySectionName:

            /* Validate the size information of the class */
            if (InfoBufferSize < sizeof(MEMORY_SECTION_NAME))
            {
                /* The size is invalid */
                return STATUS_INFO_LENGTH_MISMATCH;
            }

            Status = QueryMemorySectionName(BaseAddress,
                                            &StackBuffer.SectionName,
                                            sizeof(StackBuffer),
                                            &InformationSize);
            break;

        case MemoryWorkingSetList:
        case MemoryBasicVlmInformation:
        default:
            ERR("Unhandled memory information class %d\n", MemoryInformationClass);
            break;
    }

    InfoBufferSize = min(InfoBufferSize, InformationSize);

    /* Return the data, NtQueryInformation already probed it*/
    if (PreviousMode != KernelMode)
    {
        _SEH2_TRY
        {
            RtlCopyMemory(MemoryInformation, &StackBuffer, InfoBufferSize);
            if (ResultLength)
            {
                *ResultLength = InformationSize;
            }
        }
         _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            Status = _SEH2_GetExceptionCode();
        }
        _SEH2_END;
    }
    else
    {
        RtlCopyMemory(MemoryInformation, &StackBuffer, InfoBufferSize);
        if (ResultLength)
        {
            *ResultLength = InformationSize;
        }
    }

    /* Check if we need to detach from the process */
    if (ProcessHandle != NtCurrentProcess())
    {
        KeUnstackDetachProcess(&ApcState);
        ObDereferenceObject(Process);
    }

    return Status;
}

/*! \fn NtLockVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [inout] BaseAddress -
 *
 *  \param [inout] NumberOfBytesToLock -
 *
 *  \param [in] MapType -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtLockVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T NumberOfBytesToLock,
    _In_ ULONG MapType)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn NtUnlockVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [inout] BaseAddress -
 *
 *  \param [inout] NumberOfBytesToUnlock -
 *
 *  \param [in] MapType -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtUnlockVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T NumberOfBytesToUnlock,
    _In_ ULONG MapType)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn NtReadVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [in] BaseAddress -
 *
 *  \param [out] Buffer -
 *
 *  \param [in] NumberOfBytesToRead -
 *
 *  \param [out] NumberOfBytesRead -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtReadVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _Out_ PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToRead,
    _Out_opt_ PSIZE_T NumberOfBytesRead)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn NtWriteVirtualMemory
 *
 *  \brief ...
 *
 *  \param [in] ProcessHandle -
 *
 *  \param [in] BaseAddress -
 *
 *  \param [in] Buffer -
 *
 *  \param [in] NumberOfBytesToWrite -
 *
 *  \param [out] NumberOfBytesWritten -
 *
 *  \return ...
 */
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtWriteVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToWrite,
    _Out_opt_ PSIZE_T NumberOfBytesWritten)
{
    KPROCESSOR_MODE PreviousMode;
    PKPROCESS TargetProcess;
    KAPC_STATE ApcState;
    PVOID SafeBuffer;
    NTSTATUS Status;

    PreviousMode = ExGetPreviousMode();

    /* Refernce the process handle */
    Status = ObReferenceObjectByHandle(ProcessHandle,
                                       PROCESS_VM_WRITE,
                                       PsProcessType,
                                       PreviousMode,
                                       (PVOID*)&TargetProcess,
                                       NULL);
    if (!NT_SUCCESS(Status))
    {
        __debugbreak();
        return Status;
    }

    /* Allocate an intermediate buffer */
    SafeBuffer = ExAllocatePoolWithTag(PagedPool, NumberOfBytesToWrite, 'fBmM');
    if (SafeBuffer == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Cleanup;
    }

    /* SEH protect memory access */
    _SEH2_TRY
    {
        /* Check if the caller was from user mode */
        if (PreviousMode != KernelMode)
        {
            /* Probe the usermode buffer */
            ProbeForRead(Buffer, NumberOfBytesToWrite, 1);
        }

        /* Copy the memory to the intermediate buffer */
        RtlCopyMemory(SafeBuffer, Buffer, NumberOfBytesToWrite);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = _SEH2_GetExceptionCode();
        _SEH2_YIELD(goto Cleanup);
    }
    _SEH2_END;

    /* Attach to the target process */
    KeStackAttachProcess(TargetProcess, &ApcState);

    /* Assume success */
    Status = STATUS_SUCCESS;

    /* SEH protect memory access */
    _SEH2_TRY
    {
        /* Probe and copy the memory to the intermediate buffer */
        ProbeForWrite(BaseAddress, NumberOfBytesToWrite, 1);
        RtlCopyMemory(BaseAddress, SafeBuffer, NumberOfBytesToWrite);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = _SEH2_GetExceptionCode();
    }
    _SEH2_END;

    /* Detach fron the target process */
    KeUnstackDetachProcess(&ApcState);

Cleanup:
    /* Check if we allocated a temp buffer */
    if ((SafeBuffer != NULL) && (SafeBuffer != Buffer))
    {
        /* Free the temp buffer */
        ExFreePoolWithTag(SafeBuffer, 'fBmM');
    }

    /* Dereference the process */
    ObDereferenceObject(TargetProcess);

    return Status;
}

}; // extern "C"
}; // namespace Mm
