/*!
 * \file SectionObject.cpp
 * ...
 */

#include "SectionObject.hpp"
#include "Section.hpp"
#include <ndk/iotypes.h>
#include <ndk/obfuncs.h>

POBJECT_TYPE MmSectionObjectType;

namespace Mm {

VOID
SECTION_OBJECT::InitializeClass (
    VOID)
{
    static const UNICODE_STRING ObjectName = RTL_CONSTANT_STRING(L"Section");
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
    PSECTION Section;
    NTSTATUS Status;

    /* Check if this is a file backed section */
    if (FileObject == NULL)
    {
        /* No backing file, so create a new page-file backed SECTION */
        Status = SECTION::CreatePageFileSection(&Section,
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
        PSECTION_OBJECT_POINTERS SectionObjectPointers = FileObject->SectionObjectPointer;

        if (SectionObjectPointers == NULL)
        {
            return STATUS_INVALID_FILE_FOR_SECTION;
        }

        if (AllocationAttributes & SEC_IMAGE)
        {
            // reference existing section or create a new one
            UNIMPLEMENTED;
        }
        else
        {
            // reference existing section or create a new one
            UNIMPLEMENTED;
        }
    }

    /* Allocate a section object with Ob */
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

class SECTION*
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
        /// \todo properly calculate access
        FileAccess = FILE_READ_DATA | FILE_WRITE_DATA | SYNCHRONIZE;

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
__debugbreak();

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
        if (!NT_SUCCESS(Status))
        {
            ObDereferenceObject(SectionObject);
        }
    }

    /* Check if this call comes from user mode */
    if (ExGetPreviousMode() != KernelMode)
    {
        /* Use SEH to return the handle */
        _SEH2_TRY
        {
            ProbeForWriteHandle(OutSectionHandle);
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
        *OutSectionHandle = SectionHandle;
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
            ProbeForWriteHandle(SectionHandle);
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

NTSTATUS
NTAPI
NtQuerySection (
    _In_ HANDLE SectionHandle,
    _In_ enum _SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_ PVOID SectionInformation,
    _In_ SIZE_T Length,
    _Out_ PSIZE_T ResultLength)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
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
