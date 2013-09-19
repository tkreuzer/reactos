/*!
 * \file SectionObject.cpp
 * ...
 */

#include "SectionObject.hpp"
#include "PhysicalSection.hpp"
#include <ndk/iotypes.h>
#include <ndk/obfuncs.h>

POBJECT_TYPE MmSectionObjectType;

#define RTL_CONSTANT_STRING2(s)  { sizeof(s)-sizeof((s)[0]), sizeof(s), (PWCHAR)(s) }
namespace Mm {

VOID
SECTION_OBJECT::InitializeClass (
    VOID)
{
    static const UNICODE_STRING ObjectName = RTL_CONSTANT_STRING2(L"Section");
    static const GENERIC_MAPPING GenericMapping =
    {
        STANDARD_RIGHTS_READ | SECTION_MAP_READ | SECTION_QUERY,
        STANDARD_RIGHTS_WRITE | SECTION_MAP_WRITE,
        STANDARD_RIGHTS_EXECUTE | SECTION_MAP_EXECUTE,
        SECTION_ALL_ACCESS
    };
    OBJECT_TYPE_INITIALIZER ObjectTypeInitializer = { 0 };
    NTSTATUS Status;

    /* Setup the object type initializer */
    ObjectTypeInitializer.Length = sizeof(ObjectTypeInitializer);
    ObjectTypeInitializer.UseDefaultObject = TRUE;
    ObjectTypeInitializer.CaseInsensitive = FALSE;
    ObjectTypeInitializer.InvalidAttributes = OBJ_OPENLINK;
    ObjectTypeInitializer.GenericMapping = GenericMapping;
    ObjectTypeInitializer.ValidAccessMask = SECTION_ALL_ACCESS;
    ObjectTypeInitializer.SecurityRequired = FALSE;
    ObjectTypeInitializer.MaintainHandleCount = FALSE;
    ObjectTypeInitializer.MaintainTypeList = FALSE;
    ObjectTypeInitializer.PoolType = PagedPool;
    ObjectTypeInitializer.DefaultPagedPoolCharge = sizeof(SECTION_OBJECT);
    ObjectTypeInitializer.DumpProcedure = NULL;
    ObjectTypeInitializer.OpenProcedure = NULL;
    ObjectTypeInitializer.CloseProcedure = &SECTION_OBJECT::ObCloseProcedure;
    ObjectTypeInitializer.DeleteProcedure = &SECTION_OBJECT::ObDeleteProcedure;
    ObjectTypeInitializer.ParseProcedure = NULL;
    ObjectTypeInitializer.SecurityProcedure = NULL;
    ObjectTypeInitializer.QueryNameProcedure = NULL;
    ObjectTypeInitializer.OkayToCloseProcedure = NULL;

    /* Create the section object type */
    Status = ObCreateObjectType(const_cast<PUNICODE_STRING>(&ObjectName),
                                &ObjectTypeInitializer,
                                NULL,
                                &MmSectionObjectType);
    if (!NT_SUCCESS(Status))
    {
        /// \todo proper bugcheck params
        KeBugCheck(0);
    }


}

VOID
NTAPI
SECTION_OBJECT::ObDeleteProcedure (
    _In_ PVOID Object)
{
    DbgPrint("TODO: SECTION_OBJECT::ObDeleteProcedure is UNIMPLEMENTED!\n");
    //__debugbreak();
}

VOID
NTAPI
SECTION_OBJECT::ObCloseProcedure (
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ULONG ProcessHandleCount,
    _In_ ULONG SystemHandleCount)
{
    DbgPrint("TODO: SECTION_OBJECT::ObCloseProcedure is UNIMPLEMENTED!\n");
}

VOID
AcquireFileForSectionSynchronization (
    PFILE_OBJECT FileObject)
{

}


_Must_inspect_result_
NTSTATUS
SECTION_OBJECT::CreateInstance (
    _Out_ SECTION_OBJECT** OutSectionObject,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG64 MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ PFILE_OBJECT FileObject)
{
    PVOID Object;
    PSECTION_OBJECT SectionObject;
    PPHYSICAL_SECTION Section;
    NTSTATUS Status;

    /* Check if this is a file backed section */
    if (FileObject == NULL)
    {
        /* No backing file, so create a new page-file backed SECTION */
        Status = PHYSICAL_SECTION::CreatePageFileSection(&Section,
                                                         MaximumSize,
                                                         SectionPageProtection,
                                                         AllocationAttributes);
        if (!NT_SUCCESS(Status))
        {
            ERR("Failed to create SECTION: 0x%lx\n", Status);
            return Status;
        }
    }
    else
    {
        Status = PHYSICAL_SECTION::ReferenceOrCreateFileSection(&Section,
                                                                FileObject,
                                                                AllocationAttributes);
    }

    /* Allocate a section object with the object manager */
    Status = Ob::OBJECT::CreateObject(&Object,
                                      MmSectionObjectType,
                                      ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to create a section object: 0x%lx\n", Status);
        Section->Release();
        return Status;
    }

    /* Initialize the object */
    SectionObject = new(Object) SECTION_OBJECT;
    SectionObject->m_Section = Section;
    SectionObject->m_SectionSize = MaximumSize;
    SectionObject->m_SectionFlags = 0;
    SectionObject->m_PageProtection = SectionPageProtection;

    /* Return the section object */
    *OutSectionObject = SectionObject;

    return STATUS_SUCCESS;
}

class PHYSICAL_SECTION*
SECTION_OBJECT::ReferenceSection (
    VOID)
{
    m_Section->AddRef();
    return m_Section;
}

inline
PFILE_OBJECT
SECTION_OBJECT::GetFileObject (
    VOID)
{
    return 0;//m_FileObject;
}

extern "C" {

/** Internal API **************************************************************/

PFILE_OBJECT
NTAPI
MmGetFileObjectForSection (
    _In_ PVOID SectionObject)
{
    return static_cast<PSECTION_OBJECT>(SectionObject)->GetFileObject();
}

NTSTATUS
NTAPI
MmGetFileNameForSection (
    _In_ PVOID SectionObject,
    _Out_ POBJECT_NAME_INFORMATION *ModuleName)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

ULONG
CalculateFileAccess (
    _In_ ULONG PageProtection)
{
    switch (PageProtection & 0xFF)
    {
        case PAGE_NOACCESS: return FILE_READ_DATA;
        case PAGE_READONLY: return FILE_READ_DATA;
        case PAGE_READWRITE: return FILE_READ_DATA | FILE_WRITE_DATA;
        case PAGE_WRITECOPY: return FILE_READ_DATA;
        case PAGE_EXECUTE: return FILE_EXECUTE;
        case PAGE_EXECUTE_READ: return FILE_EXECUTE | FILE_READ_DATA;
        case PAGE_EXECUTE_READWRITE: return FILE_EXECUTE | FILE_READ_DATA | FILE_WRITE_DATA;
    }

    return FILE_EXECUTE | FILE_READ_DATA | FILE_WRITE_DATA;
}

/** Exported API **************************************************************/

_Must_inspect_result_
NTSTATUS
NTAPI
MmCreateSection (
    _Out_ PVOID* OutSectionObject,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _In_opt_ PFILE_OBJECT FileObject)
{
    SECTION_OBJECT* SectionObject;
    ACCESS_MASK FileAccess;
    NTSTATUS Status;

    /* This is not used here */
    UNREFERENCED_PARAMETER(DesiredAccess);

    /* Check if we should use the file object */
    if (FileObject != NULL)
    {
        /* In this case, ignore the file handle */
        FileHandle = NULL;
    }
    else if (FileHandle != NULL)
    {
        /* Reference the file handle */
#if 0
        Status = FILE_OBJECT::ReferenceByHandle(FileHandle,
                                                DesiredAccess,
                                                ExGetPreviousMode(),
                                                &FileObject);
#endif
        /* Calculate access mask */
        FileAccess = CalculateFileAccess(SectionPageProtection);

        /* Reference the file object */
        Status = ObReferenceObjectByHandle(FileHandle,
                                           FileAccess,
                                           IoFileObjectType,
                                           ExGetPreviousMode(),
                                           reinterpret_cast<PVOID*>(&FileObject),
                                           NULL);
        if (!NT_SUCCESS(Status))
        {
            //ERR();
            return Status;
        }
    }

    /* Create the section object */
    Status = SECTION_OBJECT::CreateInstance(&SectionObject,
                                            ObjectAttributes,
                                            MaximumSize->QuadPart,
                                            SectionPageProtection,
                                            AllocationAttributes,
                                            FileObject);


    *OutSectionObject = static_cast<PVOID>(SectionObject);

    /* Did we take a reference on the file object? */
    if (FileHandle != NULL)
    {
        /* Cleanup the reference */
        ObDereferenceObject(FileObject);
    }

    return Status;
}

/** Syscall API ***************************************************************/

NTSTATUS
NTAPI
NtCreateSection (
    _Out_ PHANDLE OutSectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle)
{
    OBJECT_ATTRIBUTES SafeObjectAttributes;
    LARGE_INTEGER SafeMaximumSize;
    PVOID SectionObject;
    HANDLE SectionHandle;
    NTSTATUS Status;
    //TRACE("Entered\n");


    /// \todo check parameters

    /* Check if this call comes from user mode */
    if (ExGetPreviousMode() != KernelMode)
    {
        /* Use SEH to copy the buffers */
        _SEH2_TRY
        {
            if (MaximumSize != NULL)
            {
                ProbeForRead(MaximumSize, sizeof(*MaximumSize), 1);
                SafeMaximumSize = *MaximumSize;
                MaximumSize = &SafeMaximumSize;
            }

            if (ObjectAttributes != NULL)
            {
                ProbeForRead(ObjectAttributes, sizeof(*ObjectAttributes), 1);
                SafeObjectAttributes = *ObjectAttributes;
                ObjectAttributes = &SafeObjectAttributes;
            }
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            //ERR("Could not
            _SEH2_YIELD(return _SEH2_GetExceptionCode();)
        }
        _SEH2_END;
    }

    if (MaximumSize == NULL)
    {
        SafeMaximumSize.QuadPart = 0;
        MaximumSize = &SafeMaximumSize;
    }

    /* Call the exported function */
    Status = MmCreateSection(&SectionObject,
                             DesiredAccess,
                             ObjectAttributes,
                             MaximumSize,
                             SectionPageProtection,
                             AllocationAttributes,
                             FileHandle,
                             NULL);
    if (NT_SUCCESS(Status))
    {
        /* Insert the object */
        Status = ObInsertObject(SectionObject,
                                NULL,
                                DesiredAccess,
                                0,
                                NULL,
                                &SectionHandle);
        if (NT_SUCCESS(Status))
        {
            /* Check if this call comes from user mode */
            if (ExGetPreviousMode() != KernelMode)
            {
                /* Use SEH to return the handle */
                _SEH2_TRY
                {
                    ProbeForWrite(OutSectionHandle, sizeof(HANDLE), sizeof(HANDLE));
                    *OutSectionHandle = SectionHandle;
                }
                _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
                {
                    ERR("Exception!\n");
                    Status = _SEH2_GetExceptionCode();
                }
                _SEH2_END;
            }
            else
            {
                /* Return the section handle */
                *OutSectionHandle = SectionHandle;
            }
        }
        else
        {
            /* Could not insert the object, so dereference it */
            ObDereferenceObject(SectionObject);
        }
    }

    return Status;
}

NTSTATUS
NTAPI
NtOpenSection (
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    KPROCESSOR_MODE PreviousMode;
    NTSTATUS Status;
    HANDLE Handle;

    /* Get the previous mode and check if it's user mode */
    PreviousMode = ExGetPreviousMode();
    if (PreviousMode != KernelMode)
    {
        /* Use SEH to probe the output argument */
        _SEH2_TRY
        {
            /* Probe the output parameter */
            ProbeForWrite(SectionHandle, sizeof(HANDLE), sizeof(HANDLE));
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            /* Return the exception code */
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END;
    }

    /* Initialize the handle */
    Handle = NULL;

    /* Open the section object */
    Status = ObOpenObjectByName(ObjectAttributes,
                                MmSectionObjectType,
                                PreviousMode,
                                NULL,
                                DesiredAccess,
                                NULL,
                                &Handle);

    /* Use SEH for pointer access */
    _SEH2_TRY
    {
        /* Return the handle to the caller */
        *SectionHandle = Handle;
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        /* Ignore any exception we might get! */
    }
    _SEH2_END;

    /* Return the status */
    return Status;
}

VOID
SECTION_OBJECT::QueryBasicInformation (
    _Out_ PSECTION_BASIC_INFORMATION BasicInformation)
{
    BasicInformation->BaseAddress = m_Section->GetBaseAddress();
    BasicInformation->Attributes = m_SectionFlags; /// CHECKME
    BasicInformation->Size.QuadPart = m_SectionSize;
}

VOID
SECTION_OBJECT::QueryImagenformation (
    _Out_ PSECTION_IMAGE_INFORMATION ImageInformation)
{
    PSECTION_IMAGE_INFORMATION_EX ImageInformationEx;

    /* Get the image information */
    ImageInformationEx = m_Section->GetImageInformation();
    if (ImageInformationEx != NULL)
    {
        RtlCopyMemory(ImageInformation, ImageInformationEx, sizeof(*ImageInformation));
    }
    else
    {
        //NT_ASSERT((m_SectionFlags & SEC_IMAGE) == 0);
        RtlZeroMemory(ImageInformation, sizeof(*ImageInformation));
    }
}

NTSTATUS
NTAPI
MmQuerySectionInformation (
    _In_ PSECTION_OBJECT SectionObject,
    _In_ enum _SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_ PVOID SectionInformation,
    _In_ SIZE_T Length,
    _Out_ PSIZE_T ResultLength)
{
    NTSTATUS Status;

    switch (SectionInformationClass)
    {
    case SectionBasicInformation:

            if (Length < sizeof(SECTION_BASIC_INFORMATION))
            {
                return STATUS_INFO_LENGTH_MISMATCH;
            }

            SectionObject->QueryBasicInformation((PSECTION_BASIC_INFORMATION)SectionInformation);
            Status = STATUS_SUCCESS;
            break;

    case SectionImageInformation:

            if (Length < sizeof(SECTION_IMAGE_INFORMATION))
            {
                return STATUS_INFO_LENGTH_MISMATCH;
            }

            SectionObject->QueryImagenformation((PSECTION_IMAGE_INFORMATION)SectionInformation);
            Status = STATUS_SUCCESS;
            break;

    default:
        return STATUS_INVALID_INFO_CLASS;
    }

    return STATUS_SUCCESS;
}

// This should probably be a Ps function and use MmQuerySectionInformation
VOID
NTAPI
MmGetImageInformation (
    _Out_ PSECTION_IMAGE_INFORMATION ImageInformation)
{
    PSECTION_OBJECT SectionObject;

    /* Get the section object of this process*/
    SectionObject = static_cast<PSECTION_OBJECT>(PsGetCurrentProcess()->SectionObject);
    NT_ASSERT(SectionObject != NULL);

    /* Return the image information */
    SectionObject->QueryImagenformation(ImageInformation);
}

NTSTATUS
NTAPI
NtQuerySection (
    _In_ HANDLE SectionHandle,
    _In_ enum _SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_ PVOID SectionInformation,
    _In_ SIZE_T Length,
    _Out_ PSIZE_T ResultLength)
{
    KPROCESSOR_MODE PreviousMode;
    PSECTION_OBJECT SectionObject;
    PVOID SafeSectionInformation;
    SIZE_T SafeLength;
    NTSTATUS Status;
    union
    {
        SECTION_BASIC_INFORMATION BasicInformation;
        SECTION_IMAGE_INFORMATION ImageInformation;
    } InfoBuffer;

    /* Get the previous mode */
    PreviousMode = ExGetPreviousMode();

    /* Reference the section handle */
    Status = ObReferenceObjectByHandle(SectionHandle,
                                       SECTION_QUERY,
                                       MmSectionObjectType,
                                       PreviousMode,
                                       (PVOID*)&SectionObject,
                                       NULL);
    if (!NT_SUCCESS(Status))
    {
        //DPRINT1("Failed to reference the section handle\n");
        /// set result length?
        return Status;
    }

    /* Check the previous mode */
    if (PreviousMode != KernelMode)
    {
        /* UserMode, use the stack buffer */
        SafeSectionInformation = &InfoBuffer;
        SafeLength = min(Length, sizeof(InfoBuffer));
    }
    else
    {
        /* KernelMode, use the provided buffer directly */
        SafeSectionInformation = SectionInformation;
        SafeLength = Length;
    }

    /* Call the internal function */
    Status = MmQuerySectionInformation(SectionObject,
                                       SectionInformationClass,
                                       SafeSectionInformation,
                                       SafeLength,
                                       &SafeLength);

    /* Dereference the section object */
    ObDereferenceObject(SectionObject);

    /* Check if we need to return the data */
    if (NT_SUCCESS(Status))
    {
        if (PreviousMode != KernelMode)
        {
            _SEH2_TRY
            {
                if (ResultLength != NULL)
                    *ResultLength = SafeLength;

                /* Copy the data back to user mode */
                RtlCopyMemory(SectionInformation,
                              SafeSectionInformation,
                              SafeLength);
            }
            _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
            {
                Status = _SEH2_GetExceptionCode();
            }
            _SEH2_END;
        }
        else
        {
            if (ResultLength != NULL)
                *ResultLength = SafeLength;
        }
    }

    return Status;
}


NTSTATUS
NTAPI
NtExtendSection (
    _In_ HANDLE SectionHandle,
    _In_ PLARGE_INTEGER NewMaximumSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtAreMappedFilesTheSame (
    _In_ PVOID File1MappedAsAnImage,
    _In_ PVOID File2MappedAsFile)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}



}; // extern "C"

}; // namespace Mm
