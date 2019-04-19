/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            ntoskrnl/ob/life.c
 * PURPOSE:         Ob functions for creating and destroying objects
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#include "ob_internal.h"

#define NDEBUG
#include <debug.h>

/*! \name ObpAllocateObject
 *
 *  \brief Allocates an object including requested headers and initializes
 *      the headers.
 *
 *  \param [in] ObjectType
 *      Pointer to the object type for the new object.
 *
 *  \param [in] ObjectSize
 *      Size of the object body in bytes.
 *
 *  \param [in] InfoMask
 *      A mask that describes what headers are to use. The value can be a
 *      combination of the OBJECT_HEADER_*_INFO_MASK constants.
 *
 *  \param [in] ObjectName
 *      Pointer to a unicode string that contains the name for the new object.
 *      Only relevant when OBJECT_HEADER_NAME_INFO_MASK is set in InfoMask.
 *
 *  \param [in] NameProbeMode
 *      Specifies the mode for probing / checking access to the name parameter.
 *      Can be either KernelMode or UserMode. The latter indicates that both
 *      The UNICODE_STRING structure, as well as the Buffer are user mode data.
 *
 *  \param [out] ResultObject
 *      Pointer to variable reveives the pointer to the object body.
 *
 *  \return
 *      NTSTATUS value, describing the status of the operation.
 *      In case of a failure, *ResultObject is undefined.
 */
NTSTATUS
NTAPI
ObpAllocateObject(
    IN POBJECT_TYPE ObjectType,
    IN ULONG ObjectSize,
    IN UCHAR InfoMask,
    IN PUNICODE_STRING ObjectName OPTIONAL,
    IN KPROCESSOR_MODE NameProbeMode OPTIONAL,
    OUT PVOID *ResultObject)
{
    POBJECT_HEADER ObjectHeader;
    UCHAR HeaderSize;
    PUCHAR Pointer;
    NTSTATUS Status;

    /* Calculate the size of the headers */
    HeaderSize =  ObpObjectHeaderInfoSize[InfoMask];
    HeaderSize += FIELD_OFFSET(OBJECT_HEADER, Body);

    /* Allocate the structure */
    Pointer = ExAllocatePoolWithTag(ObjectType->TypeInfo.PoolType,
                                    ObjectSize + HeaderSize,
                                    ObjectType->Key);
    if (!Pointer)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Calculate the pointers for body and header */
    *ResultObject = (PVOID)(Pointer + HeaderSize);
    ObjectHeader = CONTAINING_RECORD(*ResultObject, OBJECT_HEADER, Body);

    /* Initialize the object header */
    ExInitializePushLock(&ObjectHeader->Lock);
    ObjectHeader->PointerCount = 0;
    ObjectHeader->HandleCount = 0;
    ObjectHeader->TypeIndex = ObjectType->Index;
    ObjectHeader->TraceFlags = 0;
    ObjectHeader->Flags = 0;
    ObjectHeader->InfoMask = InfoMask;
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->SecurityDescriptor = NULL;

    /* Check if there is a creator info */
    if (InfoMask & OBJECT_HEADER_CREATOR_INFO_MASK)
    {
        POBJECT_HEADER_CREATOR_INFO CreatorInfo;

        CreatorInfo = ObpGetHeaderCreatorInfo(ObjectHeader);
        CreatorInfo->CreatorUniqueProcess = 0;
        CreatorInfo->CreatorBackTraceIndex = 0;

        /* Check if a type list is to be maintained */
        if (ObjectType->TypeInfo.MaintainTypeList)
        {
            /* Insert the header into the object type's list */
            ExAcquirePushLockExclusive(&ObjectType->TypeLock);
            InsertTailList(&ObjectType->TypeList, &CreatorInfo->TypeList);
            ExReleasePushLockExclusive(&ObjectType->TypeLock);
        }
    }

    /* Check if there is a name info */
    if (InfoMask & OBJECT_HEADER_NAME_INFO_MASK)
    {
        POBJECT_HEADER_NAME_INFO NameInfo;

        NameInfo = ObpGetHeaderNameInfo(ObjectHeader);
        NameInfo->Directory = NULL;
        NameInfo->ReferenceCount = 0;

        /* Make a copy of the object name */
        Status = ObpDuplicateString(&NameInfo->Name, ObjectName, NameProbeMode);
        if (!NT_SUCCESS(Status))
        {
            /* Free the allocation and return the failure status */
            ExFreePool(Pointer);
            *ResultObject = NULL;
            return Status;
        }
    }

    /* Check if there is a process info */
    if (InfoMask & OBJECT_HEADER_PROCESS_INFO_MASK)
    {
        __debugbreak();
    }

    /* Check if there is a quota info */
    if (InfoMask & OBJECT_HEADER_QUOTA_INFO_MASK)
    {
        __debugbreak();
    }

    /* Check if there is a handle info */
    if (InfoMask & OBJECT_HEADER_HANDLE_INFO_MASK)
    {
        __debugbreak();
    }

    /* All done, return success */
    return STATUS_SUCCESS;
}

