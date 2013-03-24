/*!
 * \file SectionObject.cpp
 * ...
 */

#include "SectionObject.hpp"
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
    ObjectTypeInitializer.UseDefaultObject = FALSE;
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
    PVOID SectionPointer;
    SECTION_OBJECT* SectionObject;
    NTSTATUS Status;

    /* Allocate a section object with Ob */
    Status = Ob::OBJECT::CreateObject(&SectionPointer,
                                      MmSectionObjectType,
                                      ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        //ERR("Failed to create a section object: 0x%lx\n", Status);
        return Status;
    }

    /* Initialize the object */
    SectionObject = new(SectionPointer) SECTION_OBJECT;



    /* Return the section */
    *OutSectionObject = SectionObject;

    return STATUS_SUCCESS;
}



/** Exported API **************************************************************/

extern "C" {

/** Internal API **************************************************************/

PFILE_OBJECT
NTAPI
MmGetFileObjectForSection (
    _In_ PVOID Section)
{
    SECTION_OBJECT* SectionObject = static_cast<SECTION_OBJECT*>(Section);

    return SectionObject->GetFileObject();
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
        Status = ObReferenceObjectByHandle(FileHandle,
                                           DesiredAccess,
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
            //ERR("Exception!\n");
            //Status = _SEH2_GetExceptionCode();
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
NtMapViewOfSection(
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
#if 0
    PVOID SafeBaseAddress;
    LARGE_INTEGER SafeSectionOffset;
    SIZE_T SafeViewSize;

    /* Check if this call comes from user mode */
    if (ExGetPreviousMode() != KernelMode)
    {
        /* Use SEH to copy the buffers */
        _SEH2_TRY
        {
            ProbeForRead(MaximumSize, sizeof(*MaximumSize), 1);
            SafeMaximumSize = *MaximumSize;
            MaximumSize = &SafeMaximumSize;
            ProbeForRead(ObjectAttributes, sizeof(*ObjectAttributes), 1);
            SafeObjectAttributes = *ObjectAttributes;
            ObjectAttributes = &SafeObjectAttributes;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            //ERR("Could not
            _SEH2_YIELD(return _SEH2_GetExceptionCode();)
        }
        _SEH2_END;
    }
#endif
    return 0;
}

}; // extern "C"

}; // namespace Mm