static
NTSTATUS
CaptureObjectCreateInformation (
    _In_ POBJECT_ATTRIBUTES UnsafeObjectAttributes,
    _Out_ POBJECT_ATTRIBUTES OutObjectAttributes,
    _Out_ PUNICODE_STRING OutObjectName)
{
    volatile PVOID Buffer = NULL;

    _SEH2_TRY
    {
        /* Probe and copy the object attributes structure */
        ProbeForRead(UnsafeObjectAttributes, sizeof(OBJECT_ATTRIBUTES), 1);
        *OutObjectAttributes = *UnsafeObjectAttributes;

        /* Check if we have an object name */
        if (UnsafeObjectAttributes->ObjectName)
        {
            /* Probe and copy the object name */
            ProbeForRead(UnsafeObjectAttributes->ObjectName, sizeof(UNICODE_STRING), 1);
            NameLength = *UnsafeObjectAttributes->ObjectName.Length;

            if (NameLength > 0)
            {
                /* Make sure we have no invalid length */
                if (NameLength & 1)
                {
                    Status = STATUS_INVALID_PARAMETER;
                    _SEH2_LEAVE;
                }

                /* Allocate a string buffer */
                Buffer = ExAllocatePoolWithTag(PagedPool,
                                               NameLength + sizeof(WCHAR),
                                               TAG_NAME);
                if (Buffer == NULL)
                {
                    Status = STATUS_INSUFFICIENT_RESOURCES;
                    _SEH2_LEAVE;
                }

                /* Probe and copy the name buffer */
                ProbeForRead(OutObjectName->Buffer, NameLength, sizeof(WCHAR));
                RtlCopyMemory(Buffer, OutObjectName->Buffer, NameLength);

                /* Initialize the output string */
                OutObjectName->Buffer = Buffer;
                OutObjectName->Length = NameLength;
                OutObjectName->MaximumLength = NameLength + sizeof(WCHAR);

                /* Zero-terminate the buffer */
                OutObjectName->Buffer[NameLength / sizeof(WCHAR)] = L'\0';
            }
            else
            {
                OutObjectName->Buffer = NULL;
                OutObjectAttributes->ObjectName = NULL;
            }

        }
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        /* Cleanup allocation, if any */
        if (Buffer != NULL)
        {
            ExFreePoolWithTag(Buffer, TAG_NAME);
        }

        /* Return the exception code */
        Status = _SEH2_GetExceptionCode();
    }
    _SEH2_END;

    return Status;
}

NTSTATUS
NTAPI
ObCreateObject(
    IN KPROCESSOR_MODE ObjectAttributesAccessMode OPTIONAL,
    IN POBJECT_TYPE ObjectType,
    IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
    IN KPROCESSOR_MODE AccessMode,
    IN OUT PVOID ParseContext OPTIONAL,
    IN ULONG ObjectSize,
    IN ULONG PagedPoolCharge OPTIONAL,
    IN ULONG NonPagedPoolCharge OPTIONAL,
    OUT PVOID *Object)
{
    OBJECT_ATTRIBUTES LocalObjectAttributes;
    UNICODE_STRING ObjectName;
    UCHAR InfoMask = 0;
    NTSTATUS Status;

    /* Default to failure */
    *Object = NULL;

    if (ObjectAttributes)
    {
        /* Capture object attributes, making a copy of all data */
        Status = CaptureObjectAttributes(ObjectAttributes,
                                         ObjectAttributesAccessMode,
                                         &LocalObjectAttributes,
                                         &ObjectName);


        if (ObjectAttributesAccessMode != KernelMode)
        {
            // Make sure CreateInformation->ObjectAttributes & OBJ_KERNEL_HANDLE is 0
            __debugbreak();
            _SEH2_TRY
            {
                /* Probe and copy the object attributes structure */
                ProbeForRead(ObjectAttributes, sizeof(OBJECT_ATTRIBUTES), 1);
                LocalObjectAttributes = *ObjectAttributes;
            }
            _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
            {
                /* Return the exception code */
                Status = _SEH2_GetExceptionCode();
                _SEH2_YIELD(return Status;)
            }
            _SEH2_END;

            /* Use the local copy */
            ObjectAttributes = &LocalObjectAttributes;
        }

        ObjectName = ObjectAttributes->ObjectName;
        if (ObjectName)
        {
            InfoMask |= OBJECT_HEADER_NAME_INFO_MASK;
            __debugbreak();

            if (ObjectAttributesAccessMode != KernelMode)
            {
                _SEH2_TRY
                {
                    /* Probe and copy the unicode string */
                    ProbeForRead(ObjectName, sizeof(*ObjectName), 1);
                    Length = ObjectName->Length;

                }
                _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
                {
                    /* Return the exception code */
                    Status = _SEH2_GetExceptionCode();
                    _SEH2_YIELD(return Status;)
                }
                _SEH2_END;

                /* Use the local copy */
                ObjectAttributes = &LocalObjectAttributes;
            }

        }


    }
    else
    {
        ObjectName = NULL;
    }


    /* Allocate the object */
    Status = ObpAllocateObject(ObjectType,
                               ObjectSize,
                               InfoMask,
                               ObjectName,
                               ObjectAttributesAccessMode,
                               Object);

 //   __debugbreak();


    return Status;
}


/*! \name ObCreateObjectType
 *
 *  \remarks
 *      If the function fails it will leak an object type index. But since the
 *      function is for internal use only and can only fail if the name of the
 *      object type already existed or on very low memory, it shouldn't be an
 *      issue. To fix this, the running index number could be protected with
 *      a global lock.
 */
NTSTATUS
NTAPI
ObCreateObjectType(
    IN PUNICODE_STRING TypeName,
    IN POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    IN PVOID Reserved,
    OUT POBJECT_TYPE *ResultObjectType)
{
    POBJECT_TYPE ObjectType;
    POBJECT_HEADER ObjectHeader;
    POBJECT_HEADER_NAME_INFO HeaderNameInfo;
    NTSTATUS Status;
    ULONG Key = 0;
    LONG TypeIndex;

    /* First get a type index */
    TypeIndex = InterlockedIncrement(&ObpLastObjectIndex);
    ASSERT(TypeIndex < MAX_OBJECT_TYPES);

    /* Allocate a type object */
    Status = ObpAllocateObject(ObpTypeObjectType,
                               sizeof(OBJECT_TYPE),
                               OBJECT_HEADER_CREATOR_INFO_MASK |
                                   OBJECT_HEADER_NAME_INFO_MASK,
                               TypeName,
                               KernelMode,
                               (PVOID*)&ObjectType);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Get the header and name info */
    ObjectHeader = CONTAINING_RECORD(ObjectType, OBJECT_HEADER, Body);
    HeaderNameInfo = ObpGetHeaderNameInfo(ObjectHeader);

    /* Construct a key / pooltag from the type name */
    ((PCHAR)&Key)[0] = (CHAR)TypeName->Buffer[0];
    if (TypeName->Length > 2) ((PCHAR)&Key)[1] = (CHAR)TypeName->Buffer[1];
    if (TypeName->Length > 4) ((PCHAR)&Key)[2] = (CHAR)TypeName->Buffer[2];
    if (TypeName->Length > 6) ((PCHAR)&Key)[3] = (CHAR)TypeName->Buffer[3];

    /* Initialize the basic type fields */
    InitializeListHead(&ObjectType->TypeList);
    InitializeListHead(&ObjectType->CallbackList);
    ExInitializePushLock(&ObjectType->TypeLock);
    ObjectType->Key = Key;
    ObjectType->Name = HeaderNameInfo->Name;
    ObjectType->Index = (UCHAR)TypeIndex;
    ObjectType->DefaultObject = 0; // FIXME
    ObjectType->TotalNumberOfObjects = 0;
    ObjectType->HighWaterNumberOfObjects = 0;
    ObjectType->TotalNumberOfHandles = 0;
    ObjectType->HighWaterNumberOfHandles = 0;

    /* Copy the type initializer */
    ObjectType->TypeInfo = *ObjectTypeInitializer;

    /* Insert it into the Type object directory */
    Status = ObpInsertDirectoryEntry(ObpTypeDirectoryObject, ObjectType);
    if (!NT_SUCCESS(Status))
    {
        /* Dereference the type object and return failure status */
        ObDereferenceObject(ObjectType);
        *ResultObjectType = NULL;
        return Status;
    }

    *ResultObjectType = ObjectType;
    return STATUS_SUCCESS;
}


VOID
NTAPI
ObMakeTemporaryObject(
  IN PVOID Object)
{
    __debugbreak();
}

NTSTATUS
NTAPI
NtMakeTemporaryObject(
    IN HANDLE Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtMakePermanentObject(
    IN HANDLE Object)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS
NTAPI
ObDuplicateObject(
    IN PEPROCESS SourceProcess,
    IN HANDLE SourceHandle,
    IN PEPROCESS TargetProcess OPTIONAL,
    IN PHANDLE TargetHandle OPTIONAL,
    IN ACCESS_MASK DesiredAccess,
    IN ULONG HandleAttributes,
    IN ULONG Options,
    IN KPROCESSOR_MODE PreviousMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

